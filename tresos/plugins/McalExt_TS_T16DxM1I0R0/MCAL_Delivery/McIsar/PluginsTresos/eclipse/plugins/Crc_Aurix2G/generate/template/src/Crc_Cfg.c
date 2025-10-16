[!/*****************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2021)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Crc_Cfg.c                                                     **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE      : 2021-03-01                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Crc.bmd                                           **
**                                                                            **
**  VARIANT   : Variant LT                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID=]                                          **
**                                                                            **
**  DESCRIPTION  : Code template source file for Crc Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of CRC Driver, AUTOSAR Release 4.2.2     **
**                   : Specification of Crc Driver, AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!]
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2021)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Crc_Cfg.c                                                     **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]       !!!IGNORE-LINE!!!                  **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]           !!!IGNORE-LINE!!!                **
**                                                                            **
**  BSW MODULE DECRIPTION : Crc.bmd                                           **
**                                                                            **
**  VARIANT   : Variant LT                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Crc configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of CRC Driver, AUTOSAR Release 4.2.2     **
**                   : Specification of Crc Driver, AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
[!//
[!IF "not(node:exists(as:modconf('ResourceM')[1]))"!]
  [!ERROR!][!//
    CRC Code Generator: ResourceM module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!][!//
[!IF "not(node:exists(as:modconf('Mcu')[1]))"!]
  [!ERROR!][!//
    CRC Code Generator: Mcu module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!][!//
[!IF "not(node:exists(as:modconf('McalLib')[1]))"!]
  [!ERROR!][!//
    CRC Code Generator: McalLib module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!][!//
[!/* [cover parentID={B5C3807A-0FF6-4a7e-BE27-D152F682C5B0}] [/cover] */!][!//

[!/* [cover parentID={EBEBC915-C6CE-492d-9C8C-33700DD11FC8}] [/cover] */!][!//
[!SELECT "as:modconf('Crc')[1]"!][!//
  [!//
  [!/* Include Code Generator Macros */!][!//
  [!NOCODE!][!//
    [!INCLUDE "..\Crc.m"!][!//
  [!//
  [!ENDNOCODE!][!//

/*******************************************************************************
**                             Includes                                       **
*******************************************************************************/
/* Include Crc Module File */
#include "Crc.h"
/******************************************************************************/
[!IF "CrcGeneral/Crc32P4Mode/__1 = 'CRC_32P4_TABLE'"!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safegaurd. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
/* [cover parentID={387BA95D-4ABF-40e0-A45C-D6EF94044C1E}]
 * [/cover] */
/* MISRA2012_RULE_8_9_JUSTIFICATION: This data structure is quite
 * big is size, therefore link time relocation of table is
 * provided using Autosar Memmap definition guidelines         */
/* MISRA2012_RULE_8_4_JUSTIFICATION: Crc_Table32P4 is moved to Crc_Cfg.c for
 * conditional generation but prototype is defined in Crc.c to avoid exposure
 * to user. */
const uint32 Crc_Table32P4[256] =
{
  0x00000000U, 0xF4ACFB13U, 0x1DF50D35U, 0xE959F626U,
  0x3BEA1A6AU, 0xCF46E179U, 0x261F175FU, 0xD2B3EC4CU,
  0x77D434D4U, 0x8378CFC7U, 0x6A2139E1U, 0x9E8DC2F2U,
  0x4C3E2EBEU, 0xB892D5ADU, 0x51CB238BU, 0xA567D898U,
  0xEFA869A8U, 0x1B0492BBU, 0xF25D649DU, 0x06F19F8EU,
  0xD44273C2U, 0x20EE88D1U, 0xC9B77EF7U, 0x3D1B85E4U,
  0x987C5D7CU, 0x6CD0A66FU, 0x85895049U, 0x7125AB5AU,
  0xA3964716U, 0x573ABC05U, 0xBE634A23U, 0x4ACFB130U,
  0x2BFC2843U, 0xDF50D350U, 0x36092576U, 0xC2A5DE65U,
  0x10163229U, 0xE4BAC93AU, 0x0DE33F1CU, 0xF94FC40FU,
  0x5C281C97U, 0xA884E784U, 0x41DD11A2U, 0xB571EAB1U,
  0x67C206FDU, 0x936EFDEEU, 0x7A370BC8U, 0x8E9BF0DBU,
  0xC45441EBU, 0x30F8BAF8U, 0xD9A14CDEU, 0x2D0DB7CDU,
  0xFFBE5B81U, 0x0B12A092U, 0xE24B56B4U, 0x16E7ADA7U,
  0xB380753FU, 0x472C8E2CU, 0xAE75780AU, 0x5AD98319U,
  0x886A6F55U, 0x7CC69446U, 0x959F6260U, 0x61339973U,
  0x57F85086U, 0xA354AB95U, 0x4A0D5DB3U, 0xBEA1A6A0U,
  0x6C124AECU, 0x98BEB1FFU, 0x71E747D9U, 0x854BBCCAU,
  0x202C6452U, 0xD4809F41U, 0x3DD96967U, 0xC9759274U,
  0x1BC67E38U, 0xEF6A852BU, 0x0633730DU, 0xF29F881EU,
  0xB850392EU, 0x4CFCC23DU, 0xA5A5341BU, 0x5109CF08U,
  0x83BA2344U, 0x7716D857U, 0x9E4F2E71U, 0x6AE3D562U,
  0xCF840DFAU, 0x3B28F6E9U, 0xD27100CFU, 0x26DDFBDCU,
  0xF46E1790U, 0x00C2EC83U, 0xE99B1AA5U, 0x1D37E1B6U,
  0x7C0478C5U, 0x88A883D6U, 0x61F175F0U, 0x955D8EE3U,
  0x47EE62AFU, 0xB34299BCU, 0x5A1B6F9AU, 0xAEB79489U,
  0x0BD04C11U, 0xFF7CB702U, 0x16254124U, 0xE289BA37U,
  0x303A567BU, 0xC496AD68U, 0x2DCF5B4EU, 0xD963A05DU,
  0x93AC116DU, 0x6700EA7EU, 0x8E591C58U, 0x7AF5E74BU,
  0xA8460B07U, 0x5CEAF014U, 0xB5B30632U, 0x411FFD21U,
  0xE47825B9U, 0x10D4DEAAU, 0xF98D288CU, 0x0D21D39FU,
  0xDF923FD3U, 0x2B3EC4C0U, 0xC26732E6U, 0x36CBC9F5U,
  0xAFF0A10CU, 0x5B5C5A1FU, 0xB205AC39U, 0x46A9572AU,
  0x941ABB66U, 0x60B64075U, 0x89EFB653U, 0x7D434D40U,
  0xD82495D8U, 0x2C886ECBU, 0xC5D198EDU, 0x317D63FEU,
  0xE3CE8FB2U, 0x176274A1U, 0xFE3B8287U, 0x0A977994U,
  0x4058C8A4U, 0xB4F433B7U, 0x5DADC591U, 0xA9013E82U,
  0x7BB2D2CEU, 0x8F1E29DDU, 0x6647DFFBU, 0x92EB24E8U,
  0x378CFC70U, 0xC3200763U, 0x2A79F145U, 0xDED50A56U,
  0x0C66E61AU, 0xF8CA1D09U, 0x1193EB2FU, 0xE53F103CU,
  0x840C894FU, 0x70A0725CU, 0x99F9847AU, 0x6D557F69U,
  0xBFE69325U, 0x4B4A6836U, 0xA2139E10U, 0x56BF6503U,
  0xF3D8BD9BU, 0x07744688U, 0xEE2DB0AEU, 0x1A814BBDU,
  0xC832A7F1U, 0x3C9E5CE2U, 0xD5C7AAC4U, 0x216B51D7U,
  0x6BA4E0E7U, 0x9F081BF4U, 0x7651EDD2U, 0x82FD16C1U,
  0x504EFA8DU, 0xA4E2019EU, 0x4DBBF7B8U, 0xB9170CABU,
  0x1C70D433U, 0xE8DC2F20U, 0x0185D906U, 0xF5292215U,
  0x279ACE59U, 0xD336354AU, 0x3A6FC36CU, 0xCEC3387FU,
  0xF808F18AU, 0x0CA40A99U, 0xE5FDFCBFU, 0x115107ACU,
  0xC3E2EBE0U, 0x374E10F3U, 0xDE17E6D5U, 0x2ABB1DC6U,
  0x8FDCC55EU, 0x7B703E4DU, 0x9229C86BU, 0x66853378U,
  0xB436DF34U, 0x409A2427U, 0xA9C3D201U, 0x5D6F2912U,
  0x17A09822U, 0xE30C6331U, 0x0A559517U, 0xFEF96E04U,
  0x2C4A8248U, 0xD8E6795BU, 0x31BF8F7DU, 0xC513746EU,
  0x6074ACF6U, 0x94D857E5U, 0x7D81A1C3U, 0x892D5AD0U,
  0x5B9EB69CU, 0xAF324D8FU, 0x466BBBA9U, 0xB2C740BAU,
  0xD3F4D9C9U, 0x275822DAU, 0xCE01D4FCU, 0x3AAD2FEFU,
  0xE81EC3A3U, 0x1CB238B0U, 0xF5EBCE96U, 0x01473585U,
  0xA420ED1DU, 0x508C160EU, 0xB9D5E028U, 0x4D791B3BU,
  0x9FCAF777U, 0x6B660C64U, 0x823FFA42U, 0x76930151U,
  0x3C5CB061U, 0xC8F04B72U, 0x21A9BD54U, 0xD5054647U,
  0x07B6AA0BU, 0xF31A5118U, 0x1A43A73EU, 0xEEEF5C2DU,
  0x4B8884B5U, 0xBF247FA6U, 0x567D8980U, 0xA2D17293U,
  0x70629EDFU, 0x84CE65CCU, 0x6D9793EAU, 0x993B68F9U
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
[!ENDIF!]
[!IF "CrcGeneral/Crc64Mode/__1 = 'CRC_64_TABLE'"!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_64
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
/* [cover parentID={77FC0695-CF6E-4950-9D27-A2E2A3860BDF}]
 * [/cover] */
/* MISRA2012_RULE_8_9_JUSTIFICATION: This data structure is quite
 * big is size, therefore link time relocation of table is
 * provided using Autosar Memmap definition guidelines         */
/* MISRA2012_RULE_8_4_JUSTIFICATION: Crc_Table64 is moved to Crc_Cfg.c for
 * conditional generation but prototype is defined in Crc.c to avoid exposure
 * to user. */
const uint64 Crc_Table64[256] =
{
  0x0000000000000000U, 0x42F0E1EBA9EA3693U, 0x85E1C3D753D46D26U, 0xC711223CFA3E5BB5U,
  0x493366450E42ECDFU, 0x0BC387AEA7A8DA4CU, 0xCCD2A5925D9681F9U, 0x8E224479F47CB76AU,
  0x9266CC8A1C85D9BEU, 0xD0962D61B56FEF2DU, 0x17870F5D4F51B498U, 0x5577EEB6E6BB820BU,
  0xDB55AACF12C73561U, 0x99A54B24BB2D03F2U, 0x5EB4691841135847U, 0x1C4488F3E8F96ED4U,
  0x663D78FF90E185EFU, 0x24CD9914390BB37CU, 0xE3DCBB28C335E8C9U, 0xA12C5AC36ADFDE5AU,
  0x2F0E1EBA9EA36930U, 0x6DFEFF5137495FA3U, 0xAAEFDD6DCD770416U, 0xE81F3C86649D3285U,
  0xF45BB4758C645C51U, 0xB6AB559E258E6AC2U, 0x71BA77A2DFB03177U, 0x334A9649765A07E4U,
  0xBD68D2308226B08EU, 0xFF9833DB2BCC861DU, 0x388911E7D1F2DDA8U, 0x7A79F00C7818EB3BU,
  0xCC7AF1FF21C30BDEU, 0x8E8A101488293D4DU, 0x499B3228721766F8U, 0x0B6BD3C3DBFD506BU,
  0x854997BA2F81E701U, 0xC7B97651866BD192U, 0x00A8546D7C558A27U, 0x4258B586D5BFBCB4U,
  0x5E1C3D753D46D260U, 0x1CECDC9E94ACE4F3U, 0xDBFDFEA26E92BF46U, 0x990D1F49C77889D5U,
  0x172F5B3033043EBFU, 0x55DFBADB9AEE082CU, 0x92CE98E760D05399U, 0xD03E790CC93A650AU,
  0xAA478900B1228E31U, 0xE8B768EB18C8B8A2U, 0x2FA64AD7E2F6E317U, 0x6D56AB3C4B1CD584U,
  0xE374EF45BF6062EEU, 0xA1840EAE168A547DU, 0x66952C92ECB40FC8U, 0x2465CD79455E395BU,
  0x3821458AADA7578FU, 0x7AD1A461044D611CU, 0xBDC0865DFE733AA9U, 0xFF3067B657990C3AU,
  0x711223CFA3E5BB50U, 0x33E2C2240A0F8DC3U, 0xF4F3E018F031D676U, 0xB60301F359DBE0E5U,
  0xDA050215EA6C212FU, 0x98F5E3FE438617BCU, 0x5FE4C1C2B9B84C09U, 0x1D14202910527A9AU,
  0x93366450E42ECDF0U, 0xD1C685BB4DC4FB63U, 0x16D7A787B7FAA0D6U, 0x5427466C1E109645U,
  0x4863CE9FF6E9F891U, 0x0A932F745F03CE02U, 0xCD820D48A53D95B7U, 0x8F72ECA30CD7A324U,
  0x0150A8DAF8AB144EU, 0x43A04931514122DDU, 0x84B16B0DAB7F7968U, 0xC6418AE602954FFBU,
  0xBC387AEA7A8DA4C0U, 0xFEC89B01D3679253U, 0x39D9B93D2959C9E6U, 0x7B2958D680B3FF75U,
  0xF50B1CAF74CF481FU, 0xB7FBFD44DD257E8CU, 0x70EADF78271B2539U, 0x321A3E938EF113AAU,
  0x2E5EB66066087D7EU, 0x6CAE578BCFE24BEDU, 0xABBF75B735DC1058U, 0xE94F945C9C3626CBU,
  0x676DD025684A91A1U, 0x259D31CEC1A0A732U, 0xE28C13F23B9EFC87U, 0xA07CF2199274CA14U,
  0x167FF3EACBAF2AF1U, 0x548F120162451C62U, 0x939E303D987B47D7U, 0xD16ED1D631917144U,
  0x5F4C95AFC5EDC62EU, 0x1DBC74446C07F0BDU, 0xDAAD56789639AB08U, 0x985DB7933FD39D9BU,
  0x84193F60D72AF34FU, 0xC6E9DE8B7EC0C5DCU, 0x01F8FCB784FE9E69U, 0x43081D5C2D14A8FAU,
  0xCD2A5925D9681F90U, 0x8FDAB8CE70822903U, 0x48CB9AF28ABC72B6U, 0x0A3B7B1923564425U,
  0x70428B155B4EAF1EU, 0x32B26AFEF2A4998DU, 0xF5A348C2089AC238U, 0xB753A929A170F4ABU,
  0x3971ED50550C43C1U, 0x7B810CBBFCE67552U, 0xBC902E8706D82EE7U, 0xFE60CF6CAF321874U,
  0xE224479F47CB76A0U, 0xA0D4A674EE214033U, 0x67C58448141F1B86U, 0x253565A3BDF52D15U,
  0xAB1721DA49899A7FU, 0xE9E7C031E063ACECU, 0x2EF6E20D1A5DF759U, 0x6C0603E6B3B7C1CAU,
  0xF6FAE5C07D3274CDU, 0xB40A042BD4D8425EU, 0x731B26172EE619EBU, 0x31EBC7FC870C2F78U,
  0xBFC9838573709812U, 0xFD39626EDA9AAE81U, 0x3A28405220A4F534U, 0x78D8A1B9894EC3A7U,
  0x649C294A61B7AD73U, 0x266CC8A1C85D9BE0U, 0xE17DEA9D3263C055U, 0xA38D0B769B89F6C6U,
  0x2DAF4F0F6FF541ACU, 0x6F5FAEE4C61F773FU, 0xA84E8CD83C212C8AU, 0xEABE6D3395CB1A19U,
  0x90C79D3FEDD3F122U, 0xD2377CD44439C7B1U, 0x15265EE8BE079C04U, 0x57D6BF0317EDAA97U,
  0xD9F4FB7AE3911DFDU, 0x9B041A914A7B2B6EU, 0x5C1538ADB04570DBU, 0x1EE5D94619AF4648U,
  0x02A151B5F156289CU, 0x4051B05E58BC1E0FU, 0x87409262A28245BAU, 0xC5B073890B687329U,
  0x4B9237F0FF14C443U, 0x0962D61B56FEF2D0U, 0xCE73F427ACC0A965U, 0x8C8315CC052A9FF6U,
  0x3A80143F5CF17F13U, 0x7870F5D4F51B4980U, 0xBF61D7E80F251235U, 0xFD913603A6CF24A6U,
  0x73B3727A52B393CCU, 0x31439391FB59A55FU, 0xF652B1AD0167FEEAU, 0xB4A25046A88DC879U,
  0xA8E6D8B54074A6ADU, 0xEA16395EE99E903EU, 0x2D071B6213A0CB8BU, 0x6FF7FA89BA4AFD18U,
  0xE1D5BEF04E364A72U, 0xA3255F1BE7DC7CE1U, 0x64347D271DE22754U, 0x26C49CCCB40811C7U,
  0x5CBD6CC0CC10FAFCU, 0x1E4D8D2B65FACC6FU, 0xD95CAF179FC497DAU, 0x9BAC4EFC362EA149U,
  0x158E0A85C2521623U, 0x577EEB6E6BB820B0U, 0x906FC95291867B05U, 0xD29F28B9386C4D96U,
  0xCEDBA04AD0952342U, 0x8C2B41A1797F15D1U, 0x4B3A639D83414E64U, 0x09CA82762AAB78F7U,
  0x87E8C60FDED7CF9DU, 0xC51827E4773DF90EU, 0x020905D88D03A2BBU, 0x40F9E43324E99428U,
  0x2CFFE7D5975E55E2U, 0x6E0F063E3EB46371U, 0xA91E2402C48A38C4U, 0xEBEEC5E96D600E57U,
  0x65CC8190991CB93DU, 0x273C607B30F68FAEU, 0xE02D4247CAC8D41BU, 0xA2DDA3AC6322E288U,
  0xBE992B5F8BDB8C5CU, 0xFC69CAB42231BACFU, 0x3B78E888D80FE17AU, 0x7988096371E5D7E9U,
  0xF7AA4D1A85996083U, 0xB55AACF12C735610U, 0x724B8ECDD64D0DA5U, 0x30BB6F267FA73B36U,
  0x4AC29F2A07BFD00DU, 0x08327EC1AE55E69EU, 0xCF235CFD546BBD2BU, 0x8DD3BD16FD818BB8U,
  0x03F1F96F09FD3CD2U, 0x41011884A0170A41U, 0x86103AB85A2951F4U, 0xC4E0DB53F3C36767U,
  0xD8A453A01B3A09B3U, 0x9A54B24BB2D03F20U, 0x5D45907748EE6495U, 0x1FB5719CE1045206U,
  0x919735E51578E56CU, 0xD367D40EBC92D3FFU, 0x1476F63246AC884AU, 0x568617D9EF46BED9U,
  0xE085162AB69D5E3CU, 0xA275F7C11F7768AFU, 0x6564D5FDE549331AU, 0x279434164CA30589U,
  0xA9B6706FB8DFB2E3U, 0xEB46918411358470U, 0x2C57B3B8EB0BDFC5U, 0x6EA7525342E1E956U,
  0x72E3DAA0AA188782U, 0x30133B4B03F2B111U, 0xF7021977F9CCEAA4U, 0xB5F2F89C5026DC37U,
  0x3BD0BCE5A45A6B5DU, 0x79205D0E0DB05DCEU, 0xBE317F32F78E067BU, 0xFCC19ED95E6430E8U,
  0x86B86ED5267CDBD3U, 0xC4488F3E8F96ED40U, 0x0359AD0275A8B6F5U, 0x41A94CE9DC428066U,
  0xCF8B0890283E370CU, 0x8D7BE97B81D4019FU, 0x4A6ACB477BEA5A2AU, 0x089A2AACD2006CB9U,
  0x14DEA25F3AF9026DU, 0x562E43B4931334FEU, 0x913F6188692D6F4BU, 0xD3CF8063C0C759D8U,
  0x5DEDC41A34BBEEB2U, 0x1F1D25F19D51D821U, 0xD80C07CD676F8394U, 0x9AFCE626CE85B507U
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_64
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safegaurd. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
[!ENDIF!]
/*******************************************************************************
**                  Channel Transfer notification functions                   **
*******************************************************************************/
[!INDENT "0"!][!//
[!IF "node:exists(./CrcChannelConfig)"!][!//
/* User defined notification functions to be called by CRC driver in case
 * of successful channel tranfer by DMA channel*/
  [!VAR "Totalnumber_of_FCEResource" = "num:i(count(CrcChannelConfig/*))"!][!//
  [!VAR "TransferIsr_List" = "''"!][!//
  [!FOR "FCE_ResourceIndex" = "num:i(0)" TO "num:i($Totalnumber_of_FCEResource) -1"!][!//
    [!SELECT "CrcChannelConfig/*[@index=$FCE_ResourceIndex]"!][!//
    [!VAR "Result_Handler" = "(./CrcResultNotification)"!][!//
    [!IF "$Result_Handler != 'NULL_PTR'"!][!//
      [!IF "not(contains(text:split($TransferIsr_List), $Result_Handler))"!][!//
        [!VAR "TransferIsr_List" = "concat($TransferIsr_List, $Result_Handler, ',')"!][!//
           extern void [!"$Result_Handler"!](uint32 Result);
      [!ENDIF!][!//
    [!ELSE!][!//
      [!ERROR!][!//
        CRC Code Generator: Configure the CrcResultNotification pointer to the CRC notification callback function in the resource configured in the CRC module.
      [!ENDERROR!][!//
    [!ENDIF!][!//
    [!ENDSELECT!][!//
  [!ENDFOR!][!//
/* ************************************************************************** */
[!ENDIF!][!//
[!ENDINDENT!][!//

/*******************************************************************************
**                   Channel Error notification functions                     **
*******************************************************************************/
[!INDENT "0"!][!//
  [!IF "node:exists(./CrcChannelConfig)"!][!//
/* User defined notification functions to be called by CRC driver in case
 * of error from the resource partitions */
    [!VAR "Totalnumber_of_FCEResource" = "num:i(count(CrcChannelConfig/*))"!][!//
    [!VAR "ErrorIsr_List" = "''"!][!//
    [!FOR "FCE_ResourceIndex" = "num:i(0)" TO "num:i($Totalnumber_of_FCEResource) -1"!][!//
      [!SELECT "CrcChannelConfig/*[@index=$FCE_ResourceIndex]"!][!//
      [!VAR "Error_Handler" = "(./CrcErrorNotification)"!][!//
      [!IF "$Error_Handler != 'NULL_PTR'"!][!//
        [!IF "not(contains(text:split($ErrorIsr_List), $Error_Handler))"!][!//
          [!VAR "ErrorIsr_List" = "concat($ErrorIsr_List, $Error_Handler, ',')"!][!//
             extern void [!"$Error_Handler"!](void);
        [!ENDIF!][!//
      [!ELSE!][!//
        [!ERROR!][!//
          CRC Code Generator: Configure the CrcErrorNotification pointer to the CRC error callback function in the resource configured in the CRC module.
        [!ENDERROR!][!//
      [!ENDIF!][!//
      [!ENDSELECT!][!//
    [!ENDFOR!][!//
    /* ************************************************************************** */
  [!ENDIF!][!//
[!ENDINDENT!][!//

/******************************************************************************
**                       Core Specific Configuration                         **
******************************************************************************/
[!NOCODE!][!//
  [!INDENT "0"!][!//
    [!IF "node:exists(./CrcChannelConfig)"!][!//
      [!VAR "Total_CoresConfigured" = "''"!][!//
      [!VAR "MasterCoreNumber" = "num:i(0)"!][!//
      [!/* Get the number of the core configured as the master core */!][!//
      [!CALL "Crc_CG_GetMasterCoreNumber", "MasterCoreNumber" = "num:i(0)"!][!//
      [!VAR "Totalnumber_of_FCEResource" = "num:i(count(CrcChannelConfig/*))"!][!//
      [!FOR "FCE_ResourceIndex" = "num:i(0)" TO "num:i($Totalnumber_of_FCEResource) -1"!][!//
        [!SELECT "CrcChannelConfig/*[@index=$FCE_ResourceIndex]"!][!//
          /*get the FCE channel*/
          [!VAR "FCEChannelID" = "(./CrcChannelId)"!][!//
          /*Result handler for FCE channel: Configured by user in the Treasos for each FCE channel*/
          [!VAR "Result_Handler" = "(./CrcResultNotification)"!][!//
          /*Error handler for FCE channel: Configured by user in the Treasos for each FCE channel*/
          [!VAR "Error_Handler" = "(./CrcErrorNotification)"!][!//
          /*Get only the DMA resource name*/
          [!VAR "index" = "num:i(count(text:split(./CrcDmaChannel, '/')))"!][!//
          [!VAR "CrcDma_reseource" = "text:split(./CrcDmaChannel, '/')[num:i($index)]"!][!//
          [!VAR "DmaChannelNum" = "num:i(0)"!][!//
          [!CALL "Crc_CG_GetDmaChannelNumber", "AllocationName" = "$CrcDma_reseource", "DmaChannelNum" = "$DmaChannelNum"!][!//
          /*now we have the DmaChannelID, find out the core of the channel
          if the channel is allocated and not assigned to anycore it belongs to master core*/
          [!VAR "CGCoreID" = "$MasterCoreNumber"!][!//
          [!CALL "Crc_CG_GenerateModuleMap", "AllocationName" = "$CrcDma_reseource", "Module"="'DMA'", "CGCoreID" = "$CGCoreID"!][!//
          [!CODE!][!//

          /****************************FCE channel Core_[!"$CGCoreID"!] Configuration**********************/
          /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
             because of naming convention*/
          /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
            because of naming convention*/
          /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
            because of naming convention*/
          /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
            because of naming convention*/
          #define CRC_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"$CGCoreID"!]_UNSPECIFIED
          /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
           * guideline. */
          /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
           * without safeguard. It complies to Autosar guidelines. */
          #include "Crc_MemMap.h"
          [!/* [cover parentID={6718B414-B985-4f87-A465-5260FC433809}] */!][!//
          [!/* [/cover] */!][!//
          static const Crc_ChannelConfigType Crc_ChannelConfig_Core[!"$CGCoreID"!]=
           {
            [!INDENT "2"!][!//
              /*FCE channel number*/
              [!"$FCEChannelID"!]U,
              /*DMA channel number*/
              [!"$DmaChannelNum"!]U,
              /*Result handler configured by the user for the channel*/
              [!"$Result_Handler"!],
              /*Error handler configured by the user for the channel*/
              [!"$Error_Handler"!]
            [!ENDINDENT!][!//
           };
          /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
           * because of naming convention*/
          /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
           * because of naming convention*/
          /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
           * because of naming convention*/
          /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
           * because of naming convention*/
          #define CRC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"$CGCoreID"!]_UNSPECIFIED
          /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
           * guideline. */
          /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
           * without safeguard. It complies to Autosar guidelines. */
          #include "Crc_MemMap.h"
          /**********************************************************************************/
          [!ENDCODE!][!//
          /*add the core to the configured core list*/
          [!VAR "Total_CoresConfigured" = "concat($Total_CoresConfigured, $CGCoreID, ',')"!][!//
        [!ENDSELECT!][!//
      [!ENDFOR!][!//
    [!ENDIF!][!//
  [!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!INDENT "0"!][!//
  [!IF "node:exists(./CrcChannelConfig) and $Totalnumber_of_FCEResource != num:i(0)"!][!//
    /***************************Configured Cores***********************************/
    /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
     * because of naming convention*/
    /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
     * because of naming convention*/
    /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
     * because of naming convention*/
    /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
     * because of naming convention*/
    #define CRC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
    /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
     * guideline. */
    /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
     * without safeguard. It complies to Autosar guidelines. */
    #include "Crc_MemMap.h"
    [!/* [cover parentID={E3AF5093-2FCF-45a5-AFBA-2AB287B40719}] */!][!//
    [!/* [/cover] */!][!//
    /* MISRA2012_RULE_8_4_JUSTIFICATION: Crc_ChannelConfig is moved to Crc_Cfg.c for
     * conditional generation but prototype is defined in Crc.c to avoid exposure
     * to user. */
    const Crc_ChannelConfigType *const Crc_ChannelConfig[6] =
    {
    [!INDENT "2"!][!//
      [!FOR "ChannelCoreIndex" = "0" TO "num:i(5)"!][!//
        [!VAR "ChannelCoreName" = "$ChannelCoreIndex"!][!//
        [!IF "not(contains(text:split($Total_CoresConfigured), $ChannelCoreName))"!][!//
          /*Core[!"$ChannelCoreName"!] is not configured or not available*/
          NULL_PTR,
        [!ELSE!][!//
          /*Config parameter for Core[!"$ChannelCoreName"!]*/
          &Crc_ChannelConfig_Core[!"$ChannelCoreName"!],
        [!ENDIF!][!//
      [!ENDFOR!][!//
    [!ENDINDENT!][!//
    };
    /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
     * because of naming convention*/
    /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
     * because of naming convention*/
    /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
     * because of naming convention*/
    /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
     * because of naming convention*/
    #define CRC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
    /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
     * guideline. */
    /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
     * without safeguard. It complies to Autosar guidelines. */
    #include "Crc_MemMap.h"
  [!ELSE!][!//
    /* None of the core is configured with FCE resources*/
  [!ENDIF!][!//
[!ENDINDENT!][!//
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
[!ENDSELECT!][!//
