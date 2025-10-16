/***************************************************************************
 *
 * lockinghooks.h
 *
 * Sample for implementation of interupt locking hooks using suspend/resume
 * callouts.
 *
 * (c) Elektrobit Automotive GmbH
 *
 * Elektrobit Automotive GmbH
 * Phone: +49 (0)9131 7701 0
 * Am Wolfsmantel 46, 91058 Erlangen
 * GERMANY
 *
 *
 * This example illustrates how an interrupt locking hook can be implemented
 * which is called before/after unlocking/locking interrupts. It is achieved
 * by using the interrupt locking callouts. The preprocessor switch
 *
 *                    MK_USE_INT_LOCKING_CALLOUTS
 *
 * must be set to a non-zero value to enable the callouts.
 ****************************************************************************/

#ifndef _LOCKINGHOOKS_H
#define _LOCKINGHOOKS_H

#include <public/Mk_public_types.h>
#include <public/Mk_autosar.h>

void TMPL_InterruptLockingHook(mk_objecttype_t, mk_objectid_t, mk_serviceid_t, mk_lockid_t);

#endif /* _LOCKINGHOOKS_H */
