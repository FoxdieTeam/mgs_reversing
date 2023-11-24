#include "libdg/libdg.h"
#include "libgcl/libgcl.h"

// Modified versions of functions from libdg

DG_TEX DG_UnknownTexture_800C34FC = {0};

extern int GM_GameStatus_800AB3CC;

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

