#include "rmissile.h"
#include "blast.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "takabe/prim.h"
#include "game/game.h"
#include "game/camera.h"
#include "game/object.h"
#include "game/map.h"
#include "linkvar.h"
#include "menu/menuman.h"
#include "thing/sgtrect3.h"
#include "thing/sight.h"
#include "sd/g_sound.h"

extern BLAST_DATA       blast_data_8009F4B8[8];
extern TARGET          *target_800BDF00;
extern int              dword_8009F604;
extern int              dword_800BDEF8[];
extern int              GM_CameraTrackSave;
extern SVECTOR          GM_CameraRotateSave;
extern int              GM_event_camera_flag;
extern GM_CAMERA        GM_Camera;
extern UnkCameraStruct  gUnkCameraStruct_800B77B8;
extern CAMERA           GM_CameraList[8];

/*---------------------------------------------------------------------------*/
// RC Missile (Nikita)

#define EXEC_LEVEL      GV_ACTOR_AFTER

#define NIKITA_NAME     0x50ae  // GV_StrCode("RCM")
#define NIKITA_SIGHT    0x15a9  // GV_StrCode("nikita")
#define NIKITA_MSG      0x15a9  // GV_StrCode("nikita")
#define NIKITA_MODEL    0x9a90  // GV_StrCode("nik_mis")

#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | \
                          DG_FLAG_GBOUND | DG_FLAG_ONEPIECE | \
                          DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

#define SEGMENT_ATR     (HZD_SEG_NO_MISSILE)

#define MISSILE_SPEED_SLOW      50
#define MISSILE_SPEED_FAST      200

#define FUEL_BAR_XOFFSET        31
#define FUEL_BAR_YOFFSET        39
#define FUEL_BAR_HEIGHT         10

#define COLOR_LIGHT_GREEN       MAKE_RGB0(158,184,138)
#define COLOR_DARK_GREEN        MAKE_RGB0( 93,135, 90)
#define COLOR_LIGHT_RED         MAKE_RGB0(212, 78, 78)
#define COLOR_DARK_RED          MAKE_RGB0(128, 26, 12)

typedef struct _Work
{
    GV_ACT          actor;
    CONTROL         control;
    OBJECT_NO_ROTS  object;
    MATRIX          light[2];
    SVECTOR         field_100_svector;  // work->control.mov
    SVECTOR         field_108_svector;  // work->control.mov
    char            field_110;
    char            boost_delay;
    char            field_112;
    char            fpv_mode;
    char            hud_delay;
    char            field_115;
    char            field_116;
    char            field_117;
    short           field_118;
    short           speed;
    int             field_11C;
    TARGET          target;
    short           enemy_time;
    short           cam_interp;
    SVECTOR         cam_pos;
    POLY_F4        *fuel_bar[2];
    GM_CAMERA       saved_camera;
    UnkCameraStruct saved_camera_unk;
    CAMERA          saved_camera_list[8];
    int             saved_camera_track;
    SVECTOR         saved_camera_rotate;
    int             saved_camera_event;
    DG_PRIM        *flame;
    DG_TEX         *flame_tex;
    char            field_2E0_pad[4];
    SVECTOR         flame_vec[8];
    int             flame_delay;
} Work;

/*---------------------------------------------------------------------------*/

int dword_8009F46C = 0; // FIXME: this is referenced as an array in several places
int dword_8009F470 = 0;
int dword_8009F474 = 0;
SVECTOR svector_8009F478 = {0, 0, 0, 0};
int dword_8009F480 = 0;
short Nik_Blast = 0;
SVECTOR svector_8009F488 = {100, 100, 100, 0};

/*---------------------------------------------------------------------------*/

