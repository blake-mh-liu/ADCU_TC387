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

/*==[Includes]====================================================================================*/

#include <Std_Types.h>                                          /* declarations of standard types */
#include <Csm.h>
#include <Csm_Hash.h>
#include <Cry_Common.h>                                    /* common internal static declarations */
#include <Cry_MD5.h>
#include <Cry_MD5Config.h>                       /* internal configuration dependend declarations */

#if (CRY_MD5_ENABLED == STD_ON)
/*==[Macros]======================================================================================*/

#if (defined CRY_MD5_ROUNDS)
#error CRY_MD5_ROUNDS already defined
#endif
/**
 * \brief The number of rounds performed by the MD5 algorithm.
 */
#define CRY_MD5_ROUNDS 64U                                        /* Number of rounds used by MD5 */


#if !defined(CRY_PARAM_UNUSED)
/**
 * \brief This macros avoids compiler wranings for unused variables
 */
#define CRY_PARAM_UNUSED(x) ((void) (x))
#endif

#if (defined CRY_MD5_ALGORITHM_ID)
#error CRY_MD5_ALGORITHM_ID already defined
#endif
/**
 * \brief The DER-encoded digestInfo of the MD5 hash algorithm as described in chapter 9.2 of the
 *        standard PKCS #1 v2.1. This is used in some encoded signatures, as, e.g., in the signature
 *        of an X.509 certificate.
 */
#define CRY_MD5_ALGORITHM_ID \
  (uint8)0x30, (uint8)0x20, (uint8)0x30, (uint8)0x0c, (uint8)0x06, \
  (uint8)0x08, (uint8)0x2a, (uint8)0x86, (uint8)0x48, (uint8)0x86, \
  (uint8)0xf7, (uint8)0x0d, (uint8)0x02, (uint8)0x05, (uint8)0x05, \
  (uint8)0x00, (uint8)0x04, (uint8)0x10

/*==[Types]=======================================================================================*/

/**
 * \brief The states of the MD5 computation.
 */
typedef enum
{
  CRY_S_MD5_IDLE,
  CRY_S_MD5_INIT,
  CRY_S_MD5_INITIALIZED,
  CRY_S_MD5_UPDATE,
  CRY_S_MD5_FINISH,
  CRY_S_MD5_FINISH_COMPLETE,
  CRY_S_MD5_FINISH_LENGTH,
  CRY_S_MD5_FINISH_EXPORT,
  CRY_S_MD5_PROCESS,
  CRY_S_MD5_PROCESS_COPY1,
  CRY_S_MD5_PROCESS_COMPRESS1,
  CRY_S_MD5_PROCESS_COMPRESS2,
  CRY_S_MD5_PROCESS_COMPRESS3,
  CRY_S_MD5_PROCESS_COMPRESS4,
  CRY_S_MD5_PROCESS_COPY2,
  CRY_S_MD5_COMPRESS,
  CRY_S_MD5_COMPRESS_PRECALC,
  CRY_S_MD5_COMPRESS_TRANSFORM1,
  CRY_S_MD5_COMPRESS_TRANSFORM2,
  CRY_S_MD5_COMPRESS_EXPORT
}
Cry_MD5StateType;

/**
 * \brief The MD5 context.
 */
typedef struct
{
  uint32                            DataLength;                      /* length of the input data */
  /* local variables for Cry_MD5Compress                                                         */
  uint32                            a;              /* four variables to hold the internal state */
  uint32                            b;
  uint32                            c;
  uint32                            d;
  uint32                            t;                                 /* one temporary variable */
  uint32                            W[(CRY_MD5_BLOCK_SIZE >> 2U)]; /* internal copy of user data */
  uint32                            InternalState[CRY_MD5_STATE_WORDS];
  uint32                            Count;                     /* amount of bytes already hashed */
  uint32                            left;                                /* number of bytes left */
  P2VAR(uint32,  TYPEDEF, CRY_APPL_DATA) ResultLengthPtr;
  P2VAR(uint8,   TYPEDEF, CRY_APPL_DATA) Result;       /* pointer to the result memory location */
  P2CONST(uint8, TYPEDEF, CRY_APPL_DATA) Data;                     /* pointer to the input data */
  P2CONST(uint8, TYPEDEF, CRY_APPL_DATA) p;                                /* pointer into data */
  /* internal state of the MD5 computation */
  Cry_MD5StateType                  State;               /* current state of the MD5 computation */
  Cry_MD5StateType                  ProcessInputState;     /* state of the ProcessInput function */
  Cry_MD5StateType                  CompressState;        /* state of the CompressState function */
  uint8                             Partial[CRY_MD5_BLOCK_SIZE];                   /* input data */
  uint8                             length[8U];       /* 64-bit representation of length of data */
  uint8                             MD5Pad[CRY_MD5_BLOCK_SIZE];
  uint8                             i;                                          /* loop variable */
  uint8                             k;                /* variable for internal loop calculations */
  uint8                             l;                /* variable for internal loop calculations */
  /* local variables for Cry_MD5ProcessInput                                                     */
  uint8                             copy;                             /* number of bytes to copy */
  uint8                             offset;           /* offset into temporal buffer in blockCtx */
}
Cry_MD5CtxType;


