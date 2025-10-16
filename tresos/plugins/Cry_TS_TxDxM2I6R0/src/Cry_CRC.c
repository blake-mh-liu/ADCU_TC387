/* --------{ EB Automotive C Source File }-------- */

/*==================[includes]====================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm.h>
#include <Cry_CRC_Config.h>
#include <Cry_CRC.h>
#include <Cry_Common.h>

#if (CRY_CRC_ENABLED == TRUE)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/** \brief  CRC calculation implementation state machine states.
 **/
typedef enum
{
  CRY_CRC_STATE_UNINITIALIZED,
  CRY_CRC_STATE_START,
  CRY_CRC_STATE_INITIALIZED,
  CRY_CRC_STATE_UPDATE,
  CRY_CRC_STATE_CALCULATING,
  CRY_CRC_STATE_CALCULATED,
  CRY_CRC_STATE_FINISH,
  CRY_CRC_STATE_ERROR
}
Cry_CRC_StateType;

/*---[struct]-------------------------------------------------------------------------------------*/

/** \brief CRC calculation implementation context structure.
 **/
typedef struct
{
  uint32                                  crcPoly;         /* reflected user generator polynom */
  uint32                                  crcMBPC;         /* max bytes per cycle              */
  uint32                                  crcIputXor;      /* reflected user xor iput          */
  uint32                                  crcOputXor;      /* reflected user xor oput          */
  uint32                                  crcMask;
  uint32                                  crcStep;
  uint32                                  crcRslt;
  uint32                                  iputDataLength;
  uint32                                  oputFlagTruncate;
#if (CRY_CRC_SPEED_OPTIMIZED == STD_ON)
  uint32                                  crcCfgIdx;
#endif
#if (CRY_CRC_SPEED_OPTIMIZED == STD_OFF)
  CRY_CRC_BUFTYP                          crcTabl[256U];
#endif
  P2VAR(uint32,  TYPEDEF, CRY_APPL_DATA)  oputDataLengthPtr;
  P2CONST(uint8, TYPEDEF, CRY_APPL_DATA)  iputDataPtr;
  P2VAR(uint8,   TYPEDEF, CRY_APPL_DATA)  oputDataPtr;
  Cry_CRC_StateType                       ctxState;
  Csm_ReturnType                          ctxError;
  Cry_CRC_Type                            crcType;
#if (CRY_CRC_SPEED_OPTIMIZED == STD_OFF)
  boolean                                 flgTabl;
#endif
  boolean                                 crcIputReflect;  /* inverted user iput reflect flag  */
  boolean                                 crcOputReflect;  /* inverted user oput reflect flag  */

}
Cry_CRC_ContextType;


/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief  Reverse the bit ordering of 'valuSize' lower bits in a single 'uint32' variable
 **        'valuPtr' points to.
 **/
FUNC(void, CRY_CODE) Cry_CRCReflect
(
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) valuPtr,
  VAR(uint32, AUTOMATIC               )   valuSize
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

#define CRY_START_SEC_CONST_8
#include <MemMap.h>

/** \brief  Lookup-Table used by Cry_CRCReflect()
 **/
STATIC CONST(uint8, CRY_CONST) Cry_CRC_ReflectNibble[16] =
{
  0x00, 0x08, 0x04, 0x0C,
  0x02, 0x0A, 0x06, 0x0E,
  0x01, 0x09, 0x05, 0x0D,
  0x03, 0x0B, 0x07, 0x0F
};

#define CRY_STOP_SEC_CONST_8
#include <MemMap.h>

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief  The context variable which is used to store the internal state of the CRC calculation.
 **/
