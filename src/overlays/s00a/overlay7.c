#include "libdg/libdg.h"
/*
const int s00a_dword_800E081C = 0x800CF174;
const int s00a_dword_800E0820 = 0x800CF184;
const int s00a_dword_800E0824 = 0x800CF194;
const int s00a_dword_800E0828 = 0x800CF1A4;
const int s00a_dword_800E082C = 0x800CF1B4;
const int s00a_dword_800E0830 = 0x800CF1C4;
const int s00a_dword_800E0834 = 0x800CF1D4;
const int s00a_dword_800E0838 = 0x800CF1E4;
*/
const char s00a_aResetmaxdnumd_800E083C[] = "reset max=%d num=%d \n";
const char aGmenemywatchcountd_800E0854[] = " GM_EnemyWatchCount = [%d] \n";
const char aNowzonedrzoned_800E0874[] = " now zone = %d r_zone=%d\n";
const char aNotrestrctedaread_800E0890[] = " ? ? ? Not Restrcted Area [%d] !!!!\n";
const char aErrerrerrnotlinkroutedtod_800E08B8[] = " Err Err Err Not Link Route [%d] to [%d] !!!!\n";

const char aCommanderrnozoneidingclzdidd_800E08E8[] = "command:!!!Err No Zone ID In Gcl z%d id%d!!!!!!!!\n";
const char aCommandcwhereissnake_800E091C[] = "command.c:  Where Is Snake ????\n";
const char aCom_noisemode_disD_800E0940[] = " COM_NOISEMODE_DIS =%d \n";
const char aEeeDDDTD_800E095C[] = "eee %d %d %d t %d \n";
const char aCommandC_800E0970[] = "command.c";
const RECT eyeflash_rect = {175, 100, 350, 200};
const char s00a_aKirari_800E0984[] = "kirari";
const char s00a_aEyeflashc_800E098C[] = "eyeflash.c";
const char aAsiatoc_800E0998[] = "asiato.c";

const char aLSightC[] = "l_sight.c";

const char aGrenadeModelD[] = "grenade model=%d \n";
const char aGrnadEC[] = "grnad_e.c";

const char s00a_dword_800E09D0[] = {0xa5, 0xb9, 0xa5, 0xcd};
const char s00a_dword_800E09D4[] = {0xa1, 0xbc, 0xa5, 0xaf};
const char s00a_dword_800E09D8[] = {0x0, 0x0, 0x0, 0x0};
const char s00a_dword_800E09DC[] = {0xc3, 0xca, 0xa5, 0xdc};
const char s00a_dword_800E09E0[] = {0xa1, 0xbc, 0xa5, 0xeb};
const char s00a_dword_800E09E4[] = {0x0, 0x0, 0x0, 0x0};
const char s00a_aCbbox_800E09E8[] = "cb_box";
const char s00a_aBoxkeric_800E09F0[] = "boxkeri.c";
const char s00a_aSmoke_800E09FC[] = "smoke";
const char s00a_aSmokec_800E0A04[] = "smoke.c";

// Enemy/wall.c
const char aDestroy[] = "destroy\n";
const char aBox01[] = "box_01";
const char aDbx1[] = "dbx1";
const char aDbx2[] = "dbx2";
const char aWallC[] = "wall.c";

// Enemy/asioto.c
const char aAsiotoSeSetErr[] = " asioto se set err \n";
const char aAsiotoSeNoiseSetErr[] = " asioto se noise set err \n";
const char aMigiSodesuri[] = " migi sodesuri %d \n";
const char aAsiotoC[] = "asioto.c";

const char s00a_dword_800E0A89 = 0x0A;
const char s00a_dword_800E0A8A = 0x10;
const char s00a_dword_800E0A8B = 0x19;
const char s00a_aFamasl_800E0A8C[] = "famas_l";
const char aGlightC_800E0A94[] = "glight.c";
const char s00a_dword_800E0A9D = 0x00;
const char s00a_dword_800E0A9E = 0x00;
const char s00a_dword_800E0A9F = 0x54;
const char aMouse[] = "mouse";
const char aMouseC[] = "mouse.c";

