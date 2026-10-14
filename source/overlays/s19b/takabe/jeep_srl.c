#include <stdio.h>
#include <stdlib.h>
#include "strcode.h"
#include "game/game.h"
#include "game/camera.h"
#include "libgcl/libgcl.h"
#include "takabe/thing.h"

#include "jeep_system.h"


typedef struct _JeepSegDef
{
    short    field_0;
    short    n_lines;  /* 0x02 */
    short    n_faces;  /* 0x04 */
    short    field_6;
    void    *lines;    /* 0x08: JeepSegLine[] */
    void    *faces;    /* 0x0C: JeepSegFace[] */
    int      field_10;
    u_char  *flags;    /* 0x14: n_lines bytes, twice */
} JeepSegDef;

/* One of the 16 road pieces scrolling under the jeep */
typedef struct _JeepScrollSeg
{
    SVECTOR     pos;      /* 0x00 */
    SVECTOR     dir;      /* 0x08: offset to the next piece */
    short       shear_x;  /* 0x10 */
    short       shear_y;  /* 0x12 */
    short       field_14; /* 0x14 */
    char        pad_16[0x18 - 0x16];
    DG_OBJS    *objs;     /* 0x18 */
    DG_LITS    *lits;     /* 0x1C */
    JeepSegDef *def;      /* 0x20 */
    int         flags;    /* 0x24 */
    int         event;    /* 0x28 */
} JeepScrollSeg; /* 0x2C */

typedef struct _JeepSegLine
{
    SVECTOR v[2]; /* pad words hold a radius */
} JeepSegLine; /* 0x10 */

typedef struct _JeepSegFace
{
    char    pad_0[0x10];
    SVECTOR v[4]; /* 0x10 */
} JeepSegFace; /* 0x30 */

typedef struct _JeepHzdFace
{
    SVECTOR min;  /* 0x00 */
    SVECTOR max;  /* 0x08 */
    SVECTOR v[4]; /* 0x10 */
} JeepHzdFace; /* 0x30 */

/* A road piece model and its resources */
typedef struct _JeepModel
{
    DG_DEF     *def;     /* 0x00: 'k' cache */
    DG_LITS    *lit;     /* 0x04: 'l' cache */
    int        *hzd;     /* 0x08: 'h' cache */
    JeepSegDef *segdef;  /* 0x0C: hzd[4] */
    DG_OBJS    *objs;    /* 0x10 */
    char        pad_14[0x1C - 0x14];
} JeepModel; /* 0x1C */

/* Entry of the road script (s19b_dword_800C354C), terminated by model == -1 */
typedef struct _JeepRoadCmd
{
    short model;       /* road piece model */
    short count;       /* number of pieces */
    short x, y;        /* target curve */
    short speed_x;
    short speed_y;
    short event_delay; /* the event is raised on this piece */
    short event;
} JeepRoadCmd;

typedef struct _Work
{
    GV_ACT        work;
    int           map;           /* 0x20 */
    int           name;          /* 0x24 */
    MATRIX        mtx_28;        /* 0x28 */
    JeepModel     models[13];    /* 0x48 */
    JeepScrollSeg segs[16];      /* 0x1B4 */
    DG_OBJS      *field_474[16]; /* 0x474: model 12, shown instead of far model 0 pieces */
    HZD_HDL      *hzd;           /* 0x4B4 */
    JeepHzdFace  *face_cursor;   /* 0x4B8: cursor into faces */
    JeepHzdFace   faces[24];     /* 0x4BC */
    HZD_SEG      *seg_cursor;    /* 0x93C: cursor into hzd_segs */
    HZD_SEG       hzd_segs[48];  /* 0x940 */
    int           max_lights;    /* 0xC40 */
    DG_LITS      *lits;          /* 0xC44: the map's lights, refilled every frame */
    int           curve_x;       /* 0xC48 */
    int           curve_y;       /* 0xC4C */
    int           cmd_count;     /* 0xC50 */
    int           event_delay;   /* 0xC54 */
    JeepRoadCmd  *cmd;           /* 0xC58 */
    char          pad_C5C[0x4];
    int           field_C60;     /* 0xC60 */
    int           field_C64;     /* 0xC64 */
    int           reshaded;      /* 0xC68 */
    int           head;          /* 0xC6C: index of the farthest piece */
    int           proc_gate1;    /* 0xC70 */
    int           proc_gate2;    /* 0xC74 */
    int           proc_end;      /* 0xC78 */
    char          pad_C7C[0x4];
    int           fade_time;     /* 0xC80 */
} Work;

