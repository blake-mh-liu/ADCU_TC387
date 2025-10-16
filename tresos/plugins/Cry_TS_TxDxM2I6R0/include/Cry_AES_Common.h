/* --------{ EB Automotive C Source File }-------- */

/** \cond DONTDOCUMENT */

#ifndef CRY_AES_COMMON_H
#define CRY_AES_COMMON_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

#include <Cry_AES_CommonConfig.h>

/*==================[macros]======================================================================*/

#if (defined CRY_AES_KEYSEEDLENMAX)
#error CRY_AES_KEYSEEDLENMAX is already defined
#endif
/** \brief Defines the maximum key length in bytes */
#define  CRY_AES_KEYSEEDLENMAX   32U

#if (defined CRY_AES_SZESTATE)
#error CRY_AES_SZESTATE is already defined
#endif
/** \brief Defines the length in bytes of the AES state */
#define  CRY_AES_SZESTATE        16U  /* block size in 8-bit words; always 16 for AES */

#if (defined CRY_AES_SBOXLEN)
#error CRY_AES_SBOXLEN is already defined
#endif
/** \brief Defines the length of the SBox and SBoxInv lookup tables */
#define  CRY_AES_SBOXLEN        256U

#if ((CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_RESOURCE_EFFICIENT) || \
     (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_RESOURCE_EFFICIENT))

#if (defined CRY_AES_KEYEXPDLENMAX)
#error CRY_AES_KEYEXPDLENMAX is already defined
#endif
/** \brief Defines the maximum length in bytes of the expanded key */
#define  CRY_AES_KEYEXPDLENMAX  240U

#if (defined CRY_AES_RCONLEN)
#error CRY_AES_RCONLEN is already defined
#endif
/** \brief Defines the length of the RCon table */
#define  CRY_AES_RCONLEN        255U

#if (defined CRY_AES_GF28LEN)
#error CRY_AES_GF28LEN is already defined
#endif
/** \brief Defines the length of the Cry_AES_GF28G3Exp and Cry_AES_GF28G3Ln tables */
#define  CRY_AES_GF28LEN        256U

#if (defined CRY_AES_COMMONMULGF28)
#error CRY_AES_COMMONMULGF28 is already defined
#endif
/** \brief  Fast multiply of two 8-bit large numbers in the rijndael finite field, the galois
 **         field GF(2^8).
 **
 ** \param[in]  a  The multiplication multiplier.
 ** \param[in]  b  The multiplication multiplicand.
 **/
#define CRY_AES_COMMONMULGF28(a, b)                 \
  (((((a) != 0) && ((b) != 0U)) != 0)  \
  ? Cry_AES_GF28G3Exp[((uint16)Cry_AES_GF28G3Ln[(a)] + (uint16)Cry_AES_GF28G3Ln[(b)]) % 255U] : 0U)

#endif

#if ((CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_FAST) || \
     (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_FAST))

#if (defined CRY_AES_TETDLEN)
#error CRY_AES_TETDLEN is already defined
#endif
/** \brief Defines the length of the Te/Td lookup tables */
#define CRY_AES_TETDLEN              256U

#if (defined CRY_AES_RCONFASTLEN)
#error CRY_AES_RCONFASTLEN is already defined
#endif
/** \brief Defines the length of the Round Constants table used by
 **        the fast implementation variant
 **/
#define CRY_AES_RCONFASTLEN          10U

#if (defined CRY_AES_KEYEXPDLENMAX_FAST)
#error CRY_AES_KEYEXPDLENMAX_FAST is already defined
#endif
/** \brief Defines the length in words of the expanded key */
#define  CRY_AES_KEYEXPDLENMAX_FAST  60U

