#include "jeep_liq.h"

#include <rand.h>
#include "common.h"
#include "game/game.h"
#include "linkvar.h"
#include "psxdefs.h"

extern int  s19b_dword_800C3AA0;
extern int  s19b_dword_800C3AA8;
extern int  s19b_dword_800C3AB0;
extern int  s19b_dword_800C3AB8;
extern int  s19b_dword_800C3AC0;
extern int  s19b_dword_800C3AC8;
extern int  s19b_dword_800DE650;

extern void *NewJeepBlood(MATRIX *world, int count, MATRIX *root);
extern void *NewJeepBullet(MATRIX *world, int side, int mode, int mode2);
extern void  s19b_jblood_800C7FB8(MATRIX *world);
extern void  ReadRotMatrix(MATRIX *m);

extern int   s19b_jeep_mrl_800D399C(void);
extern int   s19b_jeep_liq_800D771C(int center, int from, int to);
extern void  s19b_jeep_liq_800D6FB8(Work *work);
extern void  s19b_jeep_liq_800D7114(Work *work);
extern void  s19b_jeep_liq_800D7200(Work *work);
extern void  s19b_jeep_liq_800D7330(Work *work);
extern void  s19b_jeep_liq_800D7468(Work *work);
extern void  s19b_jeep_liq_800D76F8(Work *work, int arg1);
extern void  s19b_jeep_liq_800D7B3C(Work *work, int arg1);
extern void  s19b_jeep_liq_800D7BB0(Work *work);
extern void  s19b_jeep_liq_800D8044(Work *work);
extern void  s19b_jeep_liq_800D7A5C(Work *work);
extern void  s19b_jeep_liq_800D7860(Work *work);
extern void  s19b_jeep_liq_800D7CBC(Work *work);
extern void  s19b_jlamp_800D0A20(int arg0);
extern void  s19b_jeep_liq_800D77F0(Work *work);
extern void  s19b_jeep_liq_800D797C(Work *work);
extern void  s19b_jeep_liq_800D7C0C(Work *work);
extern void  s19b_jeep_liq_800D8014(Work *work, int arg1);
extern void  s19b_jeep_liq_800D8118(Work *work);
extern void  s19b_jeep_gls_800CEC24(int arg0, SVECTOR *out);
extern void  sna_act_helper2_helper2_80033054(int id, SVECTOR *vec);
extern int   s19b_jeep_gls_800CEDFC(int arg0, int arg1);

