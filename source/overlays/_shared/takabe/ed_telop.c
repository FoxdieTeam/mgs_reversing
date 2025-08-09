#include "ed_telop.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "menu/menuman.h"
#include "takabe/thing.h"

typedef struct _EdTelopWork
{
    GV_ACT actor;
    int    f20;
    int    f24;
    int    f28;
    int    f2C;
    int    f30;
    int    f34;
    int    f38;
    int   *f3C;
    void  *f40;
    int    proc;
} EdTelopWork;

typedef struct _EdTelopPrims
{
    DR_TPAGE tpage[2];
    SPRT     sprt[2];
} EdTelopPrims;

RECT           ed_telop_rect_800C3230 = {0, 256, 320, 1};
RECT           ed_telop_rect_800C3238 = {0, 256, 320, 160};
unsigned short ed_telop_hashes_800C3240[] = {0x29B9};

static EdTelopPrims ed_telop_prims_800C9BC8[2];
static u_long       ed_telop_800C9C38[160];

char * roll_ending2_800C5E54(void *, char *, int);
void   roll_ending2_800C5EAC(short *, void *, void *, int);

#define EXEC_LEVEL GV_ACTOR_LEVEL5

int EdTelop_800C4F18(void)
{
    char *str;

    if (!GCL_GetOption('s'))
    {
        return 1;
    }

    str = GCL_ReadString(GCL_GetParamResult());
    if (GCL_GetOption('t'))
    {
        MENU_JimakuWrite(str, GCL_GetNextParamValue());
    }

    return 1;
}

void EdTelop_800C4F80(void)
{
    u_long *ptr;
    int     i;

    ptr = ed_telop_800C9C38;
    for (i = 160; i > 0; i -= 4)
    {
        ptr[3] = 0;
        ptr[2] = 0;
        ptr[1] = 0;
        ptr[0] = 0;
        ptr += 4;
    }
}

void * EdTelop_800C4FB8(short *arg0, int arg1)
{
    RECT  rect;
    char *ptr;
    int   x, y;
    int   off;
    void *scratch;
    int   i;

    ClearImage(&ed_telop_rect_800C3238, 0, 0, 0);

    ptr = (char *)(arg0 + 20);

    EdTelop_800C4F80();

    x = arg0[0];
    y = arg0[1];

    rect = ed_telop_rect_800C3230;

    off = (320 - x) / 2;
    rect.y += (160 - y) / 2;

    scratch = (void *)SCRPAD_ADDR;

    for (i = arg0[1]; i > 0; i--)
    {
        if (!(*ptr & 0x40))
        {
            ptr = roll_ending2_800C5E54(scratch, ptr, arg0[0] / 2);
            roll_ending2_800C5EAC((short *)ed_telop_800C9C38 + off, scratch, arg0 + 2, arg0[0]);

            DrawSync(0);
            LoadImage2(&rect, ed_telop_800C9C38);
        }
        else
        {
            ptr++;
        }

        rect.y++;
    }

    return (char *)arg0 + 40 + *(int *)(arg0 + 18);
}

void EdTelop_800C512C(SPRT *sprt, DR_TPAGE *tpage, char *ot, int color)
{
    setSprt(sprt);
    setRGB0(sprt, color, color, color);
    setXY0(sprt, 0, 24);
    setUV0(sprt, 0, 0);
    setWH(sprt, 256, 160);
    addPrim(ot, sprt);
    addPrim(ot, tpage);

    tpage++;
    sprt++;

    setSprt(sprt);
    setRGB0(sprt, color, color, color);
    setXY0(sprt, 256, 24);
    setUV0(sprt, 0, 0);
    setWH(sprt, 64, 160);
    addPrim(ot, sprt);
    addPrim(ot, tpage);
}

void EdTelopAct_800C525C(EdTelopWork *work)
{
    EdTelopPrims *prims;
    DR_TPAGE     *tpage;
    SPRT         *sprt;
    char         *ot;
    int           val;

    prims = &ed_telop_prims_800C9BC8[GV_Clock];
    ot = DG_ChanlOTag(1);
    sprt = prims->sprt;
    tpage = prims->tpage;

    val = 0;
    switch (work->f24)
    {
    case 0:
        work->f40 = EdTelop_800C4FB8(work->f40, 0);
        work->f24 = 1;
        work->f2C = work->f30;
        break;

    case 1:
        EdTelop_800C512C(sprt, tpage, ot, 192 - (--work->f2C * 192) / work->f30);

        if (work->f2C <= 0)
        {
            work->f24 = 2;
            work->f2C = work->f34;
        }
        break;

    case 2:
        work->f2C--;
        EdTelop_800C512C(sprt, tpage, ot, 192);

        if (work->f2C <= 0 && work->f34 != -1)
        {
            val = 1;
        }

        switch (THING_Msg_CheckMessage(work->f20, 1, ed_telop_hashes_800C3240))
        {
        case 0:
            val = 1;
            break;

        case 1:
            break;
        }

        if (val != 0)
        {
            work->f24 = 3;
            work->f2C = work->f30;
        }
        break;

    case 3:
        EdTelop_800C512C(sprt, tpage, ot, (--work->f2C * 192) / work->f30);

        if (work->f2C <= 0)
        {
            if (++work->f28 >= *work->f3C)
            {
                work->f24 = -1;
            }
            else
            {
                work->f24 = 4;
                work->f2C = 15;
            }
        }
        break;

    case 4:
        if (--work->f2C <= 0)
        {
            work->f24 = 0;
        }
        break;

    case -1:
        ClearImage(&ed_telop_rect_800C3238, 0, 0, 0);
        GV_DestroyActor(&work->actor);
        break;

    }
}

void EdTelopDie_800C54D4(EdTelopWork* work)
{
    if (work->proc != 0)
    {
        GCL_ExecProc(work->proc, NULL);
    }
}

void EdTelopGetResources_800C5504(EdTelopWork *work)
{
    char *data;
    int   tp0, tp1;
    int   i;

    ClearImage(&ed_telop_rect_800C3238, 0, 0, 0);

    GM_GameStatus |= STATE_PADRELEASE | STATE_PAUSE_ONLY;
    DG_UnDrawFrameCount = 1;

    data = GV_GetCache(GV_CacheID(work->f38, 'r'));
    work->f3C = (int *)data;
    work->f40 = data + 4;

    work->f28 = 0;

    tp0 = getTPage(2, 0, ed_telop_rect_800C3230.x, ed_telop_rect_800C3230.y);
    tp1 = getTPage(2, 0, ed_telop_rect_800C3230.x + 256, ed_telop_rect_800C3230.y);

    for (i = 0; i < 2; i++)
    {
        setDrawTPage(&ed_telop_prims_800C9BC8[i].tpage[0], 0, 0, tp0);
        setDrawTPage(&ed_telop_prims_800C9BC8[i].tpage[1], 0, 0, tp1);
    }
}

void *NewEdTelop_800C563C(int arg0)
{
    EdTelopWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(EdTelopWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, EdTelopAct_800C525C, EdTelopDie_800C54D4, "ed_telop.c");

        work->f20 = arg0;
        work->proc = THING_Gcl_GetInt('p');
        work->f30 = THING_Gcl_GetIntDefault('f', 30);
        work->f34 = THING_Gcl_GetIntDefault('d', 150);
        work->f38 = THING_Gcl_GetInt('t');

        EdTelopGetResources_800C5504(work);
    }

    return (void *)work;
}
