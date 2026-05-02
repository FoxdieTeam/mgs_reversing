#include "common.h"
#include "game/game.h"

typedef struct _Spark2MWork
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    MATRIX   world;
    SVECTOR  vecs[16];
    SVECTOR  verts[32];
    char     pad2[0x28];
    int      f1F0;
} Spark2MWork;

typedef struct _JEEP_SYSTEM_S
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2[0x10];
    SVECTOR  pos;
} JEEP_SYSTEM_S;

extern JEEP_SYSTEM_S Takabe_JeepSystem;

extern void s19b_spark2_m_800DA19C(SVECTOR *, SVECTOR *, int);
extern void s19b_spark2_m_800DA314(void *, SVECTOR *, int);
extern void s19b_spark2_m_800DA3EC(LINE_F2 *, int, int);
extern void s19b_spark2_m_800DA41C(LINE_F2 *, int, int);

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8724.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D87A4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D88D8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8918.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D899C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8A48.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8A88.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8AAC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8ACC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8AEC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8B54.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8BC8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8CEC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8E10.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8F34.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8FB0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D902C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D90A8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9148.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D91DC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D92C8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D932C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9390.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9434.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D94C8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9558.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D95FC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D964C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9680.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9704.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D97A8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D985C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9910.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D99C4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9A30.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9A74.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9AA8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9B38.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9B88.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9C04.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9C90.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9EC0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800DA0B4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800DA19C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800DA314.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800DA3EC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800DA41C.s")
void s19b_spark2_m_800DA46C(Spark2MWork *work)
{
    int      time;
    DG_PRIM *prim;
    int      shade;

    GM_CurrentMap = work->map;

    time = --work->f1F0;
    if (time <= 0)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    s19b_spark2_m_800DA314(work->vecs, work->verts, 16);

    prim = work->prim;

    shade = (time * 16) + 50;
    if (shade > 255)
    {
        shade = 255;
    }

    s19b_spark2_m_800DA41C((LINE_F2 *)prim->packs[GV_Clock], 16, shade);

    work->world.t[0] += Takabe_JeepSystem.pos.vx;
    work->world.t[1] += Takabe_JeepSystem.pos.vy;
    work->world.t[2] += Takabe_JeepSystem.pos.vz;

    DG_SetPos(&work->world);
    DG_PutPrim(&work->prim->world);
}
void s19b_spark2_m_800DA55C(Spark2MWork *work)
{
    GM_FreePrim(work->prim);
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800DA598.s")
extern int s19b_spark2_m_800DA598(Spark2MWork *work, int arg);
extern const char aSpark2mC_800DDEB0[];

#define EXEC_LEVEL 5
#define DCache 0x1F8003FC

#define SetSpadStack(addr)                                                                                             \
    {                                                                                                                  \
        __asm__ volatile("move $8,%0" ::"r"(addr) : "$8", "memory");                                                   \
        __asm__ volatile("sw $29,0($8)" ::: "$8", "memory");                                                           \
        __asm__ volatile("addiu $8,$8,-4" ::: "$8", "memory");                                                         \
        __asm__ volatile("move $29,$8" ::: "$8", "memory");                                                            \
    }

#define ResetSpadStack()                                                                                               \
    {                                                                                                                  \
        __asm__ volatile("addiu $29,$29,4" ::: "$29", "memory");                                                       \
        __asm__ volatile("lw $29,0($29)" ::: "$29", "memory");                                                         \
    }

GV_ACT *NewSpark2M_800DA6D8(int arg0)
{
    Spark2MWork *work;

    work = (Spark2MWork *)GV_NewActor(EXEC_LEVEL, sizeof(Spark2MWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, s19b_spark2_m_800DA46C, s19b_spark2_m_800DA55C, aSpark2mC_800DDEB0);

        SetSpadStack(DCache);

        if (s19b_spark2_m_800DA598(work, arg0) < 0)
        {
            ResetSpadStack();

            GV_DestroyActor(&work->actor);
            return NULL;
        }

        ResetSpadStack();
    }

    return &work->actor;
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_fadeio_800DA784.s")
