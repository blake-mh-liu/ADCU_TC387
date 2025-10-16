/* --------{ EB Automotive C Source File }-------- */



/*==[Includes]================================================================*/

#include <Cry_Common.h>
#include <Cry_CCM_Common.h>

#if ((CRY_CCM_ENC_ENABLED == STD_ON) || (CRY_CCM_DEC_ENABLED == STD_ON))

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

FUNC(void, CRY_CODE) Cry_CCMFormatHeader
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx,
 uint32                                           payloadLen
)
{
  uint8 i;

  for(i = 0U; i < sizeof(ctx->B0Mac); i++)
  {
    ctx->B0Mac[i] = 0x00U;
    ctx->B0Enc[i] = 0x00U;
  }

  ctx->B0Mac[0U] |= (uint8)((uint8)(((ctx->cfgPtr->M - 2U) / 2U) & 0x07U) << 3U);
  ctx->B0Mac[0U] |= ((ctx->cfgPtr->L - 1U) & 0x07U);

  ctx->B0Enc[0U] = ctx->cfgPtr->L - 1U;

  if (ctx->cfgPtr->aDataLen != 0U)
  {
    ctx->B0Mac[0U] += 0x40U;
  }

  for(i = 1U; i <= (15U - ctx->cfgPtr->L); i++)
  {
    ctx->B0Mac[i] = ctx->IV[i - 1U];
    ctx->B0Enc[i] = ctx->IV[i - 1U];
  }

  if (ctx->cfgPtr->L == 2U)
  {
    ctx->B0Mac[14U] = (uint8)((payloadLen & 0x0000FF00UL) >> 8U);
    ctx->B0Mac[15U] = (uint8)(payloadLen & 0x000000FFUL);
  }
  else if (ctx->cfgPtr->L == 3U)
  {
    ctx->B0Mac[13U] = (uint8)((payloadLen & 0x00FF0000UL) >> 16U);
    ctx->B0Mac[14U] = (uint8)((payloadLen & 0x0000FF00UL) >> 8U);
    ctx->B0Mac[15U] = (uint8)(payloadLen & 0x000000FFUL);
  }
  else
  {
    ctx->B0Mac[12U] = (uint8)((payloadLen & 0xFF000000UL) >> 24U);
    ctx->B0Mac[13U] = (uint8)((payloadLen & 0x00FF0000UL) >> 16U);
    ctx->B0Mac[14U] = (uint8)((payloadLen & 0x0000FF00UL) >> 8U);
    ctx->B0Mac[15U] = (uint8)(payloadLen & 0x000000FFUL);
  }

  Cry_CommonCopy(ctx->IV,
                 ctx->B0Enc,
                 sizeof(ctx->IV)
                );

  ctx->blockFilled = sizeof(ctx->block);

}

