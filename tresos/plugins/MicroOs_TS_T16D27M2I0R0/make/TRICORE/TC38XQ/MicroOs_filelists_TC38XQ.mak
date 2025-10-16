# MicroOs_filelists_TC38XQ.mak - lists of files that go into the microkernel build
#
# This file just contains lists of files that go into various parts of the
# build for the TRICORE Architecture.
# The file is also included into the unsupported make so it must be compatible.

# MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C is the list of all the C files in the
# plugin/lib_src/CPUFAMILY directory that go into the kernel library.
# These files are listed without prefix or extension.
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C += getcoreirqtos_tc3xx
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C += hwsetstaticmemorypartition_tc161

# MK_LIBSRCCPUFAMILY_KLIB_BASELIST_S is the list of all the assembler files in the
# plugin/lib_src/CPUFAMILY directory that go into the kernel library.
# These files are listed without prefix or extension.
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_S += dogetcpxe dogetdpr dogetdprwe dosetcpr dosetcpxe dosetdpr dosetdprwe compilerstackcheckfail

# No additional files needed for this derivate
#MK_LIBSRCCPUFAMILY_KLIB_BASELIST_S +=

# MK_SRCCPUFAMILY_BASELIST_C is the list of all the C files in the
# plugin/src/CPUFAMILY directory, without prefix or extension.
# These files go directly into the system build.
MK_SRCCPUFAMILY_BASELIST_C	+= TRICORE_hwsetdynamicmemorypartition_tc161

# MK_SRCCPUFAMILY_BASELIST_S is the list of all the assembler files in the
# plugin/src/CPUFAMILY directory, without prefix or extension.
# These files go directly into the system build.
MK_SRCCPUFAMILY_BASELIST_S += TRICORE_c0_checkdynamicmpuregisters_tc162
MK_SRCCPUFAMILY_BASELIST_S += TRICORE_c0_writedynamicmpuregisters_tc162
MK_SRCCPUFAMILY_BASELIST_S += TRICORE_c1_checkdynamicmpuregisters_tc162
MK_SRCCPUFAMILY_BASELIST_S += TRICORE_c1_writedynamicmpuregisters_tc162
MK_SRCCPUFAMILY_BASELIST_S += TRICORE_c2_checkdynamicmpuregisters_tc162
MK_SRCCPUFAMILY_BASELIST_S += TRICORE_c2_writedynamicmpuregisters_tc162
MK_SRCCPUFAMILY_BASELIST_S += TRICORE_c3_checkdynamicmpuregisters_tc162
MK_SRCCPUFAMILY_BASELIST_S += TRICORE_c3_writedynamicmpuregisters_tc162


# TC38XQ has multi-core support so we add the multi-core lists here.
MK_LIBSRCKERN_KLIB_BASELIST +=	$(MK_LIBSRCKERN_KLIB_MC_BASELIST)
