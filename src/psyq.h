#ifndef _PSYQ_H_
#define _PSYQ_H_

#include <SYS/TYPES.H>
#include <LIBAPI.H>
#include <LIBETC.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include <LIBSPU.H>
#include <LIBCD.H>
#include <LIBPRESS.H>
#include <MEMORY.H>
#include <STRINGS.H>
#include <RAND.H>

// Due to none of the OpenEvent callbacks using the correct prototype,
// we now have to cast them to avoid warnings.
typedef long (*openevent_cb_t)();

// Can't include STDIO.H here as printf has been redefined to null
int sprintf(char *buffer, const char *fmt, ...);

#endif // _PSYQ_H_
