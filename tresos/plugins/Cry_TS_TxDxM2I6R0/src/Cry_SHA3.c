/* --------{ EB Automotive C Source File }-------- */

 /* MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 20.7 (required)
 *   "Expressions resulting from the expansion of macro parameters shall be
 *    enclosed in parentheses."
 *  Reason:
 *  The AUTOSAR compiler abstraction requires these definitions in this way
 *  and the arguments cannot be enclosed in parentheses due to C syntax.
 */

/* !LINKSTO EB_CRY_0004,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Cry_Common.h>
#include <Cry_SHA3.h>
#include <Cry_SHA3_Internal.h>

#include <Csm_Types.h>
#include <Csm_Hash.h>
#include <Csm.h>


#if (CRY_SHA3_ENABLED == STD_ON)

/*==[Variables with internal linkage]=========================================*/

#define CRY_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief SHA3 RunningContext
 **
 ** The context variable which is used to store the internal state of the
 ** SHA3 computation
 **/
static VAR(Cry_SHA3_ContextType, CRY_VAR) Cry_SHA3_Context =
{
    0U,
    {
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    },
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    CRY_SHA3_STATE_IDLE,
    ((uint16)0U),
    ((uint8)0U)
};

#define CRY_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO CS_SECURE_CRY_SHA3Start,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_SHA3Start
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) ConfigPtr
)
{
    Csm_ReturnType RetVal;
    P2CONST(Cry_SHAConfigType, AUTOMATIC, CRY_APPL_DATA) tmpCfgPtr;
    tmpCfgPtr = (P2CONST(Cry_SHAConfigType, AUTOMATIC, CRY_APPL_DATA))ConfigPtr;

    /* !LINKSTO EB_Cry_Immediate_Restart,1 */
#if (CRY_SHA3_IMMEDIATE_RESTART_ENABLED == STD_OFF)
    if ((CRY_SHA3_STATE_IDLE == Cry_SHA3_Context.ProcessState) ||
            ((CRY_SHA3_STATE_INITIALIZED == Cry_SHA3_Context.ProcessState) &&
                    (TRUE == tmpCfgPtr->SupportRestart)
                    /* !LINKSTO EB_Cry_Restart_SHA3,1 */
            )
       )
    {
        Cry_SHA3_Context.ConfigPtr = tmpCfgPtr;
        Cry_SHA3_Context.ProcessState = CRY_SHA3_STATE_INIT;
        RetVal = CSM_E_OK;
    }
    else if (CRY_SHA3_STATE_INITIALIZED == Cry_SHA3_Context.ProcessState)
    {
        RetVal = CSM_E_NOT_OK;
    }
    else
    {
        RetVal = CSM_E_BUSY;
    }
#else
     Cry_SHA3_Context.ConfigPtr    = tmpCfgPtr;
     Cry_SHA3_Context.ProcessState = CRY_SHA3_STATE_INIT;
     RetVal                        = CSM_E_OK;
#endif

    return RetVal;
}


/* !LINKSTO CS_SECURE_CRY_SHA3Update,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_SHA3Update
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
  uint32                                   dataLength
)
{
    Csm_ReturnType RetVal;

    switch (Cry_SHA3_Context.ProcessState)
    {
        case CRY_SHA3_STATE_IDLE:
            RetVal = CSM_E_NOT_OK;
            break;

        case CRY_SHA3_STATE_INITIALIZED:
            {
                if ((0 == dataLength) || ((NULL_PTR != dataPtr) && (0 != dataLength)))
                {
                    /* Store data into context */
                    Cry_SHA3_Context.InputDataPtr = dataPtr;
                    Cry_SHA3_Context.InputDataLength = dataLength;

                    /* Set state of the state machine to update */
                    Cry_SHA3_Context.ProcessState = CRY_SHA3_STATE_UPDATE;

                    RetVal = CSM_E_OK;
                }
                else
                {
                    RetVal = CSM_E_NOT_OK;
                }
            }
            break;

        default:
            {
              RetVal = CSM_E_BUSY;
              break;
            }
  }

  return RetVal;
}


