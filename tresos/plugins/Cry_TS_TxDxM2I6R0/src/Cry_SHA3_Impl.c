/* --------{ EB Automotive C Source File }-------- */
/* !LINKSTO EB_CRY_0004,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm_Hash.h>
#include <Csm.h>

#include <Cry_SHA3.h>
#include <Cry_Common.h>
#include <Cry_SHA3_Internal.h>

#include <TSMem.h>

#if (CRY_SHA3_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

#if (defined CRY_SHA3_ROUNDS)
#error CRY_SHA3_ROUNDS is already defined
#endif
/**
 * \brief Number of rounds of SHA3 permutation
 */
#define CRY_SHA3_ROUNDS                                 24U

#if (defined CRY_SHA3_LANES)
#error CRY_SHA3_LANES is already defined
#endif
/**
 * \brief Number of lanes in one SHA3 state
 */
#define CRY_SHA3_LANES                                  25U

#if (defined CRY_SHA3_LANE_SIZE_IN_BYTES)
#error CRY_SHA3_LANE_SIZE_IN_BYTES is already defined
#endif
/**
 * \brief Number of bytes in one lane
 */
#define CRY_SHA3_LANE_SIZE_IN_BYTES                     8U

#if (defined CRY_SHA3_LANE_LAST_BYTE_INDEX)
#error CRY_SHA3_LANE_LAST_BYTE_INDEX is already defined
#endif
/**
 * \brief Index of the last byte in one lane
 */
#define CRY_SHA3_LANE_LAST_BYTE_INDEX                   7U

#if (defined CRY_SHA3_STATE_MAX_X_DIMENSION)
#error CRY_SHA3_STATE_MAX_X_DIMENSION is already defined
#endif
/**
 * \brief Max dimension of the state in x
 */
#define CRY_SHA3_STATE_MAX_X_DIMENSION                  5U

#if (defined CRY_SHA3_STATE_MAX_Y_DIMENSION)
#error CRY_SHA3_STATE_MAX_Y_DIMENSION is already defined
#endif
/**
 * \brief Max dimension of the state in y
 */
#define CRY_SHA3_STATE_MAX_Y_DIMENSION                  5U

#if (defined CRY_SHA3_STATE_ONE_LANE_IN_32BITS_WORDS)
#error CRY_SHA3_STATE_ONE_LANE_IN_32BITS_WORDS is already defined
#endif
/**
 * \brief Max size of a lane in 32bits words
 */
#define CRY_SHA3_STATE_ONE_LANE_IN_32BITS_WORDS         2U

#if (defined CRY_SHA3_STATE_SUFFIX_PLUS_FIRST_PADDING_BIT)
#error CRY_SHA3_STATE_SUFFIX_PLUS_FIRST_PADDING_BIT is already defined
#endif
/**
 * \brief Byte that combines the suffix and the first padding bit
 */
#define CRY_SHA3_STATE_SUFFIX_PLUS_FIRST_PADDING_BIT    ((uint8)6U)

#if (defined CRY_SHA3_STATE_LAST_PADDING_BIT)
#error CRY_SHA3_STATE_LAST_PADDING_BIT is already defined
#endif
/**
 * \brief Byte containing the last padding bit
 */
#define CRY_SHA3_STATE_LAST_PADDING_BIT                 ((uint8)0x80U)

#if (defined CRY_SHA3_GET_BASE_INDEX)
#error CRY_SHA3_GET_BASE_INDEX is already defined
#endif
/**
 * \brief Convert the 2d indexes to the base linear index
 */
#define CRY_SHA3_GET_BASE_INDEX(x, y) (((((x) % 5U) + (5U * ((y) % 5U))) * 2U))

#if (defined CRY_SHA3_ROLLUP_32)
#error CRY_SHA3_ROLLUP_32 is already defined
#endif
/**
 * \brief Roll up 2 consequent 32bits word in the given offset and store only the low one
 */
#define CRY_SHA3_ROLLUP_32(low, high, offset) \
        (((offset) != 0) ? \
            ((((uint32)(low)) << (offset)) ^ (((uint32)(high)) >> (32U - (offset)))) : (low))

