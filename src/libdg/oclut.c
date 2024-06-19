#include "linker.h"
#include "libdg.h"
#include "libgcl/libgcl.h"

//**data**********************************//
DG_TEX DG_UnknownTexture_8009D378 = {0};
//****************************************//

//**sbss****************************//
extern int GM_GameStatus_800AB3CC;
//*********************************//

void DG_WriteObjClut_80018D28(DG_OBJ *pObj, int idx)
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

// guessed function name
void DG_WriteObjClutUV_80018D90(DG_OBJ *obj, int idx)
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
        texture = &DG_UnknownTexture_8009D378;
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
                    texture = DG_GetTexture_8001D830(id);
                }
                pack->clut = texture->field_6_clut;
                pack++;
            }
            obj = obj->extend;
        }
    }
}

// there must be a way to match this without the repetition
void DG_BoundChanl_helper2_80018E5C(DG_CHNL *chnl, int idx)
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
                        DG_WriteObjClut_80018D28(obj, idx);
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
                    DG_WriteObjClutUV_80018D90(obj, idx);
                    obj++;
                }
            }
        }
    }
}
