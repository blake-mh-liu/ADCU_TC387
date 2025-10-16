[!VAR "NumDevices"="num:i(MemIfGeneral/MemIfNumberOfDevices)"!][!//
[!/*
 Check if the Ea and Fee is able to allow multiple instanciations
 if there are multiple configurations for these modules.
*/!][!//
[!MACRO "HEADER_NAME", "ModName" = "'Ea'"!][!/*
  */!][!VAR "Infix"!][!/*
    */!][!IF "node:exists(CommonPublishedInformation/VendorApiInfix)"!][!/*
      */!][!"CommonPublishedInformation/VendorApiInfix"!][!/*
    */!][!ENDIF!][!/*
  */!][!ENDVAR!][!/*
  */!][!"$ModName"!][!/*
    */!][!IF "$Infix != '' "!][!/*
      */!]_[!"CommonPublishedInformation/VendorId"!]_[!"$Infix"!][!/*
    */!][!ENDIF!][!/*
  */!].h[!//
[!ENDMACRO!][!//
[!//
[!//
[!//
[!MACRO "EXTEND_NAME", "ModName" = "'Ea'"!][!/*
  */!][!IF "node:exists(CommonPublishedInformation/VendorApiInfix)"!][!/*
    */!][!VAR "Name" = "concat($ModName,'_',CommonPublishedInformation/VendorId,'_',CommonPublishedInformation/VendorApiInfix)"!][!/*
  */!][!ELSE!][!/*
    */!][!VAR "Name" = "$ModName"!][!/*
  */!][!ENDIF!][!//
[!ENDMACRO!][!//
[!//
[!//
[!//
[!/* *** first build prefix-list *** */!][!//
[!//
[!VAR "Prefixes"="''"!][!//
[!IF "node:existsAndFalse(MemIfGeneral/MemIfMemAccUsage)"!][!/*
  */!][!VAR "OldDeviceIndex" ="-1"!][!/*
  */!][!VAR "NumberOfDevices"="0"!][!/*
  */!][!VAR "DEVICE_IDs" = "''"!][!/*
  */!][!LOOP "as:modconf('Eep')"!][!/*
    */!][!VAR "NumberOfDevices"="$NumberOfDevices+1"!][!/*
    */!][!IF "contains($DEVICE_IDs, concat(EepGeneral/EepDriverIndex,'_') )"!][!/*
      */!][!IF "$MemIf_InternalCfg = 'true'"!][!/*
        */!][!ERROR "There may not be two Eep memory drivers with the same device ID. Please check EepGeneral/EepDriverIndex"!][!/*
      */!][!ENDIF!][!/*
      */!][!BREAK!][!/*
    */!][!ENDIF!][!/*
    */!][!VAR "DEVICE_IDs" = "concat($DEVICE_IDs,EepGeneral/EepDriverIndex,'_')"!][!/*
  */!][!ENDLOOP!][!//
[!//
[!/*
  */!][!LOOP "as:modconf('Fls')"!][!/*
    */!][!VAR "NumberOfDevices"="$NumberOfDevices + 1"!][!/*
    */!][!IF "contains($DEVICE_IDs, concat(FlsGeneral/FlsDriverIndex,'_') )"!][!/*
      */!][!IF "$MemIf_InternalCfg = 'true'"!][!/*
        */!][!ERROR "There may not be two Fls memory drivers with the same device ID. Please check FlsGeneral/FlsDriverIndex"!][!/*
      */!][!ENDIF!][!/*
      */!][!BREAK!][!/*
    */!][!ENDIF!][!/*
    */!][!VAR "DEVICE_IDs" = "concat($DEVICE_IDs,FlsGeneral/FlsDriverIndex,'_')"!][!/*
  */!][!ENDLOOP!][!//
[!ELSE!][!/* MemAcc used
  */!][!VAR "OldMemAccAddressAreaId" ="-1"!][!/*
  */!][!VAR "NumberOfAreas"="0"!][!/*
  */!][!VAR "AREA_IDs" = "''"!][!/*
  */!][!LOOP "as:modconf('MemAcc')/MemAccAddressAreaConfiguration/eb-list::*"!][!/*
    */!][!VAR "NumberOfAreas"="$NumberOfAreas + 1"!][!/*
    */!][!IF "contains($AREA_IDs, concat(MemAccAddressAreaId,'_') )"!][!/*
      */!][!IF "$MemIf_InternalCfg = 'true'"!][!/*
        */!][!ERROR "There may not be two memory areas with the same area ID. Please check MemAcc/MemAccAddressAreaConfiguration"!][!/*
      */!][!ENDIF!][!/*
      */!][!BREAK!][!/*
    */!][!ENDIF!][!/*
    */!][!VAR "AREA_IDs" = "concat($AREA_IDs,MemAccAddressAreaId,'_')"!][!/*
  */!][!ENDLOOP!][!//
[!ENDIF!][!//
[!//
[!//
[!/*
 The relation
 MemIfGeneral/MemIfNumberOfDevices = count(as:modconf('Ea')) + count(as:modconf('Fee'))
 is also enforced by the xdm file.
*/!][!//
[!//
[!/*
*/!][!IF "num:i($NumDevices) != (count(as:modconf('Ea')) + count(as:modconf('Fee')))"!][!/*
  */!][!IF "$MemIf_InternalCfg = 'true'"!][!/*
    */!][!ERROR "Number of devices must match the configured Ea and Fee devices"!][!/*
  */!][!ENDIF!][!/*
*/!][!ENDIF!][!//
[!//
[!//
[!IF "node:existsAndFalse(MemIfGeneral/MemIfMemAccUsage)"!][!/*
  */!][!IF "$NumberOfDevices > 1"!][!/*
    */!][!VAR "Driver"="''"!][!/*
    */!][!VAR "ListDrivers"="''"!][!//
[!/* *** If more than 1 device is present perform validity checks *** */!][!//
[!/*    !LINKSTO MemIf.MEMIF_018_3,2
        !LINKSTO MemIf.MEMIF_018_4,2 */!][!/*
    */!][!LOOP "as:modconf('Ea')"!][!/*
      */!][!VAR "Driver" = "EaBlockConfiguration/eb-list::*[1]/EaDeviceIndex"!][!/*
[!/* *** All the blocks of Ea must link the same driver *** */!][!/*
      */!][!LOOP "EaBlockConfiguration/eb-list::*"!][!/*
        */!][!IF "node:refvalid( ./EaDeviceIndex )"!][!/*
          */!][!IF "string($Driver) != ./EaDeviceIndex "!][!/*
            */!][!IF "$MemIf_InternalCfg = 'true'"!][!/*
              */!][!ERROR!][!/*
                */!]A hardware abstraction module may not have blocks in two EEP driver modules. References unequal [!"$Driver"!] != [!"(./EaDeviceIndex)"!][!/*
              */!][!ENDERROR!][!/*
            */!][!ENDIF!][!/*
            */!][!BREAK!][!/*
          */!][!ENDIF!][!/*
        */!][!ELSE!][!/*
          */!][!IF "$MemIf_InternalCfg = 'true'"!][!/*
            */!][!ERROR!][!/*
              */!]Field EaDeviceIndex must hold reference to the device this block is stored in.[!/*
            */!][!ENDERROR!][!/*
          */!][!ENDIF!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDLOOP!][!/*
      */!][!IF "contains($ListDrivers,$Driver)"!][!/*
        */!][!IF "$MemIf_InternalCfg = 'true'"!][!/*
          */!][!ERROR!][!/*
            */!]MEMIF cannot map two hardware abstraction modules to the same driver! [!"$Driver"!] referenced more than once![!/*
          */!][!ENDERROR!][!/*
        */!][!ENDIF!][!/*
        */!][!BREAK!][!/*
      */!][!ENDIF!][!/*
      */!][!VAR "ListDrivers" = "concat($ListDrivers,'_',$Driver)"!][!/*
    */!][!ENDLOOP!][!/*

    */!][!LOOP "as:modconf('Fee')"!][!/*
[!/* *** All the blocks of Fee must link the same driver *** */!][!/*
      */!][!VAR "Driver" = "FeeBlockConfiguration/eb-list::*[1]/FeeDeviceIndex"!][!/*
      */!][!LOOP "FeeBlockConfiguration/eb-list::*"!][!/*
        */!][!IF "node:refvalid( ./FeeDeviceIndex )"!][!/*
          */!][!IF "string($Driver) != ./FeeDeviceIndex "!][!/*
            */!][!IF "$MemIf_InternalCfg = 'true'"!][!/*
              */!][!ERROR!][!/*
                */!]A hardware abstraction module may not have blocks in two FLS driver modules. References unequal [!"$Driver"!] != [!"(./FeeDeviceIndex)"!][!/*
              */!][!ENDERROR!][!/*
            */!][!ENDIF!][!/*
            */!][!BREAK!][!/*
          */!][!ENDIF!][!/*
        */!][!ELSE!][!/*
          */!][!IF "$MemIf_InternalCfg = 'true'"!][!/*
            */!][!ERROR!][!/*
              */!]Field FeeDeviceIndex must hold reference to the device this block is stored in.[!/*
            */!][!ENDERROR!][!/*
          */!][!ENDIF!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDLOOP!][!/*
      */!][!IF "contains($ListDrivers,$Driver)"!][!/*
        */!][!IF "$MemIf_InternalCfg = 'true'"!][!/*
          */!][!ERROR!][!/*
            */!]MEMIF cannot map two hardware abstraction modules to the same driver! [!"$Driver"!] referenced more than once![!/*
          */!][!ENDERROR!][!/*
        */!][!ENDIF!][!/*
        */!][!BREAK!][!/*
      */!][!ENDIF!][!/*
      */!][!VAR "ListDrivers" = "concat($ListDrivers,'_',$Driver)"!][!/*
    */!][!ENDLOOP!][!/*
  */!][!ENDIF!][!/*
*/!][!ELSE!][!/*
  */!][!IF "$NumberOfAreas > 1"!][!/*
    */!][!VAR "MemoryArea"="''"!][!/*
    */!][!VAR "ListAreas"="''"!][!//
[!/* *** If more than 1 area is present perform validity checks *** */!][!//
[!/*    !LINKSTO MemIf.MEMIF_018_3_MemAcc,1
        !LINKSTO MemIf.MEMIF_018_4_MemAcc,1 */!][!/*
      */!][!LOOP "as:modconf('Ea')"!][!/*
        */!][!VAR "MemoryArea" = "EaBlockConfiguration/eb-list::*[1]/EaMemAccAddressArea"!][!//
[!/* *** All the blocks of Ea must link the same memory area *** */!][!/*
        */!][!LOOP "EaBlockConfiguration/eb-list::*"!][!/*
          */!][!IF "node:refvalid( ./EaMemAccAddressArea )"!][!/*
            */!][!IF "string($MemoryArea) != ./EaMemAccAddressArea "!][!/*
              */!][!IF "$MemIf_InternalCfg = 'true'"!][!/*
                */!][!ERROR!][!/*
                  */!]A hardware abstraction module may not have blocks in two memory areas. References unequal [!"$MemoryArea"!] != [!"(./EaMemAccAddressArea)"!][!/*
                */!][!ENDERROR!][!/*
              */!][!ENDIF!][!/*
              */!][!BREAK!][!/*
            */!][!ENDIF!][!/*
          */!][!ELSE!][!/*
            */!][!IF "$MemIf_InternalCfg = 'true'"!][!/*
              */!][!ERROR!][!/*
                */!]Field EaMemAccAddressArea must hold reference to the memory area this block is stored in.[!/*
              */!][!ENDERROR!][!/*
            */!][!ENDIF!][!/*
          */!][!ENDIF!][!/*
        */!][!ENDLOOP!][!/*
        */!][!IF "contains($ListAreas,$MemoryArea)"!][!/*
          */!][!IF "$MemIf_InternalCfg = 'true'"!][!/*
            */!][!ERROR!][!/*
              */!]MEMIF cannot map two hardware abstraction modules to the same memory area! [!"$MemoryArea"!] referenced more than once![!/*
            */!][!ENDERROR!][!/*
          */!][!ENDIF!][!/*
          */!][!BREAK!][!/*
        */!][!ENDIF!][!/*
        */!][!VAR "ListAreas" = "concat($ListAreas,'_',$MemoryArea)"!][!/*
      */!][!ENDLOOP!][!/*

      */!][!LOOP "as:modconf('Fee')"!][!/*
        */!][!VAR "MemoryArea" = "FeeBlockConfiguration/eb-list::*[1]/FeeMemAccAddressArea"!][!//
[!/* *** All the blocks of Fee must link the same memory area *** */!][!/*
        */!][!LOOP "FeeBlockConfiguration/eb-list::*"!][!/*
          */!][!IF "node:refvalid( ./FeeMemAccAddressArea )"!][!/*
            */!][!IF "string($MemoryArea) != ./FeeMemAccAddressArea "!][!/*
              */!][!IF "$MemIf_InternalCfg = 'true'"!][!/*
                */!][!ERROR!][!/*
                  */!]A hardware abstraction module may not have blocks in two memory areas. References unequal [!"$MemoryArea"!] != [!"(./FeeMemAccAddressArea)"!][!/*
                */!][!ENDERROR!][!/*
              */!][!ENDIF!][!/*  
              */!][!BREAK!][!/*
            */!][!ENDIF!][!/*
          */!][!ELSE!][!/*
            */!][!IF "$MemIf_InternalCfg = 'true'"!][!/*
              */!][!ERROR!][!/*
                */!]Field FeeMemAccAddressArea must hold reference to the memory area this block is stored in.[!/*
              */!][!ENDERROR!][!/*
            */!][!ENDIF!][!/*
          */!][!ENDIF!][!/*
        */!][!ENDLOOP!][!/*
        */!][!IF "contains($ListAreas,$MemoryArea)"!][!/*
          */!][!IF "$MemIf_InternalCfg = 'true'"!][!/*
            */!][!ERROR!][!/*
              */!]MEMIF cannot map two hardware abstraction modules to the same memory area! [!"$MemoryArea"!] referenced more than once![!/*
            */!][!ENDERROR!][!/*
          */!][!ENDIF!][!/*
          */!][!BREAK!][!/*
        */!][!ENDIF!][!/*
        */!][!VAR "ListAreas" = "concat($ListAreas,'_',$MemoryArea)"!][!/*
      */!][!ENDLOOP!][!/*
  */!][!ENDIF!][!//
[!ENDIF!][!//
[!//
[!IF "node:existsAndFalse(MemIfGeneral/MemIfMemAccUsage)"!][!//
[!//
[!//
[!//
[!/* Sort extended names ( abstraction name + vendor API infix) according to the ID of referenced memory area */!][!//
[!//
[!//
[!/* Search sequentially in the Eep and then in Fls for the lowest index
  "Name" variable is overwritten in the loop if a new smaller Id is found */!][!//
[!//
[!/* Gaps for missing indexes is filled with "_" marker */!][!//
[!VAR "Name"="''"!][!//
[!//
[!//
[!FOR "k" = "1" TO "$NumberOfDevices"!][!/*
  */!][!VAR "NewDeviceIndex" = "65536"!][!/*
  */!][!VAR "Infix"= "''"!][!/*
  */!][!LOOP "as:modconf('Eep')"!][!/*
    */!][!IF "(number($NewDeviceIndex) > EepGeneral/EepDriverIndex) and ( number($OldDeviceIndex) < EepGeneral/EepDriverIndex )"!][!/*
      */!][!VAR "NewDeviceIndex" = "EepGeneral/EepDriverIndex"!][!/*
      */!][!VAR "Name"="''"!][!/*
      */!][!LOOP "as:modconf('Ea')"!][!/*
        */!][!IF "$NewDeviceIndex = node:value(node:ref((.)/EaBlockConfiguration/eb-list::*/EaDeviceIndex)/EepDriverIndex)"!][!/*
          */!][!CALL "EXTEND_NAME", "ModName" = "'Ea'"!][!/*
          */!][!BREAK!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDLOOP!][!/*
    */!][!ENDIF!][!/*
  */!][!ENDLOOP!][!/*
  */!][!LOOP "as:modconf('Fls')"!][!/*
    */!][!IF "(number($NewDeviceIndex) > FlsGeneral/FlsDriverIndex) and ( number($OldDeviceIndex) < FlsGeneral/FlsDriverIndex )"!][!/*
      */!][!VAR "NewDeviceIndex" = "FlsGeneral/FlsDriverIndex"!][!/*
      */!][!VAR "Name"="''"!][!/*
      */!][!LOOP "as:modconf('Fee')"!][!/*
        */!][!IF "$NewDeviceIndex = node:value(node:ref((.)/FeeBlockConfiguration/eb-list::*/FeeDeviceIndex)/FlsDriverIndex)"!][!/*
          */!][!CALL "EXTEND_NAME", "ModName" = "'Fee'"!][!/*
          */!][!BREAK!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDLOOP!][!/*
    */!][!ENDIF!][!/*
  */!][!ENDLOOP!][!//
[!/* *** Fill missing indexes with null pointer so NVM and driver indexes match *** */!][!/*
  */!][!FOR "z" = "$OldDeviceIndex + 2" TO "$NewDeviceIndex"!][!/*
    */!][!VAR "Prefixes" = "concat($Prefixes,';&',"",'_')"!][!/*
  */!][!ENDFOR!][!/*
  */!][!VAR "Prefixes" = "concat($Prefixes,';&',$Name,'_')"!][!/*
  */!][!VAR "OldDeviceIndex" = "$NewDeviceIndex"!][!/*
*/!][!ENDFOR!][!//
[!VAR "Prefixes" = "substring-after($Prefixes, ';')"!][!//
[!ELSE!][!//
[!//
[!//
[!//
[!/* Sort extended names ( abstraction name + vendor API infix) according to the ID of referenced memory area */!][!//
[!//
[!//
[!/* Search sequentially in the MemAcc for the lowest index
   "Name" variable is overwritten in the loop if a new smaller Id is found */!][!//
[!//
[!/* Gaps for missing indexes is filled with "_" marker */!][!//
[!VAR "Name"="''"!][!//
[!//
[!//
[!FOR "k" = "1" TO "$NumberOfAreas"!][!/*
  */!][!VAR "NewMemAccAddressAreaId" = "65536"!][!/*
  */!][!VAR "Infix"= "''"!][!/*
  */!][!LOOP "as:modconf('MemAcc')/MemAccAddressAreaConfiguration/eb-list::*"!][!/*
    */!][!IF "(number($NewMemAccAddressAreaId) > MemAccAddressAreaId) and (number($OldMemAccAddressAreaId) < MemAccAddressAreaId )"!][!/*
      */!][!VAR "NewMemAccAddressAreaId" = "MemAccAddressAreaId"!][!/*
      */!][!VAR "Name"="''"!][!/*
      */!][!LOOP "as:modconf('Ea')"!][!/*
        */!][!IF "$NewMemAccAddressAreaId = node:value(node:ref((.)/EaBlockConfiguration/eb-list::*/EaMemAccAddressArea)/MemAccAddressAreaId)"!][!/*
          */!][!CALL "EXTEND_NAME", "ModName" = "'Ea'"!][!/*
          */!][!BREAK!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDLOOP!][!/*
      */!][!LOOP "as:modconf('Fee')"!][!/*
        */!][!IF "$NewMemAccAddressAreaId = node:value(node:ref((.)/FeeBlockConfiguration/eb-list::*/FeeMemAccAddressArea)/MemAccAddressAreaId)"!][!/*
          */!][!CALL "EXTEND_NAME", "ModName" = "'Fee'"!][!/*
          */!][!BREAK!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDLOOP!][!/*
    */!][!ENDIF!][!/*
  */!][!ENDLOOP!][!//
[!/* *** Fill missing indexes with null pointer so NVM and driver indexes match *** */!][!/*
  */!][!FOR "z" = "$OldMemAccAddressAreaId + 2" TO "$NewMemAccAddressAreaId"!][!/*
    */!][!VAR "Prefixes" = "concat($Prefixes,';&',"",'_')"!][!/*
  */!][!ENDFOR!][!/*
  */!][!VAR "Prefixes" = "concat($Prefixes,';&',$Name,'_')"!][!/*
  */!][!VAR "OldMemAccAddressAreaId" = "$NewMemAccAddressAreaId"!][!/*
*/!][!ENDFOR!][!//
[!VAR "Prefixes" = "substring-after($Prefixes, ';')"!][!//
[!ENDIF!][!//
