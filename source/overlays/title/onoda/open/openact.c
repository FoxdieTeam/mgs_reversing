/* OpenAct_800D37F4 — top-level state machine for the title screen.
 *
 * Lives in its own translation unit (separate from open.c) for two reasons:
 *
 *   1. The original psyq compiled the switch on work->fA74 into a jump table
 *      at 0x800D9028 (22 entries) and the two sub-switches on work->fA78 into
 *      tables at 0x800D9080 / 0x800D9098 (6 entries each). Those tables were
 *      reverse-transcribed as `const int title_dword_*` declarations in
 *      overlay3.c. To get gcc to re-emit equivalent tables at the SAME
 *      addresses, we need open.obj's rdata + this file's rdata (in linker
 *      order) to fill exactly 0x988 bytes before the new switch tables.
 *      The strings that previously lived at 0x800D8848..0x800D9024 in
 *      overlay3.c (0x7E0 bytes) are moved here so openact.obj's rdata fills
 *      the right portion of the gap. Linker order is configured to be
 *      open.obj -> openact.obj -> overlay3.obj.
 *
 *   2. include_asm_fixup.py expects each INCLUDE_ASM stub function to end
 *      with a 3-instruction return at the very end of its byte range. When
 *      OpenAct's switch is in the same TU as INCLUDE_ASM stubs, gcc
 *      interleaves switch jump tables with .text in a way that inflates the
 *      reported size of an adjacent stub — fixup then reads garbage instead
 *      of the stub's return and can't determine which .s file to splice in.
 *      Putting OpenAct in its own (INCLUDE_ASM-free) TU sidesteps that.
 */

#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "font/font.h"
#include "menu/menuman.h"
#include "game/game.h"
#include "sound/sd_cli.h"
#include "sound/g_sound.h"

typedef struct _Unknown
{
    SPRT  sprt[2];
    SPRT  sprt2[2][4];
    char *string;
    short num;
    short num2;
    RECT  rect;
    short f0;
    short f2;
    short f4;
    short f6;
} Unknown;

typedef struct _OpenWork
{
    GV_ACT   actor;
    DG_PRIM *prim[4];
    int      f30[22];
    char     pad[0x58];
    int      fE0[6];
    int      fF8[18];
    int      f140[9];
    int      f164;
    int      f168;
    int      f16C;
    int      f170;
    int      f174;
    int      f178;
    int      f17C;
    int      f180;
    int      f184;
    int      f188;
    POLY_FT4 f18C_polys[22];
    POLY_FT4 f4FC_polys[18];
    POLY_FT4 f7CC_polys[9];
    POLY_GT4 f934_polys[6];
    short   *fA6C;
    int      fA70;
    int      fA74;
    int      fA78;
    int      fA7C;
    int      fA80;
    int      fA84;
    int      fA88;
    int      fA8C;
    int      fA90;
    int      fA94;
    int      fA98;
    int      fA9C;
    int      fAA0;
    int      fAA4;
    char     fAA8;
    char     fAA9;
    char     fAAA;
    char     fAAB;
    char     fAAC;
    char     fAAD;
    char     fAAE;
    char     fAAF;
    char     pad6[0x8];
    int      fAB8;
    char     pad7[0x1C];
    int      fAD8;
    int      fADC;
    int      fAE0;
    int      fAE4;
    int      fAE8;
    int      fAEC;
    int      fAF0;
    int      fAF4;
    int      fAF8;
    int      fAFC;
    int      fB00;
    int      fB04;
    int      fB08;
    int      fB0C;
    int      fB10;
    int      fB14;
    int      fB18;
    int      fB1C;
    int      fB20;
    int      fB24;
    int      fB28;
    int      fB2C;
    int      fB30;
    int      fB34;
    int      fB38;
    int      fB3C;
    int      fB40;
    int      fB44;
    int      fB48;
    KCB      kcb[24];
    char     pad8[0x14];
    DR_TPAGE tpage[2];
    char     pad9[0x8];
    Unknown  unk[24];
    int      f2498;
    int      f249C;
    int      f24A0;
    int      f24A4;
    char     pad10[0x4];
    int      f24AC;
    int      f24B0;
    int      f24B4;
    int      f24B8;
    int      f24BC;
    int      f24C0;
    int      f24C4;
    int      f24C8;
    int      f24CC;
    int      f24D0;
    int      f24D4;
    int      f24D8;
    int      f24DC;
    int      f24E0;
    int      f24E4;
    int      f24E8;
    int      f24EC;
    int      f24F0;
    int      f24F4;
    int      f24F8_proc;
    char     pad11[8];
} OpenWork;

