#include "common.h"
#include "libdg/libdg.h"
#include "Anime/animconv/anime.h"
#include "strcode.h"

const char anim_data_800CC124[] = {0x0, 0x1d, 0x3, 0x0};
const char s03e_dword_800CC128[] = {0x9, 0x0, 0x10, 0x0};
const char s03e_dword_800CC12C[] = {0x1b, 0x9, 0xb, 0xb8};
const char s03e_dword_800CC130[] = {0x2, 0x0, 0x1, 0xf};
const char s03e_dword_800CC134[] = {0x7, 0x3, '\n', 0xff};
const char s03e_dword_800CC138[] = {'8', 0xff, '8', 0x2};
const char s03e_dword_800CC13C[] = {0x0, 0x1, 0xf, 0x7};
const char s03e_dword_800CC140[] = {0x3, '\n', 0xfe, 0x98};
const char s03e_dword_800CC144[] = {0xfe, 0xfc, 0x2, 0x0};
const char s03e_dword_800CC148[] = {0x1, 0xf};

const char anim_data_800CC14C[] = {0x0, 0x13, 0x1, 0x0};
const char s03e_dword_800CC150[] = {0x5, 0xc, 0x0, 0x7};
const char s03e_dword_800CC154[] = {0x1, 0xff, '\n', 0x0};
const char s03e_dword_800CC158[] = {'F', 0x0, 'F', 0x8};
const char s03e_dword_800CC15C[] = {0xf0, 0xf0, 0xf0, 0x2};
const char s03e_dword_800CC160[] = {0x0, 0x1, 0xd, 0xf};

const char anim_data_800CC164[] = {0x0, '[', 0x4, 0x0};
const char s03e_dword_800CC168[] = {0xb, 0x0, 0x1e, 0x0};
const char s03e_dword_800CC16C[] = {'6', 0x0, 'N', 0xc};
const char s03e_dword_800CC170[] = {0x0, 0x7, 0x1, 0xff};
const char s03e_dword_800CC174[] = {'\n', 0x0, 0xc8, 0x0};
const char s03e_dword_800CC178[] = {0xc8, 0x8, 0xf0, 0xf0};
const char s03e_dword_800CC17C[] = {0xf0, 0x2, 0x0, 0x1};
const char s03e_dword_800CC180[] = {0xd, 0xf, '\n', 0x1};
const char s03e_dword_800CC184[] = {0x90, 0x1, 0x90, 0xc};
const char s03e_dword_800CC188[] = {0x0, 0x7, 0x1, 0xff};
const char s03e_dword_800CC18C[] = {'\n', 0x1, ',', 0x1};
const char s03e_dword_800CC190[] = {',', 0x8, 0xf0, 0xf0};
const char s03e_dword_800CC194[] = {0xf0, 0x2, 0x0, 0x1};
const char s03e_dword_800CC198[] = {0xd, 0xf, '\n', 0x3};
const char s03e_dword_800CC19C[] = {' ', 0x3, ' ', 0xc};
const char s03e_dword_800CC1A0[] = {0x0, 0x7, 0x1, 0xff};
const char s03e_dword_800CC1A4[] = {'\n', 0x1, 0x90, 0x1};
const char s03e_dword_800CC1A8[] = {0x90, 0x8, 0xf0, 0xf0};
const char s03e_dword_800CC1AC[] = {0xf0, 0x2, 0x0, 0x1};
const char s03e_dword_800CC1B0[] = {0xd, 0xf, '\n', 0x4};
const char s03e_dword_800CC1B4[] = {0xb0, 0x4, 0xb0, 0xc};
const char s03e_dword_800CC1B8[] = {0x0, 0x7, 0x1, 0xff};
const char s03e_dword_800CC1BC[] = {'\n', 0x1, 0xf4, 0x1};
const char s03e_dword_800CC1C0[] = {0xf4, 0x8, 0xf0, 0xf0};
const char s03e_dword_800CC1C4[] = {0xf0, 0x2, 0x0, 0x1};
const char s03e_dword_800CC1C8[] = {0xd, 0xf};

