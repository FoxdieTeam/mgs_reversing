#include "libdg.h"

/**gp*******************************************/
extern unsigned long DG_PacketCode_800AB394[2];
/***********************************************/

/**data*******************************/
extern SVECTOR DG_Ambient_800AB38C;
/*************************************/

//there are a few of these that are close to  gte_MulMatrix0 but with the first part changed
// clang-format off
#define gte_Unknown(r1, r2)                                     \
    {                                                           \
        gte_ldclmv(r1);                                         \
        gte_rtir();                                             \
        gte_stclmv(r2);                                         \
        gte_ldclmv((char *)r1 + 2);                             \
        gte_rtir();                                             \
        gte_stclmv((char *)r2 + 2);                             \
        gte_ldclmv((char *)r1 + 4);                             \
        gte_rtir();                                             \
        gte_stclmv((char *)r2 + 4);                             \
    }
// clang-format on

void DG_ShadeStart_8001CF80()
{
}

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

    fa &= 0x3FC;
    fb &= 0x3FC;
    fc &= 0x3FC;
    fd &= 0x3FC;

    fa = (int)(dst + fa);
    fb = (int)(dst + fb);
    fc = (int)(dst + fc);
    fd = (int)(dst + fd);

    LCOPY2( (void*)fa, &packs->r0, (void*)fb, &packs->r1 );
    LCOPY2( (void*)fc, &packs->r2, (void*)fd, &packs->r3 );
}

POLY_GT4 *DG_Shade_Chanl_helper_helper_8001CF88( unsigned int *face_normals, POLY_GT4 *packs, int n_packs )
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

POLY_GT4 *DG_Shade_Chanl_helper_helper2_8001D034( unsigned int *face_normals, POLY_GT4 *packs, int n_packs, unsigned int* face )
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

void DG_Shade_Chanl_helper_8001D19C( DG_OBJ* obj, int idx )
{
    int n_normals;
    DG_VECTOR* nidx;
    DG_VECTOR* scrpd_nidx;
    DG_VECTOR* scrpd_nidx2;
    unsigned long *code;
    POLY_GT4* pack;
    DG_MDL* mdl;

    pack = obj->packs[ idx ];

    while ( obj )
    {
        mdl = obj->model; //t1;
        code = DG_PacketCode_800AB394;
        if ( mdl->flags & DG_MODEL_TRANS )
        {
            code = &DG_PacketCode_800AB394[1];
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

        if ( !( mdl->flags & 0x10000 ) )
        {
            pack = DG_Shade_Chanl_helper_helper_8001CF88( (unsigned int*)mdl->normal_indices, pack, obj->n_packs );
        }
        else
        {
            pack = DG_Shade_Chanl_helper_helper2_8001D034( (unsigned int*)mdl->normal_indices, pack, obj->n_packs, (unsigned int*)mdl->vertex_indices );
        }
        obj = obj->extend;
    }
}

void DG_Shade_Chanl_8001D324( DG_CHNL *chnl, int idx )
{
    unsigned int flag;
    int          i, j;
    DG_OBJ      *obj;
    DG_OBJS     *objs;
    DG_OBJS    **objs_queue;

    i = chnl->mTotalObjectCount;
    objs_queue = chnl->mQueue;

    for ( ; i > 0 ; --i )
    {
        objs = *objs_queue;
        objs_queue++;

        if ( !objs->bound_mode ) continue;

        flag = objs->flag;

        if ( !( flag & 8 ) ) continue;

        gte_SetRotMatrix( objs->light );
        gte_SetColorMatrix( &objs->light[1] );

        if ( flag & 0x100 )
        {
            gte_SetBackColor( objs->light->t[0], objs->light->t[1], objs->light->t[2] );
        }

        j = objs->n_models;
        obj = objs->objs;

        for ( ; j > 0 ; --j )
        {
            if ( obj->bound_mode )
            {

                gte_Unknown( &obj->world, 0x1F800000 );
                gte_SetLightMatrix( 0x1F800000 );
                DG_Shade_Chanl_helper_8001D19C( obj, idx );
            }
            obj++;
        }

        if ( objs->flag & DG_FLAG_AMBIENT )
        {
            gte_SetBackColor( DG_Ambient_800AB38C.vx, DG_Ambient_800AB38C.vy, DG_Ambient_800AB38C.vz );
        }
    }
}

void DG_ShadeEnd_8001D5C0(void)
{
}
