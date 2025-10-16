/* This header file does not have an include guard,
 * because it can be used multiple times to check the required OS versions.
*/

/* This Header file represents the micro kernel version.
 * EB tresos AutoCore OS 2.0.176.
*/

#include <Mk_Version.h>

#ifndef MK_TMPL_REQ_MK_SW_MAJOR_VERSION
#define MK_TMPL_REQ_MK_SW_MAJOR_VERSION	2U
#endif
#ifndef MK_TMPL_REQ_MK_SW_MINOR_VERSION
#define MK_TMPL_REQ_MK_SW_MINOR_VERSION	0U
#endif
#ifndef MK_TMPL_REQ_MK_SW_PATCH_VERSION
#define MK_TMPL_REQ_MK_SW_PATCH_VERSION	232U
#endif

#if (MK_TMPL_REQ_MK_SW_MAJOR_VERSION != MK_SW_MAJOR_VERSION)
#error "This template code requires a different MK major version."
#endif
#if (MK_TMPL_REQ_MK_SW_MINOR_VERSION != MK_SW_MINOR_VERSION)
#error "This template code requires a different MK minor version."
#endif
#if (MK_TMPL_REQ_MK_SW_PATCH_VERSION != MK_SW_PATCH_VERSION)
#error "This template code requires a different MK patch version."
#endif
