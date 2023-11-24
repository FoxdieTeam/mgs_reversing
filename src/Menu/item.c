#include "Bullet/blast.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "libdg/libdg.h"
#include "menuman.h"
#include "radio.h"
#include "linker.h"
#include "psyq.h"

extern PANEL_TEXTURE gMenuLeftItems_800BD5A0[];
extern short         GM_WeaponTypes_8009D580[];
extern short         GM_ItemTypes_8009D598[];
extern int           GM_GameStatus_800AB3CC;
extern int           GM_PlayerStatus_800ABA50;
extern int           GV_PauseLevel_800AB928;
extern int           GM_DisableItem_800ABA28;
extern int           DG_UnDrawFrameCount_800AB380;
extern int           dword_8009F46C;
extern int           GV_Time_800AB330;
extern int           GM_GameOverTimer_800AB3D4;
extern int           GM_PlayerMap_800ABA0C;
extern MATRIX        DG_ZeroMatrix_8009D430;
extern SVECTOR       GM_PlayerPosition_800ABA10;

extern int dword_800ABAD0;
int        SECTION(".sbss") dword_800ABAD0;

// Also see dword_8009E5CC.
// Those strings are passed to font_draw_string_80045D0C().
char *SECTION(".data") itm_descriptions_8009E3E4[] = {
    /* IT_Cigs */
    (char[]){0xB0, 0x14, 0x90, 0xB0, 0x90, 0xB1, 0xD0, 0x15, 0x80, 0x7C, 0x82, 0x1D, 0x82, 0x4A, 0xC2,
             0x23, 0x82, 0x29, 0xC0, 0x7F, 0x82, 0x19, 0x82, 0x2D, 0xD0, 0x06, 0x82, 0x0F, 0x90, 0x1F,
             0x90, 0x49, 0x81, 0x2E, 0x90, 0xB0, 0x90, 0xB1, 0xD0, 0x03, 0x90, 0xB2, 0x81, 0x04, 0x90,
             0xB3, 0x81, 0x0E, 0x81, 0x2B, 0x81, 0x2F, 0x90, 0xB4, 0x90, 0xB5, 0x81, 0x17, 0x81, 0x3E,
             0x81, 0x17, 0xC1, 0x47, 0x81, 0x06, 0xD0, 0x03, 0x00, 0x00, 0x00, 0x00},
    /* IT_Scope */
    (char[]){0xB0, 0x14, 0x90, 0x21, 0x90, 0x22, 0x90, 0x23, 0xD0, 0x15, 0x80, 0x7C, 0x90, 0xB6, 0x90, 0x63,
             0x90, 0xB7, 0x90, 0xB8, 0x90, 0x21, 0x90, 0x22, 0x90, 0x23, 0xD0, 0x03, 0x90, 0x24, 0x81, 0x27,
             0x82, 0x1A, 0xD0, 0x06, 0x82, 0x40, 0x82, 0x04, 0x82, 0x53, 0xD0, 0x02, 0x90, 0x18, 0x81, 0x27,
             0x82, 0x1A, 0xD0, 0x06, 0x82, 0x40, 0x82, 0x02, 0x82, 0x06, 0x82, 0x28, 0xD0, 0x03, 0x00, 0x00},
    /* IT_Box1 */
    (char[]){0xB0, 0x14, 0x82, 0x20, 0x82, 0x53, 0x82, 0x3C, 0xD0, 0x06, 0x82, 0x4B, 0x90, 0xB9, 0x41, 0xD0, 0x15, 0x80,
             0x7C, 0xB0, 0x0B, 0x82, 0x38, 0x82, 0x4A, 0x82, 0x3D, 0xD0, 0x06, 0x82, 0x28, 0x90, 0x26, 0xD0, 0x0C, 0x81,
             0x28, 0x90, 0x27, 0x81, 0x0B, 0x81, 0x4C, 0x81, 0x26, 0x81, 0x04, 0x81, 0x4B, 0xD0, 0x03, 0x00},
    /* IT_Box2 */
    (char[]){0xB0, 0x14, 0x82, 0x20, 0x82, 0x53, 0x82, 0x3C, 0xD0, 0x06, 0x82, 0x4B, 0x90, 0xB9, 0x42, 0xD0, 0x15, 0x80,
             0x7C, 0xB0, 0x0B, 0x90, 0x2A, 0x90, 0x85, 0x90, 0xBA, 0x90, 0x2B, 0x90, 0x2C, 0x90, 0xBB, 0x90, 0x26, 0xD0,
             0x0C, 0x81, 0x28, 0x90, 0x27, 0x81, 0x04, 0x81, 0x26, 0x81, 0x02, 0x81, 0x4B, 0xD0, 0x03, 0x00},
    /* IT_Box3 */
    (char[]){0xB0, 0x14, 0x82, 0x20, 0x82, 0x53, 0x82, 0x3C, 0xD0, 0x06, 0x82, 0x4B, 0x90, 0xB9, 0x43,
             0xD0, 0x15, 0x80, 0x7C, 0xB0, 0x0B, 0x90, 0x2F, 0x90, 0x30, 0x90, 0x26, 0xD0, 0x0C, 0x81,
             0x28, 0x90, 0x27, 0x81, 0x04, 0x81, 0x26, 0x81, 0x02, 0x81, 0x4B, 0xD0, 0x03, 0x00},
    /* IT_NVG */
    (char[]){0xB0, 0x14, 0x90, 0x31, 0x90, 0x32, 0x82, 0x14, 0xD0, 0x06, 0x82, 0x10, 0x82, 0x4B, 0xD0, 0x15, 0x80,
             0x7C, 0x90, 0x4A, 0x81, 0x52, 0x90, 0xA6, 0x90, 0xA7, 0x90, 0xBC, 0x81, 0x2B, 0x90, 0xBD, 0x90, 0xBE,
             0x81, 0x17, 0x81, 0x26, 0x90, 0xBF, 0x90, 0xC0, 0x90, 0x64, 0x81, 0x19, 0x81, 0x4B, 0x90, 0x31, 0x90,
             0x32, 0x90, 0xC1, 0x90, 0xC2, 0xD0, 0x03, 0x90, 0x31, 0x81, 0x04, 0x90, 0xC3, 0x90, 0xC4, 0x81, 0x27,
             0x81, 0x42, 0x90, 0x32, 0x90, 0xA4, 0x81, 0x52, 0x90, 0xC5, 0x90, 0x2B, 0x81, 0x19, 0x81, 0x4B, 0x90,
             0xC6, 0x81, 0x0C, 0x81, 0x27, 0x81, 0x0D, 0x81, 0x4B, 0xD0, 0x03, 0x00, 0x00, 0x00, 0x00},
    /* IT_ThermG */
    (char[]){0xB0, 0x14, 0x82, 0x15, 0xD0, 0x06, 0x82, 0x3E, 0x82, 0x4B, 0xC0, 0x7F, 0x82, 0x14, 0xD0, 0x06,
             0x82, 0x10, 0x82, 0x4B, 0xD0, 0x15, 0x80, 0x7C, 0x90, 0xC7, 0x90, 0xC8, 0x81, 0x2E, 0x90, 0x38,
             0x90, 0xC9, 0x81, 0x52, 0x90, 0xBF, 0x90, 0xC0, 0x90, 0x64, 0x81, 0x19, 0x81, 0x4B, 0x90, 0x31,
             0x90, 0x32, 0x90, 0xC1, 0x90, 0xC2, 0xD0, 0x03, 0x90, 0x31, 0x81, 0x04, 0x90, 0xC3, 0x90, 0xC4,
             0x81, 0x27, 0x81, 0x42, 0x90, 0x32, 0x90, 0xA4, 0x81, 0x52, 0x90, 0xC5, 0x90, 0x2B, 0x81, 0x19,
             0x81, 0x4B, 0x90, 0xC6, 0x81, 0x0C, 0x81, 0x27, 0x81, 0x0D, 0x81, 0x4B, 0xD0, 0x03, 0x00, 0x00},
    /* IT_GasMask */
    (char[]){0xB0, 0x14, 0x82, 0x0C, 0x82, 0x19, 0x82, 0x3E, 0x82, 0x19, 0x82, 0x0F, 0xD0, 0x15, 0x80, 0x7C, 0x90,
             0x91, 0x90, 0xCA, 0x90, 0x3A, 0x90, 0x64, 0x90, 0x4B, 0x90, 0xCB, 0x90, 0xC1, 0x90, 0xCC, 0x90, 0x49,
             0x82, 0x0C, 0x82, 0x19, 0x82, 0x3E, 0x82, 0x19, 0x82, 0x0F, 0xD0, 0x03, 0x90, 0x3F, 0x82, 0x0C, 0x82,
             0x19, 0x81, 0x2E, 0x90, 0xCD, 0x81, 0x27, 0x80, 0x4F, 0x80, 0x32, 0x82, 0x12, 0xD0, 0x06, 0x82, 0x18,
             0x81, 0x0C, 0x90, 0x43, 0x90, 0xCE, 0x81, 0x19, 0x81, 0x4B, 0x82, 0x19, 0x82, 0x34, 0xD0, 0x06, 0x82,
             0x29, 0x81, 0x0C, 0x90, 0xCF, 0x81, 0x0F, 0x81, 0x2A, 0x81, 0x4B, 0xD0, 0x03, 0x00, 0x00},
    /* IT_BodyArmor */
    (char[]){0xB0, 0x14, 0x82, 0x3C, 0x82, 0x27, 0xC2, 0x03, 0xD0, 0x06, 0x82, 0x02, 0xD0, 0x06, 0x82, 0x3E, 0xD0, 0x06,
             0xD0, 0x15, 0x80, 0x7C, 0x90, 0xFE, 0x90, 0xFF, 0x90, 0xD0, 0x90, 0xD1, 0x81, 0x52, 0x90, 0x48, 0x90, 0x49,
             0x81, 0x17, 0x81, 0x1F, 0x90, 0xD2, 0x90, 0x85, 0x82, 0x39, 0x82, 0x19, 0x82, 0x28, 0xD0, 0x03, 0x82, 0x20,
             0x82, 0x41, 0xD0, 0x06, 0x82, 0x18, 0x81, 0x52, 0x90, 0x42, 0x90, 0x43, 0x81, 0x15, 0x81, 0x1B, 0x81, 0x4B,
             0x90, 0xC6, 0x81, 0x0C, 0x81, 0x27, 0x81, 0x0D, 0x81, 0x4B, 0xD0, 0x03, 0x00, 0x00, 0x00, 0x00},
    /* IT_Ketchup */
    (char[]){0xB0, 0x14, 0x82, 0x11, 0x82, 0x21, 0xC2, 0x43, 0xC2, 0x23, 0x82, 0x37, 0xD0, 0x15, 0x80,
             0x7C, 0x90, 0x44, 0x90, 0x45, 0x90, 0x46, 0xD0, 0x03, 0x82, 0x04, 0x82, 0x1F, 0x82, 0x4A,
             0x82, 0x02, 0x90, 0x47, 0x82, 0x28, 0x82, 0x3E, 0x82, 0x28, 0x90, 0x48, 0x90, 0x49, 0xD0,
             0x03, 0x80, 0x23, 0x90, 0x24, 0x82, 0x3C, 0x82, 0x1F, 0x82, 0x53, 0x81, 0x27, 0x90, 0x48,
             0x90, 0x49, 0x90, 0xB6, 0x91, 0x0F, 0xD0, 0x03, 0x00, 0x00, 0x00, 0x00},
    /* IT_Stealth */
    (char[]){0xB0, 0x14, 0x82, 0x19, 0x82, 0x26, 0x82, 0x4B, 0x82, 0x19, 0x90, 0x4C, 0x90, 0x4D, 0xD0, 0x15,
             0x80, 0x7C, 0x82, 0x0A, 0x82, 0x1F, 0x82, 0x13, 0x82, 0x53, 0x81, 0x0C, 0x90, 0x54, 0x90, 0x7E,
             0x81, 0x17, 0x81, 0x1F, 0xD0, 0x02, 0x90, 0x4A, 0x81, 0x52, 0x90, 0xD3, 0x90, 0xD4, 0x81, 0x15,
             0x81, 0x1B, 0x81, 0x26, 0x90, 0x93, 0x90, 0x94, 0x81, 0x17, 0x81, 0x1F, 0x90, 0xD5, 0x81, 0x52,
             0x90, 0xD6, 0x90, 0x68, 0x90, 0x64, 0x81, 0x19, 0x81, 0x4B, 0x90, 0x4C, 0x90, 0x4D, 0x82, 0x17,
             0x82, 0x19, 0x82, 0x26, 0x82, 0x40, 0xD0, 0x03, 0x00, 0x00, 0x00, 0x00},
    /* IT_Bandana */
    (char[]){0xB0, 0x14, 0x82, 0x40, 0x82, 0x12, 0x82, 0x53, 0x82, 0x30, 0x82, 0x53, 0x82, 0x20, 0x82, 0x2A, 0xD0, 0x15,
             0x80, 0x7C, 0x82, 0x41, 0x82, 0x4A, 0x82, 0x4B, 0x81, 0x0C, 0x90, 0x34, 0x81, 0x24, 0x81, 0x11, 0x81, 0x1F,
             0x82, 0x30, 0x82, 0x53, 0x82, 0x20, 0x82, 0x2A, 0xD0, 0x03, 0x80, 0x7C, 0xB0, 0x0B, 0x82, 0x40, 0x82, 0x12,
             0x82, 0x53, 0xD0, 0x0C, 0x81, 0x28, 0x81, 0x04, 0x81, 0x06, 0x90, 0x8E, 0x81, 0x0C, 0x81, 0x2C, 0x81, 0x04,
             0x81, 0x13, 0x81, 0x3E, 0x81, 0x4C, 0x81, 0x26, 0x81, 0x04, 0x81, 0x4B, 0xD0, 0x03, 0x00, 0x00},
    /* IT_Camera */
    (char[]){0xB0, 0x14, 0x82, 0x0B, 0x82, 0x41, 0x82, 0x49, 0xD0, 0x15, 0x80, 0x7C, 0x81, 0x04, 0x81, 0x4D, 0x81, 0x04,
             0x81, 0x4D, 0x81, 0x2A, 0x81, 0x28, 0x81, 0x13, 0x81, 0x4D, 0x81, 0x52, 0x90, 0x4F, 0x90, 0x50, 0x81, 0x27,
             0x81, 0x0D, 0x81, 0x4B, 0xD0, 0x03, 0x90, 0x24, 0x81, 0x27, 0x82, 0x1A, 0xD0, 0x06, 0x82, 0x40, 0x82, 0x04,
             0x82, 0x53, 0xD0, 0x02, 0x90, 0x18, 0x81, 0x27, 0x82, 0x1A, 0xD0, 0x06, 0x82, 0x40, 0x82, 0x02, 0x82, 0x06,
             0x82, 0x28, 0xD0, 0x03, 0x90, 0x1D, 0x81, 0x27, 0x90, 0x4F, 0x90, 0x50, 0xD0, 0x03, 0x00, 0x00},
    /* IT_Ration */
    (char[]){0xB0, 0x14, 0x82, 0x4C, 0xD0, 0x06, 0x82, 0x17, 0xC2, 0x47, 0x82, 0x53, 0xD0, 0x15, 0x80, 0x7C, 0x90,
             0xD7, 0x90, 0x49, 0x90, 0xD8, 0x90, 0xD9, 0x90, 0xDA, 0x90, 0xDB, 0xD0, 0x03, 0x80, 0x4C, 0x80, 0x49,
             0x80, 0x46, 0x80, 0x45, 0x81, 0x52, 0x90, 0x52, 0x90, 0x53, 0x81, 0x19, 0x81, 0x4B, 0xD0, 0x03, 0x82,
             0x41, 0x82, 0x2B, 0xC2, 0x45, 0xD0, 0x06, 0x81, 0x52, 0x90, 0x54, 0x81, 0x04, 0x81, 0x26, 0x81, 0x04,
             0x81, 0x4B, 0x90, 0xDC, 0x81, 0x2B, 0x90, 0x1B, 0x82, 0x3C, 0x82, 0x1F, 0x82, 0x53, 0x81, 0x52, 0x90,
             0x7B, 0x81, 0x17, 0x81, 0x26, 0x90, 0x48, 0x90, 0x49, 0xD0, 0x03, 0x90, 0x93, 0x90, 0x94, 0x81, 0x27,
             0x91, 0x0C, 0x90, 0x98, 0x90, 0x48, 0x90, 0x49, 0xD0, 0x03, 0x00, 0x00, 0x00, 0x00},
    /* IT_ColdMedicine */
    (char[]){0xB0, 0x14, 0x90, 0x55, 0x90, 0x56, 0x90, 0x57, 0xD0, 0x15, 0x80, 0x7C, 0x90, 0xDD, 0x90, 0xDE,
             0x90, 0xDF, 0x90, 0xE0, 0x90, 0x57, 0xD0, 0x03, 0x90, 0x55, 0x90, 0x56, 0x81, 0x52, 0x90, 0xE1,
             0x81, 0x19, 0x90, 0xC6, 0x81, 0x0C, 0x81, 0x27, 0x81, 0x0D, 0x81, 0x4B, 0xD0, 0x03, 0x82, 0x41,
             0x82, 0x2B, 0xC2, 0x45, 0xD0, 0x06, 0x81, 0x52, 0x90, 0x54, 0x81, 0x04, 0x81, 0x26, 0x81, 0x04,
             0x81, 0x4B, 0x90, 0xDC, 0x81, 0x2B, 0x90, 0x1B, 0x82, 0x3C, 0x82, 0x1F, 0x82, 0x53, 0x81, 0x52,
             0x90, 0x7B, 0x81, 0x17, 0x81, 0x26, 0x90, 0xE2, 0x90, 0x49, 0xD0, 0x03, 0x00, 0x00, 0x00, 0x00},
    /* IT_Diazepam */
    (char[]){0xB0, 0x14, 0x82, 0x18, 0x82, 0x02, 0x82, 0x1C, 0x82, 0x31, 0x82, 0x40, 0xD0, 0x15, 0x80, 0x7C, 0x90, 0x59,
             0x90, 0x5A, 0x90, 0x5B, 0x90, 0x5C, 0x90, 0x5D, 0xD0, 0x03, 0x90, 0x5E, 0x81, 0x2E, 0x81, 0x35, 0x81, 0x4B,
             0x81, 0x08, 0x81, 0x52, 0x90, 0xE3, 0x90, 0x5C, 0x90, 0xDC, 0x90, 0xE4, 0x90, 0x58, 0x81, 0x41, 0x81, 0x4B,
             0xD0, 0x03, 0x82, 0x41, 0x82, 0x2B, 0xC2, 0x45, 0xD0, 0x06, 0x81, 0x52, 0x90, 0x54, 0x81, 0x04, 0x81, 0x26,
             0x81, 0x04, 0x81, 0x4B, 0x90, 0xDC, 0x81, 0x2B, 0x90, 0x1B, 0x82, 0x3C, 0x82, 0x1F, 0x82, 0x53, 0x81, 0x52,
             0x90, 0x7B, 0x81, 0x17, 0x81, 0x26, 0x90, 0xE2, 0x90, 0x49, 0xD0, 0x03, 0x00, 0x00},
    /* IT_PalKey */
    (char[]){0xB0, 0x14, 0x50, 0x41, 0x4C, 0x82, 0x0B, 0xD0, 0x06, 0x82, 0x29, 0xD0, 0x15, 0x80, 0x7C,
             0x90, 0xE5, 0x90, 0xA2, 0x82, 0x13, 0xD0, 0x06, 0x82, 0x29, 0x90, 0xE6, 0x90, 0xE7, 0x90,
             0xAC, 0x90, 0x51, 0x90, 0x16, 0x90, 0xE8, 0x90, 0xE9, 0x90, 0x49, 0x81, 0x2E, 0x82, 0x0B,
             0xD0, 0x06, 0x82, 0x29, 0xC0, 0x7F, 0x82, 0x0D, 0xD0, 0x06, 0xD0, 0x03, 0x00, 0x00, 0x00},
    /* IT_Card */
    (char[]){0xB0, 0x14, 0x49, 0x44, 0x82, 0x0B, 0xD0, 0x06, 0x82, 0x29, 0xD0, 0x15, 0x80, 0x7C, 0x90, 0x93,
             0x90, 0x94, 0x81, 0x19, 0x81, 0x4B, 0x81, 0x28, 0x82, 0x1B, 0x82, 0x0D, 0xC2, 0x45, 0x82, 0x4A,
             0x82, 0x26, 0xC2, 0x03, 0xC0, 0x7F, 0x82, 0x4C, 0x82, 0x39, 0x82, 0x4B, 0x81, 0x0C, 0x31, 0x81,
             0x3E, 0x81, 0x27, 0x81, 0x2E, 0x90, 0xEA, 0x81, 0x52, 0x90, 0x54, 0x81, 0x11, 0x81, 0x4B, 0x90,
             0xC6, 0x81, 0x0C, 0x81, 0x27, 0x81, 0x0D, 0x81, 0x4B, 0xD0, 0x03, 0x00},
    /* IT_TimerBomb */
    (char[]){0xB0, 0x14, 0xC0, 0x3F, 0xD0, 0x15, 0x80, 0x7C, 0x90, 0x01, 0x90, 0x67, 0x90, 0x68, 0xD0, 0x03, 0x82,
             0x41, 0x82, 0x2B, 0xC2, 0x45, 0xD0, 0x06, 0x81, 0x52, 0x90, 0x54, 0x81, 0x04, 0x81, 0x26, 0x81, 0x04,
             0x81, 0x4B, 0x81, 0x28, 0x81, 0x0D, 0x81, 0x2B, 0x90, 0x24, 0x81, 0x27, 0x90, 0x69, 0x81, 0x26, 0x81,
             0x4B, 0x81, 0x13, 0x81, 0x28, 0x81, 0x0C, 0x81, 0x27, 0x81, 0x0D, 0x81, 0x4B, 0xD0, 0x03, 0x00, 0x00},
    /* IT_MineDetector */
    (char[]){0xB0, 0x14, 0x90, 0x6A, 0x90, 0x6B, 0x90, 0x6C, 0x90, 0x6D, 0x90, 0x6E, 0xD0, 0x15, 0x80, 0x7C,
             0x90, 0x93, 0x90, 0x94, 0x81, 0x19, 0x81, 0x4B, 0x81, 0x28, 0xD0, 0x02, 0x90, 0xEB, 0x90, 0x9D,
             0x81, 0x15, 0x81, 0x4C, 0x81, 0x1F, 0x90, 0x6A, 0x90, 0x6B, 0x81, 0x2E, 0x90, 0xEC, 0x90, 0x9E,
             0x81, 0x0C, 0x82, 0x4C, 0xD0, 0x06, 0x82, 0x20, 0xD0, 0x06, 0x81, 0x2B, 0x90, 0xED, 0x90, 0xEE,
             0x81, 0x15, 0x81, 0x4C, 0x81, 0x4B, 0xD0, 0x03, 0x00, 0x00, 0x00, 0x00},
    /* IT_Disk */
    (char[]){0xB0, 0x14, 0x90, 0x4A, 0x82, 0x27, 0xC2, 0x03, 0x82, 0x19, 0x82, 0x0F, 0xD0, 0x15, 0x80, 0x7C,
             0x82, 0x41, 0x82, 0x1F, 0x82, 0x4B, 0x82, 0x0E, 0x82, 0x02, 0x81, 0x2E, 0x90, 0x70, 0x90, 0x71,
             0x82, 0x27, 0xD0, 0x06, 0x82, 0x1F, 0x81, 0x0C, 0x90, 0x72, 0x81, 0x41, 0x81, 0x49, 0x81, 0x4C,
             0x81, 0x26, 0x81, 0x04, 0x81, 0x4B, 0x81, 0x28, 0x81, 0x04, 0x81, 0x06, 0x90, 0x4A, 0x82, 0x27,
             0xC2, 0x03, 0x82, 0x19, 0x82, 0x0F, 0xD0, 0x03, 0x00, 0x00, 0x00, 0x00},
    /* IT_Rope */
    (char[]){0xB0, 0x14, 0x82, 0x4D, 0xD0, 0x06, 0x82, 0x37, 0xD0, 0x15, 0x80, 0x7C, 0x90, 0x73, 0x81, 0x0F, 0x81, 0x26,
             0x90, 0x74, 0x90, 0x75, 0x81, 0x2A, 0x82, 0x4D, 0xD0, 0x06, 0x82, 0x37, 0xD0, 0x03, 0x82, 0x2A, 0x82, 0x04,
             0x82, 0x4D, 0x82, 0x53, 0x90, 0xD0, 0x90, 0xD1, 0x90, 0xEF, 0xD0, 0x03, 0x00, 0x00, 0x00, 0x00},
    /* IT_Handkerchief */
    (char[]){0xB0, 0x14, 0x82, 0x2F, 0x82, 0x53, 0x82, 0x0B, 0x82, 0x21, 0xD0, 0x15, 0x80, 0x7C, 0x82,
             0x19, 0x82, 0x2A, 0x82, 0x04, 0x82, 0x31, 0xD0, 0x06, 0xC0, 0x7F, 0x82, 0x06, 0x82, 0x4B,
             0x82, 0x35, 0x81, 0x2E, 0x82, 0x2F, 0x82, 0x53, 0x82, 0x0B, 0x82, 0x21, 0xD0, 0x03, 0x81,
             0x0B, 0x81, 0x19, 0x81, 0x0B, 0x81, 0x2B, 0x90, 0xF0, 0x90, 0xF1, 0x81, 0x2E, 0x90, 0x78,
             0x81, 0x04, 0x81, 0x0C, 0x81, 0x19, 0x81, 0x4B, 0xD0, 0x03, 0x00, 0x00},
    /* IT_Suppressor */
    (char[]){0xB0, 0x14, 0x82, 0x15, 0x82, 0x37, 0x82, 0x4C, 0xC2, 0x23, 0x82, 0x15, 0xD0, 0x06, 0xD0, 0x15,
             0x80, 0x7C, 0x82, 0x1D, 0xD0, 0x06, 0x82, 0x13, 0x82, 0x40, 0x82, 0x34, 0x82, 0x19, 0x82, 0x28,
             0x82, 0x4B, 0x90, 0xF2, 0x90, 0x49, 0x81, 0x2E, 0x82, 0x15, 0x82, 0x37, 0x82, 0x4C, 0xC2, 0x23,
             0x82, 0x15, 0xD0, 0x06, 0xD0, 0x03, 0x82, 0x1D, 0xD0, 0x06, 0x82, 0x13, 0x82, 0x40, 0x82, 0x34,
             0x82, 0x19, 0x82, 0x28, 0x82, 0x4B, 0x81, 0x2E, 0x90, 0x7E, 0x90, 0x8C, 0x90, 0xF3, 0x81, 0x52,
             0x90, 0xF4, 0x81, 0x08, 0x81, 0x4B, 0xD0, 0x03, 0x00, 0x00, 0x00, 0x00},
};

