/**
 * \file
 *
 * \brief AUTOSAR E2E
 *
 * This file contains the implementation of the AUTOSAR
 * module E2E.
 *
 * \version 2.0.22
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef E2E_PXX_E2EXF_H
#define E2E_PXX_E2EXF_H

/*==================[inclusions]============================================*/

#include <E2E_E2EXf_Stc.h>      /* static declarations of non AUTOSAR APIs */

#if (E2EXF_IN_USE == STD_ON)

#include <E2E.h>
#include <E2E_SM.h>

/*==================[macros]================================================*/
#if (defined E2E_STD_MESSAGETYPE_INVALID) /* to prevent double declaration */
#error E2E_STD_MESSAGETYPE_INVALID already defined
#endif /* if (defined E2E_STD_MESSAGETYPE_INVALID) */
/** \brief Define message type to invalid  */
#define E2E_STD_MESSAGETYPE_INVALID               0x02U

#if (defined E2E_STD_MESSAGERESULT_INVALID) /* to prevent double declaration */
#error E2E_STD_MESSAGERESULT_INVALID already defined
#endif /* if (defined E2E_STD_MESSAGERESULT_INVALID) */
/** \brief Define message result to invalid  */
#define E2E_STD_MESSAGERESULT_INVALID             0x02U
/*==================[macro checks]==========================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

#define E2E_START_SEC_CODE
#include <E2E_MemMap.h>

/* Checks preconditions specific for E2E for methods */
extern FUNC(uint8, E2E_CODE) E2EXf_MethodPreCondCheck
(
    Std_ExtractProtocolHeaderFieldsType extractProtocolHeaderFieldsFctPtr,
    P2CONST(E2EXf_CSTransactionHandleType, AUTOMATIC, E2EXF_APPL_DATA) csTransactionHandlePtr
);

/* Checks preconditions for in-place protect transformer */
extern FUNC(uint8, E2E_CODE) E2EXf_InPlaceTransPreCondCheck
(
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) BufferPtr,
    P2VAR(E2EXF_XFRMBUFFERLENGTH_TYPE, AUTOMATIC, E2E_APPL_DATA) BufferLengthPtr,
    E2EXF_XFRMBUFFERLENGTH_TYPE InputBufferLength,
    P2CONST(E2EXf_PXXConfigType, AUTOMATIC, E2E_APPL_CONST) PXXConfigPtr
);

/* Checks preconditions for out-of-place protect transformer */
extern FUNC(uint8, E2E_CODE) E2EXf_OutOfPlaceTransPreCondCheck
(
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) BufferPtr,
    P2VAR(E2EXF_XFRMBUFFERLENGTH_TYPE, AUTOMATIC, E2E_APPL_DATA) BufferLengthPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) InputBufferPtr,
    E2EXF_XFRMBUFFERLENGTH_TYPE InputBufferLength,
    P2CONST(E2EXf_PXXConfigType, AUTOMATIC, E2E_APPL_CONST) PXXConfigPtr
);

/* Checks preconditions for client in-place protect transformer */
extern FUNC(uint8, E2E_CODE) E2EXf_PXXmSourceInPlaceTransPreCondCheck
(
    Std_ExtractProtocolHeaderFieldsType extractProtocolHeaderFieldsFctPtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) BufferPtr,
    P2VAR(E2EXF_XFRMBUFFERLENGTH_TYPE, AUTOMATIC, E2E_APPL_DATA) BufferLengthPtr,
    E2EXF_XFRMBUFFERLENGTH_TYPE InputBufferLength,
    P2CONST(E2EXf_PXXConfigType, AUTOMATIC, E2E_APPL_CONST) PXXConfigPtr
);

/* Checks preconditions for server in-place protect transformer */
extern FUNC(uint8, E2E_CODE) E2EXf_PXXmSinkInPlaceTransPreCondCheck
(
    Std_ExtractProtocolHeaderFieldsType extractProtocolHeaderFieldsFctPtr,
    P2CONST(E2EXf_CSTransactionHandleType, AUTOMATIC, E2EXF_APPL_DATA) csTransactionHandlePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) BufferPtr,
    P2VAR(E2EXF_XFRMBUFFERLENGTH_TYPE, AUTOMATIC, E2E_APPL_DATA) BufferLengthPtr,
    E2EXF_XFRMBUFFERLENGTH_TYPE InputBufferLength,
    P2CONST(E2EXf_PXXConfigType, AUTOMATIC, E2E_APPL_CONST) PXXConfigPtr
);

