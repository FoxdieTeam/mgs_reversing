#include "linker.h"

int SECTION(".rdata") jpt_80048E64[] = {0x80048F4C, 0x80048E6C, 0x80048EB8, 0x80048F30, 0x80048F3C};
const char SECTION(".rdata") aJimakuFontBuff[] = "jimaku_font_buffer_size %d\n";
const char SECTION(".rdata") aRadioCallOver[] = "RADIO CALL OVER!!\n";
const char SECTION(".rdata") aNoMemoryForFil[] = "NO MEMORY FOR FILE BODY\n";
int SECTION(".rdata") dword_crap7[] = {0x9C23582, 0x3E8206D0, 0x288223C2, 0x26811781, 0x3E810481, 0x3D01981, 0, 0x42824182, 0x6D04A82, 0x6D00B82, 0x52812982, 0x7C22182, 0xF8223C2, 0x26811781, 0x3E810481, 0x3D01981, 0};
int SECTION(".rdata") dword_80011F5C[] = {0x6D01B82, 0xCD903682, 0x19812781, 0x3D0, 0x42824182, 0x6D04A82, 0x6D00B82, 0xC812982, 0x15811581, 0x26814C81, 0x3E810481, 0x53811B81, 0x3D0, 0x9C23582, 0x3E8206D0, 0x288223C2, 0x9912B81, 0x17810A91, 0x17813E81, 0x3D01F81, 0, 0x6D01B82, 0x17813682, 0x17813E81, 0x3D01F81, 0, 0x42824182, 0x6D04A82, 0x6D00B82, 0xC812982, 0x11911091, 0x15816490, 0x26814C81, 0x3E810481, 0x53811B81, 0x3D0, 0xD819290, 0x4D823682, 0xF8223C2, 0x1F810C81, 0x3E814A81, 0x53811B81, 0x3D0, 0x49820882, 0xC8106D0, 0xCA907E90, 0x3E811781, 0x1F811781, 0x3D0, 0x6D01B82, 0x27813682, 0x3E810D81, 0x53811B81, 0x17812781, 0x3D01F81, 0};
int SECTION(".rdata") dword_8001203C[] = {0x6D01B82, 0xC813682, 0x8910791, 0x3E811781, 0x1F811781, 0x3D0, 0x6D04D82, 0xCD902982, 0x19812781, 0x3D0, 0x6D04D82, 0x17812982, 0x17813E81, 0x3D01F81, 0, 0x6D01B82, 0x35823682, 0x48201C2, 0xC814B82, 0x4A810281, 0x1B813E81, 0x3D05381, 0, 0x6D04D82, 0x27812982, 0x3E810D81, 0x53811B81, 0x17812781, 0x3D01F81, 0};
int SECTION(".rdata") dword_800120B4[] = {0x6D04D82, 0xC812982, 0x8910791, 0x3E811781, 0x1F811781, 0x3D0, 0x9C23582, 0x3E8206D0, 0x288223C2, 0x3E811781, 0xB811981, 0x3FC0, 0x27900B91, 0x17810D81, 0x48812681, 0x17814D81, 0x27810481, 0xB811981, 0x3FC0, 0x4D524F46, 0x4F205441, 0x3F4B, 0x5245564F, 0x54495257, 0x4B4F2045, 0x3F, 0x55514552, 0x20545345, 0xA5825, 0x55534552, 0x2520544C, 0xA58};
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
int SECTION(".rdata") dword_800122A8[] = {0x64826D81, 0x6E817782, 0};
int SECTION(".rdata") dword_800122B4[] = {0x67826D81, 0x6E816382, 0};
int SECTION(".rdata") dword_800122C0[] = {0x6D826D81, 0x6E816C82, 0};
int SECTION(".rdata") dword_800122CC[] = {0x64826D81, 0x6E817982, 0};
int SECTION(".rdata") dword_800122D8[] = {0x75826D81, 0x6E816482, 0};
const char SECTION(".rdata") aSSSSSS[] = "%s%s%s%s%s%s";
int SECTION(".rdata") dword_800122F4[] = {0x66826C82, 0xE7817282, 0};
const char SECTION(".rdata") aSaveData[] = "SAVE DATA";
int SECTION(".rdata") jpt_8004C4E0[] = {0x8004C4E8, 0x8004C580, 0x8004CAF8, 0x8004CB7C, 0x8004CCD4, 0x8004CC34, 0x8004CDB4};
int SECTION(".rdata") dword_80012328[] = {0xCDA5B9A5, 0xAFA5BCA1, 0};
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
int SECTION(".rdata") jpt_8005611C[] = {0x80056134, 0x80056124, 0x8005615C, 0x80056198, 0x800561E4, 0x8005624C, 0x80056504};
const char SECTION(".rdata") aNoReachZoneFro[] = " no reach zone from %d to %d \n";
const char SECTION(".rdata") aOverNoReachZon[] = "over no reach zone from %d to %d \n";
const char SECTION(".rdata") aBoundNoReachZo[] = "bound no reach zone from %d to %d \n";
const char SECTION(".rdata") aVibrateC[] = "vibrate.c";
int SECTION(".rdata") dword_800124A8[] = {0x38B00, 0x340009, 0x2FE0164, 0xC0100, 0x6FF0108, 0xECFF0000, 0x20000, 0xC0D01, 0x6FF0104, 0xECFF0000, 0xFF0A0000, 0x2F6FFF6, 0xF0D0100, 0xFF0AFE01, 0x2F6FFF6, 0xC0100, 0x6FF0110, 0xECFF0000, 0x20000, 0xC0D01, 0x6FF0104, 0xECFF0000, 0xFF0A0000, 0x2F6FFF6, 0xF0D0100, 0xAFE01, 0x21E001E, 0xC0100, 0x6FF0110, 0xECFF0000, 0x20000, 0xC0D01, 0x6FF0104, 0xECFF0000, 0xFF0A0000, 0x2F6FFF6, 0xF0D0100, 0x48300, 0x33000B, 0x174005A, 0x8FF01FE, 0xC010101, 0x2080500, 0xFF010202, 0xD010002, 0x114000C, 0x1E000AFF, 0xFE081E00, 0x2FEFE, 0x10F0D01, 0xD4FE0AFE, 0xCD4FE, 0x2020805, 0x2FF0102, 0xC0D0100, 0xFF011400, 0x1E000A, 0xFEFE081E, 0x10002FE, 0xFE010F0D, 0xFF9CFF0A, 0xE000C9C, 0xFFFEFF0A, 0xFEFE08FE, 0x2FF01FE, 0xF0D0100, 0x10AFE01, 0xCF401F4, 0xA1D00, 0x8140014, 0x1FFFFFF, 0x10002FF, 0xF0D, 0x31D00, 0x100009, 0xE803091B, 0xF010002, 0xFF0A0307, 0x238FF38, 0x70F0100, 0xFCFE0A03, 0x2FCFE, 0xF01, 0x31D00, 0x100009, 0xE803091B, 0xF010002, 0xFD0A0307, 0x2A8FDA8, 0x70F0100, 0x7CFC0A03, 0x27CFC, 0xF01, 0x10400, 0x1000205, 0xF, 0x10700, 0xE8030905, 0xF010002, 0x2CB00, 0xC790007, 0x60B00, 0xECFF00, 0x1000200, 0x52B0B0D, 0x14000000, 0xFF860000, 0xFF0100F6, 0xA0086F6, 0xA000100, 0x104000C, 0x10002FF, 0x60D, 0xD8FF, 0x104000C, 0x10002FF, 0x60D, 0, 0x102000C, 0x22B0BFF, 0xC0D0200, 0xFF010200, 0xD020002, 5, 0x7000000, 0xD8D80801, 0x4000CD8, 0xF0F0F008, 0xD010002, 0xB000C0F, 0xFF000006, 0x20000EC, 0x50D0100, 0, 0xFF860000, 0xFF0100EC, 0x140086EC, 0x14000100, 0x102000C, 0x22B0BFF, 0xC0D0100, 0xFF010400, 0xD010002, 0x104000C, 0x20002FF, 0x50D, 0};
int SECTION(".rdata") dword_800126F4[] = {0xD8080107, 0xCD8D8, 0xF0F00804, 0x10002F0, 0xF0D, 0x11900, 0xCFE0105, 0xFF011400, 0xD010002, 0x10A000C, 0xF9F908FF, 0x10002F9, 0xF0D, 0x12300, 0xCFE0105, 0xFF010A00, 0x50000A, 0x1000250, 0x5000C0D, 0x50000A, 0x8FF0150, 0x2F2F2F2, 0xF0D0100, 0x24A00, 0x1200007, 0x5000CFE, 0x2FF01, 0xC0D01, 0x8FF010A, 0x2F4F4F4, 0xF0D0100, 0xCFE01, 0x2C010A04, 0xFF012C01, 0xD010002, 0xA0A000C, 0x46004600, 0x2FF01, 0xC0D01, 0xAFF010A, 0x50005000, 0xE7E7E708, 0xD010002, 0xF, 0x12700, 0xCFE0105, 0xFF010500, 0x64000A, 0xF6F60864, 0x10002F6, 0x5000C0D, 0xAFF01, 0x8C800C8, 0x2F3F3F3, 0xF0D0100, 0x13900, 0xCFE0105, 0xFF011400, 0x1000A, 0x5050801, 0x1000205, 0xC000C0D, 0xAFF01, 0x8050005, 0x2FBFBFB, 0xC0D0100, 0xFF010A00, 0xA000A, 0xFBFB080A, 0x10002FB, 0xF0D};
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
int SECTION(".rdata") dword_crap8[] = {0xDCA5CAC3, 0xEBA5BCA1, 0};
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
int SECTION(".rdata") dword_800129B4[] = {0x6425, 0x67676F67, 0x73656C, 0x706F6373, 0x632E65, 0x69736D67, 0x2E746867, 0x63, 0x45564153, 0x4F485020, 0x4F54, 0x73257325, 0x73257325, 0};
int SECTION(".rdata") dword_800129EC[] = {0x66826C82, 0xE7817282, 0};
int SECTION(".rdata") dword_800129F8[] = {0x4081, 0x67826F82, 0x73826E82, 0x6E82, 0x544F4850, 0x3025204F, 0xA6432};
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
const char SECTION(".rdata") aD_4[] = "%d"; // 80012B80
const char SECTION(".rdata") aSocomF[] = "socom_f"; // 80012B84
const char SECTION(".rdata") rRmissileC[] = "rmissile.c"; // 80012B8C
const char SECTION(".rdata") aRmissileC[] = "amissile.c"; // 80012B98
const char SECTION(".rdata") aBlastC[] = "blast.c"; // 80012BA4

