/*********************************************************************************/
/*                                                                               */
/*                                BOOT Layers                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                                 PROG configuration                            */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file PROG_Cbk.h                      */
/*%%  |                             |  %%  \brief PROG layer include plugin file */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.74.0 BL3              */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*********************************************************************************/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*********************************************************************************/

[!AUTOSPACING!]


#ifndef PROG_CBK_H
#define PROG_CBK_H

#if (PROG_CRY_PRESENT == STD_ON)
#include "Csm.h"
#endif /* (PROG_CRY_PRESENT == STD_ON) */
#if (PROG_CSM_DECRYPTION_ENABLE == STD_ON)
#include "PROG_Encrypt.h"
#endif /* (PROG_CSM_DECRYPTION_ENABLE == STD_ON) */

#if ((PROG_IMPL_VARIANT == PROG_IMPL_4) || (PROG_IMPL_VARIANT == PROG_IMPL_5))
extern tProgBoolean m_aubBlockDownloadStatus[PROG_BLOCK_NB]; /* status of the logical download block downloded */
#endif /*((PROG_IMPL_VARIANT == PROG_IMPL_4)) */

/*------------------------------{PROG_SwitchApplicationModeInd}-----------------*/
extern void PROG_SwitchApplicationModeInd(void);

/*--------------------------{PROG_DisableECCCheck}------------------------------*/
extern void PROG_DisableECCCheck(void);

/*--------------------------{PROG_EnableECCCheck}-------------------------------*/
extern void PROG_EnableECCCheck(void);

[!IF "Decryption/Enable_Decryption = 'true'"!]
/*--------------------------------{PROG_CustomDecryptData}------------------------*/
extern tProgStatus PROG_CustomDecryptData(u8 ubEncryptionMethod, u8 * pubData, PduLengthType DataLength);
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgJLR')) and as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL'
    or node:exists(as:modconf('ProgJLR')) and as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL'
    or node:exists(as:modconf('ProgGM')) or node:exists(as:modconf('ProgFCA')) or node:exists(as:modconf('ProgVCC'))
    or node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG'))
    or node:exists(as:modconf('ProgOEMInd')) or node:exists(as:modconf('ProgFord'))
    or node:exists(as:modconf('ProgPSA'))"!]

/*--------------------------------{PROG_CheckProgRequest}------------------------*/
extern u8 PROG_CheckProgRequest(void);
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgJLR')) and as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL'
    or (node:exists(as:modconf('ProgFord')) and as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL')
    or (node:exists(as:modconf('ProgJLR')) and as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL')
    or node:exists(as:modconf('ProgGM')) or node:exists(as:modconf('ProgFCA'))
    or node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG'))
    or node:exists(as:modconf('ProgOEMInd'))
    or node:exists(as:modconf('ProgPSA'))"!]

/*--------------------------{PROG_JumpToApplication}-----------------------------*/
extern void PROG_JumpToApplication(void);
/*--------------------------------{PROG_ReturnsIsReProgRequestFromAppli}------------------------*/
extern tProgBoolean PROG_ReturnsIsReProgRequestFromAppli(void);
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgJLR')) and as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL')"!]

/*--------------------------{PROG_CustomGetSBLStartAddress}-----------------------------*/
extern u32 PROG_CustomGetSBLStartAddress(void);
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgJLR'))
    and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL' or
    as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL'))or (node:exists(as:modconf('ProgFord'))
    and (as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL' or as:modconf('ProgFord')/General/PROG_FORD_VARIANT='SBL'))
    or node:exists(as:modconf('ProgFCA'))
    or node:exists(as:modconf('ProgVAG'))
    or (node:exists(as:modconf('ProgOEMInd')) and (./OemInd/Application_Validity_Algo='Custom'))
    or node:exists(as:modconf('ProgDAG'))
    or node:exists(as:modconf('ProgPSA'))"!]

/*------------------------------{PROG_IsValidApplication}-----------------------*/
extern tProgBoolean PROG_IsValidApplication(void);
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgJLR'))
    and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL'
    or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL'))
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')
    or node:exists(as:modconf('ProgVAG'))
    or node:exists(as:modconf('ProgDAG'))"!]

/*------------------------------{PROG_VerifySectionCrc}--------------------------*/
extern tProgCompleteStatus PROG_VerifySectionCrc(void);
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgJLR')) and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL'))
    or (node:exists(as:modconf('ProgOEMInd')) and (./OemInd/Application_Validity_Algo='Custom') and (./OemInd/Erase_Mode = 'Address'))
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]

