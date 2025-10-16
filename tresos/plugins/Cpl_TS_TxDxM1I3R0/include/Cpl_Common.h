#ifndef CPL_COMMON_H
#define CPL_COMMON_H

/*================================================================================================*/

/** \file        Cpl_Common.h
 **
 ** \brief       Cpl common interface.
 **
 ** \project     Crypto Primitive Library
 ** \author      Danny Block <Danny.Block@elektrobit.com>
 ** \author      EB Automotive GmbH, 91058 Erlangen, Germany
 **
 ** \controller  independent
 ** \compiler    independent
 ** \hardware    independent
 **
 ** Copyright 2012 by EB Automotive GmbH
 ** All rights exclusively reserved for EB Automotive GmbH,
 ** unless expressly agreed to otherwise
 **/

/** \cond DONTDOCUMENT */

/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

#include <Std_Types.h>
#include <Cal_Types.h>

#include <Cpl_Version.h>

/*==================[macros]======================================================================*/

#if (defined EB_STATIC_CHECK)
/** \brief This macro can be used to avoid compiler warnings
 * It is left empty to not produce a false positive for MISRA 14.2 */
#define  CPL_PARAM_UNUSED(x)
#else
/** \brief  This macro can be used to avoid compiler warnings
 **/
#define  CPL_PARAM_UNUSED(x)  ((void) (x))
#endif
/*==================[type definitions]============================================================*/

/** \brief  The different type of RLEs.
 **/
typedef enum
{
  CPL_RLE_VARIANT_8BIT,
  CPL_RLE_VARIANT_CTRLBIT
}
Cpl_RleVariantType;

/** \brief  A ring buffer offset direction type.
 **/
typedef enum
{
  CPL_D_POSITIVE,
  CPL_D_NEGATIVE
}
Cpl_RingBufferOffsetDirectionType;

/** \brief  A ring buffer.
 **/
typedef struct
{
  P2VAR(uint8,  TYPEDEF, CPL_APPL_DATA) Array;
        uint32                          Size;
        uint32                          Level;
        uint32                          Start;
}
Cpl_RingBufferType;

/*==================[external function declarations]==============================================*/

#define CPL_START_SEC_CODE
#include <MemMap.h>

/** \brief  Initializes ring buffer with elements of type 'uint8'.
 **
 ** Constructs a ring buffer data structure variable with initialized members.
 **
 ** \param[in]   Array      A pointer to the memory area which shall hold the ring buffer.
 ** \param[in]   ArrayLen   The size of 'Array'.
 ** \param[out]  Buffer     A pointer to a ring buffer data structure variable that shall
 **                         describe the ring buffer.
 ** \param[in]   BufferLen  The size 'Buffer' shall have..
 **
 ** \returns     Information about whether the initialization was successful or not.
 **
 ** \retval      CAL_E_OK      Initialization was successful.
 ** \retval      CAL_E_NOT_OK  Initialization wasn't successful.
 **/
extern FUNC(Cal_ReturnType, CPL_CODE) Cpl_CommonRingBufferInit
(
  P2VAR(uint8,              AUTOMATIC, CPL_APPL_DATA) Array,
    VAR(uint32,             AUTOMATIC               ) ArrayLen,
  P2VAR(Cpl_RingBufferType, AUTOMATIC, CPL_APPL_DATA) Buffer,
    VAR(uint32,             AUTOMATIC               ) BufferLen
);

/** \brief  Append a new element of type 'uint8' to a ring buffer with elements of type 'uint8'.
 **
 ** Adds a new element at the end of the ring buffer, after its current last element.
 ** The content of this new element is initialized to a copy of 'Byte'.
 **
 ** \param[in]  Buffer  A pointer to a ring buffer data structure variable that describes a
 **                     ring buffer.
 ** \param[in]  Byte    Value to be append.
 **
 ** \returns    Nothing.
 **/
extern FUNC(void, CPL_CODE) Cpl_CommonRingBufferPush
(
  P2VAR(Cpl_RingBufferType, AUTOMATIC, CPL_APPL_DATA) Buffer,
    VAR(uint8,              AUTOMATIC               ) Byte
);

/** \brief  Return the element of type 'uint8' and offset 'Offset' in direction 'Dir' away from the
 **         youngest element in a ring buffer with elements of type 'uint8'.
 **
 ** \param[in]  Buffer  A pointer to a ring buffer data structure variable that describes a
 **                     ring buffer.
 ** \param[in]  Offset  The offset of the element to read based on the youngest element.
 ** \param[in]  Dir     The direction to move through the ring buffer based on the youngest element.
 **
 ** \returns    The element.
 **/
extern FUNC(uint8, CPL_CODE) Cpl_CommonRingBufferReadFromEnd
(
  P2VAR(Cpl_RingBufferType,                AUTOMATIC, CPL_APPL_DATA) Buffer,
    VAR(uint32,                            AUTOMATIC               ) Offset,
    VAR(Cpl_RingBufferOffsetDirectionType, AUTOMATIC               ) Dir
);

/** \brief  Return the number of used elements in a ring buffer with elements of type 'uint8'.
 **
 ** \param[in]  Buffer  A pointer to a ring buffer data structure variable that describes a
 **                     ring buffer.
 **
 ** \returns    The number of used elements.
 **/
extern FUNC(uint32, CPL_CODE) Cpl_CommonRingBufferGetLevel
(
  P2VAR(Cpl_RingBufferType, AUTOMATIC, CPL_APPL_DATA) Buffer
);

#define CPL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

/** \endcond  */

#endif /* #ifndef CPL_COMMON_H */

/*==================[end of file]=================================================================*/
