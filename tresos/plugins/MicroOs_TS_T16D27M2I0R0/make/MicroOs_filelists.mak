# MicroOs_filelists.mak - lists of files that go into the microkernel build
#
# This file just contains lists of files that go into various parts of the
# build.
# The file is also included into the unsupported make so it must be compatible.
# So ...
# Anyone who puts DOS/Windows-specific constructs here (including, but not
# limited to, backslash separators, cygwin dependencies, dependencies on
# asc_Make) will be taken out and summarily executed.
# YOU HAVE BEEN WARNED
#
# (c) Elektrobit Automotive GmbH

#===============================================================================
# System call list
#===============================================================================
#
# MK_SYSTEMCALL_HANDLER_BASELIST is the list of all system call handlers.
# MK_MC_SYSTEMCALL_HANDLER_BASELIST is the list of all system call handlers which are only present on multi-cores.
#
# MK_SYSTEMCALL_BASELIST is a list of base filenames for the system calls.
#  - If there is a system call handler, we need a system call (MK_SYSTEMCALL_HANDLER_BASELIST).
#  - In all cases we need be able to handle multi-core system calls (MK_MC_SYSTEMCALL_HANDLER_BASELIST).
#
# We need to separate the "system call list" from the "system call handler list", because there
# are system calls which don't have their own handler under certain circumstances.
#
# Note: waitgetclearevent is not in this list because there's no sys function
MK_SYSTEMCALL_HANDLER_BASELIST += activatetask
MK_SYSTEMCALL_HANDLER_BASELIST += chaintask
MK_SYSTEMCALL_HANDLER_BASELIST += acquirelock
MK_SYSTEMCALL_HANDLER_BASELIST += releaselock
MK_SYSTEMCALL_HANDLER_BASELIST += startos
MK_SYSTEMCALL_HANDLER_BASELIST += schedule
MK_SYSTEMCALL_HANDLER_BASELIST += shutdown
MK_SYSTEMCALL_HANDLER_BASELIST += terminateself
MK_SYSTEMCALL_HANDLER_BASELIST += waitevent
MK_SYSTEMCALL_HANDLER_BASELIST += setevent
MK_SYSTEMCALL_HANDLER_BASELIST += clearevent
MK_SYSTEMCALL_HANDLER_BASELIST += gettaskid
MK_SYSTEMCALL_HANDLER_BASELIST += getisrid
MK_SYSTEMCALL_HANDLER_BASELIST += gettaskstate
MK_SYSTEMCALL_HANDLER_BASELIST += reporterror
MK_SYSTEMCALL_HANDLER_BASELIST += callctrsub
MK_SYSTEMCALL_HANDLER_BASELIST += calltrustedfunction
MK_SYSTEMCALL_HANDLER_BASELIST += allowaccess
MK_SYSTEMCALL_HANDLER_BASELIST += terminateapplication
MK_SYSTEMCALL_HANDLER_BASELIST += enableinterruptsource
MK_SYSTEMCALL_HANDLER_BASELIST += disableinterruptsource
MK_SYSTEMCALL_HANDLER_BASELIST += asynccallctrsub
MK_SYSTEMCALL_HANDLER_BASELIST += addoncontrol
MK_SYSTEMCALL_HANDLER_BASELIST += sstadvancecounter
MK_SYSTEMCALL_HANDLER_BASELIST += sststartcounter
MK_SYSTEMCALL_HANDLER_BASELIST += sststopcounter
MK_SYSTEMCALL_HANDLER_BASELIST += getappmodevoteofcore

MK_MC_SYSTEMCALL_HANDLER_BASELIST += startcore
MK_MC_SYSTEMCALL_HANDLER_BASELIST += shutdownallcores
MK_MC_SYSTEMCALL_HANDLER_BASELIST += asyncactivatetask
MK_MC_SYSTEMCALL_HANDLER_BASELIST += asyncsetevent

