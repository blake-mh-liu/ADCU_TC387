/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CPL_0801_102, 1 */

/*==================[misra deviations]============================================================*/
/* MISRA-C:2012 Deviation List:
 *
 * MISRAC2012-1) Deviated Rule: 11.3 (required)
 *   "A cast shall not be performed between a pointer to object type and a
 *    pointer to a different object type."
 *
 *    Reason:
 *    This type cast is specified in AUTOSAR_SWS_CryptoAbstractionLibrary.pdf.
 *    It is ensured by a requirement, that this type cast does not violate
 *    memory bounds.
 *
 *  MISRAC2012-2) Deviated Rule: 20.7 (required)
 *   "Expressions resulting from the expansion of macro parameters shall be
 *    enclosed in parentheses."
 *
 *    Reason:
 *    The AUTOSAR compiler abstraction requires these definitions in this way
 *    and the arguments cannot be enclosed in parentheses due to C syntax.
 */

/*==================[includes]====================================================================*/
#include <TSMem.h>

/* !LINKSTO EB_CPL_0801_104, 1 */
#include <Cal_Types.h>
#include <Cal_Decompress.h>

#include <Cpl_LZMADecompress_Cfg.h>
#include <Cpl_LZMADecompress.h>

#if (CPL_LZMADECOMPRESS_ENABLED == STD_ON)

/*==================[macros]======================================================================*/
/** \brief The algorithm was initialized. */
#if (defined CPL_LZMA_STAT_INITIALIZED)
#error CPL_LZMA_STAT_INITIALIZED is already defined
#endif

#define CPL_LZMA_STAT_INITIALIZED   0U

/** \brief Waiting for DecompressEnd call. */
#if (defined CPL_LZMA_STAT_IDLE)
#error CPL_LZMA_STAT_IDLE is already defined
#endif

#define CPL_LZMA_STAT_IDLE          1U

/** \brief Decompression finished with success. */
#if (defined CPL_DEC_OK)
#error CPL_DEC_OK is already defined
#endif

#define CPL_DEC_OK                  0U

/** \brief Decompression failed. */
#if (defined CPL_DEC_NOT_OK)
#error CPL_DEC_NOT_OK is already defined
#endif

#define CPL_DEC_NOT_OK              1U

/** \brief State not yet known for the dummy decoder. */
#if (defined CPL_DUMMY_UNKNOWN)
#error CPL_DUMMY_UNKNOWN is already defined
#endif

#define CPL_DUMMY_UNKNOWN           0U

/** \brief No data for decoding the type of packet. */
#if (defined CPL_DUMMY_ERROR)
#error CPL_DUMMY_ERROR is already defined
#endif

#define CPL_DUMMY_ERROR             1U

/** \brief Packet is of type LIT. */
#if (defined CPL_DUMMY_LIT)
#error CPL_DUMMY_LIT is already defined
#endif

#define CPL_DUMMY_LIT               2U

/** \brief Packet is of type MATCH. */
#if (defined CPL_DUMMY_MATCH)
#error CPL_DUMMY_MATCH is already defined
#endif

#define CPL_DUMMY_MATCH             3U

/** \brief Packet is of one of the following types: REP, SHORTREP or LONGREP[*]. */
#if (defined CPL_DUMMY_REP)
#error CPL_DUMMY_REP is already defined
#endif

#define CPL_DUMMY_REP               4U

/** \brief Unknown status. */
#if (defined CPL_LZMA_STATUS_NOT_SPECIFIED)
#error CPL_LZMA_STATUS_NOT_SPECIFIED is already defined
#endif

#if (defined CPL_LZMA_STATUS_NOT_SPECIFIED)
#error CPL_LZMA_STATUS_NOT_SPECIFIED is already defined
#endif

#define CPL_LZMA_STATUS_NOT_SPECIFIED       0U

/** \brief You must provide more input bytes. */
#if (defined CPL_LZMA_STATUS_NEEDS_MORE_INPUT)
#error CPL_LZMA_STATUS_NEEDS_MORE_INPUT is already defined
#endif

#define CPL_LZMA_STATUS_NEEDS_MORE_INPUT    1U

/** \brief The length, in bytes, of a LZMA header. */
#if (defined CPL_HEADER_SIZE)
#error CPL_HEADER_SIZE is already defined
#endif

#define CPL_HEADER_SIZE             13U

/** \brief Number of required input bytes for worst case. */
#if (defined CPL_REQUIRED_INPUT_MAX)
#error CPL_REQUIRED_INPUT_MAX is already defined
#endif

#define CPL_REQUIRED_INPUT_MAX      20U

/** \brief Total number of LZMA states. */
#if (defined CPL_NUM_STATES)
#error CPL_NUM_STATES is already defined
#endif

#define CPL_NUM_STATES              12U

/** \brief The literal coder is divided in 3 ranges:
 *          - 0x001-0x0FF: Literal without match byte
 *          - 0x101-0x1FF: Literal with match byte; match bit is 0
 *          - 0x201-0x2FF: Literal with match byte; match bit is 1
 *
 *         The match byte is used in case the previous LZMA symbol
 *         was anything else than a literal.
 */
#if (defined CPL_LIT_DECODER_SIZE)
#error CPL_LIT_DECODER_SIZE is already defined
#endif

#define CPL_LIT_DECODER_SIZE        0x300U

/** \brief Maximum value of a literal. */
#if (defined CPL_LIT_MAX_VAL)
#error CPL_LIT_MAX_VAL is already defined
#endif

#define CPL_LIT_MAX_VAL             0x100U

/** \brief How large is the range that the will be split in 2
 *         based on the probabilities of 0 and 1 (range = (1 << CPL_RD_NUM_MODEL_BITS)).
 */
#if (defined CPL_RD_NUM_MODEL_BITS)
#error CPL_RD_NUM_MODEL_BITS is already defined
#endif

#define CPL_RD_NUM_MODEL_BITS       11U

/** \brief Used to scale down the probability. */
#if (defined CPL_RD_NUM_MOVE_BITS)
#error CPL_RD_NUM_MOVE_BITS is already defined
#endif

#define CPL_RD_NUM_MOVE_BITS        5U

/** \brief The length, in bytes, of the Range decoder code. */
#if (defined CPL_RD_CODE_SIZE)
#error CPL_RD_CODE_SIZE is already defined
#endif

#define CPL_RD_CODE_SIZE            4U

/** \brief The maximum number of bits used to code the type of packet. */
#if (defined CPL_MAX_POS_BITS)
#error CPL_MAX_POS_BITS is already defined
#endif

#define CPL_MAX_POS_BITS            4U

/** \brief Length information is coded on 3 bits for the Low Coder. */
#if (defined CPL_LOWCODER_LEN)
#error CPL_LOWCODER_LEN is already defined
#endif

#define CPL_LOWCODER_LEN            3U

/** \brief Length information is coded on 3 bits for the Middle Coder. */
#if (defined CPL_MIDCODER_LEN)
#error CPL_MIDCODER_LEN is already defined
#endif

#define CPL_MIDCODER_LEN            3U

/** \brief Length information is coded on 3 bits for the High Coder. */
#if (defined CPL_HIGHCODER_LEN)
#error CPL_HIGHCODER_LEN is already defined
#endif

#define CPL_HIGHCODER_LEN           8U

/** \brief LZMA encodes match distances by storing the highest two bits using
 *  a six-bit value [0, 63], and then the missing lower bits. */
#if (defined CPL_DIST_SLOT)
#error CPL_DIST_SLOT is already defined
#endif

#define CPL_DIST_SLOT               6U

/** \brief Match distances up to 127 are fully encoded using probabilities. Since
 *         the highest two bits (distance slot) are always encoded using six bits,
 *         the distances 0 - 3 don't need any additional bits to encode, since the
 *         distance slot itself is the same as the actual distance.
 *         CPL_DIST_MODEL_START indicates the first distance slot
 *         where at least one additional bit is needed.
 */
#if (defined CPL_DIST_MODEL_START)
#error CPL_DIST_MODEL_START is already defined
#endif

#define CPL_DIST_MODEL_START        4U

/** \brief Match distances > 127 are encoded in three pieces:
 *           - distance slot: the highest two bits
 *           - direct bits: 2 - 26 bits after the highest two bits
 *           - alignment bits: four lowest bits
 *
 *         Direct bits don't use any probabilities.
 */
#if (defined CPL_DIST_MODEL_END)
#error CPL_DIST_MODEL_END is already defined
#endif

#define CPL_DIST_MODEL_END          14U

/** \brief Distance slots that indicate a distance <= 127. */
#if (defined CPL_LZMA_FULL_DIST)
#error CPL_LZMA_FULL_DIST is already defined
#endif

#define CPL_LZMA_FULL_DIST          128U

/** \brief For match distances > 127 only the highest two bits and the
 *         lowest four bits (alignment) is encoded using probabilities.
 */
#if (defined CPL_DIST_ALIGN_BITS)
#error CPL_DIST_ALIGN_BITS is already defined
#endif

#define CPL_DIST_ALIGN_BITS         4U

/** \brief The minimum match length should be 2. */
#if (defined CPL_DIST_MATCH_MIN_LEN)
#error CPL_DIST_MATCH_MIN_LEN is already defined
#endif

#define CPL_DIST_MATCH_MIN_LEN      2U

/** \brief There is a 50% probability for 0 or 1 at the start of decoding.
 *  In the case of this model (2 ^ 11) / 2.
 */
#if (defined CPL_PROB_INIT_VAL)
#error CPL_PROB_INIT_VAL is already defined
#endif

#define CPL_PROB_INIT_VAL           1024U

/** \brief The Range must always be greater than CPL_RD_TOPVALUE(2^24). */
#if (defined CPL_RD_TOPVALUE)
#error CPL_RD_TOPVALUE is already defined
#endif

#define CPL_RD_TOPVALUE             16777216U

/** \brief Get the value that can be represented on val bits. */
#if (defined CPL_PSIZE)
#error CPL_PSIZE is already defined
#endif

#define CPL_PSIZE(val)              ((uint16)((uint16)1U << (val)))

/** \brief When decoding has been properly finished the code must always be zero
 *         unless the input stream is corrupt. So checking this can catch some corrupt
 *         blocks especially as we don't have any other integrity check.
 */
#if (defined CPL_RD_VALIDEND)
#error CPL_RD_VALIDEND is already defined
#endif

#define CPL_RD_VALIDEND(rangeDecoder)   ((rangeDecoder).Code == 0U)

/** \brief Number of symbols for the Low Coder. */
#if (defined CPL_LOWCODER_NUM_SYMBOLS)
#error CPL_LOWCODER_NUM_SYMBOLS is already defined
#endif

#define CPL_LOWCODER_NUM_SYMBOLS    CPL_PSIZE(3U)

/** \brief Number of symbols for the Middle Coder. */
#if (defined CPL_MIDCODER_NUM_SYMBOLS)
#error CPL_MIDCODER_NUM_SYMBOLS is already defined
#endif

#define CPL_MIDCODER_NUM_SYMBOLS    CPL_PSIZE(3U)

/** \brief Number of symbols for the High Coder. */
#if (defined CPL_HIGHCODER_NUM_SYMBOLS)
#error CPL_HIGHCODER_NUM_SYMBOLS is already defined
#endif

#define CPL_HIGHCODER_NUM_SYMBOLS   CPL_PSIZE(8U)

/** \brief Initialize the probability table with 50% of the range.
 *         In the model of LZMA an 11 bit probability is used; so a 2^10
 *         value represents the 50% of the range.
 */
#if (defined CPL_LZMA_INIT_PROBS)
#error CPL_LZMA_INIT_PROBS is already defined
#endif

#define CPL_LZMA_INIT_PROBS(prob, length)                                                          \
{                                                                                                  \
  uint16 indx = 0U;                                                                                \
                                                                                                   \
  for (indx = 0U; indx < (length); indx++)                                                         \
  {                                                                                                \
    (prob)[indx] = CPL_PROB_INIT_VAL;                                                              \
  }                                                                                                \
}

/** \brief Move the position in the ring buffer dictionary
 *         from dictPos with len positions.
 */
#if (defined CPL_LZMA_DICT_MOVE_POS)
#error CPL_LZMA_DICT_MOVE_POS is already defined
#endif

#define CPL_LZMA_DICT_MOVE_POS(dictPos, len)  (((dictPos) + (len)) % argCtx->cfgPtr->dictSize)

/** \brief Update state machine when we receive an LIT package
 */
#if (defined CPL_LZMA_UPDATE_LIT_STATE)
#error CPL_LZMA_UPDATE_LIT_STATE is already defined
#endif

#define CPL_LZMA_UPDATE_LIT_STATE   do                                                             \
                                    {                                                              \
                                      if (argCtx->decodeState < 4U)                                \
                                      {                                                            \
                                        argCtx->decodeState = 0U;                                  \
                                      }                                                            \
                                      else if (argCtx->decodeState < 10U)                          \
                                      {                                                            \
                                        argCtx->decodeState -= 3U;                                 \
                                      }                                                            \
                                      else                                                         \
                                      {                                                            \
                                        argCtx->decodeState -= 6U;                                 \
                                      }                                                            \
                                    }                                                              \
                                    while(0U)

/** \brief Update state machine when we receive an REP package
 */
#if (defined CPL_LZMA_UPDATE_REP_STATE)
#error CPL_LZMA_UPDATE_REP_STATE is already defined
#endif

