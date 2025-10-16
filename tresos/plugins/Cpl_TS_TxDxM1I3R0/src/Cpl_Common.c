/** \file        Cpl_Common.c
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

/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

#include <Std_Types.h>

#include <Cpl_Common.h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CPL_START_SEC_CODE
#include <MemMap.h>

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_CommonRingBufferInit]------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_CommonRingBufferInit
(
  P2VAR(uint8,              AUTOMATIC, CPL_APPL_DATA) Array,
    VAR(uint32,             AUTOMATIC               ) ArrayLen,
  P2VAR(Cpl_RingBufferType, AUTOMATIC, CPL_APPL_DATA) Buffer,
    VAR(uint32,             AUTOMATIC               ) BufferLen
)
{
  VAR(Cal_ReturnType,     AUTOMATIC) retVal = CAL_E_NOT_OK; /* return value */
  VAR(Cpl_RingBufferType, AUTOMATIC) locBuffer;
  VAR(uint32,             AUTOMATIC) locLoop;

  /* The FALSE branch cannot be covered as this function is called only from LZSS algorithm in which
   * enough space is reserved at compile time, therefore ArrayLen is always bigger than BufferLen.
   * Nevertheless, for completness and further uses this check needs to be kept. */
  /* CHECK: NOPARSE */
  if ( BufferLen <= ArrayLen )
  /* CHECK: PARSE */
  {
    for ( locLoop=0U; locLoop<BufferLen; locLoop++ )
    {
      Array[locLoop] = 0U;
    }

    locBuffer.Array = Array;
    locBuffer.Size  = BufferLen;
    locBuffer.Level = 0U;
    locBuffer.Start = 0U;

    *Buffer         = locBuffer;

    retVal = CAL_E_OK;
  }

  return retVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_CommonRingBufferPush]------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(void, CPL_CODE) Cpl_CommonRingBufferPush
(
  P2VAR(Cpl_RingBufferType, AUTOMATIC, CPL_APPL_DATA) Buffer,
    VAR(uint8,              AUTOMATIC               ) Byte
)
{
  VAR(uint32, AUTOMATIC) End;

  /* new end position where to insert 'Byte' */
  End                = (Buffer->Start + Buffer->Level) % Buffer->Size;

  Buffer->Array[End] = Byte;

  if (Buffer->Level == Buffer->Size)
  {
    Buffer->Start = (Buffer->Start + 1U) % Buffer->Size;
  }
  else
  {
    Buffer->Level++;
  }
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_CommonRingBufferReadFromEnd]-----------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(uint8, CPL_CODE) Cpl_CommonRingBufferReadFromEnd
(
  P2VAR(Cpl_RingBufferType,                AUTOMATIC, CPL_APPL_DATA) Buffer,
    VAR(uint32,                            AUTOMATIC               ) Offset,
    VAR(Cpl_RingBufferOffsetDirectionType, AUTOMATIC               ) Dir
)
{
  VAR(uint8,  AUTOMATIC) Byte;
  VAR(uint32, AUTOMATIC) End;

  /* actual end position where to read from */
  End = ((Buffer->Start + Buffer->Level) - 1U) % Buffer->Size;

  /* The TRUE branch cannot be covered as this function is called only from LZSS algorithm in which
   * the algorithms always reads back with at least an
   * offset of 1(Dir == CPL_D_NEGATIVE && Offset > 0).
   * Nevertheless, for completness and further uses this check needs to be kept. */
  /* CHECK: NOPARSE */
  if ( (Offset == 0U            ) ||
       (Dir    == CPL_D_POSITIVE)
     )
  {
    Byte = Buffer->Array[ ((End + Offset) % Buffer->Level) ];
  }
  else
  {
    Byte = ( End >= Offset )
         ? Buffer->Array[ End - Offset ]
         : Buffer->Array[ Buffer->Level - ((Offset - End) % Buffer->Level) ];
  }
  /* CHECK: PARSE */

  return Byte;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_CommonRingBufferGetLevel]--------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(uint32, CPL_CODE) Cpl_CommonRingBufferGetLevel
(
  P2VAR(Cpl_RingBufferType, AUTOMATIC, CPL_APPL_DATA) Buffer
)
{
  return (uint32) Buffer->Level;
}

#define CPL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]===============================================*/

/*================================================================================================*/

/*==================[end of file]=================================================================*/
