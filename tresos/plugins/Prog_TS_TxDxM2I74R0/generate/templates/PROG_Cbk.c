/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               PROG layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file PROG_Cbk.c                      */
/*%%  |                             |  %%  \brief PROG layer source plugin file  */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.74.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2015 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
#include "EB_Prj.h"
#include "PROG_Hsm.h"
#include "PROG_HsmPROG.h"
#include "board.h"
[!AUTOSPACING!]

[!IF "(node:exists(as:modconf('ProgJLR')) and ( as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL'))"!]
/** \brief This Variable is set after a successful or unsuccessful download verification in PROG_CustomSetDownloadVerificationSuccess and variable value shall be checked for validity status of the logical block during CheckValidApplication treatment.
 ** \value PROG_TRUE Treatment finish successfully
 ** \value PROG_FALSE Error happened during treatment
 **/
tProgBoolean m_aubBlockDownloadStatus[PROG_BLOCK_NB];
[!ENDIF!]
/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */
[!IF "node:exists(as:modconf('ProgJLR')) and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL')
        or node:exists(as:modconf('ProgGM')) or node:exists(as:modconf('ProgFCA')) or node:exists(as:modconf('ProgVCC'))
        or node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgFord')) or node:exists(as:modconf('ProgDAG'))
        or node:exists(as:modconf('ProgOEMInd')) or node:exists(as:modconf('ProgPSA'))"!]


/** \brief API that check if a programming request has been received by the application
 **
 ** Callback is called: at Bootloader startup to know if a programming request has
 **                     been received in Application
 **
 ** Callback shall implement: get information from application if a programming
 **                          request has been received (e.g: read a flag from
 **                          noinit RAM shared between Bootloader and
 **                           Application)
 **
 ** \return Result of check
 ** \retval PROG_BOOT_REPROG Reprogramming request has been received
 ** \retval PROG_BOOT_NO_REPROG No reprogramming request received
 **/
u8 PROG_CheckProgRequest(void)
{
    return 0U;
}
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgJLR')) and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL')
    or (node:exists(as:modconf('ProgFord')) and as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL')
	or node:exists(as:modconf('ProgGM')) or node:exists(as:modconf('ProgFCA'))
    or node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG'))
    or node:exists(as:modconf('ProgOEMInd'))
    or node:exists(as:modconf('ProgPSA'))"!]
/** \brief Callback performing jump to application software
 **
 ** Callback is called: at Bootloader startup if application is valid and shall
 **                    be executed
 **
 ** Callback shall implement: jump to application start address
 **
 **/
void PROG_JumpToApplication(void)
{

}

/** \brief API that returns information if a programming request has been received by the application
 **
 ** Callback is called: at reception of a request in BlPduR module to ignore the request if Rx simulation  
 **                           request is ongoing (programming request has been received by the application)
 **
 ** Callback shall implement: returns information from application if a programming
 **                          request has been received or not (e.g: from PROG_CheckProgRequest API)
 **
 ** \return Information checked in PROG_CheckProgRequest API
 ** \retval TRUE Reprogramming request has been received in Application
 ** \retval FALSE Reprogramming request has not been received in Application
 **/
tProgBoolean PROG_ReturnsIsReProgRequestFromAppli(void)
{
    return FALSE;
}
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgJLR')) and as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL'"!]
/** \brief Callback performing the read of the SBL software start address
 **
 ** Callback is called: While jumping to SBL to read the SBL startup address to execute it
 **
 ** Callback shall implement: jump to SBL start address
 **
 ** \return SBL Startup Address
 **
 **/
u32 PROG_CustomGetSBLStartAddress(void)
{
    return 0x00000000U;
}
[!ENDIF!]

/** \brief Callback that shall disable ECC if needed
 ** Callback is called: When Bootloader perform read access on Flash that can be
 **                     unprogrammed and can cause ECC error
 **
 ** Callback shall implement: If needed, disabling of ECC check
 **                           Hardware specific)
 **/
void PROG_DisableECCCheck(void)
{

}


/** \brief Callback that shall enable ECC if needed
 ** Callback is called: After Bootloader has performed a read access on Flash
 **                    that can be unprogrammed and can cause ECC error
 **
 ** Callback shall implement: If needed, enabling of ECC check
 **                          (Hardware specific)
 **/
void PROG_EnableECCCheck(void)
{

}

[!IF "Decryption/Enable_Decryption = 'true'"!]
/** \brief Callback that shall request data decryption before writing them to memory
 ** Callback is called: receiving a TransferData before the decompression (if activated)
 **
 ** Callback shall implement: If needed, it shall decrypt the received data according to the EncryptingMethod.
 **
 ** \param[in] ubEncryptionMethod Encrypting method  indicator (from RequestDownload dataFormatIdentifier field)
 ** \param[in,out] pubData received data pointer (points to the encrypted data and callback implementation shall copy decrypted data at the same location than the encrypted one.)
 ** \param[in] DataLength received data length
 **
 ** \return Result of the decryption
 ** \retval PROG_E_OK Decryption finish successfully
 ** \retval PROG_E_NOT_OK Error happened during decryption
 **/
tProgStatus PROG_CustomDecryptData(u8 ubEncryptionMethod, u8 * pubData, PduLengthType DataLength)
{
    OSC_PARAM_UNUSED(ubEncryptionMethod);
    OSC_PARAM_UNUSED(pubData);
    OSC_PARAM_UNUSED(DataLength);

    return PROG_E_OK;
}
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgJLR'))
    and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL'
    or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL'))
	or (node:exists(as:modconf('ProgFord'))
    and (as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL' or as:modconf('ProgFord')/General/PROG_FORD_VARIANT='SBL'))
    or node:exists(as:modconf('ProgFCA')) or node:exists(as:modconf('ProgVAG')) or (node:exists(as:modconf('ProgOEMInd'))
    and (./OemInd/Application_Validity_Algo='Custom'))
    or node:exists(as:modconf('ProgDAG'))
    or node:exists(as:modconf('ProgPSA'))"!]

/** \brief Callback checking if the application is valid or not
 **
 ** Callback is called: at startup and on some routine.
 **
 ** Callback shall implement: It shall verify that the application
 ** with all its dependencies are correctly flashed
 ** and return the result of the check
 **
 ** \return Result of check
 ** \retval TRUE Application is valid
 ** \retval FALSE Application is not valid or not present
 **/
tProgBoolean PROG_IsValidApplication(void)
{
    return FALSE;
}
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgJLR'))
    and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL' or as:modconf(ProgJLR)/General/PROG_JLR_VARIANT='SBL'
    		or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL'))"!]
/** \brief Callback verifying the application is correctly downloaded and setting the application validity marker
 **
 ** Callback is called: on CheckApplicationValidation routine at the end of the programming sequence.
 **
 ** Callback shall implement: verification that each segment is fully programmed and setting of
 ** the validity marker if necessary. It then returns the status of the check.
 **
 ** \return Result of check
 ** \retval TRUE Application is valid
 ** \retval FALSE Application is not valid or not present
 **/
tProgCompleteStatus PROG_VerifySectionCrc(void)
{
    return 0U;
}
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgJLR')) and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL')
    or (node:exists(as:modconf('ProgOEMInd')) and (./OemInd/Application_Validity_Algo='Custom') and (./OemInd/Erase_Mode != 'All'))
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]
/** \brief Callback invalidating the application markers
 **
 ** Callback is called: On Erase routine reception
 **
 ** Callback shall implement: 1- customer code that shall be executed before
 **                           performing an erasing
 **
 **                           2- It shall invalidate the application or the current erased section
 **                           to make sure no jump to the application will be done if an error occurred
 **                           and the application is not fully erased or reprogrammed
 **
 ** \param[in] ulStartAddress Erased Start address of the segment that will be erased
 ** \param[in] ulEraseLength requested erase length
 ** \param[out] ErrorCode UDS error code that shall be return in case of error during API treatment
 **
 ** \return Result application invalidation
 ** \retval PROG_E_OK Treatment finish successfully
 ** \retval PROG_E_NOT_OK Error happened during treatment (ErrorCode shall be filled in this case)
 **/
tProgStatus PROG_InvalidateSection(tProgAddressType ulStartAddress, u32 ulEraseLength, tUdsStatus * ErrorCode)
{
    OSC_PARAM_UNUSED(ulStartAddress);
    OSC_PARAM_UNUSED(ulEraseLength);
    OSC_PARAM_UNUSED(ErrorCode);

    return PROG_E_OK;
}
[!ENDIF!]

/*------------------------------{PROG_CustomSetOpenProgSession}---------------------------*/
[!IF "node:exists(as:modconf('ProgJLR'))"!]
/** \brief Called in order to set the state of ECU in programming session
 **
 ** Callback is called: during the failure of SBL activation
 **
 **  Callback shall implement: customer code that shall be executed
 **  to simulate the ECU programming session
 **/
void PROG_CustomSetOpenProgSession(void)
{

}
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or
    (node:exists(as:modconf('ProgOEMInd')) and (./OemInd/Erase_Mode = 'All')) or
    (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')"!]
/** \brief API that invalidate the application marker
 **
 ** Callback is called: On Erase routine reception
 **
 ** Callback shall implement: 1- customer code that shall be executed before
 **                           performing an erasing of a logical block
 **
 **                           2- It shall invalidate the logical block that will be erased
 **                           to make sure no jump to the application will be done if an error occurred
 **                           and the application is not fully erased or reprogrammed
 **
 ** \param[in] ubBlockId The ID of the block that will be erased
 **
 ** \return Result application invalidation
 ** \retval PROG_E_OK Treatment finish successfully
 ** \retval PROG_E_NOT_OK Error happened during treatment
 **/
tProgStatus PROG_InvalidateSection_BlockID(u8 ubBlockId)
{
    OSC_PARAM_UNUSED(ubBlockId);

    return PROG_E_OK;
}
[!ENDIF!]


/** \brief Called before Bootloader perform a jump to application
 **
 ** Callback is called: Before jumping to Application
 **
 **  Callback shall implement: customer code that shall be executed before
 **  jumping to application
 **/
void PROG_SwitchApplicationModeInd(void)
{

}

[!IF "(node:exists(as:modconf('ProgGM')) and (as:modconf('Prog')/Segments/ */Partition_Type='PROG_HSM_PARTITION'))"!]
/** \brief  Request to HSM Processor for Update
 **
 ** Callback is called: To Send Request to HSM Processor for Update
 **
 ** Callback shall implement: the reading of status to check if the HSM Processor allowed the Update
 **
 ** \return Result
 ** \retval PROG_E_OK HSM Processor Update Allowed
 ** \retval PROG_E_NOT_OK HSM Processor Update Not Allowed
 **/
tProgStatus PROG_HSMRequestUpdate(void)
{
    return PROG_E_OK;
}
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgGM')) and (as:modconf('Prog')/Segments/ */Partition_Type='PROG_HSM_PARTITION'))"!]
/** \brief  Request to HSM Processor for Update
 **
 ** Callback is called: To transfer Data from buffer to HSM Processor
 **
 ** Callback shall implement: the reading of status to check if the HSM Processor Read Data From buffer
 **
 ** \param[in] paubHsmBuffer pointer to a HSM buffer
 ** \param[in] ulHsmBufferLength Length of HSM Buffer
 ** \param[in] uwHsmPEC Programming Error Code received from HSM
 **
 ** \return Result
 ** \retval PROG_E_OK Read Data From buffer by HSM Processor succeeded
 ** \retval PROG_E_NOT_OK Read Data From buffer by HSM Processor Failed
 ** \retval PROG_E_BUSY HSM Read Data From buffer by HSM Processor InProgress
 **/
tProgStatus Prog_HSMTransferData(u8* paubHsmBuffer,PduLengthType ulHsmBufferLength, u16* uwHsmPEC)
{
	OSC_PARAM_UNUSED(paubHsmBuffer);
	OSC_PARAM_UNUSED(ulHsmBufferLength);
	OSC_PARAM_UNUSED(uwHsmPEC);
    return PROG_E_OK;
}
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgGM')) and (as:modconf('Prog')/Segments/ */Partition_Type='PROG_HSM_PARTITION'))"!]
/** \brief  Request to HSM Processor for Update
 **
 ** Callback is called: To Inform HSM Processor with Last of Data received
 **
 ** Callback shall implement: the reading of status to check if the HSM Processor Received last data
 **
 ** \return Result
 ** \retval PROG_PEC_NO_ERROR HSM Processor Received the last Data
 ** \retval ERROR_CODE HSM Processor Update Failed
 **/
tProgPECError PROG_HSMLastDataReceived(void)
{
    return PROG_E_OK;
}
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgGM'))"!]
/** \brief Callback retrieving the Key NBID value stored in memory
 **
 ** Callback is called: during reprogramming process to get the key NBID of the current
 **                     application stored in NVM.
 **
 ** It will be used to know if the new download application can be accepted or not
 **
 ** Callback shall implement: reading from non volatile memory of the Key NBID
 **                           value
 **
 ** \return Key NBID value on 16 bits
 **/
u16 PROG_GetKeyNBIDValue(void)
{
    return 0x0000U;
}
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgGM'))"!]
/** \brief Callback retrieving the NBID value store in memory
 **
 ** Callback is called: during reprogramming process to get the NBID of the current
 **                     application stored in NVM.
 **
 ** It will be used to know if the new download application can be accepted or not
 **
 ** Callback shall implement: reading from non volatile memory of the NBID
 **                           value
 **
 ** \return NBID value on 16 bits
 **/
u16 PROG_GetNBIDValue(void)
{
    return 0x0000U;
}
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgGM'))"!]
/** \brief Retrieve the Key NBID value store in memory
 **
 ** Callback is called: during reprogramming process to update the key NBID
 **                     of the downloaded application stored in NVM.
 **
 ** Callback shall implement: Writting in non volatile memory of the Key NBID
 **                          value
 **
 ** \param[in] uwKeyNBID New value of the Key NBID to be store in memory
 **
 **/
void PROG_SetKeyNBIDValue(u16 uwKeyNBID)
{
    OSC_PARAM_UNUSED(uwKeyNBID);
}
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgGM'))"!]
/** \brief Retrieve the NBID value store in memory
 **
 ** Callback is called: during reprogramming process to update the NBID
 **                     of the downloaded application stored in NVM.
 **
 ** Callback shall implement: Writting in non volatile memory of the NBID
 **                          value
 **
 ** \param[in] uwNBID New value of the NBID to be store in memory
 **
 **/
void PROG_SetNBIDValue(u16 uwNBID)
{
    OSC_PARAM_UNUSED(uwNBID);
}
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgGM'))"!]
/** \brief Set the SBI flag value in secure memory
**
** Callback is called: during startup to update the SBI flag
**                     for the SBA ticket stored in Secure RAM.
**
** Callback shall implement: Writing in secure volatile memory of the SBI flag
**                          value
**
** \param[in] ubSBI New value of the SBI flag to be stored in memory
**
**/
void PROG_SetSBIFlagValue(u8 ubSBI)
{
   OSC_PARAM_UNUSED(ubSBI);
}
/** \brief Retrieve the SBI flag value stored in memory
**
** Callback is called: during reprogramming process to update the SBI flag
**                     for the SBA ticket stored in Secure RAM.
**
** Callback shall implement: Reading in secure volatile memory of the SBI flag
**                          value
**
** \return SBI flag value on 8 bits
**
**/
u8 PROG_GetSBIFlagValue(void)
{
  return 0x00;
}
[!ENDIF!]
[!IF "not(node:exists(as:modconf('ProgVCC'))) and General/Dsc_Prog_Response = 'true'"!]
/** \brief Get the status of the suppress positive response bit from the last reprogramming request in application
 **
 ** Callback is called: At startup when Bootloader shall send a response to a request that
 **                     has been received in application
 **
 ** Callback shall implement: get from application information if the
 **                          suppressPositiveResponse bit was set in the
 **                           received request (e.g: read a flag from noinit RAM
 **                           shared between Bootloader and  Application)
 **
 ** \return Suppression bit value
 ** \retval TRUE The suppress positive response bit was set (response will not be sent)
 ** \retval FALSE The suppress positive response bit was not set (response will be sent)
 **/
u8 PROG_GetSuppressBitFromAppli(void)
{
    return FALSE;
}
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgGM'))"!]
/** \brief Copy the SBA ticket to the provided RAM buffer
 **
 ** Callback is called: On Bootloader startup during SBA check
 **
 ** Callback shall implement: the reading from non volatile memory of the SBA
 **                           ticket (822 bytes long, starting with the data
 **                          type)
 **
 ** \param[out] pubRamBuffer pointer to a RAM buffer where to copy the SBA ticket
 **
 ** \return Result
 ** \retval PROG_E_OK Copy ok
 ** \retval PROG_E_NOT_OK Copy failed
 **/
tProgStatus PROG_CopySBATicket(u8 * pubRamBuffer)
{
    OSC_PARAM_UNUSED(pubRamBuffer);

    return PROG_E_OK;
}

/** \brief get additional programming conditional flags
 **
 ** This API is called during the processing of the check programming dependencies routine
 **
 ** \param[out] pubFlag pointer to a variable to get the additional programming conditional flag
 **
 ** \return void
 **/
void Prog_CustomGetAdditionalProgrammingConditionalFlags(u8 * pubFlag)
{
    OSC_PARAM_UNUSED(pubFlag);
}
/*------------------------{end Prog_CustomGetAdditionalProgrammingConditionalFlags}--------------------------*/


/** \brief get the ecu internal programming flags
 **
 ** This API is called during the processing of the check programming dependencies routine
 **
 ** \param[out] pubFlag pointer to a variable to get the ecu internal programming flags
 **
 ** \return void
 **/
void Prog_CustomGetProgrammingConditionsFlag(u8 * pubFlag)
{
    OSC_PARAM_UNUSED(pubFlag);
}
/*------------------------{end Prog_CustomGetProgrammingConditionsFlag}--------------------------*/

/** \brief get the programming tolerant conditions flag
 **
 ** This API is called during the processing of the check programming dependencies routine
 **
 ** \param[out] pubFlag pointer to a variable to get the programming tolerant conditions flag
 **
 ** \return void
 **/
void Prog_CustomGetProgrammingTolerantConditionsFlag(u8 * pubFlag)
{
    OSC_PARAM_UNUSED(pubFlag);
}
/*------------------------{end Prog_CustomGetProgrammingTolerantConditionsFlag}--------------------------*/

/** \brief get the programming conditions flag
 **
 ** This API is called during the processing of the check programming dependencies routine
 **
 ** \param[out] pubFlag pointer to a variable to get the programming conditions flag
 **
 ** \return void
 **/
void Prog_CustomGetECUInternalProgrammingFlag(u8 * pubFlag)
{
    OSC_PARAM_UNUSED(pubFlag);
}
/*------------------------{end Prog_CustomGetECUInternalProgrammingFlag}--------------------------*/
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
/** \brief Start the Fingerprint Writing
 **
 ** Callback is called: On reception of WriteDataByIdentifier service for Fingerprint
 **                     DID
 **
 ** Callback shall implement:
 **
 **                           1- Check the validity of FingerPrint data
 **
 **                           2- the writing in non-volatile memory of the
 **                            Fingerprint data (pubRamBuffer points on the
 **                            dataIdentifier field of the WriteDataByIdentifier
 **                            request)
 **                            Asynchronous management can be implemented, in this case
 **                            PROG_E_BUSY value is returned and further call to
 **                            PROG_CustomGetWriteFingerprintStatus will allow
 **                            Bootloader to get writing status
 **
 ** \param[in] pubRamBuffer pointer to a RAM buffer where the DID identifier and fingerprint data
 **                         are located
 **
 ** \return Result
 ** \retval PROG_E_OK Write Fingerprint ok
 ** \retval PROG_E_NOT_OK Write Fingerprint failed
 ** \retval PROG_E_BUSY Write Fingerprint in progress
 **/
tProgStatus PROG_CustomWriteFingerprint(u8 * pubRamBuffer)
{
    OSC_PARAM_UNUSED(pubRamBuffer);
    return PROG_E_OK;
}

/** \brief Get the status of the fingerprint writing
 **
 ** Callback is called: After PROG_CustomWriteFingerprint returns PROG_E_BUSY, this
 **                     callback is called periodically until getting a status
 **                     different from PROG_E_BUSY
 **
 ** Callback shall implement: provide status of the fingerprint writing
 **
 ** \return Result
 ** \retval PROG_E_OK Write Fingerprint ok
 ** \retval PROG_E_NOT_OK Write Fingerprint failed
 ** \retval PROG_E_BUSY Write Fingerprint in progress
 **/
tProgStatus PROG_CustomGetWriteFingerprintStatus(void)
{
    return PROG_E_OK;
}
    [!ENDIF!]
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]
/** \brief Initialization of the Custom Checksum calculation
 **
 ** Callback is called: On start of a checksum calculation
 **
 ** Callback shall implement: Initialization of checksum calculation.
 **                          Checksum calculation is customer specific (Checksum,
 **                          CRC16,...)
 **/
void PROG_CustomStartChecksumCalc(void)
{
}
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]

