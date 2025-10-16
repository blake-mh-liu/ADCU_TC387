#ifndef CRY_MD5_H
#define CRY_MD5_H

/* --------{ EB Automotive C Source File }-------- */

/*==[Includes]====================================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

#include <Cry_MD5Config.h>

#if (CRY_MD5_ENABLED == STD_ON)

/*==[Macros]======================================================================================*/

#if (defined CRY_MD5_HASH_LEN_BYTES)
#error CRY_MD5_HASH_LEN_BYTES already defined
#endif
/**
 * \brief The length of a message digest computed with the MD5 algorithm in bytes.
 */
#define CRY_MD5_HASH_LEN_BYTES 16U                                       /* Size of an MD5 digest */

#if (defined CRY_MD5_BLOCK_SIZE)
#error CRY_MD5_BLOCK_SIZE already defined
#endif
/**
 * \brief A message which should be hashed is divided into blocks which are processed individually.
 *        This macro gives the length of a block in bytes.
 */
#define CRY_MD5_BLOCK_SIZE     64U                                   /* Blocksize of MD5 in bytes */

#if (defined CRY_MD5_STATE_WORDS)
#error CRY_MD5_STATE_WORDS already defined
#endif
/**
 * \brief The hash algorithm uses a state which is modified by processing the input. The state after
 *        processing the whole input is the hash digest. This macro gives the length of the state in
 *        32-bit words.
 */
#define CRY_MD5_STATE_WORDS     4U                          /* Number of entries of the MD5 state */

#if (defined CRY_MD5_STATE_BYTES)
#error CRY_MD5_STATE_BYTES already defined
#endif
/**
 * \brief The hash algorithm uses a state which is modified by processing the input. The state after
 *        processing the whole input is the hash digest. This macro gives the length of the state in
 *        8-bit words.
 */
#define CRY_MD5_STATE_BYTES    16U                            /* Number of bytes of the MD5 state */

/*==[Types]=======================================================================================*/

/*==[Constants with external linkage]=============================================================*/

/*==[Variables with external linkage]=============================================================*/

/*==[Declaration of functions with external linkage]==============================================*/

#define CRY_START_SEC_CODE
#include <MemMap.h>

/** \brief Init function of the MD5 algorithm.
 *
 * \param[in] cfgPtr Pointer to a Cry MD5 Configuration
 *
 * \return whether the initialization of the MD5 algorithm was successful
 *
 * \retval CSM_E_OK     the initialization of the MD5 algorithm was successful
 * \retval CSM_E_NOT_OK the initialization of the MD5 algorithm was failed
 * \retval CSM_E_BUSY   the initialization failed, the MD5 is busy
 */
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_MD5Start(P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr);

/** \brief Update function of the MD5 algorithm.
 *
 * \param[in] dataPtr    Holds a pointer to the data to be hashed
 * \param[in] dataLength Contains the number of bytes to be hashed.
 *
 * \return whether the request was successful
 *
 * \retval CSM_E_OK     request successful
 * \retval CSM_E_NOT_OK request failed
 * \retval CSM_E_BUSY   the request failed, the MD5 is busy
 */
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_MD5Update
(
  P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA) dataPtr,
  uint32                                   dataLength
);

/** \brief Finish function of the MD5 algorithm.
 *
 * \param[out]   resultPtr           Holds a pointer to the memory location which will hold the
 *                                   result of the hash value computation. If the result does not
 *                                   fit into the given buffer, and truncation is allowed, the
 *                                   result shall be truncated.
 * \param[inout] resultLengthPtr     Holds a pointer to the memory location in where the length
 *                                   information is stored. On calling this function this parameter
 *                                   shall contain the size of the buffer provided by resultPtr.
 *                                   When the request has finished, the actual length of the
 *                                   returned value shall be stored.
 * \param[in]    TruncationIsAllowed This parameter states whether a truncation of the result is
 *                                   allowed or not.
 *                                   TRUE: truncation is allowed.
 *                                   FALSE: truncation is not allowed.
 *
 * \return whether the request was successful
 *
 * \retval CSM_E_OK           request successful
 * \retval CSM_E_NOT_OK       request failed
 * \retval CSM_E_BUSY         the request failed, the MD5 is busy
 * \retval CSM_E_SMALL_BUFFER the provided buffer is too small to store the result, and truncation
 *                            was not allowed.
 */
extern FUNC(Csm_ReturnType, CRY_CODE) Cry_MD5Finish
(
  P2VAR(uint8,  AUTOMATIC, CRY_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) resultLengthPtr,
  boolean                                 TruncationIsAllowed
);

extern FUNC(void, CRY_CODE) Cry_MD5MainFunction
(
  void
);

/** \brief Algorithm identifier of MD5 hash algorithm.
 *
 * This function returns the algorithm identifier of the hash algorithm
 * defined in the given configuration.
 *
 * \param[in] cfgPtr                a pointer to the configuration for which the algorithm
 *                                  identifier should be returned.
 * \param[out] AlgorithmIdLengthPtr a pointer to a variable where the actual length of the
 *                                  algorithm identifier should be stored.
 *
 * \return AlgorithmId  A pointer to the start of a byte array which contains the
 *                      algorithm identifier.
 */
extern FUNC(P2CONST(uint8, AUTOMATIC, CRY_APPL_DATA), CRY_CODE) Cry_MD5AlgorithmId
(
  P2CONST(void, AUTOMATIC, CRY_APPL_DATA) cfgPtr,
  P2VAR(uint32, AUTOMATIC, CRY_APPL_DATA) AlgorithmIdLengthPtr
);

#define CRY_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CRY_MD5_ENABLED == STD_ON) */
#endif /* CRY_MD5_H */
