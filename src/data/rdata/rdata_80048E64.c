#include "linker.h"
#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

const int  SECTION(".rdata") jpt_80011EB8[] = {0x80048F4C, 0x80048E6C, 0x80048EB8, 0x80048F30, 0x80048F3C};
const char SECTION(".rdata") aJimakuFontBuff[] = "jimaku_font_buffer_size %d\n";
const char SECTION(".rdata") aRadioCallOver[] = "RADIO CALL OVER!!\n";
const char SECTION(".rdata") aNoMemoryForFil[] = "NO MEMORY FOR FILE BODY\n";
const int  SECTION(".rdata") dword_crap7[] = {0x9C23582, 0x3E8206D0, 0x288223C2, 0x26811781, 0x3E810481, 0x3D01981,
                                              0,         0x42824182, 0x6D04A82,  0x6D00B82,  0x52812982, 0x7C22182,
                                              0xF8223C2, 0x26811781, 0x3E810481, 0x3D01981,  0};
const int  SECTION(".rdata") dword_80011F5C[] = {
     0x6D01B82,  0xCD903682, 0x19812781, 0x3D0,      0x42824182, 0x6D04A82,  0x6D00B82,  0xC812982,
     0x15811581, 0x26814C81, 0x3E810481, 0x53811B81, 0x3D0,      0x9C23582,  0x3E8206D0, 0x288223C2,
     0x9912B81,  0x17810A91, 0x17813E81, 0x3D01F81,  0,          0x6D01B82,  0x17813682, 0x17813E81,
     0x3D01F81,  0,          0x42824182, 0x6D04A82,  0x6D00B82,  0xC812982,  0x11911091, 0x15816490,
     0x26814C81, 0x3E810481, 0x53811B81, 0x3D0,      0xD819290,  0x4D823682, 0xF8223C2,  0x1F810C81,
     0x3E814A81, 0x53811B81, 0x3D0,      0x49820882, 0xC8106D0,  0xCA907E90, 0x3E811781, 0x1F811781,
     0x3D0,      0x6D01B82,  0x27813682, 0x3E810D81, 0x53811B81, 0x17812781, 0x3D01F81,  0};
const int SECTION(".rdata") dword_8001203C[] = {0x6D01B82,  0xC813682,  0x8910791,  0x3E811781, 0x1F811781, 0x3D0,
                                                0x6D04D82,  0xCD902982, 0x19812781, 0x3D0,      0x6D04D82,  0x17812982,
                                                0x17813E81, 0x3D01F81,  0,          0x6D01B82,  0x35823682, 0x48201C2,
                                                0xC814B82,  0x4A810281, 0x1B813E81, 0x3D05381,  0,          0x6D04D82,
                                                0x27812982, 0x3E810D81, 0x53811B81, 0x17812781, 0x3D01F81,  0};
const int SECTION(".rdata") dword_800120B4[] = {
    0x6D04D82,  0xC812982,  0x8910791,  0x3E811781, 0x1F811781, 0x3D0,      0x9C23582,  0x3E8206D0,
    0x288223C2, 0x3E811781, 0xB811981,  0x3FC0,     0x27900B91, 0x17810D81, 0x48812681, 0x17814D81,
    0x27810481, 0xB811981,  0x3FC0};
