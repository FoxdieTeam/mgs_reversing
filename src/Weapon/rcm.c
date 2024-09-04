#include "rcm.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Game/map.h"
#include "libdg/libdg.h"
#include "psyq.h"
#include "Game/object.h"
#include "Bullet/rmissile.h"
#include "Game/linkvarbuf.h"
#include "SD/g_sound.h"

// nikita

extern int   GM_CurrentMap_800AB9B0;
extern short GM_Magazine_800AB9EC;
extern short GM_MagazineMax_800ABA2C;

extern SVECTOR GM_PlayerPosition_800ABA10;

extern int DG_CurrentGroupID_800AB968;

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern int              GV_Clock_800AB920;

SVECTOR stru_800AB870 = {-100, -800, 80, 0};
RECT    rect_800AB878 = {100, 100, 200, 200};
SVECTOR svector_800AB880 = {-50, -300, 100, 0};

void rcm_loader_helper_80066AF8(POLY_FT4 *poly, DG_TEX *texture)
{
    u_char offx;
    u_char offy;
    u_char offx_width;
    u_char offy_height;

    setPolyFT4(poly);
    setSemiTrans(poly, 1);

    offx = texture->off_x;
    offx_width = offx + texture->w;

    offy = texture->off_y;
    offy_height = offy + texture->h;

    setUV4(poly, offx, offy, offx_width, offy, offx, offy_height, offx_width, offy_height);
    poly->tpage = texture->tpage;
    poly->clut = texture->clut;
}

/**
 * @brief Adjusts the RGB values for the Nikita launcher's activation light.
 *
 * This function controls the blinking effect of the Nikita launcher's light
 * based on the provided flags. It modifies the brightness of the light
 * to create a fading effect when the action button is pressed.
 *
 * @param work Pointer to the RcmWork structure containing missile data.
 * @param flags Integer flags indicating the current state or input.
 */
void rcm_act_helper_80066B58(RcmWork *work, int flags)
{
    int               curRgb; // $a2
    union Prim_Union *pPrim;  // $v0

    curRgb = work->field_60_rgb;
    if ((flags & 1) != 0)
    {
        if (curRgb <= 0)
        {
            curRgb = 256;
        }
        // fade the light out
        curRgb = curRgb - 8;
    }
    else
    {
        // light off if the button is not pressed
        curRgb = 0;
    }
    work->field_60_rgb = curRgb;

    curRgb = curRgb - 64;

    if (curRgb < 0)
    {
        curRgb = 0;
    }
    pPrim = work->field_5C_pPrim->packs[GV_Clock_800AB920];
    pPrim->line_g2.r0 = curRgb;
    pPrim->line_g2.g0 = curRgb;
    pPrim->line_g2.b0 = curRgb;
}

/**
 * @brief Handles the behavior of the Nikita launcher.
 *
 * @param work The Nikita actor data.
 */
void rcm_act_80066BC0(RcmWork *work)
{
    int    mapBit;         // $a1
    int    p_flags;        // $s0
    int    ammo_count; // $s2
    MATRIX mt1;
    MATRIX mt2;

    SVECTOR vec1; // [sp+50h] [-8h] BYREF

    mapBit = work->control->map->index;

    DG_GroupObjs(work->f20_obj.objs, DG_CurrentGroupID_800AB968);
    DG_GroupPrim(work->field_5C_pPrim, DG_CurrentGroupID_800AB968);

    GM_CurrentMap_800AB9B0 = mapBit;

    if ((work->field_48_pParent->objs->flag & DG_FLAG_INVISIBLE) || (GM_PlayerStatus_800ABA50 & PLAYER_CB_BOX))
    {
        DG_InvisibleObjs( work->f20_obj.objs );
        DG_InvisiblePrim( work->field_5C_pPrim );
    }
    else
    {
        DG_VisibleObjs( work->f20_obj.objs );
        DG_VisiblePrim( work->field_5C_pPrim );
    }

    // p_flags store the state of the action button
    // to check if the player pressed and released the button
    p_flags = *work->field_50_pFlags;
    // update the blinking light
    rcm_act_helper_80066B58(work, p_flags);

    ammo_count = GM_Weapons[WEAPON_NIKITA];
    // if no ammo and the button is released, play a sound effect
    if (!ammo_count && (p_flags & 2))
    {
        GM_SeSet_80032858(&work->control->mov, SE_KARASHT);
        GM_SetNoise(5, 2, &work->control->mov);
        return;
    }

    if (ammo_count > 0 && (p_flags & 2))
    {
        // add a delay before firing the missile
        // to avoid hitting the player
        work->field_58_counter = 6;
        return;
    }
    if (work->field_58_counter)
    {
        work->field_58_counter--;
        if (work->field_58_counter < 2)
        {
            work->field_58_counter = 0;

            vec1.vx = -1024;
            vec1.vz = 0;
            vec1.vy = work->control->rot.vy;

            RotMatrixYXZ(&vec1, &mt1);
            DG_SetPos(&work->field_48_pParent->objs->objs[work->field_4C_obj_idx].world);
            DG_MovePos(&stru_800AB870);
            ReadRotMatrix(&mt2);

            mt2.t[1] = GM_PlayerPosition_800ABA10.vy + 320;

            mt1.t[0] = mt2.t[0];
            mt1.t[1] = mt2.t[1];
            mt1.t[2] = mt2.t[2];

            if (NewRMissile_8006D124(&mt1, work->field_54_whichSide))
            {
                GM_Weapons[WEAPON_NIKITA] = --ammo_count;
                GM_SeSet_80032858(&work->control->mov, SE_MISSILE_FIRED);
                GM_SetNoise(100, 2, &work->control->mov);
            }
        }
    }
}