#define CPL_LZMA_UPDATE_REP_STATE (argCtx->decodeState < 7U) ?                                     \
                                  (argCtx->decodeState = 8U) : (argCtx->decodeState = 11U)

/** \brief Update state machine when we receive an MATCH package
 */
#if (defined CPL_LZMA_UPDATE_MATCH_STATE)
#error CPL_LZMA_UPDATE_MATCH_STATE is already defined
#endif

#define CPL_LZMA_UPDATE_MATCH_STATE (argCtx->decodeState < 7U) ?                                   \
                                    (argCtx->decodeState = 7U) : (argCtx->decodeState = 10U)

/** \brief Update state machine when we receive an SREP package
 */
#if (defined CPL_LZMA_UPDATE_SREP_STATE)
#error CPL_LZMA_UPDATE_SREP_STATE is already defined
#endif

#define CPL_LZMA_UPDATE_SREP_STATE (argCtx->decodeState < 7U) ?                                    \
                                   (argCtx->decodeState = 9U) : (argCtx->decodeState = 11U)

/** \brief Get how much data was written in the dictionary
 *         since the last decompress.
 */
#if (defined CPL_LZMA_DICT_GET_SIZE_NEW_DATA)
#error CPL_LZMA_DICT_GET_SIZE_NEW_DATA is already defined
#endif

#define CPL_LZMA_DICT_GET_SIZE_NEW_DATA(size)   do                                                 \
{                                                                                                  \
  if (argCtx->dictionary.posBeforeDec <= argCtx->dictionary.pos)                                   \
  {                                                                                                \
    /* If the new dictionary symbols didn't pass the dictionary end. */                            \
    (size) = (uint16)(argCtx->dictionary.pos - argCtx->dictionary.posBeforeDec);                   \
  }                                                                                                \
  else                                                                                             \
  {                                                                                                \
    /* If the new dictionary symbols are both at the end and beginning of the dictionary. */       \
    (size) = (uint16)((argCtx->cfgPtr->dictSize - argCtx->dictionary.posBeforeDec) +               \
                      argCtx->dictionary.pos);                                                     \
  }                                                                                                \
}                                                                                                  \
while(0U)

/** \brief Get a byte from the dict at dist distance from the pos.
 */
#if (defined CPL_LZMA_DICT_GET_BYTE)
#error CPL_LZMA_DICT_GET_BYTE is already defined
#endif

#define CPL_LZMA_DICT_GET_BYTE(dict, pos, dist)                                                    \
(dict)[((dist) <= (pos)) ? ((pos) - (dist)) : (((pos) + argCtx->cfgPtr->dictSize) - (dist))]

/** \brief Add a byte to the dictionary sliding window
 *         and increment the position and processedPos.
 */
#if (defined CPL_LZMA_DICT_PUT_BYTE)
#error CPL_LZMA_DICT_PUT_BYTE is already defined
#endif

#define CPL_LZMA_DICT_PUT_BYTE(byte) do                                                            \
{                                                                                                  \
  argCtx->dictionary.dict[argCtx->dictionary.pos] = (byte);                                        \
  argCtx->dictionary.pos = (argCtx->dictionary.pos + 1U) % (argCtx->cfgPtr->dictSize);             \
  ++argCtx->processedPos;                                                                          \
}                                                                                                  \
while(0U)

/** \brief Normalize the data for Range Decoder
 *         Read a new byte in the Code and keep it above CPL_RD_TOPVALUE(2^24).
 */
#if (defined CPL_LZMA_RANGE_DECODER_NORMALIZE)
#error CPL_LZMA_RANGE_DECODER_NORMALIZE is already defined
#endif

#define CPL_LZMA_RANGE_DECODER_NORMALIZE(rangeDecoder, inputBuf) do                                \
{                                                                                                  \
  if ((rangeDecoder)->Range < CPL_RD_TOPVALUE)                                                     \
  {                                                                                                \
    if(*(inputBuf) < argCtx->bufLimit)                                                             \
    {                                                                                              \
      /* Dereference the pointer only if there is input data available.                            \
       * In the case of Cpl_LZMADummyDecode an attempt to reference                                \
       * memory overrunning the end of an object might happen.                                     \
       * The address incrementation needs to happen as it's used as an                             \
       * "end of input data" marker. */                                                            \
      inByte = **(inputBuf);                                                                       \
    }                                                                                              \
    (*(inputBuf))           = &(*(inputBuf))[1U];                                                  \
    (rangeDecoder)->Range <<= 8U;                                                                  \
    (rangeDecoder)->Code    = ((rangeDecoder)->Code << 8U) | inByte;                               \
  }                                                                                                \
}                                                                                                  \
while(0U)

/*==================[type definitions]============================================================*/
/** \brief  Internal states of the LZMADecompress.
 */
typedef uint8 LZMA_StateType;

/** \brief  Return values for the LZMA decompression.  */
typedef uint8 LZMA_ReturnType;

/** \brief  Return values for the dummy decoding of packet types.  */
typedef uint8 LZMA_DummyType;

/** \brief  Status values for each decompression.
 */
typedef uint8 LZMA_StatusType;

/** \brief Structure to store the context of Range Decoder. */
typedef struct {
  /** \brief The interval on which, based on probability, the symbols will be decoded. */
  uint32  Range;

  /** \brief Part of the input stream from which the symbols will be decoded. */
  uint32  Code;

} LZMA_RangeDecoderType;

/** \brief Structure to store the context of Dictionary. */
typedef struct {
  /** \brief Position of the last written byte. */
  uint32  pos;

  /** \brief Position of the last data that was written in the output buffer. */
  uint32  posBeforeDec;

  /** \brief Buffer to keep data for the sliding window. */
  uint8   dict[MAX_DICT_SIZE];

} LZMA_DictType;

/** \brief Structure to store the probabilities of Lower length decoder. */
typedef struct {
  /** \brief Probability of occurrence of length between [2 - 9]. */
  CProbType ProbsLow[CPL_LOWCODER_NUM_SYMBOLS];
} LZMA_LowDecType;

/** \brief Structure to store the probabilities of Middle length decoder. */
typedef struct {
  /** \brief Probability of occurrence of length between [10 - 17]. */
  CProbType ProbsMid[CPL_MIDCODER_NUM_SYMBOLS];
} LZMA_MidDecType;

/** \brief Structure to store the probabilities of High length decoder. */
typedef struct {
  /** \brief Probability of occurrence of length between [18 - 273]. */
  CProbType ProbsHigh[CPL_HIGHCODER_NUM_SYMBOLS];
} LZMA_HighDecType;

/** \brief Structure to store the probabilities of Slot decoder. */
typedef struct {
  /** \brief Occurrence probability of one of the 64 position slots. */
 CProbType Probs[CPL_PSIZE(CPL_DIST_SLOT)];
} LZMA_PosSlotType;

/** \brief Structure to store the probabilities of Align decoder. */
typedef struct {
  /** \brief Occurrence probability of the lowest 4 bits of a distance. */
  CProbType Probs[CPL_PSIZE(CPL_DIST_ALIGN_BITS)];
} LZMA_AlignType;

/** \brief Structure to store the context of Length decoder. */
typedef struct {
  /** \brief Probability for the first bit in the length decoder. */
  CProbType      C1;

  /** \brief Probability for the second bit in the length decoder. */
  CProbType      C2;

  /** \brief Occurrence probability of an specific length
   *         from [2-9] range in one of the states.
   */
  LZMA_LowDecType LowDec[CPL_PSIZE(CPL_MAX_POS_BITS)];

  /** \brief Occurrence probability of an specific length
   *         from [10-17] range in one of the states.
   */
  LZMA_MidDecType MidDec[CPL_PSIZE(CPL_MAX_POS_BITS)];

  /** \brief Occurrence probability of an specific length
   *         from [18-273] range in one of the states.
   */
  LZMA_HighDecType HighDec;

} LZMA_LenDecType;

/** \brief Structure to store the context of LZMA decoder. */
typedef struct
{
  /** \brief Pointer to the corresponding LZMA decompression primitive configuration.
   */
  P2CONST(Cpl_LZMADecompressConfigType, AUTOMATIC, CPL_APPL_DATA) cfgPtr;

  /** \brief Pointer to an intermediary buffer.
   */
  P2CONST(uint8,                        AUTOMATIC, CPL_APPL_DATA) buf;

  /** \brief Pointer to the input data limit.
   */
  P2CONST(uint8,                        AUTOMATIC, CPL_APPL_DATA) bufLimit;

  /** \brief Data structure for the dictionary. */
  LZMA_DictType         dictionary;

  /** \brief Data structure for the Range Decoder. */
  LZMA_RangeDecoderType rangeDecoder;

  /** \brief How much is to be uncompress from the entire archive. */
  uint32                unpackSize;

  /** \brief Position in the entire uncompressed data [0 - argCtx->unpackSize]. */
  uint32                processedPos;

  /** \brief How much data was processed from the entire archive. */
  uint32                inAllProcessed;

  /** \brief 1st repetition used at packet decoding. */
  uint32                rep0;

  /** \brief 2nd repetition used at packet decoding. */
  uint32                rep1;

  /** \brief 3rd repetition used at packet decoding. */
  uint32                rep2;

  /** \brief 4th repetition used at packet decoding. */
  uint32                rep3;

  /** \brief Size of temporary buffer used for decompression. */
  uint32                tempBufSize;

  /** \brief Position in the dictionary from which the data will
   *         be copied in case of SMALL_BUFFER.
   */
  uint32                sbDictPos;

  /** \brief Data structure for the length decoder. */
  LZMA_LenDecType       lenDec;

  /** \brief Data structure for the repetition-length decoder. */
  LZMA_LenDecType       repLenDec;

  /** \brief Data structure for the slot decoder. */
  LZMA_PosSlotType      posSlotDec[CPL_MAX_POS_BITS];

  /** \brief Data structure for the align decoder. */
  LZMA_AlignType        algnDec;

  /** \brief Probability table to decode the position part from a packet. */
  CProbType             posDecoders[1U + (CPL_LZMA_FULL_DIST - CPL_DIST_MODEL_END)];

  /** \brief Probability table to decode the type of packet in function of the decodeState.
   *         There are 12 states and the type of packet
   *         is coded on a maximum of 4 bits(CPL_MAX_POS_BITS).
   *         We end up with 192 possible states(12 * 4); for each we have a probability.
   */
  CProbType             isMatch[(uint16)((uint16)(CPL_NUM_STATES) << CPL_MAX_POS_BITS)];

  /** \brief Probability table to decode a certain symbol from a packet. */
  CProbType             litProbs[(uint16)CPL_LIT_DECODER_SIZE << (MAX_LC + MAX_LP)];

  /** \brief The value denotes whether a packet is a LONGREP
   *         rather than a SHORTREP based on decodeState.
   */
  CProbType             isRep0Long[(uint8)(CPL_NUM_STATES) << CPL_MAX_POS_BITS];

  /** \brief The value denotes whether a packet that includes a length is a
   *         LONGREP rather than a MATCH based on decodeState.
   */
  CProbType             isRep[CPL_NUM_STATES];

  /** \brief The value denotes whether a packet is a LONGREP
   *         rather than a SHORTREP based on decodeState.
   */
  CProbType             isRepG0[CPL_NUM_STATES];

  /** \brief The value denotes whether a packet is a LONGREP[1]
   *         rather than a LONGREP[2-3] based on decodeState.
   */
  CProbType             isRepG1[CPL_NUM_STATES];

  /** \brief The value denotes whether a packet is a LONGREP[2]
   *         rather than a LONGREP[3] based on decodeState.
   */
  CProbType             isRepG2[CPL_NUM_STATES];

  /** \brief Data length to be copied from dictionary in case of SMALL_BUFFER. */
  uint16                sbDataLen;

  /** \brief Temporary buffer used for decompression. */
  uint8                 tempBuf[CPL_REQUIRED_INPUT_MAX];

  /** \brief State of the state machine used in packet decoding. */
  uint8                 decodeState;

  /** \brief The internal state of the decompression at the API level. */
  LZMA_StateType        initState;

  /** \brief Status of the decompression. */
  LZMA_StatusType       status;

  /** \brief Flag which indicates if the Code was read or not in the first decompression call. */
  boolean               needFlush;

  /** \brief Flag which indicates if the header was decoded or not. */
  boolean               isDecodingHeader;

  /** \brief Flag which indicates if the output buffer was to small. */
  boolean               isSmallBuf;

  /** \brief Flag which indicates if the Range Decoder code was completely processed. */
  boolean               codeLeft;

} Cpl_LZMADecompressCtxBufType;

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/
/** \brief                        Decode the type of packet
 *
 *                                The decoding will happen without affecting any of the context
 *                                variables; range, code, state or any of the probabilities.
 *
 *  \param[in,out]  argCtx        Holds a pointer to the context buffer for the LZMA decompression.
 *  \param[in]      inputBuf      Holds a pointer to the data that shall be processed.
 *
 * \return          Type of packet.
 *
 * \retval          CPL_DUMMY_ERROR   No packet can be decoded with the data provided.
 * \retval          CPL_DUMMY_LIT     A LIT packet can be decoded with the data provided.
 * \retval          CPL_DUMMY_REP     A REP, SHORTREP or LONGREP[*] packet can be decoded
 *                                with the data provided.
 */
