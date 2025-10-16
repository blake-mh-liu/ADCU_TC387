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

#include <Cry_SHA2.h>
#include <Cry_SHA_Common.h>
#include <Cry_Common.h>


#if (CRY_SHA2_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

#if (CRY_SHA2_WORD_SIZE == 32U)

#if (defined CRY_SHA224256_ROUNDS)
#error CRY_SHA224256_ROUNDS is already defined
#endif
/** \brief The number of rounds performed by the SHA-256 or SHA-224 algorithm
 **
 **/
#define CRY_SHA224256_ROUNDS 64U

#if (defined CRY_SHA224256_ROTR)
#error CRY_SHA224256_ROTR is already defined
#endif
/** \brief Rotate a 32-bit word by a given amount of bits to the right
 **
 **/
#define CRY_SHA224256_ROTR(Word, Amount) \
  ((uint32)(((Word) >> (Amount)) | ((Word) << (32 - (Amount)))))

#if (defined CRY_SHA224256_ROTL)
#error CRY_SHA224256_ROTL is already defined
#endif
/** \brief Rotate a 32-bit word by a given amount of bits to the left.
 **
 **/
#define CRY_SHA224256_ROTL(Word, Amount) \
  ((uint32)(((Word) << (Amount)) | ((Word) >> (32 - (Amount)))))

#if (defined CRY_SHA224256_CAPITAL_SIGMA_0)
#error CRY_SHA224256_CAPITAL_SIGMA_0 is already defined
#endif
/** \brief The function (in LaTex notation) $\Sigma^{\{256\}}_0(x)$ from the
 ** description of SHA-256 or SHA-224 in chapter 4.1.2 of the standard FIPS 180-2
 **
 **/
#define CRY_SHA224256_CAPITAL_SIGMA_0(Word) \
(                                           \
  (uint32)                                  \
  (                                         \
    CRY_SHA224256_ROTR((Word),  2) ^        \
    CRY_SHA224256_ROTR((Word), 13) ^        \
    CRY_SHA224256_ROTR((Word), 22)          \
  )                                         \
)

#if (defined CRY_SHA224256_CAPITAL_SIGMA_1)
#error CRY_SHA224256_CAPITAL_SIGMA_1 is already defined
#endif
/** \brief The function (in LaTex notation) $\Sigma^{\{256\}}_1(x)$ from the
 ** description of SHA-256 or SHA-224 in chapter 4.1.2 of the standard FIPS 180-2
 **
 **/
#define CRY_SHA224256_CAPITAL_SIGMA_1(Word) \
(                                           \
  (uint32)                                  \
  (                                         \
     CRY_SHA224256_ROTR((Word),  6) ^       \
     CRY_SHA224256_ROTR((Word), 11) ^       \
     CRY_SHA224256_ROTR((Word), 25)         \
  )                                         \
)

#if (defined CRY_SHA224256_SMALL_SIGMA_0)
#error CRY_SHA224256_SMALL_SIGMA_0 is already defined
#endif
/** \brief The function (in LaTex notation) $\sigma^{\{256\}}_0(x)$ from the
 **  description of SHA-256 or SHA-224 in chapter 4.1.2 of the standard FIPS 180-2
 **
 **/
#define CRY_SHA224256_SMALL_SIGMA_0(Word) \
(                                         \
  (uint32)                                \
  (                                       \
    CRY_SHA224256_ROTR((Word),  7) ^      \
    CRY_SHA224256_ROTR((Word), 18) ^      \
    (uint32)((Word) >> 3)                 \
  )                                       \
)

#if (defined CRY_SHA224256_SMALL_SIGMA_1)
#error CRY_SHA224256_SMALL_SIGMA_1 is already defined
#endif
/** \brief The function (in LaTex notation) $\sigma^{\{256\}}_1(x)$ from the
 ** description of SHA-256 or SHA-224 in chapter 4.1.2 of the standard FIPS 180-2
 **
 **/
#define CRY_SHA224256_SMALL_SIGMA_1(Word) \
(                                         \
  (uint32)                                \
  (                                       \
    CRY_SHA224256_ROTR((Word), 17) ^      \
    CRY_SHA224256_ROTR((Word), 19) ^      \
    (uint32)((Word) >> 10)                \
  )                                       \
)

#if (defined CRY_SHA224256_CH)
#error CRY_SHA224256_CH is already defined
#endif
/** \brief The function Ch(x, y, z) from the description of SHA-224/SHA-256 in chapter 4.1.2
 **        of the standard FIPS 180-2
 **/
#define CRY_SHA224256_CH(x, y, z)       ((z) ^ ((x) & ((y) ^ (z))))

#if (defined CRY_SHA224256_MAJ)
#error CRY_SHA224256_MAJ is already defined
#endif
/** \brief The function Maj(x, y, z) from the description of SHA-224/SHA-256 in chapter 4.1.2
 **        of the standard FIPS 180-2
 **/
#define CRY_SHA224256_MAJ(x, y, z)      ((((x) | (y)) & (z)) | ((x) & (y)))

#if (defined CRY_SHA224256_READ_WORD)
#error CRY_SHA224256_READ_WORD is already defined
#endif
/** \brief Converts a byte array to a word
 **/
#define CRY_SHA224256_READ_WORD(BufferIndex)                            \
      (uint32)((uint32)Data[(uint8)(BufferIndex)            ] << 24U) | \
      (uint32)((uint32)Data[(uint8)(BufferIndex) + (uint8)1U] << 16U) | \
      (uint32)((uint32)Data[(uint8)(BufferIndex) + (uint8)2U] <<  8U) | \
               (uint32)Data[(uint8)(BufferIndex) + (uint8)3U];          \

#if (defined CRY_SHA224256_CALCULATE_SCHEDULE_WORD)
#error CRY_SHA224256_CALCULATE_SCHEDULE_WORD is already defined
#endif
/** \brief Calculates a SHA-224/SHA-256 message schedule word, as described in chapter 6.2.2
 **        of the standards FIPS 180-2
 **/
#define CRY_SHA224256_CALCULATE_SCHEDULE_WORD(WordPos)          \
   do                                                           \
   {                                                            \
      Cry_SHA2Ctx.W[(WordPos)] =                                \
         CRY_SHA224256_SMALL_SIGMA_1                            \
            (Cry_SHA2Ctx.W[(uint8)((WordPos) - (uint8)2U)]) +   \
         Cry_SHA2Ctx.W[(uint8)((WordPos) - (uint8)7U)]       +  \
         CRY_SHA224256_SMALL_SIGMA_0                            \
            (Cry_SHA2Ctx.W[(uint8)((WordPos) -  (uint8)15U)]) + \
         Cry_SHA2Ctx.W[(uint8)((WordPos) - (uint8)16U)];        \
   } while (0)

#if (defined CRY_SHA224256_ROUND_OPERATION)
#error CRY_SHA224256_ROUND_OPERATION is already defined
#endif
/** \brief Performs a SHA-224/SHA-256 round operation */
#define CRY_SHA224256_ROUND_OPERATION(a, b, c, d, e, f, g, h, i) \
   do                                                            \
   {                                                             \
      Cry_SHA2Ctx.t1 = (h) +                                     \
                       CRY_SHA224256_CAPITAL_SIGMA_1((e)) +      \
                       CRY_SHA224256_CH((e), (f), (g))    +      \
                       Cry_SHA224256K[(i)]                +      \
                       Cry_SHA2Ctx.W[(i)];      \
      Cry_SHA2Ctx.t2 = CRY_SHA224256_CAPITAL_SIGMA_0((a)) +      \
                       CRY_SHA224256_MAJ((a), (b), (c));         \
      (d) += Cry_SHA2Ctx.t1;                                     \
      (h) = Cry_SHA2Ctx.t1 + Cry_SHA2Ctx.t2;                     \
   } while (0)

#endif

#if (CRY_SHA2_WORD_SIZE == 64U)

#if (defined CRY_SHA384512_ROUNDS)
#error CRY_SHA384512_ROUNDS is already defined
#endif
/** \brief The number of rounds performed by the SHA-384 or SHA-512 algorithm
 **
 **/
#define CRY_SHA384512_ROUNDS 80U

#if (defined CRY_SHA384512_READ_UPPER_WORD)
#error CRY_SHA384512_READ_UPPER_WORD is already defined
#endif
/** \brief Converts a byte array to a word
 **/
