#include "zako.h"

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

SVECTOR s03d_dword_800C3B90 = {0x1F40, 0, 0x3E8, 0};
unsigned char s03d_dword_800C3B98[4] = { 1, 1, 0, 0 };
unsigned char s03d_dword_800C3B9C[4] = { 255, 1, 0, 0 };
int s03d_dword_800C3BA0 = 0x00000BB8;
int s03d_dword_800C3BA4 = 0x00000FA0;
int s03d_dword_800C3BA8 = 0x00001B58;
int s03d_dword_800C3BAC = 0x00001F40;
int s03d_dword_800C3BB0 = 0x00001F40;
int s03d_dword_800C3BB4 = 0x00001F40;
int s03d_dword_800C3BB8 = 0x00001F40;
int s03d_dword_800C3BBC = 0x00001F40;
int s03d_dword_800C3BC0 = 0x00000000;

const char s03d_dword_800DBB48[12] = "dareda!!\n";
const char s03d_dword_800DBB54[16] = "nanno otoda!!\n";
const char s03d_dword_800DBB64[16] = "tadano hakoka\n";
const char s03d_dword_800DBB74[20] = "kono asiatoha??\n";
const char s03d_dword_800DBB88[16] = "kinoseika !!\n";
const char s03d_dword_800DBB98[8] = "itazo \n";
const char s03d_dword_800DBBA0[12] = "kottida!!\n";
const char s03d_dword_800DBBAC[20] = "haitini modoruzo!!\n";
const char s03d_dword_800DBBC0[16] = "kottida !!\n";

extern int s03d_dword_800DC2E0;
extern int s03d_dword_800DC2F0;
extern int s03d_dword_800DC2F8;
extern int s03d_dword_800DC310;
extern int s03d_dword_800DC31C;
extern int s03d_dword_800DC378;
extern int s03d_dword_800DC2F4;
extern int s03d_dword_800DC2FC;
extern int s03d_dword_800DC300;
extern SVECTOR s03d_dword_800DC308;
extern int s03d_dword_800DC424;
extern int printf(const char *format, ...);
extern int s03d_dword_800C3BC0;
void s03d_800D42DC(void);
int s03d_800D46F8(int cmd);
void s03d_800D47BC(ZakoComMgr *command);
void s03d_800D4B84(ZakoComMgr *command);