extern void  title_open_800C5644(OpenWork *work, int index);
extern void  title_open_800C5CB8(OpenWork *work);
extern void  title_open_800C5CF0(OpenWork *work);
extern void  title_open_800C5D10(OpenWork *work);
extern void  title_open_800C53E0(OpenWork *work);
extern int   title_open_800C628C(OpenWork *work);
extern void  title_open_800CCDC8(OpenWork *work);
extern void  title_open_800CD074(OpenWork *work);
extern void  title_open_800CD23C(OpenWork *work, int index, int arg3);
extern void  title_open_800CD320(OpenWork *work, int index);
extern void  title_open_800CD3B8(OpenWork *work, int index);
extern void  title_open_800CD800(OpenWork *work, int index);
extern void  title_open_800CDE44(OpenWork *work, int index);
extern void  title_open_800CE378(OpenWork *work, int index);
extern void  title_open_800CE4A8(OpenWork *work, int index);
extern void  title_open_800CE544(OpenWork *work, int index);
extern void  title_open_800CE5F8(OpenWork *work, int index);
extern void  title_open_800CE6AC(OpenWork *work, int index);
extern void  title_open_800CE748(OpenWork *work, int index);
extern void  title_open_800CEB14(OpenWork *work, int index);
extern void  title_open_800CEF54(OpenWork *work, int index);
extern void  title_open_800CF504(OpenWork *work, int index);
extern void  title_open_800CF610(OpenWork *work, int index);
extern void  title_open_800CF794(OpenWork *work);
extern void  title_open_800D1CB4(OpenWork *work);
extern void  title_open_800D2A00(OpenWork *work);
extern void  title_open_800D2AFC(OpenWork *work);
extern void  title_open_800D2CA8(OpenWork *work, u_long *ot);
extern void  title_open_800D2E44(OpenWork *work, u_long *ot);
extern void  title_open_800D3500(OpenWork *work, u_long *ot);
extern void *NewMetalGearLogo(int *exit);
extern void *title_open_800C4B20(KCB *kcb);
extern int   title_dword_800D92D0;
extern const char aOpenC[];

#define EXEC_LEVEL GV_ACTOR_MANAGER

/* The strings that previously lived at 0x800D8848..0x800D9024 in overlay3.c
 * are moved here so openact.obj's rdata fills the gap up to 0x800D9028,
 * where gcc's emitted switch jump tables for OpenAct's switch then land. */