const char SECTION(".rdata") aFormatOk[] = "FORMAT OK?";
const char SECTION(".rdata") aOverwriteOk[] = "OVERWRITE OK?";
const char SECTION(".rdata") aRequestX[] = "REQUEST %X\n";
const char SECTION(".rdata") aResultX[] = "RESULT %X\n";
const char SECTION(".rdata") aNoMemoryForSta_0[] = "NO MEMORY FOR STACK\n";
const char SECTION(".rdata") aComplete[] = "COMPLETE";
const char SECTION(".rdata") aNoMemoryForObj[] = "NO MEMORY FOR OBJ\n";
const char SECTION(".rdata") aNewFileNeedDBl[] = "NEW FILE [ NEED %d BLOCK%s ]";
const char SECTION(".rdata") aFreeDBlockS[] = "FREE: %d BLOCK%s";
const char SECTION(".rdata") aCloseInfo[] = "close info\n";
const char SECTION(".rdata") aNoMemoryForInf[] = "NO MEMORY FOR INFO\n";
const char SECTION(".rdata") aAllocInfoX[] = "alloc info %X\n";
const char SECTION(".rdata") aFileS[] = "FILE %s\n";
const char SECTION(".rdata") aMemoryCard2[] = "MEMORY CARD 2";
const char SECTION(".rdata") aMemoryCard1[] = "MEMORY CARD 1";
const char SECTION(".rdata") aSaving[] = "SAVING...";
const char SECTION(".rdata") aNoSpace[] = "NO SPACE";
const char SECTION(".rdata") aLoadData[] = "LOAD DATA";
const char SECTION(".rdata") aLoading[] = "LOADING...";
const char SECTION(".rdata") aSelectMemoryCa[] = "SELECT MEMORY CARD";
const char SECTION(".rdata") aPressToExit[] = "PRESS * TO EXIT";
const char SECTION(".rdata") aPressToSelectM[] = "PRESS * TO SELECT MEMORY CARD";
const char SECTION(".rdata") aEndSaveMode[] = "END SAVE MODE\n";
const char SECTION(".rdata") aEndStateD[] = "END STATE %d\n";
const char SECTION(".rdata") aNoPlace[] = "NO PLACE";
const char SECTION(".rdata") aCodeD[] = "code %d\n";
const int  SECTION(".rdata") dword_800122A8[] = {0x64826D81, 0x6E817782, 0};
const int  SECTION(".rdata") dword_800122B4[] = {0x67826D81, 0x6E816382, 0};
const int  SECTION(".rdata") dword_800122C0[] = {0x6D826D81, 0x6E816C82, 0};
const int  SECTION(".rdata") dword_800122CC[] = {0x64826D81, 0x6E817982, 0};
const int  SECTION(".rdata") dword_800122D8[] = {0x75826D81, 0x6E816482, 0};
const char SECTION(".rdata") aSSSSSS[] = "%s%s%s%s%s%s";
const int  SECTION(".rdata") dword_800122F4[] = {0x66826C82, 0xE7817282, 0};
const char SECTION(".rdata") aSaveData[] = "SAVE DATA";
const int  SECTION(".rdata") jpt_8001230C[] = {0x8004C4E8, 0x8004C580, 0x8004CAF8, 0x8004CB7C,
                                               0x8004CCD4, 0x8004CC34, 0x8004CDB4};
const int  SECTION(".rdata") aEEBEp_80012328[] = {0xCDA5B9A5, 0xAFA5BCA1, 0};
const char SECTION(".rdata") aForceActCancel[] = "force act cancel\n";
const char SECTION(".rdata") aRunMoveCancel[] = "run move cancel\n";
const char SECTION(".rdata") aForceStanceCan[] = "force stance cancel\n";
const char SECTION(".rdata") aPosDDD[] = "pos %d %d %d\n";
const char SECTION(".rdata") aTurnDDD[] = "turn %d %d %d\n";
const char SECTION(".rdata") aCeilFloorDD[] = "ceil floor %d %d\n";
const char SECTION(".rdata") aStatus4x[] = "status %4x\n";
const char SECTION(".rdata") aWeaponD[] = "weapon %d\n";
const char SECTION(".rdata") aItemD[] = "item %d\n";
const char SECTION(".rdata") aFlag4x[] = "flag %4x\n";
const char SECTION(".rdata") aFlag24x[] = "flag2 %4x\n";
const char SECTION(".rdata") aStanceD[] = "stance %d\n";
const char SECTION(".rdata") aPadtoD[] = "padto %d\n";
const char SECTION(".rdata") aTrapCheckD[] = "trap check %d\n";
const char SECTION(".rdata") aSnaInitC[] = "sna_init.c";
const int  SECTION(".rdata") jpt_80012418[] = {0x80056134, 0x80056124, 0x8005615C, 0x80056198,
                                               0x800561E4, 0x8005624C, 0x80056504};