STATIC FUNC(LZMA_DummyType, CPL_CODE) Cpl_LZMADummyDecode
(
  P2VAR(Cpl_LZMADecompressCtxBufType,   AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                        AUTOMATIC, CPL_APPL_DATA) inputBuf
);

/** \brief                        Decode the distance from the packets
 *
 *  \param[in,out]  argCtx          Holds a pointer to the context buffer
 *                                  for the LZMA decompression.
 *  \param[in,out]  rangeDecoder    Holds a pointer to the range decoder structure.
 *  \param[in]      len             The other part of the (dist, len) package.
 *  \param[in]      inputBuf        Location of the input data.
 *  \param[in]      doUpdateContext Flag to indicate if the context is modified or not.
 *
 * \return  Distance
 */
STATIC FUNC(uint32, CPL_CODE) Cpl_LZMADistDecode
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(LZMA_RangeDecoderType,                    AUTOMATIC, CPL_APPL_DATA) rangeDecoder,
        uint16                                                              len,
  /* Deviation MISRAC2012-2 */
  P2VAR(P2CONST(uint8, AUTOMATIC, CPL_APPL_DATA), AUTOMATIC, CPL_APPL_DATA) inputBuf,
        boolean                                                             doUpdateContext
);

/** \brief                        Decode length packets using the Binary Tree
 *
 *  \param[in,out]  argCtx          Holds a pointer to the context buffer
 *                                  for the LZMA decompression.
 *  \param[in]      posState        Use value as context to select the binary tree.
 *  \param[in, out] LD              Pointer to the Length Decoder structure.
 *  \param[in]      inputBuf        Holds a pointer to the data that shall be processed.
 *  \param[in]      doUpdateContext Flag to indicate if the context is modified or not.
 *
 *  \return         Length
 */
STATIC FUNC(uint16, CPL_CODE) Cpl_LZMALenDecode
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(LZMA_RangeDecoderType,                    AUTOMATIC, CPL_APPL_DATA) rangeDecoder,
        uint32                                                              posState,
  P2VAR(LZMA_LenDecType,                          AUTOMATIC, CPL_APPL_DATA) LD,
  /* Deviation MISRAC2012-2 */
  P2VAR(P2CONST(uint8, AUTOMATIC, CPL_APPL_DATA), AUTOMATIC, CPL_APPL_DATA) inputBuf,
        boolean                                                             doUpdateContext
);

/** \brief                        Decodes bits from high bit to low bit (the normal scheme)
 *
 *  \param[in,out]  argCtx          Holds a pointer to the context buffer
 *                                  for the LZMA decompression.
 *  \param[in,out]  rangeDecoder    Holds a pointer to the range decoder structure.
 *  \param[in]      NumBits         Holds the length of the table.
 *  \param[in, out] Probs           Holds the probability table.
 *  \param[in]      inputBuf        Holds a pointer to the data that shall be processed.
 *  \param[in]      doUpdateContext Flag to indicate if the context is modified or not.
 *
 *  \returns        Decoded symbol
 */
STATIC FUNC(uint16, CPL_CODE) Cpl_LZMABitTreeDecoderDirect
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(LZMA_RangeDecoderType,                    AUTOMATIC, CPL_APPL_DATA) rangeDecoder,
        uint16                                                              numBits,
  P2VAR(CProbType,                                AUTOMATIC, CPL_APPL_DATA) probs,
  /* Deviation MISRAC2012-2 */
  P2VAR(P2CONST(uint8, AUTOMATIC, CPL_APPL_DATA), AUTOMATIC, CPL_APPL_DATA) inputBuf,
        boolean                                                             doUpdateContext
);

/** \brief                        Decodes bits from low bit to high bit (the reverse scheme)
 *
 *  \param[in,out]  argCtx          Holds a pointer to the context buffer
 *                                  for the LZMA decompression.
 *  \param[in,out]  rangeDecoder    Holds a pointer to the range decoder structure.
 *  \param[in, out] probs           Holds a pointer to the probability table.
 *  \param[in]      numBits         Holds the length of the table.
 *  \param[in]      inputBuf        Holds a pointer to the data that shall be processed.
 *  \param[in]      doUpdateContext Flag to indicate if the context is modified or not.
 *
 *  \returns        Decoded symbol
 */
STATIC FUNC(uint32, CPL_CODE) Cpl_LZMABitTreeReverseDecode
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(LZMA_RangeDecoderType,                    AUTOMATIC, CPL_APPL_DATA) rangeDecoder,
  P2VAR(CProbType,                                AUTOMATIC, CPL_APPL_DATA) probs,
        uint8                                                               numBits,
  /* Deviation MISRAC2012-2 */
  P2VAR(P2CONST(uint8, AUTOMATIC, CPL_APPL_DATA), AUTOMATIC, CPL_APPL_DATA) inputBuf,
        boolean                                                             doUpdateContext
);

/** \brief                        Decode Direct Bits from Range Decoder
 *                                Decode direct bits that have equal probabilities of 50%.
 *
 *  \param[in,out]  argCtx        Holds a pointer to the context buffer
 *                                for the LZMA decompression.
 *  \param[in,out]  rangeDecoder  Holds a pointer to the range decoder structure.
 *  \param[in]      noBits        Holds number of bits to be decoded.
 *  \param[in]      inputBuf      Holds a pointer to the data that shall be processed.
 *
 *  \returns        Decoded value.
 */
STATIC FUNC(uint32, CPL_CODE) Cpl_LZMARangeDecoderGetDirectBits
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(LZMA_RangeDecoderType,                    AUTOMATIC, CPL_APPL_DATA) rangeDecoder,
        uint32                                                              noBits,
  /* Deviation MISRAC2012-2 */
  P2VAR(P2CONST(uint8, AUTOMATIC, CPL_APPL_DATA), AUTOMATIC, CPL_APPL_DATA) inputBuf
);

/** \brief                        Decode one bit based on the probability from the probability table
 *
 *  \param[in,out]  argCtx          Holds a pointer to the context buffer
 *                                  for the LZMA decompression.
 *  \param[in,out]  rangeDecoder    Holds a pointer to the range decoder structure.
 *  \param[in, out] prob            Holds a pointer to the probability table.
 *  \param[in]      inputBuf        Holds a pointer to the data that shall be processed.
 *  \param[in]      doUpdateContext Flag to indicate if the context is modified or not.
 *
 *  \returns        Decoded symbol
 */
STATIC FUNC(uint8, CPL_CODE) Cpl_LZMARangeDecoderDecodeBit
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(LZMA_RangeDecoderType,                    AUTOMATIC, CPL_APPL_DATA) rangeDecoder,
  P2VAR(CProbType,                                AUTOMATIC, CPL_APPL_DATA) prob,
  /* Deviation MISRAC2012-2 */
  P2VAR(P2CONST(uint8, AUTOMATIC, CPL_APPL_DATA), AUTOMATIC, CPL_APPL_DATA) inputBuf,
        boolean                                                             doUpdateContext
);

/** \brief                        Initialize all the probabilities tables
 *
 *  \param[in]      argCfg        Pointer to LZMADecompress module configuration which has to
 *                                be used during the LZMA decompression computation.
 *  \param[in,out]  argCtx        Holds a pointer to the context buffer for the LZMA decompression.
 */
STATIC FUNC(void, CPL_CODE) Cpl_LZMAInit
(
  P2CONST(Cpl_LZMADecompressConfigType,           AUTOMATIC, CPL_APPL_DATA) argCfg,
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx
);

/** \brief                        Handles end of decompression status
 *
 *  \param[in,out]  argCtx        Holds a pointer to the context buffer for the LZMA decompression.
 *
 *  \returns        Error value.
 *
 *  \retval         CAL_E_OK          Request successful.
 *  \retval         CAL_E_NOT_OK      Request failed.
 */
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZMADecompressEnd
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx
);

/** \brief                        Decode the header of the LZMA stream
 *                                Decode the LP, LC, PB, dictionary size and the uncompressed size.
 *                                If those variable do not fit the configuration return NOT_OK.
 *
 *  \param[in,out]  argCtx        Holds a pointer to the context buffer for the LZMA decompression.
 *  \param[in]      LZMAHeader    Pointer to the header data.
 *
 *  \returns        Error value.
 *
 *  \retval         CAL_E_OK          Request successful.
 *  \retval         CAL_E_NOT_OK      Request failed.
 */
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZMADecodeHeader
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                                  AUTOMATIC, CPL_APPL_DATA) LZMAHeader
);

/** \brief                        Put a match represented by the (dist, len) pair in the dictionary
 *
 *  \param[in,out]  argCtx        Holds a pointer to the context buffer for the LZMA decompression
 *  \param[in]      dist          The distance from which the data will be copied
 *  \param[in]      len           How much data needs to be copied
 */
STATIC FUNC(void, CPL_CODE) Cpl_LZMADictPutMatch
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
        uint32                                                              dist,
        uint16                                                              len
);

/** \brief                        Copy from the dictionary to the output buffer
 *
 *  \param[in,out]  argCtx        Holds a pointer to the context buffer for the LZMA decompression
 *  \param[out]     outBuf        Holds a pointer to output buffer
 *  \param[in]      dicPos        The position in the dictionary from which the data will be fetched
 *  \param[in]      len           How much data needs to be copied
 */
STATIC FUNC(void, CPL_CODE) Cpl_LZMADictPutOut
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                                    AUTOMATIC, CPL_APPL_DATA) outBuf,
        uint32                                                              dictPos,
        uint32                                                              len
);

/** \brief                        Write data from the dictionary into output buffer
 *
 *  \param[in]      argCtx        Holds a pointer to the context buffer for the LZMA decompression
 *  \param[in, out] dest          Location of the output data.
 *  \param[in, out] destLen       Length of the output data.
 *  \param[in, out] isProcessed   Flag to indicate if this call of decompress finished.
 *
 *  \return         How much data was written in the output buffer.
 */
STATIC FUNC(uint16, CPL_CODE) Cpl_LZMAWriteOutput
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                                    AUTOMATIC, CPL_APPL_DATA) dest,
  P2VAR(uint32,                                   AUTOMATIC, CPL_APPL_DATA) destLen,
  P2VAR(boolean,                                  AUTOMATIC, CPL_APPL_DATA) isProcessed
);

/** \brief                        Decode a LIT packet
 *
 *  \param[in,out]  argCtx          Holds a pointer to the context buffer
 *                                  for the LZMA decompression.
 *  \param[in,out]  rangeDecoder    Holds a pointer to the range decoder structure.
 *  \param[in]      inputBuf        Location of the input data.
 *  \param[in, out] dict            Pointer to the dictionary sliding window.
 *  \param[in, out] dictPos         Position at which the byte must be put.
 *  \param[in, out] processedPos    How much from all data was processed.
 *  \param[in]      decodeState     State of the packet decompression state machine.
 *  \param[in]      doUpdateContext Flag to indicate if the context is modified or not.
 */
STATIC FUNC(void, CPL_CODE) Cpl_LZMADecodeLiteral
(
  /* Deviation MISRAC2012-2 */
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(LZMA_RangeDecoderType,                    AUTOMATIC, CPL_APPL_DATA) rangeDecoder,
  P2VAR(P2CONST(uint8, AUTOMATIC, CPL_APPL_DATA), AUTOMATIC, CPL_APPL_DATA) inputBuf,
  P2CONST(uint8,                                  AUTOMATIC, CPL_APPL_DATA) dict,
  P2CONST(uint32,                                 AUTOMATIC, CPL_APPL_DATA) dictPos,
  P2CONST(uint32,                                 AUTOMATIC, CPL_APPL_DATA) processedPos,
          uint8                                                             decodeState,
          boolean                                                           doUpdateContext
);

/** \brief                        Initialize the Length Decoder
 *                                Initialize all the probabilities table with 50% probability.
 *  \param[in, out] LD            Pointer to the Length Decoder structure.
 */
STATIC FUNC(void, CPL_CODE) Cpl_LZMALenDecInit
(
  P2VAR(LZMA_LenDecType,                          AUTOMATIC, CPL_APPL_DATA) LD
);

/** \brief                        Initialize the Distance decoder
 *
 *  \param[in,out]  argCtx        Holds a pointer to the context buffer for the LZMA decompression.
 */
STATIC FUNC(void, CPL_CODE) Cpl_LZMADistDecInit
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx
);

/** \brief                        Decode and manage input data from the DecompressRun function.
 *
 *                                This function decode a maximum of
 *                                dictionary size data in one call.
 *
 *  \param[in,out]  argCtx        Holds a pointer to the context buffer for the LZMA decompression.
 *  \param[in]      src           Location of the input data.
 *  \param[in, out] dest          Location of the output data.
 *  \param[in, out] destLen       Length of the output data.
 *                                After the call it the available space is stored.
 *  \param[in, out] status        Status of the decompression.
 */
STATIC FUNC(LZMA_ReturnType, CPL_CODE) Cpl_LZMADecodeToDic
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                                  AUTOMATIC, CPL_APPL_DATA) src,
  P2VAR(uint8,                                    AUTOMATIC, CPL_APPL_DATA) dest,
  P2VAR(uint32,                                   AUTOMATIC, CPL_APPL_DATA) destLen,
  P2VAR(LZMA_StatusType,                          AUTOMATIC, CPL_APPL_DATA) status
);

