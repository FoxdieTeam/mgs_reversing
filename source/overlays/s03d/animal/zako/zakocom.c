#include "zako.h"

#include <stdio.h>
#include "mgstype.h"
#include "mts/mts.h" // for fprintf
#include "libgcl/libgcl.h" // for GCL_NextStr, GCL_StrToInt
#include "game/game.h"
#include "game/vibrate.h" // for NewPadVibration
#include "game/strctrl.h"
#include "takabe/cineutil.h"
#include "linkvar.h"

typedef struct _ZakoComWork
{
    GV_ACT actor;
    char   pad_20[4];
} ZakoComWork;

SVECTOR s03d_dword_800C3B88 = {30000, 30000, 30000};

SVECTOR s03d_dword_800C3B90 = {8000, 0, 1000, 0};
static u_char VibH[] = { 1, 1, 0, 0 };
static u_char VibL[] = { 255, 1, 0, 0 };
int ZakoChaseDist[8] = {3000, 4000, 7000, 8000, 8000, 8000, 8000, 8000};
static int SoundPlayTime = 0;

extern int s03d_dword_800DC2E0;
extern int s03d_dword_800DC2F0;
extern int s03d_dword_800DC2F4;
void s03d_800D42DC(void);
int s03d_800D46F8(int cmd);
void s03d_800D47BC(COMMANDER *command);
void s03d_800D4B84(COMMANDER *command);

int ZakoCom_800D3FF4(Work *actor)
{
    COMMANDER *mgr = &ZakoCommand;
    int i;

    for (i = 0; i < 8; i++)
    {
        if (mgr->watchers[i].work == 0)
        {
            mgr->watchers[i].work = actor;
            mgr->watchers[i].field_4 = 2;
            return i;
        }
    }
    return -1;
}
int ZakoCom_800D4038(void)
{
    int v = s03d_dword_800DC2E0;

    s03d_dword_800DC2E0 = v + 1;
    return v;
}

void ZakoCom_800D4050(int idx)
{
    COMMANDER *mgr = &ZakoCommand;

    mgr->watchers[idx].work = 0;
    mgr->watchers[idx].field_4 = 1;
}

void ZakoCom_800D4070(int value)
{
    ZakoTopCommand.alert = value;
}

void ZakoCom_800D407C(int value)
{
    ZakoTopCommand.mode = value;
}
void ZakoCom_800D4088(void)
{
    COMMANDER *mgr = &ZakoCommand;

    mgr->target_addr = ZakoPlayerAddress;
    mgr->target_pos = ZakoPlayerPosition;
    mgr->target_map = ZakoPlayerMap;
}
void ZakoCom_800D40D4(void)
{
    int addr = HZD_GetAddress(GM_WhereList[0]->map->hzd, &GM_NoisePosition, -1);
    COMMANDER *mgr = &ZakoCommand;

    mgr->target_addr = addr;
    mgr->target_pos = GM_NoisePosition;
    mgr->target_map = GM_PlayerMap;
}
int s03d_800D414C(int map_id, int val)
{
    int i;
    JDATA *list = &ZakoCommand.jdata;

    if (list->map == map_id)
    {
        for (i = 0; i < list->count; i++)
        {
            if (list->data[i][0] == val)
            {
                return list->data[i][1];
            }
        }
        goto end;
    }
    return 0;
end:
    return -1;
}
void ZakoCom_800D41C0(void)
{
    if (s03d_dword_800DC2F4 > 0)
    {
        NewPadVibration(VibH, 1);
        NewPadVibration(VibL, 2);
        s03d_dword_800DC2F4--;
    }
    else
    {
        s03d_dword_800DC2F4 = 0;
    }
}
int ZakoCom_800D4224(char *opt, JDATA *list)
{
    int count = 0;

    do
    {
        list->data[count][0] = GCL_StrToInt(GCL_NextStr());
        list->data[count][1] = GCL_StrToInt(GCL_NextStr());
        count++;
    } while (GCL_NextStr() != NULL);

    return count;
}
int ZakoCom_800D4284(char *opt, short *out)
{
    short *p = out;
    int count = 0;
    char *str;

    while ((str = GCL_NextStr()) != 0)
    {
        *p = GCL_StrToInt(str);
        p++;
        count++;
    }

    return count;
}
void s03d_800D42DC(void)
{
    int i;
    int dist2;
    int dist1;
    int reset_pos;
    HZD_ZON *zone;
    SVECTOR svec;

    i = dist1 = reset_pos = 0;

    for ( ; i < ZakoCommand.n_zones ; i++ )
    {
        zone = &ZakoCommand.map->hzd->def->zones[ ZakoCommand.zones[ i ] ];
        svec.vx = zone->x;
        svec.vy = GM_PlayerPosition.vy;
        svec.vz = zone->z;
        dist2 = GV_DiffVec3( &svec, &GM_PlayerPosition );
        if ( dist1 < dist2 )
        {
            dist1 = dist2;
            reset_pos = i;
        }
    }

    ZakoCommand.far_zone = reset_pos;
}
int ZakoCom_800D43CC(int arg)
{
    return ZakoCommand.time % arg;
}

