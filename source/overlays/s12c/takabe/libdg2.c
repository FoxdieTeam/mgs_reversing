#include "common.h"
#include "inline_n.h"
#include "inline_x.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

// Modified versions of functions from libdg

extern int s12c_dword_800DA414;
extern int s12c_dword_800DA418;
extern int s12c_dword_800DA41C;
extern int s12c_dword_800DA420;
extern int s12c_dword_800DA424;
extern int s12c_800DA428;
extern int s12c_800DA42C;
extern int s12c_800DA430;
extern int s12c_800DA434;

short SECTION("overlay.bss") s12c_800DA440[768];
short SECTION("overlay.bss") * s12c_800DAA40;
short SECTION("overlay.bss") * s12c_800DAA44;
short SECTION("overlay.bss") * s12c_800DAA48;
short SECTION("overlay.bss") * s12c_800DAA4C;

extern int           DG_CurrentGroupID;
extern unsigned int *ptr_800B1400[256];
extern short         DG_ClipMin[2];
extern short         DG_ClipMax[2];

void s12c_800D497C(int arg0, int arg1)
{
    short *iter;
    int    i;

    s12c_800DAA40 = s12c_800DA440;
    s12c_800DAA44 = s12c_800DA440 + 256;
    s12c_800DAA48 = s12c_800DA440 + 512;

    s12c_800DA428 = arg0;
    s12c_800DA434 = arg1;
    s12c_800DA42C = arg1;
    s12c_800DA430 = arg0 + arg1;

    iter = s12c_800DAA44;
    for (i = s12c_800DA428; i < s12c_800DA430; i++)
    {
        *iter++ = ((i - s12c_800DA428) * 4096) / s12c_800DA434;
    }

    for (i = 255 - s12c_800DA434; i > 0; i--)
    {
        *iter++ = 4096;
    }

    iter = s12c_800DAA40;
    for (i = 256; i > 0; i--)
    {
        *iter++ = 0;
    }

    iter = s12c_800DAA48;
    for (i = 256; i > 0; i--)
    {
        *iter++ = 4096;
    }

    s12c_800DAA4C = s12c_800DAA44 - arg0;
}

void s12c_800D4AB4(int scale)
{
    if (scale > 255)
    {
        scale = 255;
    }

    s12c_800DA428 = scale;

    if ((scale + s12c_800DA42C) > 255)
    {
        s12c_800DA434 = 255 - scale;
    }
    else
    {
        s12c_800DA434 = s12c_800DA42C;
    }

    s12c_800DA430 = scale + s12c_800DA434;
    s12c_800DAA4C = s12c_800DAA44 - scale;
}

typedef struct _SCRATCHPAD_UNK
{
    unsigned int **buf;
    unsigned int  *ot;
    int            len;
    int            unkC;
    int            unk10;
    int            unk14;
    void          *unk18;
    short         *unk1C;
} SCRATCHPAD_UNK;

// TODO: fix this
// clang-format off
#define gte_ldrgb_s0( r0 ) __asm__ volatile (                   \
        "lwc2   $6,  4( %0 )"                                   \
        :                                                       \
        : "r"( r0 ) )

#define gte_ldrgb_s1( r0 ) __asm__ volatile (                   \
        "lwc2   $6, 12( %0 )"                                   \
        :                                                       \
        : "r"( r0 ) )

#define gte_ldrgb_s2( r0 ) __asm__ volatile (                   \
        "lwc2   $6, 20( %0 )"                                   \
        :                                                       \
        : "r"( r0 ) )

#define gte_ldrgb_s3( r0 ) __asm__ volatile (                   \
        "lwc2   $6, 28( %0 )"                                   \
        :                                                       \
        : "r"( r0 ) )

#define gte_ldrgb_f0( r0 ) __asm__ volatile (                   \
        "lwc2   $22,  4( %0 )"                                  \
        :                                                       \
        : "r"( r0 )                                             \
        : "memory" )

#define gte_ldrgb_f1( r0 ) __asm__ volatile (                   \
        "lwc2   $20, 12( %0 )"                                  \
        :                                                       \
        : "r"( r0 )                                             \
        : "memory" )

#define gte_ldrgb_f2( r0 ) __asm__ volatile (                   \
        "lwc2   $21, 20( %0 )"                                  \
        :                                                       \
        : "r"( r0 )                                             \
        : "memory" )

#define gte_ldrgb_f3( r0 ) __asm__ volatile (                   \
        "lwc2   $22, 28( %0 )"                                  \
        :                                                       \
        : "r"( r0 )                                             \
        : "memory" )

#define gte_ldrgb_f1_t( r0 ) __asm__ volatile (                 \
        "lwc2   $20, 16( %0 )"                                  \
        :                                                       \
        : "r"( r0 )                                             \
        : "memory" )

#define gte_ldrgb_f2_t( r0 ) __asm__ volatile (                 \
        "lwc2   $21, 28( %0 )"                                  \
        :                                                       \
        : "r"( r0 )                                             \
        : "memory" )

#define gte_ldrgb_f3_t( r0 ) __asm__ volatile (                 \
        "lwc2   $22, 40( %0 )"                                  \
        :                                                       \
        : "r"( r0 )                                             \
        : "memory" )

#define gte_strgb_s2_t( r0 ) __asm__ volatile (                 \
        "swc2   $20, 16( %0 );"                                 \
        "swc2   $21, 28( %0 )"                                  \
        :                                                       \
        : "r"( r0 )                                             \
        : "memory" )

#define gte_strgb_s3_t( r0 ) __asm__ volatile (                 \
        "swc2   $20, 16( %0 );"                                 \
        "swc2   $21, 28( %0 );"                                 \
        "swc2   $22, 40( %0 )"                                  \
        :                                                       \
        : "r"( r0 )                                             \
        : "memory" )

#define gte_strgb_s0( r0 ) __asm__ volatile (                   \
        "swc2   $22,  4( %0 )"                                  \
        :                                                       \
        : "r"( r0 )                                             \
        : "memory" )

#define gte_strgb_s1( r0 ) __asm__ volatile (                   \
        "swc2   $22, 12( %0 )"                                  \
        :                                                       \
        : "r"( r0 )                                             \
        : "memory" )

#define gte_strgb_s2( r0 ) __asm__ volatile (                   \
        "swc2   $20, 12( %0 );"                                 \
        "swc2   $21, 20( %0 )"                                  \
        :                                                       \
        : "r"( r0 )                                             \
        : "memory" )