const char title_aGameleveld_800D8848[] = "\n Game Level = %d\n\n";
const char title_aErrormemcardcheckerror_800D885C[] = "ERROR!!!! MEMCARD Check ERROR!!!\n";
const char title_aSppre_800D8880[] = "sp_pre";
const char title_aSpexit_800D8888[] = "sp_exit";
const char title_aSpalbum_800D8890[] = "sp_album";
const char title_aSpdemo_800D889C[] = "sp_demo";
const char title_aSpon_800D88A4[] = "sp_on";
const char title_aSpoffw_800D88AC[] = "sp_off_w";
const char title_aSponw_800D88B8[] = "sp_on_w";
const char title_aSpoff_800D88C0[] = "sp_off";
const char title_aDsppmode_800D88C8[] = "d3_sp_1p_mode";
const int title_dword_800D88D8 = 0x800C6398;
const int title_dword_800D88DC = 0x800C63C0;
const int title_dword_800D88E0 = 0x800CCDA0;
const int title_dword_800D88E4 = 0x800CCDA0;
const int title_dword_800D88E8 = 0x800C63E8;
const int title_dword_800D88EC = 0x800C6414;
const int title_dword_800D88F0 = 0x800C6440;
const int title_dword_800D88F4 = 0x800C6C50;
const int title_dword_800D88F8 = 0x800C805C;
const int title_dword_800D88FC = 0x800C8104;
const int title_dword_800D8900 = 0x800C8110;
const int title_dword_800D8904 = 0x800C812C;
const int title_dword_800D8908 = 0x800C8148;
const int title_dword_800D890C = 0x800C8164;
const int title_dword_800D8910 = 0x800CCCE4;
const int title_dword_800D8914 = 0x800CCD10;
const int title_dword_800D8918 = 0x800C8104;
const int title_dword_800D891C = 0x800CCDA0;
const int title_dword_800D8920 = 0x800C7A5C;
const int title_dword_800D8924 = 0x800C7A5C;
const int title_dword_800D8928 = 0x800C7A0C;
const int title_dword_800D892C = 0x800C760C;
const int title_dword_800D8930 = 0x800C6484;
const int title_dword_800D8934 = 0x800C65CC;
const int title_dword_800D8938 = 0x800C6714;
const int title_dword_800D893C = 0x800C6868;
const int title_dword_800D8940 = 0x800C69B0;
const int title_dword_800D8944 = 0x800C6B00;
const int title_dword_800D8948 = 0x800C6C80;
const int title_dword_800D894C = 0x800C6E48;
const int title_dword_800D8950 = 0x800C6FB4;
const int title_dword_800D8954 = 0x800C7128;
const int title_dword_800D8958 = 0x800C72AC;
const int title_dword_800D895C = 0x800C7440;
const int title_dword_800D8960 = 0x800C8194;
const int title_dword_800D8964 = 0x800C88F4;
const int title_dword_800D8968 = 0x800C911C;
const int title_dword_800D896C = 0x800C9C98;
const int title_dword_800D8970 = 0x800CA8A4;
const int title_dword_800D8974 = 0x800CB0B8;
const int title_dword_800D8978 = 0x800CB99C;
const int title_dword_800D897C = 0x800CC2B8;
const int title_dword_800D8980 = 0x800C8924;
const int title_dword_800D8984 = 0x800C8D80;
const int title_dword_800D8988 = 0x800C8D88;
const int title_dword_800D898C = 0x800C906C;
const int title_dword_800D8990 = 0x800C906C;
const int title_dword_800D8994 = 0x800C906C;
const int title_dword_800D8998 = 0x800C906C;
const int title_dword_800D899C = 0x800C8DE0;
const int title_dword_800D89A0 = 0x800C8E34;
const char title_dword_800D89A4[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D89A8 = 0x800C914C;
const int title_dword_800D89AC = 0x800C95C8;
const int title_dword_800D89B0 = 0x800C9AE4;
const int title_dword_800D89B4 = 0x800C95D0;
const int title_dword_800D89B8 = 0x800C9AE4;
const int title_dword_800D89BC = 0x800C9628;
const int title_dword_800D89C0 = 0x800C9AE4;
const int title_dword_800D89C4 = 0x800C9854;
const int title_dword_800D89C8 = 0x800C98AC;
const char title_dword_800D89CC[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D89D0 = 0x800C9CC8;
const int title_dword_800D89D4 = 0x800CA1A0;
const int title_dword_800D89D8 = 0x800CA1C0;
const int title_dword_800D89DC = 0x800CA1FC;
const int title_dword_800D89E0 = 0x800CA678;
const int title_dword_800D89E4 = 0x800CA240;
const int title_dword_800D89E8 = 0x800CA678;
const int title_dword_800D89EC = 0x800CA3EC;
const int title_dword_800D89F0 = 0x800CA440;
const char title_dword_800D89F4[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D89F8 = 0x800CA8D4;
const int title_dword_800D89FC = 0x800CAD4C;
const int title_dword_800D8A00 = 0x800CB038;
const int title_dword_800D8A04 = 0x800CB038;
const int title_dword_800D8A08 = 0x800CB038;
const int title_dword_800D8A0C = 0x800CB038;
const int title_dword_800D8A10 = 0x800CAD54;
const int title_dword_800D8A14 = 0x800CADAC;
const int title_dword_800D8A18 = 0x800CAE00;
const char title_dword_800D8A1C[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D8A20 = 0x800CB0E8;
const int title_dword_800D8A24 = 0x800CB5BC;
const int title_dword_800D8A28 = 0x800CB5DC;
const int title_dword_800D8A2C = 0x800CB8E8;
const int title_dword_800D8A30 = 0x800CB8E8;
const int title_dword_800D8A34 = 0x800CB8E8;
const int title_dword_800D8A38 = 0x800CB618;
const int title_dword_800D8A3C = 0x800CB65C;
const int title_dword_800D8A40 = 0x800CB6B0;
const char title_dword_800D8A44[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D8A48 = 0x800CB9CC;
const int title_dword_800D8A4C = 0x800CBEC0;
const int title_dword_800D8A50 = 0x800CC1EC;
const int title_dword_800D8A54 = 0x800CBEE0;
const int title_dword_800D8A58 = 0x800CC1EC;
const int title_dword_800D8A5C = 0x800CC1EC;
const int title_dword_800D8A60 = 0x800CBF1C;
const int title_dword_800D8A64 = 0x800CBF60;
const int title_dword_800D8A68 = 0x800CBFB4;
const char title_dword_800D8A6C[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D8A70 = 0x800CC2E8;
const int title_dword_800D8A74 = 0x800CC838;
const int title_dword_800D8A78 = 0x800CC858;
const int title_dword_800D8A7C = 0x800CC8A8;
const int title_dword_800D8A80 = 0x800CCBA0;
const int title_dword_800D8A84 = 0x800CCBA0;
const int title_dword_800D8A88 = 0x800CC8D0;
const int title_dword_800D8A8C = 0x800CC914;
const int title_dword_800D8A90 = 0x800CC968;
const char title_dword_800D8A94[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D8A98 = 0x800CCE20;
const int title_dword_800D8A9C = 0x800CCFB0;
const int title_dword_800D8AA0 = 0x800CCE58;
const int title_dword_800D8AA4 = 0x800CCEC0;
const int title_dword_800D8AA8 = 0x800CCF5C;
const int title_dword_800D8AAC = 0x800CCFB0;
const char title_aOpbackr_800D8AB0[] = "op_back_r";
const char title_aOpbackl_800D8ABC[] = "op_back_l";
const int title_dword_800D8AC8 = 0x800CD850;
const int title_dword_800D8ACC = 0x800CD86C;
const int title_dword_800D8AD0 = 0x800CD8CC;
const int title_dword_800D8AD4 = 0x800CD928;
const int title_dword_800D8AD8 = 0x800CD994;
const int title_dword_800D8ADC = 0x800CDA08;
const int title_dword_800D8AE0 = 0x800CDA68;
const char title_dword_800D8AE4[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D8AE8 = 0x800CE3B8;
const int title_dword_800D8AEC = 0x800CE3D8;
const int title_dword_800D8AF0 = 0x800CE408;
const int title_dword_800D8AF4 = 0x800CE440;
const int title_dword_800D8AF8 = 0x800CE4A0;
const char title_dword_800D8AFC[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D8B00 = 0x800CEB74;
const int title_dword_800D8B04 = 0x800CEC14;
const int title_dword_800D8B08 = 0x800CEC68;
const int title_dword_800D8B0C = 0x800CED18;
const int title_dword_800D8B10 = 0x800CEDC8;
const int title_dword_800D8B14 = 0x800CEE20;
const int title_dword_800D8B18 = 0x800CF808;
const int title_dword_800D8B1C = 0x800CFDE4;
const int title_dword_800D8B20 = 0x800D03C0;
const int title_dword_800D8B24 = 0x800D09A8;
const int title_dword_800D8B28 = 0x800D0F80;
const int title_dword_800D8B2C = 0x800D1550;
const char title_aClearflagd_800D8B30[] = "clear flag %d\n";
const char title_aCleardataexistss_800D8B40[] = "clear data exists %s\n";
const char title_aBislpm_800D8B58[] = "BISLPM-86111";
const char title_aOldclearflagd_800D8B68[] = "old clear flag %d\n";
const char title_aOldcleardataexistss_800D8B7C[] = "old clear data exists %s\n";
const char title_aGamedatafind_800D8B98[] = "gamedata find!\n";
const char title_aFlagx_800D8BA8[] = "flag = %x\n";
const char title_aFlagnewx_800D8BB4[] = "flag_new = %x\n";
const char title_aThisisrank_800D8BC4[] = "This Is Rank 0\n";
const char title_aThisisrank_800D8BD4[] = "This Is Rank 1\n";
const char title_aThisisrank_800D8BE4[] = "This Is Rank 2\n";
const char title_aThisisrank_800D8BF4[] = "This Is Rank 3\n";
const char title_aThisisrank_800D8C04[] = "This Is Rank 4\n";
const char title_aThisisrank_800D8C14[] = "This Is Rank 5\n";
const char title_aThisisrank_800D8C24[] = "This Is Rank 6\n";
const char title_aPhotodatafind_800D8C34[] = "photodata find!\n";
const char title_aVrfind_800D8C48[] = "VR find!\n";
const char title_aTitlememcardcheckreult_800D8C54[] = "-- Title MemCard Check Reult! --\n";
const char title_aSaveflagd_800D8C78[] = "save_flag = %d\n";
const char title_aPhotoflagd_800D8C88[] = "photo_flag = %d\n";
const char title_aVrflagd_800D8C9C[] = "vr_flag = %d\n";
const char title_aSperankd_800D8CAC[] = "spe_rank = %d\n";
const char title_aDemorankd_800D8CBC[] = "demo_rank = %d\n";
const char title_dword_800D8CCC[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D8CD0 = 0x800D2408;
const int title_dword_800D8CD4 = 0x800D2408;
const int title_dword_800D8CD8 = 0x800D2408;
const int title_dword_800D8CDC = 0x800D2414;
const int title_dword_800D8CE0 = 0x800D2414;
const int title_dword_800D8CE4 = 0x800D2430;
const int title_dword_800D8CE8 = 0x800D2430;
const int title_dword_800D8CEC = 0x800D2430;
const int title_dword_800D8CF0 = 0x800D2430;
const int title_dword_800D8CF4 = 0x800D244C;
const int title_dword_800D8CF8 = 0x800D243C;
const char title_aCdcaseopen_800D8CFC[] = "CD CASE OPEN!!\n";
const char title_aCdnormalspeedsetfailed_800D8D0C[] = "CD NORMAL SPEED SET FAILED!!\n";
const char title_aCdnormalspeedsetsuccess_800D8D2C[] = "CD NORMAL SPEED SET SUCCESS!!\n";
const char title_a_800D8D4C[] = "???????\n";
const char title_aThisisnotpsdisc_800D8D58[] = "THIS IS NOT PS DISC!!\n";
const char title_aCdstopfailed_800D8D70[] = "CD STOP FAILED!!\n";
const char title_aCdstopsuccess_800D8D84[] = "CD STOP SUCCESS!!\n";
const char title_aCdcaseclose_800D8D98[] = "CD CASE CLOSE!!\n";
const char title_aStartbuttonpush_800D8DAC[] = "START BUTTON PUSH!!\n";
const char title_aCdspinstart_800D8DC4[] = "CD SPIN START!!\n";
const char title_aCdnotspin_800D8DD8[] = "CD NOT SPIN!!\n";
const char title_aCdtocreadnotfinish_800D8DE8[] = "CD TOC READ NOT FINISH!!\n";
const char title_aCdtocreadsuccess_800D8E04[] = "CD TOC READ SUCCESS!!\n";
const char title_aCdspeedinitfailed_800D8E1C[] = "CD SPEED INIT FAILED!!\n";
const char title_aCdspeedinitsuccess_800D8E34[] = "CD SPEED INIT SUCCESS!!\n";
const char title_aCdcheckfailed_800D8E50[] = "CD CHECK FAILED!!\n";
const char title_aCdcheckok_800D8E64[] = "CD CHECK OK!!\n";
const char title_aThisisnotpsdisc_800D8E74[] = "THIS IS NOT PS DISC!!!\n";
const char title_aCdcheckerror_800D8E8C[] = "CD CHECK ERROR!!\n";
const char title_aThisispsdisc_800D8EA0[] = "THIS IS PS DISC!!\n";
const char title_aThisisdisc_800D8EB4[] = "THIS IS DISC 1!!\n";
const char title_aThisisnotdisc_800D8EC8[] = "THIS IS NOT DISC 1!!!\n";
const char title_aOkok_800D8EE0[] = "OK! OK!\n";
const char title_aNotoknotok_800D8EEC[] = "NOT OK! NOT OK!\n";
const int title_dword_800D8F00 = 0x800D24AC;
const int title_dword_800D8F04 = 0x800D254C;
const int title_dword_800D8F08 = 0x800D25F0;
const int title_dword_800D8F0C = 0x800D2620;
const int title_dword_800D8F10 = 0x800D2678;
const int title_dword_800D8F14 = 0x800D26B8;
const int title_dword_800D8F18 = 0x800D2708;
const int title_dword_800D8F1C = 0x800D2754;
const int title_dword_800D8F20 = 0x800D27BC;
const int title_dword_800D8F24 = 0x800D2984;
const int title_dword_800D8F28 = 0x800D29B8;
const char title_dword_800D8F2C[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D8F30 = 0x800D2E20;
const int title_dword_800D8F34 = 0x800D2D18;
const int title_dword_800D8F38 = 0x800D2D24;
const int title_dword_800D8F3C = 0x800D2D30;
const int title_dword_800D8F40 = 0x800D2D94;
const int title_dword_800D8F44 = 0x800D2D48;
const int title_dword_800D8F48 = 0x800D2D3C;
const int title_dword_800D8F4C = 0x800D2D88;
const int title_dword_800D8F50 = 0x800D2E20;
const char title_dword_800D8F54[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D8F58 = 0x800D2E20;
const int title_dword_800D8F5C = 0x800D2DDC;
const int title_dword_800D8F60 = 0x800D2DEC;
const int title_dword_800D8F64 = 0x800D2DFC;
const int title_dword_800D8F68 = 0x800D2E0C;
const char title_aVeryeasy_800D8F6C[] = "VERY EASY";
const char title_aEasy_800D8F78[] = "EASY";
const char title_aNormal_800D8F80[] = "NORMAL";
const char title_aHard_800D8F88[] = "HARD";
const char title_aExtreme_800D8F90[] = "EXTREME";
const int title_dword_800D8F98 = 0x800D2ED8;
const int title_dword_800D8F9C = 0x800D3024;
const int title_dword_800D8FA0 = 0x800D3170;
const int title_dword_800D8FA4 = 0x800D32B4;
const int title_dword_800D8FA8 = 0x800D33C4;
const char title_aMemorycardslot_800D8FAC[] = "MEMORY CARD SLOT 1  :  ";
const char title_aFull_800D8FC4[] = "   FULL";
const char title_aNocard_800D8FCC[] = "NO CARD";
const char title_aMemorycardslot_800D8FD4[] = "MEMORY CARD SLOT 2  :  ";
const char title_aDoyouwanttocontinue_800D8FEC[] = "DO YOU WANT TO CONTINUE\n";
const char title_aYourgamelikethis_800D9008[] = "YOUR GAME LIKE THIS?";
const char title_aYes_800D9020[] = "YES";
const char title_aNo_800D9024[] = "NO";

void OpenAct_800D37F4(OpenWork *work)
{
    u_long   *ot;
    POLY_FT4 *packs;

    ot = DG_ChanlOTag(1);
    packs = work->f18C_polys;

    title_open_800C628C(work);

    if (work->f24D4 == 0)
    {
        title_open_800D1CB4(work);
    }

    switch (work->fA74)
    {
    case 4:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            work->fB0C = 0;

            work->f30[0] = 1792;
            work->f30[1] = 1792;
            work->f30[2] = 1792;
            work->f30[3] = 1536;
            work->f30[4] = 1280;
            work->f30[5] = 1280;
            work->f30[6] = 1280;
            work->f30[7] = 256;

            GM_SetSound(0x1000001, 0);
        }

        title_open_800CD3B8(work, 0);
        title_open_800CD800(work, 3);
        title_open_800CDE44(work, 4);
        title_open_800CE378(work, 7);

        work->f164++;
        work->f168++;
        work->f16C++;
        work->f170++;
        work->f178++;
        work->f17C++;
        work->f180++;
        work->f184++;
        work->f188++;

        if (work->f164 >= 192)
        {
            work->fA74 = 5;
            work->fB0C = 1;
        }
        break;

    case 5:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            work->fB0C = 0;

            work->f30[0] = 1792;
            work->f30[1] = 1792;
            work->f30[2] = 1792;
            work->f30[3] = 1536;
            work->f30[4] = 1280;
            work->f30[5] = 1280;
            work->f30[6] = 1280;
            work->f30[7] = 256;
            work->f30[8] = 256;
            work->f30[9] = 768;
            work->f30[10] = 512;
            work->f30[11] = 1024;
            work->f30[12] = 256;
        }

        title_open_800CCDC8(work);
        title_open_800CD074(work);
        title_open_800CE748(work, 0);
        title_open_800CEB14(work, 3);
        title_open_800CEF54(work, 4);
        title_open_800CE378(work, 7);
        title_open_800CE4A8(work, 8);
        title_open_800CE544(work, 9);
        title_open_800CE5F8(work, 12);
        title_open_800CE6AC(work, 11);

        work->f164++;
        work->f168++;
        work->f16C++;
        work->f170++;
        work->f174++;
        work->f178++;
        work->f17C++;
        work->f180++;
        work->f184++;
        work->f188++;

        if (work->f164 > 407)
        {
            work->fA74 = 6;
            work->fA98 = 2;
            work->f184 = 0;
            work->fB0C = 1;
        }
        break;

    case 6:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            work->fB0C = 0;

            work->f30[0] = 1792;
            work->f30[1] = 1792;
            work->f30[2] = 1792;
            work->f30[3] = 1536;
            work->f30[4] = 1280;
            work->f30[5] = 1280;
            work->f30[6] = 1280;
            work->f30[7] = 256;
            work->f30[8] = 256;
            work->f30[9] = 768;
            work->f30[10] = 512;
            work->f30[11] = 1024;
            work->f30[12] = 256;

            setRGB0(&packs[7], 128, 128, 128);
            setRGB0(&packs[8], 128, 128, 128);
            setRGB0(&packs[9], 128, 128, 128);
            setRGB0(&packs[10], 128, 128, 128);
            setRGB0(&packs[11], 128, 128, 128);
            setRGB0(&packs[12], 128, 128, 128);

            if (work->fA7C == 0)
            {
                work->fA7C = 1;
            }

            if (work->fA80 == 0)
            {
                work->fA80 = 1;
                work->f170 = 0;
            }

            if (work->fA84 == 0)
            {
                work->fA84 = 1;
                work->f170 = 0;
            }

            work->fA98 = 2;
            work->f184 = 0;
            work->fB00 = 0;

            GM_SetSound(0x1000001, 0);
        }

        title_open_800CCDC8(work);
        title_open_800CD074(work);
        title_open_800CE748(work, 0);
        title_open_800CEB14(work, 3);
        title_open_800CEF54(work, 4);
        title_open_800CF504(work, 12);
        title_open_800C5644(work, 10);

        work->f164++;
        work->f168++;
        work->f16C++;
        work->f170++;
        work->f174++;
        work->f184++;
        break;

    case 7:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            work->fB0C = 0;

            work->f30[0] = 1792;
            work->f30[1] = 1792;
            work->f30[2] = 1792;
            work->f30[3] = 1536;
            work->f30[4] = 1280;
            work->f30[5] = 1280;
            work->f30[6] = 1280;
            work->f30[7] = 256;
            work->f30[8] = 256;
            work->f30[9] = 768;
            work->f30[10] = 512;
            work->f30[11] = 1024;

            if (!sd_sng_play())
            {
                GM_SetSound(0x1000001, 0);
            }

            switch (work->fA78)
            {
            case 0:
                work->fE0[0] = 256;
                work->fE0[1] = 256;
                work->fE0[2] = 0;
                work->fE0[3] = 0;
                work->fE0[4] = 256;
                work->fE0[5] = 0;
                break;

            case 1:
                work->fE0[0] = 256;
                work->fE0[1] = 256;
                work->fE0[2] = 256;
                work->fE0[3] = 0;
                work->fE0[4] = 0;
                work->fE0[5] = 0;
                break;

            case 2:
                work->fE0[0] = 0;
                work->fE0[1] = 256;
                work->fE0[2] = 256;
                work->fE0[3] = 256;
                work->fE0[4] = 0;
                work->fE0[5] = 0;
                break;

            case 3:
                work->fE0[0] = 0;
                work->fE0[1] = 0;
                work->fE0[2] = 256;
                work->fE0[3] = 256;
                work->fE0[4] = 256;
                work->fE0[5] = 0;
                break;

            case 4:
                work->fE0[0] = 256;
                work->fE0[1] = 0;
                work->fE0[2] = 0;
                work->fE0[3] = 256;
                work->fE0[4] = 256;
                work->fE0[5] = 0;
                break;

            case 5:
                work->fE0[0] = 256;
                work->fE0[1] = 0;
                work->fE0[2] = 0;
                work->fE0[3] = 0;
                work->fE0[4] = 256;
                work->fE0[5] = 256;
            }
        }

        title_open_800CCDC8(work);
        title_open_800CD074(work);
        title_open_800CE748(work, 0);
        title_open_800CEB14(work, 3);
        title_open_800CEF54(work, 4);

        switch (work->fA78)
        {
        case 0:
            title_open_800CF610(work, 0);
            break;

        case 1:
            title_open_800CF610(work, 1);
            break;

        case 2:
            title_open_800CF610(work, 2);
            break;

        case 3:
            title_open_800CF610(work, 3);
            break;

        case 4:
            title_open_800CF610(work, 4);
            break;

        case 5:
            title_open_800CF610(work, 5);
            break;
        }

        title_open_800C5644(work, 10);
        title_open_800CF794(work);

        work->f164++;
        work->f168++;
        work->f16C++;
        work->f170++;
        work->f174++;
        work->f184++;
        break;

    case 9:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            title_open_800C5CF0(work);
            title_open_800C5D10(work);

            work->fB0C = 0;
            work->f24C4 = 0;
            *(void **)((char *)work + 0x24A8) = NewMetalGearLogo(&work->f24C4);
        }

        title_open_800D2A00(work);
        break;

    case 16:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            title_open_800C5CF0(work);
            title_open_800C5D10(work);

            work->fB0C = 0;
            work->f24C4 = 0;
            *(void **)((char *)work + 0x24A8) = NewMetalGearLogo(&work->f24C4);
        }

        title_open_800D2AFC(work);
        break;

    case 13:
        work->fB00 = 0;
        title_open_800D2CA8(work, ot);
        break;

    case 18:
    case 19:
        work->fB00 = 0;
        title_open_800D3500(work, ot);
        break;

    case 21:
        work->fB00 = 0;
        title_open_800D2E44(work, ot);
        break;

    case 0:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            title_open_800C5CF0(work);
            work->fB0C = 0;
            work->f30[18] = 256;
            work->f30[19] = 256;
        }

        title_open_800CD23C(work, 18, 1);
        work->f164++;
        break;

    case 1:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            work->fB0C = 0;
            work->f30[20] = 256;
            work->f30[21] = 256;
        }

        title_open_800CD23C(work, 20, 15);
        work->fB00 = 0;
        work->f164++;
        break;

    case 2:
        title_open_800CD320(work, 18);
        work->fB00 = 0;
        work->f164++;
        break;

    case 3:
        title_open_800CD320(work, 20);
        work->fB00 = 0;
        work->f164++;
        break;
    }

    title_open_800C53E0(work);
}

void OpenDie_800D4098(OpenWork *work)
{
    int      i;
    void    *buf;

    GM_FreePrim(work->prim[0]);
    GM_FreePrim(work->prim[2]);
    GM_FreePrim(work->prim[3]);
    GM_FreePrim(work->prim[1]);

    for (i = 0; i < 24; i++)
    {
        buf = title_open_800C4B20(&work->kcb[i]);
        GV_FreeMemory(GV_NORMAL_MEMORY, buf);
    }
}

void title_open_800D4174(OpenWork *work, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    setPolyFT4(poly);
    setRGB0(poly, 128, 128, 128);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

static inline void title_open_helper_800D41E4(POLY_FT4 *poly, DG_TEX *tex, int uo, int vo)
{
    int u0, u1;
    int v0, v1;

    u0 = tex->off_x;
    u1 = u0 + tex->w + uo;
    v0 = tex->off_y;
    v1 = v0 + tex->h + vo;
    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

void title_open_800D41E4(OpenWork *work, int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe, int type)
{
    DG_TEX *tex;

    title_open_800D4174(work, poly, x0, y0, x1, y1, abe);

    tex = DG_GetTexture(name);
    if (type == 0)
    {
        title_open_helper_800D41E4(poly, tex, 1, 1);
    }
    else if (type == 1)
    {
        title_open_helper_800D41E4(poly, tex, 1, 0);
    }
    else if (type == 2)
    {
        title_open_helper_800D41E4(poly, tex, 0, 1);
    }
    else if (type == 3)
    {
        title_open_helper_800D41E4(poly, tex, 0, 0);
    }
}

void title_open_800D4368(OpenWork *work, int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    DG_TEX *tex;
    int     u0, u1;
    int     v0, v1;

    tex = DG_GetTexture(name);

    setPolyFT4(poly);

    u0 = tex->off_x;
    u1 = u0 + tex->w + 1;
    v0 = tex->off_y;
    v1 = v0 + tex->h + 1;
    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;

    setRGB0(poly, 0, 0, 0);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

void title_open_800D4464(OpenWork *work, int name, POLY_GT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    DG_TEX *tex;
    int     u0, u1;
    int     v0, v1;

    tex = DG_GetTexture(name);

    setPolyGT4(poly);

    u0 = tex->off_x;
    u1 = u0 + tex->w + 1;
    v0 = tex->off_y;
    v1 = v0 + tex->h + 1;
    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;

    setRGB0(poly, 0, 0, 0);
    setRGB1(poly, 0, 0, 0);
    setRGB2(poly, 0, 0, 0);
    setRGB3(poly, 0, 0, 0);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

#pragma INCLUDE_ASM("asm/overlays/title/OpenGetResources_800D4584.s")
int  OpenGetResources_800D4584(OpenWork *work, int);

void *NewOpen(int arg0, int arg1)
{
    OpenWork *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = GV_NewActor(EXEC_LEVEL, sizeof(OpenWork));
    title_dword_800D92D0 = 0;

    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, OpenAct_800D37F4, OpenDie_800D4098, aOpenC);

        if (OpenGetResources_800D4584(work, arg1) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
