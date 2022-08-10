#include "linker.h"
#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

const char SECTION(".rdata") aBullet[] = "bullet"; // 80012F9C
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
const int  SECTION(".rdata") jpt_80013334[] = {
     0x8007AED4, 0x8007AEFC, 0x8007AF04, 0x8007AF04, 0x8007AFB8, 0x8007AFE0, 0x8007B014, 0x8007B048, 0x8007B050,
     0x8007B0A4, 0x8007B10C, 0x8007B114, 0x8007B170, 0x8007B178, 0x8007B2B4, 0x8007B340, 0x8007B3C4, 0x8007B3CC,
     0x8007B498, 0x8007B498, 0x8007B498, 0x8007B66C, 0x8007B674, 0x8007B7A8, 0x8007B89C, 0x8007B928, 0x8007B950,
     0x8007B994, 0x8007BA64, 0x8007B498, 0x8007BAA4, 0x8007BB10, 0x8007BBDC, 0x8007BC24, 0x8007BC68, 0x8007BCF8,
     0x8007BD1C, 0x8007BD40, 0x8007BDF0, 0x8007BDF8, 0x8007BE58, 0x8007BF3C, 0x8007C030, 0x8007C09C, 0x8007C0E8,
     0x8007C134, 0x8007C1D8, 0x8007C200, 0x8007C224, 0x8007C22C, 0x8007C254, 0x8007C27C, 0x8007C348, 0x8007C8D8,
     0x8007C3AC, 0x8007C430, 0x8007C438, 0x8007C4DC, 0x8007C520, 0x8007C58C, 0x8007C61C, 0x8007C6A8, 0x8007C7DC,
     0x8007C8D8, 0x8007C90C, 0x8007C930, 0x8007C948, 0x8007CA4C, 0x8007CBB8, 0x8007CBEC, 0x8007CC18, 0x8007CC44,
     0x8007CC6C, 0x8007CCF4};
const int SECTION(".rdata") dword_8001345C[] = {
    0x12700,    0xCFE0105,  0xFF010500, 0x64000A,   0xF1F10864, 0x10002F1, 0x5000C0D, 0x10AFF01, 0x82C012C,  0x2E2E2E2,
    0xF0D0100,  0x24A00,    0x1200007,  0x5000CFE,  0x2FF01,    0xC0D01,   0x8FF010A, 0x2FAFAFA, 0xF0D0100,  0xCFE01,
    0x2C010A04, 0xFF012C01, 0xD010002,  0xA0A000C,  0x46004600, 0x2FF01,   0xC0D01,   0xAFF010A, 0x50005000, 0xF0F0F008,
    0xD010002,  0xF,        0x12C00,    0xCFE0105,  0xFF010500, 0xD010002, 0x105000C, 0x5000AFF, 0x20500,    0xC0D01,
    0x8FF010F,  0xAF0F0F0,  0x5000500,  0xD010002,  0xF,        0x34900,   0x1E0009,  0xCFE0138, 0x20400,    0xC0D01,
    0xECEC0804, 0x10002EC,  0xFE010F0D, 0xFC18FC0A, 0x4000C18,  0xD010002, 0x804000C, 0x2ECECEC, 0xF0D0100,  0xFB0AFE01,
    0xC50FB50,  0x20400,    0xC0D01,    0xECEC0804, 0x10002EC,  0xF0D};
const char SECTION(".rdata") aSoundLaunchArg[] = "SOUND_LAUNCH(argc:%d)\n";
const char SECTION(".rdata") aArgDS[] = "ARG%d:[%s]\n";
const char SECTION(".rdata") aStartTaskSdmai[] = "Start Task:SdMain\n";
const char SECTION(".rdata") aBgmTerminate[] = "***BGM Terminate***\n";


// For SdMain_80081A18
//const int  SECTION(".rdata") jpt_800135B4[] = {0x80081B40, 0x80081B78, 0x80081B78, 0x80081B78,
//                                               0x80081B78, 0x80081BA0, 0x80081B88};
