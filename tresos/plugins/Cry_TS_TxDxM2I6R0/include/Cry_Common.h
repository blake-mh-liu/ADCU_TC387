/* --------{ EB Automotive C Source File }-------- */

/** \cond DONTDOCUMENT */

#ifndef CRY_COMMON_H
#define CRY_COMMON_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

/*==[Macros]==================================================================*/

#if (defined CRY_COMMON_DER_HEADER_MAX_LEN)
#error CRY_COMMON_DER_HEADER_MAX_LEN is already defined
#endif
/** \brief The maximal possible length of a DER header as returned by
 * Cry_CommonDerHeaderSequence() or Cry_CommonDerHeaderOctetString().
 *
 */
#define CRY_COMMON_DER_HEADER_MAX_LEN 6U


#if (defined CRY_LEN_IN_ALIGN_TYPE)
#error CRY_LEN_IN_ALIGN_TYPE is already defined
#endif
#define CRY_LEN_IN_ALIGN_TYPE(ByteLength)      \
(                                              \
   (uint32)                                    \
   (                                           \
      (uint32)                                 \
      (                                        \
         (uint32)                              \
         (                                     \
            (uint32)(ByteLength) - (uint32)1UL \
         ) /                                   \
         (uint32)sizeof(Csm_AlignType)         \
      ) +                                      \
      (uint32)1UL                              \
   )                                           \
)


#if (defined CRY_COMMON_UNUSED_PARAMETER)
#error CRY_COMMON_UNUSED_PARAMETER is already defined
#endif
/** \brief Remove compiler warnings for unused parameters **/
#define CRY_COMMON_UNUSED_PARAMETER(x) ((void)(x))

/*==[Types]===================================================================*/

/**
 *
 * \enum Cry_ReturnType
 * \brief Enumeration of the return type of the CRY module
 *
 *//**
 * \var Cry_ReturnType::CRY_E_OK
 * \brief Operation successful
 *//**
 * \var Cry_ReturnType::CRY_E_NOT_OK
 * \brief Operation failed
 *//**
 * \var Cry_ReturnType::CRY_E_EQUAL
 * \brief Memory blocks are equal
  *//**
 * \var Cry_ReturnType::CRY_E_NOT_EQUAL
 * \brief Memory blocks are not equal
  *//**
 * \var Cry_ReturnType::CRY_E_SMALLER
 * \brief If number1 smaller than number2
  *//**
 * \var Cry_ReturnType::CRY_E_LARGER
 * \brief If number1 is greater than number2
 */
typedef enum
{
   CRY_E_OK,
   CRY_E_NOT_OK,
   CRY_E_EQUAL,
   CRY_E_NOT_EQUAL,
   CRY_E_SMALLER,
   CRY_E_LARGER
}
Cry_ReturnType;

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief   This function sets all context variables to 0.
 **
 ** \param[in out] Context A pointer to the memory area which should hold
 **                        the context.
 ** \param[in]     Length  Holds the size of the context in bytes
 **
 **/
extern FUNC(void, CRY_CODE) Cry_CommonResetCtx
(
   P2VAR(void, AUTOMATIC, CRY_APPL_DATA)   Context,
   uint32                                  Length
);

/** \brief   This function copies a block of data to a different location.
 **
 ** \param[out] Destination A pointer to the memory area which should hold
 ** the copy of the data
 ** \param[in] Source A pointer to the block of data which should be copied
 ** \param[in] ByteLength Holds the amount of bytes which should be copied
 **
 **/
extern FUNC(void, CRY_CODE) Cry_CommonCopy
(
   P2VAR(void, AUTOMATIC, CRY_APPL_DATA)   Destination,
   P2CONST(void, AUTOMATIC, CRY_APPL_DATA) Source,
   uint32                                  ByteLength
);

/** \brief   This function XOR a block of data to a another block of data.
 **
 ** \param[in,out]     Destination=a pointer to the memory area which should hold
 ** the XOR-ed data.
 ** \param[in] Source=a pointer to the block of data which should be XOR-ed to the
 **  destination.
 ** \param[in] ByteLength Holds the amount of bytes which should be XOR-ed
 **
 **/
extern FUNC(void, CRY_CODE) Cry_CommonXOR
(
   P2VAR(void, AUTOMATIC, CRY_APPL_DATA)   Destination,
   P2CONST(void, AUTOMATIC, CRY_APPL_DATA) Source,
   uint32                                  ByteLength
);

/** \brief This function compares two blocks of data
 **
 ** \param[in] BlockA Holds a pointer to the first block to compare
 ** the XOR-ed data.
 ** \param[in] BlockB Holds a pointer to the first block to compare
 ** \param[in] ByteLength Holds the amount of bytes which should be compared
 **
 ** \returns Result of the comparison
 ** \retval CRY_E_EQUAL If both blocks are identical
 ** \retval CRY_E_NOT_EQUAL If the blocks differ
 **
 **/
extern FUNC(Cry_ReturnType, CRY_CODE) Cry_CommonCompare
(
   P2CONST(void, AUTOMATIC, CRY_APPL_DATA) BlockA,
   P2CONST(void, AUTOMATIC, CRY_APPL_DATA) BlockB,
   uint32                                  ByteLength
);

/** \brief Creates a DER header for a sequence
 **
 ** This function creates a DER header for an ASN.1 sequence. The header
 ** contains a byte which identifies the sequence followed by several bytes
 ** which encode the length of the payload of the sequence
 **
 ** \param[out] HeaderBuffer Holds a pointer to the start of a buffer where the header
 ** should be stored
 ** \param[in] PayloadLength Length of the payload of the sequence
 **
 ** \returns Length of the header in bytes
 **
 **/
extern FUNC(uint32, CRY_CODE) Cry_CommonDerHeaderSequence
(
   P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) HeaderBuffer,
   uint32                                 PayloadLength
);

/** \brief Creates a DER header for an octet string
 **
 ** This function creates a DER header for an ASN.1 octet string. The header
 ** contains a byte which identifies the octet string followed by several bytes
 ** which encode the length of the payload of the octet string
 **
 ** \param[out] HeaderBuffer Holds a pointer to the start of a buffer where the header
 ** should be stored
 ** \param[in] PayloadLength Length of the payload of the octet string
 **
 ** \returns Length of the header in bytes
 **
 **/
extern FUNC(uint32, CRY_CODE) Cry_CommonDerHeaderOctetString
(
   P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) HeaderBuffer,
   uint32                                 PayloadLength
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/** \endcond  */

#endif /* CRY_COMMON_H */