/** \brief                        Handle the writing of output data in the case
 *                                the previous call of Updated returned CAL_E_SMALL_BUFFER
 *
 *  \param[in,out]  argCtx        Holds a pointer to the context buffer for the LZMA decompression.
 *  \param[in, out] dest          Location of the output data.
 *  \param[in, out] destLen       Length of the output data.
 *                                After the call it the available space is stored.
 *  \param[in, out] decFinished   Boolean flag to indicate if decoding should be done.
 *
 *  \returns        Error value.
 *
 *  \retval         CAL_E_OK            Request successful.
 *  \retval         CAL_E_NOT_OK        Request failed.
 *  \retval         CAL_E_SMALL_BUFFER  The provided output buffer is too small.
 *
 */
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZMASmallBufHandling
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  /* Deviation MISRAC2012-2 */
  P2VAR(P2VAR(uint8, AUTOMATIC, CPL_APPL_DATA),   AUTOMATIC, CPL_APPL_DATA) dest,
  P2VAR(uint32,                                   AUTOMATIC, CPL_APPL_DATA) destLen,
  P2VAR(boolean,                                  AUTOMATIC, CPL_APPL_DATA) decFinished
);

/** \brief                        Handle the aggregation of data for the header decoding
 *
 *  \param[in,out]  argCtx        Holds a pointer to the context buffer for the LZMA decompression.
 *  \param[in]      inBuf         One byte of input data.
 *  \param[in, out] decFinished   Boolean flag to indicate if decoding should be done.
 *  \param[in, out] mustCont      Flag to indicate if a new byte is needed.
 *
 *  \returns        Error value.
 *
 *  \retval         CAL_E_OK            Request successful.
 *  \retval         CAL_E_NOT_OK        Request failed.
 *
 */
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZMAHeaderHandling
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
        uint8                                                               inBuf,
  P2VAR(boolean,                                  AUTOMATIC, CPL_APPL_DATA) decFinished,
  P2VAR(boolean,                                  AUTOMATIC, CPL_APPL_DATA) mustCont
);

/** \brief                        Decode input data from the Update call.
 *
 *                                The scope of this function is to aggregate or split data from
 *                                the Update call.
 *
 *  \param[in,out]  argCtx        Holds a pointer to the context buffer for the LZMA decompression.
 *  \param[in]      src           Location of the input data.
 *  \param[in, out] srcLen        Length of the input data.
 *  \param[in, out] dest          Location of the output data.
 *  \param[in, out] destLen       Length of the output data.
 *  \param[in, out] status        Status of the decompression.
 */
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZMADecompressRun
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                                  AUTOMATIC, CPL_APPL_DATA) src,
    P2VAR(uint32,                                 AUTOMATIC, CPL_APPL_DATA) srcLen,
    P2VAR(uint8,                                  AUTOMATIC, CPL_APPL_DATA) dest,
    P2VAR(uint32,                                 AUTOMATIC, CPL_APPL_DATA) destLen
);

/** \brief                        Decodes chunks of data from DecodeToDic
 *
 *  \param[in,out]  argCtx        Holds a pointer to the context buffer for the LZMA decompression.
 */
STATIC FUNC(LZMA_ReturnType, CPL_CODE) Cpl_LZMADecodeReal
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx
);

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CPL_START_SEC_CODE
#include "MemMap.h"

/* !LINKSTO EB_CPL_0804_101, 1 */
/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMADecompressStart]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZMADecompressStart
(
  P2CONST(void,                     AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer
)
{
  /* ~~~ local constants ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  CONSTP2CONST(Cpl_LZMADecompressConfigType, AUTOMATIC, CPL_APPL_DATA) locCfgPtr =
      (P2CONST(Cpl_LZMADecompressConfigType, AUTOMATIC, CPL_APPL_DATA)) cfgPtr;

  /* Deviation MISRAC2012-1 <START> */
  CONSTP2VAR(Cpl_LZMADecompressCtxBufType, AUTOMATIC, CPL_VAR) locCtxPtr =
      (P2VAR(Cpl_LZMADecompressCtxBufType, AUTOMATIC, CPL_VAR)) contextBuffer;
  /* Deviation MISRAC2012-1 <STOP> */

  Cal_ReturnType locRetVal = CAL_E_NOT_OK;

  /* !LINKSTO EB_CPL_0804_102, 1 */
  if ( (sizeof(Cal_DecompressCtxBufType) >= sizeof(Cpl_LZMADecompressCtxBufType)) &&
       (locCtxPtr                        != NULL_PTR                            ) &&
       (locCfgPtr                        != NULL_PTR                            )
     )
  {
    Cpl_LZMAInit(locCfgPtr, locCtxPtr);
    locRetVal = CAL_E_OK;
  }

  return locRetVal;
}


/* !LINKSTO EB_CPL_0804_103, 1 */
/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMADecompressUpdate]------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZMADecompressUpdate
(
  P2CONST(void,                     AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer,
  P2CONST(uint8,                    AUTOMATIC, CPL_APPL_DATA) inputBuf,
    P2VAR(uint32,                   AUTOMATIC, CPL_APPL_DATA) inputBufLen,
    P2VAR(uint8,                    AUTOMATIC, CPL_APPL_DATA) outputBuf,
    P2VAR(uint32,                   AUTOMATIC, CPL_APPL_DATA) outputBufLen
)
{
  Cal_ReturnType locRetVal = CAL_E_NOT_OK;

  /* ~~~ local constants ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  CONSTP2CONST(Cpl_LZMADecompressConfigType, AUTOMATIC, CPL_APPL_DATA) locCfgPtr =
      (P2CONST(Cpl_LZMADecompressConfigType, AUTOMATIC, CPL_APPL_DATA)) cfgPtr;

  /* Deviation MISRAC2012-1 <START> */
  CONSTP2VAR(Cpl_LZMADecompressCtxBufType, AUTOMATIC, CPL_VAR) locCtxPtr =
      (P2VAR(Cpl_LZMADecompressCtxBufType, AUTOMATIC, CPL_VAR)) contextBuffer;
  /* Deviation MISRAC2012-1 <STOP> */
  /* !LINKSTO EB_CPL_0804_104, 1 */
  if ( (locCtxPtr            !=     NULL_PTR                  ) &&
       (locCfgPtr            !=     NULL_PTR                  ) &&
       (locCfgPtr            ==     locCtxPtr->cfgPtr         ) &&
       (locCtxPtr->initState ==     CPL_LZMA_STAT_INITIALIZED ) &&
       (inputBuf             !=     NULL_PTR                  ) &&
       (inputBufLen          !=     NULL_PTR                  ) &&
       (outputBuf            !=     NULL_PTR                  ) &&
       (outputBufLen         !=     NULL_PTR                  )
     )
  {
    locRetVal = Cpl_LZMADecompressRun(locCtxPtr, inputBuf, inputBufLen, outputBuf, outputBufLen);
  }

  /* !LINKSTO EB_CPL_0804_106, 1 */
  if ( (locRetVal        != CAL_E_OK                  ) &&
       (locRetVal        != CAL_E_SMALL_BUFFER        ) &&
       (locCtxPtr        != NULL_PTR                  ) &&
       (locCfgPtr        != NULL_PTR                  ) &&
       (locCfgPtr        == locCtxPtr->cfgPtr         )
     )
  {

    locRetVal = Cpl_LZMADecompressEnd(locCtxPtr);
  }

  return locRetVal;
}

/* !LINKSTO EB_CPL_0804_105, 1 */
/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMADecompressFinish]------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZMADecompressFinish
(
  P2CONST(void,                     AUTOMATIC, CPL_APPL_DATA) cfgPtr,
      VAR(Cal_DecompressCtxBufType, AUTOMATIC               ) contextBuffer,
    P2VAR(uint8,                    AUTOMATIC, CPL_APPL_DATA) outputBuf,
    P2VAR(uint32,                   AUTOMATIC, CPL_APPL_DATA) outputBufLen
)
{
  Cal_ReturnType locRetVal = CAL_E_NOT_OK;

  CONSTP2CONST(Cpl_LZMADecompressConfigType, AUTOMATIC, CPL_APPL_DATA) locCfgPtr =
      (P2CONST(Cpl_LZMADecompressConfigType, AUTOMATIC, CPL_APPL_DATA)) cfgPtr;

  /* Deviation MISRAC2012-1 <START> */
  CONSTP2VAR(Cpl_LZMADecompressCtxBufType, AUTOMATIC, CPL_VAR) locCtxPtr =
      (P2VAR(Cpl_LZMADecompressCtxBufType, AUTOMATIC, CPL_VAR)) contextBuffer;
  /* Deviation MISRAC2012-1 <STOP> */

  /* !LINKSTO EB_CPL_0804_108, 1 */
  if ( ( locCtxPtr             != NULL_PTR           ) &&
       ( locCfgPtr             != NULL_PTR           ) &&
       ( locCfgPtr             == locCtxPtr->cfgPtr  ) &&
       ( locCtxPtr->initState  != CPL_LZMA_STAT_IDLE ) &&
       ( outputBuf             != NULL_PTR           ) &&
       ( outputBufLen          != NULL_PTR           )
     )
  {
    locRetVal = Cpl_LZMADecompressEnd(locCtxPtr);
    *outputBufLen = 0U;
  }

  return locRetVal;
}


/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMADecodeHeader]----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZMADecodeHeader
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                                  AUTOMATIC, CPL_APPL_DATA) LZMAHeader
)
{
  Cal_ReturnType locRetVal = CAL_E_NOT_OK;
  uint8          LZMAParams;
  uint8          lc, pb, lp, i, b;
  uint32         dictSizeInHeader = 0U;

  LZMAParams = LZMAHeader[0U];

  lc = LZMAParams % 9U;
  LZMAParams /= 9U;
  pb = LZMAParams / 5U;
  lp = LZMAParams % 5U;

  /* Decode dictionary size. */
  for (i = 0U; i < 4U; i++)
  {
    dictSizeInHeader |= (uint32)LZMAHeader[i + 1U] << (8U * i);
  }

  /* If the parameters configured in Tresos don't match the ones
   * in the file header abort with CAL_E_NOT_OK.
   */
  if((argCtx->cfgPtr->lc       == lc              ) &&
     (argCtx->cfgPtr->lp       == lp              ) &&
     (argCtx->cfgPtr->pb       == pb              ) &&
     (argCtx->cfgPtr->dictSize == dictSizeInHeader)
    )
  {
    locRetVal = CAL_E_OK;
  }

  /* We support only uncompressed data smaller than 2^32 - 1.
   * The uncompressed size spans on 64 bits in the header; as we don't support
   * that we don't read the second uint32 from the header.
   */
  for (i = 0U; i < 4U; i++)
  {
    b = LZMAHeader[5U + i];
    argCtx->unpackSize |= (uint32)b << (8U * i);
  }

  return locRetVal;
}


