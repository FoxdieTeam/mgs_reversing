#include "Game/game.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

typedef struct _VibEditPrims
{
    TILE    tiles1[16];
    TILE    tiles2[16];
    TILE    tiles3[16];
    TILE    tiles4[16];
    LINE_F2 lines1[3];
    LINE_F2 lines2[3];
} VibEditPrims;

typedef struct _VibEditElem
{
    char field_0[64];
} VibEditElem;

typedef struct _VibEditWork
{
    GV_ACT        actor;
    int           field_20_status;
    int           field_24;
    int           field_28;
    char          field_2C[20];
    int           field_40;
    VibEditPrims *field_44_prims;
    int           field_48;
    char          field_4C[32];
    int           field_6C;
    char          field_70[32];
    int           field_90;
    VibEditElem   field_94_buffer[32];
    char          field_894[0x40];
} VibEditWork;

extern int GM_GameStatus_800AB3CC;
extern int GM_PlayerStatus_800ABA50;

extern const char select_aSavevibrationeditordata_800C52A4[]; // = "Save vibration editor data !\n"
extern char       select_aVibeditdat_800C52C4[];              // = "VIB_EDIT.DAT"
extern const char select_aVibeditc_800C52D4[];                // = "vib_edit.c"
extern const char select_aDd_800C50E4[];
extern const char select_aDd_800C5124[];
extern const char select_aHigh_800C50DC[];
extern const char select_aLow_800C50F0[];
extern const char select_aPadvibationparameterforgcl_800C50B8[];
extern const char select_aPadvibationparameterforprogram_800C50F8[];
extern const char select_a_800C50EC[];
extern const char select_a_800C5120[];
extern const char select_a_800C512C[];

// VibEditGetResources is calling this with two missing parameters for some reason.
int PCopen_80014B1C(const char *name);
int PCread_80014B24(int fd, char *buff, int len);
int PCclose_80014B2C(int fd);

// For some reason VibEditDie_800C467C calls this with a missing
// last argument!? But it's not bad - PsyQ documentation says
// that argument is ignored anyways...
int PCcreat(char *name /*, int perms */);
int PCwrite(int fd, char *buff, int len);

int select_800C4F28(const char *);     // PCopen
int select_800C4F48(int, char *, int); // PCwrite

int THING_Gcl_GetInt_800D8808(int param);

#define EXEC_LEVEL 3

void VibEdit_800C34F0(VibEditWork *work)
{
    VibEditPrims *prims;
    TILE         *tile1;
    TILE         *tile2;
    int           i;
    LINE_F2      *line;

    work->field_44_prims = GV_Malloc_8001620C(sizeof(VibEditPrims));
    prims = work->field_44_prims;

    tile1 = prims->tiles1;
    tile2 = prims->tiles2;

    for (i = 16; i > 0; i--)
    {
        setTile(tile1);
        *tile2++ = *tile1++;
    }

    tile1 = prims->tiles3;
    tile2 = prims->tiles4;

    for (i = 16; i > 0; i--)
    {
        setTile(tile1);
        *tile2++ = *tile1++;
    }

    line = &prims->lines1[0];
    setLineF2(line);
    setXY2(line, 16, 155, 320, 155);
    setRGB0(line, 0, 180, 0);
    prims->lines2[0] = *line;

    line = &prims->lines1[1];
    setLineF2(line);
    setXY2(line, 16, 70, 320, 70);
    setRGB0(line, 180, 0, 0);
    prims->lines2[1] = *line;

    line = &prims->lines1[2];
    setLineF2(line);
    setXY2(line, 16, 155, 16, 70);
    setRGB0(line, 0, 0, 180);
    prims->lines2[2] = *line;
}

#pragma INCLUDE_ASM("asm/overlays/select/select_800C36BC.s")

void select_800C3974(VibEditWork *work)
{
    int   i;
    char *iter;

    printf(select_aPadvibationparameterforgcl_800C50B8);
    printf(select_aHigh_800C50DC);

    iter = work->field_4C;
    for (i = 0; i < 16; i++)
    {
        if (iter[0] == 0 && iter[1] == 0)
        {
            break;
        }
        printf(select_aDd_800C50E4, iter[0], iter[1]);
        iter += 2;
    }
    printf(select_a_800C50EC);
    printf(select_aLow_800C50F0);
    iter = work->field_70;
    for (i = 0; i < 16; i++)
    {
        if (iter[0] == 0 && iter[1] == 0)
        {
            break;
        }
        printf(select_aDd_800C50E4, iter[0], iter[1]);
        iter += 2;
    }
    printf(select_a_800C50EC);
    printf(select_aPadvibationparameterforprogram_800C50F8);
    printf(select_aHigh_800C50DC);

    iter = work->field_4C;
    for (i = 0; i < 16; i++)
    {
        if (iter[0] == 0 && iter[1] == 0)
        {
            printf(select_a_800C5120, iter[0], iter[1]); // unnecessary args...
            break;
        }
        printf(select_aDd_800C5124, iter[0], iter[1]);
        iter += 2;
    }
    printf(select_a_800C50EC);
    printf(select_aHigh_800C50DC);
    iter = work->field_70;
    for (i = 0; i < 16; i++)
    {
        if (iter[0] == 0 && iter[1] == 0)
        {
            printf(select_a_800C5120, iter[0], iter[1]); // unnecessary args...
            break;
        }
        printf(select_aDd_800C5124, iter[0], iter[1]);
        iter += 2;
    }
    printf(select_a_800C512C);
}

