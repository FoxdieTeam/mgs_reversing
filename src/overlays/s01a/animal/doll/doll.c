#include "doll.h"
#include "libgcl/hash.h"

extern int GM_CurrentMap_800AB9B0;

short s01a_word_800C3CD4[8] = {31000, 15, 30, 60, 90, 32000, 32001, 30000};

GV_ACT * NewGunLight_800D3AD4(MATRIX *world, int **enable);
GV_ACT * s01a_blink_tx_800DD60C(CONTROL *, OBJECT *, int, int *);

void Demodoll_800DDEAC(DollWork *);
void Demodoll_800DDF18(DollWork *);

#define EXEC_LEVEL 4

void s01a_doll_800DBE0C(DollWork *work)
{
    CONTROL *control;
    GV_MSG  *msg;
    int      n_msgs;

    control = &work->control;
    control->field_56 = GV_ReceiveMessage_80016620(control->field_30_scriptData, &control->field_5C_mesg);

    msg = control->field_5C_mesg;
    n_msgs = control->field_56;

    while (n_msgs > 0)
    {
        switch (msg->message[0])
        {
        case HASH_SOUND_ON:
            work->fE00[1] = 1;
            break;

        case HASH_SOUND_OFF:
            work->fE00[1] = 0;
            break;
        }

        n_msgs--;
        msg++;
    }
}

void DollAct_800DBE9C(DollWork *work)
{
    CONTROL *control;

    control = &work->control;

    if (GM_CheckMessage_8002631C(&work->actor, control->field_30_scriptData, HASH_KILL))
    {
        GV_DestroyActor_800151C8(&work->actor);
        return;
    }

    s01a_doll_800DBE0C(work);

    GM_ActControl_80025A7C(control);
    GM_ActObject2_80034B88(&work->body);

    Demodoll_800DDF18(work);

    DG_GetLightMatrix2_8001A5D8(&control->field_0_mov, work->light);

    if (GM_CheckMessage_8002631C(&work->actor, control->field_30_scriptData, HASH_KILL))
    {
        GV_DestroyActor_800151C8(&work->actor);
    }
}

int s01a_doll_800DBF28(DollWork *work)
{
    HZD_HDL *hzd;
    HZD_PAT *route;
    HZD_PTP *point;
    int      i;

    hzd = work->control.field_2C_map->field_8_hzd;
    route = hzd->f00_header->routes;
    route += work->fA8C[work->fA86];

    work->fA90 = route->n_points;
    if (work->fA90 <= 0)
    {
        return -1;
    }

    point = route->points;
    for (i = 0; i < work->fA90; i++)
    {
        work->fA94[i].vx = point->x;
        work->fA94[i].vy = point->y;
        work->fA94[i].vz = point->z;
        work->fA94[i].pad = point->command;
        point++;
    }

    return 0;
}

int s01a_doll_800DBFC4(int opt, char *out)
{
    int   count;
    char *str;

    count = 0;

    while ((str = GCL_Get_Param_Result_80020AA4()) != NULL)
    {
        *out++ = GCL_StrToInt_800209E8(str);
        count++;
    }

    return count;
}

int s01a_doll_800DC01C(int opt, short *out)
{
    int   count;
    char *str;

    count = 0;

    while ((str = GCL_Get_Param_Result_80020AA4()) != NULL)
    {
        *out++ = GCL_StrToInt_800209E8(str);
        count++;
    }

    return count;
}

int s01a_doll_800DC074(int opt, int *out)
{
    int   count;
    char *str;

    count = 0;

    while ((str = GCL_Get_Param_Result_80020AA4()) != NULL)
    {
        *out++ = GCL_StrToInt_800209E8(str);
        count++;
    }

    return count;
}

int s01a_doll_800DC0CC(DollWork *work)
{
    int opt;

    work->fA8C[0] = 0;
    work->fA86 = 0;

    opt = GCL_GetOption_80020968('r');
    if (opt != NULL && s01a_doll_800DBFC4(opt, work->fA8C) > 3)
    {
        fprintf(0, "Err Err Err Change Root Num Over !!\n");
        return -1;
    }

    return 0;
}

int s01a_doll_800DC134(DollWork *work)
{
    int i;
    int opt;

    for (i = 0; i < 5; i++)
    {
        work->fBE8[i] = 0;
    }

    opt = GCL_GetOption_80020968('s');
    if (opt != NULL && s01a_doll_800DC074(opt, work->fBE8) > 4)
    {
        fprintf(0, "Err Err Err Sound Buff Over !!\n");
        return -1;
    }

    return 0;
}