/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMARangeDecoderGetDirectBits]---------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(uint32, CPL_CODE) Cpl_LZMARangeDecoderGetDirectBits
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(LZMA_RangeDecoderType,                    AUTOMATIC, CPL_APPL_DATA) rangeDecoder,
        uint32                                                              noBits,
  /* Deviation MISRAC2012-2 */
  P2VAR(P2CONST(uint8, AUTOMATIC, CPL_APPL_DATA), AUTOMATIC, CPL_APPL_DATA) inputBuf
)
{
  uint32 firstBit = 0U;
  uint32 res      = 0U;
  uint8  inByte   = 0U;

  while (noBits != 0U)
  {
    /* Down-scale the range and code. */
    rangeDecoder->Range >>= 1U;
    rangeDecoder->Code   -= rangeDecoder->Range;

    firstBit = (0U - ((uint32)rangeDecoder->Code >> 31U));

    rangeDecoder->Code += (rangeDecoder->Range & firstBit);

    CPL_LZMA_RANGE_DECODER_NORMALIZE(rangeDecoder,
                                     inputBuf
                                    );

    /* Combine new bit. */
    res <<= 1U;
    res  += (firstBit + 1U);

    --noBits;
  }

  return res;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMARangeDecoderDecodeBit]-------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(uint8, CPL_CODE) Cpl_LZMARangeDecoderDecodeBit
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(LZMA_RangeDecoderType,                    AUTOMATIC, CPL_APPL_DATA) rangeDecoder,
  P2VAR(CProbType,                                AUTOMATIC, CPL_APPL_DATA) prob,
  /* Deviation MISRAC2012-2 */
  P2VAR(P2CONST(uint8, AUTOMATIC, CPL_APPL_DATA), AUTOMATIC, CPL_APPL_DATA) inputBuf,
        boolean                                                             doUpdateContext
)
{
  uint8  symbol;
  uint8  inByte  = 0U;
  uint16 curProb = *prob;

  /* Compute the border in the range(0 - 0xFFFFFFFF) that splits it
   * into 0 and 1 based on the latest probability.
   */
  uint32 bound = (uint32)((rangeDecoder->Range >> CPL_RD_NUM_MODEL_BITS) * curProb);

  if (rangeDecoder->Code < bound)
  {
    curProb += ((CPL_PSIZE(CPL_RD_NUM_MODEL_BITS) - curProb) >> CPL_RD_NUM_MOVE_BITS);

    /* Set the new border for the range. */
    rangeDecoder->Range = bound;
    symbol              = 0U;
  }
  else
  {
    curProb -= (curProb >> CPL_RD_NUM_MOVE_BITS);

    /* Lower the range and code in order to decode the next symbol. */
    rangeDecoder->Code  -= bound;
    rangeDecoder->Range -= bound;
    symbol               = 1U;
  }

  if(doUpdateContext == TRUE)
  {
    /* Update the probability table in favor of the last detected symbol. */
    *prob = (CProbType)curProb;
  }

  /* Fetch new data if necessary. */
  CPL_LZMA_RANGE_DECODER_NORMALIZE(rangeDecoder,
                                   inputBuf
                                  );

  return symbol;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMABitTreeReverseDecode]--------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(uint32, CPL_CODE) Cpl_LZMABitTreeReverseDecode
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(LZMA_RangeDecoderType,                    AUTOMATIC, CPL_APPL_DATA) rangeDecoder,
  P2VAR(CProbType,                                AUTOMATIC, CPL_APPL_DATA) probs,
        uint8                                                               numBits,
  /* Deviation MISRAC2012-2 */
  P2VAR(P2CONST(uint8, AUTOMATIC, CPL_APPL_DATA), AUTOMATIC, CPL_APPL_DATA) inputBuf,
        boolean                                                             doUpdateContext
)
{
  uint32 bound;
  uint32 symbol = 0U;
  uint16 m      = 1U;
  uint16 curProb;
  uint8  bit;
  uint8  inByte = 0U;
  uint8  i      = 0U;

  for(i = 0U; i < numBits; i++)
  {
    /* Same functionality as Cpl_LZMARangeDecoderDecodeBit(). */

     curProb = probs[m];

    /* Compute the border in the range(0 - 0xFFFFFFFF) that splits it
     * into 0 and 1 based on the latest probability.
     */
    bound = (uint32)((rangeDecoder->Range >> CPL_RD_NUM_MODEL_BITS) * curProb);

    if (rangeDecoder->Code < bound)
    {
      curProb += ((CPL_PSIZE(CPL_RD_NUM_MODEL_BITS) - curProb) >> CPL_RD_NUM_MOVE_BITS);

      /* Set the new border for the range. */
      rangeDecoder->Range = bound;
      bit                 = 0U;
    }
    else
    {
      curProb -= (curProb >> CPL_RD_NUM_MOVE_BITS);

      /* Lower the range and code in order to decode the next symbol. */
      rangeDecoder->Code  -= bound;
      rangeDecoder->Range -= bound;
      bit                   = 1U;
    }

    if(doUpdateContext == TRUE)
    {
      /* Update the probability table in favor of the last detected symbol. */
      probs[m] = curProb;
    }

    CPL_LZMA_RANGE_DECODER_NORMALIZE(rangeDecoder,
                                     inputBuf
                                    );

    m     <<= 1U;
    m      += bit;
    symbol |= (uint32)((uint32)bit << i);
  }

  return symbol;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMABitTreeDecoderDirect]--------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(uint16, CPL_CODE) Cpl_LZMABitTreeDecoderDirect
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(LZMA_RangeDecoderType,                    AUTOMATIC, CPL_APPL_DATA) rangeDecoder,
        uint16                                                              numBits,
  P2VAR(CProbType,                                AUTOMATIC, CPL_APPL_DATA) probs,
  /* Deviation MISRAC2012-2 */
  P2VAR(P2CONST(uint8, AUTOMATIC, CPL_APPL_DATA), AUTOMATIC, CPL_APPL_DATA) inputBuf,
        boolean                                                             doUpdateContext
)
{
  uint32 bound;
  uint16 curProb;
  uint16 i;
  uint16 m      = 1U;
  uint8  inByte = 0U;
  uint8  symbol;


  for (i = 0U; i < numBits; i++)
  {
    /* Same functionality as Cpl_LZMARangeDecoderDecodeBit(). */

     curProb = probs[m];

    /* Compute the border in the range(0 - 0xFFFFFFFF) that splits it
     * into 0 and 1 based on the latest probability.
     */
    bound = (uint32)((rangeDecoder->Range >> CPL_RD_NUM_MODEL_BITS) * curProb);

    if (rangeDecoder->Code < bound)
    {
      curProb += ((CPL_PSIZE(CPL_RD_NUM_MODEL_BITS) - curProb) >> CPL_RD_NUM_MOVE_BITS);

      /* Set the new border for the range. */
      rangeDecoder->Range = bound;
      symbol              = 0U;
    }
    else
    {
      curProb -= (curProb >> CPL_RD_NUM_MOVE_BITS);

      /* Lower the range and code in order to decode the next symbol. */
      rangeDecoder->Code  -= bound;
      rangeDecoder->Range -= bound;
      symbol               = 1U;
    }

    if(doUpdateContext == TRUE)
    {
      /* Update the probability table in favor of the last detected symbol. */
      probs[m] = curProb;
    }


    CPL_LZMA_RANGE_DECODER_NORMALIZE(rangeDecoder,
                                     inputBuf
                                    );

    m = (uint16)(m << 1U) + symbol;

  }

  return m - (uint16)((uint16)1U << numBits);
}


/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMADecodeLiteral]---------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, CPL_CODE) Cpl_LZMADecodeLiteral
(
  /* Deviation MISRAC2012-2 */
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(LZMA_RangeDecoderType,                    AUTOMATIC, CPL_APPL_DATA) rangeDecoder,
  P2VAR(P2CONST(uint8, AUTOMATIC, CPL_APPL_DATA), AUTOMATIC, CPL_APPL_DATA) inputBuf,
  P2CONST(uint8,                                  AUTOMATIC, CPL_APPL_DATA) dict,
  P2CONST(uint32,                                 AUTOMATIC, CPL_APPL_DATA) dictPos,
  P2CONST(uint32,                                 AUTOMATIC, CPL_APPL_DATA) processedPos,
          uint8                                                             decodeState,
          boolean                                                           doUpdateContext
)
{
  P2VAR(CProbType, AUTOMATIC, CPL_APPL_DATA) probs;
  uint32 symbol      = 1U;
  uint32 symbolProb;
  uint16 litState    = 0U;
  uint16 litStateTmp = 0U;
  uint8  bit         = 0U;
  uint8  prevByte    = 0U;
  uint8  matchByte   = 0U;
  uint8  matchBit    = 0U;

  if (*processedPos != 0U)
  {
    prevByte = CPL_LZMA_DICT_GET_BYTE(dict,
                                      *dictPos,
                                      1U
                                     );
  }

  /* Select probability table based on the LC and LP. */
  litStateTmp = (uint16)((uint16)prevByte >> (8U - argCtx->cfgPtr->lc));
  litState    = (uint16)(*processedPos);
  litState   &= ((uint16)((uint16)1U << argCtx->cfgPtr->lp) - 1U);
  litState  <<= (uint16)(argCtx->cfgPtr->lc);
  litState   +=  litStateTmp;

  /* Go to the start probability of each symbol; from there decode
   * 8 bits that correspond to the literal.
   */
  probs = &argCtx->litProbs[(uint16)CPL_LIT_DECODER_SIZE * litState];

  /* If (decodeState > 7), the Literal Decoder uses "matchByte" that represents
   * the byte in OutputStream at position the is the DISTANCE bytes before
   * current position, where the DISTANCE is the distance in
   * DISTANCE-LENGTH pair of latest decoded match.
   */
  if (decodeState >= 7U)
  {
    matchByte = CPL_LZMA_DICT_GET_BYTE(dict,
                                       *dictPos,
                                       argCtx->rep0
                                      );
    do
    {
      matchBit     = (matchByte >> 7U) & 1U;
      matchByte  <<= 1U;

      symbolProb   = (uint32)1U + (uint32)matchBit;
      symbolProb <<= (uint32)8U;
      symbolProb  += (uint32)symbol;

      bit = Cpl_LZMARangeDecoderDecodeBit(argCtx,
                                          rangeDecoder,
                                          &probs[symbolProb],
                                          inputBuf,
                                          doUpdateContext
                                         );

      symbol = (symbol << 1U) | bit;

      if (matchBit != bit)
      {
        break;
      }
    }
    while (symbol < CPL_LIT_MAX_VAL);
  }

  while (symbol < CPL_LIT_MAX_VAL)
  {
    /* Add to symbol the decoded bit. */
    symbol = (symbol << 1U) | Cpl_LZMARangeDecoderDecodeBit(argCtx,
                                                            rangeDecoder,
                                                            &probs[symbol],
                                                            inputBuf,
                                                            doUpdateContext
                                                           );
  }

  if(doUpdateContext == TRUE)
  {
    /* Puts the decode bit into the Sliding window buffer. */
    CPL_LZMA_DICT_PUT_BYTE((uint8)(symbol - CPL_LIT_MAX_VAL));
  }
}



