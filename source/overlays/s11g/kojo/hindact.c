#include "common.h"
#include "linkvar.h"
#include "game/game.h"
#include "kojo/demo.h"
#include "hind.h"
#include "libgcl/libgcl.h"

extern DG_CHANL         DG_Chanls[3];
extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;
extern GM_CAMERA        GM_Camera;
extern int              MENU_RadarScale;
extern int              amissile_alive_8009F490;

TILE SECTION(".bss") s11g_dword_800DD34C[2];
char SECTION(".bss") hind_lifebar_name[8];
int SECTION(".bss")  s11g_dword_800DD374;
int SECTION(".bss")  s11g_dword_800DD378;

void AN_Smoke_800CE240(SVECTOR *pos);

void s11g_hind_800D5820(HindWork *work);
void s11g_hind_800DAAC8(HindWork *work);

void s11g_blastoff_800DBF88(HindWork *work);

void Hind_LookAt_800D2C1C(SVECTOR *eye, SVECTOR *center)
{
    DG_LookAt(&DG_Chanls[1], eye, center, 320);
    GM_Camera.field_2A = 0;
    gUnkCameraStruct2_800B7868.eye = *eye;
    gUnkCameraStruct2_800B7868.center = *center;
}

void s11g_hind_800D2CB4(HindWork *work)
{
    u_long *ot;
    TILE   *tile;
    int     scale;
    int     px, pz;
    int     x, z;
    int     clip;

    if (GM_GameStatus & (STATE_RADAR_OFF | STATE_CHAFF))
    {
        return;
    }

    if (GM_OptionFlag & OPTION_RADAR_OFF)
    {
        return;
    }

    if (GM_CurrentItemId == IT_Camera)
    {
        return;
    }

    ot = DG_Chanl(1)->ot[GV_Clock];
    tile = &s11g_dword_800DD34C[GV_Clock];

    SetTile(tile);

    scale = MENU_RadarScale;
    px = GM_PlayerPosition.vx;
    pz = GM_PlayerPosition.vz;
    x = ((work->field_4BC.vx - px) * scale) / 4096;
    z = ((work->field_4BC.vz - pz) * scale) / 4096;

    clip = 0;

    if (x < -34)
    {
        z = -(z * 34) / x;
        x = -34;
        clip = 1;
    }

    if (x > 32)
    {
        z = (z * 32) / x;
        x = 32;
        clip = 1;
    }

    if (z < -26)
    {
        x = -(x * 26) / z;
        z = -26;
        clip = 1;
    }

    if (z > 24)
    {
        x = (x * 24) / z;
        z = 24;
        clip = 1;
    }

    setXY0(tile, x + 270, z + 42);
    setWH(tile, 2, 2);

    if (clip == 0)
    {
        setRGB0(tile, 255, 0, 0);
    }
    else
    {
        setRGB0(tile, 255, 0, 255);
    }

    addPrim(ot, tile);
}

