#include "libdg.h"

DG_TEX dword_8009D3C4 = {0};

// #define STATIC static
#define STATIC

STATIC int DG_AllocPacks( DG_OBJ *obj, int idx )
{
    int     total_packs = 0;
    DG_OBJ *object = obj;

    while (object)
    {
        total_packs += object->n_packs;
        object = object->extend;
    }

    if (!GV_AllocMemory2(idx, total_packs * sizeof(POLY_GT4), (void **)&obj->packs[idx]))
    {
        return -1;
    }
    return 0;
}

STATIC void DG_InitPolyGT4Pack( DG_OBJ *obj, int idx )
{
    POLY_GT4 *pack;

    int rgbCode = 0x3E808080;

    if ((obj->model->flags & DG_MODEL_TRANS) == 0)
    {
        rgbCode = 0x3C808080;
    }

    pack = obj->packs[idx];
    while (obj)
    {
        int n_packs;
        for (n_packs = obj->n_packs; n_packs > 0; n_packs--)
        {
            setPolyGT4(pack);

            *(int *)&pack->r0 = rgbCode;
            *(int *)&pack->r1 = rgbCode;
            *(int *)&pack->r2 = rgbCode;
            *(int *)&pack->r3 = rgbCode;
            pack++;
        }
        obj = obj->extend;
    }
}

static inline void Apply( DG_TEX *tex, unsigned char *texcoords, POLY_GT4 *pack )
{
    unsigned int u0 = tex->off_x;
    unsigned int v0 = tex->off_y;
    int          u11 = tex->w + 1;
    int          v11 = tex->h + 1;

    pack->u0 = ((texcoords[0] * u11) / 256) + u0;
    pack->v0 = ((texcoords[1] * v11) / 256) + v0;
    pack->u1 = ((texcoords[2] * u11) / 256) + u0;
    pack->v1 = ((texcoords[3] * v11) / 256) + v0;
    pack->u2 = ((texcoords[6] * u11) / 256) + u0;
    pack->v2 = ((texcoords[7] * v11) / 256) + v0;
    pack->u3 = ((texcoords[4] * u11) / 256) + u0;
    pack->v3 = ((texcoords[5] * v11) / 256) + v0;
    pack->tpage = tex->tpage;
    pack->clut = tex->clut;
}

void DG_WriteObjPacketUV( DG_OBJ* obj, int idx )
{
    unsigned short  id;
    POLY_GT4       *pack;
    int             n_packs;
    short          *tex_ids;
    DG_TEX         *texture;
    unsigned short  current_id;
    unsigned char  *texcoords;

    pack = obj->packs[ idx ];

    if ( pack )
    {
        texture = &dword_8009D3C4;
        id = 0;

        while ( obj )
        {
            tex_ids = obj->model->materials;
            texcoords = obj->model->texcoords;
            for (n_packs = obj->n_packs; n_packs > 0 ; --n_packs )
            {
                current_id = *tex_ids;
                tex_ids++;

                if ( current_id != id )
                {
                    id = current_id;
                    texture = DG_GetTexture( current_id );
                }

                Apply(texture, texcoords, pack);
                pack++;
                texcoords += 8;
            }
            obj = obj->extend;
        }
    }
}

void DG_WriteObjPacketRGB( DG_OBJ *obj, int idx )
{
    POLY_GT4 *pack = obj->packs[idx];
    if (pack && obj)
    {
        do {
            CVECTOR *pack_rgbs = obj->rgbs;
            if (pack_rgbs)
            {
                int n_packs;
                for (n_packs = obj->n_packs; n_packs > 0; --n_packs)
                {
                    LCOPY2(&pack_rgbs[0], &pack->r0, &pack_rgbs[1], &pack->r1);
                    LCOPY2(&pack_rgbs[3], &pack->r2, &pack_rgbs[2], &pack->r3);

                    ++pack;
                    pack_rgbs += 4; // to next set of rgb
                }
            }
            obj = obj->extend;
        } while (obj);
    }
}

int DG_MakeObjPacket( DG_OBJ *obj, int idx, int flags )
{
    if (DG_AllocPacks(obj, idx) < 0)
    {
        return -1;
    }

    DG_InitPolyGT4Pack(obj, idx);

    if ((flags & DG_FLAG_TEXT) != 0)
    {
        DG_WriteObjPacketUV(obj, idx);
    }

    if ((flags & DG_FLAG_PAINT) != 0)
    {
        DG_WriteObjPacketRGB(obj, idx);
    }

    return 0;
}

void DG_FreeObjPacket( DG_OBJ *obj, int idx )
{
    POLY_GT4 **ppPack;

    ppPack = &obj->packs[idx];
    if (*ppPack)
    {
        GV_FreeMemory2(idx, (void **)ppPack);
        *ppPack = 0;
    }
}

int DG_MakeObjsPacket( DG_OBJS *objs, int idx )
{

    int flag = objs->flag;
    int n_models = objs->n_models;

    DG_OBJ *obj = objs->objs;
    while (n_models > 0)
    {
        if (!obj->packs[idx])
        {
            if (DG_MakeObjPacket(obj, idx, flag) < 0)
            {
                return -1;
            }
        }
        obj++;
        n_models--;
    }
    return 0;
}

void DG_FreeObjsPacket( DG_OBJS *objs, int idx )
{
    int     n_models;
    DG_OBJ *obj;

    n_models = objs->n_models;
    for (obj = objs->objs; n_models > 0; ++obj)
    {
        DG_FreeObjPacket(obj, idx);
        --n_models;
    }
}