/** \brief Update (transfer data blocks) for Custom Checksum calculation
 **
 ** Callback is called: After a PROG_CustomStartChecksumCalc call and when data to be
 **                     used for checksum calculation have been read from Flash memory
 **
 ** Callback shall implement: Checksum calculation.
 **                           Checksum calculation is customer specific (Checksum,
 **                          CRC16,...)
 **
 ** \param[in] pubData pointer to the data to compute
 ** \param[in] ulDataSize Length of data to compute
 **
 **/
void PROG_CustomUpdateChecksumCalc(u8* pubData, u32 ulDataSize)
{
    OSC_PARAM_UNUSED(pubData);
    OSC_PARAM_UNUSED(ulDataSize);
}
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]

/** \brief Get result of checksum calculation
 **
 ** Callback is called: To get result of a checksum calculation, after
 **                    PROG_CustomStartChecksumCalc/PROG_CustomUpdateChecksumCalc
 **                    calls
 **
 ** Callback shall implement: Provide result of checksum calculation.
 **                           Checksum calculation is customer specific (Checksum,
 **                           CRC16,...)
 **
 ** \param[out] puwCalculatedCks pointer to calculated checksum
 **
 ** \return state
 ** \retval PROG_E_OK Calculation finished successfully
 ** \retval PROG_E_BUSY Calculation in progress
 ** \retval PROG_E_NOT_OK Calculation finished on error
 **
 **/
tProgStatus PROG_CustomChecksumCalc(u16* puwCalculatedCks)
{
    OSC_PARAM_UNUSED(puwCalculatedCks);
    return PROG_E_OK;
}
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]

/** \brief Set the Application Validity
 **
 ** Callback is called: After Checksum computation has succeeded
 **
 ** Callback shall implement: Update the application validity flag as valid
 **                           (additional customer coherency check can be required
 **                           to conclude on application validity)
 **
 ** \param[in] ulAddress Start address of sector on which the CRC has succeeded
 ** \param[in] ulEndAddress End address of sector on which the CRC has succeeded
 **
 **/
void PROG_CustomSetAppValidity(u32 ulAddress, u32 ulEndAddress)
{
    OSC_PARAM_UNUSED(ulAddress);
    OSC_PARAM_UNUSED(ulEndAddress);
}
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]

/** \brief Callback storing the programming status structure
 **
 ** Callback is called: After Programming status update
 **
 ** Callback shall implement: Storage of Programming status in RAM. The storage in
 **                           non-volatile memory shall be done before the ECU is
 **
 ** \param[in] ulProgrammingStatus Programming Status (4 Bytes)
 **
 **/
void PROG_CustomWriteProgStatus(u32 ulProgrammingStatus)
{
    OSC_PARAM_UNUSED(ulProgrammingStatus);
}
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgVAG'))) or (node:exists(as:modconf('ProgDAG'))) or (node:exists(as:modconf('ProgJLR')) 
		and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL') or (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL')) or (node:exists(as:modconf('ProgFord')) and
			(as:modconf('ProgFord')/General/PROG_FORD_VARIANT='PBL' or as:modconf('ProgFord')/General/PROG_FORD_VARIANT='SBL')) or (as:modconf('Prog')/General/Transmit_Response_Before_Reset = 'false')"!]
/** \brief Store the reset cause and the need of response
 **
 ** Callback is called: Before Bootloader perform a reset to set reset cause
 **                     (UDS request that has caused the reset).
 **
 ** Callback shall implement: storage of the reset cause (UDS request)
 **
 ** \param[in] ubResetCause the reset cause
 ** \param[in] ubSendResp the need of response according to suppressPositiveResponse bit
 **            from the request
 **
 **/
void PROG_CustomStoreResetCause(tProgResCause ubResetCause, tProgBoolean ubSendResp)
{
    OSC_PARAM_UNUSED(ubResetCause);
    OSC_PARAM_UNUSED(ubSendResp);
}
/** \brief Restore the reset cause and the need of response
 **
 ** Callback is called: At Bootloader startup to get the UDS request that has caused
 **                    the reset.
 **
 ** Callback shall implement: provide the cause of the reset (UDS request) that has been
 **                           set by application or Bootloader (by call to
 **                           PROG_CustomStoreResetCause)
 **
 ** \param[out] pubResetCause pointer to the reset cause
 ** \param[out] pubSendResp Provide information if positive response shall be sent
 **             depending of the value of the suppressPositiveResponse bit from the request
 **             TRUE: response shall be sent / FALSE: no response shall be sent
 **
 **/
void PROG_CustomGetResetCause(tProgResCause* pubResetCause, tProgBoolean* pubSendResp)
{
    OSC_PARAM_UNUSED(pubResetCause);
    OSC_PARAM_UNUSED(pubSendResp);
}
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgVAG'))) or (node:exists(as:modconf('ProgDAG')))
    or (node:exists(as:modconf('ProgOEMInd'))) or (node:exists(as:modconf('ProgPSA')))"!]
[!IF "General/Check_Programming_PreConditions = 'true'"!]
/** \brief Check if all the programming pre-conditions are met
 **
 ** Callback is called: On Programming precondition check
 **
 ** Callback shall implement: programming precondition check. Inform Bootloader
 **                           if the ECU is in a state where programming can be
 **                           performed. It shall check for the error condition Security access 
 **                           if locked and update error list (m_aubPreProgErrorList).
 **                           If condition are not correct programming will be rejected by Bootloader 
 **                           and negative response will be sent on the network.
 **
 ** \param[out] ubDiagStatus UDS diagnostic status
 **
 ** \return state
 ** \retval PROG_E_OK All the programming pre-conditions are met
 ** \retval PROG_E_NOT_OK At least one programming pre-condition is NOT met
 **
 **/
tProgStatus PROG_CustCheckProgPrecond(tUdsStatus * ubDiagStatus)
{
    tProgStatus eProgStatus = PROG_E_OK;
    OSC_PARAM_UNUSED(ubDiagStatus);
    return eProgStatus;
}
[!ENDIF!]
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High') or (node:exists(as:modconf('ProgDAG'))) "!]
[!IF "General/Check_Programming_PreConditions = 'true'"!]
/** \brief Check if all the programming pre-conditions are met
 **
 ** Callback is called: On Programming precondition check
 **
 ** Callback shall implement: programming precondition check. Inform Bootloader
 **                           if the ECU is in a state where programming can be
 **                           performed. If condition are not correct programming
 **                           will be rejected by Bootloader and negative response
 **                           will be sent on the network.
 **
 ** \param[out] pubProgrammingConditionNumber Number of failed Programming Conditions
 **                                          that shall be returned in the response
 **
 ** \param[out] paubConditionList List of failed conditions
 **
 **
 **/
void PROG_CustCheckProgPrecondList(u8 * pubProgrammingConditionNumber, u8 * paubConditionList)
{
    OSC_PARAM_UNUSED(pubProgrammingConditionNumber);
    OSC_PARAM_UNUSED(paubConditionList);
    /*
        In case of condition failure set pubProgrammingConditionNumber to failure number
        and list failure in paubConditionList: e.g paubConditionList[0]=0x07
    */
}
[!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgVCC')) or node:exists(as:modconf('ProgFord'))
        or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
        or (node:exists(as:modconf('ProgJLR')) and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL'))
        or (node:exists(as:modconf('ProgOEMInd')) and (./OemInd/Application_Validity_Algo='Custom'))"!]
/** \brief Callback called after comparing the expected checksum or signature and the calculated one.
 **
 ** Callback is called: After a successful or unsuccessful download verification
 **
 ** Callback shall implement: update the external global variable m_aubBlockDownloadStatus for the logical block validity status
 **                           If Dual bank feature is used, this call back can be used to know that a complete, 
 **                           and successful application download happened and therefore allow bank swaps.                          
 **
 ** \param[in] ubLogicalBlockId The id of the logical block for which the compare was done
 ** \param[in] ubLogicalSegmentId The id of the logical segment  for which the compare was done
 **            (ignore if the full logical block is verified)
 ** \param[in] ubCompareSuccess TRUE if the 2 elements of the comparison are identical
 **
 ** \return state
 ** \retval PROG_E_OK Treatment finish successfully and If Dual bank feature is used, 0x04U is updated in m_ubPostSoftwareDownloadStatus
 ** \retval PROG_E_NOT_OK Error happened during treatment and If Dual bank feature is used, 0x02U is updated in m_ubPostSoftwareDownloadStatus
 **/
tProgStatus PROG_CustomSetDownloadVerificationSuccess(u8 ubLogicalBlockId, u8 ubLogicalSegmentId, tProgBoolean ubCompareSuccess)
{
    OSC_PARAM_UNUSED(ubLogicalBlockId);
    OSC_PARAM_UNUSED(ubLogicalSegmentId);
    OSC_PARAM_UNUSED(ubCompareSuccess);

    return PROG_E_OK;
}
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgJLR')) and ( as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL'))"!]
/** \brief  This Callback is called  to do the Compatibility check treatment.
 **
 ** Callback is called: on reception of Check Valid Application request after successful verification of downloded software to perform the compatibility Checks 
 **
 ** Callback shall implement: The algorithm performing the compatibility check of the previously programmed blocks (E.g.: checking of blocks versions compatibility) and set the application validity Status.
 **                           (checks of All blocks previously programmed are valid, SW-HW mismatch, SW-SW mismatch, other error)
 ** \return state
 ** \retval PROG_E_OK Treatment finish successfully and If Dual bank feature is used, 0x1A is updated in m_ubPostSoftwareDownloadStatus
 ** \retval PROG_E_NOT_OK Error happened during treatment and If Dual bank feature is used, 0x1BU is updated in m_ubPostSoftwareDownloadStatus
 ** \retval PROG_E_BUSY if the check is on going
 **/