/*==[Declaration of functions with internal linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/**
 * \brief Roll up an 64 bits combination with the given offset
 *
 * This function handles/rolls up the low and high 32bits word as an unity.
 *
 * \param[in] inLowWord Input low word
 * \param[in] inHighWord Input high word
 * \param[out] outLowWord Pointer to the output low word
 * \param[out] outLowWord Pointer to the output high word
 * \param[in] offset Number of bits to be rolled up
 */
static FUNC(void, CRY_CODE) CRY_SHA3_ROLLUP64
(
    uint32 inLowWord,
    uint32 inHighWord,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) outLowWord,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) outHighWord,
    uint32 offset
);

/**
 * \brief SHA3 algorithm -> step mapping: Theta
 *
 * \param[in/out] state Pointer to the SHA3 state
 */
static FUNC(void, CRY_CODE) Cry_SHA3_Theta
(
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) state
);

/**
 * \brief SHA3 algorithm -> step mapping: Rho
 *
 * \param[in/out] state Pointer to the SHA3 state
 */
static FUNC(void, CRY_CODE) Cry_SHA3_Rho
(
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) state
);

/**
 * \brief SHA3 algorithm -> step mapping: Pi
 *
 * \param[in/out] state Pointer to the SHA3 state
 */
static FUNC(void, CRY_CODE) Cry_SHA3_Pi
(
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) state
);

/**
 * \brief SHA3 algorithm -> step mapping: Chi
 *
 * \param[in/out] state Pointer to the SHA3 state
 */
static FUNC(void, CRY_CODE) Cry_SHA3_Chi
(
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) state
);


/**
 * \brief SHA3 -> Xor state with the given lane
 *
 * \param[in/out] state Pointer to the SHA3 state
 * \param[in] lanePosition Lane position
 * \param[in] laneAsBytes Pointer to the given lane
 */
static FUNC(void, CRY_CODE) Cry_SHA3_XorLane
(
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) state,
    uint8 lanePosition,
    P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) laneAsBytes
);


/**
 * \brief SHA3 permutation operation
 *
 * \param[in] state Pointer to the SHA3 state
 */
static FUNC(void, CRY_CODE) Cry_SHA3_PermuteOnState
(
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) state
);

/**
 * \brief SHA3 -> Xor the given lane and conduct the permutation if the state is fulfilled
 *
 * \param[in/out] state Pointer to the SHA3 state
 * \param[in] lanePosition Pointer to the lane position
 * \param[in] laneAsBytes Pointer to the given lane
 * \param[in] rateInLanes Rate counted in lanes
 */
static FUNC(void, CRY_CODE) Cry_SHA3_AbsorbLane
(
    P2VAR(uint32,  AUTOMATIC, CRY_APPL_DATA) state,
    P2VAR(uint8,   AUTOMATIC, CRY_APPL_DATA) lanePosition,
    P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) laneAsBytes,
    uint8                                    rateInLanes
);

/**
 * \brief SHA3 -> Add suffix and padding, then permute
 *
 * \param[in/out] state Pointer to the SHA3 state
 * \param[in] inputOffset Input offset in the state
 * \param[in] rateInBytes Rate counted in bytes
 */
static FUNC(void, CRY_CODE) Cry_SHA3_AbsorbSuffixAndPadding
(
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) state,
    uint8 inputOffset,
    uint16 rateInBytes
);

/**
 * \brief SHA3 -> Add suffix and padding, then permute
 *
 * \param[in/out] state Pointer to the SHA3 state
 * \param[in] lanePosition Lane position
 * \param[in] data Pointer to the output puffer whose size should be bigger than 8
 */
static FUNC(void, CRY_CODE) Cry_SHA3_ExtractLane
(
    P2CONST(uint32, AUTOMATIC, CRY_APPL_DATA) state,
    uint8 lanePosition,
    P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) data
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

/*==[Constants with internal linkage]=========================================*/

#define CRY_START_SEC_CONST_32
#include <MemMap.h>

/**
 * \brief Constant used in the step: rho
 */
static CONST(uint32, CRY_CONST) Cry_SHA3_RhoOffsets[CRY_SHA3_LANES] =
{
    0U,  1U, 62U, 28U, 27U,
    36U, 44U,  6U, 55U, 20U,
    3U, 10U, 43U, 25U, 39U,
    41U, 45U, 15U, 21U,  8U,
    18U,  2U, 61U, 56U, 14U
};

