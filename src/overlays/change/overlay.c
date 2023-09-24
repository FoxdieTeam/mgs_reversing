#include "Onoda/change/change.h"
#include "libgcl/hash.h"
#include "libgcl/libgcl.h"

const GCL_ActorTableEntry OverlayCharas[] = {
    { 0xF722, NewChange_800C455C },
    { 0, 0 }
};

const int dword_800C3218 = 1;
const int dword_800C321C = 0x00be00a0;
const int dword_800C3220 = 26425;
const int dword_800C3224 = 1;
const int dword_800C3228 = 0xD200A0;
const int dword_800C322C = 26425;
const int dword_800C3230 = 1;
const int dword_800C3234 = 0xBE00A0;
const int dword_800C3238 = 26425;
const int dword_800C323C = 1;
const int dword_800C3240 = 0xBE00A0;
const int dword_800C3244 = 26425;
const int dword_800C3248 = 1;
const int dword_800C324C = 0xBE00A0;
const int dword_800C3250 = 26425;
const int dword_800C3254 = 1;
const int dword_800C3258 = 0xBE00A0;
const int dword_800C325C = 26425;
const char byte_800C3260 = -1;
const char byte_800C3261 = 0;
const char byte_800C3262 = 1;
const char byte_800C3263 = 0;
const int dword_800C3264 = -0xFFFF00;
const int dword_800C3268 = 0x1C7350;
const int dword_800C326C = 0x3100000;
const int dword_800C3270 = 50397185;
const int dword_800C3274 = 83951623;
const int dword_800C3278 = 50397954;
const int dword_800C327C = 83951638;
const int dword_800C3280 = 50397454;
const int dword_800C3284 = 50594073;
const int dword_800C3288 = 50397195;
const int dword_800C328C = 50397187;
const int dword_800C3290 = 50463001;
const int dword_800C3294 = 83951625;
const int  dword_800C3298 = 0x1F801800;
const int  dword_800C329C = 0x1F801801;
const int  dword_800C32A0 = 0x1F801802;
const int  dword_800C32A4 = 0x1F801803;
const char byte_800C32A8 = 0;
const char byte_800C32A9 = 0;
const char byte_800C32AA = 0;
const int dword_800C32AB = 0;
const char byte_800C32AF = 0;
const char byte_800C32B0 = 0;
const char byte_800C32B1 = 0;
const int dword_800C32B2 = 0;
const short word_800C32B6 = 0;
const char byte_800C32BA = 6;
const int __attribute__ ((aligned (1))) dword_800C32BB = 302648325;
const int __attribute__ ((aligned (1))) dword_800C32BF = 504633359;
const int __attribute__ ((aligned (1))) dword_800C32C3 = 673063705;
const int __attribute__ ((aligned (1))) dword_800C32C7 = 824585506;
const int __attribute__ ((aligned (1))) dword_800C32CB = 942421289;
const int __attribute__ ((aligned (1))) dword_800C32CF = 1026636591;
const char byte_800C32D3 = '3';
const short word_800C32D4 = 13374;
const char byte_800C32D6 = 63;
const char byte_800C32D7 = '5';
const char byte_800C32D8 = 0x40;
const int __attribute__ ((aligned (1))) dword_800C32D9 = 54;
const int dword_800C32DD = 0;
const int dword_800C32E1 = 0;