void s19b_jeep_liq_800D6FB8(Work *work)
{
    SVECTOR *pos = (SVECTOR *)&work->prim;
    SVECTOR  rot;
    SVECTOR  vec;

    memset(&vec, 0, 8);
    vec.vz = work->field_3A8;
    rot = vec;
    DG_SetPos2(&DG_ZeroVector, &work->field_390);
    DG_RotVector(&rot, &rot, 1);
    work->field_378.vx = rot.vx;
    work->field_378.vz = rot.vz;
    s19b_jeep_gls_800CEC24(pos->vz - 0x640, &vec);
    GV_SubVec3(&vec, pos, &vec);
    vec.vx += work->field_3A0;
    vec.vx += rsin(work->field_3C8 << 5) * 50 >> 12;
    vec.vx += (rsin(work->field_3C8 << 7) << 1) * work->field_3B8 >> 12;
    work->field_390.vy = GV_VecDir2(&vec);
    work->field_3C8++;
    work->field_3AC = work->field_3A8;
}
void s19b_jeep_liq_800D7114(Work *work)
{
    int state;

    ((void (*)(void))work->field_3DC)();
    ((void (*)(Work *))work->field_3E8)(work);
    ((void (*)(Work *))work->field_3F8)(work);
    s19b_jeep_liq_800D6FB8(work);

    state = Takabe_JeepSystem.field_40;
    if (state != 0)
    {
        if (state == 6)
        {
            work->field_3D0 = (int)s19b_jeep_liq_800D7200;
        }
        else if (state == 7)
        {
            work->field_3D0 = (int)s19b_jeep_liq_800D7330;
        }
        else if (state == 8)
        {
            work->field_3D0 = (int)s19b_jeep_liq_800D7468;
        }
    }
    if (work->field_3D0 != (int)s19b_jeep_liq_800D7114)
    {
        work->field_3EC = 0;
        s19b_jeep_liq_800D76F8(work, (int)s19b_jeep_liq_800D77F0);
        s19b_jeep_liq_800D7B3C(work, (int)s19b_jeep_liq_800D7BB0);
        s19b_jeep_liq_800D8014(work, (int)s19b_jeep_liq_800D8044);
        work->field_3CC = 0;
    }
}
void s19b_jeep_liq_800D7200(Work *work)
{
    SVECTOR *pos = (SVECTOR *)&work->prim;

    switch (work->field_3CC)
    {
    case 0:
        s19b_jeep_liq_800D7A5C(work);
        s19b_jeep_liq_800D6FB8(work);
        work->field_3A0 = GV_NearSpeed(work->field_3A0, 750, 50);
        if (s19b_jeep_gls_800CEDFC(pos->vz, 2000) == 10)
        {
            work->field_3CC = 1;
        }
        break;
    case 1:
        s19b_jeep_liq_800D7860(work);
        s19b_jeep_liq_800D6FB8(work);
        s19b_jeep_liq_800D7CBC(work);
        if (s19b_jeep_gls_800CEDFC(pos->vz, 3000) == 12)
        {
            work->field_3CC = 2;
        }
        break;
    case 2:
        s19b_jeep_liq_800D77F0(work);
        s19b_jeep_liq_800D6FB8(work);
        work->field_3A0 = GV_NearSpeed(work->field_3A0, 650, 50);
        if (work->field_3A0 == 650)
        {
            work->field_3D0 = (int)s19b_jeep_liq_800D7114;
            work->field_3A4 = 650;
            work->field_3CC = 0;
        }
        break;
    }
}
void s19b_jeep_liq_800D7330(Work *work)
{
    SVECTOR *pos = (SVECTOR *)&work->prim;

    switch (work->field_3CC)
    {
    case 0:
        s19b_jeep_liq_800D7A5C(work);
        s19b_jeep_liq_800D6FB8(work);
        work->field_3A0 = GV_NearSpeed(work->field_3A0, 750, 50);
        if (s19b_jeep_gls_800CEDFC(pos->vz, 2000) == 11)
        {
            work->field_3CC = 1;
        }
        break;
    case 1:
        s19b_jeep_liq_800D797C(work);
        s19b_jeep_liq_800D6FB8(work);
        s19b_jeep_liq_800D7C0C(work);
        if (s19b_jeep_gls_800CEDFC(pos->vz, 3000) == 13)
        {
            work->field_3CC = 2;
        }
        break;
    case 2:
        s19b_jeep_liq_800D797C(work);
        s19b_jeep_liq_800D6FB8(work);
        work->field_3A0 = GV_NearSpeed(work->field_3A0, 750, 50);
        if (work->field_3A0 == 750)
        {
            work->field_3D0 = (int)s19b_jeep_liq_800D7114;
            s19b_jeep_liq_800D8014(work, (int)s19b_jeep_liq_800D8118);
            work->field_3CC = 0;
        }
        break;
    }
}
void s19b_jeep_liq_800D7468(Work *work)
{
    SVECTOR *pos = (SVECTOR *)&work->prim;
    SVECTOR  rot;
    SVECTOR  vec;

    switch (work->field_3CC)
    {
    case 0:
        work->field_3C8 = 0;
        work->field_3CC = 1;
        work->field_3C0 = 1;
        Takabe_JeepSystem.field_54 |= 0x20000;
        GM_GameStatus |= 0x104A2000;
        s19b_jlamp_800D0A20(1);
        /* fallthrough */
    case 1:
        s19b_jeep_liq_800D797C(work);
        s19b_jeep_liq_800D6FB8(work);
        work->field_3A0 = GV_NearSpeed(work->field_3A0, 500, 30);
        if (s19b_jeep_gls_800CEDFC(pos->vz, 22000) == 14)
        {
            work->field_3CC = 2;
        }
        break;
    case 2:
        s19b_jeep_liq_800D6FB8(work);
        work->field_3A0 = GV_NearSpeed(work->field_3A0, 250, 30);
        work->field_3A8 = GV_NearSpeed(work->field_3A8, 500, 3);
        if (s19b_jeep_gls_800CEDFC(pos->vz, 6000) == 14)
        {
            work->field_3CC = 3;
            work->field_380 = work->field_378;
        }
        break;
    case 3:
        memset(&vec, 0, 8);
        vec.vz = work->field_3A8;
        rot = vec;
        DG_SetPos2(&DG_ZeroVector, &work->field_390);
        DG_RotVector(&rot, &rot, 1);
        work->field_380.vx = GV_NearExp8(work->field_380.vx, 0);
        work->field_380.vz = GV_NearExp8(work->field_380.vz, 0);
        work->field_378.vx = rot.vx + work->field_380.vx;
        work->field_378.vz = rot.vz + work->field_380.vz;
        work->field_390.vy = GV_NearExp8(work->field_390.vy, 0xC00);
        work->field_3A8 = GV_NearExp4(work->field_3A8, 0);
        work->field_3AC = 0;
        if (work->field_378.vx == 0 && work->field_378.vz == 0)
        {
            work->field_3CC = 4;
        }
        break;
    case 4:
        break;
    }
    work->field_3C8++;
}
void s19b_jeep_liq_800D76B0(Work *work)
{
    ((void (*)(void))work->field_3DC)();
    work->field_3A0 = 0;
    ((void (*)(Work *))work->field_3F8)(work);
    s19b_jeep_liq_800D6FB8(work);
}

