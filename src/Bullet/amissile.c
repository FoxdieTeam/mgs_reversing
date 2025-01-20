#include "amissile.h"
#include "blast.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Anime/animeconv/anime.h"
#include "Game/camera.h"
#include "Game/object.h"
#include "Game/target.h"
#include "SD/g_sound.h"
#include "strcode.h"

extern TARGET *target_800BDF00;

extern BLAST_DATA       blast_data_8009F4B8[8];

extern PlayerStatusFlag GM_PlayerStatus;
extern UnkCameraStruct  gUnkCameraStruct_800B77B8;

/*---------------------------------------------------------------------------*/
// Anti-Air Missile (Stinger)

typedef struct AMissileWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT_NO_ROTS body;
    MATRIX         light[2];
    MATRIX         rotation;
    int            field_120;
    int            field_124;
    int            field_128;
    SVECTOR        field_12C_svector;
    DG_PRIM       *prim;
    RECT           prim_rect;
    SVECTOR        vertices[4];
} AMissileWork;

#define EXEC_LEVEL 6
#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE | DG_FLAG_ONEPIECE )

int amissile_alive_8009F490 = 0;
SVECTOR svector_8009F494 = {0, 0, 0, 0};
int dword_8009F49C = 0;
SVECTOR svector_8009F4A0 = {0, -800, 0, 0};
SVECTOR svector_8009F4A8 = {0, -350, 0, 0};
SVECTOR svector_8009F4B0 = {0, -100, -70, 0};

/*---------------------------------------------------------------------------*/

STATIC void amissile_loader_helper_8006D1F4(POLY_FT4 *poly, DG_TEX *tex)
{
    int i;
    char rgb;
    int x, y, w, h;

    for (i = 0; i < 4; poly++, i++)
    {
        rgb = 128 - 32 * i;

        setPolyFT4(poly);
        setSemiTrans(poly, 1);
        setRGB0(poly, rgb, rgb, rgb);

        x = tex->off_x;
        w = tex->w + 1;
        poly->u0 = poly->u2 = x + w / 2;
        poly->u1 = poly->u3 = x + w - 1;

        y = tex->off_y;
        h = tex->h + 1;
        poly->v0 = poly->v1 = y + h / 2;
        poly->v2 = poly->v3 = y + h - 1;

        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
    }
}

STATIC void amissile_act_helper_8006D2A0(AMissileWork *work, SVECTOR input)
{
    SVECTOR position = work->control.mov;
    SVECTOR result;
    SVECTOR rotation;

    SVECTOR *out = &work->vertices[3];
    int i;

    GV_SubVec3(&input, &position, &result);

    for (i = 0; i < 4; i++)
    {
        GV_AddVec3(&result, out - 1, out);
        out--;
    }

    rotation = DG_ZeroVector;
    rotation.vy = 500;

    DG_RotVector(&rotation, &work->vertices[0], 1);
}

STATIC void amissile_act_helper_8006D37C(AMissileWork *work)
{
    SVECTOR diff;
    SVECTOR result;
    SVECTOR *target_pos;
    int dir;
    int temp_v0;
    int temp_s1;

    if (work->field_120 < 5)
    {
        DG_RotVector(&svector_8009F4A8, &work->control.step, 1);
        return;
    }

    if (work->field_120 < 14)
    {
        DG_RotVector(&svector_8009F4B0, &work->control.step, 1);
        return;
    }

    if (--work->field_124 >= 0)
    {
        svector_8009F4A0.vz = 11;
    }
    else
    {
        svector_8009F4A0.vz = 0;
    }

    DG_RotVector(&svector_8009F4A0, &work->control.step, 1);

    if (!target_800BDF00)
    {
        return;
    }

    target_pos = &target_800BDF00->center;
    diff.vx = target_pos->vx / 8 - work->control.mov.vx / 8;
    diff.vy = target_pos->vy / 8 - work->control.mov.vy / 8;
    diff.vz = target_pos->vz / 8 - work->control.mov.vz / 8;

    dir = GV_VecDir2(&diff);
    temp_v0 = GV_DiffDirS(work->control.turn.vy, dir);

    if (abs(temp_v0) > 1024)
    {
        return;
    }

    temp_s1 = 30 - work->field_120 / 3;

    if (abs(temp_v0) < temp_s1)
    {
        work->control.turn.vy += temp_v0;
    }
    else if (temp_v0 > 0)
    {
        work->control.turn.vy += temp_s1;
    }
    else
    {
        work->control.turn.vy -= temp_s1;
    }

    result.vx = diff.vy;
    result.vz = SquareRoot0(diff.vx * diff.vx + diff.vz * diff.vz);

    dir = -GV_VecDir2(&result);
    temp_v0 = GV_DiffDirS(work->control.turn.vx, (dir - 1024) & 4095);

    if (abs(temp_v0) < temp_s1)
    {
        work->control.turn.vx += temp_v0;
    }
    else if (temp_v0 > 0)
    {
        work->control.turn.vx += temp_s1;
    }
    else
    {
        work->control.turn.vx -= temp_s1;
    }
}