/*==[Declaration of functions with internal linkage]==============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>


/**
 * \brief Update the the digest computation with the provided data block.
 */
STATIC FUNC(boolean, CRY_CODE) Cry_MD5ProcessInput(void);


/**
 * \brief Internal MD5 compression function.
 *
 * Compresses a full block of data.
 *
 * \param[in] Data Holds a pointer to the data that will be compressed.
 */
STATIC FUNC(boolean, CRY_CODE) Cry_MD5Compress
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_CONST) Data
);


/**
 * \brief Converts the 32-bit count value of the MD5 computation.
 *
 * Compresses a full block of data.
 *
 * \param[in]  Count   Holds the number of processed bytes.
 * \param[out] Convert Holds a pointer to a eight byte memory block which shall hold the number of
 *                     processed bytes according to MD5.
 */
STATIC FUNC(void, CRY_CODE) Cry_MD5CountConvert
(
  uint32                                 Count,
  P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) Convert
);



/**
 * \brief Convert the provided context into a MD5 hash value.
 *
 * Stores the computed hash value into the result location.
 */
STATIC FUNC(void, CRY_CODE) Cry_MD5Export(void);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=============================================================*/

#define CRY_START_SEC_CONST_8
#include <MemMap.h>

/** \brief The algorithm identifier.
 *
 * This constant contains the algorithm identifier for the MD5 configuration.
 */
STATIC CONST(uint8, CRY_CONST) Cry_MD5AlgorithmIdArray[] = { CRY_MD5_ALGORITHM_ID };


/** \brief Table used for compression of data in Cry_MD5Compress().
 *
 * These numbers define the access order to the words.
 * The table is coded to save space: each 4-bit nibble represents
 * one value.
 * The first nibble is packed into the first higher nibble,
 * the second in the lower nibble.
 * size: 32 bytes
 */
STATIC CONST(uint8, CRY_CONST) Z[32u] =
{
  (uint8)0x01, (uint8)0x23, (uint8)0x45, (uint8)0x67,
  (uint8)0x89, (uint8)0xab, (uint8)0xcd, (uint8)0xef,
  (uint8)0x16, (uint8)0xb0, (uint8)0x5a, (uint8)0xf4,
  (uint8)0x9e, (uint8)0x38, (uint8)0xd2, (uint8)0x7c,
  (uint8)0x58, (uint8)0xbe, (uint8)0x14, (uint8)0x7a,
  (uint8)0xd0, (uint8)0x36, (uint8)0x9c, (uint8)0xf2,
  (uint8)0x07, (uint8)0xe5, (uint8)0xc3, (uint8)0xa1,
  (uint8)0x8f, (uint8)0x6d, (uint8)0x4b, (uint8)0x29
};

/** \brief Table used for compression of data in Cry_MD5Compress().
 *
 * This table contains the constants by which to rotate.
 * Each round just 4 numbers are used.
 * size: 16 bytes
 */
STATIC CONST(uint8, CRY_CONST) S[16u] =
{
  (uint8)0x07, (uint8)0x0c, (uint8)0x11, (uint8)0x16,
  (uint8)0x05, (uint8)0x09, (uint8)0x0e, (uint8)0x14,
  (uint8)0x04, (uint8)0x0b, (uint8)0x10, (uint8)0x17,
  (uint8)0x06, (uint8)0x0a, (uint8)0x0f, (uint8)0x15
};


