#include "linker.h"

int s02a_dword_800C370C = 0x00000030;
int s02a_dword_800C3710 = 0x00000060;
int s02a_dword_800C3714 = 0x0000FFD0;
int s02a_dword_800C3718 = 0x00000060;
int s02a_dword_800C371C = 0x006BD182;
int s02a_dword_800C3720 = 0x423543D3;
int s02a_dword_800C3724 = 0x00000000;
int s02a_dword_800C3728 = 0x00000064;
int s02a_dword_800C372C = 0x00320032;
int s02a_dword_800C3730 = 0x00640064;
int s02a_dword_800C3734 = 0x006BD182;
int s02a_dword_800C3738 = 0x71F13223;
int s02a_dword_800C373C = 0x745DD420;
int s02a_dword_800C3740 = 0x006BD182;
int s02a_dword_800C3744 = 0x24023223;
int s02a_dword_800C3748 = 0x00280028;
int s02a_dword_800C374C = 0x00500050;
int s02a_dword_800C3750 = 0xFE700000;
int s02a_dword_800C3754 = 0x0000003C;


const char s02a_dword_800E30A0[] = {'b', 'l', 'u', 'r'};
const char s02a_dword_800E30A4[] = {'.', 'c', 0x0, 0x18};
const char s02a_aAwas_800E30A8[] = "awa_s";
const char s02a_aAwa_800E30B0[] = "awa_2";
const char s02a_aAwa_800E30B8[] = "awa_3";
const char s02a_aBubdsnc_800E30C0[] = "bub_d_sn.c";
const char s02a_aMouse_800E30CC[] = "mouse";
const char s02a_aShadow_800E30D4[] = "shadow";
const char s02a_dword_800E30DC[] = {'d', 'u', 'c', 't'};
const char s02a_dword_800E30E0[] = {'m', 'o', 'u', 's'};
const char s02a_dword_800E30E4[] = {'.', 'c', 0x0, 0x11};
const char s02a_dword_800E30E8[] = {0x0, 0x0, 0x0, 0x0};
const char s02a_dword_800E30EC[] = {0xf4, 0x1, 0x0, 0x0};
const char s02a_dword_800E30F0[] = {'s', 'p', 'a', 'r'};
const char s02a_dword_800E30F4[] = {'k', '2', '.', 'c'};
const char s02a_dword_800E30F8[] = {0x0, '<', '`', 0x97};
const char s02a_aRipple_800E30FC[] = "ripple";
const char s02a_dword_800E3104[] = {'r', 'i', 'p', 'p'};
const char s02a_dword_800E3108[] = {'l', 'e', '.', 'c'};
const char s02a_dword_800E310C[] = {0x0, 0x0, '#', 0x18};
const char s02a_aRsurfacec_800E3110[] = "rsurface.c";
const char s02a_aGasefctc_800E311C[] = "gas_efct.c";
const char s02a_dword_800E3128[] = {'w', 't', '_', 'a'};
const char s02a_dword_800E312C[] = {'r', 'e', 'a', '.'};
const char s02a_dword_800E3130[] = {'c', 0x0, 0xc2, 0x11};
const char s02a_aAwa_800E3134[] = "awa_3";
const char s02a_aSplashc_800E313C[] = "splash2.c";
const char s02a_aWtviewc_800E3148[] = "wt_view.c";
const char s02a_aWtviewcoverprims_800E3154[] = "(wt_view.c) Over prims !!!\n";
const char s02a_aMosaicc_800E3170[] = "mosaic.c";
const char s02a_dword_800E317C[] = {'M', 'o', 's', 'a'};
const char s02a_dword_800E3180[] = {'i', 'c', 0x0, 0x97};
const char s02a_dword_800E3184[] = {'f', 'a', 'd', 'e'};
const char s02a_dword_800E3188[] = {'i', 'o', '.', 'c'};
const char s02a_dword_800E318C[] = {0x0, '2', 0x13, 0x0};
const char s02a_dword_800E3190[] = {'c', 'i', 'n', 'e'};
const char s02a_dword_800E3194[] = {'m', 'a', '.', 'c'};
const char s02a_dword_800E3198[] = {0x0, '<', 0xb0, 0x97};
const char s02a_dword_800E319C[] = {'o', '2', '_', 'd'};
const char s02a_dword_800E31A0[] = {'a', 'm', 'g', 'e'};
const char s02a_dword_800E31A4[] = {'.', 'c', 0x0, 0x1};
const char s02a_dword_800E31A8[] = {'d', 'y', 'm', 'c'};
const char s02a_dword_800E31AC[] = {'_', 's', 'e', 'g'};
const char s02a_dword_800E31B0[] = {'.', 'c', 0x0, 'X'};
const char s02a_aFocusview_800E31B4[] = "FocusView";
const char s02a_aFocusc_800E31C0[] = "focus.c";
const char s02a_dword_800E31C8[] = {'s', 'h', 'a', 'k'};
const char s02a_dword_800E31CC[] = {'e', 'm', 'd', 'l'};
const char s02a_dword_800E31D0[] = {'.', 'c', 0x0, 0x97};
const char s02a_dword_800E31D4[] = {'c', 'a', 't', '_'};
const char s02a_dword_800E31D8[] = {'i', 'n', '.', 'c'};
const char s02a_dword_800E31DC[] = {0x0, 0xa4, 0x5, 0x0};
const char s02a_aPutobjctotalojbectd_800E31E0[] = "(put_obj.c) total ojbect : %d \n";
const char s02a_aPutobjc_800E3200[] = "put_obj.c";
const char s02a_aFamasl_800E320C[] = "famas_l";
const char s02a_aFamaslitc_800E3214[] = "famaslit.c";


int SECTION("overlay.bss") s02a_dword_800E3690;
int SECTION("overlay.bss") s02a_dword_800E3694;
int SECTION("overlay.bss") s02a_dword_800E3698;
int SECTION("overlay.bss") s02a_dword_800E369C;
int SECTION("overlay.bss") s02a_dword_800E36A0;
int SECTION("overlay.bss") s02a_dword_800E36A4;
int SECTION("overlay.bss") s02a_dword_800E36A8;
int SECTION("overlay.bss") s02a_dword_800E36AC;
int SECTION("overlay.bss") s02a_dword_800E36B0;
int SECTION("overlay.bss") s02a_dword_800E36B4;
int SECTION("overlay.bss") s02a_dword_800E36B8;
int SECTION("overlay.bss") s02a_dword_800E36BC;
int SECTION("overlay.bss") s02a_dword_800E36C0;
int SECTION("overlay.bss") s02a_dword_800E36C4;
int SECTION("overlay.bss") s02a_dword_800E36C8;
int SECTION("overlay.bss") s02a_dword_800E36CC;
int SECTION("overlay.bss") s02a_dword_800E36D0;
int SECTION("overlay.bss") s02a_dword_800E36D4;
int SECTION("overlay.bss") s02a_dword_800E36D8;
int SECTION("overlay.bss") s02a_dword_800E36DC;
int SECTION("overlay.bss") s02a_dword_800E36E0;
int SECTION("overlay.bss") s02a_dword_800E36E4;
