#include "Anime/animeconv/anime.h"

extern SVECTOR   DG_ZeroVector_800AB39C;
extern ANIMATION stru_8009F0D4;
extern ANIMATION stru_8009F0F0;
extern ANIMATION anm_800C3B78;
extern ANIMATION anm_800C3B94;
extern ANIMATION anm_800C3BB0;
extern ANIMATION anm_800C3BCC;
extern ANIMATION anm_800C3BE8;

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

    pre.speed = DG_ZeroVector_800AB39C;

    rnd = GV_RandU_80017090(16);
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
    anm->field_14_pre_script = &pre;

    pPos->vx = pos->t[0];
    pPos->vy = pos->t[1];
    pPos->vz = pos->t[2];
    pre.scr_num = 0;

    NewAnime_8005FBC8(NULL, 0, anm);

    sp28.vx = 0;
    sp28.vy = 0;
    sp28.vz = 420;

    DG_SetPos_8001BC44(pos);
    DG_MovePos_8001BD20(&sp28);
    ReadRotMatrix(&sp30);

    pPos->vx = sp30.t[0];
    pPos->vy = sp30.t[1];
    pPos->vz = sp30.t[2];
    pre.scr_num = 2;

    NewAnime_8005FBC8(NULL, 0, anm);

    if (GV_RandU_80017090(16) >= 5)
    {
        sp28.vx = 0;
        sp28.vy = 0;
        sp28.vz = -800;

        DG_SetPos_8001BC44(pos);
        DG_MovePos_8001BD20(&sp28);
        ReadRotMatrix(&sp30);

        pPos->vx = sp30.t[0];
        pPos->vy = sp30.t[1];
        pPos->vz = sp30.t[2];

        sp28.vx = GV_RandU_80017090(32) - 100;
        sp28.vy = GV_RandU_80017090(32) + 15;
        sp28.vz = GV_RandU_80017090(64) + 100;

        DG_MovePos_8001BD20(&sp28);
        ReadRotMatrix(&sp30);

        pSpeed->vx = pPos->vx - sp30.t[0];
        pSpeed->vy = pPos->vy - sp30.t[1];
        pSpeed->vz = sp30.t[2] - pPos->vz;
        pre.scr_num = 2;
        pre.s_anim = 0;

        anm = &stru_8009F0D4;
        anm->field_14_pre_script = &pre;

        NewAnime_8005FBC8(NULL, 0, anm);
    }

    if (GV_RandU_80017090(16) >= 9)
    {
        sp28.vx = 0;
        sp28.vy = 0;
        sp28.vz = -500;

        DG_SetPos_8001BC44(pos);
        DG_MovePos_8001BD20(&sp28);
        ReadRotMatrix(&sp30);

        pPos->vx = sp30.t[0];
        pPos->vy = sp30.t[1];
        pPos->vz = sp30.t[2];

        sp28.vx = 0;
        sp28.vy = 0;
        sp28.vz = -GV_RandU_80017090(32);

        DG_MovePos_8001BD20(&sp28);
        ReadRotMatrix(&sp30);

        pSpeed->vx = pPos->vx - sp30.t[0];
        pSpeed->vy = pPos->vy - sp30.t[1];
        pSpeed->vz = pPos->vz - sp30.t[2];
        pre.s_anim = 0;
        pre.scr_num = 3;

        anm = &stru_8009F0F0;
        anm->field_14_pre_script = &pre;

        NewAnime_8005FBC8(NULL, 0, anm);
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

    DG_SetPos2_8001BC8C(pos, rot);
    DG_PutVector_8001BE48(sp28, sp28, 4);

    sp48[0].vx = -100 - GV_RandU_80017090(32);
    sp48[0].vy = GV_RandU_80017090(32) + 15;
    sp48[0].vz = GV_RandS_800170BC(4);

    sp48[1].vx = 0;
    sp48[1].vy = 0;
    sp48[1].vz = -GV_RandU_80017090(32);

    DG_SetPos2_8001BC8C(&DG_ZeroVector_800AB39C, rot);
    DG_PutVector_8001BE48(sp48, sp48, 2);

    pre.speed = DG_ZeroVector_800AB39C;

    rnd = GV_RandU_80017090(16);
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
    anm->field_14_pre_script = &pre;

    *pPos = *pos;
    pre.scr_num = 0;

    NewAnime_8005FBC8(NULL, 0, anm);

    *pPos = sp28[1];
    pre.scr_num = 2;

    NewAnime_8005FBC8(NULL, 0, anm);

    if (GV_RandU_80017090(16) >= 5)
    {
        *pPos = sp28[2];
        *pSpeed = sp48[0];
        pre.scr_num = 2;
        pre.s_anim = 0;

        anm = &stru_8009F0D4;
        anm->field_14_pre_script = &pre;

        NewAnime_8005FBC8(NULL, 0, anm);
    }

    if (GV_RandU_80017090(16) >= 9)
    {
        *pPos = sp28[3];
        *pSpeed = sp48[1];
        pre.s_anim = 0;
        pre.scr_num = 3;

        anm = &stru_8009F0F0;
        anm->field_14_pre_script = &pre;

        NewAnime_8005FBC8(NULL, 0, anm);
    }
}

void AN_Unknown_800D6EB0(SVECTOR *pos)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.scr_num = 0;
    pre.s_anim = GV_RandU_80017090(1024) % 30;

    anm = &anm_800C3B94;
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8(NULL, 0, anm);
}

void AN_Unknown_800D6F6C(SVECTOR *pos)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.scr_num = 0;
    pre.s_anim = GV_RandU_80017090(1024) % 30;

    anm = &anm_800C3BB0;
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8(NULL, 0, anm);
}

void AN_Unknown_800D7028(SVECTOR *pos, int num)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.scr_num = num;
    pre.s_anim = GV_RandU_80017090(1024) % 30;

    anm = &anm_800C3BE8;
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8(NULL, 0, anm);
}

void AN_Unknown_800D70E4(SVECTOR *pos, char r, char g, char b)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.scr_num = 0;
    pre.s_anim = GV_RandU_80017090(1024) % 30;

    anm = &anm_800C3BCC;
    anm->field_14_pre_script = &pre;

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

    NewAnime_8005FBC8(NULL, 0, anm);
}