#define gte_strgb_s3( r0 ) __asm__ volatile (                   \
        "swc2   $20, 12( %0 );"                                 \
        "swc2   $21, 20( %0 );"                                 \
        "swc2   $22, 28( %0 )"                                  \
        :                                                       \
        : "r"( r0 )                                             \
        : "memory" )

#define gte_strgb_s4( r0 ) __asm__ volatile (                   \
        "swc2   $22, 40( %0 )"                                  \
        :                                                       \
        : "r"( r0 )                                             \
        : "memory" )
// clang-format on

void s12c_800D4B2C(SCRATCHPAD_UNK *scratch, P_TAG *buffer, int p)
{
}

void s12c_800D4B34(SCRATCHPAD_UNK *scratch, P_TAG *buffer, int p)
{
    gte_strgb_s0(scratch->unk18);
    gte_lddp(p);
    gte_ldrgb_s0(buffer);
    scratch->unk18 = buffer;
    gte_dpcs_b();
}

void s12c_800D4B5C(SCRATCHPAD_UNK *scratch, P_TAG *buffer, int p)
{
    int color;

    gte_strgb_s0(scratch->unk18);
    gte_lddp(p);
    gte_ldrgb_s1(buffer);
    scratch->unk18 = buffer;
    gte_nop();
    gte_dpcs();
    color = LLOAD(&buffer->r0);
    gte_strgb_s1(buffer);
    gte_ldrgb(color);
    gte_dpcs();
}

void s12c_800D4BA4(SCRATCHPAD_UNK *scratch, P_TAG *buffer, int p)
{
    int color;

    gte_strgb_s0(scratch->unk18);
    gte_lddp(p);
    gte_ldrgb_f1(buffer);
    gte_ldrgb_f2(buffer);
    scratch->unk18 = buffer;
    gte_nop();
    gte_dpct();
    color = LLOAD(&buffer->r0);
    gte_strgb_s2(buffer);
    gte_ldrgb(color);
    gte_dpcs();
}

void s12c_800D4BF4(SCRATCHPAD_UNK *scratch, P_TAG *buffer, int p)
{
    int color;

    gte_strgb_s0(scratch->unk18);
    gte_lddp(p);
    gte_ldrgb_f1(buffer);
    gte_ldrgb_f2(buffer);
    gte_ldrgb_f3(buffer);
    scratch->unk18 = buffer;
    gte_nop();
    gte_dpct();
    color = LLOAD(&buffer->r0);
    gte_strgb_s3(buffer);
    gte_ldrgb(color);
    gte_dpcs();
}

void s12c_800D4C4C(SCRATCHPAD_UNK *scratch, P_TAG *buffer, int p)
{
    int color;

    gte_strgb_s0(scratch->unk18);
    gte_lddp(p);
    gte_ldrgb_f1_t(buffer);
    gte_ldrgb_f2_t(buffer);
    scratch->unk18 = buffer;
    gte_nop();
    gte_dpct();
    color = LLOAD(&buffer->r0);
    gte_strgb_s2_t(buffer);
    gte_ldrgb(color);
    gte_dpcs();
}

void s12c_800D4C9C(SCRATCHPAD_UNK *scratch, P_TAG *buffer, int p)
{
    int color;

    gte_strgb_s0(scratch->unk18);
    gte_lddp(p);
    gte_ldrgb_f1_t(buffer);
    gte_ldrgb_f2_t(buffer);
    gte_ldrgb_f3_t(buffer);
    scratch->unk18 = buffer;
    gte_nop();
    gte_dpct();
    color = LLOAD(&buffer->r0);
    gte_strgb_s3_t(buffer);
    gte_ldrgb(color);
    gte_dpcs();
}

void *fog_prim_funcs_800C347C[] = {
    s12c_800D4B2C, // LINE_F2
    s12c_800D4B34, // LINE_F3
    s12c_800D4B34, // LINE_F4
    s12c_800D4B34, // LINE_G2
    s12c_800D4B5C, // LINE_G3
    s12c_800D4BA4, // LINE_G4
    s12c_800D4BF4, // SPRT
    s12c_800D4B34, // SPRT_16
    s12c_800D4B34, // SPRT_8
    s12c_800D4B34, // TILE
    s12c_800D4B34, // TILE_16
    s12c_800D4B34, // TILE_8
    s12c_800D4B34, // TILE_1
    s12c_800D4B34, // POLY_F3
    s12c_800D4B34, // POLY_F4
    s12c_800D4B34, // POLY_G3
    s12c_800D4BA4, // POLY_G4
    s12c_800D4BF4, // POLY_FT3
    s12c_800D4B34, // POLY_FT4
    s12c_800D4B34, // POLY_GT3
    s12c_800D4C4C, // POLY_GT4
    s12c_800D4C9C, s12c_800D4B2C, s12c_800D4B2C, s12c_800D4B2C, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
};

static inline SCRATCHPAD_UNK *get_scratch(void)
{
    return (SCRATCHPAD_UNK *)SCRPAD_ADDR;
}

void s12c_800D4CF4(unsigned int *ot)
{
    SCRATCHPAD_UNK *scratch;
    unsigned int  **buf;
    int             i;
    unsigned int   *tag;
    unsigned int    val;
    unsigned int   *next;

    scratch = get_scratch();
    scratch->unkC = s12c_800DA428;
    scratch->unk10 = s12c_800DA430;
    scratch->unk14 = s12c_800DA434;

    buf = scratch->buf;
    for (i = 256; i > 0; i--)
    {
        tag = *buf++;

        while (tag != NULL)
        {
            val = *tag;
            next = &ot[val >> 24];
            *tag = *next | 0x0C000000;
            *next = (unsigned int)tag;
            tag = (unsigned int *)(val & 0xFFFFFF);
        }
    }
}