extern Work *s19b_dword_800DE5B0;


void *NewJeepGate(int name, SVECTOR *pos, int side);
void *NewJeepGlass(int name, SVECTOR *pos, int side);
void *NewJeepLamp(SVECTOR *root_pos, int tex_id, int unused);
void *s19b_jeep2_800D6F24(int name, int map); // NewJeep2
void  s19b_jeep_800D2170(SVECTOR *col0, SVECTOR *col1, SVECTOR *col2, MATRIX *mtx);
void  s19b_jeep_800D21DC(int ang, MATRIX *mat, SVECTOR *out);
void  s19b_jeep_gls_800CE5F8(DG_OBJS *objs);
void  s19b_jeep_gls_800CE628(SVECTOR *pos, SVECTOR *src, JeepHzdFace *face, int flag);
void  s19b_jeep_gls_800CE83C(SVECTOR *src, SVECTOR *dst);
void  s19b_jeep_gls_800CE8B8(SVECTOR *src, SVECTOR *dst);
void  s19b_jeep_gls_800CEFE4(Work *work, int disable, JeepScrollSeg *seg);
void  s19b_jeep_gls_800CE400(Work *work);
DG_OBJS *s19b_jeep_gls_800CE52C(int idx, Work *work);
void  s19b_jeep_gls_800CF088(void);
void  s19b_jeep_srl_800CD790(Work *work);
void *NewJeep(int name, int where);
void  s19b_jlamp_800D0CE0(void);
void  s19b_jlamp_800D0D40(void);
int   s19b_jeep_gls_800CEDFC(int arg0, int arg1);
void  s19b_jeep_srl_800CD638(Work *work, int *out);
void  s19b_jeep_srl_800CD7B4(Work *work, JeepScrollSeg *unused, DG_LIT *out);
void  s19b_jeep_gls_800CEE7C(Work *work, int arg1, SVECTOR *pos);
extern void  Takabe_ReshadeModel(DG_OBJS *objs, void *lit);
extern void *NewPadVibration(unsigned char *, int);
extern void *NewFadeInOut(int arg0, int arg1);
extern GM_CameraSystemWork GM_Camera;
extern u_char s19b_dword_800C36FC[];
extern u_char s19b_dword_800C3710[];
void  s19b_jeep_gls_800CE8DC(struct _Work *work, JeepScrollSeg *seg, int flag);
extern void RotTransSV(SVECTOR *v0, SVECTOR *v1, long *sz);
extern MATRIX s19b_dword_800C36DC; /* shear matrix of the road pieces */
extern u_short s19b_dword_800C3530[]; /* 13 model-name hashes */

extern JeepRoadCmd s19b_dword_800C354C[];

