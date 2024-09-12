#include "camera.h"

#include "common.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/object.h"
#include "Game/linkvarbuf.h"
#include "Bullet/blast.h"
#include "Okajima/spark.h"
#include "overlays/s00a/Enemy/enemy.h"
#include "SD/g_sound.h"
#include "strcode.h"

typedef struct CameraWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT_NO_ROTS field_9C;
    OBJECT_NO_ROTS field_C0;
    SVECTOR        field_E4;
    SVECTOR        field_EC;
    MATRIX         field_F4;
    int            field_114;
    int            field_118;
    int            field_11C;
    int            field_120;
    int            field_124;
    int            field_128;
    int            field_12C;
    int            field_130;
    SVECTOR        field_134_rots[1]; // TODO: are there 2 rots?
    int            field_13C;
    int            field_140;
    MATRIX         field_144;
    int            field_164;
    int            field_168;
    int            field_16C;
    int            field_170;
    int            field_174;
    int            field_178;
    int            field_17C;
    int            field_180;
    SVECTOR        field_184;
    int            field_18C;
    int            field_190;
    DG_PRIM       *field_194;
    DG_TEX        *field_198;
    short          field_19C;
    short          field_19E;
    SVECTOR        field_1A0;
    SVECTOR        field_1A8;
    int            field_1B0;
    int            field_1B4;
    short          field_1B8;
    short          field_1BA;
    short          field_1BC;
    short          field_1BE;
    SVECTOR        field_1C0;
    int            field_1C8;
    TARGET        *field_1CC;
    SVECTOR        field_1D0;
    int            field_1D8;
    int            field_1DC;
    int            field_1E0;
    int            field_1E4;
    int            field_1E8;
    unsigned int   field_1EC;
    int            field_1F0;
    short          field_1F4;
    short          field_1F6;
    int            field_1F8;
    SVECTOR        field_1FC[8];
    SVECTOR        field_23C[8];
    unsigned short field_27C;
    unsigned short field_27E;
    unsigned short field_280;
    unsigned short field_282;
    short          field_284;
    unsigned short field_286;
    short          field_288;
    short          field_28A;
    int            field_28C;
} CameraWork;

RECT    camera_rect_800C3B68 = {120, 120, 240, 240};
SVECTOR camera_svec1_800C3B70 = {300, 300, 300, 0};

extern char s01a_dword_800E44CC[];

extern TOPCOMMAND_STRUCT TOPCOMMAND_800E0F20;
extern int               COM_VibTime_800E0F68;

extern int              GM_PlayerMap_800ABA0C;
extern SVECTOR          DG_ZeroVector;
extern SVECTOR          GM_PlayerPosition_800ABA10;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern CONTROL         *GM_WhereList_800B56D0[96];

GV_ACT *NewSpark2_800CA714(MATRIX *world);
void    AN_Unknown_800D6EB0(SVECTOR *pos);

// duplicate of s03e_guncame_800C7118
void s01a_camera_800D4CFC(DG_PRIM *prim, DG_TEX *tex, int r, int g, int b)
{
    POLY_FT4 *poly;

    poly = &prim->packs[0]->poly_ft4;
    setRGB0(poly, r, g, b);

    poly = &prim->packs[1]->poly_ft4;
    setRGB0(poly, r, g, b);
}

int s01a_camera_800D4D28(char *opt, SVECTOR *svecs)
{
    int            count;
    unsigned char *param;

    for (count = 0; (param = GCL_GetParamResult()); svecs++, count++)
    {
        GCL_StrToSV(param, svecs);
    }
    return count;
}

void s01a_camera_800D4D7C(CONTROL *arg0, SVECTOR *arg1, SVECTOR *arg2)
{
    SVECTOR svec;
    int     vy;
    int     ratan2val;

    GV_SubVec3(arg1, &arg0->mov, &svec);
    arg2->vy = ratan2(svec.vx, svec.vz) & 0xFFF;
    vy = svec.vy;
    svec.vy = 0;
    ratan2val = ratan2(GV_VecLen3(&svec), vy) & 0xFFF;
    arg2->vx = ratan2val - 1024;
    if (arg2->vx < 0)
    {
        arg2->vx = ratan2val + 3072;
    }
}

