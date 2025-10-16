/* --------{ EB Automotive C Source File }-------- */

[!SKIPFILE "(CryRsaSsaV15Verify/CryRsaSsaV15VerifyUseTimeSlices = 'false') or (CryRsaSsaV15Verify/CryRsaSsaV15VerifyUseCbk = 'false')"!][!//
#ifndef CRY_RSASSAV15VERIFYCBK_H
#define CRY_RSASSAV15VERIFYCBK_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

#include <Csm_Hash.h>

#include <Cry_LN.h>

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/
/* !LINKSTO EB_Cry_Slicing_CryRsaSsaV15VerifyNumberOfTimeSlicesCbk_h, 1
 */
/* !LINKSTO EB_Cry_Slicing_CryRsaSsaV15VerifyNumberOfTimeSlicesCbk_Signature,1
 */
typedef struct
{
  P2FUNC(uint32, CRY_APPL_CODE, CryRsaSsaV15TimeSlicesCbk)
  (
    void
  );
}
Cry_RsaSsaV15VerifyTimeSliceCbkType;

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

extern CONST(Cry_RsaSsaV15VerifyTimeSliceCbkType, CRY_CONST) Cry_RsaSsaV15VerifyTimeSliceConfig;

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

[!IF "(CryRsaSsaV15Verify/CryRsaSsaV15VerifyUseTimeSlices = 'true') and (CryRsaSsaV15Verify/CryRsaSsaV15VerifyUseCbk = 'true')"!][!//
#define CRY_START_SEC_CODE
#include <MemMap.h>

extern FUNC(uint32, CRY_APPL_CODE) [!"node:value(CryRsaSsaV15Verify/CryRsaSsaV15TimeSlicesCbk)"!]
(
  void
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>
[!ENDIF!][!//
/*================================================================================================*/

#endif /* CRY_RSASSAV15VERIFYCBK_H */
