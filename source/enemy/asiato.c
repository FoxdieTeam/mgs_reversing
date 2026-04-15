#include "asiato.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "strcode.h"

extern CONTROL *GM_WhereList[96];

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL  GV_ACTOR_LEVEL4

#define SEGMENT_ATR ( HZD_SEG_NO_NAVIGATE )

typedef struct _AsiatoCharWork
{
    GV_ACT   actor;
    DG_PRIM *prim;
    DG_TEX  *tex;
    SVECTOR  pos[4];
    int      field_48;
    int      field_4C;
    int      field_50;
} AsiatoCharWork;

/*---------------------------------------------------------------------------*/

int SECTION(".bss") NearAsiatoDist;
int SECTION(".bss") s00a_dword_800E0F94;
SVECTOR SECTION(".bss") AsiatoPositions[49];

/*---------------------------------------------------------------------------*/

static void AsiatoChar_ShadePacks(DG_PRIM *prim, DG_TEX *tex, int r, int g, int b)
{
    POLY_FT4 *poly;

    poly = prim->packs[0];
    setRGB0(poly, r, g, b);

    poly = prim->packs[1];
    setRGB0(poly, r, g, b);
}

static void AsiatoChar_SetPos(SVECTOR *vec, short x, short y, short z)
{
    vec->vx = x;
    vec->vy = y;
    vec->vz = z;
}

static void AsiatoChar_Act(AsiatoCharWork *work)
{
    int shade;
    if (++work->field_48 > 390)
    {
        GV_DestroyActor(&work->actor);
    }
    shade = 48 - work->field_48 * 48 / 690;
    AsiatoChar_ShadePacks(work->prim, work->tex, shade, shade, shade);
}

static void AsiatoChar_InitPacks(POLY_FT4 *poly, DG_TEX *tex, int abr, int r, int g, int b)
{
    setPolyFT4(poly);
    setRGB0(poly, r, g, b);

    if (abr < 4)
    {
        setSemiTrans(poly, 1);
        DG_SetPacketTexture4(poly, tex);
        poly->tpage = (poly->tpage & ~0x60) | (abr << 5);
    }
    else
    {
        DG_SetPacketTexture4(poly, tex);
    }
}

static int AsiatoChar_GetResources(AsiatoCharWork *work, MATRIX *world, int arg2, int vy)
{
    SVECTOR  svec1, svec2;
    DG_PRIM *prim;
    DG_TEX  *tex;

    AsiatoChar_SetPos(&svec1, 0, (*GM_WhereList)->rot.vy, 0);
    if (arg2 == 1)
    {
        AsiatoChar_SetPos(&work->pos[1], -70, 0, -140);
        AsiatoChar_SetPos(&work->pos[0], 70, 0, -140);
        AsiatoChar_SetPos(&work->pos[3], -70, 0, 140);
        AsiatoChar_SetPos(&work->pos[2], 70, 0, 140);
    }
    else
    {
        AsiatoChar_SetPos(&work->pos[0], -70, 0, -140);
        AsiatoChar_SetPos(&work->pos[1], 70, 0, -140);
        AsiatoChar_SetPos(&work->pos[2], -70, 0, 140);
        AsiatoChar_SetPos(&work->pos[3], 70, 0, 140);
    }

    prim = GM_MakePrim(DG_PRIM_POLY_FT4, 1, &work->pos[0], NULL);
    work->prim = prim;
    if (prim != NULL)
    {
        svec2.vx = world->t[0];
        svec2.vy = world->t[1];
        svec2.vz = world->t[2];
        svec2.vy = vy;
        work->tex = tex = DG_GetTexture(PCX_ASIATO);
        if (tex)
        {
            AsiatoChar_InitPacks(prim->packs[0], tex, 2, 48, 48, 48);
            AsiatoChar_InitPacks(prim->packs[1], tex, 2, 48, 48, 48);
            DG_SetPos2(&svec2, &svec1);
            DG_PutPrim(&work->prim->world);
            return 0;
        }
    }
    return -1;
}