const char anim_data_800CC1CC[] = {0x0, 'k', 0x4, 0x0};
const char s03e_dword_800CC1D0[] = {0xb, 0x0, '"', 0x0};
const char s03e_dword_800CC1D4[] = {'>', 0x0, 'Z', 0x8};
const char s03e_dword_800CC1D8[] = {0xff, 0xff, 0xff, 0xc};
const char s03e_dword_800CC1DC[] = {0x0, 0x7, 0x1, 0xff};
const char s03e_dword_800CC1E0[] = {'\n', 0x0, 0xc8, 0x0};
const char s03e_dword_800CC1E4[] = {0xc8, 0x8, 0xf0, 0xf0};
const char s03e_dword_800CC1E8[] = {0xf0, 0x2, 0x0, 0x1};
const char s03e_dword_800CC1EC[] = {0xd, 0xf, 0x8, 0xff};
const char s03e_dword_800CC1F0[] = {0xff, 0xff, '\n', 0x1};
const char s03e_dword_800CC1F4[] = {0x90, 0x1, 0x90, 0xc};
const char s03e_dword_800CC1F8[] = {0x0, 0x7, 0x1, 0xff};
const char s03e_dword_800CC1FC[] = {'\n', 0x1, ',', 0x1};
const char s03e_dword_800CC200[] = {',', 0x8, 0xf0, 0xf0};
const char s03e_dword_800CC204[] = {0xf0, 0x2, 0x0, 0x1};
const char s03e_dword_800CC208[] = {0xd, 0xf, 0x8, 0xff};
const char s03e_dword_800CC20C[] = {0xff, 0xff, '\n', 0x3};
const char s03e_dword_800CC210[] = {' ', 0x3, ' ', 0xc};
const char s03e_dword_800CC214[] = {0x0, 0x7, 0x1, 0xff};
const char s03e_dword_800CC218[] = {'\n', 0x1, 0x90, 0x1};
const char s03e_dword_800CC21C[] = {0x90, 0x8, 0xf0, 0xf0};
const char s03e_dword_800CC220[] = {0xf0, 0x2, 0x0, 0x1};
const char s03e_dword_800CC224[] = {0xd, 0xf, 0x8, 0xff};
const char s03e_dword_800CC228[] = {0xff, 0xff, '\n', 0x4};
const char s03e_dword_800CC22C[] = {0xb0, 0x4, 0xb0, 0xc};
const char s03e_dword_800CC230[] = {0x0, 0x7, 0x1, 0xff};
const char s03e_dword_800CC234[] = {'\n', 0x1, 0xf4, 0x1};
const char s03e_dword_800CC238[] = {0xf4, 0x8, 0xf0, 0xf0};
const char s03e_dword_800CC23C[] = {0xf0, 0x2, 0x0, 0x1};
const char s03e_dword_800CC240[] = {0xd, 0xf};

const char anim_data_800CC244[] = {0x0, '[', 0x4, 0x0};
const char s03e_dword_800CC248[] = {0xb, 0x0, 0x1e, 0x0};
const char s03e_dword_800CC24C[] = {'6', 0x0, 'N', 0xc};
const char s03e_dword_800CC250[] = {0x0, 0x7, 0x1, 0xff};
const char s03e_dword_800CC254[] = {'\n', 0x0, 0xc8, 0x0};
const char s03e_dword_800CC258[] = {0xc8, 0x8, 0xfc, 0xfc};
const char s03e_dword_800CC25C[] = {0xfc, 0x2, 0x0, 0x1};
const char s03e_dword_800CC260[] = {0xd, 0xf, '\n', 0x1};
const char s03e_dword_800CC264[] = {0x90, 0x1, 0x90, 0xc};
const char s03e_dword_800CC268[] = {0x0, 0x7, 0x1, 0xff};
const char s03e_dword_800CC26C[] = {'\n', 0x1, ',', 0x1};
const char s03e_dword_800CC270[] = {',', 0x8, 0xfc, 0xfc};
const char s03e_dword_800CC274[] = {0xfc, 0x2, 0x0, 0x1};
const char s03e_dword_800CC278[] = {0xd, 0xf, '\n', 0x3};
const char s03e_dword_800CC27C[] = {' ', 0x3, ' ', 0xc};
const char s03e_dword_800CC280[] = {0x0, 0x7, 0x1, 0xff};
const char s03e_dword_800CC284[] = {'\n', 0x1, 0x90, 0x1};
const char s03e_dword_800CC288[] = {0x90, 0x8, 0xfc, 0xfc};
const char s03e_dword_800CC28C[] = {0xfc, 0x2, 0x0, 0x1};
const char s03e_dword_800CC290[] = {0xd, 0xf, '\n', 0x4};
const char s03e_dword_800CC294[] = {0xb0, 0x4, 0xb0, 0xc};
const char s03e_dword_800CC298[] = {0x0, 0x7, 0x1, 0xff};
const char s03e_dword_800CC29C[] = {'\n', 0x1, 0xf4, 0x1};
const char s03e_dword_800CC2A0[] = {0xf4, 0x8, 0xfc, 0xfc};
const char s03e_dword_800CC2A4[] = {0xfc, 0x2, 0x0, 0x1};
const char s03e_dword_800CC2A8[] = {0xd, 0xf};