tProgStatus PROG_CustomCompatibilityCheck(void)
{
    return PROG_E_OK;
}
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgJLR')) and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL'))"!]
[!IF "General/Dual_Memory_Bank_Used = 'true'"!]
/** \brief  This Callback is called  to do the Anti-Rollback check treatment.
 **
 ** Callback is called: on successful Check Valid Application of the SW downloaded to inform the HSM about the Valid Software present in the bank during a Commit Routine. 
 **
 ** Callback shall implement: PROG_CustomCheckAntiRollback callback to read the Logical Blocks Versions,
                              perform Anti-Rollback Checks through HSM APIs and then perform the Switch bank and Commit.
                              Informing the HSM about the Valid Software present in the Current Bank.
 ** \return state
 ** \retval PROG_E_OK on successfully updating the HSM Anti-Rollback Table
 ** \retval PROG_E_NOT_OK If update on the HSM Anti-Rollback Table has failed
 **/
tProgStatus PROG_CustomCheckAntiRollback(void)
{
    return PROG_E_OK;
}
[!ENDIF!]
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgVAG')) and General/Expected_Crc_Location = 'Application')
    or (node:exists(as:modconf('ProgDAG')) and General/Expected_Crc_Location = 'Application')"!]

/** \brief This API is called in order to get the expected CRC corresponding to the required logical block,
 ** if this one is not found in the request.
 **
 ** Callback is called: During CRC verification
 **
 ** Callback shall implement: extract from downloaded software the expected CRC value
 **
 ** \param[in] ubLogicalBlockId The logical block on which corresponding CRC is required
 ** \param[out] pulExpectedCrc The expected CRC
 **
 **/
void PROG_CustomGetExpectedCrc(u8 ubLogicalBlockId, u32* pulExpectedCrc)
{
    OSC_PARAM_UNUSED(ubLogicalBlockId);
    OSC_PARAM_UNUSED(pulExpectedCrc);
}
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgVAG')) )
    or (node:exists(as:modconf('ProgDAG')))
    or (node:exists(as:modconf('ProgOEMInd')))"!]
/** \brief Callback for CRC storage
 **
 ** Callback is called: After CRC calculation
 **
 ** Callback shall implement: storage of the CRC value for further use
 **
 ** \param[in] ulCrcVal CRC value
 **
 **/
void PROG_CustomWriteCRC(u32 ulCrcVal)
{
    OSC_PARAM_UNUSED(ulCrcVal);
}
[!ENDIF!]

[!IF "DownloadVerification/CVN_Verification = 'true'"!]
/** \brief Callback for CVN check
 **
 ** Callback is called: on reception of verify partial sw
 **
 ** Callback shall implement: the check of CVN value
 **
 ** \param[in] ubLogicalBlockId Block identifier value
 ** \param[in] paubExpectedCvn CVN value
 **
 ** \return state
 ** \retval PROG_E_OK Treatment finish successfully
 ** \retval PROG_E_BUSY Treatment is in progress
 ** \retval PROG_E_NOT_OK Error happened during treatment
 **/
tProgStatus PROG_CustomCvnVerification(u8 ubLogicalBlockId, const u8* paubExpectedCvn)
{
    OSC_PARAM_UNUSED(ubLogicalBlockId);
    OSC_PARAM_UNUSED(paubExpectedCvn);
    return PROG_E_OK;
}

/** \brief Callback for CVN check
 **
 ** Callback is called: on reception of verify partial sw
 **
 ** Callback shall implement: the return of CVN status check updated in the verification callback
 **
 ** \return state
 ** \retval PROG_E_OK Treatment finish successfully
 ** \retval PROG_E_BUSY Treatment is in progress
 ** \retval PROG_E_NOT_OK Error happened during treatment
 **/
tProgStatus PROG_CustomCvnVerificationStatus(void)
{
    return PROG_E_OK;
}
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgVAG')))
    or (node:exists(as:modconf('ProgDAG')))
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
    or (node:exists(as:modconf('ProgOEMInd')))"!]
/** \brief This API is called  to do the coherency check treatment
 **
 ** Callback is called: on the coherency check request reception
 **
 ** Callback shall implement: the algorithm performing the coherency check of the previously programmed blocks (E.g.: checking of blocks versions compatibility).
 **
 ** \param[out] eCohChkResult The result of the coherency check.
 **             Can be: 0-correct, 1-incorrect, 2-incorrect error SW-HW, 3-incorrect error SW-SW, 4-incorrect other error
 **
 ** \return Coherency Check result
 ** \retval PROG_E_OK when the check has finished
 ** \retval PROG_E_BUSY if the check is on going
 **/
tProgStatus PROG_CustomCoherencyCheck(tProgCohChkResult* eCohChkResult)
{
    OSC_PARAM_UNUSED(eCohChkResult);
    return PROG_E_OK;
}
[!ENDIF!]