void ZakoCom_800D440C(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, "dareda!!\n");
        out[0] = 0x80;
    }
    else if (r == 1)
    {
        fprintf(1, "dareda!!\n");
        out[0] = 0x80;
    }
}
void ZakoCom_800D4460(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, "nanno otoda!!\n");
        out[0] = 0x87;
    }
    else if (r == 1)
    {
        fprintf(1, "nanno otoda!!\n");
        out[0] = 0x87;
    }
}
void ZakoCom_800D44B4(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, "tadano hakoka\n");
        out[0] = 0x8B;
    }
    else if (r == 1)
    {
        fprintf(1, "tadano hakoka\n");
        out[0] = 0x8B;
    }
}
void ZakoCom_800D4508(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, "kono asiatoha??\n");
        out[0] = 0x8A;
    }
    else if (r == 1)
    {
        fprintf(1, "kono asiatoha??\n");
        out[0] = 0x8A;
    }
}
void ZakoCom_800D455C(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, "kinoseika !!\n");
        out[0] = 0x86;
    }
    else if (r == 1)
    {
        fprintf(1, "kinoseika !!\n");
        out[0] = 0x86;
    }
}
void ZakoCom_800D45B0(int *out)
{
    switch (ZakoCom_800D43CC(3))
    {
    case 0:
        fprintf(1, "itazo \n");
        out[0] = 0x82;
        break;
    case 1:
        fprintf(1, "kottida!!\n");
        out[0] = 0x81;
        break;
    case 2:
        fprintf(1, "kottida!!\n");
        out[0] = 0x81;
        break;
    }
}
void ZakoCom_800D4640(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, "haitini modoruzo!!\n");
        out[0] = 0x85;
    }
    else if (r == 1)
    {
        fprintf(1, "haitini modoruzo!!\n");
        out[0] = 0x85;
    }
}
void ZakoCom_800D4694(int *out)
{
    switch (ZakoCom_800D43CC(2))
    {
    case 0:
        fprintf(1, "kottida !!\n");
        out[0] = 0x81;
        break;
    case 1:
        out[0] = 0;
        break;
    }
}
int s03d_800D46F8(int cmd)
{
    switch (cmd - 0xF0)
    {
    case 0:
        ZakoCom_800D440C(&cmd);
        break;
    case 1:
        ZakoCom_800D4460(&cmd);
        break;
    case 2:
        ZakoCom_800D44B4(&cmd);
        break;
    case 3:
        ZakoCom_800D4508(&cmd);
        break;
    case 4:
        ZakoCom_800D455C(&cmd);
        break;
    case 5:
        ZakoCom_800D4640(&cmd);
        break;
    case 6:
        ZakoCom_800D45B0(&cmd);
        break;
    case 7:
        ZakoCom_800D4694(&cmd);
        break;
    }
    return cmd;
}
void s03d_800D47BC(COMMANDER *mgr)
{
    int i;
    int prev;
    int t3;
    int t4;
    int dists[8];
    int cur, min;
    int a, b;
    Work *work;

    for (i = 0; i < mgr->n_watchers; i++)
    {
        work = mgr->watchers[ZakoCommand.order[i]].work;
        dists[i] = work->sn_dis;
    }

    for (t3 = mgr->n_watchers - 1; t3 > -1; t3 = t4)
    {
        t4 = -1;
        for (i = 1; t3 >= i; i++)
        {
            /* do/while(0) is required to reproduce the match */
            do
            {
                min = dists[i - 1];
                prev = i - 1;
            } while (0);

            cur = dists[i];

            if (cur < min)
            {
                dists[i - 1] = cur;
                dists[i] = min;

                b = ZakoCommand.order[i - 1];
                a = ZakoCommand.order[i];
                t4 = prev;

                ZakoCommand.order[i - 1] = a;
                ZakoCommand.order[i] = b;
            }
        }
    }

    for (i = 0; i < mgr->n_watchers; i++)
    {
        work = mgr->watchers[ZakoCommand.order[i]].work;
        work->chase_dis = ZakoChaseDist[ZakoCommand.order[i]];
    }
}
void ZakoCom_800D490C(COMMANDER *mgr)
{
    int i;
    int min;
    int best;

    SoundPlayTime--;
    if (SoundPlayTime < 0)
    {
        SoundPlayTime = 0;
    }
    if (SoundPlayTime > 0)
    {
        return;
    }
    min = 100000;
    best = 0;
    for (i = 0; i < mgr->n_watchers; i++)
    {
        if (mgr->watchers[i].field_4 == 2)
        {
            Work *w = mgr->watchers[i].work;

            if (w->pad.sound != 0 && w->sn_dis < min)
            {
                best = w->pad.sound;
                min = w->sn_dis;
            }
            w->pad.sound = 0;
        }
    }
    if (best != 0)
    {
        SoundPlayTime = 0x1E;
        GM_SeSet2(0, 0x30, s03d_800D46F8(best));
    }
}
void ZakoCom_800D49F0(WATCHER *e, int idx)
{
    int state = e->field_8;

    switch (state)
    {
    case 0:
        if (e->field_4 == 1)
        {
            e->field_8 = 1;
            e->field_0 = 1;
            printf("%d reset_enemy_num[%d ]\n", idx, ++ZakoCommand.n_reset);
        }
        break;
    case 1:
        e->field_0--;
        if (e->field_0 <= 0)
        {
            e->field_8 = 2;
            e->field_0 = 0;
        }
        break;
    case 2:
    {
        COMMANDER *mgr = &ZakoCommand;

        switch (mgr->alert_mode)
        {
        case 0:
            if (mgr->field_10C & 1)
            {
                s03d_800D42DC();
                e->field_4 = state;
                e->field_8 = 0;
            }
            break;
        case 1:
            if (mgr->n_reset < 16)
            {
                s03d_800D42DC();
                e->field_4 = state;
                e->field_8 = 0;
            }
            break;
        }
        break;
    }
    }
}
int ZakoCom_800D4B08(int a, int b)
{
    if (a < b)
    {
        a = b;
    }
    return a;
}
void ZakoCom_800D4B20(int targetval, COMMANDER *mgr)
{
    int v = mgr->alert_level;

    if (v - targetval >= 5)
    {
        mgr->alert_level = v - 4;
    }
    else
    {
        mgr->alert_level = targetval;
    }
    if (mgr->alert_level < ZakoTopCommand.alert)
    {
        mgr->alert_level = ZakoTopCommand.alert;
    }
    ZakoCom_800D4070(0);
}
void s03d_800D4B84(COMMANDER *command)
{
    int alert;

    switch (command->alert_mode)
    {
    case 0:
        if (command->alert_level >= 255)
        {
            command->alert_level = 0xFF;
            GM_AlertModeSet(3);
            command->alert_mode = 1;
            GM_SeSet2(NULL, 0x3F, 0x2A);
            ZakoCommand.n_reset = 0;
        }
        break;
    case 1:
        if (command->alert_level <= 0)
        {
            GM_AlertModeSet(2);
            command->alert_mode = 2;
            command->alert_time = 0;
        }
        alert = command->alert_level;
        if (alert >= 0x101)
        {
            alert = 0x100;
        }
        GM_SetAlertMax(alert);
        break;
    case 2:
        command->alert_time--;
        if (command->alert_time <= 0)
        {
            GM_AlertModeSet(0);
            command->alert_mode = 0;
            command->alert_time = 0;
        }
        if (command->alert_level >= 255)
        {
            command->alert_level = 0xFF;
            GM_AlertModeSet(3);
            command->alert_mode = 1;
            ZakoCommand.n_reset = 0;
        }
        alert = command->alert_time;
        if (alert >= 0x101)
        {
            alert = 0x100;
        }
        GM_SetAlertMax(alert);
        break;
    }
    ZakoTopCommand.mode = command->alert_mode;
}
void s03d_800D4CE0(GV_ACT *actor)
{
    int i;
    int alert;
    Work *watcher;

    alert = 0;
    for (i = 0; i < ZakoCommand.n_watchers; i++)
    {
        if (ZakoCommand.watchers[i].field_4 == 2)
        {
            watcher = ZakoCommand.watchers[i].work;
            alert = ZakoCom_800D4B08(alert, watcher->alert_level);
        }
        else if (ZakoCommand.watchers[i].field_4 == 1)
        {
            ZakoCom_800D49F0(&ZakoCommand.watchers[i], i);
        }
    }
    ZakoCom_800D490C(&ZakoCommand);
    ZakoCom_800D4B20(alert, &ZakoCommand);
    s03d_800D4B84(&ZakoCommand);
    s03d_800D47BC(&ZakoCommand);
    ZakoCommand.field_10C = 0;
}
void ZakoCom_800D4DD4(void)
{
    int addr = GM_PlayerAddress;

    if ((addr & 0xFF) == ((addr >> 8) & 0xFF) && (addr & 0xFF) != 0xFF)
    {
        ZakoPlayerAddress = addr;
        ZakoPlayerPosition = GM_PlayerPosition;
        ZakoPlayerMap = GM_PlayerMap;
    }
}
int ZakoCom_800D4E48(char *str)
{
    int count = 0;

    if (str != 0)
    {
        do
        {
            int proc = GCL_StrToInt(str);

            str = GCL_NextStr();
            GCL_ExecProc(proc, NULL);
            count++;
        } while (str != 0);
    }

    return count;
}
void s03d_800D4EAC(void)
{
    int i;
    int count;

    count = ZakoCommand.n_reset;
    if (GM_GameOverTimer != 0 || GM_Vitality <= 0)
    {
        return;
    }

    switch (ZakoGameFlag)
    {
    case 0:
        if (ZakoCommand.time2 == 0)
        {
            if (GM_StreamStatus() == -1)
            {
                GM_VoxStream(ZakoCommand.vox[0], 0x40000000);
            }
        }
        if (count != 0)
        {
            ZakoGameFlag = 1;
            ZakoCommand.time2 = 0;
        }
        ZakoCommand.time2++;
        break;
    case 1:
        if (count < 3)
        {
            break;
        }
        if (GM_ItemTypes[GM_Item + 1] & 2)
        {
            GM_Item = -1;
        }
        if (GM_WeaponTypes[GM_Weapon + 1] & 0x200)
        {
            GM_Weapon = -1;
        }
        OpenCinemaScreen(0, 60000);
        ZakoGameFlag = 2;
        ZakoCommand.time2 = 0;
        GM_GameStatus |= PLAYER_SECOND_AVAILABLE | STATE_MENU_DISABLE | STATE_LIFE_OFF | STATE_RADIO_OFF;
        break;
    case 2:
        if (ZakoCommand.time2 == 0)
        {
            if (GM_StreamStatus() == 1)
            {
                GM_StreamPlayStart();
            }
            if (ZakoCommand.procs[5] >= 0)
            {
                GCL_ExecProc(ZakoCommand.procs[5], NULL);
            }
        }
        if (ZakoCommand.time2 > 10)
        {
            ZakoGameFlag = 3;
            ZakoCommand.time2 = 0;
        }
        ZakoCommand.time2++;
        break;
    case 3:
        if (ZakoCommand.time2 > 30)
        {
            if (ZakoCommand.procs[0] >= 0)
            {
                GCL_ExecProc(ZakoCommand.procs[0], NULL);
            }
            ZakoGameFlag = 4;
            ZakoCommand.time2 = 0;
        }
        ZakoCommand.time2++;
        break;
    case 4:
        if (ZakoCommand.time2 > 60)
        {
            if (GM_StreamStatus() == -1)
            {
                GM_VoxStream(ZakoCommand.vox[1], 0);
                if (ZakoCommand.procs[1] >= 0)
                {
                    GCL_ExecProc(ZakoCommand.procs[1], NULL);
                }
                ZakoGameFlag = 5;
                ZakoCommand.time2 = 0;
                if (GM_Weapons[0] < 0)
                {
                    GM_PlayerControl->mov.vx = s03d_dword_800C3B90.vx;
                    GM_PlayerControl->mov.vz = s03d_dword_800C3B90.vz;
                }
            }
        }
        ZakoCommand.time2++;
        break;
    case 5:
        if (ZakoCommand.time2 == 60)
        {
            if (ZakoCommand.procs[2] >= 0)
            {
                GCL_ExecProc(ZakoCommand.procs[2], NULL);
            }
            ZakoGameFlag = 6;
            ZakoCommand.time2 = 0;
        }
        ZakoCommand.time2++;
        break;
    case 6:
        if (ZakoCommand.time2 == 30)
        {
            if (ZakoCommand.procs[3] >= 0)
            {
                GCL_ExecProc(ZakoCommand.procs[3], NULL);
            }
        }
        if (ZakoCommand.time2 == 180)
        {
            if (ZakoCommand.procs[4] >= 0)
            {
                GCL_ExecProc(ZakoCommand.procs[4], NULL);
            }
        }
        if (ZakoCommand.time2 > 182)
        {
            CloseCinemaScreen();
            GM_GameStatus &= ~(PLAYER_SECOND_AVAILABLE | STATE_MENU_DISABLE | STATE_LIFE_OFF | STATE_RADIO_OFF);
            ZakoGameFlag = 8;
            ZakoCommand.time2 = 0;
        }
        ZakoCommand.time2++;
        break;
    case 8:
        if (count == 13 || count == 14)
        {
            ZakoGameFlag = 9;
            ZakoCommand.time2 = 0;
        }
        ZakoCommand.time2++;
        break;
    case 9:
        if (count >= 15)
        {
            ZakoGameFlag = 10;
            ZakoCommand.time2 = 0;
        }
        break;
    case 10:
        ZakoCommand.time2 += 2;
        if (ZakoCommand.time2 - 1 > 30)
        {
            ZakoGameFlag = 11;
            ZakoCommand.time2 = 0;
        }
        break;
    case 11:
        ZakoCommand.time2 += 2;
        if (ZakoCommand.time2 - 1 > 220)
        {
            ZakoGameFlag = 12;
        }
        break;
    case 12:
        if (count >= 17)
        {
            ZakoGameFlag = 13;
            ZakoCommand.time2 = 0;
        }
        break;
    case 13:
        if (ZakoTopCommand.mode == 0)
        {
            ZakoGameFlag = 14;
            ZakoCommand.time2 = 0;
            for (i = 0; i < 8; i++)
            {
                if (ZakoCommand.watchers[i].work != NULL)
                {
                    ZakoGameFlag = 13;
                }
            }
        }
        break;
    case 14:
        if (ZakoCommand.time2 > 30)
        {
            ZakoGameFlag = 15;
        }
        ZakoCommand.time2++;
        break;
    case 15:
        break;
    }
}

