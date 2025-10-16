/* --------{ EB Automotive C Source File }-------- */

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Cry_Common.h>

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief  Creates the part of a DER header which encodes the payload length
 **
 ** The DER header of an ASN.1 element consists of several parts, one being
 ** the encoding of the length of the payload of the element. This function
 ** creates the length encoding given the payload length
 **
 ** \param[out] LengthEncodingBuffer Holds a pointer to the start of a buffer where the
 ** length encoding should be stored
 ** \param[in] PayloadLength Length of the payload of the ASN.1 element
 **
 ** \returns Length of the length encoding in bytes
 **
 **/
static FUNC(uint32, CRY_CODE) Cry_CommonDerLengthEncoding
(
   P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) LengthEncodingBuffer,
   uint32                                 PayloadLength
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

FUNC(void, CRY_CODE) Cry_CommonResetCtx
(
   P2VAR(void, AUTOMATIC, CRY_APPL_DATA)   Context,
   uint32                                  Length
)
{
  /* internal length value */
  uint32_least Len;

  /* loop over the block length */
  for(Len = (uint32_least)0U; Len < Length;  ++Len)
  {
    /* copy byte-wise */
    ((P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA))Context)[Len] = 0U;
  }
}

FUNC(void, CRY_CODE) Cry_CommonCopy
(
   P2VAR(void, AUTOMATIC, CRY_APPL_DATA)   Destination,
   P2CONST(void, AUTOMATIC, CRY_APPL_DATA) Source,
   uint32                                  ByteLength
)
{
   uint32_least len; /* internal length value */


   /* loop over the block length */
   for(len = (uint32_least)0; len < ByteLength;  ++len)
   {
      /* copy byte-wise */
      ((P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA))Destination)[len] =
                        ((P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA))Source)[len];
   }
}


FUNC(void, CRY_CODE) Cry_CommonXOR
(
   P2VAR(void, AUTOMATIC, CRY_APPL_DATA)   Destination,
   P2CONST(void, AUTOMATIC, CRY_APPL_DATA) Source,
   uint32                                  ByteLength
)
{
   uint32_least len; /* internal length value */


   /* loop over the block length */
   for(len = (uint32_least)0; len < ByteLength;  ++len)
   {
      /* XOR byte-wise */
      ((P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA))Destination)[len] ^=
                        ((P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA))Source)[len];
   }
}

FUNC(Cry_ReturnType, CRY_CODE) Cry_CommonCompare
(
   P2CONST(void, AUTOMATIC, CRY_APPL_DATA) BlockA,
   P2CONST(void, AUTOMATIC, CRY_APPL_DATA) BlockB,
   uint32                                  ByteLength
)
{
  Cry_ReturnType retVal; /* return value */
  uint32 len;            /* internal length index */


  /* initialize the return value */
  retVal = CRY_E_EQUAL;

   /* loop over the block length */
   for(len = (uint32)0; (len < ByteLength) && (retVal == CRY_E_EQUAL); ++len)
   {
      /* compare byte-wise */
      if
      (
        ((P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA))BlockA)[len] !=
        ((P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA))BlockB)[len]
      )
      {
         retVal = CRY_E_NOT_EQUAL;
      }
   }

   return retVal;
}

/* !LINKSTO CS_SECURE_CRY_0123_CommonDerHeaderSequence,1 */
FUNC(uint32, CRY_CODE) Cry_CommonDerHeaderSequence
(
   P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) HeaderBuffer,
   uint32                                 PayloadLength
)
{
   uint32 HeaderLength;


   HeaderBuffer[0] = 0x30;

   HeaderLength = Cry_CommonDerLengthEncoding(&HeaderBuffer[1], PayloadLength);

   return HeaderLength + 1;
}

/* !LINKSTO CS_SECURE_CRY_0124_CommonDerHeaderOctetString,1 */
FUNC(uint32, CRY_CODE) Cry_CommonDerHeaderOctetString
(
   P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) HeaderBuffer,
   uint32                                 PayloadLength
)
{
   uint32 HeaderLength;


   HeaderBuffer[0] = 0x04;

   HeaderLength = Cry_CommonDerLengthEncoding(&HeaderBuffer[1], PayloadLength);

   return HeaderLength + 1;
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Definition of functions with internal linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

static FUNC(uint32, CRY_CODE) Cry_CommonDerLengthEncoding
(
   P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) LengthEncodingBuffer,
   uint32                                 PayloadLength
)
{
   uint32 LengthEncodingLength;

   if(PayloadLength <= 0x7fu)
   {
      LengthEncodingBuffer[0u] = (uint8)PayloadLength;
      LengthEncodingLength = 1u;
   }
   else
   {
     /* Values greater than 0x7f need a control byte */
     uint32 numberOfBytes = 0u;
     uint32 locPayloadLength = PayloadLength;
     uint32 curPos = 0u;
     while (locPayloadLength != 0u)
     {
       locPayloadLength >>= 8u;
       numberOfBytes++;
     }
     LengthEncodingBuffer[0u] = (uint8) 0x80u | (uint8) numberOfBytes;
     /* Encode the length with big endian byte order */
     for (curPos = 1u; curPos <= numberOfBytes; curPos++)
     {
       LengthEncodingBuffer[curPos] = (uint8)(PayloadLength >> (8u * (numberOfBytes - curPos)));
     }
     LengthEncodingLength = 1u + numberOfBytes;
   }

   return LengthEncodingLength;
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>
