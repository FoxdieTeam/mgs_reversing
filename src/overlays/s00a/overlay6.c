#include "libdg/libdg.h"

/*
const int s00a_dword_800E0730 = 0x800CD654;
const int s00a_dword_800E0734 = 0x800CD800;
const int s00a_dword_800E0738 = 0x800CD800;
const int s00a_dword_800E073C = 0x800CD800;
const int s00a_dword_800E0740 = 0x800CD69C;
const int s00a_dword_800E0744 = 0x800CD71C;
const int s00a_dword_800E0748 = 0x800CD774;
const int s00a_dword_800E074C = 0x800CD79C;
const int s00a_dword_800E0750 = 0x800CD7AC;

const char s00a_dword_800E0754[] = {0x0, 0x0, 0x0, 0x0};
const int s00a_dword_800E0758 = 0x800CD95C;
const int s00a_dword_800E075C = 0x800CD914;
const int s00a_dword_800E0760 = 0x800CDABC;
const int s00a_dword_800E0764 = 0x800CDA68;
const int s00a_dword_800E0768 = 0x800CD9D4;
const int s00a_dword_800E076C = 0x800CDABC;
const int s00a_dword_800E0770 = 0x800CDA40;
const int s00a_dword_800E0774 = 0x800CDABC;
const int s00a_dword_800E0778 = 0x800CDABC;
const int s00a_dword_800E077C = 0x800CD944;
const int s00a_dword_800E0780 = 0x800CD8FC;
*/
/*
const char s00a_dword_800E0784[] = {0x0, 0x0, 0x0, 0x0};
const int s00a_dword_800E0788 = 0x800CDEDC;
const int s00a_dword_800E078C = 0x800CDF54;
const int s00a_dword_800E0790 = 0x800CDF54;
const int s00a_dword_800E0794 = 0x800CDEF4;
const int s00a_dword_800E0798 = 0x800CDF0C;
const int s00a_dword_800E079C = 0x800CDF24;
const int s00a_dword_800E07A0 = 0x800CDF3C;
*/
const char s00a_dword_800E07A4[] = {0x0, 0x0, 0x0, 0x0};
const int s00a_dword_800E07A8 = 0x800CE684;
const int s00a_dword_800E07AC = 0x800CE694;
const int s00a_dword_800E07B0 = 0x800CE6B0;
const int s00a_dword_800E07B4 = 0x800CE6CC;
const int s00a_dword_800E07B8 = 0x800CE6E8;
const int s00a_dword_800E07BC = 0x800CE704;
const int s00a_dword_800E07C0 = 0x800CE674;
const int s00a_dword_800E07C4 = 0x800CE720;
const int s00a_dword_800E07C8 = 0x800CE8C0;
const int s00a_dword_800E07CC = 0x800CE8D0;
const int s00a_dword_800E07D0 = 0x800CE8F8;
const int s00a_dword_800E07D4 = 0x800CE8E0;
const int s00a_dword_800E07D8 = 0x800CE8B0;
const int s00a_dword_800E07DC = 0x800CE8F8;
const int s00a_dword_800E07E0 = 0x800CE8F0;
const int s00a_dword_800E07E4 = 0x800CE8F8;
const int s00a_dword_800E07E8 = 0x800CE8F8;
const int s00a_dword_800E07EC = 0x800CE8F8;
const int s00a_dword_800E07F0 = 0x800CE880;
const int s00a_dword_800E07F4 = 0x800CE890;
const int s00a_dword_800E07F8 = 0x800CE8A0;
const char s00a_aCresetposd_800E07FC[] = " c_reset_pos = %d \n";
const char s00a_aKottida_800E0810[] = "kottida !!\n";
const int s00a_dword_800E081C = 0x800CF174;
const int s00a_dword_800E0820 = 0x800CF184;
const int s00a_dword_800E0824 = 0x800CF194;
const int s00a_dword_800E0828 = 0x800CF1A4;
const int s00a_dword_800E082C = 0x800CF1B4;
const int s00a_dword_800E0830 = 0x800CF1C4;
const int s00a_dword_800E0834 = 0x800CF1D4;
const int s00a_dword_800E0838 = 0x800CF1E4;
const char s00a_aResetmaxdnumd_800E083C[] = "reset max=%d num=%d \n";
const char s00a_aGmenemywatchcountd_800E0854[] = " GM_EnemyWatchCount = [%d] \n";
const char s00a_aNowzonedrzoned_800E0874[] = " now zone = %d r_zone=%d\n";
const char s00a_aNotrestrctedaread_800E0890[] = " ? ? ? Not Restrcted Area [%d] !!!!\n";
const char s00a_aErrerrerrnotlinkroutedtod_800E08B8[] = " Err Err Err Not Link Route [%d] to [%d] !!!!\n";
const char s00a_aCommanderrnozoneidingclzdidd_800E08E8[] = "command:!!!Err No Zone ID In Gcl z%d id%d!!!!!!!!\n";
const char s00a_aCommandcwhereissnake_800E091C[] = "command.c:  Where Is Snake ????\n";
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
const char s00a_dword_800E0AB0[] = {0xa5, 0xd0, 0xa5, 0xd6};
const char s00a_dword_800E0AB4[] = {0xa5, 0xeb, 0xa4, 0xcf};
const char s00a_dword_800E0AB8[] = {0xa4, 0xb8, 0xa4, 0xb1};
const char s00a_dword_800E0ABC[] = {0xa4, 0xed, 0x0, 0x0};
const char s00a_aKill_800E0AC0[] = "kill";
const char s00a_aAwas_800E0AC8[] = "awa_s";
const char s00a_aBubblesc_800E0AD0[] = "bubble_s.c";
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
const char s00a_aPatlit_800E0B24[] = "patlit";
const char s00a_aPatbody_800E0B2C[] = "pat_body";
const char s00a_aPatlamp_800E0B38[] = "pat_lamp";
const char s00a_aPatspt_800E0B44[] = "pat_spt1";
const char aPatoLmpC_800E0B50[] = "pato_lmp.c";
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
const int s00a_dword_800E0C18 = 0x800DD778;
const int s00a_dword_800E0C1C = 0x800DD7BC;
const int s00a_dword_800E0C20 = 0x800DD818;
const int s00a_dword_800E0C24 = 0x800DD850;
const int s00a_dword_800E0C28 = 0x800DD8B4;

// Takabe/telop.c
const char aTelopC[] = "telop.c";

// Takabe/cinema.c
const char aCinemaC[] = "cinema.c";
const char s00a_dword_800E0C3D = 0x2;
const char s00a_dword_800E0C3E = 0x0;
const char s00a_dword_800E0C3F = 0x0;
