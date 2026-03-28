#include "hind.h"
#include "linkvar.h"
#include "okajima/spark.h"

extern GM_CAMERA        GM_Camera;
extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

void AN_Smoke_800CE164(SVECTOR *pos, SVECTOR *speed, int index, int script);

int s11g_hind_800D5CD8(SVECTOR *from, SVECTOR *to, SVECTOR *out)
{
    int dx, dy, dz;
    int len;
    int height;

    dx = (from->vx - to->vx) / 16;
    dy = (from->vy - to->vy) / 16;
    dz = (from->vz - to->vz) / 16;

    len = SquareRoot0(dx * dx + dy * dy + dz * dz) * 16;
    height = to->vy - from->vy;

    out->vy = ratan2(to->vx - from->vx, to->vz - from->vz) & 0xFFF;
    out->vx = ratan2(len, height) & 0xFFF;
    out->vz = 0;

    return len;
}

void s11g_hind_800D5DE4(SVECTOR *out, int *yaw)
{
    MATRIX *eye;

    eye = &DG_Chanl(0)->eye;
    out->vx = eye->t[0];
    out->vy = eye->t[1];
    out->vz = eye->t[2];
    *yaw = ratan2(eye->m[0][2], eye->m[2][2]);
}

void s11g_hind_800D5E44(HindWork *work, int a1)
{
    work->field_95C = 30;
    work->field_960 = a1;
}

void s11g_hind_800D5E54(int arg0, SVECTOR *arg1, int se_id)
{
    SVECTOR sp10;
    SVECTOR pos;
    int     yaw;
    short   ang;
    int     vol;
    int     pan;

    if (!(GM_GameStatus & (GAME_FLAG_BIT_07 | STATE_BEHIND_CAMERA)) && !GM_Camera.first_person)
    {
        s11g_hind_800D5CD8(&GM_PlayerPosition, arg1, &sp10);
        ang = sp10.vy + 1024;
        sp10.vy = ang - gUnkCameraStruct2_800B7868.rotate.vy;
    }
    else
    {
        s11g_hind_800D5DE4(&pos, &yaw);
        s11g_hind_800D5CD8(&pos, arg1, &sp10);
        ang = sp10.vy + 1024;
        sp10.vy = ang - yaw;
    }

    sp10.vy &= 0xFFF;

    pan = (rcos(sp10.vy) * 31) / 4096;
    if (pan < 0)
    {
        pan += 255;
    }

    vol = 63;
    if (arg0 > 4000)
    {
        vol = 63 - ((arg0 - 4000) * 63) / 8000;
    }

    if (vol < 20)
    {
        vol = 20;
    }

    GM_SeSet2(pan, vol, se_id);
}

void s11g_hind_800D60D8(int arg0, SVECTOR *arg1, int se_id)
{
    s11g_hind_800D5E54(arg0, arg1, se_id);
}

void s11g_hind_800D5FB4(HindWork *work, int a1)
{
    MATRIX  matrix;
    SVECTOR rotation;
    VECTOR  scale;

    if (a1 == 0)
    {
        rotation.vx = GV_RandS(512) + 1024;
        rotation.vy = GV_RandS(512);
        rotation.vz = GV_RandS(512);

        scale.vx = work->field_670 * 7;
        scale.vy = work->field_670 * 7;
        scale.vz = work->field_670 * 7;
    }
    else
    {
        rotation.vx = 1024;
        rotation.vy = 0;
        rotation.vz = 0;

        scale.vx = work->field_670 * 4;
        scale.vy = work->field_670 * 4;
        scale.vz = work->field_670 * 4;
    }

    rotation.vx += work->field_788.vx;
    rotation.vy += work->field_788.vy;
    rotation.vz += work->field_788.vz;

    RotMatrixYXZ(&rotation, &matrix);

    matrix.t[0] = work->field_7D8.vx;
    matrix.t[1] = work->field_7D8.vy;
    matrix.t[2] = work->field_7D8.vz;

    ScaleMatrix(&matrix, &scale);
    NewSpark(&matrix, 0);

}

