/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               UDS layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file UDS_Cbk.c                      */
/*%%  |                             |  %%  \brief UDS layer source plugin file  */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.8.2 BL-3.X */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2015 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
#include "EB_Prj.h"
#include "board.h"
[!AUTOSPACING!]
/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

void UDS_CustomPositiveAnswerInd (const PduLengthType *pulLen, const u8 *aubUdsData)
{
    OSC_PARAM_UNUSED(pulLen);
    OSC_PARAM_UNUSED(aubUdsData);
}

[!IF "(node:exists(as:modconf('Uds')/General/UDS_TIMEOUT_CHECK) and as:modconf('Uds')/General/UDS_TIMEOUT_CHECK = 'true')"!]
tUdsBoolean UDS_CustomIsBMCountTimeout (const u8 *aubUdsData)

    OSC_PARAM_UNUSED(aubUdsData);

    return UDS_TRUE;

[!ENDIF!]

[!IF "Supplier_Services/BA = 'true'"!]
tUdsStatus UDS_CustomSupplier_BA (PduLengthType *pulLen, u8 *aubUdsData, tUdsAddrMode eUdsAddrMode, tUdsAddrType eUdsAddrType)
{
    OSC_PARAM_UNUSED(pulLen);
    OSC_PARAM_UNUSED(aubUdsData);
    OSC_PARAM_UNUSED(eUdsAddrMode);
    OSC_PARAM_UNUSED(eUdsAddrType);

    return UDS_ACK;
}
[!ENDIF!]

[!IF "Supplier_Services/BB = 'true'"!]
tUdsStatus UDS_CustomSupplier_BB (PduLengthType *pulLen, u8 *aubUdsData, tUdsAddrMode eUdsAddrMode, tUdsAddrType eUdsAddrType)
{
    OSC_PARAM_UNUSED(pulLen);
    OSC_PARAM_UNUSED(aubUdsData);
    OSC_PARAM_UNUSED(eUdsAddrMode);
    OSC_PARAM_UNUSED(eUdsAddrType);

    return UDS_ACK;
}
[!ENDIF!]

[!IF "Supplier_Services/BC = 'true'"!]
tUdsStatus UDS_CustomSupplier_BC (PduLengthType *pulLen, u8 *aubUdsData, tUdsAddrMode eUdsAddrMode, tUdsAddrType eUdsAddrType)
{
    OSC_PARAM_UNUSED(pulLen);
    OSC_PARAM_UNUSED(aubUdsData);
    OSC_PARAM_UNUSED(eUdsAddrMode);
    OSC_PARAM_UNUSED(eUdsAddrType);

    return UDS_ACK;
}
[!ENDIF!]

[!IF "Supplier_Services/BD = 'true'"!]
tUdsStatus UDS_CustomSupplier_BD (PduLengthType *pulLen, u8 *aubUdsData, tUdsAddrMode eUdsAddrMode, tUdsAddrType eUdsAddrType)
{
    OSC_PARAM_UNUSED(pulLen);
    OSC_PARAM_UNUSED(aubUdsData);
    OSC_PARAM_UNUSED(eUdsAddrMode);
    OSC_PARAM_UNUSED(eUdsAddrType);

    return UDS_ACK;
}
[!ENDIF!]

[!IF "Supplier_Services/BE = 'true'"!]
tUdsStatus UDS_CustomSupplier_BE (PduLengthType *pulLen, u8 *aubUdsData, tUdsAddrMode eUdsAddrMode, tUdsAddrType eUdsAddrType)
{
    OSC_PARAM_UNUSED(pulLen);
    OSC_PARAM_UNUSED(aubUdsData);
    OSC_PARAM_UNUSED(eUdsAddrMode);
    OSC_PARAM_UNUSED(eUdsAddrType);

    return UDS_ACK;
}
[!ENDIF!]