STATIC VAR(Cry_CRC_ContextType, CRY_VAR) Cry_CRCContext;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[external function definitions]===============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_CRCStart]-------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/* !LINKSTO EB_CRY_0011,1, CS_SECURE_CRY_0160,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_CRCStart
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  P2CONST(Cry_CRC_ConfigType, AUTOMATIC, CRY_APPL_DATA) locCfgPtr;
  uint32                                                locPoly;
  Csm_ReturnType                                        locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locCfgPtr = (P2CONST(Cry_CRC_ConfigType, AUTOMATIC, CRY_APPL_DATA)) cfgPtr;
  locRetVal = CSM_E_OK;

  /* reflect generator polynom given by user for internal use */
  locPoly   = (uint32) locCfgPtr->polyCrc;
  Cry_CRCReflect( (uint32*) &locPoly,(uint32)(locCfgPtr->typeCrc) * 8U);

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ( (Cry_CRCContext.ctxState == CRY_CRC_STATE_UNINITIALIZED) ||
       (Cry_CRCContext.ctxState == CRY_CRC_STATE_ERROR        )    )
  {
    /* context state administration */
    Cry_CRCContext.ctxState = CRY_CRC_STATE_START;

    /* initializations */
    switch ( locCfgPtr->typeCrc )
    {
      case CRY_CRC_8 : { Cry_CRCContext.crcMask = 0x000000FFU; } break;
      case CRY_CRC_16: { Cry_CRCContext.crcMask = 0x0000FFFFU; } break;
      case CRY_CRC_32: { Cry_CRCContext.crcMask = 0xFFFFFFFFU; } break;
      /* CHECK: NOPARSE */
      /* Caution: this 'default' is required by MISRA-C:2004 */
      default :                                      { break; }
      /* CHECK: PARSE */
    }
    Cry_CRCContext.crcRslt = 0U;
#if (CRY_CRC_SPEED_OPTIMIZED == STD_OFF)
    Cry_CRCContext.flgTabl = FALSE;

    /* check for necessity of recalculating Cry_CRCContext.crcTabl */

    if ( (Cry_CRCContext.crcType != locCfgPtr->typeCrc) ||
         (Cry_CRCContext.crcPoly != (uint32) locPoly           )    )
    {
      Cry_CRCContext.flgTabl = TRUE;
    }
#endif

    /* get argument parameters into context (note forwarded user input and reflected internal use)
     */
#if (CRY_CRC_SPEED_OPTIMIZED == STD_ON)
    Cry_CRCContext.crcCfgIdx      =  locCfgPtr->nodeIndex;
#endif
    Cry_CRCContext.crcType        =  locCfgPtr->typeCrc;
    Cry_CRCContext.crcPoly        = (uint32 ) locPoly;
    Cry_CRCContext.crcMBPC        = (uint32 ) locCfgPtr->mbpcCrc;

    Cry_CRCContext.crcIputXor     = (uint32 ) locCfgPtr->iputXor;
    Cry_CRCContext.crcOputXor     = (uint32 ) locCfgPtr->oputXor;

    Cry_CRCReflect( (uint32*) &Cry_CRCContext.crcIputXor, (uint32) (locCfgPtr->typeCrc) * 8U );
    Cry_CRCReflect( (uint32*) &Cry_CRCContext.crcOputXor, (uint32) (locCfgPtr->typeCrc) * 8U );

    Cry_CRCContext.crcIputReflect = ! (boolean) locCfgPtr->iputReflect;
    Cry_CRCContext.crcOputReflect = ! (boolean) locCfgPtr->oputReflect;
    Cry_CRCContext.ctxError       = CSM_E_OK;
  }
  else
  {
    locRetVal = CSM_E_NOT_OK;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_CRCUpdate]------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/* !LINKSTO EB_CRY_0012,1, CS_SECURE_CRY_0161,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_CRCUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) dataPtr,
      VAR(uint32, AUTOMATIC               ) dataLength
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Csm_ReturnType      locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = CSM_E_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ( (Cry_CRCContext.ctxState == CRY_CRC_STATE_INITIALIZED) ||
       (Cry_CRCContext.ctxState == CRY_CRC_STATE_CALCULATED )    )
  {
    /* check input arguments */

    if ( (dataPtr == NULL_PTR) || (dataLength == 0) )
    {
      /* context state administration */
      Cry_CRCContext.ctxState = CRY_CRC_STATE_CALCULATED;
    }
    /* if input arguments are ok edit context */
    else
    {
      /* initializations */
      Cry_CRCContext.crcStep = 0U;

      /* get argument parameters into context */
      Cry_CRCContext.iputDataPtr    = dataPtr;
      Cry_CRCContext.iputDataLength = dataLength;

      /* context state administration */
      Cry_CRCContext.ctxState = CRY_CRC_STATE_UPDATE;
    }
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_CRCFinish]------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/* !LINKSTO EB_CRY_0013,1, CS_SECURE_CRY_0162,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_CRCFinish
(
  P2VAR(uint8,   AUTOMATIC, CRY_APPL_DATA) resultPtr,
  P2VAR(uint32,  AUTOMATIC, CRY_APPL_DATA) resultLengthPtr,
    VAR(boolean, AUTOMATIC               ) truncationIsAllowed
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Csm_ReturnType      locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  locRetVal = CSM_E_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  if ( Cry_CRCContext.ctxState == CRY_CRC_STATE_CALCULATED )
  {

    /* check input arguments */
    if ( (*resultLengthPtr     <  (uint32) Cry_CRCContext.crcType) &&
         ( truncationIsAllowed == FALSE                 )    )
    {
      locRetVal = CSM_E_SMALL_BUFFER;
    }
    /* if input arguments are ok edit context */
    if ( locRetVal == CSM_E_OK )
    {
      /* get argument parameters into context */
      Cry_CRCContext.oputDataPtr       = resultPtr;
      Cry_CRCContext.oputDataLengthPtr = resultLengthPtr;
      Cry_CRCContext.oputFlagTruncate  = truncationIsAllowed;

      /* context state administration */
      Cry_CRCContext.ctxState = CRY_CRC_STATE_FINISH;
    }
  }
  else
  {
    locRetVal = CSM_E_BUSY;
  }

  /* ~~~ return ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  return locRetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_CRCMainFunction]------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/* !LINKSTO EB_CRY_0016,1, CS_SECURE_CRY_0163,1 */
