#ifndef _PSYQ_H_
#define _PSYQ_H_

#include <sys/types.h>
#include <libapi.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libspu.h>
#include <libcd.h>
#include <libpress.h>
#include <memory.h>
#include <strings.h>
#include <rand.h>

// Due to none of the OpenEvent callbacks using the correct prototype,
// we now have to cast them to avoid warnings.
typedef long (*openevent_cb_t)();

// Can't include <stdio.h> here as printf has been redefined.
int sprintf(char *buffer, const char *fmt, ...);

#endif // _PSYQ_H_
