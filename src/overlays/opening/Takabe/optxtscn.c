#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Takabe/thing.h"

typedef struct OpTxtScnUnk
{
    RECT  field_0;
    RECT  field_8;
    char *start;
    char *current;
} OpTxtScnUnk;

typedef struct OpTxtScnPrims
{
    DR_STP  stp[2];
    DR_MOVE move[2][4]; // Only 2 out of the 4 are used
} OpTxtScnPrims;

typedef struct OpTxtScnWork
{
    GV_ACT         actor;
    int            field_20;
    OpTxtScnUnk   *field_24;
    DG_TEX        *field_28;
    DG_TEX        *field_2C;
    RECT           field_30;
    RECT           field_38;
    OpTxtScnPrims *field_40;
    DG_OBJS       *field_44_objs[2];
    MATRIX         field_4C_light[2];
} OpTxtScnWork;

char opening_dword_800C32C8[] =
{
    0x0D, 0x05, 0x14, 0x01, 0x0C, 0x00, 0x07, 0x05, 0x01, 0x12, 0x00, 0x0F, 0x13, 0x80, 0x80, 0x0D,
    0x05, 0x0D, 0x0F, 0x12, 0x19, 0x00, 0x03, 0x08, 0x05, 0x03, 0x0B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B,
    0x1B, 0x1B, 0x1B, 0x1B, 0x0F, 0x0B, 0x80, 0x80, 0x13, 0x19, 0x13, 0x14, 0x05, 0x0D, 0x00, 0x13,
    0x14, 0x01, 0x12, 0x14, 0x80, 0x80, 0x80, 0x00, 0x0B, 0x0F, 0x0E, 0x0B, 0x01, 0x09, 0x00, 0x0E,
    0x0F, 0x00, 0x0D, 0x0F, 0x0B, 0x15, 0x14, 0x05, 0x0B, 0x09, 0x00, 0x08, 0x01, 0x00, 0x04, 0x01,
    0x10, 0x01, 0x00, 0x0B, 0x19, 0x0F, 0x0B, 0x15, 0x03, 0x08, 0x0F, 0x15, 0x00, 0x0F, 0x19, 0x0F,
    0x02, 0x09, 0x00, 0x01, 0x14, 0x2D, 0x13, 0x08, 0x01, 0x03, 0x08, 0x0F, 0x15, 0x00, 0x0E, 0x0F,
    0x00, 0x0B, 0x19, 0x15, 0x15, 0x13, 0x08, 0x15, 0x14, 0x15, 0x00, 0x04, 0x01, 0x1B, 0x80, 0x00,
    0x0D, 0x0F, 0x13, 0x08, 0x09, 0x0D, 0x0F, 0x00, 0x14, 0x05, 0x0B, 0x09, 0x00, 0x07, 0x01, 0x00,
    0x0B, 0x01, 0x0B, 0x15, 0x00, 0x08, 0x01, 0x13, 0x13, 0x08, 0x01, 0x00, 0x0E, 0x0F, 0x15, 0x12,
    0x19, 0x0F, 0x0B, 0x15, 0x00, 0x17, 0x0F, 0x00, 0x0D, 0x0F, 0x14, 0x14, 0x05, 0x09, 0x12, 0x15,
    0x00, 0x0E, 0x01, 0x12, 0x01, 0x02, 0x01, 0x00, 0x13, 0x0F, 0x12, 0x05, 0x00, 0x17, 0x0F, 0x00,
    0x13, 0x0F, 0x13, 0x08, 0x09, 0x00, 0x13, 0x15, 0x12, 0x15, 0x0B, 0x0F, 0x14, 0x0F, 0x00, 0x04,
    0x01, 0x1B, 0x80, 0x00, 0x04, 0x05, 0x08, 0x01, 0x00, 0x0B, 0x05, 0x0E, 0x14, 0x0F, 0x15, 0x00,
    0x17, 0x0F, 0x00, 0x09, 0x0E, 0x0F, 0x12, 0x15, 0x1B, 0x80, 0x80, 0x0D, 0x19, 0x00, 0x0E, 0x01,
    0x0D, 0x05, 0x00, 0x09, 0x13, 0x00, 0x0B, 0x1B, 0x14, 0x01, 0x0B, 0x01, 0x02, 0x05, 0x80, 0x14,
    0x08, 0x01, 0x0E, 0x0B, 0x00, 0x19, 0x0F, 0x15, 0x1B, 0x80, 0x80, 0x13, 0x19, 0x13, 0x14, 0x05,
    0x0D, 0x00, 0x12, 0x05, 0x02, 0x0F, 0x0F, 0x14, 0x80, 0x80, 0x80, 0xFF
};