#define CRY_STOP_SEC_CONST_8
#include <MemMap.h>


#define CRY_START_SEC_CONST_32
#include <MemMap.h>


/** \brief Values used for compression of data in Cry_MD5Compress().
 *
 * These unique values will be added each round.
 * They are constructed as follows:
 * Y[i] = first 32 bits of binary value
 *        abs( sin( j + 1 ) )
 * where j is in radians and "abs" denotes the absolute value.
 * It is therefore unlikely to compress this table further.
 * size: 256 bytes
 */
STATIC CONST(uint32, CRY_CONST) Y[64U] =
{
  /* round 1 */
  (uint32)0xd76aa478UL, (uint32)0xe8c7b756UL,
  (uint32)0x242070dbUL, (uint32)0xc1bdceeeUL,
  (uint32)0xf57c0fafUL, (uint32)0x4787c62aUL,
  (uint32)0xa8304613UL, (uint32)0xfd469501UL,
  (uint32)0x698098d8UL, (uint32)0x8b44f7afUL,
  (uint32)0xffff5bb1UL, (uint32)0x895cd7beUL,
  (uint32)0x6b901122UL, (uint32)0xfd987193UL,
  (uint32)0xa679438eUL, (uint32)0x49b40821UL,
  /* round 2 */
  (uint32)0xf61e2562UL, (uint32)0xc040b340UL,
  (uint32)0x265e5a51UL, (uint32)0xe9b6c7aaUL,
  (uint32)0xd62f105dUL, (uint32)0x02441453UL,
  (uint32)0xd8a1e681UL, (uint32)0xe7d3fbc8UL,
  (uint32)0x21e1cde6UL, (uint32)0xc33707d6UL,
  (uint32)0xf4d50d87UL, (uint32)0x455a14edUL,
  (uint32)0xa9e3e905UL, (uint32)0xfcefa3f8UL,
  (uint32)0x676f02d9UL, (uint32)0x8d2a4c8aUL,
  /* round 3 */
  (uint32)0xfffa3942UL, (uint32)0x8771f681UL,
  (uint32)0x6d9d6122UL, (uint32)0xfde5380cUL,
  (uint32)0xa4beea44UL, (uint32)0x4bdecfa9UL,
  (uint32)0xf6bb4b60UL, (uint32)0xbebfbc70UL,
  (uint32)0x289b7ec6UL, (uint32)0xeaa127faUL,
  (uint32)0xd4ef3085UL, (uint32)0x04881d05UL,
  (uint32)0xd9d4d039UL, (uint32)0xe6db99e5UL,
  (uint32)0x1fa27cf8UL, (uint32)0xc4ac5665UL,
  /* round 4 */
  (uint32)0xf4292244UL, (uint32)0x432aff97UL,
  (uint32)0xab9423a7UL, (uint32)0xfc93a039UL,
  (uint32)0x655b59c3UL, (uint32)0x8f0ccc92UL,
  (uint32)0xffeff47dUL, (uint32)0x85845dd1UL,
  (uint32)0x6fa87e4fUL, (uint32)0xfe2ce6e0UL,
  (uint32)0xa3014314UL, (uint32)0x4e0811a1UL,
  (uint32)0xf7537e82UL, (uint32)0xbd3af235UL,
  (uint32)0x2ad7d2bbUL, (uint32)0xeb86d391UL
};

#define CRY_STOP_SEC_CONST_32
#include <MemMap.h>

/*==[Variables with internal linkage]=============================================================*/


#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/**
 * \brief The context variable which is used to store the internal state of the MD5 computation.
 */
STATIC VAR(Cry_MD5CtxType, CRY_VAR) Cry_MD5Ctx;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=============================================================*/

/*==[Variables with external linkage]=============================================================*/

/*==[Definition of functions with external linkage]===============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>


FUNC(Csm_ReturnType, CRY_CODE) Cry_MD5Start(P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr)
{
  Csm_ReturnType RetVal = CSM_E_NOT_OK;

  CRY_PARAM_UNUSED(cfgPtr);

  /* !LINKSTO EB_Cry_Immediate_Restart,1 */