void s19b_jeep_liq_800D76F8(Work *work, int arg1)
{
    if (work->field_3DC != arg1)
    {
        work->field_3DC = arg1;
        work->field_3D8 = 0;
        work->field_3D4 = 0;
    }
}

int s19b_jeep_liq_800D771C(int center, int from, int to)
{
    int diff = to - from;
    int base = s19b_jeep_mrl_800D399C();

    if (diff >= 0)
    {
        if (diff > 3000)
        {
            center = GV_NearSpeed(center, base + 100, 15);
        }
        else if (diff > 750)
        {
            center = GV_NearSpeed(center, base + 50, 8);
        }
        else if (diff > 93)
        {
            center = GV_NearSpeed(center, base + 15, 3);
        }
    }
    else
    {
        if (diff < -3000)
        {
            center = GV_NearSpeed(center, base - 100, 15);
        }
        else if (diff < -750)
        {
            center = GV_NearSpeed(center, base - 50, 8);
        }
        else if (diff < -93)
        {
            center = GV_NearSpeed(center, base - 15, 3);
        }
    }
    return center;
}
void s19b_jeep_liq_800D77F0(Work *work)
{
    int v = work->field_360 - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->field_3B0 = s19b_jeep_liq_800D771C(work->field_3B0, 0x753, v);
    work->field_3A8 = GV_NearSpeed(work->field_3A8, work->field_3B0, 5);
}
void s19b_jeep_liq_800D7860(Work *work)
{
    int s1 = work->field_360 - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    int a1 = s19b_jeep_mrl_800D399C();

    if (work->field_3D4 == 0)
    {
        if (work->field_3B4 & 8)
        {
            int v1 = work->field_3A8 - 0x32;
            int v0;
            work->field_3A8 = v1;
            v0 = v1 - v1 / 16;
            work->field_3A8 = v0;
            work->field_3B0 = v0;
            work->field_3D4 = 0x3c;
            Takabe_JeepSystem.field_54 |= 2;
        }
        else if (s1 >= 0x5dd)
        {
            work->field_3B0 = GV_NearSpeed(work->field_3B0, a1 + 0x32, 7);
            Takabe_JeepSystem.field_54 |= 0x1000;
        }
    }
    else
    {
        work->field_3B0 = s19b_jeep_liq_800D771C(work->field_3B0, 0xbb8, s1);
        work->field_3D4--;
    }
    work->field_3A8 = GV_NearSpeed(work->field_3A8, work->field_3B0, 5);
}
void s19b_jeep_liq_800D797C(Work *work)
{
    int v = work->field_360 - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->field_3B0 = s19b_jeep_liq_800D771C(work->field_3B0, 0, v);
    work->field_3A8 = GV_NearSpeed(work->field_3A8, work->field_3B0, 5);
}
void s19b_jeep_liq_800D79EC(Work *work)
{
    int v = work->field_360 - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->field_3B0 = s19b_jeep_liq_800D771C(work->field_3B0, -0x177, v);
    work->field_3A8 = GV_NearSpeed(work->field_3A8, work->field_3B0, 5);
}
void s19b_jeep_liq_800D7A5C(Work *work)
{
    int v = work->field_360 - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->field_3B0 = s19b_jeep_liq_800D771C(work->field_3B0, 0xbb8, v);
    work->field_3A8 = GV_NearSpeed(work->field_3A8, work->field_3B0, 5);
}
void s19b_jeep_liq_800D7ACC(Work *work)
{
    int v = work->field_360 - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->field_3B0 = s19b_jeep_liq_800D771C(work->field_3B0, 0x1194, v);
    work->field_3A8 = GV_NearSpeed(work->field_3A8, work->field_3B0, 5);
}

