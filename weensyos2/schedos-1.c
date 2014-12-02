#include "schedos-app.h"
#include "x86sync.h"

/*****************************************************************************
 * schedos-1
 *
 *   This tiny application prints red "1"s to the console.
 *   It yields the CPU to the kernel after each "1" using the sys_yield()
 *   system call.  This lets the kernel (schedos-kern.c) pick another
 *   application to run, if it wants.
 *
 *   The other schedos-* processes simply #include this file after defining
 *   PRINTCHAR appropriately.
 *
 *****************************************************************************/

#ifndef PRINTCHAR
#define PRINTCHAR	('1' | 0x0C00)
#endif

#ifndef SHARE
#define SHARE 1
#endif

void
start(void)
{
	int i;

	sys_set_share(SHARE);

	for (i = 0; i < RUNCOUNT; i++) {
		// Write characters to the console, yielding after each one.
		sys_acquire_lock();
		{
			*cursorpos++ = PRINTCHAR;
		}
		sys_release_lock();
		sys_yield();
	}

	sys_exit(0);
}