void s11g_hind_800D60F0(HindWork *work)
{
    int dx, dz;
    int len;
    int height;

    dx = (work->field_790.vx - work->field_760.vx) >> 1;
    dz = (work->field_790.vz - work->field_760.vz) >> 1;
    work->field_788.vy = ratan2(dx, dz) & 0xFFF;

    len = SquareRoot0(dz * dz + dx * dx);
    height = (work->field_790.vy - work->field_760.vy) >> 1;

    work->field_788.vx = (ratan2(len, height) - 1024) & 0xFFF;
    work->field_788.vz = 0;
}

void s11g_hind_800D619C(HindWork *work, int index)
{
    if (work->field_94C != 1)
    {
        if (GM_StreamStatus() == -1)
        {
            GM_VoxStream(work->vox_ids[index], 0);
        }
    }
}

void s11g_hind_800D61F8(HindWork *work)
{
    work->field_65C.vx = GV_RandS(128);
    work->field_65C.vy = GV_RandS(128);
    work->field_65C.vz = GV_RandS(128);

    work->field_664.vx = GV_RandS(512);
    work->field_664.vy = GV_RandS(512);
    work->field_664.vz = GV_RandS(512);
}

void s11g_hind_800D6260(int *vec, int *pos, int *old, int len)
{
    int interp;

    interp = (*vec * (len - 1) + *pos) / len;
    *old = *vec - interp;
    *vec = interp;
}

void s11g_hind_800D62BC(VECTOR *vec, VECTOR *pos, int len)
{
    vec->vx = (vec->vx * (len - 1) + pos->vx) / len;
    vec->vy = (vec->vy * (len - 1) + pos->vy) / len;
    vec->vz = (vec->vz * (len - 1) + pos->vz) / len;
}

void Function_800D63A4(SVECTOR *vec, SVECTOR *pos, int len)
{
    vec->vx = (vec->vx * (len - 1) + pos->vx) / len;
    vec->vy = (vec->vy * (len - 1) + pos->vy) / len;
    vec->vz = (vec->vz * (len - 1) + pos->vz) / len;
}

void s11g_hind_800D648C(SVECTOR *a, SVECTOR *b, int len)
{
    SVECTOR diff;
    int     scale;

    a->vx &= 0xFFF;
    a->vy &= 0xFFF;
    a->vz &= 0xFFF;

    b->vx &= 0xFFF;
    b->vy &= 0xFFF;
    b->vz &= 0xFFF;

    diff.vx = b->vx - a->vx;
    diff.vy = b->vy - a->vy;
    diff.vz = b->vz - a->vz;

    if (diff.vx >= 2048)
    {
        a->vx += 4096;
    }

    if (diff.vy >= 2048)
    {
        a->vy += 4096;
    }

    if (diff.vz >= 2048)
    {
        a->vz += 4096;
    }

    if (diff.vx <= -2048)
    {
        b->vx += 4096;
    }

    if (diff.vy <= -2048)
    {
        b->vy += 4096;
    }

    if (diff.vz <= -2048)
    {
        b->vz += 4096;
    }

    scale = len - 1;
    a->vy = (a->vy * scale + b->vy) / len;

    len = 8;
    scale = len - 1;
    a->vx = (a->vx * scale + b->vx) / len;
    a->vz = (a->vz * scale + b->vz) / len;
}