int s01a_camera_800D4E08(CameraWork *work)
{
    SVECTOR  svec;
    CONTROL *ctrl;
    int      dir;
    int      dir2;

    if (GM_CurrentItemId == ITEM_STEALTH)
    {
        work->field_1DC = 0;
        return 0;
    }

    ctrl = &work->control;
    if (!(ctrl->map->index & GM_PlayerMap_800ABA0C))
    {
        work->field_1DC = 0;
        return 0;
    }

    s01a_camera_800D4D7C(ctrl, &GM_PlayerPosition_800ABA10, &svec);
    dir = GV_DiffDirAbs(svec.vy, ctrl->rot.vy);
    dir2 = GV_DiffDirAbs(svec.vx, ctrl->rot.vx);

    if (work->field_280 < dir2 || work->field_280 < dir ||
        GV_DiffVec3(&ctrl->mov, &GM_PlayerPosition_800ABA10) > work->field_27E)
    {
        work->field_1DC = 0;
        return 0;
    }
    if (work->field_1C8 != 0)
    {
        if (sub_80028454(ctrl->map->hzd, &ctrl->mov, &GM_PlayerPosition_800ABA10, 15, 2) != 0)
        {
            work->field_1DC = 0;
            return 0;
        }
    }
    if (TOPCOMMAND_800E0F20.mode != 1)
    {
        if (GM_PlayerStatus_800ABA50 & PLAYER_CB_BOX)
        {
            if (work->field_1DC == 0)
            {
                work->field_1D0 = GM_PlayerPosition_800ABA10;
                work->field_1D8 = GM_WhereList_800B56D0[0]->rot.vy;
                work->field_1DC = 1;
                return 0;
            }
            if (GV_DiffVec3(&work->field_1D0, &GM_PlayerPosition_800ABA10) < 50)
            {
                if (work->field_1D8 == GM_WhereList_800B56D0[0]->rot.vy)
                {
                    work->field_1DC = 1;
                    return 0;
                }
            }
        }
    }
    work->field_1DC = 1;
    return 1;
}

void s01a_camera_800D4FE8(SVECTOR *arg0, SVECTOR *arg1, int arg2)
{
    int dir;

    if (arg2 < 8)
    {
        arg1->vx = arg0->vx;
    }
    else if (arg1->vx > 768)
    {
        arg1->vx = 768;
    }

    dir = GV_DiffDirS(arg0->vy, arg1->vy);
    if (arg2 < dir)
    {
        arg1->vy = (arg0->vy + arg2) & 0xFFF;
    }
    else if (dir < -arg2)
    {
        arg1->vy = (arg0->vy - arg2) & 0xFFF;
    }
}

void s01a_camera_800D509C(CameraWork *work)
{
    s01a_camera_800D4D7C(&work->control, &GM_PlayerPosition_800ABA10, &work->control.turn);
    s01a_camera_800D4FE8(&work->field_1C0, &work->control.turn, work->field_282);
}

void s01a_camera_800D50EC(CameraWork *work)
{
    s01a_camera_800D4D7C(&work->control, &GM_PlayerPosition_800ABA10, &work->control.turn);
    s01a_camera_800D4FE8(&work->field_1C0, &work->control.turn, work->field_282);
    work->control.rot = work->control.turn;
}

int s01a_camera_800D515C(CameraWork *work)
{
    int field_1EC;

    field_1EC = work->field_1EC;
    if (field_1EC == 0)
    {
        GM_SeSet(&work->control.mov, SE_CAMERA_LENS);
        s01a_camera_800D4CFC(work->field_194, work->field_198, 0xFF, 0, 0);
    }
    s01a_camera_800D509C(work);
    if (field_1EC == 15)
    {
        s00a_command_800CEC40(&work->control.mov, 32);
        AN_Unknown_800CA1EC(&work->field_9C.objs[1].world, 0);
        COM_VibTime_800E0F68 = 10;
        s01a_camera_800D50EC(work);
    }
    if (field_1EC == 35)
    {
        ENE_SetTopCommAL_800CEAE8(0xFF);
        ENE_SetGopointLast_800CEB00();
        return 1;
    }

    work->field_1EC++;
    return 0;
}

