#include "rmissile.h"
#include "blast.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "Takabe/prim.h"
#include "Game/game.h"
#include "Game/camera.h"
#include "Game/object.h"
#include "Game/map.h"
#include "Game/linkvarbuf.h"
#include "Menu/menuman.h"
#include "Thing/sgtrect3.h"
#include "Thing/sight.h"
#include "SD/g_sound.h"
#include "strcode.h"

extern GV_PAD           GV_PadData_800B05C0[4];
extern OBJECT *         GM_PlayerBody_800ABA20;
extern SVECTOR          GM_PlayerPosition_800ABA10;
extern int              GV_Clock_800AB920;
extern BLAST_DATA       blast_data_8009F4B8[8];
extern int              GM_CurrentMap_800AB9B0;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern TARGET          *target_800BDF00;
extern int              dword_8009F604;
extern int              dword_800BDEF8[];
extern CONTROL         *GM_PlayerControl_800AB9F4;
extern int              GM_CameraTrackSave;
extern SVECTOR          GM_CameraRotateSave;
extern int              GM_event_camera_flag_800ABA9C;
extern GM_Camera        GM_Camera_800B77E8;
extern UnkCameraStruct  gUnkCameraStruct_800B77B8;
extern CAMERA           GM_CameraList_800B7718[8];

/*---------------------------------------------------------------------------*/
// RC Missile (Nikita)

typedef struct RMissileWork
{
    GV_ACT          actor;
    CONTROL         control;
    OBJECT_NO_ROTS  object;
    MATRIX          light[2];
    SVECTOR         field_100_svector;
    SVECTOR         field_108_svector;
    char            field_110;
    char            field_111;
    char            field_112;
    char            field_113;
    char            field_114;
    char            field_115;
    char            field_116;
    char            field_117;
    short           field_118;
    short           field_11A;
    int             field_11C;
    TARGET          target;
    short           field_168;
    short           field_16A;
    SVECTOR         field_16C_svector;
    POLY_F4        *field_174_polys_2Array[2];
    GM_Camera       field_17C_camera;
    UnkCameraStruct field_1F8;
    CAMERA          field_228_camera[8];
    int             field_2C8;
    SVECTOR         field_2CC_svector;
    int             field_2D4;
    DG_PRIM        *field_2D8_prim;
    DG_TEX         *field_2DC_tex;
    char            field_2E0_pad[4];
    SVECTOR         field_2E4_svector_8Array[8];
    int             field_324;
} RMissileWork;

#define EXEC_LEVEL 6

int dword_8009F46C = 0; // FIXME: this is referenced as an array in several places
int dword_8009F470 = 0;
int dword_8009F474 = 0;
SVECTOR svector_8009F478 = {0, 0, 0, 0};
int dword_8009F480 = 0;
short Nik_Blast = 0;
SVECTOR svector_8009F488 = {100, 100, 100, 0};

/*---------------------------------------------------------------------------*/

STATIC void rmissile_loader_helper4_8006B800(RMissileWork *work)
{
    GV_CopyMemory(&GM_Camera_800B77E8,        &work->field_17C_camera,  sizeof(work->field_17C_camera));
    GV_CopyMemory(&gUnkCameraStruct_800B77B8, &work->field_1F8,         sizeof(work->field_1F8));
    GV_CopyMemory(GM_CameraList_800B7718,     &work->field_228_camera,  sizeof(work->field_228_camera));
    GV_CopyMemory(&GM_CameraRotateSave,       &work->field_2CC_svector, sizeof(work->field_2CC_svector));

    work->field_2C8 = GM_CameraTrackSave;
    work->field_2D4 = GM_event_camera_flag_800ABA9C;
}