const unsigned char SECTION(".rdata") byte_80012BAC[64] =
{
  0u,
  59u,
  1u,
  0u,
  5u,
  1u,
  0u,
  2u,
  0u,
  1u,
  12u,
  0u,
  2u,
  1u,
  255u,
  10u,
  4u,
  176u,
  4u,
  176u,
  2u,
  0u,
  1u,
  13u,
  12u,
  0u,
  6u,
  1u,
  255u,
  2u,
  0u,
  1u,
  13u,
  12u,
  0u,
  7u,
  1u,
  255u,
  10u,
  0u,
  100u,
  0u,
  100u,
  8u,
  248u,
  248u,
  248u,
  2u,
  0u,
  1u,
  10u,
  0u,
  80u,
  0u,
  80u,
  8u,
  248u,
  248u,
  248u,
  2u,
  0u,
  1u,
  13u,
  15u
};

const unsigned char SECTION(".rdata") byte_80012BEC[64] =
{
  0u,
  59u,
  1u,
  0u,
  5u,
  1u,
  0u,
  2u,
  0u,
  1u,
  12u,
  0u,
  4u,
  1u,
  255u,
  10u,
  4u,
  176u,
  4u,
  176u,
  2u,
  0u,
  1u,
  13u,
  12u,
  0u,
  12u,
  1u,
  255u,
  2u,
  0u,
  1u,
  13u,
  12u,
  0u,
  8u,
  1u,
  255u,
  10u,
  0u,
  100u,
  0u,
  100u,
  8u,
  248u,
  248u,
  248u,
  2u,
  0u,
  1u,
  10u,
  0u,
  80u,
  0u,
  80u,
  8u,
  248u,
  248u,
  248u,
  2u,
  0u,
  1u,
  13u,
  15u
};

const unsigned char SECTION(".rdata") byte_80012C2C[64] =
{
  0u,
  59u,
  1u,
  0u,
  5u,
  1u,
  0u,
  2u,
  0u,
  1u,
  12u,
  0u,
  2u,
  1u,
  255u,
  10u,
  2u,
  88u,
  2u,
  88u,
  2u,
  0u,
  1u,
  13u,
  12u,
  0u,
  6u,
  1u,
  255u,
  2u,
  0u,
  1u,
  13u,
  12u,
  0u,
  7u,
  1u,
  255u,
  10u,
  0u,
  50u,
  0u,
  50u,
  8u,
  248u,
  248u,
  248u,
  2u,
  0u,
  1u,
  10u,
  0u,
  40u,
  0u,
  40u,
  8u,
  248u,
  248u,
  248u,
  2u,
  0u,
  1u,
  13u,
  15u
};

