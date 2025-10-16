/**
 * \file
 *
 * \brief AUTOSAR Cal
 *
 * This file contains the implementation of the AUTOSAR
 * module Cal.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined CAL_TRACE_H)
#define CAL_TRACE_H
/*==================[inclusions]============================================*/

[!IF "node:exists(as:modconf('Dbg'))"!]
#include <Dbg.h>
[!ENDIF!]

/*==================[macros]================================================*/

#ifndef DBG_CAL_GETVERSIONINFO_ENTRY
/** \brief Entry point of function Cal_GetVersionInfo() */
#define DBG_CAL_GETVERSIONINFO_ENTRY(a)
#endif

#ifndef DBG_CAL_GETVERSIONINFO_EXIT
/** \brief Exit point of function Cal_GetVersionInfo() */
#define DBG_CAL_GETVERSIONINFO_EXIT(a)
#endif

#ifndef DBG_CAL_ASYMPUBLICKEYEXTRACTSTART_ENTRY
/** \brief Entry point of function Cal_AsymPublicKeyExtractStart() */
#define DBG_CAL_ASYMPUBLICKEYEXTRACTSTART_ENTRY(a,b)
#endif

#ifndef DBG_CAL_ASYMPUBLICKEYEXTRACTSTART_EXIT
/** \brief Exit point of function Cal_AsymPublicKeyExtractStart() */
#define DBG_CAL_ASYMPUBLICKEYEXTRACTSTART_EXIT(a,b,c)
#endif

#ifndef DBG_CAL_ASYMPUBLICKEYEXTRACTUPDATE_ENTRY
/** \brief Entry point of function Cal_AsymPublicKeyExtractUpdate() */
#define DBG_CAL_ASYMPUBLICKEYEXTRACTUPDATE_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CAL_ASYMPUBLICKEYEXTRACTUPDATE_EXIT
/** \brief Exit point of function Cal_AsymPublicKeyExtractUpdate() */
#define DBG_CAL_ASYMPUBLICKEYEXTRACTUPDATE_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_CAL_ASYMPUBLICKEYEXTRACTFINISH_ENTRY
/** \brief Entry point of function Cal_AsymPublicKeyExtractFinish() */
#define DBG_CAL_ASYMPUBLICKEYEXTRACTFINISH_ENTRY(a,b,c)
#endif

#ifndef DBG_CAL_ASYMPUBLICKEYEXTRACTFINISH_EXIT
/** \brief Exit point of function Cal_AsymPublicKeyExtractFinish() */
#define DBG_CAL_ASYMPUBLICKEYEXTRACTFINISH_EXIT(a,b,c,d)
#endif

#ifndef DBG_CAL_COMPRESSSTART_ENTRY
/** \brief Entry point of function Cal_CompressStart() */
#define DBG_CAL_COMPRESSSTART_ENTRY(a,b)
#endif

#ifndef DBG_CAL_COMPRESSSTART_EXIT
/** \brief Exit point of function Cal_CompressStart() */
#define DBG_CAL_COMPRESSSTART_EXIT(a,b,c)
#endif

#ifndef DBG_CAL_COMPRESSUPDATE_ENTRY
/** \brief Entry point of function Cal_CompressUpdate() */
#define DBG_CAL_COMPRESSUPDATE_ENTRY(a,b,c,d,e,f)
#endif

#ifndef DBG_CAL_COMPRESSUPDATE_EXIT
/** \brief Exit point of function Cal_CompressUpdate() */
#define DBG_CAL_COMPRESSUPDATE_EXIT(a,b,c,d,e,f,g)
#endif

#ifndef DBG_CAL_COMPRESSFINISH_ENTRY
/** \brief Entry point of function Cal_CompressFinish() */
#define DBG_CAL_COMPRESSFINISH_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CAL_COMPRESSFINISH_EXIT
/** \brief Exit point of function Cal_CompressFinish() */
#define DBG_CAL_COMPRESSFINISH_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_CAL_DECOMPRESSSTART_ENTRY
/** \brief Entry point of function Cal_DecompressStart() */
#define DBG_CAL_DECOMPRESSSTART_ENTRY(a,b)
#endif

#ifndef DBG_CAL_DECOMPRESSSTART_EXIT
/** \brief Exit point of function Cal_DecompressStart() */
#define DBG_CAL_DECOMPRESSSTART_EXIT(a,b,c)
#endif