ifeq (2,$(firstword $(sort 2 $(MK_MAXCORES))))
MK_SYSTEMCALL_HANDLER_BASELIST += $(MK_MC_SYSTEMCALL_HANDLER_BASELIST)
MK_SYSTEMCALL_BASELIST += $(MK_SYSTEMCALL_HANDLER_BASELIST)
else
MK_SYSTEMCALL_BASELIST += $(MK_SYSTEMCALL_HANDLER_BASELIST) $(MK_MC_SYSTEMCALL_HANDLER_BASELIST)
endif


#===============================================================================
# Lists of base filenames for the kernel library
#===============================================================================
# MK_LIBSRCKERN_KLIB_BASELIST is the list of all files in the plugin/lib_src/kernel directory that
# go into the kernel library.
# The files are listed without prefix or extension.
# DON'T PUT SYSTEM-CALL KERNEL-SIDE FUNCTIONS HERE! - Put them in MK_SYSTEMCALL_BASELIST!!!
MK_LIBSRCKERN_KLIB_BASELIST	+=	appstateok
MK_LIBSRCKERN_KLIB_BASELIST	+=	bjqappend
MK_LIBSRCKERN_KLIB_BASELIST	+=	bjqremove
MK_LIBSRCKERN_KLIB_BASELIST	+=	calculatectrsubcallermaxprio
MK_LIBSRCKERN_KLIB_BASELIST +=	clearcorevars
MK_LIBSRCKERN_KLIB_BASELIST +=	clearisrs
MK_LIBSRCKERN_KLIB_BASELIST +=	clearlocklist
MK_LIBSRCKERN_KLIB_BASELIST +=	clearlocks
MK_LIBSRCKERN_KLIB_BASELIST +=	cleartasks
MK_LIBSRCKERN_KLIB_BASELIST +=	clearthread
MK_LIBSRCKERN_KLIB_BASELIST +=	data
MK_LIBSRCKERN_KLIB_BASELIST +=	datainitcheck
MK_LIBSRCKERN_KLIB_BASELIST	+=	dequeuethread
MK_LIBSRCKERN_KLIB_BASELIST	+=	dispatch
MK_LIBSRCKERN_KLIB_BASELIST	+=	dispatchinterruptsoft
MK_LIBSRCKERN_KLIB_BASELIST	+=	enqueuethread
MK_LIBSRCKERN_KLIB_BASELIST	+=	errorinternaltoosek
MK_LIBSRCKERN_KLIB_BASELIST +=	fillthreadregisters
MK_LIBSRCKERN_KLIB_BASELIST +=	findfirstthread
MK_LIBSRCKERN_KLIB_BASELIST +=	increasepriority
MK_LIBSRCKERN_KLIB_BASELIST +=	idle
MK_LIBSRCKERN_KLIB_BASELIST +=	initaddon
MK_LIBSRCKERN_KLIB_BASELIST +=	initapplications
MK_LIBSRCKERN_KLIB_BASELIST +=	initcorevars
MK_LIBSRCKERN_KLIB_BASELIST +=	initdatasections
MK_LIBSRCKERN_KLIB_BASELIST +=	initexecutionbudgetmonitor
MK_LIBSRCKERN_KLIB_BASELIST +=	initinterrupts
MK_LIBSRCKERN_KLIB_BASELIST +=	initmemoryprotection
MK_LIBSRCKERN_KLIB_BASELIST +=	initmemoryregion
MK_LIBSRCKERN_KLIB_BASELIST +=	initlocks
MK_LIBSRCKERN_KLIB_BASELIST +=	isallowedtoshutdown
MK_LIBSRCKERN_KLIB_BASELIST +=  isexecutionbudgetconfigured
MK_LIBSRCKERN_KLIB_BASELIST	+=	jqappend
MK_LIBSRCKERN_KLIB_BASELIST	+=	jqinit
MK_LIBSRCKERN_KLIB_BASELIST	+=	jqremove
MK_LIBSRCKERN_KLIB_BASELIST	+=	jqremovealltasksofapp
MK_LIBSRCKERN_KLIB_BASELIST	+=	threadqueueempty
MK_LIBSRCKERN_KLIB_BASELIST	+=	ortitracethreadchange
MK_LIBSRCKERN_KLIB_BASELIST	+=	panic
MK_LIBSRCKERN_KLIB_BASELIST	+=	panicstop
MK_LIBSRCKERN_KLIB_BASELIST +=	ppacontinue
MK_LIBSRCKERN_KLIB_BASELIST +=	ppapanic
MK_LIBSRCKERN_KLIB_BASELIST +=	ppapanicstop
MK_LIBSRCKERN_KLIB_BASELIST +=	ppashutdown
MK_LIBSRCKERN_KLIB_BASELIST +=	ppaterminatetaskisr
MK_LIBSRCKERN_KLIB_BASELIST +=	ppaterminateapplication
MK_LIBSRCKERN_KLIB_BASELIST +=	ppaterminateapplicationrestart
MK_LIBSRCKERN_KLIB_BASELIST +=	ppaterminatethread
MK_LIBSRCKERN_KLIB_BASELIST +=	rejectshutdown
MK_LIBSRCKERN_KLIB_BASELIST +=	internreporterror
MK_LIBSRCKERN_KLIB_BASELIST +=	interngetappmodevoteofcore
MK_LIBSRCKERN_KLIB_BASELIST +=	reportprotectionfault
MK_LIBSRCKERN_KLIB_BASELIST	+=	requeuethread
MK_LIBSRCKERN_KLIB_BASELIST +=	restartapplication
MK_LIBSRCKERN_KLIB_BASELIST +=	setupthread
MK_LIBSRCKERN_KLIB_BASELIST +=	shutdown
MK_LIBSRCKERN_KLIB_BASELIST +=	localactivatetask
MK_LIBSRCKERN_KLIB_BASELIST +=	localdisableinterruptsource
MK_LIBSRCKERN_KLIB_BASELIST +=	localenableinterruptsource
MK_LIBSRCKERN_KLIB_BASELIST +=	localgettaskstate
MK_LIBSRCKERN_KLIB_BASELIST +=	localsetevent
MK_LIBSRCKERN_KLIB_BASELIST +=	localcallctrsub
MK_LIBSRCKERN_KLIB_BASELIST +=	localterminateapplication
MK_LIBSRCKERN_KLIB_BASELIST +=	localsstadvancecounter
MK_LIBSRCKERN_KLIB_BASELIST +=	localsststartcounter
MK_LIBSRCKERN_KLIB_BASELIST +=	localsststopcounter
MK_LIBSRCKERN_KLIB_BASELIST +=	sstinit
MK_LIBSRCKERN_KLIB_BASELIST +=	ssttickerinterrupthandler
MK_LIBSRCKERN_KLIB_BASELIST +=	startchildthread
MK_LIBSRCKERN_KLIB_BASELIST +=	startkernel
MK_LIBSRCKERN_KLIB_BASELIST +=	startctrsubterminateapplication
MK_LIBSRCKERN_KLIB_BASELIST +=	startthread
MK_LIBSRCKERN_KLIB_BASELIST +=	startthreadforisr
MK_LIBSRCKERN_KLIB_BASELIST +=	startthreadforctrsubisr
MK_LIBSRCKERN_KLIB_BASELIST +=	startup
MK_LIBSRCKERN_KLIB_BASELIST +=	startupcheckcorevars
MK_LIBSRCKERN_KLIB_BASELIST +=	startuppanic
MK_LIBSRCKERN_KLIB_BASELIST +=	syscall
MK_LIBSRCKERN_KLIB_BASELIST +=	terminatethread
MK_LIBSRCKERN_KLIB_BASELIST +=	terminateapplication
MK_LIBSRCKERN_KLIB_BASELIST +=	unknowninterrupt
MK_LIBSRCKERN_KLIB_BASELIST +=	unknownctrsubcall
MK_LIBSRCKERN_KLIB_BASELIST +=	unknownsyscall
MK_LIBSRCKERN_KLIB_BASELIST +=	$(addprefix sys, $(MK_SYSTEMCALL_HANDLER_BASELIST))

