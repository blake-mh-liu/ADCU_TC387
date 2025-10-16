/* Mk_types_forward.h - private types ("forward" declarations)
 *
 * This file declares the types for the private kernel structures without
 * declaring the structures, so that the types can be used as targets in pointer declarations.
 *
 * If the actual structure is needed the header file that declares the structure
 * should be included instead of this.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 1.3 (required)
 *  There shall be no occurrence of undefined or critical unspecified behaviour.
 *
 * Reason:
 *  Information hiding. For example, the structure should be visible in a debugger but not in the
 *  application source code, or a pointer type is declared before the structure can be fully defined.
 *  Note: MISRA-C:2012 Dir 4.8 advises that incomplete declarations should be used where possible
 *
 * MISRAC2012-2) Deviated Rule: 5.7 (required)
 *  A tag name shall be a unique identifier.
 *
 * Reason:
 *  False positive because the struct is used in a forward type definition.
 *
*/
/* Deviation MISRAC2012-1 <*>, MISRAC2012-2 <*> */
#ifndef MK_TYPES_FORWARD_H
#define MK_TYPES_FORWARD_H

#ifndef MK_ASM
typedef struct mk_appcfg_s mk_appcfg_t;
typedef struct mk_irq_s mk_irq_t;
typedef struct mk_jobqueuecfg_s mk_jobqueuecfg_t;
typedef struct mk_jobqueue_s mk_jobqueue_t;
typedef struct mk_kernelcontrol_s mk_kernelcontrol_t;
typedef struct mk_memorypartition_s mk_memorypartition_t;
typedef struct mk_memoryregion_s mk_memoryregion_t;
typedef struct mk_memoryregionmap_s mk_memoryregionmap_t;
typedef struct mk_ctrsubservicedescriptor_s mk_ctrsubservicedescriptor_t;
typedef struct mk_lock_s mk_lock_t;
typedef struct mk_lockcfg_s mk_lockcfg_t;
typedef struct mk_taskcfg_s mk_taskcfg_t;
typedef struct mk_threadcfg_s mk_threadcfg_t;

typedef struct mk_message_s mk_message_t;
typedef mk_message_t *mk_msgptr_t;
typedef const mk_message_t *mk_constmsgptr_t;
typedef volatile mk_msgptr_t mk_msgptrfield_t;
typedef struct mk_msgqueuedescriptor_s mk_msgqueuedescriptor_t;
typedef struct mk_msgqueuepair_s mk_msgqueuepair_t;
#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
