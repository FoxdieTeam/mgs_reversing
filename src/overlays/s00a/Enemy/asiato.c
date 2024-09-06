#include "libgcl/hash.h"
#include "libgv/libgv.h"
#include "Game/game.h"

int SECTION("overlay.bss") NearAsiato;

int SECTION("overlay.bss") s00a_dword_800E0F94;

SVECTOR SECTION("overlay.bss") AsiatoPositions[49];

extern unsigned int GM_PlayerStatus_800ABA50;
extern SVECTOR      GM_PlayerPosition_800ABA10;
extern int          dword_800AB9D4;
extern CONTROL     *GM_WhereList_800B56D0[96];
extern OBJECT      *GM_PlayerBody_800ABA20;

// The second half of this file uses another Work struct
// (NewAsiatoChar allocates more than NewAsiato)
//
// Maybe there should be a single:
// struct AsiatoWork {
//     GV_ACT actor;
//     int    field_20;
//     int    field_24;
//     Child  children[0];
// }
// and some New* construtors allocate no children, some allocate one?
typedef struct AsiatoCharWork
{
    GV_ACT   actor;
    DG_PRIM *field_20;
    DG_TEX  *field_24;
    SVECTOR  field_28;
    SVECTOR  field_30;
    SVECTOR  field_38;
    SVECTOR  field_40;
    int      field_48;
    int      field_4C;
    int      field_50;
} AsiatoCharWork;

void AsiatoCharColor_800D0DD4(DG_PRIM *prim, DG_TEX *tex, int r, int g, int b)
{
    POLY_FT4 *poly;

    poly = &prim->packs[0]->poly_ft4;
    poly->r0 = r;
    poly->g0 = g;
    poly->b0 = b;

    poly = &prim->packs[1]->poly_ft4;
    poly->r0 = r;
    poly->g0 = g;
    poly->b0 = b;
}

void AsiatoCharPos_800D0E00(SVECTOR *out, short vx, short vy, short vz)
{
    out->vx = vx;
    out->vy = vy;
    out->vz = vz;
}

void AsiatoCharAct_800D0E10(AsiatoCharWork *work)
{
    int color;
    if (++work->field_48 > 390)
    {
        GV_DestroyActor(&work->actor);
    }
    color = 48 - work->field_48 * 48 / 690;
    AsiatoCharColor_800D0DD4(work->field_20, work->field_24, color, color, color);
}

static inline void AsiatoTexPack(POLY_FT4 *pack, DG_TEX *tex)
{
    int x, y, w, h;

    x = tex->off_x;
    w = tex->w;
    y = tex->off_y;
    h = tex->h;
    setUVWH(pack, x, y, w, h);

    pack->tpage = tex->tpage;
    pack->clut = tex->clut;
}

void AsiatoCharTexture_800D0E9C(POLY_FT4 *poly, DG_TEX *tex, int arg3, int r, int g, int b)
{
    setPolyFT4(poly);

    poly->r0 = r;
    poly->g0 = g;
    poly->b0 = b;

    if (arg3 < 4)
    {

        setSemiTrans(poly, 1);

        AsiatoTexPack(poly, tex);
        poly->tpage = (poly->tpage & 0xFF9F) | (arg3 << 5);
    }
    else
    {
        AsiatoTexPack(poly, tex);
    }
}