const char SECTION(".rdata") aNoReachZoneFro[] = " no reach zone from %d to %d \n";
const char SECTION(".rdata") aOverNoReachZon[] = "over no reach zone from %d to %d \n";
const char SECTION(".rdata") aBoundNoReachZo[] = "bound no reach zone from %d to %d \n";
const char SECTION(".rdata") aVibrateC[] = "vibrate.c";
const int  SECTION(".rdata") dword_800124A8[] = {
     0x38B00,    0x340009,   0x2FE0164,  0xC0100,    0x6FF0108,  0xECFF0000, 0x20000,    0xC0D01,    0x6FF0104,
     0xECFF0000, 0xFF0A0000, 0x2F6FFF6,  0xF0D0100,  0xFF0AFE01, 0x2F6FFF6,  0xC0100,    0x6FF0110,  0xECFF0000,
     0x20000,    0xC0D01,    0x6FF0104,  0xECFF0000, 0xFF0A0000, 0x2F6FFF6,  0xF0D0100,  0xAFE01,    0x21E001E,
     0xC0100,    0x6FF0110,  0xECFF0000, 0x20000,    0xC0D01,    0x6FF0104,  0xECFF0000, 0xFF0A0000, 0x2F6FFF6,
     0xF0D0100,  0x48300,    0x33000B,   0x174005A,  0x8FF01FE,  0xC010101,  0x2080500,  0xFF010202, 0xD010002,
     0x114000C,  0x1E000AFF, 0xFE081E00, 0x2FEFE,    0x10F0D01,  0xD4FE0AFE, 0xCD4FE,    0x2020805,  0x2FF0102,
     0xC0D0100,  0xFF011400, 0x1E000A,   0xFEFE081E, 0x10002FE,  0xFE010F0D, 0xFF9CFF0A, 0xE000C9C,  0xFFFEFF0A,
     0xFEFE08FE, 0x2FF01FE,  0xF0D0100,  0x10AFE01,  0xCF401F4,  0xA1D00,    0x8140014,  0x1FFFFFF,  0x10002FF,
     0xF0D,      0x31D00,    0x100009,   0xE803091B, 0xF010002,  0xFF0A0307, 0x238FF38,  0x70F0100,  0xFCFE0A03,
     0x2FCFE,    0xF01,      0x31D00,    0x100009,   0xE803091B, 0xF010002,  0xFD0A0307, 0x2A8FDA8,  0x70F0100,
     0x7CFC0A03, 0x27CFC,    0xF01,      0x10400,    0x1000205,  0xF,        0x10700,    0xE8030905, 0xF010002,
     0x2CB00,    0xC790007,  0x60B00,    0xECFF00,   0x1000200,  0x52B0B0D,  0x14000000, 0xFF860000, 0xFF0100F6,
     0xA0086F6,  0xA000100,  0x104000C,  0x10002FF,  0x60D,      0xD8FF,     0x104000C,  0x10002FF,  0x60D,
     0,          0x102000C,  0x22B0BFF,  0xC0D0200,  0xFF010200, 0xD020002,  5,          0x7000000,  0xD8D80801,
     0x4000CD8,  0xF0F0F008, 0xD010002,  0xB000C0F,  0xFF000006, 0x20000EC,  0x50D0100,  0,          0xFF860000,
     0xFF0100EC, 0x140086EC, 0x14000100, 0x102000C,  0x22B0BFF,  0xC0D0100,  0xFF010400, 0xD010002,  0x104000C,
     0x20002FF,  0x50D,      0};
