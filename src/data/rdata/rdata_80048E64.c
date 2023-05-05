#include "linker.h"
#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

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
const int  SECTION(".rdata") dword_800122A8[] = {0x64826D81, 0x6E817782, 0}; // shift_jis: "［ＥＸ］"
const int  SECTION(".rdata") dword_800122B4[] = {0x67826D81, 0x6E816382, 0}; // shift_jis: "［ＨＤ］"
const int  SECTION(".rdata") dword_800122C0[] = {0x6D826D81, 0x6E816C82, 0}; // shift_jis: "［ＮＭ］"
const int  SECTION(".rdata") dword_800122CC[] = {0x64826D81, 0x6E817982, 0}; // shift_jis: "［ＥＺ］"
const int  SECTION(".rdata") dword_800122D8[] = {0x75826D81, 0x6E816482, 0}; // shift_jis: "［ＶＥ］"
const char SECTION(".rdata") aSSSSSS[] = "%s%s%s%s%s%s";
const int  SECTION(".rdata") dword_800122F4[] = {0x66826C82, 0xE7817282, 0}; // shift_jis: "ＭＧＳ∫"
const char SECTION(".rdata") aSaveData[] = "SAVE DATA";
