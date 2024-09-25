/**
 * Supplemental definitions for PSX SDK headers
 */
#ifndef _PSXSDK_H_
#define _PSXSDK_H_

// Due to none of the OpenEvent callbacks using the correct prototype,
// we now have to cast them to avoid warnings.
typedef long (*openevent_cb_t)();

#endif // _PSXSDK_H_
