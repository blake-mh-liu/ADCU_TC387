/*==================[inclusions]=============================================*/

#define MEMMAP_ERROR_CDD_ADC

/*------------------[Start of a module]--------------------------------------*/

/* Memory section macros for CDD_ADC */

#if (defined CDD_ADC_START_SEC_GLOBAL)
  #ifdef MEMMAP_SECTION_OPENED
    #undef MEMMAP_ERROR_CDD_ADC
    #error Tried to open section CDD_ADC_START_SEC_GLOBAL within an already open section.
  #else
    #pragma section fardata "data_lmu0"
    #pragma section farbss "bss_lmu0"
    #define MEMMAP_SECTION_OPENED
    #define MEMMAP_SECTION_OPENED_STARTSEC_GLOBAL
    #undef CDD_ADC_START_SEC_GLOBAL
    #undef MEMMAP_ERROR_CDD_ADC
  #endif
#elif (defined CDD_ADC_STOP_SEC_GLOBAL)
  #if (defined MEMMAP_SECTION_OPENED) && (defined MEMMAP_SECTION_OPENED_STARTSEC_GLOBAL)
    #pragma section fardata restore
    #pragma section farbss restore
    #undef MEMMAP_SECTION_OPENED
    #undef MEMMAP_SECTION_OPENED_STARTSEC_GLOBAL
    #undef CDD_ADC_STOP_SEC_GLOBAL
    #undef MEMMAP_ERROR_CDD_ADC
  #else
    #undef MEMMAP_ERROR_CDD_ADC
    #error Tried to close section CDD_ADC_STOP_SEC_GLOBAL without prior opening CDD_ADC_START_SEC_GLOBAL.
  #endif

#elif (defined CDD_ADC_START_SEC_CORE1)
  #ifdef MEMMAP_SECTION_OPENED
    #undef MEMMAP_ERROR_CDD_ADC
    #error Tried to open section CDD_ADC_START_SEC_CORE1 within an already open section.
  #else
    #pragma section fardata "data_core1"
    #pragma section farbss "bss_core1"
    #define MEMMAP_SECTION_OPENED
    #define MEMMAP_SECTION_OPENED_STARTSEC_CORE1
    #undef CDD_ADC_START_SEC_CORE1
    #undef MEMMAP_ERROR_CDD_ADC
  #endif
#elif (defined CDD_ADC_STOP_SEC_CORE1)
  #if (defined MEMMAP_SECTION_OPENED) && (defined MEMMAP_SECTION_OPENED_STARTSEC_CORE1)
    #pragma section fardata restore
    #pragma section farbss restore
    #undef MEMMAP_SECTION_OPENED
    #undef MEMMAP_SECTION_OPENED_STARTSEC_CORE1
    #undef CDD_ADC_STOP_SEC_CORE1
    #undef MEMMAP_ERROR_CDD_ADC
  #else
    #undef MEMMAP_ERROR_CDD_ADC
    #error Tried to close section CDD_ADC_STOP_SEC_CORE1 without prior opening CDD_ADC_START_SEC_CORE1.
  #endif

#elif (defined CDD_ADC_START_SEC_CODE_CORE0)
  #ifdef MEMMAP_SECTION_OPENED
    #undef MEMMAP_ERROR_CDD_ADC
    #error Tried to open section CDD_ADC_START_SEC_CODE_CORE0 within an already open section.
  #else
    #pragma section code "pspr0"
    #define MEMMAP_SECTION_OPENED
    #define MEMMAP_SECTION_OPENED_STARTSEC_CODE_CORE0
    #undef CDD_ADC_START_SEC_CODE_CORE0
    #undef MEMMAP_ERROR_CDD_ADC
  #endif
#elif (defined CDD_ADC_STOP_SEC_CODE_CORE0)
  #if (defined MEMMAP_SECTION_OPENED) && (defined MEMMAP_SECTION_OPENED_STARTSEC_CODE_CORE0)
    #pragma section code restore
    #undef MEMMAP_SECTION_OPENED
    #undef MEMMAP_SECTION_OPENED_STARTSEC_CODE_CORE0
    #undef CDD_ADC_STOP_SEC_CODE_CORE0
    #undef MEMMAP_ERROR_CDD_ADC
  #else
    #undef MEMMAP_ERROR_CDD_ADC
    #error Tried to close section CDD_ADC_STOP_SEC_CODE_CORE0 without prior opening CDD_ADC_STOP_SEC_CODE_CORE0.
  #endif

#elif (defined CDD_ADC_START_SEC_CODE_CORE1)
  #ifdef MEMMAP_SECTION_OPENED
    #undef MEMMAP_ERROR_CDD_ADC
    #error Tried to open section CDD_ADC_START_SEC_CODE_CORE1 within an already open section.
  #else
    #pragma section code "pspr1"
    #define MEMMAP_SECTION_OPENED
    #define MEMMAP_SECTION_OPENED_STARTSEC_CODE_CORE1
    #undef CDD_ADC_START_SEC_CODE_CORE1
    #undef MEMMAP_ERROR_CDD_ADC
  #endif
#elif (defined CDD_ADC_STOP_SEC_CODE_CORE1)
  #if (defined MEMMAP_SECTION_OPENED) && (defined MEMMAP_SECTION_OPENED_STARTSEC_CODE_CORE1)
    #pragma section code restore
    #undef MEMMAP_SECTION_OPENED
    #undef MEMMAP_SECTION_OPENED_STARTSEC_CODE_CORE1
    #undef CDD_ADC_STOP_SEC_CODE_CORE1
    #undef MEMMAP_ERROR_CDD_ADC
  #else
    #undef MEMMAP_ERROR_CDD_ADC
    #error Tried to close section CDD_ADC_STOP_SEC_CODE_CORE1 without prior opening CDD_ADC_STOP_SEC_CODE_CORE1.
  #endif
#endif

#ifdef MEMMAP_ERROR_CDD_ADC
  #undef MEMMAP_ERROR_CDD_ADC
  #error MEMMAP_ERROR_CDD_ADC the included memory section was not defined within the SWC-IMPLEMENTATION of CDD_ADC.
#endif