int AsiatoCharGetResources_800D0F90(AsiatoCharWork *work, MATRIX *mat, int arg2, int vy)
{
    SVECTOR  svec1, svec2;
    DG_PRIM *prim;
    DG_TEX  *tex;

    AsiatoCharPos_800D0E00(&svec1, 0, (*GM_WhereList_800B56D0)->rot.vy, 0);
    if (arg2 == 1)
    {
        AsiatoCharPos_800D0E00(&work->field_30, -70, 0, -140);
        AsiatoCharPos_800D0E00(&work->field_28, 70, 0, -140);
        AsiatoCharPos_800D0E00(&work->field_40, -70, 0, 140);
        AsiatoCharPos_800D0E00(&work->field_38, 70, 0, 140);
    }
    else
    {
        AsiatoCharPos_800D0E00(&work->field_28, -70, 0, -140);
        AsiatoCharPos_800D0E00(&work->field_30, 70, 0, -140);
        AsiatoCharPos_800D0E00(&work->field_38, -70, 0, 140);
        AsiatoCharPos_800D0E00(&work->field_40, 70, 0, 140);
    }

    prim = DG_GetPrim(0x12, 1, 0, &work->field_28, 0);
    work->field_20 = prim;
    if (prim != NULL)
    {
        svec2.vx = mat->t[0];
        svec2.vy = mat->t[1];
        svec2.vz = mat->t[2];
        svec2.vy = vy;
        work->field_24 = tex = DG_GetTexture(PCX_ASIATO);
        if (tex)
        {
            AsiatoCharTexture_800D0E9C(&prim->packs[0]->poly_ft4, tex, 2, 48, 48, 48);
            AsiatoCharTexture_800D0E9C(&prim->packs[1]->poly_ft4, tex, 2, 48, 48, 48);
            DG_SetPos2(&svec2, &svec1);
            DG_PutPrim(&work->field_20->world);
            return 0;
        }
    }
    return -1;
}

void AsiatoCharDie_800D116C(AsiatoCharWork *work)
{
    DG_PRIM *prim;

    prim = work->field_20;
    if (prim != 0)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
    AsiatoPositions[work->field_4C].pad = 0;
    AsiatoPositions[48].vy--;
}

GV_ACT *NewAsiatoChar_800D11DC(MATRIX *arg0, int arg1, int arg2, int arg3, int arg4)
{
    AsiatoCharWork *work;

    work = (AsiatoCharWork *)GV_NewActor(4, sizeof(AsiatoCharWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)AsiatoCharAct_800D0E10,
                         (TActorFunction)AsiatoCharDie_800D116C, "asiato.c");
        work->field_4C = arg3;
        if (AsiatoCharGetResources_800D0F90(work, arg0, arg1, arg2) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        work->field_48 = arg4;
    }
    return &work->actor;
}

typedef struct AsiatoWork
{
    GV_ACT actor;
    int    field_20;
    int    field_24;
} AsiatoWork;

void AsiatoPos_800D129C(int idx, SVECTOR *out)
{
    *out = AsiatoPositions[idx];
}

int NextAsiato_800D12D0(HZD_HDL *hdl, int idx, SVECTOR *svec2)
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

    if (sub_80028454(hdl, svec2, vec, 15, 2))
    {
        return -1;
    }

    if (vec->pad == 1)
    {
        return idx;
    }

    return -1;
}

void CleanAsiato_800D1378()
{
    int i;

    for (i = 0; i < 48; i++)
    {
        AsiatoPositions[i].pad = 0;
    }
}

int NearAsiato_800D13A0()
{
    return NearAsiato;
}


int SearchNearAsiato_800D13B0(HZD_HDL* hzd, SVECTOR* mov, int facedir, int vision_unk, int length )
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

            if ( len < max_len && len < length && GV_DiffDirAbs( facedir, GV_VecDir2(&svec) )  < vision_unk && !sub_80028454(hzd, mov, &AsiatoPositions[i], 0xF, 2) )
            {
                max_len = len;
                s4 = i;
            }
        }
    }

    if ( max_len == 100000000 )
    {
        NearAsiato = -1;
        return -1;
    }

    NearAsiato = s4;
    return s4;
}