void select_800C3BB8(char *ptr, int cnt)
{
    int i;
    ptr += cnt * 2;
    for (i = 16 - cnt; i > 0; i--)
    {
        memcpy(ptr, ptr + 2, 2);
        ptr += 2;
    }
}

void select_800C3BF4(char *ptr, int cnt)
{
    int i;
    for (i = 15 - cnt, ptr += 30; i > 0; i--)
    {
        memcpy(ptr, ptr - 2, 2);
        ptr -= 2;
    }
}

void select_800C3C28(char *ptr, int cnt)
{
    char sp0[2];

    if (cnt >= 15)
    {
        return;
    }

    memcpy(sp0, ptr + (cnt + 1) * 2, 2);
    memcpy(ptr + (cnt + 1) * 2, ptr + cnt * 2, 2);
    memcpy(ptr + cnt * 2, sp0, 2);
}

void select_800C3C74(char *ptr, int cnt)
{
    char sp0[2];

    if (cnt <= 0)
    {
        return;
    }

    memcpy(sp0, ptr + (cnt - 1) * 2, 2);
    memcpy(ptr + (cnt - 1) * 2, ptr + cnt * 2, 2);
    memcpy(ptr + cnt * 2, sp0, 2);
}

void VibEdit_800C3CBC(VibEditWork *work, int idx)
{
    char *dst, *src;
    int   i;

    dst = work->field_94_buffer[idx].field_0;
    src = work->field_4C;
    for (i = 16; i > 0; i--)
    {
        memcpy(dst, src, 2);
        src += 2;
        dst += 2;
    }

    src = work->field_70;
    for (i = 16; i > 0; i--)
    {
        memcpy(dst, src, 2);
        src += 2;
        dst += 2;
    }
}

// VibEdit_800C3CBC but with dst/src swapped:
void VibEdit_800C3D20(VibEditWork *work, int idx)
{
    char *dst, *src;
    int   i;

    src = work->field_94_buffer[idx].field_0;
    dst = work->field_4C;
    for (i = 16; i > 0; i--)
    {
        memcpy(dst, src, 2);
        src += 2;
        dst += 2;
    }

    dst = work->field_70;
    for (i = 16; i > 0; i--)
    {
        memcpy(dst, src, 2);
        src += 2;
        dst += 2;
    }
}

void select_800C3D84(char *src, char *dst)
{
    int i;
    for (i = 16; i > 0; i--)
    {
        memcpy(dst, src, 2);
        src += 2;
        dst += 2;
    }
}

#pragma INCLUDE_ASM("asm/overlays/select/VibEditAct_800C3DB0.s")
void VibEditAct_800C3DB0(VibEditWork *work);

void VibEditDie_800C467C(VibEditWork *work)
{
    int fd;

    printf(select_aSavevibrationeditordata_800C52A4);

    VibEdit_800C3CBC(work, work->field_28);

    fd = PCcreat(select_aVibeditdat_800C52C4);
    PCwrite(fd, (char *)work->field_94_buffer, sizeof(work->field_94_buffer));
    PCclose_80014B2C(fd);

    GM_GameStatus_800AB3CC &= ~(work->field_20_status & 0x4A2000);
    GM_PlayerStatus_800ABA50 &= ~PLAYER_PAD_OFF;
}

int VibEditGetResources_800C4720(VibEditWork *work, int flags, int perms)
{
    int fd;

    work->field_40 = THING_Gcl_GetInt_800D8808('e');

    VibEdit_800C34F0(work);

    // Should have 3 args
    fd = PCopen_80014B1C(select_aVibeditdat_800C52C4);
    PCread_80014B24(fd, (char *)work->field_94_buffer, sizeof(work->field_94_buffer));
    PCclose_80014B2C(fd);

    VibEdit_800C3D20(work, work->field_28);

    work->field_20_status = GM_GameStatus_800AB3CC;
    GM_PlayerStatus_800ABA50 |= PLAYER_PAD_OFF;

    return 0;
}

GV_ACT *NewVibEdit_800C47B4(int flags, int perms)
{
    VibEditWork *work;

    work = (VibEditWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(VibEditWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)VibEditAct_800C3DB0,
                                  (TActorFunction)VibEditDie_800C467C, select_aVibeditc_800C52D4);

        if (VibEditGetResources_800C4720(work, flags, perms) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
