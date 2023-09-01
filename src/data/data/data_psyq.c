#include "linker.h"
#include "data.h"

#include "data/rdata/rdata.h"
#include "libfs/libfs.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Menu/menuman.h"
#include "libdg/libdg.h"
#include "Thing/door.h"
#include "mts/mts_new.h"
#include "Game/game.h"
#include "Game/control.h"
#include "chara/snake/sna_init.h"
#include "Equip/bodyarm.h"
#include "Equip/gasmask.h"
#include "Equip/box.h"
#include "Equip/bandana.h"
#include "Anime/animeconv/anime.h"
#include "libgcl/hash.h"
#include "Menu/menuman.h"
#include "Menu/radio.h"
#include "Bullet/blast.h"
#include "Weapon/aam.h"
#include "Equip/jpegcam.h"
#include "Menu/radar.h"

int         SECTION(".data") CD_cbread_800A3DD0 = 0;
int         SECTION(".data") CD_read_dma_mode_800A3DD4[] = {0, 0, 0};
int         SECTION(".data") dword_800A3DE0[] = {0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,       0,
                                                 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0x47350, 0x440000};
int         SECTION(".data") CD_cbsync_800A3E68 = 0;
int         SECTION(".data") CD_cbready_800A3E6C = 0;
int         SECTION(".data") CD_debug_800A3E70 = 0;
int         SECTION(".data") CD_status_800A3E74 = 0;
int         SECTION(".data") CD_status1_800A3E78 = 0;
int         SECTION(".data") CD_nopen_800A3E7C = 0;
char        SECTION(".data") CD_pos_800A3E80[] = {2, 0, 0, 0};
char        SECTION(".data") CD_com_800A3E84[] = {0, 0, 0, 0, 0, 0, 0, 0};
int         SECTION(".data") CD_comstr_800A3E8C[] = {(int)aCdlsync,           (int)aCdlnop,
                                                     (int)aCdlsetloc,         (int)aCdlplay,
                                                     (int)aCdlforward,        (int)aCdlbackward,
                                                     (int)aCdlreadn,          (int)aCdlstandby,
                                                     (int)aCdlstop,           (int)aCdlpause,
                                                     (int)aCdlreset,          (int)aCdlmute,
                                                     (int)aCdldemute,         (int)dword_800141CC + 0x10,
                                                     (int)dword_800141CC + 4, (int)dword_800141CC,
                                                     (int)aCdlgetlocl,        (int)aCdlgetlocp,
                                                     (int)dword_800141CC,     (int)aCdlgettn,
                                                     (int)aCdlgettd,          (int)aCdlseekl,
                                                     (int)aCdlseekp,          (int)dword_800141CC,
                                                     (int)dword_800141CC,     (int)dword_800141CC,
                                                     (int)dword_800141CC,     (int)aCdlreads,
                                                     (int)dword_800141CC,     (int)dword_800141CC,
                                                     (int)dword_800141CC,     (int)dword_800141CC};
int         SECTION(".data") CD_intstr_800A3F0C[] = {(int)aNointr,        (int)aDataready,    (int)aComplete_0,
                                                     (int)aAcknowledge,   (int)aDataend,      (int)aDiskerror_0,
                                                     (int)dword_800141CC, (int)dword_800141CC};
int         SECTION(".data") dword_800A3F2C[] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
                                                 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0};
int         SECTION(".data") dword_800A3FAC[] = {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0};
int         SECTION(".data") dword_800A402C[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                                 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int  SECTION(".data") dword_800A40AC[] = {0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0};
int  SECTION(".data") dword_800A4110[] = {0, 0, 0, 0, 0, 0, 0};
int  SECTION(".data") dword_800A412C = 0x1F801800;
int  SECTION(".data") dword_800A4130 = 0x1F801801;
int  SECTION(".data") dword_800A4134 = 0x1F801802;
int  SECTION(".data") dword_800A4138 = 0x1F801803;
int  SECTION(".data") dword_800A413C = 0x1F801020;
int  SECTION(".data") dword_800A4140 = 0x1F801C00;
char SECTION(".data") byte_800A4144[] = {0, 0, 0, 0};

struct off_800A4148
{
    unsigned char *p1;
    short         *p2;
    unsigned char *p3;
    int           *p4;
    unsigned char *p5;
    const char    *p6;
};
struct off_800A4148 SECTION(".data") goff_800A4148 = {
    (unsigned char *)&byte_800A4144,      (short *)0x800C14F8,
    (unsigned char *)&CD_com_800A3E84[1], (int *)&CD_status_800A3E74,
    (unsigned char *)&CD_pos_800A3E80,    (const char *)aIdBiosCV186199};
int SECTION(".data") dword_800A4160 = 0x1F801018;
int SECTION(".data") dword_800A4164 = 0x1F8010F0;
int SECTION(".data") dword_800A4168 = 0x1F8010B0;
int SECTION(".data") dword_800A416C = 0x1F8010B4;
int SECTION(".data") dword_800A4170[] = {0x1F8010B8, 0, 0, 0};