STATIC void rmissile_8006B888(RMissileWork *work)
{
    GV_CopyMemory(&work->field_17C_camera,  &GM_Camera_800B77E8,        sizeof(work->field_17C_camera));
    GV_CopyMemory(&work->field_1F8,         &gUnkCameraStruct_800B77B8, sizeof(work->field_1F8));
    GV_CopyMemory(&work->field_228_camera,  &GM_CameraList_800B7718,    sizeof(work->field_228_camera));
    GV_CopyMemory(&work->field_2CC_svector, &GM_CameraRotateSave,       sizeof(work->field_2CC_svector));

    GM_CameraTrackSave = work->field_2C8;
    GM_event_camera_flag_800ABA9C = work->field_2D4;

    sub_800309B4(2, 30);
    GM_CameraEventReset_800309A8();
}

STATIC void rmissile_8006B924(RMissileWork *work)
{
    CONTROL *ctrl;

    ctrl = &work->control;
    ctrl->skip_flag |= CTRL_SKIP_TRAP;

    rmissile_8006B888(work);
    GM_GameStatus &= ~GAME_FLAG_BIT_07;
    HZD_8002A258(ctrl->map->hzd, &ctrl->event);

    ctrl = GM_PlayerControl_800AB9F4;

    if (ctrl)
    {
        HZD_ReExecEvent(ctrl->map->hzd, &ctrl->event, 0x102);
    }
}

STATIC void rmissile_act_helper_helper_8006B9B0(RMissileWork *work)
{
    Nik_Blast = 1;

    if (dword_8009F604 != SGT_NIKITA)
    {
        NewSight_80071CDC(SGT_NIKITA, SGT_NIKITA, &Nik_Blast, 1, 0);
    }

    GM_Camera_800B77E8.first_person = 1;

    if (work->field_113 == 0)
    {
        work->field_113 = 1;
        dword_800BDEF8[0] = 0x5A875D;
        dword_800BDEF8[1] = 0xC1A80;
        NewSgtRect3(&Nik_Blast, 1, dword_800BDEF8, 0);
        GM_SeSet2(0, 0x3F, SE_ITEM_OPENWINDOW);
    }
}

STATIC void rmissile_act_helper_helper_8006BA70(RMissileWork *work)
{
    if (!target_800BDF00)
    {
        work->field_168 = 0;
        return;
    }

    work->field_168++;

    if (work->field_168 <= 16)
    {
        return;

    }

    if (work->field_168 == 32)
    {
        work->field_168 = 0;
    }

    if (!(GM_PlayerStatus_800ABA50 & PLAYER_UNK4000000))
    {
        MENU_Color(158, 184, 138);
        MENU_Locate(116, 98, 0);
        MENU_Printf("ENEMY\n");
        menu_Text_Init_80038B98();
    }
}

STATIC void rmissile_act_helper_helper_8006BB10(RMissileWork *work)
{
    int var_a1;
    unsigned int *ot;
    POLY_F4 *poly;
    CONTROL ctrl;

    var_a1 = ((1000 - work->field_118) * 60) / 1000;

    ot = (unsigned int *)DG_ChanlOTag(1);
    poly = work->field_174_polys_2Array[GV_Clock_800AB920];

    if (var_a1 > 60)
    {
        var_a1 = 60;
    }

    poly->x3 = var_a1 + 31;
    poly->x1 = var_a1 + 31;

    if (GM_PlayerStatus_800ABA50 & PLAYER_UNK4000000)
    {
        return;
    }

    if (var_a1 < 15)
    {
        setRGB0(poly, 212, 78, 78);

        if (!(work->field_118 % 15))
        {
            GM_SeSet2(0, 63, SE_SIGNAL02);
        }
    }

    addPrim(ot, poly);
    ctrl = work->control;

    MENU_Locate(8, 136, 0);
    MENU_Printf("%d", ctrl.mov.vx);

    MENU_Locate(8, 144, 0);
    MENU_Printf("%d", ctrl.mov.vy);

    MENU_Locate(8, 152, 0);
    MENU_Printf("%d", ctrl.mov.vz);

    menu_Text_Init_80038B98();
}