/*------------------------------{PROG_InvalidateSection}------------------------*/
extern tProgStatus PROG_InvalidateSection(tProgAddressType ulStartAddress, u32 ulEraseLength, tUdsStatus * ErrorCode);
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or
    (node:exists(as:modconf('ProgOEMInd')) and ((./OemInd/Erase_Mode = 'All') or (./OemInd/Erase_Mode = 'LogicalBlock'))) or
    (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')"!]

/*------------------------------{PROG_InvalidateSection_BlockID}----------------*/
extern tProgStatus PROG_InvalidateSection_BlockID(u8 ubBlockId);
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgJLR'))"!]
/*------------------------------{PROG_CustomSetOpenProgSession}---------------------------*/
extern void PROG_CustomSetOpenProgSession(void);
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgGM'))"!]

/*------------------------------{PROG_GetKeyNBIDValue}--------------------------*/
extern u16 PROG_GetKeyNBIDValue(void);


/*------------------------------{PROG_GetNBIDValue}-----------------------------*/
extern u16 PROG_GetNBIDValue(void);


/*------------------------------{PROG_SetKeyNBIDValue}--------------------------*/
extern void PROG_SetKeyNBIDValue(u16 uwKeyNBID);

/*------------------------------{PROG_SetNBIDValue}-----------------------------*/
extern void PROG_SetNBIDValue(u16 uwNBID);
/*------------------------------{PROG_GetSBIFlagValue}-----------------------------*/
extern u8 PROG_GetSBIFlagValue(void);
/*------------------------------{PROG_SetSBIFlagValue}-----------------------------*/
extern void PROG_SetSBIFlagValue(u8 ubSBI);
[!ENDIF!]
[!IF "not(node:exists(as:modconf('ProgVCC'))) and General/Dsc_Prog_Response = 'true'"!]
/*--------------------------{PROG_GetSuppressBitFromAppli}--------------------*/
extern u8 PROG_GetSuppressBitFromAppli(void);
[!ENDIF!]
[!IF "General/Erase_Check = 'true'"!]
/*------------------------------{PROG_GetEraseStateStatus}----------------------*/
extern void PROG_GetEraseStateStatus(tProgEraseStatus * eEraseStatus);

[!ENDIF!]
[!IF "node:exists(as:modconf('ProgGM'))"!]
/*---------------------------{PROG_CopySBATicket}-----------------------------*/
extern tProgStatus PROG_CopySBATicket(u8 * pubRamBuffer);
extern void Prog_CustomGetAdditionalProgrammingConditionalFlags(u8 * pubFlag);
extern void Prog_CustomGetECUInternalProgrammingFlag(u8 * pubFlag);
extern void Prog_CustomGetProgrammingTolerantConditionsFlag(u8 * pubFlag);
extern void Prog_CustomGetProgrammingConditionsFlag(u8 * pubFlag);
[!ENDIF!]
[!IF "node:exists(as:modconf('Uds'))
    and  ( (node:exists(as:modconf('ProgOEMInd')) and ./OemInd/Application_Validity_Algo='Custom')
    or not(node:exists(as:modconf('ProgOEMInd'))) )"!]
[!VAR "FINGERPRINT_USE" = "0"!]
    [!LOOP " as:modconf('Uds')/Service_DID/*"!]
        [!IF "Callback = 'PROG_WriteFingerprint'"!]
            [!VAR "FINGERPRINT_USE" = "1"!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$FINGERPRINT_USE = 1"!]

/*------------------------{PROG_CustomWriteFingerprint}-----------------------------*/
extern tProgStatus PROG_CustomWriteFingerprint(u8 * pubRamBuffer);

/*------------------------{PROG_CustomGetWriteFingerprintStatus}--------------------*/
extern tProgStatus PROG_CustomGetWriteFingerprintStatus(void);
    [!ENDIF!]
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]

/*---------------------------{PROG_CustomStartChecksumCalc}-------------------------*/
extern void PROG_CustomStartChecksumCalc(void);
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]

/*---------------------------{PROG_CustomChecksumCalc}------------------------------*/
extern tProgStatus PROG_CustomChecksumCalc(u16* puwCalculatedCks);
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]

/*---------------------------{PROG_CustomUpdateChecksumCalc}------------------------*/
extern void PROG_CustomUpdateChecksumCalc(u8* pubData, u32 ulDataSize);
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]
/*---------------------------{PROG_CustomSetAppValidity}----------------------------*/
extern void PROG_CustomSetAppValidity(u32 ulAddress, u32 ulEndAddress);
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgVAG'))
    or node:exists(as:modconf('ProgDAG'))
        or node:exists(as:modconf('ProgVCC'))
        or node:exists(as:modconf('ProgFord'))
        or (node:exists(as:modconf('ProgJLR')) and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL'
		or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL'))
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
    or (node:exists(as:modconf('ProgOEMInd')) and (./OemInd/Application_Validity_Algo='Custom'))"!]
/*---------------------------{PROG_CustomSetDownloadVerificationSuccess}----------------------*/
extern tProgStatus PROG_CustomSetDownloadVerificationSuccess(u8 ubLogicalBlockId, u8 ubLogicalSegmentId, tProgBoolean ubCompareSuccess);
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgVAG')) and General/Expected_Crc_Location = 'Application')
    or (node:exists(as:modconf('ProgOEMInd')) and (./OemInd/Application_Validity_Algo='Custom'))
    or (node:exists(as:modconf('ProgDAG')) and General/Expected_Crc_Location = 'Application')"!]

/*---------------------------{PROG_CustomGetExpectedCrc}----------------------------*/
extern void PROG_CustomGetExpectedCrc(u8 ubLogicalBlockId, u32* pulExpectedCrc);
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]

