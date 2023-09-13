#ifndef _PSYQ_H_
#define _PSYQ_H_

#include <SYS/TYPES.H>
#include <LIBAPI.H>
#include <LIBETC.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include <LIBSN.H>
#include <LIBSPU.H>
#include <LIBCD.H>
#include <LIBPAD.H>
#include <MEMORY.H>
#include <STRINGS.H>
#include <RAND.H>

// Can't include STDIO.H here as printf has been redefined to null
int sprintf(char *buffer, const char *fmt, ...);

#endif // _PSYQ_H_