const short met_logo_lines_800C32E8[] = {
    108, // table length
    0x0023, 0x0058, 0x0019, 0x0087, 0x0019, 0x0087, 0x0021,
    0x0087, 0x0023, 0x0058, 0x002e, 0x0058, 0x002e, 0x0058,
    0x002e, 0x006b, 0x002e, 0x006b, 0x0038, 0x0058, 0x0038,
    0x0058, 0x0043, 0x0058, 0x0043, 0x0058, 0x003b, 0x0079,
    0x003b, 0x0079, 0x0033, 0x0079, 0x0033, 0x0079, 0x0037,
    0x0068, 0x0037, 0x0068, 0x002f, 0x0079, 0x002f, 0x0079,
    0x0028, 0x0079, 0x0028, 0x0079, 0x0028, 0x0068, 0x0028,
    0x0068, 0x0021, 0x0087, 0x0047, 0x0058, 0x0045, 0x0060,
    0x0044, 0x0064, 0x003f, 0x0079, 0x0055, 0x0079, 0x0057,
    0x0071, 0x0057, 0x0071, 0x004a, 0x0071, 0x004a, 0x0071,
    0x004b, 0x006c, 0x004b, 0x006c, 0x0058, 0x006c, 0x0058,
    0x006c, 0x005a, 0x0064, 0x005a, 0x0064, 0x0044, 0x0064,
    0x0045, 0x0060, 0x005b, 0x0060, 0x005b, 0x0060, 0x005d,
    0x0058, 0x005d, 0x0058, 0x0047, 0x0058, 0x003f, 0x0079,
    0x0055, 0x0079, 0x0060, 0x0058, 0x007a, 0x0058, 0x007a,
    0x0058, 0x0078, 0x0060, 0x005e, 0x0060, 0x0067, 0x0060,
    0x0078, 0x0060, 0x0070, 0x0060, 0x0067, 0x0060, 0x0062,
    0x0079, 0x0070, 0x0060, 0x006b, 0x0079, 0x006b, 0x0079,
    0x0062, 0x0079, 0x0060, 0x0058, 0x005e, 0x0060, 0x007b,
    0x0064, 0x006f, 0x0079, 0x006f, 0x0079, 0x0079, 0x0079,
    0x0079, 0x0079, 0x0081, 0x006b, 0x0081, 0x006b, 0x0085,
    0x006b, 0x0085, 0x006b, 0x0086, 0x0079, 0x0086, 0x0079,
    0x008f, 0x0079, 0x008f, 0x0079, 0x008d, 0x0064, 0x007b,
    0x0064, 0x008d, 0x0064, 0x007d, 0x0060, 0x008d, 0x0060,
    0x008d, 0x0060, 0x008c, 0x0058, 0x007d, 0x0060, 0x0082,
    0x0058, 0x0082, 0x0058, 0x008c, 0x0058, 0x0091, 0x0079,
    0x00a7, 0x0079, 0x0091, 0x0079, 0x0098, 0x0058, 0x0098,
    0x0058, 0x00a1, 0x0058, 0x00a1, 0x0058, 0x009c, 0x0071,
    0x009c, 0x0071, 0x00a9, 0x0071, 0x00a9, 0x0071, 0x00a7,
    0x0079, 0x00ba, 0x0058, 0x00ad, 0x0068, 0x00ad, 0x0068,
    0x00b3, 0x0079, 0x00b3, 0x0079, 0x00c8, 0x0079, 0x00c8,
    0x0079, 0x00cd, 0x0064, 0x00cd, 0x0064, 0x00bd, 0x0064,
    0x00bd, 0x0064, 0x00bb, 0x006c, 0x00bb, 0x006c, 0x00c2,
    0x006c, 0x00c2, 0x006c, 0x00c1, 0x0071, 0x00c1, 0x0071,
    0x00ba, 0x0071, 0x00ba, 0x0071, 0x00b7, 0x0068, 0x00b7,
    0x0068, 0x00bd, 0x0060, 0x00bd, 0x0060, 0x00ce, 0x0060,
    0x00ce, 0x0060, 0x00d0, 0x0058, 0x00d0, 0x0058, 0x00ba,
    0x0058, 0x00d4, 0x0058, 0x00d2, 0x0060, 0x00d1, 0x0064,
    0x00cc, 0x0079, 0x00cc, 0x0079, 0x00e2, 0x0079, 0x00d1,
    0x0064, 0x00e7, 0x0064, 0x00d2, 0x0060, 0x00e8, 0x0060,
    0x00d4, 0x0058, 0x00ea, 0x0058, 0x00ea, 0x0058, 0x00e8,
    0x0060, 0x00e7, 0x0064, 0x00e5, 0x006c, 0x00e5, 0x006c,
    0x00d8, 0x006c, 0x00e2, 0x0079, 0x00e4, 0x0071, 0x00e4,
    0x0071, 0x00d7, 0x0071, 0x00d8, 0x006c, 0x00d7, 0x0071,
    0x00e4, 0x0079, 0x00ee, 0x0079, 0x00ee, 0x0079, 0x00f6,
    0x006c, 0x00f6, 0x006c, 0x00fa, 0x006c, 0x00fa, 0x006c,
    0x00fb, 0x0079, 0x00fb, 0x0079, 0x0104, 0x0079, 0x0104,
    0x0079, 0x0102, 0x0064, 0x0102, 0x0064, 0x00f0, 0x0064,
    0x00f2, 0x0060, 0x0102, 0x0060, 0x0102, 0x0060, 0x0101,
    0x0058, 0x0101, 0x0058, 0x00f7, 0x0058, 0x00f2, 0x0060,
    0x00f7, 0x0058, 0x00f0, 0x0064, 0x00e4, 0x0079, 0x0106,
    0x0079, 0x0110, 0x0079, 0x010e, 0x0058, 0x0124, 0x0058,
    0x0124, 0x0058, 0x0127, 0x0061, 0x0127, 0x0061, 0x0120,
    0x006a, 0x011e, 0x006a, 0x0127, 0x0087, 0x0127, 0x0087,
    0x011d, 0x0087, 0x011d, 0x0087, 0x0115, 0x006b, 0x0115,
    0x006b, 0x0113, 0x006b, 0x0113, 0x006b, 0x0110, 0x0079,
    0x010b, 0x0064, 0x011a, 0x0064, 0x011a, 0x0064, 0x011e,
    0x0060, 0x011e, 0x0060, 0x010c, 0x0060, 0x010e, 0x0058,
    0x010c, 0x0060, 0x010b, 0x0064, 0x0106, 0x0079, 0x011e,
    0x006a, 0x0120, 0x006a, 0x0026, 0x007d, 0x0024, 0x0087,
    0x0117, 0x007d, 0x011a, 0x0087, 0x0117, 0x007d, 0x0026,
    0x007d, 0x0024, 0x0087, 0x011a, 0x0087
};
const short word_800C364A = 0x200;

