/*UARYT.h*/

#ifndef CAN_CAN_H_
#define CAN_CAN_H_

#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif

#define ECU1_TX_OBJ_NUM     5u  /* TX Obj 사용 수 (=5개의 ID 사용)(사용자 임의 설정 값) */
#define ECU1_RX_OBJ_NUM     5u  /* RX Obj 사용 수 (=5개의 ID 사용)(사용자 임의 설정 값) */


typedef struct
{
    IfxMultican_Can         can;                                /**< \brief CAN driver handle */
    IfxMultican_Can_Node    canSrcNode;                         /**< \brief CAN driver Node */
    IfxMultican_Can_MsgObj  CanEcu1MsgTxObj[ECU1_TX_OBJ_NUM];   /**< \brief CAN Source Message object */
    IfxMultican_Can_MsgObj  CanEcu1MsgRxObj[ECU1_RX_OBJ_NUM];   /**< \brief CAN Source Message object */
}CANstr;

Global CANstr   CANstr01;

Global IfxMultican_Message RxData[3];

Global void Init_CAN(void);     /*CAN 초기화 함수*/
void Init_CAN_Obj(int32_t msgObjId, uint32_t msgId, uint8_t frameType, uint8_t msgDlc, uint32_t extendedFrame, IfxMultican_Can_MsgObj* pArrObjNum);
Global void CAN_TX(void);       /*송신 함수*/


#endif /* CAN_CAN_H_ */
