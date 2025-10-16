/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BM layer                                        */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BM_Cbk.c                        */
/*%%  |                             |  %%  \brief BM layer include plugin file   */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.20.0 BL3                */
/*%%  |   &       &    &            |  %%  Variant: OsekCore                  */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files                                                                */

#include "EB_Prj.h"

/*                                                                               */
/*===============================================================================*/




/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/

/*============================ PRIVATE DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Private Constants                                                           */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

/*                                                                               */
/*===============================================================================*/


/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */
/** \brief Callback performing initialization of DualBankInit
 **
 ** Callback is called: at Bootloader start i.e BM_InitialBootStartUp/BM_Manage
 **
 ** Callback shall implement: to initialize all the needed data for the dual memory
 **                      banks usage
 **
 **/
[!IF "as:modconf('BM')/General/Dual_Memory_Bank_Used = 'true'"!]
/*--------------------------{BM_CustomDualBankInit}---------------------------*/
void BM_CustomDualBankInit (void)
{

}
/*-----------------------{end BM_CustomDualBankInit}--------------------------*/
[!IF "as:modconf('BM')/General/Trial_period = 'true'"!]
/*--------------------------{BM_CustomPerformRollBack}---------------------------*/
extern void BM_CustomPerformRollBack (void)
{

}
/*-----------------------{end BM_CustomPerformRollBack}--------------------------*/

/*--------------------------{BM_CustomTrialPeriodCheck}---------------------------*/
extern tBMBoolean BM_CustomTrialPeriodCheck (void)
{
    return BM_TRUE;
}
/*-----------------------{end BM_CustomTrialPeriodCheck}--------------------------*/
[!ENDIF!]
[!ENDIF!]


[!IF "as:modconf('BM')/General/Boot_Manager_Variant = "Initial Boot Manager""!]

/*----------------------------{BM_CheckProgRequest}----------------------------------*/
extern tBMBoolean BM_CheckProgRequest(void)
{
    return BM_TRUE;
}
/*----------------------------{end BM_CheckProgRequest}------------------------------*/

/*----------------------------{BM_CustomCheckValidAppl}----------------------------------*/
extern tBMBoolean BM_CustomCheckValidAppl(void)
{
    return BM_TRUE;
}
/*----------------------------{end BM_CustomCheckValidAppl}------------------------------*/

/*----------------------------{BM_CustomCheckValidBLU}----------------------------------*/
extern tBMBoolean BM_CustomCheckValidBLU(void)
{
    return BM_TRUE;
}
/*----------------------------{end BM_CustomCheckValidBLU}------------------------------*/

/*----------------------------{BM_CustomCheckValidBL}----------------------------------*/
extern tBMBoolean BM_CustomCheckValidBL(void)
{
    return BM_TRUE;
}
/*----------------------------{end BM_CustomCheckValidBL}------------------------------*/

/*----------------------------{BM_JumpToApplication}----------------------------------*/
extern void BM_JumpToApplication(void)
{

}
/*----------------------------{end BM_JumpToApplication}------------------------------*/

/*----------------------------{BM_JumpToBLU}----------------------------------*/
extern void BM_JumpToBLU(void)
{

}
/*----------------------------{end BM_JumpToBLU}------------------------------*/

/*----------------------------{BM_JumpToBL}----------------------------------*/
extern void BM_JumpToBL(void)
{

}
/*----------------------------{end BM_JumpToBL}------------------------------*/
[!IF "General/Test_Application = 'true'"!]
 /*---------------------------{BM_CustomAllowTestApplExe}----------------------------*/
void BM_CustomAllowTestApplExe(void)
{

}
/*-----------------------{end BM_CustomAllowTestApplExe}-------------------------*/
[!ENDIF!]

[!IF "as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure'"!]
/*----------------------------------{BM_CustomSetInvalidBlu}--------------------------------*/
void BM_CustomSetInvalidBlu(void)
{

}
/*----------------------------------{end BM_CustomSetInvalidBlu}----------------------------*/
[!ENDIF!]
[!ENDIF!]

void BM_DisableECCCheck(void)
{

}