int s00a_asiato_800D1500( HZD_HDL *hzd, SVECTOR *pos, int name )
{
    int i;
    int test;
    HZD_TRG  *triggers;

    triggers = hzd->f04_area->triggers;

    for ( i = 0 ; i < hzd->f04_area->n_triggers ; i++ )
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

int s00a_asiato_800D15D8( HZD_HDL *hzd, SVECTOR *pos )
{
    int i;
    int test;
    HZD_TRG  *triggers;

    triggers = hzd->f04_area->triggers;

    for ( i = 0 ; i < hzd->f04_area->n_triggers ; i++ )
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

int AsiatoCheck_800D16C0( HZD_HDL *hzd, SVECTOR *pos )
{
    if ( AsiatoPositions[48].vy <= 0 )
    {
        return 0;
    }

    return s00a_asiato_800D15D8( hzd, pos );
}

int s00a_asiato_800D16F8(AsiatoWork *work, HZD_HDL *hdl, SVECTOR *pos)
{
    work->field_20 = 0;

    if (s00a_asiato_800D1500(hdl, pos, HASH_POOL))
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

    return s00a_asiato_800D1500(hdl, pos, HASH_ASIATO);
}

int AsiatoIsAllowedOnMove_800D179C()
{
    // If player is moving and not on wall or prone
    return (GM_PlayerStatus_800ABA50 & (PLAYER_ON_WALL | PLAYER_MOVING | PLAYER_GROUND)) == PLAYER_MOVING;
}

int s00a_asiato_800D17BC(AsiatoWork *work)
{
    HZD_HDL *hdl;

    hdl = GM_WhereList_800B56D0[0]->map->hzd;
    if (!AsiatoIsAllowedOnMove_800D179C() || !s00a_asiato_800D16F8(work, hdl, &GM_PlayerPosition_800ABA10))
    {
        return 0;
    }

    if (dword_800AB9D4 != 2)
    {
        return dword_800AB9D4 == 10 ? 2 : 0;
    }
    return 1;
}

void RecordAsiatoPosition_800D1844()
{
    SVECTOR *svec;

    svec = &AsiatoPositions[AsiatoPositions[48].vx];
    *svec = GM_PlayerPosition_800ABA10;
    AsiatoPositions[AsiatoPositions[48].vx].pad = 1;
    AsiatoPositions[48].vy++;
    AsiatoPositions[48].vx++;
    if (AsiatoPositions[48].vx >= 48)
    {
        AsiatoPositions[48].vx = 0;
    }
}

void AsiatoAct_800D18C8(AsiatoWork *work)
{
    int     temp_v0;
    DG_OBJ *var_s0;

    temp_v0 = s00a_asiato_800D17BC(work);
    if ((temp_v0 != 0) && (AsiatoPositions[48].vy < 48))
    {
        if (temp_v0 == 1)
        {
            var_s0 = &GM_PlayerBody_800ABA20->objs->objs[12];
        }
        else
        {
            var_s0 = &GM_PlayerBody_800ABA20->objs->objs[15];
        }
        RecordAsiatoPosition_800D1844();
        GM_CurrentMap_800AB9B0 = (*GM_WhereList_800B56D0)->map->index;
        NewAsiatoChar_800D11DC(&var_s0->world, temp_v0, (*GM_WhereList_800B56D0)->levels[0],
                               AsiatoPositions[48].vx - 1, work->field_20);
    }
}

void AsiatoDie_800D1994(AsiatoWork *work)
{
}

void AsiatoInit_800D199C(AsiatoWork *work)
{
    int i;

    for (i = 0; i < 48; i++)
    {
        AsiatoCharPos_800D0E00(&AsiatoPositions[i], 0, 0, 0);
        AsiatoPositions[i].pad = 0;
    }

    AsiatoPositions[48].vx = 0;
    AsiatoPositions[48].vy = 0;
    work->field_24 = 0;
}

void AsiatoAct_800D18C8(AsiatoWork *work);

GV_ACT *NewAsiato_800D1A14(int name, int where, int argc, char **argv)
{
    AsiatoWork *work;

    work = (AsiatoWork *)GV_NewActor(4, sizeof(AsiatoWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)AsiatoAct_800D18C8,
                         (TActorFunction)AsiatoDie_800D1994, "asiato.c");
        AsiatoInit_800D199C(work);
    }

    return &work->actor;
}

GV_ACT * NewAsiatoKun_800D1A70(int name, int where, int argc, char **argv)
{
    // Identical to NewAsiato_800D1A14
    AsiatoWork *work;

    work = (AsiatoWork *)GV_NewActor(4, sizeof(AsiatoWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)AsiatoAct_800D18C8,
                                  (TActorFunction)AsiatoDie_800D1994, "asiato.c");
        AsiatoInit_800D199C(work);
    }

    return &work->actor;
}