void s11g_hind_800D66F0(HindWork *work)
{
    SVECTOR pos;
    SVECTOR speed;

    pos.vx = (GV_RandS(2048) * work->field_66C) / 4096;
    pos.vy = (GV_RandS(2048) * work->field_66C) / 4096;
    pos.vz = (GV_RandS(4096) * work->field_66C) / 4096;

    DG_SetPos2(&DG_ZeroVector, &work->control.rot);
    DG_PutVector(&pos, &pos, 1);
    GV_AddVec3(&pos, &work->field_63C, &pos);

    speed = DG_ZeroVector;

    if (work->field_66C < 819)
    {
        AN_Smoke_800CE164(&pos, &speed, 1, 0);
    }
    else if (work->field_66C < 1024)
    {
        AN_Smoke_800CE164(&pos, &speed, 1, 1);
    }
    else if (work->field_66C < 1365)
    {
        AN_Smoke_800CE164(&pos, &speed, 1, 2);
    }
    else
    {
        AN_Smoke_800CE164(&pos, &speed, 1, 3);
    }
}

const int s11g_dword_800DD190 = 0x800D68E0;
const int s11g_dword_800DD194 = 0x800D68F0;
const int s11g_dword_800DD198 = 0x800D69E4;
const int s11g_dword_800DD19C = 0x800D7628;
const int s11g_dword_800DD1A0 = 0x800D7628;
const int s11g_dword_800DD1A4 = 0x800D7020;
const int s11g_dword_800DD1A8 = 0x800D70A8;
const int s11g_dword_800DD1AC = 0x800D724C;
const int s11g_dword_800DD1B0 = 0x800D743C;
const int s11g_dword_800DD1B4 = 0x800D7628;
const int s11g_dword_800DD1B8 = 0x800D7628;
const int s11g_dword_800DD1BC = 0x800D7628;
const int s11g_dword_800DD1C0 = 0x800D7628;
const int s11g_dword_800DD1C4 = 0x800D7628;
const int s11g_dword_800DD1C8 = 0x800D7628;
const int s11g_dword_800DD1CC = 0x800D7628;
const int s11g_dword_800DD1D0 = 0x800D7628;
const int s11g_dword_800DD1D4 = 0x800D6A54;
const int s11g_dword_800DD1D8 = 0x800D6BE0;
const int s11g_dword_800DD1DC = 0x800D7628;
const int s11g_dword_800DD1E0 = 0x800D7628;
const int s11g_dword_800DD1E4 = 0x800D6D40;

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D6848.s")

const int s11g_dword_800DD1E8 = 0x800D7700;
const int s11g_dword_800DD1EC = 0x800D776C;
const int s11g_dword_800DD1F0 = 0x800D7868;
const int s11g_dword_800DD1F4 = 0x800D9260;
const int s11g_dword_800DD1F8 = 0x800D9260;
const int s11g_dword_800DD1FC = 0x800D7FB4;
const int s11g_dword_800DD200 = 0x800D80D8;
const int s11g_dword_800DD204 = 0x800D827C;
const int s11g_dword_800DD208 = 0x800D8458;
const int s11g_dword_800DD20C = 0x800D8D58;
const int s11g_dword_800DD210 = 0x800D90B4;
const int s11g_dword_800DD214 = 0x800D9260;
const int s11g_dword_800DD218 = 0x800D9260;
const int s11g_dword_800DD21C = 0x800D9260;
const int s11g_dword_800DD220 = 0x800D9260;
const int s11g_dword_800DD224 = 0x800D9260;
const int s11g_dword_800DD228 = 0x800D9260;
const int s11g_dword_800DD22C = 0x800D78D8;
const int s11g_dword_800DD230 = 0x800D7A68;
const int s11g_dword_800DD234 = 0x800D9260;
const int s11g_dword_800DD238 = 0x800D9260;
const int s11g_dword_800DD23C = 0x800D7C3C;
const int s11g_dword_800DD240 = 0x800D96F0;
const int s11g_dword_800DD244 = 0x800D9B70;
const int s11g_dword_800DD248 = 0x800D9B70;
const int s11g_dword_800DD24C = 0x800D9B70;
const int s11g_dword_800DD250 = 0x800D974C;
const int s11g_dword_800DD254 = 0x800D9858;
const int s11g_dword_800DD258 = 0x800D9A74;
const int s11g_dword_800DD25C = 0x800D9B40;
const int s11g_dword_800DD260 = 0x800D9BC4;
const int s11g_dword_800DD264 = 0x800DA520;
const int s11g_dword_800DD268 = 0x800DA520;
const int s11g_dword_800DD26C = 0x800DA520;
const int s11g_dword_800DD270 = 0x800D9C08;
const int s11g_dword_800DD274 = 0x800D9D74;
const int s11g_dword_800DD278 = 0x800D9FD8;
const int s11g_dword_800DD27C = 0x800DA0E0;
const int s11g_dword_800DD280 = 0x800DA2B4;

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D7644.s")

