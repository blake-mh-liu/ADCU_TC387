/* Mk_c2_defaults.h
 *
 * This file contains the default configuration parameters for core 2.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_C2_DEFAULTS_H
#define MK_C2_DEFAULTS_H

/* Default size of kernel stack
*/
#ifndef MK_CFG_C2_KERNEL_STACK_NELEMENTS
#define MK_CFG_C2_KERNEL_STACK_NELEMENTS	256
#endif

/* Define the default core properties
 * Default value for the master core is MK_COREPROP_STARTAUTO, otherwise MK_COREPROP_STARTMANUAL
*/
#if MK_CFG_HWMASTERCOREINDEX == 2
#define MK_CFG_C2_PROPERTIES           MK_COREPROP_STARTAUTO
#else
#define MK_CFG_C2_PROPERTIES           MK_COREPROP_STARTMANUAL
#endif

/* Default configuration for the invalid message handler on core 2
 *
 * There currently are three variants to choose from on how invalid cross core messages are handled:
 * MK_IgnoreInvalidXcoreMessage:	The error is ignored
 * MK_CountInvalidXcoreMessage:		The error is ignored, but counted in coreVars->nDroppedMessages
 * MK_PanicInvalidXcoreMessage:		A Panic is initiated in response to the error
*/
#ifndef MK_CFG_C2_MSG_INVALIDHANDLER
#define MK_CFG_C2_MSG_INVALIDHANDLER           MK_CountInvalidXcoreMessage
#endif

/* Default configuration for the idle thread on core 2
*/

#ifndef MK_CFG_C2_IDLE_FUNCTION
#define MK_CFG_C2_IDLE_FUNCTION				MK_Idle
#endif

#ifndef MK_CFG_C2_IDLE_MODE
#define MK_CFG_C2_IDLE_MODE					MK_THRMODE_USER
#endif

/* interrupts need to be enabled in the IDLE thread */
#define MK_CFG_C2_IDLE_LEVEL				MK_HWENABLEALLLEVEL
#define MK_CFG_C2_IDLE_IRQEN				MK_THRIRQ_ENABLE

#define MK_CFG_C2_IDLE_FPUEN				MK_THRFPU_DISABLE
#define MK_CFG_C2_IDLE_HWS					MK_THRHWS_DEFAULT

#ifndef MK_CFG_C2_IDLE_MEMPART
#define MK_CFG_C2_IDLE_MEMPART				(-1)
#endif

#ifndef MK_CFG_C2_IDLE_STACK_NELEMENTS
#define MK_CFG_C2_IDLE_STACK_NELEMENTS		8
#endif


/* Default configuration for the init ("main") thread on core 2
*/
#ifndef MK_CFG_C2_INIT_FUNCTION
#define MK_CFG_C2_INIT_FUNCTION				main
#endif

#ifndef MK_CFG_C2_INIT_MODE
#define MK_CFG_C2_INIT_MODE					MK_THRMODE_USER
#endif

#define MK_CFG_C2_INIT_LEVEL				MK_HWONLYXCORELEVEL
#define MK_CFG_C2_INIT_IRQEN				MK_THRIRQ_ENABLE

#define MK_CFG_C2_INIT_FPUEN				MK_THRFPU_DISABLE
#define MK_CFG_C2_INIT_HWS					MK_THRHWS_DEFAULT

#ifndef MK_CFG_C2_INIT_QPRIO
#error "MK_CFG_C2_INIT_QPRIO must be defined by the configuration"
#endif

#ifndef MK_CFG_C2_INIT_RPRIO
#error "MK_CFG_C2_INIT_RPRIO must be defined by the configuration"
#endif

#ifndef MK_CFG_C2_INIT_MEMPART
#define MK_CFG_C2_INIT_MEMPART				(-1)
#endif

#ifndef MK_CFG_C2_INIT_STACK_NELEMENTS
#error "MK_CFG_C2_INIT_STACK_NELEMENTS must be defined by the configuration"
#endif


/* Default configuration for the shutdown idle thread on core 2
*/
#ifndef MK_CFG_C2_SHUTDOWN_FUNCTION
#define MK_CFG_C2_SHUTDOWN_FUNCTION			MK_Idle
#endif

#ifndef MK_CFG_C2_SHUTDOWN_MODE
#define MK_CFG_C2_SHUTDOWN_MODE				MK_THRMODE_USER
#endif

#define MK_CFG_C2_SHUTDOWN_LEVEL			MK_HWONLYXCORELEVEL
#define MK_CFG_C2_SHUTDOWN_IRQEN			MK_THRIRQ_ENABLE