/**
 * \brief Constant used in the step: iota
 */
static CONST(uint32, CRY_CONST) Cry_SHA3_RoundConstants[CRY_SHA3_ROUNDS][2] =
{
    { 0x00000001U, 0x00000000U },
    { 0x00008082U, 0x00000000U },
    { 0x0000808aU, 0x80000000U },
    { 0x80008000U, 0x80000000U },
    { 0x0000808bU, 0x00000000U },
    { 0x80000001U, 0x00000000U },
    { 0x80008081U, 0x80000000U },
    { 0x00008009U, 0x80000000U },
    { 0x0000008aU, 0x00000000U },
    { 0x00000088U, 0x00000000U },
    { 0x80008009U, 0x00000000U },
    { 0x8000000aU, 0x00000000U },
    { 0x8000808bU, 0x00000000U },
    { 0x0000008bU, 0x80000000U },
    { 0x00008089U, 0x80000000U },
    { 0x00008003U, 0x80000000U },
    { 0x00008002U, 0x80000000U },
    { 0x00000080U, 0x80000000U },
    { 0x0000800aU, 0x00000000U },
    { 0x8000000aU, 0x80000000U },
    { 0x80008081U, 0x80000000U },
    { 0x00008080U, 0x80000000U },
    { 0x80000001U, 0x00000000U },
    { 0x80008008U, 0x80000000U }
};

#define CRY_STOP_SEC_CONST_32
#include <MemMap.h>

/*==[Definition of functions with external linkage]===========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>


static FUNC(void, CRY_CODE) CRY_SHA3_ROLLUP64
(
    uint32 inLowWord,
    uint32 inHighWord,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) outLowWord,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) outHighWord,
    uint32 offset
)
{
    if (offset > 32U)
    {
        offset -= 32U;
        *outLowWord = CRY_SHA3_ROLLUP_32(inHighWord, inLowWord, offset);
        *outHighWord = CRY_SHA3_ROLLUP_32(inLowWord, inHighWord, offset);
    }
    else
    {
        *outLowWord = CRY_SHA3_ROLLUP_32(inLowWord, inHighWord, offset);
        *outHighWord = CRY_SHA3_ROLLUP_32(inHighWord, inLowWord, offset);
    }
}


static FUNC(void, CRY_CODE) Cry_SHA3_Theta
(
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) state
)
{
    uint32 x, y;
    uint32 tmpIndex;
    uint32 C[CRY_SHA3_STATE_MAX_X_DIMENSION][CRY_SHA3_STATE_ONE_LANE_IN_32BITS_WORDS];
    uint32 D[CRY_SHA3_STATE_MAX_X_DIMENSION][CRY_SHA3_STATE_ONE_LANE_IN_32BITS_WORDS];

    for (x = 0U; x < CRY_SHA3_STATE_MAX_X_DIMENSION; ++x)
    {
        C[x][0U] = 0U;
        C[x][1U] = 0U;
        for (y = 0U; y < CRY_SHA3_STATE_MAX_Y_DIMENSION; ++y)
        {
            tmpIndex = CRY_SHA3_GET_BASE_INDEX(x, y);
            C[x][0U] ^= state[tmpIndex];
            ++tmpIndex;
            C[x][1U] ^= state[tmpIndex];
        }
    }

    for (x = 0U; x < CRY_SHA3_STATE_MAX_X_DIMENSION; ++x)
    {
        CRY_SHA3_ROLLUP64(C[(x + 1U) % 5U][0U], C[(x + 1U) % 5U][1U], &(D[x][0U]), &(D[x][1U]), 1U);

        /* In the following, variable y is used as a temp. variable */
        y = (x + 4U) % 5U;

        D[x][0U] ^= C[y][0U];
        D[x][1U] ^= C[y][1U];
    }

    for (x = 0U; x < CRY_SHA3_STATE_MAX_X_DIMENSION; ++x)
    {
        for (y = 0U; y < CRY_SHA3_STATE_MAX_Y_DIMENSION; ++y)
        {
            tmpIndex = CRY_SHA3_GET_BASE_INDEX(x, y);
            state[tmpIndex] ^= D[x][0U];
            ++tmpIndex;
            state[tmpIndex] ^= D[x][1U];
        }
    }
}


