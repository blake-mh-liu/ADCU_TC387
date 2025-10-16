# MicroOs_filelist_TRICORE.mak - lists of files that go into the microkernel build

# This file just contains lists of files that go into various parts of the
# build for the TRICORE Architecture.
# The file is also included into the unsupported make so it must be compatible.

# MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C is the list of all the C files in the
# plugin/lib_src/CPUFAMILY directory that go into the kernel library.
# These files are listed without prefix or extension.

MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	hwallocatethreadregisters
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	freethreadregisters
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	handlevirtualaddresstrap
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	handleprotectiontrap
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	handleinstructiontrap
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	handlecontexttrap
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	handlebuserrortrap
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	handleassertiontrap
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	handlenmi
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	hwclearcorevars
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	hwinitinterruptcontroller
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	syscall
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	exceptionhandlercommon
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	fillexceptioninfo
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	fillpanicexceptioninfo
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	hwinitprocessor
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	dispatchinterruptsoft
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	initcsalist
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	hwinitmemoryprotection
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	reconfiguresrnsrc
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	intirconfigdriver
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	setandchecksrcvalue
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	fillexinfohelper
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	sststm
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	writeendinit

ifeq ($(MkFeature_TricoreTosValueValidityCheck),enabled)
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	waitforsrcupdateinlwsroftos
endif

ifneq ($(MK_MAXCORES),1)
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_C +=	hwsetcorevars
endif

# MK_LIBSRCCPUFAMILY_KLIB_BASELIST_S is the list of all the assembler files in the
# plugin/lib_src/CPUFAMILY directory that go into the kernel library.
# These files are listed without prefix or extension.
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_S +=	resumethread
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_S +=	allocatetwocsas
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_S +=	swapfcx
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_S +=	vectortables
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_S +=	hwenablememoryprotection
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_S +=	hwsetupexceptions
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_S +=	setupinterrupttable
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_S +=	entry2
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_S +=   enabletps
MK_LIBSRCCPUFAMILY_KLIB_BASELIST_S +=	bootcsalist

# The system-call stubs are written in assembly language ...
# See the global MicroOs_filelists.mak for details
MK_LIBSRCCPUFAMILY_ULIB_BASELIST_S +=	$(addprefix usr, $(MK_SYSTEMCALL_BASELIST))
MK_LIBSRCCPUFAMILY_ULIB_BASELIST_S +=	$(addprefix usr, $(MK_OSCALL_BASELIST))
MK_LIBSRCCPUFAMILY_ULIB_BASELIST_S +=	usrwaitgetclearevent

# Userland function for reading the time from STM.
MK_LIBSRCCPUFAMILY_ULIB_BASELIST_C	+=	hwreadtime

# MK_SRCCPUFAMILY_BASELIST_C is the list of all the C files in the
# plugin/src/CPUFAMILY directory, without prefix or extension.
# These files go directly into the system build.
MK_SRCCPUFAMILY_BASELIST_C	+= TRICORE_configuration
MK_SRCCPUFAMILY_BASELIST_C	+= TRICORE_c0_configuration
ifeq (2,$(firstword $(sort 2 $(MK_MAXCORES))))
MK_SRCCPUFAMILY_BASELIST_C	+= TRICORE_c1_configuration
endif
ifeq (3,$(firstword $(sort 3 $(MK_MAXCORES))))
MK_SRCCPUFAMILY_BASELIST_C	+= TRICORE_c2_configuration
endif
ifeq (4,$(firstword $(sort 4 $(MK_MAXCORES))))
MK_SRCCPUFAMILY_BASELIST_C	+= TRICORE_c3_configuration
endif
ifeq (5,$(firstword $(sort 5 $(MK_MAXCORES))))
MK_SRCCPUFAMILY_BASELIST_C	+= TRICORE_c4_configuration
endif
ifeq (6,$(firstword $(sort 6 $(MK_MAXCORES))))
MK_SRCCPUFAMILY_BASELIST_C	+= TRICORE_c5_configuration
endif
MK_SRCCPUFAMILY_BASELIST_C  += TRICORE_exectickconv

# MK_SRCCPUFAMILY_BASELIST_S is the list of all the assembler files in the
# plugin/src/CPUFAMILY directory, without prefix or extension.
# These files go directly into the system build.
#MK_SRCCPUFAMILY_BASELIST_S += TRICORE_foo

# MK_SRCQMCPUFAMILY_BASELIST_C is the list of all the assembler files in the
# plugin/src/QM/CPUFAMILY directory, without prefix or extension.
# These files go directly into the system build.
#MK_SRCQMCPUFAMILY_BASELIST_S += entry