[!IF "node:exists(as:modconf('Uds'))"!]
[!VAR "COHERENCY_PRE_CHECK_USE" = "0"!]
    [!LOOP " as:modconf('Uds')/Routine_Control/ *"!]
        [!IF "Callback = 'PROG_CoherencyPreCheck'"!]
            [!VAR "COHERENCY_PRE_CHECK_USE" = "1"!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$COHERENCY_PRE_CHECK_USE = 1"!]
/** \brief This API is called to perform the Pre Check Coherency on data passed in parameter
 **
 ** Callback is called: on the reception of the Pre Check Programming Dependencies Routine
 **
 ** Callback shall implement the algorithm performing the Pre Check Programming Dependencies.
 **
 ** \param[in]  paubUdsData Pointer to the data on which Pre Check shall be performed
 ** \param[in]  pulLen      Number of bytes of the data
 ** \param[out] eUdsStatus  The result of the pre check coherency.
 **             Can be: UDS_ACK, UDS_NRC_XX (XX can take the values defined in ISO 14429 -  Annex A - Negative Response codes)
 **
 ** \return Coherency Pre Check Status Record
 ** \retval 0-No Failure
 ** \retval 1-Internal Error
 ** \retval 2-Error HW-SW
 ** \retval 3-Error SW-SW
 **/
tProgCohPreChkResult PROG_CustomComputeCoherencyPreCheck(u8* paubUdsData, PduLengthType pulLen, tUdsStatus* eUdsStatus)
{
    OSC_PARAM_UNUSED(paubUdsData);
    OSC_PARAM_UNUSED(pulLen);
    OSC_PARAM_UNUSED(eUdsStatus);
    return PROG_E_COHPRECHK_CORRECT;
}
    [!ENDIF!]
[!ENDIF!]


[!IF "node:exists(as:modconf('ProgGM'))"!]
[!IF "GM/EcuId_Source = 'User_Callback'"!]
/** \brief API to be called in order to get the ECU Id from a custom location
 **
 ** This API is called to get the ECU ID during the TransferData. The implementation of this API shall permit
 ** to give the EcuId to the bootloader from a custom location (Flash, RAM, custom configuration, etc.).
 **
 ** \param[out] paubEcuId Pointer to ECU Id
 **
 **/
/*---------------------------{PROG_CustomGetEcuId}-----------------------------*/
void PROG_CustomGetEcuId(u8* paubEcuId)
{
    OSC_PARAM_UNUSED(paubEcuId);
}
/*------------------------{end PROG_CustomGetEcuId}--------------------------*/
[!ENDIF!]
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgVAG'))
    or (node:exists(as:modconf('ProgDAG')))
    or ( (node:exists(as:modconf('ProgFCA'))) and (as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')) )"!]
/** \brief API to get the stored value of the programming counter.
 **
 ** \param[in] ubBlockId BlockID
 **
 ** Callback is called: Before erasing the block
 **
 ** Callback shall implement: return the current value of the programming counter
 **
 ** \return programming counter on 16 bits
 **/
/*---------------------------{PROG_CustomGetProgCounter}-----------------------------*/
u16 PROG_CustomGetProgCounter(u8 ubBlockId)
{
    OSC_PARAM_UNUSED(ubBlockId);
    return 0x0000U;
}
/*------------------------{end PROG_CustomGetProgCounter}--------------------------*/


/** \brief API to increment the programming counter for the erased logical block.
 **
 ** This API is called to increment the programming counter of the block.
 ** The maximum value shall be limited at 0xFFFF and it shall not overflow.
 **
 ** \param[in] ubBlockId BlockID
 **
 ** Callback is called: Before erasing the block
 **
 ** Callback shall implement: increment the current value of the programming counter
 **
 ** \return Result of incrementation operation
 ** \retval PROG_E_OK incrementation operation finished successfully
 ** \retval PROG_E_NOT_OK incrementation operation error happened
 **
 **/
/*---------------------------{PROG_CustomIncrementProgCounter}-----------------------------*/
tProgStatus PROG_CustomIncrementProgCounter(u8 ubBlockId)
{
    OSC_PARAM_UNUSED(ubBlockId);
    return PROG_E_OK;
}
/*------------------------{end PROG_CustomIncrementProgCounter}--------------------------*/
[!ENDIF!]

 [!IF "node:exists(as:modconf('Uds'))"!]
     [!VAR "PARTIAL_VERIFY_CRC_USE" = "0"!]
     [!LOOP " as:modconf('Uds')/Routine_Control/ *"!]
         [!IF "(Callback = 'PROG_PartialVerificationCrc') or (Callback = 'PROG_LogicalBlockHash')"!]
             [!VAR "PARTIAL_VERIFY_CRC_USE" = "1"!]
         [!ENDIF!]
     [!ENDLOOP!]
     [!IF "$PARTIAL_VERIFY_CRC_USE = 1"!]

/** \brief This API allows the integrator to store information regarding the partial software download for a specific blockId.
        The callback is called after each successful CheckMemory routine processing.
 **
 ** \param[in] ubBlockId block Id for which the information is stored
 ** \param[out] aulSegProgSize pointer to an array containing the size of programmed data for each segment in the block
 ** \param[out] ubSegNbr number of the segments programmed
 **
 **/
/*---------------------------{PROG_CustomGetPartProgSegList}-----------------------------*/
void PROG_CustomGetPartProgSegList(u8 ubBlockId,u32* aulSegProgSize,u8* ubSegNbr)
{
    OSC_PARAM_UNUSED(ubBlockId);
    OSC_PARAM_UNUSED(aulSegProgSize);
    OSC_PARAM_UNUSED(ubSegNbr);
}
/*------------------------{end PROG_CustomGetPartProgSegList}--------------------------*/

/** \brief This API allows the integrator to store information regarding the partial software download for a specific blockId.
        The callback is called after each successful CheckMemory routine processing.
 **
 ** \param[in] ubBlockId block Id for which the information is stored
 ** \param[in] aulSegProgSize pointer to an array containing the size of programmed data for each segment in the block
 ** \param[in] ubSegNbr number of the segments programmed
 **
 **/
/*---------------------------{PROG_CustomSetPartProgSegList}-----------------------------*/
void PROG_CustomSetPartProgSegList(u8 ubBlockId,u32* aulSegProgSize,u8* ubSegNbr)
{
    OSC_PARAM_UNUSED(ubBlockId);
    OSC_PARAM_UNUSED(aulSegProgSize);
    OSC_PARAM_UNUSED(ubSegNbr);
}
/*------------------------{end PROG_CustomSetPartProgSegList}--------------------------*/

/** \brief This API allows the integrator to clear information stored in the non-volatile memory regarding the partial software download for a specific block.
        The callback is called at every block erase
 **
 ** \param[in] ubBlockId block Id for which the information is stored
 **
 **/
/*---------------------------{PROG_CustomClearPartProgSegList}-----------------------------*/
void PROG_CustomClearPartProgSegList(u8 ubBlockId)
{
    OSC_PARAM_UNUSED(ubBlockId);
}
/*------------------------{end PROG_CustomClearPartProgSegList}--------------------------*/

    [!ENDIF!]
[!ENDIF!]

[!IF "node:exists(as:modconf('Csm'))"!]
[!IF "(node:exists(as:modconf('ProgGM'))
      or node:exists(as:modconf('ProgVCC'))
      or node:exists(as:modconf('ProgFord'))
    or (node:exists(as:modconf('ProgDAG')))
    or (node:exists(as:modconf('ProgFCA')))
    or (node:exists(as:modconf('ProgVAG')))
    or (node:exists(as:modconf('ProgOEMInd')))
    or (node:exists(as:modconf('ProgJLR')))
    )"!]


/** \brief Read the current active public key and Get the public key modulus and exponent when using asymmetric cryptography. Used in SA_InitCrypto
 **
 ** \param[out] paubPublicModulus Pointer to asymmetric cryptography public key modulus array
 ** \param[out] pulPublicExponent Pointer to asymmetric cryptography public key exponent
 **
 **/
/*---------------------------{PROG_CustomGetAsymPublicKey}-----------------------------*/
void PROG_CustomGetAsymPublicKey(const u8** paubPublicModulus, u32* pulPublicExponent)
{
    OSC_PARAM_UNUSED(paubPublicModulus);
    OSC_PARAM_UNUSED(pulPublicExponent);
}
/*------------------------{end PROG_CustomGetAsymPublicKey}--------------------------*/
[!ENDIF!]
[!ENDIF!]

[!IF "node:exists(as:modconf('Csm'))"!]
 [!IF "(node:exists(as:modconf('ProgFord')) and as:modconf('ProgFord')/General/PROG_FORD_VARIANT='SBL')"!]
 
/** \brief Get the public key modulus and exponent based on token key based on operation when using asymmetric cryptography. 
 ** Used in SA_InitCrypto
 **
 ** \param[out] paubPublicModulus Pointer to asymmetric cryptography public key modulus array
 ** \param[out] pulPublicExponent Pointer to asymmetric cryptography public key exponent
 ** \param[in]  ubActiveKeySign will have the data  i.e. used to get the required data (Development or production) 
 **
 **/
 /*---------------------------{PROG_CustomGetRequiredTokenAsymPublicKey}-----------------------------*/
void PROG_CustomGetRequiredTokenAsymPublicKey(const u8** paubPublicModulus, u32* pulPublicExponent, u8 ubActiveKeySign)
{
    OSC_PARAM_UNUSED(paubPublicModulus);
    OSC_PARAM_UNUSED(pulPublicExponent);
    OSC_PARAM_UNUSED(ubActiveKeySign);
}
 /*---------------------------{end PROG_CustomGetRequiredTokenAsymPublicKey}-----------------------------*/
 [!ENDIF!]
[!ENDIF!]


[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT ='Authenticated') and
    (as:modconf('BM')/Security/SecureBoot/BOOT_VERIFICATION ='ON')"!]
/** \brief This API is called to get the computed Bootloader checksum stored in non-volatile memory
 **
 ** Callback is called: Before starting Bootloader to verify the computed checksum
 **
 ** Callback shall implement: get from non-volatile memory the Bootloader checksum and
 **                           copy it to the provided pointer
 **
 ** \param[out] pubComputedChecksum Pointer where to copy the checksum.
 **
 **/
void PROG_CustomGetComputedBootloaderChecksum(u8 * pubComputedChecksum)
{
    OSC_PARAM_UNUSED(pubComputedChecksum);
}

/** \brief This API is called to know if the stored Bootloader checksum is valid
 **
 ** Callback is called: Before reading the bootloader checksum
 **
 ** Callback shall implement: get from non-volatile memory the Bootloader checksum status
 **
 ** \return Validity status
 ** \retval PROG_E_OK Checksum is valid
 ** \retval PROG_E_NOT_OK Checksum is invalid
 **
 **/
tProgBoolean PROG_CustomIsValidBootloaderChecksum(void)
{
    return PROG_TRUE;
}
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
((node:exists(as:modconf('CryIf'))) and (node:exists(node:ref(node:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId)/CsmJobPrimitiveRef)/CsmMacGenerate)) )"!]


void PROG_CustomGetMacKey(const u8** paubKeyData, u32* pulKeyLength)
{
    OSC_PARAM_UNUSED(paubKeyData);
    OSC_PARAM_UNUSED(pulKeyLength);
}
[!ENDIF!]
[!ENDIF!]
 [!ENDIF!]
/** \brief This API is called to store the computed Application checksum in non-volatile memory
 **
 ** Callback is called:  Before sending response to CheckMemory request for authenticated block
 **
 ** Callback shall implement: store in non-volatile memory the Application checksum (will be
 ** compare at next startup with one calculated by application). It shall also update the checksum
 ** computed by application.
 **
 ** \param[in] pubComputedChecksum Pointer to Application checksum to store.
 ** \param[in] uwBlockIdentifier Block Identifier.
 **
 **/
void PROG_CustomSetApplicationChecksum(u8 * pubComputedChecksum, u16 uwBlockIdentifier)
{
    OSC_PARAM_UNUSED(pubComputedChecksum);
    OSC_PARAM_UNUSED(uwBlockIdentifier);
}
[!ENDIF!]

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT='Authenticated')"!]
/** \brief This API is called to set the Bootloader checksum as invalid
 **
 ** Callback is called: After Bootloader checksum computation, before updating
 ** the checksum.
 **
 ** Callback shall implement: Set in non-volatile memory the Bootloader checksum validity
 **                           flag with invalid value
 **
 **/
void PROG_CustomInvalidateBootloaderChecksum(void)
{

}

/** \brief This API is called to store the computed Bootloader checksum in non-volatile memory
 **
 ** Callback is called: After Bootloader checksum computation at Bootloader start
 **
 ** Callback shall implement: store in non-volatile memory the Bootloader checksum
 **
 ** \param[in] pubComputedChecksum Pointer to Bootloader checksum to store.
 **
 **/
void PROG_CustomSetBootloaderChecksum(u8 * pubComputedChecksum)
{
    OSC_PARAM_UNUSED(pubComputedChecksum);
}

/** \brief This API is called to set the Bootloader checksum as valid
 **
 ** Callback is called: After Bootloader checksum computation, after updating
 ** the checksum.
 **
 ** Callback shall implement: Set in non-volatile memory the Bootloader checksum validity
 **                           flag with valid value
 **
 **/
void PROG_CustomValidateBootloaderChecksum(void)
{

}
[!ENDIF!]


[!IF "(node:exists(as:modconf('ProgVAG')) or (node:exists(as:modconf('ProgDAG'))))"!]

    [!VAR "UPDATE_TP_PARAM_USED" = "0"!]
        [!IF "node:exists(as:modconf('Uds'))"!]
            [!LOOP " as:modconf('Uds')/Service_DID/ *"!]
                [!IF "(DID = num:hextoint('0x010B') and (node:exists(as:modconf('ProgDAG')))) or
                    (DID = num:hextoint('0x0410') and (node:exists(as:modconf('ProgVAG'))))"!]
                    [!VAR "UPDATE_TP_PARAM_USED" = "1"!]
                [!ENDIF!]
            [!ENDLOOP!]
        [!ENDIF!]
    [!IF "$UPDATE_TP_PARAM_USED = 1"!]

/** \brief Get the TP Blocksize value
 **
 ** Callback is called:  On bootloader startup or on demand of reprogramming, in order to get the TP Blocksize value used in application
 **
 ** Callback shall implement: The get of the TP Blocksize value used in application. If no valid value is available PROG_E_NOT_OK shall be returned.
 **
 ** \param[in,out] ubTpBsValue Blocksize value
 **
 ** \return return Get TP value status
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomGetTpBsValue(u8* ubTpBsValue)
{
    OSC_PARAM_UNUSED(ubTpBsValue);

    return PROG_E_OK;
}
    [!ENDIF!]
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgDAG')))"!]
[!VAR "UPDATE_TP_PARAM_USED" = "0"!]
    [!IF "node:exists(as:modconf('Uds'))"!]
        [!LOOP " as:modconf('Uds')/Service_DID/ *"!]
            [!IF "DID = num:hextoint('0x010B')"!]
                [!VAR "UPDATE_TP_PARAM_USED" = "1"!]
            [!ENDIF!]
        [!ENDLOOP!]
    [!ENDIF!]
    [!IF "$UPDATE_TP_PARAM_USED = 1"!]
/** \brief Get the STmin value
 **
 ** Callback is called:  On bootloader startup or on demand of reprogramming, in order to get the STmin value used in application
 **
 ** Callback shall implement: The get of the STmin value used in application. If no valid value is available PROG_E_NOT_OK shall be returned.
 **
 ** \param[in,out] ubTpStminValue STmin value
 **
 ** \return Get STmin value status
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomGetTpStminValue(u8* ubTpStminValue)
{
    OSC_PARAM_UNUSED(ubTpStminValue);

    return PROG_E_OK;
}
    [!ENDIF!]
[!ENDIF!]


/** \brief Notification of a download event
 **
 ** Callback is called: On reception of RequestDownload routine
 **
 ** Callback shall implement: provide information that the Flash Memory was programmed and should be erased before a new writing and customer specific implementation on download event
 **
 ** \param[in] ulStartAddress received start address value
 ** \param[in] ulMemorySize received memory size value
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomDownloadNotification(u32 ulStartAddress, u32 ulMemorySize)
{
    OSC_PARAM_UNUSED(ulStartAddress);
    OSC_PARAM_UNUSED(ulMemorySize);
    return PROG_E_OK;
}

[!IF "General/Erase_Check = 'Memory Block Erased Check'"!]
/** \brief Get the erase status of the memory block
 **
 ** Callback is called: On reception of Erase routine
 **
 ** Callback shall implement: provide information if logical block is already
 **                           erase and that erase shall be skipped
 **
 ** \param[in] ubBlockId ID of the Memory block to be erased
 **
 ** \return state
 ** \retval PROG_E_NOT_ERASED
 ** \retval PROG_E_ERASED
 **/
tProgEraseStatus PROG_CustomGetEraseStatus(u8 ubBlockId)
{
    OSC_PARAM_UNUSED(ubBlockId);

    return PROG_E_NOT_ERASED;
}
[!ENDIF!]

[!IF "General/Erase_Check = 'Memory Block Erased Check'"!]
/** \brief Set the erase status of the memory block
 **
 ** Callback is called: After successful logical block erasing and
 **                     RequestDownload request reception
 **
 ** Callback shall implement: storage of the logical block erase status
 **
 ** \param[in] ubBlockId ID of the Memory block to be erased
 ** \param[in] eEraseStatus New erase status
 **
 ** \return eProgStatus success of the erase status update
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomSetEraseStatus(u8 ubBlockId,tProgEraseStatus eEraseStatus)
{
    OSC_PARAM_UNUSED(ubBlockId);
    OSC_PARAM_UNUSED(eEraseStatus);

    return PROG_E_OK;
}
[!ENDIF!]

[!IF "General/Erase_Check = 'First Programming Check'"!]
/** \brief Get the status of the Flash memory if it's full erased or not (i.e first download on this ECU)
 **
 ** Callback is called: On reception of Erase routine to skip erasing if memory has never been written
 **
 ** Callback shall implement: provide information if this is the first Flash programming
 **
 ** \return eIsFirstProgramming status return by the function (PROG_TRUE / PROG_FALSE)
 **/
tProgBoolean PROG_CustomIsFirstProgramming(void)
{
    return PROG_FALSE;
}
[!ENDIF!]

/** \brief Notification of memory access to allow customers to place their routines
 **
 ** Callback is called: After successful memory data access
 **
 ** Callback shall implement: Operation that need to be performed after a memory data access
 **
 ** \param[in] eMemType Memory type (RAM, Flash and Flash Ext)
 ** \param[in] eOperationType Operation type (Read, write and erase)
 ** \param[in] uMemAddress Start address
 ** \param[in] ulLength Data length
 ** \param[in] paubDataBuffer Data buffer
 **
 ** \return eProgStatus success of the operation(s)
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomMemoryAccessNotification
(
    tProgMemType eMemType,
    tOperationType eOperationType,
    tProgAddressType uMemAddress,
    tDataLength ulLength,
    tDataBufferType PROG_FAR_POINTER paubDataBuffer
)
{
    OSC_PARAM_UNUSED(eMemType);
    OSC_PARAM_UNUSED(eOperationType);
    OSC_PARAM_UNUSED(uMemAddress);
    OSC_PARAM_UNUSED(ulLength);
    OSC_PARAM_UNUSED(paubDataBuffer);

    return PROG_E_OK;
}

[!VAR "CUSTOM_MEMORY_USE" = "0"!]
[!VAR "CUSTOM_MEMORY_ASYN" = "0"!]
[!LOOP "Segments/ *"!]
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
/** \brief This API is called to perform an erase operation
 **
 ** Callback is called: After request erasing of the custom memory
 **
 ** Callback shall implement: Operation to erase the custom memory
 **
 ** \param[in] uMemAddress Start address
 ** \param[in] ulLength Data length
 **
 ** \return eProgStatus success of the operation(s)
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 ** \retval PROG_E_BUSY
 **/
tProgStatus PROG_CustomMemoryErase
(
    tProgAddressType uMemAddress,
    tDataLength ulLength
)
{
    OSC_PARAM_UNUSED(uMemAddress);
    OSC_PARAM_UNUSED(ulLength);

    return PROG_E_OK;
}

/** \brief This API is called to perform a writing operation
 **
 ** Callback is called: After request writing data on the custom memory
 **
 ** Callback shall implement: Operation to write data on custom memory
 **
 ** \param[in] uMemAddress Start address
 ** \param[in] ulLength Data length
 ** \param[in] paubDataBuffer Data buffer
 **
 ** \return eProgStatus success of the operation(s)
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 ** \retval PROG_E_BUSY
 **/
tProgStatus PROG_CustomMemoryWrite
(
    tProgAddressType uMemAddress,
    tDataLength ulLength,
    tDataBufferType PROG_FAR_POINTER paubDataBuffer
)
{
    OSC_PARAM_UNUSED(uMemAddress);
    OSC_PARAM_UNUSED(ulLength);
    OSC_PARAM_UNUSED(paubDataBuffer);

    return PROG_E_OK;
}

/** \brief This API is called to perform a reading operation
 **
 ** Callback is called: After request reading data on the custom memory
 **
 ** Callback shall implement: Operation to read data on custom memory
 **
 ** \param[in] uMemAddress Start address
 ** \param[in] ulLength Data length
 ** \param[in] paubDataBuffer Data buffer
 **
 ** \return eProgStatus success of the operation(s)
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 ** \retval PROG_E_BUSY
 **/
tProgStatus PROG_CustomMemoryRead
(
    tProgAddressType uMemAddress,
    tDataLength ulLength,
    tDataBufferType PROG_FAR_POINTER paubDataBuffer
)
{
    OSC_PARAM_UNUSED(uMemAddress);
    OSC_PARAM_UNUSED(ulLength);
    OSC_PARAM_UNUSED(paubDataBuffer);

    return PROG_E_OK;
}

[!IF "$CUSTOM_MEMORY_ASYN = 1"!]
/** \brief Get the status of memory job
 **
 ** Callback is called: After each memory access operation
 **
 ** Callback shall implement: After PROG_CustomMemoryErase/PROG_CustomMemoryWrite/PROG_CustomMemoryRead
 **                           returns PROG_E_BUSY, this callback is called periodically until getting
 **                           a status different from PROG_E_BUSY.
 **
 ** \return eProgStatus success of the operation(s)
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 ** \retval PROG_E_BUSY
 **/
tProgStatus PROG_CustomMemGetJobStatus(void)
{
    return PROG_E_OK;
}

[!ELSE!]
/** \brief Get next sector start address
 **
 ** Callback is called: After an erase operation to set the beginning of the next sector address
 **
 ** Callback shall implement: Operation to get the next sector address
 **
 ** \param[in] uMemAddress Memory address of reference sector
 **
 ** \return Start address of the next sector.
 **
 **/
tProgAddressType PROG_CustomGetNextSectorAddr
(
    tProgAddressType uMemAddress
)
{
    return uMemAddress;
}

[!ENDIF!]
[!ENDIF!]
[!IF "General/ResumableReprog = 'true'"!]
/** \brief Retrieve segment list stored in memory
 **
 ** Callback is called: This function is called in case reprogramming shall be resume in order
 ** to get all data that have been previously written for the logical block
 **
 ** Callback shall implement: Copy from memory of data that have been previously stored
 ** with PROG_CustomStoreSegmentList
 **
 ** \param[in,out] pstSegList pointer on structure where to copy the data
 **
 **
 **/
void PROG_CustomGetSegmentList
(
    tSegmentListType * pstSegList
)
{
    OSC_PARAM_UNUSED(pstSegList);
}

/** \brief Store segment list in memory
 **
 ** Callback is called: This function is called on RequestTransferExit to
 ** store information about the downloaded segment
 **
 ** Callback shall implement: Copy to memory of the segment list
 **
 ** \param[in] pstSegList address of structure to copy
 **
 ** \return Resume address of the logical block.
 **
 **/
void PROG_CustomStoreSegmentList(tSegmentListType * pstSegList)
{
    OSC_PARAM_UNUSED(pstSegList);
}

/** \brief Store resume address
 **
 ** Callback is called: During reprogramming to store resume address
 **
 ** \param[in] ubBlockId Index of the logical block
 ** \param[in] ulAddress Address to store
 **
 **
 **/
void PROG_CustomStoreResumeAddress
(
    u8 ubBlockId,
    u32 ulAddress
)
{
    OSC_PARAM_UNUSED(ubBlockId);
    OSC_PARAM_UNUSED(ulAddress);
}

/** \brief Get resume address
 **
 ** Callback is called: On reception of ReadDataByIdenfifier for
 ** DID "Reprogramming Resume Information"
 **
 ** \param[in] ubBlockId Index of the logical block
 **
 **
 **/
u32 PROG_CustomGetResumeAddress
(
    u8 ubBlockId
)
{
    OSC_PARAM_UNUSED(ubBlockId);

    return 0U;
}


[!ENDIF!]


[!IF "node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High'"!]
/** \brief Callback used to check the TargetName
 **
 ** \param[in] pubTargetNameAddress TargetName address
 ** \param[in] ubLen TargetName length
 **
 ** \return return status
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomCheckTargetName(u8* pubTargetNameAddress,u8 ubLen)
{
    OSC_PARAM_UNUSED(pubTargetNameAddress);
    OSC_PARAM_UNUSED(ubLen);

    return PROG_E_OK;
}

/** \brief Callback used to check the RollbackId
 **
 ** \param[in] pubRollbackIdAddress RollbackId address
 ** \param[in] ubLen RollbackId length
 **
 ** \return return status
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomCheckRollbackId(u8* pubRollbackIdAddress,u8 ubLen)
{
    OSC_PARAM_UNUSED(pubRollbackIdAddress);
    OSC_PARAM_UNUSED(ubLen);
    return PROG_E_OK;
}

/** \brief Callback used to check the CompatibilityId
 **
 ** \param[in] pubCompatibilityIdAddress CompatibilityId address
 ** \param[in] ubLen CompatibilityId length
 **
 ** \return return status
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomCheckCompatibilityId(u8* pubCompatibilityIdAddress,u8 ubLen)
{
    OSC_PARAM_UNUSED(pubCompatibilityIdAddress);
    OSC_PARAM_UNUSED(ubLen);
    return PROG_E_OK;
}

/** \brief Callback used to check the Uuid
 **
 ** \param[in] pubUuidAddress Uuid address
 ** \param[in] ubLen Uuid length
 **
 ** \return return status
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomCheckUuid(u8* pubUuidAddress,u8 ubLen)
{
    OSC_PARAM_UNUSED(pubUuidAddress);
    OSC_PARAM_UNUSED(ubLen);
    return PROG_E_OK;
}

/** \brief Callback used to check the SigningInfo (SigningName and SigningKeyIdentifier)
 **
 ** \param[in] pubSigningInfoAddress SigningInfo address
 ** \param[in] ubLen SigningInfo length
 **
 ** \return return status
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomCheckSigningInfo(u8* pubSigningInfoAddress,u8 ubLen)
{
    OSC_PARAM_UNUSED(pubSigningInfoAddress);
    OSC_PARAM_UNUSED(ubLen);
    return PROG_E_OK;
}
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgVCC'))"!]
/** \brief Get ESS validity status
 **
 ** Callback is called: Before using information from ESS
 **
 ** Callback shall implement: ESS validity status
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK ESS is valid
 ** \retval PROG_E_NOT_OK is not valid
 **/
tProgStatus Prog_GetEssValidityStatus(void)
{
    return PROG_E_NOT_OK;
}
/** \brief Get ESS number of logical block
 **
 ** Callback is called: On RD or Erase routine to identify the downloaded block
 **
 ** Callback shall implement: return number of logical block in ESS
 **
 ** \param[out] pubBlockNbr number of logical block in ESS
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK Information is available
 ** \retval PROG_E_NOT_OK Information is not available
 **/
tProgStatus Prog_GetEssLogicalBlockNbr(u8* pubBlockNbr)
{
    OSC_PARAM_UNUSED(pubBlockNbr);
    return PROG_E_NOT_OK;
}
/** \brief Get ESS logical block Identifier
 **
 ** Callback is called: On RD or Erase routine to identify the downloaded block
 **
 ** Callback shall implement: return identifier of the request logical block in ESS
 **
 ** \param[in] ubBlockIndex Block identifier
 ** \param[out] pulBlockIdent identifier of the request logical block in ESS
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK Information is available
 ** \retval PROG_E_NOT_OK Information is not available
 **/
tProgStatus Prog_GetEssLogicalBlockId(u8 ubBlockIndex, u16* pulBlockIdent)
{
    OSC_PARAM_UNUSED(ubBlockIndex);
    OSC_PARAM_UNUSED(pulBlockIdent);
    return PROG_E_NOT_OK;
}
/** \brief Get ESS logical block address
 **
 ** Callback is called: On RD or Erase routine to identify the downloaded block
 **
 ** Callback shall implement: return address of the request logical block in ESS
 **
 ** \param[in] ubBlockIndex Block identifier
 ** \param[out] pulBlockAddr address of the request logical block in ESS
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK Information is available
 ** \retval PROG_E_NOT_OK Information is not available
 **/
tProgStatus Prog_GetEssLogicalBlockStartAddr(u8 ubBlockIndex, u32* pulBlockAddr)
{
    OSC_PARAM_UNUSED(ubBlockIndex);
    OSC_PARAM_UNUSED(pulBlockAddr);
    return PROG_E_NOT_OK;
}
/** \brief Get ESS logical block Length
 **
 ** Callback is called: On RD or Erase routine to identify the downloaded block
 **
 ** Callback shall implement: return length of the request logical block in ESS
 **
 ** \param[in] ubBlockIndex Block identifier
 ** \param[out] pulBlockLength length of the request logical block in ESS
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK Information is available
 ** \retval PROG_E_NOT_OK Information is not available
 **/
tProgStatus Prog_GetEssLogicalBlockLength(u8 ubBlockIndex, u32* pulBlockLength)
{
    OSC_PARAM_UNUSED(ubBlockIndex);
    OSC_PARAM_UNUSED(pulBlockLength);
    return PROG_E_NOT_OK;
}
/** \brief Get ESS logical block VBT address
 **
 ** Callback is called: On RD to get Verification Block Table location
 **
 ** Callback shall implement: return address of the verification block table of the request logical block in ESS
 **
 ** \param[in] ubBlockIndex Block identifier
 ** \param[out] pulVBTAddress address of the verification block table of the request logical block in ESS
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK Information is available
 ** \retval PROG_E_NOT_OK Information is not available
 **/
tProgStatus Prog_GetEssLogicalBlockVerifTable(u8 ubBlockIndex, u32* pulVBTAddress)
{
    OSC_PARAM_UNUSED(ubBlockIndex);
    OSC_PARAM_UNUSED(pulVBTAddress);
    return PROG_E_NOT_OK;
}

/** \brief Get ESS VBT Length
 **
 ** Callback is called: On RD to get Verification Block Table location length
 **
 ** Callback shall implement: return length of the verification block table of the request logical block in ESS
 **
 ** \param[out] pulVBTLength length of the verification block table in ESS
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK Information is available
 ** \retval PROG_E_NOT_OK Information is not available
 **/
tProgStatus Prog_GetEss_VBTLength(u32* pulVBTLength)
{
    OSC_PARAM_UNUSED(pulVBTLength);
    return PROG_E_OK;
}

/** \brief Get APPL/CALIB VBT Length
 **
 ** Callback is called: On RD to get Verification Block Table location length for application and calibration
 **
 ** Callback shall implement: return length of the verification block table of the request logical block in APPL/CALIB
 **
 ** \param[in]  ubBlockIndex index of the logical block in Prog plugin configuration
 ** \param[out] pulVBTLength length of the verification block table of Application and calibration
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK Information is available
 ** \retval PROG_E_NOT_OK Information is not available
 **/
tProgStatus Prog_GetAPPL_VBTLength(u8 ubBlockIndex, u32* pulVBTLength)
{
    OSC_PARAM_UNUSED(ubBlockIndex);
    OSC_PARAM_UNUSED(pulVBTLength);
    return PROG_E_NOT_OK;
}


/** \brief Get ESS VBT address
 **
 ** Callback is called: On RD to get Verification Block Table location
 **
 ** Callback shall implement: return address of the verification block table of the request logical block in ESS
 **
 ** \param[out] pulVBTAddress address of the verification block table of the request logical block in ESS
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK Information is available
 ** \retval PROG_E_NOT_OK Information is not available
 **/
tProgStatus Prog_GetEssVerifTable(u32* pulVBTAddress)
{
    OSC_PARAM_UNUSED(pulVBTAddress);
    return PROG_E_OK;
}
/** \brief Get the address of the jump to the application
 **
 ** Callback is called: On switching to application mode
 **
 ** Callback shall implement: get the application start address from the ESS
 **
 ** \param[out] ulApplicationStartAddress Application start address
 **
 ** \return void
 **/
void Prog_GetEssApplicationStartAddress(u32* ulApplicationStartAddress)
{
    OSC_PARAM_UNUSED(ulApplicationStartAddress);
}
/** \brief API that invalidate the logical block
 **
 ** Callback is called: On Erase routine reception
 **
 ** Callback shall implement: 1- customer code that shall be executed before
 **                           performing an erasing of a logical block
 **
 **                           2- It shall invalidate the logical block that will be erased
 **                           to make sure no jump to the application will be done if an error occurred
 **                           and the application is not fully erased or reprogrammed
 **
 ** \param[in] ubBlockId The ID of the block that will be erased
 **
 ** \return Result application invalidation
 ** \retval PROG_E_OK Treatment finish successfully
 ** \retval PROG_E_NOT_OK Error happened during treatment
 **/
tProgStatus PROG_InvalidateBlock(u8 ubBlockId)
{
    OSC_PARAM_UNUSED(ubBlockId);
    return PROG_E_OK;
}
/** \brief Get the start address of the ESS
 **
 ** Callback is called: On calculating MAC
 **
 ** Callback shall implement: get the start address of the ESS
 **
 ** \param[out] ulEssStartAddress ESS start address
 **
 ** \return void
 **/
void Prog_GetEssStartAddr(u32* ulEssStartAddress)
{
    OSC_PARAM_UNUSED(ulEssStartAddress);
}

/** \brief Get the length of the ESS
 **
 ** Callback is called: On calculating MAC of ESS
 **
 ** \param[out] ulEssLength ESS length
 **
 ** Callback shall implement: get the length of the ESS
 **
 ** \return void
 **/
void Prog_GetEssLength(u32* ulEssLength)
{
    OSC_PARAM_UNUSED(ulEssLength);
}

/** \brief Check if the production key is written or not
 **
 ** Callback is called: before writing or reading the production key
 **
 **
 ** Callback shall implement: check if the key exists or not
 **
 ** \return boolean TRUE : Key exists, FALSE : Key does not exist
 **/
boolean Prog_CustomIsProdKeyPresent(void)
{
    return TRUE;
}

/** \brief Get the checksum of the key
 **
 ** Callback is called: On receiving RDBI of the production key
 **
 ** \param[out] aubKeyChecksum key checksum
 **
 ** Callback shall implement: get the key checksum from the non volatile memory
 **
 ** \return void
 **/
void Prog_CustomReadKeyChecksum(u8* aubKeyChecksum)
{
    OSC_PARAM_UNUSED(aubKeyChecksum);
}

/** \brief write the production key used in signature verification
 **
 ** Callback is called: On receiving WDBI for the production key
 **
 ** \param[in] ulExponent key exponent
 ** \param[in] aubModulus key modulus
 ** \param[in] aubKeyChecksum key checksum
 **
 ** Callback shall implement: write the key and its checksum in non volatile memory
 **
 ** \return void
 **/
void Prog_CustomWriteKey(u32 ulExponent, u8* aubModulus, u8* aubKeyChecksum)
{
    OSC_PARAM_UNUSED(ulExponent);
    OSC_PARAM_UNUSED(aubModulus);
    OSC_PARAM_UNUSED(aubKeyChecksum);
}

/** \brief Get the result of the certificate verification
 **
 ** Callback is called: On checkMemory request
 **
 ** Callback shall implement: the certificate verification or its result
 **
 ** \return eProgStatus success of the certificate verification
 ** \retval PROG_E_OK Certificate verification passed
 ** \retval PROG_E_NOT_OK Certificate verification failed
 **/
tProgStatus  PROG_CustomCheckCertificateVerification(void)
{
    return PROG_E_OK;
}
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgFord'))"!]
/** \brief API that invalidate the logical block
 **
 ** Callback is called: On Erase routine reception
 **
 ** Callback shall implement: 1- customer code that shall be executed before
 **                           performing an erasing of a logical block
 **
 **                           2- It shall invalidate the logical block that will be erased
 **                           to make sure no jump to the application will be done if an error occurred
 **                           and the application is not fully erased or reprogrammed
 **
 ** \param[in] ubBlockId The ID of the block that will be erased
 **
 ** \return Result application invalidation
 ** \retval PROG_E_OK Treatment finish successfully
 ** \retval PROG_E_NOT_OK Error happened during treatment
 **/
tProgStatus PROG_InvalidateBlock(u8 ubBlockId)
{
    OSC_PARAM_UNUSED(ubBlockId);
    return PROG_E_OK;
}

/** \brief Get logical block VS address
 **
 ** Callback is called: On RD to get Verification Structure Address
 **
 ** Callback shall implement: return address of the verification Structure of the requested logical block
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK Return value shall always be E_OK
 **/
tProgStatus Prog_GetLogicalBlockVerifStructure(u8 ubBlockIndex, u32* pulVSAddress)
{
    OSC_PARAM_UNUSED(ubBlockIndex);
    OSC_PARAM_UNUSED(pulVSAddress);
    return PROG_E_OK;
}

/** \brief Get logical block Signature address
 **
 ** Callback is called: On request Validate Application to get address of Signature of the requested logical block
 **
 ** Callback shall implement: return adress of the Signature
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK Information is available
 ** \retval PROG_E_NOT_OK Information is not available
 **/
tProgStatus Prog_GetLogicalBlockSignature(u8 ubBlockIndex, u32* pulSignatureAddress)
{
    OSC_PARAM_UNUSED(ubBlockIndex);
    OSC_PARAM_UNUSED(pulSignatureAddress);
    return PROG_E_OK;
}

/** \brief The API shall be used during validate application execution to validate the blocks in verification structure
 **
 ** Callback is called: On request Validate Application to validate VS blocks
 **
 ** Callback shall implement: return VS blocks status and m_ubValidateMemoryStatus shall also be updated to the error code
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK VS blocks are correct
 ** \retval PROG_E_NOT_OK VS blocks are mismatch
 **/
tProgStatus PROG_CustomCheckVSBlocksMismatch(u8* pubValidateMemoryStatus)
{
    OSC_PARAM_UNUSED(pubValidateMemoryStatus);
    return PROG_E_OK;
}
[!ENDIF!]

[!IF "General/Dual_Memory_Bank_Used = 'true'"!]
/** \brief Calculate the write address on inactive memory bank
 **
 ** \param[in] ulAddr Write address on active memory bank
 **
 ** \return Calculated address on inactive memory bank
 **/
u32 PROG_CustomCalcInactiveBankWriteAddr(u32 ulAddr)
{
    OSC_PARAM_UNUSED(ulAddr);

    return 0U;
}

/** \brief Calculate the read address on active memory bank
 **
 ** \param[in] ulAddr Address on active memory bank
 **
 ** \return Calculated address on active bank
 **/
u32 PROG_CustomCalcActiveBankReadAddr(u32 ulAddr)
{
    OSC_PARAM_UNUSED(ulAddr);

    return 0U;
}

/** \brief Calculate the read address on inactive memory bank
 **
 ** \param[in] ulAddr Address on active memory bank
 **
 ** \return Calculated address on inactive bank
 **/
u32 PROG_CustomCalcInactiveBankReadAddr(u32 ulAddr)
{
    OSC_PARAM_UNUSED(ulAddr);

    return 0U;
}

[!ENDIF!]

[!IF "as:modconf('BM')/Security/SecureBoot/BMSecureBootWithHsm = 'true'"!]
/** \brief ask HSM to update the SecureBoot checksum of a memory block
 **
 ** Callback is called: during the routine control check memory, update the MAC value of the given memory block
 **
 ** \param[in] uwBlockId
 ** \param[in] aubMacExpctdSign
 ** \param[in] aubSignLength
 ** \param[in] ulbankOffset
 ** \param[in,out] pubMemoryAddress
 ** \param[in] ulMemorySize
 **
 ** Callback shall implement: call the APIs provided by HSM to update the SecureBoot checksum of the memory block.
 ** NOTE:
 ** 1. ulbankOffset is inactive bank address offset when dual bank feature is enabled otherwise it will be Zero always.
 ** 2. Public keyshould be loaded into D-Flash in DER encoding format incase of asymmetric cryptographic MAC verification .
 **
 ** \return Result of the job
 ** \retval PROG_E_OK     the job is finished correctly
 ** \retval PROG_E_NOT_OK the job fails
 ** \retval PROG_E_BUSY   the job is still on-going
 **/
tProgStatus PROG_CustomHsmUpdateBlock(u16 uwBlockId, u8 *aubMacExpctdSign, u16 aubSignLength, u32 ulbankOffset, u8 *pubMemoryAddress, u32 ulMemorySize)
{
    OSC_PARAM_UNUSED(uwBlockId);
    OSC_PARAM_UNUSED(aubMacExpctdSign);
    OSC_PARAM_UNUSED(aubSignLength);
    OSC_PARAM_UNUSED(ulbankOffset);
    OSC_PARAM_UNUSED(pubMemoryAddress);
    OSC_PARAM_UNUSED(ulMemorySize);
    return PROG_E_OK;
}
/** \brief ask HSM to update the SecureBoot checksum of a memory block
 **
 ** Callback is called: during the routine control check memory, update the MAC value of the given memory block
 **
 ** \param[in] uwBlockId
 ** \param[in,out] pubMemoryAddress
 ** \param[in] ulMemorySize
 **
 ** Callback shall implement: call the APIs provided by HSM to Initialize the update operation the SecureBoot checksum of the memory block
 **
 ** \return Result of the job
 ** \retval PROG_E_OK     the job is finished correctly
 ** \retval PROG_E_NOT_OK the job fails
 ** \retval PROG_E_BUSY   the job is still on-going
 **/
tProgStatus PROG_CustomHsmUpdateInitBlock(u16 uwBlockId, u8 *pubMemoryAddress, u32 ulMemorySize)
{
    OSC_PARAM_UNUSED(uwBlockId);
    OSC_PARAM_UNUSED(pubMemoryAddress);
    OSC_PARAM_UNUSED(ulMemorySize);
    return PROG_E_OK;
}

/** \brief notify the user that the SecureBoot checksum of the memory block is updated successfully or not
 **
 ** Callback is called: during the routine control check memory, when the memory updating process is completed.
 **
 ** \param[in] ubJobResult
 **
 ** Callback shall implement: keep the job result somewhere if necessary
 **
 ** \return void
 **/
void PROG_CustomHsmUpdateFinish(tProgStatus ubJobResult)
{
    OSC_PARAM_UNUSED(ubJobResult);
}
[!ENDIF!]

[!IF "((node:exists(as:modconf('ProgFord'))) and (Segments/*/Partition_Type = 'PROG_HSM_PARTITION'))"!]
/** \brief ask HSM to update the HSM Firmware
 **
 ** Callback is called: during the routine control check memory, to update the HSM Firmware blocks.
 **
 ** \param[in] uwBlockId
 ** \param[in,out] pubMemoryAddress
 ** \param[in] ulMemorySize
 **
 ** Callback shall implement: call the APIs provided by HSM to update the HSM Firmware.
 **
 ** \return Result of the job
 ** \retval PROG_E_OK     the job is finished correctly
 ** \retval PROG_E_NOT_OK the job fails
 ** \retval PROG_E_BUSY   the job is still on-going
 **/
tProgStatus PROG_CustomHsmFwUpdateBlock(u16 uwBlockId, u8 *pubMemoryAddress, u32 ulMemorySize)
{
    OSC_PARAM_UNUSED(uwBlockId);
    OSC_PARAM_UNUSED(pubMemoryAddress);
    OSC_PARAM_UNUSED(ulMemorySize);
    return PROG_E_OK;
}
/** \brief ask HSM to update the HSM Firmware
 **
 ** Callback is called: during the routine control check memory, to initialize the HSM Firmware update process.
 **
 ** \param[in] uwBlockId
 ** \param[in,out] pubMemoryAddress
 ** \param[in] ulMemorySize
 **
 ** Callback shall implement: call the APIs provided by HSM to Initialize the update operation during the HSM Firmware update
 **
 ** \return Result of the job
 ** \retval PROG_E_OK     the job is finished correctly
 ** \retval PROG_E_NOT_OK the job fails
 ** \retval PROG_E_BUSY   the job is still on-going
 **/
tProgStatus PROG_CustomHsmFwUpdateInitBlock(u16 uwBlockId, u8 *pubMemoryAddress, u32 ulMemorySize)
{
    OSC_PARAM_UNUSED(uwBlockId);
    OSC_PARAM_UNUSED(pubMemoryAddress);
    OSC_PARAM_UNUSED(ulMemorySize);
    return PROG_E_OK;
}

/** \brief notify the user that the HSM Firmware is updated successfully or not
 **
 ** Callback is called: during the routine control check memory, when the HSM Firmware updating process is completed.
 **
 ** \param[in] void
 **
 ** Callback shall implement: keep the job result somewhere if necessary
 **
 ** \return Result of the job
 ** \retval PROG_E_OK     the job is finished correctly
 ** \retval PROG_E_NOT_OK the job fails
 ** \retval PROG_E_BUSY   the job is still on-going
 **/
tProgStatus PROG_CustomHsmFwUpdateFinish(void)
{
    return PROG_E_OK;
}
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgJLR')) or (node:exists(as:modconf('ProgFCA')) and (as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid'))"!]
[!VAR "SIGNATUREVERIFCATIONENABLED"="'false'"!]
[!LOOP "Segments/ *"!]
    [!IF "SignatureVerification = 'true'"!]
        [!VAR "SIGNATUREVERIFCATIONENABLED"="'true'"!]
    [!ENDIF!]
