/* Mk_trustedfunction.h - private header for activation of trusted function threads
 *
 * This file contains definitions for the microkernel's handling of trusted function threads.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_TRUSTEDFUNCTION_H
#define MK_TRUSTEDFUNCTION_H

#include <public/Mk_public_types.h>
#include <private/Mk_types_forward.h>
#include <private/Mk_thread.h>
#include <private/Mk_jobqueue.h>
#include <private/Mk_core.h>

#ifndef MK_ASM

/* MK_nTrustedFunctions is a constant that contains the number of trusted functions.
*/
extern const mk_objquantity_t MK_nTrustedFunctions;

/* MK_TFJ_SIZE - size of a trusted function job buffer
 *
 * A trusted function is passed two parameters. The first is the function ID and the second is
 * a void *. We only need to put the second parameter into the job buffer because the id is already
 * there. Also, trusted functions need special handling because (on some processors) the pointer
 * parameter might be passed using a different register.
*/
#define MK_TFJ_SIZE	4

#if MK_TFJ_SIZE > MK_BJ_MAX
#error "Development error: a trusted function job won't fit into a standard job buffer!"
#endif

/* Trusted function configuration.
 *
 * This structure consists of the items from a thread configuration that change per trusted function.
*/

typedef void (*mk_trustedfunction_t)(mk_objectid_t, void *);
typedef struct mk_trustedfunctioncfg_s mk_trustedfunctioncfg_t;
struct mk_trustedfunctioncfg_s
{
	const mk_char_t *name;			/* The name of the trusted function */
	mk_objectid_t coreIndex;		/* Index of the core that it runs on */
	mk_trustedfunction_t func;		/* Thread entry function (i.e. the actual trusted function, TRUSTED_xxx */
	mk_hwps_t ps;					/* Initial processor status (processor mode, interrupt status, level etc.) */
	mk_objectid_t memoryPartition;	/* Index of memory partition */
};

/* A macro to provide an initializer for a mk_trustedfunctioncfg_t element.
*/
#define MK_TRUSTEDFUNCTIONCFG(name, coreIdx, func, pm, fpu, hws, partIdx) \
{																				\
	(name),																		\
	(coreIdx),																		\
	(func),																		\
	MK_HWPS_INIT((pm), MK_HWENABLEALLLEVEL, MK_THRIRQ_ENABLE, (fpu), (hws)),	\
	(partIdx)																	\
}


/* The system's trusted function configuration is a constant array of individual config structs.
*/
extern const mk_trustedfunctioncfg_t * const MK_trustedFunctionCfg;

#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