void s19b_jeep_srl_800CD638(Work *work, int *out)
{
    JeepRoadCmd *p = work->cmd;

    work->curve_x = GV_NearSpeed(work->curve_x, p->x, p->speed_x);
    work->curve_y = GV_NearSpeed(work->curve_y, p->y, p->speed_y);
    out[0] = p->model;
    out[1] = work->curve_x;
    out[2] = work->curve_y;
    out[3] = p->event;

    if (work->cmd_count > 0)
    {
        if (--work->event_delay == 0)
        {
            Takabe_JeepSystem.seg_event = p->event;
        }
        else
        {
            Takabe_JeepSystem.seg_event = 0;
        }
        if (--work->cmd_count == 0)
        {
            work->cmd++;
            p = work->cmd;
            if (p->model == -1)
            {
                p = s19b_dword_800C354C;
                work->cmd = p;
            }
            work->cmd_count = p->count;
            work->event_delay = p->event_delay;
        }
    }
    else
    {
        Takabe_JeepSystem.seg_event = 0;
        if (Takabe_JeepSystem.field_44 != 0)
        {
            Takabe_JeepSystem.field_44--;
            work->cmd_count = -work->cmd_count;
        }
    }
}
void s19b_jeep_srl_800CD790(Work *work)
{
    JeepRoadCmd *p = s19b_dword_800C354C;
    work->cmd = p;
    work->cmd_count = p->count;
    work->event_delay = p->event_delay;
}
void s19b_jeep_srl_800CD7B4(Work *work, JeepScrollSeg *unused, DG_LIT *out)
{
    JeepScrollSeg *seg;
    DG_LIT        *vtx;
    DG_OBJS       *objs;
    SVECTOR        pos;
    long           flag;
    int            i;
    int            k;
    int            n;
    int            map;

    for (i = 0; i < 16; i++)
    {
        k = (i - work->head) & 0xF;
        seg = &work->segs[i];
        if ((unsigned)(k - 4) < 8)
        {
            DG_SetPos2(&seg->pos, &DG_ZeroVector);
            DG_PutObjs(seg->objs);
            s19b_dword_800C36DC.m[0][2] = seg->shear_x;
            s19b_dword_800C36DC.m[1][2] = seg->shear_y;
            MulMatrix0(&seg->objs->world, &s19b_dword_800C36DC, &seg->objs->world);
            SetRotMatrix(&seg->objs->world);
            objs = seg->objs;
            map = GM_CurrentMap;
            objs->group_id = map;
            work->field_474[i]->root = &seg->objs->world;
            if (seg->objs->def == work->models[0].def && abs(seg->pos.vz) >= 0x1771)
            {
                work->field_474[i]->flag &= ~0x80;
                seg->objs->flag |= 0x80;
            }
            else
            {
                seg->objs->flag &= ~0x80;
                work->field_474[i]->flag |= 0x80;
            }
            n = seg->lits->n_lights;
            vtx = seg->lits->lights;
            while (n > 0)
            {
                RotTransSV(&vtx->point, &pos, &flag);
                out->point = pos;
                out->r_range = vtx->r_range >> 1;
                out->e_range = vtx->e_range >> 1;
                out->color = vtx->color;
                work->lits->n_lights++;
                vtx++;
                out++;
                n--;
            }
            if ((unsigned)(k - 5) < 5)
            {
                s19b_jeep_gls_800CE8DC(work, seg, 1);
            }
            else
            {
                s19b_jeep_gls_800CE8DC(work, seg, 0);
            }
            seg->flags &= ~2;
        }
        else
        {
            seg->objs->flag |= 0x80;
            work->field_474[i]->flag |= 0x80;
        }
        seg->flags &= ~1;
    }
}