#define CRY_SHA384512_READ_UPPER_WORD(BufferIndex)                      \
      (uint32)((uint32)Data[(uint8)(BufferIndex)            ] << 24U) | \
      (uint32)((uint32)Data[(uint8)(BufferIndex) + (uint8)1U] << 16U) | \
      (uint32)((uint32)Data[(uint8)(BufferIndex) + (uint8)2U] <<  8U) | \
               (uint32)Data[(uint8)(BufferIndex) + (uint8)3U];          \

#if (defined CRY_SHA384512_READ_LOWER_WORD)
#error CRY_SHA384512_READ_LOWER_WORD is already defined
#endif
/** \brief Converts a byte array to a word
 **/
#define CRY_SHA384512_READ_LOWER_WORD(BufferIndex)                      \
      (uint32)((uint32)Data[(uint8)(BufferIndex) + (uint8)4U] << 24U) | \
      (uint32)((uint32)Data[(uint8)(BufferIndex) + (uint8)5U] << 16U) | \
      (uint32)((uint32)Data[(uint8)(BufferIndex) + (uint8)6U] <<  8U) | \
               (uint32)Data[(uint8)(BufferIndex) + (uint8)7U];          \

#if (defined CRY_SHA384512_CH)
#error CRY_SHA384512_CH is already defined
#endif
/** \brief The function Ch(x, y, z) from the description of SHA-384/SHA-512 in chapter 4.1.3
 **        of the standard FIPS 180-2
 **/
#define CRY_SHA384512_CH(x, y, z)                            \
  do                                                         \
  {                                                          \
    ch[0] = (((z)[0]) ^ (((x)[0]) & (((y)[0]) ^ ((z)[0])))); \
    ch[1] = (((z)[1]) ^ (((x)[1]) & (((y)[1]) ^ ((z)[1])))); \
  } while (0)

#if (defined CRY_SHA384512_MAJ)
#error CRY_SHA384512_MAJ is already defined
#endif
/** \brief The function Maj(x, y, z) from the description of SHA-384/SHA-512 in chapter 4.1.3
 **        of the standard FIPS 180-2
 **/
#define CRY_SHA384512_MAJ(x, y, z)                                         \
  do                                                                       \
  {                                                                        \
    maj[0] = (((((x)[0]) | ((y)[0])) & ((z)[0])) | (((x)[0]) & ((y)[0]))); \
    maj[1] = (((((x)[1]) | ((y)[1])) & ((z)[1])) | (((x)[1]) & ((y)[1]))); \
  } while (0)

#if (defined CRY_SHA384512_ADD)
#error CRY_SHA384512_ADD is already defined
#endif
/** \brief Addition modulo 2^64 where an uint64 is implemented as
 **        an array of two uint32.
 **        Ans[0U] respresents the lower word and Ans[1U] the high word.
 **/
#define CRY_SHA384512_ADD(Ans, N, M)                                            \
  do                                                                            \
  {                                                                             \
    (Ans)[1U] = (N)[1U] + (M)[1U] +                                             \
              (((((N)[0] + (M)[0]) < (N)[0]) || (((N)[0] + (M)[0]) < (M)[0])) ? \
                (uint32)1U : (uint32)0U);                                       \
    (Ans)[0U] = (N)[0U] + (M)[0U];                                              \
  } while (0)

#if (defined CRY_SHA384512_ROTR)
#error CRY_SHA384512_ROTR is already defined
#endif
/** \brief Rotate a 64-bit word by a given amount of bits to the right
 *         word[0U] respresents the lower word and word[1U] the high word.
 **/
#define CRY_SHA384512_ROTR(word, offset)                            \
  do                                                                \
  {                                                                 \
    uint32 accLower = 0U, accUpper = 0U;                            \
    uint32 tmpOffset = (offset);                                    \
                                                                    \
    if ((tmpOffset) > CRY_SHA2_WORDWIDTH)                           \
    {                                                               \
      uint32 tmp0, tmp1;                                            \
                                                                    \
      tmp0 = (word)[0U];                                            \
      tmp1 = (word)[1U];                                            \
                                                                    \
      (tmpOffset) -= CRY_SHA2_WORDWIDTH;                            \
                                                                    \
      accLower = (word)[0U]  << (CRY_SHA2_WORDWIDTH - (tmpOffset)); \
      accUpper = (word)[1U]  << (CRY_SHA2_WORDWIDTH - (tmpOffset)); \
                                                                    \
      (word)[1U] = accUpper | (tmp0 >> (tmpOffset));                \
      (word)[0U] = accLower | (tmp1 >> (tmpOffset));                \
    }                                                               \
    else                                                            \
    {                                                               \
      accLower = (word)[0U] << (CRY_SHA2_WORDWIDTH - (tmpOffset));  \
      accUpper = (word)[1U] << (CRY_SHA2_WORDWIDTH - (tmpOffset));  \
                                                                    \
      (word)[0U] = accUpper | ((word)[0U] >> (tmpOffset));          \
      (word)[1U] = accLower | ((word)[1U] >> (tmpOffset));          \
    }                                                               \
  } while (0)

#if (defined CRY_SHA384512_SHR)
#error CRY_SHA384512_SHR is already defined
#endif
/** \brief The function (in LaTex notation) $\SHR^{\{n}}(x)$ from the
 **        description of SHA-384 or SHA-512 in chapter 4.1.2 of the standard FIPS 180-2
 **        word[0U] respresents the lower word and word[1U] the high word.
 **/
#define CRY_SHA384512_SHR(word, offset)                       \
  do                                                          \
  {                                                           \
    uint32 accUpper = 0U;                                     \
                                                              \
    accUpper = (word)[1U] << (CRY_SHA2_WORDWIDTH - (offset)); \
                                                              \
    (word)[0U] = accUpper | ((word)[0U] >> (offset));         \
    (word)[1U] = ((word)[1U] >> (offset));                    \
  } while (0)

#if (defined CRY_SHA384512_CALCULATE_SCHEDULE_WORD)
#error CRY_SHA384512_CALCULATE_SCHEDULE_WORD
#endif
/** \brief Calculates a SHA-384/SHA-512 message schedule word, as described in chapter 6.3.2
 **        of the standard FIPS 180-2
 **/
#define CRY_SHA384512_CALCULATE_SCHEDULE_WORD(WordPos)                                          \
  do                                                                                            \
  {                                                                                             \
    addTmp0[0U] = Cry_SHA2Ctx.W[(uint8)        (((WordPos) - (uint8)2U) << 1U)     ];           \
    addTmp0[1U] = Cry_SHA2Ctx.W[(uint8)((uint8)(((WordPos) - (uint8)2U) << 1U) + 1U)];          \
    Cry_SHA384512_SmallSigma1(addTmp0);                                                         \
    sigm0[0U] = addTmp0[0U];                                                                    \
    sigm0[1U] = addTmp0[1U];                                                                    \
                                                                                                \
    addTmp0[0U] = Cry_SHA2Ctx.W[(uint8)        (((WordPos) - (uint8)15U) << 1U)      ];         \
    addTmp0[1U] = Cry_SHA2Ctx.W[(uint8)((uint8)(((WordPos) - (uint8)15U) << 1U) + 1U)];         \
    Cry_SHA384512_SmallSigma0(addTmp0);                                                         \
    sigm1[0U] = addTmp0[0U];                                                                    \
    sigm1[1U] = addTmp0[1U];                                                                    \
                                                                                                \
    CRY_SHA384512_ADD(addTmp0, sigm0, &Cry_SHA2Ctx.W[(uint8)(((WordPos) - (uint8)7U ) << 1U)]); \
    CRY_SHA384512_ADD(addTmp1, sigm1, &Cry_SHA2Ctx.W[(uint8)(((WordPos) - (uint8)16U) << 1U)]); \
    CRY_SHA384512_ADD(&Cry_SHA2Ctx.W[(uint8)((WordPos) << 1U)], addTmp0, addTmp1);              \
  } while (0)

