[!/**
 * \file
 *
 * \brief AUTOSAR Crypto
 *
 * This file contains the implementation of the AUTOSAR
 * module Crypto.
 *
 * \version 2.0.39
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */!][!//
[!/* ---------------------------------------------------------------------------------------*/!][!//
[!//
[!/* *** multiple inclusion protection *** */!][!//
[!IF "not(var:defined('CRYPTO_XVIX_XAIX_MACROS_M'))"!][!//
[!VAR "CRYPTO_XVIX_XAIX_MACROS_M" = "'true'"!][!//
[!INDENT "0"!][!//
[!//
[!/* ---------------------------------------------------------------------------------------*/!][!//
[!//
[!VAR "WS" = "'                                                                             '"!][!//
[!//
[!/*
****************************************************************************************************
* MACRO to get all discrete primitives referenced to all Crypto Driver Objects as strings.
* Each string contains a space separated list of primitive patterns '<service>_<family>_<mode>'.
* Per string an individual representation of the pattern is used.
* All elements in the PrimitivesPoolListLong are named according to their ECUC requirement.
* (s:Crypto.Asr.ECUC_Crypto_00034, f:Crypto.Asr.ECUC_Crypto_00035, m:Crypto.Asr.ECUC_Crypto_00036)
*
* PrimitivesPoolListLong, e.g. [HASH|CRYPTO_ALGOFAM_SHA2_256|CRYPTO_ALGOMOD_NOT_SET ENCRYPT|CRYPTO_ALGOFAM_AES|CRYPTO_ALGOMOD_ECB ...]
* PrimitivesPoolListShrt, e.g. [HASH_SHA2256_NOTSET ENCRYPT_AES_ECB ...]
****************************************************************************************************
*/!][!//
[!//
[!MACRO "GetPrimitivesPoolList", "ctr"!][!//
  [!//
  [!VAR "PrimitivesPoolListShrt" = "''"!][!//
  [!VAR "PrimitivesPoolListLong" = "''"!][!//
  [!VAR "PrimitivesPoolListSize" = "num:i(0)"!][!//
  [!SELECT "node:ref($ctr)"!][!//
    [!/*------------------------------------------------------------------------------------*/!][!//
    [!/* get primitives                                                                     */!][!//
    [!LOOP "eb-list::*/eb-list::*/CryptoPrimitiveRef/eb-list::*"!][!//
      [!VAR "ps" = "node:value(node:ref(.)/CryptoPrimitiveService)"!][!//
      [!VAR "pf" = "node:value(node:ref(.)/CryptoPrimitiveAlgorithmFamiliy/eb-list::*[node:pos(.)=0])"!][!//
      [!VAR "pm" = "node:value(node:ref(.)/CryptoPrimitiveAlgorithmMode/eb-list::*[node:pos(.)=0])"!][!//
      [!VAR "sf" = "node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0])"!][!//
      [!VAR "vs" = "'EMPTY'"!][!//
      [!VAR "vf" = "'EMPTY'"!][!//
      [!VAR "vm" = "'EMPTY'"!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!IF "($ps = 'RANDOM')"!][!VAR "ps" = "'RANDOMGENERATE'"!][!ENDIF!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!/* !!! NOTE: This test is performed for robustness only.
           !!!       It shall be ensured via the module pre-configuration that only HASHes are
           !!!       used as secondary family.
           !!!       In the SCov this path should always be uncovered.
      */!][!//
      [!IF "$sf != 'CRYPTO_ALGOFAM_NOT_SET'       and
            $sf != 'CRYPTO_ALGOFAM_BLAKE_1_512'   and
            $sf != 'CRYPTO_ALGOFAM_BLAKE_2s_256'  and
            $sf != 'CRYPTO_ALGOFAM_BLAKE_2s_512'  and
            $sf != 'CRYPTO_ALGOFAM_RIPEMD160'     and
            $sf != 'CRYPTO_ALGOFAM_SHA1'          and
            $sf != 'CRYPTO_ALGOFAM_SHA2_224'      and
            $sf != 'CRYPTO_ALGOFAM_SHA2_256'      and
            $sf != 'CRYPTO_ALGOFAM_SHA2_384'      and
            $sf != 'CRYPTO_ALGOFAM_SHA2_512'      and
            $sf != 'CRYPTO_ALGOFAM_SHA2_512_224'  and
            $sf != 'CRYPTO_ALGOFAM_SHA2_512_256'  and
            $sf != 'CRYPTO_ALGOFAM_SHA3_224'      and
            $sf != 'CRYPTO_ALGOFAM_SHA3_256'      and
            $sf != 'CRYPTO_ALGOFAM_SHA3_384'      and
            $sf != 'CRYPTO_ALGOFAM_SHA3_512'      and
            $sf != 'CRYPTO_ALGOFAM_SHAKE128'      and
            $sf != 'CRYPTO_ALGOFAM_SHAKE256'      and
            $sf != 'CRYPTO_ALGOFAM_PADDING_PKCS7' and
            $sf != 'CRYPTO_ALGOFAM_PADDING_TLS12'"!][!//
        [!ERROR!][!//
          [!"$ps"!].[!"$pf"!].[!"$pm"!] uses an not allowed secondary primitive family. Allowed are NOTSET, HASHes and PADDINGs.
        [!ENDERROR!][!//
      [!ENDIF!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!/* add BlockCipher ECB mode if a BlockCipher without ECB is configured              */!][!//
      [!IF "($ps = 'ENCRYPT'                                          ) and
            ($pf = 'CRYPTO_ALGOFAM_3DES' or $pf = 'CRYPTO_ALGOFAM_AES') and
            ($pm != 'CRYPTO_ALGOMODE_ECB'                             )"!][!//
        [!VAR "vs" = "'ENCRYPT'"!][!//
        [!VAR "vf" = "node:value(node:ref(.)/CryptoPrimitiveAlgorithmFamiliy/eb-list::*[node:pos(.)=0])"!][!//
        [!VAR "vm" = "'CRYPTO_ALGOMODE_ECB'"!][!//
      [!ENDIF!][!//
      [!IF "($ps = 'DECRYPT'                                              ) and
            ($pf = 'CRYPTO_ALGOFAM_3DES'  or  $pf = 'CRYPTO_ALGOFAM_AES'  ) and
            ($pm != 'CRYPTO_ALGOMODE_ECB' and $pm != 'CRYPTO_ALGOMODE_CBC')"!][!//
        [!VAR "vs" = "'ENCRYPT'"!][!//
        [!VAR "vf" = "node:value(node:ref(.)/CryptoPrimitiveAlgorithmFamiliy/eb-list::*[node:pos(.)=0])"!][!//
        [!VAR "vm" = "'CRYPTO_ALGOMODE_ECB'"!][!//
      [!ENDIF!][!//
      [!IF "($ps = 'DECRYPT'                                          ) and
            ($pf = 'CRYPTO_ALGOFAM_3DES' or $pf = 'CRYPTO_ALGOFAM_AES') and
            ($pm = 'CRYPTO_ALGOMODE_CBC'                              )"!][!//
        [!VAR "vs" = "'DECRYPT'"!][!//
        [!VAR "vf" = "node:value(node:ref(.)/CryptoPrimitiveAlgorithmFamiliy/eb-list::*[node:pos(.)=0])"!][!//
        [!VAR "vm" = "'CRYPTO_ALGOMODE_ECB'"!][!//
      [!ENDIF!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!/* add BlockCipher ECB mode if a BlockCipher based AEAD is configured               */!][!//
      [!IF "($ps = 'AEAD_ENCRYPT'        or       $ps = 'AEAD_DECRYPT') and
            ($pf = 'CRYPTO_ALGOFAM_3DES' or $pf = 'CRYPTO_ALGOFAM_AES') and
            ($pm != 'CRYPTO_ALGOMODE_ECB'                            )"!][!//
        [!VAR "vs" = "'ENCRYPT'"!][!//
        [!VAR "vf" = "node:value(node:ref(.)/CryptoPrimitiveAlgorithmFamiliy/eb-list::*[node:pos(.)=0])"!][!//
        [!VAR "vm" = "'CRYPTO_ALGOMODE_ECB'"!][!//
      [!ENDIF!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!/* add BlockCipher ECB mode if a BlockCipher based MAC is configured                */!][!//
      [!IF "($ps = 'MAC_GENERATE'        or $ps = 'MAC_VERIFY'        ) and
            ($pf = 'CRYPTO_ALGOFAM_3DES' or $pf = 'CRYPTO_ALGOFAM_AES') and
            ($pm != 'CRYPTO_ALGOMODE_ECB'                             )"!][!//
        [!VAR "vs" = "'ENCRYPT'"!][!//
        [!VAR "vf" = "node:value(node:ref(.)/CryptoPrimitiveAlgorithmFamiliy/eb-list::*[node:pos(.)=0])"!][!//
        [!VAR "vm" = "'CRYPTO_ALGOMODE_ECB'"!][!//
      [!ENDIF!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!/* add BlockCipher ECB mode if a BlockCipher based RANDOM is configured             */!][!//
      [!IF "($ps = 'RANDOMGENERATE'      ) and
            ($pf = 'CRYPTO_ALGOFAM_AES'  ) and
            ($pm != 'CRYPTO_ALGOMODE_ECB')"!][!//
        [!VAR "vs" = "'ENCRYPT'"!][!//
        [!VAR "vf" = "node:value(node:ref(.)/CryptoPrimitiveAlgorithmFamiliy/eb-list::*[node:pos(.)=0])"!][!//
        [!VAR "vm" = "'CRYPTO_ALGOMODE_ECB'"!][!//
      [!ENDIF!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!/* add Hash if a Hash based MAC is configured                                       */!][!//
      [!IF "($ps = 'MAC_GENERATE'                or $ps = 'MAC_VERIFY'                    ) and
            ($pf = 'CRYPTO_ALGOFAM_BLAKE_1_256'  or $pf = 'CRYPTO_ALGOFAM_BLAKE_1_512'  or
             $pf = 'CRYPTO_ALGOFAM_BLAKE_2s_256' or $pf = 'CRYPTO_ALGOFAM_BLAKE_2s_512' or
             $pf = 'CRYPTO_ALGOFAM_RIPEMD160'    or $pf = 'CRYPTO_ALGOFAM_SHA1'         or
             $pf = 'CRYPTO_ALGOFAM_SHA2_224'     or $pf = 'CRYPTO_ALGOFAM_SHA2_256'     or
             $pf = 'CRYPTO_ALGOFAM_SHA2_384'     or $pf = 'CRYPTO_ALGOFAM_SHA2_512'     or
             $pf = 'CRYPTO_ALGOFAM_SHA2_512_224' or $pf = 'CRYPTO_ALGOFAM_SHA2_512_256' or
             $pf = 'CRYPTO_ALGOFAM_SHA3_224'     or $pf = 'CRYPTO_ALGOFAM_SHA3_256'     or
             $pf = 'CRYPTO_ALGOFAM_SHA3_384'     or $pf = 'CRYPTO_ALGOFAM_SHA3_512'     or
             $pf = 'CRYPTO_ALGOFAM_SHAKE128'     or $pf = 'CRYPTO_ALGOFAM_SHAKE256'        ) and
            ($pm = 'CRYPTO_ALGOMODE_HMAC'                                                  )"!][!//
        [!VAR "vs" = "'HASH'"!][!//
        [!VAR "vf" = "$pf"!][!//
        [!VAR "vm" = "'CRYPTO_ALGOMODE_NOT_SET'"!][!//
      [!ENDIF!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!VAR "PrimitivesPoolListLong" = "concat($PrimitivesPoolListLong, ' ', $ps, '|', $pf, '|', $pm)"!][!//
      [!IF "$vs != 'EMPTY' and $vf != 'EMPTY' and $vm != 'EMPTY'"!][!//
        [!VAR "PrimitivesPoolListLong" = "concat($PrimitivesPoolListLong, ' ', $vs, '|', $vf, '|', $vm)"!][!//
      [!ENDIF!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
    [!ENDLOOP!][!//
    [!/*------------------------------------------------------------------------------------*/!][!//
    [!/* get secondary primitives (HASHes only)                                             */!][!//
    [!LOOP "eb-list::*/eb-list::*/CryptoPrimitiveRef/eb-list::*"!][!//
      [!IF "node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]) = 'CRYPTO_ALGOFAM_BLAKE_1_256'  or
            node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]) = 'CRYPTO_ALGOFAM_BLAKE_1_512'  or
            node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]) = 'CRYPTO_ALGOFAM_BLAKE_2s_256' or
            node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]) = 'CRYPTO_ALGOFAM_BLAKE_2s_512' or
            node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]) = 'CRYPTO_ALGOFAM_RIPEMD160'    or
            node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]) = 'CRYPTO_ALGOFAM_SHA1'         or
            node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]) = 'CRYPTO_ALGOFAM_SHA2_224'     or
            node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]) = 'CRYPTO_ALGOFAM_SHA2_256'     or
            node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]) = 'CRYPTO_ALGOFAM_SHA2_384'     or
            node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]) = 'CRYPTO_ALGOFAM_SHA2_512'     or
            node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]) = 'CRYPTO_ALGOFAM_SHA2_512_224' or
            node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]) = 'CRYPTO_ALGOFAM_SHA2_512_256' or
            node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]) = 'CRYPTO_ALGOFAM_SHA3_224'     or
            node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]) = 'CRYPTO_ALGOFAM_SHA3_256'     or
            node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]) = 'CRYPTO_ALGOFAM_SHA3_384'     or
            node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]) = 'CRYPTO_ALGOFAM_SHA3_512'     or
            node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]) = 'CRYPTO_ALGOFAM_SHAKE128'     or
            node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]) = 'CRYPTO_ALGOFAM_SHAKE256'"!][!//
        [!VAR "ps" = "'HASH'"!][!//
        [!VAR "pf" = "node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0])"!][!//
        [!VAR "pm" = "'CRYPTO_ALGOMODE_NOT_SET'"!][!//
        [!VAR "sf" = "'CRYPTO_ALGOFAM_NOT_SET'"!][!//
        [!/*--------------------------------------------------------------------------------*/!][!//
        [!VAR "PrimitivesPoolListLong" = "concat($PrimitivesPoolListLong, ' ', $ps, '|', $pf, '|', $pm)"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!/*------------------------------------------------------------------------------------*/!][!//
    [!LOOP "eb-list::*/eb-list::*"!][!//
      [!IF "node:exists(./CryptoDefaultRandomPrimitiveRef)"!][!//
        [!VAR "ps" = "node:value(node:ref(./CryptoDefaultRandomPrimitiveRef)/CryptoPrimitiveService)"!][!//
        [!VAR "pf" = "node:value(node:ref(./CryptoDefaultRandomPrimitiveRef)/CryptoPrimitiveAlgorithmFamiliy/eb-list::*[node:pos(.)=0])"!][!//
        [!VAR "pm" = "node:value(node:ref(./CryptoDefaultRandomPrimitiveRef)/CryptoPrimitiveAlgorithmMode/eb-list::*[node:pos(.)=0])"!][!//
        [!VAR "sf" = "node:value(node:ref(./CryptoDefaultRandomPrimitiveRef)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0])"!][!//
        [!/*--------------------------------------------------------------------------------*/!][!//
        [!IF "$ps = 'RANDOM'"!][!VAR "ps" = "'RANDOMGENERATE'"!][!ENDIF!][!//
        [!IF "($ps = 'RANDOMGENERATE'      ) and
              ($pf = 'CRYPTO_ALGOFAM_AES'  ) and
              ($pm = 'CRYPTO_ALGOMODE_CTRDRBG')"!][!//
          [!VAR "vs" = "'ENCRYPT'"!][!//
          [!VAR "vf" = "'CRYPTO_ALGOFAM_AES'"!][!//
          [!VAR "vm" = "'CRYPTO_ALGOMODE_ECB'"!][!//
        [!ENDIF!][!//
        [!/*--------------------------------------------------------------------------------*/!][!//
        [!VAR "PrimitivesPoolListLong" = "concat($PrimitivesPoolListLong, ' ', $ps, '|', $pf, '|', $pm)"!][!//
        [!IF "$vs != 'EMPTY' and $vf != 'EMPTY' and $vm != 'EMPTY'"!][!//
          [!VAR "PrimitivesPoolListLong" = "concat($PrimitivesPoolListLong, ' ', $vs, '|', $vf, '|', $vm)"!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!/*------------------------------------------------------------------------------------*/!][!//
    [!VAR "PrimitivesPoolListLong" = "text:order(text:split($PrimitivesPoolListLong), 1)"!][!//
    [!VAR "PrimitivesPoolListLong" = "text:replaceAll($PrimitivesPoolListLong, '\[', '' )"!][!//
    [!VAR "PrimitivesPoolListLong" = "text:replaceAll($PrimitivesPoolListLong, '\]', '' )"!][!//
    [!VAR "PrimitivesPoolListLong" = "text:replaceAll($PrimitivesPoolListLong, ',',  ' ')"!][!//
    [!//
    [!VAR "PrimitivesPoolListShrt" = "$PrimitivesPoolListLong"!][!//
    [!VAR "PrimitivesPoolListShrt" = "text:replaceAll($PrimitivesPoolListShrt, 'CRYPTO_ALGOFAM_',  '' )"!][!//
    [!VAR "PrimitivesPoolListShrt" = "text:replaceAll($PrimitivesPoolListShrt, 'CRYPTO_ALGOMODE_', '' )"!][!//
    [!VAR "PrimitivesPoolListShrt" = "text:replaceAll($PrimitivesPoolListShrt, '_',                '' )"!][!//
    [!VAR "PrimitivesPoolListShrt" = "text:replaceAll($PrimitivesPoolListShrt, '\|',               '_')"!][!//
    [!VAR "PrimitivesPoolListShrt" = "text:toupper($PrimitivesPoolListShrt                            )"!][!//
    [!//
    [!VAR "PrimitivesPoolListSize" = "num:i(count(text:split($PrimitivesPoolListShrt)))"!][!//
  [!ENDSELECT!][!//
[!ENDMACRO!][!//
[!//
[!/* ---------------------------------------------------------------------------------------*/!][!//
[!//
[!/*
****************************************************************************************************
* MACRO to get all discrete primitives and primary-secondary primitives combinations referenced to
* a single Crypto Driver Object as strings.
* Each string contains a space separated list of primitive patterns '<service>_<family>_<mode>'.
* Per string an individual representation of the pattern is used.
*
* String variables / Lists are named as follows:
* => CryptoDriverObjectPrimitivesList{Cnfg,Real}{Full,Trim}{P1,P2,R1,R2}{Long,Shrt}
* {Cnfg,Real}   = describes, whether
*                 - {Cnfg} it's a list of primary-secondary primitives combinations
*                   directly configured by the user or
*                 - {Real} if it's a list of primary-secondary primitives combinations that
*                   contain implicitely added secondary primitives
*                   (e.g. secondary ENCRYPT_AES_ECB for primary ENCRYPT_AES_nonECB or secondary
*                         HASH_SHA2256_NOTSET for primary MACGENERATE_SHA2256_HMAC) or
* {Full,Trim}   = describes whether it's a list containing full primary-secondary primitives
*                 combinations (2x3 elms per entry) or only trimmed discrete primitives (1x3 elms per
*                 entry)
* {P1,P2,R1,R2} = describes whether it's a list of primary, (first) secondary or second secondary (random) primitives
* {Long,Shrt}   = describes whether it's a list of long (full enumeration name as specified by SWS) or
*                 short representation of primitives
*                 All elements in the Long category are named according to their ECUC requirement.
*                 (s:Crypto.Asr.ECUC_Crypto_00034, f:Crypto.Asr.ECUC_Crypto_00035, m:Crypto.Asr.ECUC_Crypto_00036)
*
* Example:
* => Configure by user:
*      CDO0 ... ENCRYPT+AES+CBC, SIGNATUREGENERATE+RSA+RSASSA+SHA2512, HASH+SHA2256+NOTSET
*      CDO1 ... MACGENERATE+SHA2384+HMAC
* => Lists CDO1:
*      CryptoDriverObjectPrimitivesListCnfgFullP1Long = "ENCRYPT|CRYPTO_ALGOFAM_AES|CRYPTO_ALGOMOD_CBC|CRYPTO_NOT_SET|CRYPTO_ALGOFAM_NOT_SET|CRYPTO_ALGOMOD_NOT_SET
*                                                        HASH|CRYPTO_ALGOFAM_SHA2_256|CRYPTO_ALGOMOD_NOT_SET|CRYPTO_NOT_SET|CRYPTO_ALGOFAM_NOT_SET|CRYPTO_ALGOMOD_NOT_SET
*                                                        CRYPTO_SIGNATUREGENERATE|CRYPTO_ALGOFAM_RSA|CRYPTO_ALGOMOD_RSASSA|HASH|CRYPTO_ALGOFAM_SHA2_512|CRYPTO_ALGOMOD_NOT_SET"
*      CryptoDriverObjectPrimitivesListCnfgFullP1Shrt = "ENCRYPT_AES_CBC_NOTSET_NOTSET_NOTSET
*                                                        HASH_SHA2256_NOTSET_NOTSET_NOTSET_NOTSET
*                                                        SIGNATUREGENERATE_RSA_RSASSA_HASH_SHA2512_NOTSET"
*      CryptoDriverObjectPrimitivesListCnfgTrimP1Long = "ENCRYPT|CRYPTO_ALGOFAM_AES|CRYPTO_ALGOMOD_CBC
*                                                        HASH|CRYPTO_ALGOFAM_SHA2_256|CRYPTO_ALGOMOD_NOT_SET
*                                                        CRYPTO_SIGNATUREGENERATE|CRYPTO_ALGOFAM_RSA|CRYPTO_ALGOMOD_RSASSA"
*      CryptoDriverObjectPrimitivesListCnfgTrimP1Shrt = "ENCRYPT_AES_CBC
*                                                        HASH_SHA2256_NOTSET
*                                                        SIGNATUREGENERATE_RSA_RSASSA"
*      CryptoDriverObjectPrimitivesListRealFullP1Long = "ENCRYPT|CRYPTO_ALGOFAM_AES|CRYPTO_ALGOMOD_CBC|ENCRYPT|CRYPTO_ALGOFAM_AES|CRYPTO_ALGOMOD_ECB
*                                                        HASH|CRYPTO_ALGOFAM_SHA2_256|CRYPTO_ALGOMOD_NOT_SET|CRYPTO_NOT_SET|CRYPTO_ALGOFAM_NOT_SET|CRYPTO_ALGOMOD_NOT_SET
*                                                        CRYPTO_SIGNATUREGENERATE|CRYPTO_ALGOFAM_RSA|CRYPTO_ALGOMOD_RSASSA|HASH|CRYPTO_ALGOFAM_SHA2_512|CRYPTO_ALGOMOD_NOT_SET"
*      CryptoDriverObjectPrimitivesListRealFullP1Shrt = "ENCRYPT_AES_CBC_ENCRYPT_AES_ECB
*                                                        HASH_SHA2256_NOTSET_NOTSET_NOTSET_NOTSET
*                                                        SIGNATUREGENERATE_RSA_RSASSA_HASH_SHA2512_NOTSET"
*      CryptoDriverObjectPrimitivesListRealTrimP1Long = "ENCRYPT|CRYPTO_ALGOFAM_AES|CRYPTO_ALGOMOD_CBC
*                                                        HASH|CRYPTO_ALGOFAM_SHA2_256|CRYPTO_ALGOMOD_NOT_SET
*                                                        CRYPTO_SIGNATUREGENERATE|CRYPTO_ALGOFAM_RSA|CRYPTO_ALGOMOD_RSASSA"
*      CryptoDriverObjectPrimitivesListRealTrimP1Shrt = "ENCRYPT_AES_CBC
*                                                        HASH_SHA2256_NOTSET
*                                                        SIGNATUREGENERATE_RSA_RSASSA"
*      CryptoDriverObjectPrimitivesListCnfgFullP2Long = "HASH|CRYPTO_ALGOFAM_SHA2_512|CRYPTO_ALGOMOD_NOT_SET|CRYPTO_NOT_SET|CRYPTO_ALGOFAM_NOT_SET|CRYPTO_ALGOMOD_NOT_SET"
*      CryptoDriverObjectPrimitivesListCnfgFullP2Shrt = "HASH_SHA2512_NOTSET"
*      CryptoDriverObjectPrimitivesListCnfgTrimP2Long = "HASH|CRYPTO_ALGOFAM_SHA2_512|CRYPTO_ALGOMOD_NOT_SET"
*      CryptoDriverObjectPrimitivesListCnfgTrimP2Shrt = "HASH_SHA2512_NOTSET"
*      CryptoDriverObjectPrimitivesListRealFullP2Long = "ENCRYPT|CRYPTO_ALGOFAM_AES|CRYPTO_ALGOMOD_ECB|CRYPTO_NOT_SET|CRYPTO_ALGOFAM_NOT_SET|CRYPTO_ALGOMOD_NOT_SET
*                                                        HASH|CRYPTO_ALGOFAM_SHA2_512|CRYPTO_ALGOMOD_NOT_SET|CRYPTO_NOT_SET|CRYPTO_ALGOFAM_NOT_SET|CRYPTO_ALGOMOD_NOT_SET"
*      CryptoDriverObjectPrimitivesListRealFullP2Shrt = "ENCRYPT_AES_ECB_NOTSET_NOTSET_NOTSET
*                                                        HASH_SHA2512_NOTSET_NOTSET_NOTSET_NOTSET"
*      CryptoDriverObjectPrimitivesListRealTrimP2Long = "ENCRYPT|CRYPTO_ALGOFAM_AES|CRYPTO_ALGOMOD_ECB
*                                                        HASH|CRYPTO_ALGOFAM_SHA2_512|CRYPTO_ALGOMOD_NOT_SET"
*      CryptoDriverObjectPrimitivesListRealTrimP2Shrt = "ENCRYPT_AES_ECB
*                                                        HASH_SHA2512_NOTSET"
****************************************************************************************************
*/!][!//
[!//
[!MACRO "GetCryptoDriverObjectPrimitivesList", "cdo"!][!//
  [!//
  [!/* P1 = Primary primitive */!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealFullP1Long" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealFullP1Shrt" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealFullP1Size" = "num:i(0)"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealTrimP1Long" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealTrimP1Shrt" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealTrimP1Size" = "num:i(0)"!][!//
  [!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP1Long" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP1Shrt" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP1Size" = "num:i(0)"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP1Long" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP1Shrt" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP1Size" = "num:i(0)"!][!//
  [!//
  [!/* P2 = Secondary primitive */!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealFullP2Long" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealFullP2Shrt" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealFullP2Size" = "num:i(0)"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealTrimP2Long" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealTrimP2Shrt" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealTrimP2Size" = "num:i(0)"!][!//
  [!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP2Long" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP2Shrt" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP2Size" = "num:i(0)"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP2Long" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP2Shrt" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP2Size" = "num:i(0)"!][!//
  [!//
  [!/* R1 = Primary part of random primitive (CryptoDefaultRandomPrimitiveRef) */!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealFullR1Long" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealFullR1Shrt" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealFullR1Size" = "num:i(0)"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealTrimR1Long" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealTrimR1Shrt" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealTrimR1Size" = "num:i(0)"!][!//
  [!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR1Long" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR1Shrt" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR1Size" = "num:i(0)"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR1Long" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR1Shrt" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR1Size" = "num:i(0)"!][!//
  [!//
  [!/* R2 = Secondary part of random primitive (CryptoDefaultRandomPrimitiveRef) */!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealFullR2Long" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealFullR2Shrt" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealFullR2Size" = "num:i(0)"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealTrimR2Long" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealTrimR2Shrt" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListRealTrimR2Size" = "num:i(0)"!][!//
  [!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR2Long" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR2Shrt" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR2Size" = "num:i(0)"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR2Long" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR2Shrt" = "''"!][!//
  [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR2Size" = "num:i(0)"!][!//
  [!//
  [!SELECT "node:ref($cdo)"!][!//
    [!VAR "name_cdo" = "node:name(.)"!][!//
    [!/*------------------------------------------------------------------------------------*/!][!//
    [!/* get primitives                                                                     */!][!//
    [!LOOP "./CryptoPrimitiveRef/eb-list::*"!][!//
      [!VAR "name_pri" = "node:name(.)"!][!//
      [!VAR "psl" = "node:value(node:ref(.)/CryptoPrimitiveService)"!][!//
      [!VAR "pfl" = "node:value(node:ref(.)/CryptoPrimitiveAlgorithmFamiliy/eb-list::*[node:pos(.)=0])"!][!//
      [!VAR "pml" = "node:value(node:ref(.)/CryptoPrimitiveAlgorithmMode/eb-list::*[node:pos(.)=0])"!][!//
      [!VAR "ssl" = "'CRYPTO_NOT_SET'"!][!//
      [!VAR "sfl" = "node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0])"!][!//
      [!VAR "sml" = "'CRYPTO_ALGOMODE_NOT_SET'"!][!//
      [!VAR "tsl" = "'CRYPTO_NOT_SET'"!][!//
      [!VAR "tfl" = "'CRYPTO_ALGOFAM_NOT_SET'"!][!//
      [!VAR "tml" = "'CRYPTO_ALGOMODE_NOT_SET'"!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!IF "($psl = 'RANDOM')"!][!VAR "psl" = "'RANDOMGENERATE'"!][!ENDIF!][!//
      [!IF "($sfl = 'RANDOM')"!][!VAR "sfl" = "'RANDOMGENERATE'"!][!ENDIF!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP1Long" = "concat($CryptoDriverObjectPrimitivesListCnfgFullP1Long, ' ', $psl, '|', $pfl, '|', $pml)"!][!//
      [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP1Long" = "concat($CryptoDriverObjectPrimitivesListCnfgFullP1Long, '|', $ssl, '|', $sfl, '|', $sml)"!][!//
      [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP1Long" = "concat($CryptoDriverObjectPrimitivesListCnfgTrimP1Long, ' ', $psl, '|', $pfl, '|', $pml)"!][!//
      [!//
      [!IF "$sfl != 'CRYPTO_ALGOFAM_NOT_SET'"!][!//
        [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP2Long" = "concat($CryptoDriverObjectPrimitivesListCnfgFullP2Long, ' ', $ssl, '|', $sfl, '|', $sml)"!][!//
        [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP2Long" = "concat($CryptoDriverObjectPrimitivesListCnfgFullP2Long, '|', $tsl, '|', $tfl, '|', $tml)"!][!//
        [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP2Long" = "concat($CryptoDriverObjectPrimitivesListCnfgTrimP2Long, ' ', $ssl, '|', $sfl, '|', $sml)"!][!//
      [!ENDIF!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!/* add secondary primitive BlockCipher ECB mode if a AEAD with BlockCipher ECB is configured */!][!//
      [!IF "($psl = 'AEAD_ENCRYPT'        or       $psl = 'AEAD_DECRYPT') and
            ($pfl = 'CRYPTO_ALGOFAM_3DES' or $pfl = 'CRYPTO_ALGOFAM_AES') and
            ($pml != 'CRYPTO_ALGOMODE_ECB'                             )"!][!//
        [!VAR "ssl" = "'ENCRYPT'"!][!//
        [!VAR "sfl" = "$pfl"!][!//
        [!VAR "sml" = "'CRYPTO_ALGOMODE_ECB'"!][!//
        [!VAR "tsl" = "'CRYPTO_NOT_SET'"!][!//
        [!VAR "tfl" = "'CRYPTO_ALGOFAM_NOT_SET'"!][!//
        [!VAR "tml" = "'CRYPTO_ALGOMODE_NOT_SET'"!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!/* add secondary primitive BlockCipher ECB mode if a BlockCipher without ECB is configured */!][!//
      [!ELSEIF "($psl = 'ENCRYPT'                                           ) and
                ($pfl = 'CRYPTO_ALGOFAM_3DES' or $pfl = 'CRYPTO_ALGOFAM_AES') and
                ($pml != 'CRYPTO_ALGOMODE_ECB'                              )"!][!//
        [!VAR "ssl" = "'ENCRYPT'"!][!//
        [!VAR "sfl" = "node:value(node:ref(.)/CryptoPrimitiveAlgorithmFamiliy/eb-list::*[node:pos(.)=0])"!][!//
        [!VAR "sml" = "'CRYPTO_ALGOMODE_ECB'"!][!//
        [!VAR "tsl" = "'CRYPTO_NOT_SET'"!][!//
        [!VAR "tfl" = "'CRYPTO_ALGOFAM_NOT_SET'"!][!//
        [!VAR "tml" = "'CRYPTO_ALGOMODE_NOT_SET'"!][!//
      [!ELSEIF "($psl = 'DECRYPT'                                               ) and
                ($pfl = 'CRYPTO_ALGOFAM_3DES'  or  $pfl = 'CRYPTO_ALGOFAM_AES'  ) and
                ($pml != 'CRYPTO_ALGOMODE_ECB' and $pml != 'CRYPTO_ALGOMODE_CBC')"!][!//
        [!VAR "ssl" = "'ENCRYPT'"!][!//
        [!VAR "sfl" = "node:value(node:ref(.)/CryptoPrimitiveAlgorithmFamiliy/eb-list::*[node:pos(.)=0])"!][!//
        [!VAR "sml" = "'CRYPTO_ALGOMODE_ECB'"!][!//
        [!VAR "tsl" = "'CRYPTO_NOT_SET'"!][!//
        [!VAR "tfl" = "'CRYPTO_ALGOFAM_NOT_SET'"!][!//
        [!VAR "tml" = "'CRYPTO_ALGOMODE_NOT_SET'"!][!//
      [!ELSEIF "($psl = 'DECRYPT'                                           ) and
                ($pfl = 'CRYPTO_ALGOFAM_3DES' or $pfl = 'CRYPTO_ALGOFAM_AES') and
                ($pml = 'CRYPTO_ALGOMODE_CBC'                               )"!][!//
        [!VAR "ssl" = "'DECRYPT'"!][!//
        [!VAR "sfl" = "node:value(node:ref(.)/CryptoPrimitiveAlgorithmFamiliy/eb-list::*[node:pos(.)=0])"!][!//
        [!VAR "sml" = "'CRYPTO_ALGOMODE_ECB'"!][!//
        [!VAR "tsl" = "'CRYPTO_NOT_SET'"!][!//
        [!VAR "tfl" = "'CRYPTO_ALGOFAM_NOT_SET'"!][!//
        [!VAR "tml" = "'CRYPTO_ALGOMODE_NOT_SET'"!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!/* add secondary primitive BlockCipher ECB mode if a BlockCipher based MAC is configured */!][!//
      [!ELSEIF "($psl = 'MAC_GENERATE'        or $psl = 'MAC_VERIFY'        ) and
                ($pfl = 'CRYPTO_ALGOFAM_3DES' or $pfl = 'CRYPTO_ALGOFAM_AES') and
                ($pml = 'CRYPTO_ALGOMODE_CMAC'                             )"!][!//
        [!VAR "ssl" = "'ENCRYPT'"!][!//
        [!VAR "sfl" = "$pfl"!][!//
        [!VAR "sml" = "'CRYPTO_ALGOMODE_ECB'"!][!//
        [!VAR "tsl" = "'CRYPTO_NOT_SET'"!][!//
        [!VAR "tfl" = "'CRYPTO_ALGOFAM_NOT_SET'"!][!//
        [!VAR "tml" = "'CRYPTO_ALGOMODE_NOT_SET'"!][!//
      [!/* add secondary primitive BlockCipher ECB mode if a BlockCipher based RANDOMGENERATE is configured */!][!//
      [!ELSEIF "($psl = 'RANDOMGENERATE'         ) and
                ($pfl = 'CRYPTO_ALGOFAM_AES'     ) and
                ($pml = 'CRYPTO_ALGOMODE_CTRDRBG')"!][!//
        [!VAR "ssl" = "'ENCRYPT'"!][!//
        [!VAR "sfl" = "$pfl"!][!//
        [!VAR "sml" = "'CRYPTO_ALGOMODE_ECB'"!][!//
        [!VAR "tsl" = "'CRYPTO_NOT_SET'"!][!//
        [!VAR "tfl" = "'CRYPTO_ALGOFAM_NOT_SET'"!][!//
        [!VAR "tml" = "'CRYPTO_ALGOMODE_NOT_SET'"!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!/* add secondary primitive Hash if a Hash based MAC is configured                   */!][!//
      [!ELSEIF "($psl = 'MAC_GENERATE'                or $psl = 'MAC_VERIFY'                    ) and
                ($pfl = 'CRYPTO_ALGOFAM_BLAKE_1_256'  or $pfl = 'CRYPTO_ALGOFAM_BLAKE_1_512'  or
                 $pfl = 'CRYPTO_ALGOFAM_BLAKE_2s_256' or $pfl = 'CRYPTO_ALGOFAM_BLAKE_2s_512' or
                 $pfl = 'CRYPTO_ALGOFAM_RIPEMD160'    or $pfl = 'CRYPTO_ALGOFAM_SHA1'         or
                 $pfl = 'CRYPTO_ALGOFAM_SHA2_224'     or $pfl = 'CRYPTO_ALGOFAM_SHA2_256'     or
                 $pfl = 'CRYPTO_ALGOFAM_SHA2_384'     or $pfl = 'CRYPTO_ALGOFAM_SHA2_512'     or
                 $pfl = 'CRYPTO_ALGOFAM_SHA2_512_224' or $pfl = 'CRYPTO_ALGOFAM_SHA2_512_256' or
                 $pfl = 'CRYPTO_ALGOFAM_SHA3_224'     or $pfl = 'CRYPTO_ALGOFAM_SHA3_256'     or
                 $pfl = 'CRYPTO_ALGOFAM_SHA3_384'     or $pfl = 'CRYPTO_ALGOFAM_SHA3_512'     or
                 $pfl = 'CRYPTO_ALGOFAM_SHAKE128'     or $pfl = 'CRYPTO_ALGOFAM_SHAKE256'        ) and
                ($pml = 'CRYPTO_ALGOMODE_HMAC'                                                   )"!][!//
        [!VAR "ssl" = "'HASH'"!][!//
        [!VAR "sfl" = "$pfl"!][!//
        [!VAR "sml" = "'CRYPTO_ALGOMODE_NOT_SET'"!][!//
        [!VAR "tsl" = "'CRYPTO_NOT_SET'"!][!//
        [!VAR "tfl" = "'CRYPTO_ALGOFAM_NOT_SET'"!][!//
        [!VAR "tml" = "'CRYPTO_ALGOMODE_NOT_SET'"!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!/* add secondary primitive service if a Hash based secondary primitive is configured*/!][!//
      [!ELSEIF "$sfl = 'CRYPTO_ALGOFAM_BLAKE_1_512'  or
                $sfl = 'CRYPTO_ALGOFAM_BLAKE_2s_256' or
                $sfl = 'CRYPTO_ALGOFAM_BLAKE_2s_512' or
                $sfl = 'CRYPTO_ALGOFAM_RIPEMD160'    or
                $sfl = 'CRYPTO_ALGOFAM_SHA1'         or
                $sfl = 'CRYPTO_ALGOFAM_SHA2_224'     or
                $sfl = 'CRYPTO_ALGOFAM_SHA2_256'     or
                $sfl = 'CRYPTO_ALGOFAM_SHA2_384'     or
                $sfl = 'CRYPTO_ALGOFAM_SHA2_512'     or
                $sfl = 'CRYPTO_ALGOFAM_SHA2_512_224' or
                $sfl = 'CRYPTO_ALGOFAM_SHA2_512_256' or
                $sfl = 'CRYPTO_ALGOFAM_SHA3_224'     or
                $sfl = 'CRYPTO_ALGOFAM_SHA3_256'     or
                $sfl = 'CRYPTO_ALGOFAM_SHA3_384'     or
                $sfl = 'CRYPTO_ALGOFAM_SHA3_512'     or
                $sfl = 'CRYPTO_ALGOFAM_SHAKE128'     or
                $sfl = 'CRYPTO_ALGOFAM_SHAKE256'"!][!//
        [!VAR "ssl" = "'HASH'"!][!//
        [!VAR "sfl" = "$sfl"!][!//
        [!VAR "sml" = "'CRYPTO_ALGOMODE_NOT_SET'"!][!//
        [!VAR "tsl" = "'CRYPTO_NOT_SET'"!][!//
        [!VAR "tfl" = "'CRYPTO_ALGOFAM_NOT_SET'"!][!//
        [!VAR "tml" = "'CRYPTO_ALGOMODE_NOT_SET'"!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!/* !!! NOTE: This check is performed for robustness only.
           !!!       It shall be ensured via the module pre-configuration that only HASHes are
           !!!       used as secondary family.
           !!!       In the SCov this path should always be uncovered.
      */!][!//
      [!ELSEIF "$sfl != 'CRYPTO_ALGOFAM_NOT_SET'       and
                $sfl != 'CRYPTO_ALGOFAM_BLAKE_1_512'   and
                $sfl != 'CRYPTO_ALGOFAM_BLAKE_2s_256'  and
                $sfl != 'CRYPTO_ALGOFAM_BLAKE_2s_512'  and
                $sfl != 'CRYPTO_ALGOFAM_RIPEMD160'     and
                $sfl != 'CRYPTO_ALGOFAM_SHA1'          and
                $sfl != 'CRYPTO_ALGOFAM_SHA2_224'      and
                $sfl != 'CRYPTO_ALGOFAM_SHA2_256'      and
                $sfl != 'CRYPTO_ALGOFAM_SHA2_384'      and
                $sfl != 'CRYPTO_ALGOFAM_SHA2_512'      and
                $sfl != 'CRYPTO_ALGOFAM_SHA2_512_224'  and
                $sfl != 'CRYPTO_ALGOFAM_SHA2_512_256'  and
                $sfl != 'CRYPTO_ALGOFAM_SHA3_224'      and
                $sfl != 'CRYPTO_ALGOFAM_SHA3_256'      and
                $sfl != 'CRYPTO_ALGOFAM_SHA3_384'      and
                $sfl != 'CRYPTO_ALGOFAM_SHA3_512'      and
                $sfl != 'CRYPTO_ALGOFAM_SHAKE128'      and
                $sfl != 'CRYPTO_ALGOFAM_SHAKE256'      and
                $sfl != 'CRYPTO_ALGOFAM_PADDING_PKCS7' and
                $sfl != 'CRYPTO_ALGOFAM_PADDING_TLS12'"!][!//
        [!ERROR!][!//
          Primitive '[!"$name_pri"!]', assigned to Crypto Driver Objects '[!"$name_cdo"!]' contains an not allowed
          secondary primitive family. Allowed are NOTSET, HASHes and PADDINGs.
        [!ENDERROR!][!//
      [!ENDIF!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!VAR "CryptoDriverObjectPrimitivesListRealFullP1Long" = "concat($CryptoDriverObjectPrimitivesListRealFullP1Long, ' ', $psl, '|', $pfl, '|', $pml)"!][!//
      [!VAR "CryptoDriverObjectPrimitivesListRealFullP1Long" = "concat($CryptoDriverObjectPrimitivesListRealFullP1Long, '|', $ssl, '|', $sfl, '|', $sml)"!][!//
      [!VAR "CryptoDriverObjectPrimitivesListRealTrimP1Long" = "concat($CryptoDriverObjectPrimitivesListRealTrimP1Long, ' ', $psl, '|', $pfl, '|', $pml)"!][!//
      [!//
      [!IF "$sfl != 'CRYPTO_ALGOFAM_NOT_SET'"!][!//
        [!VAR "CryptoDriverObjectPrimitivesListRealFullP2Long" = "concat($CryptoDriverObjectPrimitivesListRealFullP2Long, ' ', $ssl, '|', $sfl, '|', $sml)"!][!//
        [!VAR "CryptoDriverObjectPrimitivesListRealFullP2Long" = "concat($CryptoDriverObjectPrimitivesListRealFullP2Long, '|', $tsl, '|', $tfl, '|', $tml)"!][!//
        [!VAR "CryptoDriverObjectPrimitivesListRealTrimP2Long" = "concat($CryptoDriverObjectPrimitivesListRealTrimP2Long, ' ', $ssl, '|', $sfl, '|', $sml)"!][!//
      [!ENDIF!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
    [!ENDLOOP!][!//
    [!/*------------------------------------------------------------------------------------*/!][!//
    [!/* get optional Random primary primitive (R1)                                       */!][!//
    [!IF "node:exists(./CryptoDefaultRandomPrimitiveRef)"!][!//
      [!VAR "psl" = "node:value(node:ref(./CryptoDefaultRandomPrimitiveRef)/CryptoPrimitiveService)"!][!//
      [!VAR "pfl" = "node:value(node:ref(./CryptoDefaultRandomPrimitiveRef)/CryptoPrimitiveAlgorithmFamiliy/eb-list::*[node:pos(.)=0])"!][!//
      [!VAR "pml" = "node:value(node:ref(./CryptoDefaultRandomPrimitiveRef)/CryptoPrimitiveAlgorithmMode/eb-list::*[node:pos(.)=0])"!][!//
      [!VAR "ssl" = "'CRYPTO_NOT_SET'"!][!//
      [!VAR "sfl" = "node:value(node:ref(./CryptoDefaultRandomPrimitiveRef)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0])"!][!//
      [!VAR "sml" = "'CRYPTO_ALGOMODE_NOT_SET'"!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!IF "($psl = 'RANDOM')"!][!VAR "psl" = "'RANDOMGENERATE'"!][!ENDIF!][!//
      [!IF "($sfl = 'RANDOM')"!][!VAR "sfl" = "'RANDOMGENERATE'"!][!ENDIF!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!/* get optional Random secondary primitive (R2)                                       */!][!//
      [!IF "($psl = 'RANDOMGENERATE'         ) and
            ($pfl = 'CRYPTO_ALGOFAM_AES'     ) and
            ($pml = 'CRYPTO_ALGOMODE_CTRDRBG')"!][!//
        [!VAR "ssl" = "'ENCRYPT'"!][!//
        [!VAR "sfl" = "$pfl"!][!//
        [!VAR "sml" = "'CRYPTO_ALGOMODE_ECB'"!][!//
      [!ENDIF!][!//
      [!/*----------------------------------------------------------------------------------*/!][!//
      [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR1Long" = "concat($CryptoDriverObjectPrimitivesListCnfgFullR1Long, ' ', $psl, '|', $pfl, '|', $pml)"!][!//
      [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR1Long" = "concat($CryptoDriverObjectPrimitivesListCnfgFullR1Long, '|', $ssl, '|', $sfl, '|', $sml)"!][!//
      [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR1Long" = "concat($CryptoDriverObjectPrimitivesListCnfgTrimR1Long, ' ', $psl, '|', $pfl, '|', $pml)"!][!//
      [!//
      [!IF "$sfl != 'CRYPTO_ALGOFAM_NOT_SET'"!][!//
        [!VAR "CryptoDriverObjectPrimitivesListRealFullR2Long" = "concat($CryptoDriverObjectPrimitivesListRealFullR2Long, ' ', $ssl, '|', $sfl, '|', $sml)"!][!//
        [!VAR "CryptoDriverObjectPrimitivesListRealFullR2Long" = "concat($CryptoDriverObjectPrimitivesListRealFullR2Long, '|', $tsl, '|', $tfl, '|', $tml)"!][!//
        [!VAR "CryptoDriverObjectPrimitivesListRealTrimR2Long" = "concat($CryptoDriverObjectPrimitivesListRealTrimR2Long, ' ', $ssl, '|', $sfl, '|', $sml)"!][!//
      [!ENDIF!][!//
      [!VAR "CryptoDriverObjectPrimitivesListRealFullR1Long" = "$CryptoDriverObjectPrimitivesListCnfgFullR1Long"!][!//
      [!VAR "CryptoDriverObjectPrimitivesListRealTrimR1Long" = "$CryptoDriverObjectPrimitivesListCnfgTrimR1Long"!][!//
    [!ENDIF!][!//
    [!/*------------------------------------------------------------------------------------*/!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP1Long" = "text:order(text:split($CryptoDriverObjectPrimitivesListRealFullP1Long), 1 )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullP1Long, '\[', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullP1Long, '\]', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullP1Long, ',',  ' ')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP1Shrt" = "$CryptoDriverObjectPrimitivesListRealFullP1Long"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullP1Shrt, 'CRYPTO_ALGOFAM_',  '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullP1Shrt, 'CRYPTO_ALGOMODE_', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullP1Shrt, '_',                '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullP1Shrt, '\|',               '_')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP1Shrt" = "text:toupper($CryptoDriverObjectPrimitivesListRealFullP1Shrt                            )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP1Size" = "num:i(count(text:split($CryptoDriverObjectPrimitivesListRealFullP1Shrt)))"!][!//
    [!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP1Long" = "text:order(text:split($CryptoDriverObjectPrimitivesListRealTrimP1Long), 1 )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimP1Long, '\[', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimP1Long, '\]', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimP1Long, ',',  ' ')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP1Shrt" = "$CryptoDriverObjectPrimitivesListRealTrimP1Long"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimP1Shrt, 'CRYPTO_ALGOFAM_',  '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimP1Shrt, 'CRYPTO_ALGOMODE_', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimP1Shrt, '_',                '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimP1Shrt, '\|',               '_')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP1Shrt" = "text:toupper($CryptoDriverObjectPrimitivesListRealTrimP1Shrt                            )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP1Size" = "num:i(count(text:split($CryptoDriverObjectPrimitivesListRealTrimP1Shrt)))"!][!//
    [!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP1Long" = "text:order(text:split($CryptoDriverObjectPrimitivesListCnfgFullP1Long), 1 )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullP1Long, '\[', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullP1Long, '\]', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullP1Long, ',',  ' ')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP1Shrt" = "$CryptoDriverObjectPrimitivesListCnfgFullP1Long"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullP1Shrt, 'CRYPTO_ALGOFAM_',  '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullP1Shrt, 'CRYPTO_ALGOMODE_', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullP1Shrt, '_',                '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullP1Shrt, '\|',               '_')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP1Shrt" = "text:toupper($CryptoDriverObjectPrimitivesListCnfgFullP1Shrt                            )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP1Size" = "num:i(count(text:split($CryptoDriverObjectPrimitivesListCnfgFullP1Shrt)))"!][!//
    [!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP1Long" = "text:order(text:split($CryptoDriverObjectPrimitivesListCnfgTrimP1Long), 1 )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimP1Long, '\[', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimP1Long, '\]', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimP1Long, ',',  ' ')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP1Shrt" = "$CryptoDriverObjectPrimitivesListCnfgTrimP1Long"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimP1Shrt, 'CRYPTO_ALGOFAM_',  '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimP1Shrt, 'CRYPTO_ALGOMODE_', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimP1Shrt, '_',                '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimP1Shrt, '\|',               '_')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP1Shrt" = "text:toupper($CryptoDriverObjectPrimitivesListCnfgTrimP1Shrt                            )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP1Size" = "num:i(count(text:split($CryptoDriverObjectPrimitivesListCnfgTrimP1Shrt)))"!][!//
    [!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP2Long" = "text:order(text:split($CryptoDriverObjectPrimitivesListRealFullP2Long), 1 )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullP2Long, '\[', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullP2Long, '\]', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullP2Long, ',',  ' ')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP2Shrt" = "$CryptoDriverObjectPrimitivesListRealFullP2Long"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullP2Shrt, 'CRYPTO_ALGOFAM_',  '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullP2Shrt, 'CRYPTO_ALGOMODE_', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullP2Shrt, '_',                '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullP2Shrt, '\|',               '_')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP2Shrt" = "text:toupper($CryptoDriverObjectPrimitivesListRealFullP2Shrt                            )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullP2Size" = "num:i(count(text:split($CryptoDriverObjectPrimitivesListRealFullP2Shrt)))"!][!//
    [!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP2Long" = "text:order(text:split($CryptoDriverObjectPrimitivesListRealTrimP2Long), 1 )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimP2Long, '\[', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimP2Long, '\]', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimP2Long, ',',  ' ')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP2Shrt" = "$CryptoDriverObjectPrimitivesListRealTrimP2Long"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimP2Shrt, 'CRYPTO_ALGOFAM_',  '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimP2Shrt, 'CRYPTO_ALGOMODE_', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimP2Shrt, '_',                '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimP2Shrt, '\|',               '_')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP2Shrt" = "text:toupper($CryptoDriverObjectPrimitivesListRealTrimP2Shrt                            )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimP2Size" = "num:i(count(text:split($CryptoDriverObjectPrimitivesListRealTrimP2Shrt)))"!][!//
    [!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP2Long" = "text:order(text:split($CryptoDriverObjectPrimitivesListCnfgFullP2Long), 1 )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullP2Long, '\[', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullP2Long, '\]', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullP2Long, ',',  ' ')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP2Shrt" = "$CryptoDriverObjectPrimitivesListCnfgFullP2Long"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullP2Shrt, 'CRYPTO_ALGOFAM_',  '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullP2Shrt, 'CRYPTO_ALGOMODE_', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullP2Shrt, '_',                '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullP2Shrt, '\|',               '_')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP2Shrt" = "text:toupper($CryptoDriverObjectPrimitivesListCnfgFullP2Shrt                            )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullP2Size" = "num:i(count(text:split($CryptoDriverObjectPrimitivesListCnfgFullP2Shrt)))"!][!//
    [!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP2Long" = "text:order(text:split($CryptoDriverObjectPrimitivesListCnfgTrimP2Long), 1 )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimP2Long, '\[', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimP2Long, '\]', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimP2Long, ',',  ' ')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP2Shrt" = "$CryptoDriverObjectPrimitivesListCnfgTrimP2Long"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimP2Shrt, 'CRYPTO_ALGOFAM_',  '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimP2Shrt, 'CRYPTO_ALGOMODE_', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimP2Shrt, '_',                '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimP2Shrt, '\|',               '_')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP2Shrt" = "text:toupper($CryptoDriverObjectPrimitivesListCnfgTrimP2Shrt                            )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimP2Size" = "num:i(count(text:split($CryptoDriverObjectPrimitivesListCnfgTrimP2Shrt)))"!][!//
    [!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR1Long" = "text:order(text:split($CryptoDriverObjectPrimitivesListRealFullR1Long), 1 )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullR1Long, '\[', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullR1Long, '\]', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullR1Long, ',',  ' ')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR1Shrt" = "$CryptoDriverObjectPrimitivesListRealFullR1Long"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullR1Shrt, 'CRYPTO_ALGOFAM_',  '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullR1Shrt, 'CRYPTO_ALGOMODE_', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullR1Shrt, '_',                '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullR1Shrt, '\|',               '_')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR1Shrt" = "text:toupper($CryptoDriverObjectPrimitivesListRealFullR1Shrt                            )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR1Size" = "num:i(count(text:split($CryptoDriverObjectPrimitivesListRealFullR1Shrt)))"!][!//
    [!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR1Long" = "text:order(text:split($CryptoDriverObjectPrimitivesListRealTrimR1Long), 1 )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimR1Long, '\[', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimR1Long, '\]', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimR1Long, ',',  ' ')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR1Shrt" = "$CryptoDriverObjectPrimitivesListRealTrimR1Long"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, 'CRYPTO_ALGOFAM_',  '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, 'CRYPTO_ALGOMODE_', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, '_',                '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, '\|',               '_')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR1Shrt" = "text:toupper($CryptoDriverObjectPrimitivesListRealTrimR1Shrt                            )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR1Size" = "num:i(count(text:split($CryptoDriverObjectPrimitivesListRealTrimR1Shrt)))"!][!//
    [!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR1Long" = "text:order(text:split($CryptoDriverObjectPrimitivesListCnfgFullR1Long), 1 )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullR1Long, '\[', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullR1Long, '\]', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullR1Long, ',',  ' ')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR1Shrt" = "$CryptoDriverObjectPrimitivesListCnfgFullR1Long"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullR1Shrt, 'CRYPTO_ALGOFAM_',  '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullR1Shrt, 'CRYPTO_ALGOMODE_', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullR1Shrt, '_',                '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullR1Shrt, '\|',               '_')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR1Shrt" = "text:toupper($CryptoDriverObjectPrimitivesListCnfgFullR1Shrt                            )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR1Size" = "num:i(count(text:split($CryptoDriverObjectPrimitivesListCnfgFullR1Shrt)))"!][!//
    [!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR1Long" = "text:order(text:split($CryptoDriverObjectPrimitivesListCnfgTrimR1Long), 1 )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimR1Long, '\[', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimR1Long, '\]', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR1Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimR1Long, ',',  ' ')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR1Shrt" = "$CryptoDriverObjectPrimitivesListCnfgTrimR1Long"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimR1Shrt, 'CRYPTO_ALGOFAM_',  '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimR1Shrt, 'CRYPTO_ALGOMODE_', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimR1Shrt, '_',                '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR1Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimR1Shrt, '\|',               '_')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR1Shrt" = "text:toupper($CryptoDriverObjectPrimitivesListCnfgTrimR1Shrt                            )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR1Size" = "num:i(count(text:split($CryptoDriverObjectPrimitivesListCnfgTrimR1Shrt)))"!][!//
    [!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR2Long" = "text:order(text:split($CryptoDriverObjectPrimitivesListRealFullR2Long), 1 )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullR2Long, '\[', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullR2Long, '\]', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullR2Long, ',',  ' ')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR2Shrt" = "$CryptoDriverObjectPrimitivesListRealFullR2Long"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullR2Shrt, 'CRYPTO_ALGOFAM_',  '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullR2Shrt, 'CRYPTO_ALGOMODE_', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullR2Shrt, '_',                '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealFullR2Shrt, '\|',               '_')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR2Shrt" = "text:toupper($CryptoDriverObjectPrimitivesListRealFullR2Shrt                            )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealFullR2Size" = "num:i(count(text:split($CryptoDriverObjectPrimitivesListRealFullR2Shrt)))"!][!//
    [!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR2Long" = "text:order(text:split($CryptoDriverObjectPrimitivesListRealTrimR2Long), 1 )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimR2Long, '\[', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimR2Long, '\]', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimR2Long, ',',  ' ')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR2Shrt" = "$CryptoDriverObjectPrimitivesListRealTrimR2Long"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, 'CRYPTO_ALGOFAM_',  '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, 'CRYPTO_ALGOMODE_', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, '_',                '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, '\|',               '_')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR2Shrt" = "text:toupper($CryptoDriverObjectPrimitivesListRealTrimR2Shrt                            )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListRealTrimR2Size" = "num:i(count(text:split($CryptoDriverObjectPrimitivesListRealTrimR2Shrt)))"!][!//
    [!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR2Long" = "text:order(text:split($CryptoDriverObjectPrimitivesListCnfgFullR2Long), 1 )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullR2Long, '\[', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullR2Long, '\]', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullR2Long, ',',  ' ')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR2Shrt" = "$CryptoDriverObjectPrimitivesListCnfgFullR2Long"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullR2Shrt, 'CRYPTO_ALGOFAM_',  '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullR2Shrt, 'CRYPTO_ALGOMODE_', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullR2Shrt, '_',                '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgFullR2Shrt, '\|',               '_')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR2Shrt" = "text:toupper($CryptoDriverObjectPrimitivesListCnfgFullR2Shrt                            )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgFullR2Size" = "num:i(count(text:split($CryptoDriverObjectPrimitivesListCnfgFullR2Shrt)))"!][!//
    [!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR2Long" = "text:order(text:split($CryptoDriverObjectPrimitivesListCnfgTrimR2Long), 1 )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimR2Long, '\[', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimR2Long, '\]', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR2Long" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimR2Long, ',',  ' ')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR2Shrt" = "$CryptoDriverObjectPrimitivesListCnfgTrimR2Long"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimR2Shrt, 'CRYPTO_ALGOFAM_',  '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimR2Shrt, 'CRYPTO_ALGOMODE_', '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimR2Shrt, '_',                '' )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR2Shrt" = "text:replaceAll($CryptoDriverObjectPrimitivesListCnfgTrimR2Shrt, '\|',               '_')"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR2Shrt" = "text:toupper($CryptoDriverObjectPrimitivesListCnfgTrimR2Shrt                            )"!][!//
    [!VAR "CryptoDriverObjectPrimitivesListCnfgTrimR2Size" = "num:i(count(text:split($CryptoDriverObjectPrimitivesListCnfgTrimR2Shrt)))"!][!//
  [!ENDSELECT!][!//
[!ENDMACRO!][!//
[!//
[!/* ---------------------------------------------------------------------------------------*/!][!//
[!//
[!/*
****************************************************************************************************
* MACRO to get the token string that determines the size of the primitive workspace type with
* biggest memory consumption to be used in e.g. macro definitions
* The input shall be a list CryptoDriverObjectPrimitivesListRealTrim{Pri,Sec,Rnd}Size as returned
* from macro GetCryptoDriverObjectPrimitivesList
****************************************************************************************************
*/!][!//
[!//
[!MACRO "GetMaxWorkspaceSize", "lst"!][!//
  [!//
  [!VAR "CryptoDriverObjectWorkspaceSize" = "$lst"!][!//
  [!VAR "__GetMaxWorkspaceSizeTemp"       = "''"!][!//
  [!VAR "__GetMaxWorkspaceSizeLimit"      = "num:i(count(text:split($CryptoDriverObjectWorkspaceSize)))"!][!//
  [!VAR "__GetMaxWorkspaceSizeBound"      = "num:i(0)"!][!//
  [!//
  [!FOR "i" = "1" TO "$__GetMaxWorkspaceSizeLimit"!][!//
    [!VAR "__GetMaxWorkspaceSizeTemp" = "concat($__GetMaxWorkspaceSizeTemp, ' sizeof(Crypto_xVIx_xAIx_CPr_', text:split($CryptoDriverObjectWorkspaceSize)[position() = $i], '_WorkspaceType)')"!][!//
  [!ENDFOR!][!//
  [!VAR "CryptoDriverObjectWorkspaceSize" = "normalize-space($__GetMaxWorkspaceSizeTemp)"!][!//
  [!VAR "__GetMaxWorkspaceSizeTemp"       = "''"!][!//
  [!//
  [!IF "$__GetMaxWorkspaceSizeLimit != 1"!][!//
    [!FOR "i" = "1" TO "$__GetMaxWorkspaceSizeLimit"!][!//
      [!VAR "__GetMaxWorkspaceSizeTemp" = "''"!][!//
      [!IF "(count(text:split($CryptoDriverObjectWorkspaceSize)) mod 2) = 0"!][!//
        [!VAR "__GetMaxWorkspaceSizeBound" = "num:i(count(text:split($CryptoDriverObjectWorkspaceSize)))"!][!//
      [!ELSE!][!//
        [!VAR "__GetMaxWorkspaceSizeBound" = "num:i(count(text:split($CryptoDriverObjectWorkspaceSize)) - 1)"!][!//
      [!ENDIF!][!//
      [!FOR "j" = "1" TO "$__GetMaxWorkspaceSizeBound"!][!//
        [!IF "($j mod 2) != 0"!][!//
          [!VAR "__GetMaxWorkspaceSizeTemp" = "concat($__GetMaxWorkspaceSizeTemp, ' CRYPTO_XVIX_XAIX_MAX(', text:split($CryptoDriverObjectWorkspaceSize)[position() = $j], ',')"!][!//
        [!ELSE!][!//
          [!VAR "__GetMaxWorkspaceSizeTemp" = "concat($__GetMaxWorkspaceSizeTemp, text:split($CryptoDriverObjectWorkspaceSize)[position() = $j], ')')"!][!//
        [!ENDIF!][!//
      [!ENDFOR!][!//
      [!IF "$__GetMaxWorkspaceSizeBound < (num:i(count(text:split($CryptoDriverObjectWorkspaceSize))))"!][!//
        [!VAR "__GetMaxWorkspaceSizeTemp" = "concat($__GetMaxWorkspaceSizeTemp, " ", text:split($CryptoDriverObjectWorkspaceSize)[position() = (num:i(count(text:split($CryptoDriverObjectWorkspaceSize))))])"!][!//
      [!ENDIF!][!//
      [!VAR "CryptoDriverObjectWorkspaceSize" = "normalize-space($__GetMaxWorkspaceSizeTemp)"!][!//
      [!IF "num:i(count(text:split($CryptoDriverObjectWorkspaceSize))) = 1"!][!//
        [!BREAK!][!//
      [!ENDIF!][!//
    [!ENDFOR!][!//
  [!ENDIF!][!//
  [!//
[!ENDMACRO!][!//
[!//
[!/* ---------------------------------------------------------------------------------------*/!][!//
[!//
[!/*
****************************************************************************************************
* MACRO to get the alignment for the memory mapping sections for the CDO workspaces
****************************************************************************************************
*/!][!//
[!//
[!MACRO "GetWorkspacesMemMapAlignment"!][!//
  [!//
  [!IF "ecu:get('Cpu.Type') > 32"!]UNSPECIFIED[!ELSE!][!"ecu:get('Cpu.Type')"!][!ENDIF!]
  [!//
[!ENDMACRO!][!//
[!//
[!/* ---------------------------------------------------------------------------------------*/!][!//
[!//
[!/*
****************************************************************************************************
* MACRO to get specific requirement links for Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_SRV_FAM_MOD/0001
****************************************************************************************************
*/!][!//
[!//
[!MACRO "GetReqs_Crypto_xVIx_xAIx_CPr_SRV_FAM_MOD", "pri"!][!//
  [!IF "$pri = 'AEADDECRYPT_AES_CCM'                 "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_AEADDECRYPT_AES_CCM/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'AEADDECRYPT_AES_GCM'                 "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_AEADDECRYPT_AES_GCM/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'AEADENCRYPT_AES_CCM'                 "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'AEADENCRYPT_AES_GCM'                 "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'DECRYPT_AES_CBC'                     "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_DECRYPT_AES_CBC/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'DECRYPT_AES_ECB'                     "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'DECRYPT_LZSS_STREAMBIT'              "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'DECRYPT_LZSS_STREAMBYTE'             "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'DECRYPT_RSA_RSAESOAEP'               "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'ENCRYPT_AES_CBC'                     "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_CBC/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'ENCRYPT_AES_ECB'                     "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'ENCRYPT_RSA_RSAESOAEP'               "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_ENCRYPT_RSA_RSAESOAEP/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'HASH_SHA1_NOTSET'                    "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_HASH_SHA1_NOTSET/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'HASH_SHA2224_NOTSET'                 "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_HASH_SHA2224_NOTSET/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'HASH_SHA2256_NOTSET'                 "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_HASH_SHA2256_NOTSET/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'HASH_SHA2384_NOTSET'                 "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_HASH_SHA2384_NOTSET/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'HASH_SHA2512_NOTSET'                 "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_HASH_SHA2512_NOTSET/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'HASH_SHA3224_NOTSET'                 "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'HASH_SHA3256_NOTSET'                 "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_HASH_SHA3256_NOTSET/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'HASH_SHA3384_NOTSET'                 "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_HASH_SHA3384_NOTSET/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'HASH_SHA3512_NOTSET'                 "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_HASH_SHA3512_NOTSET/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'MACGENERATE_AES_CMAC'                "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_MACGENERATE_AES_CMAC/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'MACGENERATE_SHA1_HMAC'               "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_MACGENERATE_SHA1_HMAC/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'MACGENERATE_SHA2224_HMAC'            "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_MACGENERATE_SHA2224_HMAC/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'MACGENERATE_SHA2256_HMAC'            "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_MACGENERATE_SHA2256_HMAC/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'MACGENERATE_SHA2384_HMAC'            "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_MACGENERATE_SHA2384_HMAC/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'MACGENERATE_SHA2512_HMAC'            "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_MACGENERATE_SHA2512_HMAC/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'MACGENERATE_SIPHASH_SIPHASH24'       "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'MACVERIFY_AES_CMAC'                  "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_MACVERIFY_AES_CMAC/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'MACVERIFY_SHA1_HMAC'                 "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA1_HMAC/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'MACVERIFY_SHA2224_HMAC'              "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2224_HMAC/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'MACVERIFY_SHA2256_HMAC'              "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2256_HMAC/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'MACVERIFY_SHA2384_HMAC'              "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2384_HMAC/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'MACVERIFY_SHA2512_HMAC'              "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'MACVERIFY_SIPHASH_SIPHASH24'         "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_MACVERIFY_SIPHASH_SIPHASH24/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'RANDOMGENERATE_AES_CTRDRBG'          "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'RANDOMGENERATE_NOTSET_NOTSET'        "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_NOTSET_NOTSET/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'SIGNATUREGENERATE_ED25519PH_NOTSET'  "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519PH_NOTSET/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'SIGNATUREGENERATE_ED25519_NOTSET'    "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'SIGNATUREGENERATE_RSA_RSASSAPKCS1V15'"!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'SIGNATUREVERIFY_ECDSA_NOTSET'        "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'SIGNATUREVERIFY_ED25519PH_NOTSET'    "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519PH_NOTSET/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'SIGNATUREVERIFY_ED25519_NOTSET'      "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'SIGNATUREVERIFY_RSA_RSASSAPKCS1V15'  "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_RSA_RSASSAPKCS1V15/0001,1 */[!ENDIF!][!//
  [!IF "$pri = 'SIGNATUREVERIFY_RSA_RSASSAPSS'       "!]/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_RSA_RSASSAPSS/0001,1 */[!ENDIF!][!//
  [!CR!][!//
[!ENDMACRO!][!//
[!//
[!/* ---------------------------------------------------------------------------------------*/!][!//
[!//
[!/*
****************************************************************************************************
* MACRO to get the result length for the used secondary primitive
****************************************************************************************************
*/!][!//
[!//
[!MACRO "GetMaxResultSizeOfSecondary", "ctr", "psrv", "pfam", "pmod"!][!//
  [!//
  [!VAR "HashResultSize" = "num:i(0)"!][!//
  [!SELECT "node:ref($ctr)"!][!//
    [!/*------------------------------------------------------------------------------------*/!][!//
    [!IF "$psrv = 'ENCRYPT' or $psrv = 'DECRYPT' or $psrv = 'SIGNATURE_GENERATE' or $psrv = 'SIGNATURE_VERIFY'"!][!//
      [!IF "$pfam = 'CRYPTO_ALGOFAM_RSA' and ($pmod = 'CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5' or $pmod = 'CRYPTO_ALGOMODE_RSASSA_PSS' or $pmod = 'CRYPTO_ALGOMODE_RSAES_OAEP')"!][!//
        [!LOOP "eb-list::*/eb-list::*/CryptoPrimitiveRef/eb-list::*"!][!//
          [!VAR "sf" = "node:value(node:ref(.)/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0])"!][!//
          [!IF "$sf = 'CRYPTO_ALGOFAM_SHA1'"!][!VAR "HashResultSize"= "'20U'"!][!ENDIF!][!//
          [!IF "$sf = 'CRYPTO_ALGOFAM_SHA2_224' or $sf = 'CRYPTO_ALGOFAM_SHA3_224'"!][!VAR "HashResultSize"= "'28U'"!][!ENDIF!][!//
          [!IF "$sf = 'CRYPTO_ALGOFAM_SHA2_256' or $sf = 'CRYPTO_ALGOFAM_SHA3_256'"!][!VAR "HashResultSize"= "'32U'"!][!ENDIF!][!//
          [!IF "$sf = 'CRYPTO_ALGOFAM_SHA2_384' or $sf = 'CRYPTO_ALGOFAM_SHA3_384'"!][!VAR "HashResultSize"= "'48U'"!][!ENDIF!][!//
          [!IF "$sf = 'CRYPTO_ALGOFAM_SHA2_512' or $sf = 'CRYPTO_ALGOFAM_SHA3_512'"!][!VAR "HashResultSize"= "'64U'"!][!ENDIF!][!//
        [!ENDLOOP!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!//
  [!ENDSELECT!][!//
[!ENDMACRO!][!//
[!/* ---------------------------------------------------------------------------------------*/!][!//
[!//
[!ENDINDENT!][!//
[!ENDIF!][!/* *** multiple inclusion protection *** */!][!//