int s01a_doll_800DC1AC(DollWork *work, int name, int map)
{
    int      opt;
    int      model;
    int      motion;
    int      config;
    int      radar_atr;
    CONTROL *control;
    int      pos;
    int      dir;
    OBJECT  *body;
    int      flag;
    int      i;
    SVECTOR  indices;
    int      weapon;

    work->fE58 = 0;

    opt = GCL_GetOption_80020968('m');
    if (opt == NULL)
    {
        return -1;
    }

    model = GCL_StrToInt_800209E8((char *)opt);

    opt = GCL_GetOption_80020968('o');
    if (opt == NULL)
    {
        return -1;
    }

    motion = GCL_StrToInt_800209E8((char *)opt);

    opt = GCL_GetOption_80020968('c');
    if (opt != NULL)
    {
        config = GCL_StrToInt_800209E8((char *)opt);
    }
    else
    {
        config = 0;
    }

    switch (config)
    {
    case 0:
        radar_atr = RADAR_OFF;
        break;

    case 1:
        radar_atr = 0x1000;
        break;

    case 2:
        radar_atr = RADAR_NOISE;
        break;

    default:
        radar_atr = -1;
        break;
    }

    control = &work->control;

    if (GM_InitLoader_8002599C(control, name, map) < 0)
    {
        return -1;
    }

    pos = GCL_GetOption_80020968('p');
    dir = GCL_GetOption_80020968('d');
    GM_ConfigControlString_800261C0(control, (char *)pos, (char *)dir);

    if (radar_atr >= 0)
    {
        GM_ConfigControlAttribute_8002623C(control, radar_atr | RADAR_SIGHT | RADAR_VISIBLE);
    }

    control->field_36 = -1;
    GM_ConfigControlInterp_80026244(control, 4);
    GM_ConfigControlTrapCheck_80026308(control);
    control->field_59 = 1;

    work->fE58 |= 0x1;

    body = &work->body;

    opt = GCL_GetOption_80020968('g');
    if (opt != NULL)
    {
        flag = GCL_StrToInt_800209E8((char *)opt);
    }
    else
    {
        flag = 1;
    }

    if (flag != 0)
    {
        GM_InitObject_80034A18(body, model, BODY_FLAG, motion);
    }
    else
    {
        GM_InitObject_80034A18(body, model, BODY_FLAG2, motion);
    }

    GM_ConfigObjectJoint_80034CB4(body);
    GM_ConfigMotionControl_80034F08(body, &work->m_ctrl, motion, &work->oars[0], &work->oars[21], control, work->rots);
    body->objs->waist_rot = NULL;
    GM_ConfigObjectLight_80034C44(body, work->light);

    work->fE58 |= 0x2;

    GM_ConfigMotionAdjust_80035008(&work->body, work->adjust);

    work->fE38 = -1;

    opt = GCL_GetOption_80020968('s');
    if (opt != NULL)
    {
        work->fE18[0] = GCL_StrToInt_800209E8((char *)opt);

        i = 1;
        while ((opt = (int)GCL_Get_Param_Result_80020AA4()) != NULL)
        {
            if (i >= 8)
            {
                printf("Max Voice Over!! \n");
                return -1;
            }

            work->fE18[i] = GCL_StrToInt_800209E8((char *)opt);
            i++;
        }
    }
    else
    {
        for (i = 0; i < 8; i++)
        {
            work->fE18[i] = 0;
        }
    }

    work->fDF8 = 1;

    opt = GCL_GetOption_80020968('b');
    if (opt != NULL)
    {
        work->fDF8 = GCL_StrToInt_800209E8((char *)opt);
    }

    indices.vx  = 0;
    indices.vy  = 6;
    indices.vz  = 12;
    indices.pad = 15;

    work->shadow = shadow_init_800602CC(control, body, indices);
    if (work->shadow == NULL)
    {
        return -1;
    }

    work->fE58 |= 0x4;

    opt = GCL_GetOption_80020968('w');
    if (opt == NULL)
    {
        return 0;
    }

    weapon = GCL_StrToInt_800209E8((char *)opt);

    GM_InitObject_80034A18(&work->weapon, weapon, WEAPON_FLAG, 0);
    GM_ConfigObjectLight_80034C44(&work->weapon, work->light);
    GM_ConfigObjectRoot_80034C5C(&work->weapon, body, 4);

    work->fE58 |= 0x8;

    if (weapon == KMD_FAMAS)
    {
        work->glight = NewGunLight_800D3AD4(&body->objs->objs[4].world, NULL);
        if (work->glight == NULL)
        {
            return -1;
        }

        work->fE58 |= 0x10;
    }

    return 0;
}

