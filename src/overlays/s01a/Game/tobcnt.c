#include "common.h"
#include "libdg/libdg.h"
#include "libgcl/hash.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/game.h"

typedef struct _TobcntWork
{
    GV_ACT   actor;
    short    state;
    short    time;
    short    timeout;
    short    gradient;
    int      vox;
    POLY_G4  polys[2][12];
    LINE_G2  lines[2][166];
    DR_TPAGE tpage[2];
    TILE     tile[2];
    DR_TPAGE tpage2[2];
    DVECTOR  directions[166];
} TobcntWork;

extern int    GM_GameStatus_800AB3CC;
extern int    GM_LoadRequest_800AB3D0;
extern int    GM_GameOverTimer_800AB3D4;
extern int    GV_Clock_800AB920;
extern int    GV_PauseLevel_800AB928;
extern GV_PAD GV_PadData_800B05C0[4];

extern short tobcnt_lines[];

extern const char aTobcntTitle[]; // = "title"
extern const char aTobcntC[];     // = "tobcnt.c"

#define EXEC_LEVEL 0

char * Tobcnt_800C4070(char *buf, int x, int y, int name, unsigned int color, char *ot)
{
    DG_TEX   *tex;
    SPRT     *sprt;
    DR_TPAGE *tpage;

    tex = DG_GetTexture_8001D830(name);

    sprt = (SPRT *)buf;
    setXY0(sprt, x, y);
    setUV0(sprt, tex->field_8_offx, tex->field_9_offy);
    setWH(sprt, tex->field_A_width + 1, tex->field_B_height + 1);
    sprt->clut = tex->field_6_clut;
    LSTORE( color, &sprt->r0 );
    setSprt(sprt);
    addPrim(ot, sprt);

    tpage = (DR_TPAGE *)(buf + sizeof(SPRT));
    setDrawTPage(tpage, 1, 0, tex->field_4_tPage);
    addPrim(ot, tpage);

    return buf + sizeof(SPRT) + sizeof(DR_TPAGE);
}

int Tobcnt_800C41A0(int shade, int state)
{
    int r, gb;

    if (state < 8)
    {
        r = 128;
        gb = 255;
    }
    else
    {
        state = __min(state - 8, 8);
        r = 128 - state * 16;
        gb = 255 - ((255 - shade) * state) / 8;
    }

    return r | gb << 8 | gb << 16;
}

void Tobcnt_800C4204( TobcntWork *work, char *ot )
{
    int       x0, y0;
    int       x1, y1;
    int       width, height;
    int       state;
    int       count;
    int       color1, color2, color3;
    DR_TPAGE *tpage;
    short    *lines;
    int       flag;
    DVECTOR  *directions;
    LINE_G2  *line;
    POLY_G4  *poly;
    int       shade;

    state = work->state;
    lines = tobcnt_lines;
    count = tobcnt_lines[0];

    directions = work->directions;
    line = work->lines[GV_Clock_800AB920];
    poly = work->polys[GV_Clock_800AB920];

    lines++;

    if ( state > 0 )
    {
        if ( state < count + 16 )
        {
            work->state = state + 2;
        }
        else
        {
            work->state = 0;
        }
    }

    flag = 1;
    if ( state == 0 )
    {
        flag = 0;
        state = 16;
    }

    for ( ; count > 0; count-- )
    {
        height = 0;
        width = 0;

        if ( flag )
        {
            if ( state < 8 )
            {
                width = directions->vx >> state;
                height = directions->vy >> state;

                if ( (count % 4) == 2 )
                {
                    width = -width;
                    height = -height;
                }
            }

            if ( --state < 0 )
            {
                break;
            }
        }

        x0 = lines[0];
        x1 = lines[2];

        x0 += width;
        x1 += width * 2;

        y0 = lines[1] + height;
        y1 = lines[3] + height * 2;

        line->x0 = x0;
        line->y0 = y0;
        line->x1 = x1;
        line->y1 = y1;

        color1 = x0 - 160;
        color2 = x1 - 160;

        if (color1 < 0)
        {
            color1 = -color1;
        }
        if (color2 < 0)
        {
            color2 = -color2;
        }

        color1 = 255 - color1;
        color2 = 255 - color2;

        if (color1 > 255)
        {
            color1 = 255;
        }

        if (color2 > 255)
        {
            color2 = 255;
        }

        LSTORE(Tobcnt_800C41A0(color1, state), &line->r0);

        if (count < 3)
        {
            LSTORE(0, &line->r1);
        }
        else
        {
            LSTORE(Tobcnt_800C41A0(color2, state), &line->r1);
        }

        setLineG2(line);
        addPrim(ot, line);
        line++;

        if (state >= 8 && state <= 13)
        {
            width = -(directions->vy >> (state - 6));
            height = directions->vx >> (state - 6);

            poly->x0 = x1 - width;
            poly->y0 = y1 - height;
            poly->x1 = x0 - width;
            poly->y1 = y0 - height;
            poly->x2 = (x0 + x1) / 2;
            poly->y2 = (y0 + y1) / 2;
            poly->x3 = x0 + width;
            poly->y3 = y0 + height;

            LSTORE(0, &poly->r0);
            LSTORE(0, &poly->r1);
            LSTORE(0x804000, &poly->r2);
            LSTORE(0, &poly->r3);

            setPolyG4(poly);
            setSemiTrans(poly, 1);
            addPrim(ot, poly);
            poly++;

            poly->x0 = x1 - width;
            poly->y0 = y1 - height;
            poly->x1 = x1 + width;
            poly->y1 = y1 + height;
            poly->x2 = (x0 + x1) / 2;
            poly->y2 = (y0 + y1) / 2;
            poly->x3 = x0 + width;
            poly->y3 = y0 + height;

            LSTORE(0, &poly->r0);
            LSTORE(0, &poly->r1);
            LSTORE(0x804000, &poly->r2);
            LSTORE(0, &poly->r3);

            setPolyG4(poly);
            setSemiTrans(poly, 1);
            addPrim(ot, poly);
            poly++;
        }

        lines += 4;
        directions++;
    }

    tpage = &work->tpage[GV_Clock_800AB920];
    setDrawTPage( tpage, 1, 1, getTPage( 0, 1, 0, 0 ) );
    addPrim( ot, tpage );

    if ( work->state == 0 )
    {
        if (work->gradient > 32)
        {
            shade = (64 - work->gradient) * 2 + 100;
        }
        else
        {
            shade = work->gradient * 2 + 100;
        }

        color3 = (shade << 8) | (shade << 16);
        Tobcnt_800C4070( (char *)work->polys[GV_Clock_800AB920], 114, 121, PCX_COMING_SOON, color3, ot );
    }
}