void *s12c_800D4D8C(union Prim_Union *buffer, int n_prims, int size, void (*callback)(void *, void *, int))
{
    unsigned int *ot;
    int          *currentOt;
    int           len;
    int           idx, idx2;

    int *scratch;
    scratch = (int *)SCRPAD_ADDR;

    ot = (unsigned int *)scratch[1];
    len = scratch[2];

    while (--n_prims >= 0)
    {
        idx = buffer->u16_access[0];
        if (idx > 0)
        {
            idx -= len;
            if (idx < 0)
            {
                idx = 0;
            }

            idx >>= 8;
            idx2 = idx - scratch[3];

            if (idx < scratch[4])
            {
                if (idx2 >= 0)
                {
                    callback(scratch, buffer, ((short *)scratch[7])[idx2]);
                }

                currentOt = &ot[idx];

                // Not quite addPrim()
                buffer->s32_access[0] = (buffer->s32_access[0] & 0xFF000000) | *currentOt;
                *currentOt = (int)(buffer)&0xFFFFFF;
            }
        }

        buffer = (union Prim_Union *)((char *)buffer + size);
    }

    return buffer;
}

void FogSortChanl_800D4E98(DG_CHANL *chanl, int idx)
{
    SCRATCHPAD_UNK *scratch;
    int             mask;
    int             group_id;
    void          **queue;
    int             i;
    DG_PRIM        *prim;
    int             type;

    scratch = get_scratch();
    scratch->buf = ptr_800B1400;
    scratch->ot = (unsigned int *)chanl->ot[idx] + 1;

    s12c_800D4CF4(scratch->ot);

    mask = 0x1F;
    if (GV_PauseLevel != 0)
    {
        mask = 0;
    }

    gte_ldfcdir(0, 0, 0);

    scratch->unk18 = (void *)0x1F800020;
    scratch->unk1C = s12c_800DAA44;

    group_id = DG_CurrentGroupID;

    queue = (void **)&chanl->mQueue[chanl->mFreePrimCount];
    for (i = chanl->mTotalQueueSize - chanl->mFreePrimCount; i > 0; i--)
    {
        prim = *queue++;
        type = prim->type;

        if (type & DG_PRIM_INVISIBLE)
        {
            continue;
        }

        if ((prim->group_id != 0) && !(prim->group_id & group_id))
        {
            continue;
        }

        // TODO: clean up
        ((SCRATCHPAD_UNK *)SCRPAD_ADDR)->len = prim->field_2E_k500;

        type = (type + 1) & mask;
        s12c_800D4D8C(prim->packs[idx], prim->n_prims, prim->psize,
                      fog_prim_funcs_800C347C[type]);
    }

    gte_strgb_s0(*(void **)0x1F800018);
}

static inline void copy_bounding_box_to_spad(DG_Bounds *bounds)
{
    DG_Bounds *bounding_box = (DG_Bounds *)SCRPAD_ADDR;
    bounding_box->max.vx = bounds->max.vx;
    bounding_box->max.vy = bounds->max.vy;
    bounding_box->max.vz = bounds->max.vz;

    bounding_box->min.vx = bounds->min.vx;
    bounding_box->min.vy = bounds->min.vy;
    bounding_box->min.vz = bounds->min.vz;
}

static inline void set_svec_from_bounding_box(int i, SVECTOR *svec)
{
    svec->vx = i & 1 ? ((long *)SCRPAD_ADDR)[3] : ((long *)SCRPAD_ADDR)[0];
    svec->vy = i & 2 ? ((long *)SCRPAD_ADDR)[4] : ((long *)SCRPAD_ADDR)[1];
    svec->vz = i & 4 ? ((long *)SCRPAD_ADDR)[5] : ((long *)SCRPAD_ADDR)[2];
}

void DG_BoundObjs_800D5010(DG_OBJS *objs, int idx, unsigned int flag, int in_bound_mode)
{
    int        i, i2, i3, a2, t0, a3, t1;
    int        bound_mode, bound_mode2, bound_mode3;
    int        n_models;
    int        n_bounding_box_vec;
    DG_OBJ    *obj;
    DVECTOR   *dvec;
    SVECTOR   *svec;
    DG_VECTOR *vec3_1;
    DG_VECTOR *vec3_2;
    DG_Bounds *mdl_bounds;

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
                mdl_bounds = (DG_Bounds *)&obj->model->min;
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

                if (((a2 > *(short *)(SCRPAD_ADDR + 0x90)) || (a3 < *(short *)(SCRPAD_ADDR + 0x94)) ||
                     (t0 > *(short *)(SCRPAD_ADDR + 0x92)) || (t1 < *(short *)(SCRPAD_ADDR + 0x96))))
                {
                    bound_mode3 = 0;
                    goto END;
                }
                else
                {

                    bound_mode2 = ((a3 > *(short *)(SCRPAD_ADDR + 0x90)) || (a2 < *(short *)(SCRPAD_ADDR + 0x94)) ||
                                   (t1 > *(short *)(SCRPAD_ADDR + 0x92)) || (t0 < *(short *)(SCRPAD_ADDR + 0x96)))
                                      ? 1
                                      : 2;
                    if (*(int *)(SCRPAD_ADDR + 0x98) & 0x2)
                    {
                        int   var_t2_2;
                        int   i3, t1, t0;
                        long *test;
                        var_t2_2 = 0;
                        test = (long *)(SCRPAD_ADDR + 0x6C);
                        t1 = 0;
                        t0 = 0xFFFF;
                        i3 = 8;
                        while (i3 > 0)
                        {

                            if (*test < t0)
                            {
                                t0 = *test;
                            }
                            if (t1 < *test)
                            {
                                t1 = *test;
                            }
                            if (*test)
                            {
                                var_t2_2 = bound_mode2;
                            }
                            test++;
                            i3--;
                        }

                        if (var_t2_2)
                        {
                            if (t0 / 256 < s12c_800DA430)
                            {
                                if (t1 / 256 >= s12c_800DA428)
                                {
                                    bound_mode3 = var_t2_2 | 4;
                                }
                                else
                                {
                                    bound_mode3 = var_t2_2;
                                }
                            }
                            else
                            {
                                bound_mode3 = 0;
                            }
                        }
                        else
                        {
                            bound_mode3 = 0;
                        }
                    }
                    else
                    {
                        long *test;
                        test = (long *)(SCRPAD_ADDR + 0x6C);
                        i3 = 8;
                        while (i3 > 0)
                        {
                            --i3;
                            if (*test)
                            {
                                bound_mode3 = bound_mode2;
                                goto END;
                            }
                            test++;
                        }
                        bound_mode3 = 0;
                    }
                END:
                    bound_mode = bound_mode3;
                }
            }
        }

        // loc_800188E4
        obj->bound_mode = (obj->bound_mode & 0x18) | bound_mode;
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
            obj->bound_mode = 0;
        }
        obj++;
    }
}

