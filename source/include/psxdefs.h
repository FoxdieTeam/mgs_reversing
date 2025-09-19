/**
 * Supplemental definitions for PSX SDK headers
 */
#ifndef __MGS_PSXDEFS_H__
#define __MGS_PSXDEFS_H__

// Due to none of the OpenEvent callbacks using the correct prototype,
// we now have to cast them to avoid warnings.
typedef long (*openevent_cb_t)();

/* scratch pad address 0x1f800000 - 0x1f800400 */
#define getScratchAddr2(type, offset)   ((type *)(0x1f800000+(offset)))

#endif // __MGS_PSXDEFS_H__