char *SECTION(".data") dword_8009E444[] = {
    (char[]){0xB0, 0x14, 0x82, 0x4C, 0xD0, 0x06, 0x82, 0x17, 0xC2, 0x47, 0x82, 0x53, 0xD0, 0x15, 0x80, 0x7C,
             0x90, 0x79, 0x81, 0x4A, 0x81, 0x24, 0x81, 0x04, 0x81, 0x26, 0x81, 0x04, 0x81, 0x26, 0xD0, 0x02,
             0x90, 0x48, 0x90, 0x49, 0x81, 0x27, 0x81, 0x0D, 0x81, 0x2A, 0x81, 0x04, 0xD0, 0x03, 0x00, 0x00},
    (char[]){0xB0, 0x14, 0x82, 0x11, 0x82, 0x21, 0xC2, 0x43, 0xC2, 0x23, 0x82, 0x37, 0xD0, 0x15, 0x80, 0x7C,
             0x90, 0x79, 0x81, 0x4A, 0x81, 0x24, 0x81, 0x04, 0x81, 0x26, 0x81, 0x04, 0x81, 0x26, 0xD0, 0x02,
             0x90, 0x48, 0x90, 0x49, 0x81, 0x27, 0x81, 0x0D, 0x81, 0x2A, 0x81, 0x04, 0xD0, 0x03, 0x00, 0x00},
};