void BM_EnableECCCheck(void)
{

}

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated')
    or (as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure')"!]
/*---------------------------{BM_CustomBckOperation}----------------------------*/
void BM_CustomBckOperation (void)
{

}
/*------------------------{end BM_CustomBckOperation}---------------------------*/
  [!IF "(as:modconf('BM')/Security/SecureBoot/BMSecureBootWithHsm = 'true')"!]
 /*---------------------------{BM_CustomHsmVerifyMac}----------------------------*/
tBMHsmJobResult BM_CustomHsmVerifyMac(u16 uwBlockId)
{
    OSC_PARAM_UNUSED(uwBlockId);
    return BM_HSM_JOB_OK;
}
/*------------------------{end BM_CustomHsmVerifyMac}---------------------------*/
  [!ENDIF!]
[!ENDIF!]

[!IF "as:modconf('BM')/General/Boot_Manager_Variant = "Boot Manager""!]
/*----------------------------{BM_HardwareInit}----------------------------------*/
void BM_HardwareInit (void)
{

}
/*----------------------------{end BM_HardwareInit}------------------------------*/

/*----------------------------{BM_SoftwareInit}----------------------------------*/
void BM_SoftwareInit(void)
{

}
/*----------------------------{end BM_SoftwareInit}-----------------------------*/

[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true'"!]
/*-----------------------------{BM_GetTesterAddress}----------------------------*/
void BM_GetTesterAddress (u16 *ubTesterAddress)
{
    OSC_PARAM_UNUSED(ubTesterAddress);
}
/*-------------------------{end BM_GetTesterAddress}----------------------------*/
[!ENDIF!]

[!IF "(as:modconf('BM')/Security/SecureBoot/BMSecureBootWithHsm = 'false')"!]
[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated')"!]
/*------------------{BM_CustomGetComputedApplicationChecksum}-------------------*/
void BM_CustomGetComputedApplicationChecksum (u8 * pubChecksum,  u16 uwBlockIdentifier)
{
    OSC_PARAM_UNUSED(pubChecksum);
    OSC_PARAM_UNUSED(uwBlockIdentifier);
}
/*----------------{end BM_CustomGetComputedApplicationChecksum}-----------------*/
[!ENDIF!]
[!ENDIF!]

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated')
    or (as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure')"!]
[!IF "(as:modconf('BM')/Security/SecureBoot/BMSecureBootWithHsm = 'false')"!]
/*----------------------{BM_CustomGetExpectedApplicationChecksum}-----------------------*/
void BM_CustomGetExpectedApplicationChecksum (u8 * pubChecksum, u16 uwBlockIdentifier)
{
    OSC_PARAM_UNUSED(pubChecksum);
    OSC_PARAM_UNUSED(uwBlockIdentifier);
}
/*-------------------{end BM_CustomGetExpectedApplicationChecksum}----------------------*/
[!ENDIF!]
/*--------------------------{BM_CustomSetInvalidAppli}--------------------------*/
void BM_CustomSetInvalidAppli (u16 uwBlockIdentifier)
{
    OSC_PARAM_UNUSED(uwBlockIdentifier);
}
/*-----------------------{end BM_CustomSetInvalidAppli}-------------------------*/
[!ENDIF!]

[!IF "((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated')
    or (as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure'))
    and (as:modconf('BM')/Security/SecureBoot/BOOT_VERIFICATION = 'ON')"!]
/*--------------------------{BM_CustomSetInvalidBoot}---------------------------*/
void BM_CustomSetInvalidBoot (void)
{

}
/*-----------------------{end BM_CustomSetInvalidBoot}--------------------------*/
[!ENDIF!]

[!IF "General/BM_TIMEOUT_CHECK = 'true'"!]
/*---------------------------{BM_CustomIsNormalStartup}----------------------------*/
tBMBoolean BM_CustomIsNormalStartup (void)
{
    return(BM_TRUE);
}
/*-----------------------{end BM_CustomIsNormalStartup}-------------------------*/
[!ENDIF!]
[!IF "(as:modconf('BM')/Security/SecureBoot/BMSecureBootWithHsm = 'false')"!]
 [!VAR "ASR_430_MACPATH" = "0"!]

  [!IF "node:exists(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId)"!]
    [!IF "node:exists(node:ref(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId)/CsmJobPrimitiveRef)"!]
      [!IF "node:exists(node:ref(node:ref(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId)/CsmJobPrimitiveRef)/CsmMacVerify)"!]
 [!VAR "ASR_430_MACPATH" = "1"!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!]

 [!IF "((not(node:exists(as:modconf('CryIf')))) and (contains(as:modconf('BM')/Security/BMCsmChecksumConfigId, '/Csm/Csm/CsmMacVerify/') =  'true'))
     or ((node:exists(as:modconf('CryIf'))) and  "$ASR_430_MACPATH = 1")"!]


const u32 m_ulMacKeyKength = 0x00000010UL;
const u8 m_aubKeyData[16U] =
{
    0xEBU, 0xEBU, 0xEBU, 0xEBU,
    0xEBU, 0xEBU, 0xEBU, 0xEBU,
    0xEBU, 0xEBU, 0xEBU, 0xEBU,
    0xEBU, 0xEBU, 0xEBU, 0xEBU
};
/*---------------------------{BM_CustomGetMacKey}----------------------------*/
void BM_CustomGetMacKey(const u8** paubKeyData, u32* pulKeyLength)
{
    *paubKeyData   = m_aubKeyData;
    *pulKeyLength  = m_ulMacKeyKength;
}
/*-----------------------{end BM_CustomGetMacKey}-------------------------*/
  [!ENDIF!]
[!ENDIF!]
[!ENDIF!]