void s19b_jeep_srl_800CDAA4(Work *work)
{
    DG_LIT        *vtx;
    DG_LITS       *lits;
    JeepScrollSeg *seg;
    JeepScrollSeg *next;
    int            out[4];
    int            i;
    int            j;
    int            k;
    int            z;
    int            n;
    int            v;

    GM_CurrentMap = work->map;
    if (work->reshaded == 0)
    {
        for (j = 0; j < 13; j++)
        {
            Takabe_ReshadeModel(work->models[j].objs, work->models[j].lit);
        }
        work->reshaded = 1;
    }
    Takabe_JeepSystem.scroll = Takabe_JeepSystem.offset;
    lits = work->lits;
    lits->n_lights = 0;
    vtx = lits->lights;
    work->face_cursor = work->faces;
    work->seg_cursor = work->hzd_segs;
    work->hzd->n_d_segs = 0;
    work->hzd->n_d_flrs = 0;
    for (i = 0; i < 16; i++)
    {
        seg = &work->segs[i];
        z = seg->pos.vz + Takabe_JeepSystem.scroll.vz;
        if (z >= 32000)
        {
            s19b_jeep_srl_800CD638(work, out);
            v = out[1];
            seg->dir.vx = v / 2;
            seg->shear_x = (-v << 11) / 4000;
            v = out[2];
            seg->dir.vy = v / 2;
            seg->shear_y = (-v << 11) / 4000;
            seg->flags = 3;
            seg->event = out[3];
            z -= 64000;
            k = (i + 1) & 0xF;
            next = &work->segs[k];
            seg->pos.vx = next->pos.vx + next->dir.vx;
            seg->pos.vy = next->pos.vy + next->dir.vy;
            seg->pos.vx += seg->dir.vx;
            seg->pos.vy += seg->dir.vy;
            if (k < i)
            {
                seg->pos.vx -= Takabe_JeepSystem.scroll.vx;
                seg->pos.vy -= Takabe_JeepSystem.scroll.vy;
            }
            work->head = i;
            s19b_jeep_gls_800CE5F8(seg->objs);
            seg->objs = s19b_jeep_gls_800CE52C(out[0], work);
            seg->lits = work->models[out[0]].lit;
            seg->def = work->models[out[0]].segdef;
            seg->pos.vz = z;
            seg->pos.vx += Takabe_JeepSystem.scroll.vx;
            seg->pos.vy += Takabe_JeepSystem.scroll.vy;
            s19b_jeep_gls_800CEE7C(work, out[3], &seg->pos);
            s19b_jeep_gls_800CEFE4(work, out[0], seg);
        }
        else
        {
            seg->pos.vz = z;
            seg->pos.vx += Takabe_JeepSystem.scroll.vx;
            seg->pos.vy += Takabe_JeepSystem.scroll.vy;
        }
    }
    SetSpadStack(SPAD_STACK_ADDR);
    s19b_jeep_srl_800CD7B4(work, seg, vtx);
    ResetSpadStack();
    if ((u_int)work->lits->n_lights > (u_int)work->max_lights)
    {
        printf("<<<<< light over !!!!!!!(jeep.srl.c) >>>>>\n");
    }
    s19b_jlamp_800D0D40();
    GM_Camera.flag |= 2;
    GM_Camera.zoom = 0xF0;
    if (work->fade_time != 0)
    {
        n = work->fade_time + 1;
        work->fade_time = n;
        if (n >= 0x47)
        {
            if (work->proc_end != 0 && GM_GameOverTimer == 0)
            {
                GCL_ExecProc(work->proc_end, NULL);
            }
        }
        else if (n >= 0x1F)
        {
            if (n == 0x1F)
            {
                NewPadVibration(s19b_dword_800C36FC, 1);
                NewPadVibration(s19b_dword_800C3710, 2);
            }
        }
    }
    else
    {
        if (s19b_jeep_gls_800CEDFC(Takabe_JeepSystem.control->mov.vz, 9600) == 14)
        {
            NewFadeInOut(2, 0x14);
            work->fade_time = 1;
        }
    }
    Takabe_JeepSystem.world.t[0] += Takabe_JeepSystem.scroll.vx;
    Takabe_JeepSystem.world.t[1] += Takabe_JeepSystem.scroll.vy;
    Takabe_JeepSystem.world.t[2] += Takabe_JeepSystem.scroll.vz;
}
void s19b_jeep_srl_800CDAA4(Work *work);

void s19b_jeep_srl_800CDF48(Work *work)
{
    int *n_lights;
    int  i;

    for (i = 0; i < 16; i++)
    {
        s19b_jeep_gls_800CE5F8(work->field_474[i]);
    }
    for (i = 0; i < 16; i++)
    {
        s19b_jeep_gls_800CE5F8(work->segs[i].objs);
    }
    for (i = 0; i < 13; i++)
    {
        DG_OBJS *objs = work->models[i].objs;
        DG_FreePreshade(objs);
        DG_FreeObjs(objs);
    }
    Takabe_JeepSystem.field_78 = 0;
    GM_StreamPlayStop();
    n_lights = &work->lits->n_lights;
    *n_lights = work->max_lights;
    GM_GameStatus &= ~0x20000000;
}
void s19b_jeep_srl_800CDF48(Work *work);