void s19b_jeep_liq_800D7B3C(Work *work, int arg1)
{
    if (work->field_3E8 != arg1)
    {
        work->field_3E8 = arg1;
        work->field_3E4 = 0;
        work->field_3E0 = 0;
    }
}

int s19b_jeep_liq_800D7B60(int center, int range)
{
    return (rand() * range >> 15) - range / 2 + center;
}
void s19b_jeep_liq_800D7BB0(Work *work)
{
    if (++work->field_3E0 == 0x1e)
    {
        work->field_3A4 = s19b_jeep_liq_800D7B60(0, 0x4b0);
        work->field_3E0 = 0;
    }
    work->field_3A0 = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x1e);
}
void s19b_jeep_liq_800D7C0C(Work *work)
{
    int n = work->field_3E0 + 1;
    work->field_3E0 = n;

    switch (work->field_3E4)
    {
    case 0:
        work->field_3A4 = 0x546;
        work->field_3A0 = GV_NearSpeed(work->field_3A0, 0x546, 0x32);
        if (work->field_3E0 == 0x28)
        {
            work->field_3E4 = 1;
            work->field_3E0 = 0x13;
        }
        break;
    case 1:
        if (n == 0x14)
        {
            work->field_3A4 = s19b_jeep_liq_800D7B60(0x4e2, 0xfa);
            work->field_3E0 = 0;
        }
        work->field_3A0 = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x1e);
        break;
    }
}
void s19b_jeep_liq_800D7CBC(Work *work)
{
    int n = work->field_3E0 + 1;
    work->field_3E0 = n;

    switch (work->field_3E4)
    {
    case 0:
        work->field_3A4 = 0x5dc;
        if (work->field_3E0 == 0x28)
        {
            work->field_3E4 = 1;
            work->field_3E0 = 0x13;
        }
        work->field_3A0 = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x32);
        break;
    case 1:
        if (n == 0x14)
        {
            work->field_3A4 = s19b_jeep_liq_800D7B60(0x5dc, 0xfa);
            work->field_3E0 = 0;
        }
        work->field_3A0 = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x1e);
        break;
    }
}
void s19b_jeep_liq_800D7D68(Work *work)
{
    int n = work->field_3E0 + 1;
    work->field_3E0 = n;

    switch (work->field_3E4)
    {
    case 0:
        if (n == 1)
        {
            work->field_3A4 = s19b_jeep_liq_800D7B60(0x2ee, 0x190);
        }
        else if (n == 0x1e)
        {
            work->field_3E4 = 1;
            work->field_3E0 = 0;
        }
        work->field_3A0 = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x32);
        break;
    case 1:
        if (n == 1)
        {
            work->field_3A4 = -0x226;
        }
        else if (n == 0x3c)
        {
            work->field_3E4 = 0;
            work->field_3E0 = 0;
        }
        work->field_3A0 = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x64);
        break;
    }
}
void s19b_jeep_liq_800D7E2C(Work *work)
{
    int n = work->field_3E0 + 1;
    work->field_3E0 = n;

    switch (work->field_3E4)
    {
    case 0:
        if (n == 1)
        {
            work->field_3A4 = s19b_jeep_liq_800D7B60(-0x2ee, 0x96);
        }
        else if (n == 0x3c)
        {
            work->field_3E4 = 1;
            work->field_3E0 = 0;
        }
        {
            int r = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x4b);
            work->field_3A0 = r;
            if (r == work->field_3A4)
            {
                Takabe_JeepSystem.field_54 |= 0x2000;
            }
        }
        break;
    case 1:
        if (n == 1)
        {
            work->field_3A4 = s19b_jeep_liq_800D7B60(-0x2ee, 0xfa);
        }
        else if (n == 0x1e)
        {
            work->field_3E4 = 1;
            work->field_3E0 = 0;
        }
        work->field_3A0 = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x19);
        break;
    }
}
void s19b_jeep_liq_800D7F20(Work *work)
{
    int n = work->field_3E0 + 1;
    work->field_3E0 = n;

    switch (work->field_3E4)
    {
    case 0:
        if (n == 1)
        {
            work->field_3A4 = s19b_jeep_liq_800D7B60(0x2ee, 0x96);
            work->field_3E0 = 0;
        }
        else if (n == 0x3c)
        {
            work->field_3E4 = 1;
            work->field_3E0 = 0;
        }
        {
            int r = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x4b);
            work->field_3A0 = r;
            if (r == work->field_3A4)
            {
                Takabe_JeepSystem.field_54 |= 0x2000;
            }
        }
        break;
    case 1:
        if (n == 1)
        {
            work->field_3A4 = s19b_jeep_liq_800D7B60(0x2ee, 0xfa);
        }
        else if (n == 0x1e)
        {
            work->field_3E4 = 1;
            work->field_3E0 = 0;
        }
        work->field_3A0 = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x19);
        break;
    }
}
void s19b_jeep_liq_800D8014(Work *work, int arg1)
{
    if (work->field_3F8 != arg1)
    {
        work->field_3F8 = arg1;
        work->field_3E4 = 0;
        work->field_3E0 = 0;
        work->field_3B4 &= ~2;
    }
}
extern unsigned char s19b_dword_800C3A9C[];
extern int s19b_jeep_mrl_800D39B4(SVECTOR *dst);