void s01a_camera_800D522C(CameraWork *work)
{
    if (mts_get_tick_count() - work->field_286 >= 13)
    {
        if (work->field_28A != 0)
        {
            GM_SeSet(&work->control.mov, SE_CAMERA_SCAN);
        }
        work->field_286 = mts_get_tick_count();
    }
}

int s01a_camera_800D528C(CameraWork *work)
{
    SVECTOR *turn;

    if (work->field_1EC > 60)
    {
        if (!(work->field_1EC & 3))
        {
            s01a_camera_800D522C(work);
        }
        if (work->field_282 >= 8)
        {
            turn = &work->control.turn;
            turn->vy = (turn->vy + 8) & 0xFFF;
            if (GV_DiffDirAbs(work->field_1C0.vy, turn->vy) >= work->field_282)
            {
                return 1;
            }
        }
        else
        {
            return 0;
        }
    }
    work->field_1EC++;
    return 0;
}

// Same as s01a_camera_800D528C, but with - 8 instead of + 8
int s01a_camera_800D5338(CameraWork *work)
{
    SVECTOR *turn;

    if (work->field_1EC > 60)
    {
        if (!(work->field_1EC & 3))
        {
            s01a_camera_800D522C(work);
        }
        if (work->field_282 >= 8)
        {
            turn = &work->control.turn;
            turn->vy = (turn->vy - 8) & 0xFFF;
            if (GV_DiffDirAbs(work->field_1C0.vy, turn->vy) >= work->field_282)
            {
                return 1;
            }
        }
        else
        {
            return 0;
        }
    }
    work->field_1EC++;
    return 0;
}

void s01a_camera_800D53E4(CameraWork *work)
{
    CONTROL *ctrl;
    SVECTOR *turn;
    int      dir1, dir2;
    int      temp_v0;

    ctrl = &work->control;
    if (!(work->field_1EC & 0x3F))
    {
        temp_v0 = GV_RandU(16);
        turn = &work->control.turn;
        work->control.field_54 = 48;
        work->field_1EC += temp_v0;
        temp_v0 = work->field_1C0.vy - (1024 - GV_RandU(2048));
        turn->vy = temp_v0 & 0xFFF;
        turn->vx = GV_RandU(768);
        s01a_camera_800D4FE8(&work->field_1C0, turn, work->field_282);
        work->field_1F4 = ctrl->rot.vx;
        work->field_1F6 = ctrl->rot.vy;
    }
    dir1 = GV_DiffDirAbs(work->field_1F4, ctrl->rot.vx);
    dir2 = GV_DiffDirAbs(work->field_1F6, ctrl->rot.vy);
    if ((dir1 > 16 || dir2 > 16) && work->field_28A != 0)
    {
        GM_SeSet(&ctrl->mov, SE_CAMERA_SCAN);
    }
    work->field_1F4 = ctrl->rot.vx;
    work->field_1F6 = ctrl->rot.vy;
    work->field_1EC++;
}

// Copy of s01a_camera_800D53E4, but with different GM_SeSet
void s01a_camera_800D5504(CameraWork *work)
{
    CONTROL *ctrl;
    SVECTOR *turn;
    int      dir1, dir2;
    int      temp_v0;

    ctrl = &work->control;
    if (!(work->field_1EC & 0x3F))
    {
        temp_v0 = GV_RandU(16);
        turn = &work->control.turn;
        work->control.field_54 = 48;
        work->field_1EC += temp_v0;
        temp_v0 = work->field_1C0.vy - (1024 - GV_RandU(2048));
        turn->vy = temp_v0 & 0xFFF;
        turn->vx = GV_RandU(768);
        s01a_camera_800D4FE8(&work->field_1C0, turn, work->field_282);
        work->field_1F4 = ctrl->rot.vx;
        work->field_1F6 = ctrl->rot.vy;
    }
    dir1 = GV_DiffDirAbs(work->field_1F4, ctrl->rot.vx);
    dir2 = GV_DiffDirAbs(work->field_1F6, ctrl->rot.vy);
    if ((dir1 > 16 || dir2 > 16) && work->field_28A != 0)
    {
        GM_SeSet(&ctrl->mov, SE_CAMERA_JAMMED);
    }
    work->field_1F4 = ctrl->rot.vx;
    work->field_1F6 = ctrl->rot.vy;
    work->field_1EC++;
}

