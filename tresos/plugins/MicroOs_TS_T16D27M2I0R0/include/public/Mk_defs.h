/* Mk_defs.h
 *
 * This file contains identifying definitions for the known processor families and toolchains,
 * for use when defining MK_CPUFAMILY and MK_TOOL.
 *
 * The Makefiles must ensure that these macros are defined appropriately on
 * the command line.
 *
 * Example: -DMK_TOOL=MK_gnu -DMK_CPUFAMILY=MK_PA
 *
 * Many processor families require the MK_CPU macro as well. The definitions
 * for the CPU are handled in the hardware-specific files. Overlap
 * of allocated numbers between processor families is not a problem, because
 * the processor files will/should never be mixed.
 *
 * The value 0 is never used, because that is the value that preprocessors
 * return for undefined symbols.
 *
 * CAVEAT:
 * The presence of a toolchain or processor here doesn't imply a commitment
 * to support the toolchain or processor in the future.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_DEFS_H
#define MK_DEFS_H

#ifndef MK_TOOL
#error "MK_TOOL is not defined. Check your Makefiles!"
#endif

#ifndef MK_CPUFAMILY
#error "MK_CPUFAMILY is not defined. Check your Makefiles!"
#endif

/* Known toolchains
 *
 * In EB tradition, toolchain names in the makefiles are lowercase
 *
 * Note: presence of a toolchain in this list does not imply a commitment to provide support
 * for that toolchain in any future version of the microkernel.
*/
#define MK_gnu			1
#define MK_diab			2
#define MK_tasking		3
#define MK_ghs			4
#define MK_cosmic		5
#define MK_mwerks		6
#define MK_softune		7
#define MK_realview		8
#define MK_iar			9
#define MK_vc			10
#define MK_renesas		11
#define MK_cw			12
#define MK_ticgt		13
#define MK_armkeil		16

/* Known processor families.
 *
 * Note: presence of a processor family in this list does not imply a commitment to provide support
 * for that processor family in any future version of the microkernel.
*/
#define MK_PA			1
#define MK_TRICORE		2
#define MK_ARM			3
#define MK_RH850		4
#define MK_ARM64		5
#define MK_CORTEXM		6
#define MK_BLANKFAMILY	99

/* Endianness. MK_ENDIAN must be one of these
*/
#define MK_LITTLEENDIAN	1
#define MK_BIGENDIAN	2

/* Stack direction. MK_STACKGROWS must be one of these
*/
#define MK_STACKGROWSDOWN	1
#define MK_STACKGROWSUP		2

/* Characteristics of division with negative result. MK_HWNEGDIV must be one of these.
 *
 * Possible behavior:                     -5/3    -5%3    5/(-3)    5%(-3)
 *    - rounds towards zero                -1      -2      -1         2
 *    - rounds towards minus infinity      -2       1      -2        -1
 *
 * The macro MK_NEGDIV and the documentation in the HW/SW interface specification satisfies the
 * requirements of MISRA-2004 rule 3.3
 *
 * In the unlikely event that we find a processor that rounds pos/neg and neg/pos in
 * different directions, we will need  two more cases here.
*/
#define MK_NEGDIV_ROUNDTOWARDZERO		1
#define MK_NEGDIV_ROUNDTOWARDMINUSINF	2

/* Possible values for MK_MEM_PROT. Specifies the type of memory protection scheme used. Derivatives
 * either use an MPU or an MMU.
*/
#define MK_MEM_PROT_MPU		1
#define MK_MEM_PROT_MMU		2

/* Possible values for MK_CACHEOP_PRIVILEGE.
 * Specifies whether cache maintenance operations are possible in user or
 * supervisor mode. (User mode typically includes supervisor mode, but not vice
 * versa.)
*/
#define MK_CACHEOP_SUPERVISOR	1
#define MK_CACHEOP_USER			2

#endif

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
