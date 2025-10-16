/* --------{ EB Automotive C Source File }-------- */
#ifndef CRY_CCM_COMMONCONFIG_H
#define CRY_CCM_COMMONCONFIG_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>

/*==================[macros]======================================================================*/

/** \brief Length of the MAC in bytes. */
#if (defined CRY_CCM_MAC_4_BYTES)
#error CRY_CCM_MAC_4_BYTES is already defined
#endif
#define CRY_CCM_MAC_4_BYTES   4U

#if (defined CRY_CCM_MAC_6_BYTES)
#error CRY_CCM_MAC_6_BYTES is already defined
#endif
#define CRY_CCM_MAC_6_BYTES   6U

#if (defined CRY_CCM_MAC_8_BYTES)
#error CRY_CCM_MAC_8_BYTES is already defined
#endif
#define CRY_CCM_MAC_8_BYTES   8U

#if (defined CRY_CCM_MAC_10_BYTES)
#error CRY_CCM_MAC_10_BYTES is already defined
#endif
#define CRY_CCM_MAC_10_BYTES  10U

#if (defined CRY_CCM_MAC_12_BYTES)
#error CRY_CCM_MAC_12_BYTES is already defined
#endif
#define CRY_CCM_MAC_12_BYTES  12U

#if (defined CRY_CCM_MAC_14_BYTES)
#error CRY_CCM_MAC_14_BYTES is already defined
#endif
#define CRY_CCM_MAC_14_BYTES  14U

#if (defined CRY_CCM_MAC_16_BYTES)
#error CRY_CCM_MAC_16_BYTES is already defined
#endif
#define CRY_CCM_MAC_16_BYTES  16U

/** \brief Length(in bytes) of the field where the payload size is encoded. */

#if (defined CRY_CCM_LEN_FIELD_2_BYTES)
#error CRY_CCM_LEN_FIELD_2_BYTES is already defined
#endif
#define CRY_CCM_LEN_FIELD_2_BYTES 2U

#if (defined CRY_CCM_LEN_FIELD_3_BYTES)
#error CRY_CCM_LEN_FIELD_3_BYTES is already defined
#endif
#define CRY_CCM_LEN_FIELD_3_BYTES 3U

#if (defined CRY_CCM_LEN_FIELD_4_BYTES)
#error CRY_CCM_LEN_FIELD_4_BYTES is already defined
#endif
#define CRY_CCM_LEN_FIELD_4_BYTES 4U

/*==================[type definitions]============================================================*/

/*---[enum]---------------------------------------------------------------------------------------*/
/* !LINKSTO EB_CRY_0017,1 */
/** \brief  Configuration type for representing a configured CCM algorithm.
 **/
typedef struct
{
  /** \brief Length of the authentificated data. */
  uint32           aDataLen;
  /** \brief Length of the MAC tag. */
  uint8            M;
  /** \brief Size of the lenght field in bits. */
  uint8            L;
  /** \brief Configuration ID of the symetric block encrypt. */
  Csm_ConfigIdType symBlockCfgId;
}
Cry_CcmCryptConfigType;

/*---[struct]-------------------------------------------------------------------------------------*/

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CRY_CCM_COMMONCONFIG_H */
