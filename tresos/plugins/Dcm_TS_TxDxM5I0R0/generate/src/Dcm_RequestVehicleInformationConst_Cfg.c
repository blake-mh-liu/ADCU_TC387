/* --------{ EB Automotive C Source File }-------- */
[!AUTOSPACING!]

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.7 (required)
 *     Expressions resulting from the expansion of macro parameters shall be enclosed in parentheses.
 *
 *     Reason:
 *     The macro DCM_CONST_CALIBRATION is used to modify the read-only attribute of a memory section
 *     to which a constant is assigned via the compiler abstraction macro, in order for the compiler
 *     to allow the simulation of the constant calibration. The syntax of the compiler abstraction
 *     macro definition requires DCM_CONST_CALIBRATION macro's definition to not be enclosed in
 *     parentheses.
 */

/*==================[inclusions]=================================================================*/
#include <Dcm_Int.h>
#include <Dcm_API_Cfg.h>
#include <Dcm_RequestVehicleInformation_Cfg.h>

#if (DCM_INCLUDE_RTE == STD_ON)
#include <Rte_Dcm.h>
#endif
[!INDENT "0"!]
/*==================[macros]=====================================================================*/

/*==================[type definitions]===========================================================*/

/*==================[external function declarations]=============================================*/

/*==================[internal function declarations]=============================================*/

/*==================[internal constants]=========================================================*/

/*==================[internal data]==============================================================*/

