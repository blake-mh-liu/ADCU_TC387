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

/* !LINKSTO EB_CRY_0004,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm_Hash.h>
#include <Csm.h>

#include <Cry_SHA1.h>
#include <Cry_SHA_Common.h>
#include <Cry_Common.h>


#if (CRY_SHA1_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

#if (defined CRY_SHA1_ROUNDS)
#error CRY_SHA1_ROUNDS is already defined
#endif
/** \brief The number of rounds performed by the SHA-1 algorithm. */
#define CRY_SHA1_ROUNDS                80U

#if (defined CRY_SHA1_CH)
#error CRY_SHA1_CH is already defined
#endif
/** \brief The function Ch(x, y, z) from the description of SHA-1 in chapter 4.1.1
 **        of the standard FIPS 180-2
 **/
#define CRY_SHA1_CH(x, y, z)           ((z) ^ ((x) & ((y) ^ (z))))

#if (defined CRY_SHA1_MAJ)
#error CRY_SHA1_MAJ is already defined
#endif
/** \brief The function Maj(x, y, z) from the description of SHA-1 in chapter 4.1.1
 **        of the standard FIPS 180-2
 **/
#define CRY_SHA1_MAJ(x, y, z)          (((x) & (y)) | ((z) & ((x) | (y))))

#if (defined CRY_SHA1_PARITY)
#error CRY_SHA1_PARITY is already defined
#endif
/** \brief The function Parity(x, y, z) from the description of SHA-1 in chapter 4.1.1
 **        of the standard FIPS 180-2
 **/
#define CRY_SHA1_PARITY(x, y, z)       ((x) ^ (y) ^ (z))

#if (defined CRY_SHA1_ROTL)
#error CRY_SHA1_ROTL is already defined
#endif
/** \brief Rotate a 32-bit word by a given amount of bits to the left */
#define CRY_SHA1_ROTL(Word, Amount)             \
  ((uint32)(((Word) << (Amount)) | ((Word) >> (32 - (Amount)))))

#if (defined CRY_SHA1_READ_WORD)
#error CRY_SHA1_READ_WORD is already defined
#endif
/** \brief Converts a byte array to a word
 **/
#define CRY_SHA1_READ_WORD(BufferIndex)                                 \
      (uint32)((uint32)Data[(uint8)(BufferIndex)            ] << 24U) | \
      (uint32)((uint32)Data[(uint8)(BufferIndex) + (uint8)1U] << 16U) | \
      (uint32)((uint32)Data[(uint8)(BufferIndex) + (uint8)2U] <<  8U) | \
               (uint32)Data[(uint8)(BufferIndex) + (uint8)3U];          \

#if (defined CRY_SHA1_CALCULATE_SCHEDULE_WORD)
#error CRY_SHA1_CALCULATE_SCHEDULE_WORD is already defined
/** \brief Calculates a SHA-1 message schedule word, as described in chapter 6.1.2
 **        of the standard FIPS 180-2
 **/
#endif
#define CRY_SHA1_CALCULATE_SCHEDULE_WORD(WordPos)        \
  do                                                     \
  {                                                      \
     Cry_SHA1Ctx.t1 =                                    \
        Cry_SHA1Ctx.W[(uint8)((WordPos) - (uint8) 3U)] ^ \
        Cry_SHA1Ctx.W[(uint8)((WordPos) - (uint8) 8U)] ^ \
        Cry_SHA1Ctx.W[(uint8)((WordPos) - (uint8)14U)] ^ \
        Cry_SHA1Ctx.W[(uint8)((WordPos) - (uint8)16U)];  \
                                                         \
     Cry_SHA1Ctx.W[(WordPos)] =                          \
        (uint32)                                         \
        (                                                \
           (uint32)(Cry_SHA1Ctx.t1 << 1U) |              \
           (uint32)(Cry_SHA1Ctx.t1 >> 31U)               \
        );                                               \
  } while (0)