int s01a_doll_800DC570(DollWork *work)
{
    int i;
    int opt;

    for (i = 0; i < 8; i++)
    {
        work->fC30[i] = s01a_word_800C3CD4[i];
    }

    opt = GCL_GetOption_80020968('f');
    if (opt != NULL && s01a_doll_800DC01C(opt, &work->fC30[1]) > 4)
    {
        printf("Err Err Err  Set time Over\n");
        return -1;
    }

    for (i = 0; i < 4; i++)
    {
        work->fC40[i] = i * 1024;
    }

    opt = GCL_GetOption_80020968('v');
    if (opt != NULL && s01a_doll_800DC01C(opt, work->fC40) > 4)
    {
        printf("Err Err Err  Set Dir Over\n");
        return -1;
    }

    return 0;
}

int s01a_doll_800DC648(char *opt, DollWork *work)
{
    SVECTOR     entry;
    DollMotion *motion;

    while ((opt = GCL_Get_Param_Result_80020AA4()) != NULL)
    {
        GCL_StrToSV_80020A14(opt, &entry);

        motion = &work->fC48[entry.vx];

        if (motion->index >= 4)
        {
            return -1;
        }

        motion->entries[motion->index].vx  = entry.vy;
        motion->entries[motion->index].vy  = entry.vz & 0xFF;
        motion->entries[motion->index].vz  = (entry.vz >> 8) & 0x3;
        motion->entries[motion->index].pad = (entry.vz >> 10) & 0x3;

        printf(" motion[%d] flam[%d] se[%d] ", entry.vx, entry.vy, motion->entries[motion->index].vy);
        printf(" mode[%d] foot[%d]\n", motion->entries[motion->index].vz, motion->entries[motion->index].pad);

        motion->index++;
    }

    return 0;
}

int s01a_doll_800DC774(DollWork *work)
{
    int i;
    int opt;

    for (i = 0; i < 8; i++)
    {
        work->fE60[i] = -1;
    }

    i = 0;
    opt = GCL_GetOption_80020968('a');

    while (opt != NULL)
    {
        if (i >= 8)
        {
            return -1;
        }

        work->fE60[i] = GCL_StrToInt_800209E8((char *)opt);

        opt = (int)GCL_Get_Param_Result_80020AA4();
        i++;
    }

    return i;
}

int s01a_doll_800DC7FC(DollWork *work)
{
    int i;
    int opt;

    for (i = 0; i < 16; i++)
    {
        work->fE48[i] = 0;
    }

    i = 0;
    opt = GCL_GetOption_80020968('n');

    while (opt != NULL)
    {
        if (i >= 16)
        {
            return -1;
        }

        work->fE48[i] = GCL_StrToInt_800209E8((char *)opt);

        opt = (int)GCL_Get_Param_Result_80020AA4();
        i++;
    }

    return i;
}

int s01a_doll_800DC884(DollWork *work)
{
    int i;
    int opt;
    int ret;

    for (i = 0; i < 12; i++)
    {
        work->fC48[i].index = 0;
    }

    opt = GCL_GetOption_80020968('x');
    if (opt != NULL)
    {
        ret = s01a_doll_800DC648((char *)opt, work);
        if (ret < 0)
        {
            printf("Err Err Err  Set SE Over\n");
            return -1;
        }
    }
    else
    {
        ret = 0;
    }

    return ret;
}

void DollDie_800DC8F0(DollWork *work)
{
    if (work->fE58 & 0x1)
    {
        GM_FreeControl_800260CC(&work->control);
    }

    if (work->fE58 & 0x2)
    {
        GM_FreeObject_80034BF8(&work->body);
    }

    if (work->fE58 & 0x8)
    {
        GM_FreeObject_80034BF8(&work->weapon);
    }

    if (work->fE58 & 0x4)
    {
        GV_DestroyOtherActor_800151D8(&work->shadow->field_0_actor);
    }

    if (work->fE58 & 0x10)
    {
        GV_DestroyOtherActor_800151D8(work->glight);
    }

    if (work->fE58 & 0x20)
    {
        GV_DestroyOtherActor_800151D8(work->fE04);
    }

    if (work->fE5C >= 0)
    {
        if (work->fE80 != 0)
        {
            GCL_ExecProc_8001FF2C(work->fE5C, NULL);
        }
        else
        {
            GCL_ForceExecProc_8001FEFC(work->fE5C, NULL);
        }
    }
}