FUNC(void, CRY_CODE) Cry_CCMFormatAad
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx
)
{
  uint8 i;
  uint8 headerLen;
  uint32 len;
  uint32 aadOffset;

  ctx->aDataProcessed = FALSE;

  if (ctx->cfgPtr->aDataLen <= 0xFEFFU)
  {
    headerLen = 2U;

    /* 0 < l(a) < (2^16 - 2^8) */
    ctx->aad[1U] = (uint8)(ctx->cfgPtr->aDataLen & 0x000000FFUL);
    ctx->aad[0U] = (uint8)((ctx->cfgPtr->aDataLen & 0x0000FF00UL) >> 8U);
    len = (ctx->cfgPtr->aDataLen <= (uint8)(CRY_CCM_BLOCK_LEN - headerLen) ? ctx->cfgPtr->aDataLen :
                                                                 (uint8)(CRY_CCM_BLOCK_LEN - headerLen));
    Cry_CommonCopy(&ctx->aad[headerLen],
                   ctx->iputTextPtr,
                   len
                  );

    if (ctx->cfgPtr->aDataLen <= (uint8)(CRY_CCM_BLOCK_LEN - headerLen))
    {
      /* No offset for aData is necessary as aData can fit in one block. */
      aadOffset = ctx->cfgPtr->aDataLen;

      ctx->aDataProcessed = TRUE;

      /* Padding */
      for(i = (uint8)(ctx->cfgPtr->aDataLen + headerLen); i < CRY_CCM_BLOCK_LEN; i++)
      {
        ctx->aad[i] = 0x00U;
      }
    }
    else
    {
      /* Offset in the input data from which complete blocks can be processed. */
      aadOffset = len;
    }
  }
  else
  {
    headerLen = 6U;

    /* (2^16 - 2^8) <= l(a) < 2^32 */
    ctx->aad[0U] = 0xFFU;
    ctx->aad[1U] = 0xFEU;

    ctx->aad[2U] = (uint8)((ctx->cfgPtr->aDataLen & 0xFF000000UL) >> 24U);
    ctx->aad[3U] = (uint8)((ctx->cfgPtr->aDataLen & 0x00FF0000UL) >> 16U);
    ctx->aad[4U] = (uint8)((ctx->cfgPtr->aDataLen & 0x0000FF00UL) >> 8U);
    ctx->aad[5U] = (uint8)(ctx->cfgPtr->aDataLen & 0x000000FFUL);

    aadOffset = (uint32)((uint32)CRY_CCM_BLOCK_LEN - headerLen);

    Cry_CommonCopy(&ctx->aad[headerLen],
                   ctx->iputTextPtr,
                   aadOffset
                  );

  }

  /* Offset the input data pointer to the rest of aData or the payload */
  ctx->iputTextPtr     = &ctx->iputTextPtr[aadOffset];
  ctx->iputTextLength -= aadOffset;
  ctx->leftAData       = ctx->cfgPtr->aDataLen - aadOffset;

}

FUNC(Csm_ReturnType, CRY_CODE) Cry_CCMBlockEnc
(
    P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx,
  P2CONST(uint8,           AUTOMATIC, CRY_APPL_DATA) iputTextPtr,
          uint32                                     iputTextLength,
    P2VAR(uint8,           AUTOMATIC, CRY_APPL_DATA) oputTextPtr,
    P2VAR(uint32,          AUTOMATIC, CRY_APPL_DATA) oputTextLengthPtr
)
{
  Cry_CcmCryptBlockStateType blockEncStatePre = ctx->blockEncState;
  Csm_ReturnType locRetVal = CSM_E_NOT_OK;

  switch ( ctx->blockEncState )
  {
    case CRY_AES_ENC_S_REQ_SB_ST:
    {
      ctx->blockEncState = CRY_AES_ENC_S_WAIT_SB_ST;
      locRetVal = Csm_SymBlockEncryptStart(ctx->cfgPtr->symBlockCfgId,
                                           ctx->keyPtr
                                          );
    }
    break;

    case CRY_AES_ENC_S_REQ_SB_UPD:
    {
      ctx->blockEncState = CRY_AES_ENC_S_WAIT_SB_UPD;
      locRetVal = Csm_SymBlockEncryptUpdate(ctx->cfgPtr->symBlockCfgId,
                                            iputTextPtr,
                                            iputTextLength,
                                            oputTextPtr,
                                            oputTextLengthPtr
                                           );
    }
    break;

    case CRY_AES_ENC_S_REQ_SB_FIN:
    {
      ctx->blockEncState = CRY_AES_ENC_S_WAIT_SB_FIN;
      locRetVal = Csm_SymBlockEncryptFinish(ctx->cfgPtr->symBlockCfgId);
    }
    break;

    case CRY_AES_ENC_S_WAIT_SB_ST:
    case CRY_AES_ENC_S_WAIT_SB_UPD:
    case CRY_AES_ENC_S_WAIT_SB_FIN:
    {
      locRetVal = CSM_E_OK;
    }
    break;

    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
    case CRY_AES_ENC_S_UNINIT:
    default:
    {
      ctx->blockEncState = CRY_AES_ENC_S_UNINIT;
    }
    break;
    /* CHECK: PARSE */
  }

  if (locRetVal == CSM_E_BUSY)
  {
    ctx->blockEncState = blockEncStatePre;
  }
  else if (locRetVal == CSM_E_NOT_OK)
  {
    ctx->blockEncState = CRY_AES_ENC_S_UNINIT;
  }
  else
  {
    /* CSM_E_OK returned, nothing to be done. */
  }

  return locRetVal;
}