static FUNC(void, CRY_CODE) Cry_SHA3_Rho
(
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) state
)
{
    uint32 x, y, tmpIndex;
    for (x = 0; x < CRY_SHA3_STATE_MAX_X_DIMENSION; ++x)
    {
        for (y = 0; y < CRY_SHA3_STATE_MAX_Y_DIMENSION; ++y)
        {
            tmpIndex = CRY_SHA3_GET_BASE_INDEX(x, y);
            CRY_SHA3_ROLLUP64(state[tmpIndex],
                              state[tmpIndex + 1U],
                              &(state[tmpIndex]),
                              &(state[tmpIndex + 1U]),
                              Cry_SHA3_RhoOffsets[((5U * y) + x)]
                             );
        }
    }
}


static FUNC(void, CRY_CODE) Cry_SHA3_Pi
(
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) state
)
{
    uint32 x, y;
    uint32 tmpIndex1, tmpIndex2;
    uint32 tempState[CRY_SHA3_STATE_SIZE_IN_32BITS_WORDS];

    for (x = 0U; x < CRY_SHA3_STATE_SIZE_IN_32BITS_WORDS; ++x)
    {
        tempState[x] = state[x];
    }

    for (x = 0U; x < CRY_SHA3_STATE_MAX_X_DIMENSION; ++x)
    {
        for (y = 0U; y < CRY_SHA3_STATE_MAX_Y_DIMENSION; ++y)
        {
            tmpIndex1 = CRY_SHA3_GET_BASE_INDEX(y, ((2U * x) + (3U * y)));
            tmpIndex2 = CRY_SHA3_GET_BASE_INDEX(x, y);

            state[tmpIndex1] = tempState[tmpIndex2];
            ++tmpIndex1;
            ++tmpIndex2;
            state[tmpIndex1] = tempState[tmpIndex2];
        }
    }
}


static FUNC(void, CRY_CODE) Cry_SHA3_Chi
(
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) state
)
{
    uint32 x, y;
    uint32 tmpIndex1, tmpIndex2, tmpIndex3;
    uint32 C[5U][CRY_SHA3_STATE_ONE_LANE_IN_32BITS_WORDS];

    for (y = 0U; y < CRY_SHA3_STATE_MAX_Y_DIMENSION; ++y)
    {
        for (x = 0U; x < CRY_SHA3_STATE_MAX_X_DIMENSION; ++x)
        {
            tmpIndex1 = CRY_SHA3_GET_BASE_INDEX(x, y);
            tmpIndex2 = CRY_SHA3_GET_BASE_INDEX((x + 1U), y);
            tmpIndex3 = CRY_SHA3_GET_BASE_INDEX((x + 2U), y);

            C[x][0U] = state[tmpIndex1] ^ ((~state[tmpIndex2]) & state[tmpIndex3]);
            ++tmpIndex1;
            ++tmpIndex2;
            ++tmpIndex3;
            C[x][1U] = state[tmpIndex1] ^ ((~state[tmpIndex2]) & state[tmpIndex3]);
        }

        for (x = 0U; x < CRY_SHA3_STATE_MAX_X_DIMENSION; ++x)
        {
            tmpIndex1 = CRY_SHA3_GET_BASE_INDEX(x, y);
            state[tmpIndex1] = C[x][0U];
            ++tmpIndex1;
            state[tmpIndex1] = C[x][1U];
        }
    }
}


static FUNC(void, CRY_CODE) Cry_SHA3_PermuteOnState
(
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) state
)
{
    uint32 i;
    for (i = 0U; i < CRY_SHA3_ROUNDS; ++i)
    {
        Cry_SHA3_Theta(state);
        Cry_SHA3_Rho(state);
        Cry_SHA3_Pi(state);
        Cry_SHA3_Chi(state);

        /* Iota */
        state[0U] ^= Cry_SHA3_RoundConstants[i][0U];
        state[1U] ^= Cry_SHA3_RoundConstants[i][1U];
    }
}