STATIC void rmissile_act_helper_8006BD24(RMissileWork *work, int pad_status)
{
    if (work->field_112 || work->field_117 || work->field_110)
    {
        return;
    }

    if (pad_status & PAD_TRIANGLE)
    {
        rmissile_act_helper_helper_8006B9B0(work);

        gUnkCameraStruct_800B77B8.rotate2.vx = 0;
        gUnkCameraStruct_800B77B8.rotate2.vy = work->control.rot.vy;
        gUnkCameraStruct_800B77B8.rotate2.vz = 0;

        DG_InvisibleObjs(work->object.objs);

        work->field_11C = -2;

        if (work->field_114 < 16)
        {
            work->field_114++;
            return;
        }

        rmissile_act_helper_helper_8006BB10(work);
        rmissile_act_helper_helper_8006BA70(work);
        return;
    }

    if (work->field_113 != 0)
    {
        work->field_115 = 5;
    }

    work->field_114 = 0;
    work->field_113 = 0;

    GM_Camera_800B77E8.first_person = 0;
    Nik_Blast = 0;

    if (work->field_115)
    {
        work->field_115--;

        if (!work->field_115)
        {
            DG_VisibleObjs(work->object.objs);
        }
    }
}

STATIC void rmissile_act_helper_8006BE50(RMissileWork *work, int arg1)
{
    if (GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF)
    {
        return;
    }

    if (arg1 >= 0 && work->control.turn.vy != arg1)
    {
        work->field_111 = 30;
        work->control.turn.vy = arg1;
    }
}

STATIC void rmissile_act_helper_8006BE90(RMissileWork *work, int arg1)
{
    if (GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF)
    {
        return;
    }

    if (arg1 & 0x8000)
    {
        work->field_111 = 30;
        work->control.turn.vy += 64;
        work->control.turn.vy &= 0xFFF;
    }

    if (arg1 & 0x2000)
    {
        work->field_111 = 30;
        work->control.turn.vy -= 64;
        work->control.turn.vy &= 0xFFF;
    }
}

STATIC void rmissile_act_helper_8006BEEC(RMissileWork *work)
{
    if (work->field_117)
    {
        return;
    }

    if (GM_PlayerStatus_800ABA50 & 0x2100 || dword_8009F474 == 1 || GM_GameStatus & (STATE_CHAFF | STATE_JAMMING))
    {
        work->field_117 = 1;
        work->field_16A = 15;
        work->field_16C_svector = work->control.mov;
        work->field_113 = 0;

        GM_Camera_800B77E8.first_person = 0;
        Nik_Blast = 0;

        if (!work->field_112)
        {
            DG_VisibleObjs(work->object.objs);
        }

        dword_8009F474 = 0;
        rmissile_8006B924(work);
    }
}

STATIC void rmissile_act_helper_8006BFD4(RMissileWork *work)
{
    if (work->field_111)
    {
        work->field_111--;

        if (!work->field_111)
        {
            GM_SeSet2(0, 63, SE_MISSILE_BOOST);
            work->field_116 = 12;
        }

        work->field_11A = 50;

        if (!work->field_112)
        {
            work->field_11C = 0;
        }
    }
    else
    {
        if (work->field_116)
        {
            work->field_116--;
            gUnkCameraStruct_800B77B8.eye.vy += GV_RandS(512) * work->field_116 / 32;
        }

        work->field_11A = 200;

        if (!work->field_112)
        {
            work->field_11C = 8;
        }
    }
}

STATIC int rmissile_act_helper_helper_8006C0A4(void)
{
    GV_MSG *message;
    int length;

    length = GV_ReceiveMessage(0x15A9, &message);

    if (length > 0)
    {
        for (length--; length >= 0; message++, length--)
        {
            if (message->message[0] == HASH_KILL)
            {
                return 1;
            }
        }
    }

    return 0;
}

