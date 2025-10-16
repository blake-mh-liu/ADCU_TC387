#ifndef SOMEIPXF_S_API_STC_H
#define SOMEIPXF_S_API_STC_H

/**
 * \file
 *
 * \brief AUTOSAR SomeIpXf
 *
 * This file contains the implementation of the AUTOSAR
 * module SomeIpXf.
 *
 * \version 1.0.57
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.10 (advisory)
 * The # and ## preprocessor operators should not be used.
 *
 * Reason:
 * ## operator is used for code generation via pre-processor.
 *
 */

/*==================[inclusions]============================================*/
#include <SomeIpXf_Cfg.h>              /* Generated configuration */

/*==================[macros]================================================*/

#if (defined SOMEIPXF_XFRMBUFFERLENGTH_TYPE) /* to prevent double declaration */
#error SOMEIPXF_XFRMBUFFERLENGTH_TYPE already defined
#endif

#if (SOMEIPXF_XFRMBUFFERLENGTHTYPE_ISUINT32 == STD_ON)
#define SOMEIPXF_XFRMBUFFERLENGTH_TYPE uint32
#else
#define SOMEIPXF_XFRMBUFFERLENGTH_TYPE uint16
#endif

/* -------------------- SOMEIPXF message types (SWS_SomeIpXf_00031) ----------*/

#if (defined SOMEIPXF_MESSAGE_TYPE_REQUEST)
#error SOMEIPXF_MESSAGE_TYPE_REQUEST already defined
#endif
/** \brief A request expecting a response */
#define SOMEIPXF_MESSAGE_TYPE_REQUEST                             0x00U

#if (defined SOMEIPXF_MESSAGE_TYPE_REQUEST_NO_RETURN)
#error SOMEIPXF_MESSAGE_TYPE_REQUEST_NO_RETURN already defined
#endif
/** \brief A fire&forget request */
#define SOMEIPXF_MESSAGE_TYPE_REQUEST_NO_RETURN                   0x01U

#if (defined SOMEIPXF_MESSAGE_TYPE_NOTIFICATION)
#error SOMEIPXF_MESSAGE_TYPE_NOTIFICATION already defined
#endif
/** \brief A request of a notification expecting no response */
#define SOMEIPXF_MESSAGE_TYPE_NOTIFICATION                        0x02U

#if (defined SOMEIPXF_MESSAGE_TYPE_RESPONSE)
#error SOMEIPXF_MESSAGE_TYPE_RESPONSE already defined
#endif
/** \brief The response message */
#define SOMEIPXF_MESSAGE_TYPE_RESPONSE                            0x80U

#if (defined SOMEIPXF_MESSAGE_TYPE_ERROR)
#error SOMEIPXF_MESSAGE_TYPE_ERROR already defined
#endif
/** \brief The response containing an error */
#define SOMEIPXF_MESSAGE_TYPE_ERROR                               0x81U

/* -------------------- END OF SOMEIPXF message types (SWS_SomeIpXf_00031) ----------*/

/*==================[Error codes]===========================================*/

/*==================[macro checks]==========================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/
#define SOMEIPXF_START_SEC_CODE
#include <SomeIpXf_MemMap.h>

/** \brief Extracts the relevant SOME/IP protocol header fields of the message.
**
** This service extracts the relevant SOME/IP protocol header fields of the message
** type and the message result type.
** At the time being, this is limited to the types used for C/S communication
** i.e. Message Type:(REQUEST and RESPONSE) and Message Result:(OK and ERROR).
**
** \param[in] buffer         Buffer allocated by the RTE,
**                           where the transformed data has to be stored by the transformer.
** \param[in] bufferLength   Length of the buffer.
**
** \param[out] messageType   Canonical representation of the message type extracted
**                           from the transformers protocol header.
** \param[out] messageResult Canonical representation of the message result type extracted
**                           from the transformers protocol header).
**
** \return Std_ReturnType
** \retval E_OK - Relevant protocol header fields have been extracted successfully.
** \retval E_NOT_OK - An error occurred during parsing of the SOME/IP protocol header
**                    e.g., incorrect protocol version or insufficient buffer length
**                          (bufferLength smaller than minimal SOME/IP header length).
**
** \ServiceID{0x05}
** \Reentrancy{Reentrant}
** \Synchronicity{Synchronous}
*/
extern FUNC(Std_ReturnType, SOMEIPXF_CODE) SomeIpXf_ExtractProtocolHeaderFields
(
   P2CONST(uint8, AUTOMATIC, SOMEIPXF_APPL_DATA) buffer,
   uint32 bufferLength,
   P2VAR(Std_MessageTypeType, AUTOMATIC, SOMEIPXF_APPL_DATA) messageType,
   P2VAR(Std_MessageResultType, AUTOMATIC, SOMEIPXF_APPL_DATA) messageResult
);

#define SOMEIPXF_STOP_SEC_CODE
#include <SomeIpXf_MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef SOMEIPXF_S_API_STC_H */
/*==================[end of file]===========================================*/