// TODO: This (whole?) buffer is very likely a EUC-JP/SHIFT-JIS string.
// It starts with SHIFT-JIS: "ｰ針震人仁刃ﾐ" and then EUC-JP: "|HARD, EXTREM B"
char SECTION(".data") dword_8009E44C[] = {
    0xB0, 0x14, 0x90, 0x6A, 0x90, 0x6B, 0x90, 0x6C, 0x90, 0x6D, 0x90, 0x6E, 0xD0, 0x15, 0x80, 0x7C, 0x48, 0x41, 0x52,
    0x44, 0x2C, 0x20, 0x45, 0x58, 0x54, 0x52, 0x45, 0x4D, 0x20, 0x82, 0x42, 0xD0, 0x06, 0x82, 0x29, 0x81, 0x27, 0x81,
    0x2F, 0x90, 0x48, 0x90, 0x49, 0x81, 0x27, 0x81, 0x0D, 0x81, 0x2A, 0x81, 0x04, 0xD0, 0x03, 0x00, 0x00, 0x00};

menu_weapon_rpk_info SECTION(".data") gMenuItemRpkInfo_8009E484[] = {
    {"CIGS", 14},    {"SCOPE", 30},   {"C.BOX A", 17},  {"C.BOX B", 17},  {"C.BOX C", 17}, {"N.V.G", 15},
    {"THERM.G", 16}, {"GASMASK", 19}, {"B.ARMOR", 18},  {"KETCHUP", 25},  {"STEALTH", 32}, {"BANDANA", 31},
    {"CAMERA", 12},  {"RATION", 22},  {"MEDICINE", 21}, {"DIAZEPAM", 21}, {"PAL KEY", 23}, {"CARD", 27},
    {"TIMER.B", 26}, {"MINE.D", 20},  {"DISC", 28},     {"ROPE", 24},     {"SCARF", 29},   {"SUPPR.", 13}};

