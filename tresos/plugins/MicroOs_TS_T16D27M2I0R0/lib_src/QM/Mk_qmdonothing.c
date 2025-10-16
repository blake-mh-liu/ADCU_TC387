/* Mk_qmdonothing.c
 *
 * This file contains the function MK_QmDoNothing()
 *
 * The reason for its existence is so that it can be called from template code that must be adapted
 * by the user, so serve as an indication that the template has not been adapted correctly.
 *
 * Most template functions are called from the board package, but the functions in the board package are
 * called directly and therefore cannot have "Qm" in their name. This means that they don't show up in
 * a QM search through the final binary, as demanded by the Safety Manual.
 *
 * If the board functions as delivered call other template functions, there is no great problem. But if they
 * do not need to call any other templates, but still need to be adapted, a call to MK_QmDoNothing()
 * marks the binary as "QM".
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <QM/Mk_qmdonothing.h>

/* MK_QmDoNothing() - do an uncertified nothing.
*/
void MK_QmDoNothing(void)
{
	do
	{
		/* nothing */
	} while (0);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