#define MK_CFG_C2_SHUTDOWN_FPUEN			MK_THRFPU_DISABLE
#define MK_CFG_C2_SHUTDOWN_HWS				MK_THRHWS_DEFAULT

#ifndef MK_CFG_C2_SHUTDOWN_MEMPART
#define MK_CFG_C2_SHUTDOWN_MEMPART			(-1)
#endif

#ifndef MK_CFG_C2_SHUTDOWN_STACK_NELEMENTS
#define MK_CFG_C2_SHUTDOWN_STACK_NELEMENTS	8
#endif


/* Default configuration for the error hook thread on core 2
*/
#ifndef MK_CFG_C2_HAS_ERRORHOOK
#define MK_CFG_C2_HAS_ERRORHOOK				0
#endif

#if MK_CFG_C2_HAS_ERRORHOOK

#define MK_CFG_C2_ERRORHOOK_FUNCTION		ErrorHook

#ifndef MK_CFG_C2_ERRORHOOK_MODE
#define MK_CFG_C2_ERRORHOOK_MODE			MK_THRMODE_USER
#endif

#ifndef MK_CFG_C2_ERRORHOOK_LEVEL
#error "MK_CFG_C2_ERRORHOOK_LEVEL must be defined by the configuration"
#endif

#define MK_CFG_C2_ERRORHOOK_FPUEN			MK_THRFPU_DISABLE
#define MK_CFG_C2_ERRORHOOK_IRQEN			MK_THRIRQ_ENABLE

#define MK_CFG_C2_ERRORHOOK_HWS				MK_THRHWS_DEFAULT

#ifndef MK_CFG_C2_ERRORHOOK_QPRIO
#error "MK_CFG_C2_ERRORHOOK_QPRIO must be defined by the configuration"
#endif

#ifndef MK_CFG_C2_ERRORHOOK_RPRIO
#error "MK_CFG_C2_ERRORHOOK_RPRIO must be defined by the configuration"
#endif

#ifndef MK_CFG_C2_ERRORHOOK_MEMPART
#define MK_CFG_C2_ERRORHOOK_MEMPART			(-1)
#endif

#ifndef MK_CFG_C2_ERRORHOOK_STACK_NELEMENTS
#error "MK_CFG_C2_ERRORHOOK_STACK_NELEMENTS must be defined by the configuration"
#endif

#endif

/* Default configuration for the protection hook thread on core 2
*/
#ifndef MK_CFG_C2_HAS_PROTECTIONHOOK
#define MK_CFG_C2_HAS_PROTECTIONHOOK		0
#endif

#if MK_CFG_C2_HAS_PROTECTIONHOOK

#define MK_CFG_C2_PROTECTIONHOOK_FUNCTION	ProtectionHook

#ifndef MK_CFG_C2_PROTECTIONHOOK_MODE
#define MK_CFG_C2_PROTECTIONHOOK_MODE		MK_THRMODE_USER
#endif

#ifndef MK_CFG_C2_PROTECTIONHOOK_LEVEL
#error "MK_CFG_C2_PROTECTIONHOOK_LEVEL must be defined by the configuration"
#endif

#define MK_CFG_C2_PROTECTIONHOOK_IRQEN		MK_THRIRQ_ENABLE

#define MK_CFG_C2_PROTECTIONHOOK_FPUEN		MK_THRFPU_DISABLE
#define MK_CFG_C2_PROTECTIONHOOK_HWS		MK_THRHWS_DEFAULT

#ifndef MK_CFG_C2_PROTECTIONHOOK_MEMPART
#define MK_CFG_C2_PROTECTIONHOOK_MEMPART	(-1)
#endif

#ifndef MK_CFG_C2_PROTECTIONHOOK_QPRIO
#error "MK_CFG_C2_PROTECTIONHOOK_QPRIO must be defined by the configuration"
#endif

#ifndef MK_CFG_C2_PROTECTIONHOOK_RPRIO
#error "MK_CFG_C2_PROTECTIONHOOK_RPRIO must be defined by the configuration"
#endif

#ifndef MK_CFG_C2_PROTECTIONHOOK_STACK_NELEMENTS
#error "MK_CFG_C2_PROTECTIONHOOK_STACK_NELEMENTS must be defined by the configuration"
#endif

#endif


/* Default configuration for the counter subsystem thread on core 2
*/
#define MK_CFG_C2_HAS_CTRSUB				1

#if MK_CFG_C2_HAS_CTRSUB

#ifndef MK_CFG_C2_CTRSUB_MODE
#error "MK_CFG_C2_CTRSUB_MODE must be defined by the configuration"
#endif

#define MK_CFG_C2_CTRSUB_LEVEL				MK_HWENABLEALLLEVEL
#define MK_CFG_C2_CTRSUB_IRQEN				MK_THRIRQ_ENABLE