void s11g_hind_800D9344(HindWork *work)
{
    VECTOR  sp10;
    SVECTOR sp20;

    switch (work->field_5C8)
    {
    case 0:
        if ((work->field_430 * 7) / 8 < work->field_434)
        {
            s11g_hind_800D5E44(work, (GV_RandU(4096) % 2) + 130);
        }
        else
        {
            switch (work->field_8C4++ % 3)
            {
            case 0:
                s11g_hind_800D619C(work, 25);
                break;
            case 1:
                s11g_hind_800D619C(work, 26);
                break;
            case 2:
                s11g_hind_800D619C(work, 27);
                break;
            }
        }

        work->field_5C8 = 4;
        work->field_5E4 = GV_RandU(8) + 32;
        work->field_8D0 = 1;

        sp20.vx = (GV_RandU(4096) + 10000) * (GV_RandU(2) * 2 - 1);
        sp20.vy = (-1000 - GV_RandU(4096));
        sp20.vz = (GV_RandU(4096) + 10000) * (GV_RandU(2) * 2 - 1);

        work->field_60C.vx += sp20.vx;
        work->field_60C.vy += sp20.vy;
        work->field_60C.vz += sp20.vz;
        work->field_5F4 += GV_RandS(256);
        /* fallthrough */
    case 4:
        if (work->field_5E4 > 0)
        {
            sp10.vx = work->field_60C.vx - work->field_5FC.vx;
            sp10.vz = work->field_60C.vz - work->field_5FC.vz;
            SquareRoot0(sp10.vx * sp10.vx + sp10.vz * sp10.vz);
            s11g_hind_800D62BC(&work->field_60C, &work->field_5FC, 32);
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);
        }
        else
        {
            work->field_5C8 = 5;
            work->field_5E4 = GV_RandU(8) + 32;
            work->field_60C = work->field_4BC;
        }
        break;
    case 5:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 16);
        }
        else
        {
            work->field_64C = 0;

            if (work->field_5C4 == 2)
            {
                work->field_5C8 = 6;
                work->field_5E4 = 0;
            }
            else if (work->field_5CC == 1 && work->field_5D0 == 5)
            {
                work->field_5C4 = work->field_5CC;
                work->field_5C8 = work->field_5D0;
                work->field_5E4 = 5;
            }
            else
            {
                work->field_5C8 = 0;
                work->field_5C4 = work->field_5CC;
            }
        }
        break;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D96B0.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D9B80.s")

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800DA534.s")
void s11g_hind_800DA534(HindWork *work);

/*
TODO: This only matches when field_5F4 is volatile
void s11g_hind_800DA534(HindWork *work)
{
    int f5F4;

    s11g_hind_800D61F8(work);

    work->field_5C8 = 5;
    work->field_5E4 = 100;
    work->field_5F8 = GV_RandU(2);
    do {} while (0);
    work->field_5F4 = (work->field_5F4 + 2048) & 0xFFF;

    f5F4 = work->field_5F4;
    if (f5F4 > 256 && f5F4 < 1792)
    {
        if (f5F4 < 1024)
        {
            work->field_5F4 = 256;
        }
        else
        {
            work->field_5F4 = 1792;
        }
    }

    work->field_60C.vx = rcos(work->field_5F4) * 43;
    work->field_60C.vy = (work->field_60C.vy + 10000) / 2;
    work->field_60C.vz = rsin(work->field_5F4) * 43;
}
*/