int ZakoCom_800D3FF4(ZakoActor *actor)
{
    ZakoComMgr *mgr = ZAKOCOM_MGR;
    int i;

    for (i = 0; i < 8; i++)
    {
        if (mgr->entries[i].field_C == 0)
        {
            mgr->entries[i].field_C = actor;
            mgr->entries[i].field_4 = 2;
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
    ZakoComMgr *mgr = ZAKOCOM_MGR;

    mgr->entries[idx].field_C = 0;
    mgr->entries[idx].field_4 = 1;
}

void ZakoCom_800D4070(int value)
{
    s03d_dword_800DC2E8.alert = value;
}

void ZakoCom_800D407C(int value)
{
    s03d_dword_800DC2E8.mode = value;
}
void ZakoCom_800D4088(void)
{
    ZakoComMgr *mgr = ZAKOCOM_MGR;

    mgr->field_24 = s03d_dword_800DC2FC;
    mgr->field_2C = s03d_dword_800DC308;
    mgr->field_28 = s03d_dword_800DC300;
}
void ZakoCom_800D40D4(void)
{
    int addr = HZD_GetAddress(GM_WhereList[0]->map->hzd, &GM_NoisePosition, -1);
    ZakoComMgr *mgr = ZAKOCOM_MGR;

    mgr->field_24 = addr;
    mgr->field_2C = GM_NoisePosition;
    mgr->field_28 = GM_PlayerMap;
}
int s03d_800D414C(int map_id, int val)
{
    int i;
    A4_STRUCT *unk = (A4_STRUCT *)&s03d_dword_800DC378;

    if (unk->map_id == map_id)
    {
        for (i = 0; i < unk->n_entry; i++)
        {
            if (unk->field_04[i].field_00 == val)
            {
                return unk->field_04[i].field_02;
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
        NewPadVibration(s03d_dword_800C3B98, 1);
        NewPadVibration(s03d_dword_800C3B9C, 2);
        s03d_dword_800DC2F4--;
    }
    else
    {
        s03d_dword_800DC2F4 = 0;
    }
}
int ZakoCom_800D4224(int arg0, short *out)
{
    int count = 0;
    int i = 0;

    do
    {
        count++;
        out[i + 2] = GCL_StrToInt(GCL_NextStr());
        out[i + 3] = GCL_StrToInt(GCL_NextStr());
        i += 2;
    } while (GCL_NextStr() != 0);

    return count;
}
int ZakoCom_800D4284(int arg0, short *out)
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

    for ( ; i < ZAKOCOM_MGR->field_34 ; i++ )
    {
        zone = &ZAKOCOM_MGR->field_64->hzd->def->zones[ ZAKOCOM_MGR->field_38[ i ] ];
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

    ZAKOCOM_MGR->field_36 = reset_pos;
}
int ZakoCom_800D43CC(int arg)
{
    return s03d_dword_800DC31C % arg;
}

void ZakoCom_800D440C(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, s03d_dword_800DBB48);
        out[0] = 0x80;
    }
    else if (r == 1)
    {
        fprintf(1, s03d_dword_800DBB48);
        out[0] = 0x80;
    }
}
void ZakoCom_800D4460(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, s03d_dword_800DBB54);
        out[0] = 0x87;
    }
    else if (r == 1)
    {
        fprintf(1, s03d_dword_800DBB54);
        out[0] = 0x87;
    }
}
void ZakoCom_800D44B4(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, s03d_dword_800DBB64);
        out[0] = 0x8B;
    }
    else if (r == 1)
    {
        fprintf(1, s03d_dword_800DBB64);
        out[0] = 0x8B;
    }
}
void ZakoCom_800D4508(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, s03d_dword_800DBB74);
        out[0] = 0x8A;
    }
    else if (r == 1)
    {
        fprintf(1, s03d_dword_800DBB74);
        out[0] = 0x8A;
    }
}
void ZakoCom_800D455C(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, s03d_dword_800DBB88);
        out[0] = 0x86;
    }
    else if (r == 1)
    {
        fprintf(1, s03d_dword_800DBB88);
        out[0] = 0x86;
    }
}
void ZakoCom_800D45B0(int *out)
{
    switch (ZakoCom_800D43CC(3))
    {
    case 0:
        fprintf(1, s03d_dword_800DBB98);
        out[0] = 0x82;
        break;
    case 1:
        fprintf(1, s03d_dword_800DBBA0);
        out[0] = 0x81;
        break;
    case 2:
        fprintf(1, s03d_dword_800DBBA0);
        out[0] = 0x81;
        break;
    }
}
void ZakoCom_800D4640(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, s03d_dword_800DBBAC);
        out[0] = 0x85;
    }
    else if (r == 1)
    {
        fprintf(1, s03d_dword_800DBBAC);
        out[0] = 0x85;
    }
}
void ZakoCom_800D4694(int *out)
{
    switch (ZakoCom_800D43CC(2))
    {
    case 0:
        fprintf(1, s03d_dword_800DBBC0);
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
void s03d_800D47BC(ZakoComMgr *mgr)
{
    int i;
    int prev;
    int t3;
    int t4;
    int dists[8];
    int cur, min;
    int a, b;
    ZakoActor *work;

    for (i = 0; i < mgr->count; i++)
    {
        work = mgr->entries[ZAKOCOM_MGR->field_40[i]].field_C;
        dists[i] = work->field_B90;
    }

    for (t3 = mgr->count - 1; t3 > -1; t3 = t4)
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

                b = ZAKOCOM_MGR->field_40[i - 1];
                a = ZAKOCOM_MGR->field_40[i];
                t4 = prev;

                ZAKOCOM_MGR->field_40[i - 1] = a;
                ZAKOCOM_MGR->field_40[i] = b;
            }
        }
    }

    for (i = 0; i < mgr->count; i++)
    {
        work = mgr->entries[ZAKOCOM_MGR->field_40[i]].field_C;
        work->field_B64 = (&s03d_dword_800C3BA0)[ZAKOCOM_MGR->field_40[i]];
    }
}
void ZakoCom_800D490C(ZakoComMgr *mgr)
{
    int i;
    int min;
    int best;

    s03d_dword_800C3BC0--;
    if (s03d_dword_800C3BC0 < 0)
    {
        s03d_dword_800C3BC0 = 0;
    }
    if (s03d_dword_800C3BC0 > 0)
    {
        return;
    }
    min = 100000;
    best = 0;
    for (i = 0; i < mgr->count; i++)
    {
        if (mgr->entries[i].field_4 == 2)
        {
            ZakoActor *w = mgr->entries[i].field_C;

            if (w->field_AE8 != 0 && w->field_B90 < min)
            {
                best = w->field_AE8;
                min = w->field_B90;
            }
            w->field_AE8 = 0;
        }
    }
    if (best != 0)
    {
        s03d_dword_800C3BC0 = 0x1E;
        GM_SeSet2(0, 0x30, s03d_800D46F8(best));
    }
}
void ZakoCom_800D49F0(ZakoComEntry *e, int idx)
{
    int state = e->field_8;

    switch (state)
    {
    case 0:
        if (e->field_4 == 1)
        {
            e->field_8 = 1;
            e->field_0 = 1;
            printf("%d reset_enemy_num[%d ]\n", idx, ++ZAKOCOM_MGR->field_60);
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
        ZakoComMgr *mgr = ZAKOCOM_MGR;

        switch (mgr->field_1C)
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
            if (mgr->field_60 < 16)
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
void ZakoCom_800D4B20(int targetval, ZakoComMgr *mgr)
{
    int v = mgr->field_18;

    if (v - targetval >= 5)
    {
        mgr->field_18 = v - 4;
    }
    else
    {
        mgr->field_18 = targetval;
    }
    if (mgr->field_18 < s03d_dword_800DC2E8.alert)
    {
        mgr->field_18 = s03d_dword_800DC2E8.alert;
    }
    ZakoCom_800D4070(0);
}
void s03d_800D4B84(ZakoComMgr *command)
{
    int alert;

    switch (command->field_1C)
    {
    case 0:
        if (command->field_18 >= 255)
        {
            command->field_18 = 0xFF;
            GM_AlertModeSet(3);
            command->field_1C = 1;
            GM_SeSet2(NULL, 0x3F, 0x2A);
            ZAKOCOM_MGR->field_60 = 0;
        }
        break;
    case 1:
        if (command->field_18 <= 0)
        {
            GM_AlertModeSet(2);
            command->field_1C = 2;
            command->field_14 = 0;
        }
        alert = command->field_18;
        if (alert >= 0x101)
        {
            alert = 0x100;
        }
        GM_SetAlertMax(alert);
        break;
    case 2:
        command->field_14--;
        if (command->field_14 <= 0)
        {
            GM_AlertModeSet(0);
            command->field_1C = 0;
            command->field_14 = 0;
        }
        if (command->field_18 >= 255)
        {
            command->field_18 = 0xFF;
            GM_AlertModeSet(3);
            command->field_1C = 1;
            ZAKOCOM_MGR->field_60 = 0;
        }
        alert = command->field_14;
        if (alert >= 0x101)
        {
            alert = 0x100;
        }
        GM_SetAlertMax(alert);
        break;
    }
    s03d_dword_800DC2E8.mode = command->field_1C;
}
void s03d_800D4CE0(GV_ACT *actor)
{
    int i;
    int alert;
    ZakoActor *watcher;

    alert = 0;
    for (i = 0; i < ZAKOCOM_MGR->count; i++)
    {
        if (ZAKOCOM_MGR->entries[i].field_4 == 2)
        {
            watcher = ZAKOCOM_MGR->entries[i].field_C;
            alert = ZakoCom_800D4B08(alert, watcher->field_B28);
        }
        else if (ZAKOCOM_MGR->entries[i].field_4 == 1)
        {
            ZakoCom_800D49F0(&ZAKOCOM_MGR->entries[i], i);
        }
    }
    ZakoCom_800D490C(ZAKOCOM_MGR);
    ZakoCom_800D4B20(alert, ZAKOCOM_MGR);
    s03d_800D4B84(ZAKOCOM_MGR);
    s03d_800D47BC(ZAKOCOM_MGR);
    ZAKOCOM_MGR->field_10C = 0;
}
void ZakoCom_800D4DD4(void)
{
    int addr = GM_PlayerAddress;

    if ((addr & 0xFF) == ((addr >> 8) & 0xFF) && (addr & 0xFF) != 0xFF)
    {
        s03d_dword_800DC2FC = addr;
        s03d_dword_800DC308 = GM_PlayerPosition;
        s03d_dword_800DC300 = GM_PlayerMap;
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

    count = ZAKOCOM_MGR->field_60;
    if (GM_GameOverTimer != 0 || GM_Vitality <= 0)
    {
        return;
    }

    switch (s03d_dword_800DC2F8)
    {
    case 0:
        if (ZAKOCOM_MGR->field_10 == 0)
        {
            if (GM_StreamStatus() == -1)
            {
                GM_VoxStream(ZAKOCOM_MGR->field_114, 0x40000000);
            }
        }
        if (count != 0)
        {
            s03d_dword_800DC2F8 = 1;
            ZAKOCOM_MGR->field_10 = 0;
        }
        ZAKOCOM_MGR->field_10++;
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
        s03d_dword_800DC2F8 = 2;
        ZAKOCOM_MGR->field_10 = 0;
        GM_GameStatus |= PLAYER_SECOND_AVAILABLE | STATE_MENU_DISABLE | STATE_LIFE_OFF | STATE_RADIO_OFF;
        break;
    case 2:
        if (ZAKOCOM_MGR->field_10 == 0)
        {
            if (GM_StreamStatus() == 1)
            {
                GM_StreamPlayStart();
            }
            if (ZAKOCOM_MGR->field_124[5] >= 0)
            {
                GCL_ExecProc(ZAKOCOM_MGR->field_124[5], NULL);
            }
        }
        if (ZAKOCOM_MGR->field_10 > 10)
        {
            s03d_dword_800DC2F8 = 3;
            ZAKOCOM_MGR->field_10 = 0;
        }
        ZAKOCOM_MGR->field_10++;
        break;
    case 3:
        if (ZAKOCOM_MGR->field_10 > 30)
        {
            if (ZAKOCOM_MGR->field_124[0] >= 0)
            {
                GCL_ExecProc(ZAKOCOM_MGR->field_124[0], NULL);
            }
            s03d_dword_800DC2F8 = 4;
            ZAKOCOM_MGR->field_10 = 0;
        }
        ZAKOCOM_MGR->field_10++;
        break;
    case 4:
        if (ZAKOCOM_MGR->field_10 > 60)
        {
            if (GM_StreamStatus() == -1)
            {
                GM_VoxStream(ZAKOCOM_MGR->field_118, 0);
                if (ZAKOCOM_MGR->field_124[1] >= 0)
                {
                    GCL_ExecProc(ZAKOCOM_MGR->field_124[1], NULL);
                }
                s03d_dword_800DC2F8 = 5;
                ZAKOCOM_MGR->field_10 = 0;
                if (GM_Weapons[0] < 0)
                {
                    GM_PlayerControl->mov.vx = s03d_dword_800C3B90.vx;
                    GM_PlayerControl->mov.vz = s03d_dword_800C3B90.vz;
                }
            }
        }
        ZAKOCOM_MGR->field_10++;
        break;
    case 5:
        if (ZAKOCOM_MGR->field_10 == 60)
        {
            if (ZAKOCOM_MGR->field_124[2] >= 0)
            {
                GCL_ExecProc(ZAKOCOM_MGR->field_124[2], NULL);
            }
            s03d_dword_800DC2F8 = 6;
            ZAKOCOM_MGR->field_10 = 0;
        }
        ZAKOCOM_MGR->field_10++;
        break;
    case 6:
        if (ZAKOCOM_MGR->field_10 == 30)
        {
            if (ZAKOCOM_MGR->field_124[3] >= 0)
            {
                GCL_ExecProc(ZAKOCOM_MGR->field_124[3], NULL);
            }
        }
        if (ZAKOCOM_MGR->field_10 == 180)
        {
            if (ZAKOCOM_MGR->field_124[4] >= 0)
            {
                GCL_ExecProc(ZAKOCOM_MGR->field_124[4], NULL);
            }
        }
        if (ZAKOCOM_MGR->field_10 > 182)
        {
            CloseCinemaScreen();
            GM_GameStatus &= ~(PLAYER_SECOND_AVAILABLE | STATE_MENU_DISABLE | STATE_LIFE_OFF | STATE_RADIO_OFF);
            s03d_dword_800DC2F8 = 8;
            ZAKOCOM_MGR->field_10 = 0;
        }
        ZAKOCOM_MGR->field_10++;
        break;
    case 8:
        if (count == 13 || count == 14)
        {
            s03d_dword_800DC2F8 = 9;
            ZAKOCOM_MGR->field_10 = 0;
        }
        ZAKOCOM_MGR->field_10++;
        break;
    case 9:
        if (count >= 15)
        {
            s03d_dword_800DC2F8 = 10;
            ZAKOCOM_MGR->field_10 = 0;
        }
        break;
    case 10:
        ZAKOCOM_MGR->field_10 += 2;
        if (ZAKOCOM_MGR->field_10 - 1 > 30)
        {
            s03d_dword_800DC2F8 = 11;
            ZAKOCOM_MGR->field_10 = 0;
        }
        break;
    case 11:
        ZAKOCOM_MGR->field_10 += 2;
        if (ZAKOCOM_MGR->field_10 - 1 > 220)
        {
            s03d_dword_800DC2F8 = 12;
        }
        break;
    case 12:
        if (count >= 17)
        {
            s03d_dword_800DC2F8 = 13;
            ZAKOCOM_MGR->field_10 = 0;
        }
        break;
    case 13:
        if (s03d_dword_800DC2E8.mode == 0)
        {
            s03d_dword_800DC2F8 = 14;
            ZAKOCOM_MGR->field_10 = 0;
            for (i = 0; i < 8; i++)
            {
                if (ZAKOCOM_MGR->entries[i].field_C != NULL)
                {
                    s03d_dword_800DC2F8 = 13;
                }
            }
        }
        break;
    case 14:
        if (ZAKOCOM_MGR->field_10 > 30)
        {
            s03d_dword_800DC2F8 = 15;
        }
        ZAKOCOM_MGR->field_10++;
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
    ZAKOCOM_MGR->field_C++;
    ZakoCom_800D41C0();
    if (s03d_dword_800DC2F8 == 15)
    {
        GV_DestroyActor(actor);
    }
}

void s03d_800D5458(GV_ACT *actor)
{
    if (ZAKOCOM_MGR->field_120 >= 0)
    {
        GCL_ExecProc(ZAKOCOM_MGR->field_120, NULL);
    }
}

int ZakoCom_800D5484(int arg0, int *out)
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
    if (ZakoCom_800D5484((int)opt, &s03d_dword_800DC424) < 4)
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
        ZAKOCOM_MGR->field_124[i] = c;
    }

    i = 0;
    opt = GCL_GetOption('a');
    while (opt)
    {
        if (i >= 8)
        {
            return -1;
        }

        ZAKOCOM_MGR->field_124[i] = GCL_StrToInt(opt);
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
    s03d_dword_800DC2F8 = 0;
    ZAKOCOM_MGR->field_18 = ZAKOCOM_MGR->field_20 = 0;
    s03d_dword_800DC2F4 = 0;
    ZAKOCOM_MGR->field_60 = 0;
    ZAKOCOM_MGR->field_10 = 0;
    ZakoCom_800D54DC();
    GM_InitHomingSystem();

    for (i = 0; i < 8; i++)
    {
        ZAKOCOM_MGR->entries[i].field_0 = 0;
        ZAKOCOM_MGR->entries[i].field_4 = 0;
        ZAKOCOM_MGR->entries[i].field_8 = 0;
        ZAKOCOM_MGR->entries[i].field_C = NULL;
    }

    for (i = 7; i >= 0; i--)
    {
        ZAKOCOM_MGR->field_40[i] = i;
    }

    ZAKOCOM_MGR->field_C = 0;
    ZAKOCOM_MGR->field_1C = 0;
    s03d_dword_800DC2E8.mode = 0;
    s03d_dword_800DC2E8.alert = 0;
    ZAKOCOM_MGR->field_64 = GM_GetMap(where);

    if (GCL_GetOption('e'))
    {
        ZAKOCOM_MGR->field_120 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        ZAKOCOM_MGR->field_120 = -1;
    }

    s03d_800D5538();

    if (GCL_GetOption('b'))
    {
        ZAKOCOM_MGR->field_144 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        ZAKOCOM_MGR->field_144 = -1;
    }

    opt = GCL_GetOption('v');
    if (opt)
    {
        ZAKOCOM_MGR->field_34 = ZakoCom_800D4284((int)opt, ZAKOCOM_MGR->field_38);
    }
    else
    {
        ZAKOCOM_MGR->field_34 = 1;
        ZAKOCOM_MGR->field_38[0] = 0;
    }

    for (i = 0; i < ZAKOCOM_MGR->field_34; i++)
    {
        fprintf(1, "zone=%d ", ZAKOCOM_MGR->field_38[i]);
    }

    ZAKOCOM_MGR->field_36 = 0;
    s03d_dword_800DC2F0 = 0;

    opt = GCL_GetOption('j');
    if (opt)
    {
        ZAKOCOM_MGR->field_68.n_entry = ZakoCom_800D4224((int)opt, (short *)&ZAKOCOM_MGR->field_68);
    }
    else
    {
        ZAKOCOM_MGR->field_68.n_entry = 1;
        ZAKOCOM_MGR->field_68.field_04[0].field_00 = 0;
        ZAKOCOM_MGR->field_68.field_04[0].field_02 = 0;
    }

    ZAKOCOM_MGR->field_68.map_id = where;
    ZAKOCOM_MGR->count = 0;

    opt = GCL_GetOption('n');
    if (opt)
    {
        ZAKOCOM_MGR->count = ZakoCom_800D4E48(opt);
    }

    ZAKOCOM_MGR->field_0 = 0;
    ZAKOCOM_MGR->field_4 = 0;
    ZAKOCOM_MGR->field_110 = 0;
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