static void AsiatoChar_Die(AsiatoCharWork *work)
{
    GM_FreePrim(work->prim);

    AsiatoPositions[work->field_4C].pad = 0;
    AsiatoPositions[48].vy--;
}

/*---------------------------------------------------------------------------*/

void *NewAsiatoChar(MATRIX *world, int arg1, int arg2, int arg3, int arg4)
{
    AsiatoCharWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(AsiatoCharWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, AsiatoChar_Act, AsiatoChar_Die, "asiato.c");
        work->field_4C = arg3;
        if (AsiatoChar_GetResources(work, world, arg1, arg2) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        work->field_48 = arg4;
    }
    return (void *)work;
}

/*---------------------------------------------------------------------------*/

void AsiatoPos(int idx, SVECTOR *out)
{
    *out = AsiatoPositions[idx];
}

int NextAsiato(HZD_HDL *hdl, int idx, SVECTOR *svec2)
{
    SVECTOR *vec;

    if (++idx >= 48)
    {
        idx = 0;
    }

    vec = &AsiatoPositions[idx];
    if (GV_DiffVec3(svec2, vec) >= 5000)
    {
        return -1;
    }

    if (HZD_LineCheck(hdl, svec2, vec, HZD_CHECK_ALL, SEGMENT_ATR))
    {
        return -1;
    }

    if (vec->pad == 1)
    {
        return idx;
    }

    return -1;
}

void CleanAsiato(void)
{
    int i;

    for (i = 0; i < 48; i++)
    {
        AsiatoPositions[i].pad = 0;
    }
}

int NearAsiato(void)
{
    return NearAsiatoDist;
}

int SearchNearAsiato( HZD_HDL *hzd, SVECTOR *mov, int facedir, int vision_unk, int length )
{
    int i;
    int len;
    int max_len;
    SVECTOR svec;

    int s4;
    max_len = 100000000;

    s4 = 0;
    for ( i = 0; i < 48 ; i++ )
    {
        if (AsiatoPositions[i].pad == 1 )
        {
            GV_SubVec3( &AsiatoPositions[i], mov, &svec );
            svec.vy = 0;
            len = GV_VecLen3( &svec );

            if ( len < max_len && len < length && GV_DiffDirAbs( facedir, GV_VecDir2(&svec) ) < vision_unk &&
                !HZD_LineCheck(hzd, mov, &AsiatoPositions[i], HZD_CHECK_ALL, SEGMENT_ATR) )
            {
                max_len = len;
                s4 = i;
            }
        }
    }

    if ( max_len == 100000000 )
    {
        NearAsiatoDist = -1;
        return -1;
    }

    NearAsiatoDist = s4;
    return s4;
}

static int asiato_800D1500( HZD_HDL *hzd, SVECTOR *pos, int name )
{
    int i;
    int test;
    HZD_TRG  *triggers;

    triggers = hzd->group->triggers;

    for ( i = 0 ; i < hzd->group->n_triggers ; i++ )
    {
            if ( triggers->trap.name_id == name )
            {
                test = pos->vx;
                if ( test >= triggers->trap.b1.x  &&  triggers->trap.b2.x >= test )
                {
                    test = pos->vz;
                    if ( test >= triggers->trap.b1.z  &&  triggers->trap.b2.z >= test )
                    {
                        test = pos->vy;
                        if ( test >= triggers->trap.b1.y  &&  triggers->trap.b2.y >= test )
                        {
                            return 1;
                        }
                    }
                }
            }

            triggers++;
    }
    return 0;
}

static int asiato_800D15D8( HZD_HDL *hzd, SVECTOR *pos )
{
    int i;
    int test;
    HZD_TRG  *triggers;

    triggers = hzd->group->triggers;

    for ( i = 0 ; i < hzd->group->n_triggers ; i++ )
    {
            if ( triggers->trap.name_id == HASH_ASIATO || triggers->trap.name_id == HASH_POOLATO )
            {
                test = pos->vx;
                if ( test >= triggers->trap.b1.x  &&  triggers->trap.b2.x >= test )
                {
                    test = pos->vz;
                    if ( test >= triggers->trap.b1.z  &&  triggers->trap.b2.z >= test )
                    {
                        test = pos->vy;
                        if ( test >= triggers->trap.b1.y  &&  triggers->trap.b2.y >= test )
                        {
                            return 1;
                        }
                    }
                }
            }

            triggers++;
    }
    return 0;
}

