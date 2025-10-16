/* --------{ EB Automotive C Source File }-------- */

#ifndef CRY_AES_COMMONCONFIG_H
#define CRY_AES_COMMONCONFIG_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>

/*==================[macros]======================================================================*/

#if (defined CRY_AES_SCHEDULE_STATIC)
#error CRY_AES_SCHEDULE_STATIC is already defined
#endif
#define  CRY_AES_SCHEDULE_STATIC   1U

#if (defined CRY_AES_SCHEDULE_DYNAMIC)
#error CRY_AES_SCHEDULE_DYNAMIC
#endif
#define  CRY_AES_SCHEDULE_DYNAMIC  2U

#if (defined CRY_AES_SCHEDULE)
#error CRY_AES_SCHEDULE
#endif
#define  CRY_AES_SCHEDULE  CRY_AES_SCHEDULE_STATIC  /* CRY_AES_SCHEDULE_STATIC  (completed) ||
                                                       CRY_AES_SCHEDULE_DYNAMIC (pending)      */

#if (defined CRY_AES_ENCRYPT_RESOURCE_EFFICIENT)
#error CRY_AES_ENCRYPT_RESOURCE_EFFICIENT is already defined
#endif
/** \brief Value indicating that the AES encryption "RESOURCE_EFFICIENT"
 **        implementation shall be used
 **/
#define CRY_AES_ENCRYPT_RESOURCE_EFFICIENT                 0U


#if (defined CRY_AES_ENCRYPT_FAST)
#error CRY_AES_ENCRYPT_FAST
#endif
/** \brief Value indicating that the AES encryption "FAST" implementation shall be used */
#define CRY_AES_ENCRYPT_FAST                               1U

#if (defined CRY_AES_ENCRYPT_IMPLEMENTATION)
#error CRY_AES_ENCRYPT_IMPLEMENTATION is already defined
#endif
/* !LINKSTO EB_Cry_AES_Encrypt_Implementation,1 */
/** \brief Switch for selecting between encryption "RESOURCE_EFFICIENT" or "FAST"
 **        implementation variant
 **/
#define CRY_AES_ENCRYPT_IMPLEMENTATION                     [!//
[!IF "node:exists(as:modconf('Cry')/CryAESEncrypt/CryAESEncryptImplementation)"!][!//
[!IF "as:modconf('Cry')/CryAESEncrypt/CryAESEncryptImplementation = 'CRY_AES_ENCRYPT_RESOURCE_EFFICIENT'"!][!//
CRY_AES_ENCRYPT_RESOURCE_EFFICIENT
[!ELSE!][!//
CRY_AES_ENCRYPT_FAST
[!ENDIF!][!//
[!ELSE!][!//
CRY_AES_ENCRYPT_RESOURCE_EFFICIENT
[!ENDIF!][!//

#if (defined CRY_AES_DECRYPT_RESOURCE_EFFICIENT)
#error CRY_AES_DECRYPT_RESOURCE_EFFICIENT is already defined
#endif
/** \brief Value indicating that the AES decryption "RESOURCE_EFFICIENT"
 **        implementation shall be used
 **/
#define CRY_AES_DECRYPT_RESOURCE_EFFICIENT                 0U

#if (defined CRY_AES_DECRYPT_FAST)
#error CRY_AES_DECRYPT_FAST is already defined
#endif
/** \brief Value indicating that the AES decryption "FAST" implementation shall be used */
#define CRY_AES_DECRYPT_FAST                               1U

#if (defined CRY_AES_DECRYPT_IMPLEMENTATION)
#error CRY_AES_DECRYPT_IMPLEMENTATION is already defined
#endif
/* !LINKSTO EB_Cry_AES_Decrypt_Implementation,1 */
/** \brief Switch for selecting between decryption "RESOURCE_EFFICIENT" or "FAST"
 **        implementation variant
 **/
#define CRY_AES_DECRYPT_IMPLEMENTATION                     [!//
[!IF "node:exists(as:modconf('Cry')/CryAESDecrypt/CryAESDecryptImplementation)"!][!//
[!IF "as:modconf('Cry')/CryAESDecrypt/CryAESDecryptImplementation = 'CRY_AES_DECRYPT_RESOURCE_EFFICIENT'"!][!//
CRY_AES_DECRYPT_RESOURCE_EFFICIENT
[!ELSE!][!//
CRY_AES_DECRYPT_FAST
[!ENDIF!][!//
[!ELSE!][!//
CRY_AES_DECRYPT_RESOURCE_EFFICIENT
[!ENDIF!][!//

/*==================[type definitions]============================================================*/

/*---[enum]---------------------------------------------------------------------------------------*/

/** \brief  Type of the configured AES algorithm.
 **/
typedef enum
{
  CRY_AES_KEY_128 = 16,
  CRY_AES_KEY_192 = 24,
  CRY_AES_KEY_256 = 32
}
Cry_AES_KeyType;

/*---[struct]-------------------------------------------------------------------------------------*/

/* !LINKSTO EB_CRY_0017,1 */
/** \brief  Configuration type for representing a configured AES algorithm.
 **/
typedef struct
{
  Cry_AES_KeyType typeKey;
}
Cry_AES_ConfigType;

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CRY_AES_COMMONCONFIG_H */
