[!/*****************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : FlsLoader_Cfg.c                                               **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE      : 2019-05-23                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : FlsLoader.bmd                                     **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID= {085B0C5A-211D-4994-95F9-C73F09E104C7}]   **
**                                                                            **
**  DESCRIPTION  : Code template source file for FlsLoader Driver             **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!]
[!//
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2018)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : FlsLoader_Cfg.c                                               **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]              !!!IGNORE-LINE!!!           **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                !!!IGNORE-LINE!!!           **
**                                                                            **
**  BSW MODULE DECRIPTION : FlsLoader.bmd                                     **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : FlsLoader configuration generated out of ECUC file         **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/


/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
  /* Inclusion of Flash header file */
#include "FlsLoader.h"
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/******************************************************************************/
/*******************************************************************************
** Name             : FlsLoader_GenerateModuleMap                             **
**                                                                            **
** Description      : Macro to generate core-channel mappings for a module    **
**                                                                            **
*******************************************************************************/
[!/* [cover parentID={085B0C5A-211D-4994-95F9-C73F09E104C7}]
[/cover] */!]

[!INDENT "0"!][!//
  [!SELECT "as:modconf('FlsLoader')[1]"!][!//
    [!NOCODE!][!//
      [!VAR "NumPFBank" = "ecu:get('FlsLoader.PfBank')"!][!//
    [!ENDNOCODE!][!//

    [!/* [cover parentID={C829DF02-56F2-4e35-8652-24A8516EF825}]
    [/cover] */!]
    #define FLSLOADER_START_SEC_CONST_QM_LOCAL_8
    /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
    [!INDENT "3"!][!//
      without safegaurd. It complies to Autosar guidelines. */
    [!ENDINDENT!][!//
    #include "FlsLoader_MemMap.h"

    [!/* [cover parentID={E0DC3BE3-1081-4c90-9189-F295DBE16C2D}]
    [/cover] */!][!//
    /* Number of sectors for each PFlash banks */
    const uint8 FlsLoader_PFlashSectorCount[FLSLOADER_NUM_OF_PFLASH_BANK] =
    {
    [!NOCODE!][!//
      [!FOR "BankCount" = "num:i(0)" TO "num:i($NumPFBank) - num:i(1)"!][!//
        [!CODE!][!//
          [!INDENT "4"!][!//
            FLSLOADER_NUM_OF_PF[!"$BankCount"!]_SECTORS[!//
            [!IF "$BankCount < ($NumPFBank - num:i(1))"!][!//
              ,[!//
            [!ENDIF!]
          [!ENDINDENT!][!//
        [!ENDCODE!][!//
      [!ENDFOR!][!//
    [!ENDNOCODE!][!//
    };

    #define FLSLOADER_STOP_SEC_CONST_QM_LOCAL_8
    /* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function 
    [!INDENT "2"!][!//
      before MemMap inclusion It complies to Autosar guidelines. */
    [!ENDINDENT!][!//
    /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
    [!INDENT "3"!][!//
      without safegaurd. It complies to Autosar guidelines. */
    [!ENDINDENT!][!//
    #include "FlsLoader_MemMap.h"

    [!/* [cover parentID={C829DF02-56F2-4e35-8652-24A8516EF825}]
    [/cover] */!]
    #define FLSLOADER_START_SEC_CONST_QM_LOCAL_32
    /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
    [!INDENT "3"!][!//
      without safegaurd. It complies to Autosar guidelines. */
    [!ENDINDENT!][!//
    #include "FlsLoader_MemMap.h"

    [!/* [cover parentID={887DA0A3-E610-4232-8D92-D4A3235AEE8F}]
    [/cover] */!][!//
    /* Start address of all the PFlash banks */
    const uint32 FlsLoader_PFlashOffset[FLSLOADER_NUM_OF_PFLASH_BANK] =
    {
    [!NOCODE!][!//
      [!FOR "BankCount" = "num:i(0)" TO "num:i($NumPFBank) - num:i(1)"!][!//
        [!VAR "Sector" = "text:join(concat('FlsLoader.Pf', $BankCount, 'StartAddress'))"!]
        [!CODE!][!//
          [!INDENT "4"!][!//
            (uint32)[!"text:toupper(num:inttohex(ecu:get($Sector)))"!]U[!//
            [!IF "$BankCount < ($NumPFBank - num:i(1))"!][!//
              ,[!//
            [!ENDIF!]
          [!ENDINDENT!][!//
        [!ENDCODE!][!//
      [!ENDFOR!][!//
    [!ENDNOCODE!][!//
    };

    [!IF "FlsLoaderGeneral/FlsLoaderDevErrorDetect = 'true'"!][!//
      [!/* [cover parentID={5A243A8F-C699-455f-84E6-5A94BC1C19E4}]
      [/cover] */!][!//
      /* End address of all the PFlash banks */
      const uint32 FlsLoader_PFlashEndAddress[FLSLOADER_NUM_OF_PFLASH_BANK] =
      {
      [!NOCODE!][!//
        [!FOR "BankCount" = "num:i(0)" TO "num:i($NumPFBank) - num:i(1)"!][!//
          [!VAR "Sector" = "text:join(concat('FlsLoader.Pf', $BankCount, 'EndAddress'))"!]
          [!CODE!][!//
            [!INDENT "4"!][!//
            (uint32)[!"text:toupper(num:inttohex(ecu:get($Sector)))"!]U[!//
            [!IF "$BankCount < ($NumPFBank - num:i(1))"!][!//
              ,[!//
            [!ENDIF!]
            [!ENDINDENT!][!//
          [!ENDCODE!][!//
        [!ENDFOR!][!//
      [!ENDNOCODE!][!//
      };

    [!ENDIF!][!//
    [!NOCODE!]
      [!VAR "CallOutFunc" = "FlsLoaderGeneral/FlsLoaderCallOutFunction"!]
      [!IF "$CallOutFunc != 'NULL_PTR'"!][!//
        [!IF "not(num:isnumber($CallOutFunc))"!]
          [!CODE!][!//
            /* Function pointer to user defined call out function*/
            const FlsLoader_CallOutFunc FlsLoader_CallOutPtr = &[!"$CallOutFunc"!];
          [!ENDCODE!]
        [!ELSE!]
          [!IF "(num:radixtoint($CallOutFunc) < num:i(1)) or (num:radixtoint($CallOutFunc) > num:i(4294967295))"!]
            [!ERROR!]
              FlsLoaderCallOutFunction address value should be within 1 to maximum 32-bit range.
            [!ENDERROR!]
          [!ELSE!]
            [!CODE!][!//

              [!/* [cover parentID={EED4AEA7-29D5-49a7-871F-99E96A9536E6}]
              [/cover] */!]
              /* Function pointer to user defined call out function*/
              const FlsLoader_CallOutFunc FlsLoader_CallOutPtr = \
                                        (FlsLoader_CallOutFunc) [!"text:toupper(num:inttohex(num:radixtoint($CallOutFunc), 8))"!]U;
            [!ENDCODE!]
          [!ENDIF!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDNOCODE!][!//

    #define FLSLOADER_STOP_SEC_CONST_QM_LOCAL_32
    /* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function 
    [!INDENT "2"!][!//
      before MemMap inclusion It complies to Autosar guidelines. */
    [!ENDINDENT!][!//
    /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
    [!INDENT "3"!][!//
      without safegaurd. It complies to Autosar guidelines. */
    [!ENDINDENT!][!//
    #include "FlsLoader_MemMap.h"
  [!ENDSELECT!][!//
[!ENDINDENT!][!//
