#include "libdg.h"

extern unsigned long DG_PacketCode_800AB394[2];

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

            gte_strgb3( &scrpd_nidx2[-1].field_0_x, &scrpd_nidx2[-1].field_4_y, &scrpd_nidx2[-1].field_8_z );
        }

        if ( !( mdl->flags_0 & 0x10000 ) )
        {
            pack = DG_Shade_Chanl_helper_helper_8001CF88( (unsigned int*)mdl->normalFaceOffset_48, pack, obj->n_packs );
        }
        else
        {
            pack = DG_Shade_Chanl_helper_helper2_8001D034( (unsigned int*)mdl->normalFaceOffset_48, pack, obj->n_packs, (unsigned int*)mdl->faceIndexOffset_3C );
        }
        obj = obj->extend;
    }
}