void sub_8003CEF8(PANEL_TEXTURE *a1);
int  menu_number_draw_number2_80042FC0(Actor_MenuMan *work, int xpos, int ypos, int current, int total);
void menu_init_sprt_8003D0D0(SPRT *pPrim, PANEL_TEXTURE *pUnk, int offset_x, int offset_y);
int  menu_number_draw_string_800430F0(Actor_MenuMan *work, unsigned int *pOt, int xpos, int ypos, const char *str,
                                      int flags);
void menu_sub_menu_update_8003DA0C(Actor_MenuMan *work, unsigned int *pOt, Menu_Inventory *pSubMenu);
void Menu_item_render_frame_rects_8003DBAC(MenuPrim *pGlue, int x, int y, int param_4);
int  menu_8003D538(void);
void menu_8003D7DC(Actor_MenuMan *work, unsigned int *pOt, Menu_Inventory *pSubMenu);
int  sub_8003D568(void);

void menu_sub_8003B568(void)
{
    int    imgIdx;
    u_long palIdx;
    int    i;

    for (i = 0; i < MENU_ITEM_COUNT; i++)
    {
        imgIdx = 0xc + i;
        palIdx = 0x2e;
        if (imgIdx != 0x16)
        {
            palIdx = 0;
            if (imgIdx == 0x1b)
            {
                palIdx = 0x2f;
            }
        }
        menu_init_rpk_item_8003DDCC(&gMenuLeftItems_800BD5A0[i], imgIdx, palIdx);
    }
}