const unsigned char SECTION(".rdata") byte_80012C6C[64] =
{
  0u,
  59u,
  1u,
  0u,
  5u,
  1u,
  0u,
  2u,
  0u,
  1u,
  12u,
  0u,
  2u,
  1u,
  255u,
  10u,
  0u,
  200u,
  0u,
  200u,
  2u,
  0u,
  1u,
  13u,
  12u,
  0u,
  6u,
  1u,
  255u,
  2u,
  0u,
  1u,
  13u,
  12u,
  0u,
  7u,
  1u,
  255u,
  10u,
  0u,
  20u,
  0u,
  20u,
  8u,
  248u,
  248u,
  248u,
  2u,
  0u,
  1u,
  10u,
  0u,
  20u,
  0u,
  20u,
  8u,
  248u,
  248u,
  248u,
  2u,
  0u,
  1u,
  13u,
  15u
};

const unsigned char SECTION(".rdata") byte_80012CAC[290] =
{
  1u,
  23u,
  4u,
  0u,
  11u,
  0u,
  75u,
  0u,
  144u,
  0u,
  217u,
  1u,
  0u,
  2u,
  0u,
  1u,
  12u,
  0u,
  2u,
  1u,
  255u,
  10u,
  4u,
  176u,
  4u,
  176u,
  2u,
  0u,
  1u,
  13u,
  12u,
  0u,
  6u,
  1u,
  255u,
  10u,
  0u,
  200u,
  0u,
  200u,
  2u,
  0u,
  1u,
  13u,
  12u,
  0u,
  7u,
  1u,
  255u,
  10u,
  0u,
  100u,
  0u,
  100u,
  8u,
  248u,
  248u,
  248u,
  2u,
  0u,
  1u,
  10u,
  0u,
  80u,
  0u,
  80u,
  8u,
  248u,
  248u,
  248u,
  2u,
  0u,
  1u,
  13u,
  15u,
  1u,
  0u,
  2u,
  0u,
  1u,
  1u,
  0u,
  2u,
  0u,
  1u,
  12u,
  0u,
  2u,
  1u,
  255u,
  10u,
  3u,
  232u,
  3u,
  232u,
  2u,
  0u,
  1u,
  13u,
  12u,
  0u,
  6u,
  1u,
  255u,
  10u,
  0u,
  180u,
  0u,
  180u,
  2u,
  0u,
  1u,
  13u,
  12u,
  0u,
  7u,
  1u,
  255u,
  10u,
  0u,
  100u,
  0u,
  100u,
  8u,
  248u,
  248u,
  248u,
  2u,
  0u,
  1u,
  10u,
  0u,
  80u,
  0u,
  80u,
  8u,
  248u,
  248u,
  248u,
  2u,
  0u,
  1u,
  13u,
  15u,
  12u,
  0u,
  2u,
  1u,
  0u,
  2u,
  0u,
  1u,
  13u,
  1u,
  0u,
  2u,
  0u,
  1u,
  12u,
  0u,
  2u,
  1u,
  255u,
  10u,
  3u,
  32u,
  3u,
  32u,
  2u,
  0u,
  1u,
  13u,
  12u,
  0u,
  6u,
  1u,
  255u,
  10u,
  0u,
  160u,
  0u,
  160u,
  2u,
  0u,
  1u,
  13u,
  12u,
  0u,
  7u,
  1u,
  255u,
  10u,
  0u,
  100u,
  0u,
  100u,
  8u,
  248u,
  248u,
  248u,
  2u,
  0u,
  1u,
  10u,
  0u,
  80u,
  0u,
  80u,
  8u,
  248u,
  248u,
  248u,
  2u,
  0u,
  1u,
  13u,
  15u,
  12u,
  0u,
  3u,
  1u,
  0u,
  2u,
  0u,
  1u,
  13u,
  1u,
  0u,
  2u,
  0u,
  1u,
  12u,
  0u,
  2u,
  1u,
  255u,
  10u,
  2u,
  88u,
  2u,
  88u,
  2u,
  0u,
  1u,
  13u,
  12u,
  0u,
  6u,
  1u,
  255u,
  10u,
  0u,
  140u,
  0u,
  140u,
  2u,
  0u,
  1u,
  13u,
  12u,
  0u,
  7u,
  1u,
  255u,
  10u,
  0u,
  100u,
  0u,
  100u,
  8u,
  248u,
  248u,
  248u,
  2u,
  0u,
  1u,
  10u,
  0u,
  80u,
  0u,
  80u,
  8u,
  248u,
  248u,
  248u,
  2u,
  0u,
  1u,
  13u,
  15u
};


const char SECTION(".rdata") aOpen[] = " open!! \n";  // 80012DD0
const char SECTION(".rdata") aClose[] = " close!! \n";  // 80012DDC
const char SECTION(".rdata") aDoorCloseD[] = "door:close %d\n";  // 80012DE8
const char SECTION(".rdata") aCancel[] = "cancel\n";  // 80012DF8
const char SECTION(".rdata") aDoorOpenD[] = "door:open %d\n";  // 80012E00
const char SECTION(".rdata") aSnakeDoorX[] = "Snake Door %X\n";  // 80012E10
const char SECTION(".rdata") aDoorOpencancel[] = "door:opencancel %d\n"; // 80012E20
const char SECTION(".rdata") aCloseDoorX[] = "close door %X\n";
const char SECTION(".rdata") aCloseDoorX_0[] = "CLOSE door %X\n";
const char SECTION(".rdata") aDoorC[] = "door.c";

const char SECTION(".rdata") aSgtrect3C[] = "sgtrect3.c";
int SECTION(".rdata") dword_80012E68[] = {0x7325, 0x68676973, 0x632E74, 0x6F6F6C62, 0x315F64, 0x6F6F6C62, 0x632E64, 0x12A00, 0x2FE0105, 0x80100, 0xCB0B0, 0xAFF0105, 0x64006400, 0xD010002, 0x105000C, 0x1E000AFF, 0xE8081E00, 0x2F8F8, 0xF0D01, 0x6C625F64, 0x2E646F6F, 0x63, 0x6374656B, 0x5F706168, 0x79657267, 0};
const char SECTION(".rdata") aDBloodrC[] = "d_bloodr.c";
char SECTION(".rdata") byte_80012EDC[] = {0,    0,    0};
char SECTION(".rdata") byte_80012EDF = 0;

const char SECTION(".rdata") byte_80012EE0[4] = {0xDC, 0x5, 0, 0};
const char SECTION(".rdata") aBullet_0[] = "bullet";
const char SECTION(".rdata") byte_80012EEC[4] = { '\xC8', '\0', '\xC8', '\0' };
const char SECTION(".rdata") byte_80012EF0[4] = { '\xC8', '\0', '\0', '\0' };
const char SECTION(".rdata") aClaymoreC[] ="claymore.c";
const char SECTION(".rdata") aSparkFl[] ="spark_fl";