#if (defined CRY_AES_COMMON_BYTEARRAY_TO_UINT32)
#error CRY_AES_COMMON_BYTEARRAY_TO_UINT32 is already defined
#endif
/** \brief Converts a byte array to an uint32 using big endian byte order */
#define CRY_AES_COMMON_BYTEARRAY_TO_UINT32(src)  \
  (uint32)(((uint32)((src)[0]) << 24U) |         \
           ((uint32)((src)[1]) << 16U) |         \
           ((uint32)((src)[2]) <<  8U) |         \
           ((uint32)((src)[3])))

#if (defined CRY_AES_COMMON_UINT32_TO_BYTEARRAY)
#error CRY_AES_COMMON_UINT32_TO_BYTEARRAY is already defined
#endif
/** \brief Converts an uint32 to a byte array using big endian byte order */
#define CRY_AES_COMMON_UINT32_TO_BYTEARRAY(dst, src)  \
  do                                                  \
  {                                                   \
    (dst)[0] = (uint8)((src) >> 24U);                 \
    (dst)[1] = (uint8)((src) >> 16U);                 \
    (dst)[2] = (uint8)((src) >>  8U);                 \
    (dst)[3] = (uint8)((src)       );                 \
  }                                                   \
  while (0)

#if (defined CRY_AES_COMMON_ROTL3)
#error CRY_AES_COMMON_ROTL3 is already defined
#endif
/** \brief Performs a left rotation by three bytes */
#define CRY_AES_COMMON_ROTL3(word)       \
  ((uint32)((word) << 24U) | (uint32)((word) >>  8U))

#if (defined CRY_AES_COMMON_ROTL2)
#error CRY_AES_COMMON_ROTL2 is already defined
#endif
/** \brief Performs a left rotation by two bytes */
#define CRY_AES_COMMON_ROTL2(word)       \
  ((uint32)((word) << 16U) | (uint32)((word) >> 16U))

#if (defined CRY_AES_COMMON_ROTL1)
#error CRY_AES_COMMON_ROTL1 is already defined
#endif
/** \brief Performs a left rotation by one byte */
#define CRY_AES_COMMON_ROTL1(word)       \
  ((uint32)((word) <<  8U) | (uint32)((word) >> 24U))

#endif

/*==================[type definitions]============================================================*/

/*---[enum]---------------------------------------------------------------------------------------*/

/** \brief  AES algorithm implementation specific internal representation of Csm_SymKeyType.
 **/
typedef struct
{
   uint32  length;
   uint8   data[CRY_AES_KEYSEEDLENMAX];
}
Cry_AES_SymKeyType;

/** \brief  AES algorithm implementation state machine states.
 **/
typedef enum
{
  CRY_AES_STATE_UNINITIALIZED,
  CRY_AES_STATE_START,
  CRY_AES_STATE_INITIALIZED,
  CRY_AES_STATE_UPDATE,
  CRY_AES_STATE_CALCULATING,
  CRY_AES_STATE_FINISH,
  CRY_AES_STATE_ERROR
}
Cry_AES_StateType;

/*---[struct]-------------------------------------------------------------------------------------*/

/** \brief  AES algorithm implementation context structure.
 **/
/* !LINKSTO EB_CRY_0022,1 */
typedef struct {
          uint32                            szeTurn;        /* number of turns 10, 12, 14.       */
          uint32                            keySeedLen;
#if ((CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_FAST) || \
     (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_FAST))
          uint32                            keyExpdFast[CRY_AES_KEYEXPDLENMAX_FAST];
#endif
          uint32                            keyExpdLen;
          uint32                            txtIputLen;
          uint32                            txtOputLen;
  P2CONST(uint8,  TYPEDEF,  CRY_APPL_DATA ) txtIput;
    P2VAR(uint8,  TYPEDEF,  CRY_APPL_DATA ) txtOput;
          Cry_AES_StateType                 ctxState;
          Csm_ReturnType                    ctxError;
          uint8                             aesState[CRY_AES_SZESTATE];  /* AES state            */
          uint8                             szeKey;         /* key size in 32-bit words; 4, 6, 8 */
          uint8                             cntTurn;        /* counter of turns                  */
          uint8                             keySeed[CRY_AES_KEYSEEDLENMAX];
