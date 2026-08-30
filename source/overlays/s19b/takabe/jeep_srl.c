#include <stdio.h>
#include <stdlib.h>
#include "strcode.h"
#include "game/game.h"
#include "game/camera.h"
#include "libgcl/libgcl.h"
#include "takabe/thing.h"

typedef struct _JEEP_SYSTEM
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2[0x10];
    SVECTOR  pos;
    SVECTOR  field_20;
    int      field_28;
    int      field_2C;
    int      field_30;
    char     pad3[0x38 - 0x30 - sizeof(int)];
    SVECTOR  field_38;
    int      field_40;
    int      field_44;
    int      field_48;
    char     pad4[0x60 - 0x48 - sizeof(int)];
    OBJECT  *body;
    char     pad5[0x78 - 0x60 - sizeof(OBJECT *)];
    int      field_78;
    int      field_7C;
    MATRIX   world;
    char     pad6[0xCC];
} JEEP_SYSTEM;

extern JEEP_SYSTEM Takabe_JeepSystem;

#define EXEC_LEVEL GV_ACTOR_PREV

typedef struct _JeepScrollSeg
{
    SVECTOR  pos;      /* 0x00 */
    SVECTOR  field_8;  /* 0x08 */
    short    field_10; /* 0x10 */
    short    field_12; /* 0x12 */
    short    field_14; /* 0x14 */
    char     pad_16[0x18 - 0x16];
    DG_OBJS *field_18; /* 0x18 */
    int     *field_1C; /* 0x1C: count, then JeepVtx[] */
    struct _JeepSegDef *field_20; /* 0x20 */
    int      field_24; /* 0x24 */
    int      field_28; /* 0x28 */
} JeepScrollSeg; /* 0x2C */

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

typedef struct _JeepSegLine
{
    SVECTOR v[2]; /* pad words hold a radius */
} JeepSegLine; /* 0x10 */

typedef struct _JeepSegFace
{
    char    pad_0[0x10];
    SVECTOR v[4]; /* 0x10 */
} JeepSegFace; /* 0x30 */

typedef struct _JeepVtx
{
    SVECTOR pos;    /* 0x00 */
    u_short field_8;
    u_short field_A;
    CVECTOR field_C;
} JeepVtx; /* 0x10 */

typedef struct _JeepHzdFace
{
    SVECTOR min;  /* 0x00 */
    SVECTOR max;  /* 0x08 */
    SVECTOR v[4]; /* 0x10 */
} JeepHzdFace; /* 0x30 */

typedef struct _JeepLight
{
    DG_DEF  *def;     /* 0x00: 'k' cache */
    int     *lit;     /* 0x04: 'l' cache, count followed by DG_LITs */
    int     *hzd;     /* 0x08: 'h' cache */
    int      field_C; /* 0x0C: hzd[4] */
    DG_OBJS *objs;    /* 0x10 */
    char     pad_14[0x1C - 0x14];
} JeepLight; /* 0x1C */

typedef struct _Work
{
    GV_ACT        work;
    int           map;         /* 0x20 */
    int           name;        /* 0x24 */
    MATRIX        mtx_28;      /* 0x28 */
    JeepLight     lights[13];  /* 0x48 */
    JeepScrollSeg segs[16]; /* 0x1B4 */
    DG_OBJS      *field_474[16]; /* 0x474 */
    HZD_HDL      *field_4B4;     /* 0x4B4 */
    JeepHzdFace  *field_4B8;     /* 0x4B8: cursor into faces */
    JeepHzdFace   faces[24];     /* 0x4BC */
    HZD_SEG      *field_93C;     /* 0x93C: cursor into hzd_segs */
    HZD_SEG       hzd_segs[48];  /* 0x940 */
    int           field_C40;
    int          *field_C44;
    char          pad1d[0xC48 - 0xC44 - sizeof(int *)];
    int           field_C48;
    int           field_C4C;
    int           field_C50;
    int           field_C54;
    short        *field_C58;
    char          pad1b[0xC60 - 0xC58 - sizeof(short *)];
    int           field_C60;
    int           field_C64;
    int           field_C68;
    int           field_C6C;
    int           field_C70;
    int           field_C74;
    int           field_C78;
    int           field_C7C;
    int           field_C80;
} Work;

