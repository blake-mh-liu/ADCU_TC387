[!/* ====================================================================================== */!][!//
[!AUTOSPACING!][!//
[!/* ====================================================================================== */!][!//
[!//
/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <Std_Types.h>

/*==================[macros]======================================================================*/

/* --- Extension to Std_ReturnType -------------------------------------------------------------- */

/** \brief  The service request failed because the service is still busy .
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_91043,1 */
#ifndef CRYPTO_E_BUSY
    #define CRYPTO_E_BUSY               0x0002U
#endif

/** \brief  The service request failed because the entropy of the random number generator is exhausted.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_91043,1 */
#ifndef CRYPTO_E_ENTROPY_EXHAUSTED
    #define CRYPTO_E_ENTROPY_EXHAUSTED  0x0004U
#endif

/** \brief  The service request failed because read access was denied.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_91043,1 */
#ifndef CRYPTO_E_KEY_READ_FAIL
    #define CRYPTO_E_KEY_READ_FAIL      0x0006U
#endif

/** \brief  The service request failed because the writing access failed.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_91043,1 */
#ifndef CRYPTO_E_KEY_WRITE_FAIL
    #define CRYPTO_E_KEY_WRITE_FAIL     0x0007U
#endif

/** \brief  The service request failed because at least one required key element is not available.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_91043,1 */
#ifndef CRYPTO_E_KEY_NOT_AVAILABLE
    #define CRYPTO_E_KEY_NOT_AVAILABLE  0x0008U
#endif

/** \brief  The service request failed because the key is invalid.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_91043,1 */
#ifndef CRYPTO_E_KEY_NOT_VALID
    #define CRYPTO_E_KEY_NOT_VALID      0x0009U
#endif

/** \brief  The service request failed because the key size does not match.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_91043,1 */
#ifndef CRYPTO_E_KEY_SIZE_MISMATCH
    #define CRYPTO_E_KEY_SIZE_MISMATCH  0x000AU
#endif

/** \brief  The service request failed because the Job has been canceled.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_91043,1 */
#ifndef CRYPTO_E_JOB_CANCELED
    #define CRYPTO_E_JOB_CANCELED       0x000CU
#endif

/** \brief  The service request failed because of uninitialized source key element.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_91043,1 */
#ifndef CRYPTO_E_KEY_EMPTY
    #define CRYPTO_E_KEY_EMPTY          0x000DU
#endif

[!IF "node:existsAndTrue(as:modconf('Base')/GeneralTypes/Crypto_GeneralTypes/Crypto_GeneralTypes_R2111_CustomServiceApis)"!][!//
/** \brief  Custom processing failed.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_91043_ADD01,1 */
#ifndef CRYPTO_E_CUSTOM_ERROR
    #define CRYPTO_E_CUSTOM_ERROR       0x000EU
#endif

[!ENDIF!][!//
[!//
/* --- Crypto_AlgorithmFamilyType --------------------------------------------------------------- */

/** \brief  Algorithm family is not set.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_NOT_SET
    #define CRYPTO_ALGOFAM_NOT_SET                  0x0000U
#endif /* #ifndef  CRYPTO_ALGOFAM_NOT_SET */

/** \brief  SHA1 hash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_SHA1
    #define CRYPTO_ALGOFAM_SHA1                     0x0001U
#endif /* #ifndef  CRYPTO_ALGOFAM_SHA1 */

/** \brief  SHA2-224 hash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_SHA2_224
    #define CRYPTO_ALGOFAM_SHA2_224                 0x0002U
#endif /* #ifndef  CRYPTO_ALGOFAM_SHA2_224 */

/** \brief  SHA2-256 hash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_SHA2_256
    #define CRYPTO_ALGOFAM_SHA2_256                 0x0003U
#endif /* #ifndef  CRYPTO_ALGOFAM_SHA2_256 */

/** \brief  SHA2-384 hash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_SHA2_384
    #define CRYPTO_ALGOFAM_SHA2_384                 0x0004U
#endif /* #ifndef  CRYPTO_ALGOFAM_SHA2_384 */

/** \brief  SHA2-512 hash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_SHA2_512
    #define CRYPTO_ALGOFAM_SHA2_512                 0x0005U
#endif /* #ifndef  CRYPTO_ALGOFAM_SHA2_512 */

/** \brief  SHA2-512/224 hash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_SHA2_512_224
    #define CRYPTO_ALGOFAM_SHA2_512_224             0x0006U
#endif /* #ifndef  CRYPTO_ALGOFAM_SHA2_512_224 */

/** \brief  SHA2-512/256 hash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_SHA2_512_256
    #define CRYPTO_ALGOFAM_SHA2_512_256             0x0007U
#endif /* #ifndef  CRYPTO_ALGOFAM_SHA2_512_256 */

/** \brief  SHA3-224 hash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_SHA3_224
    #define CRYPTO_ALGOFAM_SHA3_224                 0x0008U
#endif /* #ifndef  CRYPTO_ALGOFAM_SHA3_224 */

/** \brief  SHA3-256 hash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_SHA3_256
    #define CRYPTO_ALGOFAM_SHA3_256                 0x0009U
#endif /* #ifndef  CRYPTO_ALGOFAM_SHA3_256 */

/** \brief  SHA3-384 hash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_SHA3_384
    #define CRYPTO_ALGOFAM_SHA3_384                 0x000AU
#endif /* #ifndef  CRYPTO_ALGOFAM_SHA3_384 */

/** \brief  SHA3-512 hash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_SHA3_512
    #define CRYPTO_ALGOFAM_SHA3_512                 0x000BU
#endif /* #ifndef  CRYPTO_ALGOFAM_SHA3_512 */

/** \brief  SHAKE128 hash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_SHAKE128
    #define CRYPTO_ALGOFAM_SHAKE128                 0x000CU
#endif /* #ifndef  CRYPTO_ALGOFAM_SHAKE128 */

/** \brief  SHAKE256 hash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_SHAKE256
    #define CRYPTO_ALGOFAM_SHAKE256                 0x000DU
#endif /* #ifndef  CRYPTO_ALGOFAM_SHAKE256 */

/** \brief  RIPEMD hash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_RIPEMD160
    #define CRYPTO_ALGOFAM_RIPEMD160                0x000EU
#endif /* #ifndef  CRYPTO_ALGOFAM_RIPEMD160 */

/** \brief  BLAKE-1-256 hash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_BLAKE_1_256
    #define CRYPTO_ALGOFAM_BLAKE_1_256              0x000FU
#endif /* #ifndef  CRYPTO_ALGOFAM_BLAKE_1_256 */

/** \brief  BLAKE-1-512 hash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_BLAKE_1_512
    #define CRYPTO_ALGOFAM_BLAKE_1_512              0x0010U
#endif /* #ifndef  CRYPTO_ALGOFAM_BLAKE_1_512 */

/** \brief  BLAKE-2s-256 hash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_BLAKE_2s_256
    #define CRYPTO_ALGOFAM_BLAKE_2s_256             0x0011U
#endif /* #ifndef  CRYPTO_ALGOFAM_BLAKE_2s_256 */

/** \brief  BLAKE-2s-512 hash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_BLAKE_2s_512
    #define CRYPTO_ALGOFAM_BLAKE_2s_512             0x0012U
#endif /* #ifndef  CRYPTO_ALGOFAM_BLAKE_2s_512 */

/** \brief  3DES cipher.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_3DES
    #define CRYPTO_ALGOFAM_3DES                     0x0013U
#endif /* #ifndef  CRYPTO_ALGOFAM_3DES */

/** \brief  AES cipher.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_AES
    #define CRYPTO_ALGOFAM_AES                      0x0014U
#endif /* #ifndef  CRYPTO_ALGOFAM_AES */

/** \brief  ChaCha cipher.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_CHACHA
    #define CRYPTO_ALGOFAM_CHACHA                   0x0015U
#endif /* #ifndef  CRYPTO_ALGOFAM_CHACHA */

/** \brief  RSA cipher.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_RSA
    #define CRYPTO_ALGOFAM_RSA                      0x0016U
#endif /* #ifndef  CRYPTO_ALGOFAM_RSA */

/** \brief  ED22519 elliptic curve.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_ED25519
    #define CRYPTO_ALGOFAM_ED25519                  0x0017U
#endif /* #ifndef  CRYPTO_ALGOFAM_ED25519 */

/** \brief  Brainpool elliptic curve.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_BRAINPOOL
    #define CRYPTO_ALGOFAM_BRAINPOOL                0x0018U
#endif /* #ifndef  CRYPTO_ALGOFAM_BRAINPOOL */

/** \brief  NIST ECC elliptic curves.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_ECCNIST
    #define CRYPTO_ALGOFAM_ECCNIST                  0x0019U
#endif /* #ifndef  CRYPTO_ALGOFAM_ECCNIST */

/** \brief  Random Number Generator.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_RNG
    #define CRYPTO_ALGOFAM_RNG                      0x001BU
#endif /* #ifndef  CRYPTO_ALGOFAM_RNG */

/** \brief  SipHash.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_SIPHASH
    #define CRYPTO_ALGOFAM_SIPHASH                  0x001CU
#endif /* #ifndef  CRYPTO_ALGOFAM_SIPHASH */

/** \brief  Elliptic curve according to ANSI X9.62.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_ECCANSI
    #define CRYPTO_ALGOFAM_ECCANSI                  0x001EU
#endif /* #ifndef  CRYPTO_ALGOFAM_ECCANSI */

/** \brief  Elliptic curve according to SECG.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_ECCSEC
    #define CRYPTO_ALGOFAM_ECCSEC                   0x001FU
#endif /* #ifndef  CRYPTO_ALGOFAM_ECCSEC */

/** \brief  Random number generator according to NIST SP800-90A.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_DRBG
    #define CRYPTO_ALGOFAM_DRBG                     0x0020U
#endif /* #ifndef  CRYPTO_ALGOFAM_DRBG */

/** \brief  Random number generator according to FIPS 186.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_FIPS186
    #define CRYPTO_ALGOFAM_FIPS186                  0x0021U
#endif /* #ifndef  CRYPTO_ALGOFAM_FIPS186 */

/** \brief  Cipher padding according to PKCS.7.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_PADDING_PKCS7
    #define CRYPTO_ALGOFAM_PADDING_PKCS7            0x0022U
#endif /* #ifndef  CRYPTO_ALGOFAM_PADDING_PKCS7 */

/** \brief  Cipher padding mode. Fill/verify data with 0, but first bit after the data is 1.
 **         Eg. 'DATA' & 0x80 & 0x00….
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_PADDING_ONEWITHZEROS
    #define CRYPTO_ALGOFAM_PADDING_ONEWITHZEROS     0x0023U
#endif /* #ifndef  CRYPTO_ALGOFAM_PADDING_ONEWITHZEROS */

/** \brief  Password-Based Key Derivation Function 2.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_PBKDF2
    #define CRYPTO_ALGOFAM_PBKDF2                   0x0024U
#endif /* #ifndef  CRYPTO_ALGOFAM_PBKDF2 */

/** \brief  ANSI X9.63 Public Key Cryptography.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_KDFX963
    #define CRYPTO_ALGOFAM_KDFX963                  0x0025U
#endif /* #ifndef  CRYPTO_ALGOFAM_KDFX963 */

/** \brief  Diffie-Hellman.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_DH
    #define CRYPTO_ALGOFAM_DH                       0x0026U
#endif /* #ifndef  CRYPTO_ALGOFAM_DH */

/** \brief  SM2 elliptic curve algorithm.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_SM2
    #define CRYPTO_ALGOFAM_SM2                      0x0027U
#endif /* #ifndef  CRYPTO_ALGOFAM_SM2 */

/** \brief  Stream cipher based on [x01].
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_EEA3
    #define CRYPTO_ALGOFAM_EEA3                     0x0028U
#endif /* #ifndef  CRYPTO_ALGOFAM_EEA3 */

/** \brief  Chinese hash algorithm based on [x02].
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_SM3
    #define CRYPTO_ALGOFAM_SM3                      0x0029U
#endif /* #ifndef  CRYPTO_ALGOFAM_SM3 */

/** \brief  Authentication algorithm [x01].
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_EIA3
    #define CRYPTO_ALGOFAM_EIA3                     0x002AU
#endif /* #ifndef  CRYPTO_ALGOFAM_EIA3 */

/** \brief  HMAC-based extract-and-expand key derivation function.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_HKDF
    #define CRYPTO_ALGOFAM_HKDF                     0x002BU
#endif /* #ifndef  CRYPTO_ALGOFAM_HKDF */

/** \brief  Elliptic-curve Digital Signatures.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_ECDSA
    #define CRYPTO_ALGOFAM_ECDSA                    0x002CU
#endif /* #ifndef  CRYPTO_ALGOFAM_ECDSA */

/** \brief  MAC calculation algorithm.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_POLY1305
    #define CRYPTO_ALGOFAM_POLY1305                 0x002DU
#endif /* #ifndef  CRYPTO_ALGOFAM_POLY1305 */

/** \brief  Elliptic curve X25519 for ECDH.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_X25519
    #define CRYPTO_ALGOFAM_X25519                   0x002EU
#endif /* #ifndef  CRYPTO_ALGOFAM_X25519 */

/** \brief  Elliptic-curve Diffie Hellman.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_ECDH
    #define CRYPTO_ALGOFAM_ECDH                     0x002FU
#endif /* #ifndef  CRYPTO_ALGOFAM_ECDH */

/** \brief  Custom algorithm family.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
#ifndef CRYPTO_ALGOFAM_CUSTOM
    #define CRYPTO_ALGOFAM_CUSTOM                   0x00FFU
#endif /* #ifndef  CRYPTO_ALGOFAM_CUSTOM */

/* --- Crypto_AlgorithmModeType ----------------------------------------------------------------- */

/** \brief  Algorithm key is not set.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_NOT_SET
    #define CRYPTO_ALGOMODE_NOT_SET                 0x0000U
#endif /* #ifndef  CRYPTO_ALGOMODE_NOT_SET */

/** \brief  Blockmode: Electronic Code Book.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_ECB
    #define CRYPTO_ALGOMODE_ECB                     0x0001U
#endif /* #ifndef  CRYPTO_ALGOMODE_ECB */

/** \brief  Blockmode: Cipher Block Chaining.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_CBC
    #define CRYPTO_ALGOMODE_CBC                     0x0002U
#endif /* #ifndef  CRYPTO_ALGOMODE_CBC */

/** \brief  Blockmode: Cipher Feedback Mode.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_CFB
    #define CRYPTO_ALGOMODE_CFB                     0x0003U
#endif /* #ifndef  CRYPTO_ALGOMODE_CFB */

/** \brief  Blockmode: Output Feedback Mode.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_OFB
    #define CRYPTO_ALGOMODE_OFB                     0x0004U
#endif /* #ifndef  CRYPTO_ALGOMODE_OFB */

/** \brief  Blockmode: Counter Modex.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_CTR
    #define CRYPTO_ALGOMODE_CTR                     0x0005U
#endif /* #ifndef  CRYPTO_ALGOMODE_CTR */

/** \brief  Blockmode: Galois/Counter Mode.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_GCM
    #define CRYPTO_ALGOMODE_GCM                     0x0006U
#endif /* #ifndef  CRYPTO_ALGOMODE_GCM */

/** \brief  XEX Tweakable Block Cipher with Ciphertext Stealing.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_XTS
    #define CRYPTO_ALGOMODE_XTS                     0x0007U
#endif /* #ifndef  CRYPTO_ALGOMODE_XTS */

/** \brief  RSA Optimal Asymmetric Encryption Padding.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_RSAES_OAEP
    #define CRYPTO_ALGOMODE_RSAES_OAEP              0x0008U
#endif /* #ifndef  CRYPTO_ALGOMODE_RSAES_OAEP */

/** \brief  RSA encryption/decryption with PKCS#1 v1.5 padding.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_RSAES_PKCS1_v1_5
    #define CRYPTO_ALGOMODE_RSAES_PKCS1_v1_5        0x0009U
#endif /* #ifndef  CRYPTO_ALGOMODE_RSAES_PKCS1_v1_5 */

/** \brief  RSA Probabilistic Signature Scheme.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_RSASSA_PSS
    #define CRYPTO_ALGOMODE_RSASSA_PSS              0x000AU
#endif /* #ifndef  CRYPTO_ALGOMODE_RSASSA_PSS */

/** \brief  RSA signature with PKCS#1 v1.5.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5
    #define CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5       0x000BU
#endif /* #ifndef  CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5 */

/** \brief  8 rounds (e.g. ChaCha8).
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_8ROUNDS
    #define CRYPTO_ALGOMODE_8ROUNDS                 0x000CU
#endif /* #ifndef  CRYPTO_ALGOMODE_8ROUNDS */

/** \brief  12 rounds (e.g. ChaCha12).
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_12ROUNDS
    #define CRYPTO_ALGOMODE_12ROUNDS                0x000DU
#endif /* #ifndef  CRYPTO_ALGOMODE_12ROUNDS */

/** \brief  20 rounds (e.g. ChaCha20).
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_20ROUNDS
    #define CRYPTO_ALGOMODE_20ROUNDS                0x000EU
#endif /* #ifndef  CRYPTO_ALGOMODE_20ROUNDS */

/** \brief  Hashed-based MAC.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_HMAC
    #define CRYPTO_ALGOMODE_HMAC                    0x000FU
#endif /* #ifndef  CRYPTO_ALGOMODE_HMAC */

/** \brief  Cipher-based MAC.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_CMAC
    #define CRYPTO_ALGOMODE_CMAC                    0x0010U
#endif /* #ifndef  CRYPTO_ALGOMODE_CMAC */

/** \brief  Galois MAC.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_GMAC
    #define CRYPTO_ALGOMODE_GMAC                    0x0011U
#endif /* #ifndef  CRYPTO_ALGOMODE_GMAC */

/** \brief  Counter-based Deterministic Random Bit Generator.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_CTRDRBG
    #define CRYPTO_ALGOMODE_CTRDRBG                 0x0012U
#endif /* #ifndef  CRYPTO_ALGOMODE_CTRDRBG */

/** \brief  Siphash-2-4.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_SIPHASH_2_4
    #define CRYPTO_ALGOMODE_SIPHASH_2_4             0x0013U
#endif /* #ifndef  CRYPTO_ALGOMODE_SIPHASH_2_4 */

/** \brief  Siphash-4-8.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_SIPHASH_4_8
    #define CRYPTO_ALGOMODE_SIPHASH_4_8             0x0014U
#endif /* #ifndef  CRYPTO_ALGOMODE_SIPHASH_4_8 */

/** \brief  ANSI R1 Curve.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_PXXXR1
    #define CRYPTO_ALGOMODE_PXXXR1                  0x0015U
#endif /* #ifndef  CRYPTO_ALGOMODE_PXXXR1 */

/** \brief  Custom algorithm mode.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
#ifndef CRYPTO_ALGOMODE_CUSTOM
    #define CRYPTO_ALGOMODE_CUSTOM                  0x00FFU
#endif /* #ifndef  CRYPTO_ALGOMODE_CUSTOM */

/* --- Crypto_InputOutputRedirectionConfigType -------------------------------------------------- */

/** \brief   tbd
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_91024,1 */
#ifndef CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT
    #define CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT    0x0001U
#endif /* #ifndef  CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT */

/** \brief   tbd
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_91024,1 */
#ifndef CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT
    #define CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT  0x0002U
#endif /* #ifndef  CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT */

/** \brief   tbd
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_91024,1 */
#ifndef CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT
    #define CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT   0x0004U
#endif /* #ifndef  CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT */

/** \brief   tbd
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_91024,1 */
#ifndef CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT
    #define CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT   0x0010U
#endif /* #ifndef  CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT */

/** \brief   tbd
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_91024,1 */
#ifndef CRYPTO_REDIRECT_CONFIG_SECONDARY_OUTPUT
    #define CRYPTO_REDIRECT_CONFIG_SECONDARY_OUTPUT 0x0020U
#endif /* #ifndef  CRYPTO_REDIRECT_CONFIG_SECONDARY_OUTPUT */

/* --- Crypto_JobStateType ---------------------------------------------------------------------- */

/** \brief  Job is in the state 'idle'. This state is reached after Csm_Init() or when the
 **         'Finish' state is finished.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01028,1 */
#ifndef CRYPTO_JOBSTATE_IDLE
    #define CRYPTO_JOBSTATE_IDLE                    0x0000U
#endif /* #ifndef  CRYPTO_JOBSTATE_IDLE */

/** \brief  Job is in the state 'active'. There was already some input or there are
 **         intermediate results. This state is reached, when the 'update' or 'start' operation
 **         finishes.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01028,1 */
#ifndef CRYPTO_JOBSTATE_ACTIVE
    #define CRYPTO_JOBSTATE_ACTIVE                  0x0001U
#endif /* #ifndef  CRYPTO_JOBSTATE_ACTIVE */

/* --- Crypto_ProcessingType -------------------------------------------------------------------- */

/** \brief  Asynchronous job processing.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01049,1 */
#ifndef CRYPTO_PROCESSING_ASYNC
    #define CRYPTO_PROCESSING_ASYNC                 0x0000U
#endif /* #ifndef  CRYPTO_PROCESSING_ASYNC */

/** \brief  Synchronous job processing.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01049,1 */
#ifndef CRYPTO_PROCESSING_SYNC
    #define CRYPTO_PROCESSING_SYNC                  0x0001U
#endif /* #ifndef  CRYPTO_PROCESSING_SYNC */

/* --- Crypto_ServiceInfoType ------------------------------------------------------------------- */

/** \brief  Hash Service.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031,1 */
#ifndef CRYPTO_HASH
    #define CRYPTO_HASH                             0x0000U
#endif /* #ifndef  CRYPTO_HASH */

/** \brief  MacGenerate Service.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031,1 */
#ifndef CRYPTO_MACGENERATE
    #define CRYPTO_MACGENERATE                      0x0001U
#endif /* #ifndef  CRYPTO_MACGENERATE */

/** \brief  MacVerify Service.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031,1 */
#ifndef CRYPTO_MACVERIFY
    #define CRYPTO_MACVERIFY                        0x0002U
#endif /* #ifndef  CRYPTO_MACVERIFY */

/** \brief  Encrypt Service.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031,1 */
#ifndef CRYPTO_ENCRYPT
    #define CRYPTO_ENCRYPT                          0x0003U
#endif /* #ifndef  CRYPTO_ENCRYPT */

/** \brief  Decrypt Service.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031,1 */
#ifndef CRYPTO_DECRYPT
    #define CRYPTO_DECRYPT                          0x0004U
#endif /* #ifndef  CRYPTO_DECRYPT */

/** \brief  AEADEncrypt Service.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031,1 */
#ifndef CRYPTO_AEADENCRYPT
    #define CRYPTO_AEADENCRYPT                      0x0005U
#endif /* #ifndef  CRYPTO_AEADENCRYPT */

/** \brief  AEADDecrypt Service.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031,1 */
#ifndef CRYPTO_AEADDECRYPT
    #define CRYPTO_AEADDECRYPT                      0x0006U
#endif /* #ifndef  CRYPTO_AEADDECRYPT */

/** \brief  SignatureGenerate Service.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031,1 */
#ifndef CRYPTO_SIGNATUREGENERATE
    #define CRYPTO_SIGNATUREGENERATE                0x0007U
#endif /* #ifndef  CRYPTO_SIGNATUREGENERATE */

/** \brief  SignatureVerify Service.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031,1 */
#ifndef CRYPTO_SIGNATUREVERIFY
    #define CRYPTO_SIGNATUREVERIFY                  0x0008U
#endif /* #ifndef  CRYPTO_SIGNATUREVERIFY */

/** \brief  RandomGenerate Service.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031,1 */
#ifndef CRYPTO_RANDOMGENERATE
    #define CRYPTO_RANDOMGENERATE                   0x000BU
#endif /* #ifndef  CRYPTO_RANDOMGENERATE */

/** \brief  RandomSeed Service.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031,1 */
#ifndef CRYPTO_RANDOMSEED
    #define CRYPTO_RANDOMSEED                       0x000CU
#endif /* #ifndef  CRYPTO_RANDOMSEED */

/** \brief  KeyGenerate Service.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031,1 */
#ifndef CRYPTO_KEYGENERATE
    #define CRYPTO_KEYGENERATE                      0x000DU
#endif /* #ifndef  CRYPTO_KEYGENERATE */

/** \brief  KeyDerive Service.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031,1 */
#ifndef CRYPTO_KEYDERIVE
    #define CRYPTO_KEYDERIVE                        0x000EU
#endif /* #ifndef  CRYPTO_KEYDERIVE */

/** \brief  KeyExchangeCalcPubVal Service.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031,1 */
#ifndef CRYPTO_KEYEXCHANGECALCPUBVAL
    #define CRYPTO_KEYEXCHANGECALCPUBVAL            0x000FU
#endif /* #ifndef  CRYPTO_KEYEXCHANGECALCPUBVAL */

/** \brief  KeyExchangeCalcSecret Service.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031,1 */
#ifndef CRYPTO_KEYEXCHANGECALCSECRET
    #define CRYPTO_KEYEXCHANGECALCSECRET            0x0010U
#endif /* #ifndef  CRYPTO_KEYEXCHANGECALCSECRET */

/** \brief  KeySetValid Service.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031,1 */
#ifndef CRYPTO_KEYSETVALID
    #define CRYPTO_KEYSETVALID                      0x0013U
#endif /* #ifndef  CRYPTO_KEYSETVALID */

/** \brief  KeySetInvalid Service.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031,1 */
#ifndef CRYPTO_KEYSETINVALID
    #define CRYPTO_KEYSETINVALID                    0x0014U
#endif /* #ifndef  CRYPTO_KEYSETINVALID */

[!IF "node:existsAndTrue(as:modconf('Base')/GeneralTypes/Crypto_GeneralTypes/Crypto_GeneralTypes_R2111_CustomServiceApis)"!][!//
/** \brief  Custom service job.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031_ADD01,1 */
#ifndef CRYPTO_CUSTOM_SERVICE
    #define CRYPTO_CUSTOM_SERVICE                   0x0015U
#endif /* #ifndef  CRYPTO_CUSTOM_SERVICE */

[!ENDIF!][!//
[!//
/*==================[type definitions]============================================================*/

/** \brief  Enumeration of the algorithm family.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01047,1 */
typedef uint8 Crypto_AlgorithmFamilyType;

/** \brief  Enumeration of the algorithm mode.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01048,1 */
typedef uint8 Crypto_AlgorithmModeType;

/** \brief  Defines which of the input/output parameters are re-directed to a key element. The
 **         values can be combined to define a bit field.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_91024,1 */
typedef uint8 Crypto_InputOutputRedirectionConfigType;

/** \brief  Enumeration of the current job state.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01028,1 */
typedef uint8 Crypto_JobStateType;

/** \brief  Enumeration of the processing type.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01049,1 */
typedef uint8 Crypto_ProcessingType;

/** \brief  Enumeration of the kind of the service.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01031,1 */
typedef uint8 Crypto_ServiceInfoType;

/** \brief  Structure which determines the exact algorithm. Note, not every algorithm needs to
 **         specify all fields. AUTOSAR shall only allow valid combinations.
 **
 ** \var    family
 ** \brief  The family of the algorithm.
 **
 ** \var    secondaryFamily
 ** \brief  The secondary family of the algorithm.
 **
 ** \var    keyLength
 ** \brief  The key length in bits to be used with that algorithm.
 **
 ** \var    mode
 ** \brief  The operation mode to be used with that algorithm.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01008,1 */
typedef struct
{
  Crypto_AlgorithmFamilyType family;
  Crypto_AlgorithmFamilyType secondaryFamily;
  uint32                     keyLength;
  Crypto_AlgorithmModeType   mode;
}
Crypto_AlgorithmInfoType;

/** \brief  Structure which contains basic information about the crypto primitive.
 **
 ** \var    service
 ** \brief  Contains the enum of the used service, e.g. Encrypt.
 **
 ** \var    algorithm
 ** \brief  Contains the information of the used algorithm.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01011,1 */
typedef struct
{
  CONST(Crypto_ServiceInfoType,   CSM_CONST) service;
  CONST(Crypto_AlgorithmInfoType, CSM_CONST) algorithm;
}
Crypto_PrimitiveInfoType;

/** \brief  Structure which contains further information, which depends on the job and the
 **         crypto primitive.
 **
 ** \var    callbackId
 ** \brief  Internal identifier of the callback function, to be called by Csm, if the
 **         configured service is finished.
 **
 ** \var    primitiveInfo
 ** \brief  Pointer to a structure containing further configuration of the crypto primitives.
 **
 ** \var    cryIfKeyId
 ** \brief  Identifier of the CryIf key.
 **
 ** \var    processingType
 ** \brief  Determines the synchronous or asynchronous behavior.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01012,1 */
typedef struct
{
          uint32                                              callbackId;
  P2CONST(Crypto_PrimitiveInfoType, AUTOMATIC, CSM_APPL_DATA) primitiveInfo;
          uint32                                              cryIfKeyId;
          Crypto_ProcessingType                               processingType;
}
Crypto_JobPrimitiveInfoType;

/** \brief  Structure which contains input and output information depending on the job and the
 **         crypto primitive.
 **
 ** \var    inputPtr
 ** \brief  Pointer to the input data.
 **
 ** \var    inputLength
 ** \brief  Contains the input length in bytes.
 **
 ** \var    secondaryInputPtr
 ** \brief  Pointer to the secondary input data (for MacVerify, SignatureVerify).
 **
 ** \var    secondaryInputLength
 ** \brief  Contains the secondary input length in bits or bytes, depending on the requested
 **         service.
 **
 ** \var    tertiaryInputPtr
 ** \brief  Pointer to the tertiary input data (for MacVerify, SignatureVerify).
 **
 ** \var    tertiaryInputLength
 ** \brief  Contains the tertiary input length in bytes.
 **
 ** \var    outputPtr
 ** \brief  Pointer to the output data.
 **
 ** \var    outputLengthPtr
 ** \brief  Holds a pointer to a memory location containing the output length in bytes.
 **
 ** \var    secondaryOutputPtr
 ** \brief  Pointer to the secondary output data.
 **
 ** \var    secondaryOutputLengthPtr
 ** \brief  Holds a pointer to a memory location containing the secondary output length in
 **         bytes.
 **
 ** \var    verifyPtr
 ** \brief  Output pointer to a memory location holding a Crypto_VerifyResultType.
 **
 ** \var    mode
 ** \brief  Indicator of the mode(s)/operation(s) to be performed.
 **
 ** \var    cryIfKeyId
 ** \brief  Holds the CryIf key id for key operation services.
 **
 ** \var    targetCryIfKeyId
 ** \brief  Holds the target CryIf key id for key operation services.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01009,1 */
typedef struct
{
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) inputPtr;
          uint32                                              inputLength;
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) secondaryInputPtr;
          uint32                                              secondaryInputLength;
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) tertiaryInputPtr;
          uint32                                              tertiaryInputLength;
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) outputPtr;
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) outputLengthPtr;
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) secondaryOutputPtr;
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) secondaryOutputLengthPtr;
    P2VAR(Crypto_VerifyResultType,  AUTOMATIC, CSM_APPL_DATA) verifyPtr;
          Crypto_OperationModeType                            mode;
          uint32                                              cryIfKeyId;
          uint32                                              targetCryIfKeyId;
}
Crypto_JobPrimitiveInputOutputType;

/** \brief  Structure which holds the identifiers of the keys and key elements which shall be
 **         used as input and output for a job and a bit structure which indicates which
 **         buffers shall be redirected to those key elements.
 **
 ** \var    redirectionConfig
 ** \brief  Bit structure which indicates which buffer shall be redirected to a key element.
 **         Values from Crypto_InputOutputRedirectionConfigType can be used and combined with
 **         unary OR operation.
 **
 ** \var    inputKeyId
 ** \brief  Identifier of the key which shall be used as input.
 **
 ** \var    inputKeyElementId
 ** \brief  Identifier of the key element which shall be used as input.
 **
 ** \var    secondaryInputKeyId
 ** \brief  Identifier of the key which shall be used as secondary input.
 **
 ** \var    secondaryInputKeyElementId
 ** \brief  Identifier of the key element which shall be used as secondary input.
 **
 ** \var    tertiaryInputKeyId
 ** \brief  Identifier of the key which shall be used as tertiary input.
 **
 ** \var    tertiaryInputKeyElementId
 ** \brief  Identifier of the key element which shall be used as tertiary input.
 **
 ** \var    outputKeyId
 ** \brief  Identifier of the key which shall be used as output.
 **
 ** \var    outputKeyElementId
 ** \brief  Identifier of the key element which shall be used as output.
 **
 ** \var    secondaryOutputKeyId
 ** \brief  Identifier of the key which shall be used as secondary output.
 **
 ** \var    secondaryOutputKeyElementId
 ** \brief  Identifier of the key element which shall be used as secondary output.
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_91026,1 */
typedef struct
{
  uint8  redirectionConfig;
  uint32 inputKeyId;
  uint32 inputKeyElementId;
  uint32 secondaryInputKeyId;
  uint32 secondaryInputKeyElementId;
  uint32 tertiaryInputKeyId;
  uint32 tertiaryInputKeyElementId;
  uint32 outputKeyId;
  uint32 outputKeyElementId;
  uint32 secondaryOutputKeyId;
  uint32 secondaryOutputKeyElementId;
}
Crypto_JobRedirectionInfoType;

/** \brief  Structure which contains further information, which depends on the job and the
 **         crypto primitive.
 **
 ** \var    jobId
 ** \brief  Identifier for the job structure.
 **
 ** \var    jobState
 ** \brief  Determines the current job state.
 **
 ** \var    jobPrimitiveInputOutput
 ** \brief  Structure containing input and output information depending on the job and the
 **         crypto primitive.
 **
 ** \var    jobPrimitiveInfo
 ** \brief  Pointer to a structure containing further information which depends on the job and
 **         the crypto primitive.
 **
 ** \var    jobRedirectionInfoRef
 ** \brief  Pointer to a structure containing further information on the usage of keys as input
 **         and output for jobs.
 **
 ** \var    cryptoKeyId
 ** \brief  Identifier of the Crypto Driver key. The identifier shall be written by the Crypto
 **         Interface.
 **
 ** \var    targetCryptoKeyId
 ** \brief  Target identifier of the Crypto Driver key. The identifier shall be written by the
 **         Crypto Interface.
 **
 ** \var    jobPriority
 ** \brief  Specifies the importance of the job (the higher, the more important).
 **/
/* !LINKSTO Base.ASR21-11.SWS_Csm_01013,1 */
typedef struct
{
          uint32                                                        jobId;
          Crypto_JobStateType                                           jobState;
          Crypto_JobPrimitiveInputOutputType                            jobPrimitiveInputOutput;
  P2CONST(Crypto_JobPrimitiveInfoType,        AUTOMATIC, CSM_APPL_DATA) jobPrimitiveInfo;
    P2VAR(Crypto_JobRedirectionInfoType,      AUTOMATIC, CSM_APPL_DATA) jobRedirectionInfoRef;
          uint32                                                        cryptoKeyId;
          uint32                                                        targetCryptoKeyId;
    CONST(uint32,                                        CSM_CONST    ) jobPriority;
}
Crypto_JobType;

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

/*================================================================================================*/
