/* --------{ EB Automotive C Source File }-------- */

[!SKIPFILE "(CryRsaSsaPssVerify/CryRsaSsaPssVerifyUseTimeSlices = 'false') or (CryRsaSsaPssVerify/CryRsaSsaPssVerifyUseCbk = 'false')"!][!//
#ifndef CRY_RSASSAPSSVERIFYCBK_H
#define CRY_RSASSAPSSVERIFYCBK_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

#include <Csm_Hash.h>

#include <Cry_LN.h>

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/
/* !LINKSTO EB_Cry_Slicing_CryRsaSsaPssVerifyNumberOfTimeSlicesCbk_h, 1
 */
/* !LINKSTO EB_Cry_Slicing_CryRsaSsaPssVerifyNumberOfTimeSlicesCbk_Signature,1
 */
typedef struct
{
  P2FUNC(uint32, CRY_APPL_CODE, CryRsaSsaPssTimeSlicesCbk)
  (
    void
  );
}
Cry_RsaSsaPssVerifyTimeSliceCbkType;

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

extern CONST(Cry_RsaSsaPssVerifyTimeSliceCbkType, CRY_CONST) Cry_RsaSsaPssVerifyTimeSliceConfig;

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

[!IF "(CryRsaSsaPssVerify/CryRsaSsaPssVerifyUseTimeSlices = 'true') and (CryRsaSsaPssVerify/CryRsaSsaPssVerifyUseCbk = 'true')"!][!//
#define CRY_START_SEC_CODE
#include <MemMap.h>

extern FUNC(uint32, CRY_APPL_CODE) [!"node:value(CryRsaSsaPssVerify/CryRsaSsaPssTimeSlicesCbk)"!]
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>
[!ENDIF!][!//
/*================================================================================================*/

#endif /* CRY_RSASSAPSSVERIFYCBK_H */