extern Work *s19b_dword_800DE5B0;

const char s19b_aLightoverjeepsrlc_800DDC94[] = "<<<<< light over !!!!!!!(jeep.srl.c) >>>>>\n";
const char s19b_aMaxlightd_800DDCC0[] = "max light:%d\n";
const char s19b_aJsnake_800DDCD0[] = "j_snake";

void *NewJeepGate(int name, SVECTOR *pos, int side);
void *NewJeepGlass(int name, SVECTOR *pos, int side);
void *NewJeepLamp(SVECTOR *root_pos, int tex_id, int unused);
void *s19b_jeep2_800D6F24(int name, int map); // NewJeep2
void  s19b_jeep_800D2170(SVECTOR *arg0, SVECTOR *arg1, SVECTOR *arg2, short *arg3);
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
void  s19b_jeep_srl_800CD7B4(Work *work, int arg1, JeepVtx *out);
void  s19b_jeep_gls_800CEE7C(Work *work, int arg1, SVECTOR *pos);
extern void  Takabe_ReshadeModel(DG_OBJS *objs, void *lit);
extern void *NewPadVibration(unsigned char *, int);
extern void *NewFadeInOut(int arg0, int arg1);
extern GM_CameraSystemWork GM_Camera;
extern int s19b_dword_800C36FC;
extern int s19b_dword_800C3710;
void  s19b_jeep_gls_800CE8DC(struct _Work *work, JeepScrollSeg *seg, int flag);
extern void RotTransSV(SVECTOR *v0, SVECTOR *v1, long *sz);
extern int  s19b_dword_800C36DC;
extern int s19b_dword_800C3530;

extern int s19b_dword_800C354C;

