#include "libdg.h"
#include "common.h"
#include "game/game.h"

extern int DG_CurrentGroupID;

STATIC void DG_WriteObjClut(DG_OBJ *obj, int idx);
STATIC void DG_WriteObjClutUV(DG_OBJ *obj, int idx);
STATIC void DG_BoundIrTexture(DG_CHANL *chanl, int idx);

static inline void copy_bounding_box_to_spad(DG_BOUND *bounds)
{
    DG_BOUND *bounding_box = (DG_BOUND *)SCRPAD_ADDR;
    bounding_box->min.vx = bounds->min.vx;
    bounding_box->min.vy = bounds->min.vy;
    bounding_box->min.vz = bounds->min.vz;

    bounding_box->max.vx = bounds->max.vx;
    bounding_box->max.vy = bounds->max.vy;
    bounding_box->max.vz = bounds->max.vz;
}

static inline void set_svec_from_bounding_box(int i, SVECTOR *svec)
{
    svec->vx = i & 1 ? ((long *)SCRPAD_ADDR)[3] : ((long *)SCRPAD_ADDR)[0];
    svec->vy = i & 2 ? ((long *)SCRPAD_ADDR)[4] : ((long *)SCRPAD_ADDR)[1];
    svec->vz = i & 4 ? ((long *)SCRPAD_ADDR)[5] : ((long *)SCRPAD_ADDR)[2];
}

void DG_BoundStart(void)
{
    /* do nothing */
}

STATIC void DG_BoundObjs(DG_OBJS *objs, int idx, unsigned int flag, int in_bound_mode)
{
    int        i, i2, i3, a2, t0, a3, t1;
    int        bound_mode;
    int        n_models;
    int        n_bounding_box_vec;
    int        ret, extra;
    long      *test;
    DG_OBJ    *obj;
    DVECTOR   *dvec;
    SVECTOR   *svec;
    DG_VECTOR *vec3_1;
    DG_VECTOR *vec3_2;
    DG_BOUND  *mdl_bounds;

    n_models = objs->n_models;
    obj = (DG_OBJ *)&objs->objs;

    for (; n_models > 0; --n_models)
    {
        bound_mode = 0;
        if (in_bound_mode)
        {
            bound_mode = 2;
            if (flag & DG_FLAG_BOUND)
            {
                gte_SetRotMatrix(&obj->screen);
                gte_SetTransMatrix(&obj->screen);

                svec = (SVECTOR *)(SCRPAD_ADDR + 0x18);
                mdl_bounds = (DG_BOUND *)&obj->model->min;
                copy_bounding_box_to_spad(mdl_bounds);
                vec3_1 = (DG_VECTOR *)(SCRPAD_ADDR + 0x30);
                vec3_2 = (DG_VECTOR *)(SCRPAD_ADDR + 0x60);
                i = 9;

                while (i > 0)
                {
                    n_bounding_box_vec = 3;
                    do
                    {
                        set_svec_from_bounding_box(i, svec);
                        ++svec;
                        --i;
                        --n_bounding_box_vec;
                    } while (n_bounding_box_vec > 0);

                    svec = (SVECTOR *)(SCRPAD_ADDR + 0x18);
                    gte_stsxy3c(vec3_1);
                    gte_stsz3c(vec3_2);

                    gte_ldv3c((SVECTOR *)(SCRPAD_ADDR + 0x18));
                    vec3_1++;
                    vec3_2++;
                    gte_rtpt_b();
                }

                gte_stsxy3c(vec3_1);
                gte_stsz3c(vec3_2);

                // probably start of another inline func
                a2 = *(short *)(SCRPAD_ADDR + 0x3C);
                t0 = *(short *)(SCRPAD_ADDR + 0x3E);
                a3 = a2;
                t1 = t0;
                dvec = (DVECTOR *)(SCRPAD_ADDR + 0x3C);

                for (i2 = 7; i2 > 0; --i2)
                {
                    dvec++;
                    // loc_800187FC:
                    if (dvec->vx < a2)
                    {
                        a2 = dvec->vx;
                    }
                    else
                    {
                        if (a3 < dvec->vx)
                            a3 = dvec->vx;
                    }
                    if (dvec->vy < t0)
                    {
                        t0 = dvec->vy;
                    }
                    else
                    {
                        if (t1 < dvec->vy)
                            t1 = dvec->vy;
                    }
                }
                // loc_80018858
                // this seems ridiculous but was the only way it matched
                if ((a2 >= 0xA1) || (a3 < -0xA0) || (t0 >= 0x71) || (t1 < -0x70))
                {
                    extra = 0;
                }
                else
                {
                    ret = ((a3 >= 0xA1) || (a2 < -0xA0) || (t1 >= 0x71) || (t0 < -0x70)) ? 1 : 2;
                    test = (long *)(SCRPAD_ADDR + 0x6C);
                    i3 = 8;
                    while (i3 > 0)
                    {
                        --i3;
                        if (*test)
                        {
                            extra = ret;
                            goto END;
                        }
                        test++;
                    }
                    extra = 0;
                }
            END:
                ret = extra;
                bound_mode = ret;
            }
        }

        // loc_800188E4
        obj->bound_mode = bound_mode;
        if (bound_mode)
        {
            obj->free_count = 8;
            if (!obj->packs[idx])
            {
                int res = DG_MakeObjPacket(obj, idx, flag);
                if (res < 0)
                {
                    obj->bound_mode = 0;
                    if (flag & DG_FLAG_GBOUND)
                    {
                        objs->bound_mode = 0;
                        return;
                    }
                }
            }
        }
        else
        {
            if (obj->packs[idx])
            {
                --obj->free_count;
                if (obj->free_count <= 0)
                {
                    DG_FreeObjPacket(obj, idx);
                }
            }
        }
        obj++;
    }
}