FUNC(Csm_ReturnType, CRY_CODE) Cry_CTRReqStart
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx
)
{
  Csm_ReturnType locRetVal;

  ctx->payloadState   = CRY_PLD_ENC_S_WAIT_SB_ST;

  ctx->iputTextPtr    = &ctx->initInDataPtr[ctx->cfgPtr->aDataLen];

  locRetVal = Csm_SymBlockEncryptStart(ctx->cfgPtr->symBlockCfgId,
                                       ctx->keyPtr
                                      );
  switch (locRetVal)
  {
    case CSM_E_OK:
      break;

    case CSM_E_BUSY:
    {
      ctx->payloadState = CRY_PLD_ENC_S_REQ_SB_ST;
    }
    break;

    default:
    {
      ctx->payloadState = CRY_PLD_ENC_S_UNINIT;
    }
    break;
  }

  return locRetVal;
}

FUNC(Csm_ReturnType, CRY_CODE) Cry_CTRReqUpdate
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx
)
{
  Csm_ReturnType locRetVal;
  uint32         blockLen = sizeof(ctx->block);

  ctx->payloadState = CRY_PLD_ENC_S_WAIT_SB_UPD;

  locRetVal = Csm_SymBlockEncryptUpdate(ctx->cfgPtr->symBlockCfgId,
                                        ctx->IV,
                                        sizeof(ctx->IV),
                                        ctx->encIV,
                                        &blockLen
                                       );

  switch (locRetVal)
  {
    case CSM_E_OK:
      break;

    case CSM_E_BUSY:
    {
      ctx->payloadState = CRY_PLD_ENC_S_REQ_SB_UPD;
    }
    break;

    default:
    {
      ctx->payloadState = CRY_PLD_ENC_S_UNINIT;
    }
    break;
  }

  return locRetVal;
}

FUNC(Csm_ReturnType, CRY_CODE) Cry_CTRReqFinish
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx
)
{
  Csm_ReturnType locRetVal;

  ctx->payloadState = CRY_PLD_ENC_S_WAIT_SB_FIN;

  locRetVal = Csm_SymBlockEncryptFinish(ctx->cfgPtr->symBlockCfgId);

  switch (locRetVal)
  {
    case CSM_E_OK:
      break;

    case CSM_E_BUSY:
    {
      ctx->payloadState = CRY_PLD_ENC_S_REQ_SB_FIN;
    }
    break;

    default:
    {
      ctx->payloadState = CRY_PLD_ENC_S_UNINIT;
    }
    break;
  }

  return locRetVal;
}

FUNC(Csm_ReturnType, CRY_CODE) Cry_CBCReqStart
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx
)
{
  Csm_ReturnType locRetVal;

  ctx->macState = CRY_CBC_ENC_S_WAIT_SB_ST;

  locRetVal = Csm_SymBlockEncryptStart(ctx->cfgPtr->symBlockCfgId,
                                       ctx->keyPtr
                                      );

  switch (locRetVal)
  {
    case CSM_E_OK:
      break;

    case CSM_E_BUSY:
    {
      ctx->macState = CRY_CBC_ENC_S_REQ_SB_ST;
    }
    break;

    default:
    {
      ctx->macState = CRY_CBC_ENC_S_UNINIT;
    }
    break;
  }

  return locRetVal;
}

FUNC(Csm_ReturnType, CRY_CODE) Cry_CBCReqUpdate
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx
)
{
  Csm_ReturnType locRetVal;

  uint32 blockLen = sizeof(ctx->block);

  ctx->macState = CRY_CBC_ENC_S_WAIT_SB_UPD;

  locRetVal = Csm_SymBlockEncryptUpdate(ctx->cfgPtr->symBlockCfgId,
                                        ctx->block,
                                        sizeof(ctx->block),
                                        ctx->lastCipherText,
                                        &blockLen
                                       );

  switch (locRetVal)
  {
    case CSM_E_OK:
      break;

    case CSM_E_BUSY:
    {
      ctx->macState = CRY_CBC_ENC_S_REQ_SB_UPD;
    }
    break;

    default:
    {
      ctx->macState = CRY_CBC_ENC_S_UNINIT;
    }
    break;
  }

  return locRetVal;
}

