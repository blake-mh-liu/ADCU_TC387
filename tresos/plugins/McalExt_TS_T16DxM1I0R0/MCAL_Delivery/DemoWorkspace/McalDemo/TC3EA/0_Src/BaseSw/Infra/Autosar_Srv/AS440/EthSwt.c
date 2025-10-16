/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2021)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : EthSwt.c                                                    **
**                                                                           **
**  VERSION    : 2.0.0                                                       **
**                                                                           **
**  DATE       : 2021-11-09                                                  **
**                                                                           **
**  VARIANT    : NA                                                          **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : Implementation of Ethernet Switch driver functions         **
**                  required by ETH driver.                                  **
**                This file is for Evaluation Purpose Only                   **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "EthSwt_Eth.h"

#ifdef APP_SW
#if(APP_SW == TEST_APP)
  #include "Test_EthSwt.h"
#endif
#endif

void EthSwt_EthTxAdaptBufferLength(uint16* LengthPtr)
{
#ifdef APP_SW
#if(APP_SW == TEST_APP)
    TestEthSwt_EthTxAdaptBufferLength(LengthPtr);
#endif
#endif
}

Std_ReturnType EthSwt_EthTxPrepareFrame(uint8 CtrlIdx,
                  Eth_BufIdxType BufIdx, uint8** DataPtr, uint16* LengthPtr)
{
#if ((defined(APP_SW)) && (APP_SW == TEST_APP))
  return (TestEthSwt_EthTxPrepareFrame(CtrlIdx,BufIdx,DataPtr,LengthPtr));
#else
  return E_OK;
#endif
}

Std_ReturnType EthSwt_EthTxProcessFrame(uint8 CtrlIdx,
                  Eth_BufIdxType BufIdx, uint8** DataPtr, uint16* LengthPtr)
{
#if ((defined(APP_SW)) && (APP_SW == TEST_APP))
  return (TestEthSwt_EthSwt_EthTxProcessFrame(CtrlIdx,BufIdx,DataPtr,LengthPtr));
#else
  return E_OK;
#endif
}

Std_ReturnType EthSwt_EthTxFinishedIndication(uint8 CtrlIdx,
                                              Eth_BufIdxType BufIdx)
{
#if ((defined(APP_SW)) && (APP_SW == TEST_APP))
  return (TestEthSwt_EthTxFinishedIndication(CtrlIdx,BufIdx));
#else
  return E_OK;
#endif
}

Std_ReturnType EthSwt_EthRxProcessFrame(uint8 CtrlIdx,
                 Eth_BufIdxType BufIdx, uint8** DataPtr, uint16* LengthPtr,
                 boolean* IsMgmtFrameOnlyPtr)
{
#if ((defined(APP_SW)) && (APP_SW == TEST_APP))
  return (TestEthSwt_EthRxProcessFrame(CtrlIdx,BufIdx,DataPtr,LengthPtr,IsMgmtFrameOnlyPtr));
#else
  return E_OK;
#endif
}

Std_ReturnType EthSwt_EthRxFinishedIndication(uint8 CtrlIdx,
                                              Eth_BufIdxType BufIdx)
{
#if ((defined(APP_SW)) && (APP_SW == TEST_APP))
  return (TestEthSwt_EthRxFinishedIndication(CtrlIdx,BufIdx));
#else
  return E_OK;
#endif
}