PANEL_TEXTURE *menu_rpk_8003B5E0(int index)
{
    return &gMenuLeftItems_800BD5A0[gMenuItemRpkInfo_8009E484[index].field_4_rpk_idx - 12];
}

void menu_8003B614(int index)
{
    char *ptr = itm_descriptions_8009E3E4[index];

    if (GM_FrozenItemsState == 1)
    {
        if (index != ITEM_KETCHUP)
        {
            if (index == ITEM_RATION)
            {
                ptr = dword_8009E444[0];
            }
        }
        else
        {
            ptr = dword_8009E444[1];
        }
    }

    if (index == ITEM_CARD)
    {
        ptr[46] = GM_CardFlag + 48;
    }

    if (index == ITEM_MINE_D && GM_DifficultyFlag >= DIFFICULTY_HARD)
    {
        ptr = (char *)dword_8009E44C;
    }

    sub_8003F97C(ptr);
}

int menu_item_IsItemDisabled_8003B6D0(int item)
{
    int bit;

    if ((GM_WeaponTypes_8009D580[GM_CurrentWeaponId + 1] & 0x200) && (GM_ItemTypes_8009D598[item + 1] & 1))
    {
        return 1;
    }

    if (GM_PlayerStatus_800ABA50 & (PLAYER_GROUND | PLAYER_FIRST_PERSON_DUCT))
    {
        if ((item == ITEM_C_BOX_A) || (item == ITEM_C_BOX_B) || (item == ITEM_C_BOX_C))
        {
            return 1;
        }
    }

    if (dword_8009F46C != 0)
    {
        if ((item == ITEM_SCOPE) || (item == ITEM_C_BOX_A) || (item == ITEM_C_BOX_B) || (item == ITEM_C_BOX_C) ||
            (item == ITEM_CAMERA))
        {
            return 1;
        }
    }

    bit = 1 << item;
    return (GM_DisableItem_800ABA28 & bit) != 0;
}

void menu_8003B794(Actor_MenuMan *work, unsigned int *pOt, int id)
{
    RECT           pal_rect;
    RECT           img_rect;
    Menu_rpk_item *pPalItem;
    Menu_rpk_item *pImgItem;
    SPRT          *pSprt;

    pPalItem = menu_rpk_get_pal_8003DD9C(id * 2 + 33);
    pImgItem = menu_rpk_get_img_8003DDB4(id * 2 + 34);

    pal_rect.x = 960;
    pal_rect.y = 336;
    pal_rect.w = 16;
    pal_rect.h = 1;
    LoadImage(&pal_rect, pPalItem->field_4_pixel_ptr);

    img_rect.x = 960;
    img_rect.y = 337;
    img_rect.w = pImgItem->field_2_w;
    img_rect.h = pImgItem->field_3_h;
    LoadImage(&img_rect, pImgItem->field_4_pixel_ptr);

    NEW_PRIM(pSprt, work);

    pSprt->v0 = 81;
    pSprt->x0 = 230;
    pSprt->u0 = 0;
    pSprt->y0 = 116;
    pSprt->w = pImgItem->field_2_w * 4;
    pSprt->h = pImgItem->field_3_h;
    LSTORE(0x80808080, &pSprt->r0);
    pSprt->clut = getClut(pal_rect.x, pal_rect.y);
    setSprt(pSprt);
    addPrim(pOt, pSprt);
}

void menu_item_helper_8003B8F0(Actor_MenuMan *work, unsigned int *pOt, int xpos, int ypos, Menu_Inventory *pMenuSub)
{
    PANEL_TEXTURE *pMenuSprt;       // $s6
    SPRT          *pIconSprt;       // $s0
    int            rgb;             // $s1
    int            bBlueBackground; // $a3
    TextConfig     textConfig;      // [sp+18h] [-10h] BYREF

    if (pMenuSub->field_0_current.field_0_id >= 0)
    {
        pMenuSprt = menu_rpk_8003B5E0(pMenuSub->field_0_current.field_0_id);
        sub_8003CEF8(pMenuSprt);
        if (menu_item_IsItemDisabled_8003B6D0(pMenuSub->field_0_current.field_0_id))
        {
            menu_draw_nouse_800435A4(work->field_20_otBuf, xpos, ypos);
        }
        if (GM_FrozenItemsState == 1)
        {
            if (pMenuSub->field_0_current.field_0_id == ITEM_RATION ||
                pMenuSub->field_0_current.field_0_id == ITEM_KETCHUP)
            {
                menu_draw_frozen_800435C8(work->field_20_otBuf, xpos, ypos);
            }
        }

        if (GM_ItemTypes_8009D598[pMenuSub->field_0_current.field_0_id + 1] & ITEMTYPE_CONSUMABLE)
        {
            menu_number_draw_number2_80042FC0(work, xpos, ypos + 11, pMenuSub->field_0_current.field_2_num,
                                              GM_ItemsMax[pMenuSub->field_0_current.field_0_id]);
        }
        else if (pMenuSub->field_0_current.field_0_id == ITEM_CARD)
        {
            textConfig.xpos = xpos;
            textConfig.ypos = ypos + 14;
            textConfig.flags = 0;
            textConfig.colour = 0x64808080;
            menu_number_draw_string_80042BF4(work->field_20_otBuf, &textConfig, "LV.");
            textConfig.ypos -= 2;
            menu_number_draw_80042988(work->field_20_otBuf, &textConfig, GM_Items[ITEM_CARD]);
        }
        else if (pMenuSub->field_0_current.field_0_id == ITEM_TIMER_B)
        {
            menu_number_draw_80042F78(work, pOt, xpos + 10, ypos + 10, GM_Items[ITEM_TIMER_B], 0);
        }

        if (pMenuSprt->field_C_uvclut)
        {
            NEW_PRIM(pIconSprt, work);

            if (!pMenuSub->field_0_current.field_4_pos)
            {
                rgb = 0x808080;
            }
            else
            {
                rgb = 0x404040;
            }
            menu_init_sprt_8003D0D0(pIconSprt, pMenuSprt, xpos, ypos);
            LSTORE(rgb, &pIconSprt->r0);
            setSprt(pIconSprt);
            addPrim(pOt, pIconSprt);
        }
        menu_number_draw_string_800430F0(
            work, pOt, xpos + 46, ypos + 22,
            gMenuItemRpkInfo_8009E484[pMenuSub->field_0_current.field_0_id].field_0_weapon_name, 1);
    }
    else
    {
        menu_number_draw_string_800430F0(work, pOt, xpos + 46, ypos + 22, "NO ITEM", 1);
    }

    if (!pMenuSub->field_0_current.field_4_pos)
    {
        bBlueBackground = pMenuSub->field_0_current.field_6_current == 0;
    }
    else
    {
        bBlueBackground = 0;
    }

    Menu_item_render_frame_rects_8003DBAC(work->field_20_otBuf, xpos, ypos, bBlueBackground);
}