#ifndef DBG_CAL_DECOMPRESSUPDATE_ENTRY
/** \brief Entry point of function Cal_DecompressUpdate() */
#define DBG_CAL_DECOMPRESSUPDATE_ENTRY(a,b,c,d,e,f)
#endif

#ifndef DBG_CAL_DECOMPRESSUPDATE_EXIT
/** \brief Exit point of function Cal_DecompressUpdate() */
#define DBG_CAL_DECOMPRESSUPDATE_EXIT(a,b,c,d,e,f,g)
#endif

#ifndef DBG_CAL_DECOMPRESSFINISH_ENTRY
/** \brief Entry point of function Cal_DecompressFinish() */
#define DBG_CAL_DECOMPRESSFINISH_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CAL_DECOMPRESSFINISH_EXIT
/** \brief Exit point of function Cal_DecompressFinish() */
#define DBG_CAL_DECOMPRESSFINISH_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_CAL_HASHSTART_ENTRY
/** \brief Entry point of function Cal_HashStart() */
#define DBG_CAL_HASHSTART_ENTRY(a,b)
#endif

#ifndef DBG_CAL_HASHSTART_EXIT
/** \brief Exit point of function Cal_HashStart() */
#define DBG_CAL_HASHSTART_EXIT(a,b,c)
#endif

#ifndef DBG_CAL_HASHUPDATE_ENTRY
/** \brief Entry point of function Cal_HashUpdate() */
#define DBG_CAL_HASHUPDATE_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CAL_HASHUPDATE_EXIT
/** \brief Exit point of function Cal_HashUpdate() */
#define DBG_CAL_HASHUPDATE_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_CAL_HASHFINISH_ENTRY
/** \brief Entry point of function Cal_HashFinish() */
#define DBG_CAL_HASHFINISH_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_CAL_HASHFINISH_EXIT
/** \brief Exit point of function Cal_HashFinish() */
#define DBG_CAL_HASHFINISH_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_CAL_KEYDERIVESTART_ENTRY
/** \brief Entry point of function Cal_KeyDeriveStart() */
#define DBG_CAL_KEYDERIVESTART_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CAL_KEYDERIVESTART_EXIT
/** \brief Exit point of function Cal_KeyDeriveStart() */
#define DBG_CAL_KEYDERIVESTART_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_CAL_KEYDERIVEUPDATE_ENTRY
/** \brief Entry point of function Cal_KeyDeriveUpdate() */
#define DBG_CAL_KEYDERIVEUPDATE_ENTRY(a,b,c,d,e,f)
#endif

#ifndef DBG_CAL_KEYDERIVEUPDATE_EXIT
/** \brief Exit point of function Cal_KeyDeriveUpdate() */
#define DBG_CAL_KEYDERIVEUPDATE_EXIT(a,b,c,d,e,f,g)
#endif

#ifndef DBG_CAL_KEYDERIVEFINISH_ENTRY
/** \brief Entry point of function Cal_KeyDeriveFinish() */
#define DBG_CAL_KEYDERIVEFINISH_ENTRY(a,b,c)
#endif

#ifndef DBG_CAL_KEYDERIVEFINISH_EXIT
/** \brief Exit point of function Cal_KeyDeriveFinish() */
#define DBG_CAL_KEYDERIVEFINISH_EXIT(a,b,c,d)
#endif

