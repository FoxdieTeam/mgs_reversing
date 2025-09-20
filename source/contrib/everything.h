// used to generate decomp.me contexts / import into ida/ghidra
#define GHIDRA_CONTEXT

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <libapi.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libcd.h>
#include <libpad.h>
#include <libpress.h>
#include <libspu.h>
#include <libsn.h>
#include "psxdefs.h"

#include "common.h"
#include "inline_n.h"
#include "charadef.h"
#include "strcode.h"

#include "mts/mts.h"
#include "mts/mts_new.h"
#include "mts/mts_pad.h"
#include "sd/sd_cli.h"
#include "sd/sd_incl.h"
#include "sd/sd_ext.h"

#include "libgv/libgv.h"
#include "libfs/libfs.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "memcard/memcard.h"

#include "game/game.h"
#include "game/delay.h"
#include "linkvar.h"
#include "game/item.h"
#include "game/jimctrl.h"
#include "game/loader.h"
#include "game/motion.h"
#include "game/vibrate.h"
#include "font/font.h"

#include "chara/snake/afterse.h"
#include "chara/snake/shadow.h"
#include "chara/snake/sna_hzd.h"
#include "chara/snake/sna_init.h"
#include "anime/animconv/anime.h"
#include "bullet/bullet.h"
#include "equip/equip.h"
#include "weapon/weapon.h"
#include "kojo/demo.h"
#include "menu/menuman.h"
#include "menu/radar.h"
#include "menu/radio.h"
#include "okajima/blood.h"
#include "okajima/claymore.h"
#include "okajima/d_bloodr.h"
#include "okajima/spark.h"
#include "okajima/stgfd_io.h"
#include "okajima/stngrnd.h"
#include "takabe/goggle.h"
#include "takabe/goggleir.h"
#include "takabe/scn_mask.h"
#include "thing/door.h"
#include "thing/sgtrect3.h"
#include "thing/sight.h"
