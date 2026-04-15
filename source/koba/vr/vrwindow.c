#include "vrwindow.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "sound/g_sound.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL              GV_ACTOR_LEVEL2

#define VRWIN_STATE_0           0
#define VRWIN_STATE_1           1
#define VRWIN_STATE_2           2
#define VRWIN_STATE_3           3
#define VRWIN_STATE_4           4
#define VRWIN_STATE_5           5
#define VRWIN_STATE_CLOSED      6

/*---------------------------------------------------------------------------*/

typedef struct _Work
{
    GV_ACT         actor;
    RECT           m_rect;      // margin?
    RECT           w_rect;      // window?
    short          step;
    int            f34;
    char           state;
    int            proc;
    char           i_num;       // number of lines
    char          *b_text[16];
    u_short        name;
    u_short        clut;
    KCB            kcb;
    SPRT           sprts[2];
    TILE           tiles[2];
    LINE_F3        lines1[2];
    LINE_F3        lines2[2];
    DR_TPAGE       tpages[2];
    int            f16C;
    char           pad[0x4];
    RECT           f174;
    int            flag;
    int            f180;
    void          *font_buffer;
    short          f188;
    short          f18A;
} Work;

/*---------------------------------------------------------------------------*/

int vrwindow_X1 = 896;
int vrwindow_Y1 = 256;
int vrwindow_X2 = 896;
int vrwindow_Y2 = 510;

char SECTION(".bss") vrwindow_strbuf[100];

/*---------------------------------------------------------------------------*/

static void Vrwindow_800D73A4(Work *work, RECT *rect)
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

static int CheckMessage(Work *work)
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

static void CloseWindow(Work *work)
{
    if (!(GV_PadData[2].status & (PAD_UDLR | PAD_ABXY)))
    {
        return;
    }

    if (work->proc != 0)
    {
        GCL_ExecProc(work->proc, NULL);
    }

    GM_SeSet2(0, 63, SE_MENU_SELECT);

    switch (work->state)
    {
    case VRWIN_STATE_0:
        work->state = VRWIN_STATE_4;
        work->step = 0;
        break;

    case VRWIN_STATE_1:
        work->state = VRWIN_STATE_5;
        work->step = 4 - work->step;
        break;

    case VRWIN_STATE_2:
        work->state = VRWIN_STATE_4;
        work->step = 4 - work->step;
        break;

    case VRWIN_STATE_3:
        work->state = VRWIN_STATE_4;
        work->step = 0;
        break;
    }
}

static int PrintMessage(Work *work, int size)
{
    int i;
    int len;
    int idx;

    font_clear(&work->kcb);

    for (i = 0; i < work->f16C; i++)
    {
        if (i >= work->i_num)
        {
            break;
        }

        len = strlen(work->b_text[work->f34 + i]);

        if (size < len)
        {
            strncpy(vrwindow_strbuf, work->b_text[work->f34 + i], size);

            idx = work->f180;
            work->f180 = 0;

            while (idx < size)
            {
                if ((work->f180 != 0) || (vrwindow_strbuf[idx] > 0x1F && vrwindow_strbuf[idx] < 0x7F))
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
                vrwindow_strbuf[size - 1] = '\0';
                work->f180 = size - 1;
            }
            else
            {
                vrwindow_strbuf[size] = '\0';
                work->f180 = size;
            }

            if (work->f180 != 0 && vrwindow_strbuf[work->f180 - 1] != ' ')
            {
                GM_SeSet2(0, 63, 179);
            }

            font_draw_string(&work->kcb, 0, i * 18, vrwindow_strbuf, work->kcb.color);
            font_update(&work->kcb);
            break;
        }

        font_draw_string(&work->kcb, 0, i * 18, work->b_text[work->f34 + i], work->kcb.color);
        font_update(&work->kcb);

        size -= len;
        work->f180 = 0;
    }

    if (i == work->f16C || i == work->i_num)
    {
        return 0;
    }

    return 1;
}