OpTxtScnUnk opening_dword_800C33E4[2] =
{
    {{0, 0, 32, 10}, {0, 0, 32, 70},   opening_dword_800C32C8, opening_dword_800C32C8},
    {{0, 0, 20, 5},  {0, 128, 32, 70}, opening_dword_800C32C8, opening_dword_800C32C8}
};

extern int    GV_Clock;
extern int    GM_CurrentMap;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

#define getTPageX(tp) (((tp) << 6) & 0x3c0)
#define getTPageY(tp) ((((tp) << 4) & 0x100) + (((tp) >> 2) & 0x200))

void Optxtscn_800CCBDC(DG_TEX *tex, RECT *out)
{
    out->x = (tex->off_x >> 2) + getTPageX(tex->tpage);
    out->y = tex->off_y + getTPageY(tex->tpage);
    out->w = (tex->w + 3) / 4;
    out->h = tex->h;
}

void Optxtscn_800CCC4C(OpTxtScnWork *work, OpTxtScnUnk *unk, DR_MOVE *move, int xoff)
{
    RECT rect;
    int  x, y;

    x = work->field_30.x + unk->field_8.x + unk->field_0.x;
    y = work->field_30.y + unk->field_8.y + (unk->field_0.h - 2) * 7;

    rect.x = work->field_38.x + xoff;
    rect.y = work->field_38.y;
    rect.w = 1;
    rect.h = 7;

    SetDrawMove(move, &rect, x, y);

    if (++unk->field_0.x > (unk->field_0.w - 2))
    {
        unk->field_0.x = 1;
        unk->field_0.y = 1;
    }
}

void Optxtscn_800CCD08(OpTxtScnWork *work, OpTxtScnUnk *unk, DR_MOVE *move)
{
    RECT rect;
    int  x, y;

    x = work->field_30.x + unk->field_8.x;
    y = work->field_30.y + unk->field_8.y;

    rect.x = x;
    rect.y = y + 14;
    rect.w = unk->field_8.w;
    rect.h = unk->field_8.h - 14;

    SetDrawMove(move, &rect, x, y + 7);

    unk->field_0.y = 0;
    unk->field_0.x = 1;
}

void Optxtscn_800CCD80(OpTxtScnWork *work)
{
    RECT rect;
    rect.x = work->field_30.x;
    rect.y = work->field_30.y;
    rect.w = work->field_30.w;
    rect.h = work->field_30.h;

    ClearImage(&rect, 0, 0, 0);
}

char Optxtscn_800CCDCC(char x, OpTxtScnUnk *unk)
{
    if (x >= 28)
    {
        x = 0;
    }

    return x;
}

