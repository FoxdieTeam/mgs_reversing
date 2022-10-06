#include "libdg.h"

void DG_TransStart_8001DC88()
{
}

unsigned int DG_Trans_Chanl_helper_helper_helper_8001DC90( unsigned int normal_idx, POLY_GT4 *packs )
{
    int *pack_ptr;
    int a2, a3, t3, t5, num, stride;
    int i, temp;
    unsigned int scrpd_idx, scrpd_idx2;
    unsigned char t6;

    scrpd_idx = 0x1F800000;
    t3 = *( int* )(scrpd_idx + 0x3F8);
    if ( !t3 ) return 0;
    
    
    t5 = *( int* )( scrpd_idx + 0x3FC );
    num = 0;
    stride = 0;
    
    pack_ptr = ( int* )&packs->x0;
    a3 = 8;
    i = 4;
    t6 = 32;
    scrpd_idx2 = 0x1f800000;
    
    for ( ; i > 0; i-- )
    {
        a2 = normal_idx & 0x7f;        

        if ((normal_idx & 0x80) == 0)
        {
            a2 = (a2 * 4) + scrpd_idx2;
            temp = ((unsigned int*)a2)[0x80];
            a2 = *( int* )a2;
            num = num + temp;
            stride++;
        }
        else
        {
            a2 = t5 + ( a2 << 3 );
            temp = ( ( unsigned short* )scrpd_idx2 )[0xFF];
            a2 = ( ( short* )a2 )[3];

            if (temp & 4)
            {
                * (pack_ptr - 1 ) = (t3 + a2) - 4;
            }
            
            a2 = *(int *)(t3 + a2);
        }
      
        *pack_ptr = a2;
        pack_ptr += 3;
        normal_idx = ( normal_idx << ( t6 - a3 ) ) | ( normal_idx >> a3 );
        a3 = a3 + 8;
    }

    if (stride == 2)
    {
        return num / 2;
    }
    else if (stride == 1)
    {
        return num;
    }
    else if (stride == 3)
    {
        return num / 3;
    }
    return 0;
}

POLY_GT4 * DG_Trans_Chanl_helper_helper_8001DD90(unsigned int *pFaceIndices, POLY_GT4 *pPoly, int nPacks)
{
    unsigned char bVar1;
    int iVar2;
    unsigned int uVar7;
    int count;
    unsigned int scratchpad;
    unsigned int uVar8;
    unsigned int *n0, *n1, *n2, *n3;
    
    for (count = nPacks - 1; count >= 0; (pPoly++)->tag = uVar7, pFaceIndices++, count--)
    {
        scratchpad = 0x1f800000;
        uVar7 = 0;
        uVar8 = 0xfffe0000;

        n0 = (unsigned int *)*pFaceIndices;
        
        if (*pFaceIndices & 0x80808080)
        {
            uVar7 = DG_Trans_Chanl_helper_helper_helper_8001DC90(*pFaceIndices, pPoly);
            continue;
        }

        n1 = (unsigned int *)*pFaceIndices;
        n2 = (unsigned int *)*pFaceIndices;
        n3 = (unsigned int *)*pFaceIndices;
            
        n0 = (unsigned int *)((unsigned int)n0 << 2);
        n1 = (unsigned int *)((unsigned int)n1 >> 6);
        n2 = (unsigned int *)((unsigned int)n2 >> 22);
        n3 = (unsigned int *)((unsigned int)n3 >> 14);

        n0 = (unsigned int *)((int)n0 & 0x1fc);
        n1 = (unsigned int *)((int)n1 & 0x1fc);
        n2 = (unsigned int *)((int)n2 & 0x1fc);
        n3 = (unsigned int *)((int)n3 & 0x1fc);

        n0 = (unsigned int *)((int)n0 + scratchpad);
        n1 = (unsigned int *)((int)n1 + scratchpad);
        n2 = (unsigned int *)((int)n2 + scratchpad);
        n3 = (unsigned int *)((int)n3 + scratchpad);


        if ((*(unsigned short *)(scratchpad + 0x1fe) & 1))
        {
            bVar1 = 0;
                
            if (n0[0x80] >> 24) 
            {
                bVar1 = n0[0x80] >> 24 & n1[0x80] >> 24 & n2[0x80] >> 24 & n3[0x80] >> 24;
            }
                
            if (bVar1) 
            {
                continue;
            }
        }

        gte_ldsxy3(*n0, *n1, *n2);
        gte_nclip();

        LCOPY(n3, &pPoly->x3);
            
        gte_stopz((int *)0x1f8001f8);
        gte_stsxy3_gt3(&pPoly->tag);

        iVar2 = *(int *)(scratchpad + 0x1f8);

        if (iVar2 < 1)
        {
            if (!(*(short *)(scratchpad + 0x1fc)) || !iVar2)
            {
                continue;
            }

            uVar7 = (((-iVar2) << 8) & uVar8) | 0x10000;
        }
        else
        {
            uVar7 = iVar2 << 8 & uVar8;
        }

        uVar7 |= (((int) (n0[0x80] + n3[0x80])) / 2) & 0xffff;
    }

    return pPoly;
}