int s01a_camera_800D5624(CameraWork *work)
{
    CONTROL *ctrl;
    SVECTOR *turn;
    SVECTOR *svec1;
    int      dir, dir2, dir3;

    svec1 = &work->field_1C0;
    turn = &work->control.turn;
    ctrl = &work->control;

    dir = GV_DiffDirS(svec1->vy, turn->vy);
    if (dir < -10)
    {
        turn->vy += 8;
    }
    else if (dir < 10)
    {
        turn->vy = svec1->vy;
    }
    else
    {
        turn->vy -= 8;
    }
    turn->vy &= 0xFFF;

    dir = GV_DiffDirS(svec1->vx, turn->vx);
    if (dir < -10)
    {
        turn->vx += 8;
    }
    else if (dir < 10)
    {
        turn->vx = svec1->vx;
    }
    else
    {
        turn->vx -= 8;
    }
    turn->vx &= 0xFFF;

    if (turn->vx == svec1->vx && turn->vy == svec1->vy && work->field_1EC > 96)
    {
        return 1;
    }

    dir2 = GV_DiffDirAbs(work->field_1F4, ctrl->rot.vx);
    dir3 = GV_DiffDirAbs(work->field_1F6, ctrl->rot.vy);
    if ((dir2 > 16 || dir3 > 16) && work->field_28A != 0)
    {
        GM_SeSet(&work->control.mov, SE_CAMERA_SCAN);
    }

    work->field_1F4 = ctrl->rot.vx;
    work->field_1F6 = ctrl->rot.vy;
    work->field_1EC++;
    return 0;
}

void s01a_camera_800D57CC(CameraWork *work)
{
    switch (work->field_1E8)
    {
    case 1:
        if (s01a_camera_800D528C(work))
        {
            work->field_1E8 = 2;
            work->field_1EC = 0;
        }
        if (s01a_camera_800D4E08(work))
        {
            work->field_1E8 = 5;
            work->field_1EC = 0;
        }
        break;
    case 2:
        if (s01a_camera_800D5338(work))
        {
            work->field_1E8 = 1;
            work->field_1EC = 0;
        }
        if (s01a_camera_800D4E08(work))
        {
            work->field_1E8 = 5;
            work->field_1EC = 0;
        }
        break;
    case 3:
        work->field_1E8 = 1;
        work->field_1EC = 0;
        break;
    case 5:
        if (s01a_camera_800D515C(work))
        {
            work->field_1E0 = 1;
            work->field_1E8 = 4;
            work->field_1EC = 0;
            return;
        }
        break;
    case 7:
        if (s01a_camera_800D5624(work))
        {
            if (work->field_27C == 2)
            {
                work->field_1E8 = 3;
            }
            else
            {
                work->field_1E8 = 1;
            }
            work->field_1EC = 0;
            s01a_camera_800D4CFC(work->field_194, work->field_198, 0, 0xFF, 0);
        }
        break;
    }

    if (TOPCOMMAND_800E0F20.mode == 1)
    {
        work->field_1E0 = TOPCOMMAND_800E0F20.mode;
        work->field_1E8 = 0;
        work->field_1EC = 0;
        s01a_camera_800D4CFC(work->field_194, work->field_198, 0xFF, 0, 0);
    }
    if (GM_GameStatus & STATE_CHAFF)
    {
        work->field_1E0 = 3;
        work->field_1E8 = 6;
        work->field_1EC = 0;
        s01a_camera_800D4CFC(work->field_194, work->field_198, 0xFF, 0xFF, 0);
    }
}