void menu_8003BBEC(Actor_MenuMan *work)
{
    Menu_Item_Unknown *temp_v0 = work->field_1DC_menu_item.field_C_alloc;
    int                index;
    short             *pLinkVar;

    work->field_1DC_menu_item.field_10_state = 0;

    AssignXYFromVec_8003D1B8(&work->field_1DC_menu_item.field_0_current,
                             &temp_v0->field_20_array[temp_v0->field_0_main.field_4_selected_idx]);

    if (work->field_1DC_menu_item.field_0_current.field_2_num <= 0)
    {
        work->field_1DC_menu_item.field_0_current.field_0_id = ITEM_NONE;
    }

    index = work->field_1DC_menu_item.field_0_current.field_0_id;
    pLinkVar = linkvarbuf;

    if ((index >= 0) && !menu_item_IsItemDisabled_8003B6D0(index))
    {
        pLinkVar[15] = index;
        sub_8003CFE0(menu_rpk_8003B5E0(index), 0);
        work->field_1DC_menu_item.field_11 = pLinkVar[15];
    }
    else
    {
        if (index != ITEM_NONE)
        {
            dword_800ABAD0 = index;
        }

        GM_CurrentItemId = ITEM_NONE;
        work->field_1DC_menu_item.field_0_current.field_0_id = ITEM_NONE;
    }

    work->field_1DC_menu_item.field_12_flashingAnimationFrame = 10;

    menu_panel_free_8003D184(work->field_1DC_menu_item.field_C_alloc);
    menu_font_kill_8003FC0C();

    GM_SeSet2_80032968(0, 63, 20);
}

int dword_800AB574 = 0;
int dword_800AB578 = 0;

int menu_item_update_helper_8003BCD4(Actor_MenuMan *work)
{
    int                activeItems;
    int                i;
    Menu_Item_Unknown *pPanels;
    int                cardVal;
    int                panelIndex;

    if (!(GM_GameStatus_800AB3CC & GAME_FLAG_BIT_19))
    {
        activeItems = 0;

        for (i = 0; i < GM_TotalItems; i++)
        {
            if (GM_Items[i] > 0)
            {
                activeItems++;
            }
        }

        pPanels = menu_alloc_panel_8003D124(activeItems + 1);
        work->field_1DC_menu_item.field_C_alloc = pPanels;

        if (!pPanels)
        {
            return 0;
        }

        if ((GM_CurrentItemId != ITEM_NONE) && (GM_CurrentItemId != ITEM_CARD))
        {
            dword_800ABAD0 = GM_CurrentItemId;
        }
        else if (dword_800ABAD0 < 0)
        {
            dword_800ABAD0 = 0;
        }

        cardVal = -1;

        if (GM_CardFlag > 0)
        {
            cardVal = 0;
        }

        panelIndex = 0;

        for (i = 0; i < GM_TotalItems; i++)
        {
            if (i == dword_800ABAD0)
            {
                AssignXY_8003D1A8(&pPanels->field_20_array[panelIndex], ITEM_NONE, 1);

                panelIndex++;

                if (cardVal == 0)
                {
                    if (GM_CurrentItemId == ITEM_NONE)
                    {
                        AssignXY_8003D1A8(&pPanels->field_20_array[panelIndex], ITEM_CARD, GM_Items[ITEM_CARD]);
                        panelIndex++;
                    }
                    else
                    {
                        cardVal = 1;
                    }
                }
            }

            if ((GM_Items[i] > 0) && (i != ITEM_CARD))
            {
                AssignXY_8003D1A8(&pPanels->field_20_array[panelIndex], i, GM_Items[i]);
                panelIndex++;
            }

            if (cardVal > 0)
            {
                AssignXY_8003D1A8(&pPanels->field_20_array[panelIndex], ITEM_CARD, GM_Items[ITEM_CARD]);
                panelIndex++;
                cardVal = 0;
            }
        }
    }
    else
    {
        pPanels = menu_alloc_panel_8003D124(1);
        work->field_1DC_menu_item.field_C_alloc = pPanels;

        if (!pPanels)
        {
            return 0;
        }

        AssignXY_8003D1A8(&pPanels->field_20_array[0], ITEM_NONE, 1);
    }

    if (!sub_8003F84C(0))
    {
        menu_panel_free_8003D184(pPanels);
        return 0;
    }

    dword_800AB578 = 0;
    dword_800AB574 = 0;
    work->field_1DC_menu_item.field_10_state = 2;

    sub_8003D520();
    sub_8003CE40(gMenuLeftItems_800BD5A0, MENU_ITEM_COUNT);
    menu_panel_8003D2BC(work->field_1DC_menu_item.field_C_alloc, work->field_1DC_menu_item.field_0_current.field_0_id);
    GM_SeSet2_80032968(0, 63, 21);
    return 1;
}