#if (CRY_MD5_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  if (CRY_S_MD5_IDLE == Cry_MD5Ctx.State)
  {
    /* Set state of the md5 state machine to init                                                 */
    Cry_MD5Ctx.State     = CRY_S_MD5_INIT;
    RetVal               = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }
#else
  /* Set state of the md5 state machine to init                                                 */
  Cry_MD5Ctx.State     = CRY_S_MD5_INIT;
  RetVal               = CSM_E_OK;
#endif

  return RetVal;
}


FUNC(Csm_ReturnType, CRY_CODE) Cry_MD5Update
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
  uint32                                   dataLength
)
{
  Csm_ReturnType RetVal = CSM_E_NOT_OK;

  if (CRY_S_MD5_INITIALIZED == Cry_MD5Ctx.State)
  {

    RetVal = CSM_E_OK;

    /* Store data into context                                                                    */
    Cry_MD5Ctx.Data       = dataPtr;
    Cry_MD5Ctx.DataLength = dataLength;

    /* Set state of the md5 state machine to update                                               */
    Cry_MD5Ctx.ProcessInputState = CRY_S_MD5_PROCESS;
    Cry_MD5Ctx.State             = CRY_S_MD5_UPDATE;
  }
  else
  {
    if (CRY_S_MD5_IDLE != Cry_MD5Ctx.State)
    {
      RetVal = CSM_E_BUSY;
    }
  }

  return RetVal;
}


FUNC(Csm_ReturnType, CRY_CODE) Cry_MD5Finish
(
  P2VAR(uint8,  AUTOMATIC, CRY_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) resultLengthPtr,
  boolean                                 TruncationIsAllowed
)
{
  Csm_ReturnType RetVal = CSM_E_NOT_OK;

  if (CRY_S_MD5_INITIALIZED == Cry_MD5Ctx.State)
  {

    /* !LINKSTO CSM0661, 1
     */
    if (( CRY_MD5_STATE_BYTES > *resultLengthPtr ) && (FALSE == TruncationIsAllowed))
    {
      RetVal           = CSM_E_SMALL_BUFFER;
      Cry_MD5Ctx.State = CRY_S_MD5_IDLE;
    }
    else
    {
      RetVal = CSM_E_OK;

      /* Store data into context                                                                  */
      Cry_MD5Ctx.Result            = resultPtr;
      Cry_MD5Ctx.ResultLengthPtr   = resultLengthPtr;

      /* Set state of the md5 state machine to finish                                             */
      Cry_MD5Ctx.ProcessInputState = CRY_S_MD5_PROCESS;
      Cry_MD5Ctx.State             = CRY_S_MD5_FINISH;
    }
  }
  else
  {
    if (CRY_S_MD5_IDLE != Cry_MD5Ctx.State)
    {
      RetVal = CSM_E_BUSY;
    }
  }

  return RetVal;
}