void Tobcnt_800C4750(TobcntWork *work, char *ot, int shade)
{
    TILE     *tile;
    DR_TPAGE *tpage;

    tile = &work->tile[GV_Clock_800AB920];
    LSTORE((shade << 16) | (shade << 8) | shade, &tile->r0);
    setTile(tile);
    setSemiTrans(tile, 1);
    setXY0(tile, 0, 0);
    setWH(tile, 320, 240);
    addPrim(ot, tile);

    tpage = &work->tpage2[GV_Clock_800AB920];
    setDrawTPage(tpage, 1, 1, getTPage(0, 2, 0, 0));
    addPrim(ot, tpage);
}

void TobcntAct_800C482C(TobcntWork *work)
{
    char   *ot;
    GV_PAD *pad;
    int     shade;

    ot = DG_ChanlOTag(1);

    if (work->time < 256)
    {
        Tobcnt_800C4204(work, ot);
        Tobcnt_800C4750(work, ot, work->time);

        if ((work->time == 120) && (work->vox >= 0))
        {
            GM_StreamPlayStart_80037D1C();
        }

        work->time += 3;
        if (work->time >= 256)
        {
            if (work->state > 0)
            {
                work->time = 255;
            }
            else
            {
                work->time = 256;
                work->timeout = 300;

                GV_PauseLevel_800AB928 |= 0x1;
                DG_FreeObjectQueue_800183D4();
                GM_GameStatus_800AB3CC |= 0x4A6000;
            }
        }
    }
    else if (work->time == 256)
    {
        Tobcnt_800C4204(work, ot);

        pad = &GV_PadData_800B05C0[0];
        GM_GameStatus_800AB3CC &= ~(GAME_FLAG_BIT_29 | GAME_FLAG_BIT_28);

        if ((pad->press & (PAD_START | PAD_CIRCLE | PAD_TRIANGLE)) || (--work->timeout < 0))
        {
            if (work->timeout > 0)
            {
                sub_80032AEC(0, 63, 33);
            }

            work->time = 257;
            work->timeout = 0;
            work->gradient = 32;
        }
        else
        {
            work->gradient = (work->gradient + 1) % 64;
        }
    }
    else
    {
        shade = __min(work->time - 256, 255);
        Tobcnt_800C4750(work, ot, shade);
        Tobcnt_800C4204(work, ot);

        work->time += 4;
        if (work->time > 542)
        {
            work->time = 542;

            if (GM_StreamStatus_80037CD8() == -1)
            {
                GV_DestroyActor_800151C8(&work->actor);
            }
        }
    }
}

void TobcntDie_800C4A64(TobcntWork *work)
{
    char *stage_name;

    stage_name = (char *)aTobcntTitle;
    GV_PauseLevel_800AB928 &= ~0x1;

    DG_ResetObjectQueue_8001844C();
    GM_StreamPlayStop_80037D64();

    GM_SetArea_8002A7D8(GV_StrCode_80016CCC(stage_name), stage_name);

    GM_LoadRequest_800AB3D0 = 0x81;
    GM_GameOverTimer_800AB3D4 = 0;
}

void TobcntGetResources_800C4AD0(TobcntWork *work)
{
    int      count;
    short   *in;
    DVECTOR *out;
    SVECTOR *vecs;

    count = tobcnt_lines[0];
    in = tobcnt_lines + 1;
    out = work->directions;

    *(short *)0x1F800004 = 0;

    for (; count > 0; count--)
    {
        vecs = (SVECTOR *)0x1F800000;
        vecs[0].vx = in[0] - in[2];
        vecs[0].vy = in[1] - in[3];

        VectorNormalSS((SVECTOR *)0x1F800000, (SVECTOR *)0x1F800008);

        out->vx = -vecs[1].vx / 8;
        out->vy = -vecs[1].vy / 8;

        in += 4;
        out++;
    }
}

GV_ACT * NewTobcnt_800C4BC8(void)
{
    TobcntWork *work;

    GM_GameStatus_800AB3CC |= 0x4A6000;

    work = (TobcntWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(TobcntWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)TobcntAct_800C482C, (TActorFunction)TobcntDie_800C4A64, aTobcntC);

        work->state = 1;
        work->time = 0;

        if (GCL_GetOption_80020968('v'))
        {
            work->vox = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        }
        else
        {
            work->vox = -1;
        }

        TobcntGetResources_800C4AD0(work);
    }

    GM_Sound_80032C48(-0xFFFF02, 0);
    GM_Sound_80032C48(0x01FFFF0B, 0);
    sub_80032AEC(0, 63, 15);

    if (work->vox >= 0)
    {
        GM_VoxStream_80037E40(work->vox, 0x40000000);
    }

    GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_27;

    return &work->actor;
}
