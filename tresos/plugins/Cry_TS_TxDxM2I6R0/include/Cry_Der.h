/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0008,1 */

/* MISRA-C:2004 Deviation List
 *
 * MISRA-1:
 * Deviated Rule: 19.7 - "A function should be used in preference to a
 *                        function-like macro."
 *
 * Reason:
 * The macros are called often and are very simple.
 *
 */

#ifndef CRY_DER_H
#define CRY_DER_H

/*==[Includes]================================================================*/

#include <Std_Types.h> /* standard types */

/*==[Macros]==================================================================*/

#if (defined CRY_DER_CHECK_FUNCTION)
#error CRY_DER_CHECK_FUNCTION is already defined
#endif
/** \brief Calls the check function for the given component.
 *
 * Given a description of a component and the start of the encoding of the
 * component, this macro calls the check function for that component. The check
 * function is extracted from the component description.
 *
 * \param[in] ComponentPtr pointer to the description of a component to check
 * \param[in] Encoding pointer to the start of the encoding of the component to
 *                     check
 * \param[in]  MaxLength The maximal allowed length of the encoding of the
 *                      component.
 * \param[out] LengthPtr A pointer to a variable where the length of the
 *                       encoding of the value will be stored if the
 *                       encoding is valid
 *
 *
 * \return The validity of the encoding of the component
 *
 * \retval ::TRUE If the encoding is valid
 * \retval ::FALSE If the encoding is invalid
 */
#define CRY_DER_CHECK_FUNCTION(ComponentPtr, Encoding, MaxLength, LengthPtr)  \
  (                                                                           \
    (ComponentPtr)->ParseFunctionsPtr->CheckFunction                          \
                                       (                                      \
                                          (ComponentPtr),                     \
                                          (Encoding),                         \
                                          (MaxLength),                        \
                                          (LengthPtr)                         \
                                       )                                      \
  )

#if (defined CRY_DER_FIND_FUNCTION)
#error CRY_DER_FIND_FUNCTION is already defined
#endif
/** \brief Calls the find function for the given component.
 *
 * Given a description of a component, the start of the encoding of the
 * component, and a description of the subcomponent to find, this macro calls
 * the find function for the component. The find function is extracted from the
 * component description.
 *
 * \param[in]  ComponentPtr A pointer to the description of the component which
 *                          has to be searched
 * \param[in]  Encoding A pointer to the start of the encoding of the component
 * \param[in]  SubComponentToFindPtr A pointer to the description of the
 *                                   subcomponent which has to be found
 * \param[out] PositionPtr A pointer to a variable where the following will
 *                         be stored if the search was successful: the byte
 *                         position of the encoding of the first occurrence
 *                         of the given subcomponent which fulfills the
 *                         requirement "position >= StartSearch"
 * \param[in]  StartSearch Subcomponents which start before this position in
 *                         the encoding are ignored in the search.
 *
 * \return The success value of the search
 *
 * \retval ::TRUE If the subcomponent has been found
 * \retval ::FALSE If the subcomponent has not been found
 */
#define CRY_DER_FIND_FUNCTION(                                     \
        ComponentPtr,                                              \
        Encoding,                                                  \
        SubComponentToFindPtr,                                     \
        PositionPtr,                                               \
        StartSearch                                                \
      )                                                            \
  (                                                                \
    (ComponentPtr)->ParseFunctionsPtr->FindFunction                \
                                       (                           \
                                          (ComponentPtr),          \
                                          (Encoding),              \
                                          (SubComponentToFindPtr), \
                                          (PositionPtr),           \
                                          (StartSearch)            \
                                       )                           \
  )

#if (defined CRY_DER_1ST_SUB_CMP_CONTENTS)
#error CRY_DER_1ST_SUB_CMP_CONTENTS is already defined
#endif
/** \brief Returns the contents of a subcomponent stored in a given component.
 *
 * Given a pointer to the start of the DER encoding of a component, and a
 * description of a subcomponent, this function returns the byte position of the
 * start of the contents of the subcomponent and it also returns the length of
 * the contents of the subcomponent.
 *
 * \param[in]  ComponentPtr A pointer to the description of the component which
 *                          has to be searched
 * \param[in]  Encoding A pointer to the start of the encoding
 * \param[in]  ComponentToFindPtr A pointer to the description of the
 *                                subcomponent to find
 * \param[out] ContentsLengthPtr A pointer to a variable where the length of
 *                               the contents of the subcomponent will be stored
 *
 * \return the amount of bytes to skip in the encoding of the component
 *         to reach the start of the contents of the encoding of the
 *         first instance of the subcomponent
 */