# MMU only kernel lib files:
ifeq ($(MK_MEM_PROT),MK_MEM_PROT_MMU)
MK_LIBSRCKERN_KLIB_BASELIST +=	heapallocate
MK_LIBSRCKERN_KLIB_BASELIST +=	generateflatpartitionmap
MK_LIBSRCKERN_KLIB_BASELIST +=	checkregionalignment
endif

# Single-core only kernel lib files:
ifeq ($(MK_MAXCORES),1)
MK_LIBSRCKERN_KLIB_BASELIST +=	getlockobjectfromidsingle
endif

# Sema42 generic spinlock implementation
ifeq ($(MK_SEMA42_SPINLOCKS),1)
MK_LIBSRCKERN_KLIB_BASELIST += tryspinlocksema42
endif

#===============================================================================
# Lists of base filenames for the kernel library for multi-core systems.
#===============================================================================
# MK_LIBSRCKERN_KLIB_MC_BASELIST is the list of extra files in the plugin/lib_src/kernel directory that
# go into the kernel library for multi-core systems only.
# The files are listed without prefix or extension.
# Derivatives with multi-core features add this list to MK_LIBSRCKERN_KLIB_BASELIST
# DON'T PUT SYSTEM-CALL KERNEL-SIDE FUNCTIONS HERE! - Put them in MK_SYSTEMCALL_BASELIST!!!
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	addxcorectrsubjob
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	clearspinlocks
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	countinvalidxcoremessage
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	crosscoremessagehandler
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	genericgetcorevarsstartup
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	getlockobjectfromidmulti
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	handlemessagesfrom
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	ignoreinvalidxcoremessage
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	initmessagequeues
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	initsynchere
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	multiactivatetask
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	multisetevent
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	multigettaskstate
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	multicallctrsub
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	multidisableinterruptsource
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	multienableinterruptsource
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	multiterminateapplication
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	panicinvalidxcoremessage
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	reportdroppedxcorerequest
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	sendmessage
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	startupchecksynchere
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	startupinitdatasectionsmulti
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	synchere
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	xcoreactivatetask
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	xcoreasyncactivatetask
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	xcoregettaskstate
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	xcorecallctrsub
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	xcoreasynccallctrsub
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	xcorereply
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	xcoresetevent
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	xcoreasyncsetevent
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	xcorestartcore
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	xcoreshutdown
MK_LIBSRCKERN_KLIB_MC_BASELIST +=	xcoreterminateapplication


