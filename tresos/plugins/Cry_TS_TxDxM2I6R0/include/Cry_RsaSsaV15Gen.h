/* --------{ EB Automotive C Source File }-------- */

#ifndef CRY_RSASSAV15GEN_H
#define CRY_RSASSAV15GEN_H

/* !LINKSTO CS_SECURE_CRY_0001_RsaSsaV15Gen,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

#include <Csm_Hash.h>

#include <Cry_LN.h>

#include <Cry_RsaSsaV15GenConfig.h>

#if (CRY_RSASSAV15_GEN_ENABLED == TRUE)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/*
 * CHECK: NOPARSE

<api API="FCT_EXTERN_USER">
  <name>Cry_RsaSsaV15GenStart</name>
  <synopsis>Start signature generation.</synopsis>
  <syntax>
FUNC(Csm_ReturnType, CRY_CODE) Cry_RsaSsaV15GenStart
(
   P2CONST(void, AUTOMATIC, CRY_APPL_DATA)     cfgPtr,
   P2CONST(Csm_AsymPublicKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
);
  </syntax>
  <description>
    This function requests the start of the RSASSA-PKCS1-v1_5 signature
    generation for the given configuration and key. The start is performed in
    Cry_RsaSsaV15GenMainFunction().
  </description>
  <parameter>
    cfgPtr=a pointer to the configuration for which the start of the signature
    generation should be requested.
  </parameter>
  <parameter>
    keyPtr=a pointer to the key which should be used in the signature
    generation.
  </parameter>
  <returns>
    CSM_E_OK=If the start was successfully requested.
  </returns>
  <returns>
    CSM_E_BUSY=If a service of the RSASSA-PKCS1-v1_5 signature generation is
    already running.
  </returns>
</api>

 * CHECK: PARSE
*/
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_RsaSsaV15GenStart
(
   P2CONST(void, AUTOMATIC, CRY_APPL_DATA)      cfgPtr,
   P2CONST(Csm_AsymPrivateKeyType, AUTOMATIC, CRY_APPL_DATA) keyPtr
);

/*
 * CHECK: NOPARSE

<api API="FCT_EXTERN_USER">
  <name>Cry_RsaSsaV15GenUpdate</name>
  <synopsis>Update signature generation.</synopsis>
  <syntax>
FUNC(Csm_ReturnType, CRY_CODE) Cry_RsaSsaV15GenUpdate
(
   P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
   uint32                                   dataLength
);
  </syntax>
  <description>
    This function requests the update of the RSASSA-PKCS1-v1_5 signature
    generation for the given data. The update is performed in
    Cry_RsaSsaV15GenMainFunction().
  </description>
  <parameter>
    dataPtr=a pointer to the start of an array which contains a part of the
    data for which the signature should be created.
  </parameter>
  <parameter>
    dataLength=the amount of bytes of data.
  </parameter>
  <returns>
    CSM_E_OK=If the update was successfully requested.
  </returns>
  <returns>
    CSM_E_BUSY=If the main function is processing a requested service at the
    moment.
  </returns>
  <returns>
    CSM_E_NOT_OK=If no signature generation has been started via
    Cry_RsaSsaV15GenStart(), yet.
  </returns>
</api>

 * CHECK: PARSE
*/
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_RsaSsaV15GenUpdate
(
   P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
   uint32                                   dataLength
);

/*
 * CHECK: NOPARSE

<api API="FCT_EXTERN_USER">
  <name>Cry_RsaSsaV15GenFinish</name>
  <synopsis>Finish signature generation.</synopsis>
  <syntax>
FUNC(Csm_ReturnType, CRY_CODE) Cry_RsaSsaV15GenFinish
(
   P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA)  resultPtr,
   P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) resultLengthPtr
);
  </syntax>
  <description>
    This function requests the finishing of the RSASSA-PKCS1-v1_5 signature
    generation and the storing of the signature in the given result buffer. The
    finishing is performed in Cry_RsaSsaV15GenMainFunction().
  </description>
  <parameter>
    resultPtr=a pointer to the start of a buffer where the generated
    signature should be stored.
  </parameter>
  <parameter>
    resultLengthPtr=a pointer to a variable which contains the maximal allowed
    length for the signature and where the actual length of the signature
    should be stored.
  </parameter>
  <returns>
    CSM_E_OK=If the finish was successfully requested.
  </returns>
  <returns>
    CSM_E_BUSY=If the main function is processing a requested service at the
    moment.
  </returns>
  <returns>
    CSM_E_NOT_OK=If no signature generation has been started via
    Cry_RsaSsaV15GenStart(), yet.
  </returns>
</api>

 * CHECK: PARSE
*/
extern FUNC(Csm_ReturnType, CRY_APPL_CODE) Cry_RsaSsaV15GenFinish
(
   P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA)  resultPtr,
   P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) resultLengthPtr
);

/*
 * CHECK: NOPARSE

<api API="FCT_EXTERN_USER">
  <name>Cry_RsaSsaV15GenMainFunction</name>
  <synopsis>Perform the RSASSA-PKCS1-v1_5 generation tasks.</synopsis>
  <syntax>
FUNC(void, CRY_CODE) Cry_RsaSsaV15GenMainFunction
(
   void
);
  </syntax>
  <description>
    This function performs the actual RSASSA-PKCS1-v1_5 signature generation
    tasks which have been requested by the service functions. When a task has
    finished, the function Csm_SignatureGenerateServiceCallbackNotification() is
    called to inform the CSM of the result. If the complete signature generation
    has finished, additionally the function
    Csm_SignatureGenerateServiceFinishNotification() is called.
  </description>
</api>

 * CHECK: PARSE
*/
extern FUNC(void, CRY_APPL_CODE) Cry_RsaSsaV15GenMainFunction
(
   void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CRY_RSASSAV15_GEN_ENABLED == TRUE) */

#endif /* CRY_RSASSAV15GEN_H */
