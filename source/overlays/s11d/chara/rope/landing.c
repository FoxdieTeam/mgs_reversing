#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/vibrate.h"       // for NewPadVibration
#include "chara/snake/shadow.h" // for NewShadow

extern UnkCameraStruct gUnkCameraStruct_800B77B8;

extern void OpenCinemaScreen(int type, int time);
extern void CloseCinemaScreen(void);

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL      GV_ACTOR_LEVEL5

#define NUM_JOINT       16
#define MOTION_DATA     GV_StrCode("sne_11d2")
#define BODY_MODEL      GV_StrCode("snake")
#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND )

/*---------------------------------------------------------------------------*/

typedef struct _Work
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         body;
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT m_segs1[NUM_JOINT + 1];
    MOTION_SEGMENT m_segs2[NUM_JOINT + 1];
    SVECTOR        rots[NUM_JOINT];
    SVECTOR        adjust[NUM_JOINT];
    MATRIX         light[2];
    DG_PRIM       *shadow_prim;
    SVECTOR        shadow_vertices[4];
    void          *shadow;
    DG_PRIM       *prim;
    SVECTOR        vertices[32];
    int            level;
    int            state;
    int            commence;
    int            proc_id;
} Work;

static u_char s11d_dword_800C3348[] = {0x7F, 0x02, 0x00, 0x00};
static u_char s11d_dword_800C334C[] = {0xFF, 0x02, 0x00, 0x00};

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    int state;

    GM_ActMotion(&work->body);
    GM_ActControl(&work->control);
    work->control.mov.vy = work->body.height + work->level;
    GM_ActObject(&work->body);
    DG_GetLightMatrix(&work->control.mov, work->light);

    gUnkCameraStruct_800B77B8.eye = work->control.mov;
    gUnkCameraStruct_800B77B8.rotate2 = work->control.rot;
    gUnkCameraStruct_800B77B8.track = 4000;

    work->control.height = work->body.height;

    state = work->state;
    if (state >= 0)
    {
        work->state++;

        if (state == 0)
        {
            GM_GameStatus |= ( STATE_PAUSE_ONLY | STATE_PADRELEASE );
            GCL_ExecProc(work->commence, NULL);
        }

        work->shadow_prim->world.t[0] = work->control.mov.vx;
        work->shadow_prim->world.t[1] = work->control.mov.vy;
        work->shadow_prim->world.t[2] = work->control.mov.vz;

        if (state > 16)
        {
            work->shadow_prim->world.t[1] = work->level;
        }
        else
        {
            work->shadow_prim->world.t[1] = -13500;
        }

        if (state < 16)
        {
            work->prim->world.t[0] = work->body.objs->objs[4].world.t[0];
            work->prim->world.t[1] = work->body.objs->objs[4].world.t[1];
            work->prim->world.t[2] = work->body.objs->objs[4].world.t[2];
        }

        if (state == 8)
        {
            GM_SeSet2(0, 63, 128);
        }

        if (state == 24)
        {
            GM_SeSet2(0, 63, 129);
            NewPadVibration(s11d_dword_800C3348, 1);
            NewPadVibration(s11d_dword_800C334C, 2);
        }

        if (work->body.is_end)
        {
            work->m_ctrl.info1.field_14 = 0;
            work->m_ctrl.interp = 15;
            GCL_ExecProc(work->proc_id, NULL);
            work->state = -1;
        }
    }
}

/*---------------------------------------------------------------------------*/

static void Die(Work *work)
{
    CloseCinemaScreen();

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreePrim(work->shadow_prim);
    GM_FreePrim(work->prim);

    if (work->shadow)
    {
        GV_DestroyOtherActor(work->shadow);
    }

    GM_GameStatus &= ~( STATE_PAUSE_ONLY | STATE_PADRELEASE );
}

/*---------------------------------------------------------------------------*/

