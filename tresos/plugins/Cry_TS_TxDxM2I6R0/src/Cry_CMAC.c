/* --------{ EB Automotive C Source File }-------- */

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm.h>

#include <Cry_CMAC.h>
#include <Cry_CMACGenConfig.h>
#include <Cry_CMACVrfyConfig.h>
#include <Cry_Common.h>

#if ((CRY_CMAC_GEN_ENABLED == STD_ON) || (CRY_CMAC_VRFY_ENABLED == STD_ON))

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_8
#include <MemMap.h>

CONST(uint8, CRY_CONST) Cry_CMACSubKeyGenerationConstant[CRY_CMAC_BLOCK_LEN_BYTES] =
{
  0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
  0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x87U,
};

CONST(uint8, CRY_CONST) Cry_CMACSubKeyGenerationConstantOMAC2[CRY_CMAC_BLOCK_LEN_BYTES] =
{
  0x80U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
  0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x43U,
};

CONST(uint8, CRY_CONST) Cry_CMACZeroBlock[CRY_CMAC_BLOCK_LEN_BYTES] =
{
  0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
  0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
};

#define CRY_STOP_SEC_CONST_8
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

FUNC(void, CRY_CODE) Cry_CMACShiftBlockOneBitLeft
(
  P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) block
)
{
  uint8 i;

  for(i = 0U; i < (uint8)(CRY_CMAC_BLOCK_LEN_BYTES - 1U); i++)
  {
    block[i] = (uint8)(block[i     ] << 1U) |
               (uint8)(block[i + 1U] >> 7U);
  }

  /* The last byte of the block cannot use a bit from the next byte. */
  block[CRY_CMAC_BLOCK_LEN_BYTES - 1U] <<= 1;
}

FUNC(void, CRY_CODE) Cry_CMACShiftBlockOneBitRight
(
  P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) block
)
{
  uint8 i;

  for(i = (uint8)(CRY_CMAC_BLOCK_LEN_BYTES - 1U); i > 0U; i--)
  {
    block[i] = (uint8)(block[i     ] >> 1U) |
               (uint8)(block[i - 1U] << 7U);
  }

  /* The first byte of the block cannot use a bit from the next byte. */
  block[0U] >>= 1U;
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>


/*==[Definition of functions with internal linkage]===========================*/

#else /* #if ((CRY_CMAC_GEN_ENABLED == STD_ON) || (CRY_CMAC_VRFY_ENABLED == STD_ON)) */

typedef uint8 Cry_CMAC_PrvtEmptyTranslationUnitType;

#endif /* #if ((CRY_CMAC_GEN_ENABLED == STD_ON) || (CRY_CMAC_VRFY_ENABLED == STD_ON)) #else */