/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMADecompressRun]---------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZMADecompressRun
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                                  AUTOMATIC, CPL_APPL_DATA) src,
    P2VAR(uint32,                                 AUTOMATIC, CPL_APPL_DATA) srcLen,
    P2VAR(uint8,                                  AUTOMATIC, CPL_APPL_DATA) dest,
    P2VAR(uint32,                                 AUTOMATIC, CPL_APPL_DATA) destLen
)
{
  uint32          locDestLen    = *destLen;
  uint32          locSrcLen     = *srcLen;
  uint32          initDestLen;
  uint32          destLenPreDec = 0U;
  uint32          destIdx       = 0U;
  uint32          initInSize    = 0U;
  uint32          inRead        = 0U;
  uint8           inBuf;
  Cal_ReturnType  localRet      = CAL_E_OK;
  LZMA_ReturnType retDec        = CPL_DEC_OK;
  boolean         decFinished   = FALSE;
  boolean         mustCont      = FALSE;

  initInSize  = locSrcLen;
  initDestLen = locDestLen;

  localRet = Cpl_LZMASmallBufHandling(argCtx,
                                      &dest,
                                      &locDestLen,
                                      &decFinished
                                     );

  /* If there is no input data or output space available, exit. */
  if((locSrcLen  == 0U) ||
     (locDestLen == 0U)
    )
  {
    decFinished = TRUE;
  }

  /* While there is input data and the decompression is not finished. */
  while(decFinished == FALSE)
  {
    mustCont = FALSE;

    inBuf = src[initInSize - locSrcLen];

    /* How much was read in the current Update call. */
    ++inRead;

    /* Adjust how much data is to be decoded from the update call. */
    --locSrcLen;

    ++argCtx->inAllProcessed;

    if(argCtx->isDecodingHeader == TRUE)
    {
      localRet = Cpl_LZMAHeaderHandling(argCtx,
                                        inBuf,
                                        &decFinished,
                                        &mustCont
                                       );
    }

    /* If all input data was used by the header decoder, exit. */
    if(locSrcLen == 0U)
    {
      decFinished = TRUE;
    }

    /* The header decoding was completed successfully. */
    if((localRet == CAL_E_OK) &&
       (mustCont == FALSE   )
      )
    {
      destLenPreDec = locDestLen;

      retDec = Cpl_LZMADecodeToDic(argCtx,
                                   &inBuf,
                                   &dest[destIdx],
                                   &locDestLen,
                                   &argCtx->status
                                  );

      destIdx   += destLenPreDec - locDestLen;

      /* If some parts of the Range Decoder code remained unprocessed decrement
       * the srcLen as the last input byte must be read again in the next call.
       */
      if(argCtx->codeLeft == TRUE)
      {
        --inRead;

        ++locSrcLen;

        --argCtx->inAllProcessed;
      }

      /* Check if the output buffer length is not enough. */
      if (argCtx->isSmallBuf == TRUE)
      {
        localRet    = CAL_E_SMALL_BUFFER;
        decFinished = TRUE;
      }

      if (retDec != CPL_DEC_OK)
      {
        decFinished = TRUE;

        localRet    = CAL_E_NOT_OK;
      }

      /* Check if we got to the end of decompression or
         if there is not input data or no output space, exit. */
      if (((CPL_RD_VALIDEND(argCtx->rangeDecoder)   )  &&
           (argCtx->unpackSize             ==     0U)  &&
           (argCtx->isSmallBuf             ==  FALSE)  &&
           (argCtx->isDecodingHeader       ==  FALSE)) ||
          ((locSrcLen  == 0U)  ||  (locDestLen == 0U))
         )
      {
        decFinished = TRUE;
      }
    }
  }

  /* If there is some input data but there is no space available
   * in the output buffer return CAL_E_SMALL_BUFFER. */
  if((locSrcLen  !=       0U) &&
     (locDestLen ==       0U) &&
     (localRet   == CAL_E_OK)
    )
  {
    localRet = CAL_E_SMALL_BUFFER;
  }

  *destLen = initDestLen - locDestLen;
  *srcLen  = inRead;

  return localRet;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMAHeaderHandling]--------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZMAHeaderHandling
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
        uint8                                                               inBuf,
  P2VAR(boolean,                                  AUTOMATIC, CPL_APPL_DATA) decFinished,
  P2VAR(boolean,                                  AUTOMATIC, CPL_APPL_DATA) mustCont
)
{
  Cal_ReturnType localRet = CAL_E_NOT_OK;

  if(argCtx->tempBufSize < (CPL_HEADER_SIZE - 1U))
  {
    localRet = CAL_E_OK;

    /* If the header is not yet decoded fetch bytes
     * until we have CPL_HEADER_SIZE and try to decode it.
     */
    argCtx->tempBuf[argCtx->tempBufSize] = inBuf;

    /* Adjust how much data was read in the header array. */
    ++argCtx->tempBufSize;

    /* New data is needed for header decoding. */
    *mustCont = TRUE;
  }
  else
  {
    localRet = Cpl_LZMADecodeHeader(argCtx,
                                    argCtx->tempBuf
                                   );

    if(localRet != CAL_E_OK)
    {
      *decFinished = TRUE;
    }
    else
    {
      argCtx->isDecodingHeader = FALSE;
    }

    /* Reset the temporary buffer as it's used in other places. */
    TS_MemSet(argCtx->tempBuf, 0U, argCtx->tempBufSize);
    argCtx->tempBufSize = 0U;

    /* All the data we read was used for decoding
     * the header; jump to read of new data.
     */
    *mustCont = TRUE;
  }

  return localRet;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMASmallBufHandling]------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZMASmallBufHandling
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  /* Deviation MISRAC2012-2 */
  P2VAR(P2VAR(uint8, AUTOMATIC, CPL_APPL_DATA),   AUTOMATIC, CPL_APPL_DATA) dest,
  P2VAR(uint32,                                   AUTOMATIC, CPL_APPL_DATA) destLen,
  P2VAR(boolean,                                  AUTOMATIC, CPL_APPL_DATA) decFinished
)
{
  Cal_ReturnType localRet = CAL_E_OK;

  /* If there is old data that wasn't copied because of small buffer, copy it now. */
  if(argCtx->isSmallBuf == TRUE)
  {
    /* If the size of the newly provided buffer is enough for the old data. */
    if(*destLen >= argCtx->sbDataLen)
    {
      /* This branch represents the case where the provided buffer is >= than the data
       * that has to be written. In case the buffer is strictly larger than what we need
       * write the data from previous Update call and try do decompress new data. If it's
       * equal whit the length of the data that needs to be written don't do any new
       * decompression.
       */

      /* Write uncompressed data from previous Update call. */
      Cpl_LZMADictPutOut(argCtx,
                         *dest,
                         argCtx->sbDictPos,
                         argCtx->sbDataLen
                        );

      argCtx->isSmallBuf = FALSE;

      /* We don't have any more space for new decompression. */
      if(*destLen <= argCtx->sbDataLen)
      {
        *decFinished     = TRUE;

        /* Because we don't enter the decoding, as we don't have space, set return value here. */
        localRet         = CAL_E_OK;
      }

      /* There is some space left for the new decompression. */

      /* Update the position in the output buffer after the data written from past decompress. */
      (*dest)   = &(*dest)[argCtx->sbDataLen];

      /* How much space we have available after the past data write. */
      *destLen -= argCtx->sbDataLen;

      /* How much is to be processed from the uncompressed data. */
      argCtx->unpackSize -= argCtx->sbDataLen;

      argCtx->sbDataLen = 0U;
      argCtx->sbDictPos = 0U;
    }
    else if (*destLen != 0U)
    {
      /* This branch represent the case where data larger than the output buffer needs to be written
       * but the output buffer is smaller than what needs to be written.
       * In this case only the buffer length data is written and the position/how much
       * data is to be written is adjusted for the next call of Update.
       * As we don't have any space available for the data from previous
       * Update calls no new input data can be processed.
       */

      *decFinished       = TRUE;
      argCtx->isSmallBuf = TRUE;

      /* Write only the length that was provided and adjust what needs
       * to be written in the next call(how much from sbDataLen).
       */
      Cpl_LZMADictPutOut(argCtx,
                         *dest,
                         argCtx->sbDictPos,
                         *destLen
                        );

      /* How much is to be processed from the uncompressed data. */
      argCtx->unpackSize -= *destLen;

      /* Adjust the sbDataLen whit how much was written in this call. */
      argCtx->sbDataLen -= (uint16)*destLen;

      /* Adjust the dictionary location from which we should
       * copy data for the next call of Update. */
      argCtx->sbDictPos = CPL_LZMA_DICT_MOVE_POS(argCtx->sbDictPos,
                                                 *destLen
                                                );

      /* Because we don't enter the decoding, as we don't have space, set return value here. */
      localRet         = CAL_E_SMALL_BUFFER;

      /* How much available space we have. */
      *destLen = 0U;
    }
    else
    {
      /* If we have data from previous calls and the outputBufLen is 0
       * return with CAL_E_SMALL_BUFFER.
       */
      localRet = CAL_E_SMALL_BUFFER;
    }
  }

  return localRet;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMADecodeReal]------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(LZMA_ReturnType, CPL_CODE) Cpl_LZMADecodeReal
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx
)
{
  uint32          dist     = 0U;
  uint32          posState = 0U;
  uint32          idx      = 0U;
  uint16          len      = 0U;
  boolean         isMatch  = TRUE;
  LZMA_ReturnType localRet = CPL_DEC_OK;

/* Type of packets
* -----------------------------------------------------------------------------------------------
* |       Packet     | Type        |               Description            |  Length(in bits)    |
* |-----------------------------------------------------------------------|---------------------|
* | 0 + byteCode     | LIT         | Single byte(usually an ASCII code)   |       9             |
* | 1+0 + len + dist | MATCH       | Pair of (distance, length)           |  2 + [3:8] + [7:11] |
* | 1+1+0+0          | SHORTREP    | One byte repeat at last distance     |       4             |
* | 1+1+0+1 + len    | LONGREP[0]  | Distance = last distance used        |    4 + [3:8]        |
* | 1+1+1+0 + len    | LONGREP[1]  | Distance = second last distance used |    4 + [3:8]        |
* | 1+1+1+1+0 + len  | LONGREP[2]  | Distance = third last distance used  |    5 + [3:8]        |
* | 1+1+1+1+1 + len  | LONGREP[3]  | Distance = fourth last distance used |    5 + [3:8]        |
* -----------------------------------------------------------------------------------------------
*/

  /* Prepare the index for the state/packet type decoding. */
  posState = argCtx->processedPos & ((uint32)((uint32)1U << argCtx->cfgPtr->pb) - 1U);
  idx      = (uint8)((uint8)(argCtx->decodeState << CPL_MAX_POS_BITS) + posState);

  if(Cpl_LZMARangeDecoderDecodeBit(argCtx,
                                   &argCtx->rangeDecoder,
                                   &argCtx->isMatch[idx],
                                   &argCtx->buf,
                                   TRUE
                                  ) == 0U
    )
  {
    /* [0b + literal] We have a LIT packet. */
    Cpl_LZMADecodeLiteral(argCtx,
                          &argCtx->rangeDecoder,
                          &argCtx->buf,
                          argCtx->dictionary.dict,
                          &argCtx->dictionary.pos,
                          &argCtx->processedPos,
                          argCtx->decodeState,
                          TRUE
                         );

    CPL_LZMA_UPDATE_LIT_STATE;

    isMatch = FALSE;
  }
  /* [1b + ...] Start decoding all MATCH, SHORTREP, LONGREP[*] packets. */
  else if(Cpl_LZMARangeDecoderDecodeBit(argCtx,
                                        &argCtx->rangeDecoder,
                                        &argCtx->isRep[argCtx->decodeState],
                                        &argCtx->buf,
                                        TRUE
                                       ) == 1U
        )
  {
    /* If the dictionary is empty and we have some matches. */
    if (argCtx->processedPos == 0U)
    {
      localRet = CPL_DEC_NOT_OK;
    }
    else
    {
      if(Cpl_LZMARangeDecoderDecodeBit(argCtx,
                                       &argCtx->rangeDecoder,
                                       &argCtx->isRepG0[argCtx->decodeState],
                                       &argCtx->buf,
                                       TRUE
                                      ) == 0U
             )
      {

        idx  = (uint32)(argCtx->decodeState) << (uint32)(CPL_MAX_POS_BITS);
        idx += posState;

        if(Cpl_LZMARangeDecoderDecodeBit(argCtx,
                                         &argCtx->rangeDecoder,
                                         &argCtx->isRep0Long[idx],
                                         &argCtx->buf,
                                         TRUE
                                        ) == 0U
          )
        {
          /* [1100b] We have a SHORTREP packet. */
          CPL_LZMA_UPDATE_SREP_STATE;

          CPL_LZMA_DICT_PUT_BYTE(CPL_LZMA_DICT_GET_BYTE(argCtx->dictionary.dict,
                                                        argCtx->dictionary.pos,
                                                        argCtx->rep0
                                                       )
                                   );
          isMatch = FALSE;
        }
      }
      else
      {
        if(Cpl_LZMARangeDecoderDecodeBit(argCtx,
                                         &argCtx->rangeDecoder,
                                         &argCtx->isRepG1[argCtx->decodeState],
                                         &argCtx->buf,
                                         TRUE
                                        ) == 0U
          )
        {
          /* [1110b] We have a LONGREP[1] packet. */
          dist = argCtx->rep1;
        }
        else
        {
          if(Cpl_LZMARangeDecoderDecodeBit(argCtx,
                                           &argCtx->rangeDecoder,
                                           &argCtx->isRepG2[argCtx->decodeState],
                                           &argCtx->buf,
                                           TRUE
                                          ) == 0U
            )
          {
            /* [11110b] We have a LONGREP[2] packet. */
            dist = argCtx->rep2;
          }
          else
          {
            /* [11111b] We have a LONGREP[3] packet. */
            dist         = argCtx->rep3;
            argCtx->rep3 = argCtx->rep2;
          }
          argCtx->rep2   = argCtx->rep1;
        }
        argCtx->rep1     = argCtx->rep0;
        argCtx->rep0     = dist;
      }
    }

    if ((localRet == CPL_DEC_OK) &&
        (isMatch  == TRUE      )
       )
    {
      /* Decode the length for LONGREP[*]. The length can be maximum 273. */
      len = Cpl_LZMALenDecode(argCtx,
                              &argCtx->rangeDecoder,
                              posState,
                              &(argCtx->repLenDec),
                              &argCtx->buf,
                              TRUE
                             );

      CPL_LZMA_UPDATE_REP_STATE;
    }
  }
  else
  {
    /* [10b + len + dist] We have a MATCH packet. */
    argCtx->rep3 = argCtx->rep2;
    argCtx->rep2 = argCtx->rep1;
    argCtx->rep1 = argCtx->rep0;
    len  = Cpl_LZMALenDecode(argCtx,
                             &argCtx->rangeDecoder,
                             posState,
                             &(argCtx->lenDec),
                             &argCtx->buf,
                             TRUE
                            );

    CPL_LZMA_UPDATE_MATCH_STATE;

    dist  = Cpl_LZMADistDecode(argCtx,
                               &argCtx->rangeDecoder,
                               len,
                               &argCtx->buf,
                               TRUE
                              );
    argCtx->rep0  = dist + 1U;

    /* The refereed distance is greater than the data in the dictionary. */
    if(dist >= argCtx->processedPos)
    {
      localRet = CPL_DEC_NOT_OK;
    }
  }

  if ((localRet == CPL_DEC_OK) &&
      (isMatch  == TRUE      )
     )
  {
    /* Normalize the length. */
    len += CPL_DIST_MATCH_MIN_LEN;

    /* Add to the dictionary the match formed by the (rep0, len) pair. */
    Cpl_LZMADictPutMatch(argCtx,
                         argCtx->rep0,
                         len
                        );
  }

  return localRet;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMADummyDecode]-----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(LZMA_DummyType, CPL_CODE) Cpl_LZMADummyDecode
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                                  AUTOMATIC, CPL_APPL_DATA) inputBuf
)
{
  P2VAR(CProbType,     AUTOMATIC, CPL_APPL_DATA) prob;
  LZMA_RangeDecoderType                          RDStatusDummy;
  uint32                                         posState       = 0U;
  uint32                                         idx            = 0U;
  uint32                                         dictPos        = argCtx->dictionary.pos;
  uint32                                         processedPos   = argCtx->processedPos;
  uint16                                         len            = 0U;
  uint8                                          decodeState    = argCtx->decodeState;
  boolean                                        isProcessed    = FALSE;
  LZMA_DummyType                                 localRet;

  RDStatusDummy.Code  = argCtx->rangeDecoder.Code;
  RDStatusDummy.Range = argCtx->rangeDecoder.Range;

/* Type of packets
* -----------------------------------------------------------------------------------------------
* |       Packet     | Type        |               Description            |  Length(in bits)    |
* |-----------------------------------------------------------------------|---------------------|
* | 0 + byteCode     | LIT         | Single byte(usually an ASCII code)   |       9             |
* | 1+0 + len + dist | MATCH       | Pair of (distance, length)           |  2 + [3:8] + [7:11] |
* | 1+1+0+0          | SHORTREP    | One byte repeat at last distance     |       4             |
* | 1+1+0+1 + len    | LONGREP[0]  | Distance = last distance used        |    4 + [3:8]        |
* | 1+1+1+0 + len    | LONGREP[1]  | Distance = second last distance used |    4 + [3:8]        |
* | 1+1+1+1+0 + len  | LONGREP[2]  | Distance = third last distance used  |    5 + [3:8]        |
* | 1+1+1+1+1 + len  | LONGREP[3]  | Distance = fourth last distance used |    5 + [3:8]        |
* -----------------------------------------------------------------------------------------------
*/

  /* Prepare the index for the state/packet type decoding. */
  posState = (processedPos) & ((uint32)((uint32)1U << argCtx->cfgPtr->pb) - 1U);
  idx      = (uint8)((uint8)(decodeState << CPL_MAX_POS_BITS) + posState);
  prob     = &(argCtx->isMatch[idx]);

  if(Cpl_LZMARangeDecoderDecodeBit(argCtx,
                                   &RDStatusDummy,
                                   prob,
                                   &inputBuf,
                                   FALSE
                                  ) == 0U
    )
  {
    /* [0b + literal] We have a LIT packet. */
    Cpl_LZMADecodeLiteral(argCtx,
                          &RDStatusDummy,
                          &inputBuf,
                          argCtx->dictionary.dict,
                          &dictPos,
                          &processedPos,
                          decodeState,
                          FALSE
                         );

    localRet = CPL_DUMMY_LIT;
  }
  else
  {
    /* [1b + ...] Start decoding all MATCH, SHORTREP, LONGREP[*] packets. */
    prob = &(argCtx->isRep[decodeState]);

    if(Cpl_LZMARangeDecoderDecodeBit(argCtx,
                                     &RDStatusDummy,
                                     prob,
                                     &inputBuf,
                                     FALSE
                                    ) != 0U
      )
    {
      /* [11] */
      prob = &(argCtx->isRepG0[decodeState]);

      if(Cpl_LZMARangeDecoderDecodeBit(argCtx,
                                       &RDStatusDummy,
                                       prob,
                                       &inputBuf,
                                       FALSE
                                      ) == 0U
        )
      {

        /* This corresponds for both SHORTREP and LONGREP[0]. */
        localRet = CPL_DUMMY_REP;

        /* [110] */
        idx  = (uint32)((uint32)((uint32)decodeState << CPL_MAX_POS_BITS) + posState);
        prob = &(argCtx->isRep0Long[idx]);

        if(Cpl_LZMARangeDecoderDecodeBit(argCtx,
                                         &RDStatusDummy,
                                         prob,
                                         &inputBuf,
                                         FALSE
                                        ) == 0U
          )
        {
          /* [1100] SHORTREP */
          isProcessed = TRUE;
        }
      }
      else
      {
        localRet = CPL_DUMMY_REP;
        prob     = &(argCtx->isRepG1[decodeState]);

        if(Cpl_LZMARangeDecoderDecodeBit(argCtx,
                                         &RDStatusDummy,
                                         prob,
                                         &inputBuf,
                                         FALSE
                                        ) == 1U
          )
        {
          prob = &(argCtx->isRepG2[decodeState]);

          /* Either 0 or 1 corespond to a LONGREP packet;
           * we can ignore the return value. */
          (void)Cpl_LZMARangeDecoderDecodeBit(argCtx,
                                              &RDStatusDummy,
                                              prob,
                                              &inputBuf,
                                              FALSE
                                             );
        }
      }

      if (isProcessed == FALSE)
      {
        /* Decode the length for LONGREP[*]. */
        len = Cpl_LZMALenDecode(argCtx,
                                &RDStatusDummy,
                                posState,
                                &(argCtx->repLenDec),
                                &inputBuf,
                                FALSE
                               );

      }
    }
    else
    {
      /* [10b + len + dist] We have a MATCH packet. */
      len = Cpl_LZMALenDecode(argCtx,
                              &RDStatusDummy,
                              posState,
                              &(argCtx->lenDec),
                              &inputBuf,
                              FALSE
                             );

      /* The return value is ignored as we don't care about the coded distance;
       * What is of interest is that we have enough data to decode the distance.
       */
      (void)Cpl_LZMADistDecode(argCtx,
                               &RDStatusDummy,
                               len,
                               &inputBuf,
                               FALSE
                              );

      localRet = CPL_DUMMY_MATCH;
    }
  }

  /* Check if the input buffer boundary was exceded after the last run of the Range Decoder */
  if(inputBuf > argCtx->bufLimit)
  {
    localRet = CPL_DUMMY_ERROR;
  }

  return localRet;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMADecodeToDic]-----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(LZMA_ReturnType, CPL_CODE) Cpl_LZMADecodeToDic
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2CONST(uint8,                                  AUTOMATIC, CPL_APPL_DATA) src,
  P2VAR(uint8,                                    AUTOMATIC, CPL_APPL_DATA) dest,
  P2VAR(uint32,                                   AUTOMATIC, CPL_APPL_DATA) destLen,
  P2VAR(LZMA_StatusType,                          AUTOMATIC, CPL_APPL_DATA) status
)
{
  uint32          inSize      = 1U;
  uint32          processed   = 0U;
  uint32          rem;
  uint32          lookAhead;
  uint16          writtenData = 0U;
  LZMA_DummyType  dummyRes;
  LZMA_ReturnType localRet    = CPL_DEC_OK;
  boolean         isProcessed = FALSE;

  *status = CPL_LZMA_STATUS_NOT_SPECIFIED;

  argCtx->codeLeft = FALSE;

  argCtx->dictionary.posBeforeDec = argCtx->dictionary.pos;

  /* While there is data larger than the largest packet size. */
  while((localRet    == CPL_DEC_OK) &&
        (isProcessed == FALSE     )
       )
  {
    isProcessed = FALSE;

     /* Read the first uint32 of compressed data(the Range Decoder code). */
    if(argCtx->needFlush == TRUE)
    {
      argCtx->tempBuf[argCtx->tempBufSize] = *src;

      argCtx->tempBufSize++;

      /* After reading the first code we don't have any more data, exit. */
      isProcessed = TRUE;

      /* There is no sufficient data to build the code. */
      if (argCtx->tempBufSize <= CPL_RD_CODE_SIZE)
      {
        *status  = CPL_LZMA_STATUS_NEEDS_MORE_INPUT;
        localRet = CPL_DEC_OK;
      }
      else if (argCtx->tempBuf[0U] != 0U)
      {
        /* First byte of the compressed data cannot be 0. */
        localRet = CPL_DEC_NOT_OK;
      }
      else
      {
        argCtx->rangeDecoder.Code = ((uint32)argCtx->tempBuf[1U] << 24U)
                                  | ((uint32)argCtx->tempBuf[2U] << 16U)
                                  | ((uint32)argCtx->tempBuf[3U] << 8U )
                                  | ((uint32)argCtx->tempBuf[4U]);

        argCtx->rangeDecoder.Range = 0xFFFFFFFFU;
        argCtx->needFlush          = FALSE;
        argCtx->tempBufSize        = 0U;
      }
    }
    else
    {
      /* If there is no chunks left from previous buffers. */
      if (argCtx->tempBufSize == 0U)
      {
        /* Set the upper limit of the input data. */
        argCtx->bufLimit = &src[inSize];

        /* Check if we can decode some type of packet from the data chunk. */
        dummyRes = Cpl_LZMADummyDecode(argCtx,
                                       src
                                      );

        if (dummyRes == CPL_DUMMY_ERROR)
        {
          /* Save data chunk for the next decompression. */
          TS_MemCpy(argCtx->tempBuf, src, inSize);

          argCtx->tempBufSize = inSize;
          *status             = CPL_LZMA_STATUS_NEEDS_MORE_INPUT;
          isProcessed         = TRUE;
          localRet            = CPL_DEC_OK;
        }
        else
        {
          /*  We found sufficient data to decode a packet.
           *  In this case the the decoding
           *  will happen for one symbol.
           */
          argCtx->buf = src;

          /* Try to decode the data. */
          localRet = Cpl_LZMADecodeReal(argCtx);

          if(localRet == CPL_DEC_OK)
          {
            /* Update how much input data was processed. */
            processed = 0U;

            while((argCtx->buf) != (&(src[processed])))
            {
              processed++;
            }

            /* Adjust how much input data is to be processed. */
            inSize    -= processed;

            writtenData = Cpl_LZMAWriteOutput(argCtx,
                                              dest,
                                              destLen,
                                              &isProcessed
                                             );

            /* Adjust the pointer to point to end of output data. */
            dest        = &dest[writtenData];

            if ((inSize != 0U) && (*destLen == 0U))
            {
              argCtx->codeLeft = TRUE;
            }

          }
          else
          {
            /* E_NOT_OK returned, exit. */
            isProcessed = TRUE;
          }
        } /* End of error checking. */
      }
      /* Some chunks form the previous data are to be processed. */
      else
      {
        /* How much data remained from the previous buffer decoding. */
        rem       = argCtx->tempBufSize;
        lookAhead = 0U;

        /*  Merge data from previous buffer with data from current buffer
         *  in order to have sufficient data to decode the longest package.
         */
        while ((rem       < CPL_REQUIRED_INPUT_MAX) &&
               (lookAhead < inSize                )
              )
        {
          argCtx->tempBuf[rem] = src[lookAhead];
          rem++;
          lookAhead++;
        }

        /* Adjust the length of merged data. */
        argCtx->tempBufSize = rem;

        /* Set the upper limit of the input data. */
        argCtx->bufLimit = &argCtx->tempBuf[rem];

        /*  If there might be insufficient data for one packet try to decode it.
         *  This check is done again as the inSize above can
         *  be lower than what is needed for one packet.
         */
        /* Check if we can decode some type of packet from the data chunk. */
        dummyRes = Cpl_LZMADummyDecode(argCtx,
                                       argCtx->tempBuf
                                      );

        if (dummyRes == CPL_DUMMY_ERROR)
        {
          *status      = CPL_LZMA_STATUS_NEEDS_MORE_INPUT;
          isProcessed  = TRUE;
          localRet     = CPL_DEC_OK;
        }
        else
        {
          /* Try to run the decoding on the merged buffer. */
          argCtx->buf = argCtx->tempBuf;

          /* The decoding is happening only on one byte of input data as only for
           * that one the dummy decoding was ran. If the decoding will be done
           * up to tempBuf[tempBufSize] the algorithm might end up reading wrong
           * data after the tempBuf[tempBufSize] position.
           **/
          localRet = Cpl_LZMADecodeReal(argCtx);

          if(localRet == CPL_DEC_OK)
          {
            /* If there is not enough data to process. */
            processed = 0U;

            while((argCtx->buf) != (&(argCtx->tempBuf[processed])))
            {
              processed++;
            }

            /* Remaining data in the tempBuf. */
            rem       -= processed;

            /* Remaining data from the inBuf read in this iteration. */
            lookAhead -= rem;

            /* Adjust how much is to be read form the new input data. */
            inSize    -= lookAhead;

            argCtx->tempBufSize = 0U;

            writtenData = Cpl_LZMAWriteOutput(argCtx,
                                              dest,
                                              destLen,
                                              &isProcessed
                                             );

            /* Adjust the pointer to point to end of output data. */
            dest = &dest[writtenData];

            /* With the current test vectors the below branch is unreachable.
             * It's nearly impossible to craft a test vector and a test sequence
             * that will cover it. Nevertheless this check is necessary as there
             * might be cases where Range Decoder code corresponding to the
             * input byte is not entirely processed.
             */
            /*CHECK: NOPARSE */
            if ((inSize   != 0U) &&
                (*destLen == 0U)
               )
            {
              argCtx->codeLeft = TRUE;
            }
            /*CHECK: PARSE */
          }
          else
          {
            /* E_NOT_OK was returned, exit in flames. */
            isProcessed = TRUE;
          }
        }
      }
    }

  }

  return localRet;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMALenDecInit]------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, CPL_CODE) Cpl_LZMALenDecInit