void s19b_jeep_liq_800D8044(Work *work)
{
    SVECTOR sp10;

    s19b_jeep_mrl_800D39B4(&sp10);
    if (Takabe_JeepSystem.field_5C != 0 && work->field_3F0 >= 0x15)
    {
        work->field_3F0 = 0;
        if (work->field_3A0 > 0)
        {
            s19b_jeep_liq_800D7B3C(work, (int)s19b_jeep_liq_800D7E2C);
        }
        else
        {
            s19b_jeep_liq_800D7B3C(work, (int)s19b_jeep_liq_800D7F20);
        }
        Takabe_JeepSystem.field_54 |= 0x1000;
        GM_SeSet((SVECTOR *)&work->prim, s19b_dword_800C3A9C[GV_RandU(4)]);
    }
    else
    {
        work->field_3F0++;
    }
}
void s19b_jeep_liq_800D8118(Work *work)
{
    SVECTOR dst;
    int     d;

    s19b_jeep_mrl_800D39B4(&dst);
    d = work->ctrl.mov.vx - dst.vz;
    if (d < 0)
    {
        work->field_3EC = 5;
        s19b_jeep_liq_800D76F8(work, (int)s19b_jeep_liq_800D79EC);
        s19b_jeep_liq_800D7B3C(work, (int)s19b_jeep_liq_800D7D68);
    }
    else
    {
        work->field_3EC = 2;
        s19b_jeep_liq_800D76F8(work, (int)s19b_jeep_liq_800D79EC);
        s19b_jeep_liq_800D7B3C(work, (int)s19b_jeep_liq_800D7F20);
    }
}
extern void s19b_jlamp_800D0A20(int arg0);
extern void s19b_jeep_liq_800D7114(Work *work);

