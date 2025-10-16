/* --------{ EB Automotive C Source File }-------- */

/* MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 20.7 (required)
 *   "Expressions resulting from the expansion of macro parameters shall be
 *    enclosed in parentheses."
 *  Reason:
 *  The AUTOSAR compiler abstraction requires these definitions in this way
 *  and the arguments cannot be enclosed in parentheses due to C syntax.
 */

/* !LINKSTO EB_CRY_0009,1 */

/*==[Includes]================================================================*/

#include <Cry_Der.h>
#include <Cry_DerCVC.h>  /* !LINKSTO EB_CRY_0010,1 */
#include <Cry_Common.h>

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

static FUNC(void, CRY_CODE) Cry_DerParseDate
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) Encoding,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) date
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* The description of a CV certificate */

/* The description of an RSA public key inside a CVC certificate */

/** \brief A description of the subcomponent "OID" of "RSAPublicKey" */
static CONST(Cry_DerComponentType, CRY_CONST) Cry_DerCVCRSAPubKCptOid =
{
   &Cry_DerParseFunctionsObjectIdentifier,
   0U, NULL_PTR,
   0U, NULL_PTR
};

/** \brief A description of the subcomponent "modulus" of "RSAPublicKey" */
static CONST(Cry_DerComponentType, CRY_CONST) Cry_DerCVCRSAPubKCptModulus =
{
   &Cry_DerParseFunctionsInteger,
   0U, NULL_PTR,
   0U, NULL_PTR
};

/** \brief A description of the subcomponent "publicKeyExponent" of
 * "RSAPublicKey"
 */
static CONST(Cry_DerComponentType, CRY_CONST) Cry_DerCVCRSAPubKCptPubKeyExp =
{
   &Cry_DerParseFunctionsInteger,
   0U, NULL_PTR,
   0U, NULL_PTR
};

/** \brief A description of the subcomponents of "SubjectPublicKeyInfo" */
static CONST(Cry_DerSubComponentType, CRY_CONST) Cry_DerCVCSubCptsSbjPbKeyInfo[] =
{
    {CRY_DER_TAG_OID,     &Cry_DerCVCRSAPubKCptOid, FALSE },
    {CRY_DER_TAG_MODULUS, &Cry_DerCVCRSAPubKCptModulus, FALSE },
    {CRY_DER_TAG_EXP,     &Cry_DerCVCRSAPubKCptPubKeyExp, FALSE }
};

/** \brief A description of the component "SubjectPublicKeyInfo" */
static CONST(Cry_DerComponentType, CRY_CONST) Cry_DerCVCCptSbjPbKeyInfo =
{
  &Cry_DerParseFunctionsSequence,
  0U, NULL_PTR,
  CRY_DER_ARRAY_INFO(Cry_DerCVCSubCptsSbjPbKeyInfo)
};

/** \brief A description of the subcomponents of "Hold Auth template" */
static CONST(Cry_DerSubComponentType, CRY_CONST) Cry_DerCVCSubCptsHoldAuthTem[] =
{
  {CRY_DER_TAG_OID,            &Cry_DerCptObjIdentifier, FALSE },
  {CRY_DER_TAG_DISCRETIONDATA, &Cry_DerCptOctetString,   FALSE },
};

/** \brief A description of the component "Hold Auth template" */
static CONST(Cry_DerComponentType, CRY_CONST) Cry_DerCVCCptHoldAuthTem =
{
  &Cry_DerParseFunctionsSequence,
  0U, NULL_PTR,
  CRY_DER_ARRAY_INFO(Cry_DerCVCSubCptsHoldAuthTem)
};

/** \brief The allowed ranges for "Identifier"  */
static CONST(Cry_DerRangeType, CRY_CONST) Cry_DerCVCRangesIden[] =
{
  {
    0,
    0,
    FALSE
  }
};

/** \brief A description of the component "Version" */
static CONST(Cry_DerComponentType, CRY_CONST) Cry_DerCVCCptIden =
{
  &Cry_DerParseFunctionsInteger,
  CRY_DER_ARRAY_INFO(Cry_DerCVCRangesIden),
  0U, NULL_PTR
};

