/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                EB                                             */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file EB_Pub.h                        */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.18.0 BL3                */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*********************************************************************************/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*********************************************************************************/
[!AUTOSPACING!]
[!CODE!]

#ifndef EB_PUB_H
#define EB_PUB_H

/* skip this code from DoxyGen only API documentation is provided */
#ifndef DOXYGEN_SHOULD_SKIP_THIS

[!IF "node:exists(as:modconf('Uds'))"!]
#define EB_NO_NRC_78    U8_MAX
[!ENDIF!]

#define EB_TRUE         1U
#define EB_FALSE        0U

[!IF "as:modconf('Tp')/TpGeneral/TpDataStreaming = 'true'"!]
#define EB_STREAMING_ALLOWED    0U
#define EB_STREAMING_FORBIDDEN  1U
[!ENDIF!]
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */
/** \brief Initialize all layers
 **
 ** This function call all the subInit function EB_InitX
 ** It shall be called only once at ECU start-up.
 **
 **/
extern void EB_Init (void);

/** \brief Initialize all communication layers
 **
 ** This function initializes all layers that are mandatory for communication 
 ** by calling *_Init (ex: ::COM_Init)
 ** CAN transceiver is set to NORMAL mode.
 ** All COM nodes are initialized.
 ** COM layer is activated.
 **
 **/
extern void EB_Init1(void);

/** \brief Initialize all specific bootloader layers
 **
 ** This function initializes the Bootloader specific layer 
 ** (PROG, SA and FLASH) by calling there *_Init function.
 **
 **/
extern void EB_Init2(void);

/** \brief Periodical task of all layers
 **
 ** Modules periodic functions are called in this function (ex: ::COM_Manage)
 ** EB_MANAGE_PERIOD is configured in Tresos EB plugin.
 ** The reception of segmented frames are handled in this function.
 **
 **/
extern void EB_Manage (void);

[!IF "as:modconf('Tp')/TpGeneral/TpDataStreaming = 'true'"!]
extern void EB_SetStreamingStatus(u8 ubStreamingState);
[!ENDIF!]


/** \brief Check if FlexRay network is synchronized
 **
 ** If FlexRay is used, this Api check if the Flexray
 ** network is synchronized and return the status and 
 ** the FlexRay cycle.
 **
 ** \return synchronization status
 ** \retval EB_TRUE            Network is synchronized
 ** \retval EB_FALSE           Network is not synchronized
 **/
extern u8 EB_IsNetworkSynchronized(u8 * frCycle);

/** \brief Activate the FlexRay mode AllSlots 
 **
 ** If FlexRay is used, this Api call FlexRay state manager 
 ** to request him the AllSlots mode
 **
 **/
extern void EB_AllSlots(void);

/** \brief Request the commnunication deactivation 
 **
 ** Request to CAN or FlexRay stack to stop communication
 **
 **/
extern void EB_Com_Deactivate(void);


[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true'"!]
/** \brief Store the tester address in global variable
 **
 ** Provide to EB the tester address that shall be accepted
 ** in reception.
 **
 **/
extern void EB_SetTesterAddress(u16 ubTesterAddress);
[!ENDIF!]

[!IF "node:exists(as:modconf('Prog'))"!]
/** \brief Send A TP frame using the current Tester Address
 **
 ** Send A TP frame using the current Tester Address
 **
 ** \param[in]  uwLen Message length
 ** \param[in]  paubUdsData message data pointer
 **
 **/
extern void EB_Send_TPFrame(u16 uwLen, u8 *paubUdsData);
[!ENDIF!]

/** \brief Simulate the reception of a frame
 **
 ** Simulate the reception of a frame
 **
 ** \param[in]  uwLen Message length
 ** \param[in]  paubUdsData message data pointer
 ** \param[in]  ulUdsDataSize Size of the paubUdsData buffer
 ** \param[in]  ubWithResp indicate if a response will be performed (TRUE/FALSE)
 **
 **/
extern void EB_SimulateRxRequest(u16 uwLen, u8 * paubUdsData, PduLengthType ulUdsDataSize, u8 ubWithResp);

/** \brief EB Session timer stop
 **
 ** This function allows to stop the session timer managed by UDS.
 **
 **/
extern void EB_StopSessionTimer (void);

#endif      /* EB_PUB_H */
[!ENDCODE!]