void menu_item_update_helper2_8003BF1C(Actor_MenuMan *work, unsigned int *pOt)
{
    unsigned short     anim_frame;
    int                anim_frame2;
    int                switched_weapon;
    int                last_id;
    Menu_Item_Unknown *pAlloc;
    PANEL             *pPanel;

    switch (work->field_1DC_menu_item.field_10_state)
    {
    case 0:
        anim_frame = work->field_1DC_menu_item.field_12_flashingAnimationFrame & 0xffff;
        anim_frame2 = anim_frame & 0xffff;

        if (anim_frame2 != 0)
        {
            work->field_1DC_menu_item.field_12_flashingAnimationFrame--;

            if ((anim_frame2 & 3) > 1)
            {
                menu_sub_menu_update_8003DA0C(work, pOt, &work->field_1DC_menu_item);

                if (((anim_frame2 & 3) == 3) &&
                    (work->field_1DC_menu_item.field_0_current.field_0_id != GM_CurrentItemId) &&
                    menu_item_IsItemDisabled_8003B6D0(work->field_1DC_menu_item.field_0_current.field_0_id) &&
                    (DG_UnDrawFrameCount_800AB380 == 0))
                {
                    GM_SeSet2_80032968(0, 63, 54);
                    break;
                }
            }
        }
        else
        {
            switched_weapon = 0;
            if (menu_item_IsItemDisabled_8003B6D0(GM_CurrentItemId))
            {
                last_id = GM_CurrentItemId;
                GM_CurrentItemId = ITEM_NONE;
                work->field_1DC_menu_item.field_12_flashingAnimationFrame = 19;
                dword_800ABAD0 = last_id;
                break;
            }

            if (work->field_1DC_menu_item.field_0_current.field_0_id != GM_CurrentItemId)
            {
                switched_weapon = 1;

                if (work->field_1DC_menu_item.field_0_current.field_0_id != ITEM_NONE &&
                    work->field_1DC_menu_item.field_0_current.field_0_id != ITEM_CARD)
                {
                    dword_800ABAD0 = work->field_1DC_menu_item.field_0_current.field_0_id;
                }

                work->field_1DC_menu_item.field_0_current.field_0_id = GM_CurrentItemId;
            }

            if (GM_CurrentItemId >= 0)
            {
                if (switched_weapon != 0)
                {
                    sub_8003CFE0(menu_rpk_8003B5E0(GM_CurrentItemId), 0);
                    work->field_1DC_menu_item.field_11 = GM_CurrentItemId;
                }

                work->field_1DC_menu_item.field_0_current.field_2_num = GM_Items[GM_CurrentItemId];
                menu_sub_menu_update_8003DA0C(work, pOt, &work->field_1DC_menu_item);
            }
        }
        break;

    case 2:
        if (menu_8003D538())
        {
            work->field_1DC_menu_item.field_10_state = 1;
        }

        dword_800AB574 = 0;

    case 1:
        pAlloc = work->field_1DC_menu_item.field_C_alloc;
        pPanel = &pAlloc->field_20_array[pAlloc->field_0_main.field_4_selected_idx];

        if (GM_GameStatus_800AB3CC & GAME_FLAG_BIT_13)
        {
            dword_800AB578 = 0;
            dword_800AB574 = 0;
        }

        if ((pPanel->field_4_pos == 0) && (pPanel->field_0_id >= 0))
        {
            if (dword_800AB578 == 0)
            {
                if (++dword_800AB574 == 4)
                {
                    menu_8003B614(pPanel->field_0_id);
                    dword_800AB578 = 1;
                }
            }
        }
        else
        {
            dword_800AB578 = 0;
            dword_800AB574 = 0;
        }

        if (dword_800AB578 != 0)
        {
            if (pPanel->field_0_id == ITEM_PAL_KEY)
            {
                menu_8003B794(work, pOt, GM_ShapeKeyState);
            }

            menu_8003F9B4(work, pOt, "EQUIP");
        }

        menu_8003D7DC(work, pOt, &work->field_1DC_menu_item);
        break;

    case 3:
        if (sub_8003D568() != 0)
        {
            work->field_2A_state = 0;
            GV_PauseLevel_800AB928 &= ~4;
            menu_8003BBEC(work);
        }
        else
        {
            menu_8003D7DC(work, pOt, &work->field_1DC_menu_item);
        }
        break;
    }
}

void menu_item_update_helper3_8003C24C(Menu_Item_Unknown *pPanels, unsigned short press)
{
    PANEL *pPanel;
    short  heal_amount;
    short  item_amount;

    if (!(press & PAD_CIRCLE))
    {
        return;
    }

    pPanel = &pPanels->field_20_array[pPanels->field_0_main.field_4_selected_idx];

    if (pPanel->field_2_num <= 0)
    {
        return;
    }

    switch (pPanel->field_0_id)
    {
    case ITEM_KETCHUP:
    case ITEM_RATION:
        if (GM_FrozenItemsState != 0)
        {
            GM_SeSet2_80032968(0, 63, 115); // Frozen item ding
            return;
        }

        if (GM_SnakeCurrentHealth == GM_SnakeMaxHealth)
        {
            GM_SeSet2_80032968(0, 63, 35); // "BA BA" denied sound
            return;
        }

        if (pPanel->field_0_id == ITEM_RATION)
        {
            if (GM_DifficultyFlag == DIFFICULTY_VERY_EASY)
            {
                heal_amount = 1024;
            }
            else if (GM_DifficultyFlag == DIFFICULTY_EASY)
            {
                heal_amount = 384;
            }
            else
            {
                heal_amount = 256;
            }
        }
        else
        {
            heal_amount = 64;
            pPanel->field_0_id = ITEM_NONE;
            GM_KetchupFlag = 0;
        }

        GM_SnakeCurrentHealth += heal_amount;
        GM_TotalRationsUsed++;

        if (GM_SnakeCurrentHealth > GM_SnakeMaxHealth)
        {
            GM_SnakeCurrentHealth = GM_SnakeMaxHealth;
        }

        GM_SeSet2_80032968(0, 63, 12); // Ration used sound
        break;

    case ITEM_MEDICINE:
        if (GM_StatusEvent & EV_CommonCold) // Snake has a cold :(
        {
            GM_StatusEvent &= ~EV_CommonCold;
            GM_SnakeColdTimer = 0;
            GM_SnakeColdUnk9A = 0;
        }

        GM_SeSet2_80032968(0, 63, 34); // Medicine used sound
        break;

    case ITEM_DIAZEPAM:
        GM_StatusEvent |= EV_Tranquilizer;

        if (GM_TranquilizerTimer < 0)
        {
            GM_TranquilizerTimer = 0;
        }

        GM_TranquilizerTimer += 1200;

        GM_SeSet2_80032968(0, 63, 34); // Medicine used sound
        break;

    case ITEM_TIMER_B:
        if ((GM_PlayerStatus_800ABA50 & 0x362) || dword_8009F46C || menu_item_IsItemDisabled_8003B6D0(ITEM_TIMER_B))
        {
            GM_SeSet2_80032968(0, 63, 35); // "BA BA" denied sound
        }
        else
        {
            pPanel->field_0_id = ITEM_NONE;
            GM_TimerBombFlag = ITEM_NONE;
            GM_PlayerStatus_800ABA50 |= PLAYER_THROWING;
            GM_SeSet2_80032968(0, 63, 33); // Title screen exit/bomb discard sound
        }
        return;

    default:
        return;
    }

    if (pPanel->field_0_id >= 0)
    {
        item_amount = GM_Items[pPanel->field_0_id];
        pPanel->field_2_num = item_amount - 1;
        GM_Items[pPanel->field_0_id] = item_amount - 1;
    }
}