static FUNC(void, CRY_CODE) Cry_SHA3_XorLane
(
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) state,
    uint8 lanePosition,
    P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) laneAsBytes
)
{
    uint32 low, high;

    low = laneAsBytes[0]
        | ((uint32) (laneAsBytes[1]) << 8U)
        | ((uint32) (laneAsBytes[2]) << 16U)
        | ((uint32) (laneAsBytes[3]) << 24U);

    high = laneAsBytes[4]
        | ((uint32) (laneAsBytes[5]) << 8U)
        | ((uint32) (laneAsBytes[6]) << 16U)
        | ((uint32) (laneAsBytes[7]) << 24U);

    state[(lanePosition * 2U) + 0U] ^= low;
    state[(lanePosition * 2U) + 1U] ^= high;
}


static FUNC(void, CRY_CODE) Cry_SHA3_AbsorbLane
(
    P2VAR(uint32,  AUTOMATIC, CRY_APPL_DATA) state,
    P2VAR(uint8,   AUTOMATIC, CRY_APPL_DATA) lanePosition,
    P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) laneAsBytes,
    uint8                                    rateInLanes
)
{
    uint8 tmpLanePos;

    tmpLanePos = *lanePosition;
    Cry_SHA3_XorLane(state, tmpLanePos, laneAsBytes);
    ++tmpLanePos;
    tmpLanePos %= rateInLanes;
    *lanePosition = tmpLanePos;

    if (0U == tmpLanePos)
    {
        Cry_SHA3_PermuteOnState(state);
    }
}


/**
 * \brief SHA3 -> Sponge absord operation
 *
 * \param[in] data Pointer to the input
 * \param[in] dataBytesLen Input length
 * \param[in] rateInBytes Rate counted in bytes
 * \param[in/out] state Pointer to the SHA3 state
 * \param[in/out] inputOffset Pointer to the input offset in the state
 */
FUNC(void, CRY_CODE) Cry_SHA3_SpongeAbsorb
(
    P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) data,
    uint32 dataBytesLen,
    uint16 rateInBytes,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) state,
    P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) inputOffset
)
{
    uint8 rateInLanes;
    uint8 lanePosition;
    uint8 offsetInLane;
    P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) curData;

    rateInLanes = (uint8)(rateInBytes / CRY_SHA3_LANE_SIZE_IN_BYTES);
    lanePosition = *inputOffset / CRY_SHA3_LANE_SIZE_IN_BYTES;
    offsetInLane = *inputOffset % CRY_SHA3_LANE_SIZE_IN_BYTES;
    curData = data;

    while (dataBytesLen > 0U)
    {
        if ((0U == offsetInLane) && (dataBytesLen >= CRY_SHA3_LANE_SIZE_IN_BYTES))
        {
            Cry_SHA3_AbsorbLane(state, &lanePosition, curData, rateInLanes);
            dataBytesLen -= CRY_SHA3_LANE_SIZE_IN_BYTES;
            curData = &curData[CRY_SHA3_LANE_SIZE_IN_BYTES];
        }
        else
        {
            uint8 tmpCount;
            uint32 maxRestBytes;
            uint32 realRestBytes;
            uint8 tmpLane[CRY_SHA3_LANE_SIZE_IN_BYTES];

            TS_MemSet(tmpLane, 0U, CRY_SHA3_LANE_SIZE_IN_BYTES);
            maxRestBytes = (uint32)CRY_SHA3_LANE_SIZE_IN_BYTES - (uint32)offsetInLane;
            realRestBytes = maxRestBytes > dataBytesLen ? dataBytesLen : maxRestBytes;

            for (tmpCount = 0U; tmpCount < realRestBytes; ++tmpCount)
            {
                tmpLane[tmpCount + offsetInLane] = *curData;
                curData = &curData[1U];
                --dataBytesLen;
            }

            if (maxRestBytes == realRestBytes)
            {
                Cry_SHA3_AbsorbLane(state, &lanePosition, tmpLane, rateInLanes);
                offsetInLane = 0U;
            }
            else
            {
                Cry_SHA3_XorLane(state, lanePosition, tmpLane);
                offsetInLane += (uint8)realRestBytes;
            }
        }
    }

    *inputOffset = (lanePosition * CRY_SHA3_LANE_SIZE_IN_BYTES) + offsetInLane;
}


