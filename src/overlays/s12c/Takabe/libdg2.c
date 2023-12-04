#include "libdg/libdg.h"
#include "libgcl/libgcl.h"

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

short SECTION("overlay.bss")  s12c_800DA440[768];
short SECTION("overlay.bss") *s12c_800DAA40;
short SECTION("overlay.bss") *s12c_800DAA44;
short SECTION("overlay.bss") *s12c_800DAA48;
short SECTION("overlay.bss") *s12c_800DAA4C;

extern int           GM_GameStatus_800AB3CC;
extern int           GV_PauseLevel_800AB928;
extern int           DG_CurrentGroupID_800AB968;
extern unsigned int *ptr_800B1400[256];

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
    unsigned int *ot;
    int len;
    int unkC;
    int unk10;
    int unk14;
    void *unk18;
    short *unk1C;
} SCRATCHPAD_UNK;

// TODO: fix this
#define gte_ldrgb_s0(r0) __asm__ volatile("lwc2   $6,  4( %0 )" : : "r"(r0))
#define gte_ldrgb_s1(r0) __asm__ volatile("lwc2   $6, 12( %0 )" : : "r"(r0))
#define gte_ldrgb_s2(r0) __asm__ volatile("lwc2   $6, 20( %0 )" : : "r"(r0))
#define gte_ldrgb_s3(r0) __asm__ volatile("lwc2   $6, 28( %0 )" : : "r"(r0))

#define gte_ldrgb_f0(r0) __asm__ volatile("lwc2   $22,  4( %0 )" : : "r"(r0) : "memory")
#define gte_ldrgb_f1(r0) __asm__ volatile("lwc2   $20, 12( %0 )" : : "r"(r0) : "memory")
#define gte_ldrgb_f2(r0) __asm__ volatile("lwc2   $21, 20( %0 )" : : "r"(r0) : "memory")
#define gte_ldrgb_f3(r0) __asm__ volatile("lwc2   $22, 28( %0 )" : : "r"(r0) : "memory")

#define gte_ldrgb_f1_t(r0) __asm__ volatile("lwc2   $20, 16( %0 )" : : "r"(r0) : "memory")
#define gte_ldrgb_f2_t(r0) __asm__ volatile("lwc2   $21, 28( %0 )" : : "r"(r0) : "memory")
#define gte_ldrgb_f3_t(r0) __asm__ volatile("lwc2   $22, 40( %0 )" : : "r"(r0) : "memory")

#define gte_strgb_s2_t(r0) __asm__ volatile("swc2   $20, 16( %0 );" "swc2   $21, 28( %0 )" : : "r"(r0) : "memory")
#define gte_strgb_s3_t(r0) __asm__ volatile("swc2   $20, 16( %0 );" "swc2   $21, 28( %0 );" "swc2   $22, 40( %0 )" : : "r"(r0) : "memory")

#define gte_strgb_s0(r0) __asm__ volatile("swc2   $22,  4( %0 )" : : "r"(r0) : "memory")
#define gte_strgb_s1(r0) __asm__ volatile("swc2   $22, 12( %0 )" : : "r"(r0) : "memory")
#define gte_strgb_s2(r0) __asm__ volatile("swc2   $20, 12( %0 );" "swc2   $21, 20( %0 )" : : "r"(r0) : "memory")
#define gte_strgb_s3(r0) __asm__ volatile("swc2   $20, 12( %0 );" "swc2   $21, 20( %0 );" "swc2   $22, 28( %0 )" : : "r"(r0) : "memory")


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
    s12c_800D4C9C,
    s12c_800D4B2C,
    s12c_800D4B2C,
    s12c_800D4B2C,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

static inline SCRATCHPAD_UNK * get_scratch(void)
{
    return (SCRATCHPAD_UNK *)0x1f800000;
}