void s12c_800D5B00(DG_CHANL *chanl, int idx);

void FogBoundChanl_800D5500(DG_CHANL *chanl, int idx)
{
    int          i, i2, i3, a2, t0, a3, t1;
    int          n_objs;
    int          bound_mode, bound_mode2;
    DG_OBJS    **objs;
    int          local_group_id;
    DVECTOR     *dvec;
    SVECTOR     *svec;
    DG_VECTOR   *vec3_1;
    DG_VECTOR   *vec3_2;
    DG_Bounds   *mdl_bounds;
    int          n_bounding_box_vec;
    unsigned int flag;
    short       *scrpad;

    DG_Clip(&chanl->clip_rect, chanl->clip_distance);

    scrpad = (short *)SCRPAD_ADDR;
    memcpy(scrpad + 0x90 / 2, DG_ClipMax, 4);
    memcpy(scrpad + 0x94 / 2, DG_ClipMin, 4);

    objs = chanl->mQueue;
    n_objs = chanl->mTotalObjectCount;
    local_group_id = DG_CurrentGroupID;

    for (; n_objs > 0; --n_objs)
    {
        DG_OBJS *current_objs = *objs;
        objs++;
        flag = current_objs->flag;

        bound_mode = 0;
        *(int *)(SCRPAD_ADDR + 0x98) = flag;
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
                    mdl_bounds = (DG_Bounds *)&current_objs->def->max;
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

                    if ((a2 > *(short *)(SCRPAD_ADDR + 0x90)) || (a3 < *(short *)(SCRPAD_ADDR + 0x94)) ||
                        (t0 > *(short *)(SCRPAD_ADDR + 0x92)) || (t1 < *(short *)(SCRPAD_ADDR + 0x96)))
                    {
                        bound_mode = 0;
                    }
                    else
                    {
                        int bound_mode3;
                        bound_mode2 = ((a3 > *(short *)(SCRPAD_ADDR + 0x90)) || (a2 < *(short *)(SCRPAD_ADDR + 0x94)) ||
                                       (t1 > *(short *)(SCRPAD_ADDR + 0x92)) || (t0 < *(short *)(SCRPAD_ADDR + 0x96)))
                                          ? 1
                                          : 2;
                        if (*(int *)(SCRPAD_ADDR + 0x98) & 0x2)
                        {
                            int   var_t2_2;
                            int   i3, t1, t0;
                            long *test;
                            var_t2_2 = 0;
                            test = (long *)(SCRPAD_ADDR + 0x6C);
                            t1 = 0;
                            t0 = 0xFFFF;
                            i3 = 8;
                            while (i3 > 0)
                            {

                                if (*test < t0)
                                {
                                    t0 = *test;
                                }
                                if (t1 < *test)
                                {
                                    t1 = *test;
                                }
                                if (*test)
                                {
                                    var_t2_2 = bound_mode2;
                                }
                                test++;
                                i3--;
                            }

                            if (var_t2_2)
                            {
                                if (t0 / 256 < s12c_800DA430)
                                {
                                    if (t1 / 256 >= s12c_800DA428)
                                    {
                                        bound_mode3 = var_t2_2 | 4;
                                    }
                                    else
                                    {
                                        bound_mode3 = var_t2_2;
                                    }
                                }
                                else
                                {
                                    bound_mode3 = 0;
                                }
                            }
                            else
                            {
                                bound_mode3 = 0;
                            }
                        }
                        else
                        {
                            long *test;
                            test = (long *)(SCRPAD_ADDR + 0x6C);
                            i3 = 8;
                            while (i3 > 0)
                            {
                                --i3;
                                if (*test)
                                {
                                    bound_mode3 = bound_mode2;
                                    goto END;
                                }
                                test++;
                            }
                            bound_mode3 = 0;
                        }
                    END:
                        bound_mode = bound_mode3;
                    }
                }
            }
        }
        current_objs->bound_mode = bound_mode;
        DG_BoundObjs_800D5010(current_objs, idx, flag, bound_mode);
    }

    s12c_800D5B00(chanl, idx);
}

// Identical to DG_WriteObjClut_80018D28
void s12c_800D59CC(DG_OBJ *pObj, int idx)
{
    int       n_packs;
    POLY_GT4 *pPack = pObj->packs[idx];
    short     val = 0x3FFF;
    if (pPack && pPack->clut != val)
    {
        while (pObj)
        {
            n_packs = pObj->n_packs;
            while (n_packs > 0)
            {
                pPack->clut = val;

                ++pPack;
                --n_packs;
            }

            pObj = pObj->extend;
        }
    }
}

DG_TEX DG_UnknownTexture_800C34FC = {0};

// Identical to DG_WriteObjClutUV_80018D90
void s12c_800D5A34(DG_OBJ *obj, int idx)
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
        texture = &DG_UnknownTexture_800C34FC;
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

// Identical to DG_BoundIrTexture_80018E5C
// there must be a way to match this without the repetition
void s12c_800D5B00(DG_CHANL *chanl, int idx)
{
    int       i, i2;
    DG_OBJ   *obj;
    DG_OBJS  *objs;
    DG_OBJS **objs_list;

    objs_list = chanl->mQueue;
    if (GM_GameStatus & STATE_THERMG)
    {
        for (i = chanl->mTotalObjectCount; i > 0; --i)
        {
            objs = *objs_list;
            objs_list++;
            if (objs->flag & DG_FLAG_IRTEXTURE && objs->bound_mode)
            {
                obj = objs->objs;
                for (i2 = objs->n_models; i2 > 0; --i2)
                {
                    if (obj->bound_mode)
                    {
                        s12c_800D59CC(obj, idx);
                    }
                    obj++;
                }
            }
        }
    }
    else
    {
        for (i = chanl->mTotalObjectCount; i > 0; --i)
        {
            objs = *objs_list;
            objs_list++;
            if (objs->flag & DG_FLAG_IRTEXTURE && objs->bound_mode)
            {
                obj = objs->objs;
                for (i2 = objs->n_models; i2 > 0; --i2)
                {
                    s12c_800D5A34(obj, idx);
                    obj++;
                }
            }
        }
    }
}

// clang-format off
#define gte_ldVZ2_2( r0 ) __asm__ volatile (                    \
        "lwc2   $5, 20( %0 )"                                   \
        :                                                       \
        : "r"( r0 ) )
