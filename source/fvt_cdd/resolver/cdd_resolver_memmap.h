/*==================[inclusions]=============================================*/

#define MEMMAP_ERROR_CDD_RESOLVER

/*------------------[Start of a module]--------------------------------------*/

/* Memory section macros for CDD_RESOLVER */

#if (defined CDD_RESOLVER_START_SEC_CODE)
  #ifdef MEMMAP_SECTION_OPENED
    #undef MEMMAP_ERROR_CDD_RESOLVER
    #error Tried to open section CDD_RESOLVER_START_SEC_CODE within an already open section.
  #else
    #pragma section code "pspr1"
    #define MEMMAP_SECTION_OPENED
    #define MEMMAP_SECTION_OPENED_STARTSEC_CODE
    #undef CDD_RESOLVER_START_SEC_CODE
    #undef MEMMAP_ERROR_CDD_RESOLVER
  #endif
#elif (defined CDD_RESOLVER_STOP_SEC_CODE)
  #if (defined MEMMAP_SECTION_OPENED) && (defined MEMMAP_SECTION_OPENED_STARTSEC_CODE)
    #pragma section code restore
    #undef MEMMAP_SECTION_OPENED
    #undef MEMMAP_SECTION_OPENED_STARTSEC_CODE
    #undef CDD_RESOLVER_STOP_SEC_CODE
    #undef MEMMAP_ERROR_CDD_RESOLVER
  #else
    #undef MEMMAP_ERROR_CDD_RESOLVER
    #error Tried to close section CDD_RESOLVER_STOP_SEC_CODE without prior opening CDD_RESOLVER_STOP_SEC_CODE.
  #endif
#endif

#ifdef MEMMAP_ERROR_CDD_RESOLVER
  #undef MEMMAP_ERROR_CDD_RESOLVER
  #error MEMMAP_ERROR_CDD_RESOLVER the included memory section was not defined within the SWC-IMPLEMENTATION of CDD_RESOLVER_GLOBAL.
#endif