void s12c_800D4CF4(unsigned int *ot)
{
    SCRATCHPAD_UNK *scratch;
    unsigned int **buf;
    int            i;
    unsigned int  *tag;
    unsigned int   val;
    unsigned int  *next;

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

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_fadeio_800D4D8C.s")
void s12c_fadeio_800D4D8C(void *, int, int, void *);

void FogSortChanl_800D4E98(DG_CHNL *chnl, int idx)
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
    scratch->ot = (unsigned int *)chnl->mOrderingTables[idx] + 1;

    s12c_800D4CF4(scratch->ot);

    mask = 0x1F;
    if (GV_PauseLevel_800AB928 != 0)
    {
        mask = 0;
    }

    gte_ldfcdir(0, 0, 0);

    scratch->unk18 = (void *)0x1F800020;
    scratch->unk1C = s12c_800DAA44;

    group_id = DG_CurrentGroupID_800AB968;

    queue = (void **)&chnl->mQueue[chnl->mFreePrimCount];
    for (i = chnl->mTotalQueueSize - chnl->mFreePrimCount; i > 0; i--)
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
        ((SCRATCHPAD_UNK *)0x1f800000)->len = prim->field_2E_k500;

        type = (type + 1) & mask;
        s12c_fadeio_800D4D8C(prim->field_40_pBuffers[idx], prim->n_prims, prim->field_30_prim_size, fog_prim_funcs_800C347C[type]);
    }

    gte_strgb_s0(*(void **)0x1F800018);
}

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_fadeio_800D5010.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/FogBoundChanl_800D5500.s")

// Identical to DG_WriteObjClut_80018D28
void s12c_fadeio_800D59CC(DG_OBJ *pObj, int idx)
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
void s12c_fadeio_800D5A34(DG_OBJ *obj, int idx)
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
            tex_ids = obj->model->materialOffset_50;
            for (n_packs = obj->n_packs; n_packs > 0; --n_packs)
            {
                current_id = *tex_ids;
                tex_ids++;
                if ((current_id & 0xFFFF) != id)
                {
                    id = current_id;
                    texture = DG_GetTexture_8001D830(id);
                }
                pack->clut = texture->field_6_clut;
                pack++;
            }
            obj = obj->extend;
        }
    }
}

// Identical to DG_BoundChanl_helper2_80018E5C
// there must be a way to match this without the repetition
void s12c_fadeio_800D5B00(DG_CHNL *chnl, int idx)
{
    int       i, i2;
    DG_OBJ   *obj;
    DG_OBJS  *objs;
    DG_OBJS **objs_list;

    objs_list = chnl->mQueue;
    if (GM_GameStatus_800AB3CC & GAME_FLAG_BIT_04)
    {
        for (i = chnl->mTotalObjectCount; i > 0; --i)
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
                        s12c_fadeio_800D59CC(obj, idx);
                    }
                    obj++;
                }
            }
        }
    }
    else
    {
        for (i = chnl->mTotalObjectCount; i > 0; --i)
        {
            objs = *objs_list;
            objs_list++;
            if (objs->flag & DG_FLAG_IRTEXTURE && objs->bound_mode)
            {
                obj = objs->objs;
                for (i2 = objs->n_models; i2 > 0; --i2)
                {
                    s12c_fadeio_800D5A34(obj, idx);
                    obj++;
                }
            }
        }
    }
}

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_fadeio_800D5C48.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_fadeio_800D5CDC.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_fadeio_800D5DE0.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_fadeio_800D6020.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/FogTransChanl_800D63B0.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_fadeio_800D6588.s")
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_fadeio_800D6698.s")
void s12c_fadeio_800D6698(DG_MDL* mdl);

//just an index using an int shifted to get each byte of the face normal idx, but didnt match that way
static inline void set_face_normal_pack(unsigned int *face_normals, POLY_GT4 *packs, void* dst)
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

    LCOPY2( (void*)fa, &packs->r0, (void*)fb, &packs->r1 );
    LCOPY2( (void*)fc, &packs->r2, (void*)fd, &packs->r3 );
}