FUNC(void, CRY_CODE) Cry_MD5MainFunction
(
  void
)
{
  switch(Cry_MD5Ctx.State)
  {

    /* ------------------------------START------------------------------------------*/

    /* Initialise the context of the MD5 algorithm                                              */
    case CRY_S_MD5_INIT:
      /* Init number of processed bytes                                                        */
      Cry_MD5Ctx.Count = (uint32)0U;
      /* Initialize the internal state of the hash function                                    */
      Cry_MD5Ctx.InternalState[0U] = (uint32) 0x67452301UL;
      Cry_MD5Ctx.InternalState[1U] = (uint32) 0xefcdab89UL;
      Cry_MD5Ctx.InternalState[2U] = (uint32) 0x98badcfeUL;
      Cry_MD5Ctx.InternalState[3U] = (uint32) 0x10325476UL;

      /* Update state of the MD5 algorithm                                                     */
      Cry_MD5Ctx.State = CRY_S_MD5_INITIALIZED;
      Csm_HashCallbackNotification(CSM_E_OK);
      break;

    /* Context is initialized there is nothing to do, if the MainFunction invokes us again      */
    case CRY_S_MD5_INITIALIZED:
      break;

    /* ------------------------------UPDATE------------------------------------------*/

    case CRY_S_MD5_UPDATE:
      if ( TRUE == Cry_MD5ProcessInput() )
      {
        Cry_MD5Ctx.State = CRY_S_MD5_INITIALIZED;
        Csm_HashCallbackNotification(CSM_E_OK);
      }
      break;

    /* ------------------------------FINISH------------------------------------------*/

    case CRY_S_MD5_FINISH:
      /* initialize the Pad block */
      Cry_MD5Ctx.MD5Pad[0] = (uint8)0x80;
      Cry_MD5Ctx.length[0] = (uint8)1;

      do
      {
        Cry_MD5Ctx.MD5Pad[Cry_MD5Ctx.length[0]] = (uint8)0;
        ++Cry_MD5Ctx.length[0];
      } while( Cry_MD5Ctx.length[0] < (uint8)CRY_MD5_BLOCK_SIZE );

      /* convert length information */
      Cry_MD5CountConvert(Cry_MD5Ctx.Count, Cry_MD5Ctx.length);

      Cry_MD5Ctx.Data = Cry_MD5Ctx.MD5Pad;
      Cry_MD5Ctx.DataLength =
        ((
          (CRY_MD5_BLOCK_SIZE - 9U) - (Cry_MD5Ctx.Count)
         ) &
         (
           (uint32) 0x3f
         )
        ) + (uint32)1U;

      Cry_MD5Ctx.ProcessInputState = CRY_S_MD5_PROCESS;

      Cry_MD5Ctx.State = CRY_S_MD5_FINISH_COMPLETE;
      break;

    case CRY_S_MD5_FINISH_COMPLETE:

      if (TRUE == Cry_MD5ProcessInput())
      {

        Cry_MD5Ctx.Data = Cry_MD5Ctx.length;

        Cry_MD5Ctx.DataLength = 8U;

        Cry_MD5Ctx.ProcessInputState = CRY_S_MD5_PROCESS;

        Cry_MD5Ctx.State = CRY_S_MD5_FINISH_LENGTH;
      }
      break;

    case CRY_S_MD5_FINISH_LENGTH:

      if (TRUE == Cry_MD5ProcessInput())
      {
        Cry_MD5Ctx.State = CRY_S_MD5_FINISH_EXPORT;
      }
      break;

    case CRY_S_MD5_FINISH_EXPORT:

      Cry_MD5Export();

      Cry_MD5Ctx.State = CRY_S_MD5_IDLE;

      Csm_HashServiceFinishNotification();
      Csm_HashCallbackNotification(CSM_E_OK);
      break;

    /* Something went wrong                                                                     */
    default:
      {
        Cry_MD5Ctx.State = CRY_S_MD5_IDLE;
        Csm_HashCallbackNotification(CSM_E_NOT_OK);
        Csm_HashServiceFinishNotification();
        break;
      }
  }
}

/* Deviation MISRAC2012-1 */
FUNC(P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA), CRY_CODE) Cry_MD5AlgorithmId
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) AlgorithmIdLengthPtr
)
{
  CRY_PARAM_UNUSED(cfgPtr);

  *AlgorithmIdLengthPtr = sizeof(Cry_MD5AlgorithmIdArray);

  return Cry_MD5AlgorithmIdArray;
}

/*==[Definition of functions with internal linkage]===============================================*/