void s19b_jeep_liq_800D81A8(Work *work)
{
    int n = work->field_3F0;
    work->field_3F0 = n + 1;
    if (n == 0)
    {
        GM_GameStatus |= STATE_RADIO_OFF | STATE_LIFEBAR_OFF | STATE_MENU_OFF | STATE_RADAR_OFF | STATE_PADRELEASE;
        s19b_jlamp_800D0A20(0);
    }
    else if (n >= 0x150)
    {
        GM_GameStatus &= ~(STATE_RADIO_OFF | STATE_LIFEBAR_OFF | STATE_MENU_OFF | STATE_RADAR_OFF | STATE_PADRELEASE);
        s19b_jeep_liq_800D8014(work, (int)s19b_jeep_liq_800D8044);
        s19b_jeep_liq_800D76F8(work, (int)s19b_jeep_liq_800D77F0);
        work->field_3D0 = (int)s19b_jeep_liq_800D7114;
    }
}
const SVECTOR s19b_dword_800DDE60 = {0x15E, 0x3CF, -0x15E, 0};

void s19b_jeep_liq_800D8250(Work *work)
{
    OBJECT  *body = &work->obj;
    CONTROL *ctl = &work->ctrl;
    DG_OBJS *objs;
    SVECTOR *jpos = &Takabe_JeepSystem.field_138;
    SVECTOR  pos = s19b_dword_800DDE60;

    GM_ActMotion(body);
    ctl->rot = ctl->turn = DG_ZeroVector;
    ctl->mov = pos;
    GM_ActControl(ctl);
    GM_ActObject(body);
    objs = body->objs;
    CompMatrix((MATRIX *)work->prim, &objs->world, &objs->world);
    DG_GetLightMatrix(&ctl->mov, &work->mtx[0]);
    ctl->mov.vx = objs->world.t[0];
    ctl->mov.vy = objs->world.t[1];
    ctl->mov.vz = objs->world.t[2];
    jpos->vx = body->objs->objs[6].world.t[0];
    jpos->vy = body->objs->objs[6].world.t[1];
    jpos->vz = body->objs->objs[6].world.t[2];
    GM_MoveTarget(work->f8E4, &ctl->mov);
    s19b_spark2_m_800D964C(work);
    sna_act_helper2_helper2_80033054(0x7BF2, &work->sv_7B8);
    work->svecs2[6].vx = work->sv_7B8.vx;
    if ((work->f940 & 3) == 1)
    {
        body->objs->flag |= 0x80;
    }
    else
    {
        body->objs->flag &= ~0x80;
    }
}
const char s19b_aLiquid_800DDE68[] = "liquid";
const char s19b_aLqdb_800DDE70[] = "lqd_19b";
const char s19b_aFamas_800DDE78[] = "famas";

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D8420.s")
void s19b_spark2_m_800D8620(Work *work)
{
    GM_FreeTarget(work->f8E4);
    GM_FreeHomingTarget(work->homing);
    GM_FreeObject(&work->obj2);
    GM_FreeControl(&work->ctrl);
    GM_FreeObject(&work->obj);
}
extern void s19b_jeep_liq_800D8250(Work *work);
extern int  s19b_jeep_liq_800D8420(Work *work, int name);
const char s19b_aJeepliqc_800DDE80[] = "jeep_liq.c";
const char s19b_dword_800DDE8C[] = "liqiud";

void *s19b_spark2_m_800D8670(CONTROL *arg0, DG_PRIM *arg1, int *arg2)
{
    Work *work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));

    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jeep_liq_800D8250, s19b_spark2_m_800D8620,
                         s19b_aJeepliqc_800DDE80);
        work->control = arg0;
        work->prim = arg1;
        work->f944 = arg2;
        if (s19b_jeep_liq_800D8420(work, GV_StrCode(s19b_dword_800DDE8C)) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return work;
}
