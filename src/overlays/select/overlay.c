#include "libgcl/libgcl.h"
#include "libgcl/hash.h"
#include "../select1/Game/select.h"

GCL_ActorTableEntry selectOverlayCharas[] =
{
    { CHARA_SELECT, NewSelect_800c3434 },
    { 0x6C66, (TGCL_ActorCreateFn)0x800C47B4 },
    { 0, 0 }
};

int select_dword_800C3220 = 0x800C5060;
int select_dword_800C3224 = 0x800C5054;
int select_dword_800C3228 = 0x800C5048;
int select_dword_800C322C = 0x800C5038;
int select_dword_800C3230 = 0x800C50AC;
int select_dword_800C3234 = 0x800C509C;
int select_dword_800C3238 = 0x800C508C;
int select_dword_800C323C = 0x800C507C;
int select_dword_800C3240 = 0x800C506C;

// Game/select.c:
const char aNoMenu[] = "NO MENU\n";
const char aSelect[] = {'s', 'e', 'l', 'e', 'c', 't', '.', 'c', 0x0, 'r', ':', ' '}; // "select.c" + padding filled with memleak ("r: ")?

const char select_aSwapforward_800C5038[] = "SWAP FORWARD";
const char select_aSwapback_800C5048[] = "SWAP BACK";
const char select_aDelparam_800C5054[] = "DEL PARAM";
const char select_aInsparam_800C5060[] = "INS PARAM";
const char select_aQuickloadlow_800C506C[] = "QUICK LOAD LOW";
const char select_aQuickloadhigh_800C507C[] = "QUICK LOAD HIGH";
const char select_aQuicksavelow_800C508C[] = "QUICK SAVE LOW";
const char select_aQuicksavehigh_800C509C[] = "QUICK SAVE HIGH";
const char select_aChangebank_800C50AC[] = "CHANGE BANK";
const char select_aPadvibationparameterforgcl_800C50B8[] = "pad vibation parameter (for gcl)\n";
const char select_aHigh_800C50DC[] = "high:{ ";
const char select_aDd_800C50E4[] = "%d,%d ";
const char select_a_800C50EC[] = "}\n";
const char select_aLow_800C50F0[] = "low:{ ";
const char select_aPadvibationparameterforprogram_800C50F8[] = "pad vibation parameter (for program)\n";
const char select_a_800C5120[] = "0,0";
const char select_aDd_800C5124[] = "%d,%d,";
const char select_a_800C512C[] = "}\n\n";
const char select_aEditmenu_800C5130[] = "EDIT MENU";
const char select_aFilemenu_800C513C[] = "FILE MENU";
const char select_aSd_800C5148[] = "%s %d";
const char select_aVibrationeditorver_800C5150[] = "Vibration Editor   Ver 1.50\n";
const char select_aSelectparamlr_800C5170[] = "Select param  - < L1  R1 >\n";
const char select_aChangelengthlr_800C518C[] = "Change length - < L   R  >\n";
const char select_aChangepowerud_800C51A8[] = "Change power  - < U   D  >\n";
const char select_aExitl_800C51C4[] = "EXIT          - < L3 >\n";
const char select_aPlaya_800C51DC[] = "PLAY          - < A >\n";
const char select_aTypechangex_800C51F4[] = "Type change   - < X >\n";
const char select_aDispparamy_800C520C[] = "Disp param    - < Y >\n";
const char select_aEditmenur_800C5224[] = "Edit menu     - < R2 >\n";
const char select_aFilemenul_800C523C[] = "File menu     - < L2 >\n";
const char select_aEditvibrationtyped_800C5254[] = "Edit vibration - type %d\n";
const char select_aEddd_800C5270[] = "E%2d- %3d %3d\n";
const char select_aDdd_800C5280[] = " %2d- %3d %3d\n";
const int select_dword_800C5290 = 0x800C43FC;
const int select_dword_800C5294 = 0x800C43C8;
const int select_dword_800C5298 = 0x800C43D4;
const int select_dword_800C529C = 0x800C43E0;
const int select_dword_800C52A0 = 0x800C43EC;
const char select_aSavevibrationeditordata_800C52A4[] = "Save vibration editor data !\n";
const char select_aVibeditdat_800C52C4[] = "VIB_EDIT.DAT";
const char select_aVibeditc_800C52D4[] = "vib_edit.c";