[!ENDLOOP!]
[!IF "(not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))) or ($SIGNATUREVERIFCATIONENABLED = 'true')"!]
/** \brief Callback to fetch the Signature verification Data start/end address and Signature start address
 **
 ** Callback is called: during the routine control check programming dependency request
 **
 ** \param[in,out] ulStartAddress
 ** \param[in,out] ulEndAddress
 ** \param[out] ulSignatureStartAddress
 **
 ** Callback shall implement: Updating of the signature verification data start/end and signature start address
 **
 ** \return void
 **/
void PROG_CustomGetVerificationParameters(u32 * ulStartAddress, u32 * ulEndAddress ,u32 * ulSignatureStartAddress)
{
    OSC_PARAM_UNUSED(ulStartAddress);
    OSC_PARAM_UNUSED(ulEndAddress);
    OSC_PARAM_UNUSED(ulSignatureStartAddress);
}
[!ENDIF!]
[!ENDIF!]

[!IF "as:modconf('Prog')/Decryption/Enable_Csm_Decryption = 'true'"!]
/** \brief Get initialization vector and its length for decryption
 **
 ** \param[out] pubInitVect pointer to IV array location
 ** \param[out] pulInitVectLength to IV length location
 **
 ** Callback shall implement: Retrieve the IV and its length for decryption
 **
 **/