const int SECTION(".rdata") dword_800126F4[] = {
    0xD8080107, 0xCD8D8,    0xF0F00804, 0x10002F0,  0xF0D,      0x11900,    0xCFE0105,  0xFF011400, 0xD010002,
    0x10A000C,  0xF9F908FF, 0x10002F9,  0xF0D,      0x12300,    0xCFE0105,  0xFF010A00, 0x50000A,   0x1000250,
    0x5000C0D,  0x50000A,   0x8FF0150,  0x2F2F2F2,  0xF0D0100,  0x24A00,    0x1200007,  0x5000CFE,  0x2FF01,
    0xC0D01,    0x8FF010A,  0x2F4F4F4,  0xF0D0100,  0xCFE01,    0x2C010A04, 0xFF012C01, 0xD010002,  0xA0A000C,
    0x46004600, 0x2FF01,    0xC0D01,    0xAFF010A,  0x50005000, 0xE7E7E708, 0xD010002,  0xF,        0x12700,
    0xCFE0105,  0xFF010500, 0x64000A,   0xF6F60864, 0x10002F6,  0x5000C0D,  0xAFF01,    0x8C800C8,  0x2F3F3F3,
    0xF0D0100,  0x13900,    0xCFE0105,  0xFF011400, 0x1000A,    0x5050801,  0x1000205,  0xC000C0D,  0xAFF01,
    0x8050005,  0x2FBFBFB,  0xC0D0100,  0xFF010A00, 0xA000A,    0xFBFB080A, 0x10002FB,  0xF0D};
const char SECTION(".rdata") aScriptActErr[] = " SCRIPT ACT ERR!! \n";
const char SECTION(".rdata") aAnimeC[] = "anime.c";
const char SECTION(".rdata") aShadowC[] = "shadow.c";
const char SECTION(".rdata") aAfterseC[] = "afterse.c";
const char SECTION(".rdata") aSnaHip1[] = "sna_hip1";
const char SECTION(".rdata") aSnaChest3[] = "sna_chest3";
const char SECTION(".rdata") aSnaChest2[] = "sna_chest2";
const char SECTION(".rdata") aSnaChest1[] = "sna_chest1";
const char SECTION(".rdata") aSnaArmer4[] = "sna_armer4";
const char SECTION(".rdata") aSnaArmer3[] = "sna_armer3";
const char SECTION(".rdata") aSnaArmer2[] = "sna_armer2";
const char SECTION(".rdata") aSnaArmer1[] = "sna_armer1";
const char SECTION(".rdata") aBodyarmC[] = "bodyarm.c";
const char SECTION(".rdata") aGasMask_DUP[] = "gas_mask";
const char SECTION(".rdata") aGasmaskC[] = "gasmask.c";
const char SECTION(".rdata") aKogaku2C[] = "kogaku2.c";
const char SECTION(".rdata") aCbBox22[] = "cb_box22";
const char SECTION(".rdata") aCbBox21[] = "cb_box21";
const char SECTION(".rdata") aCbBox42[] = "cb_box42";
const char SECTION(".rdata") aCbBox41[] = "cb_box41";
const char SECTION(".rdata") aCbBox12[] = "cb_box12";
const char SECTION(".rdata") aCbBox11[] = "cb_box11";
const int  SECTION(".rdata") dword_crap8[] = {0xDCA5CAC3, 0xEBA5BCA1, 0};
const char SECTION(".rdata") aCbBox[] = "cb_box";
const char SECTION(".rdata") aBoxC[] = "box.c";
const char SECTION(".rdata") aSnaFace3[] = "sna_face3";
const char SECTION(".rdata") aSnaFace2[] = "sna_face2";
const char SECTION(".rdata") aSnaFace[] = "sna_face";
const char SECTION(".rdata") aSnaMf3[] = "sna_mf3";
const char SECTION(".rdata") aSnaMf2[] = "sna_mf2";
const char SECTION(".rdata") aSnaMf1[] = "sna_mf1";
const char SECTION(".rdata") aBandanaC[] = "bandana.c";
const char SECTION(".rdata") aCigar[] = "cigar";
const char SECTION(".rdata") aRcmL[] = "rcm_l";
const char SECTION(".rdata") aTabakoC[] = "tabako.c";
const char SECTION(".rdata") aZoomLevelD[] = "- ZOOM LEVEL - - %d -";
const char SECTION(".rdata") aD_44[] = "%d";

const char SECTION(".rdata") aGoggles_2[] = "goggles";
const char SECTION(".rdata") aScopeC[] ="scope.c";

