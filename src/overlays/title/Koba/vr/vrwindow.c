#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"
#include "SD/g_sound.h"

typedef struct VrwindowWork
{
    GV_ACT         actor;
    RECT           f20;
    RECT           f28;
    short          f30;
    int            f34;
    char           f38;
    int            f3C;
    char           f40;
    char          *f44[16];
    unsigned short name;
    unsigned short clut;
    KCB            kcb;
    SPRT           sprts[2];
    TILE           tiles[2];
    LINE_F3        lines1[2];
    LINE_F3        lines2[2];
    DR_TPAGE       tpages[2];
    int            f16C;
    char           pad[0x4];
    RECT           f174;
    int            f17C;
    int            f180;
    void          *font_buffer;
    short          f188;
    short          f18A;
} VrwindowWork;

int vrwindow_800C3774 = 896;
int vrwindow_800C3778 = 256;
int vrwindow_800C377C = 896;
int vrwindow_800C3780 = 510;

extern GV_PAD GV_PadData_800B05C0[4];

extern char vrwindow_800D92D4[];

#define EXEC_LEVEL GV_ACTOR_LEVEL2

void Vrwindow_800D73A4(VrwindowWork *work, RECT *rect)
{
    setXY0(&work->tiles[GV_Clock], rect->x, rect->y);
    setWH(&work->tiles[GV_Clock], rect->w, rect->h);

    setXY3(&work->lines1[GV_Clock],
           rect->x, rect->y,
           rect->x + rect->w, rect->y,
           rect->x + rect->w, rect->y + rect->h);

    setXY3(&work->lines2[GV_Clock],
           rect->x, rect->y,
           rect->x, rect->y + rect->h,
           rect->x + rect->w, rect->y + rect->h);
}

int Vrwindow_800D74AC(VrwindowWork *work)
{
    GV_MSG *msg;
    int     n_msgs;

    n_msgs = GV_ReceiveMessage(work->name, &msg);
    for (; n_msgs > 0; n_msgs--, msg++)
    {
        if (msg->message[0] == 0x3213)
        {
            return 1;
        }
    }

    return 0;
}

void Vrwindow_800D7510(VrwindowWork *work)
{
    if (!(GV_PadData_800B05C0[2].status & 0xF0F0))
    {
        return;
    }

    if (work->f3C != 0)
    {
        GCL_ExecProc(work->f3C, NULL);
    }

    GM_SeSet2(0, 63, SE_MENU_SELECT);

    switch (work->f38)
    {
    case 0:
        work->f38 = 4;
        work->f30 = 0;
        break;

    case 1:
        work->f38 = 5;
        work->f30 = 4 - work->f30;
        break;

    case 2:
        work->f38 = 4;
        work->f30 = 4 - work->f30;
        break;

    case 3:
        work->f38 = 4;
        work->f30 = 0;
        break;
    }
}

int Vrwindow_800D75D8(VrwindowWork *work, int size)
{
    int i;
    int len;
    int idx;

    font_clear(&work->kcb);

    for (i = 0; i < work->f16C; i++)
    {
        if (i >= work->f40)
        {
            break;
        }

        len = strlen(work->f44[work->f34 + i]);

        if (size < len)
        {
            strncpy(vrwindow_800D92D4, work->f44[work->f34 + i], size);

            idx = work->f180;
            work->f180 = 0;

            while (idx < size)
            {
                if ((work->f180 != 0) || (vrwindow_800D92D4[idx] > 0x1F && vrwindow_800D92D4[idx] < 0x7F))
                {
                    work->f180 = 0;
                }
                else
                {
                    work->f180 = size;
                }

                idx++;
            }

            if (size != 0 && work->f180 != 0)
            {
                vrwindow_800D92D4[size - 1] = '\0';
                work->f180 = size - 1;
            }
            else
            {
                vrwindow_800D92D4[size] = '\0';
                work->f180 = size;
            }

            if (work->f180 != 0 && vrwindow_800D92D4[work->f180 - 1] != ' ')
            {
                GM_SeSet2(0, 63, 179);
            }

            font_draw_string(&work->kcb, 0, i * 18, vrwindow_800D92D4, work->kcb.color);
            font_update(&work->kcb);
            break;
        }

        font_draw_string(&work->kcb, 0, i * 18, work->f44[work->f34 + i], work->kcb.color);
        font_update(&work->kcb);

        size -= len;
        work->f180 = 0;
    }

    if (i == work->f16C || i == work->f40)
    {
        return 0;
    }

    return 1;
}

