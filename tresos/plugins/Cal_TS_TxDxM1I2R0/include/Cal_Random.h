/**
 * \file
 *
 * \brief AUTOSAR Cal
 *
 * This file contains the implementation of the AUTOSAR
 * module Cal.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef CAL_RANDOM_H
#define CAL_RANDOM_H


/*==[Includes]================================================================*/


#include <Cal_Types.h>

#include <Cal_Random_Cfg.h>


/*==[Macros]==================================================================*/



/*==[Types]===================================================================*/

#if ((CAL_RANDOMSEED_ENABLED == TRUE) || (CAL_RANDOMGEN_ENABLED == TRUE))
/* !LINKSTO CAL0730, 1
 */
/* !LINKSTO CAL0742, 1
 */
/** \brief type which specifies the array size of the context buffer required for random number
 *         seeding and generating.
 */
typedef Cal_AlignType Cal_RandomCtxBufType[CAL_RANDOM_CONTEXT_BUFFER_SIZE];

#endif /* #if ((CAL_RANDOMSEED_ENABLED == TRUE) || (CAL_RANDOMGEN_ENABLED == TRUE)) */

#if (CAL_RANDOMSEED_ENABLED == TRUE)

/* !LINKSTO CAL0025, 1
 */
/* !LINKSTO CAL0074, 1
 */
/**
 * \struct Cal_RandomSeedConfigType
 * \brief Structure representing the configuration of the random seed
 *         algorithm.
 *//**
 * \var Cal_RandomSeedConfigType::ConfigId
 * \brief Identifier for the current configuration.
 *//**
 * \var Cal_RandomSeedConfigType::PrimitiveSeedStartFct
 * \brief Pointer to the seed start function of the underlying Cpl primitive.
 *//**
 * \var Cal_RandomSeedConfigType::PrimitiveSeedUpdateFct
 * \brief Pointer to the seed update function of the underlying Cpl primitive.
 *//**
 * \var Cal_RandomSeedConfigType::PrimitiveSeedFinishFct
 * \brief Pointer to the seed finish function of the underlying Cpl primitive.
 *//**
 * \var Cal_RandomSeedConfigType::PrimitiveConfigPtr
 * \brief Pointer to a Cpl configuration.
 */
typedef struct
{
  Cal_ConfigIdType ConfigId;

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveSeedStartFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA) cfgPtr,
    Cal_RandomCtxBufType                    contextBuffer
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveSeedUpdateFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA)  cfgPtr,
    Cal_RandomCtxBufType                     contextBuffer,
    P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) seedPtr,
    uint32                                   seedLength
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveSeedFinishFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA)  cfgPtr,
    Cal_RandomCtxBufType                     contextBuffer
  );

  P2CONST(void, TYPEDEF, CAL_CONST) PrimitiveConfigPtr;
}
Cal_RandomSeedConfigType;

#endif /* #if (CAL_RANDOMSEED_ENABLED == TRUE) */

#if (CAL_RANDOMGEN_ENABLED == TRUE)

/**
 * \struct Cal_RandomGenerateConfigType
 * \brief Structure representing the configuration of the random generation
 *         algorithm.
 *//**
 * \var Cal_RandomGenerateConfigType::ConfigId
 * \brief Identifier for the current configuration.
 *//**
 * \var Cal_RandomGenerateConfigType::PrimitiveGenerateFct
 * \brief Pointer to the random generation function of the underlying Cpl primitive.
 *//**
 * \var Cal_RandomGenerateConfigType::PrimitiveConfigPtr
 * \brief Pointer to a Cpl configuration.
 */
typedef struct
{
  Cal_ConfigIdType ConfigId;

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveGenerateFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA) cfgPtr,
    Cal_RandomCtxBufType                    contextBuffer,
    P2VAR(uint8,  AUTOMATIC, CAL_APPL_DATA) resultPtr,
    uint32                                  resultLength
  );

  P2CONST(void, TYPEDEF, CAL_CONST) PrimitiveConfigPtr;
}
Cal_RandomGenerateConfigType;

#endif /* #if (CAL_RANDOMGEN_ENABLED == TRUE) */

/*==[Constants with external linkage]=========================================*/


#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

#if (CAL_RANDOMSEED_ENABLED == TRUE)
/** \brief Random Seed configuration.
 *  An array containing the configurations of the RandomSeed service.
 */
extern CONST(Cal_RandomSeedConfigType, CAL_CONST)
  Cal_RandomSeedConfigurations[CAL_RANDOMSEED_CONFIG_COUNT];
#endif /* #if (CAL_RANDOMSEED_ENABLED == TRUE) */

#if (CAL_RANDOMGEN_ENABLED == TRUE)
/** \brief Random Generation configuration.
 *  An array containing the configurations of the RandomGenerate service.
 */