// Identical to DG_Shade_Chanl_helper_helper_8001CF88
POLY_GT4 *s12c_fadeio_800D6744( unsigned int *face_normals, POLY_GT4 *packs, int n_packs )
{
    for ( --n_packs; n_packs >= 0 ; --n_packs )
    {
        void *scrpad_pack = (void*)0x1F800020;
        if ( packs->tag & 0xFFFF )
        {
            set_face_normal_pack(face_normals, packs, scrpad_pack);
        }
        packs++;
        face_normals++;
    }

    return packs;
}

// Identical to DG_Shade_Chanl_helper_helper2_8001D034
POLY_GT4 *s12c_fadeio_800D67F0( unsigned int *face_normals, POLY_GT4 *packs, int n_packs, unsigned int* face )
{
    unsigned int t2, t6;
    unsigned int fa,fb,fc,fd;
    void* scrpad_pack;
    for ( --n_packs; n_packs >= 0 ; packs++, face_normals++, face++, --n_packs )
    {
        t6 = 0x80808080;
        scrpad_pack = (void*)0x1F800020;
        fa = *face_normals;

        if ( !( packs->tag & 0xFFFF ) && !( *face_normals & t6 ) ) continue;

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

        if ( t2 & t6 )
        {
            int val;
            if ( t2 & 0x80 )
            {
                val = **(int**)&packs->r0;
            }
            else
            {
                val = *(int*)fa;
            }
            t2 >>= 8;
            *(int*)&packs->r0 = val;

            if ( t2 & 0x80 )
            {
                val = **(int**)&packs->r1;
            }
            else
            {
                val = *(int*)fb;
            }
            t2 >>= 8;
            *(int*)&packs->r1 = val;

            if ( t2 & 0x80 )
            {
                val = **(int**)&packs->r3;
            }
            else
            {
                val = *(int*)fd;
            }
            t2 >>= 8;
            *(int*)&packs->r3 = val;

            if ( t2 & 0x80 )
            {
                val = **(int**)&packs->r2;
            }
            else
            {
                val = *(int*)fc;
            }
            t2 >>= 8;
            *(int*)&packs->r2 = val;

        }
        else
        {
            LCOPY2( (void*)fa, &packs->r0, (void*)fb, &packs->r1 );
            LCOPY2( (void*)fc, &packs->r2, (void*)fd, &packs->r3 );
        }
    }

    return packs;
}

// Based on DG_Shade_Chanl_helper_8001D19C, but most of the body of
// the for loop extracted to a separate function?
void s12c_fadeio_800D6958( DG_OBJ* obj, int idx )
{
    // int n_normals;
    // DG_VECTOR* nidx;
    // DG_VECTOR* scrpd_nidx;
    // DG_VECTOR* scrpd_nidx2;
    // unsigned long *code;
    POLY_GT4* pack;
    DG_MDL* mdl;

    pack = obj->packs[ idx ];

    while ( obj )
    {
        mdl = obj->model; //t1;

        s12c_fadeio_800D6698(mdl);
        /*
        code = DG_PacketCode_800AB394;
        if ( mdl->flags_0 & 2 )
        {
            code = &DG_PacketCode_800AB394[1];
        }

        gte_ldrgb( code );
        scrpd_nidx = (DG_VECTOR*)0x1F800020;
        nidx = (DG_VECTOR*)mdl->normalIndexOffset_44; //a2
        n_normals = mdl->numNormals_40;

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

        if ( !( mdl->flags_0 & 0x10000 ) )
        {
            pack = s12c_fadeio_800D6744( (unsigned int*)mdl->normalFaceOffset_48, pack, obj->n_packs );
        }
        else
        {
            pack = s12c_fadeio_800D67F0( (unsigned int*)mdl->normalFaceOffset_48, pack, obj->n_packs, (unsigned int*)mdl->faceIndexOffset_3C );
        }
        obj = obj->extend;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s12c/FogShadeChanl_800D6A04.s")

