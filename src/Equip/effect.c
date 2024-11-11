#include "common.h"
#include "libdg/libdg.h"
#include "Game/game.h"

#define TEX_COPY_WORDS  ((sizeof(DG_TEX) - offsetof(DG_TEX, used)) / sizeof(u_short))

STATIC void EQ_MoveTexture(u_short *src, u_short *dst)
{
    u_short i;

    for (i = 0; i < TEX_COPY_WORDS; i++)
    {
        *dst++ = *src++;
    }
}

void EQ_ChangeTexture(const char *itemName1, const char *itemName2)
{
    u_short temp[TEX_COPY_WORDS];
    DG_TEX *tex1;
    DG_TEX *tex2;

    tex1 = DG_GetTexture(GV_StrCode(itemName1));
    tex2 = DG_GetTexture(GV_StrCode(itemName2));

    EQ_MoveTexture((u_short *)&tex1->used, temp);
    EQ_MoveTexture((u_short *)&tex2->used, (u_short *)&tex1->used);
    EQ_MoveTexture(temp, (u_short *)&tex2->used);
}

// Remove head model
void EQ_InvisibleHead(OBJECT *object, short *n_packs, short *raise)
{
    if (object->objs->n_models >= 7)
    {
        *n_packs = object->objs->objs[6].n_packs;
        *raise = object->objs->objs[6].raise;
        DG_FreeObjPacket(&object->objs->objs[6], 0);
        DG_FreeObjPacket(&object->objs->objs[6], 1);
        object->objs->objs[6].n_packs = 1;
        object->objs->objs[6].raise = -30000;
    }
}

// Put head model back
void EQ_VisibleHead(OBJECT *object, short *n_packs, short *raise)
{
    if (object->objs->n_models >= 7)
    {
        object->objs->objs[6].n_packs = *n_packs;
        object->objs->objs[6].raise = *raise;
        DG_FreeObjPacket(&object->objs->objs[6], 0);
        DG_FreeObjPacket(&object->objs->objs[6], 1);
    }
}

#ifdef VR_EXE
// Copies of EQ_InvisibleHead/EQ_VisibleHead
// but with additional parameter "idx"

void EQ_InvisibleUnit(OBJECT *object, int idx, short *n_packs, short *raise)
{
    if (idx < object->objs->n_models)
    {
        *n_packs = object->objs->objs[idx].n_packs;
        *raise = object->objs->objs[idx].raise;
        DG_FreeObjPacket(&object->objs->objs[idx], 0);
        DG_FreeObjPacket(&object->objs->objs[idx], 1);
        object->objs->objs[idx].n_packs = 1;
        object->objs->objs[idx].raise = -30000;
    }
}

void EQ_VisibleUnit(OBJECT *object, int idx, short *n_packs, short *raise)
{
    if (idx < object->objs->n_models)
    {
        object->objs->objs[idx].n_packs = *n_packs;
        object->objs->objs[idx].raise = *raise;
        DG_FreeObjPacket(&object->objs->objs[idx], 0);
        DG_FreeObjPacket(&object->objs->objs[idx], 1);
    }
}
#endif // VR_EXE