STATIC void rmissile_act_helper_8006C114(RMissileWork *work)
{
    SVECTOR *position;
    int found;
    MATRIX rotation;
    BLAST_DATA *blast;

    if (work->field_112)
    {
        return;
    }

    position = &work->control.mov;
    found = rmissile_act_helper_helper_8006C0A4();

    if (work->control.field_58 <= 0 && !(work->control.field_57 & 2))
    {
        if (position->vy - work->field_108_svector.vy < 200)
        {
            if (++work->field_118 != 1000 && !GM_PowerTarget(&work->target) && !dword_8009F480 && !found)
            {
                if (!HZD_80029098(work->control.map->hzd, position, 250, 15, 8))
                {
                    if (abs(position->vx) <= 30000 && abs(position->vy) <= 30000 && abs(position->vz) <= 30000)
                    {
                        return;
                    }
                }
            }
        }
    }

    if (GM_Camera_800B77E8.first_person && !work->field_117)
    {
        GM_Camera_800B77E8.first_person = 0;
        Nik_Blast = 0;
    }

    work->field_113 = 0;
    dword_8009F480 = 0;
    work->field_112 = 1;
    work->field_118 = found ? 28 : 0;
    work->control.step = DG_ZeroVector;
    DG_InvisibleObjs(work->object.objs);
    work->object.objs->group_id = 0;
    work->field_11C = -2;

    if (!found)
    {
        DG_SetPos2(position, &work->control.rot);
        ReadRotMatrix(&rotation);

        GM_CurrentMap_800AB9B0 = work->control.map->index;

        if (GM_GameStatus & (STATE_PADRELEASE | STATE_PADDEMO | STATE_DEMO))
        {
            blast = &blast_data_8009F4B8[7];
        #ifdef VR_EXE
            if ((GM_GameStatus & STATE_PADDEMO) &&
                !(GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF) &&
                !(GM_GameStatus & STATE_PADRELEASE))
            {
                blast = &blast_data_8009F4B8[4];
            }
        #endif
        }
        else
        {
            blast = &blast_data_8009F4B8[4];
        }
        NewBlast(&rotation, blast);
    }
}

STATIC void rmissile_act_helper_8006C37C(RMissileWork *work)
{
    SVECTOR   vecs[8];
    POLY_FT4 *poly;
    DG_TEX   *tex;
    int i;
    int inc;
    int offx;
    int offy;
    int width;
    int height;
    int y;
    int rand1;
    int rand2;

    if (work->field_11C > 0)
    {
        inc = 80;
        y = 120;
    }
    else
    {
        inc = 64;
        y = 120;
    }

    poly = &work->field_2D8_prim->packs[GV_Clock_800AB920]->poly_ft4;

    for (i = 0; i < 8; i++, poly++)
    {
        if (work->field_11C && (i == 0))
        {
            poly->tpage &= ~0x60;
            poly->tpage |= 0x20;
        }
        else
        {
            poly->tpage |= 0x60;
        }

        vecs[i].vx = 0;

        if (work->field_11C)
        {
            vecs[i].vy = 150 + i * inc;
        }
        else
        {
            vecs[i].vy = 250 + i * inc;
        }

        vecs[i].vz = 0;

        work->field_2E4_svector_8Array[i].pad = y;
        y = 15 * y / 16;


        rand1 = GV_RandU(4) & 1;
        rand2 = GV_RandU(4);

        tex = work->field_2DC_tex;

        offx = work->field_2DC_tex->off_x;
        width = work->field_2DC_tex->w + 1;

        poly->u3 = offx + (width << rand1) / 2 - 1;
        poly->u1 = offx + (width << rand1) / 2 - 1;

        poly->u2 = offx + ((width * rand1) >> 1);
        poly->u0 = offx + ((width * rand1) >> 1);


        offy = work->field_2DC_tex->off_y;
        height = work->field_2DC_tex->h + 1;

        poly->v1 = offy + (height * (rand2 / 2)) / 2;
        poly->v0 = offy + (height * (rand2 / 2)) / 2;

        poly->v3 = offy + (height * (rand2 / 2 + 1)) / 2 - 1;
        poly->v2 = offy + (height * (rand2 / 2 + 1)) / 2 - 1;

        setRGB0(poly, 128u - i * 16, 128u - i * 16, 128u - i * 16);
    }

    DG_SetPos2(&work->control.mov, &work->control.rot);
    DG_PutVector(vecs, work->field_2E4_svector_8Array, 8);
}