/*==================[external constants]=========================================================*/
[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspVehInfo/eb-list::*)"!][!//
#define DCM_START_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

  [!/* !LINKSTO Dcm.Dsn.RequestVehicleInformation.ConfigurationDataElements,1 */!][!//
  [!/* !LINKSTO Dcm.dsn.Dsp.ReqVehInfo.Config.0005,1 */!][!//
  CONST(Dcm_DspVehInfoType,DCM_CONST) Dcm_DspVehInfo[DCM_DSP_VEHINFO_NUM] =
  {
    [!VAR "VehInfoStartIndex" = "0"!]
    [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspVehInfo/eb-list::* , 'DcmDspVehInfoInfoType'))"!]
      [!/* !LINKSTO Dcm.RequestVehicleInformation.DcmDspVehInfoASRVersion403.NonAvailabilityInfoType.DcmDspVehInfoNODIProvRespFalse,1 */!][!//
      [!/* !LINKSTO Dcm.RequestVehicleInformation.DcmDspVehInfoASRVersion440.NonAvailabilityInfoType.DcmDspVehInfoNODIProvRespFalse,1 */!][!//
      [!VAR "VehInfoCnt" = "num:integer(count(DcmDspVehInfoData/eb-list::*))"!]
      [!WS "2"!]/* VehInfo [!"as:name(.)"!] */
      [!WS "2"!]{
        [!INDENT "4"!]
           /*index of first VehInfoDataConfig*/
          [!"num:i($VehInfoStartIndex)"!]U,
           /*count of VehInfoDataConfig*/
          [!"num:i($VehInfoCnt)"!]U,
           /*VehInfoInfoType*/
          [!"num:inttohex(DcmDspVehInfoInfoType)"!]U,
          [!IF "as:modconf('Dcm')[1]/DcmConfigSet/eb-list::*[1]/DcmGeneral/DcmDspVehInfoASRVersion = 'AUTOSAR_440'"!]
            [!IF "node:existsAndTrue(DcmDspVehInfoNODIProvResp)"!]
             /* DcmDspVehInfoNODIProvResp */
            TRUE,
            [!ELSE!]
             /* DcmDspVehInfoNODIProvResp */
            FALSE,
            [!ENDIF!]
          [!ENDIF!]
    [!ENDINDENT!]
  [!WS "2"!]},
      [!VAR "VehInfoStartIndex" = "$VehInfoStartIndex + $VehInfoCnt"!]
  [!ENDLOOP!]
};

[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspVehInfo/eb-list::*/DcmDspVehInfoData/eb-list::*)"!]
[!/* !LINKSTO Dcm.dsn.Dsp.ReqVehInfo.Config.0001,1 */!][!//
CONST(Dcm_DspVehInfoDataType,DCM_CONST) Dcm_DspVehInfoData[DCM_DSP_VEHINFODATA_NUM] =
{
  [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspVehInfo/eb-list::* , 'DcmDspVehInfoInfoType'))"!]
    [!LOOP "util:distinct(node:order(DcmDspVehInfoData/eb-list::*, 'DcmDspVehInfoDataOrder'))"!]
      [!WS "2"!]/* VehInfo [!"as:name(../..)"!] - VehInfoData [!"as:name(.)"!] */
      [!WS "2"!]{
      [!INDENT "4"!]
        [!IF "node:existsAndTrue(DcmDspVehInfoDataUsePort)"!]
          [!/* !LINKSTO Dcm.dsn.Dsp.ReqVehInfo.Config.0009,1 */!][!//
           /* Rte GetInfotypeValueData operation pointer */
          &Rte_Call_InfotypeServices_[!"as:name(.)"!]_GetInfotypeValueData,
        [!ELSE!]
          [!/* !LINKSTO Dcm.dsn.Dsp.ReqVehInfo.Config.0008,1 */!][!//
           /* DcmDspVehInfoDataReadFnc Pointer*/
          &[!"DcmDspVehInfoDataReadFnc"!],
        [!ENDIF!]
        [!/* !LINKSTO Dcm.dsn.Dsp.ReqVehInfo.Config.0006,1 */!][!//
         /*DataSize*/
        [!"num:i(DcmDspVehInfoDataSize)"!]U,
    [!ENDINDENT!]
      [!WS "2"!]},
    [!ENDLOOP!]
  [!ENDLOOP!]
};
[!ENDIF!]

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CALIB_8
#include <Dcm_MemMap.h>

[!/* !LINKSTO Dcm.dsn.Dsp.ReqVehInfo.Config.0010,1 */!][!//
[!VAR "BitIndex" = "0"!][!//
[!VAR "ByteVal" = "0"!][!//
[!VAR "ByteFilled" = "0"!][!//
[!VAR "VehInfoRemaining" = "num:i(count(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspVehInfo/eb-list::*))"!][!//
/* Deviation MISRAC2012-1 */
CONST(uint8,DCM_CONST_CALIBRATION) Dcm_DspVehInfoUsed[DCM_DSP_VEHINFO_USED_ARRAY_SIZE] =
{
  [!LOOP "util:distinct(node:order(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspVehInfo/eb-list::* , 'DcmDspVehInfoInfoType'))"!]
    [!IF "$VehInfoRemaining > 0"!]
      [!VAR "VehInfoRemaining" = "$VehInfoRemaining - 1"!]
    [!ENDIF!]
    [!IF "node:existsAndTrue(DcmDspVehInfoUsed)"!]
      [!VAR "ByteVal" = "bit:or($ByteVal,bit:shl(1,$BitIndex))"!]
    [!ENDIF!]
    [!VAR "BitIndex" = "$BitIndex + 1"!]
    [!IF "($BitIndex mod 8) = 0"!]
      [!VAR "ByteFilled" = "1"!]
      [!VAR "BitIndex" = "0"!]
    [!ENDIF!]
    [!IF "($ByteFilled = 1) or ($VehInfoRemaining = 0)"!]
      [!WS "2"!][!"num:i($ByteVal)"!]U,
      [!VAR "ByteFilled" = "0"!]
      [!VAR "ByteVal" = "0"!]
    [!ENDIF!]
  [!ENDLOOP!]
};

#define DCM_STOP_SEC_CALIB_8
#include <Dcm_MemMap.h>
[!ENDIF!]
[!//
[!ENDINDENT!]

/*==================[external data]==============================================================*/

/*==================[external function definitions]==============================================*/

/*==================[internal function definitions]==============================================*/

/*==================[end of file]================================================================*/