// jump_table_800C5C6C

int  dword_800C5C6C = 0x800C3C68;
int  dword_800C5C70 = 0x800C3C68;
int  dword_800C5C74 = 0x800C3C68;
int  dword_800C5C78 = 0x800C3C74;
int  dword_800C5C7C = 0x800C3C74;
int  dword_800C5C80 = 0x800C3C90;
int  dword_800C5C84 = 0x800C3C90;
int  dword_800C5C88 = 0x800C3C90;
int  dword_800C5C8C = 0x800C3C90;
int  dword_800C5C90 = 0x800C3C9C;
int  dword_800C5C94 = 0x800C3CA8;
char aCdCaseOpenn_800C5C98[] = "CD CASE OPEN!!\n";
char aCdNormalSpeedSetFailedn_800C5CA8[] = "CD NORMAL SPEED SET FAILED!!\n";
short word_800C5CC6 = 0;
char aCdNormalSpeedSetSuccessn_800C5CC8[] = "CD NORMAL SPEED SET SUCCESS!!\n";
char byte_800C5CE7 = 0;
char an_800C5CE8[] = "???????\n";
char byte_800C5CF1 = 0;
short word_800C5CF2 = 0;
char aThisIsNotPsDiscn_800C5CF4[] = "THIS IS NOT PS DISC!!\n";
char byte_800C5D0B = 0;
char aCdStopFailedn_800C5D0C[] = "CD STOP FAILED!!\n";
short word_800C5D1E = 0;
char aCdStopSuccessn_800C5D20[] = "CD STOP SUCCESS!!\n";
char byte_800C5D33 = 0;
char aCdCaseClosen_800C5D34[] = "CD CASE CLOSE!!\n";
char byte_800C5D45 = 0;
short word_800C5D46 = 0;
char aStartButtonPushn_800C5D48[] = "START BUTTON PUSH!!\n";
char byte_800C5D5D = 0;
short word_800C5D5E = 0;
char aCdSpinStartn_800C5D60[] = "CD SPIN START!!\n";
char byte_800C5D71 = 0;
short word_800C5D72 = 0;
char aCdNotSpinn_800C5D74[] = "CD NOT SPIN!!\n";
char byte_800C5D83 = 0;
char aCdTocReadNotFinishn_800C5D84[] = "CD TOC READ NOT FINISH!!\n";
short word_800C5D9E = 0;
char aCdTocReadSuccessn_800C5DA0[] = "CD TOC READ SUCCESS!!\n";
char byte_800C5DB7 = 0;
char aCdSpeedInitSuccessn_800C5DB8[] = "CD SPEED INIT SUCCESS!!\n";
char byte_800C5DD1 = 0;
short word_800C5DD2 = 0;
char aCdCheckFailedxxn_800C5DD4[] = "CD CHECK FAILED[%X:%X]!!\n";
short word_800C5DEE = 0;
char aThisIsCddan_800C5DF0[] = "This is CDDA\n";
short word_800C5DFE = 0;
char aCdCheckOkn_800C5E00[] = "CD CHECK OK!!\n";
char byte_800C5E0F = 0;
char aThisIsNotPsDiscn_800C5E10[] = "THIS IS NOT PS DISC!!!\n";
char aCdCheckErrorn_800C5E28[] = "CD CHECK ERROR!!\n";
short word_800C5E3A = 0;
char aThisIsPsDiscn_800C5E3C[] = "THIS IS PS DISC!!\n";
char byte_800C5E4F = 0;
char aThisIsDisc2n_800C5E50[] = "THIS IS DISC 2!!\n";
short word_800C5E62 = 0;
char aThisIsNotDisc2n_800C5E64[] = "THIS IS NOT DISC 2!!!\n";
char byte_800C5E7B = 0;
char aOkOkn_800C5E7C[] = "OK! OK!\n";
char byte_800C5E85 = 0;
short word_800C5E86 = 0;
char aNotOkNotOkn_800C5E88[] = "NOT OK! NOT OK!\n";
char byte_800C5E99 = 0;
short word_800C5E9A = 0;
// jump_table_800C5E9C