#===============================================================================
# Lists of base filenames for the user library
#===============================================================================
# MK_LIBSRCUSER_ULIB_BASELIST is the list of all files in the plugin/lib_src/user directory
# that go into the User library.
# The files are listed without prefix or extension.
MK_LIBSRCUSER_ULIB_BASELIST += libgetalarm
MK_LIBSRCUSER_ULIB_BASELIST += libcallctrsub1
MK_LIBSRCUSER_ULIB_BASELIST += libcallctrsub2
MK_LIBSRCUSER_ULIB_BASELIST += libcallctrsub3
MK_LIBSRCUSER_ULIB_BASELIST += libasynccallctrsub1
MK_LIBSRCUSER_ULIB_BASELIST += libasynccallctrsub2
MK_LIBSRCUSER_ULIB_BASELIST += libasynccallctrsub3
MK_LIBSRCUSER_ULIB_BASELIST += libcalltrustedfunction
MK_LIBSRCUSER_ULIB_BASELIST += libgetcountervalue
MK_LIBSRCUSER_ULIB_BASELIST += libgetevent
MK_LIBSRCUSER_ULIB_BASELIST += libgeterrorinfoforcore
MK_LIBSRCUSER_ULIB_BASELIST += libgetexceptioninfoforcore
MK_LIBSRCUSER_ULIB_BASELIST += libgetpanicexceptioninfoforcore
MK_LIBSRCUSER_ULIB_BASELIST += liblookupexceptioninfoforcore
MK_LIBSRCUSER_ULIB_BASELIST += libgetntasks
MK_LIBSRCUSER_ULIB_BASELIST += libgetpanicreasonforcore
MK_LIBSRCUSER_ULIB_BASELIST += libgetprotectioninfoforcore
MK_LIBSRCUSER_ULIB_BASELIST += libgettaskid
MK_LIBSRCUSER_ULIB_BASELIST += libgettaskstate
MK_LIBSRCUSER_ULIB_BASELIST += liberrorgetserviceidforcore
MK_LIBSRCUSER_ULIB_BASELIST += liberrorgetparameterforcore
MK_LIBSRCUSER_ULIB_BASELIST += libelapsedtime
MK_LIBSRCUSER_ULIB_BASELIST += libelapsedtime32
MK_LIBSRCUSER_ULIB_BASELIST += libelapsedmicroseconds
MK_LIBSRCUSER_ULIB_BASELIST += libisschedulenecessary
MK_LIBSRCUSER_ULIB_BASELIST += libscheduleifnecessary
MK_LIBSRCUSER_ULIB_BASELIST += libwaitgetclearevent
MK_LIBSRCUSER_ULIB_BASELIST += libgetappstateforctrsub
MK_LIBSRCUSER_ULIB_BASELIST += libresumeinterrupts
MK_LIBSRCUSER_ULIB_BASELIST += libsuspendinterrupts
MK_LIBSRCUSER_ULIB_BASELIST += libgetapplicationid
MK_LIBSRCUSER_ULIB_BASELIST += libgetcurrentapplicationid
MK_LIBSRCUSER_ULIB_BASELIST += libgetapplicationstate