void s19b_jeep_srl_800CD638(Work *work, int *out)
{
    short *p = work->field_C58;

    work->field_C48 = GV_NearSpeed(work->field_C48, p[2], p[4]);
    work->field_C4C = GV_NearSpeed(work->field_C4C, p[3], p[5]);
    out[0] = p[0];
    out[1] = work->field_C48;
    out[2] = work->field_C4C;
    out[3] = p[7];

    if (work->field_C50 > 0)
    {
        if (--work->field_C54 == 0)
        {
            Takabe_JeepSystem.field_40 = p[7];
        }
        else
        {
            Takabe_JeepSystem.field_40 = 0;
        }
        if (--work->field_C50 == 0)
        {
            work->field_C58 += 8;
            p = work->field_C58;
            if (*p == -1)
            {
                p = (short *)&s19b_dword_800C354C;
                work->field_C58 = p;
            }
            work->field_C50 = p[1];
            work->field_C54 = p[6];
        }
    }
    else
    {
        Takabe_JeepSystem.field_40 = 0;
        if (Takabe_JeepSystem.field_44 != 0)
        {
            Takabe_JeepSystem.field_44--;
            work->field_C50 = -work->field_C50;
        }
    }
}
void s19b_jeep_srl_800CD790(Work *work)
{
    short *p = (short *)&s19b_dword_800C354C;
    work->field_C58 = p;
    work->field_C50 = p[1];
    work->field_C54 = p[6];
}
void s19b_jeep_srl_800CD7B4(Work *work, int arg1, JeepVtx *out)
{
    JeepScrollSeg *seg;
    JeepVtx       *vtx;
    DG_OBJS       *objs;
    SVECTOR        pos;
    long           flag;
    int            i;
    int            k;
    int            n;
    int            map;

    for (i = 0; i < 16; i++)
    {
        k = (i - work->field_C6C) & 0xF;
        seg = &work->segs[i];
        if ((unsigned)(k - 4) < 8)
        {
            DG_SetPos2(&seg->pos, &DG_ZeroVector);
            DG_PutObjs(seg->field_18);
            ((MATRIX *)&s19b_dword_800C36DC)->m[0][2] = seg->field_10;
            ((MATRIX *)&s19b_dword_800C36DC)->m[1][2] = seg->field_12;
            MulMatrix0(&seg->field_18->world, (MATRIX *)&s19b_dword_800C36DC, &seg->field_18->world);
            SetRotMatrix(&seg->field_18->world);
            objs = seg->field_18;
            map = GM_CurrentMap;
            objs->group_id = map;
            work->field_474[i]->root = &seg->field_18->world;
            if (seg->field_18->def == work->lights[0].def && abs(seg->pos.vz) >= 0x1771)
            {
                work->field_474[i]->flag &= ~0x80;
                seg->field_18->flag |= 0x80;
            }
            else
            {
                seg->field_18->flag &= ~0x80;
                work->field_474[i]->flag |= 0x80;
            }
            n = *seg->field_1C;
            vtx = (JeepVtx *)(seg->field_1C + 1);
            while (n > 0)
            {
                RotTransSV(&vtx->pos, &pos, &flag);
                out->pos = pos;
                out->field_8 = vtx->field_8 >> 1;
                out->field_A = vtx->field_A >> 1;
                out->field_C = vtx->field_C;
                (*work->field_C44)++;
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
            seg->field_24 &= ~2;
        }
        else
        {
            seg->field_18->flag |= 0x80;
            work->field_474[i]->flag |= 0x80;
        }
        seg->field_24 &= ~1;
    }
}

void s19b_jeep_srl_800CDAA4(Work *work)
{
    JeepVtx       *vtx;
    int           *count;
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
    if (work->field_C68 == 0)
    {
        for (j = 0; j < 13; j++)
        {
            Takabe_ReshadeModel(work->lights[j].objs, work->lights[j].lit);
        }
        work->field_C68 = 1;
    }
    Takabe_JeepSystem.pos = Takabe_JeepSystem.field_20;
    count = work->field_C44;
    *count = 0;
    vtx = (JeepVtx *)(count + 1);
    work->field_4B8 = work->faces;
    work->field_93C = work->hzd_segs;
    work->field_4B4->dynamic_queue_index = 0;
    work->field_4B4->dynamic_floor_index = 0;
    for (i = 0; i < 16; i++)
    {
        seg = &work->segs[i];
        z = seg->pos.vz + Takabe_JeepSystem.pos.vz;
        if (z >= 32000)
        {
            s19b_jeep_srl_800CD638(work, out);
            v = out[1];
            seg->field_8.vx = v / 2;
            seg->field_10 = (-v << 11) / 4000;
            v = out[2];
            seg->field_8.vy = v / 2;
            seg->field_12 = (-v << 11) / 4000;
            seg->field_24 = 3;
            seg->field_28 = out[3];
            z -= 64000;
            k = (i + 1) & 0xF;
            next = &work->segs[k];
            seg->pos.vx = next->pos.vx + next->field_8.vx;
            seg->pos.vy = next->pos.vy + next->field_8.vy;
            seg->pos.vx += seg->field_8.vx;
            seg->pos.vy += seg->field_8.vy;
            if (k < i)
            {
                seg->pos.vx -= Takabe_JeepSystem.pos.vx;
                seg->pos.vy -= Takabe_JeepSystem.pos.vy;
            }
            work->field_C6C = i;
            s19b_jeep_gls_800CE5F8(seg->field_18);
            seg->field_18 = s19b_jeep_gls_800CE52C(out[0], work);
            seg->field_1C = work->lights[out[0]].lit;
            seg->field_20 = (struct _JeepSegDef *)work->lights[out[0]].field_C;
            seg->pos.vz = z;
            seg->pos.vx += Takabe_JeepSystem.pos.vx;
            seg->pos.vy += Takabe_JeepSystem.pos.vy;
            s19b_jeep_gls_800CEE7C(work, out[3], &seg->pos);
            s19b_jeep_gls_800CEFE4(work, out[0], seg);
        }
        else
        {
            seg->pos.vz = z;
            seg->pos.vx += Takabe_JeepSystem.pos.vx;
            seg->pos.vy += Takabe_JeepSystem.pos.vy;
        }
    }
    SetSpadStack(SPAD_STACK_ADDR);
    s19b_jeep_srl_800CD7B4(work, (int)seg, vtx);
    ResetSpadStack();
    if ((u_int)*work->field_C44 > (u_int)work->field_C40)
    {
        printf((char *)s19b_aLightoverjeepsrlc_800DDC94);
    }
    s19b_jlamp_800D0D40();
    GM_Camera.flag |= 2;
    GM_Camera.zoom = 0xF0;
    if (work->field_C80 != 0)
    {
        n = work->field_C80 + 1;
        work->field_C80 = n;
        if (n >= 0x47)
        {
            if (work->field_C78 != 0 && GM_GameOverTimer == 0)
            {
                GCL_ExecProc(work->field_C78, NULL);
            }
        }
        else if (n >= 0x1F)
        {
            if (n == 0x1F)
            {
                NewPadVibration((unsigned char *)&s19b_dword_800C36FC, 1);
                NewPadVibration((unsigned char *)&s19b_dword_800C3710, 2);
            }
        }
    }
    else
    {
        if (s19b_jeep_gls_800CEDFC(Takabe_JeepSystem.control->mov.vz, 9600) == 14)
        {
            NewFadeInOut(2, 0x14);
            work->field_C80 = 1;
        }
    }
    Takabe_JeepSystem.world.t[0] += Takabe_JeepSystem.pos.vx;
    Takabe_JeepSystem.world.t[1] += Takabe_JeepSystem.pos.vy;
    Takabe_JeepSystem.world.t[2] += Takabe_JeepSystem.pos.vz;
}
void s19b_jeep_srl_800CDAA4(Work *work);

void s19b_jeep_srl_800CDF48(Work *work)
{
    int i;

    for (i = 0; i < 16; i++)
    {
        s19b_jeep_gls_800CE5F8(work->field_474[i]);
    }
    for (i = 0; i < 16; i++)
    {
        s19b_jeep_gls_800CE5F8(work->segs[i].field_18);
    }
    for (i = 0; i < 13; i++)
    {
        DG_OBJS *objs = work->lights[i].objs;
        DG_FreePreshade(objs);
        DG_FreeObjs(objs);
    }
    Takabe_JeepSystem.field_78 = 0;
    GM_StreamPlayStop();
    *work->field_C44 = work->field_C40;
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
    work->field_C44 = (int *)map->lit;
    work->field_C40 = *work->field_C44;
    printf((char *)s19b_aMaxlightd_800DDCC0, work->field_C40);
    Takabe_JeepSystem.field_48 = THING_Gcl_GetInt('c');
    work->field_C60 = 0;
    work->field_C68 = 0;
    work->field_C6C = 0;
    Takabe_JeepSystem.field_20 = DG_ZeroVector;
    Takabe_JeepSystem.pos = Takabe_JeepSystem.field_20;
    Takabe_JeepSystem.field_30 = 0;
    Takabe_JeepSystem.field_2C = 0;
    Takabe_JeepSystem.field_28 = 0;
    seg = work->segs;
    for (i = 0, z = -31500; i < 16; seg++, i++, z += 4000)
    {
        seg->field_18 = s19b_jeep_gls_800CE52C(0, work);
        seg->field_1C = work->lights[0].lit;
        seg->field_20 = (struct _JeepSegDef *)work->lights[0].field_C;
        seg->field_8.vz = -2000;
        seg->field_10 = 0;
        seg->field_14 = 0;
        seg->field_8.vx = 0;
        seg->field_8.vy = 0;
        seg->pos.vx = 0;
        seg->pos.vy = 0;
        seg->pos.vz = z;
        seg->field_24 = 1;
        seg->field_28 = 0;
        Takabe_JeepSystem.field_38 = seg->pos;
        if (Takabe_JeepSystem.field_38.vz < 16000)
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
    work->field_4B4 = GM_GetMap(work->map)->hzd;
    s19b_dword_800DE5B0 = work;
    if (GCL_GetOption('e'))
    {
        work->field_C70 = GCL_StrToInt(GCL_NextStr());
        work->field_C74 = GCL_StrToInt(GCL_NextStr());
        work->field_C78 = GCL_StrToInt(GCL_NextStr());
    }
    Takabe_JeepSystem.field_78 = 0x800;
    Takabe_JeepSystem.world = DG_ZeroMatrix;
    NewJeep(GV_StrCode(s19b_aJsnake_800DDCD0), where);
    s19b_jlamp_800D0CE0();
    s19b_jeep_srl_800CD790(work);
    work->field_C58 = (short *)&s19b_dword_800C354C;
    GM_GameStatus |= STATE_NOSLOW;
    return 0;
}
int s19b_jeep_srl_800CE020(Work *work, int name, int where);

void *NewJeepScroll(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
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

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_gls_800CE400.s")
DG_OBJS *s19b_jeep_gls_800CE52C(int idx, Work *work)
{
    JeepLight *lights = work->lights;
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
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_gls_800CE8DC.s")
void s19b_jeep_gls_800CEB2C(int arg0, SVECTOR *rot)
{
    Work   *work = s19b_dword_800DE5B0;
    int     idx = work->field_C6C;
    int     base;
    SVECTOR dir;

    base = work->segs[idx].pos.vz - 0x7D0;
    base = (arg0 - base) / 4000; /* two statements: quotient reuses the dividend reg */
    idx += base;
    idx &= 0xF;
    dir = work->segs[idx].field_8;
    rot->vy = GV_VecDir2(&dir);
    rot->vx = ratan2(-dir.vy, SquareRoot0(dir.vx * dir.vx + dir.vz * dir.vz));
    rot->vz = 0;
}
void s19b_jeep_gls_800CEC24(int arg0, SVECTOR *out)
{
    Work          *work = s19b_dword_800DE5B0;
    int            idx = work->field_C6C;
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
    dir = seg->field_8;
    sum.vx = dir.vx + prev->field_8.vx;
    sum.vy = dir.vy + prev->field_8.vy;
    sum.vz = -4000;
    s19b_jeep_800D2170(&zero, &dir, &sum, (short *)&mtx);
    s19b_jeep_800D21DC(((seg->pos.vz - arg0) << 12) / 4000, &mtx, out);
    GV_AddVec3(out, &seg->pos, out);
}
int s19b_jeep_gls_800CEDFC(int arg0, int arg1)
{
    Work          *work = s19b_dword_800DE5B0;
    int            idx = work->field_C6C;
    int            base;
    JeepScrollSeg *seg;

    base = work->segs[idx].pos.vz - 0x7D0;
    idx += (arg0 - base - arg1) / 4000;
    idx &= 0xF;
    seg = &work->segs[idx];
    return seg->field_28;
}

void s19b_jeep_gls_800CEE7C(Work *work, int arg1, SVECTOR *pos)
{
    GCL_ARGS args;
    SVECTOR  diff;
    int      state;
    int      proc_id;
    
    Takabe_JeepSystem.field_38 = *pos;
    state = Takabe_JeepSystem.field_40;

    GV_SubVec3(pos, &Takabe_JeepSystem.pos, &diff);

    if (state == 2)
    {
        Takabe_JeepSystem.field_7C = 0;

        NewJeepGate(1, &diff, 0);
        NewJeepGate(1, &diff, 1);
        NewJeepGlass(2, &diff, 0);
        NewJeepGlass(2, &diff, 1);

        proc_id = work->field_C70;
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

        proc_id = work->field_C74;
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

    GV_SubVec3(&Takabe_JeepSystem.field_38, &Takabe_JeepSystem.pos, &diff);

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