void s03d_800D53EC(GV_ACT *actor)
{
    s03d_800D4EAC();
    ZakoCom_800D4DD4();
    s03d_800D4CE0(actor);
    ZakoCommand.time++;
    ZakoCom_800D41C0();
    if (ZakoGameFlag == 15)
    {
        GV_DestroyActor(actor);
    }
}

void s03d_800D5458(GV_ACT *actor)
{
    if (ZakoCommand.end_proc >= 0)
    {
        GCL_ExecProc(ZakoCommand.end_proc, NULL);
    }
}

int ZakoCom_800D5484(char *opt, int *out)
{
    int *p = out;
    int count = 0;
    char *str;

    while ((str = GCL_NextStr()) != 0)
    {
        *p = GCL_StrToInt(str);
        p++;
        count++;
    }

    return count;
}
int ZakoCom_800D54DC(void)
{
    char *opt = GCL_GetOption('s');

    if (opt == 0)
    {
        return 0;
    }
    if (ZakoCom_800D5484(opt, ZakoCommand.vox) < 4)
    {
        return 0;
    }
    fprintf(0, "Err Err Err Sound Buff Over !!\n");
    return -1;
}
int s03d_800D5538(void)
{
    int   i;
    int   c;
    char *opt;

    c = -1;
    for (i = 7; i >= 0; i--)
    {
        ZakoCommand.procs[i] = c;
    }

    i = 0;
    opt = GCL_GetOption('a');
    while (opt)
    {
        if (i >= 8)
        {
            return -1;
        }

        ZakoCommand.procs[i] = GCL_StrToInt(opt);
        opt = GCL_NextStr();
        i++;
    }

    return i;
}
void s03d_800D55C8(ZakoComWork *work, int name, int where)
{
    int   i;
    char *opt;

    s03d_dword_800DC2E0 = 0;
    ZakoGameFlag = 0;
    ZakoCommand.alert_level = ZakoCommand.field_20 = 0;
    s03d_dword_800DC2F4 = 0;
    ZakoCommand.n_reset = 0;
    ZakoCommand.time2 = 0;
    ZakoCom_800D54DC();
    GM_InitHomingSystem();

    for (i = 0; i < 8; i++)
    {
        ZakoCommand.watchers[i].field_0 = 0;
        ZakoCommand.watchers[i].field_4 = 0;
        ZakoCommand.watchers[i].field_8 = 0;
        ZakoCommand.watchers[i].work = NULL;
    }

    for (i = 7; i >= 0; i--)
    {
        ZakoCommand.order[i] = i;
    }

    ZakoCommand.time = 0;
    ZakoCommand.alert_mode = 0;
    ZakoTopCommand.mode = 0;
    ZakoTopCommand.alert = 0;
    ZakoCommand.map = GM_GetMap(where);

    if (GCL_GetOption('e'))
    {
        ZakoCommand.end_proc = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        ZakoCommand.end_proc = -1;
    }

    s03d_800D5538();

    if (GCL_GetOption('b'))
    {
        ZakoCommand.field_144 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        ZakoCommand.field_144 = -1;
    }

    opt = GCL_GetOption('v');
    if (opt)
    {
        ZakoCommand.n_zones = ZakoCom_800D4284(opt, ZakoCommand.zones);
    }
    else
    {
        ZakoCommand.n_zones = 1;
        ZakoCommand.zones[0] = 0;
    }

    for (i = 0; i < ZakoCommand.n_zones; i++)
    {
        fprintf(1, "zone=%d ", ZakoCommand.zones[i]);
    }

    ZakoCommand.far_zone = 0;
    s03d_dword_800DC2F0 = 0;

    opt = GCL_GetOption('j');
    if (opt)
    {
        ZakoCommand.jdata.count = ZakoCom_800D4224(opt, &ZakoCommand.jdata);
    }
    else
    {
        ZakoCommand.jdata.count = 1;
        ZakoCommand.jdata.data[0][0] = 0;
        ZakoCommand.jdata.data[0][1] = 0;
    }

    ZakoCommand.jdata.map = where;
    ZakoCommand.n_watchers = 0;

    opt = GCL_GetOption('n');
    if (opt)
    {
        ZakoCommand.n_watchers = ZakoCom_800D4E48(opt);
    }

    ZakoCommand.field_0 = 0;
    ZakoCommand.field_4 = 0;
    ZakoCommand.field_110 = 0;
}

void *s03d_800D580C(int name, int where)
{
    ZakoComWork *work;

    work = GV_NewActor(4, sizeof(ZakoComWork));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s03d_800D53EC, s03d_800D5458, "zakocom.c");
        s03d_800D55C8(work, name, where);
    }
    return work;
}
