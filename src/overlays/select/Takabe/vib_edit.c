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

typedef struct _VibEditWork
{
    GV_ACT        actor;
    int           status;
    int           f24;
    int           f28;
    char          pad[0x14];
    int           f40;
    VibEditPrims *prims;
    char          pad2[0x4C];
    char          buffer[2048];
    char          pad3[0x40];
} VibEditWork;

extern int GM_GameStatus_800AB3CC;
extern int GM_PlayerStatus_800ABA50;

extern const char select_aSavevibrationeditordata_800C52A4[]; // = "Save vibration editor data !\n"
extern const char select_aVibeditdat_800C52C4[];              // = "VIB_EDIT.DAT"
extern const char select_aVibeditc_800C52D4[];                // = "vib_edit.c"

// VibEditGetResources is calling this with two missing parameters for some reason.
int PCopen_80014B1C(const char *name);
int PCread_80014B24(int fd, char *buff, int len);
int PCclose_80014B2C(int fd);

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

    work->prims = GV_Malloc_8001620C(sizeof(VibEditPrims));
    prims = work->prims;

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
#pragma INCLUDE_ASM("asm/overlays/select/select_800C3974.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C3BB8.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C3BF4.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C3C28.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C3C74.s")
#pragma INCLUDE_ASM("asm/overlays/select/VibEdit_800C3CBC.s")
void VibEdit_800C3CBC(VibEditWork *work, int);

#pragma INCLUDE_ASM("asm/overlays/select/VibEdit_800C3D20.s")
void VibEdit_800C3D20(VibEditWork *work, int);

#pragma INCLUDE_ASM("asm/overlays/select/select_800C3D84.s")

#pragma INCLUDE_ASM("asm/overlays/select/VibEditAct_800C3DB0.s")
void VibEditAct_800C3DB0(VibEditWork *work);

void VibEditDie_800C467C(VibEditWork *work)
{
    int fd;

    printf(select_aSavevibrationeditordata_800C52A4);

    VibEdit_800C3CBC(work, work->f28);

    fd = select_800C4F28(select_aVibeditdat_800C52C4);
    select_800C4F48(fd, work->buffer, 2048);
    PCclose_80014B2C(fd);

    GM_GameStatus_800AB3CC &= ~(work->status & 0x4A2000);
    GM_PlayerStatus_800ABA50 &= ~PLAYER_PAD_OFF;
}

int VibEditGetResources_800C4720(VibEditWork *work, int flags, int perms)
{
    int fd;

    work->f40 = THING_Gcl_GetInt_800D8808('e');

    VibEdit_800C34F0(work);

    // Should have 3 args
    fd = PCopen_80014B1C(select_aVibeditdat_800C52C4);
    PCread_80014B24(fd, work->buffer, 2048);
    PCclose_80014B2C(fd);

    VibEdit_800C3D20(work, work->f28);

    work->status = GM_GameStatus_800AB3CC;
    GM_PlayerStatus_800ABA50 |= PLAYER_PAD_OFF;

    return 0;
}

GV_ACT *NewVibEdit_800C47B4(int flags, int perms)
{
    VibEditWork *work;

    work = (VibEditWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(VibEditWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)VibEditAct_800C3DB0, (TActorFunction)VibEditDie_800C467C, select_aVibeditc_800C52D4);

        if (VibEditGetResources_800C4720(work, flags, perms) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