void s11g_hind_800D2F60(HindWork *work)
{
    DG_VECTOR sp10[2];
    VECTOR    sp30;
    VECTOR    sp38;
    VECTOR   *vec;
    int       len;
    int       len2;

    sp30.vx = GM_PlayerPosition.vx;
    sp30.vy = GM_PlayerPosition.vy;
    sp30.vz = GM_PlayerPosition.vz;
    sp38 = work->field_760;
    sub_8007F06C(sp10, &sp30, &sp38);

    vec = NULL;

    if (sp38.vx < -work->field_514)
    {
        vec = &work->field_518;
        sub_8007F1DC(&sp38, sp10, vec);
    }
    else if (sp38.vx > work->field_514)
    {
        vec = &work->field_528;
        sub_8007F1DC(&sp38, sp10, vec);
    }

    if (sp38.vz < -work->field_514)
    {
        vec = &work->field_538;
        sub_8007F1DC(&sp38, sp10, vec);
    }
    else if (sp38.vz > work->field_514)
    {
        vec = &work->field_548;
        sub_8007F1DC(&sp38, sp10, vec);
    }

    if (vec == NULL)
    {
        sp30.vx = 4096;
        sp30.vy = 4096;
        sp30.vz = 4096;
        ScaleMatrix(&work->missile3.objs->world, &sp30);
        work->field_670 = 4096;
        work->field_7D8.vx = work->field_760.vx;
        work->field_7D8.vy = work->field_760.vy;
        work->field_7D8.vz = work->field_760.vz;
        return;
    }

    sp30.vx = (work->field_760.vx - gUnkCameraStruct2_800B7868.eye.vx) >> 2;
    sp30.vy = (work->field_760.vy - gUnkCameraStruct2_800B7868.eye.vy) >> 2;
    sp30.vz = (work->field_760.vz - gUnkCameraStruct2_800B7868.eye.vz) >> 2;

    len = SquareRoot0(sp30.vx * sp30.vx + sp30.vy * sp30.vy + sp30.vz * sp30.vz) * 4;

    sub_8007F1DC(&sp38, sp10, vec);

    work->field_7D8.vx = sp38.vx;
    work->field_7D8.vy = sp38.vy;
    work->field_7D8.vz = sp38.vz;

    sp30.vx = sp38.vx - gUnkCameraStruct2_800B7868.eye.vx;
    sp30.vy = sp38.vy - gUnkCameraStruct2_800B7868.eye.vy;
    sp30.vz = sp38.vz - gUnkCameraStruct2_800B7868.eye.vz;

    len2 = SquareRoot0(sp30.vx * sp30.vx + sp30.vy * sp30.vy + sp30.vz * sp30.vz);
    if (len == 0)
    {
        len = len2 * 4096;
    }
    else
    {
        len = (len2 * 4096) / len;
    }

    sp30.vx = len;
    sp30.vy = len;
    sp30.vz = len;
    ScaleMatrix(&work->missile3.objs->world, &sp30);
    work->field_670 = len;
}

void s11g_hind_800D3214(HindWork *work)
{
    int field_654;
    int var_a2;
    int var_s1;

    if (GM_GameStatus & STATE_LIFEBAR_OFF)
    {
        return;
    }

    field_654 = work->field_654;
    if (field_654 < 0)
    {
        field_654 = 0;
    }

    var_s1 = work->field_7F4;
    var_a2 = var_s1;
    if (var_s1 < field_654)
    {
        var_a2 = field_654;
        var_s1 = field_654;
    }
    MENU_DrawBar(16, 28, var_a2, field_654, &work->lifebar);
    if (field_654 < var_s1)
    {
        work->field_7F4 -= 8;
        if (work->field_7F4 < field_654)
        {
            work->field_7F4 = field_654;
        }
    }
}

void s11g_hind_800D32CC(HindWork *work)
{
    MENU_BAR_CONF *conf;

    strcpy(hind_lifebar_name, "HIND");

    conf = &work->lifebar;
    conf->name = hind_lifebar_name;
    conf->left[0] = 16;
    conf->left[1] = 111;
    conf->left[2] = 159;
    conf->right[0] = 31;
    conf->right[1] = 223;
    conf->right[2] = 127;
}

// Identical to d03a_red_alrt_800C437C
int HindReceiveMessage_800D3334(unsigned short name, int nhashes, unsigned short *hashes)
{
    GV_MSG *msg;
    int     nmsgs;
    int     found;
    int     hash;
    int     i;

    nmsgs = GV_ReceiveMessage(name, &msg);
    found = -1;

    for (; nmsgs > 0; nmsgs--, msg++)
    {
        hash = msg->message[0];

        for (i = 0; i < nhashes; i++)
        {
            if (hash == hashes[i])
            {
                found = i;
            }
        }
    }

    return found;
}

void Hind_800D33CC(HindWork *work, int arg)
{
    GCL_ARGS args;
    long     argv[1];

    args.argc = 1;
    argv[0] = arg;
    args.argv = argv;

    GCL_ExecProc(work->field_8F0, &args);
}

