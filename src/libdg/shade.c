#include "libdg.h"

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