#ifndef DBG_CAL_KEYEXCHANGECALCPUBVAL_ENTRY
/** \brief Entry point of function Cal_KeyExchangeCalcPubVal() */
#define DBG_CAL_KEYEXCHANGECALCPUBVAL_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_CAL_KEYEXCHANGECALCPUBVAL_EXIT
/** \brief Exit point of function Cal_KeyExchangeCalcPubVal() */
#define DBG_CAL_KEYEXCHANGECALCPUBVAL_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_CAL_KEYEXCHANGECALCSECRETSTART_ENTRY
/** \brief Entry point of function Cal_KeyExchangeCalcSecretStart() */
#define DBG_CAL_KEYEXCHANGECALCSECRETSTART_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CAL_KEYEXCHANGECALCSECRETSTART_EXIT
/** \brief Exit point of function Cal_KeyExchangeCalcSecretStart() */
#define DBG_CAL_KEYEXCHANGECALCSECRETSTART_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_CAL_KEYEXCHANGECALCSECRETUPDATE_ENTRY
/** \brief Entry point of function Cal_KeyExchangeCalcSecretUpdate() */
#define DBG_CAL_KEYEXCHANGECALCSECRETUPDATE_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CAL_KEYEXCHANGECALCSECRETUPDATE_EXIT
/** \brief Exit point of function Cal_KeyExchangeCalcSecretUpdate() */
#define DBG_CAL_KEYEXCHANGECALCSECRETUPDATE_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_CAL_KEYEXCHANGECALCSECRETFINISH_ENTRY
/** \brief Entry point of function Cal_KeyExchangeCalcSecretFinish() */
#define DBG_CAL_KEYEXCHANGECALCSECRETFINISH_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_CAL_KEYEXCHANGECALCSECRETFINISH_EXIT
/** \brief Exit point of function Cal_KeyExchangeCalcSecretFinish() */
#define DBG_CAL_KEYEXCHANGECALCSECRETFINISH_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_CAL_MACGENERATESTART_ENTRY
/** \brief Entry point of function Cal_MacGenerateStart() */
#define DBG_CAL_MACGENERATESTART_ENTRY(a,b,c)
#endif

#ifndef DBG_CAL_MACGENERATESTART_EXIT
/** \brief Exit point of function Cal_MacGenerateStart() */
#define DBG_CAL_MACGENERATESTART_EXIT(a,b,c,d)
#endif

#ifndef DBG_CAL_MACGENERATEUPDATE_ENTRY
/** \brief Entry point of function Cal_MacGenerateUpdate() */
#define DBG_CAL_MACGENERATEUPDATE_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CAL_MACGENERATEUPDATE_EXIT
/** \brief Exit point of function Cal_MacGenerateUpdate() */
#define DBG_CAL_MACGENERATEUPDATE_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_CAL_MACGENERATEFINISH_ENTRY
/** \brief Entry point of function Cal_MacGenerateFinish() */
#define DBG_CAL_MACGENERATEFINISH_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_CAL_MACGENERATEFINISH_EXIT
/** \brief Exit point of function Cal_MacGenerateFinish() */
#define DBG_CAL_MACGENERATEFINISH_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_CAL_MACVERIFYSTART_ENTRY
/** \brief Entry point of function Cal_MacVerifyStart() */
#define DBG_CAL_MACVERIFYSTART_ENTRY(a,b,c)
#endif

#ifndef DBG_CAL_MACVERIFYSTART_EXIT
/** \brief Exit point of function Cal_MacVerifyStart() */
#define DBG_CAL_MACVERIFYSTART_EXIT(a,b,c,d)
#endif

#ifndef DBG_CAL_MACVERIFYUPDATE_ENTRY
/** \brief Entry point of function Cal_MacVerifyUpdate() */
#define DBG_CAL_MACVERIFYUPDATE_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CAL_MACVERIFYUPDATE_EXIT
/** \brief Exit point of function Cal_MacVerifyUpdate() */
#define DBG_CAL_MACVERIFYUPDATE_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_CAL_MACVERIFYFINISH_ENTRY
/** \brief Entry point of function Cal_MacVerifyFinish() */
#define DBG_CAL_MACVERIFYFINISH_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_CAL_MACVERIFYFINISH_EXIT
/** \brief Exit point of function Cal_MacVerifyFinish() */
#define DBG_CAL_MACVERIFYFINISH_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_CAL_RANDOMSEEDSTART_ENTRY
/** \brief Entry point of function Cal_RandomSeedStart() */
#define DBG_CAL_RANDOMSEEDSTART_ENTRY(a,b)
#endif

#ifndef DBG_CAL_RANDOMSEEDSTART_EXIT
/** \brief Exit point of function Cal_RandomSeedStart() */
#define DBG_CAL_RANDOMSEEDSTART_EXIT(a,b,c)
#endif

#ifndef DBG_CAL_RANDOMSEEDUPDATE_ENTRY
/** \brief Entry point of function Cal_RandomSeedUpdate() */
#define DBG_CAL_RANDOMSEEDUPDATE_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CAL_RANDOMSEEDUPDATE_EXIT
/** \brief Exit point of function Cal_RandomSeedUpdate() */
#define DBG_CAL_RANDOMSEEDUPDATE_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_CAL_RANDOMSEEDFINISH_ENTRY
/** \brief Entry point of function Cal_RandomSeedFinish() */
#define DBG_CAL_RANDOMSEEDFINISH_ENTRY(a,b)
#endif