#if ((CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_RESOURCE_EFFICIENT) || \
     (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_RESOURCE_EFFICIENT))
          uint8                             keyExpd[CRY_AES_KEYEXPDLENMAX];
#endif
#if ((CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_RESOURCE_EFFICIENT) || \
     (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_RESOURCE_EFFICIENT))
          uint8                             keyTurn[CRY_AES_SZESTATE];
#endif

}
Cry_AES_ContextType;

/*==================[external function declarations]==============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

#if ((CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_RESOURCE_EFFICIENT) || \
     (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_RESOURCE_EFFICIENT))

/** \brief  Rijndael's key expansion expands an 16/24/32 byte key into an 176/208/240 bytes key.
 **
 ** \param[in,out]  context  Pointer to context structure.
 **/
extern FUNC(void, CRY_CODE) Cry_AES_CommonKeyExpand
(
  P2VAR(Cry_AES_ContextType, AUTOMATIC, CRY_APPL_DATA) context
);

/** \brief  Creates the key for a single AES turn (e.g. from expanded key).
 **
 ** \param[in,out]  context     Pointer to context structure.
 ** \param[in]      keyExpdPos  Position value of begin of turn key in expanded key.
 **/
extern FUNC(void, CRY_CODE) Cry_AES_CommonTurnKeyCreate
(
  P2VAR(Cry_AES_ContextType, AUTOMATIC, CRY_APPL_DATA) context,
        uint32                                         keyExpdPos
);

/** \brief  Adds the AES turn key.
 **
 ** \param[in,out]  context  Pointer to context structure.
 **/
extern FUNC(void, CRY_CODE) Cry_AES_CommonTurnKeyAdd
(
  P2VAR(Cry_AES_ContextType, AUTOMATIC, CRY_APPL_DATA) context
);

/** \brief  Transponse the AES state array in AES context structure.
 **
 ** \param[in,out]  context  Pointer to context structure.
 **/
extern FUNC(void, CRY_CODE) Cry_AES_CommonAesStateTranspose
(
  P2VAR(Cry_AES_ContextType, AUTOMATIC, CRY_APPL_DATA) context
);

#endif

#if ((CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_FAST) || \
     (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_FAST))

/** \brief  Rijndael's key expansion expands an 16/24/32 byte key into an 176/208/240 bytes key.
 **
 ** \param[in,out]  context  Pointer to context structure.
 **/
extern FUNC(void, CRY_CODE) Cry_AES_CommonCalculateKeySchedule
(
  P2VAR(Cry_AES_ContextType, AUTOMATIC, CRY_APPL_DATA) context
);

/** \brief  Maps the input byte array stored in the AES state variable to the intermediate
 **         variables used to perform the calculation
 **
 ** \param[out]  firstCol   Pointer to the variable where the values corresponding
 **              to the first column will be stored.
 ** \param[out]  secondCol  Pointer to the variable where the values corresponding
 **              to the second column will be stored.
 ** \param[out]  thirdCol   Pointer to the variable where the values corresponding
 **              to the third column will be stored.
 ** \param[out]  fourthCol  Pointer to the variable where the values corresponding
 **              to the fourth column will be stored.
 ** \param[in]   context    Pointer to context structure.
 **/
extern FUNC(void, CRY_CODE) Cry_AES_CommonMapState
(
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) firstCol,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) secondCol,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) thirdCol,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) fourthCol,
  P2CONST(Cry_AES_ContextType, AUTOMATIC, CRY_APPL_DATA) context
);

/** \brief  Unmaps the output of the algorithm stored in the intermediate variables used to perform
 **         the calculation to the AES state variable
 **
 ** \param[in]   firstCol   Pointer to the variable where the values corresponding
 **              to the first column are stored.
 ** \param[in]   secondCol  Pointer to the variable where the values corresponding
 **              to the second column are stored.
 ** \param[in]   thirdCol   Pointer to the variable where the values corresponding
 **              to the third column are stored.
 ** \param[in]   fourthCol  Pointer to the variable where the values corresponding
 **              to the fourth column are stored.
 ** \param[out]  context    Pointer to context structure.
 **/