// clang-format on

// DG_Trans_Chanl_helper_simple_8001DF48
void s12c_800D5C48(DG_PVECTOR *a0, int count)
{
    DG_VECTOR    *scrpd_nidx;
    DG_VECTOR    *scrpd_nidx2;
    register long v1 asm("t2"); // FIXME
    long          v2, v3, v4, v5;

    scrpd_nidx = (DG_VECTOR *)getScratchAddr(0);
    scrpd_nidx2 = (DG_VECTOR *)getScratchAddr(128);

    v1 = a0[0].vxy;
    v2 = a0[0].vz;
    v3 = a0[1].vxy;
    v4 = a0[1].vz;
    v5 = a0[2].vxy;

    while (count > 0)
    {
        gte_ldVXY0(v1);
        gte_ldVZ0(v2);
        gte_ldVXY1(v3);
        gte_ldVZ1(v4);
        gte_ldVXY2(v5);
        gte_ldVZ2_2(a0);

        a0 += 3;
        count -= 3;
        gte_rtpt_b();

        v1 = a0[0].vxy;
        v2 = a0[0].vz;
        v3 = a0[1].vxy;
        v4 = a0[1].vz;
        v5 = a0[2].vxy;

        gte_stsxy3c(scrpd_nidx);
        gte_stsz3c(scrpd_nidx2);
        scrpd_nidx++;
        scrpd_nidx2++;
    }
}

// modified DG_WriteObjVerticesIndirect
unsigned int s12c_800D5CDC(unsigned int normal_idx, POLY_GT4 *packs)
{
    int          *pack_ptr;
    int           a2, a3, t3, t5, num, stride;
    int           i, temp;
    unsigned int  scrpd_idx;
    unsigned char t6;

    scrpd_idx = SCRPAD_ADDR;
    t3 = *(int *)(scrpd_idx + 0x3F8);
    if (!t3)
        return 0;

    t5 = *(int *)(scrpd_idx + 0x3FC);
    num = 0;
    stride = 0;

    pack_ptr = (int *)&packs->x0;
    a3 = 8;
    i = 4;
    t6 = 32;

    for (; i > 0; i--)
    {
        a2 = normal_idx & 0x7f;

        if ((normal_idx & 0x80) == 0)
        {
            a2 = scrpd_idx + (a2 * 4);
            temp = ((unsigned int *)a2)[0x80];
            a2 = *(int *)a2;
            num = num + temp;
            stride++;
        }
        else
        {
            a2 = t5 + (a2 << 3);
            temp = ((unsigned short *)scrpd_idx)[0xFF];
            a2 = ((short *)a2)[3];

            if (temp & 4)
            {
                *(pack_ptr - 1) = (t3 + a2) - 4;
            }

            a2 = *(int *)(t3 + a2);
        }

        *pack_ptr = a2;
        pack_ptr += 3;
        normal_idx = (normal_idx << (t6 - a3)) | (normal_idx >> a3);
        a3 = a3 + 8;
    }

    if (stride == 2)
    {
        return num / 2;
    }
    else if (stride != 0)
    {
        return num / stride;
    }
    return 0;
}

// Modified DG_WriteObjVertices
POLY_GT4 *s12c_800D5DE0(unsigned int *pFaceIndices, POLY_GT4 *pPoly, int n_packs)
{
    unsigned int v0, v1, v2;
    unsigned int n0, n1, n2, n3;
    unsigned int tag;
    int          opz;
    unsigned int scratchpad;

    for (n_packs = n_packs + -1; n_packs >= 0; (pPoly++)->tag = tag, pFaceIndices++, n_packs--)
    {
        scratchpad = SCRPAD_ADDR;
        tag = 0;
        n0 = *pFaceIndices;

        if (n0 & 0x80808080)
        {
            tag = s12c_800D5CDC(n0, pPoly);
            continue;
        }

        n1 = n0;
        n2 = n0;
        n3 = n0;

        n0 = n0 << 2;
        n1 = n1 >> 6;
        n2 = n2 >> 22;
        n3 = n3 >> 14;

        n0 = n0 & 0x1fc;
        n1 = n1 & 0x1fc;
        n2 = n2 & 0x1fc;
        n3 = n3 & 0x1fc;

        n0 = n0 + scratchpad;
        n1 = n1 + scratchpad;
        n2 = n2 + scratchpad;
        n3 = n3 + scratchpad;

        v0 = ((unsigned int *)n0)[0];
        n0 = ((unsigned int *)n0)[0x80];
        v1 = ((unsigned int *)n1)[0];
        v2 = ((unsigned int *)n2)[0];

        if ((*(unsigned short *)(scratchpad + 0x1fe) & 1) && (n0 >> 24))
        {
            LCOPY((unsigned int *)n3, &pPoly->x3);
            n1 = ((unsigned int *)n1)[0x80];
            n2 = ((unsigned int *)n2)[0x80];
            n3 = ((unsigned int *)n3)[0x80];

            if ((n0 & n1 & n2 & n3) >> 24 != 0)
            {
                continue;
            }
            gte_ldsxy3(v0, v1, v2);
            LSTORE(v0, &pPoly->x0);
            LSTORE(v1, &pPoly->x1);
            gte_nclip_b();
            tag = ((n0 + n3) >> 1) & 0xffff;
            LSTORE(v2, &pPoly->x2);
            gte_read_opz(opz);
            gte_nop();
        }
        else
        {
            gte_ldsxy3(v0, v1, v2);
            n1 = ((unsigned int *)n1)[0x80];
            n2 = ((unsigned int *)n2)[0x80];
            gte_nclip_b();
            LCOPY((unsigned int *)n3, &pPoly->x3);
            n3 = ((unsigned int *)n3)[0x80];
            LSTORE(v0, &pPoly->x0);
            LSTORE(v1, &pPoly->x1);
            tag = ((n0 + n3) >> 1) & 0xffff;
            gte_read_opz(opz);
            LSTORE(v2, &pPoly->x2);
        }

        if (opz < 1)
        {
            int new_var;

            if ((*(unsigned short *)0x1f8001fc) || opz == 0)
            {
                tag = 0;
                continue;
            }

            new_var = 65536;
            tag = (tag | new_var) | ((-opz * 0x100) & 0xfffe0000);
        }
        else
        {
            tag |= (opz << 8) & 0xfffe0000;
        }

        if (*(unsigned short *)(SCRPAD_ADDR + 0x1fe) & 2)
        {
            LSTORE(((n0 >> 8) & 0xff) | (n1 & 0xff00) | ((n2 << 8) & 0xff0000) | ((n3 << 16) & 0xff000000), &pPoly->r0);
        }
    }

    return pPoly;
}