static int InitShadow(Work *work)
{
    DG_PRIM  *prim;
    DG_TEX   *tex;
    int       i;
    POLY_FT4 *packs;
    SVECTOR  *vert;

    work->shadow_prim = prim = GM_MakePrim(DG_PRIM_POLY_FT4, 1, work->shadow_vertices, NULL);
    if (prim == NULL)
    {
        return -1;
    }

    tex = DG_GetTexture(GV_StrCode("shadow"));
    if (tex == NULL)
    {
        return -1;
    }

    for (i = 0; i < 2; i++)
    {
        packs = prim->packs[i];
        setPolyFT4(packs);
        setSemiTrans(packs, 1);
        setRGB0(packs, 72, 72, 72);
        DG_SetPacketTexture4(packs, tex);
    }

    vert = work->shadow_vertices;
    for (i = 0; i < 4; i++)
    {
        *vert = DG_ZeroVector;

        if (i & 1)
        {
            vert->vx = 400;
        }
        else
        {
            vert->vx = -400;
        }

        if (i & 2)
        {
            vert->vz = 400;
        }
        else
        {
            vert->vz = -400;
        }


        vert++;
    }

    prim->world = DG_ZeroMatrix;
    prim->raise = 2000;
    return 0;
}

static int InitWire(Work *work)
{
    SVECTOR  *vert;
    DG_PRIM  *prim;
    DG_TEX   *tex;
    int       i, j, k;
    POLY_FT4 *packs;
    int       height;

    vert = work->vertices;

    work->prim = prim = GM_MakePrim(DG_PRIM_POLY_FT4, 8, work->vertices, NULL);
    if (prim == NULL)
    {
        return -1;
    }

    prim->group_id = 0;

    tex = DG_GetTexture(GV_StrCode("wire"));
    if (tex == NULL)
    {
        return -1;
    }

    for (i = 0; i < 2; i++)
    {
        packs = prim->packs[i];
        height = -1000;

        for (j = 0; j < 8; j++, packs++)
        {
            setPolyFT4(packs);
            setSemiTrans(packs, 1);
            setRGB0(packs, 48, 48, 48);
            DG_SetPacketTexture4(packs, tex);

            if (i == 0)
            {
                for (k = 0; k < 4; k++)
                {
                    vert->vz = 0;
                    vert->vy = (k & 2) ? height : height - 500;
                    vert->vx = (k & 1) ? 34 : -34;
                    vert++;
                }

                height += 500;
            }
        }
    }

    prim->world = DG_ZeroMatrix;
    return 0;
}

static int GetResources(Work *work, int name, int where)
{
    SVECTOR  indices;
    CONTROL *control;
    OBJECT  *body;

    control = &work->control;
    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));
    GM_ConfigControlHazard(control, 0, -2, -2);

    body = &work->body;
    GM_InitObject(body, BODY_MODEL, BODY_FLAG, MOTION_DATA);

    GM_ConfigObjectJoint(body);
    GM_ConfigMotionControl(body, &work->m_ctrl, MOTION_DATA, work->m_segs1, work->m_segs2, control, work->rots);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectAction(body, 0, 0, 0);

    if (GCL_GetOption('e'))
    {
        work->proc_id = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->proc_id = -1;
    }

    if (GCL_GetOption('c'))
    {
        work->commence = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->commence = -1;
    }

    if (GCL_GetOption('l'))
    {
        work->level = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->level = -16500;
    }

    if (InitShadow(work) < 0)
    {
        return -1;
    }

    if (InitWire(work) < 0)
    {
        return -1;
    }

    indices.vx = 0;
    indices.vy = 6;
    indices.vz = 12;
    indices.pad = 15;
    work->shadow = NewShadow(control, body, indices);

    work->state = 0;

    OpenCinemaScreen(1, 30000);
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewLanding(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "landing.c");

        if (GetResources(work, name, where) >= 0)
        {
            return work;
        }

        GV_DestroyActor(work);
    }

    return NULL;
}