#if (defined CRY_SHA384512_ROUND_OPERATION)
#error CRY_SHA384512_ROUND_OPERATION is already defined
#endif
/** \brief Performs a SHA-384/SHA-512 round operation */
#define CRY_SHA384512_ROUND_OPERATION(a, b, c, d, e, f, g, h, i) \
  do                                                             \
  {                                                              \
    addTmp0[0U] = (e)[0U];                                       \
    addTmp0[1U] = (e)[1U];                                       \
    Cry_SHA384512_CapitalSigma1(addTmp0);                        \
    sigm[0U] = addTmp0[0U];                                      \
    sigm[1U] = addTmp0[1U];                                      \
                                                                 \
    CRY_SHA384512_CH((e), (f), (g));                             \
                                                                 \
    CRY_SHA384512_ADD(addTmp1, (h), sigm);                       \
    CRY_SHA384512_ADD(addTmp2, addTmp1, ch);                     \
    CRY_SHA384512_ADD(addTmp3,                                   \
                      &Cry_SHA384512K[(uint8)((i) << 1U)],       \
                      &Cry_SHA2Ctx.W[(uint8)((i) << 1U)]);       \
    CRY_SHA384512_ADD(Cry_SHA2Ctx.t1, addTmp2, addTmp3);         \
                                                                 \
    addTmp0[0U] = (a)[0U];                                       \
    addTmp0[1U] = (a)[1U];                                       \
    Cry_SHA384512_CapitalSigma0(addTmp0);                        \
    sigm[0U] = addTmp0[0U];                                      \
    sigm[1U] = addTmp0[1U];                                      \
                                                                 \
    CRY_SHA384512_MAJ((a), (b), (c));                            \
                                                                 \
    CRY_SHA384512_ADD(Cry_SHA2Ctx.t2, maj, sigm);                \
                                                                 \
    addTmp0[0] = (d)[0];                                         \
    addTmp0[1] = (d)[1];                                         \
    CRY_SHA384512_ADD((d), addTmp0, Cry_SHA2Ctx.t1);             \
    CRY_SHA384512_ADD((h), Cry_SHA2Ctx.t1, Cry_SHA2Ctx.t2);      \
  } while (0)

#endif

#if (defined CRY_SHA2_WORDWIDTH)
#error CRY_SHA2_WORDWIDTH is already defined
#endif
/** \brief The width, in bits, of a word */
#define CRY_SHA2_WORDWIDTH            32U

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief  Initialize Processing of hash request
 **
 **  This function initializes the internal states to prepare for a hash calculation
 **
 **/
static FUNC(void, CRY_CODE) Cry_SHA2Init
(
  void
);

#if (CRY_SHA2_WORD_SIZE == 32U)

/** \brief  Compress one block of data to hash
 **
 **  This function compresses one block of data to hash according to the rules
 **  of SHA-2 and updates the internal state accordingly. The macro
 **  CRY_SHACOMPRESSSTART() has to be called before the first call to this
 **  function.
 **
 ** \param[in] Data A pointer to a block of data of size
 ** ::CRY_SHA2_BLOCK_LEN_BYTES bytes which has to be processed
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
static FUNC(boolean, CRY_CODE) Cry_SHA224256Compress
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) Data
);

#endif

#if (CRY_SHA2_WORD_SIZE == 64U)

/** \brief The function (in LaTex notation) $\Sigma^{\{512\}}_0(x)$ from the
 **        description of SHA-384 or SHA-512 in chapter 4.1.2 of the standard FIPS 180-2
 **
 **/
static FUNC(void, CRY_CODE) Cry_SHA384512_CapitalSigma0
(
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) word
);

/** \brief The function (in LaTex notation) $\Sigma^{\{512\}}_1(x)$ from the
 **        description of SHA-384 or SHA-512 in chapter 4.1.2 of the standard FIPS 180-2
 **
 **/
static FUNC(void, CRY_CODE) Cry_SHA384512_CapitalSigma1
(
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) word
);

/** \brief The function (in LaTex notation) $\sigma^{\{512\}}_0(x)$ from the
 **        description of SHA-384 or SHA-512 in chapter 4.1.2 of the standard FIPS 180-2
 **
 **/
static FUNC(void, CRY_CODE) Cry_SHA384512_SmallSigma0
(
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) word
);

/** \brief The function (in LaTex notation) $\sigma^{\{512\}}_1(x)$ from the
 **        description of SHA-384 or SHA-512 in chapter 4.1.2 of the standard FIPS 180-2
 **
 **/
static FUNC(void, CRY_CODE) Cry_SHA384512_SmallSigma1
(
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) word
);

/** \brief  Processes one block of data to hash
 **
 **  This function compresses one block of data to hash according to the rules
 **  of SHA-2 and updates the internal state accordingly. The function
 **  Cry_SHACompressStart() has to be called before the first call to this
 **  function.
 **
 ** \param[in] Data A pointer to a block of data of size
 ** ::CRY_SHA2_BLOCK_LEN_BYTES bytes which has to be processed
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
static FUNC(boolean, CRY_CODE) Cry_SHA384512Compress
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) Data
);

#endif

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

#define CRY_START_SEC_CONST_32
#include <MemMap.h>

#if (CRY_SHA2_WORD_SIZE == 32U)

/** \brief Array "K" of SHA-256 or SHA-224 computation
 **
 ** For each computation round i, the SHA-256 or SHA-224 computation uses a constant K_i
 ** in the computation of T_1. This array contains those constants
 **/
static CONST(uint32, CRY_CONST) Cry_SHA224256K[CRY_SHA224256_ROUNDS] =
{
   0x428a2f98UL, 0x71374491UL, 0xb5c0fbcfUL, 0xe9b5dba5UL,
   0x3956c25bUL, 0x59f111f1UL, 0x923f82a4UL, 0xab1c5ed5UL,
   0xd807aa98UL, 0x12835b01UL, 0x243185beUL, 0x550c7dc3UL,
   0x72be5d74UL, 0x80deb1feUL, 0x9bdc06a7UL, 0xc19bf174UL,
   0xe49b69c1UL, 0xefbe4786UL, 0x0fc19dc6UL, 0x240ca1ccUL,
   0x2de92c6fUL, 0x4a7484aaUL, 0x5cb0a9dcUL, 0x76f988daUL,
   0x983e5152UL, 0xa831c66dUL, 0xb00327c8UL, 0xbf597fc7UL,
   0xc6e00bf3UL, 0xd5a79147UL, 0x06ca6351UL, 0x14292967UL,
   0x27b70a85UL, 0x2e1b2138UL, 0x4d2c6dfcUL, 0x53380d13UL,
   0x650a7354UL, 0x766a0abbUL, 0x81c2c92eUL, 0x92722c85UL,
   0xa2bfe8a1UL, 0xa81a664bUL, 0xc24b8b70UL, 0xc76c51a3UL,
   0xd192e819UL, 0xd6990624UL, 0xf40e3585UL, 0x106aa070UL,
   0x19a4c116UL, 0x1e376c08UL, 0x2748774cUL, 0x34b0bcb5UL,
   0x391c0cb3UL, 0x4ed8aa4aUL, 0x5b9cca4fUL, 0x682e6ff3UL,
   0x748f82eeUL, 0x78a5636fUL, 0x84c87814UL, 0x8cc70208UL,
   0x90befffaUL, 0xa4506cebUL, 0xbef9a3f7UL, 0xc67178f2UL
};

#endif

#if (CRY_SHA2_WORD_SIZE == 64U)

/** \brief Array "K" of SHA-384 or SHA-512 computation
 **
 ** For each computation round i, the SHA-384 or SHA-512 computation uses a constant K_i
 ** in the computation of T_1. This array contains those constants
 **/