void menu_item_update_helper4_8003C4EC(void)
{
    Blast_Data blastData;
    MATRIX     mtx;
    int        time;
    int        speed;
    int        speed2;

    if (GV_PauseLevel_800AB928)
    {
        return;
    }

    time = GV_Time_800AB330 % 30;
    switch (time)
    {
    case 0:
        if (GM_RationFlag <= 0)
        {
            break;
        }

        speed = GM_EnvironTemp;
        if (speed == 0)
        {
            speed = 10;
        }

        if (GM_CurrentItemId == ITEM_RATION)
        {
            if (speed > 0)
            {
                speed += GM_BodyTemp;
            }
            else
            {
                speed = GM_BodyTemp;
            }
        }

        GM_FrozenItemsTemp += speed;

        if (GM_FrozenItemsTemp < GM_FrozenItemsTempMin)
        {
            if (GM_FrozenItemsState == 0)
            {
                GM_FrozenItemsState = 1;
            }

            GM_FrozenItemsTemp = GM_FrozenItemsTempMin;
        }

        if (GM_FrozenItemsTemp < 0)
        {
            break;
        }

        if (GM_FrozenItemsState == 1)
        {
            GM_FrozenItemsState = 0;

            if (GM_CurrentItemId == ITEM_RATION || GM_CurrentItemId == ITEM_KETCHUP)
            {
                GM_SeSet2_80032968(0, 63, 119); // Unfreeze sound (also used by Nikita)
            }
        }

        GM_FrozenItemsTemp = 0;
        break;

    case 1:
        if (GM_ShapeKeyFlag <= 0)
        {
            break;
        }

        if (GM_EnvironTemp == 0)
        {
            if (GM_ShapeKeyState == 0)
            {
                GM_ShapeKeyTemp = 0;
                break;
            }

            if (GM_ShapeKeyTemp < 0)
            {
                speed2 = 10;
            }
            else
            {
                speed2 = -10;
            }
        }
        else
        {
            speed2 = GM_EnvironTemp;
        }

        GM_ShapeKeyTemp += speed2;

        if (GM_ShapeKeyTemp > GM_ShapeKeyTempMax)
        {
            GM_ShapeKeyState = 1;
            GM_ShapeKeyTemp = GM_ShapeKeyTempMax;
            break;
        }

        if (GM_ShapeKeyTemp < GM_ShapeKeyTempMin)
        {
            GM_ShapeKeyState = 2;
            GM_ShapeKeyTemp = GM_ShapeKeyTempMin;
            break;
        }

        if (GM_ShapeKeyTemp >= 0 && GM_ShapeKeyState == 2)
        {
            GM_ShapeKeyState = 0;
            break;
        }

        if (GM_ShapeKeyTemp <= 0 && GM_ShapeKeyState == 1)
        {
            GM_ShapeKeyState = 0;
        }
        break;

    case 2:
        if (GM_TimerBombFlag <= 0)
        {
            break;
        }

        if (GM_GameStatus_800AB3CC &
            (GAME_FLAG_BIT_27 | GAME_FLAG_BIT_28 | GAME_FLAG_BIT_29 | GAME_FLAG_BIT_31 | GAME_FLAG_BIT_32))
        {
            break;
        }

        if (GM_GameOverTimer_800AB3D4 != 0)
        {
            break;
        }

        if (menu_item_IsItemDisabled_8003B6D0(ITEM_TIMER_B))
        {
            break;
        }

        if (--GM_TimerBombFlag <= 0)
        {
            if (GM_PlayerStatus_800ABA50 & PLAYER_INVULNERABLE)
            {
                GM_TimerBombFlag = 1;
            }
            else
            {
                blastData.field_0 = 1024;
                blastData.field_4 = 5;
                blastData.field_8_z = 1024;
                blastData.field_C = 2000;
                blastData.field_10 = 10;

                GM_CurrentMap_800AB9B0 = GM_PlayerMap_800ABA0C;

                mtx = DG_ZeroMatrix_8009D430;
                mtx.t[0] = GM_PlayerPosition_800ABA10.vx;
                mtx.t[1] = GM_PlayerPosition_800ABA10.vy;
                mtx.t[2] = GM_PlayerPosition_800ABA10.vz;
                NewBlast_8006DFDC(&mtx, &blastData);

                GM_CurrentItemId = ITEM_NONE;
                GM_StatusEvent |= EV_BlownUp;
            }
        }
        else if (GM_CurrentItemId == ITEM_TIMER_B)
        {
            GM_SeSet2_80032968(0, 63, 117); // Bomb tick sound
        }
        break;

    case 3:
        if (GM_SnakeColdUnk9A < 0)
        {
            if (--GM_SnakeColdTimer < GM_SnakeColdUnk98)
            {
                GM_SnakeColdTimer = GM_SnakeColdUnk98;
                GM_StatusEvent |= EV_CommonCold;
            }
        }
        else
        {
            GM_SnakeColdTimer = 0;
        }

        break;

    case 4:
        GM_GameTimeSeconds++;
        break;
    }
}

void menu_item_update_8003C95C(Actor_MenuMan *work, unsigned int *pOt)
{
    GV_PAD         *pPad = work->field_24_pInput;
    Menu_Inventory *pLeftRight;

    if (work->field_2A_state == 0)
    {
        if (!(GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_11 | GAME_FLAG_BIT_20)))
        {
            if (!(GM_PlayerStatus_800ABA50 &
                  (PLAYER_PAD_OFF | PLAYER_PREVENT_ITEM_SWITCH | PLAYER_PREVENT_WEAPON_ITEM_SWITCH)))
            {
                if (menu_8003DA9C(&work->field_1DC_menu_item, pPad))
                {
                    if (menu_item_update_helper_8003BCD4(work))
                    {
                        work->field_2A_state = 2;
                        GV_PauseLevel_800AB928 |= 4;
                    }
                }
                else if (!(GM_GameStatus_800AB3CC & GAME_FLAG_BIT_19) && (pPad->press & PAD_L1))
                {
                    int itemid = GM_CurrentItemId;

                    if (itemid >= 0)
                    {
                        GM_CurrentItemId = -1;
                    }
                    else if (!menu_item_IsItemDisabled_8003B6D0(work->field_1DC_menu_item.field_11))
                    {
                        if (GM_Items[work->field_1DC_menu_item.field_11] > 0)
                        {
                            GM_CurrentItemId = work->field_1DC_menu_item.field_11;
                        }
                    }

                    if (itemid != GM_CurrentItemId)
                    {
                        GM_SeSet2_80032968(0, 63, 20);
                    }
                }
            }
        }
        else
        {
            return;
        }
    }
    else if (work->field_2A_state == 2)
    {
        pLeftRight = &work->field_1DC_menu_item;

        if (sub_8003DAFC(pLeftRight, pPad))
        {
            work->field_1DC_menu_item.field_10_state = 3;
        }
        else if (sub_8003D52C() > 255)
        {
            sub_8003D6CC(pLeftRight, pPad);
            menu_item_update_helper3_8003C24C(work->field_1DC_menu_item.field_C_alloc, pPad->press);
        }
    }
    else if (work->field_2A_state != 4)
    {
        if (GM_CurrentItemId >= 0)
        {
            int ret = sub_8003D52C();
            if (ret < 255)
            {
                sub_8003DA60(work, pOt, &work->field_1DC_menu_item, -ret / 4, 0);
                work->field_1DC_menu_item.field_12_flashingAnimationFrame = 0;
            }
        }
        else
        {
            work->field_1DC_menu_item.field_12_flashingAnimationFrame = 0;
        }
        return;
    }
    else
    {
        return;
    }

    menu_item_update_helper2_8003BF1C(work, pOt);
    menu_item_update_helper4_8003C4EC();
}

void sub_8003CB98(Actor_MenuMan *work)
{
    int            field_0_item_id_idx; // $a0
    PANEL_TEXTURE *pItem;               // $v0

    menu_restore_nouse_80043470();
    field_0_item_id_idx = work->field_1DC_menu_item.field_0_current.field_0_id;
    if (field_0_item_id_idx != ITEM_NONE ||
        (field_0_item_id_idx = work->field_1DC_menu_item.field_11, field_0_item_id_idx != ITEM_NONE))
    {
        pItem = menu_rpk_8003B5E0(field_0_item_id_idx);
        sub_8003CFE0(pItem, 0);
    }
}

void menu_item_init_8003CBF0(Actor_MenuMan *menuMan)
{
    short val = -1;

    menuMan->field_2C_modules[MENU_ITEM] = (TMenuUpdateFn)menu_item_update_8003C95C;
    menuMan->field_1DC_menu_item.field_0_current.field_0_id = val;
    menuMan->field_1DC_menu_item.field_10_state = 0;
    menuMan->field_1DC_menu_item.field_0_current.field_4_pos = 0;
    menuMan->field_1DC_menu_item.field_0_current.field_6_current = 1;
    menuMan->field_1DC_menu_item.field_11 = val;
    menuMan->field_28_flags |= 4;
    dword_800ABAD0 = 0;
    sub_8003D6A8(&menuMan->field_1DC_menu_item, 0, (int *)menu_item_helper_8003B8F0);
    menu_sub_8003B568();
    sub_8003CB98(menuMan);
    menu_init_nouse_800434A8();
}

void menu_item_kill_8003CC74(Actor_MenuMan *pMenu)
{
    pMenu->field_28_flags &= ~4u;
}