void PROG_CustomDecryptGetInitVector(const u8** pubInitVect, u32 * pulInitVectLength)
{
    OSC_PARAM_UNUSED(pubInitVect);
    OSC_PARAM_UNUSED(pulInitVectLength);
}

/** \brief Get symetrical decryption key and its length
 **
 ** \param[out] pubKey pointer to key array location
 ** \param[out] pulKeyLength pointer to key length location
 **
 ** Callback shall implement: Retrieve the symetrical decryption key and its length
 **
 **/
void PROG_CustomGetSymDecryptionKey(const u8** pubKey, u32 * pulKeyLength)
{
    OSC_PARAM_UNUSED(pubKey);
    OSC_PARAM_UNUSED(pulKeyLength);
}
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgJLR'))"!]
/** \brief Callback performing the update of Software Signing Certificate/Software Signing Public Key for Signature verification. 
 **
 ** Callback is called: While Software Signing Certificate/Software Signing Public Key is to be updated for Signature verification.
 **
 ** Callback shall implement: Call functions for certificate update / Copy public key as below.
 **                           The 5th byte in the request shall be checked for Type
 **
 ** For Type : 01- Software Signing Certificate
 **
 **     Length of request : 4bytes of the service + 1 byte for the Type(01) + Certificate Size
 **
 **     Call functions for certificate update, parsing and verification that shall provide a status (certificate update pass or fail) and also the public Key.
 **      If Certificate update passed : copy the retrieved public key to the variable m_aubPublicModulus, update length and status 0x02 for the response
 **      If Certificate update failed : update length and status 0x3 for the response.
 **
 ** For Type : 02- Software Signing Public Key
 **
 **     Length of request : 4bytes of the service + 1 byte for the Type(02) + Public Key Size
 **
 **     Copy the public Key to the variable m_aubPublicModulus and the length and respective status shall be updated for the response.
 **
 **
 ** \param[in,out] puwLen received length pointer (in : length of request, out : Shall be updated with length of response) 
 ** \param[in,out] aubUdsData received data pointer to Diagnostic buffer (in : Request data, out : Response data)
 **
 **                    Request of Routine Control :
 **                           1. aubUdsData[0]: Shall contain Service ID for Routine Control
 **                           2. aubUdsData[1]: Shall contain Sub function for Routine Control
 **                           3. aubUdsData[2]: Shall contain Routine Control Identifier (MSB)
 **                           4. aubUdsData[3]: Shall contain Routine Control Identifier (LSB)
 **                           5. aubUdsData[4]: Shall contain the type parameter for certificate or the public key.
 **                           6. aubUdsData[5]: Shall contain first byte certificate data or the public key data
 **                           :
 **                           : 
 **                           n. aubUdsData[n]: Shall contain last byte certificate data or the public key data
 **
 **                    Response of Routine Control (Positive) :
 **                           1. aubUdsData[0]: Shall contain Service ID for Routine Control + 0x40
 **                           2. aubUdsData[1]: Shall contain Sub function for Routine Control
 **                           3. aubUdsData[2]: Shall contain Routine Control Identifier (MSB)
 **                           4. aubUdsData[3]: Shall contain Routine Control Identifier (LSB)
 **                           5. aubUdsData[4]: Shall contain the byte 0x4A.
 **                           6. aubUdsData[5]: Shall contain status of update 0x02 - Update of Certificate/Public Key Accepted/Success or
 **                                             Shall contain status of update 0x03 - Update of Certificate/Public Key Rejected/Failed
 **
 ** \return eStatus : Diag response to routine request
 ** \return UDS_ACK    - Positive response for routine request
 ** \return UDS_NRC_13 - NRC13 (Incorrect message length) for routine request
 ** \return UDS_NRC_31 - NRC31 (Request out of range) for routine request
 **
 **/
tUdsStatus PROG_CustomUpdateCertAsymPublicKey(u16 *puwLen, u8 *aubUdsData)
{
    OSC_PARAM_UNUSED(puwLen);
    OSC_PARAM_UNUSED(aubUdsData);

    return UDS_ACK;
}
[!IF "(as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL') or (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL') or (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL')"!]
/** \brief Callback for the VDS table access.
 **
 ** Callback is called:
 ** 1. During processing of the UDS Erase or Reset request for clearing/Erasing VDS table
 ** 2. During processing of the UDS RTE request for Updating VDS table
 ** 3. During processing of the UDS Routine Control for Submit Signature request for Reading VDS table
 **
 ** Callback shall be implemented: to store, clear, read and fetch segment Id based on the VDS address of the VDS
 ** table.
 **
 **
 ** \param[in,out] pstVDSlayout is the pointer to the VDS buffer
 ** \param[in,out] pubSegmentId is the pointer to the corresponding Segment ID
 ** \param[in]     ubVDSaccesstype is the VDS access type (Read/Update/Clear/fetch ID) specifier
 ** \param[in,out] pubFirstSegment is the pointer to the first Segment index for logical block
 **
 ** \return tProgStatus : status of the VDS access
 ** \return PROG_E_OK
 ** \return PROG_E_NOT_OK
 **
 **/
tProgStatus PROG_CustomVDStable_update(tVDSlayout * pstVDSlayout,u8 * pubSegmentId,u8 * pubFirstSegment, u8 ubVDSaccesstype)
{
	tProgStatus eStatus;
	OSC_PARAM_UNUSED(pstVDSlayout);
	OSC_PARAM_UNUSED(pubSegmentId);
	OSC_PARAM_UNUSED(pubFirstSegment);
	eStatus = PROG_E_OK;
	switch(ubVDSaccesstype)
	{
	case PROG_VDSUPDATE_CLEAR:
		/* Clear the VDS table from the Memory for the requested pubSegmentId*/
		break;
	case PROG_VDSUPDATE_STORE:
		/* Store the VDS table from the provided pstVDSlayout buffer to the
		 * desired Memory type and address for the requested pubSegmentId */
		break;
	case PROG_VDSUPDATE_GETSEGID_BYADR:
		/* Update the pubSegmentId value with the segmentId of the Segment for
		 * the given VDS address- pstVDSlayout*/
		break;
	case PROG_VDSUPDATE_READVDS:
		/* Read/Copy the VDS table from the memory to the pstVDSlayout buffer for
		 * the requested pubSegmentId */
		break;

	default:
		/* Not supported Access type */
		break;
	}
    return eStatus;
}
[!ENDIF!]
[!ENDIF!]