#ifndef DBG_CAL_RANDOMSEEDFINISH_EXIT
/** \brief Exit point of function Cal_RandomSeedFinish() */
#define DBG_CAL_RANDOMSEEDFINISH_EXIT(a,b,c)
#endif

#ifndef DBG_CAL_RANDOMGENERATE_ENTRY
/** \brief Entry point of function Cal_RandomGenerate() */
#define DBG_CAL_RANDOMGENERATE_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CAL_RANDOMGENERATE_EXIT
/** \brief Exit point of function Cal_RandomGenerate() */
#define DBG_CAL_RANDOMGENERATE_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_CAL_SIGNATUREVERIFYSTART_ENTRY
/** \brief Entry point of function Cal_SignatureVerifyStart() */
#define DBG_CAL_SIGNATUREVERIFYSTART_ENTRY(a,b,c)
#endif

#ifndef DBG_CAL_SIGNATUREVERIFYSTART_EXIT
/** \brief Exit point of function Cal_SignatureVerifyStart() */
#define DBG_CAL_SIGNATUREVERIFYSTART_EXIT(a,b,c,d)
#endif

#ifndef DBG_CAL_SIGNATUREVERIFYUPDATE_ENTRY
/** \brief Entry point of function Cal_SignatureVerifyUpdate() */
#define DBG_CAL_SIGNATUREVERIFYUPDATE_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CAL_SIGNATUREVERIFYUPDATE_EXIT
/** \brief Exit point of function Cal_SignatureVerifyUpdate() */
#define DBG_CAL_SIGNATUREVERIFYUPDATE_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_CAL_SIGNATUREVERIFYFINISH_ENTRY
/** \brief Entry point of function Cal_SignatureVerifyFinish() */
#define DBG_CAL_SIGNATUREVERIFYFINISH_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_CAL_SIGNATUREVERIFYFINISH_EXIT
/** \brief Exit point of function Cal_SignatureVerifyFinish() */
#define DBG_CAL_SIGNATUREVERIFYFINISH_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_CAL_SYMBLOCKDECRYPTSTART_ENTRY
/** \brief Entry point of function Cal_SymBlockDecryptStart() */
#define DBG_CAL_SYMBLOCKDECRYPTSTART_ENTRY(a,b,c)
#endif

#ifndef DBG_CAL_SYMBLOCKDECRYPTSTART_EXIT
/** \brief Exit point of function Cal_SymBlockDecryptStart() */
#define DBG_CAL_SYMBLOCKDECRYPTSTART_EXIT(a,b,c,d)
#endif

#ifndef DBG_CAL_SYMBLOCKDECRYPTUPDATE_ENTRY
/** \brief Entry point of function Cal_SymBlockDecryptUpdate() */
#define DBG_CAL_SYMBLOCKDECRYPTUPDATE_ENTRY(a,b,c,d,e,f)
#endif

#ifndef DBG_CAL_SYMBLOCKDECRYPTUPDATE_EXIT
/** \brief Exit point of function Cal_SymBlockDecryptUpdate() */
#define DBG_CAL_SYMBLOCKDECRYPTUPDATE_EXIT(a,b,c,d,e,f,g)
#endif

#ifndef DBG_CAL_SYMBLOCKDECRYPTFINISH_ENTRY
/** \brief Entry point of function Cal_SymBlockDecryptFinish() */
#define DBG_CAL_SYMBLOCKDECRYPTFINISH_ENTRY(a,b)
#endif

#ifndef DBG_CAL_SYMBLOCKDECRYPTFINISH_EXIT
/** \brief Exit point of function Cal_SymBlockDecryptFinish() */
#define DBG_CAL_SYMBLOCKDECRYPTFINISH_EXIT(a,b,c)
#endif

#ifndef DBG_CAL_SYMBLOCKENCRYPTSTART_ENTRY
/** \brief Entry point of function Cal_SymBlockEncryptStart() */
#define DBG_CAL_SYMBLOCKENCRYPTSTART_ENTRY(a,b,c)
#endif