void s01a_camera_800D5970(CameraWork *work)
{
    if (work->field_1E8 != 0)
    {
        if (work->field_1E8 == 4)
        {
            s01a_camera_800D509C(work);
            ENE_SetTopCommAL_800CEAE8(0xFF);
            ENE_SetGopointLast_800CEB00();
            if (!s01a_camera_800D4E08(work))
            {
                work->field_1E8 = 0;
            }
        }
    }
    else if (s01a_camera_800D4E08(work))
    {
        work->field_1E8 = 4;
    }
    if (TOPCOMMAND_800E0F20.mode != 1)
    {
        work->field_1E0 = 2;
        work->field_1E8 = 6;
        work->field_1EC = 0;
        s01a_camera_800D4CFC(work->field_194, work->field_198, 0xFF, 0xFF, 0);
    }
    if (GM_GameStatus & STATE_CHAFF)
    {
        work->field_1E0 = 3;
        work->field_1E8 = 6;
        work->field_1EC = 0;
        s01a_camera_800D4CFC(work->field_194, work->field_198, 0xFF, 0xFF, 0);
    }
}

void s01a_camera_800D5A68(CameraWork *work)
{
    if (work->field_1E8 == 6)
    {
        s01a_camera_800D53E4(work);
        if (TOPCOMMAND_800E0F20.mode == 0)
        {
            work->field_1E0 = 0;
            work->field_1E8 = 7;
            work->field_1EC = 0;
        }
    }
    if (s01a_camera_800D4E08(work))
    {
        ENE_SetTopCommAL_800CEAE8(0xFF);
        ENE_SetGopointLast_800CEB00();
        COM_VibTime_800E0F68 = 0xA;
        s00a_command_800CEC40(&work->control.mov, 0x20);
        AN_Unknown_800CA1EC(&work->field_9C.objs[1].world, 0);
        s01a_camera_800D50EC(work);
        work->field_1E0 = 1;
        work->field_1E8 = 4;
        work->field_1EC = 0;
        s01a_camera_800D4CFC(work->field_194, work->field_198, 0xFF, 0, 0);
    }
    else if (TOPCOMMAND_800E0F20.mode == 1)
    {
        work->field_1E0 = TOPCOMMAND_800E0F20.mode;
        work->field_1E8 = 0;
        work->field_1EC = 0;
        s01a_camera_800D4CFC(work->field_194, work->field_198, 0xFF, 0, 0);
    }
    if (GM_GameStatus & STATE_CHAFF)
    {
        work->field_1E0 = 3;
        work->field_1E8 = 6;
        work->field_1EC = 0;
        s01a_camera_800D4CFC(work->field_194, work->field_198, 0xFF, 0xFF, 0);
    }
}

void s01a_camera_800D5B9C(CameraWork *work)
{
    int field_1E8;

    field_1E8 = work->field_1E8;
    if (field_1E8 == 6)
    {
        if (GM_GameStatus & STATE_CHAFF)
        {
            s01a_camera_800D5504(work);
            return;
        }
        switch (TOPCOMMAND_800E0F20.mode)
        {
        case 0:
            work->field_1E0 = 0;
            work->field_1E8 = 7;
            work->field_1EC = 0;
            break;
        case 1:
            work->field_1E0 = TOPCOMMAND_800E0F20.mode;
            work->field_1E8 = 0;
            work->field_1EC = 0;
            s01a_camera_800D4CFC(work->field_194, work->field_198, 0xFF, 0, 0);
            break;
        case 2:
            work->field_1E0 = TOPCOMMAND_800E0F20.mode;
            work->field_1E8 = field_1E8;
            work->field_1EC = 0;
            s01a_camera_800D4CFC(work->field_194, work->field_198, 0xFF, 0xFF, 0);
            break;
        }
    }
}

void s01a_camera_800D5C7C(CameraWork *work)
{
    switch (work->field_1E0)
    {
    case 0:
        s01a_camera_800D57CC(work);
        break;
    case 1:
        s01a_camera_800D5970(work);
        break;
    case 2:
        s01a_camera_800D5A68(work);
        break;
    case 3:
        s01a_camera_800D5B9C(work);
        break;
    }
}