void OptxtscnAct_800CCDE8(OpTxtScnWork *work)
{
    OpTxtScnUnk *unk;
    DR_MOVE     *move;
    char        *ot;
    int          i;
    char         xoff;

    work->field_20++;

    if (work->field_30.w == 0)
    {
        return;
    }

    if (work->field_20 < 2)
    {
        return;
    }

    unk = work->field_24;
    move = work->field_40->move[GV_Clock];
    ot = DG_ChanlOTag(1);

    for (i = 2; i > 0; i--)
    {
        if (*unk->current == 0xFF)
        {
            unk->current = unk->start;
        }

        xoff = *unk->current++;

        if ((unk->field_0.y == 0) && (xoff != 0x80))
        {
            if (unk == &work->field_24[1])
            {
                xoff = GV_RandU(32);
            }

            xoff = Optxtscn_800CCDCC(xoff, unk);
            Optxtscn_800CCC4C(work, unk, move, xoff);
        }
        else
        {
            Optxtscn_800CCD08(work, unk, move);
        }

        addPrim(ot, move);

        unk++;
        move++;
    }

    addPrim(ot, &work->field_40->stp[GV_Clock]);

    if (work->field_20 == 2)
    {
        Optxtscn_800CCD80(work);
    }
}

void OpTxtScnDie_800CCFFC(OpTxtScnWork *work)
{
    int i;

    if (work->field_40)
    {
        GV_DelayedFree(work->field_40);
    }

    s16b_800C4594(0x53B6, 0x448B);

    for (i = 0; i < 2; i++)
    {
        if (work->field_44_objs[i])
        {
            DG_DequeueObjs(work->field_44_objs[i]);
            DG_FreeObjs(work->field_44_objs[i]);
        }
    }
}

int OptxtscnGetResources_800CD080(OpTxtScnWork *work)
{
    unsigned short cacheIds[2];
    DG_DEF        *def;
    DG_OBJS       *objs;
    OpTxtScnPrims *prims;
    DG_TEX        *tex;
    MATRIX        *mat;
    int            i;

    work->field_28 = tex = DG_GetTexture(0xCC22);
    Optxtscn_800CCBDC(tex, &work->field_30);

    work->field_2C = tex = DG_GetTexture(0xEF71);
    Optxtscn_800CCBDC(tex, &work->field_38);

    s16b_800C4594(0x53B6, 0xA8A4);

    work->field_40 = prims = GV_Malloc(sizeof(OpTxtScnPrims));
    SetDrawStp(&prims->stp[0], 0);
    SetDrawStp(&prims->stp[1], 0);

    work->field_24 = opening_dword_800C33E4;
    do {} while (0);

    mat = &DG_ZeroMatrix;
    cacheIds[0] = 0xEFAA;
    cacheIds[1] = 0xEFAB;
    DG_SetPos(mat);

    for (i = 0; i < 2; i++)
    {
        def = GV_GetCache(GV_CacheID(cacheIds[i], 'k'));
        if (def == NULL)
        {
            return -1;
        }

        objs = DG_MakeObjs(def, 0x15D, 0);
        work->field_44_objs[i] = objs;
        DG_PutObjs(objs);
        objs->light = work->field_4C_light;
        DG_QueueObjs(objs);
        DG_GroupObjs(objs, GM_CurrentMap);

        tex = DG_GetTexture(def->model[0].materials[0]);
        tex->clut = work->field_2C->clut;
        tex->tpage = (work->field_28->tpage & 0xFF9F) | 0x20;

        tex->off_x = work->field_24[i].field_8.x * 4;
        tex->off_y = work->field_24[i].field_8.y;
        tex->w = work->field_24[i].field_8.w * 4 - 1;
        tex->h = work->field_24[i].field_8.h - 1;
    }

    work->field_4C_light[0].t[0] = 0x800;
    work->field_4C_light[0].t[1] = 0x800;
    work->field_4C_light[0].t[2] = 0x800;
    return 0;
}

GV_ACT *NewOpTxtScn_800CD29C(void)
{
    OpTxtScnWork *work;

    work = (OpTxtScnWork *)GV_NewActor(EXEC_LEVEL, sizeof(OpTxtScnWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)OptxtscnAct_800CCDE8,
                         (GV_ACTFUNC)OpTxtScnDie_800CCFFC, "optxtscn.c");
        if (OptxtscnGetResources_800CD080(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