MK_LIBSRCUSER_ULIB_BASELIST += libgetappmodevoteofcore
MK_LIBSRCUSER_ULIB_BASELIST += libiscoreinuse

# Functions that differ between 32-bit and 64-bit architectures
ifeq ($(MK_64BIT_ARCH),1)
MK_LIBSRCUSER_ULIB_BASELIST += libdifftime32_64
MK_LIBSRCUSER_ULIB_BASELIST += libmuldiv64
else
MK_LIBSRCUSER_ULIB_BASELIST += libdifftime
MK_LIBSRCUSER_ULIB_BASELIST += libdifftime32
MK_LIBSRCUSER_ULIB_BASELIST += libmuldiv
endif

# Single-core only functions.
ifeq ($(MK_MAXCORES), 1)
MK_LIBSRCUSER_ULIB_BASELIST += libconditionalgetresourcesingle
endif

# NOTE Multicore functions only if processor is multi-core
ifeq (2,$(firstword $(sort 2 $(MK_MAXCORES))))
MK_LIBSRCUSER_ULIB_BASELIST += libgetphysicalcoreid
MK_LIBSRCUSER_ULIB_BASELIST += libgetlogicalcoreid
MK_LIBSRCUSER_ULIB_BASELIST += libconditionalgetresourcemulti
MK_LIBSRCUSER_ULIB_BASELIST += libgetcoreid
MK_LIBSRCUSER_ULIB_BASELIST += libgetspinlock
MK_LIBSRCUSER_ULIB_BASELIST += libtrytogetspinlock
MK_LIBSRCUSER_ULIB_BASELIST += libgettaskcoreid
MK_LIBSRCUSER_ULIB_BASELIST += libgetcountercoreid
MK_LIBSRCUSER_ULIB_BASELIST += libgetalarmcoreid
MK_LIBSRCUSER_ULIB_BASELIST += libgetscheduletablecoreid
MK_LIBSRCUSER_ULIB_BASELIST += libwaitforreply
MK_LIBSRCUSER_ULIB_BASELIST += libwaitforreplyandvalue
endif

#===============================================================================
# Lists of base filenames for QM files in the user library
#===============================================================================
# MK_LIBSRCQM_ULIB_BASELIST is the list of all files in the plugin/lib_src/QM directory that
# go into the user library.
# The files are listed without prefix or extension.
MK_LIBSRCQM_ULIB_BASELIST	+=	qmdonothing