/*---------------------------{PROG_CustomWriteProgStatus}---------------------------*/
extern void PROG_CustomWriteProgStatus(u32 ulProgrammingStatus);
[!ENDIF!] /* PROG_REQ_PROGRAMMING_STATUS_ENABLE == STD_ON */
[!IF "(node:exists(as:modconf('ProgVAG'))) or (node:exists(as:modconf('ProgDAG'))) or (node:exists(as:modconf('ProgJLR')) and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL')) or (node:exists(as:modconf('ProgFord')) and (as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL' or as:modconf('ProgFord')/General/PROG_FORD_VARIANT='SBL')) or (as:modconf('Prog')/General/Transmit_Response_Before_Reset = 'false')"!]

/*---------------------------{PROG_CustomGetResetCause}-----------------------------*/
extern void PROG_CustomGetResetCause(tProgResCause* pubResetCause, tProgBoolean* pubSendResp);

/*---------------------------{PROG_CustomStoreResetCause}---------------------------*/
extern void PROG_CustomStoreResetCause(tProgResCause ubResetCause, tProgBoolean ubSendResp);
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG'))
    or node:exists(as:modconf('ProgOEMInd')) or node:exists(as:modconf('ProgPSA'))"!]
[!IF "General/Check_Programming_PreConditions = 'true'"!]
/*---------------------------{PROG_CustCheckProgPrecond}----------------------------*/
extern tProgStatus PROG_CustCheckProgPrecond(tUdsStatus * ubDiagStatus);
[!ENDIF!]
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High') or (node:exists(as:modconf('ProgDAG'))) "!]
[!IF "General/Check_Programming_PreConditions = 'true'"!]
/*---------------------------{PROG_CustCheckProgPrecond}----------------------------*/
extern void PROG_CustCheckProgPrecondList(u8 * pubProgrammingConditionNumber, u8 * paubConditionList);
[!ENDIF!]
[!ENDIF!]


#ifdef NCS_UNITARY_TEST
extern void PROG_RamRead(tProgAddressType uMemAddress, tDataLength ulLength, tDataBufferType PROG_FAR_POINTER paubDataBuffer);
extern void PROG_RamWrite(tProgAddressType uMemAddress, tDataLength ulLength, tDataBufferType PROG_FAR_POINTER paubDataBuffer);
#endif     /* NCS_UNITARY_TEST */
[!IF "(node:exists(as:modconf('ProgVAG')) )
    or (node:exists(as:modconf('ProgDAG')))
    or (node:exists(as:modconf('ProgOEMInd')))"!]
/*---------------------------{PROG_CustomWriteCRC}-----------------------------*/
extern void PROG_CustomWriteCRC(u32 ulCrcVal);
[!ENDIF!]

[!IF "DownloadVerification/CVN_Verification = 'true'"!]
extern tProgStatus PROG_CustomCvnVerification(u8 ubLogicalBlockId, const u8* paubExpectedCvn);
extern tProgStatus PROG_CustomCvnVerificationStatus(void);
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgVAG'))
    or (node:exists(as:modconf('ProgDAG')))
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
    or (node:exists(as:modconf('ProgOEMInd'))))"!]
/*---------------------------{PROG_CustomCoherencyCheck}-----------------------------*/
extern tProgStatus PROG_CustomCoherencyCheck(tProgCohChkResult* eCohChkResult);
[!ENDIF!]

