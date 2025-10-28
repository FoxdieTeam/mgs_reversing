#include "common.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "game/target.h"
#include "hind_bul.h"

extern SVECTOR s11d_800BB39C;
extern int s11d_dword_800D3318;
extern HindBulWork *s11d_dword_800D1F88;

#define SEGMENT_ATR (HZD_SEG_NO_PLAYER)

// Forward declarations
int s11d_hind_bul_800CB794(HindBulWork *work);
int s11d_hind_bul_800CBA5C(HZD_SEG *seg, HZD_SEG *seg2);
int s11d_hind_bul_800CBBA8(HindBulWork *work, int arg0, int arg1);

// Function 1: s11d_hind_bul_800CB888 - Update primitive world matrix (ENABLED for testing)
void s11d_hind_bul_800CB888(HindBulWork *work)
{
    SVECTOR sp10;
    SVECTOR sp18;
    short angle;

    sp10 = s11d_800BB39C;
    angle = ratan2(work->control.step.vx, work->control.step.vz);
    sp10.vy = angle;
    sp18 = sp10;
    RotMatrix(&sp10, &work->prim->world);
    work->prim->world.t[0] = work->control.mov.vx;
    work->prim->world.t[1] = work->control.mov.vy;
    work->prim->world.t[2] = work->control.mov.vz;
}

// Function 6: s11d_hind_bul_800CB794 - Hit detection (ENABLED for testing)
int s11d_hind_bul_800CB794(HindBulWork *work)
{
    int faint;
    TARGET *target;

    target = &work->target;
    faint = target->faint;

    if (faint == 0)
    {
        return 0;
    }

    GM_SeSet2(0, 0x3F, 0x6F);
    return 1;
}

/*
 * WIP: Remaining functions - work-in-progress decompiled code that doesn't compile yet.
 * Temporarily disabled to allow builds to proceed. The assembly versions are used instead.
 * TODO: Fix TARGET structure field names and missing prototypes before re-enabling.
 */
#if 0

// Function 2: s11d_hind_bul_800CBA14 - Die/cleanup function
void s11d_hind_bul_800CBA14(HindBulWork *work)
{
    DG_PRIM *prim;

    GM_FreeControl(&work->control);
    prim = work->prim;
    if (prim)
    {
        GM_FreeObject((OBJECT *)prim);
        DG_FreePrim(prim);
    }
}

// Function 3: s11d_hind_bul_800CB938 - Act function
void s11d_hind_bul_800CB938(HindBulWork *work)
{
    short pos_temp[3];

    GM_ActControl(&work->control);
    GM_ActObject((OBJECT *)work->prim);
    s11d_hind_bul_800CB888(work);

    if (s11d_hind_bul_800CB794(work) != 0)
    {
        work->enable--;
    }

    if (work->enable <= 0)
    {
        pos_temp[0] = work->pos.vx;
        pos_temp[1] = work->pos.vy;
        pos_temp[2] = work->pos.vz;
        GV_NearExp4V(pos_temp, pos_temp, 0xB5);
        GV_DestroyActor(&work->actor);
    }
}

// Function 4: s11d_hind_bul_800CBFD8 - Constructor
GV_ACT *s11d_hind_bul_800CBFD8(int arg0, int arg1, int arg2, int enable)
{
    HindBulWork *work;
    
    work = (HindBulWork *)GV_NewActor(5, sizeof(HindBulWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor,
                         s11d_hind_bul_800CB938,
                         s11d_hind_bul_800CBA14,
                         "hd_bul.c");
        if (s11d_hind_bul_800CBBA8(work, arg0, arg1) >= 0)
        {
            s11d_dword_800D1F88 = work;
            work->enable = enable;
            return &work->actor;
        }
        GV_DestroyActor(&work->actor);
    }
    return NULL;
}

// Function 5: s11d_hind_bul_800CBBA8 - Initialize bullet resources (STUB)
int s11d_hind_bul_800CBBA8(HindBulWork *work, int arg0, int arg1)
{
    CONTROL *control;
    TARGET *target;
    int i;

    control = &work->control;
    
    if (GM_InitControl(control, arg0, 0) < 0)
    {
        return -1;
    }
    
    GM_ConfigControlInterp(control, 4);
    GM_ConfigControlString(control, NULL, NULL);

    target = &work->target;
    GM_SetTarget(target, TARGET_POWER, ENEMY_SIDE, s11d_hind_bul_800CBA5C);
    GM_Target_8002DCCC(target, 7, 2, 0x10, 0, &s11d_800BB39C);
    
    target->field_2C_vec = control->mov;
    
    work->map = arg1;
    work->prim = (DG_PRIM *)GV_NewMemory(0, sizeof(DG_PRIM));
    
    if (!work->prim)
    {
        return -1;
    }
    
    // Initialize vertices array
    for (i = 0; i < 16; i++)
    {
        work->vertices[i] = s11d_800BB39C;
    }
    
    return 0;
}

// Function 7: s11d_hind_bul_800CBA5C - Line collision check (STUB)
int s11d_hind_bul_800CBA5C(HZD_SEG *seg, HZD_SEG *seg2)
{
    // TODO: Implement full collision check logic
    return 0;
}

// Function 8: s11d_hind_bul_800CBE4C - Bullet spawner (STUB)
int s11d_hind_bul_800CBE4C(HindBulWork *work, OBJECT *parent, int num_bullets)
{
    MATRIX *world;
    SVECTOR pos;
    CONTROL *control;
    int i;

    control = &work->control;
    world = &parent->objs->world;

    for (i = 0; i < num_bullets; i++)
    {
        DG_SetPos(world);
        DG_PutVector(&work->vertices[i], &pos, 1);

        control->mov = pos;
        control->step.vx = 0;
        control->step.vy = 0;
        control->step.vz = 0;

        s11d_hind_bul_800CBBA8(work, work->map, 0);
    }

    return 0;
}

#endif /* WIP code disabled */

// Enabled function - s11d_hind_bul_800CBA14 - Die/cleanup function
void s11d_hind_bul_800CBA14(HindBulWork *work)
{
    DG_PRIM *prim;

    GM_FreeControl(&work->control);
    prim = work->prim;
    if (prim)
    {
        GM_FreeObject((OBJECT *)prim);
        DG_FreePrim(prim);
    }
}