void s01a_camera_800D5D10(CameraWork *work)
{
    work->control.radar_cone.dir = work->control.rot.vy;
}

void s01a_camera_800D5D1C(CameraWork *work)
{
    MATRIX  mat;
    SVECTOR svec;
    int     i;

    if (++work->field_1F0 >= 10)
    {
        svec.vx = GV_RandU(1024);
        svec.vy = GV_RandU(2048);
        svec.vz = 0;

        DG_SetPos2(&work->control.mov, &svec);
        ReadRotMatrix(&mat);

        if (!(work->field_1F0 & 0x7))
        {
            NewSpark_80074564(&mat, GV_RandU(2));
        }
        if (work->field_1F0 == work->field_1F0 / 12 * 12)
        {
            NewSpark2_800CA714(&mat);
        }
    }

    work->field_9C.objs->flag |= 0x80;
    work->field_C0.objs->flag |= 0x80;
    s01a_camera_800D4CFC(work->field_194, work->field_198, 0, 0, 0);

    for (i = 0; i < 8; i++)
    {
        work->field_1FC[i].vy -= 15;
        work->field_23C[i].vx += work->field_1FC[i].vx;
        work->field_23C[i].vy += work->field_1FC[i].vy;
        work->field_23C[i].vz += work->field_1FC[i].vz;
        AN_Unknown_800D6EB0(&work->field_23C[i]);
    }
    if (work->field_1F0 >= 40)
    {
        GV_DestroyActor(&work->actor);
    }
}

int s01a_camera_800D5EC0(CameraWork *work)
{
    GV_MSG *msg;
    int     type;

    if (GV_ReceiveMessage(work->control.name, &msg) <= 0)
    {
        return -1;
    }

    // They just randomly decided not to use a switch here...
    type = msg->message[0];
    if (type == HASH_LEAVE)
    {
        work->field_284 = 0;
        work->control.radar_atr &= ~RADAR_SIGHT;
    }
    else if (type == HASH_ENTER)
    {
        do
        {
            work->field_284 = 1;
            work->control.radar_atr |= RADAR_SIGHT;
        } while (0);
    }
    else if (type == HASH_SOUND_ON)
    {
        work->field_28A = 1;
    }
    else if (type == HASH_SOUND_OFF)
    {
        work->field_28A = 0;
    }
    return type;
}

void CameraAct_800D5F64(CameraWork *work)
{
    MATRIX   mat;
    SVECTOR  svec1;
    SVECTOR  svec2;
    CONTROL *ctrl;
    TARGET  *target;
    int      i;

    s01a_camera_800D5EC0(work);
    ctrl = &work->control;
    if (work->field_1F0 == 0)
    {
        GM_ActControl(ctrl);
        GM_ActObject2((OBJECT *)&work->field_9C);
        DG_PutPrim(&work->field_194->world);
        if (work->field_9C.objs->bound_mode != 0)
        {
            DG_GetLightMatrix2(&ctrl->mov, &work->field_144);
        }

        target = work->field_1CC;
        GM_MoveTarget(target, &ctrl->mov);
        if (target->damaged & TARGET_POWER)
        {
            if (target->a_mode != 2)
            {
                target->field_28 = 0;
                target->damaged = 0;
            }
            else
            {
                if (work->field_28C >= 0)
                {
                    GCL_ExecProc(work->field_28C, NULL);
                }
                work->field_1F0 = 1;
                AN_Blast_Mini_8006E2A8(&ctrl->mov);
                for (i = 0; i < 8; i++)
                {
                    svec1.vz = 0;
                    svec2.vx = GV_RandS(128);
                    svec2.vy = GV_RandU(256) + 32;
                    svec2.vz = 0;
                    svec1.vx = GV_RandU(256) + 64;

                    svec1.vy = work->control.rot.vy + GV_RandS(1024);
                    RotMatrixYXZ_gte(&svec1, &mat);
                    ApplyMatrixSV(&mat, &svec2, &work->field_1FC[i]);
                    work->field_23C[i] = work->control.mov;
                }
            }
        }
    }
    else
    {
        s01a_camera_800D5D1C(work);
    }
    if (work->field_284 != 0)
    {
        s01a_camera_800D5C7C(work);
        s01a_camera_800D5D10(work);
        DG_VisiblePrim(work->field_194);
        work->control.radar_atr |= RADAR_SIGHT;
    }
    else
    {
        DG_InvisiblePrim(work->field_194);
        work->control.radar_atr &= ~RADAR_SIGHT;
    }
}

