/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2020)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : EthSwt_Eth.h                                                **
**                                                                           **
**  VERSION    : 1.0.0                                                       **
**                                                                           **
**  DATE       : 2020-08-05                                                  **
**                                                                           **
**  VARIANT    : NA                                                          **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION  : This file exports EthSwt functions required by ETH driver **
**                  This file is for Evaluation Purpose Only                 **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: yes                                     **
**                                                                           **
******************************************************************************/

#ifndef ETHSWT_ETH_H
#define ETHSWT_ETH_H

#include "Std_Types.h"
#include "Eth_GeneralTypes.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

extern void EthSwt_EthTxAdaptBufferLength(uint16* LengthPtr);

extern Std_ReturnType EthSwt_EthTxPrepareFrame(uint8 CtrlIdx,
                  Eth_BufIdxType BufIdx, uint8** DataPtr, uint16* LengthPtr);

extern Std_ReturnType EthSwt_EthTxProcessFrame(uint8 CtrlIdx,
                  Eth_BufIdxType BufIdx, uint8** DataPtr, uint16* LengthPtr);

extern Std_ReturnType EthSwt_EthTxFinishedIndication(uint8 CtrlIdx,
                                                     Eth_BufIdxType BufIdx);

extern Std_ReturnType EthSwt_EthRxProcessFrame(uint8 CtrlIdx,
                 Eth_BufIdxType BufIdx, uint8** DataPtr, uint16* LengthPtr,
                 boolean* IsMgmtFrameOnlyPtr);

extern Std_ReturnType EthSwt_EthRxFinishedIndication(uint8 CtrlIdx,
                                                     Eth_BufIdxType BufIdx);

#endif /* end of ETHSWT_ETH_H */