#define CALCULATE_CLIPPING(verts)                               \
    {                                                           \
        int  tmp;                                               \
        char res;                                               \
        res = 0;                                                \
        tmp = (verts)->vx;                                      \
        if (tmp < -160) {                                       \
            res = 1;                                            \
        }                                                       \
        else if (tmp > 160) {                                   \
            res = 2;                                            \
        }                                                       \
        tmp = (verts)->vy;                                      \
        if (tmp < -112) {                                       \
            res |= 4;                                           \
        }                                                       \
        else if (tmp > 112) {                                   \
            res |= 8;                                           \
        }                                                       \
        *((char *)((verts) + 128) + 3) = res;                   \
    }

static inline void DG_TransVerticesBound(DG_PVECTOR *verts, int n_verts)
{
    int      vert_count;
    DVECTOR *results_xy;
    DVECTOR *results_z;
    int      z0;
    int      xy1, z1;
    int      xy2;

    int xy0;

    gte_ldv3c(verts);

    verts += 3;
    vert_count = n_verts - 3;
    results_xy = (DVECTOR *)getScratchAddr(0);
    results_z = (DVECTOR *)getScratchAddr(128);
    gte_rtpt_b();

    results_xy += 3;
    results_z += 3;

    xy0 = verts[0].vxy;
    z0 = verts[0].vz;

    xy1 = verts[1].vxy;
    z1 = verts[1].vz;

    xy2 = verts[2].vxy;

    gte_stsxy3c(results_xy - 3);
    gte_stsz3c(results_z - 3);

    while (vert_count > 0)
    {
        gte_ldVXY0(xy0);
        gte_ldVZ0(z0);
        gte_ldVXY1(xy1);
        gte_ldVZ1(z1);
        gte_ldVXY2(xy2);
        gte_ldVZ2_2(verts);

        verts += 3;
        vert_count -= 3;

        gte_rtpt_b();

        CALCULATE_CLIPPING(results_xy - 3);
        CALCULATE_CLIPPING(results_xy - 2);
        CALCULATE_CLIPPING(results_xy - 1);

        xy0 = verts[0].vxy;
        z0 = verts[0].vz;

        xy1 = verts[1].vxy;
        z1 = verts[1].vz;

        xy2 = verts[2].vxy;

        gte_stsxy3c(results_xy);
        gte_stsz3c(results_z);

        results_xy += 3;
        results_z += 3;
    }

    CALCULATE_CLIPPING(results_xy - 3);
    CALCULATE_CLIPPING(results_xy - 2);
    CALCULATE_CLIPPING(results_xy - 1);
}

// Modified DG_TransObj
void s12c_800D6020(DG_OBJ *obj, int idx)
{
    POLY_GT4   *packs;
    DG_MDL     *mdl;
    DG_PVECTOR *verts;

    packs = obj->packs[idx];

    while (obj)
    {
        mdl = obj->model;
        verts = (DG_PVECTOR *)mdl->vertices;

        if (*(unsigned short *)0x1F8001FE & 1)
        {
            DG_TransVerticesBound(verts, mdl->n_verts);
        }
        else
        {
            s12c_800D5C48(verts, mdl->n_verts);
        }

        *(unsigned short *)0x1F8001FC = !(mdl->flags & DG_MODEL_BOTHFACE);
        do
        {
        } while (0);

        packs = s12c_800D5DE0((unsigned int *)mdl->vindices, packs, obj->n_packs);
        obj = obj->extend;
    }
}

void FogTransChanl_800D63B0(DG_CHANL *chanl, int idx)
{
    short    *pScratchpad = (short *)getScratchAddr(0);
    DG_OBJS **ppObjs;
    int       objects;
    DG_OBJS  *pObjs;
    DG_OBJ   *pObj;
    int       uVar5;
    int       models;
    DG_MDL   *pMdl;
    DG_OBJ   *pParent;
    short     uVar1;

    DG_Clip(&chanl->clip_rect, chanl->clip_distance);

    ppObjs = (DG_OBJS **)chanl->mQueue;

    for (objects = chanl->mTotalObjectCount; objects > 0; objects--)
    {
        pObjs = *ppObjs++;

        if (!pObjs->bound_mode)
        {
            continue;
        }

        pObj = pObjs->objs;
        uVar5 = !(pObjs->flag & DG_FLAG_GBOUND);

        for (models = pObjs->n_models; models > 0; pObj++, models--)
        {
            if (!pObj->bound_mode)
            {
                continue;
            }

            pMdl = pObj->model;
            pParent = &pObjs->objs[pMdl->parent];

            ((POLY_GT4 **)pScratchpad)[0xfe] = pParent->packs[GV_Clock];
            ((SVECTOR **)pScratchpad)[0xff] = pMdl->vertices;

            gte_SetRotMatrix(&pObj->screen);
            gte_SetTransMatrix(&pObj->screen);

            uVar1 = 0;

            if (uVar5 != 0)
            {
                uVar1 = pObj->bound_mode & 1;
            }

            pScratchpad[0xff] = uVar1;
            if (pObj->bound_mode & 4)
            {
                pScratchpad[0xff] |= 2;
            }

            if (pObjs->flag & DG_FLAG_SHADE)
            {
                pScratchpad[0xff] |= 4;
            }

            s12c_800D6020(pObj, idx);
        }
    }
}

// clang-format off
#define gte_ldRGB( r0 ) __asm__ volatile (                      \
        "swc2   $22, 4( %0 )"                                   \
        :                                                       \
        : "r"( r0 )                                             \
        : "memory" )

#define gte_ldRGB2( r0 ) __asm__ volatile (                     \
        "swc2   $22, 16( %0 )"                                  \
        :                                                       \
        : "r"( r0 )                                             \
        : "memory" )

#define gte_ldRGB3( r0 ) __asm__ volatile (                     \
        "swc2   $22, 28( %0 )"                                  \
        :                                                       \
        : "r"( r0 )                                             \
        : "memory" )

