#ifndef _VALCAN_H_
#define _VALCAN_H_

#include "mgstype.h"
#include "libgv/libgv.h"
#include "game/game.h"

// Raven (Vulcan Raven, "valcan") boss of s15a/s15c.
// The original code is split in three objects (see the uninitialized memory
// between their .rdata): valcan.c, val_life.c and val_ai.c (the names of the
// last two are made up).

typedef struct _Work
{
    GV_ACT         actor;
    int            field_20;
    CONTROL        control;
    OBJECT         field_A0;
    OBJECT         field_184;
    MOTION_CONTROL field_268;
    MOTION_SEGMENT field_2B8;
    char           pad2DC[0x240];
    SVECTOR        field_51C;
    SVECTOR        field_524;
    char           pad52C[0x78];
    SVECTOR        field_5A4[0x10];
    MATRIX         field_624[2];
    TARGET        *field_664;
    TARGET        *field_668;
    int            field_66C;
    int            field_670;
    char           pad674[0x10];
    int            field_684;
    int            field_688;
    int            field_68C;
    int            field_690;
    int            field_694;
    int            field_698;
    int            field_69C;
    int            field_6A0;
    int            field_6A4;
    int            field_6A8;
    int            field_6AC;
    int            field_6B0;
    int            field_6B4;
    int            field_6B8;
    int            field_6BC;
    int            field_6C0;
    SVECTOR        field_6C4;
    SVECTOR        field_6CC;
    SVECTOR        field_6D4[4];
    DG_PRIM       *field_6F4;
    short          field_6F8[4][4][2];
    short          field_738;
    short          field_73A;
    short          field_73C;
    short          field_73E;
    int            field_740;
    int            field_744[4];
    short          field_754;
    short          field_756;
    int            field_758;
    int            field_75C;
    int            field_760;
    int            field_764;
    int            field_768;
    int            field_76C;
    int            field_770;
    int            field_774;
    int            field_778;
    int            field_77C;
    int            field_780;
    int            field_784;
    int            field_788;
    int            field_78C;
    int            field_790;
    int            field_794;
    int            field_798;
    int            field_79C;
    short          field_7A0;
    short          field_7A2;
    SVECTOR        field_7A4;
    SVECTOR        field_7AC;
    int            field_7B4;
    char           pad7B8[0x1C];
    int            field_7D4;
    int            field_7D8;
    char           field_7DC[32][2]; // could be smaller
    int            field_81C;
    int            field_820;
    int            field_824;
    int            field_828;
    int            field_82C;
    int            field_830;
    int            field_834;
    int            field_838;
    int            field_83C;
    int            field_840;
    char           pad844[0x34];
    SVECTOR        field_878;
    char           pad880[0x50];
    int            field_8D0;
    int            field_8D4;
    int            field_8D8;
    int            field_8DC;
    int            field_8E0;
    int            field_8E4;
    int            field_8E8;
    int            field_8EC;
    int            field_8F0;
    MENU_BAR_CONF  lifebar_8F4;
    int            field_900;
    int            field_904;
    char           pad908[4];
    int            field_90C;
    SVECTOR        field_910;
    int            field_918;
    int            field_91C;
    int            field_920;
    int            field_924;
    HZD_SEG        field_928;
    int            field_938;
    int            field_93C;
    int            field_940;
    int            field_944;
    int            field_948;
    int            field_94C;
    int            field_950;
} Work;

#define SEGMENT_ATR ( HZD_SEG_NO_NAVIGATE )

extern SVECTOR valcan_pos_800E3470;

/* dyncon.c */
extern int dyncon_800E3448[4];
extern int dyncon_800E3458[4];

int Valcan_800D8D20(CONTROL *control, SVECTOR *svec1);
void ValcanQueueDynamicSegment_800D8D5C(Work *work, int flag);
void ValcanDequeueDynamicSegment_800D8DA0(Work *work);
void Valcan_800D8DD8(Work *work);
void ValcanGetInts_800D8E88(unsigned char *opt, int *out);
void s15c_valcan_800D8ECC(Work *work);
void Valcan_800D9028(POLY_FT4 *prims, DG_TEX *tex);
void ValcanAct_800D9088(Work *work);
int ValcanGetResources_800D92A8(Work *work, int name, int where);
void ValcanDie_800D96E8(Work *work);
int ValcanGetResources2_800D9774(Work *work);
int ValcanGetResources_800D9830(Work *work, int name, int where);
void *NewValcan_800D9864(int name, int where);
void Valcan_800D990C(Work *work);
void Valcan_800D99F0(Work *work);
void Valcan_800D9AB8(Work *work);
void Valcan_800D9B3C(Work *work);
void Valcan_800D9B5C(Work *work);
void Valcan_800D9D90(Work *work);
int Valcan_800D9DC0(Work *work, int param_2);
void Valcan_800D9EBC(SVECTOR *from, SVECTOR *to, SVECTOR *out);
void Valcan_800D9F3C(Work *work, int count);
void Valcan_800D9F8C(Work *work);
void Valcan_800DA044(Work *work);
void Valcan_800DA140(Work *work);
int Valcan_800DA1AC(int arg0, int arg1);
void Valcan_800DA21C(Work *work);
int Valcan_800DA2A8(Work *work);
int Valcan_800DA558(Work *work, int arg1);
void Valcan_800DA8E4(Work *work);
void Valcan_800DA990(Work *work);
void Valcan_800DACCC(Work *work);
int Valcan_800DAE38();
int Valcan_800DAE7C(Work *work);
int Valcan_800DAFCC(Work *work);
int Valcan_800DB200(Work *work);
int Valcan_800DB2E4(Work *work);
int Valcan_800DB470(Work *work);
void Valcan_800DB500(Work *work);
void Valcan_800DB868(Work *work);
void Valcan_800DB9F0(Work *work);
void Valcan_800DBCB4(Work *work);
void Valcan_800DBF74(Work *work);
void Valcan_800DC06C(Work *work, int index, int blood_count);
void Valcan_800DC124(Work *work);
void Valcan_800DC290(Work *work, int arg1, int arg2);
void Valcan_800DC2EC(Work *work, int action);
void Valcan_800DC318(Work *work);
void Valcan_800DC7A0(Work *work);
void Valcan_800DCC84(Work *work);
void Valcan_800DCE60(Work *work);
void Valcan_800DCF8C(Work *work);
void Valcan_800DD03C(Work *work);
void Valcan_800DD578(Work *work);


#endif // _VALCAN_H_