const char aBabu[] = {0xa5, 0xd0, 0xa5, 0xd6}; // "バブ" = bubble
const char aRuWa[] = {0xa5, 0xeb, 0xa4, 0xcf}; // "ルは" = ????

const char s00a_dword_800E0AB8[] = {0xa4, 0xb8, 0xa4, 0xb1};
const char s00a_dword_800E0ABC[] = {0xa4, 0xed, 0x0, 0x0};
const char aKill[] = "kill";

const char aAwas[] = "awa_s";
const char aBubbleSC[] = "bubble_s.c";

const char s00a_dword_800E0ADC[] = {0xb3, 0xab, 0xa4, 0xaf};
const char s00a_dword_800E0AE0[] = {0x0, 0x0, 0x0, 0x0};
const char s00a_dword_800E0AE4[] = {0xca, 0xc4, 0xa4, 0xe1};
const char s00a_dword_800E0AE8[] = {0xa4, 0xeb, 0x0, 0x0};
const char s00a_aOpen_800E0AEC[] = "open";
const char s00a_aClose_800E0AF4[] = "close";
const char s00a_aSeon_800E0AFC[] = "se_on";
const char s00a_aSeoff_800E0B04[] = "se_off";
const int s00a_dword_800E0B0C = 0x800D6750;
const int s00a_dword_800E0B10 = 0x800D676C;
const int s00a_dword_800E0B14 = 0x800D6750;
const int s00a_dword_800E0B18 = 0x800D676C;
const int s00a_dword_800E0B1C = 0x800D6780;
const int s00a_dword_800E0B20 = 0x800D678C;

const char aPatlit[] = "patlit";
const char aPatBody[] = "pat_body";
const char aPatLamp[] = "pat_lamp";
const char aPatSpt1[] = "pat_spt1";
const char aPatoLmpC[] = "pato_lmp.c";

const char s00a_dword_800E0B5B = 0xFF;
const char aRipple_800E0B5C[] = "ripple";
const char aRippleC_800E0B64[] = "ripple.c";
const char s00a_dword_800E0B6D = 0x34;
const char s00a_dword_800E0B6E = 0x0F;
const char s00a_dword_800E0B6F = 0x00;
const char aRsurfaceC_800E0B70[] = "rsurface.c";
const char s00a_dword_800E0B7B = 0x38;
const char aRipplesC_800E0B7C[] = "ripples.c";
const char s00a_dword_800E0B86 = 0x23;
const char s00a_dword_800E0B87 = 0x18;

const char aElevatorC[] = "elevator.c";

const char s00a_dword_800E0B93 = 0x10;
const char aWtAreaC_800E0B94[] = "wt_area.c";
const char s00a_aAwa_800E0B9E = 0xF4;
const char s00a_aAwa_800E0B9F = 0x03;
const char aAwa_800E0BA0[] = "awa_3";
const char aSplash2C_800E0BA8[] = "splash2.c";
const char s00a_aWtviewc_800E0BB2 = 0x3F;
const char s00a_aWtviewc_800E0BB3 = 0x00;

const char sWtViewC[] = "wt_view.c";

const char s00a_aWtviewcoverprims_800E0BC0[] = "(wt_view.c) Over prims !!!\n";
const char s00a_aMosaicc_800E0BDC[] = "mosaic.c";
const char aMosaic_800E0BE8[] = "Mosaic";
const char s00a_dword_800E0BEF = 0xB0;

const char aPadRecStart[] = "Pad rec start\n";
const char aPadDemoC[] = "pad_demo.c";

const char s00a_dword_800E0C0B = 0x10;

// Takabe/fadeio.c
const char aFadeioC[] = "fadeio.c";

const char s00a_dword_800E0C15 = 0x30;
const char s00a_dword_800E0C16 = 0x03;
const char s00a_dword_800E0C17 = 0x00;