static void SaveCameraState(Work *work)
{
    GV_CopyMemory(&GM_Camera,                 &work->saved_camera,        sizeof(work->saved_camera));
    GV_CopyMemory(&gUnkCameraStruct_800B77B8, &work->saved_camera_unk,    sizeof(work->saved_camera_unk));
    GV_CopyMemory(GM_CameraList,              &work->saved_camera_list,   sizeof(work->saved_camera_list));
    GV_CopyMemory(&GM_CameraRotateSave,       &work->saved_camera_rotate, sizeof(work->saved_camera_rotate));

    work->saved_camera_track = GM_CameraTrackSave;
    work->saved_camera_event = GM_event_camera_flag;
}

static void ResetCameraState(Work *work)
{
    GV_CopyMemory(&work->saved_camera,        &GM_Camera,                 sizeof(work->saved_camera));
    GV_CopyMemory(&work->saved_camera_unk,    &gUnkCameraStruct_800B77B8, sizeof(work->saved_camera_unk));
    GV_CopyMemory(&work->saved_camera_list,   &GM_CameraList,             sizeof(work->saved_camera_list));
    GV_CopyMemory(&work->saved_camera_rotate, &GM_CameraRotateSave,       sizeof(work->saved_camera_rotate));

    GM_CameraTrackSave = work->saved_camera_track;
    GM_event_camera_flag = work->saved_camera_event;

    sub_800309B4(2, 30);
    GM_CameraEventReset();
}

static void rmissile_8006B924(Work *work)
{
    CONTROL *ctrl;

    ctrl = &work->control;
    ctrl->skip_flag |= CTRL_SKIP_TRAP;

    ResetCameraState(work);
    GM_GameStatus &= ~GAME_FLAG_BIT_07;
    HZD_ExecLeaveEvent(ctrl->map->hzd, &ctrl->event);

    ctrl = GM_PlayerControl;

    if (ctrl)
    {
        HZD_ReExecEvent(ctrl->map->hzd, &ctrl->event, 0x102);
    }
}

static void SetFirstPersonView(Work *work)
{
    Nik_Blast = 1;

    if (dword_8009F604 != NIKITA_SIGHT)
    {
        NewSight(NIKITA_SIGHT, NIKITA_SIGHT, &Nik_Blast, IT_Scope, NULL);
    }

    GM_Camera.first_person = 1;

    if (work->fpv_mode == FALSE)
    {
        work->fpv_mode = TRUE;
        dword_800BDEF8[0] = COLOR_DARK_GREEN;
        dword_800BDEF8[1] = COLOR_DARK_RED;
        NewSgtRect3(&Nik_Blast, 1, dword_800BDEF8, 0);
        GM_SeSet2(0, 0x3F, SE_ITEM_OPENWINDOW);
    }
}

static void DrawEnemyText(Work *work)
{
    if (!target_800BDF00)
    {
        work->enemy_time = 0;
        return;
    }

    work->enemy_time++;

    if (work->enemy_time <= 16)
    {
        return;
    }

    if (work->enemy_time == 32)
    {
        work->enemy_time = 0;
    }

    if (!(GM_PlayerStatus & PLAYER_NOT_SIGHT))
    {
        MENU_Color(158, 184, 138);
        MENU_Locate(116, 98, 0);
        MENU_Printf("ENEMY\n");
        menu_Text_Init_80038B98();
    }
}

static void DrawMissileHud(Work *work)
{
    int width;
    u_long *ot;
    POLY_F4 *bar;
    CONTROL ctrl;

    width = ((1000 - work->field_118) * 60) / 1000;

    ot = (u_long *)DG_ChanlOTag(1);
    bar = work->fuel_bar[GV_Clock];

    if (width > 60)
    {
        width = 60;
    }

    /* update fuel gauge */
    bar->x3 = width + FUEL_BAR_XOFFSET;
    bar->x1 = width + FUEL_BAR_XOFFSET;

    if (GM_PlayerStatus & PLAYER_NOT_SIGHT)
    {
        return;
    }

    if (width < 15)
    {
        /* low fuel remaining */
        setRGB0(bar, 212, 78, 78);

        if (!(work->field_118 % 15))
        {
            GM_SeSet2(0, 63, SE_SIGNAL02);
        }
    }

    addPrim(ot, bar);

    /* print missile XYZ position */
    ctrl = work->control;

    MENU_Locate(8, 136, 0);
    MENU_Printf("%d", ctrl.mov.vx);

    MENU_Locate(8, 144, 0);
    MENU_Printf("%d", ctrl.mov.vy);

    MENU_Locate(8, 152, 0);
    MENU_Printf("%d", ctrl.mov.vz);

    menu_Text_Init_80038B98();
}