/* Checks preconditions for client out-of-place protect transformer */
extern FUNC(uint8, E2E_CODE) E2EXf_PXXmSourceOutOfPlaceTransPreCondCheck
(
    Std_ExtractProtocolHeaderFieldsType extractProtocolHeaderFieldsFctPtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) BufferPtr,
    P2VAR(E2EXF_XFRMBUFFERLENGTH_TYPE, AUTOMATIC, E2E_APPL_DATA) BufferLengthPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) InputBufferPtr,
    E2EXF_XFRMBUFFERLENGTH_TYPE InputBufferLength,
    P2CONST(E2EXf_PXXConfigType, AUTOMATIC, E2E_APPL_CONST) PXXConfigPtr
);

/* Checks preconditions for server out-of-place protect transformer */
extern FUNC(uint8, E2E_CODE) E2EXf_PXXmSinkOutOfPlaceTransPreCondCheck
(
    Std_ExtractProtocolHeaderFieldsType extractProtocolHeaderFieldsFctPtr,
    P2CONST(E2EXf_CSTransactionHandleType, AUTOMATIC, E2EXF_APPL_DATA) csTransactionHandlePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) BufferPtr,
    P2VAR(E2EXF_XFRMBUFFERLENGTH_TYPE, AUTOMATIC, E2E_APPL_DATA) BufferLengthPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) InputBufferPtr,
    E2EXF_XFRMBUFFERLENGTH_TYPE InputBufferLength,
    P2CONST(E2EXf_PXXConfigType, AUTOMATIC, E2E_APPL_CONST) PXXConfigPtr
);

/* Prepare in-place buffer of protect transformer */
extern FUNC(void, E2E_CODE) E2EXf_InPlaceShiftUpperHeaderToLeft
(
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) BufferPtr,
    P2CONST(E2EXf_PXXConfigType, AUTOMATIC, E2E_APPL_CONST) PXXConfigPtr
);

/* Prepare out-of-place buffer of protect transformer by copying buffer and
   shifting upper header to left */
extern FUNC(void, E2E_CODE) E2EXf_CopyOutOfPlaceBuffer
(
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) BufferPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) InputBufferPtr,
    E2EXF_XFRMBUFFERLENGTH_TYPE InputBufferLength,
    P2CONST(E2EXf_PXXConfigType, AUTOMATIC, E2E_APPL_CONST) PXXConfigPtr
);

/* Checks preconditions for in-place check transformer */
extern FUNC(uint8, E2E_CODE) E2EXf_Inv_InPlaceTransPreCondCheck
(
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) BufferPtr,
    P2VAR(E2EXF_XFRMBUFFERLENGTH_TYPE, AUTOMATIC, E2E_APPL_DATA) BufferLengthPtr,
    E2EXF_XFRMBUFFERLENGTH_TYPE InputBufferLength,
    P2CONST(E2EXf_PXXConfigType, AUTOMATIC, E2E_APPL_CONST) PXXConfigPtr
);

/* Checks preconditions for out-of-place protect transformer */
extern FUNC(uint8, E2E_CODE) E2EXf_Inv_OutOfPlaceTransPreCondCheck
(
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) BufferPtr,
    P2VAR(E2EXF_XFRMBUFFERLENGTH_TYPE, AUTOMATIC, E2E_APPL_DATA) BufferLengthPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) InputBufferPtr,
    E2EXF_XFRMBUFFERLENGTH_TYPE InputBufferLength,
    P2CONST(E2EXf_PXXConfigType, AUTOMATIC, E2E_APPL_CONST) PXXConfigPtr
);