#define CRY_DER_1ST_SUB_CMP_CONTENTS( \
        ComponentPtr,                 \
        Encoding,                     \
        SubComponentToFindPtr,        \
        ContentsLengthPtr             \
      )                               \
  Cry_DerSubComponentContents         \
  (                                   \
    (ComponentPtr),                   \
    (Encoding),                       \
    (SubComponentToFindPtr),          \
    (ContentsLengthPtr),              \
    0                                 \
  )                                   \

#if (defined CRY_DER_ARRAY_INFO)
#error CRY_DER_ARRAY_INFO is already defined
#endif
/** \brief Prefixes a given array with its length information.
 *
 * Cry_DerComponentStruct stores pointers to the start of arrays. Those arrays
 * must be traversed completely. To be able to do this, the struct also stores
 * the sizes of those arrays. This macro, when given an array, computes the
 * size of the array and returns a struct initializer which contains the size
 * of the array followed by the array itself. The value returned by this macro
 * can then be used in the initializer for a constant of type
 * Cry_DerComponentStruct.
 *
 * \param[in]  array An array who is used in the initialization of a constant of
 *             type Cry_DerComponentStruct.
 *
 * \return A struct initializer which contains the size of the array followed by
 *         the array itself
 */
#define CRY_DER_ARRAY_INFO(array) ((uint32)sizeof(array)/(uint32)sizeof((array)[0])), (array)

#if (defined CRY_DER_TAG_LENGTH)
#error CRY_DER_TAG_LENGTH is already defined
#endif
/** \brief Tag length which is supported by DER parser */
#define  CRY_DER_TAG_LENGTH   ((uint8)sizeof(uint32))

#if (defined CRY_DER_TAG_AUTHREF)
#error CRY_DER_TAG_AUTHREF is already defined
#endif
/** \brief Encoding of the class "Authority Reference" in an ASN.1 tag */
#define CRY_DER_TAG_AUTHREF        (uint32) 0x42U

#if (defined CRY_DER_TAG_DISCRETIONDATA)
#error CRY_DER_TAG_DISCRETIONDATA is already defined
#endif
/** \brief Encoding of the class "Discretionary Data" in an ASN.1 tag */
#define CRY_DER_TAG_DISCRETIONDATA (uint32) 0x53U

#if (defined CRY_DER_TAG_MODULUS)
#error CRY_DER_TAG_MODULUS is already defined
#endif
/** \brief Encoding of the class "Key Modulus" in an ASN.1 tag */
#define CRY_DER_TAG_MODULUS        (uint32) 0x81U

#if (defined CRY_DER_TAG_EXP)
#error CRY_DER_TAG_EXP is already defined
#endif
/** \brief Encoding of the class "Key Exponent" in an ASN.1 tag */
#define CRY_DER_TAG_EXP            (uint32) 0x82U

#if (defined CRY_DER_TAG_HOLDREF)
#error CRY_DER_TAG_HOLDREF is already defined
#endif
/** \brief Encoding of the class "Holder Reference" in an ASN.1 tag */
#define CRY_DER_TAG_HOLDREF        (uint32) 0x5F20U

#if (defined CRY_DER_TAG_EXPIRATIONDATE)
#error CRY_DER_TAG_EXPIRATIONDATE is already defined
#endif
/** \brief Encoding of the class "Expiration Data" in an ASN.1 tag */
#define CRY_DER_TAG_EXPIRATIONDATE (uint32) 0x5F24U

#if (defined CRY_DER_TAG_EFFECTIVEDATE)
#error CRY_DER_TAG_EFFECTIVEDATE is already defined
#endif
/** \brief Encoding of the class "Effective Data" in an ASN.1 tag */
#define CRY_DER_TAG_EFFECTIVEDATE  (uint32) 0x5F25U

#if (defined CRY_DER_TAG_PROFILE_ID)
#error CRY_DER_TAG_PROFILE_ID is already defined
#endif
/** \brief Encoding of the class "Profile Identifier" in an ASN.1 tag */
#define CRY_DER_TAG_PROFILE_ID     (uint32) 0x5F29U

#if (defined CRY_DER_TAG_SIGNATURE)
#error CRY_DER_TAG_SIGNATURE is already defined
#endif
/** \brief Encoding of the class "Signature" in an ASN.1 tag */
#define CRY_DER_TAG_SIGNATURE      (uint32) 0x5F37U