[!IF "as:modconf('Prog')/Segments/ */Partition_Type = 'PROG_BLU_APP_PARTITION' 
   or as:modconf('Prog')/Segments/ */Partition_Type = 'PROG_BLU_CAL_PARTITION'
   or as:modconf('Prog')/Segments/ */Partition_Type = 'PROG_BLU_PARTITION'"!]
/** \brief This API is called to set a flag which indicate that the BLU donwload is in progress
 **
 ** Callback is called: After a BLU sucessfull download
 **
 ** \param[in] ubBLUDownload indicating if BLU download is in progress
 **
 ** Callback shall implement: set the flag in a non-volatile memory
 **
 ** \return void
 **
 **/
void PROG_CustomSetBLUDownloadInProgress(tProgBoolean ubBLUDownload)
{
    OSC_PARAM_UNUSED(ubBLUDownload);
}

/** \brief This API is called to get a flag which indicate if the BLU donwload is in progress
 **
 ** Callback is called: during the reset to check if BLU donwload is in progress, if true resume the BLU download
 **
 ** Callback shall implement: read of the flag from a non-volatile memory
 **
 ** \return BLU Download status
 ** \retval PROG_TRUE if BLU Download is in progress
 ** \retval PROG_FALSE if BLU Download isn't in progress
 **/
tProgBoolean PROG_CustomIsBLUDownloadInProgress(void)
{
    return PROG_TRUE;
}

/** \brief This API is called to check if the current block/segment is BLUpdater
 **
 ** Callback is called: After a successful or unsuccessful block/segment verification of the BLUpdater
 **
 ** Callback shall implement: read on the flashed data the area of the BLU marker and check it if it matches the BLU pattern
 **
 ** \param[in] ubLogicalBlockId The id of the logical block for which the presence of BLU pattern is checked
 ** \param[in] ubLogicalSegmentId The id of the logical segment  for which the presence of BLU pattern is checked
 **            (ignore if the full logical block is verified)
 **
 ** \return BLU Pattern presence
 ** \retval PROG_TRUE if BLU Pattern is present
 ** \retval PROG_FALSE if BLU Pattern is absent
 **/
tProgBoolean PROG_CustomIsBLUPatternPresent(u8 ubLogicalBlockId, u8 ubLogicalSegmentId)
{
    OSC_PARAM_UNUSED(ubLogicalBlockId);
    OSC_PARAM_UNUSED(ubLogicalSegmentId);
    return PROG_TRUE;
}

[!IF "node:exists(as:modconf('ProgOEMInd'))"!]
/** \brief Callback used for BLUpdater download, called after comparing the expected CRC and the calculated one.
 **
 ** Callback is called: After a successful or unsuccessful block/segment verification of the BLUpdater
 **
 ** Callback shall implement: update of the logical block validity status
 **
 ** \param[in] ubCompareSuccess TRUE if the 2 elements of the comparison are identical
 **
 ** \return state
 ** \retval PROG_E_OK Treatment finished successfully
 ** \retval PROG_E_NOT_OK Error happened during treatment
 **/
/*---------------------------{PROG_CustomSetBLUVerificationSuccess}----------------------------*/
tProgStatus PROG_CustomSetBLUVerificationSuccess(tProgBoolean ubCompareSuccess)
{
    OSC_PARAM_UNUSED(ubCompareSuccess);
    return PROG_E_OK;
}
[!ENDIF!]
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgPSA'))"!]
/** \brief Callback setting the ECU status value
 **
 ** Callback is called: at reception of erase memory or end programming
 **
 ** \param[in] ubEcuStatusValue New ECU status value to be set
 **
 ** Callback shall implement: Update the value of the ECU Status
 **
 ** \return void
 **/
void PROG_CustomSetECUStatus(u8 ubEcuStatusValue)
{
    OSC_PARAM_UNUSED(ubEcuStatusValue);
}

/** \brief Callback getting the ECU status value
 **
 ** Callback is called: at bootloader start up
 **
 ** \param[in,out] pubEcuStatus Current ECU status
 **
 ** Callback shall implement: Gets the value of the ECU Status
 **
 ** \return void
 **/
void PROG_CustomGetECUStatus(u8 *pubEcuStatus)
{
    OSC_PARAM_UNUSED(pubEcuStatus);
}

/** \brief Allow to write the application key and perform a byte by byte compare
 **
 ** Callback is called: during transfer data of the application key
 **
 ** \param[in] pubData buffer of the application key data to write
 ** \param[in] ubDataLength length of the application key
 **
 ** Callback shall implement: the writing of the application key into memory 
 **                           and once it is written perform a comparison byte by byte
 **
 ** \return Result of the job
 ** \retval PROG_E_OK     the job is finished correctly
 ** \retval PROG_E_NOT_OK the job fails
 ** \retval PROG_E_BUSY   the job is still on-going
 **/
tProgStatus PROG_CustomWriteKeyAppli(u8 * pubData, u8 ubDataLength)
{
    OSC_PARAM_UNUSED(pubData);
    OSC_PARAM_UNUSED(ubDataLength);
    return PROG_E_OK;
}

/** \brief Allow to write the log zone (ZI) and perform a byte by byte compare
 **
 ** Callback is called: during transfer data of the log zone (ZI)
 **
 ** \param[in] pubData buffer of the log zone (ZI) data to write
 ** \param[in] ubDataLength length of the log zone (ZI)
 **
 ** Callback shall implement: the writing of the log zone (ZI) into memory
 **                           and once it is written perform a comparison byte by byte
 **
 ** \return Result of the job
 ** \retval PROG_E_OK     the job is finished correctly
 ** \retval PROG_E_NOT_OK the job fails
 ** \retval PROG_E_BUSY   the job is still on-going
 **/
tProgStatus PROG_CustomWriteZI(u8 * pubData, u8 ubDataLength)
{
    OSC_PARAM_UNUSED(pubData);
    OSC_PARAM_UNUSED(ubDataLength);
    return PROG_E_OK;
}

/** \brief Checks the status of memory writing
 **
 ** Callback is called: during transfer data of application key or the log zone writing
 **
 ** \param[in] ubLogicalMarker logical marker for which the writing status is requested value [0x83 or 0x88]
 **
 ** Callback shall implement: return the status of memory access after requesting the writing
 **
 ** \return Result of the job
 ** \retval PROG_E_OK     the job is finished correctly
 ** \retval PROG_E_NOT_OK the job fails
 ** \retval PROG_E_BUSY   the job is still on-going
 **/
tProgStatus PROG_CustomGetWriteJobResult(u8 ubLogicalMarker)
{
    OSC_PARAM_UNUSED(ubLogicalMarker);
    return PROG_E_OK;
}

/** \brief Checks the available space for writing ZI
 **
 ** Callback is called: during transfer data of log zone writing
 **
 ** Callback shall implement: verification if enough space is available for writing log zone (ZI)
 **
 ** \return Result of the check
 ** \retval PROG_E_OK     enough space is available for writing ZI
 ** \retval PROG_E_NOT_OK space not sufficient for writing ZI
 **/
tProgStatus PROG_CustomCheckZIAvailableSpace(void)
{
    return PROG_E_OK;
}

/** \brief Allows to write the log save marking byte
 **
 ** Callback is called: if error occurs on writing the log zone (ZI)
 **
 ** \param[in] ubNewLogSaveMarkingByte new value of the log save marking
 **
 ** Callback shall implement: the update of the log zave marking byte into NVM
 **
 ** \return Result of the job
 ** \retval PROG_E_OK     the job is finished correctly
 ** \retval PROG_E_NOT_OK the job fails
 ** \retval PROG_E_BUSY   the job is still on-going
 **/
tProgStatus PROG_CustomUpdateLogSaveMarkingByte(u8 ubNewLogSaveMarkingByte)
{
    OSC_PARAM_UNUSED(ubNewLogSaveMarkingByte);
    return PROG_E_OK;
}

/** \brief Allow to read the application key
 **
 ** Callback is called: upon receiving an SA request with sub-function sendKey
 **
 ** \param[out] aubKeyAppli buffer of the application key data to write
 **
 ** Callback shall implement: the reading of the application key
 **
 ** \return Result of the job
 ** \retval PROG_E_OK     the job is finished correctly
 ** \retval PROG_E_NOT_OK the job fails
 **/
tProgStatus PROG_CustomReadKeyAppli(u16 *aubKeyAppli)
{
    OSC_PARAM_UNUSED(aubKeyAppli);
    return PROG_E_OK;
}

/** \brief Stores the size of the latest downloaded segments
 **
 ** Callback is called: upon receiving a request transfer exit for application and/or calibration
 **
 **
 ** \param[in] pulSegSize address to the buffer to save in non-volatile memory
 ** \param[in] ubSegmentId segment ID in prog plugin configuration
 **
 ** Callback shall implement: storage of the size of the downloaded segments
 **
 ** \return void
 **/
void PROG_CustomStoreDownloadedSegmentSize(u32 * pulSegSize, u8 ubSegmentId)
{
    OSC_PARAM_UNUSED(pulSegSize);
    OSC_PARAM_UNUSED(ubSegmentId);
}

/** \brief Retrieve the size of the latest downloaded segments 
 **
 ** Callback is called: upon receiving a request download for application and/or calibration
 **
 ** \param[out] pulSegSize address to the buffer to fill
 ** \param[in]  ubSegmentId segment ID in prog plugin configuration
 **
 ** Callback shall implement: retrieving of size of the downloaded segments
 **
 ** \return void
 **/
void PROG_CustomGetDownloadedSegmentSize(u32 * pulSegSize, u8 ubSegmentId)
{
    OSC_PARAM_UNUSED(pulSegSize);
    OSC_PARAM_UNUSED(ubSegmentId);
}
[!ENDIF!]

[!IF "((node:exists(Security/ProgCsmReferences/SignatureVerification/Allow2CustomCsmStartPreprocess)) and (node:value(Security/ProgCsmReferences/SignatureVerification/Allow2CustomCsmStartPreprocess) = 'true')) or
((node:exists(Security/Allow2CustomCsmStartPreprocess)) and (node:value(Security/Allow2CustomCsmStartPreprocess) = 'true')) or
((node:exists(Decryption/Allow2CustomCsmStartPreprocess)) and (node:value(Decryption/Allow2CustomCsmStartPreprocess) = 'true')) or
((node:exists(GM/ProgCsmReferences/Allow2CustomCsmStartPreprocess)) and (node:value(Allow2CustomCsmStartPreprocess) = 'true'))"!]
/** \brief This Optional Callback used for the Custom Csm Implementation, called before the Csm Start mode of operation.
 **
 ** Callback is called: Before the start of Csm operation, after all successful job cancel operations(if cancellation is enabled)
 **
 ** Callback shall implement: the Custom operation such as Key DER encoding or set IV or just the notification about the start of the 
 ** crypto operation or any custom operation needed for the Integration.
 **
 ** \param[in,out] ubKeyPtr is the pointer to the address of the key buffer
 ** \param[in]     ulCsmJobId is the Csm Job ID for which the key pointer could be updated or read
 **
 ** \return state
 ** \retval E_OK Treatment finished successfully
 ** \retval E_NOT_OK Error happened during treatment
 **/
Csm_ReturnType PROG_CustomCsmStrtPreproc(const u8** ubKeyPtr, u32 ulCsmJobId)
{
    OSC_PARAM_UNUSED(ubKeyPtr);
    OSC_PARAM_UNUSED(ulCsmJobId);
    return E_OK;
}
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgFord'))"!]

/** \brief This Optional Callback used for the Custom Implementation to get Assymetric Public key in DER Format
 **  User needs to consider following points while implementing the callback
 **         First 4 bytes of pointer has length information
 **		    User needs to consider the Key information from 5 th byte
 **		    If the CSM used is AR4.3
 **               Then 4 byte exponent is present in next 16 bytes and Modulus is present in next 1024 bytes
 **               Exponent and Modulus to be extracted from respective positions before encoding in DER Format
 **         If the CSM used is AR4.0
 **               4 bytes :Length of Exponent
 **				  4 bytes :Exponent
 **               256 bytes : No data
 **				  4 bytes :Length of Modulus
 **				  256 bytes:Modulus in little endian format
 ** Callback is called: Before the start of hash calculation and after Assymetrical Public Key is retrieved
 **
 ** Callback shall implement: the Custom operation such as Key DER encoding
 **
 ** \param[in,out] ubKeyPtr is the pointer to the address of the key buffer with 
                     first 4 bytes as length.It will hold the Public Key in DER Format
					 
 
 **
 ** \return state
 **/
/*---------------------------{PROG_CustomGetDERFormat}-----------------------------*/
void PROG_CustomGetDERFormat(const u8** ubKeyPtr)
{
    OSC_PARAM_UNUSED(ubKeyPtr);

}
/*------------------------{end PROG_CustomGetDERFormat}--------------------------*/

/*---------------------------{Prog_CustomReadPublicKeyHash}-----------------------------*/

/** \brief
 ** Callback is called: When user wants to read the In House Public Key Hash when in Applicative Software
 **
 ** \param[in,out] aubPublicKeyHash is the pointer to the address of the array which holds Public Key Hash
 **
 ** \return state
 **/

void Prog_CustomReadPublicKeyHash(u8*aubPublicKeyHash)
{
    OSC_PARAM_UNUSED(aubPublicKeyHash);

}

/*------------------------{end Prog_CustomReadPublicKeyHash}--------------------------*/
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFord')) and as:modconf('ProgFord')/General/PROG_FORD_VARIANT='SBL')"!]
/** \brief validates the update/switching key routine header and updates the status
 **
 ** Callback is called: upon receiving a key update/switching rouitne request and used to validation the header of the routine.
 **
 ** \param[out] pubHeaderStatus contains the header status, error code incase failure
 ** \param[in]  pubUdsData complete diagnostic request and used to extract the header parameters
 ** \param[in]  ulDataLength length of diagnostic request 
 **
 ** Callback shall implement: should validate the header parameter (SYNCP Bitwise Encoded Data,
 ** CPU Destination, Service Type, Command Type, Cryptotype, Payload size, FESN, Module Message ID,
 ** Server Message ID, Message Status, Key Index) and update the result incase of failure in pubHeaderStatus
 **
 ** \return Status of header verification
 ** \retval PROG_E_OK  header verification was successful
 ** \retval PROG_E_NOT_OK  header verification failed
 **/
tProgStatus PROG_CustomVerifyUpdateSwitchKeyHeader(const u8 * pubUdsData, u16 ulDataLength, u8 *pubHeaderStatus)
{
    OSC_PARAM_UNUSED(pubUdsData);
    OSC_PARAM_UNUSED(ulDataLength);
    OSC_PARAM_UNUSED(pubHeaderStatus);

    return PROG_E_OK;
}

/** \brief updates the development public key
 **
 ** Callback is called: upon receiving a key update/switching rouitne request and used to update the newly received
 ** Development public key.
 **
 ** \param[in]  pubNewDevPubKey will have new development public that needs to be stored in flash
 ** \param[out]  pubWriteStat return the error code in case key update into flash failes
 **
 ** Callback shall implement: machanism to store the Development public key into Flash area
 **
 ** \return Status of Keyupdate
 ** \retval PROG_E_OK  Keyupdate was successful
 ** \retval PROG_E_NOT_OK  Keyupdate verification failed
 **/
tProgStatus PROG_CustomUpdateDevelopmentKey(u8 *pubNewDevPubKey, u8* pubWriteStat)
{
    OSC_PARAM_UNUSED(pubNewDevPubKey);
    OSC_PARAM_UNUSED(pubWriteStat);
    return PROG_E_OK;
}

/** \brief updates the production public key
 **
 ** Callback is called: upon receiving a key update/switching rouitne request and used to update the newly received
 ** Production public key.
 **
 ** \param[in]  pubNewProdPubKey will have new Production public that needs to be stored in flash
 ** \param[out]  pubWriteStat return the error code in case key update into flash failes
 **
 ** Callback shall implement: machanism to store the production public key into Flash area
 **
 ** \return Status of Keyupdate
 ** \retval PROG_E_OK  Keyupdate was successful
 ** \retval PROG_E_NOT_OK  Keyupdate verification failed
 **/
tProgStatus PROG_CustomUpdateProductionKey(u8 *pubNewProdPubKey, u8* pubWriteStat)
{
    OSC_PARAM_UNUSED(pubNewProdPubKey);
    OSC_PARAM_UNUSED(pubWriteStat);
    return PROG_E_OK;
}

/** \brief Updates the token public key 
 **
 ** Callback is called: upon receiving a key update/switching rouitne request and used to update the newly received
 ** Token public key.
 **
 ** \param[in]  pubNewTokenPubKey will have new Token public that needs to be stored in flash
 ** \param[out]  pubWriteStat return the error code in case key update into flash failes
 **
 ** Callback shall implement: machanism to store the Token public key into Flash area
 **
 ** \return Status of Keyupdate
 ** \retval PROG_E_OK  Keyupdate was successful
 ** \retval PROG_E_NOT_OK  Keyupdate verification failed
 **/
tProgStatus PROG_CustomUpdateTokenKey(u8 *pubNewTokenPubKey, u8* pubWriteStat)
{
    OSC_PARAM_UNUSED(pubNewTokenPubKey);
    OSC_PARAM_UNUSED(pubWriteStat);
    return PROG_E_OK;
}

/** \brief used to the routine request in non-volatile memory 
 **
 ** Callback is called: upon receiving a key update/switching rouitne request and the request was handled 
 ** was successfully.
 **
 ** \param[in]  pubUdsData will have the received diagnostic request
 ** \param[in]  ulDataLength will have size of Token public key
 ** \param[out]  pubWriteStat return the error code in case key update into flash failes
 **
 ** Callback shall implement: machanism to store the received switchingKey Routine request into non-volatile memory.
 **
 ** \return Status of Request copy into flash
 ** \retval PROG_E_OK  Request copy was successful
 ** \retval PROG_E_NOT_OK  Request copy verification failed
 **/
tProgStatus PROG_CustomCopySwitchingKeyRequest(const u8 * pubUdsData, u16 ulDataLength, u8* pubWriteStat)
{
    OSC_PARAM_UNUSED(pubUdsData);
    OSC_PARAM_UNUSED(ulDataLength);
    OSC_PARAM_UNUSED(pubWriteStat);
    return PROG_E_OK;
}


/** \brief used Update the Active Key into non-volatile memory.
 **
 ** Callback is called: upon receiving a key update/switching rouitne request and there was a change the key
 ** Development or Production key.
 **
 ** \param[in]  ubActiveKey will have Requested key.
 ** \param[in]  ubActiveKeyMode will have Requested key.
 ** \param[out] pubWriteStat error code in case of status update into falsh failes
 **
 ** Callback shall implement: machanism to store the Active key mode into non-volatile memory.
 **
 ** \return Status of key status update into flash
 ** \retval PROG_E_OK  key status update was successful
 ** \retval PROG_E_NOT_OK  key status update verification failed
 **/
tProgStatus PROG_CustomUpdateActiveKeyStatAndMode(u8 ubActiveKey, u8 ubActiveKeyMode, u8* pubWriteStat)
{
    OSC_PARAM_UNUSED(ubActiveKey);
    OSC_PARAM_UNUSED(ubActiveKeyMode);
    OSC_PARAM_UNUSED(pubWriteStat);
    return PROG_E_OK;
}
[!ENDIF!]
#if ((PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91))
/** \brief check for the pre conditions for Secure Access.
 **
 ** Callback is called: when Seed is requested for unlocking Secure Access. 
 ** Callback shall implement: function to check pre conditions as per requirements 
 ** and returns as Ok or Not OK value.
 **
 ** \return Active Key Mode.
 **/
 
tProgStatus PROG_CustomCheckSA_PreConditions(void)
{
return E_OK;
}
#endif
[!IF "node:exists(as:modconf('ProgFord'))"!]
/** \brief used Read the Active Key  from non-volatile memory.
 **
 ** Callback is called: upon receiving a key update/switching rouitne request and there is need to read
 ** the active key.
 **
 **
 ** Callback shall implement: machanism to read the Active key from non-volatile memory.
 **
 ** \return Active Key.
 **/
u8 PROG_CustomGetActiveKey(void)
{
    return E_OK;
}

/** \brief used Update the Active Key Mode from non-volatile memory.
 **
 ** Callback is called: upon receiving a key update/switching rouitne request and there was a need to read the key Mode
 ** (Production key Mode, Use Development Key untill otherwise told, use development key
 ** temporarily, use develeopment key untill date, use Development key untill specified Ignition cycles)
 **
 ** Callback shall implement: machanism to read the Active key mode from non-volatile memory.
 **
 ** \return Active Key Mode.
 **/
u8 PROG_CustomGetKeyMode(void)
{
    return E_OK;
}

/** \brief Get the last sucessful switching key request
 **
 ** Callback is called: On receiving RDBI of the last sucessful switching key request key
 **
 ** \param[out] aubKeyRCData key checksum
 **
 ** Callback shall implement: get the last sucessful switching key request from the non volatile memory
 **
 ** \return void
 **/
void Prog_CustomReadLastSuccessSwitchingKeyRCReqest(u8* aubKeyRCData)
{
    OSC_PARAM_UNUSED(aubKeyRCData);
}
[!ENDIF!]
[!IF " node:exists(as:modconf('ProgOEMInd')) "!]


/** \brief API that check whether the transition is allowed from the compare key to RD
 **
 ** Callback is called: at Bootloader before starting RD to know if the transition to RD is allowed
 **
 ** Callback shall implement: get information from Bootloader if a compare key
 **                          request has been received and completed successfully and also if needed integrator can
 **                          perform any prechecks before trainsition to RD.
 **
 ** \return Result of check
 ** \retval PROG_E_OK If Transition to RD is allowed
 ** \retval PROG_E_NOT_OK If Transition to RD is not allowed
 **/
tProgStatus PROG_Custom_Guard_CompareKey_RD(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}
[!ENDIF!]

/** \brief Callback for SBL Address Check
 **
 ** Callback is called: After SBL Address is fetched
 **
 ** Callback shall implement: Check the correct SBL Start Address
 **
 ** \return Indicate Correct SBL Start Address
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **
 **/
/*---------------------------{PROG_CustomCheckSBLStartAddress}-----------------------------*/
tProgStatus PROG_CustomCheckSBLStartAddress(u32 ulAddressSBL)
{
    OSC_PARAM_UNUSED(ulAddressSBL);
    return PROG_E_OK;
}
/*------------------------{end PROG_CustomCheckSBLStartAddress}--------------------------*/



/** \brief callback to poll the ReprogMemM job status
 **
 ** Callback is called: when write and read PSI is requested
 **
 ** Callback shall implement: ReProgMemM_MainFunction should be called continuously until the pending state of ReprogMemM job ** status changes to no error state.
 ** \return Result of check
 ** \retval PROG_E_OK If jobstatus is REPROGMEMM_JOB_STATUS_NO_ERROR
 ** \retval PROG_E_NOT_OK If jobstatus is not REPROGMEMM_JOB_STATUS_NO_ERROR
 **/
/*---------------------------{PROG_Custom_MemStatuscheck}-----------------------------*/
tProgStatus PROG_Custom_MemStatuscheck(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}
/*------------------------{end PROG_Custom_MemStatuscheck}--------------------------*/

[!IF "(node:exists(as:modconf('ProgJLR')) and ( as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='OneLevelBL' ))"!]
/** \brief Callback to update the m_aubBlockDownloadStatus in case of unsigned software download
 **
 ** Callback is called: for unsigned software download in case OneLevel Bootloader
 **
 ** Callback shall implement: As there was not machanism to known the status of CRC, currently we are not
 **                           updating the m_aubBlockDownloadStatus to true no where for unsigned software download.
 **                           Integrator should implement a machanism to set the m_aubBlockDownloadStatus to TRUE in case
 **                           for all blocks which has signature verification is disabled.
 **
 **
 **/
/*---------------------------{PROG_CustomSetUnsigneBlckDwnldStat}-----------------------------*/
void PROG_CustomSetUnsigneBlckDwnldStat(void)
{

}
/*---------------------------{PROG_CustomSetUnsigneBlckDwnldStat}-----------------------------*/
[!ENDIF!]

[!IF "as:modconf('BlPduR')/General/Eth_Protocol_Supported = 'true'"!]
[!IF "node:exists(as:modconf('DoIP'))"!]
/** \brief Callback to update the m_ubDoIpRoutingActivationRequestRxConfirmation for offboard diagnostic request.
 **
 ** Callback is called: when DoIpRouting Activation is received for offboard diagnostic tester
 **
 ** Callback shall implement: Mechanism to set the m_ubDoIpRoutingActivationRequestRxConfirmation for offboard tester
 **                           Add set Authentified for that tester. Please refer the implementation in the comments below.
 **
 **
 **/
/*---------------------------{PROG_DoIpRoutineActivationRxConfirmationCbk}-----------------------------*/
Std_ReturnType PROG_DoIpRoutineActivationRxConfirmationCbk(
    P2VAR(boolean, AUTOMATIC, EBSTUBS_APPL_DATA) Authentified,
    P2CONST(uint8, AUTOMATIC, DOIP_APPL_DATA) AuthenticationReqData,
    P2VAR(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) AuthenticationResData)
{
    OSC_PARAM_UNUSED(AuthenticationReqData);
    OSC_PARAM_UNUSED(AuthenticationResData);
    OSC_PARAM_UNUSED(Authentified);

/*  static u8 ub_status;
    OSC_PARAM_UNUSED(AuthenticationReqData);
    OSC_PARAM_UNUSED(AuthenticationResData);

    E80 offboard tester
    if((ub_status == PROG_FALSE) && (stNoIntShareVar.ubRxPduId == 0))  
    {
        RoutingConfirmation flag is used to confirm the routing activation, with routing activation communication will not happen 
        m_ubDoIpRoutingActivationRequestRxConfirmation = TRUE;
        ub_status = PROG_TRUE;
    }
   
    Check if the request from Application and from f02 , then block 0e80
    if((0x55AA55AA == stNoIntShareVar.ulProgSig) && (stNoIntShareVar.ubRxPduId == 2) && (stNoIntShareVar.ubResponseRequired == 1))
    {
        *Authentified = FALSE;
    }
    else if(((stNoIntShareVar.ubResetCause == PROG_RESET_CAUSE_BLU) || (stNoIntShareVar.ubResetCause == PROG_RESET_CAUSE_DSC01) || (stNoIntShareVar.ubResetCause == PROG_RESET_CAUSE_ER)) && (stNoIntShareVar.ubRxPduId == 2) && (stNoIntShareVar.ubResponseRequired == 1))
    {
        *Authentified = FALSE;
    }
    else if (m_ConnectionCheck == 0x03)
    {
        *Authentified = FALSE;
    }
    else
    {
        if(m_ConnectionCheck == 0x00) 
        {
         m_ConnectionCheck =0x01;
        }
        *Authentified = TRUE;      
    } */

    return E_OK;
}
/*---------------------------{End of PROG_DoIpRoutineActivationRxConfirmationCbk}-----------------------------*/

/** \brief Callback to update the m_ubDoIpRoutingActivationRequestRxConfirmation_CallBack for onboard diagnostic request.
 **
 ** Callback is called: when DoIpRouting Activation is received for onboard diagnostic tester
 **
 ** Callback shall implement: Mechanism to set the m_ubDoIpRoutingActivationRequestRxConfirmation_CallBack for onboard tester
 **                           Add set Authentified for that tester. Please refer the implementation in the comments below.
 **
 **
 **/
/*---------------------------{PROG_DoIpRoutineActivationRxConfirmationCbk_OnBoard}-----------------------------*/
Std_ReturnType PROG_DoIpRoutineActivationRxConfirmationCbk_OnBoard(
    P2VAR(boolean, AUTOMATIC, EBSTUBS_APPL_DATA) Authentified,
    P2CONST(uint8, AUTOMATIC, DOIP_APPL_DATA) AuthenticationReqData,
    P2VAR(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) AuthenticationResData)
{
    OSC_PARAM_UNUSED(AuthenticationReqData);
    OSC_PARAM_UNUSED(AuthenticationResData);
    OSC_PARAM_UNUSED(Authentified);

/*    static u8 ub_status;
    OSC_PARAM_UNUSED(AuthenticationReqData);
    OSC_PARAM_UNUSED(AuthenticationResData);


    if((ub_status == PROG_FALSE) && (stNoIntShareVar.ubRxPduId == 2)) 
    {
      RoutingConfirmation flag is used to confirm the routing activation, with routing activation communication will not happen
      m_ubDoIpRoutingActivationRequestRxConfirmation_CallBack = TRUE;
      ub_status = PROG_TRUE;  
    } 
    
    Check if the request from Application and from f02 , then block 0e80
    if((0x55AA55AA == stNoIntShareVar.ulProgSig) && (stNoIntShareVar.ubRxPduId == 0) && (stNoIntShareVar.ubResponseRequired == 1))
    {
        *Authentified = FALSE;
    }
    Warm or Cold start RESET
    else if( ((stNoIntShareVar.ubResetCause == PROG_RESET_CAUSE_BLU) || (stNoIntShareVar.ubResetCause == PROG_RESET_CAUSE_DSC01) || (stNoIntShareVar.ubResetCause == PROG_RESET_CAUSE_ER)) && (stNoIntShareVar.ubRxPduId == 0) && (stNoIntShareVar.ubResponseRequired == 1))
    {
        *Authentified = FALSE;
    }
    Warm start if OFFboard 0e80 has connected
    else if (m_ConnectionCheck == 0x01)
    {
        *Authentified = FALSE;
    }
    else
    {     we are in cold start
        if(m_ConnectionCheck == 0x00)
        {
         m_ConnectionCheck = 0x03;
        }
        *Authentified = TRUE;
    }*/

    return E_OK;
}
/*---------------------------{End of PROG_DoIpRoutineActivationRxConfirmationCbk_OnBoard}-----------------------------*/
[!ENDIF!]
[!ENDIF!]
