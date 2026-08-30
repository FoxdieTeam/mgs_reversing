#include "strcode.h"
#include "game/game.h"
#include "libgcl/libgcl.h"

typedef struct _JEEP_SYSTEM
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2[0x10];
    SVECTOR  pos;
    char     pad3[0x18];
    SVECTOR  field_38;
    int      field_40;
    int      field_44;
    char     pad4[0x1C - sizeof(int)];
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
    char     pad_10[0x18 - 0x10];
    DG_OBJS *field_18; /* 0x18 */
    char     pad_1C[0x28 - 0x1C];
    int      field_28; /* 0x28 */
} JeepScrollSeg; /* 0x2C */

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
    char          pad1[0x48 - 0x20];
    JeepLight     lights[13];  /* 0x48 */
    JeepScrollSeg segs[16]; /* 0x1B4 */
    DG_OBJS      *field_474[16]; /* 0x474 */
    void         *field_4B4;     /* 0x4B4 */
    JeepHzdFace  *field_4B8;     /* 0x4B8 */
    char          pad1a[0xC40 - 0x4B8 - sizeof(void *)];
    int           field_C40;
    int          *field_C44;
    int           field_C48;
    int           field_C4C;
    int           field_C50;
    int           field_C54;
    short        *field_C58;
    char          pad1b[0xC6C - 0xC58 - sizeof(short *)];
    int           field_C6C;
    int           field_C70;
    int           field_C74;
    char          pad2[0xC];
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
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_srl_800CD7B4.s")

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_srl_800CDAA4.s")
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

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_srl_800CE020.s")
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
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_gls_800CEB2C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_gls_800CEC24.s")
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

void s19b_jeep_gls_800CEFE4(Work *work, int disable)
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
