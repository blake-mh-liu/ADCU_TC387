/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0001,1, CS_SECURE_CRY_0001_SSGGenerate,1 */

#ifndef CRY_SSGGENERATE_H
#define CRY_SSGGENERATE_H

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm.h>                    /* !LINKSTO EB_CRY_0002,1 */
#include <Cry_SSGGenerateConfig.h>  /* !LINKSTO EB_CRY_0002,1 */

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#if (CRY_SSGGENERATE_ENABLED == STD_ON)

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief  Generate pseudo random bytes
 **
 ** This function requests the generation of pseudo random bytes. The byte
 ** generation is performed in Cry_SSGMainFunction()
 **
 ** \param[in] cfgPtr  A pointer to the configuration which should be used in the
 ** pseudo random byte generation. This configuration contains, among others, a
 ** pointer to the state which should be used for the generation.
 **
 ** \param[out] resultPtr A pointer to the start of a buffer where the generated
 ** pseudo random bytes should be stored
 **
 ** \param[out] resultLength Holds the amount of bytes which should be generated
 **
 ** \returns Generation operation state
 **
 ** \retval CSM_E_OK If the byte generation was successfully requested
 **
 ** \retval CSM_E_BUSY If another service of the SSG is already running
 **
 **/
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_SSGGenerate
(
  P2CONST(void,  AUTOMATIC, CRY_APPL_DATA) cfgPtr,
    P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) resultPtr,
          uint32                           resultLength
);

/**
 ** \brief This function performs the actual SSG tasks which have been requested by
 ** the service functions. When a task has finished, the function
 ** Csm_RandomCallbackNotification() is called to inform the CSM of the result.
 **/
extern FUNC(void, CRY_CODE) Cry_SSGGenerateMainFunction
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CRY_SSGGENERATE_ENABLED == STD_ON) */

#endif