void VrwindowAct_800D7818(VrwindowWork *work)
{
    RECT rect;

    if (work->f18A != 0)
    {
        if (work->f188 >= 0 && work->f188 <= 9)
        {
            work->f188++;
        }
        else if (work->f188 == 10)
        {
            GV_PauseLevel |= 4;
            work->f188++;
        }
    }

    switch(work->f38)
    {
    case 0:
        if (Vrwindow_800D74AC(work))
        {
            work->f38 = 4;
        }

        addPrim(DG_ChanlOTag(1), &work->sprts[GV_Clock]);
        Vrwindow_800D7510(work);
        break;

    case 1:
        rect.w = (work->f28.w * work->f30) / 5;
        rect.h = 1;
        rect.x = work->f28.x + (work->f28.w - rect.w) / 2;
        rect.y = work->f28.y + work->f28.h / 2;
        Vrwindow_800D73A4(work, &rect);

        if (++work->f30 == 5)
        {
            work->f38 = 2;
            work->f30 = 0;
        }

        Vrwindow_800D7510(work);
        break;

    case 2:
        rect.w = work->f28.w;
        rect.h = work->f28.h * work->f30 / 4;
        rect.x = work->f28.x;
        rect.y = work->f28.y + (work->f28.h - rect.h) / 2;
        Vrwindow_800D73A4(work, &rect);

        if (++work->f30 == 5)
        {
            work->f38 = 3;
            work->f30 = 0;
        }

        Vrwindow_800D7510(work);
        break;

    case 3:
        work->f30 += 2;
        if (!Vrwindow_800D75D8(work, work->f30))
        {
            work->f30 -= strlen(work->f44[work->f34]) * 2;
            work->f180 = 0;

            if (work->f40 <= (work->f34++ + work->f16C))
            {
                work->f38 = 0;
                work->f30 = 0;
            }
        }

        Vrwindow_800D73A4(work, &work->f28);

        addPrim(DG_ChanlOTag(1), &work->sprts[GV_Clock]);
        Vrwindow_800D7510(work);
        break;

    case 4:
        rect.w = work->f28.w;
        rect.h = work->f28.h * (4 - work->f30) / 4;
        rect.x = work->f28.x;
        rect.y = work->f28.y + (work->f28.h - rect.h) / 2;
        Vrwindow_800D73A4(work, &rect);

        if (++work->f30 == 5)
        {
            work->f38 = 5;
            work->f30 = 0;
        }
        break;

    case 5:
        rect.w = work->f28.w * (4 - work->f30) / 4;
        rect.h = 1;
        rect.x = work->f28.x + (work->f28.w - rect.w) / 2;
        rect.y = work->f28.y + work->f28.h / 2;
        Vrwindow_800D73A4(work, &rect);

        if (++work->f30 == 5)
        {
            work->f38 = 6;
            work->f30 = 0;
        }
        break;

    case 6:
        if (++work->f30 == 3)
        {
            GV_DestroyActor(&work->actor);
            GV_PauseLevel &= ~4;
        }
        return;
    }

    addPrim(DG_ChanlOTag(1), &work->lines1[GV_Clock]);
    addPrim(DG_ChanlOTag(1), &work->lines2[GV_Clock]);
    addPrim(DG_ChanlOTag(1), &work->tiles[GV_Clock]);
    addPrim(DG_ChanlOTag(1), &work->tpages[GV_Clock]);
}

void Vrwindow_800D7ED8(RECT *rect);

void VrwindowDie_800D7E10(VrwindowWork *work)
{
    if (work->f17C != 0)
    {
        Vrwindow_800D7ED8(&work->f174);
    }

    GV_Free(work->font_buffer);
}

void Vrwindow_800D7E54(VrwindowWork *work, RECT *rect)
{
    rect->x = vrwindow_800C3774;
    rect->y = vrwindow_800C3778;
    rect->w = work->f20.w / 4;
    rect->h = work->f20.h;

    vrwindow_800C3778 += work->f28.h;
    if (vrwindow_800C3778 > 512)
    {
        printf("vrwindow: Can\'t alloc !! \n");
    }
}

void Vrwindow_800D7ED8(RECT *rect)
{
    vrwindow_800C3778 = 256;
    vrwindow_800C377C = 960;
}

unsigned short Vrwindow_800D7EF4(RECT *rect)
{
    rect->x = vrwindow_800C377C;
    rect->y = vrwindow_800C3780;
    rect->w = 16;
    rect->h = 1;

    vrwindow_800C377C += 16;

    return getClut(rect->x, rect->y);
}

void Vrwindow_800D7F48(KCB *kcb, int x, int y, VrwindowWork *work)
{
    RECT rect;

    Vrwindow_800D7E54(work, &work->f174);
    ClearImage(&work->f174, 0, 0, 0);

    work->clut = Vrwindow_800D7EF4(&rect);
    font_init_kcb(kcb, &work->f174, rect.x, rect.y);
    font_set_kcb(kcb, -1, -1, 0, 6, 2, 0);

    work->font_buffer = GV_Malloc(font_get_buffer_size(kcb));
    font_set_buffer(kcb, work->font_buffer);

    font_set_color(kcb, 0, 0x6739, 0);
    font_clut_update(kcb);
}