int s19b_jeep_srl_800CE020(Work *work, int name, int where)
{
    JeepScrollSeg *seg;
    DG_OBJS       *objs;
    DG_OBJS      **gate;
    MAP           *map;
    int            i;
    int            z;
    int            n;

    s19b_jeep_gls_800CF088();
    GM_CurrentMap = where;
    work->map = where;
    work->name = name;
    work->field_C64 = 0;
    work->mtx_28 = DG_ZeroMatrix;
    s19b_jeep_gls_800CE400(work);
    map = GM_GetMap(GM_CurrentMap);
    work->lits = map->lit;
    work->max_lights = work->lits->n_lights;
    printf("max light:%d\n", work->max_lights);
    Takabe_JeepSystem.otacon = THING_Gcl_GetInt('c');
    work->field_C60 = 0;
    work->reshaded = 0;
    work->head = 0;
    Takabe_JeepSystem.offset = DG_ZeroVector;
    Takabe_JeepSystem.scroll = Takabe_JeepSystem.offset;
    Takabe_JeepSystem.world_pos.vz = 0;
    Takabe_JeepSystem.world_pos.vy = 0;
    Takabe_JeepSystem.world_pos.vx = 0;
    seg = work->segs;
    for (i = 0, z = -31500; i < 16; seg++, i++, z += 4000)
    {
        seg->objs = s19b_jeep_gls_800CE52C(0, work);
        seg->lits = work->models[0].lit;
        seg->def = work->models[0].segdef;
        seg->dir.vz = -2000;
        seg->shear_x = 0;
        seg->field_14 = 0;
        seg->dir.vx = 0;
        seg->dir.vy = 0;
        seg->pos.vx = 0;
        seg->pos.vy = 0;
        seg->pos.vz = z;
        seg->flags = 1;
        seg->event = 0;
        Takabe_JeepSystem.seg_pos = seg->pos;
        if (Takabe_JeepSystem.seg_pos.vz < 16000)
        {
            s19b_jeep_gls_800CEFE4(work, 0, seg);
        }
    }
    gate = work->field_474;
    for (n = 16; n > 0; n--)
    {
        objs = s19b_jeep_gls_800CE52C(12, work);
        *gate++ = objs;
        objs->flag |= 0x80;
    }
    work->hzd = GM_GetMap(work->map)->hzd;
    s19b_dword_800DE5B0 = work;
    if (GCL_GetOption('e'))
    {
        work->proc_gate1 = GCL_StrToInt(GCL_NextStr());
        work->proc_gate2 = GCL_StrToInt(GCL_NextStr());
        work->proc_end = GCL_StrToInt(GCL_NextStr());
    }
    Takabe_JeepSystem.field_78 = 0x800;
    Takabe_JeepSystem.world = DG_ZeroMatrix;
    NewJeep(GV_StrCode("j_snake"), where);
    s19b_jlamp_800D0CE0();
    s19b_jeep_srl_800CD790(work);
    work->cmd = s19b_dword_800C354C;
    GM_GameStatus |= STATE_NOSLOW;
    return 0;
}
int s19b_jeep_srl_800CE020(Work *work, int name, int where);