STATIC void RMissileAct(RMissileWork *work)
{
    GV_PAD *pad;
    BLAST_DATA *blast;
    SVECTOR vector;
    SVECTOR vector2;
    MATRIX rotation;

    pad = &GV_PadData_800B05C0[0];

    if (GM_PlayerStatus_800ABA50 & PLAYER_USING_CONTROLLER_PORT_2)
    {
        pad = &GV_PadData_800B05C0[1];
    }

    if (work->field_324-- > 0 || (work->field_11C < 0 && work->field_11C > -3))
    {
        DG_InvisiblePrim(work->field_2D8_prim);
    }
    else
    {
        DG_VisiblePrim(work->field_2D8_prim);
        rmissile_act_helper_8006C37C(work);
    }

    if (work->field_110 && !work->field_112)
    {
        if (--work->field_110 != 0)
        {
            if (work->field_118 != 0)
            {
                vector2 = work->control.mov;
                GV_NearExp2V(&vector2.vx, &work->field_100_svector.vx, 3);
                GV_SubVec3(&vector2, &work->control.mov, &work->control.step);
            }
        }
        else
        {
            DG_VisibleObjs(work->object.objs);
            work->target.side = 0;
            GV_SubVec3(&work->field_100_svector, &work->control.mov, &work->control.step);
        }
    }

    if (GM_CurrentWeaponId != 3)
    {
        if (!work->field_112)
        {
            GM_CurrentMap_800AB9B0 = work->control.map->index;
            DG_SetPos2(&work->control.mov, &work->control.rot);
            ReadRotMatrix(&rotation);

            if (GM_GameStatus & (STATE_PADRELEASE | STATE_PADDEMO | STATE_DEMO)
                || !GM_SnakeCurrentHealth || GM_GameOverTimer)
            {
                blast = &blast_data_8009F4B8[7];
            #ifdef VR_EXE
                if ((GM_GameStatus & STATE_PADDEMO) &&
                    !(GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF) &&
                    !(GM_GameStatus & STATE_PADRELEASE))
                {
                    blast = &blast_data_8009F4B8[4];
                }
            #endif
            }
            else
            {
                blast = &blast_data_8009F4B8[4];
            }

            NewBlast(&rotation, blast);
        }

        dword_8009F480 = 0;

        if (GM_Camera_800B77E8.first_person && GM_PlayerBody_800ABA20)
        {
            DG_InvisibleObjs(GM_PlayerBody_800ABA20->objs);
        }

        work->field_11C = -1;
        GV_DestroyActor(&work->actor);
    }
    else
    {
        rmissile_act_helper_8006BEEC(work);
        rmissile_act_helper_8006C114(work);

        if (!work->field_117)
        {
            gUnkCameraStruct_800B77B8.eye = work->control.mov;
        }
        else
        {
            vector = work->field_16C_svector;
            GV_NearTimeV(&work->field_16C_svector.vx, &GM_PlayerPosition_800ABA10.vx, work->field_16A, 3);
            gUnkCameraStruct_800B77B8.eye = work->field_16C_svector;

            if (work->field_16A > 0)
            {
                work->field_16A--;
            }
        }

        dword_8009F46C = !work->field_117;

        if (work->field_112)
        {
            if (++work->field_118 == 30)
            {
                GV_DestroyActor(&work->actor);
            }
        }
        else
        {
            GM_SetNoise(5, 2, &work->control.mov);
            work->field_108_svector = work->control.mov;

            GM_ActControl(&work->control);
            svector_8009F478 = vector2 = work->control.mov;

            GM_ActObject2((OBJECT *)&work->object);
            DG_GetLightMatrix2(&vector2, work->light);

            if (!work->field_117 && !work->field_110)
            {
                if (GM_PlayerBody_800ABA20)
                {
                    DG_VisibleObjs(GM_PlayerBody_800ABA20->objs);
                }

                if (!work->field_113)
                {
                    rmissile_act_helper_8006BE50(work, pad->dir);
                }
                else
                {
                    rmissile_act_helper_8006BE90(work, pad->status);
                }
            }

            rmissile_act_helper_8006BFD4(work);

            if (1000 - work->field_118 < 100)
            {
                work->control.rot.vy += GV_RandS(32) * (work->field_118 - 900) / 32;
                work->field_11C = GV_RandU(2);
            }

            if (work->field_117 == 1)
            {
                work->control.rot.vy += GV_RandS(128);
            }

            GV_DirVec2(work->control.rot.vy, work->field_11A, &work->control.step);
            rmissile_act_helper_8006BD24(work, pad->status);
            GM_MoveTarget(&work->target, &vector2);
        }
    }
}

