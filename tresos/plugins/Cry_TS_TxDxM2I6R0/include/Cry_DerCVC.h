/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0008,1 */

#ifndef CRY_DERCVC_H
#define CRY_DERCVC_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/** \var CVDateInfoType
 *  \brief Stores the date of expiration and effectiveness
 *         year:  data >> 16
 *         month: data >> 8 & 0xFF
 *         day:   data & 0xFF
 */
 /** \var CVDateInfoType::ExpirationDate
 *   \brief The Expiration date of the certificate.
 */
 /** \var CVDateInfoType::EffectiveDate
 *   \brief Starting date from which the certificate is valid.
 */
typedef struct CVDateInfoStruct
{
  uint32 ExpirationDate;
  uint32 EffectiveDate;

}CVDateInfoType;

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief Checks the validity of a CV certificate.
 *
 * Given a pointer to the start of the DER encoding of a CVC certifcate,
 * this function checks whether it is valid and whether its length is exactly
 * the length given as an argument.
 *
 * \param[in]  Encoding A pointer to the start of the DER encoding of
 *                      the certificate to be checked
 * \param[in]  EncodingLength The expected length of the certificate
 *
 * \return Validation result
 *
 * \retval ::TRUE If the certificate is valid and has the expected
 *                length
 * \retval ::FALSE If the certificate is invalid or does not have the
 *                 expected length
 */
extern FUNC(boolean, CRY_CODE) Cry_DerCVCCheckCertificate
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) Encoding,
          uint32                           EncodingLength
);

/** \brief Returns the signature stored in a CV certificate.
 *
 * Given a pointer to the start of the DER encoding of a CV certificate,
 * this function returns a pointer to the start of the signature of the certificate
 * and it also returns the length of the signature.
 *
 * See chapter 4.1.1.3 of RFC 2459.
 *
 * \param[in]  Encoding A pointer to the start of the DER encoding of
 *                      the certificate
 * \param[out] ThingLengthPointer A pointer to a variable where the length of
 *                                the signature will be stored
 *
 * \return A pointer to the start of the contents of the encoding of the
 *         signature
 */
extern FUNC(P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA), CRY_CODE) Cry_DerCVCGetSignatureValue
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) Encoding,
   P2VAR(uint32,  AUTOMATIC, CRY_APPL_DATA) ThingLengthPtr
);

/** \brief Returns the signed data in a CV certificate.
 *
 * Given a pointer to the start of the DER encoding of a CV certificate,
 * this function returns a pointer to the start of the data of the signature
 * which was signed and it also returns the length of the signed data.
 *
 * See chapter 4.1.2 of RFC 2459.
 *
 * \param[in]  Encoding A pointer to the start of the DER encoding of
 *                      the certificate
 * \param[out] ThingLengthPointer A pointer to a variable where the length of
 *                                the signed data will be stored
 *
 * \return A pointer to the start of signed data
 */
extern FUNC(P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA), CRY_CODE) Cry_DerCVCGetSignedData
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) Encoding,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) ThingLengthPtr
);

/** \brief Returns the exponent of the public RSA key stored in a CV certificate.
 *
 * Given a pointer to the start of the DER encoding of a CV certificate,
 * this function returns a pointer to the start of the exponent of the
 * public RSA key stored in the certificate and it also returns the length of the
 * exponent.
 *
 * See chapter 7.3.1 of RFC 2459.
 *
 * \param[in]  Encoding          A pointer to the start of the DER encoding of
 *                               the certificate
 * \param[out] ExponentLengthPtr A pointer to a variable where the length of
 *                                the exponent will be stored
 *
 * \return A pointer to the start of the contents of the encoding of the
 *         exponent of the public key
 */
extern FUNC(P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA), CRY_CODE) Cry_DerCVCRSAPubKeyGetExponent
(
  P2CONST(uint8,    AUTOMATIC, CRY_APPL_DATA) Encoding,
    P2VAR(uint32,   AUTOMATIC, CRY_APPL_DATA) ExponentLengthPtr
);

/** \brief Returns the modulus of the public RSA key stored in a CV certificate.
 *
 * Given a pointer to the start of the DER encoding of a CV certificate,
 * this function returns a pointer to the start of the modulus of the
 * public RSA key stored in the certificate and it also returns the length of the
 * modulus.
 *
 * See chapter 7.3.1 of RFC 2459.
 *
 * \param[in]  Encoding         A pointer to the start of the DER encoding of
 *                              the certificate
 * \param[out] ModulusLengthPtr A pointer to a variable where the length of
 *                              the modulus will be stored
 *
 * \return A pointer to the start of the contents of the encoding of the
 *         modulus of the public key
 */
extern FUNC(P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA), CRY_CODE) Cry_DerCVCRSAPubKeyGetModulus
(
  P2CONST(uint8,    AUTOMATIC, CRY_APPL_DATA) Encoding,
    P2VAR(uint32,   AUTOMATIC, CRY_APPL_DATA) ModulusLengthPtr
);

/** \brief Returns the expiration and effective date stored in a CV certificate.
 *
 * Given a pointer to the start of the DER encoding of a CV certificate, this
 * function extracts the dates (effective date and expiration date) and returns
 * them in the parameter CVDate.
 *
 * \param[in]  Encoding A pointer to the start of the DER encoding of
 *                      the certificate
 * \param[out] CVDate   A pointer to a structure where the dates will be stored
 *
 * \return void
 */
extern FUNC(void, CRY_CODE) Cry_DerCVCGetDate
(
  P2CONST(uint8,          AUTOMATIC, CRY_APPL_DATA) Encoding,
    P2VAR(CVDateInfoType, AUTOMATIC, CRY_APPL_DATA) CVDate
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /*CRY_DERCVC_H*/