void s01a_camera_800D6174(CameraWork *work)
{
    CONTROL    *ctrl;
    RADAR_CONE *cone;

    ctrl = &work->control;
    ctrl->radar_atr |= RADAR_UNK3;

    cone = &work->control.radar_cone;
    cone->dir = 0;
    cone->len = work->field_27E;
    cone->ang = work->field_280 * 2;
    cone->_pad = 0;
}

int s01a_camera_800D61AC(CameraWork *work, int arg1, int arg2)
{
    char *opt;

    opt = GCL_GetOption('m');
    if (opt)
    {
        // field_27C is set to 0 after the if...
        work->field_27C = GCL_StrToInt(opt);
    }
    else
    {
        work->field_27C = 0;
    }
    work->field_27C = 0; // lol

    opt = GCL_GetOption('l');
    if (opt)
    {
        work->field_27E = GCL_StrToInt(opt);
    }
    else
    {
        work->field_27E = 0;
    }

    opt = GCL_GetOption('w');
    if (opt)
    {
        work->field_280 = GCL_StrToInt(opt);
        if (work->field_280 > 512)
        {
            work->field_280 = 512;
        }
    }
    else
    {
        work->field_280 = 0;
    }

    work->field_1C8 = 0;
    if (GCL_GetOption('h'))
    {
        work->field_1C8 = 1;
    }

    opt = GCL_GetOption('x');
    if (opt)
    {
        work->field_282 = GCL_StrToInt(opt);
        if (work->field_282 > 1024)
        {
            work->field_282 = 1024;
        }
    }
    else
    {
        work->field_282 = 0;
    }

    work->control.mov.vy += 25;
    work->control.mov.vz += 450;

    work->field_EC = work->control.rot;
    work->field_1C0 = work->field_EC;
    if (work->field_1C0.vx > 512)
    {
        work->field_1C0.vx = 512;
    }
    work->field_EC.vx = 0;
    s01a_camera_800D4CFC(work->field_194, work->field_198, 0, 0xFF, 0);
    DG_SetPos2(&work->control.mov, &work->field_EC);
    DG_MovePos(&work->field_E4);
    GM_ActObject2((OBJECT *)&work->field_C0);
    opt = GCL_GetOption('r');
    if (opt)
    {
        work->field_19C = s01a_camera_800D4D28(opt, &work->field_1A0);
        work->field_19E = 0;
    }
    else
    {
        work->field_19C = 0;
    }
    if (work->field_27C == 2)
    {
        work->field_1A8 = work->field_1A0;
    }
    if (GCL_GetOption('e'))
    {
        work->field_28C = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->field_28C = -1;
    }
    s01a_camera_800D6174(work);
    work->field_1E0 = 0;
    if (work->field_27C == 2)
    {
        work->field_1E8 = 3;
    }
    else
    {
        work->field_1E8 = 1;
    }
    work->field_1EC = 0;
    work->field_1F0 = 0;
    return 0;
}

int s01a_camera_800D640C(CameraWork *work)
{
    OBJECT_NO_ROTS *obj;

    obj = &work->field_C0;
    GM_InitObjectNoRots(obj, GV_StrCode("cam_arm"), 0x36D, 0);
    GM_ConfigObjectLight((OBJECT *)obj, &work->field_F4);
    DG_GetLightMatrix2(&work->control.mov, &work->field_F4);
    work->field_E4.vy = -25;
    work->field_E4.vx = 0;
    work->field_E4.vz = -450;

    return 0;
}