/** \brief A description of the component "CertificateSerialNumber" */
static CONST(Cry_DerComponentType, CRY_CONST) Cry_DerCVCCptCertDate =
{
  &Cry_DerParseFunctionsDate,
  0U, NULL_PTR,
  0U, NULL_PTR
};

/** \brief A description of the component "CertificateCharacterString" */
static CONST(Cry_DerComponentType, CRY_CONST) Cry_DerCptCharacterS =
{
  &Cry_DerParseFunctionsCharacterS,
  0U, NULL_PTR,
  0U, NULL_PTR
};

/** \brief A description of the subcomponents of "TBSCertificate" */
static CONST(Cry_DerSubComponentType, CRY_CONST) Cry_DerCVCSubCptsTBSCert[] =
{
  {CRY_DER_TAG_PROFILE_ID,     &Cry_DerCVCCptIden,         FALSE }, /* Profile Identifier */
  {CRY_DER_TAG_AUTHREF,        &Cry_DerCptCharacterS,      FALSE }, /* Authority Reference */
  {CRY_DER_TAG_PUBKEY,         &Cry_DerCVCCptSbjPbKeyInfo, FALSE }, /* Public Key */
  {CRY_DER_TAG_HOLDREF,        &Cry_DerCptCharacterS,      FALSE }, /* Holder Reference */
  {CRY_DER_TAG_HOLDAUTHTEMPL,  &Cry_DerCVCCptHoldAuthTem,  FALSE }, /* Holder Authorization Template */
  {CRY_DER_TAG_EFFECTIVEDATE,  &Cry_DerCVCCptCertDate,     FALSE }, /* Effective Date */
  {CRY_DER_TAG_EXPIRATIONDATE, &Cry_DerCVCCptCertDate,     FALSE }, /* Expiration Date */
};

/** \brief A description of the component "TBSCertificate" */
static CONST(Cry_DerComponentType, CRY_CONST) Cry_DerCVCCptTBSCert =
{
  &Cry_DerParseFunctionsSequence,
  0U, NULL_PTR,
  CRY_DER_ARRAY_INFO(Cry_DerCVCSubCptsTBSCert)
};

/** \brief A description of the subcomponents of "Certificate" */
static CONST(Cry_DerSubComponentType, CRY_CONST) Cry_DerCVCSubCptsCertificate[] =
{
  {CRY_DER_TAG_CERTBODY, &Cry_DerCVCCptTBSCert, FALSE },
  {CRY_DER_TAG_SIGNATURE, &Cry_DerCptOctetString, FALSE }
};

/** \brief A description of the component "Certificate" */
static CONST(Cry_DerComponentType, CRY_CONST) Cry_DerCVCCptCertificate =
{
  &Cry_DerParseFunctionsSequence,
  0U, NULL_PTR,
  CRY_DER_ARRAY_INFO(Cry_DerCVCSubCptsCertificate)
};


#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

FUNC(boolean, CRY_CODE) Cry_DerCVCCheckCertificate
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) Encoding,
          uint32                           EncodingLength
)
{
  uint32 CurrentPos;   /* The current position in the encoding */
  boolean Valid;

  /* Check the validity of the CVC certificate */
  if
  (
    CRY_DER_CHECK_FUNCTION
    (
      &Cry_DerCVCCptCertificate,
      Encoding,
      EncodingLength,
      &CurrentPos
    ) &&
    (CurrentPos == EncodingLength)
  )
  {
    Valid = TRUE;
  }
  else
  {
    /* The length of the certificate is not correct or the certificate was
     * completely invalid.
     */
    Valid = FALSE;
  }

  return Valid;
}

/*------------------------------------------------------------------------------------------------*/
/* Deviation MISRAC2012-1 */
FUNC(P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA), CRY_CODE) Cry_DerCVCGetSignatureValue
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) Encoding,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) ThingLengthPtr
)
{
  return &Encoding[CRY_DER_1ST_SUB_CMP_CONTENTS
                  (
                     &Cry_DerCVCCptCertificate,
                     Encoding,
                     &Cry_DerCVCSubCptsCertificate[1U],
                     ThingLengthPtr
                  )];
}