extern CONST(Cal_RandomGenerateConfigType, CAL_CONST)
  Cal_RandomGenConfigurations[CAL_RANDOMGEN_CONFIG_COUNT];
#endif /* #if (CAL_RANDOMGEN_ENABLED == TRUE) */

#define CAL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>


/*==[Variables with external linkage]=========================================*/



/*==[Declaration of functions with external linkage]==========================*/

#define CAL_START_SEC_CODE
#include <MemMap.h>


#if (CAL_RANDOMSEED_ENABLED == TRUE)
/* !LINKSTO CAL0149, 1
 */
/**
 *
 * \brief Start seeding.
 *
 * This function performs the initialization of the Random Seed. The initialization function of the
 * configured primitive is called and its return value is returned.
 *
 * \param[in]  cfgId         An identification of the configuration for which the
 *                           initialization shall be requested.
 * \param[out] contextBuffer A Pointer to a buffer where the context of the current configuration
 *                           will be stored.
 *
 * \returns error value
 *
 * \retval CAL_E_OK     If the seeding start was successfully requested.
 * \retval CAL_E_NOT_OK If the request failed.
 *
 */
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_RandomSeedStart
(
  Cal_ConfigIdType     cfgId,
  Cal_RandomCtxBufType contextBuffer
);

/* !LINKSTO CAL0156, 1
 */
/**
 *
 * \brief Update seeding.
 *
 * This function performs the update of the Random seed. The seeding function of the
 * configured primitive is called and its return value is returned.
 *
 * \param[in]     cfgId         An identification of the configuration for which the
 *                              seed update shall be requested.
 * \param[in,out] contextBuffer A Pointer to a buffer where the context of the current configuration
 *
 * \param[in]     seedPtr       A pointer to the start of an array which contains the seed.
 *
 * \param[in]     seedLength    Holds the length of the seed array.
 *
 * \returns error value
 *
 * \retval CAL_E_OK     If the seeding update was successfully requested.
 * \retval CAL_E_NOT_OK If no seeding has been started via Cal_RandomSeedStart()
 *                      yet.
 */
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_RandomSeedUpdate
(
  Cal_ConfigIdType                         cfgId,
  Cal_RandomCtxBufType                     contextBuffer,
  P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) seedPtr,
  uint32                                   seedLength
);

/* !LINKSTO CAL0163, 1
 */
/**
 *
 * \brief Finish seeding.
 *
 * This function performs the finishing of the seeding.
 *
 * \param[in]     cfgId         An identification of the configuration for which the
 *                              seeding finish shall be requested.
 * \param[in,out] contextBuffer A Pointer to a buffer where the context of the current configuration
 *
 * \returns error value
 *
 * \retval CAL_E_OK     If the seeding finish was successfully requested.
 * \retval CAL_E_NOT_OK If no seeding has been started via Cal_RandomSeedStart()
 *                      yet.
 */
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_RandomSeedFinish
(
  Cal_ConfigIdType                         cfgId,
  Cal_RandomCtxBufType                     contextBuffer
);

#endif /* #if (CAL_RANDOMSEED_ENABLED == TRUE) */

#if (CAL_RANDOMGEN_ENABLED == TRUE)

/* !LINKSTO CAL0543, 1
 */
/**
 *
 * \brief Generate pseudo random bytes.
 *
 * This function performs the generation of pseudo random bytes. The
 * byte generation function of the configured primitive is called and its
 * return value is returned.
 *
 * \param[in]     cfgId         An identification of the configuration for which the byte
 *                              generation should be requested.
 *
 * \param[in,out] contextBuffer A Pointer to a buffer where the context of the current configuration
 *
 * \param[out]    resultPtr     A pointer to the start of a buffer where the generated
 *                              pseudo random bytes should be stored.
 *
 * \param[in]     resultLength  Holds the amount of bytes which should be generated.
 *
 * \returns error value
 *
 * \retval CAL_E_OK                 If the byte generation was successfully requested.
 * \retval CAL_E_NOT_OK             If the request failed.
 * \retval CAL_E_ENTROPY_EXHAUSTION If the request failed, entropy of random number generator is
 *                                  exhausted.
 *
 */
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_RandomGenerate
(
  Cal_ConfigIdType                       cfgId,
  Cal_RandomCtxBufType                   contextBuffer,
  P2VAR(uint8, AUTOMATIC, CAL_APPL_DATA) resultPtr,
  uint32                                 resultLength
);

#endif /* #if (CAL_RANDOMGEN_ENABLED == TRUE) */

#define CAL_STOP_SEC_CODE
#include <MemMap.h>



#endif /* #ifndef CAL_RANDOM_H */