// duplicate of s03e_guncame_800C8E04
void s01a_camera_800D648C(POLY_FT4 *poly, DG_TEX *tex, int col)
{
    char          height;
    char          width;
    unsigned char x_offset;
    unsigned char y_offset;

    setPolyFT4(poly);
    setRGB0(poly, col, col, col);
    setSemiTrans(poly, 1);

    x_offset = tex->off_x;
    width = x_offset + tex->w;

    y_offset = tex->off_y;
    height = y_offset + tex->h;

    poly->u0 = x_offset;
    poly->v0 = y_offset;
    poly->u1 = width;
    poly->v1 = y_offset;
    poly->u2 = x_offset;
    poly->v2 = height;
    poly->u3 = width;
    poly->v3 = height;

    poly->tpage = tex->tpage;
    poly->clut = (unsigned short)tex->clut;
}

int s01a_camera_800D6504(CameraWork *work)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->field_184.vx = 50;
    work->field_184.vy = 300;
    work->field_184.vz = 350;
    prim = DG_GetPrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 1, 0, &work->field_184, &camera_rect_800C3B68);
    work->field_194 = prim;
    if (prim != NULL)
    {
        prim->field_2E_k500 = 500;
        work->field_198 = tex = DG_GetTexture(GV_StrCode("camera_l"));
        if (tex != NULL)
        {
            s01a_camera_800D648C(&prim->packs[0]->poly_ft4, tex, 0x80);
            s01a_camera_800D648C(&prim->packs[1]->poly_ft4, tex, 0x64);
            return 0;
        }
    }
    return -1;
}

int CameraGetResources_800D65EC(CameraWork *work, int arg1, int arg2)
{
    TARGET         *target, *target2;
    int             type;
    char           *opt;
    CONTROL        *ctrl;
    OBJECT_NO_ROTS *obj;

    ctrl = &work->control;
    if (GM_InitControl(ctrl, arg1, arg2) < 0)
    {
        return -1;
    }

    GM_ConfigControlString(ctrl, GCL_GetOption('p'), GCL_GetOption('d'));
    GM_ConfigControlAttribute(ctrl, 0x49);
    GM_ConfigControlHazard(ctrl, -1, -2, -1);

    work->control.step = DG_ZeroVector;

    type = 0x41;
    obj = &work->field_9C;

    opt = GCL_GetOption('n');
    if (opt)
    {
        type = GCL_StrToInt(opt);
    }

    // Dead code (if with identical cases):
    if (type == 0x41)
    {
        opt = "s_camera";
    }
    else
    {
        opt = "s_camera";
    }
    GM_InitObjectNoRots(obj, GV_StrCode(opt), 0x32D, 0);

    obj->objs->rots = work->field_134_rots;
    GM_ConfigObjectLight((OBJECT *)obj, &work->field_144);
    GM_ConfigObjectStep((OBJECT *)obj, &work->control.step);
    DG_GetLightMatrix2(&ctrl->mov, &work->field_144);

    work->field_1BA = 175;
    work->field_1B8 = 0;
    work->field_1BC = 600;

    s01a_camera_800D640C(work);
    s01a_camera_800D6504(work);

    target = GM_AllocTarget();
    work->field_1CC = target2 = target;
    if (target)
    {
        GM_SetTarget(target2, 20, 2, &camera_svec1_800C3B70);
        work->field_284 = 1;
        work->field_286 = 0;
        work->field_288 = 1;
        work->field_28A = 1;
        return 0;
    }

    return -1;
}

void CameraDie_800D678C(CameraWork *work)
{
    DG_PRIM *prim;

    GM_FreeControl(&work->control);
    GM_FreeObject((OBJECT *)&work->field_9C);
    GM_FreeObject((OBJECT *)&work->field_C0);

    prim = work->field_194;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
    GM_FreeTarget(work->field_1CC);
}

GV_ACT *NewCamera_800D67F8(int name, int where, int argc, char **argv)
{
    CameraWork *work;

    work = (CameraWork *)GV_NewActor(4, sizeof(CameraWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)CameraAct_800D5F64,
                         (TActorFunction)CameraDie_800D678C, "camera.c");
        if (CameraGetResources_800D65EC(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        s01a_camera_800D61AC(work, name, where);
    }
    return &work->actor;
}
