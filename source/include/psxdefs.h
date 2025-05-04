/**
 * Supplemental definitions for PSX SDK headers
 */
#ifndef _PSXDEFS_H_
#define _PSXDEFS_H_

// Due to none of the OpenEvent callbacks using the correct prototype,
// we now have to cast them to avoid warnings.
typedef long (*openevent_cb_t)();

#endif // _PSXDEFS_H_