STATIC void RMissileDie(RMissileWork *work)
{
    DG_PRIM *prim;

    GM_FreeControl(&work->control);
    GM_FreeObject((OBJECT *)&work->object);

    if (work->field_174_polys_2Array[0])
    {
        GV_DelayedFree(work->field_174_polys_2Array[0]);
        dword_8009F46C = 0;
    }
    else
    {
        dword_8009F46C = 0;
    }

    dword_8009F470 = 0;
    Nik_Blast = 0;

    prim = work->field_2D8_prim;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    if (!work->field_117)
    {
        rmissile_8006B924(work);
    }
}

STATIC int RMissileInitTarget(RMissileWork *work, int side)
{
    TARGET *target = &work->target;

    GM_SetTarget(target, TARGET_POWER, side, &svector_8009F488);
    GM_Target_8002DCCC(target, 0, -1, 1, 0, &DG_ZeroVector);
    GM_MoveTarget(target, &work->control.mov);
    return 0;
}

STATIC int RMissileInitPolys(RMissileWork *work)
{
    POLY_F4 *poly;
    POLY_F4 *poly2;

    work->field_174_polys_2Array[0] = poly = GV_Malloc(sizeof(POLY_F4) * 2);

    if (!poly)
    {
        return -1;
    }

    work->field_174_polys_2Array[1] = poly + 1;

    LSTORE(0x008ab89e, &poly[0].r0);
    LSTORE(0x008ab89e, &poly[1].r0);

    poly2 = poly + 1;

    SetPolyF4(poly);
    SetPolyF4(poly2);
    SetSemiTrans(poly, 1);
    SetSemiTrans(poly2, 1);

    poly2->x2 = 31;
    poly2->x0 = 31;
    poly->x2 = 31;
    poly->x0 = 31;
    poly2->y1 = 39;
    poly2->y0 = 39;
    poly->y1 = 39;
    poly->y0 = 39;
    poly2->y3 = 49;
    poly2->y2 = 49;
    poly->y3 = 49;
    poly->y2 = 49;

    return 0;
}

