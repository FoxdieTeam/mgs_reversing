#ifndef __MGS_GAME_H__
#define __MGS_GAME_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "menu/menuman.h"
#include "sound/sd_cli.h"
#include "sound/g_sound.h"

#include "charadef.h"
//#include "linkvar.h"
#include "g_define.h"
#include "g_struct.h"
#include "g_extern.h"
#include "g_macro.h"

#include "camera.h"
#include "strctrl.h"

/*---------------------------------------------------------------------------*/

enum GAMED_STATE {          // private to gamed.c
    WAIT_LOAD   = 0,
    WORKING     = 1
};

typedef struct {            // private to gamed.c
    GV_ACT actor;
    enum GAMED_STATE status;
    int killing_count;
} gameWork;

/*---------------------------------------------------------------------------*/
#endif // __MGS_GAME_H__