STATIC FUNC(boolean, CRY_CODE) Cry_MD5ProcessInput(void)
{
  boolean finished = FALSE;

  switch(Cry_MD5Ctx.ProcessInputState)
    {
    case CRY_S_MD5_PROCESS:
      /* if there is no data, there is no work to do */
      if(Cry_MD5Ctx.DataLength != (uint32)0)
      {
        Cry_MD5Ctx.p = Cry_MD5Ctx.Data;
        Cry_MD5Ctx.left = Cry_MD5Ctx.DataLength;
        Cry_MD5Ctx.copy = (uint8) 0;

        /* get unprocessed bytes from last block and update the counter */
        Cry_MD5Ctx.offset = (uint8) ((Cry_MD5Ctx.Count) & (uint32) 0x3f);
        /* Ignore a possible overflow here */
        Cry_MD5Ctx.Count += Cry_MD5Ctx.DataLength;

        Cry_MD5Ctx.ProcessInputState = CRY_S_MD5_PROCESS_COPY1;

      }
      else
      {
        finished = TRUE;                                                        /* no work to do */
      }
      break;

    case CRY_S_MD5_PROCESS_COPY1:
      /* if existent, process incomplete blocks */
      if(Cry_MD5Ctx.offset > (uint8) 0)
      {
        /* find out how much data we need to copy */
        if
        (
          (uint32)((uint32)Cry_MD5Ctx.offset + Cry_MD5Ctx.DataLength) >
          (uint32)CRY_MD5_BLOCK_SIZE
        )
        {
          Cry_MD5Ctx.copy = (uint8)CRY_MD5_BLOCK_SIZE - Cry_MD5Ctx.offset;
        }
        else
        {
          /* cast is ok here: we tested dataBytes "< 64" above */
          Cry_MD5Ctx.copy = (uint8) Cry_MD5Ctx.DataLength;
        }
        /* fill up the temporary buffer with as much data as possible */
        Cry_CommonCopy
        (
          &Cry_MD5Ctx.Partial[Cry_MD5Ctx.offset],
          Cry_MD5Ctx.p,
          (uint16)Cry_MD5Ctx.copy
        );

        Cry_MD5Ctx.ProcessInputState = CRY_S_MD5_PROCESS_COMPRESS1;

      }
      else
      {
        Cry_MD5Ctx.ProcessInputState = CRY_S_MD5_PROCESS_COMPRESS3;
      }
      break;

    case CRY_S_MD5_PROCESS_COMPRESS1:
      /* look if we have one block to compress */
      if( (uint8)(Cry_MD5Ctx.offset + Cry_MD5Ctx.copy) < (uint8)CRY_MD5_BLOCK_SIZE )
      {
        /* if we still don't have enough data to fill a block, do nothing                     */
        finished = TRUE;
      }
      else
      {
        /* we have one complete block, so compress it */
        Cry_MD5Ctx.p = &Cry_MD5Ctx.p[Cry_MD5Ctx.copy];
        Cry_MD5Ctx.left -= (uint32)Cry_MD5Ctx.copy;
        Cry_MD5Ctx.CompressState = CRY_S_MD5_COMPRESS;
        Cry_MD5Ctx.ProcessInputState = CRY_S_MD5_PROCESS_COMPRESS2;
      }
      break;

    case CRY_S_MD5_PROCESS_COMPRESS2:
      if ( TRUE == Cry_MD5Compress( Cry_MD5Ctx.Partial ) )
      {
        Cry_MD5Ctx.ProcessInputState = CRY_S_MD5_PROCESS_COMPRESS3;
      }
      break;

    case CRY_S_MD5_PROCESS_COMPRESS3:
      Cry_MD5Ctx.CompressState = CRY_S_MD5_COMPRESS;
      Cry_MD5Ctx.ProcessInputState = CRY_S_MD5_PROCESS_COMPRESS4;
      break;

    case CRY_S_MD5_PROCESS_COMPRESS4:

      /* process complete blocks */
      if ( (Cry_MD5Ctx.left & (uint32)0xffffffc0UL) != (uint32) 0 )
      {
        if ( TRUE == Cry_MD5Compress( Cry_MD5Ctx.p ) )
        {
          Cry_MD5Ctx.p = &Cry_MD5Ctx.p[CRY_MD5_BLOCK_SIZE];
          Cry_MD5Ctx.left -= (uint32)CRY_MD5_BLOCK_SIZE;
        }
      }
      else
      {
        Cry_MD5Ctx.ProcessInputState = CRY_S_MD5_PROCESS_COPY2;
      }
      break;

    case CRY_S_MD5_PROCESS_COPY2:
      /* Check if there is still data */
      if( Cry_MD5Ctx.left > (uint32) 0U )
      {
        /* Copy data into partial buffer */
        Cry_CommonCopy(Cry_MD5Ctx.Partial, Cry_MD5Ctx.p, (uint16)Cry_MD5Ctx.left);
      }
      finished = TRUE;
      break;

    /* CHECK: NOPARSE */
    /* Caution: this 'default' is required by MISRA-C:2004 */
    default:
      {
        finished = TRUE;
        break;
      }
    /* CHECK: PARSE */
  }

  return finished;
}