#if (defined CRY_DER_TAG_PUBKEY)
#error CRY_DER_TAG_PUBKEY is already defined
#endif
/** \brief Encoding of the class "Public Key" in an ASN.1 tag */
#define CRY_DER_TAG_PUBKEY         (uint32) 0x7F49U

#if (defined CRY_DER_TAG_HOLDAUTHTEMPL)
#error CRY_DER_TAG_HOLDAUTHTEMPL is already defined
#endif
/** \brief Encoding of the class "Holder Authorization Template" in an ASN.1 tag */
#define CRY_DER_TAG_HOLDAUTHTEMPL  (uint32) 0x7F4CU

#if (defined CRY_DER_TAG_CERTBODY)
#error CRY_DER_TAG_CERTBODY is already defined
#endif
/** \brief Encoding of the class "Body" in an ASN.1 tag */
#define CRY_DER_TAG_CERTBODY       (uint32) 0x7F4EU

#if (defined CRY_DER_TAG_OID)
#error CRY_DER_TAG_OID is already defined
#endif
/** \brief Encoding of the class "Object Identifier" in an ASN.1 tag */
#define CRY_DER_TAG_OID            (uint32) 0x06U

#if (defined CRY_DER_TAG_IGNORED)
#error CRY_DER_TAG_IGNORED is already defined
#endif
/** \brief ASN.1 tag which is ignored */
#define  CRY_DER_TAG_IGNORED (uint8)0U

/*==[Types]===================================================================*/

/** \struct Cry_DerRangeType
 *  \brief A range of allowed values.
 *
 * This is used in when restricting the allowed values of several types. Types
 * whose allowed values can be restricted are "integer", "enumerated", and
 * "set-of".
 */
/** \var Cry_DerRangeType::Min
 *  \brief The minimal allowed value.
 */
/** \var Cry_DerRangeType::Max
 *  \brief The maximal allowed value. Only used when Cry_DerRangeType::Unbounded
 *         is ::FALSE
 */
/** \var Cry_DerRangeType::Unbounded
 *  \brief If this is ::TRUE, the range is not bounded from above. This means
 *         that Cry_DerRangeType::Max will be ignored.
 */
typedef struct
{
  uint32  Min;
  uint32  Max;
  boolean Unbounded;
} Cry_DerRangeType;

/* These structs are defined below. This declaration is needed because otherwise we
 * would have circular dependencies in the definitions of
 * Cry_DerFindFctPtrType, Cry_DerParseFunctionsType, Cry_DerComponentStruct,
 * and Cry_DerSubComponentStruct.
 */
struct Cry_DerComponentStruct;
struct Cry_DerSubComponentStruct;

/** \brief The type used for all find functions of the parser.
 *
 * Given a description of a component, the start of the encoding of the
 * component, and a description of the subcomponent to find, the function
 * searches the subcomponent in the encoding of the component.
 *
 * \param[in]  ComponentPtr A pointer to the description of the component which
 *                          has to be searched
 * \param[in]  Encoding A pointer to the start of the encoding of the component
 * \param[in]  SubComponentToFindPtr A pointer to the description of the
 *                                  subcomponent which has to be found
 * \param[out] PositionPtr A pointer to a variable where the following will
 *                         be stored if the search was successful: the byte
 *                         position of the encoding of the first occurrence
 *                         of the given subcomponent which fulfills the
 *                         requirement "position >= StartSearch"
 * \param[in]  StartSearch Subcomponents which start before this position in
 *                         the encoding are ignored in the search.
 *
 * \return The success value of the search
 *
 * \retval ::TRUE If the subcomponent has been found
 * \retval ::FALSE If the subcomponent has not been found
 */
typedef P2FUNC(boolean, CRY_CODE, Cry_DerFindFctPtrType)
(
  P2CONST(struct Cry_DerComponentStruct,    AUTOMATIC, CRY_APPL_DATA ) ComponentPtr,
  P2CONST(uint8,                            AUTOMATIC, CRY_APPL_DATA ) Encoding,
  P2CONST(struct Cry_DerSubComponentStruct, AUTOMATIC, CRY_APPL_DATA ) SubComponentToFindPtr,
    P2VAR(uint32,                           AUTOMATIC, CRY_APPL_DATA ) PositionPtr,
          uint32                                                       StartSearch
);

/** \brief The type used for all check functions of the parser.
 *
 * Given a description of a component and the start of the encoding of the
 * component, the function checks whether the component is valid and whether
 * its encoding is not longer than the maximal allowed length.
 *
 * \param[in] ComponentPtr pointer to the description of a component to check
 * \param[in] Encoding pointer to the start of the encoding of the component to
 *                     check
 * \param[in]  MaxLength The maximal allowed length of the encoding of the
 *                      component.
 * \param[out] LengthPtr A pointer to a variable where the length of the
 *                       encoding of the value will be stored if the
 *                       encoding is valid
 *
 *
 * \return The validity of the encoding of the component
 *
 * \retval ::TRUE If the encoding is valid
 * \retval ::FALSE If the encoding is invalid
 */