void s01a_doll_800DC9FC(DollWork *work)
{
    int act;

    act = work->fA94[0].pad & 0x1F;
    printf("doll act=%d \n", act);

    if (act > 0 && act < 16)
    {
        GM_ConfigObjectAction_80034CD4(&work->body, act + 1, 0, 0);

        work->fBE0 = act + 1;
        work->fC04 = act;
        work->fC08 = 1;

        Demodoll_800DDEAC(work);
    }
    else
    {
        GM_ConfigObjectAction_80034CD4(&work->body, 0, 0, 0);
    }

    work->control.field_32_height = work->body.field_18;
}

int DollGetResources_800DCAA4(DollWork *work, int name, int map)
{
    int   opt;
    int   hzd;
    short ry;

    if (s01a_doll_800DC1AC(work, name, map) < 0)
    {
        return -1;
    }

    s01a_doll_800DC134(work);

    if (s01a_doll_800DC0CC(work) < 0)
    {
        return -1;
    }

    if (s01a_doll_800DBF28(work) < 0)
    {
        fprintf(1, "demodoll.c : action point Err\n");
        return -1;
    }

    if (s01a_doll_800DC570(work) < 0)
    {
        return -1;
    }

    if (s01a_doll_800DC884(work) < 0)
    {
        return -1;
    }

    if (s01a_doll_800DC774(work) < 0)
    {
        return -1;
    }

    if (s01a_doll_800DC7FC(work) < 0)
    {
        return -1;
    }

    opt = GCL_GetOption_80020968('e');
    if (opt != NULL)
    {
        work->fE5C = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->fE5C = -1;
    }

    work->fE80 = 0;

    opt = GCL_GetOption_80020968('z');
    if (opt != NULL)
    {
        work->fE80 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    opt = GCL_GetOption_80020968('k');
    if (opt != NULL)
    {
        work->fE3C = GCL_StrToInt_800209E8((char *)opt);
    }
    else
    {
        work->fE3C = 6;
    }

    opt = GCL_GetOption_80020968('h');
    if (opt != NULL)
    {
        work->fE3E = GCL_StrToInt_800209E8((char *)opt);
    }
    else
    {
        work->fE3E = 0;
    }

    opt = GCL_GetOption_80020968('i');
    if (opt != NULL)
    {
        work->fDFE = GCL_StrToInt_800209E8((char *)opt);
    }
    else
    {
        work->fDFE = -1;
    }

    opt = GCL_GetOption_80020968('j');
    if (opt != NULL)
    {
        work->fE58 |= 0x20;
        work->fE04 = s01a_blink_tx_800DD60C(&work->control, &work->body, GCL_StrToInt_800209E8((char *)opt), (int *)work->fE00);
    }

    work->fE00[0] = 0;
    work->fE00[1] = 1;
    work->fE44 = 0;
    work->fE40 = 0;
    work->fDFC = 0;
    work->fC10 = 0;
    work->fC14 = 0;
    work->fC18 = 0;
    work->fB94 = 0;

    work->fBA0 = work->fA94[0];
    hzd = HZD_GetAddress_8005C6C4(work->control.field_2C_map->field_8_hzd, &work->fBA0, -1);
    work->fBB4 = hzd;
    work->fBB8 = GM_CurrentMap_800AB9B0;

    work->control.field_0_mov = work->fA94[0];

    work->fB98 = work->fA94[0];
    work->fBAC = GM_CurrentMap_800AB9B0;
    hzd = HZD_GetAddress_8005C6C4(work->control.field_2C_map->field_8_hzd, &work->control.field_0_mov, -1);
    work->fBA8 = hzd;
    work->fBC4 = hzd;
    work->fBB0 = hzd;
    work->fBC8 = work->fB98;

    ry = work->fC40[(work->fB98.pad & 0x300) >> 8];
    work->control.field_8_rot.vy = ry;
    work->control.field_4C_turn.vy = ry;

    s01a_doll_800DC9FC(work);

    return 0;
}

GV_ACT * NewDoll_800DCD78(int name, int where)
{
    DollWork *work;

    work = (DollWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(DollWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)DollAct_800DBE9C, (TActorFunction)DollDie_800DC8F0, "doll.c");

        if (DollGetResources_800DCAA4(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
