/*
 * UART.c
 *
 *  Created on: 2024. 10. 29.
 *      Author: FM17
 */


#include "Header_USER.h"

#define ASC_TX_BUFFER_SIZE                256
#define ASC_RX_BUFFER_SIZE                256

#define ASC_BAUDRATE                      115200

//----------------- Main <-> Sub -----------------//
#define ISR_PRIORITY_ASCLIN_TX_SUB        9
#define ISR_PRIORITY_ASCLIN_RX_SUB        4
#define ISR_PRIORITY_ASCLIN_ER_SUB        13

static IfxAsclin_Asc SUB_ascHandle0;

uint8 SUB_uartTxBuffer[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
uint8 SUB_uartRxBuffer[ASC_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];


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

//char dataSet[5];

uint8 dataSet[3];
void out_UART_SUB(uint8 data){

    //float Num = 60;

    //int n100 = ((int)Num)/100;
//    int n10 = (((int)Num)/10)%10;
//    int n1 = ((int)Num)%10;
    //int n0 = ((int)(Num*10))%10;

    Ifx_SizeT count = 3;

    //uint8 dataSet[count];

    dataSet[0] = 'E';
    dataSet[1] = 'H';
    dataSet[2] = '\n';

    IfxAsclin_Asc_write(&SUB_ascHandle0, dataSet, &count, TIME_INFINITE);

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
            RXcnt_SUB = byte0;
            RXDATA_SUB[byte1] = IfxAsclin_Asc_blockingRead(&SUB_ascHandle0);
    }

    if(RXDATA_SUB[byte0] == 'O'){
        IfxPort_setPinHigh(PORT_102);
    }
    else if(RXDATA_SUB[byte0] == 'X'){
        IfxPort_setPinLow(PORT_102);
    }
    //RXDATA_SUB[byte0] = '1';
}

IFX_INTERRUPT(asc2ErrISR, 0, ISR_PRIORITY_ASCLIN_ER_SUB);
void asc2ErrISR(void){
    // while(1);
}