void DG_BoundChanl(DG_CHANL *chanl, int idx)
{
    int          i, i2, i3, a2, t0, a3, t1;
    int          n_objs;
    int          bound_mode;
    DG_OBJS    **objs;
    int          local_group_id;
    DVECTOR     *dvec;
    SVECTOR     *svec;
    DG_VECTOR   *vec3_1;
    DG_VECTOR   *vec3_2;
    DG_BOUND    *mdl_bounds;
    int          n_bounding_box_vec;
    long        *test;
    unsigned int flag;

    DG_Clip(&chanl->clip_rect, chanl->clip_distance);

    objs = chanl->mQueue;
    n_objs = chanl->mTotalObjectCount;
    local_group_id = DG_CurrentGroupID;

    for (; n_objs > 0; --n_objs)
    {
        DG_OBJS *current_objs = *objs;
        objs++;
        flag = current_objs->flag;

        bound_mode = 0;
        if (!(flag & DG_FLAG_INVISIBLE))
        {
            if (!current_objs->group_id || (current_objs->group_id & local_group_id))
            {
                bound_mode = 2;
                if (flag & DG_FLAG_GBOUND)
                {
                    gte_SetRotMatrix(&current_objs->objs->screen);
                    gte_SetTransMatrix(&current_objs->objs->screen);

                    svec = (SVECTOR *)(SCRPAD_ADDR + 0x18);
                    mdl_bounds = (DG_BOUND *)&current_objs->def->min;
                    copy_bounding_box_to_spad(mdl_bounds);
                    vec3_1 = (DG_VECTOR *)(SCRPAD_ADDR + 0x30);
                    vec3_2 = (DG_VECTOR *)(SCRPAD_ADDR + 0x60);
                    i = 9;

                    while (i > 0)
                    {
                        n_bounding_box_vec = 3;
                        do
                        {
                            set_svec_from_bounding_box(i, svec);
                            ++svec;
                            --i;
                            --n_bounding_box_vec;
                        } while (n_bounding_box_vec > 0);

                        svec = (SVECTOR *)(SCRPAD_ADDR + 0x18);
                        gte_stsxy3c(vec3_1);
                        gte_stsz3c(vec3_2);

                        gte_ldv3c((SVECTOR *)(SCRPAD_ADDR + 0x18));
                        vec3_1++;
                        vec3_2++;
                        gte_rtpt_b();
                    }

                    gte_stsxy3c(vec3_1);
                    gte_stsz3c(vec3_2);

                    // probably start of another inline func
                    a2 = *(short *)(SCRPAD_ADDR + 0x3C);
                    t0 = *(short *)(SCRPAD_ADDR + 0x3E);
                    a3 = a2;
                    t1 = t0;
                    dvec = (DVECTOR *)(SCRPAD_ADDR + 0x3C);

                    for (i2 = 7; i2 > 0; --i2)
                    {
                        dvec++;
                        if (dvec->vx < a2)
                        {
                            a2 = dvec->vx;
                        }
                        else
                        {
                            if (a3 < dvec->vx)
                                a3 = dvec->vx;
                        }
                        if (dvec->vy < t0)
                        {
                            t0 = dvec->vy;
                        }
                        else
                        {
                            if (t1 < dvec->vy)
                                t1 = dvec->vy;
                        }
                    }

                    if ((a2 >= 0xA1) || (a3 < -0xA0) || (t0 >= 0x71) || (t1 < -0x70))
                    {
                        bound_mode = 0;
                    }
                    else
                    {
                        bound_mode = ((a3 >= 0xA1) || (a2 < -0xA0) || (t1 >= 0x71) || (t0 < -0x70)) ? 1 : 2;
                        test = (long *)(SCRPAD_ADDR + 0x6C);
                        i3 = 8;
                        while (i3 > 0)
                        {
                            --i3;
                            if (*test)
                            {
                                goto END;
                            }
                            test++;
                        }
                        bound_mode = 0;
                    }
                END:
                }
            }
        }
        // loc_80018CE0:
        current_objs->bound_mode = bound_mode;
        DG_BoundObjs(current_objs, idx, flag, bound_mode);
    }

    DG_BoundIrTexture(chanl, idx);
}

