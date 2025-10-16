[!INCLUDE "Nm_Functions.m"!]
[!VAR "EmptyTranslationUnitNeeded" = "'true'"!]
[!CALL "SetupSynchronizedPncShutdownVariables"!]
[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]
  [!IF "(node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmSynchronizedPncShutdownEnabled))"!]  
  [!IF "count(text:split($BusNames,' ')) > 0"!]        
#include <TSAutosar.h>                     /* EB specific standard types */
#include <SchM_Nm.h>
#include <Nm_Cbk.h>
#include <Nm.h>
#include <Nm_Int.h>
    [!FOR "BusId" = "1" TO "count(text:split($BusNames,' '))"!]
      [!VAR "CurrentBusName" = "text:split($BusNames,' ')[position() = $BusId]"!]        
      [!VAR "QueueSize" = "text:split($BusNrOfPassiveChannels,' ')[position() = $BusId]"!]
      [!IF "num:i($QueueSize) > 0"!]       
#define NM_START_SEC_CODE
#include <Nm_MemMap.h>      
FUNC(void, NM_CODE) Nm_ForwardSynchronizedPncShutdown_[!"$CurrentBusName"!]_To_Nm_RcvFnct (void)
{
  Nm_PnSyncShutdown_BusNm_To_Nm_DataType data;
  while (SchM_Receive_Nm_Nm_ForwardSynchronizedPncShutdown_[!"$CurrentBusName"!]_To_Nm_DataGet(&data) == SCHM_E_OK)
  {
    Nm_ForwardSynchronizedPncShutdown(data.Channel, data.PnInfo);
  }
}
#define NM_STOP_SEC_CODE
#include <Nm_MemMap.h>      
          [!VAR "EmptyTranslationUnitNeeded" = "'false'"!]
      [!ENDIF!] [!/* [!IF "num:i($QueueSize) > 0"!]  */!]
    [!ENDFOR!] [!/*[!FOR "BusId" = "1" TO "count(text:split($BusNames,' '))"!]*/!]
  [!ENDIF!] [!/*[!IF "count(text:split($BusNames,' ')) > 0"!]*/!]
[!ENDIF!] [!/* [!IF "(node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmSynchronizedPncShutdownEnabled))"!]  
               */!]
[!ENDIF!] [!/*[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]*/!]

[!IF "$EmptyTranslationUnitNeeded = 'true'"!]

#include <TSCompiler.h>

TS_PREVENTEMPTYTRANSLATIONUNIT

[!ENDIF!] [!/*[!IF "$EmptyTranslationUnitNeeded = 'true'"!]*/!]