#===============================================================================
# Lists of architecture base filenames for the user library
#===============================================================================
# MK_LIBSRCCPUFAMILY_ULIB_BASELIST_x is the list of all files in the plugin/lib_src/$CPUFAMILY directory
# that go into the User library.
# The files are listed without prefix or extension. These files go into the user library.
#
# The basenames of these files are the same for all architectures because they are the stub
# functions that make the system calls.
# It is not known here whether these are C or assembly-language files, so the
# architecture file list must make these assignments with _x replaced by _S or _C as appropriate
#MK_LIBSRCCPUFAMILY_ULIB_BASELIST_x	+=	$(addprefix usr, $(MK_SYSTEMCALL_BASELIST))
#MK_LIBSRCCPUFAMILY_ULIB_BASELIST_x	+=	$(addprefix usr, $(MK_OSCALL_BASELIST))

#===============================================================================
# Lists of base filenames for the error library
#===============================================================================

#===============================================================================
# Lists of base filenames for the binary build
#===============================================================================
# MK_SRC_CFG_BASELIST is the list of all configuration-dependent files in the plugin/src directory,
# without prefix or extension. These files go straight into the system build
MK_SRC_CFG_BASELIST +=	configuration
MK_SRC_CFG_BASELIST +=	configuration_sst

MK_SRC_CFG_BASELIST +=	c0_configuration
MK_SRC_CFG_BASELIST +=	c0_kernel_stack
MK_SRC_CFG_BASELIST +=	c0_idleshutdown_stack
MK_SRC_CFG_BASELIST +=	c0_aux1_stack
MK_SRC_CFG_BASELIST +=	c0_aux2_stack
MK_SRC_CFG_BASELIST +=	c0_errorhook_stack
MK_SRC_CFG_BASELIST +=	c0_protectionhook_stack
MK_SRC_CFG_BASELIST +=	c0_configuration_sst


# The following ifs check in a shell-independent way whether MK_MAXCORES is at least X
# It works by lexically sorting the list X MK_MAXCORES, then check if the first (i.e. the smallest value)
# of the result list is X. If it is, MK_MAXCORES >= X. Otherwise, MK_MAXCORES would appear as the first
# word in the list and fail the comparison.
# This works for up to 9 cores, for more we would have to prefix the smaller numbers with 0.

ifeq (2,$(firstword $(sort 2 $(MK_MAXCORES))))
MK_SRC_CFG_BASELIST +=	c1_configuration
MK_SRC_CFG_BASELIST +=	c1_kernel_stack
MK_SRC_CFG_BASELIST +=	c1_idleshutdown_stack
MK_SRC_CFG_BASELIST +=	c1_aux1_stack
MK_SRC_CFG_BASELIST +=	c1_aux2_stack
MK_SRC_CFG_BASELIST +=	c1_errorhook_stack
MK_SRC_CFG_BASELIST +=	c1_protectionhook_stack
MK_SRC_CFG_BASELIST +=	c1_configuration_sst
endif

ifeq (3,$(firstword $(sort 3 $(MK_MAXCORES))))
MK_SRC_CFG_BASELIST +=	c2_configuration
MK_SRC_CFG_BASELIST +=	c2_kernel_stack
MK_SRC_CFG_BASELIST +=	c2_idleshutdown_stack
MK_SRC_CFG_BASELIST +=	c2_aux1_stack
MK_SRC_CFG_BASELIST +=	c2_aux2_stack
MK_SRC_CFG_BASELIST +=	c2_errorhook_stack
MK_SRC_CFG_BASELIST +=	c2_protectionhook_stack
MK_SRC_CFG_BASELIST +=	c2_configuration_sst
endif