ANIMATION anm_800C3B78 = {PCX_SOCOM_F, 2, 2, 4, 1, 300, 1, 800, 800, 128, NULL, (char *)anim_data_800CC124};
ANIMATION anm_800C3B94 = {PCX_SMOKE, 8, 4, 30, 1, 500, 1, 400, 400, 128, NULL, (char *)anim_data_800CC14C};
ANIMATION anm_800C3BB0 = {PCX_SMOKE, 8, 4, 30, 1, 500, 1, 400, 400, 128, NULL, (char *)anim_data_800CC164};
ANIMATION anm_800C3BCC = {PCX_SMOKE, 8, 4, 30, 1, 500, 1, 400, 400, 0, NULL, (char *)anim_data_800CC1CC};
ANIMATION anm_800C3BE8 = {PCX_SMOKE, 8, 4, 30, 1, 500, 2, 400, 400, 32, NULL, (char *)anim_data_800CC244};

extern ANIMATION stru_8009F0D4;
extern ANIMATION stru_8009F0F0;

void AN_Unknown_800D6898(MATRIX *pos)
{
    PRESCRIPT  pre;
    SVECTOR   *pPos;
    SVECTOR   *pSpeed;
    ANIMATION *anm;
    SVECTOR    sp28;
    MATRIX     sp30;
    int        rnd;

    pPos = &pre.pos;
    pSpeed = &pre.speed;

    pre.speed = DG_ZeroVector;

    rnd = GV_RandU(16);
    if (rnd >= 7)
    {
        pre.s_anim = 3;
    }
    else if (rnd >= 5)
    {
        pre.s_anim = 2;
    }
    else if (rnd >= 3)
    {
        pre.s_anim = 1;
    }
    else
    {
        pre.s_anim = 0;
    }

    anm = &anm_800C3B78;
    anm->pre_script = &pre;

    pPos->vx = pos->t[0];
    pPos->vy = pos->t[1];
    pPos->vz = pos->t[2];
    pre.scr_num = 0;

    NewAnime(NULL, 0, anm);

    sp28.vx = 0;
    sp28.vy = 0;
    sp28.vz = 420;

    DG_SetPos(pos);
    DG_MovePos(&sp28);
    ReadRotMatrix(&sp30);

    pPos->vx = sp30.t[0];
    pPos->vy = sp30.t[1];
    pPos->vz = sp30.t[2];
    pre.scr_num = 2;

    NewAnime(NULL, 0, anm);

    if (GV_RandU(16) >= 5)
    {
        sp28.vx = 0;
        sp28.vy = 0;
        sp28.vz = -800;

        DG_SetPos(pos);
        DG_MovePos(&sp28);
        ReadRotMatrix(&sp30);

        pPos->vx = sp30.t[0];
        pPos->vy = sp30.t[1];
        pPos->vz = sp30.t[2];

        sp28.vx = GV_RandU(32) - 100;
        sp28.vy = GV_RandU(32) + 15;
        sp28.vz = GV_RandU(64) + 100;

        DG_MovePos(&sp28);
        ReadRotMatrix(&sp30);

        pSpeed->vx = pPos->vx - sp30.t[0];
        pSpeed->vy = pPos->vy - sp30.t[1];
        pSpeed->vz = sp30.t[2] - pPos->vz;
        pre.scr_num = 2;
        pre.s_anim = 0;

        anm = &stru_8009F0D4;
        anm->pre_script = &pre;

        NewAnime(NULL, 0, anm);
    }

    if (GV_RandU(16) >= 9)
    {
        sp28.vx = 0;
        sp28.vy = 0;
        sp28.vz = -500;

        DG_SetPos(pos);
        DG_MovePos(&sp28);
        ReadRotMatrix(&sp30);

        pPos->vx = sp30.t[0];
        pPos->vy = sp30.t[1];
        pPos->vz = sp30.t[2];

        sp28.vx = 0;
        sp28.vy = 0;
        sp28.vz = -GV_RandU(32);

        DG_MovePos(&sp28);
        ReadRotMatrix(&sp30);

        pSpeed->vx = pPos->vx - sp30.t[0];
        pSpeed->vy = pPos->vy - sp30.t[1];
        pSpeed->vz = pPos->vz - sp30.t[2];
        pre.s_anim = 0;
        pre.scr_num = 3;

        anm = &stru_8009F0F0;
        anm->pre_script = &pre;

        NewAnime(NULL, 0, anm);
    }
}