static void rmissile_act_helper_8006BD24(Work *work, int pad_status)
{
    if (work->field_112 || work->field_117 || work->field_110)
    {
        return;
    }

    if (pad_status & PAD_TRIANGLE)
    {
        SetFirstPersonView(work);

        gUnkCameraStruct_800B77B8.rotate2.vx = 0;
        gUnkCameraStruct_800B77B8.rotate2.vy = work->control.rot.vy;
        gUnkCameraStruct_800B77B8.rotate2.vz = 0;

        DG_InvisibleObjs(work->object.objs);

        work->field_11C = -2;

        if (work->hud_delay < 16)
        {
            work->hud_delay++;
            return;
        }

        DrawMissileHud(work);
        DrawEnemyText(work);
        return;
    }

    if (work->fpv_mode)
    {
        work->field_115 = 5;
    }

    work->hud_delay = 0;
    work->fpv_mode = FALSE;

    GM_Camera.first_person = 0;
    Nik_Blast = 0;

    if (work->field_115)
    {
        work->field_115--;

        if (work->field_115 == 0)
        {
            DG_VisibleObjs(work->object.objs);
        }
    }
}

static void SetMissileDir3P(Work *work, int pad_dir)
{
    if (GM_PlayerStatus & PLAYER_PAD_OFF)
    {
        return;
    }

    if (pad_dir >= 0 && work->control.turn.vy != pad_dir)
    {
        work->boost_delay = 30;
        work->control.turn.vy = pad_dir;
    }
}

static void SetMissileDir1P(Work *work, int pad_status)
{
    if (GM_PlayerStatus & PLAYER_PAD_OFF)
    {
        return;
    }

    if (pad_status & PAD_LEFT)
    {
        work->boost_delay = 30;
        work->control.turn.vy += 64;
        work->control.turn.vy &= 0x0FFF;
    }

    if (pad_status & PAD_RIGHT)
    {
        work->boost_delay = 30;
        work->control.turn.vy -= 64;
        work->control.turn.vy &= 0x0FFF;
    }
}

static void rmissile_act_helper_8006BEEC(Work *work)
{
    if (work->field_117)
    {
        return;
    }

    if (GM_PlayerStatus & (PLAYER_DAMAGED | PLAYER_GAME_OVER) ||
        dword_8009F474 == 1 || GM_GameStatus & (STATE_CHAFF | STATE_JAMMING))
    {
        work->field_117 = 1;
        work->cam_interp = 15;
        work->cam_pos = work->control.mov;
        work->fpv_mode = FALSE;

        GM_Camera.first_person = 0;
        Nik_Blast = 0;

        if (!work->field_112)
        {
            DG_VisibleObjs(work->object.objs);
        }

        dword_8009F474 = 0;
        rmissile_8006B924(work);
    }
}

static void rmissile_act_helper_8006BFD4(Work *work)
{
    if (work->boost_delay)
    {
        work->boost_delay--;

        if (work->boost_delay == 0)
        {
            GM_SeSet2(0, 63, SE_MISSILE_BOOST);
            work->field_116 = 12;
        }

        work->speed = MISSILE_SPEED_SLOW;

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

        work->speed = MISSILE_SPEED_FAST;

        if (!work->field_112)
        {
            work->field_11C = 8;
        }
    }
}

static int CheckMessage(void)
{
    GV_MSG *msg;
    int     len;

    len = GV_ReceiveMessage(NIKITA_MSG, &msg);
    if (len > 0)
    {
        for (len--; len >= 0; msg++, len--)
        {
            if (msg->message[0] == HASH_KILL)
            {
                return 1;
            }
        }
    }
    return 0;
}