static FUNC(void, CRY_CODE) Cry_SHA3_AbsorbSuffixAndPadding
(
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) state,
    uint8 inputOffset,
    uint16 rateInBytes
)
{
    uint8 rateInLanes;
    uint8 lanePosition;
    uint8 offsetInLane;
    uint8 tmpLane[CRY_SHA3_LANE_SIZE_IN_BYTES];

    rateInLanes = (uint8)(rateInBytes / CRY_SHA3_LANE_SIZE_IN_BYTES);
    lanePosition = inputOffset / CRY_SHA3_LANE_SIZE_IN_BYTES;
    offsetInLane = inputOffset % CRY_SHA3_LANE_SIZE_IN_BYTES;
    TS_MemSet(tmpLane, 0U, CRY_SHA3_LANE_SIZE_IN_BYTES);

    tmpLane[offsetInLane] = CRY_SHA3_STATE_SUFFIX_PLUS_FIRST_PADDING_BIT;
    Cry_SHA3_XorLane(state, lanePosition, tmpLane);
    /* reset */
    tmpLane[offsetInLane] = 0x0U;

    /* the last lane position in the rate */
    lanePosition = rateInLanes - ((uint8)1U);
    tmpLane[CRY_SHA3_LANE_LAST_BYTE_INDEX] |= CRY_SHA3_STATE_LAST_PADDING_BIT;

    Cry_SHA3_XorLane(state, lanePosition, tmpLane);
    Cry_SHA3_PermuteOnState(state);
}


static FUNC(void, CRY_CODE) Cry_SHA3_ExtractLane
(
    P2CONST(uint32, AUTOMATIC, CRY_APPL_DATA) state,
    uint8 lanePosition,
    P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) data
)
{
    uint32 low, high;

    low = state[lanePosition * 2U];
    high = state[(lanePosition * 2U) + 1U];

    data[0] = (uint8)(low & 0xFFU);
    data[1] = (uint8)((low >> 8U) & 0xFFU);
    data[2] = (uint8)((low >> 16U) & 0xFFU);
    data[3] = (uint8)((low >> 24U) & 0xFFU);

    data[4] = (uint8)(high & 0xFFU);
    data[5] = (uint8)((high >> 8U) & 0xFFU);
    data[6] = (uint8)((high >> 16U) & 0xFFU);
    data[7] = (uint8)((high >> 24U) & 0xFFU);
}


/**
 * \brief SHA3 -> Sponge squeeze operation
 *
 * \param[in/out] state Pointer to the SHA3 state
 * \param[in] inputOffset Pointer to the input offset in the state
 * \param[in] rateInBytes Rate counted in bytes
 * \param[in] outData Pointer to the output
 * \param[in/out] dataBytesLen Output buffer length
 */
FUNC(void, CRY_CODE) Cry_SHA3_SpongeSqueeze
(
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) state,
    uint8 inputOffset,
    uint16 rateInBytes,
    uint16 hashLen,
    P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) outDataPtr,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) outBytesLenPtr
)
{
    uint8 lanePosition;
    uint32 outLen;

    outLen = ((uint32)hashLen) < (*outBytesLenPtr) ? ((uint32)hashLen) : (*outBytesLenPtr);
    *outBytesLenPtr = outLen;

    Cry_SHA3_AbsorbSuffixAndPadding(state, inputOffset, rateInBytes);

    lanePosition = 0U;
    while (outLen > 0U)
    {
        if (outLen < CRY_SHA3_LANE_SIZE_IN_BYTES)
        {
            uint8 i;
            uint8 tmpLane[CRY_SHA3_LANE_SIZE_IN_BYTES];
            Cry_SHA3_ExtractLane(state, lanePosition, tmpLane);
            for (i = 0U; i < outLen; ++i)
            {
                outDataPtr[i] = tmpLane[i];
            }
            outLen = 0U;
        }
        else
        {
            Cry_SHA3_ExtractLane(state, lanePosition, outDataPtr);
            outLen -= CRY_SHA3_LANE_SIZE_IN_BYTES;
            outDataPtr = &outDataPtr[CRY_SHA3_LANE_SIZE_IN_BYTES];
        }
        ++lanePosition;
    }
}


#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CRY_SHA3_ENABLED == STD_ON) #else */