#ifndef DBG_CAL_SYMBLOCKENCRYPTSTART_EXIT
/** \brief Exit point of function Cal_SymBlockEncryptStart() */
#define DBG_CAL_SYMBLOCKENCRYPTSTART_EXIT(a,b,c,d)
#endif

#ifndef DBG_CAL_SYMBLOCKENCRYPTUPDATE_ENTRY
/** \brief Entry point of function Cal_SymBlockEncryptUpdate() */
#define DBG_CAL_SYMBLOCKENCRYPTUPDATE_ENTRY(a,b,c,d,e,f)
#endif

#ifndef DBG_CAL_SYMBLOCKENCRYPTUPDATE_EXIT
/** \brief Exit point of function Cal_SymBlockEncryptUpdate() */
#define DBG_CAL_SYMBLOCKENCRYPTUPDATE_EXIT(a,b,c,d,e,f,g)
#endif

#ifndef DBG_CAL_SYMBLOCKENCRYPTFINISH_ENTRY
/** \brief Entry point of function Cal_SymBlockEncryptFinish() */
#define DBG_CAL_SYMBLOCKENCRYPTFINISH_ENTRY(a,b)
#endif

#ifndef DBG_CAL_SYMBLOCKENCRYPTFINISH_EXIT
/** \brief Exit point of function Cal_SymBlockEncryptFinish() */
#define DBG_CAL_SYMBLOCKENCRYPTFINISH_EXIT(a,b,c)
#endif

#ifndef DBG_CAL_SYMDECRYPTSTART_ENTRY
/** \brief Entry point of function Cal_SymDecryptStart() */
#define DBG_CAL_SYMDECRYPTSTART_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_CAL_SYMDECRYPTSTART_EXIT
/** \brief Exit point of function Cal_SymDecryptStart() */
#define DBG_CAL_SYMDECRYPTSTART_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_CAL_SYMDECRYPTUPDATE_ENTRY
/** \brief Entry point of function Cal_SymDecryptUpdate() */
#define DBG_CAL_SYMDECRYPTUPDATE_ENTRY(a,b,c,d,e,f)
#endif

#ifndef DBG_CAL_SYMDECRYPTUPDATE_EXIT
/** \brief Exit point of function Cal_SymDecryptUpdate() */
#define DBG_CAL_SYMDECRYPTUPDATE_EXIT(a,b,c,d,e,f,g)
#endif

#ifndef DBG_CAL_SYMDECRYPTFINISH_ENTRY
/** \brief Entry point of function Cal_SymDecryptFinish() */
#define DBG_CAL_SYMDECRYPTFINISH_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CAL_SYMDECRYPTFINISH_EXIT
/** \brief Exit point of function Cal_SymDecryptFinish() */
#define DBG_CAL_SYMDECRYPTFINISH_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_CAL_SYMKEYEXTRACTSTART_ENTRY
/** \brief Entry point of function Cal_SymKeyExtractStart() */
#define DBG_CAL_SYMKEYEXTRACTSTART_ENTRY(a,b)
#endif

#ifndef DBG_CAL_SYMKEYEXTRACTSTART_EXIT
/** \brief Exit point of function Cal_SymKeyExtractStart() */
#define DBG_CAL_SYMKEYEXTRACTSTART_EXIT(a,b,c)
#endif

#ifndef DBG_CAL_SYMKEYEXTRACTUPDATE_ENTRY
/** \brief Entry point of function Cal_SymKeyExtractUpdate() */
#define DBG_CAL_SYMKEYEXTRACTUPDATE_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CAL_SYMKEYEXTRACTUPDATE_EXIT
/** \brief Exit point of function Cal_SymKeyExtractUpdate() */
#define DBG_CAL_SYMKEYEXTRACTUPDATE_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_CAL_SYMKEYEXTRACTFINISH_ENTRY
/** \brief Entry point of function Cal_SymKeyExtractFinish() */
#define DBG_CAL_SYMKEYEXTRACTFINISH_ENTRY(a,b,c)
#endif

#ifndef DBG_CAL_SYMKEYEXTRACTFINISH_EXIT
/** \brief Exit point of function Cal_SymKeyExtractFinish() */
#define DBG_CAL_SYMKEYEXTRACTFINISH_EXIT(a,b,c,d)
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

#endif /* (!defined CAL_TRACE_H) */
/*==================[end of file]===========================================*/
