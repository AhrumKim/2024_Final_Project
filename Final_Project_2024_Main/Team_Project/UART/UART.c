/*
 * UART.c
 *
 *  Created on: 2024. 10. 29.
 *      Author: FM17
 */


#include "UART.h"
#include "PWM.h"
#include "PID.h"
#include "Encoder.h"

float data_pwm;
float data_ref;
float data_rad;
float data_rpm;

#define ASC_TX_BUFFER_SIZE                256
#define ASC_RX_BUFFER_SIZE                256

#define ASC_BAUDRATE                      115200

//----------------- Main <-> PC -----------------//
#define ISR_PRIORITY_ASCLIN_TX_PC       8
#define ISR_PRIORITY_ASCLIN_RX_PC        4
#define ISR_PRIORITY_ASCLIN_ER_PC        12

static IfxAsclin_Asc PC_ascHandle0;

uint8 PC_uartTxBuffer[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
uint8 PC_uartRxBuffer[ASC_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];


//----------------- Main <-> Sub -----------------//
#define ISR_PRIORITY_ASCLIN_TX_SUB        9
#define ISR_PRIORITY_ASCLIN_RX_SUB        5
#define ISR_PRIORITY_ASCLIN_ER_SUB        13

static IfxAsclin_Asc SUB_ascHandle0;

uint8 SUB_uartTxBuffer[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
uint8 SUB_uartRxBuffer[ASC_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];


//----------------- Main <-> PC -----------------//
void init_UART_PC(void){
    IfxAsclin_Asc_Config    ascConf;

    IfxAsclin_Asc_initModuleConfig(&ascConf, &MODULE_ASCLIN3);

    ascConf.baudrate.baudrate   = ASC_BAUDRATE;
    ascConf.baudrate.oversampling   = IfxAsclin_OversamplingFactor_16;

    ascConf.bitTiming.medianFilter  = IfxAsclin_SamplesPerBit_three;
    ascConf.bitTiming.samplePointPosition   = IfxAsclin_SamplePointPosition_8;

    ascConf.interrupt.txPriority    = ISR_PRIORITY_ASCLIN_TX_PC;
    ascConf.interrupt.rxPriority    = ISR_PRIORITY_ASCLIN_RX_PC;
    ascConf.interrupt.erPriority    = ISR_PRIORITY_ASCLIN_ER_PC;
    ascConf.interrupt.typeOfService = IfxSrc_Tos_cpu0;

    const IfxAsclin_Asc_Pins pins = {
            .tx         = &IfxAsclin3_TX_P15_7_OUT,
            .txMode     = IfxPort_OutputMode_pushPull,
            .rx         = &IfxAsclin3_RXD_P32_2_IN,
            .rxMode     = IfxPort_InputMode_pullUp,
            .cts        = NULL_PTR,
            .ctsMode    = IfxPort_InputMode_pullUp,
            .rts        = NULL_PTR,
            .rtsMode    = IfxPort_OutputMode_pushPull,
            .pinDriver  =IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    ascConf.pins = &pins;

    ascConf.txBuffer        = PC_uartTxBuffer;
    ascConf.txBufferSize    = ASC_TX_BUFFER_SIZE;
    ascConf.rxBuffer        = PC_uartRxBuffer;
    ascConf.rxBufferSize    = ASC_RX_BUFFER_SIZE;

    IfxAsclin_Asc_initModule(&PC_ascHandle0, &ascConf);



    Uart_SUB_Output='X';
}


void out_UART_PC(uint8 data){

    if(Sudden_accel_flag == 0){
        data_ref = target_speed*34000/100;        // 목표 속도 출력
    }
    else{
        data_ref = 0;
    }
    int d100 = ((int)data_ref)/100;
    int d10 = (((int)data_ref)/10)%10;
    int d1 = ((int)data_ref)%10;
    int d0 = ((int)(data_ref*10))%10;

    data_rad = velocity_rad/100;           // 현재 속도 출력

    int r100 = ((int)data_rad/100);
    int r10 = (((int)data_rad)/10)%10;
    int r1 = ((int)data_rad)%10;
    int r0 = ((int)(data_rad*10))%10;

    Ifx_SizeT count = 20;

    uint8 dataSet[count];

    dataSet[0] = 'R';
    dataSet[1] = 'e';
    dataSet[2] = 'f';
    dataSet[3] = ',';
    dataSet[4] = 'R';
    dataSet[5] = 'P';
    dataSet[6] = 'M';
    dataSet[7] = '\n';

    dataSet[8] = (char)((d100)+'0');
    dataSet[9] = (char)((d10)+'0');
    dataSet[10] = (char)((d1)+'0');
    dataSet[11] = '.';
    dataSet[12] = (char)((d0)+'0');
    dataSet[13] = ',';

    dataSet[14] = (char)((r100)+'0');
    dataSet[15] = (char)((r10)+'0');
    dataSet[16] = (char)((r1)+'0');
    dataSet[17] = '.';
    dataSet[18] = (char)((r0)+'0');
    dataSet[19] = '\n';

    IfxAsclin_Asc_write(&PC_ascHandle0, dataSet, &count, TIME_INFINITE);

    if(Uart_PC_Output == 'W'){   // 경고
        Ifx_SizeT count_W = 12;

        uint8 dataSet_W[count_W];

        dataSet_W[0] = 'T';
        dataSet_W[1] = 'e';
        dataSet_W[2] = 'm';
        dataSet_W[3] = 'p';
        dataSet_W[4] = 'W';
        dataSet_W[5] = 'a';
        dataSet_W[6] = 'r';
        dataSet_W[7] = 'n';
        dataSet_W[8] = 'i';
        dataSet_W[9] = 'n';
        dataSet_W[10] = 'g';
        dataSet_W[11] = '\n';
        IfxAsclin_Asc_write(&PC_ascHandle0, dataSet_W, &count, TIME_INFINITE);
    }


}



//----------------- Main <-> Sub -----------------//
void init_UART_SUB(void){
    IfxAsclin_Asc_Config    ascConf;

    IfxAsclin_Asc_initModuleConfig(&ascConf, &MODULE_ASCLIN2);

    ascConf.baudrate.baudrate   = ASC_BAUDRATE;
    ascConf.baudrate.oversampling   = IfxAsclin_OversamplingFactor_16;

    ascConf.bitTiming.medianFilter  = IfxAsclin_SamplesPerBit_three;
    ascConf.bitTiming.samplePointPosition   = IfxAsclin_SamplePointPosition_8;

    ascConf.interrupt.txPriority    = ISR_PRIORITY_ASCLIN_TX_SUB;
    ascConf.interrupt.rxPriority    = ISR_PRIORITY_ASCLIN_RX_SUB;
    ascConf.interrupt.erPriority    = ISR_PRIORITY_ASCLIN_ER_SUB;
    ascConf.interrupt.typeOfService = IfxSrc_Tos_cpu0;

    const IfxAsclin_Asc_Pins pins = {
            .tx         = &IfxAsclin2_TX_P33_9_OUT,
            .txMode     = IfxPort_OutputMode_pushPull,
            .rx         = &IfxAsclin2_RXE_P33_8_IN,
            .rxMode     = IfxPort_InputMode_pullUp,
            .cts        = NULL_PTR,
            .ctsMode    = IfxPort_InputMode_pullUp,
            .rts        = NULL_PTR,
            .rtsMode    = IfxPort_OutputMode_pushPull,
            .pinDriver  = IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    ascConf.pins = &pins;

    ascConf.txBuffer        = SUB_uartTxBuffer;
    ascConf.txBufferSize    = ASC_TX_BUFFER_SIZE;
    ascConf.rxBuffer        = SUB_uartRxBuffer;
    ascConf.rxBufferSize    = ASC_RX_BUFFER_SIZE;

    IfxAsclin_Asc_initModule(&SUB_ascHandle0, &ascConf);

}

// 서브 보드로 데이터 전송
void out_UART_SUB(const unsigned char chr){
        IfxAsclin_Asc_blockingWrite(&SUB_ascHandle0, chr);
}


//----------------- Main <-> PC -----------------//
IFX_INTERRUPT(asc0TxISR, 0, ISR_PRIORITY_ASCLIN_TX_PC);
void asc0TxISR(void){
    IfxAsclin_Asc_isrTransmit(&PC_ascHandle0);
}

IFX_INTERRUPT(asc0RxISR, 0, ISR_PRIORITY_ASCLIN_RX_PC);
void asc0RxISR(void){
    IfxAsclin_Asc_isrReceive(&PC_ascHandle0);

    if(RXcnt_PC == byte0){
        RXcnt_PC = byte1;
        RXDATA_PC[byte0] = IfxAsclin_Asc_blockingRead(&PC_ascHandle0);
    }

    else if(RXcnt_PC == byte1){
        RXcnt_PC = byte0;
        RXDATA_PC[byte1] = IfxAsclin_Asc_blockingRead(&PC_ascHandle0);
    }
    if(RXDATA_PC[0] == 'C' && RXDATA_PC[1] == '\n'){Uart_SUB_Output = 'O';}
    else{Uart_SUB_Output = 'X';}

}

IFX_INTERRUPT(asc0ErrISR, 0, ISR_PRIORITY_ASCLIN_ER_PC);
void asc0ErrISR(void){
    while(1);
}



//----------------- Main <-> Sub -----------------//
IFX_INTERRUPT(asc2TxISR, 0, ISR_PRIORITY_ASCLIN_TX_SUB);
void asc2TxISR(void){
    IfxAsclin_Asc_isrTransmit(&SUB_ascHandle0);
}

IFX_INTERRUPT(asc2RxISR, 0, ISR_PRIORITY_ASCLIN_RX_SUB);
void asc2RxISR(void){
    IfxAsclin_Asc_isrReceive(&SUB_ascHandle0);

    if(RXcnt_SUB == byte0){
        RXcnt_SUB = byte1;
        RXDATA_SUB[byte0] = IfxAsclin_Asc_blockingRead(&SUB_ascHandle0);
    }

    else if(RXcnt_SUB == byte1){
            RXcnt_SUB = byte2;
            RXDATA_SUB[byte1] = IfxAsclin_Asc_blockingRead(&SUB_ascHandle0);
    }
    else if(RXcnt_SUB == byte2){
                RXcnt_SUB = byte0;
                RXDATA_SUB[byte2] = IfxAsclin_Asc_blockingRead(&SUB_ascHandle0);
    }
    if(RXDATA_SUB[0] == 'E' && RXDATA_SUB[1] == 'H' && RXDATA_SUB[2] == '\n'){
        Uart_PC_Output = 'W';   // 경고
    }
    else{Uart_PC_Output = 'S';} // 안전
}

IFX_INTERRUPT(asc2ErrISR, 0, ISR_PRIORITY_ASCLIN_ER_SUB);
void asc2ErrISR(void){
    while(1);
    //ch='X';
}