STATIC FUNC(boolean, CRY_CODE) Cry_MD5Compress
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_CONST) Data
)
{

  boolean finished = FALSE;


  switch(Cry_MD5Ctx.CompressState)
  {
    case CRY_S_MD5_COMPRESS:
      /* Copy global state to local state                                                      */
      Cry_MD5Ctx.a = Cry_MD5Ctx.InternalState[0U];
      Cry_MD5Ctx.b = Cry_MD5Ctx.InternalState[1U];
      Cry_MD5Ctx.c = Cry_MD5Ctx.InternalState[2U];
      Cry_MD5Ctx.d = Cry_MD5Ctx.InternalState[3U];

      /* copy data to local buffer */

      Cry_MD5Ctx.l = 0U;
      for ( Cry_MD5Ctx.i = 0U; Cry_MD5Ctx.i < (CRY_MD5_BLOCK_SIZE >> 2U); Cry_MD5Ctx.i++)
      {
        Cry_MD5Ctx.W[Cry_MD5Ctx.i] = 0U;
        for (Cry_MD5Ctx.k = 0U; Cry_MD5Ctx.k < 4U; Cry_MD5Ctx.k++)
        {
          Cry_MD5Ctx.W[Cry_MD5Ctx.i] |=
            (uint32) Data[Cry_MD5Ctx.l + Cry_MD5Ctx.k] << ((uint32)Cry_MD5Ctx.k << 3U);
        }
        Cry_MD5Ctx.l += 4U;
      }

      /* The message digest transformation loop                                                */
      Cry_MD5Ctx.i = (uint8) 0;
      Cry_MD5Ctx.CompressState = CRY_S_MD5_COMPRESS_PRECALC;
      break;

    case CRY_S_MD5_COMPRESS_PRECALC:
      /* precalculations: select index into nibble-arrays */
      /* k will contain the word access order number */
      Cry_MD5Ctx.l = Z[Cry_MD5Ctx.i >> 1U];
      if( (Cry_MD5Ctx.i & (uint8) 0x01) != 0U )
      {
        /* not divisible by 2: choose lowe nibble */
        Cry_MD5Ctx.k = Cry_MD5Ctx.l & (uint8)0x0f;
      }
      else
      {
        /* divisible by 2: choose higher nibble */
        Cry_MD5Ctx.k =Cry_MD5Ctx.l >> 4U;
      }

      /* round transformation, start with round functions */
      Cry_MD5Ctx.l = Cry_MD5Ctx.i >> 4U; /* divide by 16: 4 rounds with 16 steps */

      Cry_MD5Ctx.CompressState = CRY_S_MD5_COMPRESS_TRANSFORM1;
      break;

    case CRY_S_MD5_COMPRESS_TRANSFORM1:

      /* Round transformation                                                                  */
      switch( Cry_MD5Ctx.l )
      {
           /* Round dependent part first                                                         */
        case 0:
          /* rounds 0 .. 15 */
          Cry_MD5Ctx.t = ((Cry_MD5Ctx.c ^ Cry_MD5Ctx.d) & Cry_MD5Ctx.b) ^ Cry_MD5Ctx.d;
          break;

        case 1:
          /* rounds 16 .. 31 */
          Cry_MD5Ctx.t = (Cry_MD5Ctx.b & Cry_MD5Ctx.d) | (Cry_MD5Ctx.c & (~Cry_MD5Ctx.d));
          break;

        case 2:
          /* rounds 32 .. 47 */
          Cry_MD5Ctx.t = (Cry_MD5Ctx.b ^ Cry_MD5Ctx.c) ^ Cry_MD5Ctx.d;
          break;

        default:
          {
            /* rounds 48 .. 63 */
            Cry_MD5Ctx.t = Cry_MD5Ctx.c ^ (Cry_MD5Ctx.b | (~Cry_MD5Ctx.d));
            break;
          }
      }

      Cry_MD5Ctx.CompressState = CRY_S_MD5_COMPRESS_TRANSFORM2;
      break;

    case CRY_S_MD5_COMPRESS_TRANSFORM2:
      /* round independent part */
      Cry_MD5Ctx.t += Cry_MD5Ctx.a + (Cry_MD5Ctx.W[Cry_MD5Ctx.k] + Y[Cry_MD5Ctx.i]);
      Cry_MD5Ctx.a = Cry_MD5Ctx.d;                         /* permute the words for next round */
      Cry_MD5Ctx.d = Cry_MD5Ctx.c;
      Cry_MD5Ctx.c = Cry_MD5Ctx.b;
      /* b = b + (t shifted left by S[i]) */
      Cry_MD5Ctx.k = S[ ((uint8)(Cry_MD5Ctx.l << 2U)) + (Cry_MD5Ctx.i & (uint8) 0x03) ];
      Cry_MD5Ctx.b += (Cry_MD5Ctx.t << Cry_MD5Ctx.k) | (Cry_MD5Ctx.t >> (32U - Cry_MD5Ctx.k));

      Cry_MD5Ctx.i++;

      if (Cry_MD5Ctx.i != (uint8) CRY_MD5_ROUNDS)
      {
        Cry_MD5Ctx.CompressState = CRY_S_MD5_COMPRESS_PRECALC;
      }
      else
      {
        Cry_MD5Ctx.CompressState = CRY_S_MD5_COMPRESS_EXPORT;
      }
      break;

    case CRY_S_MD5_COMPRESS_EXPORT:
      /* Copy internal state back to MD5Ctx                                                    */
      Cry_MD5Ctx.InternalState[0U] += Cry_MD5Ctx.a;
      Cry_MD5Ctx.InternalState[1U] += Cry_MD5Ctx.b;
      Cry_MD5Ctx.InternalState[2U] += Cry_MD5Ctx.c;
      Cry_MD5Ctx.InternalState[3U] += Cry_MD5Ctx.d;

      finished = TRUE;
      break;

    /* CHECK: NOPARSE */
    /* Caution: this 'default' is required by MISRA-C:2004 */
    default:
      {
        finished = TRUE;
        break;
      }
    /* CHECK: PARSE */
  }
  return finished;
}