#define MK_CFG_C2_CTRSUB_FPUEN				MK_THRFPU_DISABLE
#define MK_CFG_C2_CTRSUB_HWS				MK_THRHWS_DEFAULT

#ifndef MK_CFG_C2_CTRSUB_QPRIO
#error "MK_CFG_C2_CTRSUB_QPRIO must be defined by the configuration"
#endif

#ifndef MK_CFG_C2_CTRSUB_RPRIO
#error "MK_CFG_C2_CTRSUB_RPRIO must be defined by the configuration"
#endif

#ifndef MK_CFG_C2_CTRSUB_MEMPART
#define MK_CFG_C2_CTRSUB_MEMPART				(-1)
#endif

#ifndef MK_CFG_C2_CTRSUB_STACK_NELEMENTS
#define MK_CFG_C2_CTRSUB_STACK_NELEMENTS		64
#endif

#else

/* Define stack requirement as zero for use in the stack size calculation
*/
#define MK_CFG_C2_CTRSUB_STACK_NELEMENTS      0

#endif


/* Default configuration for the shutdown hook thread on core 2
*/
#ifndef MK_CFG_C2_HAS_SHUTDOWNHOOK
#define MK_CFG_C2_HAS_SHUTDOWNHOOK			0
#endif

#if MK_CFG_C2_HAS_SHUTDOWNHOOK

#define MK_CFG_C2_SHUTDOWNHOOK_FUNCTION		ShutdownHook

#ifndef MK_CFG_C2_SHUTDOWNHOOK_MODE
#define MK_CFG_C2_SHUTDOWNHOOK_MODE			MK_THRMODE_USER
#endif

#ifndef MK_CFG_C2_SHUTDOWNHOOK_LEVEL
#error "MK_CFG_C2_SHUTDOWNHOOK_LEVEL must be defined by the configuration"
#endif

#define MK_CFG_C2_SHUTDOWNHOOK_IRQEN		MK_THRIRQ_ENABLE

#define MK_CFG_C2_SHUTDOWNHOOK_FPUEN		MK_THRFPU_DISABLE
#define MK_CFG_C2_SHUTDOWNHOOK_HWS			MK_THRHWS_DEFAULT

#ifndef MK_CFG_C2_SHUTDOWNHOOK_QPRIO
#error "MK_CFG_C2_SHUTDOWNHOOK_QPRIO must be defined by the configuration"
#endif

#ifndef MK_CFG_C2_SHUTDOWNHOOK_RPRIO
#error "MK_CFG_C2_SHUTDOWNHOOK_RPRIO must be defined by the configuration"
#endif

#ifndef MK_CFG_C2_SHUTDOWNHOOK_MEMPART
#define MK_CFG_C2_SHUTDOWNHOOK_MEMPART		(-1)
#endif

#ifndef MK_CFG_C2_SHUTDOWNHOOK_STACK_NELEMENTS
#error "MK_CFG_C2_SHUTDOWNHOOK_STACK_NELEMENTS must be defined by the configuration"
#endif

#else

/* Define stack requirement as zero for use in the stack size calculation
*/
#define MK_CFG_C2_SHUTDOWNHOOK_STACK_NELEMENTS	0

#endif


/* Default configuration for the trusted function thread on core 2
*/
#ifndef MK_CFG_C2_HAS_TRUSTEDFUNCTION
#define MK_CFG_C2_HAS_TRUSTEDFUNCTION		0
#endif

#if MK_CFG_C2_HAS_TRUSTEDFUNCTION

#define MK_CFG_C2_TF_MODE					MK_THRMODE_USER
#define MK_CFG_C2_TF_LEVEL					MK_HWENABLEALLLEVEL
#define MK_CFG_C2_TF_IRQEN					MK_THRIRQ_ENABLE
#define MK_CFG_C2_TF_FPUEN					MK_THRFPU_DISABLE
#define MK_CFG_C2_TF_HWS					MK_THRHWS_DEFAULT

#ifndef MK_CFG_C2_TF_QPRIO
#error "MK_CFG_C2_TF_QPRIO must be defined by the configuration"
#endif

#ifndef MK_CFG_C2_TF_RPRIO
#error "MK_CFG_C2_TF_RPRIO must be defined by the configuration"
#endif

#ifndef MK_CFG_C2_TF_STACK_NELEMENTS
#error "MK_CFG_C2_TF_STACK_NELEMENTS must be defined by the configuration"
#endif

#else

/* Define stack requirement as zero for use in the stack size calculation
*/
#define MK_CFG_C2_TF_STACK_NELEMENTS		0

#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
