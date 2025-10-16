/* --------{ EB Automotive C Source File }-------- */

/** \cond DONTDOCUMENT */

#ifndef CRY_CMAC_H
#define CRY_CMAC_H

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm.h>
#include <Cry_CMACGenConfig.h>
#include <Cry_CMACVrfyConfig.h>

#if ((CRY_CMAC_GEN_ENABLED == STD_ON) || (CRY_CMAC_VRFY_ENABLED == STD_ON))

/*==[Macros]==================================================================*/

#if (defined CRY_CMAC_BLOCK_LEN_BYTES)
#error CRY_CMAC_BLOCK_LEN_BYTES is already defined
#endif
/** \brief the length of one encryption block for the CMAC
 */
#define CRY_CMAC_BLOCK_LEN_BYTES 16U

#if (defined CRY_CMAC_BYTE_WITH_MSB_SET)
#error CRY_CMAC_BYTE_WITH_MSB_SET is already defined
#endif
/** \brief a byte which has only its most significant bit set
 */
#define CRY_CMAC_BYTE_WITH_MSB_SET 0x80U

#if (defined CRY_CMAC_BYTE_WITH_LSB_SET)
#error CRY_CMAC_BYTE_WITH_LSB_SET is already defined
#endif
/** \brief a byte which has only its least significant bit set
 */
#define CRY_CMAC_BYTE_WITH_LSB_SET 0x01U

#if (defined CRY_CMAC_TYPE_CMAC)
#error CRY_CMAC_TYPE_CMAC is already defined
#endif
/** \brief Flag to indicate that OMAC1/CMAC is used
 */
#define CRY_CMAC_TYPE_CMAC      0U

#if (defined CRY_CMAC_TYPE_OMAC2)
#error CRY_CMAC_TYPE_OMAC2 is already defined
#endif
/** \brief Flag to indicate that OMAC2 is used
 */
#define CRY_CMAC_TYPE_OMAC2     1U

/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_8
#include <MemMap.h>

/** \brief the CMAC constant string R128 for subkey generation
 */
extern CONST(uint8, CRY_CONST) Cry_CMACSubKeyGenerationConstant[CRY_CMAC_BLOCK_LEN_BYTES];

/** \brief the OMAC2 constant string R128 for subkey generation
 */
extern CONST(uint8, CRY_CONST) Cry_CMACSubKeyGenerationConstantOMAC2[CRY_CMAC_BLOCK_LEN_BYTES];

/** \brief A block consisting of zeroes
 *
 * This block is used in the subkey generation and it is xor-ed with the first input
 * block M1 before encryption.
 */
extern CONST(uint8, CRY_CONST) Cry_CMACZeroBlock[CRY_CMAC_BLOCK_LEN_BYTES];

#define CRY_STOP_SEC_CONST_8
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief Shift data block one bit to the left
 *
 * \param[in,out] block   A pointer to the the start of a block of size CRY_CMAC_BLOCK_LEN_BYTES
 *                        which has to be shifted one bit to the left.
 *
 * \Reentrancy{Reentrant}
 * \Synchronicity{Synchronous}
 */
extern FUNC(void, CRY_CODE) Cry_CMACShiftBlockOneBitLeft
(
  P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) block
);

/** \brief Shift data block one bit to the right
 *
 * \param[in,out] block   A pointer to the the start of a block of size CRY_CMAC_BLOCK_LEN_BYTES
 *                        which has to be shifted one bit to the right.
 *
 * \Reentrancy{Reentrant}
 * \Synchronicity{Synchronous}
 */
extern FUNC(void, CRY_CODE) Cry_CMACShiftBlockOneBitRight
(
  P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) block
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if ((CRY_CMAC_GEN_ENABLED == STD_ON) || (CRY_CMAC_VRFY_ENABLED == STD_ON)) */

/** \endcond  */

#endif /* CRY_CMAC_H */
