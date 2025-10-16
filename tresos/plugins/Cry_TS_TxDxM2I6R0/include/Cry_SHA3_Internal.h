/* --------{ EB Automotive C Source File }-------- */

#ifndef CRY_SHA3_INTERNAL_H
#define CRY_SHA3_INTERNAL_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>
#include <Cry_SHA3Config.h>

#if ((CRY_SHA3_ENABLED == STD_ON))

/*==[Macros]==================================================================*/

#if (defined CRY_SHA3_STATE_SIZE_IN_BYTES)
#error CRY_SHA3_STATE_SIZE_IN_BYTES is already defined
#endif
/**
 * \brief Size of SHA3 internal state, counted in bytes
 */
#define CRY_SHA3_STATE_SIZE_IN_BYTES        200U

#if (defined CRY_SHA3_STATE_SIZE_IN_32BITS_WORDS)
#error CRY_SHA3_STATE_SIZE_IN_32BITS_WORDS is already defined
#endif
/**
 * \brief Size of SHA3 internal state, counted in 32bits words
 */
#define CRY_SHA3_STATE_SIZE_IN_32BITS_WORDS 50U

/*==[Types]===================================================================*/

/**
 ** \enum Cry_SHA3StateType
 ** \brief Enumeration of the internal states of the SHA3 computation
 **
 ** \var CRY_SHA3_STATE_IDLE
 ** \brief The algorithm is in the idle state
 **
 ** \var CRY_SHA3_STATE_INIT
 ** \brief The initialization of the algorithm is in progress
 **
 ** \var CRY_SHA3_STATE_INITIALIZED
 ** \brief The algorithm is initialized
 **
 ** \var CRY_SHA3_STATE_UPDATE
 ** \brief The update operation of the algorithm is in progress
 **
 ** \var CRY_SHA3_STATE_FINISH
 ** \brief The finish operation of the algorithm is in progress
 **/
typedef enum
{
    CRY_SHA3_STATE_IDLE,
    CRY_SHA3_STATE_INIT,
    CRY_SHA3_STATE_INITIALIZED,
    CRY_SHA3_STATE_UPDATE,
    CRY_SHA3_STATE_FINISH
}
Cry_SHA3_ProcessStateType;


/**
 ** \struct Cry_SHA3_ContextType
 ** \brief The configuration of the SHA3 hash computation
 **
 ** \var Cry_SHA3_DataType::InputDataLength
 ** \brief Length of the input data in bytes
 **
 ** \var Cry_SHA3_DataType::HashState
 ** \brief The current state of the hash computation
 **
 ** \var Cry_SHA3_DataType::ConfigPtr
 ** \brief A pointer to the current SHA configuration which has to be used
 **
 ** \var Cry_SHA3_DataType::ResultLengthPtr
 ** \brief Pointer to a variable which contains the maximal result
 ** length and where the length of the result will be stored
 **
 ** \var Cry_SHA3_DataType::ResultPtr
 ** \brief Pointer to the memory location in which to store the result
 **
 ** \var Cry_SHA3_DataType::InputDataPtr
 ** \brief Pointer to the input data
 **
 ** \var Cry_SHA3_DataType::ProcessState
 ** \brief Internal state of SHA3 computation process
 **
 ** \var Cry_SHA3_DataType::HashRateLength
 ** \brief Hash rate lenght in bytes
 **
 ** \var Cry_SHA3_DataType::HashStateInputOffset
 ** \brief Current input offset in the SHA3 state
 **/
typedef struct
{
    uint32                       InputDataLength;
    uint32                       HashState[CRY_SHA3_STATE_SIZE_IN_32BITS_WORDS];
    P2CONST(Cry_SHAConfigType, TYPEDEF, CRY_APPL_DATA)       ConfigPtr;
    P2VAR(uint32, TYPEDEF, CRY_APPL_DATA)                    ResultLengthPtr;
    P2VAR(uint8, TYPEDEF, CRY_APPL_DATA)                     ResultPtr;
    P2CONST(uint8, TYPEDEF, CRY_APPL_DATA)                   InputDataPtr;
    Cry_SHA3_ProcessStateType                                ProcessState;
    uint16                                                   HashRateLength;
    uint8                                                    HashStateInputOffset;
}
Cry_SHA3_ContextType;


/*==[Declaration of functions with external linkage]==========================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/**
 * \brief SHA3 -> Sponge absord operation
 *
 * \param[in] data Pointer to the input
 * \param[in] dataBytesLen Input length
 * \param[in] rateInBytes Rate counted in bytes
 * \param[in/out] state Pointer to the SHA3 state
 * \param[in/out] inputOffset Pointer to the input offset in the state
 */
extern FUNC(void, CRY_CODE) Cry_SHA3_SpongeAbsorb
(
    P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) data,
    uint32 dataBytesLen,
    uint16 rateInBytes,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) state,
    P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) inputOffset
);

/**
 * \brief SHA3 -> Sponge squeeze operation
 *
 * \param[in/out] state Pointer to the SHA3 state
 * \param[in] inputOffset Pointer to the input offset in the state
 * \param[in] rateInBytes Rate counted in bytes
 * \param[in] hashLen Hash length
 * \param[in] outDataPtr Pointer to the output
 * \param[in/out] outBytesLenPtr Pointer to the output puffer length
 */
extern FUNC(void, CRY_CODE) Cry_SHA3_SpongeSqueeze
(
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) state,
    uint8 inputOffset,
    uint16 rateInBytes,
    uint16 hashLen,
    P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) outDataPtr,
    P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) outBytesLenPtr
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if ((CRY_SHA3_ENABLED == STD_ON)) */

#endif