FUNC(Csm_ReturnType, CRY_CODE) Cry_CBCReqFinish
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx
)
{
  Csm_ReturnType locRetVal;

  ctx->macState = CRY_CBC_ENC_S_WAIT_SB_FIN;

  locRetVal = Csm_SymBlockEncryptFinish(ctx->cfgPtr->symBlockCfgId);

  switch (locRetVal)
  {
    case CSM_E_OK:
      break;

    case CSM_E_BUSY:
    {
      ctx->macState = CRY_CBC_ENC_S_REQ_SB_FIN;
    }
    break;

    default:
    {
      ctx->macState = CRY_CBC_ENC_S_UNINIT;
    }
    break;
  }

  return locRetVal;
}

FUNC(Csm_ReturnType, CRY_CODE) Cry_CBCEncAad
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx
)
{
  Csm_ReturnType locRetVal = CSM_E_NOT_OK;

  if(ctx->cfgPtr->aDataLen != 0U)
  {
    uint32 blockLen = sizeof(ctx->block);

    ctx->macState = CRY_CBC_ENC_S_WAIT_AAD_UPD;

    Cry_CommonXOR(ctx->aad,
                  ctx->lastCipherText,
                  sizeof(ctx->block)
                 );

    locRetVal = Csm_SymBlockEncryptUpdate(ctx->cfgPtr->symBlockCfgId,
                                          ctx->aad,
                                          sizeof(ctx->block),
                                          ctx->lastCipherText,
                                          &blockLen
                                         );

    switch (locRetVal)
    {
      case CSM_E_OK:
        break;

      case CSM_E_BUSY:
      {
        ctx->macState = CRY_CBC_ENC_S_ENC_AAD;
      }
      break;

      default:
      {
        ctx->macState = CRY_CBC_ENC_S_UNINIT;
      }
      break;
    }
  }
  else
  {
    ctx->macState = CRY_CBC_ENC_S_CP_FROM_INP;
    locRetVal     = CSM_E_OK;
  }

  return locRetVal;
}

FUNC(void, CRY_CODE) Cry_CTRCopyFromInput
(
 P2VAR(Cry_CCMCtxType,  AUTOMATIC, CRY_APPL_DATA) ctx
)
{
  /* If there is enough data for one block process it otherwise pad it. */
  if (ctx->iputTextLength >= sizeof(ctx->block))
  {
    Cry_CommonCopy(ctx->block,
                   ctx->iputTextPtr,
                   sizeof(ctx->block)
                  );

    ctx->iputTextPtr     = &ctx->iputTextPtr[sizeof(ctx->block)];
    ctx->iputTextLength -= sizeof(ctx->block);
    ctx->blockFilled     = sizeof(ctx->block);

    Cry_CCMInc(ctx->IV);

    /* context state administration */
    ctx->payloadState = CRY_PLD_ENC_S_REQ_SB_UPD;
  }
  else
  {
    if (ctx->iputTextLength == 0U)
    {
      ctx->payloadState = CRY_PLD_ENC_S_REQ_SB_FIN;
    }
    else
    {
      /* copy and do padding */
      Cry_CommonCopy(ctx->block,
                     ctx->iputTextPtr,
                     ctx->iputTextLength
                    );

      Cry_CCMInc(ctx->IV);

      ctx->blockFilled    = ctx->iputTextLength;
      ctx->iputTextLength = 0U;
      ctx->payloadState   = CRY_PLD_ENC_S_REQ_SB_UPD;
    }
  }
}

FUNC(void, CRY_CODE) Cry_CCMInc
(
  P2VAR(uint8,  AUTOMATIC, CRY_APPL_DATA) IV
)
{
  uint8 n;
  /* CHECK: NOPARSE */
  /* The counter(CTR) can't be represented on 16 bytes because it's value have to be equal to
   * 15-nonce
   */
  for( n = CRY_CCM_BLOCK_LEN; n != 0U; n-- )
  {
    ++IV[n - 1U];

    if (IV[n - 1U] != 0x00U)
    {
        break;
    }
  }
  /* CHECK: PARSE */
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Definition of functions with internal linkage]==========================*/

/*----------------------------------------------------------------------------*/
#else /* #if (CRY_CCM_ENC_ENABLED == STD_ON) */

typedef uint8 Cry_CcmCommon_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_CCM_ENC_ENABLED == STD_ON) #else */