const char SECTION(".rdata") aSparkC[] = "spark.c";
const char SECTION(".rdata") aRefrection6[] = "refrection6";
const char SECTION(".rdata") aStngrndC[] = "stngrnd.c";
int SECTION(".rdata") dword_80012F2C[] = {0x11F00, 0xC000105, 0x10A0400, 0x2F401F4, 0xC0D0100, 0x10A0700, 0x8F401F4, 0x2F0F0F0, 0xF0D0100};
int SECTION(".rdata") dword_80012F50[] = {0x11F00, 0xC000105, 0x20A0500, 0x2580258, 0xC0D0100, 0xA0900, 0x81E001E, 0x2EEEEEE, 0xF0D0100};
int SECTION(".rdata") dword_80012F74[] = {0x80075084, 0x80075098, 0x800750B0, 0x800750D4, 0x800750EC, 0x80075104, 0x8007511C};
const char SECTION(".rdata") aStgfdIoC[] = "stgfd_io.c";
const char SECTION(".rdata") aBullet[] = "bullet";
const char SECTION(".rdata") aBulletC[] = "bullet.c";
const char SECTION(".rdata") aEffect[] = "effect";
const char SECTION(".rdata") aChafgrndC[] = "chafgrnd.c";
const char SECTION(".rdata") aGoggles_0[] = "goggles";
const char SECTION(".rdata") aGoggleC[] = "goggle.c";
const char SECTION(".rdata") aGglmngC[] = "gglmng.c";
const char SECTION(".rdata") a02d[] = "%02d";
const char SECTION(".rdata") aLd[] = "%ld\n";
const char SECTION(".rdata") aScan[] = "SCAN";
const char SECTION(".rdata") aModeB[] = "MODE - B";
const char SECTION(".rdata") aModeA[] = "MODE - A";
const char SECTION(".rdata") aGglsightC[] = "gglsight.c";
const char SECTION(".rdata") aScnMaskC[] = "scn_mask.c";
const char SECTION(".rdata") aGoggles_1[] = "goggles";
const char SECTION(".rdata") aGoggleirC[] = "goggleir.c";
const char SECTION(".rdata") aDemothrdC[] = "demothrd.c";
const char SECTION(".rdata") aDemoFileS[] = "Demo file = \"%s\"\n";
const char SECTION(".rdata") aSNotFound[] = "\"%s\" not found\n";
const char SECTION(".rdata") aErrorInitializ[] = "Error:Initialize demo\n";
const char SECTION(".rdata") aPlaydemosound[] = "PlayDemoSound\n";
const char SECTION(".rdata") aCacheBufferCle[] = "Cache Buffer Cleared\n";
const char SECTION(".rdata") aCacheReadEnabl[] = "Cache Read Enable\n";
const char SECTION(".rdata") aNoloadModelSta[] = "Noload model ( Stage )\n";
const char SECTION(".rdata") aNoloadModelSce[] = "Noload model ( Scene = No.%d )\n";
const char SECTION(".rdata") aErrorInitContr[] = "Error init control ( Scene = No.%d )\n";
const char SECTION(".rdata") a16dO4a[] = "16d_o4a";
const char SECTION(".rdata") a16dO5a[] = "16d_o5a";
const char SECTION(".rdata") a16dO6a[] = "16d_o6a";
const char SECTION(".rdata") a16dO7a[] = "16d_o7a";
const char SECTION(".rdata") a16dO8a[] = "16d_o8a";
const char SECTION(".rdata") a16dO9a[] = "16d_o9a";
const char SECTION(".rdata") a16dO10a[] = "16d_o10a";
const char SECTION(".rdata") a16dO4b[] = "16d_o4b";
const char SECTION(".rdata") a16dO5b[] = "16d_o5b";
const char SECTION(".rdata") a16dO6b[] = "16d_o6b";
const char SECTION(".rdata") a16dO7b[] = "16d_o7b";
const char SECTION(".rdata") a16dO8b[] = "16d_o8b";
const char SECTION(".rdata") a16dO9b[] = "16d_o9b";
const char SECTION(".rdata") a16dO10b[] = "16d_o10b";
const char SECTION(".rdata") a16dO4c[] = "16d_o4c";
const char SECTION(".rdata") a16dO5c[] = "16d_o5c";
const char SECTION(".rdata") a16dO6c[] = "16d_o6c";
const char SECTION(".rdata") a16dO7c[] = "16d_o7c";
const char SECTION(".rdata") a16dO8c[] = "16d_o8c";
const char SECTION(".rdata") a16dO9c[] = "16d_o9c";
const char SECTION(".rdata") a16dO10c[] = "16d_o10c";
const char SECTION(".rdata") a02aR8[] = "02a_r8";
const char SECTION(".rdata") aMgrexw[] = "mgrexw";
const char SECTION(".rdata") aMgrexll[] = "mgrexll";
const char SECTION(".rdata") aMgrexrl[] = "mgrexrl";
const char SECTION(".rdata") aPitT[] = "pit_t";
const char SECTION(".rdata") aPitU[] = "pit_u";
const char SECTION(".rdata") aPitLiq[] = "pit_liq";
const char SECTION(".rdata") aRadarF1[] = "radar_f1";
const char SECTION(".rdata") aRadarF2[] = "radar_f2";
const char SECTION(".rdata") aRadarF3[] = "radar_f3";
const char SECTION(".rdata") aLHatch1[] = "l_hatch1";
const char SECTION(".rdata") aLHatch2[] = "l_hatch2";
const char SECTION(".rdata") aLHatch3[] = "l_hatch3";
const char SECTION(".rdata") aLHatch4[] = "l_hatch4";
const char SECTION(".rdata") aRHatch1[] = "r_hatch1";
const char SECTION(".rdata") aRHatch2[] = "r_hatch2";
const char SECTION(".rdata") aRHatch3[] = "r_hatch3";
const char SECTION(".rdata") aRHatch4[] = "r_hatch4";
const char SECTION(".rdata") aM1e1[] = "m1e1";
const char SECTION(".rdata") aM1e1demo[] = "m1e1demo";
const char SECTION(".rdata") aM1e1cl1[] = "m1e1cl1";
const char SECTION(".rdata") aM1e1cl2[] = "m1e1cl2";
const char SECTION(".rdata") aM1e1cl3[] = "m1e1cl3";
const char SECTION(".rdata") aM1e1cr1[] = "m1e1cr1";
const char SECTION(".rdata") aM1e1cr2[] = "m1e1cr2";
const char SECTION(".rdata") aM1e1cr3[] = "m1e1cr3";
const char SECTION(".rdata") aHind[] = "hind";
const char SECTION(".rdata") aHinddemo[] = "hinddemo";
const char SECTION(".rdata") aNull[] = "null";
const char SECTION(".rdata") aNoloadModelNul[] = "Noload model ( null.kmd )\n";
const char SECTION(".rdata") aErrorInitContr_0[] = "Error init control ( null.kmd )\n";
int SECTION(".rdata") jpt_8007AECC[] = {0x8007AED4, 0x8007AEFC, 0x8007AF04, 0x8007AF04, 0x8007AFB8, 0x8007AFE0, 0x8007B014, 0x8007B048, 0x8007B050, 0x8007B0A4, 0x8007B10C, 0x8007B114, 0x8007B170, 0x8007B178, 0x8007B2B4, 0x8007B340, 0x8007B3C4, 0x8007B3CC, 0x8007B498, 0x8007B498, 0x8007B498, 0x8007B66C, 0x8007B674, 0x8007B7A8, 0x8007B89C, 0x8007B928, 0x8007B950, 0x8007B994, 0x8007BA64, 0x8007B498, 0x8007BAA4, 0x8007BB10, 0x8007BBDC, 0x8007BC24, 0x8007BC68, 0x8007BCF8, 0x8007BD1C, 0x8007BD40, 0x8007BDF0, 0x8007BDF8, 0x8007BE58, 0x8007BF3C, 0x8007C030, 0x8007C09C, 0x8007C0E8, 0x8007C134, 0x8007C1D8, 0x8007C200, 0x8007C224, 0x8007C22C, 0x8007C254, 0x8007C27C, 0x8007C348, 0x8007C8D8, 0x8007C3AC, 0x8007C430, 0x8007C438, 0x8007C4DC, 0x8007C520, 0x8007C58C, 0x8007C61C, 0x8007C6A8, 0x8007C7DC, 0x8007C8D8, 0x8007C90C, 0x8007C930, 0x8007C948, 0x8007CA4C, 0x8007CBB8, 0x8007CBEC, 0x8007CC18, 0x8007CC44, 0x8007CC6C, 0x8007CCF4};
int SECTION(".rdata") dword_8001345C[] = {0x12700, 0xCFE0105, 0xFF010500, 0x64000A, 0xF1F10864, 0x10002F1, 0x5000C0D, 0x10AFF01, 0x82C012C, 0x2E2E2E2, 0xF0D0100, 0x24A00, 0x1200007, 0x5000CFE, 0x2FF01, 0xC0D01, 0x8FF010A, 0x2FAFAFA, 0xF0D0100, 0xCFE01, 0x2C010A04, 0xFF012C01, 0xD010002, 0xA0A000C, 0x46004600, 0x2FF01, 0xC0D01, 0xAFF010A, 0x50005000, 0xF0F0F008, 0xD010002, 0xF, 0x12C00, 0xCFE0105, 0xFF010500, 0xD010002, 0x105000C, 0x5000AFF, 0x20500, 0xC0D01, 0x8FF010F, 0xAF0F0F0, 0x5000500, 0xD010002, 0xF, 0x34900, 0x1E0009, 0xCFE0138, 0x20400, 0xC0D01, 0xECEC0804, 0x10002EC, 0xFE010F0D, 0xFC18FC0A, 0x4000C18, 0xD010002, 0x804000C, 0x2ECECEC, 0xF0D0100, 0xFB0AFE01, 0xC50FB50, 0x20400, 0xC0D01, 0xECEC0804, 0x10002EC, 0xF0D};
const char SECTION(".rdata") aSoundLaunchArg[] = "SOUND_LAUNCH(argc:%d)\n";
const char SECTION(".rdata") aArgDS[] = "ARG%d:[%s]\n";
const char SECTION(".rdata") aStartTaskSdmai[] = "Start Task:SdMain\n";
const char SECTION(".rdata") aBgmTerminate[] = "***BGM Terminate***\n";
int SECTION(".rdata") jpt_80081B38[] = {0x80081B40, 0x80081B78, 0x80081B78, 0x80081B78, 0x80081B78, 0x80081BA0, 0x80081B88};
const char SECTION(".rdata") aStartTaskSdint[] = "Start Task:SdInt\n";
const char SECTION(".rdata") aBlankDataAddrX[] = "blank_data_addr=%x\n";
const char SECTION(".rdata") aSpuWaveStartPt[] = "spu_wave_start_ptr=%x\n";
const char SECTION(".rdata") aSpuBgmStartPtr[] = "spu_bgm_start_ptr_r=%x\n";
const char SECTION(".rdata") aSpuBufferOver[] = "SPU Buffer Over!!\n";
const char SECTION(".rdata") aSpuBgmStartPtr_0[] = "spu_bgm_start_ptr_l=%x\n";
const char SECTION(".rdata") aSpuReverbBuffe[] = "SPU Reverb Buffer Over!!\n";
const char SECTION(".rdata") aSoundErrorSpuO[] = "SOUND ERROR:SPU OFF ENV ON(STR_TRACK_R=%x)\n";
const char SECTION(".rdata") aSoundErrorSpuO_0[] = "SOUND ERROR:SPU OFF ENV ON(STR_TRACK_L=%x)\n";
const char SECTION(".rdata") aSngDataX[] = "sng_data %X\n";
const char SECTION(".rdata") aWaveHeaderX[] = "wave_header %X\n";
const char SECTION(".rdata") aVoiceTblX[] = "voice_tbl %X\n";
const char SECTION(".rdata") aSeHeaderX[] = "se_header %X\n";
const char SECTION(".rdata") aSeDataX[] = "se_data %X\n";
const char SECTION(".rdata") aCdloadBufXXX[] = "CDLOAD_BUF %X %X %X\n";
const char SECTION(".rdata") aStrHeaderX[] = "str_header %X\n";
const char SECTION(".rdata") aCanceledStrFad[] = "Canceled STR FadeOut(%x:%x:%x)";
const char SECTION(".rdata") aStreamFilePosE[] = "Stream:File Pos Error\n";
const char SECTION(".rdata") aStartstreamXVo[] = "StartStream(%x:vol=%x)\n";
int SECTION(".rdata") jpt_80082674[] = {0x8008272C, 0x8008272C, 0x8008267C, 0x8008268C, 0x800826CC};
const char SECTION(".rdata") aSoundStreaming[] = "\nSOUND STREAMING ERROR:NO LAST LEFT DATA\n";
const char SECTION(".rdata") aStrUnplaySizeX[] = "str_unplay_size=%x\n";
const char SECTION(".rdata") asc_800137E0[] = "*";
int SECTION(".rdata") jpt_80082820[] = {0x80082828, 0x80082A28, 0x80082BC8, 0x80082D20, 0x800832BC, 0x80083358};
const char SECTION(".rdata") aErrorSeFileAlr[] = "ERROR:SE File Already Opened.\n";
const char SECTION(".rdata") aLoadsefileFile[] = "LoadSeFile:File Open Error(%x)\n";
const char SECTION(".rdata") aErrorWaveFileA[] = "ERROR:Wave File Already Opened.\n";
const char SECTION(".rdata") aLoadwavefileFi[] = "LoadWaveFile:File Open Error(%x)\n";
const char SECTION(".rdata") aSupOffsetXSize[] = "SUP OFFSET=%x:SIZE=%x\n";
const char SECTION(".rdata") aSrcXDstX[] = "    SRC=%x:DST=%x\n";
const char SECTION(".rdata") aBinOffsetX[] = "BIN OFFSET=%x\n";
const char SECTION(".rdata") aSpuOffsetXSize[] = "SPU OFFSET=%x:SIZE=%x\n";
const char SECTION(".rdata") aCompleteLoadSe[] = "Complete Load Se:%x\n";
const char SECTION(".rdata") aSdSngdataloadi[] = "SD_SngDataLoadInit\n";
const char SECTION(".rdata") aLoadinitD[] = "LoadInit %d\n";
const char SECTION(".rdata") asc_80013914[] = "$";
const char SECTION(".rdata") aSdWavLoadBufOv[] = "!!! SD WAV LOAD BUF OVER !!!\n";
const char SECTION(".rdata") aUnloadD[] = "unload %d\n";
const char SECTION(".rdata") aSngcodeX[] = "SngCode=%x\n";
const char SECTION(".rdata") aSongpauseon[] = "SongPauseOn\n";
const char SECTION(".rdata") aSongpauseoff[] = "SongPauseOff\n";
const char SECTION(".rdata") aSongfadein[] = "SongFadein\n";
const char SECTION(".rdata") aSongfadeoutPau[] = "SongFadeout&Pause\n";
const char SECTION(".rdata") aSongfadeoutSto[] = "SongFadeout&Stop\n";
const char SECTION(".rdata") aSongkaihimode[] = "SongKaihiMode\n";
const char SECTION(".rdata") aSongsyukanmode[] = "SongSyukanMode On\n";
const char SECTION(".rdata") aSongsyukanmode_0[] = "SongSyukanMode Off\n";
const char SECTION(".rdata") aSongstop[] = "SongStop\n";
const char SECTION(".rdata") aErrorSngPlayCo[] = "ERROR:SNG PLAY CODE(%x/%x)\n";
const char SECTION(".rdata") aSngStatusX[] = "sng_status=%x\n";
const char SECTION(".rdata") aSamesonghasalr[] = "SameSongHasAlreadyPlayed\n";
const char SECTION(".rdata") aSoundWorkIsBro[] = "*** SOUND WORK IS BROKEN !!! ***\n";
const char SECTION(".rdata") aSongEndXX[] = "*** song_end:%x -> %x        ***\n";
const char SECTION(".rdata") aSngFadeoutStar[] = "SNG FADEOUT START(status=%x)\n";
const char SECTION(".rdata") aSngFadeoutCanc[] = "SNG FADEOUT CANCELED(status=%x)\n";
const char SECTION(".rdata") aLoadsngdataFil[] = "LoadSngData:File Open Error(%x)\n";
const char SECTION(".rdata") aCompletedloads[] = "CompletedLoadSong(%x)\n";
const char SECTION(".rdata") aXaSoundStart[] = "***XA Sound Start***\n";
const char SECTION(".rdata") aXaSoundStop[] = "***XA Sound Stop***\n";
const char SECTION(".rdata") aSdcodeX[] = "SdCode=%x\n";
const char SECTION(".rdata") aToomuchbgmsoun[] = "***TooMuchBGMSoundCode(%x)***\n";
const char SECTION(".rdata") aSdsetLastStrea[] = "SdSet:Last Stream Not Terminated.(status=%x)\n";
const char SECTION(".rdata") aSdsetSameStrea[] = "SdSet:Same Stream is Already Played.(code=%x)\n";
const char SECTION(".rdata") aStrFoS[] = "*** STR FO(S) ***\n";
const char SECTION(".rdata") aStrFoM[] = "*** STR FO(M) ***\n";
const char SECTION(".rdata") aStrFoL[] = "*** STR FO(L) ***\n";
const char SECTION(".rdata") aStrFoLl[] = "*** STR FO(LL) ***\n";
const char SECTION(".rdata") aStrFiMAtNextSt[] = "*** STR FI(M) at Next STR ***\n";
const char SECTION(".rdata") aStrFiMStart[] = "*** STR FI(M) Start ***\n";
const char SECTION(".rdata") aErrStrFiM[] = "*** ERR:STR FI(M) ***\n";
const char SECTION(".rdata") aStrFiLAtNextSt[] = "*** STR FI(L) at Next STR***\n";
const char SECTION(".rdata") aStrFiLStart[] = "*** STR FI(L) Start ***\n";
const char SECTION(".rdata") aErrStrFiL[] = "*** ERR:STR FI(L) ***\n";
const char SECTION(".rdata") aStrFoSStop[] = "*** STR FO(S)+STOP ***\n";
const char SECTION(".rdata") aStrFoMStop[] = "*** STR FO(M)+STOP ***\n";
const char SECTION(".rdata") aStrFoLStop[] = "*** STR FO(L)+STOP ***\n";
const char SECTION(".rdata") aStrFoLlStop[] = "*** STR FO(LL)+STOP ***\n";
int SECTION(".rdata") dword_80013D10[] = {0x3F3F3F, 0xDDA1AAA5, 0xDDA1D0A5, 0xEDA5D5A5, 0xDDA1, 0xD7A5B3A5, 0xEDA5, 0xF3CCBDCD, 0xE1CEBFCC, 0, 0xECA5D6A5, 0xAFA5DDA1, 0xA4A5DDA5, 0xC8A5F3A5, 0};
int SECTION(".rdata") dword_80013D4C[] = {0xB9A5B7A5, 0xE0A5C6A5, 0xDDA1B3A5, 0xEBA5, 0xDDA1C7A5, 0xD0A5BFA5, 0xA8A5B9A5, 0xDDA1E9A5, 0};
int SECTION(".rdata") dword_80013D70[] = {0xE1CEBFCC, 0xB9A5D0A5, 0xE9A5A8A5, 0xDDA1, 0xC8A5B9A5, 0xFEBBA2A5, 0xC9A5A2A5, 0xB9A5ECA5, 0xE9A5A8A5, 0xDDA1, 0xDDA1EDA5, 0xFEBBC9A5, 0xC9A5A2A5, 0xB9A5ECA5, 0xE9A5A8A5, 0xDDA1, 0x53424C54, 0};
const char SECTION(".rdata") aTlbl[] = "TLBL";
int SECTION(".rdata") dword_80013DC0[] = {0x646F4D, 0xF4C9B0B3, 0xEAA4E4B3, 0xDFA4FEB9, 0};
const char SECTION(".rdata") aTaskStartDX[] = "TASK START: %d %X\n";
const char SECTION(".rdata") aAssertionFaled[] = "assertion faled : %s line %d : Task %d\n";
const char SECTION(".rdata") aMtsNewC[] = "mts_new.c";
const char SECTION(".rdata") aTaskStartBody[] = "task_start_body";
const char SECTION(".rdata") asc_80013E2C[] = "\n";
const char SECTION(".rdata") aGetNewVblContr[] = "get_new_vbl_control_table";
const char SECTION(".rdata") aWaitvblD[] = "waitvbl %d";
const char SECTION(".rdata") aTaskCreateXX[] = "task_create %x %x";
const char SECTION(".rdata") aSendDstD[] = "send dst %d";
const char SECTION(".rdata") aSendStateDeadD[] = "send state DEAD %d";
const char SECTION(".rdata") aIsendDstD[] = "isend dst %d";
const char SECTION(".rdata") aIsendStateDead[] = "isend state DEAD %d";
const char SECTION(".rdata") aRcvSrcD[] = "rcv src %d";
const char SECTION(".rdata") aRcvStateDeadD[] = "rcv state DEAD %d";
const char SECTION(".rdata") aRcvCallerD[] = "rcv caller %d";
const char SECTION(".rdata") aRcvSpDStateD[] = "rcv sp %d state %d";
const char SECTION(".rdata") aRcvSpMessageX[] = "rcv sp message %X";
const char SECTION(".rdata") aSendTD[] = "send t %d";
const char SECTION(".rdata") aRcvSpDMessageX[] = "rcv sp %d message %x";
const char SECTION(".rdata") aRecvSrcD[] = "RECV ?? SRC %d";
const char SECTION(".rdata") aWupDeadD[] = "wup DEAD %d";
const char SECTION(".rdata") aMultiTaskSched[] = "Multi Task Scheduler for PSX ver2.02 %s %s\n";
const char SECTION(".rdata") aJul111998[] = "Jul 11 1998";
const char SECTION(".rdata") a221633[] = "22:16:33";
const char SECTION(".rdata") aProgramBottomX[] = "PROGRAM BOTTOM %X\n";
const char SECTION(".rdata") aBootTasknrD[] = "boot tasknr %d";
const char SECTION(".rdata") aSystemClientD[] = "system client %d";
const char SECTION(".rdata") aTaskDStart[] = "TASK %d START:";
const char SECTION(".rdata") aTaskDAlreadyEx[] = "TASK %d already exist\n";
const char SECTION(".rdata") aSystemExitDead[] = "system exit DEAD %d";
const char SECTION(".rdata") aSystemExitCall[] = "system exit caller %d";
const char SECTION(".rdata") aTaskExit[] = "TASK EXIT";
const char SECTION(".rdata") aSystemWrongCod[] = "system wrong code %d";
const char SECTION(".rdata") aMtsStaTskServe[] = "mts_sta_tsk server %d";
const char SECTION(".rdata") aMtsExtTsk[] = "mts_ext_tsk";
const char SECTION(".rdata") aPending[] = "Pending";
const char SECTION(".rdata") aWaitvbl[] = "WaitVBL";
const char SECTION(".rdata") aSleeping[] = "Sleeping";
const char SECTION(".rdata") aReady[] = "Ready";
const char SECTION(".rdata") aReceiving[] = "Receiving";
const char SECTION(".rdata") aSending[] = "Sending";
const char SECTION(".rdata") aProcessList[] = "\nProcess list\n";
const char SECTION(".rdata") aC[] = "%c";
const char SECTION(".rdata") aTask02dSp04dUs[] = "Task %02d SP %04d USE %04d/%04d";
const char SECTION(".rdata") aTask02dSpUse[] = " Task %02d SP ---- USE ----/----";
int SECTION(".rdata") dword_800140F0 = 0x732520;
const char SECTION(".rdata") aRunning[] = "Running";
const char SECTION(".rdata") aD_0[] = " %d\n";
const char SECTION(".rdata") aTaskState08x[] = "TASK STATE = %08X\n";
const char SECTION(".rdata") aVblWaitCue[] = "VBL wait cue";
const char SECTION(".rdata") a02dD[] = " : %02d (%d)";
const char SECTION(".rdata") aTickCountD[] = "Tick count %d\n\n";
const char SECTION(".rdata") aCdinitInitFail[] = "CdInit: Init failed\n";
int SECTION(".rdata") dword_crap9[] = {0, 0};
const char SECTION(".rdata") aNone_0[] = "none";
int SECTION(".rdata") dword_crap10[] = {0, 0};
const char SECTION(".rdata") aCdlreads[] = "CdlReadS";
const char SECTION(".rdata") aCdlseekp[] = "CdlSeekP";
const char SECTION(".rdata") aCdlseekl[] = "CdlSeekL";
const char SECTION(".rdata") aCdlgettd[] = "CdlGetTD";
const char SECTION(".rdata") aCdlgettn[] = "CdlGetTN";
const char SECTION(".rdata") aCdlgetlocp[] = "CdlGetlocP";
const char SECTION(".rdata") aCdlgetlocl[] = "CdlGetlocL";
int SECTION(".rdata") dword_800141CC[] = {0x3F, 0x536C6443, 0x6F6D7465, 0x6564, 0x536C6443, 0x69667465, 0x7265746C, 0};
const char SECTION(".rdata") aCdldemute[] = "CdlDemute";
const char SECTION(".rdata") aCdlmute[] = "CdlMute";
const char SECTION(".rdata") aCdlreset[] = "CdlReset";
const char SECTION(".rdata") aCdlpause[] = "CdlPause";
const char SECTION(".rdata") aCdlstop[] = "CdlStop";
const char SECTION(".rdata") aCdlstandby[] = "CdlStandby";
const char SECTION(".rdata") aCdlreadn[] = "CdlReadN";
const char SECTION(".rdata") aCdlbackward[] = "CdlBackward";
const char SECTION(".rdata") aCdlforward[] = "CdlForward";
const char SECTION(".rdata") aCdlplay[] = "CdlPlay";
const char SECTION(".rdata") aCdlsetloc[] = "CdlSetloc";
const char SECTION(".rdata") aCdlnop[] = "CdlNop";
const char SECTION(".rdata") aCdlsync[] = "CdlSync";
const char SECTION(".rdata") aDiskerror_0[] = "DiskError";
const char SECTION(".rdata") aDataend[] = "DataEnd";
const char SECTION(".rdata") aAcknowledge[] = "Acknowledge";
const char SECTION(".rdata") aComplete_0[] = "Complete";
const char SECTION(".rdata") aDataready[] = "DataReady";
const char SECTION(".rdata") aNointr[] = "NoIntr";
const char SECTION(".rdata") aCdTimeout[] = "CD timeout: ";
const char SECTION(".rdata") aSSSyncSReadyS[] = "%s:(%s) Sync=%s, Ready=%s\n";
const char SECTION(".rdata") aDiskerror[] = "DiskError: ";
const char SECTION(".rdata") aComSCode02x02x[] = "com=%s,code=(%02x:%02x)\n";
const char SECTION(".rdata") aCdromUnknownIn[] = "CDROM: unknown intr";
const char SECTION(".rdata") aD_1[] = "(%d)\n";
int SECTION(".rdata") dword_crap11 = 0;
int SECTION(".rdata") jpt_8008D13C[] = {0x8008D290, 0x8008D244, 0x8008D144, 0x8008D310, 0x8008D390};
const char SECTION(".rdata") aCdSync[] = "CD_sync";
const char SECTION(".rdata") aCdReady[] = "CD_ready";
const char SECTION(".rdata") aS[] = "%s...\n";
const char SECTION(".rdata") aSNoParam[] = "%s: no param\n";
const char SECTION(".rdata") aCdCw[] = "CD_cw";
const char SECTION(".rdata") aIdBiosCV186199[] = "$Id: bios.c,v 1.86 1997/03/28 07:42:42 makoto Exp yos $";
const char SECTION(".rdata") aCdInit[] = "CD_init:";
const char SECTION(".rdata") aAddr08x[] = "addr=%08x\n";
const char SECTION(".rdata") aCdDatasync[] = "CD_datasync";
int SECTION(".rdata") dword_crap12[] = {0, 0, 0};
const char SECTION(".rdata") a0123456789abcd[] = "0123456789ABCDEF";
const char SECTION(".rdata") a0123456789abcd_0[] = "0123456789abcdef";
int SECTION(".rdata") jpt_8008EB30[] = {0x8008EB50, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008EE08, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008EF20, 0x8008EB7C, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008EB38, 0x8008EB7C, 0x8008F000, 0x8008F000, 0x8008EB44, 0x8008F000, 0x8008EFCC, 0x8008ECF4, 0x8008EDF4, 0x8008F000, 0x8008F000, 0x8008EF40, 0x8008F000, 0x8008EBD4, 0x8008F000, 0x8008F000, 0x8008EE14, 0};
const char SECTION(".rdata") aNull_0[] = "<NULL>";
int SECTION(".rdata") dword_crap13[] = {0, 0};
const char SECTION(".rdata") aIdSysCV1140199[] = "$Id: sys.c,v 1.140 1998/01/12 07:52:27 noda Exp yos $";
const char SECTION(".rdata") aResetgraphJtb0[] = "ResetGraph:jtb=%08x,env=%08x\n";
const char SECTION(".rdata") aResetgraphD[] = "ResetGraph(%d)...\n";
const char SECTION(".rdata") aSetgraphdebugL[] = "SetGraphDebug:level:%d,type:%d reverse:%d\n";
const char SECTION(".rdata") aSetgrapqueD[] = "SetGrapQue(%d)...\n";
const char SECTION(".rdata") aDrawsynccallba[] = "DrawSyncCallback(%08x)...\n";
const char SECTION(".rdata") aSetdispmaskD[] = "SetDispMask(%d)...\n";
const char SECTION(".rdata") aDrawsyncD[] = "DrawSync(%d)...\n";
const char SECTION(".rdata") aSBadRect[] = "%s:bad RECT";
const char SECTION(".rdata") aDDDD[] = "(%d,%d)-(%d,%d)\n";
const char SECTION(".rdata") aS_0[] = "%s:";
const char SECTION(".rdata") aClearimage[] = "ClearImage";
const char SECTION(".rdata") aClearimage2[] = "ClearImage2";
const char SECTION(".rdata") aLoadimage[] = "LoadImage";
const char SECTION(".rdata") aStoreimage[] = "StoreImage";
const char SECTION(".rdata") aMoveimage[] = "MoveImage";
const char SECTION(".rdata") aClearotag08xD[] = "ClearOTag(%08x,%d)...\n";
const char SECTION(".rdata") aClearotagr08xD[] = "ClearOTagR(%08x,%d)...\n";
const char SECTION(".rdata") aDrawotag08x[] = "DrawOTag(%08x)...\n";
const char SECTION(".rdata") aPutdrawenv08x[] = "PutDrawEnv(%08x)...\n";
const char SECTION(".rdata") aDrawotagenv08x[] = "DrawOTagEnv(%08x,&08x)...\n";
const char SECTION(".rdata") aPutdispenv08x[] = "PutDispEnv(%08x)...\n";
const char SECTION(".rdata") aGpuTimeoutQueD[] = "GPU timeout:que=%d,stat=%08x,chcr=%08x,madr=%08x\n";
const char SECTION(".rdata") aLoadimage2[] = "LoadImage2";
const char SECTION(".rdata") aSpuTOS[] = "SPU:T/O [%s]\n";
const char SECTION(".rdata") aWaitReset[] = "wait (reset)";
const char SECTION(".rdata") aWaitWrdyHL[] = "wait (wrdy H -> L)";
const char SECTION(".rdata") aWaitDmafClearW[] = "wait (dmaf clear/W)";
int SECTION(".rdata") dword_crap14[] = {0, 0};
const char SECTION(".rdata") aSpuTOS_0[] = "SPU:T/O [%s]\n";
const char SECTION(".rdata") aWaitIrqOn[] = "wait (IRQ/ON)";
const char SECTION(".rdata") aWaitIrqOff[] = "wait (IRQ/OFF)";
int SECTION(".rdata") jpt_80097088[] = {0x800970C8, 0x80097090, 0x80097098, 0x800970A0, 0x800970A8, 0x800970B0, 0x800970B8, 0x800970C0};
int SECTION(".rdata") jpt_80097148[] = {0x80097188, 0x80097150, 0x80097158, 0x80097160, 0x80097168, 0x80097170, 0x80097178, 0x80097180};
int SECTION(".rdata") jpt_8009764C[] = {0x80097654, 0x8009765C, 0x80097664, 0x8009766C, 0x80097674, 0x8009767C, 0x80097684, 0};
int SECTION(".rdata") jpt_8009772C[] = {0x80097734, 0x8009773C, 0x80097744, 0x8009774C, 0x80097754, 0x8009775C, 0x80097764, 0};
const char SECTION(".rdata") aVsyncTimeout[] = "VSync: timeout\n";
const char SECTION(".rdata") aIdIntrCV175199[] = "$Id: intr.c,v 1.75 1997/02/07 09:00:36 makoto Exp $";
const char SECTION(".rdata") aUnexpectedInte[] = "unexpected interrupt(%04x)\n";
const char SECTION(".rdata") aIntrTimeout04x[] = "intr timeout(%04x:%04x)\n";
int SECTION(".rdata") dword_crap15 = 0;
const char SECTION(".rdata") aDmaBusErrorCod[] = "DMA bus error: code=%08x\n";
const char SECTION(".rdata") aMadrD08x[] = "MADR[%d]=%08x\n";
int SECTION(".rdata") dword_crap16 = 0;
int SECTION(".rdata") jpt_8009A4F4[] = {0x8009A4FC, 0x8009A508, 0x8009A514, 0x8009A520, 0x8009A52C, 0, 0, 0};