typedef P2FUNC(boolean, CRY_CODE, Cry_DerCheckFctPtrType)
(
  P2CONST(struct Cry_DerComponentStruct, AUTOMATIC, CRY_APPL_DATA ) ComponentPtr,
  P2CONST(uint8,                         AUTOMATIC, CRY_APPL_DATA ) Encoding,
          uint32                                                    MaxLength,
    P2VAR(uint32,                        AUTOMATIC, CRY_APPL_DATA ) LengthPtr
);

/** \struct Cry_DerParseFunctionsType
 *  \brief The functions needed to parse the DER encoding of an ASN.1 component
 *         of a certain type.
 *
 *//** \var Cry_DerParseFunctionsType::CheckFunction
 *  \brief The function to check the validity of the encoding of the component.
 *
 *//** \var Cry_DerParseFunctionsType::FindFunction
 *  \brief The function to search a given subcomponent in the encoding of the
 *         component.
 */
typedef struct
{
  Cry_DerCheckFctPtrType CheckFunction;
  Cry_DerFindFctPtrType  FindFunction;
} Cry_DerParseFunctionsType;

/** \struct Cry_DerComponentStruct
 *  \brief A description of an ASN.1 component.
 *
 *//** \var Cry_DerComponentStruct::ParseFunctionsPtr
 *  \brief A pointer to the parse functions which have to be used for this
 *         component
 *
 *//** \var Cry_DerComponentStruct::NrOfRanges
 *  \brief The size of the array Cry_DerComponentStruct::Ranges.
 *
 *//** \var Cry_DerComponentStruct::Ranges
 *  \brief An array containing the allowed values if the component is
 *         restricted.
 *
 * Some components can be restricted in certain ways. This is a
 * pointer to the start of an array which contains the allowed ranges for the
 * restrictions:
 *
 * \li Components of type "enumerated" must have one of several given values.
 *
 * \li Components of type "integer" can sometimes be restricted to several given
 *     values.
 *
 * \li Components of type "set-of" may sometimes only have a certain amount of
 *     subcomponents.
 *
 *//** \var Cry_DerComponentStruct::NrOfSubComponents
 *  \brief The size of the array Cry_DerComponentStruct::SubComponents.
 *
 *//** \var Cry_DerComponentStruct::SubComponents
 *  \brief An pointer to the start of an array which contains the description of
 *         the subcomponents of this component.
 *
 * Several "constructed" component types consist of subcomponents. This array
 * describes the subcomponents:
 *
 * \li A component of type "sequence" consists of a list of subcomponents. This
 *     array must then be a list of those subcomponents.
 *
 * \li A component of type "choice" consists of one subcomponent from a list of
 *     allowed subcomponents. This array must then be a list of those allowed
 *     subcomponents.
 *
 * \li A component of type "set-of" consists of a group of subcomponents of a
 *     given type. This array must then contain a single entry which is the
 *     description of the allowed subcomponent type.
 */
struct Cry_DerComponentStruct
{
  P2CONST(Cry_DerParseFunctionsType,        TYPEDEF, CRY_APPL_DATA ) ParseFunctionsPtr;
          uint32                                                     NrOfRanges;
  P2CONST(Cry_DerRangeType,                 TYPEDEF, CRY_APPL_DATA ) Ranges;
          uint32                                                     NrOfSubComponents;
  P2CONST(struct Cry_DerSubComponentStruct, TYPEDEF, CRY_APPL_DATA ) SubComponents;
};

/** \struct Cry_DerSubComponentStruct
 *  \brief A description of the subcomponent of an ASN.1 component.
 *
 *//** \var Cry_DerSubComponentStruct::Tag
 *  \brief The ASN.1 tag of the subcomponent
 *
 *//** \var Cry_DerSubComponentStruct::ComponentPtr
 *  \brief A description of the subcomponent
 *
 *//** \var Cry_DerSubComponentStruct::IsOptional
 *  \brief Is this subcomponent optional in the component?
 *
 */
struct Cry_DerSubComponentStruct
{
          uint32                                                    Tag;
  P2CONST(struct Cry_DerComponentStruct, TYPEDEF, CRY_APPL_DATA )   ComponentPtr;
          boolean                                                   IsOptional;
};