ifeq (4,$(firstword $(sort 4 $(MK_MAXCORES))))
MK_SRC_CFG_BASELIST +=	c3_configuration
MK_SRC_CFG_BASELIST +=	c3_kernel_stack
MK_SRC_CFG_BASELIST +=	c3_idleshutdown_stack
MK_SRC_CFG_BASELIST +=	c3_aux1_stack
MK_SRC_CFG_BASELIST +=	c3_aux2_stack
MK_SRC_CFG_BASELIST +=	c3_errorhook_stack
MK_SRC_CFG_BASELIST +=	c3_protectionhook_stack
MK_SRC_CFG_BASELIST +=	c3_configuration_sst
endif

ifeq (5,$(firstword $(sort 5 $(MK_MAXCORES))))
MK_SRC_CFG_BASELIST +=	c4_configuration
MK_SRC_CFG_BASELIST +=	c4_kernel_stack
MK_SRC_CFG_BASELIST +=	c4_idleshutdown_stack
MK_SRC_CFG_BASELIST +=	c4_aux1_stack
MK_SRC_CFG_BASELIST +=	c4_aux2_stack
MK_SRC_CFG_BASELIST +=	c4_errorhook_stack
MK_SRC_CFG_BASELIST +=	c4_protectionhook_stack
MK_SRC_CFG_BASELIST +=	c4_configuration_sst
endif

ifeq (6,$(firstword $(sort 6 $(MK_MAXCORES))))
MK_SRC_CFG_BASELIST +=	c5_configuration
MK_SRC_CFG_BASELIST +=	c5_kernel_stack
MK_SRC_CFG_BASELIST +=	c5_idleshutdown_stack
MK_SRC_CFG_BASELIST +=	c5_aux1_stack
MK_SRC_CFG_BASELIST +=	c5_aux2_stack
MK_SRC_CFG_BASELIST +=	c5_errorhook_stack
MK_SRC_CFG_BASELIST +=	c5_protectionhook_stack
MK_SRC_CFG_BASELIST +=	c5_configuration_sst
endif


MK_SRC_CFG_BASELIST +=	configuration_addon
MK_SRC_CFG_BASELIST +=	configuration_application
MK_SRC_CFG_BASELIST +=	configuration_interrupt
MK_SRC_CFG_BASELIST +=	configuration_job
MK_SRC_CFG_BASELIST +=	configuration_memoryprotection
MK_SRC_CFG_BASELIST +=	configuration_protectionaction
MK_SRC_CFG_BASELIST +=	configuration_ctrsub
MK_SRC_CFG_BASELIST +=	configuration_lock
MK_SRC_CFG_BASELIST +=	configuration_task
MK_SRC_CFG_BASELIST +=	configuration_trustedfunction
MK_SRC_CFG_BASELIST +=	configuration_syscall

ifeq (2,$(firstword $(sort 2 $(MK_MAXCORES))))
MK_SRC_CFG_BASELIST +=	configuration_xcall
endif

#MK_SRC_CFG_BASELIST +=	board
MK_SRC_CFG_BASELIST +=	softwarevectortable

# MK_GEN_CFG_BASELIST is the list of all generated files
# without prefix or extension. These files go straight into the system build
MK_GEN_CFG_BASELIST +=	gen_global

# OS_GEN_CFG_BASELIST is the list of all generated files (OS files)
# without prefix or extension. These files go straight into the system build
OS_GEN_CFG_BASELIST +=	gen

#===============================================================================
# Lists of base filenames for files which belong to a certain feature.
#===============================================================================
# Code should be added as a "feature" as soon as it is used by more than one derivative.

# Some derivatives need the ExtendTimer feature to provide a 64-bit time stamp.
ifeq ($(MkFeature_ExtendTimer),enabled)
MK_LIBSRCKERN_KLIB_BASELIST +=	extendtimer
MK_LIBSRCUSER_ULIB_BASELIST +=	libgenericreadtime
endif

#===============================================================================
# Addons
#===============================================================================
# Any addon can drop a named MicroOs_addon_*_filelists.mak in this
# directory. Include it as well.
-include $(MicroOs_MAKE_PATH)/MicroOs_addon_*_filelists.mak
