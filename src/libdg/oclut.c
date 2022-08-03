#include "linker.h"
#include "libdg.h"
#include "dgd.h"
#include "libgv.h"

//funcs
extern DG_TEX *DG_FindTexture_8001D830( int code );
int sub_800190A0( GV_Heap* heap, long* a0, long* a1 );

//data
extern DG_TEX DG_UnknownTexture_8009D378;

//sbss
extern int GM_GameStatus_800AB3CC;

//bss
extern GV_Heap MemorySystems_800AD2F0[3];

#define SCRPAD_ADDR 0x1F800000

typedef struct unknown_scrpad_struct
{
    long pad[8]; 
    GV_Heap* pHeap;
    long unknown_24;
    long unknown_28;
    long unknown_2C;
    long unknown_30;
} unknown_scrpad_struct;

void DG_WriteObjClut_80018D28(DG_OBJ *pObj, int idx)
{
    int n_packs;
    POLY_GT4 *pPack = pObj->packs[idx];
    short val = 0x3FFF;
    if (pPack && pPack->clut != val)
    {
        if (pObj)
        {
            do
            {

                n_packs = pObj->n_packs;
                while (n_packs > 0)
                {
                    pPack->clut = val;

                    ++pPack;
                    --n_packs;
                }

                pObj = pObj->extend;
            } while (pObj);
        }
    }
}

//guessed function name
void DG_WriteObjClutUV_80018D90( DG_OBJ* obj, int idx )
{
    unsigned short  id;
    POLY_GT4       *pack;
    int             n_packs;
    short          *tex_ids;
    DG_TEX         *texture;
    unsigned short  current_id;

    pack = obj->packs[ idx ];
   
    if ( pack && pack->clut == 0x3FFF )
    {
        texture = &DG_UnknownTexture_8009D378;
        id = 0;
        while ( obj )
        {
            tex_ids = obj->model->materialOffset_50;
            for (n_packs = obj->n_packs; n_packs > 0 ; --n_packs )
            {
                current_id = *tex_ids;
                tex_ids++;
                if ( ( current_id & 0xFFFF ) != id )
                {
                    id = current_id;
                    texture = DG_FindTexture_8001D830( id );
                }
                pack->clut = texture->field_6_clut;
                pack++;
            }
            obj = obj->extend;
        }
    }
}

//there must be a way to match this without the repetition
void DG_BoundChanl_helper2_80018E5C( DG_CHNL* chnl, int idx )
{
    int       i, i2;
    DG_OBJ   *obj;
    DG_OBJS  *objs;
    DG_OBJS **objs_list;

    objs_list = chnl->mQueue;
    if (GM_GameStatus_800AB3CC & 0x08)
    {
        for ( i = chnl->mTotalObjectCount ; i > 0; --i )
        {
            objs = *objs_list;
            objs_list++;
            if (objs->flag & 0x200 && objs->bound_mode)
            {
                obj = objs->objs;
                for ( i2 = objs->n_models; i2 > 0 ; --i2 )
                {
                    if ( obj->bound_mode )
                    {
                        DG_WriteObjClut_80018D28( obj, idx );
                    }
                    obj++;
                }
            }
        }
    }
    else
    {
        for ( i = chnl->mTotalObjectCount ; i > 0; --i )
        {
            objs = *objs_list;
            objs_list++;
            if (objs->flag & 0x200 && objs->bound_mode)
            {
                obj = objs->objs;
                for ( i2 = objs->n_models; i2 > 0 ; --i2 )
                {
                    DG_WriteObjClutUV_80018D90( obj, idx );
                    obj++;
                }
            }
        }
    }
}

GV_Heap *DG_DivideChanl_helper_helper_80018FA4( int memIdx, long* unknown, int a2 )
{
    int sum;
    int i, t2;
    GV_Heap* heap;
    GV_MemoryAllocation* alloc;

    t2 = 0;
    heap = &MemorySystems_800AD2F0[ memIdx ];
    
    alloc = heap->mAllocs;
    i = heap->mUnitsCount;
    while ( i > 0 )
    {
        if (alloc->mAllocType == GV_MemoryAllocation_States_Free_0)
        {
            sum = (alloc[1].mPDataStart - alloc[0].mPDataStart ) / a2;
            t2 += sum;
        }
        --i;
        alloc++;
    }

    unknown[0] = t2;
    return heap;
}

void DG_DivideChanl_helper_80019044( int memIdx )
{
    long ret;
    GV_Heap* heap;

    unknown_scrpad_struct* unknown = (unknown_scrpad_struct*)(SCRPAD_ADDR);
    
    heap = DG_DivideChanl_helper_helper_80018FA4( memIdx, &unknown->unknown_28, 0x34);
    unknown->pHeap = heap;
    unknown->unknown_24 = 0;
    ret = sub_800190A0( heap, &unknown->unknown_24, &unknown->unknown_30 );
    
    unknown->unknown_2C = ret;
}