/** \brief A description of an ASN.1 subcomponent of a component, identical to
 *         Cry_DerSubComponentStruct.
 */
typedef struct Cry_DerSubComponentStruct Cry_DerSubComponentType;

/** \brief A description of an ASN.1 component, identical to
 *         Cry_DerComponentStruct.
 */
typedef struct Cry_DerComponentStruct Cry_DerComponentType;

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief The functions needed to parse the encoding of a "sequence".
 *
 * See X.690, chapter 8.9.
 */
extern CONST(Cry_DerParseFunctionsType, CRY_CONST) Cry_DerParseFunctionsSequence;

/** \brief The functions needed to parse the encoding of a "octetstring".
 *
 * See X.690, chapter 8.7.
 */
extern CONST(Cry_DerParseFunctionsType, CRY_CONST) Cry_DerParseFunctionsOctetstring;

/** \brief The functions needed to parse the encoding of a "CharacterString".
 *
 * See X.690, chapter 8.21.
 */
extern CONST(Cry_DerParseFunctionsType, CRY_CONST) Cry_DerParseFunctionsCharacterS;

/** \brief The functions needed to parse the encoding of an "integer".
 *
 * See X.690, chapter 8.3.
 */
extern CONST(Cry_DerParseFunctionsType, CRY_CONST) Cry_DerParseFunctionsInteger;

/** \brief The functions needed to parse the encoding of an "object identifier".
 *
 * See X.690, chapter 8.19.
 */
extern CONST(Cry_DerParseFunctionsType, CRY_CONST) Cry_DerParseFunctionsObjectIdentifier;

/** \brief The functions needed to parse the BCD encoding of a date.
 *
 */
extern CONST(Cry_DerParseFunctionsType, CRY_CONST) Cry_DerParseFunctionsDate;

/** \brief A description of an "OBJECT IDENTIFIER" */
extern CONST(Cry_DerComponentType, CRY_CONST) Cry_DerCptObjIdentifier;

/** \brief A description of a "OCTET STRING" */
extern CONST(Cry_DerComponentType, CRY_CONST) Cry_DerCptOctetString;

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief Returns the contents of a subcomponent stored in a given component.
 *
 * Given a pointer to the start of the DER encoding of a component, and a
 * description of a subcomponent, this function returns the byte position of the
 * start of the contents of the subcomponent and it also returns the length of
 * the contents of the subcomponent.
 *
 * \param[in]  ComponentPtr A pointer to the description of the component which
 *                          has to be searched
 * \param[in]  Encoding A pointer to the start of the encoding
 * \param[in]  ComponentToFindPtr A pointer to the description of the
 *                                subcomponent to find
 * \param[out] ContentsLengthPtr A pointer to a variable where the length of
 *                               the contents of the sub component will be stored
 * \param[in]  StartSearch Subcomponents which start before this position in
 *                         the encoding are ignored in the search.
 *
 * \return the amount of bytes to skip in the encoding of the component
 *         to reach the start of the contents of the encoding of the first
 *         subcomponent whose start position fulfills the requirement
 *         "position >= StartSearch".
 */
extern FUNC(uint32, CRY_CODE) Cry_DerSubComponentContents
(
  P2CONST(Cry_DerComponentType,    AUTOMATIC, CRY_APPL_DATA) ComponentPtr,
  P2CONST(uint8,                   AUTOMATIC, CRY_APPL_DATA) Encoding,
  P2CONST(Cry_DerSubComponentType, AUTOMATIC, CRY_APPL_DATA) SubComponentToFindPtr,
    P2VAR(uint32,                  AUTOMATIC, CRY_APPL_DATA) ContentsLengthPtr,
          uint32                                             StartSearch
);

/** \brief Find the start of the contents of a given DER encoding of a value.
 *
 * See X.690, chapter 8.1.1
 *
 * \param[in]  Encoding A pointer to the start of the encoding of the value
 *
 * \return The byte position of the start of the contents in the encoding
 */
extern FUNC(uint32, CRY_CODE) Cry_DerEncGetContentsStart
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) Encoding
);

/** \brief Find the length of the contents of a given DER encoding of a value.
 *
 * See X.690, chapter 8.1.1
 *
 * Since the return value is a uint32 value, only lengths smaller than 2^32
 * can be handled.
 *
 * \param[in]  Encoding A pointer to the start of the encoding of the value
 *
 * \return The length of the contents of the encoding
 */
extern FUNC(uint32, CRY_CODE) Cry_DerEncGetContentsLength
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) Encoding
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #ifndef CRY_DER_H */