#if (defined CRY_SHA1_ROUND_OPERATION_1)
#error CRY_SHA1_ROUND_OPERATION_1 is already defined
#endif
/** \brief Performs a SHA-1 round operation for stage 1 (rounds 0 to 19) */
#define CRY_SHA1_ROUND_OPERATION_1(a, b, c, d, e, i) \
  do                                                 \
  {                                                  \
    (e) = CRY_SHA1_ROTL((a), 5U)     +               \
          CRY_SHA1_CH((b), (c), (d)) +               \
          (e)                        +               \
          Cry_SHA1Ctx.W[(i)]         +               \
          (uint32)0x5a827999UL;                      \
    (b) = CRY_SHA1_ROTL((b), 30U);                   \
  } while (0)

#if (defined CRY_SHA1_ROUND_OPERATION_2)
#error CRY_SHA1_ROUND_OPERATION_2 is already defined
#endif
/** \brief Performs a SHA-1 round operation for stage 2 (rounds 20 to 39) */
#define CRY_SHA1_ROUND_OPERATION_2(a, b, c, d, e, i) \
  do                                                 \
  {                                                  \
    (e) = CRY_SHA1_ROTL((a), 5U)         +           \
          CRY_SHA1_PARITY((b), (c), (d)) +           \
          (e)                            +           \
          Cry_SHA1Ctx.W[(i)]             +           \
          (uint32)0x6ed9eba1UL;                      \
    (b) = CRY_SHA1_ROTL((b), 30U);                   \
  } while (0)

#if (defined CRY_SHA1_ROUND_OPERATION_3)
#error CRY_SHA1_ROUND_OPERATION_3 is already defined
#endif
/** \brief Performs a SHA-1 round operation for stage 3 (rounds 40 to 59) */
#define CRY_SHA1_ROUND_OPERATION_3(a, b, c, d, e, i) \
  do                                                 \
  {                                                  \
    (e) = CRY_SHA1_ROTL((a), 5U)      +              \
          CRY_SHA1_MAJ((b), (c), (d)) +              \
          (e)                         +              \
          Cry_SHA1Ctx.W[(i)]          +              \
          (uint32)0x8f1bbcdcUL;                      \
    (b) = CRY_SHA1_ROTL((b), 30U);                   \
  } while (0)

#if (defined CRY_SHA1_ROUND_OPERATION_4)
#error CRY_SHA1_ROUND_OPERATION_4 is already defined
#endif
/** \brief Performs a SHA-1 round operation for stage 4 (rounds 60 to 79) */
#define CRY_SHA1_ROUND_OPERATION_4(a, b, c, d, e, i) \
  do                                                 \
  {                                                  \
    (e) = CRY_SHA1_ROTL((a), 5U)         +           \
          CRY_SHA1_PARITY((b), (c), (d)) +           \
          (e)                            +           \
          Cry_SHA1Ctx.W[(i)]             +           \
          (uint32)0xca62c1d6UL;                      \
    (b) = CRY_SHA1_ROTL((b), 30U);                   \
  } while (0)

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief  Initialize Processing of hash request
 **
 **  This function initializes the internal states to prepare for a hash calculation
 **
 **/
static FUNC(void, CRY_CODE) Cry_SHA1Init
(
  void
);

/** \brief  Processes one block of data to hash
 **
 **  This function compresses one block of data to hash according to the rules
 **  of SHA-1 and updates the internal state accordingly. The macro
 **  CRY_SHACOMPRESSSTART() has to be called before the first call to this
 **  function.
 **
 ** \param[in] Data A pointer to a block of data of size
 ** ::CRY_SHA1_BLOCK_LEN_BYTES bytes which has to be processed
 **
 ** \returns Compression operation state
 **
 ** \retval FALSE The compression has not yet finished. It has to be called again with
 ** the same parameters
 **
 ** \retval TRUE The compression has finished. Now, the result is stored in the
 ** context variable
 **
 **/
static FUNC(boolean, CRY_CODE) Cry_SHA1Compress
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) Data
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief SHA1 Ctx
 **
 ** The context variable which is used to store the internal state of the
 ** SHA1 computation
 **/