(
  P2VAR(LZMA_LenDecType,                          AUTOMATIC, CPL_APPL_DATA) LD
)
{
  uint8 i = 0U;

  LD->C1 = CPL_PROB_INIT_VAL;
  LD->C2 = CPL_PROB_INIT_VAL;

  /* Initialize probs for High Decoder. */
  CPL_LZMA_INIT_PROBS(LD->HighDec.ProbsHigh, CPL_HIGHCODER_NUM_SYMBOLS);

  for (i = 0; i < (uint8)(1U << CPL_MAX_POS_BITS); i++)
  {
    /* Initialize probs for Low Decoder. */
    CPL_LZMA_INIT_PROBS(LD->LowDec[i].ProbsLow, CPL_LOWCODER_NUM_SYMBOLS);

    /* Initialize probs for Middle Decoder. */
    CPL_LZMA_INIT_PROBS(LD->MidDec[i].ProbsMid, CPL_MIDCODER_NUM_SYMBOLS);
  }
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMALenDecode]-------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(uint16, CPL_CODE) Cpl_LZMALenDecode
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(LZMA_RangeDecoderType,                    AUTOMATIC, CPL_APPL_DATA) rangeDecoder,
        uint32                                                              posState,
  P2VAR(LZMA_LenDecType,                          AUTOMATIC, CPL_APPL_DATA) LD,
  /* Deviation MISRAC2012-2 */
  P2VAR(P2CONST(uint8, AUTOMATIC, CPL_APPL_DATA), AUTOMATIC, CPL_APPL_DATA) inputBuf,
        boolean                                                             doUpdateContext
)
{
  uint16 retVal = 0U;

  if(Cpl_LZMARangeDecoderDecodeBit(argCtx,
                                   rangeDecoder,
                                   &LD->C1,
                                   inputBuf,
                                   doUpdateContext
                                  ) == 0U
    )
  {
    /* The length code starts with 0: we have 3 bits for the
     * effective length which should be in the [2 - 9] range.
     */
    retVal = Cpl_LZMABitTreeDecoderDirect(argCtx,
                                          rangeDecoder,
                                          CPL_LOWCODER_LEN,
                                          LD->LowDec[posState].ProbsLow,
                                          inputBuf,
                                          doUpdateContext
                                         );
  }
  else if(Cpl_LZMARangeDecoderDecodeBit(argCtx,
                                        rangeDecoder,
                                        &LD->C2,
                                        inputBuf,
                                        doUpdateContext
                                       ) == 0U
        )
  {
    /* The length code starts with 1: we have 3 bits for the
     * effective length which should be in the [10 - 17] range.
     */
    retVal = 8U + Cpl_LZMABitTreeDecoderDirect(argCtx,
                                               rangeDecoder,
                                               CPL_MIDCODER_LEN,
                                               LD->MidDec[posState].ProbsMid,
                                               inputBuf,
                                               doUpdateContext
                                              );
  }
  else
  {
    /* The length code is 11: we have 8 bits for the
     * effective length which should be in the [18 - 273] range.
     */
    retVal = 16U + Cpl_LZMABitTreeDecoderDirect(argCtx,
                                                rangeDecoder,
                                                CPL_HIGHCODER_LEN,
                                                LD->HighDec.ProbsHigh,
                                                inputBuf,
                                                doUpdateContext
                                               );
  }

  return retVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMADistDecInit]-----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, CPL_CODE) Cpl_LZMADistDecInit
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx
)
{
  uint8 i = 0U;

  for (i = 0U; i < CPL_MAX_POS_BITS; i++)
  {
    /* Init probs for Slot Decoder. */
    CPL_LZMA_INIT_PROBS(argCtx->posSlotDec[i].Probs,
                        CPL_PSIZE(CPL_DIST_SLOT)
                       );
  }

  /* Init probs for Align Decoder. */
  CPL_LZMA_INIT_PROBS(argCtx->algnDec.Probs,
                      CPL_PSIZE(CPL_DIST_ALIGN_BITS)
                     );

  /* Init probs for Distance Decoder. */
  CPL_LZMA_INIT_PROBS(argCtx->posDecoders,
                      (uint16)((uint16)1U + (CPL_LZMA_FULL_DIST - CPL_DIST_MODEL_END))
                     );
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMADistDecode]------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(uint32, CPL_CODE) Cpl_LZMADistDecode
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(LZMA_RangeDecoderType,                    AUTOMATIC, CPL_APPL_DATA) rangeDecoder,
        uint16                                                              len,
  /* Deviation MISRAC2012-2 */
  P2VAR(P2CONST(uint8, AUTOMATIC, CPL_APPL_DATA), AUTOMATIC, CPL_APPL_DATA) inputBuf,
        boolean                                                             doUpdateContext
)
{
  P2VAR(CProbType, AUTOMATIC, CPL_APPL_DATA) tempArg;
        uint32                               retDist;
        uint32                               dist;
        uint32                               numDirectBits;
        uint16                               lenState = len;
        uint16                               posSlot;

  if (lenState > (CPL_MAX_POS_BITS - 1U))
  {
    lenState = CPL_MAX_POS_BITS - 1U;
  }

  /* Get the distance slot. */
  posSlot = Cpl_LZMABitTreeDecoderDirect(argCtx,
                                         rangeDecoder,
                                         CPL_DIST_SLOT,
                                         argCtx->posSlotDec[lenState].Probs,
                                         inputBuf,
                                         doUpdateContext
                                        );

  /* First 3 distance slots are encoded with no context bits; they represent the 0 - 3 distances. */
  if(posSlot < CPL_DIST_MODEL_START)
  {
    retDist = posSlot;
  }
  else
  {
    numDirectBits = ((uint32)((uint32)posSlot >> 1U) - 1U);
    dist = (uint32)((uint32)((uint32)2U | (uint32)(posSlot & (uint32)1U)) << numDirectBits);

    if(posSlot < CPL_DIST_MODEL_END)
    {
      tempArg = &(argCtx->posDecoders[dist - posSlot]);
      dist   += Cpl_LZMABitTreeReverseDecode(argCtx,
                                             rangeDecoder,
                                             tempArg,
                                             (uint8)numDirectBits,
                                             inputBuf,
                                             doUpdateContext
                                            );
    }
    else
    {
      dist += Cpl_LZMARangeDecoderGetDirectBits(argCtx,
                                                rangeDecoder,
                                                (numDirectBits - CPL_DIST_ALIGN_BITS),
                                                inputBuf
                                               ) << CPL_DIST_ALIGN_BITS;

      dist += Cpl_LZMABitTreeReverseDecode(argCtx,
                                           rangeDecoder,
                                           argCtx->algnDec.Probs,
                                           CPL_DIST_ALIGN_BITS,
                                           inputBuf,
                                           doUpdateContext
                                          );
    }
    retDist = dist;
  }

  return retDist;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMAInit]------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, CPL_CODE) Cpl_LZMAInit