STATIC int AMissileCheckMessage(void)
{
#ifdef VR_EXE
    GV_MSG *msg;
    int     count;

    count = GV_ReceiveMessage(KMD_STINGER, &msg);
    if (count > 0)
    {
        for (count--; count >= 0; count--)
        {
            if (msg->message[0] == HASH_KILL)
            {
                return 1;
            }

            msg++;
        }
    }
#endif
    return 0;
}

STATIC void AMissileAct(AMissileWork *work)
{
    MATRIX rotation;
    SVECTOR position;
    SVECTOR addition;
#ifdef VR_EXE
    SVECTOR rotator;
#endif

    CONTROL *control;
    int result;
    BLAST_DATA *blast;

    control = &work->control;
    position = control->mov;

    GM_ActControl(control);
    amissile_act_helper_8006D37C(work);
    GM_ActObject2((OBJECT *)&work->body);

    work->prim->world.t[0] = work->control.mov.vx;
    work->prim->world.t[1] = work->control.mov.vy;
    work->prim->world.t[2] = work->control.mov.vz;

    DG_GetLightMatrix2(&control->mov, work->light);

    if (work->field_120 >= 15)
    {
        amissile_act_helper_8006D2A0(work, position);
    }

    amissile_alive_8009F490 = 1;
    svector_8009F494 = control->mov;

    if (work->field_120 == 0)
    {
        DG_VisiblePrim(work->prim);
        ReadRotMatrix(&work->rotation);
        NewAnime_8005DE70(&work->rotation);
        work->field_128 = 4;
    }

    if (work->field_120 == 14)
    {
        ReadRotMatrix(&work->rotation);
        NewAnime_8005DE70(&work->rotation);
        GM_SeSet2(0, 63, SE_MISSILE_BOOST);
        work->prim_rect.x = work->prim_rect.y = 1030;
        work->prim_rect.w = work->prim_rect.h = 2060;
        work->field_128 = 12;
        GM_ConfigControlHazard(control, 100, 100, 100);
    }

    if (--work->field_128 > 0)
    {
        gUnkCameraStruct_800B77B8.eye.vy += GV_RandS(512) * work->field_128 / 8;

        if (work->field_120 >= 14)
        {
            work->prim_rect.x = work->prim_rect.y = work->prim_rect.y - 65;
            work->prim_rect.w = work->prim_rect.h = work->prim_rect.h - 130;
        }
    }

    // probably an inline
    control = &work->control;
    GV_AddVec3(&control->mov, &control->step, &addition);

    result = AMissileCheckMessage();

    // this is probably also an inline
    if (work->control.field_58 <= 0 && !work->control.field_57)
    {
        if (++work->field_120 != 90 &&
            !GM_Target_8002E1B8(&control->mov, &addition,
                                work->control.map->index, &addition, 1) &&
                                !dword_8009F49C)
        {
            if (!result)
            {
                if (abs(work->control.mov.vx) <= 30000 &&
                    abs(work->control.mov.vy) <= 30000 &&
                    abs(work->control.mov.vz) <= 30000)
                {
                    return;
                }
            }
        }
    }

#ifdef VR_EXE
    rotator = work->control.mov;

    if (rotator.vx > 30000)
    {
        rotator.vx = 30000;
    }
    else if (rotator.vx < -30000)
    {
        rotator.vx = -30000;
    }

    if (rotator.vy > 30000)
    {
        rotator.vy = 30000;
    }
    else if (rotator.vy < -30000)
    {
        rotator.vy = -30000;
    }

    if (rotator.vz > 30000)
    {
        rotator.vz = 30000;
    }
    else if (rotator.vz < -30000)
    {
        rotator.vz = -30000;
    }

    DG_SetPos2(&rotator, &work->control.rot);
#endif

    if (!result)
    {
        ReadRotMatrix(&rotation);

        if (GM_GameStatus & (STATE_PADRELEASE | STATE_PADDEMO | STATE_DEMO) || GM_PlayerStatus & PLAYER_PAD_OFF)
        {
            blast = &blast_data_8009F4B8[7];
#ifdef VR_EXE
            if ((GM_GameStatus & STATE_PADDEMO) && !(GM_PlayerStatus & PLAYER_PAD_OFF) && !(GM_GameStatus & STATE_PADRELEASE))
            {
                blast = &blast_data_8009F4B8[3];
            }
#endif
        }
        else
        {
            blast = &blast_data_8009F4B8[3];
        }

        NewBlast(&rotation, blast);
    }

    amissile_alive_8009F490 = 0;
    GV_DestroyActor(&work->actor);
}