void *NewJeepScroll(int name, int where)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_PREV, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jeep_srl_800CDAA4, s19b_jeep_srl_800CDF48, "jeep_srl.c");

        if (s19b_jeep_srl_800CE020(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}

void s19b_jeep_gls_800CE400(Work *work)
{
    JeepModel *light;
    DG_DEF    *def;
    DG_LITS   *lit;
    int       *hzd;
    DG_OBJS   *objs;
    int        i;

    light = work->models;

    for (i = 0; i < 13; light++, i++)
    {
        light->def = def = GV_GetCache(GV_CacheID(s19b_dword_800C3530[i], 'k'));
        light->lit = lit = GV_GetCache(GV_CacheID(s19b_dword_800C3530[i], 'l'));
        if (lit == NULL)
        {
            light->lit = lit = work->models[0].lit;
        }

        light->hzd     = hzd = GV_GetCache(GV_CacheID(s19b_dword_800C3530[i], 'h'));
        light->segdef = (JeepSegDef *)hzd[4];
        light->objs    = objs = DG_MakeObjs(def, 'W', 0);

        if (lit != NULL)
        {
            DG_MakePreshade(objs, lit->lights, lit->n_lights);
        }
        else
        {
            DG_MakePreshade(objs, NULL, NULL);
        }

        light->objs->flag |= 0x80;
    }
}
DG_OBJS *s19b_jeep_gls_800CE52C(int idx, Work *work)
{
    JeepModel *lights = work->models;
    DG_OBJS   *objs;
    DG_OBJ    *src;
    DG_OBJ    *dst;
    DG_OBJ    *next_src;
    DG_OBJ    *next_dst;
    int        i;
    int        map;

    objs = DG_MakeObjs(lights[idx].def, 'W', 0);
    next_dst = objs->objs;
    next_src = lights[idx].objs->objs;
    for (i = objs->n_models; i > 0; i--)
    {
        src = next_src;
        next_src = src + 1;
        dst = next_dst;
        next_dst = dst + 1;
        while (dst != NULL)
        {
            dst->rgbs = src->rgbs;
            dst = dst->extend;
            src = src->extend;
        }
    }
    DG_SetPos(&DG_ZeroMatrix);
    DG_PutObjs(objs);
    DG_QueueObjs(objs);
    map = GM_CurrentMap;
    objs->group_id = map;
    return objs;
}
void s19b_jeep_gls_800CE5F8(DG_OBJS *objs)
{
    DG_DequeueObjs(objs);
    objs->objs[0].rgbs = NULL;
    DG_FreeObjs(objs);
}
void s19b_jeep_gls_800CE628(SVECTOR *pos, SVECTOR *src, JeepHzdFace *face, int flag)
{
    VECTOR   d2;
    VECTOR   d1;
    VECTOR   cross;
    SVECTOR  nrm;
    SVECTOR *p = src;

    face->v[0].vx = p->vx;
    face->v[0].vz = p->vy;
    face->v[0].vy = p->vz;
    p++;
    face->v[1].vx = p->vx;
    face->v[1].vz = p->vy;
    face->v[1].vy = p->vz;
    p++;
    face->v[2].vx = p->vx;
    face->v[2].vz = p->vy;
    face->v[2].vy = p->vz;
    p++;
    face->v[3].vx = p->vx;
    face->v[3].vz = p->vy;
    face->v[3].vy = p->vz;
    if (face->v[3].vy < face->v[0].vy)
    {
        face->v[0].vy = face->v[1].vy = face->v[2].vy = face->v[3].vy = pos->vz;
    }
    if (flag)
    {
        d1.vx = src[1].vx - src[0].vx;
        d1.vy = src[1].vy - src[0].vy;
        d1.vz = src[1].vz - src[0].vz;
        d2.vx = src[2].vx - src[1].vx;
        d2.vy = src[2].vy - src[1].vy;
        d2.vz = src[2].vz - src[1].vz;
        OuterProduct12(&d2, &d1, &cross);
        VectorNormalS(&cross, &nrm);
        face->v[0].pad = nrm.vx >> 4;
        face->v[1].pad = nrm.vz >> 4;
        face->v[2].pad = nrm.vy >> 4;
    }
    face->min.vy = pos->vz - 2000;
    face->max.vy = pos->vz + 2000;
    face->min.vx = pos->vx - 8000;
    face->max.vx = pos->vx + 8000;
    face->min.vz = pos->vy - 8000;
    face->max.vz = pos->vy + 8000;
    face->min.pad = 0;
}
void s19b_jeep_gls_800CE83C(SVECTOR *src, SVECTOR *dst)
{
    dst[0].vx  = src->vx;
    dst[0].vz  = src->vy;
    dst[0].vy  = src->vz;
    dst[0].pad = src->pad;
    src++;
    dst[1].vx  = src->vx;
    dst[1].vz  = src->vy;
    dst[1].vy  = src->vz;
    dst[1].pad = src->pad;
    HZD_SetDynamicSegment((HZD_SEG *)dst, (HZD_SEG *)dst);
}
void s19b_jeep_gls_800CE8B8(SVECTOR *src, SVECTOR *dst)
{
    dst->vx = src->vx;
    dst->vy = src->vz;
    dst->vz = src->vy;
}
/* Queues the dynamic floors and (if do_segs) walls of a road piece in the hazard.
 * The wall loop has its own def and cnt: with variables shared by both loops they are
 * live in several basic blocks and get allocated after the single-block temporaries,
 * which changes the registers. */
void s19b_jeep_gls_800CE8DC(struct _Work *work, JeepScrollSeg *road, int do_segs)
{
    JeepSegLine *line;
    JeepSegDef  *def;
    JeepSegDef  *def2;
    u_char      *flags1;
    u_char      *flags2;
    SVECTOR     *vec;
    JeepSegFace *face;
    short       *cnt;
    short       *cnt2;
    int          i;
    SVECTOR      verts[4];

    SetRotMatrix(&road->objs->world);
    def = road->def;
    cnt = &work->hzd->n_d_segs;
    face = def->faces;

    for (i = def->n_faces; i > 0; i--)
    {
        if (*cnt < 24)
        {
            vec = verts;
            s19b_jeep_gls_800CE8B8(&face->v[0], vec++);
            s19b_jeep_gls_800CE8B8(&face->v[1], vec++);
            s19b_jeep_gls_800CE8B8(&face->v[2], vec++);
            s19b_jeep_gls_800CE8B8(&face->v[3], vec++);
            DG_PutVector(verts, verts, 4);

            if (Takabe_JeepSystem.scroll.vz != 0)
            {
                s19b_jeep_gls_800CE628(&road->pos, verts, work->face_cursor, road->flags & 2);
            }

            face++;
            HZD_QueueDynamicFloor(work->hzd, (HZD_FLR *)work->face_cursor++);
        }
    }

    if (do_segs)
    {
        def2 = road->def;
        cnt2 = &work->hzd->n_d_segs;
        flags1 = def2->flags;
        line = def2->lines;
        flags2 = flags1 + def2->n_lines;

        for (i = def2->n_lines; i > 0; i--)
        {
            if (*cnt2 < 48)
            {
                vec = verts;
                s19b_jeep_gls_800CE8B8(&line->v[0], vec);
                s19b_jeep_gls_800CE8B8(&line->v[1], &verts[1]);
                DG_PutVector(vec, vec, 2);

                verts[0].pad = line->v[0].pad / 2;
                verts[1].pad = line->v[1].pad / 2;

                if (Takabe_JeepSystem.scroll.vz != 0)
                {
                    s19b_jeep_gls_800CE83C(vec, (SVECTOR *)work->seg_cursor);
                }

                line++;
                HZD_QueueDynamicSegment2(work->hzd, work->seg_cursor++, *flags1 | (*flags2 << 8));
                flags1++;
                flags2++;
            }
        }
    }
}
void s19b_jeep_gls_800CEB2C(int arg0, SVECTOR *rot)
{
    Work   *work = s19b_dword_800DE5B0;
    int     idx = work->head;
    int     base;
    SVECTOR dir;

    base = work->segs[idx].pos.vz - 0x7D0;
    base = (arg0 - base) / 4000; /* two statements: quotient reuses the dividend reg */
    idx += base;
    idx &= 0xF;
    dir = work->segs[idx].dir;
    rot->vy = GV_VecDir2(&dir);
    rot->vx = ratan2(-dir.vy, SquareRoot0(dir.vx * dir.vx + dir.vz * dir.vz));
    rot->vz = 0;
}
void s19b_jeep_gls_800CEC24(int arg0, SVECTOR *out)
{
    Work          *work = s19b_dword_800DE5B0;
    int            idx = work->head;
    int            base;
    JeepScrollSeg *seg;
    JeepScrollSeg *prev;
    SVECTOR        zero;
    SVECTOR        dir;
    SVECTOR        sum;
    MATRIX         mtx;

    base = work->segs[idx].pos.vz - 0x7D0;
    base = (arg0 - base) / 4000; /* two statements: quotient reuses the dividend reg */
    idx += base;
    seg = &work->segs[idx & 0xF];
    if (arg0 < seg->pos.vz)
    {
        prev = &work->segs[(idx + 15) & 0xF];
    }
    else
    {
        prev = seg;
        seg = &work->segs[(idx + 1) & 0xF];
    }
    zero = DG_ZeroVector;
    dir = seg->dir;
    sum.vx = dir.vx + prev->dir.vx;
    sum.vy = dir.vy + prev->dir.vy;
    sum.vz = -4000;
    s19b_jeep_800D2170(&zero, &dir, &sum, &mtx);
    s19b_jeep_800D21DC(((seg->pos.vz - arg0) << 12) / 4000, &mtx, out);
    GV_AddVec3(out, &seg->pos, out);
}
int s19b_jeep_gls_800CEDFC(int arg0, int arg1)
{
    Work          *work = s19b_dword_800DE5B0;
    int            idx = work->head;
    int            base;
    JeepScrollSeg *seg;

    base = work->segs[idx].pos.vz - 0x7D0;
    idx += (arg0 - base - arg1) / 4000;
    idx &= 0xF;
    seg = &work->segs[idx];
    return seg->event;
}

void s19b_jeep_gls_800CEE7C(Work *work, int arg1, SVECTOR *pos)
{
    GCL_ARGS args;
    SVECTOR  diff;
    int      state;
    int      proc_id;
    
    Takabe_JeepSystem.seg_pos = *pos;
    state = Takabe_JeepSystem.seg_event;

    GV_SubVec3(pos, &Takabe_JeepSystem.scroll, &diff);

    if (state == 2)
    {
        Takabe_JeepSystem.field_7C = 0;

        NewJeepGate(1, &diff, 0);
        NewJeepGate(1, &diff, 1);
        NewJeepGlass(2, &diff, 0);
        NewJeepGlass(2, &diff, 1);

        proc_id = work->proc_gate1;
        if (proc_id)
        {
            args.argc = 0;
            args.argv = NULL;
            GCL_ExecProc(proc_id, &args);
        }
    }
    else if (state == 4)
    {
        Takabe_JeepSystem.field_7C = 0;

        NewJeepGate(1, &diff, 0);
        NewJeepGate(1, &diff, 1);
        NewJeepGlass(2, &diff, 0);
        NewJeepGlass(2, &diff, 1);

        proc_id = work->proc_gate2;
        if (proc_id)
        {
            args.argc = 0;
            args.argv = NULL;
            GCL_ExecProc(proc_id, &args);
        }
    }
    else if (state == 5)
    {
        s19b_jeep2_800D6F24(GV_StrCode("j_liquid"), GM_CurrentMap);
    }
}

void s19b_jeep_gls_800CEFE4(Work *work, int disable, JeepScrollSeg *seg)
{
    SVECTOR diff;
    SVECTOR pos;

    GV_SubVec3(&Takabe_JeepSystem.seg_pos, &Takabe_JeepSystem.scroll, &diff);

    if (disable == 0)
    {
        pos.vx = diff.vx + 1562;
        pos.vy = diff.vy + 1815;
        pos.vz = diff.vz - 500;
        NewJeepLamp(&pos, PCX_JEEP_BONBORI_ADD, 0);

        pos.vx = diff.vx - 1562;
        pos.vy = diff.vy + 1815;
        pos.vz = diff.vz - 500;
        NewJeepLamp(&pos, PCX_JEEP_BONBORI_ADD, 0);
    }
}

void s19b_jeep_gls_800CF088(void)
{
    GV_ZeroMemory(&Takabe_JeepSystem, sizeof(Takabe_JeepSystem));
}