static void rmissile_act_helper_8006C114(Work *work)
{
    SVECTOR *position;
    int result;
    MATRIX rotation;
    BLAST_DATA *blast;

    if (work->field_112)
    {
        return;
    }

    position = &work->control.mov;
    result = CheckMessage();

    if (work->control.touch_flag <= 0 && !(work->control.level_flag & 2))
    {
        if (position->vy - work->field_108_svector.vy < 200)
        {
            if (++work->field_118 != 1000 && !GM_PowerTarget(&work->target) && !dword_8009F480 && !result)
            {
                if (!HZD_PointCheck(work->control.map->hzd, position, 250, HZD_CHECK_ALL, SEGMENT_ATR))
                {
                    if (abs(position->vx) <= 30000 &&
                        abs(position->vy) <= 30000 &&
                        abs(position->vz) <= 30000)
                    {
                        return;
                    }
                }
            }
        }
    }

    if (GM_Camera.first_person && !work->field_117)
    {
        GM_Camera.first_person = 0;
        Nik_Blast = 0;
    }

    work->fpv_mode = FALSE;
    dword_8009F480 = 0;
    work->field_112 = 1;
    work->field_118 = result ? 28 : 0;
    work->control.step = DG_ZeroVector;
    DG_InvisibleObjs(work->object.objs);
    work->object.objs->group_id = 0;
    work->field_11C = -2;

    if (!result)
    {
        DG_SetPos2(position, &work->control.rot);
        ReadRotMatrix(&rotation);

        GM_CurrentMap = work->control.map->index;

        if (GM_GameStatus & (STATE_PADRELEASE | STATE_PADDEMO | STATE_DEMO))
        {
            blast = &blast_data_8009F4B8[7];
        #ifdef VR_EXE
            if ((GM_GameStatus & STATE_PADDEMO) &&
                !(GM_PlayerStatus & PLAYER_PAD_OFF) &&
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

static void rmissile_act_helper_8006C37C(Work *work)
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

    poly = &work->flame->packs[GV_Clock]->poly_ft4;

    for (i = 0; i < 8; i++, poly++)
    {
        if (work->field_11C && (i == 0))
        {
            poly->tpage &= ~0x0060;
            poly->tpage |= 0x0020;
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

        work->flame_vec[i].pad = y;
        y = 15 * y / 16;


        rand1 = GV_RandU(4) & 1;
        rand2 = GV_RandU(4);

        tex = work->flame_tex;

        offx = work->flame_tex->off_x;
        width = work->flame_tex->w + 1;

        poly->u3 = offx + (width << rand1) / 2 - 1;
        poly->u1 = offx + (width << rand1) / 2 - 1;

        poly->u2 = offx + ((width * rand1) >> 1);
        poly->u0 = offx + ((width * rand1) >> 1);


        offy = work->flame_tex->off_y;
        height = work->flame_tex->h + 1;

        poly->v1 = offy + (height * (rand2 / 2)) / 2;
        poly->v0 = offy + (height * (rand2 / 2)) / 2;

        poly->v3 = offy + (height * (rand2 / 2 + 1)) / 2 - 1;
        poly->v2 = offy + (height * (rand2 / 2 + 1)) / 2 - 1;

        setRGB0(poly, 128u - i * 16, 128u - i * 16, 128u - i * 16);
    }

    DG_SetPos2(&work->control.mov, &work->control.rot);
    DG_PutVector(vecs, work->flame_vec, 8);
}

static void Act(Work *work)
{
    GV_PAD *pad;
    BLAST_DATA *blast;
    SVECTOR vector;
    SVECTOR vector2;
    MATRIX rotation;

    pad = &GV_PadData[0];

    if (GM_PlayerStatus & PLAYER_SECOND_CONTROLLER)
    {
        pad = &GV_PadData[1];
    }

    if (work->flame_delay-- > 0 || (work->field_11C < 0 && work->field_11C > -3))
    {
        DG_InvisiblePrim(work->flame);
    }
    else
    {
        DG_VisiblePrim(work->flame);
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
        /* player has unequipped the Nikita launcher */
        if (!work->field_112)
        {
            GM_CurrentMap = work->control.map->index;
            DG_SetPos2(&work->control.mov, &work->control.rot);
            ReadRotMatrix(&rotation);

            if (GM_GameStatus & (STATE_PADRELEASE | STATE_PADDEMO | STATE_DEMO)
                || !GM_SnakeCurrentHealth || GM_GameOverTimer)
            {
                blast = &blast_data_8009F4B8[7];
            #ifdef VR_EXE
                if ((GM_GameStatus & STATE_PADDEMO) &&
                    !(GM_PlayerStatus & PLAYER_PAD_OFF) &&
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

        if (GM_Camera.first_person && GM_PlayerBody)
        {
            DG_InvisibleObjs(GM_PlayerBody->objs);
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
            vector = work->cam_pos;
            GV_NearTimeV(&work->cam_pos.vx, &GM_PlayerPosition.vx, work->cam_interp, 3);
            gUnkCameraStruct_800B77B8.eye = work->cam_pos;

            if (work->cam_interp > 0)
            {
                work->cam_interp--;
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
                if (GM_PlayerBody)
                {
                    DG_VisibleObjs(GM_PlayerBody->objs);
                }

                if (work->fpv_mode == FALSE)
                {
                    SetMissileDir3P(work, pad->dir);
                }
                else
                {
                    SetMissileDir1P(work, pad->status);
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

            GV_DirVec2(work->control.rot.vy, work->speed, &work->control.step);
            rmissile_act_helper_8006BD24(work, pad->status);
            GM_MoveTarget(&work->target, &vector2);
        }
    }
}

/*---------------------------------------------------------------------------*/

static void Die(Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject((OBJECT *)&work->object);

    if (work->fuel_bar[0])
    {
        GV_DelayedFree(work->fuel_bar[0]);
        dword_8009F46C = 0;
    }
    else
    {
        dword_8009F46C = 0;
    }

    dword_8009F470 = 0;
    Nik_Blast = 0;

    GM_FreePrim(work->flame);

    if (!work->field_117)
    {
        rmissile_8006B924(work);
    }
}

/*---------------------------------------------------------------------------*/

static int InitTarget(Work *work, int side)
{
    TARGET *target = &work->target;

    GM_SetTarget(target, TARGET_POWER, side, &svector_8009F488);
    GM_Target_8002DCCC(target, 0, -1, 1, 0, &DG_ZeroVector);
    GM_MoveTarget(target, &work->control.mov);
    return 0;
}

static int InitFuelBar(Work *work)
{
    POLY_F4 *poly1;
    POLY_F4 *poly2;

    work->fuel_bar[0] = poly1 = GV_Malloc(sizeof(POLY_F4) * 2);

    if (poly1 == NULL)
    {
        return -1;
    }

    work->fuel_bar[1] = &poly1[1];

    LSTORE(COLOR_LIGHT_GREEN, &poly1[0].r0);
    LSTORE(COLOR_LIGHT_GREEN, &poly1[1].r0);

    poly2 = &poly1[1];

    SetPolyF4(poly1);
    SetPolyF4(poly2);
    SetSemiTrans(poly1, 1);
    SetSemiTrans(poly2, 1);

    /* left side screen coordinates */
    poly2->x2 = FUEL_BAR_XOFFSET;
    poly2->x0 = FUEL_BAR_XOFFSET;
    poly1->x2 = FUEL_BAR_XOFFSET;
    poly1->x0 = FUEL_BAR_XOFFSET;

    /* top side screen coordinates */
    poly2->y1 = FUEL_BAR_YOFFSET;
    poly2->y0 = FUEL_BAR_YOFFSET;
    poly1->y1 = FUEL_BAR_YOFFSET;
    poly1->y0 = FUEL_BAR_YOFFSET;

    /* bottom side screen coordinates */
    poly2->y3 = (FUEL_BAR_YOFFSET + FUEL_BAR_HEIGHT);
    poly2->y2 = (FUEL_BAR_YOFFSET + FUEL_BAR_HEIGHT);
    poly1->y3 = (FUEL_BAR_YOFFSET + FUEL_BAR_HEIGHT);
    poly1->y2 = (FUEL_BAR_YOFFSET + FUEL_BAR_HEIGHT);

    return 0;
}

static inline void set_poly_tex(POLY_FT4 *poly, DG_TEX *tex)
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

static void SetPolyTexture(POLY_FT4 *poly, DG_TEX *tex, int n_poly)
{
    set_poly_tex(poly, tex);
    poly->tpage = (poly->tpage & ~0x0060) | 0x20;

    poly->r0 = 0;
    poly->g0 = 0;
    poly->b0 = 0;

    poly++;
    n_poly--;

    while (n_poly-- != 0)
    {
        set_poly_tex(poly, tex);
        poly->tpage |= 0x0060;

        setRGB0(poly, 0, 0, 0);

        poly++;
    }
}

static void InitMissileFlame(Work *work)
{
    DG_TEX *tex;
    SVECTOR *vec;
    DG_PRIM *prim;
    int count;

    tex = DG_GetTexture(GV_StrCode("socom_f"));

    work->flame_tex = tex;
    prim = work->flame = Takabe_MakeIndividualRect3DPrim(8, work->flame_vec);

    SetPolyTexture(&prim->packs[0]->poly_ft4, tex, 8);
    SetPolyTexture(&prim->packs[1]->poly_ft4, tex, 8);

    prim->world = DG_ZeroMatrix;
    prim->field_2E_k500 = 100;

    vec = work->flame_vec;
    for (count = 8; count > 0; vec++, count--)
    {
        vec->pad = 0;
    }
}

static inline int GetEight(void)
{
    return 8;   // what???
}

static int GetResources(Work *work, MATRIX *world, int side)
{
    CONTROL        *ctrl;
    OBJECT_NO_ROTS *object;

    dword_8009F46C = 1;
    dword_8009F470 = 1;

    SaveCameraState(work);

    ctrl = &work->control;

    if (GM_InitControl(ctrl, NIKITA_NAME, 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlMatrix(ctrl, world);

    work->field_100_svector = ctrl->mov;
    work->field_110 = 8;
    ctrl->mov = GM_PlayerPosition;
    work->field_108_svector = GM_PlayerPosition;
    svector_8009F478 = GM_PlayerPosition;

    GM_ConfigControlHazard(ctrl, 400, 0xC8, 0xC8);
    ctrl->exclude_flag = GetEight();
    GM_ConfigControlTrapCheck(ctrl);

    object = &work->object;
    ctrl->turn.vz = 0;
    ctrl->rot.vz = 0;
    ctrl->skip_flag |= CTRL_SKIP_NEAR_CHECK;

    GM_InitObjectNoRots(object, NIKITA_MODEL, BODY_FLAG, 0);

    if (!object->objs)
    {
        return -1;
    }

    GM_ConfigObjectLight((OBJECT *)object, work->light);

    if (InitTarget(work, side) < 0)
    {
        return -1;
    }

    if (InitFuelBar(work) < 0)
    {
        return -1;
    }

    DG_InvisibleObjs(work->object.objs);
    work->field_11C = -1;
    work->flame_delay = 10;
    InitMissileFlame(work);
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewRMissile(MATRIX *world, int side)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));

    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "rmissile.c");

        if (GetResources(work, world, side) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->boost_delay = 30;
        work->field_112 = 0;
        work->fpv_mode = FALSE;
        work->field_117 = 0;
        work->hud_delay = 0;
        work->field_115 = 0;
        work->field_116 = 0;
        dword_8009F480 = 0;
        work->field_118 = 0;
        work->speed = 0;
        work->field_11C = 0;
        work->enemy_time = 0;
        Nik_Blast = 0;
    }

    return (void *)work;
}