/* Checks preconditions for client in-place check transformer */
extern FUNC(uint8, E2E_CODE) E2EXf_Inv_PXXmSourceInPlaceTransPreCondCheck
(
    Std_ExtractProtocolHeaderFieldsType extractProtocolHeaderFieldsFctPtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) BufferPtr,
    P2VAR(E2EXF_XFRMBUFFERLENGTH_TYPE, AUTOMATIC, E2E_APPL_DATA) BufferLengthPtr,
    E2EXF_XFRMBUFFERLENGTH_TYPE InputBufferLength,
    P2CONST(E2EXf_PXXConfigType, AUTOMATIC, E2E_APPL_CONST) PXXConfigPtr
);

/* Checks preconditions for server in-place check transformer */
extern FUNC(uint8, E2E_CODE) E2EXf_Inv_PXXmSinkInPlaceTransPreCondCheck
(
    Std_ExtractProtocolHeaderFieldsType extractProtocolHeaderFieldsFctPtr,
    P2CONST(E2EXf_CSTransactionHandleType, AUTOMATIC, E2EXF_APPL_DATA) csTransactionHandlePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) BufferPtr,
    P2VAR(E2EXF_XFRMBUFFERLENGTH_TYPE, AUTOMATIC, E2E_APPL_DATA) BufferLengthPtr,
    E2EXF_XFRMBUFFERLENGTH_TYPE InputBufferLength,
    P2CONST(E2EXf_PXXConfigType, AUTOMATIC, E2E_APPL_CONST) PXXConfigPtr
);

/* Checks preconditions for client out-of-place check transformer */
extern FUNC(uint8, E2E_CODE) E2EXf_Inv_PXXmSourceOutOfPlaceTransPreCondCheck
(
    Std_ExtractProtocolHeaderFieldsType extractProtocolHeaderFieldsFctPtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) BufferPtr,
    P2VAR(E2EXF_XFRMBUFFERLENGTH_TYPE, AUTOMATIC, E2E_APPL_DATA) BufferLengthPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) InputBufferPtr,
    E2EXF_XFRMBUFFERLENGTH_TYPE InputBufferLength,
    P2CONST(E2EXf_PXXConfigType, AUTOMATIC, E2E_APPL_CONST) PXXConfigPtr
);

/* Checks preconditions for server out-of-place check transformer */
extern FUNC(uint8, E2E_CODE) E2EXf_Inv_PXXmSinkOutOfPlaceTransPreCondCheck
(
    Std_ExtractProtocolHeaderFieldsType extractProtocolHeaderFieldsFctPtr,
    P2CONST(E2EXf_CSTransactionHandleType, AUTOMATIC, E2EXF_APPL_DATA) csTransactionHandlePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) BufferPtr,
    P2VAR(E2EXF_XFRMBUFFERLENGTH_TYPE, AUTOMATIC, E2E_APPL_DATA) BufferLengthPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) InputBufferPtr,
    E2EXF_XFRMBUFFERLENGTH_TYPE InputBufferLength,
    P2CONST(E2EXf_PXXConfigType, AUTOMATIC, E2E_APPL_CONST) PXXConfigPtr
);

/* Prepare in-place buffer of check transformer */
extern FUNC(void, E2E_CODE) E2EXf_Inv_InPlaceShiftUpperHeaderToRight
(
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) BufferPtr,
    P2CONST(E2EXf_PXXConfigType, AUTOMATIC, E2E_APPL_CONST) PXXConfigPtr
);

/* Copy buffer for out-of-place check transformer */
extern FUNC(void, E2E_CODE) E2EXf_Inv_CopyOutOfPlaceBuffer
(
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) BufferPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) InputBufferPtr,
    E2EXF_XFRMBUFFERLENGTH_TYPE InputBufferLength,
    P2CONST(E2EXf_PXXConfigType, AUTOMATIC, E2E_APPL_CONST) PXXConfigPtr
);

/* Calls E2E_SMCheck and sets dependent return value */
extern FUNC(uint8, E2E_CODE) E2EXf_Inv_SMCheck
(
    E2E_PCheckStatusType RetValMapStatusToSM,
    P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_CONST) SMConfigPtr,
    P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_VAR_CLEARED) SMCheckStatePtr
);

#define E2E_STOP_SEC_CODE
#include <E2E_MemMap.h>

#endif /* (E2EXF_IN_USE == STD_ON) */

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef E2E_PXX_E2EXF_H */
/*==================[end of file]===========================================*/