/* !LINKSTO CS_SECURE_CRY_SHA3Finish,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_SHA3Finish
(
  P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA)  resultPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) resultLengthPtr,
  boolean                                 truncationAllowed
)
{
    Csm_ReturnType RetVal;

    switch (Cry_SHA3_Context.ProcessState)
    {
        case CRY_SHA3_STATE_IDLE:
            RetVal = CSM_E_NOT_OK;
            break;

        case CRY_SHA3_STATE_INITIALIZED:
            {
                if ((NULL_PTR == resultPtr) || (NULL_PTR == resultLengthPtr))
                {
                    Cry_SHA3_Context.ProcessState = CRY_SHA3_STATE_IDLE;
                    RetVal = CSM_E_NOT_OK;
                }
                else
                {
                    if (truncationAllowed ||
                            ((*resultLengthPtr) >= Cry_SHA3_Context.ConfigPtr->HashLength)
                       )
                    {
                        /* Store data into context */
                        Cry_SHA3_Context.ResultPtr = resultPtr;
                        Cry_SHA3_Context.ResultLengthPtr = resultLengthPtr;

                        /* Set state of the state machine to finish */
                        Cry_SHA3_Context.ProcessState = CRY_SHA3_STATE_FINISH;

                        RetVal = CSM_E_OK;
                    }
                    else
                    {
                        /* !LINKSTO CSM0661,1 */
                        RetVal = CSM_E_SMALL_BUFFER;
                    }
                }
            }
            break;

        default:
            {
              RetVal = CSM_E_BUSY;
              break;
            }
    }

    return RetVal;
}

 /* !LINKSTO  CS_SECURE_CRY_SHA3MainFunction, 1 */
FUNC(void, CRY_CODE) Cry_SHA3MainFunction
(
  void
)
{
    switch(Cry_SHA3_Context.ProcessState)
    {
        case CRY_SHA3_STATE_INIT:
            {
                uint32 i;

                /* Reset the state and the input offset */
                for (i = 0; i < (sizeof(Cry_SHA3_Context.HashState)/sizeof(uint32)); ++i)
                {
                    Cry_SHA3_Context.HashState[i] = 0;
                }
                Cry_SHA3_Context.HashStateInputOffset = 0;

                /*Calculate the rate */
                Cry_SHA3_Context.HashRateLength =
                    (uint16)(CRY_SHA3_STATE_SIZE_IN_BYTES -
                                (Cry_SHA3_Context.ConfigPtr->HashLength << 1)
                            );

                Cry_SHA3_Context.ProcessState = CRY_SHA3_STATE_INITIALIZED;

                /* !LINKSTO CSM0454, 1
                */
                Csm_HashCallbackNotification(CSM_E_OK);
            }
            break;

        case CRY_SHA3_STATE_UPDATE:
            {
                Cry_SHA3_Context.ProcessState = CRY_SHA3_STATE_INITIALIZED;

                Cry_SHA3_SpongeAbsorb(
                        Cry_SHA3_Context.InputDataPtr,
                        Cry_SHA3_Context.InputDataLength,
                        Cry_SHA3_Context.HashRateLength,
                        Cry_SHA3_Context.HashState,
                        &Cry_SHA3_Context.HashStateInputOffset
                        );

                /* !LINKSTO CSM0454, 1
                */
                Csm_HashCallbackNotification(CSM_E_OK);
            }
            break;

        case CRY_SHA3_STATE_FINISH:
            {
                Cry_SHA3_SpongeSqueeze(
                    Cry_SHA3_Context.HashState,
                    Cry_SHA3_Context.HashStateInputOffset,
                    Cry_SHA3_Context.HashRateLength,
                    ((uint16)Cry_SHA3_Context.ConfigPtr->HashLength),
                    Cry_SHA3_Context.ResultPtr,
                    Cry_SHA3_Context.ResultLengthPtr
                    );

                Cry_SHA3_Context.ProcessState = CRY_SHA3_STATE_IDLE;

                /* !LINKSTO CSM0454,1 */
                Csm_HashCallbackNotification(CSM_E_OK);

                Csm_HashServiceFinishNotification();
            }
            break;

        default:
            {
              break;
            }
    }
}

/* !LINKSTO EB_CRY_0015,1 */
/* Deviation MISRAC2012-1 */
FUNC(P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA), CRY_CODE) Cry_SHA3AlgorithmId
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) ConfigPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) AlgorithmIdLengthPtr
)
{
    *AlgorithmIdLengthPtr =
        ((P2CONST(Cry_SHAConfigType, AUTOMATIC, CRY_APPL_DATA))ConfigPtr)->AlgorithmIdLength;
    return ((P2CONST(Cry_SHAConfigType, AUTOMATIC, CRY_APPL_DATA))ConfigPtr)->AlgorithmId;
}


#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CRY_SHA3_ENABLED == STD_ON) #else */