[!IF "node:exists(as:modconf('Uds'))"!]
    [!VAR "COHERENCY_PRE_CHECK_USE" = "0"!]
    [!LOOP " as:modconf('Uds')/Routine_Control/*"!]
        [!IF "Callback = 'PROG_CoherencyPreCheck'"!]
            [!VAR "COHERENCY_PRE_CHECK_USE" = "1"!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$COHERENCY_PRE_CHECK_USE = 1"!]
/*---------------------------{PROG_CustomComputeCoherencyPreCheck}-----------------------------*/
extern tProgCohChkResult PROG_CustomComputeCoherencyPreCheck(u8* paubUdsData, PduLengthType pulLen, tUdsStatus* eUdsStatus);
    [!ENDIF!]
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgJLR')) and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL'))"!]
extern tProgStatus PROG_CustomCompatibilityCheck(void);
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgJLR')) and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL'))"!]
[!IF "General/Dual_Memory_Bank_Used = 'true'"!]
extern tProgStatus PROG_CustomCheckAntiRollback(void);
[!ENDIF!]
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgGM'))"!]
[!IF "GM/EcuId_Source = 'User_Callback'"!]
extern void PROG_CustomGetEcuId(u8* paubEcuId);
[!ENDIF!]
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgVAG'))
    or (node:exists(as:modconf('ProgDAG')))
    or ( (node:exists(as:modconf('ProgOEMInd'))) and ( (as:modconf('Prog')/OemInd/Request_Download_Address_Mode = 'Download by logical block') 
    or (as:modconf('Prog')/OemInd/Request_Download_Address_Mode = 'Download by logical block and segment') ) )
    or ( (node:exists(as:modconf('ProgFCA'))) and (as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')) )"!]
extern u16 PROG_CustomGetProgCounter(u8 ubBlockId);

extern tProgStatus PROG_CustomIncrementProgCounter(u8 ubBlockId);
[!ENDIF!]

[!IF "node:exists(as:modconf('Uds'))"!]
    [!VAR "PARTIAL_VERIFY_CRC_USE" = "0"!]
    [!LOOP " as:modconf('Uds')/Routine_Control/*"!]
        [!IF "(Callback = 'PROG_PartialVerificationCrc') or (Callback = 'PROG_LogicalBlockHash')"!]
            [!VAR "PARTIAL_VERIFY_CRC_USE" = "1"!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$PARTIAL_VERIFY_CRC_USE = 1"!]
extern void PROG_CustomGetPartProgSegList(u8 ubBlockId,u32* aulSegProgSize,u8* ubSegNbr);
extern void PROG_CustomSetPartProgSegList(u8 ubBlockId,u32* aulSegProgSize,u8* ubSegNbr);
extern void PROG_CustomClearPartProgSegList(u8 ubBlockId);
    [!ENDIF!]
[!ENDIF!]

[!IF "node:exists(as:modconf('Csm'))"!]
[!IF "(node:exists(as:modconf('ProgGM'))
    or (node:exists(as:modconf('ProgDAG')))
    or (node:exists(as:modconf('ProgVCC')))
    or (node:exists(as:modconf('ProgFord')))
    or (node:exists(as:modconf('ProgJLR')))
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')
    or (node:exists(as:modconf('ProgVAG')))
    or (node:exists(as:modconf('ProgOEMInd'))))"!]
extern void PROG_CustomGetAsymPublicKey(const u8** paubPublicModulus, u32* pulPublicExponent);
[!ENDIF!]
[!ENDIF!]


[!IF "node:exists(as:modconf('Csm'))"!]
[!IF "(node:exists(as:modconf('ProgFord')) and as:modconf('ProgFord')/General/PROG_FORD_VARIANT='SBL')"!]
extern void PROG_CustomGetRequiredTokenAsymPublicKey(const u8** paubPublicModulus, u32* pulPublicExponent, u8 ubActiveKeySign);
[!ENDIF!]
[!ENDIF!]

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT='Authenticated')"!]
/*---------------------------{PROG_CustomInvalidateBootloaderChecksum}-----------------------------*/
extern void PROG_CustomInvalidateBootloaderChecksum(void);

/*---------------------------{PROG_CustomValidateBootloaderChecksum}-----------------------------*/
extern void PROG_CustomValidateBootloaderChecksum(void);

/*---------------------------{PROG_CustomSetBootloaderChecksum}-----------------------------*/
extern void PROG_CustomSetBootloaderChecksum(u8 * pubComputedChecksum);
[!ENDIF!]

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT ='Authenticated') and
    (as:modconf('BM')/Security/SecureBoot/BOOT_VERIFICATION ='ON')"!]
/*---------------------------{PROG_CustomGetComputedBootloaderChecksum}-----------------------------*/
extern void PROG_CustomGetComputedBootloaderChecksum(u8 * pubComputedChecksum);

/*---------------------------{PROG_CustomIsValidBootloaderChecksum}-----------------------------*/
extern tProgStatus PROG_CustomIsValidBootloaderChecksum(void);
[!ENDIF!]

 [!IF "((not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false')))
         and (node:exists(as:modconf('ProgDAG'))
         or node:exists(as:modconf('ProgJLR'))
         or node:exists(as:modconf('ProgFCA'))
         or node:exists(as:modconf('ProgOEMInd'))))
         or ((as:modconf('Prog')/Security/Secure_Checksum_computation = 'true') and (node:exists(as:modconf('ProgVCC'))) and (as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='SBL'))
         or ((as:modconf('Prog')/Security/Secure_Checksum_computation = 'true') and (node:exists(as:modconf('ProgFord'))) and (as:modconf('ProgFord')/General/PROG_FORD_VARIANT='SBL'))"!]
[!IF "(not(node:exists(as:modconf('BM')/Security/SecureBoot/BMSecureBootWithHsm)) or (as:modconf('BM')/Security/SecureBoot/BMSecureBootWithHsm = 'false'))"!]
[!IF "(node:exists(as:modconf('Prog')/Security/ProgCsmSecureConfigId))"!]
[!IF "(not(node:exists(as:modconf('CryIf'))) and (contains(as:modconf('Prog')/Security/ProgCsmSecureConfigId, '/Csm/Csm/CsmMacGenerate/') =  'true')) or
    (node:exists(as:modconf('CryIf')) and (node:exists(node:ref(node:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId)/CsmJobPrimitiveRef)/CsmMacGenerate)) )"!]
/*---------------------------{PROG_CustomGetMacKey}-----------------------------*/
extern void PROG_CustomGetMacKey(const u8** paubKeyData, u32* pulKeyLength);
[!ENDIF!]
[!ENDIF!]
 [!ENDIF!]
/*---------------------------{PROG_CustomSetApplicationChecksum}-----------------------------*/
extern void PROG_CustomSetApplicationChecksum(u8 * pubComputedChecksum, u16 uwBlockIdentifier);
[!ENDIF!]





[!IF "(node:exists(as:modconf('ProgVAG'))
    or (node:exists(as:modconf('ProgDAG'))))"!]

    [!VAR "UPDATE_TP_PARAM_USED" = "0"!]
    [!IF "node:exists(as:modconf('Uds'))"!]
    [!LOOP " as:modconf('Uds')/Service_DID/*"!]
        [!IF "(DID = num:hextoint('0x010B') and (node:exists(as:modconf('ProgDAG')))) or
            (DID = num:hextoint('0x0410') and (node:exists(as:modconf('ProgVAG'))))"!]
            [!VAR "UPDATE_TP_PARAM_USED" = "1"!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!ENDIF!]
    [!IF "$UPDATE_TP_PARAM_USED = 1"!]

extern tProgStatus PROG_CustomGetTpBsValue(u8* ubTpBsValue);
    [!ENDIF!]
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgDAG')))"!]
    [!VAR "UPDATE_TP_PARAM_USED" = "0"!]
    [!IF "node:exists(as:modconf('Uds'))"!]
    [!LOOP " as:modconf('Uds')/Service_DID/*"!]
        [!IF "DID = num:hextoint('0x010B')"!]
            [!VAR "UPDATE_TP_PARAM_USED" = "1"!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!ENDIF!]
    [!IF "$UPDATE_TP_PARAM_USED = 1"!]
extern tProgStatus PROG_CustomGetTpStminValue(u8* ubTpStminValue);
    [!ENDIF!]
[!ENDIF!]

[!IF "General/Erase_Check = 'First Programming Check'"!]
/*---------------------------{PROG_CustomIsFirstProgramming}-----------------------------*/
extern tProgBoolean PROG_CustomIsFirstProgramming(void);
[!ENDIF!]

/*---------------------------{PROG_CustomDownloadNotification}-----------------------------*/
extern tProgStatus PROG_CustomDownloadNotification(u32 ulStartAddress, u32 ulMemorySize);

[!IF "General/Erase_Check = 'Memory Block Erased Check'"!]
/*---------------------------{PROG_CustomGetEraseStatus}-----------------------------*/
extern tProgEraseStatus PROG_CustomGetEraseStatus(u8 ubBlockId);
[!ENDIF!]

[!IF "General/Erase_Check = 'Memory Block Erased Check'"!]
/*---------------------------{PROG_CustomSetEraseStatus}-----------------------------*/
extern tProgStatus PROG_CustomSetEraseStatus(u8 ubBlockId,tProgEraseStatus eEraseStatus);
[!ENDIF!]

/*---------------------------{PROG_CustomMemoryAccessNotification}-------------------*/
extern tProgStatus PROG_CustomMemoryAccessNotification
(
    tProgMemType eMemType,
    tOperationType eOperationType,
    tProgAddressType uMemAddress,
    tDataLength ulLength,
    tDataBufferType PROG_FAR_POINTER paubDataBuffer
);

[!VAR "CUSTOM_MEMORY_USE" = "0"!]
[!VAR "CUSTOM_MEMORY_ASYN" = "0"!]
[!LOOP "Segments/*"!]
    [!VAR "Memory_Type" = "node:ref(Memory)/Memory_Type"!]
    [!IF "$Memory_Type = 'CUSTOM'"!]
        [!VAR "CUSTOM_MEMORY_USE" = "1"!]
        [!VAR "MEMORY_MODE_CUSTOM_MEM" = "node:ref(Memory)/Memory_Mode"!]
        [!IF "$MEMORY_MODE_CUSTOM_MEM = 'asynchronous'"!]
            [!VAR "CUSTOM_MEMORY_ASYN" = "1"!]
        [!ENDIF!]
    [!ENDIF!]
[!ENDLOOP!]

[!IF "$CUSTOM_MEMORY_USE = 1"!]
/*---------------------------{PROG_CustomMemoryErase}-------------------*/
extern tProgStatus PROG_CustomMemoryErase
(
    tProgAddressType uMemAddress,
    tDataLength ulLength
);

/*---------------------------{PROG_CustomMemoryWrite}-------------------*/
extern tProgStatus PROG_CustomMemoryWrite
(
    tProgAddressType uMemAddress,
    tDataLength ulLength,
    tDataBufferType PROG_FAR_POINTER paubDataBuffer
);

/*---------------------------{PROG_CustomMemoryRead}-------------------*/
extern tProgStatus PROG_CustomMemoryRead
(
    tProgAddressType uMemAddress,
    tDataLength ulLength,
    tDataBufferType PROG_FAR_POINTER paubDataBuffer
);

[!IF "$CUSTOM_MEMORY_ASYN = 1"!]
/*---------------------------{PROG_CustomMemGetJobStatus}-------------------*/
extern tProgStatus PROG_CustomMemGetJobStatus(void);
[!ELSE!]
/*---------------------------{PROG_CustomGetNextSextorAddr}-------------------*/
extern tProgAddressType PROG_CustomGetNextSectorAddr(tProgAddressType uMemAddress);
[!ENDIF!]
[!ENDIF!]

[!IF "General/ResumableReprog = 'true'"!]
/*---------------------------{PROG_CustomGetSegmentList}-------------------*/
extern void PROG_CustomGetSegmentList(tSegmentListType * pstSegList);

extern void PROG_CustomStoreSegmentList(tSegmentListType * pstSegList);

extern void PROG_CustomStoreResumeAddress(u8 ubBlockId, u32 ulAddress);

extern u32 PROG_CustomGetResumeAddress(u8 ubBlockId);
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High'"!]
/*---------------------------{PROG_CustomCheckTargetName}-----------------------------*/
extern tProgStatus PROG_CustomCheckTargetName(u8* pubTargetNameAddress,u8 ubLen);
/*------------------------{end PROG_CustomCheckTargetName}--------------------------*/

/*---------------------------{PROG_CustomCheckRollbackId}-----------------------------*/
extern tProgStatus PROG_CustomCheckRollbackId(u8* pubRollbackIdAddress,u8 ubLen);
/*------------------------{end PROG_CustomCheckRollbackId}--------------------------*/

/*---------------------------{PROG_CustomCheckCompatibilityId}-----------------------------*/
extern tProgStatus PROG_CustomCheckCompatibilityId(u8* pubCompatibilityIdAddress,u8 ubLen);
/*------------------------{end PROG_CustomCheckCompatibilityId}--------------------------*/

/*---------------------------{PROG_CustomCheckUuid}-----------------------------*/
extern tProgStatus PROG_CustomCheckUuid(u8* pubUuidAddress,u8 ubLen);
/*------------------------{end PROG_CustomCheckUuid}--------------------------*/

/*---------------------------{PROG_CustomCheckSigningInfo}-----------------------------*/
extern tProgStatus PROG_CustomCheckSigningInfo(u8* pubSigningInfoAddress,u8 ubLen);
/*------------------------{end PROG_CustomCheckSigningInfo}--------------------------*/
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgVCC'))"!]
extern tProgStatus Prog_GetEssValidityStatus(void);
extern tProgStatus Prog_GetEssLogicalBlockNbr(u8* pubBlockNbr);
extern tProgStatus Prog_GetEssLogicalBlockId(u8 ubBlockIndex, u16* pulBlockIdent);
extern tProgStatus Prog_GetEssLogicalBlockStartAddr(u8 ubBlockIndex, u32* pulBlockAddr);
extern tProgStatus Prog_GetEssLogicalBlockLength(u8 ubBlockIndex, u32* pulBlockLength);
extern tProgStatus Prog_GetEssLogicalBlockVerifTable(u8 ubBlockIndex, u32* pulVBTAddress);
extern tProgStatus Prog_GetEss_VBTLength(u32* pulVBTLength);
extern tProgStatus Prog_GetAPPL_VBTLength(u8 ubBlockIndex, u32* pulVBTLength);
extern tProgStatus Prog_GetEssVerifTable(u32* pulVBTAddress);
extern tProgStatus PROG_InvalidateBlock(u8 ubBlockId);
extern void Prog_GetEssApplicationStartAddress(u32* ulApplicationStartAddress);
extern void Prog_GetEssStartAddr(u32* ulEssStartAddress);
extern void Prog_GetEssLength(u32* ulEssLength);
extern boolean Prog_CustomIsProdKeyPresent(void);
extern void Prog_CustomReadKeyChecksum(u8* aubKeyChecksum);
extern void Prog_CustomWriteKey(u32 ulExponent, u8* aubModulus, u8* aubKeyChecksum);
extern tProgStatus PROG_CustomCheckCertificateVerification(void);
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgFord'))"!]
extern tProgStatus Prog_GetLogicalBlockVerifStructure(u8 ubBlockIndex, u32* pulVSAddress);
extern tProgStatus Prog_GetLogicalBlockSignature(u8 ubBlockIndex, u32* pulSignatureAddress);
extern tProgStatus PROG_InvalidateBlock(u8 ubBlockId);
extern tProgStatus PROG_CustomCheckVSBlocksMismatch(u8* pubValidateMemoryStatus);
[!ENDIF!]

[!IF "as:modconf('BM')/Security/SecureBoot/BMSecureBootWithHsm = 'true'"!]
extern tProgStatus PROG_CustomHsmUpdateInitBlock(u16 uwBlockId, u8 *pubMemoryAddress, u32 ulMemorySize);
extern tProgStatus PROG_CustomHsmUpdateBlock(u16 uwBlockId, u8 *aubMacExpctdSign, u16 aubSignLength, u32 ulbankOffset, u8 *pubMemoryAddress, u32 ulMemorySize);
extern void        PROG_CustomHsmUpdateFinish(tProgStatus ubJobResult);
[!ELSEIF "((node:exists(as:modconf('ProgFord'))) and (Segments/*/Partition_Type = 'PROG_HSM_PARTITION'))"!]
extern tProgStatus PROG_CustomHsmFwUpdateInitBlock(u16 uwBlockId, u8 *pubMemoryAddress, u32 ulMemorySize);
extern tProgStatus PROG_CustomHsmFwUpdateBlock(u16 uwBlockId, u8 *pubMemoryAddress, u32 ulMemorySize);
extern tProgStatus PROG_CustomHsmFwUpdateFinish(void);
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgGM')) and (as:modconf('Prog')/Segments/*/Partition_Type='PROG_HSM_PARTITION'))"!]
extern tProgStatus PROG_HSMRequestUpdate(void);
extern tProgStatus Prog_HSMTransferData(u8* paubHsmBuffer,PduLengthType ulHsmBufferLength, u16* uwHsmPEC);
extern tProgPECError PROG_HSMLastDataReceived(void);

[!ENDIF!]

[!IF "General/Dual_Memory_Bank_Used = 'true'"!]
/*---------------------------{PROG_CustomCalcInactiveBankWriteAddr}-----------------------------*/
extern u32 PROG_CustomCalcInactiveBankWriteAddr(u32 ulAddr);
/*------------------------{end PROG_CustomCalcInactiveBankWriteAddr}--------------------------*/

/*---------------------------{PROG_CustomCalcInactiveBankReadAddr}-----------------------------*/
extern u32 PROG_CustomCalcInactiveBankReadAddr(u32 ulAddr);
/*------------------------{end PROG_CustomCalcInactiveBankReadAddr}--------------------------*/

/*---------------------------{PROG_CustomCalcActiveBankReadAddr}-----------------------------*/
extern u32 PROG_CustomCalcActiveBankReadAddr(u32 ulAddr);
/*------------------------{end PROG_CustomCalcActiveBankReadAddr}--------------------------*/

[!ENDIF!]

[!IF "((node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid') or (node:exists(as:modconf('ProgJLR'))))"!]
[!VAR "SIGNATUREVERIFCATIONENABLED"="'false'"!]
[!LOOP "Segments/*"!]
    [!IF "SignatureVerification = 'true'"!]
        [!VAR "SIGNATUREVERIFCATIONENABLED"="'true'"!]
    [!ENDIF!]
[!ENDLOOP!]
[!IF "(not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))) or ($SIGNATUREVERIFCATIONENABLED = 'true')"!]
extern void PROG_CustomGetVerificationParameters(u32 * m_ulStartAddress, u32 * m_ulEndAddress ,u32 * m_ubSignatureStartAddress);
[!ENDIF!]
[!ENDIF!]
#if (PROG_CSM_DECRYPTION_ENABLE == STD_ON)
extern void PROG_CustomGetSymDecryptionKey(const u8** pubKey, u32 * pulKeyLength);
extern void PROG_CustomDecryptGetInitVector(const u8** pubInitVect, u32 * pulInitVectLength);
#endif /* (PROG_CSM_DECRYPTION_ENABLE == STD_ON) */

[!IF "(node:exists(as:modconf('ProgJLR')))"!]
extern tUdsStatus PROG_CustomUpdateCertAsymPublicKey(u16 *puwLen, u8 *aubUdsData);
extern tProgStatus PROG_CustomVDStable_update(tVDSlayout * pstVDSlayout,u8 * pubSegmentId,u8 * pubFirstSegment, u8 ubVDSaccesstype);
[!ENDIF!]

[!IF "as:modconf('Prog')/Segments/*/Partition_Type = 'PROG_BLU_APP_PARTITION' 
   or as:modconf('Prog')/Segments/*/Partition_Type = 'PROG_BLU_CAL_PARTITION'
   or as:modconf('Prog')/Segments/*/Partition_Type = 'PROG_BLU_PARTITION'"!]
/*---------------------------{PROG_CustomSetBLUDownloadInProgress}----------------------------*/
extern void PROG_CustomSetBLUDownloadInProgress(tProgBoolean ubBLUDownload);
/*---------------------------{PROG_CustomIsBLUDownloadInProgress}----------------------------*/
extern tProgBoolean PROG_CustomIsBLUDownloadInProgress(void);
/*---------------------------{PROG_CustomIsBLUPatternPresent}----------------------------*/
extern tProgBoolean PROG_CustomIsBLUPatternPresent(u8 ubLogicalBlockId, u8 ubLogicalSegmentId);
[!IF "node:exists(as:modconf('ProgOEMInd'))"!]
/*---------------------------{PROG_CustomSetBLUVerificationSuccess}----------------------------*/
extern tProgStatus PROG_CustomSetBLUVerificationSuccess(tProgBoolean ubCompareSuccess);
[!ENDIF!]
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgPSA'))"!]
/*--------------------------{PROG_CustomSetECUStatus}-----------------------------*/
extern void PROG_CustomSetECUStatus(u8 ubEcuStatusValue);

/*--------------------------{PROG_CustomGetECUStatus}-----------------------------*/
extern void PROG_CustomGetECUStatus(u8 *ubEcuStatus);

/*--------------------------{PROG_CustomWriteKeyAppli}-----------------------------*/
extern tProgStatus PROG_CustomWriteKeyAppli(u8 * pubData, u8 ubDataLength);

/*--------------------------{PROG_CustomWriteZI}-----------------------------*/
extern tProgStatus PROG_CustomWriteZI(u8 * pubData, u8 ubDataLength);

/*--------------------------{PROG_CustomGetWriteJobResult}-----------------------------*/
extern tProgStatus PROG_CustomGetWriteJobResult(u8 ubLogicalMarker);

/*--------------------------{PROG_CustomCheckZIAvailableSpace}-----------------------------*/
extern tProgStatus PROG_CustomCheckZIAvailableSpace(void);

/*--------------------------{PROG_CustomUpdateLogSaveMarkingByte}-----------------------------*/
extern tProgStatus PROG_CustomUpdateLogSaveMarkingByte(u8 ubNewLogSaveMarkingByte);

/*--------------------------{PROG_CustomReadKeyAppli}-----------------------------*/
extern tProgStatus PROG_CustomReadKeyAppli(u16 * aubKeyAppli);

/*--------------------------{PROG_CustomStoreDownloadedSegmentSize}-----------------------------*/
extern void PROG_CustomStoreDownloadedSegmentSize(u32 * pulSegSize, u8 ubSegmentId);

/*--------------------------{PROG_CustomGetDownloadedSegmentSize}-----------------------------*/
extern void PROG_CustomGetDownloadedSegmentSize(u32 * pulSegSize, u8 ubSegmentId);
[!ENDIF!]
 [!IF "((node:exists(Security/ProgCsmReferences/SignatureVerification/Allow2CustomCsmStartPreprocess)) and (node:value(Security/ProgCsmReferences/SignatureVerification/Allow2CustomCsmStartPreprocess) = 'true')) or
((node:exists(Security/Allow2CustomCsmStartPreprocess)) and (node:value(Security/Allow2CustomCsmStartPreprocess) = 'true')) or
((node:exists(Decryption/Allow2CustomCsmStartPreprocess)) and (node:value(Decryption/Allow2CustomCsmStartPreprocess) = 'true')) or
((node:exists(GM/ProgCsmReferences/Allow2CustomCsmStartPreprocess)) and (node:value(Allow2CustomCsmStartPreprocess) = 'true'))"!]
extern Csm_ReturnType PROG_CustomCsmStrtPreproc(const u8** ubKeyPtr, u32 ulCsmJobId);
[!ENDIF!]
/*---------------------------{PROG_CustomGetDERFormat}-----------------------------*/
[!IF "node:exists(as:modconf('ProgFord'))"!]
extern void PROG_CustomGetDERFormat(const u8** ubKeyPtr);
extern void Prog_CustomReadPublicKeyHash(u8*aubPublicKeyHash);
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgFord')) and as:modconf('ProgFord')/General/PROG_FORD_VARIANT='SBL')"!]
extern tProgStatus PROG_CustomVerifyUpdateSwitchKeyHeader(const u8 * pubUdsData, u16 ulDataLength, u8 *pubHeaderStatus);
extern tProgStatus PROG_CustomUpdateDevelopmentKey(u8 *pubNewDevPubKey, u8* pubWriteStat);
extern tProgStatus PROG_CustomUpdateProductionKey(u8 *pubNewProdPubKey, u8* pubWriteStat);
extern tProgStatus PROG_CustomUpdateTokenKey(u8 *pubNewTokenPubKey, u8* pubWriteStat);
extern tProgStatus PROG_CustomCopySwitchingKeyRequest(const u8 * pubUdsData, u16 ulDataLength, u8* pubWriteStat);
extern tProgStatus PROG_CustomUpdateActiveKeyStatAndMode(u8 ubActiveKey, u8 ubActiveKeyMode, u8* pubWriteStat);
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgFord'))"!]
extern u8 PROG_CustomGetActiveKey(void);
extern u8 PROG_CustomGetKeyMode(void);
extern void Prog_CustomReadLastSuccessSwitchingKeyRCReqest(u8* aubKeyRCData);
[!ENDIF!]
#if ((PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91))
extern tProgStatus PROG_CustomCheckSA_PreConditions(void);
#endif
[!IF " node:exists(as:modconf('ProgOEMInd')) "!]
tProgStatus PROG_Custom_Guard_CompareKey_RD(void);
[!ENDIF!]
extern tProgStatus PROG_CustomCheckSBLStartAddress(u32 ulAddressSBL);
extern tProgStatus PROG_Custom_MemStatuscheck(void);
[!IF "(node:exists(as:modconf('ProgJLR')) and ( as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL' ))"!]
extern void PROG_CustomSetUnsigneBlckDwnldStat(void);
[!ENDIF!]
#endif     /* PROG_CBK_H */