void DG_BoundEnd(void)
{
    /* do nothing */
}

// Possibly a different file.

STATIC DG_TEX DG_UnknownTexture = {0};

/* Replace the CLUT for this model with a plain white one for thermal goggles */
STATIC void DG_WriteObjClut(DG_OBJ *obj, int idx)
{
    int       n_packs;
    POLY_GT4 *pPack = obj->packs[idx];
    short     val = 0x3FFF;
    if (pPack && pPack->clut != val)
    {
        while (obj)
        {
            n_packs = obj->n_packs;
            while (n_packs > 0)
            {
                pPack->clut = val;

                ++pPack;
                --n_packs;
            }

            obj = obj->extend;
        }
    }
}

/* Restore the CLUT for this model */
STATIC void DG_WriteObjClutUV(DG_OBJ *obj, int idx)
{
    unsigned short id;
    POLY_GT4      *pack;
    int            n_packs;
    short         *tex_ids;
    DG_TEX        *texture;
    unsigned short current_id;

    pack = obj->packs[idx];

    if (pack && pack->clut == 0x3FFF)
    {
        texture = &DG_UnknownTexture;
        id = 0;
        while (obj)
        {
            tex_ids = obj->model->materials;
            for (n_packs = obj->n_packs; n_packs > 0; --n_packs)
            {
                current_id = *tex_ids;
                tex_ids++;
                if ((current_id & 0xFFFF) != id)
                {
                    id = current_id;
                    texture = DG_GetTexture(id);
                }
                pack->clut = texture->clut;
                pack++;
            }
            obj = obj->extend;
        }
    }
}

// there must be a way to match this without the repetition
STATIC void DG_BoundIrTexture(DG_CHANL *chanl, int idx)
{
    DG_OBJS **queue;
    int       n_objects;
    DG_OBJS  *objs;
    DG_OBJ   *obj;
    int       n_models;

    queue = chanl->mQueue;
    if (GM_GameStatus & STATE_THERMG)
    {
        for (n_objects = chanl->mTotalObjectCount; n_objects > 0; n_objects--)
        {
            objs = *queue++;

            if (objs->flag & DG_FLAG_IRTEXTURE && objs->bound_mode != 0)
            {
                obj = objs->objs;

                for (n_models = objs->n_models; n_models > 0; n_models--)
                {
                    if (obj->bound_mode != 0)
                    {
                        DG_WriteObjClut(obj, idx);
                    }

                    obj++;
                }
            }
        }
    }
    else
    {
        for (n_objects = chanl->mTotalObjectCount; n_objects > 0; n_objects--)
        {
            objs = *queue++;

            if (objs->flag & DG_FLAG_IRTEXTURE && objs->bound_mode != 0)
            {
                obj = objs->objs;

                for (n_models = objs->n_models; n_models > 0; n_models--)
                {
                    DG_WriteObjClutUV(obj, idx);
                    obj++;
                }
            }
        }
    }
}