STATIC void AMissileDie(AMissileWork *work)
{
    DG_PRIM *prim;

    GM_FreeControl(&work->control);
    GM_FreeObject((OBJECT *)&work->body);

    prim = work->prim;

    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    if (target_800BDF00)
    {
        target_800BDF00 = 0;
    }

    amissile_alive_8009F490 = 0;
}


STATIC int AMissileGetResources(AMissileWork *work, MATRIX *world, int side)
{
    CONTROL *control = &work->control;
    OBJECT_NO_ROTS *body;
    DG_OBJS *objs;
    RECT *rect;
    DG_PRIM *prim;
    SVECTOR vector;
    int i;
    DG_TEX *tex;

    if (GM_InitControl(control, 0, 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlMatrix(control, world);
    GM_ConfigControlHazard(control, 100, 50, 50);

    body = &work->body;

    control->skip_flag |= CTRL_SKIP_NEAR_CHECK;
    control->field_59 = 8;

    GM_InitObjectNoRots(body, KMD_STN_FR, BODY_FLAG, 0);

    objs = body->objs;

    if (!objs)
    {
        return -1;
    }

    objs->world = *world;
    GM_ConfigObjectLight((OBJECT *)body, work->light);

    body->objs->objs[0].raise = -500;

    rect = &work->prim_rect;
    rect->x = rect->y = 30;
    rect->w = rect->h = 60;

    work->prim = prim = DG_GetPrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 4, 0, work->vertices, rect);

    if (!prim)
    {
        return -1;
    }

    DG_SetPos2(&control->mov, &control->rot);

    vector.vz = 0;
    vector.vx = 0;
    vector.vy = 500;

    for (i = 0; i < 4; i++)
    {
        DG_RotVector(&vector, &work->vertices[i], 1);
        vector.vy += 2000;
    }

    tex = DG_GetTexture(PCX_SOCOM_F);
    if (!tex)
    {
        return -1;
    }

    amissile_loader_helper_8006D1F4(&prim->packs[0]->poly_ft4, tex);
    amissile_loader_helper_8006D1F4(&prim->packs[1]->poly_ft4, tex);

    prim->world = DG_ZeroMatrix;
    DG_InvisiblePrim(prim);
    return 0;
}

/*---------------------------------------------------------------------------*/

GV_ACT *NewAMissile(MATRIX *world, int side)
{
    AMissileWork *work = (AMissileWork *)GV_NewActor(EXEC_LEVEL, sizeof(AMissileWork));

    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)&AMissileAct,
                         (GV_ACTFUNC)&AMissileDie, "amissile.c");

        if (AMissileGetResources(work, world, side) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->field_124 = 30;
        work->field_120 = 0;
        work->field_128 = 0;
        work->field_12C_svector = DG_ZeroVector;
    }

    return &work->actor;
}