int  dword_800C5E9C = 0x800C3D1C;
int  dword_800C5EA0 = 0x800C3DD8;
int  dword_800C5EA4 = 0x800C3EAC;
int  dword_800C5EA8 = 0x800C3EDC;
int  dword_800C5EAC = 0x800C3F34;
int  dword_800C5EB0 = 0x800C3F74;
int  dword_800C5EB4 = 0x800C3FEC;
int  dword_800C5EB8 = 0x800C4074;
int  dword_800C5EBC = 0x800C4094;
int  dword_800C5EC0 = 0x800C42A8;
int  dword_800C5EC4 = 0x800C42DC;
char aChangec_800C5EC8[] = "change.c";
char aSafecheckstartn_800C5ED4[] = "SafeCheckStart\n";
int dword_800C5EE4 = 173625940;
int dword_800C5EE8 = 0;
char aTimeoutn_800C5EEC[] = "TIMEOUT\n";
char byte_800C5EF5 = 0;
short word_800C5EF6 = 0;
char aTryEndn_800C5EF8[] = "TRY END\n";
char byte_800C5F01 = 0;
short word_800C5F02 = 0;
char aOpenn_800C5F04[] = "OPEN\n";
short word_800C5F0A = 0;
char aSafecheckendn_800C5F0C[] = "SafeCheckEND\n";
int __attribute__ ((aligned (1))) dword_800C5F1A = -0x52750000;
int __attribute__ ((aligned (1))) dword_800C5F1E = 0x498FA790;
int __attribute__ ((aligned (1))) dword_800C5F22 = -1249724009;
int __attribute__ ((aligned (1))) dword_800C5F26 = -1249715070;
int __attribute__ ((aligned (1))) dword_800C5F2A = 1115798914;
int __attribute__ ((aligned (1))) dword_800C5F2E = -1854171638;
int __attribute__ ((aligned (1))) dword_800C5F32 = -1985314100;
int __attribute__ ((aligned (1))) dword_800C5F36 = -2103275012;
int __attribute__ ((aligned (1))) dword_800C5F3A = -2098560333;
int __attribute__ ((aligned (1))) dword_800C5F3E = -2103278908;
int __attribute__ ((aligned (1))) dword_800C5F42 = -1467872535;
int __attribute__ ((aligned (1))) dword_800C5F46 = -360531070;
int __attribute__ ((aligned (1))) dword_800C5F4A = -1602049406;
int __attribute__ ((aligned (1))) dword_800C5F4E = -595400574;
int __attribute__ ((aligned (1))) dword_800C5F52 = 1115797378;
short  __attribute__ ((aligned (1))) word_800C5F56 = 0;
int dword_800C5F58 = 33489153;
int dword_800C5F5C = -255;
int dword_800C5F60 = 0;
int dword_800C5F64 = 0;
int dword_800C5F68 = 0;
char aMetLogo_800C5F6C[] = "met_logo.c";