static void Act(Work *work)
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

    switch (work->state)
    {
    case VRWIN_STATE_0:
        if (CheckMessage(work))
        {
            work->state = VRWIN_STATE_4;
        }

        addPrim(DG_ChanlOTag(1), &work->sprts[GV_Clock]);
        CloseWindow(work);
        break;

    case VRWIN_STATE_1:
        rect.w = (work->w_rect.w * work->step) / 5;
        rect.h = 1;
        rect.x = work->w_rect.x + (work->w_rect.w - rect.w) / 2;
        rect.y = work->w_rect.y + work->w_rect.h / 2;
        Vrwindow_800D73A4(work, &rect);

        if (++work->step == 5)
        {
            work->state = VRWIN_STATE_2;
            work->step = 0;
        }

        CloseWindow(work);
        break;

    case VRWIN_STATE_2:
        rect.w = work->w_rect.w;
        rect.h = work->w_rect.h * work->step / 4;
        rect.x = work->w_rect.x;
        rect.y = work->w_rect.y + (work->w_rect.h - rect.h) / 2;
        Vrwindow_800D73A4(work, &rect);

        if (++work->step == 5)
        {
            work->state = VRWIN_STATE_3;
            work->step = 0;
        }

        CloseWindow(work);
        break;

    case VRWIN_STATE_3:
        work->step += 2;
        if (!PrintMessage(work, work->step))
        {
            work->step -= strlen(work->b_text[work->f34]) * 2;
            work->f180 = 0;

            if (work->i_num <= (work->f34++ + work->f16C))
            {
                work->state = VRWIN_STATE_0;
                work->step = 0;
            }
        }

        Vrwindow_800D73A4(work, &work->w_rect);

        addPrim(DG_ChanlOTag(1), &work->sprts[GV_Clock]);
        CloseWindow(work);
        break;

    case VRWIN_STATE_4:
        rect.w = work->w_rect.w;
        rect.h = work->w_rect.h * (4 - work->step) / 4;
        rect.x = work->w_rect.x;
        rect.y = work->w_rect.y + (work->w_rect.h - rect.h) / 2;
        Vrwindow_800D73A4(work, &rect);

        if (++work->step == 5)
        {
            work->state = VRWIN_STATE_5;
            work->step = 0;
        }
        break;

    case VRWIN_STATE_5:
        rect.w = work->w_rect.w * (4 - work->step) / 4;
        rect.h = 1;
        rect.x = work->w_rect.x + (work->w_rect.w - rect.w) / 2;
        rect.y = work->w_rect.y + work->w_rect.h / 2;
        Vrwindow_800D73A4(work, &rect);

        if (++work->step == 5)
        {
            work->state = VRWIN_STATE_CLOSED;
            work->step = 0;
        }
        break;

    case VRWIN_STATE_CLOSED:
        if (++work->step == 3)
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

static void Vrwindow_800D7ED8(RECT *rect);

static void Die(Work *work)
{
    if (work->flag)
    {
        Vrwindow_800D7ED8(&work->f174);
    }

    GV_Free(work->font_buffer);
}

static void Vrwindow_800D7E54(Work *work, RECT *rect)
{
    rect->x = vrwindow_X1;
    rect->y = vrwindow_Y1;
    rect->w = work->m_rect.w / 4;
    rect->h = work->m_rect.h;

    vrwindow_Y1 += work->w_rect.h;
    if (vrwindow_Y1 > 512)
    {
        printf("vrwindow: Can\'t alloc !! \n");
    }
}

static void Vrwindow_800D7ED8(RECT *rect)
{
    vrwindow_Y1 = 256;
    vrwindow_X2 = 960;
}

static u_short Vrwindow_800D7EF4(RECT *rect)
{
    rect->x = vrwindow_X2;
    rect->y = vrwindow_Y2;
    rect->w = 16;
    rect->h = 1;

    vrwindow_X2 += 16;

    return getClut(rect->x, rect->y);
}

static void InitWindowText(KCB *kcb, int x, int y, Work *work)
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

static int GetResources(Work *work, int map)
{
    int i;

    GM_SetCurrentMap(map);

    work->f188 = 0;
    InitWindowText(&work->kcb, work->m_rect.w, work->m_rect.h + 18, work);

    for (i = 0; i < 2; i++)
    {
        setDrawTPage(&work->tpages[i], 1, 0, getTPage(0, 0, 896, 256));

        LSTORE(COLOR_GRAY, &work->sprts[i].r0);
        LCOPY(&work->m_rect.x, &work->sprts[i].x0);
        LCOPY(&work->m_rect.w, &work->sprts[i].w);
        setSprt(&work->sprts[i]);
        setUV0(&work->sprts[i], (work->f174.x - 896) * 4, work->f174.y);
        work->sprts[i].clut = work->clut;

        setTile(&work->tiles[i]);
        setRGB0(&work->tiles[i], 0, 0, 0);
        setXY0(&work->tiles[i], work->w_rect.x, work->w_rect.y);
        setWH(&work->tiles[i], work->w_rect.w, work->w_rect.h);
        setSemiTrans(&work->tiles[i], 1);

        setLineF3(&work->lines1[i]);
        setLineF3(&work->lines2[i]);
        setRGB0(&work->lines1[i], 64, 64, 64);
        setRGB0(&work->lines2[i], 64, 64, 64);

        work->f180 = 0;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewVrWindow(int name, int where)
{
    Work    *work;
    int     i;
    int     width;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "vrwindow.c");

        work->state = VRWIN_STATE_1;
        work->step = 0;
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

        work->i_num = GCL_StrToInt(GCL_GetOption('i'));

        if (GCL_GetOption('b'))
        {
            for (i = 0; i < work->i_num; i++)
            {
                work->b_text[i] = GCL_ReadString((char *)GCL_GetParamResult());
                if (work->b_text[i] == 0)
                {
                    break;
                }
            }
        }

        if (GCL_GetOption('w'))
        {
            work->w_rect.x = GCL_StrToInt((char *)GCL_GetParamResult());
            work->w_rect.y = GCL_StrToInt((char *)GCL_GetParamResult());
            work->w_rect.w = GCL_StrToInt((char *)GCL_GetParamResult());
            work->w_rect.h = GCL_StrToInt((char *)GCL_GetParamResult());

            width = work->w_rect.w;
            if (width & 3)
            {
                work->w_rect.w += 4 - (width % 4);
            }

            work->w_rect.h = (work->i_num * 18) + 18;
            work->w_rect.x = (FRAME_WIDTH - work->w_rect.w) >> 1;
            work->w_rect.y = (FRAME_HEIGHT - work->w_rect.h) >> 1;
        }
        else
        {
            work->w_rect.x = 0;
            work->w_rect.y = 0;
            work->w_rect.w = 256;
            work->w_rect.h = 13;
        }

        if (GCL_GetOption('m'))
        {
            work->m_rect.x = work->w_rect.x + GCL_StrToInt((char *)GCL_GetParamResult());
            work->m_rect.y = work->w_rect.y + GCL_StrToInt((char *)GCL_GetParamResult());
            work->m_rect.w = GCL_StrToInt((char *)GCL_GetParamResult());
            work->m_rect.h = GCL_StrToInt((char *)GCL_GetParamResult());
        }
        else
        {
            work->m_rect.x = work->w_rect.x;
            work->m_rect.y = work->w_rect.y;
            work->m_rect.w = work->w_rect.w;
            work->m_rect.h = work->w_rect.h;
        }

        work->m_rect.x = work->w_rect.x + 16;
        work->m_rect.y = work->w_rect.y + 12;
        work->m_rect.w = work->w_rect.w - 16;
        work->m_rect.h = work->w_rect.h - 12;

        if (GCL_GetOption('p'))
        {
            work->proc = GCL_StrToInt((char *)GCL_GetParamResult());
        }
        else
        {
            work->proc = 0;
        }

        if (GCL_GetOption('f'))
        {
            work->flag = TRUE;
        }
        else
        {
            work->flag = FALSE;
        }

        work->name = name;
        work->f16C = work->m_rect.h / 18;

        if (GetResources(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