STATIC FUNC(void, CRY_CODE) Cry_MD5CountConvert
(
  uint32                                 Count,
  P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) Convert
)
{
                                                                             /* convert into bits */
  Count <<= 3U;

                                                                               /* Copy the result */
  /* ISO-C says that downcasting takes the lowest 8 bits of the 32-bit value                      */
  Convert[0U] = (uint8)(Count       );
  Convert[1U] = (uint8)(Count >>  8U);
  Convert[2U] = (uint8)(Count >> 16U);
  Convert[3U] = (uint8)(Count >> 24U);
  Convert[4U] = (uint8)0;
  Convert[5U] = (uint8)0;
  Convert[6U] = (uint8)0;
  Convert[7U] = (uint8)0;
}



STATIC FUNC(void, CRY_CODE) Cry_MD5Export(void)
{
  uint8 index;                                                                   /* loop variable */
  uint8 tmpIndex;                                               /* tmp space to save loop results */

  if (CRY_MD5_STATE_BYTES < *Cry_MD5Ctx.ResultLengthPtr)
  {
    *Cry_MD5Ctx.ResultLengthPtr = CRY_MD5_STATE_BYTES;
  }

  index = (uint8)0;
  do
  {
    tmpIndex = index;
    tmpIndex <<= 2U;
    if (*Cry_MD5Ctx.ResultLengthPtr > tmpIndex)
    {
      Cry_MD5Ctx.Result[tmpIndex] = (uint8)(Cry_MD5Ctx.InternalState[index]       );
      tmpIndex++;
    }

    if (*Cry_MD5Ctx.ResultLengthPtr > tmpIndex)
    {
      Cry_MD5Ctx.Result[tmpIndex] = (uint8)(Cry_MD5Ctx.InternalState[index] >> 8U );
      tmpIndex++;
    }

    if (*Cry_MD5Ctx.ResultLengthPtr > tmpIndex)
    {
      Cry_MD5Ctx.Result[tmpIndex] = (uint8)(Cry_MD5Ctx.InternalState[index] >> 16U);
      tmpIndex++;
    }

    if (*Cry_MD5Ctx.ResultLengthPtr > tmpIndex)
    {
      Cry_MD5Ctx.Result[tmpIndex] = (uint8)(Cry_MD5Ctx.InternalState[index] >> 24U);
    }
    index++;
  } while (index <= (uint8)(*Cry_MD5Ctx.ResultLengthPtr >> 2U));

}



#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#else /* #if (CRY_MD5_ENABLED == STD_ON) */


/** \brief Dummy definition preventing this file from being empty, if there is no MD5 configuration.
 */
typedef void Cry_MD5_EmptyTranslationUnit_t;

#endif /* #if (CRY_MD5_ENABLED == STD_ON) #else */