#define gte_ldRGBC( r0 ) __asm__ volatile (                     \
        "mtc2   %0, $6;"                                        \
        :                                                       \
        : "r"( r0 ) )
// clang-format on

void s12c_800D6588(DG_OBJ *pDGObj, int idx)
{
    unsigned int rgb;
    POLY_GT4    *poly;
    CVECTOR     *r0;
    int          i;
    char        *iVar6;
    int          last;
    int          tmp2;
    int          index;

    poly = pDGObj->packs[idx];

    if (poly == 0)
    {
        return;
    }

    iVar6 = (char *)s12c_800DAA4C;
    last = SCRPAD_ADDR;

    for (; pDGObj != 0; pDGObj = pDGObj->extend)
    {
        r0 = pDGObj->rgbs;

        if (!r0)
        {
            continue;
        }
        for (i = pDGObj->n_packs; i > 0; r0 += 4, i--)
        {
            rgb = LLOAD(&poly->r0);

            index = ((rgb * 2) & 0x1fe);
            tmp2 = *(short *)(iVar6 + index);
            gte_strgb_s4(last);
            gte_lddp(tmp2);
            gte_ldrgb(r0);

            index = (rgb >> 7 & 0x1fe);
            gte_dpcs_b();
            tmp2 = *(short *)(iVar6 + index);

            last = LLOAD(&r0[1]);
            gte_ldRGB(poly);
            gte_lddp(tmp2);
            gte_ldRGBC(last);

            index = (rgb >> 15 & 0x1fe);
            gte_dpcs_b();
            tmp2 = *(short *)(iVar6 + index);

            last = LLOAD(&r0[3]);
            gte_ldRGB2(poly);
            gte_lddp(tmp2);
            gte_ldRGBC(last);

            index = (rgb >> 23 & 0x1fe);
            gte_dpcs_b();
            tmp2 = *(short *)(iVar6 + index);

            last = LLOAD(&r0[2]);
            gte_ldRGB3(poly);
            gte_lddp(tmp2);
            gte_ldRGBC(last);

            last = (int)poly;
            poly++;
            gte_dpcs_b();
        }
    }

    gte_strgb_s4(last);
}

// clang-format off
#define gte_strgb3_2( vec ) __asm__ volatile (                  \
        "swc2   $20, 0( %0 );"                                  \
        "swc2   $21, 4( %0 );"                                  \
        "swc2   $22, 8( %0 )"                                   \
        :                                                       \
        : "r"( vec )                                            \
        : "memory" )
// clang-format on

void s12c_800D6698(DG_MDL *mdl)
{
    int            n_normals;
    long          *nidx;
    DG_VECTOR     *scrpd_nidx2;
    unsigned long *code;
    long           v1, v2, v3, v4, v5, v6;

    code = DG_PacketCode;
    if (mdl->flags & DG_MODEL_TRANS)
    {
        code = &DG_PacketCode[1];
    }

    gte_ldrgb(code);
    nidx = (long *)mdl->normals;
    n_normals = mdl->n_normals;

    v1 = nidx[0];
    v2 = nidx[1];
    v3 = nidx[2];
    v4 = nidx[3];
    v5 = nidx[4];
    v6 = nidx[5];

    scrpd_nidx2 = (DG_VECTOR *)0x1F800020;
    while (n_normals > 0)
    {
        gte_ldVXY0(v1);
        gte_ldVZ0(v2);
        gte_ldVXY1(v3);
        gte_ldVZ1(v4);
        gte_ldVXY2(v5);
        gte_ldVZ2(v6);

        nidx += 6;
        n_normals -= 3;
        gte_nct_b();

        do {
            v1 = nidx[0];
            v2 = nidx[1];
            v3 = nidx[2];
            v4 = nidx[3];
            v5 = nidx[4];
            v6 = nidx[5];
        } while (0);

        gte_strgb3_2(scrpd_nidx2);
        scrpd_nidx2++;
    }
}

// just an index using an int shifted to get each byte of the face normal idx, but didnt match that way
static inline void DG_ShadePack(unsigned int *face_normals, POLY_GT4 *packs, void *dst)
{
    unsigned int fa, fb, fc, fd;
    fa = *face_normals;
    fb = *face_normals;
    fc = *face_normals;
    fd = *face_normals;

    fa <<= 2;
    fb >>= 6;
    fc >>= 22;
    fd >>= 14;

    fa &= 0x1FC;
    fb &= 0x1FC;
    fc &= 0x1FC;
    fd &= 0x1FC;
    fa = (int)(dst + fa);
    fb = (int)(dst + fb);
    fc = (int)(dst + fc);
    fd = (int)(dst + fd);

    LCOPY2((void *)fa, &packs->r0, (void *)fb, &packs->r1);
    LCOPY2((void *)fc, &packs->r2, (void *)fd, &packs->r3);
}

// Identical to DG_Shade_Chanl_helper_helper_8001CF88
POLY_GT4 *s12c_800D6744(unsigned int *face_normals, POLY_GT4 *packs, int n_packs)
{
    for (--n_packs; n_packs >= 0; --n_packs)
    {
        void *scrpad_pack = (void *)0x1F800020;
        if (packs->tag & 0xFFFF)
        {
            DG_ShadePack(face_normals, packs, scrpad_pack);
        }
        packs++;
        face_normals++;
    }

    return packs;
}