static CONST(uint32, CRY_CONST) Cry_SHA384512K[CRY_SHA384512_ROUNDS << 1U] =
{
    0xd728ae22UL, 0x428a2f98UL, 0x23ef65cdUL, 0x71374491UL,
    0xec4d3b2fUL, 0xb5c0fbcfUL, 0x8189dbbcUL, 0xe9b5dba5UL,
    0xf348b538UL, 0x3956c25bUL, 0xb605d019UL, 0x59f111f1UL,
    0xaf194f9bUL, 0x923f82a4UL, 0xda6d8118UL, 0xab1c5ed5UL,
    0xa3030242UL, 0xd807aa98UL, 0x45706fbeUL, 0x12835b01UL,
    0x4ee4b28cUL, 0x243185beUL, 0xd5ffb4e2UL, 0x550c7dc3UL,
    0xf27b896fUL, 0x72be5d74UL, 0x3b1696b1UL, 0x80deb1feUL,
    0x25c71235UL, 0x9bdc06a7UL, 0xcf692694UL, 0xc19bf174UL,
    0x9ef14ad2UL, 0xe49b69c1UL, 0x384f25e3UL, 0xefbe4786UL,
    0x8b8cd5b5UL, 0x0fc19dc6UL, 0x77ac9c65UL, 0x240ca1ccUL,
    0x592b0275UL, 0x2de92c6fUL, 0x6ea6e483UL, 0x4a7484aaUL,
    0xbd41fbd4UL, 0x5cb0a9dcUL, 0x831153b5UL, 0x76f988daUL,
    0xee66dfabUL, 0x983e5152UL, 0x2db43210UL, 0xa831c66dUL,
    0x98fb213fUL, 0xb00327c8UL, 0xbeef0ee4UL, 0xbf597fc7UL,
    0x3da88fc2UL, 0xc6e00bf3UL, 0x930aa725UL, 0xd5a79147UL,
    0xe003826fUL, 0x06ca6351UL, 0x0a0e6e70UL, 0x14292967UL,
    0x46d22ffcUL, 0x27b70a85UL, 0x5c26c926UL, 0x2e1b2138UL,
    0x5ac42aedUL, 0x4d2c6dfcUL, 0x9d95b3dfUL, 0x53380d13UL,
    0x8baf63deUL, 0x650a7354UL, 0x3c77b2a8UL, 0x766a0abbUL,
    0x47edaee6UL, 0x81c2c92eUL, 0x1482353bUL, 0x92722c85UL,
    0x4cf10364UL, 0xa2bfe8a1UL, 0xbc423001UL, 0xa81a664bUL,
    0xd0f89791UL, 0xc24b8b70UL, 0x0654be30UL, 0xc76c51a3UL,
    0xd6ef5218UL, 0xd192e819UL, 0x5565a910UL, 0xd6990624UL,
    0x5771202aUL, 0xf40e3585UL, 0x32bbd1b8UL, 0x106aa070UL,
    0xb8d2d0c8UL, 0x19a4c116UL, 0x5141ab53UL, 0x1e376c08UL,
    0xdf8eeb99UL, 0x2748774cUL, 0xe19b48a8UL, 0x34b0bcb5UL,
    0xc5c95a63UL, 0x391c0cb3UL, 0xe3418acbUL, 0x4ed8aa4aUL,
    0x7763e373UL, 0x5b9cca4fUL, 0xd6b2b8a3UL, 0x682e6ff3UL,
    0x5defb2fcUL, 0x748f82eeUL, 0x43172f60UL, 0x78a5636fUL,
    0xa1f0ab72UL, 0x84c87814UL, 0x1a6439ecUL, 0x8cc70208UL,
    0x23631e28UL, 0x90befffaUL, 0xde82bde9UL, 0xa4506cebUL,
    0xb2c67915UL, 0xbef9a3f7UL, 0xe372532bUL, 0xc67178f2UL,
    0xea26619cUL, 0xca273eceUL, 0x21c0c207UL, 0xd186b8c7UL,
    0xcde0eb1eUL, 0xeada7dd6UL, 0xee6ed178UL, 0xf57d4f7fUL,
    0x72176fbaUL, 0x06f067aaUL, 0xa2c898a6UL, 0x0a637dc5UL,
    0xbef90daeUL, 0x113f9804UL, 0x131c471bUL, 0x1b710b35UL,
    0x23047d84UL, 0x28db77f5UL, 0x40c72493UL, 0x32caab7bUL,
    0x15c9bebcUL, 0x3c9ebe0aUL, 0x9c100d4cUL, 0x431d67c4UL,
    0xcb3e42b6UL, 0x4cc5d4beUL, 0xfc657e2aUL, 0x597f299cUL,
    0x3ad6faecUL, 0x5fcb6fabUL, 0x4a475817UL, 0x6c44198cUL
};

#endif

#define CRY_STOP_SEC_CONST_32
#include <MemMap.h>

/*==[Variables with internal linkage]=========================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief SHA2 Ctx
 **
 ** The context variable which is used to store the internal state of the
 ** SHA2 computation. This context is used for SHA-224, SHA-256, SHA-384 and SHA-512.
 **/