int VrwindowGetResources_800D8024(VrwindowWork *work, int map)
{
    int i;

    GM_CurrentMap = map;

    work->f188 = 0;
    Vrwindow_800D7F48(&work->kcb, work->f20.w, work->f20.h + 18, work);

    for (i = 0; i < 2; i++)
    {
        setDrawTPage(&work->tpages[i], 1, 0, getTPage(0, 0, 896, 256));

        LSTORE(0x808080, &work->sprts[i].r0);
        LCOPY(&work->f20.x, &work->sprts[i].x0);
        LCOPY(&work->f20.w, &work->sprts[i].w);
        setSprt(&work->sprts[i]);
        setUV0(&work->sprts[i], (work->f174.x - 896) * 4, work->f174.y);
        work->sprts[i].clut = work->clut;

        setTile(&work->tiles[i]);
        setRGB0(&work->tiles[i], 0, 0, 0);
        setXY0(&work->tiles[i], work->f28.x, work->f28.y);
        setWH(&work->tiles[i], work->f28.w, work->f28.h);
        setSemiTrans(&work->tiles[i], 1);

        setLineF3(&work->lines1[i]);
        setLineF3(&work->lines2[i]);
        setRGB0(&work->lines1[i], 64, 64, 64);
        setRGB0(&work->lines2[i], 64, 64, 64);

        work->f180 = 0;
    }

    return 0;
}

void *NewVrwindow_800D81AC(int name, int where)
{
    VrwindowWork *work;
    int           i;
    int           width;

    work = GV_NewActor(EXEC_LEVEL, sizeof(VrwindowWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, VrwindowAct_800D7818, VrwindowDie_800D7E10, "vrwindow.c");

        work->f38 = 1;
        work->f30 = 0;
        work->f34 = 0;

        GM_SeSet2(0, 63, SE_MENU_SELECT);

        if (GCL_GetOption('s'))
        {
            work->f18A = 0;
        }
        else
        {
            work->f18A = 1;
        }

        work->f40 = GCL_StrToInt(GCL_GetOption('i'));

        if (GCL_GetOption('b'))
        {
            for (i = 0; i < work->f40; i++)
            {
                work->f44[i] = GCL_ReadString((char *)GCL_GetParamResult());
                if (work->f44[i] == 0)
                {
                    break;
                }
            }
        }

        if (GCL_GetOption('w'))
        {
            work->f28.x = GCL_StrToInt((char *)GCL_GetParamResult());
            work->f28.y = GCL_StrToInt((char *)GCL_GetParamResult());
            work->f28.w = GCL_StrToInt((char *)GCL_GetParamResult());
            work->f28.h = GCL_StrToInt((char *)GCL_GetParamResult());

            width = work->f28.w;
            if (width & 3)
            {
                work->f28.w += 4 - (width % 4);
            }

            work->f28.h = (work->f40 * 18) + 18;
            work->f28.x = (320 - work->f28.w) >> 1;
            work->f28.y = (224 - work->f28.h) >> 1;
        }
        else
        {
            work->f28.x = 0;
            work->f28.y = 0;
            work->f28.w = 256;
            work->f28.h = 13;
        }

        if (GCL_GetOption('m'))
        {
            work->f20.x = work->f28.x + GCL_StrToInt((char *)GCL_GetParamResult());
            work->f20.y = work->f28.y + GCL_StrToInt((char *)GCL_GetParamResult());
            work->f20.w = GCL_StrToInt((char *)GCL_GetParamResult());
            work->f20.h = GCL_StrToInt((char *)GCL_GetParamResult());
        }
        else
        {
            work->f20.x = work->f28.x;
            work->f20.y = work->f28.y;
            work->f20.w = work->f28.w;
            work->f20.h = work->f28.h;
        }

        work->f20.x = work->f28.x + 16;
        work->f20.y = work->f28.y + 12;
        work->f20.w = work->f28.w - 16;
        work->f20.h = work->f28.h - 12;

        if (GCL_GetOption('p'))
        {
            work->f3C = GCL_StrToInt((char *)GCL_GetParamResult());
        }
        else
        {
            work->f3C = 0;
        }

        if (GCL_GetOption('f'))
        {
            work->f17C = 1;
        }
        else
        {
            work->f17C = 0;
        }

        work->name = name;
        work->f16C = work->f20.h / 18;

        if (VrwindowGetResources_800D8024(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