// Identical to DG_Shade_Chanl_helper_helper2_8001D034
POLY_GT4 *s12c_800D67F0(unsigned int *face_normals, POLY_GT4 *packs, int n_packs, unsigned int *face)
{
    unsigned int t2, t6;
    unsigned int fa, fb, fc, fd;
    void        *scrpad_pack;
    for (--n_packs; n_packs >= 0; packs++, face_normals++, face++, --n_packs)
    {
        t6 = 0x80808080;
        scrpad_pack = (void *)0x1F800020;
        fa = *face_normals;

        if (!(packs->tag & 0xFFFF) && !(*face_normals & t6))
            continue;

        t2 = *face;
        fd = *face_normals;
        fa = *face_normals << 2;
        fb = *face_normals >> 6;
        fc = *face_normals >> 22;
        fd = *face_normals >> 14;

        fa &= 0x1FC;
        fb &= 0x1FC;
        fc &= 0x1FC;
        fd &= 0x1FC;

        fa += (unsigned int)scrpad_pack;
        fb += (unsigned int)scrpad_pack;
        fc += (unsigned int)scrpad_pack;
        fd += (unsigned int)scrpad_pack;

        if (t2 & t6)
        {
            int val;
            if (t2 & 0x80)
            {
                val = **(int **)&packs->r0;
            }
            else
            {
                val = *(int *)fa;
            }
            t2 >>= 8;
            *(int *)&packs->r0 = val;

            if (t2 & 0x80)
            {
                val = **(int **)&packs->r1;
            }
            else
            {
                val = *(int *)fb;
            }
            t2 >>= 8;
            *(int *)&packs->r1 = val;

            if (t2 & 0x80)
            {
                val = **(int **)&packs->r3;
            }
            else
            {
                val = *(int *)fd;
            }
            t2 >>= 8;
            *(int *)&packs->r3 = val;

            if (t2 & 0x80)
            {
                val = **(int **)&packs->r2;
            }
            else
            {
                val = *(int *)fc;
            }
            t2 >>= 8;
            *(int *)&packs->r2 = val;
        }
        else
        {
            LCOPY2((void *)fa, &packs->r0, (void *)fb, &packs->r1);
            LCOPY2((void *)fc, &packs->r2, (void *)fd, &packs->r3);
        }
    }

    return packs;
}

// Based on DG_Shade_Chanl_helper_8001D19C, but most of the body of
// the for loop extracted to a separate function?
void s12c_800D6958(DG_OBJ *obj, int idx)
{
    // int n_normals;
    // DG_VECTOR* nidx;
    // DG_VECTOR* scrpd_nidx;
    // DG_VECTOR* scrpd_nidx2;
    // unsigned long *code;
    POLY_GT4 *pack;
    DG_MDL   *mdl;

    pack = obj->packs[idx];

    while (obj)
    {
        mdl = obj->model; // t1;

        s12c_800D6698(mdl);
        /*
        code = DG_PacketCode;
        if ( mdl->flags & DG_MODEL_TRANS )
        {
            code = &DG_PacketCode[1];
        }

        gte_ldrgb( code );
        scrpd_nidx = (DG_VECTOR*)0x1F800020;
        nidx = (DG_VECTOR*)mdl->normals; //a2
        n_normals = mdl->n_normals;

        scrpd_nidx[0] = nidx[0]; //maybe copyvector macro
        scrpd_nidx[1] = nidx[1];

        scrpd_nidx2 = (DG_VECTOR*)0x1F800020;
        while ( n_normals > 0 )
        {

            gte_ldv3c( scrpd_nidx2 );
            n_normals  -= 3;
            nidx += 2;
            gte_nct_b();
            scrpd_nidx2++;

            scrpd_nidx2[0] = nidx[0];
            scrpd_nidx2[1] = nidx[1];

            gte_strgb3( &scrpd_nidx2[-1].vx, &scrpd_nidx2[-1].vy, &scrpd_nidx2[-1].vz );
        }
        */

        if (!(mdl->flags & 0x10000))
        {
            pack = s12c_800D6744((unsigned int *)mdl->nindices, pack, obj->n_packs);
        }
        else
        {
            pack = s12c_800D67F0((unsigned int *)mdl->nindices, pack, obj->n_packs,
                                 (unsigned int *)mdl->vindices);
        }
        obj = obj->extend;
    }
}

void FogShadeChanl_800D6A04(DG_CHANL *chanl, int index)
{
    MATRIX    color;
    VECTOR    scale;
    DG_OBJS **queue;
    int       n_objects;
    DG_OBJS  *objs;
    int       s;
    DG_OBJ   *obj;
    int       n_models;
    int       bound_index;

    gte_ldfcdir(0, 0, 0);

    queue = chanl->mQueue;
    for (n_objects = chanl->mTotalObjectCount; n_objects > 0; n_objects--)
    {
        objs = *queue++;
        if (objs->bound_mode != 0)
        {
            if (objs->flag & DG_FLAG_SHADE)
            {
                s = objs->objs[0].screen.t[2] / 256;
                s = 4096 - s12c_800DAA4C[s];
                gte_SetRotMatrix(objs->light);

                scale.vx = scale.vy = scale.vz = s;
                color = objs->light[1];
                ScaleMatrix(&color, &scale);
                gte_SetColorMatrix(&color);

                if (objs->flag & DG_FLAG_AMBIENT)
                {
                    VECTOR *ambient = (VECTOR *)objs->light[0].t;
                    int     r = (ambient->vx * s) / 4096;
                    int     g = (ambient->vy * s) / 4096;
                    int     b = (ambient->vz * s) / 4096;
                    gte_SetBackColor(r, g, b);
                }
                else
                {
                    SVECTOR *ambient = &DG_Ambient;
                    int      r = (ambient->vx * s) / 4096;
                    int      g = (ambient->vy * s) / 4096;
                    int      b = (ambient->vz * s) / 4096;
                    gte_SetBackColor(r, g, b);
                }

                obj = objs->objs;
                for (n_models = objs->n_models; n_models > 0; n_models--)
                {
                    if (obj->bound_mode != 0)
                    {
                        MulRotMatrix0(&obj->world, (MATRIX *)SCRPAD_ADDR);
                        SetLightMatrix((MATRIX *)SCRPAD_ADDR);
                        s12c_800D6958(obj, index);
                    }

                    obj++;
                }

                gte_SetBackColor(DG_Ambient.vx, DG_Ambient.vy, DG_Ambient.vz);
            }
            else if (objs->flag & DG_FLAG_PAINT)
            {
                bound_index = (index + 1) * 8;
                obj = objs->objs;
                for (n_models = objs->n_models; n_models > 0; n_models--)
                {
                    if (obj->bound_mode != 0)
                    {
                        if (!(obj->bound_mode & 0x4))
                        {
                            if (!(obj->bound_mode & bound_index))
                            {
                                DG_WriteObjPacketRGB(obj, index);
                                obj->bound_mode |= bound_index;
                            }
                        }
                        else
                        {
                            SetSpadStack(SPAD_STACK_ADDR);
                            s12c_800D6588(obj, index);
                            ResetSpadStack();
                            obj->bound_mode &= ~bound_index;
                        }
                    }

                    obj->bound_mode &= ~0x4;
                    obj++;
                }
            }
        }

        objs->bound_mode &= 0x3;
    }
}