/**
 * @brief Frees resources associated with the Nikita launcher.
 *
 * @param work The Nikita actor data.
 */
void rcm_kill_80066E68(RcmWork *work)
{
    DG_PRIM *prim;

    GM_FreeObject_80034BF8((OBJECT *)&work->f20_obj);
    prim = work->field_5C_pPrim;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

/**
 * @brief Loads resources for the Nikita launcher.
 *
 * @param actor The RcmWork structure to initialize.
 * @param object The parent OBJECT structure.
 */
int rcm_loader_80066EB0(RcmWork *actor, OBJECT *object, int unit)
{
    DG_PRIM        *pNewPrim;
    DG_TEX         *pTexture;
    OBJECT_NO_ROTS *obj;

    obj = &actor->f20_obj;
    GM_InitObjectNoRots_800349B0(obj, GV_StrCode("nikita"), 109, 0);
    if (!obj->objs)
    {
        return -1;
    }

    GM_ConfigObjectRoot_80034C5C((OBJECT *)obj, object, unit);

    pNewPrim = DG_GetPrim(1042, 1, 0, &svector_800AB880, &rect_800AB878);
    actor->field_5C_pPrim = pNewPrim;

    if (pNewPrim)
    {
        pTexture = DG_GetTexture(GV_StrCode("rcm_l"));
        if (pTexture)
        {
            rcm_loader_helper_80066AF8(&pNewPrim->packs[0]->poly_ft4, pTexture);
            rcm_loader_helper_80066AF8(&pNewPrim->packs[1]->poly_ft4, pTexture);
            pNewPrim->root = &object->objs->objs[unit].world;
            return 0;
        }
    }

    return -1;
}

/**
 * @brief Creates a new Nikita launcher actor.
 *
 * @param pCtrl The control structure for the Nikita launcher.
 * @param parent_obj The parent OBJECT structure.
 * @param num_parent The parent object index.
 * @param pFlags Pointer to flags indicating Nikita state.
 * @param whichSide Indicates which side the Nikita is on.
 * @return GV_ACT* Returns a pointer to the new actor.
 */
GV_ACT *NewRCM_80066FF0(CONTROL *pCtrl, OBJECT *parent_obj, int num_parent, unsigned int *pFlags, int whichSide)
{
    RcmWork *rcm;
    int      loadResult;

    rcm = (RcmWork *)GV_NewActor(6, sizeof(RcmWork));
    if (rcm != 0)
    {
        GV_SetNamedActor(&rcm->actor,
                         (TActorFunction)rcm_act_80066BC0,
                         (TActorFunction)rcm_kill_80066E68,
                         "rcm.c");

        loadResult = rcm_loader_80066EB0(rcm, parent_obj, num_parent);

        if (loadResult < 0)
        {
            GV_DestroyActor(&rcm->actor);
            return 0;
        }

        rcm->control = pCtrl;
        rcm->field_48_pParent = parent_obj;
        rcm->field_4C_obj_idx = num_parent;
        rcm->field_50_pFlags = pFlags;
        rcm->field_54_whichSide = whichSide;
        rcm->field_60_rgb = 0;
        rcm->field_58_counter = 0;
    }
    GM_MagazineMax_800ABA2C = 0;
    GM_Magazine_800AB9EC = 0;
    return &rcm->actor;
}
