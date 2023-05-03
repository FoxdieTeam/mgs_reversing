#include "linker.h"

const char SECTION(".rdata") aTotalD[] = "TOTAL %d\n";
const char SECTION(".rdata") aClipD[] = "CLIP %d\n";
const char SECTION(".rdata") aXDYD[] = "x %d y %d\n";
const char SECTION(".rdata") aWDHD[] = "w %d h %d\n";
const char SECTION(".rdata") aWrongRubiCodeX[] = "Wrong rubi code %x\n";
const char SECTION(".rdata") aNoMemoryForSav[] = "NO MEMORY FOR SAVE TEX\n";
const char SECTION(".rdata") aNoFaceData[] = "NO_FACE_DATA\n";
const char SECTION(".rdata") aFrameNumD[] = "frame num %d\n";
const char SECTION(".rdata") aSetCharaCodeD[] = "set chara code %d\n";
const char SECTION(".rdata") aAnimeCharaDCod[] = "ANIME CHARA %d CODE %d\n";
const char SECTION(".rdata") aVoxcodeX[] = "voxcode %X\n";
const char SECTION(".rdata") aIllegalCodeX[] = "illegal code %x\n";
const char SECTION(".rdata") aSetDS[] = "set %d %s\n";
const char SECTION(".rdata") aBlockExecError[] = "block exec error\n";
const char SECTION(".rdata") aNoMemoryForFac[] = "NO MEMORY FOR FACE %d\n";
const char SECTION(".rdata") aFaceDataNumD[] = "face data num %d\n";
const char SECTION(".rdata") aNoMemoryForSta[] = "NO MEMORY FOR STACK\n";
const char SECTION(".rdata") aNoMemory[] = "no memory\n";
int        SECTION(".rdata") dword_crap6 = 0;
