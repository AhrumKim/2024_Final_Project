/*CAN.c*/
#include "CAN.h"

void init_CAN(void)
{
    /* CAN 모듈 초기화 */
    /*create module config*/
    IfxMultican_Can_Config  canConfig;
    IfxMultican_Can_initModuleConfig(&canConfig, &MODULE_CAN);

    /*intialize module*/
    IfxMultican_Can_initModule(&CANstr01.can, &canConfig);

    /*CAN 노드 초기화*/
    /*create CAN node config*/
    IfxMultican_Can_NodeConfig  canNodeConfig;
    IfxMultican_Can_Node_initConfig(&canNodeConfig, &CANstr01.can);

    canNodeConfig.baudrate  = 500000UL;
    canNodeConfig.nodeId    = (IfxMultican_NodeId)((int)IfxMultican_NodeId_0);
    canNodeConfig.rxPin     = &IfxMultican_RXD0B_P20_7_IN;
    canNodeConfig.rxPinMode = IfxPort_InputMode_pullUp;
    canNodeConfig.txPin     = &IfxMultican_TXD0_P20_8_OUT;
    canNodeConfig.txPinMode = IfxPort_OutputMode_pushPull;

    IfxMultican_Can_Node_init(&CANstr01.canSrcNode, &canNodeConfig);

    /* 각각의 CAN msgID 초기화 */
    /* TX */
    init_CAN_Obj(0u, 0x100, IfxMultican_Frame_transmit, IfxMultican_DataLengthCode_8, FALSE, &CANstr01.CanEcu1MsgTxObj[0]);
    init_CAN_Obj(1u, 0x101, IfxMultican_Frame_transmit, IfxMultican_DataLengthCode_8, FALSE, &CANstr01.CanEcu1MsgTxObj[1]);
    init_CAN_Obj(2u, 0x102, IfxMultican_Frame_transmit, IfxMultican_DataLengthCode_8, FALSE, &CANstr01.CanEcu1MsgTxObj[2]);

    /* RX */
    init_CAN_Obj(3u, 0x100, IfxMultican_Frame_receive, IfxMultican_DataLengthCode_8, FALSE, &CANstr01.CanEcu1MsgRxObj[0]);
}

void init_CAN_Obj(int32_t msgObjId, uint32_t msgId, uint8_t frameType, uint8_t msgDlc, uint32_t extendedFrame, IfxMultican_Can_MsgObj* pArrObjNum)
{
    /* create message object config */
    IfxMultican_Can_MsgObjConfig       canMsgObjConfig;
    IfxMultican_Can_MsgObj_initConfig(&canMsgObjConfig, &CANstr01.canSrcNode);

    canMsgObjConfig.msgObjId                = msgObjId;
    canMsgObjConfig.messageId               = msgId;
    canMsgObjConfig.frame                   = frameType;
    canMsgObjConfig.control.messageLen      = msgDlc;
    canMsgObjConfig.control.extendedFrame   = extendedFrame;
    canMsgObjConfig.acceptanceMask          = 0x7FFFFFFFUL;
    canMsgObjConfig.control.matchingId      = TRUE;

    if (frameType == IfxMultican_Frame_receive)
    {
        canMsgObjConfig.rxInterrupt.enabled = TRUE;
        canMsgObjConfig.rxInterrupt.srcId   = 0u;
        SRC_CAN_CAN0_INT0.B.SRPN            = 30u;
        SRC_CAN_CAN0_INT0.B.TOS             = 0u;
        SRC_CAN_CAN0_INT0.B.SRE             = 1u;
    }

    /* initialize message object */
    IfxMultican_Can_MsgObj_init(pArrObjNum, &canMsgObjConfig);
}

void CAN_TX(void)
{
    const uint32 dataLow    = 0x12340000;
    const uint32 dataHigh   = 0x9abc0000;

    {
        IfxMultican_Message     msg;
        IfxMultican_Message_init(&msg, 0x100, dataLow, dataHigh, IfxMultican_DataLengthCode_8);
        while (IfxMultican_Can_MsgObj_sendMessage(&CANstr01.CanEcu1MsgTxObj[0], &msg) == IfxMultican_Status_notSentBusy)
        {}
    }
}

IFX_INTERRUPT(ISR_CAN_RX, 0, 30);
void ISR_CAN_RX(void)
{
    IfxMultican_Status      readStatus;

    IfxCpu_enableInterrupts();

    readStatus = IfxMultican_Can_MsgObj_readMessage(&CANstr01.CanEcu1MsgRxObj[0], &RxData[0]);
}