static VAR(Cry_SHACtxType, CRY_VAR) Cry_SHA2Ctx;

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO CS_SECURE_CRY_0067,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_SHA2Start
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr
)
{
  Csm_ReturnType RetVal;

  /* !LINKSTO EB_Cry_Immediate_Restart,1 */
#if (CRY_SHA2_IMMEDIATE_RESTART_ENABLED == STD_OFF)
  if(CRY_SHA_S_IDLE == Cry_SHA2Ctx.State)
  {
    Cry_SHA2Ctx.RestartFlag = FALSE;

    Cry_SHA2Ctx.CfgPtr =
      (P2CONST(Cry_SHAConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;

    Cry_SHA2Ctx.State = CRY_SHA_S_INIT;

    RetVal = CSM_E_OK;
  }
  else if((Cry_SHA2Ctx.CfgPtr == cfgPtr) && (Cry_SHA2Ctx.CfgPtr->SupportRestart == TRUE))
  {
    /* !LINKSTO EB_Cry_Restart_SHA2,1 */
    Cry_SHA2Ctx.RestartFlag = TRUE;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }
#else
    Cry_SHA2Ctx.CfgPtr =
        (P2CONST(Cry_SHAConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr;

    Cry_SHA2Ctx.State = CRY_SHA_S_INIT;

    RetVal = CSM_E_OK;
#endif

  return RetVal;
}

/* !LINKSTO CS_SECURE_CRY_0068,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_SHA2Update
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
  uint32                                   dataLength
)
{
  Csm_ReturnType RetVal;

  if(CRY_SHA_S_IDLE == Cry_SHA2Ctx.State)
  {
    RetVal = CSM_E_NOT_OK;
  }
  else if(CRY_SHA_S_INITIALIZED == Cry_SHA2Ctx.State)
  {
    /* Store data into context */
    Cry_SHA2Ctx.Data = dataPtr;
    Cry_SHA2Ctx.DataLength = dataLength;

    /* Set state of the state machine to update */
    Cry_SHA2Ctx.State = CRY_SHA_S_UPDATE;

    Cry_SHA2Ctx.ProcessInputState = CRY_SHA_S_PROCESS;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}

/* !LINKSTO CS_SECURE_CRY_0069,1 */
FUNC(Csm_ReturnType, CRY_CODE) Cry_SHA2Finish
(
  P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA)  resultPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) resultLengthPtr,
  boolean                                 truncationAllowed
)
{
  Csm_ReturnType RetVal;

  if(CRY_SHA_S_IDLE == Cry_SHA2Ctx.State)
  {
    RetVal = CSM_E_NOT_OK;
  }
  else if(CRY_SHA_S_INITIALIZED == Cry_SHA2Ctx.State)
  {
    /* Store data into context */
    Cry_SHA2Ctx.Result = resultPtr;
    Cry_SHA2Ctx.ResultLengthPtr = resultLengthPtr;
    Cry_SHA2Ctx.TruncationAllowed = truncationAllowed;
    /* Set state of the state machine to finish */
    Cry_SHA2Ctx.State = CRY_SHA_S_FINISH;

    Cry_SHA2Ctx.ProcessInputState = CRY_SHA_S_PROCESS;

    RetVal = CSM_E_OK;
  }
  else
  {
    RetVal = CSM_E_BUSY;
  }

  return RetVal;
}

/* !LINKSTO  CS_SECURE_CRY_0070, 1 */
FUNC(void, CRY_CODE) Cry_SHA2MainFunction
(
  void
)
{
#if (CRY_SHA2_WORD_SIZE == 32U)
  Cry_SHAMainFunction(&Cry_SHA2Ctx, &Cry_SHA2Init, &Cry_SHA224256Compress);
#endif
#if (CRY_SHA2_WORD_SIZE == 64U)
  Cry_SHAMainFunction(&Cry_SHA2Ctx, &Cry_SHA2Init, &Cry_SHA384512Compress);
#endif
}

/* !LINKSTO EB_CRY_0015,1 */
/* Deviation MISRAC2012-1 */
FUNC(P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA), CRY_CODE) Cry_SHA2AlgorithmId
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) AlgorithmIdLengthPtr
)
{
  *AlgorithmIdLengthPtr =
      ((P2CONST(Cry_SHAConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr)->AlgorithmIdLength;

  return ((P2CONST(Cry_SHAConfigType, AUTOMATIC, CRY_APPL_DATA))cfgPtr)->AlgorithmId;
}

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Definition of functions with internal linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

static FUNC(void, CRY_CODE) Cry_SHA2Init (void)
{
  switch(Cry_SHA2Ctx.CfgPtr->HashLength)
  {
#if (CRY_SHA2_WORD_SIZE == 32U)
     /* 2. Initialize the internal state of the hash function */
     case CRY_SHA224_HASH_LEN_BYTES:
        Cry_SHA2Ctx.Internalstate[0U] = (uint32) 0xc1059ed8UL;
        Cry_SHA2Ctx.Internalstate[1U] = (uint32) 0x367cd507UL;
        Cry_SHA2Ctx.Internalstate[2U] = (uint32) 0x3070dd17UL;
        Cry_SHA2Ctx.Internalstate[3U] = (uint32) 0xf70e5939UL;
        Cry_SHA2Ctx.Internalstate[4U] = (uint32) 0xffc00b31UL;
        Cry_SHA2Ctx.Internalstate[5U] = (uint32) 0x68581511UL;
        Cry_SHA2Ctx.Internalstate[6U] = (uint32) 0x64f98fa7UL;
        Cry_SHA2Ctx.Internalstate[7U] = (uint32) 0xbefa4fa4UL;
        break;

     case CRY_SHA256_HASH_LEN_BYTES:
        Cry_SHA2Ctx.Internalstate[0U] = (uint32) 0x6a09e667UL;
        Cry_SHA2Ctx.Internalstate[1U] = (uint32) 0xbb67ae85UL;
        Cry_SHA2Ctx.Internalstate[2U] = (uint32) 0x3c6ef372UL;
        Cry_SHA2Ctx.Internalstate[3U] = (uint32) 0xa54ff53aUL;
        Cry_SHA2Ctx.Internalstate[4U] = (uint32) 0x510e527fUL;
        Cry_SHA2Ctx.Internalstate[5U] = (uint32) 0x9b05688cUL;
        Cry_SHA2Ctx.Internalstate[6U] = (uint32) 0x1f83d9abUL;
        Cry_SHA2Ctx.Internalstate[7U] = (uint32) 0x5be0cd19UL;
        break;
#endif

#if (CRY_SHA2_WORD_SIZE == 64U)
     case CRY_SHA384_HASH_LEN_BYTES:
        Cry_SHA2Ctx.Internalstate[0U ] = (uint32) 0xc1059ed8UL;
        Cry_SHA2Ctx.Internalstate[1U ] = (uint32) 0xcbbb9d5dUL;
        Cry_SHA2Ctx.Internalstate[2U ] = (uint32) 0x367cd507UL;
        Cry_SHA2Ctx.Internalstate[3U ] = (uint32) 0x629a292aUL;
        Cry_SHA2Ctx.Internalstate[4U ] = (uint32) 0x3070dd17UL;
        Cry_SHA2Ctx.Internalstate[5U ] = (uint32) 0x9159015aUL;
        Cry_SHA2Ctx.Internalstate[6U ] = (uint32) 0xf70e5939UL;
        Cry_SHA2Ctx.Internalstate[7U ] = (uint32) 0x152fecd8UL;
        Cry_SHA2Ctx.Internalstate[8U ] = (uint32) 0xffc00b31UL;
        Cry_SHA2Ctx.Internalstate[9U ] = (uint32) 0x67332667UL;
        Cry_SHA2Ctx.Internalstate[10U] = (uint32) 0x68581511UL;
        Cry_SHA2Ctx.Internalstate[11U] = (uint32) 0x8eb44a87UL;
        Cry_SHA2Ctx.Internalstate[12U] = (uint32) 0x64f98fa7UL;
        Cry_SHA2Ctx.Internalstate[13U] = (uint32) 0xdb0c2e0dUL;
        Cry_SHA2Ctx.Internalstate[14U] = (uint32) 0xbefa4fa4UL;
        Cry_SHA2Ctx.Internalstate[15U] = (uint32) 0x47b5481dUL;
        break;

     case CRY_SHA512_HASH_LEN_BYTES:
        Cry_SHA2Ctx.Internalstate[0U ] = (uint32) 0xf3bcc908UL;
        Cry_SHA2Ctx.Internalstate[1U ] = (uint32) 0x6a09e667UL;
        Cry_SHA2Ctx.Internalstate[2U ] = (uint32) 0x84caa73bUL;
        Cry_SHA2Ctx.Internalstate[3U ] = (uint32) 0xbb67ae85UL;
        Cry_SHA2Ctx.Internalstate[4U ] = (uint32) 0xfe94f82bUL;
        Cry_SHA2Ctx.Internalstate[5U ] = (uint32) 0x3c6ef372UL;
        Cry_SHA2Ctx.Internalstate[6U ] = (uint32) 0x5f1d36f1UL;
        Cry_SHA2Ctx.Internalstate[7U ] = (uint32) 0xa54ff53aUL;
        Cry_SHA2Ctx.Internalstate[8U ] = (uint32) 0xade682d1UL;
        Cry_SHA2Ctx.Internalstate[9U ] = (uint32) 0x510e527fUL;
        Cry_SHA2Ctx.Internalstate[10U] = (uint32) 0x2b3e6c1fUL;
        Cry_SHA2Ctx.Internalstate[11U] = (uint32) 0x9b05688cUL;
        Cry_SHA2Ctx.Internalstate[12U] = (uint32) 0xfb41bd6bUL;
        Cry_SHA2Ctx.Internalstate[13U] = (uint32) 0x1f83d9abUL;
        Cry_SHA2Ctx.Internalstate[14U] = (uint32) 0x137e2179UL;
        Cry_SHA2Ctx.Internalstate[15U] = (uint32) 0x5be0cd19UL;
        break;
#endif
    /* CHECK: NOPARSE */
    /* Defensive Programming - unreachable code. This default case is required by MISRA-C:2004 */
     default:
        {
          break;
          /* CHECK: PARSE */
        }
  }

}

#if (CRY_SHA2_WORD_SIZE == 32U)

static FUNC(boolean, CRY_CODE) Cry_SHA224256Compress
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
#endif /* #if (CRY_SHAONEANDTWO_VARIANT = CRY_SHAONEANDTWO_INTERRUPTABLE) */

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
  /* If IterationsPerMain is 0, the while loop shall be left only when it's finished */
  while ((finished == FALSE) &&
         ((Cry_SHA2Ctx.CfgPtr->IterationsPerMain == 0U) ||
          (iterationCnt < Cry_SHA2Ctx.CfgPtr->IterationsPerMain))
        )
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */
  {
#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
    iterationCnt++;

    switch (Cry_SHA2Ctx.SHACompressState)
    {
      case CRY_SHA_S_COMPRESS:
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */

        /* set the initial hash value */
        Cry_SHA2Ctx.a = Cry_SHA2Ctx.Internalstate[0U];
        Cry_SHA2Ctx.b = Cry_SHA2Ctx.Internalstate[1U];
        Cry_SHA2Ctx.c = Cry_SHA2Ctx.Internalstate[2U];
        Cry_SHA2Ctx.d = Cry_SHA2Ctx.Internalstate[3U];
        Cry_SHA2Ctx.e = Cry_SHA2Ctx.Internalstate[4U];
        Cry_SHA2Ctx.f = Cry_SHA2Ctx.Internalstate[5U];
        Cry_SHA2Ctx.g = Cry_SHA2Ctx.Internalstate[6U];
        Cry_SHA2Ctx.h = Cry_SHA2Ctx.Internalstate[7U];

        /* clear the index for the next round */
        Cry_SHA2Ctx.i = (uint8)0U;

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
        /* 2. the message Cry_SHA2Ctx.result transformation loop */
        Cry_SHA2Ctx.SHACompressState = CRY_SHA_S_COMPRESS_TRANSFORM;
        break;
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
      case CRY_SHA_S_COMPRESS_TRANSFORM:
#else
        for (Cry_SHA2Ctx.i = 0U; Cry_SHA2Ctx.i < CRY_SHA224256_ROUNDS; Cry_SHA2Ctx.i += 8U)
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */
        {
          /* Prepare the message schedule */
          if (Cry_SHA2Ctx.i < (uint8)(CRY_SHA2_BLOCK_LEN_BYTES / 4U))
          {
            /* precalculate the data index */
            const uint8 dataIdx = Cry_SHA2Ctx.i << (uint8)2U;

            /* copy the first 64 bytes from the user input to the message schedule */
            Cry_SHA2Ctx.W[(uint8)(Cry_SHA2Ctx.i + 0U)] =
               CRY_SHA224256_READ_WORD((uint8)(dataIdx +  0U));
            Cry_SHA2Ctx.W[(uint8)(Cry_SHA2Ctx.i + 1U)] =
               CRY_SHA224256_READ_WORD((uint8)(dataIdx +  4U));
            Cry_SHA2Ctx.W[(uint8)(Cry_SHA2Ctx.i + 2U)] =
               CRY_SHA224256_READ_WORD((uint8)(dataIdx +  8U));
            Cry_SHA2Ctx.W[(uint8)(Cry_SHA2Ctx.i + 3U)] =
               CRY_SHA224256_READ_WORD((uint8)(dataIdx + 12U));
            Cry_SHA2Ctx.W[(uint8)(Cry_SHA2Ctx.i + 4U)] =
               CRY_SHA224256_READ_WORD((uint8)(dataIdx + 16U));
            Cry_SHA2Ctx.W[(uint8)(Cry_SHA2Ctx.i + 5U)] =
               CRY_SHA224256_READ_WORD((uint8)(dataIdx + 20U));
            Cry_SHA2Ctx.W[(uint8)(Cry_SHA2Ctx.i + 6U)] =
               CRY_SHA224256_READ_WORD((uint8)(dataIdx + 24U));
            Cry_SHA2Ctx.W[(uint8)(Cry_SHA2Ctx.i + 7U)] =
               CRY_SHA224256_READ_WORD((uint8)(dataIdx + 28U));
          }
          else
          {
            /* each word is constructed recursively from 4 previous words */
            CRY_SHA224256_CALCULATE_SCHEDULE_WORD(Cry_SHA2Ctx.i + 0U);
            CRY_SHA224256_CALCULATE_SCHEDULE_WORD(Cry_SHA2Ctx.i + 1U);
            CRY_SHA224256_CALCULATE_SCHEDULE_WORD(Cry_SHA2Ctx.i + 2U);
            CRY_SHA224256_CALCULATE_SCHEDULE_WORD(Cry_SHA2Ctx.i + 3U);
            CRY_SHA224256_CALCULATE_SCHEDULE_WORD(Cry_SHA2Ctx.i + 4U);
            CRY_SHA224256_CALCULATE_SCHEDULE_WORD(Cry_SHA2Ctx.i + 5U);
            CRY_SHA224256_CALCULATE_SCHEDULE_WORD(Cry_SHA2Ctx.i + 6U);
            CRY_SHA224256_CALCULATE_SCHEDULE_WORD(Cry_SHA2Ctx.i + 7U);
          }

          /* Perform the round operations */
          CRY_SHA224256_ROUND_OPERATION(Cry_SHA2Ctx.a,
                                        Cry_SHA2Ctx.b,
                                        Cry_SHA2Ctx.c,
                                        Cry_SHA2Ctx.d,
                                        Cry_SHA2Ctx.e,
                                        Cry_SHA2Ctx.f,
                                        Cry_SHA2Ctx.g,
                                        Cry_SHA2Ctx.h,
                                        (Cry_SHA2Ctx.i + 0U));

          CRY_SHA224256_ROUND_OPERATION(Cry_SHA2Ctx.h,
                                        Cry_SHA2Ctx.a,
                                        Cry_SHA2Ctx.b,
                                        Cry_SHA2Ctx.c,
                                        Cry_SHA2Ctx.d,
                                        Cry_SHA2Ctx.e,
                                        Cry_SHA2Ctx.f,
                                        Cry_SHA2Ctx.g,
                                        (Cry_SHA2Ctx.i + 1U));

          CRY_SHA224256_ROUND_OPERATION(Cry_SHA2Ctx.g,
                                        Cry_SHA2Ctx.h,
                                        Cry_SHA2Ctx.a,
                                        Cry_SHA2Ctx.b,
                                        Cry_SHA2Ctx.c,
                                        Cry_SHA2Ctx.d,
                                        Cry_SHA2Ctx.e,
                                        Cry_SHA2Ctx.f,
                                        (Cry_SHA2Ctx.i + 2U));

          CRY_SHA224256_ROUND_OPERATION(Cry_SHA2Ctx.f,
                                        Cry_SHA2Ctx.g,
                                        Cry_SHA2Ctx.h,
                                        Cry_SHA2Ctx.a,
                                        Cry_SHA2Ctx.b,
                                        Cry_SHA2Ctx.c,
                                        Cry_SHA2Ctx.d,
                                        Cry_SHA2Ctx.e,
                                        (Cry_SHA2Ctx.i + 3U));

          CRY_SHA224256_ROUND_OPERATION(Cry_SHA2Ctx.e,
                                        Cry_SHA2Ctx.f,
                                        Cry_SHA2Ctx.g,
                                        Cry_SHA2Ctx.h,
                                        Cry_SHA2Ctx.a,
                                        Cry_SHA2Ctx.b,
                                        Cry_SHA2Ctx.c,
                                        Cry_SHA2Ctx.d,
                                        (Cry_SHA2Ctx.i + 4U));

          CRY_SHA224256_ROUND_OPERATION(Cry_SHA2Ctx.d,
                                        Cry_SHA2Ctx.e,
                                        Cry_SHA2Ctx.f,
                                        Cry_SHA2Ctx.g,
                                        Cry_SHA2Ctx.h,
                                        Cry_SHA2Ctx.a,
                                        Cry_SHA2Ctx.b,
                                        Cry_SHA2Ctx.c,
                                        (Cry_SHA2Ctx.i + 5U));

          CRY_SHA224256_ROUND_OPERATION(Cry_SHA2Ctx.c,
                                        Cry_SHA2Ctx.d,
                                        Cry_SHA2Ctx.e,
                                        Cry_SHA2Ctx.f,
                                        Cry_SHA2Ctx.g,
                                        Cry_SHA2Ctx.h,
                                        Cry_SHA2Ctx.a,
                                        Cry_SHA2Ctx.b,
                                        (Cry_SHA2Ctx.i + 6U));

          CRY_SHA224256_ROUND_OPERATION(Cry_SHA2Ctx.b,
                                        Cry_SHA2Ctx.c,
                                        Cry_SHA2Ctx.d,
                                        Cry_SHA2Ctx.e,
                                        Cry_SHA2Ctx.f,
                                        Cry_SHA2Ctx.g,
                                        Cry_SHA2Ctx.h,
                                        Cry_SHA2Ctx.a,
                                        (Cry_SHA2Ctx.i + 7U));
        }

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
        Cry_SHA2Ctx.i += 8U;

        if (Cry_SHA2Ctx.i == (uint8) CRY_SHA224256_ROUNDS)
        {
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */
          /* 3. copy internal state back to Ctx */
          Cry_SHA2Ctx.Internalstate[0U] += Cry_SHA2Ctx.a;
          Cry_SHA2Ctx.Internalstate[1U] += Cry_SHA2Ctx.b;
          Cry_SHA2Ctx.Internalstate[2U] += Cry_SHA2Ctx.c;
          Cry_SHA2Ctx.Internalstate[3U] += Cry_SHA2Ctx.d;
          Cry_SHA2Ctx.Internalstate[4U] += Cry_SHA2Ctx.e;
          Cry_SHA2Ctx.Internalstate[5U] += Cry_SHA2Ctx.f;
          Cry_SHA2Ctx.Internalstate[6U] += Cry_SHA2Ctx.g;
          Cry_SHA2Ctx.Internalstate[7U] += Cry_SHA2Ctx.h;

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

#endif

#if (CRY_SHA2_WORD_SIZE == 64U)

static FUNC(void, CRY_CODE) Cry_SHA384512_CapitalSigma0
(
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) word
)
{
  uint32 w[2U], rot1[2U], rot2[2U], rot3[2U];
  w[0U] = word[0U];
  w[1U] = word[1U];

  CRY_SHA384512_ROTR(word, 28U);
  rot1[0U] = word[0U];
  rot1[1U] = word[1U];

  word[0U] = w[0U];
  word[1U] = w[1U];
  CRY_SHA384512_ROTR(word, 34U);
  rot2[0U] = word[0U];
  rot2[1U] = word[1U];

  word[0U] = w[0U];
  word[1U] = w[1U];
  CRY_SHA384512_ROTR(word, 39U);
  rot3[0U] = word[0U];
  rot3[1U] = word[1U];

  word[0U] = rot1[0U] ^ rot2[0U] ^ rot3[0U];
  word[1U] = rot1[1U] ^ rot2[1U] ^ rot3[1U];
}

static FUNC(void, CRY_CODE) Cry_SHA384512_CapitalSigma1
(
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) word
)
{
  uint32 w[2U], rot1[2U], rot2[2U], rot3[2U];
  w[0U] = word[0U];
  w[1U] = word[1U];

  CRY_SHA384512_ROTR(word, 14U);
  rot1[0U] = word[0U];
  rot1[1U] = word[1U];

  word[0U] = w[0U];
  word[1U] = w[1U];
  CRY_SHA384512_ROTR(word, 18U);
  rot2[0U] = word[0U];
  rot2[1U] = word[1U];

  word[0U] = w[0U];
  word[1U] = w[1U];
  CRY_SHA384512_ROTR(word, 41U);
  rot3[0U] = word[0U];
  rot3[1U] = word[1U];

  word[0U] = rot1[0U] ^ rot2[0U] ^ rot3[0U];
  word[1U] = rot1[1U] ^ rot2[1U] ^ rot3[1U];
}

static FUNC(void, CRY_CODE) Cry_SHA384512_SmallSigma0
(
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) word
)
{
  uint32 w[2U], rot1[2U], rot2[2U], shr[2U];
  w[0U] = word[0U];
  w[1U] = word[1U];

  CRY_SHA384512_ROTR(word, 1U);
  rot1[0U] = word[0U];
  rot1[1U] = word[1U];

  word[0U] = w[0U];
  word[1U] = w[1U];
  CRY_SHA384512_ROTR(word, 8U);
  rot2[0U] = word[0U];
  rot2[1U] = word[1U];

  word[0U] = w[0U];
  word[1U] = w[1U];
  CRY_SHA384512_SHR(word, 7U);
  shr[0U] = word[0U];
  shr[1U] = word[1U];

  word[0U] = rot1[0U] ^ rot2[0U] ^ shr[0U];
  word[1U] = rot1[1U] ^ rot2[1U] ^ shr[1U];
}

static FUNC(void, CRY_CODE) Cry_SHA384512_SmallSigma1
(
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) word
)
{
  uint32 w[2U], rot1[2U], rot2[2U], shr[2U];
  w[0U] = word[0U];
  w[1U] = word[1U];

  CRY_SHA384512_ROTR(word, 19U);
  rot1[0U] = word[0U];
  rot1[1U] = word[1U];

  word[0U] = w[0U];
  word[1U] = w[1U];
  CRY_SHA384512_ROTR(word, 61U);
  rot2[0U] = word[0U];
  rot2[1U] = word[1U];

  word[0U] = w[0U];
  word[1U] = w[1U];
  CRY_SHA384512_SHR(word, 6U);
  shr[0U] = word[0U];
  shr[1U] = word[1U];

  word[0U] = rot1[0U] ^ rot2[0U] ^ shr[0U];
  word[1U] = rot1[1U] ^ rot2[1U] ^ shr[1U];
}

static FUNC(boolean, CRY_CODE) Cry_SHA384512Compress
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
         ((Cry_SHA2Ctx.CfgPtr->IterationsPerMain == 0U) ||
          (iterationCnt < Cry_SHA2Ctx.CfgPtr->IterationsPerMain))
        )
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */
  {
#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
    iterationCnt++;

    switch (Cry_SHA2Ctx.SHACompressState)
    {
      case CRY_SHA_S_COMPRESS:
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */

        /* set the initial hash value */
        Cry_SHA2Ctx.a[0U] = Cry_SHA2Ctx.Internalstate[ 0U];
        Cry_SHA2Ctx.a[1U] = Cry_SHA2Ctx.Internalstate[ 1U];
        Cry_SHA2Ctx.b[0U] = Cry_SHA2Ctx.Internalstate[ 2U];
        Cry_SHA2Ctx.b[1U] = Cry_SHA2Ctx.Internalstate[ 3U];
        Cry_SHA2Ctx.c[0U] = Cry_SHA2Ctx.Internalstate[ 4U];
        Cry_SHA2Ctx.c[1U] = Cry_SHA2Ctx.Internalstate[ 5U];
        Cry_SHA2Ctx.d[0U] = Cry_SHA2Ctx.Internalstate[ 6U];
        Cry_SHA2Ctx.d[1U] = Cry_SHA2Ctx.Internalstate[ 7U];
        Cry_SHA2Ctx.e[0U] = Cry_SHA2Ctx.Internalstate[ 8U];
        Cry_SHA2Ctx.e[1U] = Cry_SHA2Ctx.Internalstate[ 9U];
        Cry_SHA2Ctx.f[0U] = Cry_SHA2Ctx.Internalstate[10U];
        Cry_SHA2Ctx.f[1U] = Cry_SHA2Ctx.Internalstate[11U];
        Cry_SHA2Ctx.g[0U] = Cry_SHA2Ctx.Internalstate[12U];
        Cry_SHA2Ctx.g[1U] = Cry_SHA2Ctx.Internalstate[13U];
        Cry_SHA2Ctx.h[0U] = Cry_SHA2Ctx.Internalstate[14U];
        Cry_SHA2Ctx.h[1U] = Cry_SHA2Ctx.Internalstate[15U];

        /* clear the index for the next round */
        Cry_SHA2Ctx.i = (uint8)0U;

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
        /* 2. the message Cry_SHA2Ctx.result transformation loop */
        Cry_SHA2Ctx.SHACompressState = CRY_SHA_S_COMPRESS_TRANSFORM;
        break;
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
      case CRY_SHA_S_COMPRESS_TRANSFORM:
#else
        for (Cry_SHA2Ctx.i = 0U; Cry_SHA2Ctx.i < CRY_SHA384512_ROUNDS; Cry_SHA2Ctx.i += 8U)
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */
        {
          uint32    sigm[2U];
          uint32      ch[2U];
          uint32     maj[2U];
          uint32 addTmp0[2U];
          uint32 addTmp1[2U];
          uint32 addTmp2[2U];
          uint32 addTmp3[2U];
          /* precalculate the message schedule word index */
          const uint8 wordIdx = Cry_SHA2Ctx.i << (uint8)1U;

          /* Prepare the message schedule */
          if (Cry_SHA2Ctx.i < (uint8)16U)
          {
            const uint8 dataIdx = Cry_SHA2Ctx.i << (uint8)3U;

            /* copy the first 128 bytes from the user input to the message schedule */
            Cry_SHA2Ctx.W[wordIdx +  0U] =
              CRY_SHA384512_READ_LOWER_WORD((uint8)(dataIdx + 0U));
            Cry_SHA2Ctx.W[wordIdx +  1U] =
              CRY_SHA384512_READ_UPPER_WORD((uint8)(dataIdx + 0U));

            Cry_SHA2Ctx.W[wordIdx +  2U] =
              CRY_SHA384512_READ_LOWER_WORD((uint8)(dataIdx + 8U));
            Cry_SHA2Ctx.W[wordIdx +  3U] =
              CRY_SHA384512_READ_UPPER_WORD((uint8)(dataIdx + 8U));

            Cry_SHA2Ctx.W[wordIdx +  4U] =
              CRY_SHA384512_READ_LOWER_WORD((uint8)(dataIdx + 16U));
            Cry_SHA2Ctx.W[wordIdx +  5U] =
              CRY_SHA384512_READ_UPPER_WORD((uint8)(dataIdx + 16U));

            Cry_SHA2Ctx.W[wordIdx +  6U] =
              CRY_SHA384512_READ_LOWER_WORD((uint8)(dataIdx + 24U));
            Cry_SHA2Ctx.W[wordIdx +  7U] =
              CRY_SHA384512_READ_UPPER_WORD((uint8)(dataIdx + 24U));

            Cry_SHA2Ctx.W[wordIdx +  8U] =
              CRY_SHA384512_READ_LOWER_WORD((uint8)(dataIdx + 32U));
            Cry_SHA2Ctx.W[wordIdx +  9U] =
              CRY_SHA384512_READ_UPPER_WORD((uint8)(dataIdx + 32U));

            Cry_SHA2Ctx.W[wordIdx + 10U] =
              CRY_SHA384512_READ_LOWER_WORD((uint8)(dataIdx + 40U));
            Cry_SHA2Ctx.W[wordIdx + 11U] =
              CRY_SHA384512_READ_UPPER_WORD((uint8)(dataIdx + 40U));

            Cry_SHA2Ctx.W[wordIdx + 12U] =
              CRY_SHA384512_READ_LOWER_WORD((uint8)(dataIdx + 48U));
            Cry_SHA2Ctx.W[wordIdx + 13U] =
              CRY_SHA384512_READ_UPPER_WORD((uint8)(dataIdx + 48U));

            Cry_SHA2Ctx.W[wordIdx + 14U] =
              CRY_SHA384512_READ_LOWER_WORD((uint8)(dataIdx + 56U));
            Cry_SHA2Ctx.W[wordIdx + 15U] =
              CRY_SHA384512_READ_UPPER_WORD((uint8)(dataIdx + 56U));
          }
          else
          {
            /* each word is constructed recursively from 4 previous words */
            uint32 sigm0[2U];
            uint32 sigm1[2U];

            /* The data is saved in W in machine endianness;
             * Each word is constructed recursively  from 4 previous words */
            CRY_SHA384512_CALCULATE_SCHEDULE_WORD(Cry_SHA2Ctx.i + 0U);
            CRY_SHA384512_CALCULATE_SCHEDULE_WORD(Cry_SHA2Ctx.i + 1U);
            CRY_SHA384512_CALCULATE_SCHEDULE_WORD(Cry_SHA2Ctx.i + 2U);
            CRY_SHA384512_CALCULATE_SCHEDULE_WORD(Cry_SHA2Ctx.i + 3U);
            CRY_SHA384512_CALCULATE_SCHEDULE_WORD(Cry_SHA2Ctx.i + 4U);
            CRY_SHA384512_CALCULATE_SCHEDULE_WORD(Cry_SHA2Ctx.i + 5U);
            CRY_SHA384512_CALCULATE_SCHEDULE_WORD(Cry_SHA2Ctx.i + 6U);
            CRY_SHA384512_CALCULATE_SCHEDULE_WORD(Cry_SHA2Ctx.i + 7U);
          }

          /* Perform the round operation */
          CRY_SHA384512_ROUND_OPERATION(Cry_SHA2Ctx.a,
                                        Cry_SHA2Ctx.b,
                                        Cry_SHA2Ctx.c,
                                        Cry_SHA2Ctx.d,
                                        Cry_SHA2Ctx.e,
                                        Cry_SHA2Ctx.f,
                                        Cry_SHA2Ctx.g,
                                        Cry_SHA2Ctx.h,
                                        (Cry_SHA2Ctx.i +  0U));

          CRY_SHA384512_ROUND_OPERATION(Cry_SHA2Ctx.h,
                                        Cry_SHA2Ctx.a,
                                        Cry_SHA2Ctx.b,
                                        Cry_SHA2Ctx.c,
                                        Cry_SHA2Ctx.d,
                                        Cry_SHA2Ctx.e,
                                        Cry_SHA2Ctx.f,
                                        Cry_SHA2Ctx.g,
                                        (Cry_SHA2Ctx.i +  1U));

          CRY_SHA384512_ROUND_OPERATION(Cry_SHA2Ctx.g,
                                        Cry_SHA2Ctx.h,
                                        Cry_SHA2Ctx.a,
                                        Cry_SHA2Ctx.b,
                                        Cry_SHA2Ctx.c,
                                        Cry_SHA2Ctx.d,
                                        Cry_SHA2Ctx.e,
                                        Cry_SHA2Ctx.f,
                                        (Cry_SHA2Ctx.i +  2U));

          CRY_SHA384512_ROUND_OPERATION(Cry_SHA2Ctx.f,
                                        Cry_SHA2Ctx.g,
                                        Cry_SHA2Ctx.h,
                                        Cry_SHA2Ctx.a,
                                        Cry_SHA2Ctx.b,
                                        Cry_SHA2Ctx.c,
                                        Cry_SHA2Ctx.d,
                                        Cry_SHA2Ctx.e,
                                        (Cry_SHA2Ctx.i +  3U));

          CRY_SHA384512_ROUND_OPERATION(Cry_SHA2Ctx.e,
                                        Cry_SHA2Ctx.f,
                                        Cry_SHA2Ctx.g,
                                        Cry_SHA2Ctx.h,
                                        Cry_SHA2Ctx.a,
                                        Cry_SHA2Ctx.b,
                                        Cry_SHA2Ctx.c,
                                        Cry_SHA2Ctx.d,
                                        (Cry_SHA2Ctx.i +  4U));

          CRY_SHA384512_ROUND_OPERATION(Cry_SHA2Ctx.d,
                                        Cry_SHA2Ctx.e,
                                        Cry_SHA2Ctx.f,
                                        Cry_SHA2Ctx.g,
                                        Cry_SHA2Ctx.h,
                                        Cry_SHA2Ctx.a,
                                        Cry_SHA2Ctx.b,
                                        Cry_SHA2Ctx.c,
                                        (Cry_SHA2Ctx.i + 5U));

          CRY_SHA384512_ROUND_OPERATION(Cry_SHA2Ctx.c,
                                        Cry_SHA2Ctx.d,
                                        Cry_SHA2Ctx.e,
                                        Cry_SHA2Ctx.f,
                                        Cry_SHA2Ctx.g,
                                        Cry_SHA2Ctx.h,
                                        Cry_SHA2Ctx.a,
                                        Cry_SHA2Ctx.b,
                                        (Cry_SHA2Ctx.i + 6U));

          CRY_SHA384512_ROUND_OPERATION(Cry_SHA2Ctx.b,
                                        Cry_SHA2Ctx.c,
                                        Cry_SHA2Ctx.d,
                                        Cry_SHA2Ctx.e,
                                        Cry_SHA2Ctx.f,
                                        Cry_SHA2Ctx.g,
                                        Cry_SHA2Ctx.h,
                                        Cry_SHA2Ctx.a,
                                        (Cry_SHA2Ctx.i + 7U));
        }

#if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE)
        Cry_SHA2Ctx.i += 8U;

        if (Cry_SHA2Ctx.i == (uint8) CRY_SHA384512_ROUNDS)
        {
#endif /* #if (CRY_SHAONEANDTWO_VARIANT == CRY_SHAONEANDTWO_INTERRUPTABLE) */
          /* 3. copy internal state back to Ctx */
          CRY_SHA384512_ADD(&Cry_SHA2Ctx.Internalstate[ 0U],
                            &Cry_SHA2Ctx.Internalstate[ 0U],
                            Cry_SHA2Ctx.a);
          CRY_SHA384512_ADD(&Cry_SHA2Ctx.Internalstate[ 2U],
                            &Cry_SHA2Ctx.Internalstate[ 2U],
                            Cry_SHA2Ctx.b);
          CRY_SHA384512_ADD(&Cry_SHA2Ctx.Internalstate[ 4U],
                            &Cry_SHA2Ctx.Internalstate[ 4U],
                            Cry_SHA2Ctx.c);
          CRY_SHA384512_ADD(&Cry_SHA2Ctx.Internalstate[ 6U],
                            &Cry_SHA2Ctx.Internalstate[ 6U],
                            Cry_SHA2Ctx.d);
          CRY_SHA384512_ADD(&Cry_SHA2Ctx.Internalstate[ 8U],
                            &Cry_SHA2Ctx.Internalstate[ 8U],
                            Cry_SHA2Ctx.e);
          CRY_SHA384512_ADD(&Cry_SHA2Ctx.Internalstate[10U],
                            &Cry_SHA2Ctx.Internalstate[10U],
                            Cry_SHA2Ctx.f);
          CRY_SHA384512_ADD(&Cry_SHA2Ctx.Internalstate[12U],
                            &Cry_SHA2Ctx.Internalstate[12U],
                            Cry_SHA2Ctx.g);
          CRY_SHA384512_ADD(&Cry_SHA2Ctx.Internalstate[14U],
                            &Cry_SHA2Ctx.Internalstate[14U],
                            Cry_SHA2Ctx.h);

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

#endif

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#else /* #if (CRY_SHA2_ENABLED == STD_ON) */

typedef uint8 Cry_SHA2_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_SHA2_ENABLED == STD_ON) #else */