void AN_Unknown_800D6BCC(SVECTOR *pos, SVECTOR *rot)
{
    PRESCRIPT  pre;
    SVECTOR   *pPos;
    SVECTOR   *pSpeed;
    ANIMATION *anm;
    SVECTOR    sp28[4];
    SVECTOR    sp48[6]; // The stack has an extra 32 unused bytes
    int        rnd;

    pPos = &pre.pos;
    pSpeed = &pre.speed;

    sp28[0].vx = 0;
    sp28[0].vy = 0;
    sp28[0].vz = 250;

    sp28[1].vx = 0;
    sp28[1].vy = 0;
    sp28[1].vz = 420;

    sp28[2].vx = -100;
    sp28[2].vy = 0;
    sp28[2].vz = -800;

    sp28[3].vx = 0;
    sp28[3].vy = 0;
    sp28[3].vz = -500;

    DG_SetPos2(pos, rot);
    DG_PutVector(sp28, sp28, 4);

    sp48[0].vx = -100 - GV_RandU(32);
    sp48[0].vy = GV_RandU(32) + 15;
    sp48[0].vz = GV_RandS(4);

    sp48[1].vx = 0;
    sp48[1].vy = 0;
    sp48[1].vz = -GV_RandU(32);

    DG_SetPos2(&DG_ZeroVector, rot);
    DG_PutVector(sp48, sp48, 2);

    pre.speed = DG_ZeroVector;

    rnd = GV_RandU(16);
    if (rnd >= 7)
    {
        pre.s_anim = 3;
    }
    else if (rnd >= 5)
    {
        pre.s_anim = 2;
    }
    else if (rnd >= 3)
    {
        pre.s_anim = 1;
    }
    else
    {
        pre.s_anim = 0;
    }

    anm = &anm_800C3B78;
    anm->pre_script = &pre;

    *pPos = *pos;
    pre.scr_num = 0;

    NewAnime(NULL, 0, anm);

    *pPos = sp28[1];
    pre.scr_num = 2;

    NewAnime(NULL, 0, anm);

    if (GV_RandU(16) >= 5)
    {
        *pPos = sp28[2];
        *pSpeed = sp48[0];
        pre.scr_num = 2;
        pre.s_anim = 0;

        anm = &stru_8009F0D4;
        anm->pre_script = &pre;

        NewAnime(NULL, 0, anm);
    }

    if (GV_RandU(16) >= 9)
    {
        *pPos = sp28[3];
        *pSpeed = sp48[1];
        pre.s_anim = 0;
        pre.scr_num = 3;

        anm = &stru_8009F0F0;
        anm->pre_script = &pre;

        NewAnime(NULL, 0, anm);
    }
}

void AN_Unknown_800D6EB0(SVECTOR *pos)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.scr_num = 0;
    pre.s_anim = GV_RandU(1024) % 30;

    anm = &anm_800C3B94;
    anm->pre_script = &pre;

    NewAnime(NULL, 0, anm);
}

void AN_Unknown_800D6F6C(SVECTOR *pos)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.scr_num = 0;
    pre.s_anim = GV_RandU(1024) % 30;

    anm = &anm_800C3BB0;
    anm->pre_script = &pre;

    NewAnime(NULL, 0, anm);
}

void AN_Unknown_800D7028(SVECTOR *pos, int num)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.scr_num = num;
    pre.s_anim = GV_RandU(1024) % 30;

    anm = &anm_800C3BE8;
    anm->pre_script = &pre;

    NewAnime(NULL, 0, anm);
}

void AN_Unknown_800D70E4(SVECTOR *pos, char r, char g, char b)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.scr_num = 0;
    pre.s_anim = GV_RandU(1024) % 30;

    anm = &anm_800C3BCC;
    anm->pre_script = &pre;

    anm->field_18_ptr[12] = r;
    anm->field_18_ptr[13] = g;
    anm->field_18_ptr[14] = b;

    anm->field_18_ptr[35] = r;
    anm->field_18_ptr[36] = g;
    anm->field_18_ptr[37] = b;

    anm->field_18_ptr[63] = r;
    anm->field_18_ptr[64] = g;
    anm->field_18_ptr[65] = b;

    anm->field_18_ptr[91] = r;
    anm->field_18_ptr[92] = g;
    anm->field_18_ptr[93] = b;

    anm->field_18_ptr[26] = -((r - 1) / 7);
    anm->field_18_ptr[27] = -((g - 1) / 7);
    anm->field_18_ptr[28] = -((b - 1) / 7);

    anm->field_18_ptr[54] = -((r - 1) / 7);
    anm->field_18_ptr[55] = -((g - 1) / 7);
    anm->field_18_ptr[56] = -((b - 1) / 7);

    anm->field_18_ptr[82] = -((r - 1) / 7);
    anm->field_18_ptr[83] = -((g - 1) / 7);
    anm->field_18_ptr[84] = -((b - 1) / 7);

    anm->field_18_ptr[110] = -((r - 1) / 7);
    anm->field_18_ptr[111] = -((g - 1) / 7);
    anm->field_18_ptr[112] = -((b - 1) / 7);

    NewAnime(NULL, 0, anm);
}