// TODO: Some kanji text in here
const int  SECTION(".rdata") aD_4_800129B4[] = {0x69736D67, 0x2E746867, 0x63,       0x45564153, 0x4F485020,
                                                0x4F54,     0x73257325, 0x73257325, 0};


const int  SECTION(".rdata") aVlvfvrbc_800129EC[] = {0x66826C82, 0xE7817282, 0};
const int  SECTION(".rdata") dword_800129F8[] = {0x4081, 0x67826F82, 0x73826E82, 0x6E82};
const char SECTION(".rdata") aPHOTO[] = "PHOTO %02d\n";
const char SECTION(".rdata") aSaveHeaderX[] = "save header = %x\n";
const char SECTION(".rdata") aDTryQScaleDSiz[] = "%d try q_scale = %d size = %d\n";
const char SECTION(".rdata") aSinreiSyasinCh[] = "Sinrei Syasin Check Start\n";
const char SECTION(".rdata") aHereIsSinreiSp[] = "Here is Sinrei Spot!\n";
const char SECTION(".rdata") aGmPhotocodeD[] = "GM_Photocode = %d\n";
const char SECTION(".rdata") aPointCheck[] = "Point Check\n";
const char SECTION(".rdata") aResultD[] = "Result = %d\n";
const char SECTION(".rdata") aNotSinreiSpot[] = "Not Sinrei Spot!\n";
const char SECTION(".rdata") aGoggles[] = "goggles";
const char SECTION(".rdata") aZoom4d[] = "zoom  : %4d\n";
const char SECTION(".rdata") aAngle4d4d[] = "angle : %4d, %4d\n";
const char SECTION(".rdata") aJpegcamC[] = "jpegcam.c";
const char SECTION(".rdata") aGrenadeC[] = "grenade.c";
const char SECTION(".rdata") aClaymore_0[] = "claymore";
const char SECTION(".rdata") aLockOn[] = "LOCK_ON\n";
const char SECTION(".rdata") aStnsightC[] = "stnsight.c";
const char SECTION(".rdata") aRfsightC[] = "rfsight.c";
const char SECTION(".rdata") aTenageC[] = "tenage.c";
const char SECTION(".rdata") aBakudanC[] = "bakudan.c";
const char SECTION(".rdata") aClaymore_1[] = "CLAYMORE";
const char SECTION(".rdata") aFull_0[] = "FULL";
const char SECTION(".rdata") aClaymore_2[] = "claymore";
const char SECTION(".rdata") aJiraiC[] = "jirai.c";
const char SECTION(".rdata") aEnemy[] = "ENEMY\n";
const char SECTION(".rdata") aD_4[] = "%d";               // 80012B80
const char SECTION(".rdata") aSocomF[] = "socom_f";       // 80012B84
const char SECTION(".rdata") rRmissileC[] = "rmissile.c"; // 80012B8C
const char SECTION(".rdata") aRmissileC[] = "amissile.c"; // 80012B98
const char SECTION(".rdata") aBlastC[] = "blast.c";       // 80012BA4

const unsigned char SECTION(".rdata") byte_80012BAC[64] = {
    0u,   59u,  1u,   0u, 5u, 1u, 0u,   2u, 0u,  1u, 12u, 0u,  2u,   1u,   255u, 10u,  4u,  176u, 4u,   176u, 2u,   0u,
    1u,   13u,  12u,  0u, 6u, 1u, 255u, 2u, 0u,  1u, 13u, 12u, 0u,   7u,   1u,   255u, 10u, 0u,   100u, 0u,   100u, 8u,
    248u, 248u, 248u, 2u, 0u, 1u, 10u,  0u, 80u, 0u, 80u, 8u,  248u, 248u, 248u, 2u,   0u,  1u,   13u,  15u};

