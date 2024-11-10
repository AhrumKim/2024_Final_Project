/*
 * PWM.c
 *
 *  Created on: 2024. 10. 25.
 *      Author: FM22
 */
#include "UART.h"

#define ASC_TX_BUFFER_SIZE              256         /* 버퍼 사이즈 설정 변수 */
#define ASC_RX_BUFFER_SIZE              256
#define ASC_BAUDRATE                 115200
#define ISR_PRIORITY_ASCLIN_TX          8
#define ISR_PRIORITY_ASCLIN_RX          4
#define ISR_PRIORITY_ASCLIN_ER          12

static IfxAsclin_Asc        g_ascHandle0;

uint8 g_uartTxBuffer[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
uint8 g_uartRxBuffer[ASC_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

void init_UART(void)
{
    IfxAsclin_Asc_Config ascConf;

    /* Set default configurations */
    IfxAsclin_Asc_initModuleConfig(&ascConf, &MODULE_ASCLIN3); /* Initialize the structure with default values*/

    /* Set the desired baud rate */
    ascConf.baudrate.baudrate               = ASC_BAUDRATE;
    ascConf.baudrate.oversampling           = IfxAsclin_OversamplingFactor_16;

    /* Configure the sampling mode */
    ascConf.bitTiming.medianFilter          = IfxAsclin_SamplesPerBit_three;
    ascConf.bitTiming.samplePointPosition   = IfxAsclin_SamplePointPosition_8;

    /* ISR priorities and interrupt target */
    ascConf.interrupt.txPriority    = ISR_PRIORITY_ASCLIN_TX;/* TX 인터럽트 순위 설정*/
    ascConf.interrupt.rxPriority    = ISR_PRIORITY_ASCLIN_RX;/*RX 인터럽트 순위 설정*/
    ascConf.interrupt.erPriority    = ISR_PRIORITY_ASCLIN_ER;/* 에러 인터럽트 순위 설정*/
    ascConf.interrupt.typeOfService = IfxSrc_Tos_cpu0;/* 인터럽트 발생 CPU 설정 */



    /* Pin configuration */
    const IfxAsclin_Asc_Pins pins = {
            .tx         = &IfxAsclin3_TX_P15_7_OUT,/* TX 핀 설정*/
            .txMode     = IfxPort_OutputMode_pushPull,/* TX 핀 설정 */
            .rx         = &IfxAsclin3_RXD_P32_2_IN,/* RX 핀 설정 */
            .rxMode     = IfxPort_InputMode_pullUp, /*RX 핀 모드 설정*/
            .cts        = NULL_PTR, /* CTS pin not used(clear to send)*/
            .ctsMode    = IfxPort_InputMode_pullUp,
            .rts        = NULL_PTR,/* RTS pin not used(request to send)*/
            .rtsMode    = IfxPort_OutputMode_pushPull,
            .pinDriver = IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    ascConf.pins = &pins;


    /* FIFO buffers configuration */
    ascConf.txBuffer = g_uartTxBuffer;                  /* Set the transmission buffer*//*Tx: IfxAsclin0_TX_P14_0_OUT  Rx: IfxAsclin0_RXA_P14_1_IN*/
    ascConf.txBufferSize = ASC_TX_BUFFER_SIZE;          /* Set the transmission buffer size*/
    ascConf.rxBuffer = g_uartRxBuffer;                  /* Set the receiving buffer*/
    ascConf.rxBufferSize = ASC_RX_BUFFER_SIZE;          /* Set the receiving buffer size*/

    /* Init ASCLIN module */
    IfxAsclin_Asc_initModule(&g_ascHandle0, &ascConf);   /* Initialize the module with the given configuration     ← 설정 값 반영*/
}


void out_UART0 (const unsigned char chr)
{
    IfxAsclin_Asc_blockingWrite(&g_ascHandle0, chr);
}
IFX_INTERRUPT (asc0TxISR, 0, ISR_PRIORITY_ASCLIN_TX);
void asc0TxISR (void) {IfxAsclin_Asc_isrTransmit(&g_ascHandle0);}

IFX_INTERRUPT (asc0RxISR, 0, ISR_PRIORITY_ASCLIN_RX);
void asc0RxISR (void)
{
    IfxAsclin_Asc_isrReceive(&g_ascHandle0);
    RXDATA = IfxAsclin_Asc_blockingRead(&g_ascHandle0);

    RXcnt++;
}

IFX_INTERRUPT(asc0ErrISR, 0, ISR_PRIORITY_ASCLIN_ER);
void asc0ErrISR (void) {while(1); }