void s11g_hind_800DA614(HindWork *work)
{
    int amount;

    s11g_hind_800D61F8(work);

    work->field_5C8 = 6;
    work->field_5E4 = GV_RandU(8) + 16;

    switch (GM_DifficultyFlag)
    {
    default:
    case DIFFICULTY_EASY:
    case DIFFICULTY_NORMAL:
        if ((work->field_5E8 < 10) && ((work->field_5E8 & 3) == 0))
        {
            if (GV_RandU(2) == 0)
            {
                work->field_5F8 = 1 - work->field_5F8;
            }
        }

        amount = 64;
        break;
    case DIFFICULTY_HARD:
        if ((work->field_5E8 == 5) || (work->field_5E8 == 10))
        {
            if (GV_RandU(2) == 0)
            {
                work->field_5F8 = 1 - work->field_5F8;
            }
        }

        amount = 70;
        break;
    case DIFFICULTY_EXTREME:
        if ((work->field_5E8 == 5) || (work->field_5E8 == 10))
        {
            if (GV_RandU(2) == 0)
            {
                work->field_5F8 = 1 - work->field_5F8;
            }
        }

        amount = 72;
        break;
    }

    if (work->field_5F8 != 0)
    {
        work->field_5F4 += amount;
    }
    else
    {
        work->field_5F4 -= amount;
    }

    work->field_60C.vx = rcos(work->field_5F4) * ((work->field_5E8 / 2) + 29);
    work->field_60C.vy = 32000;
    work->field_60C.vz = rsin(work->field_5F4) * ((work->field_5E8 / 2) + 29);
}

void s11g_hind_800DA7C4(HindWork *work)
{
    switch (work->field_5C8)
    {
    case 0:
        work->field_5C8 = 4;
        work->field_5E4 = 0;
        work->field_60C = work->field_4BC;
        work->field_60C.vy = 13000;
        /* fallthrough */
    case 4:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);
        }
        else
        {
            work->field_5C8 = 7;
            work->field_5E4 = 0;
        }
        break;
    case 5:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 128);
            work->field_5D4 = 1;
        }
        else if (((work->field_430 * 2) / 3) < work->field_434)
        {
            if (GV_DiffDirS(work->field_5F4, work->control.turn.vy) > 0)
            {
                work->field_5F8 = 1;
            }
            else
            {
                work->field_5F8 = 0;
            }

            work->field_5E8 = 24;
            s11g_hind_800DA614(work);
        }
        else
        {
            work->field_5C8 = 8;
            work->field_5E4 = GV_RandU(16) + 32;
            work->field_60C.vx = (rcos(work->field_5F4) * 30000) / 4096;
            work->field_60C.vy = 25000;
            work->field_60C.vz = (rsin(work->field_5F4) * 30000) / 4096;
            work->field_5F4 += (GV_RandS(126) + 700) * (GV_RandU(2) * 2 - 1);
            work->field_5F4 &= 0xFFF;
        }
        break;
    case 6:
        if (work->field_5E8 > 9)
        {
            work->field_62C = work->field_60C;
        }

        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 64);
        }
        else if (work->field_5E8 > 0)
        {
            s11g_hind_800DA614(work);
            work->field_5E8--;
        }
        else
        {
            work->field_5C8 = 7;
            work->field_5E4 = 10;
        }
        break;
    case 7:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);
        }
        else
        {
            work->field_8CC = 1;
            s11g_hind_800DA534(work);
        }
        break;
    case 8:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 128);
        }
        else
        {
            work->field_5C4 = 2;
            work->field_5C8 = 0;
        }
        break;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800DAAC8.s")
