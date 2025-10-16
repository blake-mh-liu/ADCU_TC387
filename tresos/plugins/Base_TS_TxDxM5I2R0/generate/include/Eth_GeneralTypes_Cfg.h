#ifndef ETH_GENERALTYPES_CFG_H
#define ETH_GENERALTYPES_CFG_H
[!AUTOSPACING!][!//
/**
 * \file
 *
 * \brief AUTOSAR Base
 *
 * This file contains the implementation of the AUTOSAR
 * module Base.
 *
 * \version 5.2.5
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

#include <Std_Types.h>          /* AUTOSAR standard type definitions */

/*==================[type definitions]=======================================*/

/** \brief Represents the hardware object handles of a ETH hardware buffer.
 *
 * Range:
 *  - uint32 (if configuration parameter 'EthIf/EthIfPublicCfg/EthIfPublicHandleTypeEnum = UINT32')
 *  - uint8  (otherwise)
 */
 /* !LINKSTO Base.EB_Ref.SWS_Eth_00026.ImplementedTypes,1, Base.SWS_Eth_00175,1, Base.Eth.Eth_BufIdxType,1 */
[!IF "node:exists(as:modconf('EthIf')[1]/EthIfGeneral/EthIfPublicHandleTypeEnum) and
      (as:modconf('EthIf')[1]/EthIfGeneral/EthIfPublicHandleTypeEnum = 'UINT32')"!]
typedef uint32 Eth_BufIdxType;
[!ELSE!][!//
#define Eth_BufIdxType uint8
[!ENDIF!][!//

/*==================[macros]=================================================*/

/** \brief Invalid buffer index (i.e. max value).
 *
 * Range:
 *  - uint32 (if configuration parameter 'EthIf/EthIfPublicCfg/EthIfPublicHandleTypeEnum = UINT32')
 *  - uint8  (otherwise)
 */
[!IF "node:exists(as:modconf('EthIf')[1]/EthIfGeneral/EthIfPublicHandleTypeEnum) and
      (as:modconf('EthIf')[1]/EthIfGeneral/EthIfPublicHandleTypeEnum = 'UINT32')"!]
#define ETH_BUFIDXTYPE_INVALID ((Eth_BufIdxType) 0xFFFFFFFFU)
[!ELSE!][!//
#define ETH_BUFIDXTYPE_INVALID ((Eth_BufIdxType) 0xFFU)
[!ENDIF!][!//

#endif /* ifndef ETH_GENERALTYPES_CFG_H */
/*==================[end of file]============================================*/