int AsiatoCheck( HZD_HDL *hzd, SVECTOR *pos )
{
    if ( AsiatoPositions[48].vy <= 0 )
    {
        return 0;
    }

    return asiato_800D15D8( hzd, pos );
}

/*---------------------------------------------------------------------------*/

typedef struct _AsiatoWork
{
    GV_ACT actor;
    int    field_20;
    int    field_24;
} AsiatoWork;

static int asiato_800D16F8(AsiatoWork *work, HZD_HDL *hdl, SVECTOR *pos)
{
    work->field_20 = 0;

    if (asiato_800D1500(hdl, pos, HASH_POOL))
    {
        work->field_24 = 60;
        return 0;
    }

    if (work->field_24 > 0)
    {
        work->field_20 = 360 - work->field_24 * 2;
        work->field_24--;
        return 1;
    }

    return asiato_800D1500(hdl, pos, HASH_ASIATO);
}

static int AsiatoIsAllowedOnMove_800D179C()
{
    // If player is moving and not on wall or prone
    return (GM_PlayerStatus & (PLAYER_CAUTION | PLAYER_MOVE | PLAYER_GROUND)) == PLAYER_MOVE;
}

static int asiato_800D17BC(AsiatoWork *work)
{
    HZD_HDL *hdl;

    hdl = GM_WhereList[0]->map->hzd;
    if (!AsiatoIsAllowedOnMove_800D179C() || !asiato_800D16F8(work, hdl, &GM_PlayerPosition))
    {
        return 0;
    }

    if (dword_800AB9D4 != 2)
    {
        return dword_800AB9D4 == 10 ? 2 : 0;
    }
    return 1;
}

static void RecordAsiatoPosition(void)
{
    SVECTOR *svec;

    svec = &AsiatoPositions[AsiatoPositions[48].vx];
    *svec = GM_PlayerPosition;
    AsiatoPositions[AsiatoPositions[48].vx].pad = 1;
    AsiatoPositions[48].vy++;
    AsiatoPositions[48].vx++;
    if (AsiatoPositions[48].vx >= 48)
    {
        AsiatoPositions[48].vx = 0;
    }
}

static void Act(AsiatoWork *work)
{
    int     temp_v0;
    DG_OBJ *obj;

    temp_v0 = asiato_800D17BC(work);
    if ((temp_v0 != 0) && (AsiatoPositions[48].vy < 48))
    {
        if (temp_v0 == 1)
        {
            obj = &GM_PlayerBody->objs->objs[12];
        }
        else
        {
            obj = &GM_PlayerBody->objs->objs[15];
        }
        RecordAsiatoPosition();
        GM_SetCurrentMap((*GM_WhereList)->map->index);
        NewAsiatoChar(&obj->world, temp_v0, (*GM_WhereList)->levels[0], AsiatoPositions[48].vx - 1, work->field_20);
    }
}

static void Die(AsiatoWork *work)
{
    /* do nothing */
}

static void GetResources(AsiatoWork *work)
{
    int i;

    for (i = 0; i < 48; i++)
    {
        AsiatoChar_SetPos(&AsiatoPositions[i], 0, 0, 0);
        AsiatoPositions[i].pad = 0;
    }

    AsiatoPositions[48].vx = 0;
    AsiatoPositions[48].vy = 0;
    work->field_24 = 0;
}

/*---------------------------------------------------------------------------*/

void *NewAsiato(int name, int where, int argc, char **argv)
{
    AsiatoWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(AsiatoWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "asiato.c");
        GetResources(work);
    }

    return (void *)work;
}

void *NewAsiatoKun(int name, int where, int argc, char **argv)
{
    // Identical to NewAsiato
    AsiatoWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(AsiatoWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "asiato.c");
        GetResources(work);
    }

    return (void *)work;
}