static VAR(Cry_SHACtxType, CRY_VAR) Cry_SHA1Ctx;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO CS_SECURE_CRY_SHA1Start,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_SHA1Start
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO EB_Cry_Immediate_Restart,1 */
#if (CRY_SHA1_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  if(CRY_SHA_S_IDLE == Cry_SHA1Ctx.State)
  {
    Cry_SHA1Ctx.CfgPtr =
        (P2CONST(Cry_SHAConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;

    Cry_SHA1Ctx.State = CRY_SHA_S_INIT;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }
#else
    Cry_SHA1Ctx.CfgPtr =
        (P2CONST(Cry_SHAConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;

    Cry_SHA1Ctx.State = CRY_SHA_S_INIT;

    RetVal = CSM_E_OK;
#endif

  return RetVal;
}

/* !LINKSTO CS_SECURE_CRY_SHA1Update,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_SHA1Update
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
  uint32                                   dataLength
)
{
  Csm_ReturnType RetVal;


  if(CRY_SHA_S_IDLE == Cry_SHA1Ctx.State)
  {
    RetVal = CSM_E_NOT_OK;
  }
  else if(CRY_SHA_S_INITIALIZED == Cry_SHA1Ctx.State)
  {
    /* Store data into context */
    Cry_SHA1Ctx.Data = dataPtr;
    Cry_SHA1Ctx.DataLength = dataLength;

    /* Set state of the state machine to update */
    Cry_SHA1Ctx.State = CRY_SHA_S_UPDATE;

    Cry_SHA1Ctx.ProcessInputState = CRY_SHA_S_PROCESS;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}

/* !LINKSTO CS_SECURE_CRY_SHA1Finish,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_SHA1Finish
(
  P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA)  resultPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) resultLengthPtr,
  boolean                                 truncationAllowed
)
{
  Csm_ReturnType RetVal;


  if(CRY_SHA_S_IDLE == Cry_SHA1Ctx.State)
  {
    RetVal = CSM_E_NOT_OK;
  }
  else if(CRY_SHA_S_INITIALIZED == Cry_SHA1Ctx.State)
  {
    /* Store data into context */
    Cry_SHA1Ctx.Result = resultPtr;
    Cry_SHA1Ctx.ResultLengthPtr = resultLengthPtr;
    Cry_SHA1Ctx.TruncationAllowed = truncationAllowed;
    /* Set state of the state machine to finish */
    Cry_SHA1Ctx.State = CRY_SHA_S_FINISH;

    Cry_SHA1Ctx.ProcessInputState = CRY_SHA_S_PROCESS;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}

/* !LINKSTO  CS_SECURE_CRY_SHA1MainFunction, 1 */
FUNC(void, CRY_CODE) Cry_SHA1MainFunction
(
  void
)
{
  Cry_SHAMainFunction(&Cry_SHA1Ctx, &Cry_SHA1Init, &Cry_SHA1Compress);
}

/* !LINKSTO EB_CRY_0015,1 */
/* Deviation MISRAC2012-1 */
FUNC(P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA), CRY_CODE) Cry_SHA1AlgorithmId
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) AlgorithmIdLengthPtr
)
{
  *AlgorithmIdLengthPtr =
      ((P2CONST(Cry_SHAConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr)->AlgorithmIdLength;

  return ((P2CONST(Cry_SHAConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr)->AlgorithmId;
}

/*==[Definition of functions with internal linkage]===========================*/

static FUNC(void, CRY_CODE) Cry_SHA1Init (void)
{
  Cry_SHA1Ctx.Internalstate[0U] = (uint32) 0x67452301UL;
  Cry_SHA1Ctx.Internalstate[1U] = (uint32) 0xefcdab89UL;
  Cry_SHA1Ctx.Internalstate[2U] = (uint32) 0x98badcfeUL;
  Cry_SHA1Ctx.Internalstate[3U] = (uint32) 0x10325476UL;
  Cry_SHA1Ctx.Internalstate[4U] = (uint32) 0xc3d2e1f0UL;
}

static FUNC(boolean, CRY_CODE) Cry_SHA1Compress
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) Data
)
{
  boolean finished;
#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
  uint16 iterationCnt = 0U;
  finished = FALSE;
#else
  finished = TRUE;
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
  /* If IterationsPerMain is 0, the while loop shall be left only when it's finished */
  while ((finished == FALSE) &&
         ((Cry_SHA1Ctx.CfgPtr->IterationsPerMain == 0U) ||
          (iterationCnt < Cry_SHA1Ctx.CfgPtr->IterationsPerMain))
        )
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */
  {
#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
    iterationCnt++;

    switch (Cry_SHA1Ctx.SHACompressState)
    {
      case CRY_SHA_S_COMPRESS:
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */
        Cry_SHA1Ctx.a = Cry_SHA1Ctx.Internalstate[0U];
        Cry_SHA1Ctx.b = Cry_SHA1Ctx.Internalstate[1U];
        Cry_SHA1Ctx.c = Cry_SHA1Ctx.Internalstate[2U];
        Cry_SHA1Ctx.d = Cry_SHA1Ctx.Internalstate[3U];
        Cry_SHA1Ctx.e = Cry_SHA1Ctx.Internalstate[4U];

        /* copy data to local buffer */
        Cry_SHA1Ctx.i = (uint8)0U;

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
        /* 2. the message Cry_SHA1Ctx.result transformation loop */
        Cry_SHA1Ctx.SHACompressState = CRY_SHA_S_COMPRESS_EXPANSION;
        break;
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
      case CRY_SHA_S_COMPRESS_EXPANSION:
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */
        for (Cry_SHA1Ctx.i = 0U; Cry_SHA1Ctx.i < (uint8)CRY_SHA1_ROUNDS; Cry_SHA1Ctx.i += 4U)
        {
          /* Prepare the message schedule */
          if (Cry_SHA1Ctx.i < (uint8)(CRY_SHA1_BLOCK_LEN_BYTES / 4U))
          {
            const uint8 dataIdx = Cry_SHA1Ctx.i << (uint8)2U;

            /* copy the first 64 bytes from the user input to the message schedule */
            Cry_SHA1Ctx.W[(uint8)(Cry_SHA1Ctx.i + 0U)] =
              CRY_SHA1_READ_WORD((uint8)(dataIdx +  0U));
            Cry_SHA1Ctx.W[(uint8)(Cry_SHA1Ctx.i + 1U)] =
              CRY_SHA1_READ_WORD((uint8)(dataIdx +  4U));
            Cry_SHA1Ctx.W[(uint8)(Cry_SHA1Ctx.i + 2U)] =
              CRY_SHA1_READ_WORD((uint8)(dataIdx +  8U));
            Cry_SHA1Ctx.W[(uint8)(Cry_SHA1Ctx.i + 3U)] =
              CRY_SHA1_READ_WORD((uint8)(dataIdx + 12U));
          }
          else
          {
            /* each word is constructed recursively from 4 previous words */
            CRY_SHA1_CALCULATE_SCHEDULE_WORD(Cry_SHA1Ctx.i + 0U);
            CRY_SHA1_CALCULATE_SCHEDULE_WORD(Cry_SHA1Ctx.i + 1U);
            CRY_SHA1_CALCULATE_SCHEDULE_WORD(Cry_SHA1Ctx.i + 2U);
            CRY_SHA1_CALCULATE_SCHEDULE_WORD(Cry_SHA1Ctx.i + 3U);
          }
        }

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
        Cry_SHA1Ctx.i = (uint8)0U;
        /* 2. the message Cry_SHA1Ctx.result transformation loop */
        Cry_SHA1Ctx.SHACompressState = CRY_SHA_S_COMPRESS_TRANSFORM;
        break;
          /* Perform the entire message expansion once */
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
      case CRY_SHA_S_COMPRESS_TRANSFORM:
#else
        for (Cry_SHA1Ctx.i = 0U; Cry_SHA1Ctx.i < CRY_SHA1_ROUNDS; Cry_SHA1Ctx.i += 5U)
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */
        {
          const uint8 roundOperation = Cry_SHA1Ctx.i / (uint8)20U;

          /* Perform the round operations */
          switch (roundOperation)
          {
            case 0U:
              CRY_SHA1_ROUND_OPERATION_1(Cry_SHA1Ctx.a,
                                         Cry_SHA1Ctx.b,
                                         Cry_SHA1Ctx.c,
                                         Cry_SHA1Ctx.d,
                                         Cry_SHA1Ctx.e,
                                         (Cry_SHA1Ctx.i + 0U));

              CRY_SHA1_ROUND_OPERATION_1(Cry_SHA1Ctx.e,
                                         Cry_SHA1Ctx.a,
                                         Cry_SHA1Ctx.b,
                                         Cry_SHA1Ctx.c,
                                         Cry_SHA1Ctx.d,
                                         (Cry_SHA1Ctx.i + 1U));

              CRY_SHA1_ROUND_OPERATION_1(Cry_SHA1Ctx.d,
                                         Cry_SHA1Ctx.e,
                                         Cry_SHA1Ctx.a,
                                         Cry_SHA1Ctx.b,
                                         Cry_SHA1Ctx.c,
                                         (Cry_SHA1Ctx.i + 2U));

              CRY_SHA1_ROUND_OPERATION_1(Cry_SHA1Ctx.c,
                                         Cry_SHA1Ctx.d,
                                         Cry_SHA1Ctx.e,
                                         Cry_SHA1Ctx.a,
                                         Cry_SHA1Ctx.b,
                                         (Cry_SHA1Ctx.i + 3U));

              CRY_SHA1_ROUND_OPERATION_1(Cry_SHA1Ctx.b,
                                         Cry_SHA1Ctx.c,
                                         Cry_SHA1Ctx.d,
                                         Cry_SHA1Ctx.e,
                                         Cry_SHA1Ctx.a,
                                         (Cry_SHA1Ctx.i + 4U));
              break;

            case 1U:
              CRY_SHA1_ROUND_OPERATION_2(Cry_SHA1Ctx.a,
                                         Cry_SHA1Ctx.b,
                                         Cry_SHA1Ctx.c,
                                         Cry_SHA1Ctx.d,
                                         Cry_SHA1Ctx.e,
                                         (Cry_SHA1Ctx.i + 0U));

              CRY_SHA1_ROUND_OPERATION_2(Cry_SHA1Ctx.e,
                                         Cry_SHA1Ctx.a,
                                         Cry_SHA1Ctx.b,
                                         Cry_SHA1Ctx.c,
                                         Cry_SHA1Ctx.d,
                                         (Cry_SHA1Ctx.i + 1U));

              CRY_SHA1_ROUND_OPERATION_2(Cry_SHA1Ctx.d,
                                         Cry_SHA1Ctx.e,
                                         Cry_SHA1Ctx.a,
                                         Cry_SHA1Ctx.b,
                                         Cry_SHA1Ctx.c,
                                         (Cry_SHA1Ctx.i + 2U));

              CRY_SHA1_ROUND_OPERATION_2(Cry_SHA1Ctx.c,
                                         Cry_SHA1Ctx.d,
                                         Cry_SHA1Ctx.e,
                                         Cry_SHA1Ctx.a,
                                         Cry_SHA1Ctx.b,
                                         (Cry_SHA1Ctx.i + 3U));

              CRY_SHA1_ROUND_OPERATION_2(Cry_SHA1Ctx.b,
                                         Cry_SHA1Ctx.c,
                                         Cry_SHA1Ctx.d,
                                         Cry_SHA1Ctx.e,
                                         Cry_SHA1Ctx.a,
                                         (Cry_SHA1Ctx.i + 4U));
              break;

            case 2U:
              CRY_SHA1_ROUND_OPERATION_3(Cry_SHA1Ctx.a,
                                         Cry_SHA1Ctx.b,
                                         Cry_SHA1Ctx.c,
                                         Cry_SHA1Ctx.d,
                                         Cry_SHA1Ctx.e,
                                         (Cry_SHA1Ctx.i + 0U));

              CRY_SHA1_ROUND_OPERATION_3(Cry_SHA1Ctx.e,
                                         Cry_SHA1Ctx.a,
                                         Cry_SHA1Ctx.b,
                                         Cry_SHA1Ctx.c,
                                         Cry_SHA1Ctx.d,
                                         (Cry_SHA1Ctx.i + 1U));

              CRY_SHA1_ROUND_OPERATION_3(Cry_SHA1Ctx.d,
                                         Cry_SHA1Ctx.e,
                                         Cry_SHA1Ctx.a,
                                         Cry_SHA1Ctx.b,
                                         Cry_SHA1Ctx.c,
                                         (Cry_SHA1Ctx.i + 2U));

              CRY_SHA1_ROUND_OPERATION_3(Cry_SHA1Ctx.c,
                                         Cry_SHA1Ctx.d,
                                         Cry_SHA1Ctx.e,
                                         Cry_SHA1Ctx.a,
                                         Cry_SHA1Ctx.b,
                                         (Cry_SHA1Ctx.i + 3U));

              CRY_SHA1_ROUND_OPERATION_3(Cry_SHA1Ctx.b,
                                         Cry_SHA1Ctx.c,
                                         Cry_SHA1Ctx.d,
                                         Cry_SHA1Ctx.e,
                                         Cry_SHA1Ctx.a,
                                         (Cry_SHA1Ctx.i + 4U));
              break;

            default:
              {
                CRY_SHA1_ROUND_OPERATION_4(Cry_SHA1Ctx.a,
                                           Cry_SHA1Ctx.b,
                                           Cry_SHA1Ctx.c,
                                           Cry_SHA1Ctx.d,
                                           Cry_SHA1Ctx.e,
                                           (Cry_SHA1Ctx.i + 0U));

                CRY_SHA1_ROUND_OPERATION_4(Cry_SHA1Ctx.e,
                                           Cry_SHA1Ctx.a,
                                           Cry_SHA1Ctx.b,
                                           Cry_SHA1Ctx.c,
                                           Cry_SHA1Ctx.d,
                                           (Cry_SHA1Ctx.i + 1U));

                CRY_SHA1_ROUND_OPERATION_4(Cry_SHA1Ctx.d,
                                           Cry_SHA1Ctx.e,
                                           Cry_SHA1Ctx.a,
                                           Cry_SHA1Ctx.b,
                                           Cry_SHA1Ctx.c,
                                           (Cry_SHA1Ctx.i + 2U));

                CRY_SHA1_ROUND_OPERATION_4(Cry_SHA1Ctx.c,
                                           Cry_SHA1Ctx.d,
                                           Cry_SHA1Ctx.e,
                                           Cry_SHA1Ctx.a,
                                           Cry_SHA1Ctx.b,
                                           (Cry_SHA1Ctx.i + 3U));

                CRY_SHA1_ROUND_OPERATION_4(Cry_SHA1Ctx.b,
                                           Cry_SHA1Ctx.c,
                                           Cry_SHA1Ctx.d,
                                           Cry_SHA1Ctx.e,
                                           Cry_SHA1Ctx.a,
                                           (Cry_SHA1Ctx.i + 4U));
                break;
              }
          }
        }

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
        Cry_SHA1Ctx.i += 5U;

        if (Cry_SHA1Ctx.i == (uint8)CRY_SHA1_ROUNDS)
        {
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */
          /* 3. copy internal state back to Ctx */
          Cry_SHA1Ctx.Internalstate[0U] += Cry_SHA1Ctx.a;
          Cry_SHA1Ctx.Internalstate[1U] += Cry_SHA1Ctx.b;
          Cry_SHA1Ctx.Internalstate[2U] += Cry_SHA1Ctx.c;
          Cry_SHA1Ctx.Internalstate[3U] += Cry_SHA1Ctx.d;
          Cry_SHA1Ctx.Internalstate[4U] += Cry_SHA1Ctx.e;

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
          /* Processing of the message block is completed */
          finished = TRUE;
        }
        break;
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
      /* CHECK: NOPARSE */
      /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
      default:
        {
          finished = TRUE;
          break;
        }
      /* CHECK: PARSE */
    }
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */
  }

  return finished;
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#else /* #if (CRY_SHA1_ENABLED == STD_ON) */

typedef uint8 Cry_SHA1_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_SHA1_ENABLED == STD_ON) #else */