static inline void rmissile_loader_helper_helper_8006CD1C_set_poly(POLY_FT4 *poly, DG_TEX *tex)
{
    int u, v, w, h;

    setPolyFT4(poly);
    setSemiTrans(poly, 1);

    u = tex->off_x;
    w = (tex->w + 1) / 2;
    poly->u2 = u;
    poly->u0 = u;
    u += w;
    poly->u3 = u - 1;
    poly->u1 = u - 1;

    v = tex->off_y;
    h = (tex->h + 1) / 2;
    poly->v1 = v;
    poly->v0 = v;
    v += h;
    poly->v3 = v - 1;
    poly->v2 = v - 1;

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

STATIC void rmissile_loader_helper_helper_8006CD1C(POLY_FT4 *poly, DG_TEX *tex, int n_poly)
{
    rmissile_loader_helper_helper_8006CD1C_set_poly(poly, tex);
    poly->tpage = (poly->tpage & 0xff9f) | 0x20;

    poly->r0 = 0;
    poly->g0 = 0;
    poly->b0 = 0;

    poly++;
    n_poly--;

    while (n_poly-- != 0)
    {
        rmissile_loader_helper_helper_8006CD1C_set_poly(poly, tex);
        poly->tpage |= 0x60;

        setRGB0(poly, 0, 0, 0);

        poly++;
    }
}

STATIC void rmissile_loader_helper_8006CE54(RMissileWork *work)
{
    int hash;
    DG_TEX *tex;
    SVECTOR *vec;
    DG_PRIM *prim;
    int count;

    hash = GV_StrCode("socom_f");
    tex = DG_GetTexture(hash);

    work->field_2DC_tex = tex;
    prim = work->field_2D8_prim = Takabe_MakeIndividualRect3DPrim(8, work->field_2E4_svector_8Array);

    rmissile_loader_helper_helper_8006CD1C(&prim->packs[0]->poly_ft4, tex, 8);
    rmissile_loader_helper_helper_8006CD1C(&prim->packs[1]->poly_ft4, tex, 8);

    prim->world = DG_ZeroMatrix;
    prim->field_2E_k500 = 100;

    vec = work->field_2E4_svector_8Array;
    for (count = 8; count > 0; vec++, count--)
    {
        vec->pad = 0;
    }
}

static inline int RMissileGetEight(void)
{
    return 8;   // what???
}

STATIC int RMissileGetResources(RMissileWork *work, MATRIX *world, int side)
{
    CONTROL        *ctrl;
    OBJECT_NO_ROTS *object;

    dword_8009F46C = 1;
    dword_8009F470 = 1;

    rmissile_loader_helper4_8006B800(work);

    ctrl = &work->control;

    if (GM_InitControl(ctrl, CHARA_RCM, 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlMatrix(ctrl, world);

    work->field_100_svector = ctrl->mov;
    work->field_110 = 8;
    ctrl->mov = GM_PlayerPosition_800ABA10;
    work->field_108_svector = GM_PlayerPosition_800ABA10;
    svector_8009F478 = GM_PlayerPosition_800ABA10;

    GM_ConfigControlHazard(ctrl, 400, 0xC8, 0xC8);
    ctrl->field_59 = RMissileGetEight();
    GM_ConfigControlTrapCheck(ctrl);

    object = &work->object;
    ctrl->turn.vz = 0;
    ctrl->rot.vz = 0;
    ctrl->skip_flag |= CTRL_SKIP_NEAR_CHECK;

    GM_InitObjectNoRots(object, 0x9A90, 0x36D, 0);

    if (!object->objs)
    {
        return -1;
    }

    GM_ConfigObjectLight((OBJECT *)object, work->light);

    if (RMissileInitTarget(work, side) < 0)
    {
        return -1;
    }

    if (RMissileInitPolys(work) < 0)
    {
        return -1;
    }

    DG_InvisibleObjs(work->object.objs);
    work->field_11C = -1;
    work->field_324 = 10;
    rmissile_loader_helper_8006CE54(work);
    return 0;
}

/*---------------------------------------------------------------------------*/

GV_ACT *NewRMissile(MATRIX *world, int side)
{
    RMissileWork *work;

    work = (RMissileWork *)GV_NewActor(EXEC_LEVEL, sizeof(RMissileWork));

    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)RMissileAct,
                         (GV_ACTFUNC)RMissileDie, "rmissile.c");

        if (RMissileGetResources(work, world, side) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->field_111 = 30;
        work->field_112 = 0;
        work->field_113 = 0;
        work->field_117 = 0;
        work->field_114 = 0;
        work->field_115 = 0;
        work->field_116 = 0;
        dword_8009F480 = 0;
        work->field_118 = 0;
        work->field_11A = 0;
        work->field_11C = 0;
        work->field_168 = 0;
        Nik_Blast = 0;
    }

    return &work->actor;
}
