/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0001,1, CS_SECURE_CRY_0001_SSGSeed,1 */

#ifndef CRY_SSGSEED_H
#define CRY_SSGSEED_H

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm.h>                /* !LINKSTO EB_CRY_0002,1 */
#include <Cry_SSGSeedConfig.h>  /* !LINKSTO EB_CRY_0002,1 */

#if(CRY_SSGSEED_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/**
 ** \brief This function requests the initialization of the SSG state which has been
 **  given with the passed configuration pointer. The initialization is
 ** performed in Cry_SSGMainFunction().
 **
 ** \param[in] cfgPtr Pointer to the configuration which should be used in the
 **  state initialization. This configuration contains, among others, a pointer
 **  to the state which should be initialized.
 **
 ** \return Request result
 **
 ** \retval   CSM_E_OK      If the start was successfully requested.
 ** \retval   CSM_E_BUSY    If a service of SSGSeed is already running.
 **/
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_SSGSeedStart
(
   P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr
);

/**
 ** \brief This function requests the seeding of the SSG state which has been
 ** given with the passed configuration pointer. The seeding is
 ** performed in Cry_SSGMainFunction().
 **
 ** \param[in] seedPtr Pointer to the start of an array which contains the seed.
 ** \param[in] seedLength The length of the seed in byte
 ** \return Rquest result
 **
 ** \retval   CSM_E_OK      If the update was successfully requested.
 ** \retval   CSM_E_NOT_OK  If there was an error
 ** \retval   CSM_E_BUSY    If the SSGSeed Service computation is
 **                         already running.
 **/
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_SSGSeedUpdate
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) seedPtr,
          uint32                           seedLength
);

/**
 ** \brief This function requests the finishing of the seeding of the SSG.
 ** The finishing of the seeding is performed in Cry_SSGMainFunction()
 **
 ** \return Request result
 **
 ** \retval   CSM_E_OK      If the finish was successfully requested.
 ** \retval   CSM_E_NOT_OK  If there was an error
 ** \retval   CSM_E_BUSY    If the SSGSeed Service computation is
 **                         already running.
 **/
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_SSGSeedFinish
(
  void
);

/**
 ** \brief This function performs the actual SSG tasks which have been requested by
 ** the service functions. When a task has finished, the function
 ** Csm_RandomCallbackNotification() is called to inform the CSM of the result.
 **/
extern FUNC(void, CRY_APPL_CODE) Cry_SSGSeedMainFunction
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CRY_SSGSEED_ENABLED == STD_ON) */

#endif