const unsigned char SECTION(".rdata") byte_80012BEC[64] = {
    0u,   59u,  1u,   0u, 5u,  1u, 0u,   2u, 0u,  1u, 12u, 0u,  4u,   1u,   255u, 10u,  4u,  176u, 4u,   176u, 2u,   0u,
    1u,   13u,  12u,  0u, 12u, 1u, 255u, 2u, 0u,  1u, 13u, 12u, 0u,   8u,   1u,   255u, 10u, 0u,   100u, 0u,   100u, 8u,
    248u, 248u, 248u, 2u, 0u,  1u, 10u,  0u, 80u, 0u, 80u, 8u,  248u, 248u, 248u, 2u,   0u,  1u,   13u,  15u};

const unsigned char SECTION(".rdata") byte_80012C2C[64] = {
    0u,   59u,  1u,   0u, 5u, 1u, 0u,   2u, 0u,  1u, 12u, 0u,  2u,   1u,   255u, 10u,  2u,  88u, 2u,  88u, 2u,  0u,
    1u,   13u,  12u,  0u, 6u, 1u, 255u, 2u, 0u,  1u, 13u, 12u, 0u,   7u,   1u,   255u, 10u, 0u,  50u, 0u,  50u, 8u,
    248u, 248u, 248u, 2u, 0u, 1u, 10u,  0u, 40u, 0u, 40u, 8u,  248u, 248u, 248u, 2u,   0u,  1u,  13u, 15u};

const unsigned char SECTION(".rdata") byte_80012C6C[64] = {
    0u,   59u,  1u,   0u, 5u, 1u, 0u,   2u, 0u,  1u, 12u, 0u,  2u,   1u,   255u, 10u,  0u,  200u, 0u,  200u, 2u,  0u,
    1u,   13u,  12u,  0u, 6u, 1u, 255u, 2u, 0u,  1u, 13u, 12u, 0u,   7u,   1u,   255u, 10u, 0u,   20u, 0u,   20u, 8u,
    248u, 248u, 248u, 2u, 0u, 1u, 10u,  0u, 20u, 0u, 20u, 8u,  248u, 248u, 248u, 2u,   0u,  1u,   13u, 15u};

const unsigned char SECTION(".rdata") byte_80012CAC[290] = {
    1u,   23u,  4u,   0u,   11u,  0u,   75u,  0u,   144u, 0u,   217u, 1u,   0u,   2u,   0u,  1u,   12u,  0u,   2u,
    1u,   255u, 10u,  4u,   176u, 4u,   176u, 2u,   0u,   1u,   13u,  12u,  0u,   6u,   1u,  255u, 10u,  0u,   200u,
    0u,   200u, 2u,   0u,   1u,   13u,  12u,  0u,   7u,   1u,   255u, 10u,  0u,   100u, 0u,  100u, 8u,   248u, 248u,
    248u, 2u,   0u,   1u,   10u,  0u,   80u,  0u,   80u,  8u,   248u, 248u, 248u, 2u,   0u,  1u,   13u,  15u,  1u,
    0u,   2u,   0u,   1u,   1u,   0u,   2u,   0u,   1u,   12u,  0u,   2u,   1u,   255u, 10u, 3u,   232u, 3u,   232u,
    2u,   0u,   1u,   13u,  12u,  0u,   6u,   1u,   255u, 10u,  0u,   180u, 0u,   180u, 2u,  0u,   1u,   13u,  12u,
    0u,   7u,   1u,   255u, 10u,  0u,   100u, 0u,   100u, 8u,   248u, 248u, 248u, 2u,   0u,  1u,   10u,  0u,   80u,
    0u,   80u,  8u,   248u, 248u, 248u, 2u,   0u,   1u,   13u,  15u,  12u,  0u,   2u,   1u,  0u,   2u,   0u,   1u,
    13u,  1u,   0u,   2u,   0u,   1u,   12u,  0u,   2u,   1u,   255u, 10u,  3u,   32u,  3u,  32u,  2u,   0u,   1u,
    13u,  12u,  0u,   6u,   1u,   255u, 10u,  0u,   160u, 0u,   160u, 2u,   0u,   1u,   13u, 12u,  0u,   7u,   1u,
    255u, 10u,  0u,   100u, 0u,   100u, 8u,   248u, 248u, 248u, 2u,   0u,   1u,   10u,  0u,  80u,  0u,   80u,  8u,
    248u, 248u, 248u, 2u,   0u,   1u,   13u,  15u,  12u,  0u,   3u,   1u,   0u,   2u,   0u,  1u,   13u,  1u,   0u,
    2u,   0u,   1u,   12u,  0u,   2u,   1u,   255u, 10u,  2u,   88u,  2u,   88u,  2u,   0u,  1u,   13u,  12u,  0u,
    6u,   1u,   255u, 10u,  0u,   140u, 0u,   140u, 2u,   0u,   1u,   13u,  12u,  0u,   7u,  1u,   255u, 10u,  0u,
    100u, 0u,   100u, 8u,   248u, 248u, 248u, 2u,   0u,   1u,   10u,  0u,   80u,  0u,   80u, 8u,   248u, 248u, 248u,
    2u,   0u,   1u,   13u,  15u};

