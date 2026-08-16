#ifndef __MGS_FMT_LIT_H__
#define __MGS_FMT_LIT_H__

// This is originally a u_long *,
// with (DG_LIT *)( lit + 1 ) used to access the lights
typedef struct LIT {
    int    n_lights;
    DG_LIT lights[0];
} LIT;

#endif // __MGS_FMT_LIT_H__