/*------------------------------------------------------------------------------------------------*/
/* Deviation MISRAC2012-1 */
FUNC(P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA), CRY_CODE) Cry_DerCVCGetSignedData
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) Encoding,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) ThingLengthPtr
)
{
  uint32 Position;
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) ResultPtr;
  /* CHECK: NOPARSE */
  /* Because the certificate is have check for validity the function should be found. The only
   * possibility is here to fail is when the initially buffer is valid but later it is somehow
   * corrupted.
   */
  if
  (
    CRY_DER_FIND_FUNCTION
    (
       &Cry_DerCVCCptCertificate,
       Encoding,
       &Cry_DerCVCSubCptsCertificate[0],
       &Position,
       0
    ) == TRUE
  )
  {
    *ThingLengthPtr = Cry_DerEncGetContentsStart(&Encoding[Position]) +
                      Cry_DerEncGetContentsLength(&Encoding[Position]);

    ResultPtr = &Encoding[Position];
  }
  else
  {
    *ThingLengthPtr = 0;

    ResultPtr = NULL_PTR;
  }
  /* CHECK: PARSE */

  return ResultPtr;
}

/*------------------------------------------------------------------------------------------------*/
/* Deviation MISRAC2012-1 */
FUNC(P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA), CRY_CODE) Cry_DerCVCRSAPubKeyGetExponent
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) Encoding,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) ExponentLengthPtr
)
{

  /* Get to the start of the exponent */

  return &Encoding[CRY_DER_1ST_SUB_CMP_CONTENTS
                    (
                      &Cry_DerCVCCptCertificate,
                      Encoding,
                      &Cry_DerCVCSubCptsSbjPbKeyInfo[2],
                      ExponentLengthPtr
                    )];
}

/*------------------------------------------------------------------------------------------------*/
/* Deviation MISRAC2012-1 */
FUNC(P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA), CRY_CODE) Cry_DerCVCRSAPubKeyGetModulus
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) Encoding,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) ModulusLengthPtr
)
{
  /* Get to the start of the modulus */

  return &Encoding[CRY_DER_1ST_SUB_CMP_CONTENTS
                      (
                        &Cry_DerCVCCptCertificate,
                        Encoding,
                        &Cry_DerCVCSubCptsSbjPbKeyInfo[1],
                        ModulusLengthPtr
                      )];
}

/*------------------------------------------------------------------------------------------------*/

FUNC(void, CRY_CODE) Cry_DerCVCGetDate
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) Encoding,
  P2VAR(CVDateInfoType, AUTOMATIC, CRY_APPL_DATA) CVDate
)
{
  uint32 ThingLengthPtr;
  uint32 CurrentPos;

  /* Effective date */
  CurrentPos = Cry_DerSubComponentContents(&Cry_DerCVCCptCertificate,
                                           Encoding,
                                           &Cry_DerCVCSubCptsTBSCert[5U],
                                           &ThingLengthPtr,
                                           0
                                           );

  Cry_DerParseDate(&Encoding[CurrentPos], &(CVDate->EffectiveDate));

  /* Expiration date */
  CurrentPos = Cry_DerSubComponentContents(&Cry_DerCVCCptCertificate,
                                           Encoding,
                                           &Cry_DerCVCSubCptsTBSCert[6U],
                                           &ThingLengthPtr,
                                           0
                                           );

  Cry_DerParseDate(&Encoding[CurrentPos], &(CVDate->ExpirationDate));
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Definition of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief Extracting BCD encoded date from certificate.
 *
 * Date is in BCD format in the CV and extracting it according to that
 *
 * \param[in] EncodingPtr pointer to the start of the encoding of the value
 * \param[out] date        pointer of the return value where date will be stored
 *
 * \return none
 *
 */

static FUNC(void, CRY_CODE) Cry_DerParseDate
(
  P2CONST(uint8,  AUTOMATIC, CRY_APPL_DATA) Encoding,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) date
)
{
  uint32 year;
  uint32 month;
  uint32 day;

  *date = 0;

  year  = (uint32) (uint8) ((Encoding[0U] * 10U) + Encoding[1U]);
  month = (uint32) (uint8) ((Encoding[2U] * 10U) + Encoding[3U]);
  day   = (uint32) (uint8) ((Encoding[4U] * 10U) + Encoding[5U]);

  *date = ((year << 16U)) | (month << 8U) | day;
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>