FUNC(void, CRY_CODE) Cry_CRCMainFunction
(
  void
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  /* --- */

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  switch ( Cry_CRCContext.ctxState )
  {
    /* *** Cry_CRCMainFunction > CRY_CRC_STATE_UNINITIALIZED ************************************ */
    case CRY_CRC_STATE_UNINITIALIZED:
    break;

    /* *** Cry_CRCMainFunction > CRY_CRC_STATE_START ******************************************** */
    case CRY_CRC_STATE_START:
    {
      /* local variables */
#if (CRY_CRC_SPEED_OPTIMIZED == STD_OFF)
      uint32     locLoopByt = 0U;
      uint32     locLoopBit = 0U;
      uint32     locTempCrc = 0U;
#endif
      /* context state administration */
      Cry_CRCContext.ctxState = CRY_CRC_STATE_INITIALIZED;

      /* init crc table */
#if (CRY_CRC_SPEED_OPTIMIZED == STD_OFF)
      if ( Cry_CRCContext.flgTabl == TRUE )
      {
        Cry_CRCContext.crcTabl[0] = 0U;
        for ( locLoopByt = 1U; locLoopByt < 256U; locLoopByt++ )
        {
          locTempCrc = locLoopByt;
          for ( locLoopBit = 0U; locLoopBit < 8U; locLoopBit++ )
          {
            locTempCrc = ((locTempCrc & 1U) == 1U)
              ? ( (locTempCrc >> 1U) ^ Cry_CRCContext.crcPoly )
              :   (locTempCrc >> 1U);
          }
          Cry_CRCContext.crcTabl[locLoopByt] = locTempCrc;
        }
      }
#endif
      /* init some more context variables */
      Cry_CRCContext.crcRslt = (0U ^ Cry_CRCContext.crcIputXor);

      /* callback */
      Csm_ChecksumCallbackNotification(Cry_CRCContext.ctxError);

    }
    break;

    /* *** Cry_CRCMainFunction > CRY_CRC_STATE_INITIALIZED ************************************** */
    case CRY_CRC_STATE_INITIALIZED:
    break;

    /* *** Cry_CRCMainFunction > CRY_CRC_STATE_UPDATE ******************************************* */
    case CRY_CRC_STATE_UPDATE:
    {
        /* context state administration */
        Cry_CRCContext.ctxState = CRY_CRC_STATE_CALCULATING;
    }
    break;

    /* *** Cry_CRCMainFunction > CRY_CRC_STATE_CALCULATING ************************************** */
    case CRY_CRC_STATE_CALCULATING:
    {
      /* local variables */
      uint32                 locLoopDat = 0U;
      uint32                 locTempByt = 0U;
#if (CRY_CRC_SPEED_OPTIMIZED == STD_ON)
      uint32                 lutID = 0U;
#endif

      /* main turn */

      for ( locLoopDat = Cry_CRCContext.crcStep;
              (locLoopDat <  Cry_CRCContext.iputDataLength                  ) &&
              (locLoopDat < (Cry_CRCContext.crcStep + Cry_CRCContext.crcMBPC)    );
              locLoopDat++
          )
        {
          locTempByt = Cry_CRCContext.iputDataPtr[locLoopDat];

          if ( Cry_CRCContext.crcIputReflect == TRUE )
          {
            Cry_CRCReflect( (uint32*) &locTempByt, 8U );
          }
#if (CRY_CRC_SPEED_OPTIMIZED == STD_OFF)
          Cry_CRCContext.crcRslt =
            (
              ( Cry_CRCContext.crcRslt >> 8U ) ^ Cry_CRCContext.crcTabl
                [
                  ( Cry_CRCContext.crcRslt ^ locTempByt ) & 0xFFU
                ]
            )
            & Cry_CRCContext.crcMask;
#else
            lutID = Cry_CRC_LUT_idx[Csm_CRC_LUT_idx[Cry_CFG_idx[Cry_CRCContext.crcCfgIdx]]];
            Cry_CRCContext.crcRslt =
            (
              ( Cry_CRCContext.crcRslt >> 8U ) ^ Cry_CRC_LUT[lutID]
                [
                  ( Cry_CRCContext.crcRslt ^ locTempByt ) & 0xFFU
                ]
            )
            & Cry_CRCContext.crcMask;
#endif
        }
        Cry_CRCContext.crcStep = locLoopDat;

      /* final turn */
      if ( Cry_CRCContext.crcStep == Cry_CRCContext.iputDataLength )
      {
        /* context state administration */
        Cry_CRCContext.ctxState = CRY_CRC_STATE_CALCULATED;

        /* callback */
        Csm_ChecksumCallbackNotification(Cry_CRCContext.ctxError);
      }

    }
    break;

    /* *** Cry_CRCMainFunction > CRY_CRC_STATE_CALCULATED *************************************** */
    case CRY_CRC_STATE_CALCULATED:
    break;

    /* *** Cry_CRCMainFunction > CRY_CRC_STATE_FINISH ******************************************* */
    case CRY_CRC_STATE_FINISH:
    {
      /* local variables */
      uint32      locLen = (uint32) Cry_CRCContext.crcType;
      uint8       locLoop;

      /* context state administration */
      Cry_CRCContext.ctxState = CRY_CRC_STATE_UNINITIALIZED;

      /* correcting crcRslt */
      if ( Cry_CRCContext.crcOputReflect == TRUE )
      {
        Cry_CRCReflect( (uint32*) &Cry_CRCContext.crcRslt, (uint32) Cry_CRCContext.crcType * 8U );
      }
      Cry_CRCContext.crcRslt ^= Cry_CRCContext.crcOputXor;

      /* correcting local len information if necessary */
      if ( ( Cry_CRCContext.oputFlagTruncate  == TRUE                  ) &&
           (*Cry_CRCContext.oputDataLengthPtr <  (uint32 ) Cry_CRCContext.crcType)    )
      {
        locLen = *Cry_CRCContext.oputDataLengthPtr;
      }

      /* copy to oput variables */
      for ( locLoop = 0U; locLoop < locLen; locLoop++ )
      {
        Cry_CRCContext.oputDataPtr[locLoop] =
          (uint8) (Cry_CRCContext.crcRslt >> ((locLen - locLoop - 1U) * 8U)) & 0xFFU;
      }
      *Cry_CRCContext.oputDataLengthPtr = locLen;

      /* callback */
      Csm_ChecksumCallbackNotification(Cry_CRCContext.ctxError);
      Csm_ChecksumServiceFinishNotification();
    }
    break;
     /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. */

    /* *** Cry_CRCMainFunction > CRY_CRC_STATE_ERROR ******************************************** */
    case CRY_CRC_STATE_ERROR:
    break;

    /* *** Cry_CRCMainFunction > DEFAULT ******************************************************** */
    default:
    {
      /* context state administration */
      Cry_CRCContext.ctxState = CRY_CRC_STATE_ERROR;

      Cry_CRCContext.ctxError = 0xFFU;
    }
    break;
    /* CHECK: PARSE */
  }
}

/*==================[internal function definitions]===============================================*/

/*------------------------------------------------------------------------------------------------*/
/*---[Cry_CRCReflect]-----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(void, CRY_CODE) Cry_CRCReflect
(
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) valuPtr,
    VAR(uint32, AUTOMATIC               ) valuSize
)
{
  /* local variables */
  uint32 locTempVal = 0x00U;
  uint8  locLoopBit = 0x00U;

  /* reflect bit order of 'valuSize' lower bits */
  for ( locLoopBit = 0U; locLoopBit < valuSize; locLoopBit += 4U )
  {
    locTempVal  |= (uint32)((uint32)Cry_CRC_ReflectNibble[*valuPtr & 0x0FU] <<
                            (uint32)(valuSize - locLoopBit - 4U)
                           );
    *valuPtr   >>= 0x04U;
  }
  *valuPtr = locTempVal;
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#else /* #if (CRY_CRC_ENABLED == TRUE) */

/* dummy definition to prevent empty translation unit */
typedef void Cry_CRC_PreventEmptyTranslationUnit_t;

#endif /* #if (CRY_CRC_ENABLED == TRUE) #else */

/*==================[end of file]=================================================================*/