extern FUNC(void, CRY_CODE) Cry_AES_CommonUnmapState
(
  P2CONST(uint32, AUTOMATIC, CRY_APPL_DATA) firstCol,
  P2CONST(uint32, AUTOMATIC, CRY_APPL_DATA) secondCol,
  P2CONST(uint32, AUTOMATIC, CRY_APPL_DATA) thirdCol,
  P2CONST(uint32, AUTOMATIC, CRY_APPL_DATA) fourthCol,
  P2VAR(Cry_AES_ContextType, AUTOMATIC, CRY_APPL_DATA) context
);

#endif

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/

#define CRY_START_SEC_CONST_8
#include <MemMap.h>

#if (CRY_AES_SCHEDULE == CRY_AES_SCHEDULE_STATIC)

/** \brief Look-up table for the ByteSub layer */
extern CONST(uint8, CRY_CONST) Cry_AES_SboxNrm[CRY_AES_SBOXLEN];

/** \brief Look-up table for the InvByteSub layer */
extern CONST(uint8, CRY_CONST) Cry_AES_SboxInv[CRY_AES_SBOXLEN];

#if ((CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_RESOURCE_EFFICIENT) || \
     (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_RESOURCE_EFFICIENT))

/** \brief Round Coefficients table used in the KeySchedule by
 **        the "Resource Efficient" code variant
 **/
extern CONST(uint8, CRY_CONST) Cry_AES_Rcon[CRY_AES_RCONLEN];

/** \brief Look-up table for performing a fast multiplication of
 **        two 8-bit large numbers in the rijndael finite field
 **/
extern CONST(uint8, CRY_CONST) Cry_AES_GF28G3Exp[CRY_AES_GF28LEN];
/** \brief Look-up table for performing a fast multiplication of
 **        two 8-bit large numbers in the rijndael finite field
 **/
extern CONST(uint8, CRY_CONST) Cry_AES_GF28G3Ln[CRY_AES_GF28LEN];

#endif

#define CRY_STOP_SEC_CONST_8
#include <MemMap.h>

#define CRY_START_SEC_CONST_32
#include <MemMap.h>

#if (CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_FAST)

/** \brief Look-up table for the first column of the state matrix.
 **        This table combines the ByteSub, ShiftRow and MixColumn transformations.
 **        The values of this table represent the product between Cry_AES_SboxNrm and coefficients
 **        [02, 01, 01, 03] from the MixColumn layer.
 **/
extern CONST(uint32, CRY_CONST) Cry_AES_Te0[CRY_AES_TETDLEN];

#endif

#if ((CRY_AES_ENCRYPT_IMPLEMENTATION == CRY_AES_ENCRYPT_FAST) || \
     (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_FAST))

/** \brief Round Coefficients table used in the KeySchedule by
 **        the "Fast" code variant
 **/
extern CONST(uint32, CRY_CONST) Cry_AES_Rcon_Fast[CRY_AES_RCONFASTLEN];

#endif

#if (CRY_AES_DECRYPT_IMPLEMENTATION == CRY_AES_DECRYPT_FAST)
/** \brief Look-up table for the first column of the state matrix.
 **        This table combines the InvByteSub, InvShiftRow and invMixColumn transformations.
 **        The values of this table represent the product between Cry_AES_SboxInv and coefficients
 **        [0E, 09, 0D, 0B] from the InvMixColumn layer.
 **/
extern CONST(uint32, CRY_CONST) Cry_AES_Td0[CRY_AES_TETDLEN];

#endif

#define CRY_STOP_SEC_CONST_32
#include <MemMap.h>

#endif

/*==================[external data]===============================================================*/

/*================================================================================================*/

/** \endcond  */

#endif /* #ifndef CRY_AES_COMMON_H */
