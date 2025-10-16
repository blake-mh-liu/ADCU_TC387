/* --------{ EB Automotive C Source File }-------- */

#ifndef CRY_EXTRACTECPUBKEYCONFIG_H
#define CRY_EXTRACTECPUBKEYCONFIG_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>
#include <Csm.h>

#include <Cry_LN.h>

/*==================[macros]======================================================================*/

#if (defined CRY_X_ELLIPTIC_KEY_ENABLED)
#error CRY_X_ELLIPTIC_KEY_ENABLED is already defined
#endif
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CryExtractECPubKey/CryExtractECPubKeyConfig/*))"!][!//
#define CRY_X_ELLIPTIC_KEY_ENABLED TRUE
[!ELSE!][!//
#define CRY_X_ELLIPTIC_KEY_ENABLED FALSE
[!ENDIF!][!//

#if (CRY_X_ELLIPTIC_KEY_ENABLED == TRUE)

#if (defined CRY_ECPUBKEY_NUM_LEN)
#error CRY_ECPUBKEY_NUM_LEN is already defined
#endif
/** \brief The length, in bytes, which is needed for the elliptic curve public key. */
#define CRY_ECPUBKEY_NUM_LEN    32U

#if (defined CRY_ECPUBKEY_NUM_LEN_WORDS)
#error CRY_ECPUBKEY_NUM_LEN_WORDS is already defined
#endif
/** \brief The length, in words, which is needed for the long number representation of
 *         the longest possible elliptic curve public key.
 */
#define CRY_ECPUBKEY_NUM_LEN_WORDS                          \
(                                                           \
   (Cry_LNWordType)                                         \
   (                                                        \
      Cry_LNNumberLen(CRY_ECPUBKEY_NUM_LEN) +               \
      (Cry_LNWordType)1UL                                   \
   )                                                        \
)

#if (defined CRY_ECPUBKEY_TEMP_LEN_WORDS)
#error CRY_ECPUBKEY_TEMP_LEN_WORDS is already defined
#endif
/** \brief The length, in words, which is needed for the long number representation of
 *         the longest possible temporary number.
 */
#define CRY_ECPUBKEY_TEMP_LEN_WORDS                        \
(                                                          \
   (Cry_LNWordType)                                        \
   (                                                       \
      (CRY_ECPUBKEY_NUM_LEN_WORDS * (Cry_LNWordType)2UL) - \
      (Cry_LNWordType)1UL                                  \
   )                                                       \
)

#if (defined CRY_ECPUBKEY_BUFLEN)
#error CRY_ECPUBKEY_BUFLEN is already defined
#endif
/** \brief The length */
#define CRY_ECPUBKEY_BUFLEN                             \
(                                                       \
  (                                                     \
    CRY_ECPUBKEY_TEMP_LEN_WORDS *                       \
    CRY_LN_WORD_LEN_BYTES                               \
  )                                                     \
)

/*==================[type definitions]============================================================*/

/*---[struct]-------------------------------------------------------------------------------------*/
/** \brief  Type of the configured elliptic curve primitives.
 **/
typedef enum
{
  CRY_EDC_255
}
Cry_EC_Type;

/** \brief  Configuration type for representing a configuration
 *          for the elliptic curve primitive used.
 **/
typedef struct
{
  uint32                                 keyBytesLength;
  Cry_EC_Type                            keyType;
}
Cry_ExtractECPubKeyCfgType;

/** \brief  xValue=The Public Key
 **/
typedef struct
{
  Cry_LNWordType xValue[CRY_ECPUBKEY_TEMP_LEN_WORDS];
}
Cry_EPointType;

/** \brief  The key used for verifying a signature
 *          length=Dummy element to make the type compatible with the Csm key type.
 *          Q=The coordinate of the point on the curve
 **/
typedef struct
{
  uint32 length;
  Cry_EPointType Q;
}
Cry_ECKeyType;

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/

[!IF "count(as:modconf('Cry')/CryExtractECPubKey/CryExtractECPubKeyConfig/*) > 0"!][!//

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!LOOP "as:modconf('Cry')/CryExtractECPubKey/CryExtractECPubKeyConfig/*"!][!//
extern CONST(Cry_ExtractECPubKeyCfgType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!ENDIF!][!//

/*==================[external data]===============================================================*/

#endif /* #if (CRY_X_ELLIPTIC_KEY_ENABLED == TRUE) */

#endif /* #ifndef CRY_EXTRACTECPUBKEYCONFIG_H */
