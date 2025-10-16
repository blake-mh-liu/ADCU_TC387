/**
 * \file
 *
 * \brief AUTOSAR LinIf
 *
 * This file contains the implementation of the AUTOSAR
 * module LinIf.
 *
 * \version 5.8.50
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#ifndef LINIF_SYMBOLICNAMES_PBCFG_H
#define LINIF_SYMBOLICNAMES_PBCFG_H

/*==================[includes]===============================================*/

/*==================[ Macros]=================================================*/
[!INCLUDE "LinIf_Macros.m"!][!//

/* generating macros for LinIfChannel */[!/*
*/!][!LOOP "as:modconf('LinIf')[1]/LinIfGlobalConfig/*/LinIfChannel/*"!][!/*
*/!][!CALL "GetSymbolName","ShortNameRef"="'.'","OldName"="node:name(../.)"!]
/** \brief Export symbolic name value for [!"as:name(.)"!] */
#if (defined LinIfConf_[!"$SymbolName"!])
#error LinIfConf_[!"$SymbolName"!] already defined!
#endif /* #if( defined LinIfConf_[!"$SymbolName"!])*/
#define LinIfConf_[!"$SymbolName"!]                    [!"num:i(LinIfChannelId)"!]U
[!ENDLOOP!][!//


/* generating macros for TxPdu */[!/*
*/!][!LOOP "as:modconf('LinIf')[1]/LinIfGlobalConfig/*/LinIfChannel/*/LinIfFrame/*[LinIfPduDirection='LinIfTxPdu']/LinIfPduDirection"!][!/*
*/!][!CALL "GetLinIfPduSymbolName","ObjectRef"="'.'"!]
/*---------------------------[!"$SymbolName"!]-------------------------------------*/
/** \brief Export symbolic name value for AUTOSAR version 4.0 rev3 */
#if (defined LinIfConf_[!"$SymbolName"!])
#error LinIfConf_[!"$SymbolName"!] already defined!
#endif /* #if( defined LinIfConf_[!"$SymbolName"!])*/
#define LinIfConf_[!"$SymbolName"!]                   [!"LinIfTxPduId"!]U
[!ENDLOOP!][!//


/* generating macros for ScheduleTableIndex */[!/*
*/!][!LOOP "as:modconf('LinIf')[1]/LinIfGlobalConfig/*/LinIfChannel/*/LinIfScheduleTable/*[as:name(.) != 'NULL_SCHEDULE']"!][!/*
*/!][!CALL "GetSymbolName","ShortNameRef"="'.'","OldName"="node:name(..)"!]
/*---------------------------[!"$SymbolName"!]-------------------------------------*/
/** \brief Export symbolic name value for AUTOSAR version 4.0 rev3 */
#if (defined LinIfConf_[!"$SymbolName"!])
#error LinIfConf_[!"$SymbolName"!] already defined!
#endif /* #if( defined LinIfConf_[!"$SymbolName"!])*/
#define LinIfConf_[!"$SymbolName"!]                   [!"LinIfScheduleTableIndex"!]U
[!ENDLOOP!][!//


/* Frame macros - generated for backwards compatibility*/[!/*
*/!]
[!VAR "I"="0"!][!/*
*/!][!LOOP "as:modconf('LinIf')[1]/LinIfGlobalConfig/*[1]/LinIfChannel/*"!][!/*
*/!][!LOOP "LinIfFrame/*[LinIfFrameType='UNCONDITIONAL' and LinIfPduDirection='LinIfRxPdu']"!][!/*
  */!][!IF "node:exists('LinIfFrameName')"!]
#if (defined [!"LinIfFrameName"!])
#error [!"LinIfFrameName"!] already defined!
#endif /* #if( defined [!"LinIfFrameName"!])*/
#define [!"LinIfFrameName"!] [!"num:i($I)"!]U[!/*
  */!][!ELSE!][!/* default for compatibility with previous versions */!]
#if (defined LINIF_FRAME_[!"as:name(../..)"!]_[!"as:name(.)"!])
#error LINIF_FRAME_[!"as:name(../..)"!]_[!"as:name(.)"!] already defined!
#endif /* #if( defined LINIF_FRAME_[!"as:name(../..)"!]_[!"as:name(.)"!]*/
#define LINIF_FRAME_[!"as:name(../..)"!]_[!"as:name(.)"!] [!"num:i($I)"!]U[!/*
  */!][!ENDIF!][!/*
  */!][!VAR "I"="$I + 1"!][!/*
  */!][!ENDLOOP!][!/*
*/!][!ENDLOOP!]



#endif /* ifndef LINIF_SYMBOLICNAMES_PBCFG_H */
/*==================[end of file]============================================*/