void HindAct(HindWork *work)
{
    DG_VECTOR auStack_78[2];
    VECTOR    scale;
    VECTOR    local_50;
    SVECTOR   eye;
    SVECTOR   center;
    SVECTOR   local_30[2];
    u_short   hashes[3];
    VECTOR   *vec;
    int       len1;
    int       len2;
    int       iVar6;
    int       iVar7;

    if (work->field_950 < 4)
    {
        work->field_950++;
    }
    else if ((GM_GameOverTimer != 0) && (work->field_94C == 0))
    {
        work->field_94C = 1;
        GM_GameStatus &= ~STATE_PADDEMO;
        GM_StreamPlayStop();
    }

    if ((work->field_94C == 1) && work->field_8E4)
    {
        GV_DestroyOtherActor(work->field_8E4);
        work->field_8E4 = NULL;
    }

    if ((work->field_94C == 0) && (GM_StreamStatus() == 1))
    {
        GM_StreamPlayStop();
    }

    hashes[0] = GV_StrCode("bullet_off");
    hashes[1] = GV_StrCode("bullet_on");
    hashes[2] = GV_StrCode("destroy");

    switch (HindReceiveMessage_800D3334(work->name, 3, hashes))
    {
    case 0:
        work->field_930 = 1;
        break;
    case 1:
        work->field_930 = 0;
        break;
    case 2:
        work->field_938 = 1;
        return;
    }

    GM_ActMotion(&work->body);
    GM_ActControl(&work->control);
    GM_ActObject(&work->body);

    DG_GetLightMatrix2(&work->control.mov, work->body_light);

    work->missile1.objs->root = &work->body.objs->objs[7].world;
    GM_ActObject2(&work->missile1);
    work->missile1_light[0] = work->body_light[0];
    work->missile1_light[1] = work->body_light[1];

    work->missile2.objs->root = &work->body.objs->objs[8].world;
    GM_ActObject2(&work->missile2);
    work->missile2_light[0] = work->body_light[0];
    work->missile2_light[1] = work->body_light[1];

    switch (work->field_674)
    {
    case 0:
        DG_InvisibleObjs(work->missile3.objs);
        break;
    case 1:
        DG_InvisibleObjs(work->missile1.objs);
        DG_VisibleObjs(work->missile3.objs);

        DG_SetPos2(&work->field_7D8,&work->field_788);
        GM_ActObject2(&work->missile3);

        work->missile3.objs->light->t[0] = 128;
        work->missile3.objs->light->t[1] = 128;
        work->missile3.objs->light->t[2] = 128;

        DG_AmbientObjs(work->missile3.objs);
        s11g_hind_800D2F60(work);
        break;
    case 2:
        DG_InvisibleObjs(work->missile1.objs);
        DG_InvisibleObjs(work->missile3.objs);
        s11g_hind_800D2F60(work);
        break;
    case 3:
        DG_InvisibleObjs(work->missile1.objs);
        DG_InvisibleObjs(work->missile2.objs);
        DG_VisibleObjs(work->missile3.objs);

        DG_SetPos2(&work->field_7D8,&work->field_788);
        GM_ActObject2(&work->missile3);

        work->missile3.objs->light->t[0] = 128;
        work->missile3.objs->light->t[1] = 128;
        work->missile3.objs->light->t[2] = 128;

        DG_AmbientObjs(work->missile3.objs);
        s11g_hind_800D2F60(work);
        break;
    case 4:
        DG_InvisibleObjs(work->missile1.objs);
        DG_InvisibleObjs(work->missile2.objs);
        DG_InvisibleObjs(work->missile3.objs);
        break;
    }

    switch (work->field_678)
    {
    case 0:
        GM_GameStatus &= ~STATE_PADDEMO;
        break;
    case 11:
        GM_GameStatus |= STATE_PADDEMO;

        s11g_hind_800D2F60(work);
        DG_InvisibleObjs(work->missile1.objs);
        DG_VisibleObjs(work->missile3.objs);
        DG_SetPos2(&work->field_7D8, &work->field_788);
        GM_ActObject2(&work->missile3);
        DG_GetLightMatrix2(&work->field_7D8, work->missile3_light);

        eye.vx = -14598;
        eye.vy = 17975;
        eye.vz = 300;

        center.vx = -6935;
        center.vy = 19318;
        center.vz = -1365;

        Hind_LookAt_800D2C1C(&eye, &center);
        break;
    case 12:
        GM_GameStatus |= STATE_PADDEMO;
        s11g_hind_800D2F60(work);

        DG_InvisibleObjs(work->missile1.objs);
        DG_InvisibleObjs(work->missile2.objs);
        DG_VisibleObjs(work->missile3.objs);

        DG_SetPos2(&work->field_7D8, &work->field_788);
        GM_ActObject2(&work->missile3);
        DG_GetLightMatrix2(&work->field_7D8, work->missile3_light);

        eye.vx = -14598;
        eye.vy = 17975;
        eye.vz = 2311;

        center.vx = -6935;
        center.vy = 19318;
        center.vz = -1365;

        Hind_LookAt_800D2C1C(&eye, &center);
        break;
    case 13:
        break;
    }

    if (--work->field_504 < 0)
    {
        work->field_504 = 0;
    }

    if (--work->field_508 < 0)
    {
        work->field_508 = 0;
    }

    if ((work->field_50C > 0) && (--work->field_50C == 0))
    {
        work->target1->damaged &= ~TARGET_POWER;
        work->target2->damaged &= ~TARGET_POWER;
        work->target3->damaged &= ~TARGET_POWER;

        if (work->field_434 <= 0)
        {
            if (work->field_658 == 0)
            {
                work->field_658 = 1;
            }

            if (work->field_658 == 1)
            {
                work->field_658 = 2;
            }

            work->field_5C4 = 0;
            work->field_5C8 = 0;
        }
    }

    switch (work->field_4AC)
    {
    case 2:
        s11g_hind_800D5820(work);
        break;
    case 3:
        s11g_hind_800DAAC8(work);
        break;
    }

    if (amissile_alive_8009F490 != 1)
    {
        work->field_A78 = gUnkCameraStruct2_800B7868.eye;
    }

    scale.vx = work->field_A78.vx;
    scale.vy = work->field_A78.vy;
    scale.vz = work->field_A78.vz;

    local_50 = work->field_4BC;

    sub_8007F06C(auStack_78, &scale, &local_50);

    vec = NULL;
    if (local_50.vx < -work->field_514)
    {
        vec = &work->field_518;
        sub_8007F1DC(&local_50, auStack_78, vec);
    }
    else if (local_50.vx > work->field_514)
    {
        vec = &work->field_528;
        sub_8007F1DC(&local_50, auStack_78, vec);
    }

    if (local_50.vz < -work->field_514)
    {
        vec = &work->field_538;
        sub_8007F1DC(&local_50, auStack_78, vec);
    }
    else if (local_50.vz > work->field_514)
    {
        vec = &work->field_548;
        sub_8007F1DC(&local_50, auStack_78, vec);
    }

    scale.vx = (work->field_4BC.vx - work->field_A78.vx) / 8;
    scale.vy = (work->field_4BC.vy - work->field_A78.vy) / 8;
    scale.vz = (work->field_4BC.vz - work->field_A78.vz) / 8;

    len1 = SquareRoot0(scale.vx * scale.vx + scale.vy * scale.vy + scale.vz * scale.vz) << 3;

    if (vec == NULL)
    {
        work->field_5DC = 0;

        scale.vx = 4096;
        scale.vy = 4096;
        scale.vz = 4096;

        ScaleMatrix(&work->body.objs->world, &scale);

        work->field_66C = 4096;
        work->field_63C.vx = work->field_4BC.vx;
        work->field_63C.vy = work->field_4BC.vy;
        work->field_63C.vz = work->field_4BC.vz;
    }
    else
    {
        work->field_5DC = 1;
        sub_8007F1DC(&local_50, auStack_78, vec);

        work->field_63C.vx = local_50.vx;
        work->field_63C.vy = local_50.vy;
        work->field_63C.vz = local_50.vz;

        scale.vx = local_50.vx - work->field_A78.vx;
        scale.vy = local_50.vy - work->field_A78.vy;
        scale.vz = local_50.vz - work->field_A78.vz;

        len2 = SquareRoot0(scale.vx * scale.vx + scale.vy * scale.vy + scale.vz * scale.vz);
        if (len1 == 0)
        {
            len1 = len2 * 4096;
        }
        else
        {
            len1 = (len2 * 4096) / len1;
        }

        scale.vx = len1;
        scale.vy = len1;
        scale.vz = len1;

        ScaleMatrix(&work->body.objs->world, &scale);
        work->field_66C = len1;
    }

    work->control.mov.vx = local_50.vx;
    work->control.mov.vy = local_50.vy;
    work->control.mov.vz = local_50.vz;

    eye = work->control.mov;
    eye.vy -= -work->body.objs->objs[0].model->min.vy / 12;

    local_30[0] = DG_ZeroVector;
    local_30[0].vy = (work->field_66C * -2000) / 4096;
    local_30[0].vz = (work->field_66C * 4000) / 4096;

    local_30[1] = DG_ZeroVector;
    local_30[1].vz = (work->field_66C * -8000) / 4096;

    DG_SetPos2(&eye, &work->control.rot);
    DG_PutVector(local_30, local_30, 2);

    center.vx = center.vy = center.vz = (work->field_66C * 5000) / 4096;

    work->target1->size = center;
    work->target2->size = center;
    work->target3->size = center;

    GM_MoveTarget(work->target1, &eye);
    GM_MoveTarget(work->target2, &local_30[0]);
    GM_MoveTarget(work->target3, &local_30[1]);

    if (work->field_500 == 0)
    {
        s11g_blastoff_800DBF88(work);
    }

    iVar7 = len1;
    if (iVar7 > 60000)
    {
        iVar7 = 60000;
    }

    iVar6 = 0;
    if (work->control.mov.vy < 0)
    {
        iVar6 = abs(work->control.mov.vy / 128);
    }

    iVar7 = (128 - (iVar7 * 128) / 180000 - iVar6) / 2;
    if (iVar7 < 0)
    {
        iVar7 = 0;
    }

    work->body.objs->light->t[0] = iVar7;
    work->body.objs->light->t[1] = iVar7;
    work->body.objs->light->t[2] = iVar7 * 2;

    DG_AmbientObjs(work->body.objs);

    work->field_64C = 0;

    if ((work->field_658 == 0) && (work->field_50C == 0))
    {
        if ((work->target1->damaged != TARGET_STALE) ||
            (work->target2->damaged != TARGET_STALE) ||
            (work->target3->damaged != TARGET_STALE))
        {
            if ((work->target1->weapon == WP_Stinger) ||
                (work->target2->weapon == WP_Stinger) ||
                (work->target3->weapon == WP_Stinger))
            {
                if (work->control.mov.vy > 0)
                {
                    work->target1->damaged |= TARGET_POWER;
                    work->target2->damaged |= TARGET_POWER;
                    work->target3->damaged |= TARGET_POWER;

                    work->target1->weapon = WP_Socom;
                    work->target2->weapon = WP_Socom;
                    work->target3->weapon = WP_Socom;

                    work->field_64C = 1;
                    if (len1 < 10000)
                    {
                        work->field_64C = 2;
                    }

                    work->field_434--;
                    work->field_654 -= work->field_650;
                    work->field_50C = work->field_438;
                }
                else
                {
                    work->target1->damaged &= ~TARGET_POWER;
                    work->target2->damaged &= ~TARGET_POWER;
                    work->target3->damaged &= ~TARGET_POWER;
                }
            }
            else
            {
                work->target1->damaged &= ~TARGET_POWER;
                work->target2->damaged &= ~TARGET_POWER;
                work->target3->damaged &= ~TARGET_POWER;
            }
        }
    }

    if (work->field_50C > 0)
    {
        if ((GV_Time % 4) == 0)
        {
            AN_Smoke_800CE240(&work->control.mov);
        }

        if ((work->field_50C % 2) == 0)
        {
            work->body.objs->light->t[0] = 190;
            work->body.objs->light->t[1] = 190;
            work->body.objs->light->t[2] = 190;

            DG_AmbientObjs(work->body.objs);
        }
    }

    work->field_414 = 0;

    if ((work->field_4AC == 2) && (work->field_5F0 > 0) && (work->field_94C != 1))
    {
        if (work->field_8F0 != -1)
        {
            if (work->field_5F0 == 90)
            {
                Hind_800D33CC(work, 1);
            }
            else if (work->field_5F0 == 1)
            {
                Hind_800D33CC(work, 0);
            }
        }

        GV_DemoPadStatus[0] = 0;
        GV_DemoPadStatus[1] = 0;

        GM_GameStatus |= 0x4A0040;
        GM_GameStatus |= 0x40000000;

        if (--work->field_5F0 == 0)
        {
            GM_GameStatus &= ~0x004A0040;
            GM_GameStatus &= ~0x40000000;

            work->body.objs->def->model[2].vertices = work->field_A70;

            if ((work->last_weapon == WP_Rifle) || (work->last_weapon == WP_Stinger))
            {
                GM_CurrentWeaponId = work->last_weapon;
            }

            if ((work->last_item == IT_Scope) || (work->last_item == IT_Camera) || (work->last_item == IT_NVG) || (work->last_item == IT_ThermG))
            {
                GM_CurrentItemId = work->last_item;
            }

            work->last_weapon = WP_None;
            work->last_item = IT_None;
        }

        memset(&eye, 0, sizeof(eye));
        memset(&center, 0, sizeof(center));

        eye.vx = work->field_5D8 * 4000;
        eye.vy = -1000;
        eye.vz = -1500;

        DG_SetPos2(&work->control.mov, &work->control.rot);
        DG_PutVector(&eye, &eye, 1);

        center.vx = (GM_PlayerPosition.vx + work->control.mov.vx) / 2;
        center.vy = (GM_PlayerPosition.vy + work->control.mov.vy) / 2 + 1000;
        center.vz = (GM_PlayerPosition.vz + work->control.mov.vz) / 2;

        Hind_LookAt_800D2C1C(&eye, &center);
    }

    s11g_hind_800D2CB4(work);

    if (work->field_4AC != 2)
    {
        if (work->field_7F8 == 0)
        {
            work->field_7F8 = 1;
        }

        if (work->field_7F8 == 2)
        {
            s11g_hind_800D3214(work);
        }

        if (work->field_7F8 == 1)
        {
            work->field_7F8 = 2;
            s11g_hind_800D32CC(work);
            s11g_hind_800D3214(work);
        }
    }
}

void HindDie(HindWork *work)
{
    GM_GameStatus &= ~STATE_PADDEMO;
    GM_GameStatus &= ~(STATE_RADAR_OFF | STATE_MENU_OFF | STATE_LIFEBAR_OFF);

    if (work->end_proc >= 0 && work->field_94C != 1 && work->field_A74 == 1)
    {
        GCL_ForceExecProc(work->end_proc, NULL);
    }

    if (work->field_8E8)
    {
        GV_DestroyOtherActor(work->field_8E8);
        work->field_8E8 = NULL;
    }

    if (work->field_8E4)
    {
        GV_DestroyOtherActor(work->field_8E4);
        work->field_8E4 = NULL;
    }

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeObject(&work->missile1);
    GM_FreeObject(&work->missile2);
    GM_FreeObject(&work->missile3);
    GM_FreeTarget(work->target1);
    GM_FreeTarget(work->target2);
    GM_FreeTarget(work->target3);
}