const char SECTION(".rdata") aOpen[] = " open!! \n";                     // 80012DD0
const char SECTION(".rdata") aClose[] = " close!! \n";                   // 80012DDC
const char SECTION(".rdata") aDoorCloseD[] = "door:close %d\n";          // 80012DE8
const char SECTION(".rdata") aCancel[] = "cancel\n";                     // 80012DF8
const char SECTION(".rdata") aDoorOpenD[] = "door:open %d\n";            // 80012E00
const char SECTION(".rdata") aSnakeDoorX[] = "Snake Door %X\n";          // 80012E10
const char SECTION(".rdata") aDoorOpencancel[] = "door:opencancel %d\n"; // 80012E20
const char SECTION(".rdata") aCloseDoorX[] = "close door %X\n";
const char SECTION(".rdata") aCloseDoorX_0[] = "CLOSE door %X\n";
const char SECTION(".rdata") aDoorC[] = "door.c";

const char SECTION(".rdata") aSgtrect3C[] = "sgtrect3.c";

// AN_Blood_Mist_80072934
const char SECTION(".rdata") aStringFormat[] = "%s";
const char SECTION(".rdata") aSightC[] = "sight.c";
const char SECTION(".rdata") aBlood_1[] = "blood_1";
const char SECTION(".rdata") aBloodC[] = "blood.c";
const int  SECTION(".rdata") aS_2_80012E68[] = {0x12A00,   0x2FE0105, 0x80100,    0xCB0B0,    0xAFF0105, 0x64006400,
                                                0xD010002, 0x105000C, 0x1E000AFF, 0xE8081E00, 0x2F8F8,   0xF0D01};

const char SECTION(".rdata") aDBloodC[] = "d_blood.c";
const char SECTION(".rdata") aKetchapGrey[] = "ketchap_grey";
const char SECTION(".rdata") aDBloodrC[] = "d_bloodr.c";

char SECTION(".rdata") byte_80012EDC[] = {0, 0, 0};
char SECTION(".rdata") byte_80012EDF = 0;

const char SECTION(".rdata") byte_80012EE0[4] = {0xDC, 0x5, 0, 0};
const char SECTION(".rdata") aBullet_0[] = "bullet";

const SVECTOR SECTION(".rdata") stru_80012EEC = {200, 200, 200, 0};

const char SECTION(".rdata") aClaymoreC[] = "claymore.c";
const char SECTION(".rdata") aSparkFl[] = "spark_fl";

const char SECTION(".rdata") aSparkC[] = "spark.c";
const char SECTION(".rdata") aRefrection6[] = "refrection6";
const char SECTION(".rdata") aStngrndC[] = "stngrnd.c";
const int  SECTION(".rdata") dword_80012F2C[] = {0x11F00,   0xC000105, 0x10A0400, 0x2F401F4, 0xC0D0100,
                                                 0x10A0700, 0x8F401F4, 0x2F0F0F0, 0xF0D0100};
const int  SECTION(".rdata") dword_80012F50[] = {0x11F00, 0xC000105, 0x20A0500, 0x2580258, 0xC0D0100,
                                                 0xA0900, 0x81E001E, 0x2EEEEEE, 0xF0D0100};