(
  P2CONST(Cpl_LZMADecompressConfigType,           AUTOMATIC, CPL_APPL_DATA) argCfg,
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx
)
{
  TS_MemSet(argCtx, 0U, sizeof(Cpl_LZMADecompressCtxBufType));

  argCtx->cfgPtr           = argCfg;
  argCtx->initState        = CPL_LZMA_STAT_INITIALIZED;
  argCtx->isSmallBuf       = FALSE;
  argCtx->codeLeft         = FALSE;
  argCtx->needFlush        = TRUE;
  argCtx->isDecodingHeader = TRUE;
  argCtx->inAllProcessed   = 0U;
  argCtx->rep0             = 1U;
  argCtx->rep1             = 1U;
  argCtx->rep2             = 1U;
  argCtx->rep3             = 1U;
  argCtx->dictionary.pos   = 0U;
  argCtx->processedPos     = 0U;

  /* Init probabilities tables. */
  CPL_LZMA_INIT_PROBS(argCtx->isMatch,    ((uint16)((uint16)(CPL_NUM_STATES) << CPL_MAX_POS_BITS)));
  CPL_LZMA_INIT_PROBS(argCtx->isRep,      (uint16)CPL_NUM_STATES);
  CPL_LZMA_INIT_PROBS(argCtx->isRepG0,    (uint16)CPL_NUM_STATES);
  CPL_LZMA_INIT_PROBS(argCtx->isRepG1,    (uint16)CPL_NUM_STATES);
  CPL_LZMA_INIT_PROBS(argCtx->isRepG2,    (uint16)CPL_NUM_STATES);
  CPL_LZMA_INIT_PROBS(argCtx->isRep0Long, ((uint16)((uint16)CPL_NUM_STATES << CPL_MAX_POS_BITS)));
  CPL_LZMA_INIT_PROBS(argCtx->litProbs,
              ((uint16)((uint16)CPL_LIT_DECODER_SIZE << (argCtx->cfgPtr->lc + argCtx->cfgPtr->lp)))
                     );

  Cpl_LZMALenDecInit(&(argCtx->lenDec));
  Cpl_LZMALenDecInit(&(argCtx->repLenDec));
  Cpl_LZMADistDecInit(argCtx);

}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMADecompressEnd]---------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(Cal_ReturnType, CPL_CODE) Cpl_LZMADecompressEnd
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx
)
{
  /* ~~~ declare local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  Cal_ReturnType locRetVal;

  /* ~~~ initialize local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  locRetVal = CAL_E_NOT_OK;

  /* ~~~ run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  if ((CPL_RD_VALIDEND(argCtx->rangeDecoder)    ) &&
      (argCtx->unpackSize              ==     0U) &&
      (argCtx->isSmallBuf              ==  FALSE) &&
      (argCtx->isDecodingHeader        ==  FALSE)
     )
  {
    locRetVal = CAL_E_OK;
  }

  argCtx->initState = CPL_LZMA_STAT_IDLE;

  return locRetVal;
}


/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMADictPutMatch]----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, CPL_CODE) Cpl_LZMADictPutMatch
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
        uint32                                                              dist,
        uint16                                                              len
)
{
  P2VAR(uint8, AUTOMATIC, CPL_APPL_DATA) dst;
        uint16                           i = 0U;

  /* Copy byte-wise within the dictionary */
  for (i = 0U; i < len; ++i)
  {
    dst  = &argCtx->dictionary.dict[argCtx->dictionary.pos];
    *dst = CPL_LZMA_DICT_GET_BYTE(argCtx->dictionary.dict,
                                  argCtx->dictionary.pos,
                                  dist
                                 );
    argCtx->dictionary.pos = CPL_LZMA_DICT_MOVE_POS(argCtx->dictionary.pos,
                                                    1U
                                                   );
    ++argCtx->processedPos;
  }
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMADictPutOut]------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, CPL_CODE) Cpl_LZMADictPutOut
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                                    AUTOMATIC, CPL_APPL_DATA) outBuf,
        uint32                                                              dictPos,
        uint32                                                              len
)
{
  uint16 i          = 0U;
  uint32 lenTillEnd = 0U;

  /* If the dictionary position + what needs to be fetched
   * is more than the upper limit of the dictionary. */
  if ((dictPos + len) > argCtx->cfgPtr->dictSize)
  {
    /* Calculate how much space we have up to the dictionary end. */
    lenTillEnd = argCtx->cfgPtr->dictSize - dictPos;

    /* Copy the data up to the dictionary end. */
    for (i = 0; i < lenTillEnd; ++i)
    {
      *outBuf = argCtx->dictionary.dict[dictPos + i];
      outBuf  = &outBuf[1U];
    }

    /* Copy the rest of data from the dictionary beginning. */
    for (i = 0; i < (len - lenTillEnd); ++i)
    {
      *outBuf = argCtx->dictionary.dict[i];
      outBuf  = &outBuf[1U];
    }
  }
  else
  {
    /* If the data to be fetched do not exceed the dictionary limit. */
    for (i = 0; i < len; ++i)
    {
      *outBuf = argCtx->dictionary.dict[dictPos + i];
      outBuf  = &outBuf[1U];
    }
  }

  /* Adjust the position before this decoding with what we've processed
   * in this write to out buffer. This way we increase the available space
   * in the dictionary as the len bytes are no longer needed in the dicit. */
  argCtx->dictionary.posBeforeDec = CPL_LZMA_DICT_MOVE_POS(dictPos,
                                                           len
                                                          );
}


/*------------------------------------------------------------------------------------------------*/
/*----[Cpl_LZMAWriteOutput]-----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
STATIC FUNC(uint16, CPL_CODE) Cpl_LZMAWriteOutput
(
  P2VAR(Cpl_LZMADecompressCtxBufType,             AUTOMATIC, CPL_APPL_DATA) argCtx,
  P2VAR(uint8,                                    AUTOMATIC, CPL_APPL_DATA) dest,
  P2VAR(uint32,                                   AUTOMATIC, CPL_APPL_DATA) destLen,
  P2VAR(boolean,                                  AUTOMATIC, CPL_APPL_DATA) isProcessed
)
{

  uint16 outSizeCur  = 0U;
  uint16 writtenData = 0U;

  /* Adjust how far we are in the dictionary. */
  CPL_LZMA_DICT_GET_SIZE_NEW_DATA(outSizeCur);

  /* Write data only if there is enough space in the
   * output buffer provided by the Update call.
   */
  if ((outSizeCur <= *destLen) &&
      (outSizeCur !=       0U)
     )
  {
    /* Write uncompressed data. */
    Cpl_LZMADictPutOut(argCtx,
                       dest,
                       argCtx->dictionary.posBeforeDec,
                       outSizeCur
                      );

    /* How much data we've written. */
    writtenData = outSizeCur;

    /* Adjust the length of processed data. */
    *destLen   -= outSizeCur;

    /* How much is to be processed from the uncompressed data. */
    argCtx->unpackSize -= outSizeCur;

    /* If what we've write is equal with the remaining space, exit. */
    if (*destLen == 0U)
    {
      *isProcessed = TRUE;
    }
  }
  else
  {
    /* If there is out data and some, smaller than needed,
     * space write part of out data. */

    argCtx->isSmallBuf = TRUE;
    *isProcessed       = TRUE;

    /* Write only uncompressed data that fit in the provided buffer. */
    Cpl_LZMADictPutOut(argCtx,
                       dest,
                       argCtx->dictionary.posBeforeDec,
                       (uint16)*destLen
                      );

    /* How much data we've written. */
    writtenData = (uint16)*destLen;

    /* How much data is to be written in the output buf. */
    argCtx->sbDataLen   = outSizeCur - (uint16)*destLen;

    /* Position in the dictionary from which the data will be copied. */
    argCtx->sbDictPos   = argCtx->dictionary.posBeforeDec;

    /* How much is to be processed from the uncompressed data. */
    argCtx->unpackSize -= *destLen;

    /* Adjust the length of processed data. */
    *destLen            = 0U;
  }

  /* Check if we got to the end of decompression. */
  if ((CPL_RD_VALIDEND(argCtx->rangeDecoder)    ) &&
      (argCtx->unpackSize              ==     0U) &&
      (argCtx->isSmallBuf              ==  FALSE) &&
      (argCtx->isDecodingHeader        ==  FALSE)
     )
  {
    *isProcessed = TRUE;
  }

  return writtenData;
}

#define CPL_STOP_SEC_CODE
#include "MemMap.h"

/*==================[internal function definitions]===============================================*/

/*================================================================================================*/

#else /* #if (CPL_LZMADECOMPRESS_ENABLED == STD_ON) */

/** \brief  Dummy definition preventing this file from being empty, if there is no primitive
 **         configuration.
 **/
typedef void Cpl_LzmaDecompress_PrvntEmptyTranslationUnit_t;

#endif /* #if (CPL_LZMADECOMPRESS_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/
