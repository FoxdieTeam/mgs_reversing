#include "evpanel.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/camera.h"
#include "linkvar.h"
#include "game/vibrate.h"
#include "takabe/thing.h"
#include "sd/g_sound.h"
#include "strcode.h"

extern GM_CAMERA    GM_Camera;
extern int          GM_CameraShakeOffset;

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL4

//  #61808a  97,128,138
//  #202020  32, 32, 32

typedef struct EvPanelWork
{
    GV_ACT         actor;
    DG_PRIM       *field_20; // POLY_FT4
    DG_PRIM       *field_24; // POLY_FT4
    unsigned short field_28;
    unsigned short field_2A;
    unsigned short name;
    short          field_2E;
    short          button_count;
    short          current_button_idx;
    char           field_34;
    char           field_35;
    short          field_36;
    short          field_38;
    short          field_3A;
    short          field_3C;
    short          field_3E;
    short          field_40;
    short          field_42;
    short          field_44;
    short          field_46;
    short          field_48;
    short          field_4A;
    int            field_4C;
    char          *field_50;
    int            field_54;
    int            field_58;
    int            field_5C;
    int            field_60;
    int            field_64;
    int            field_68;
    int            field_6C;
    int            field_70;
    int            field_74;
    int            field_78;
    int            field_7C;
    int            field_80;
    SVECTOR        f84;
    SVECTOR        f8C;
    SVECTOR        field_94[4];
    SVECTOR        field_B4[0];
} EvPanelWork;

/*---------------------------------------------------------------------------*/

unsigned short s03e_dword_800C3268[] = {
    0x121F,
    0x8D5C,
    HASH_ENTER,     // GV_StrCode("入る")
    HASH_LEAVE,     // GV_StrCode("出る")
    0x8591,
    0x6555,
    0x2EAB
};

char s03e_dword_800C3278[] = {0x7F, 0x02, 0x00, 0x00};
char s03e_dword_800C327C[] = {0x55, 0x02, 0x6E, 0x02, 0x1E, 0x0E, 0x41, 0x04, 0x7D, 0x06, 0x5F, 0x06, 0x46, 0x08, 0x37, 0x0A, 0x2D, 0x0C, 0x00, 0x00};
char s03e_dword_800C3290[] = {0x00, 0x0A, 0x7F, 0x02, 0x00, 0x1E, 0x7F, 0x02, 0x00, 0x00, 0x00, 0x00};
char s03e_dword_800C329C[] = {0x23, 0x04, 0x4B, 0x04, 0x87, 0x06, 0x41, 0x08, 0x2D, 0x0C, 0x41, 0x06, 0x5F, 0x04, 0x00, 0x00};

const char s03e_aMessagein_800CBF18[] = "message in\n";
const char s03e_aMessageout_800CBF24[] = "message out\n";
const char s03e_aMessagex_800CBF34[] = "message %X\n";
const char s03e_aNofloorproc_800CBF40[] = "NO FLOOR PROC\n";
const char s03e_aRotd_800CBF50[] = "ROT %d\n";
const char s03e_aReqdoorclose_800CBF58[] = "REQ:DOOR CLOSE\n";
const char s03e_aInitopen_800CBF68[] = "INiTOPEN\n";

EvPanelWork *SECTION("overlay.bss") s03e_dword_800CC6B8;

/*---------------------------------------------------------------------------*/

static void s03e_evpanel_800C33E0(DG_PRIM *prim, int texid)
{
    int       i;
    POLY_FT4 *poly;
    DG_TEX   *tex;
    int       x, y, w, h;

    for (i = 0; i < 2; i++)
    {
        poly = &prim->packs[i]->poly_ft4;
        tex = DG_GetTexture(texid);

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;
        setUVWH(poly, x, y, w, h);

        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
    }
}

static int s03e_evpanel_800C3488(EvPanelWork *work)
{
    GV_MSG      *msg;
    int          n_msgs;
    int          message;
    int          code;
    unsigned int i;

    n_msgs = GV_ReceiveMessage(work->name, &msg);
    message = 0;

    for (; n_msgs > 0; n_msgs--)
    {
        code = msg->message[0];

        if (code == HASH_KILL)
        {
            GV_DestroyActor(&work->actor);
            return 0;
        }

        for (i = 0; i < 7; i++)
        {
            if (s03e_dword_800C3268[i] != code)
            {
                continue;
            }
                message |= 1 << i;

            if (code == HASH_ENTER || code == HASH_LEAVE)
            {
                if (msg->message[1] == CHARA_SNAKE)
                {
                    message |= 0x100;
                }
                else
                {
                    message |= 0x200;
                }

                if (code == HASH_ENTER)
                {
                    printf((char *)s03e_aMessagein_800CBF18);
                    work->field_44++;
                }
                else
                {
                    printf((char *)s03e_aMessageout_800CBF24);

                    if (--work->field_44 < 0)
                    {
                        work->field_44 = 0;
                    }
                }
            }
            else if (code == 0x8591)
            {
                if (msg->message[1] == HASH_ENTER)
                {
                    message |= 0x1000;
                }
                else
                {
                    message |= 0x2000;
                }
            }
            else if (code == 0x2EAB)
            {
                if (msg->message_len >= 2)
                {
                    message |= 0x400;
                    work->f8C.pad = msg->message[1];
                }
            }
            else if (code == 0x121F)
            {
                if ((msg->message_len >= 2) && (msg->message[1] == 0))
                {
                    work->field_36 = -1;
                }
                else
                {
                    work->field_36 = 0;
                }
            }
        }

        msg++;
    }

    if (message != 0)
    {
        printf((char *)s03e_aMessagex_800CBF34, message);
    }

    return message;
}

static void s03e_evpanel_800C36B0(EvPanelWork *work)
{
    GCL_ARGS args;
    int      code;
    int      proc;
    long     data[1];
    char    *script;
    int      i;

    script = work->field_50;
    for (i = 0; i < work->button_count; i++)
    {
        script = GCL_GetNextValue(script, &code, &proc);
        if (script == NULL)
        {
            printf((char *)s03e_aNofloorproc_800CBF40);
        }

        if (i == work->current_button_idx)
        {
            args.argc = 1;
            args.argv = data;

            data[0] = work->f8C.vy;
            printf((char *)s03e_aRotd_800CBF50, work->f8C.vy);

            GCL_ExecProc(proc, &args);
            break;
        }
    }
}

static void EvPanelUpdateHighlightedButton_800C3778(EvPanelWork *work)
{
    int       i, j;
    POLY_FT4 *poly;

    for (i = 0; i < 2; i++)
    {
        poly = &work->field_20->packs[i]->poly_ft4;

        for (j = 0; j < work->button_count; j++)
        {
            if (j == work->current_button_idx)
            {
                // Highlighted
                poly->r0 = GET_R_FROM_RGBA(COLOR_WHITE); // 255;
                poly->g0 = GET_G_FROM_RGBA(COLOR_WHITE); // 255;
                poly->b0 = GET_B_FROM_RGBA(COLOR_WHITE); // 255;
            }
            else
            {
                // Not highlighted
                poly->r0 = GET_R_FROM_RGBA(COLOR_GRAY); // 128;
                poly->g0 = GET_G_FROM_RGBA(COLOR_GRAY); // 128;
                poly->b0 = GET_B_FROM_RGBA(COLOR_GRAY); // 128;
            }

            poly++;
        }
    }
}

static void s03e_evpanel_800C37FC(EvPanelWork *work, int index)
{
    int       i;
    POLY_FT4 *poly;

    if (index == 2)
    {
        index = (GV_Time / 8) % 2;
    }

    for (i = 0; i < 2; i++)
    {
        poly = &work->field_24->packs[i]->poly_ft4;

        if (index != 0)
        {
            poly->r0 = 97;
            poly->g0 = 128;
            poly->b0 = 138;
        }
        else
        {
            poly->r0 = 32;
            poly->g0 = 32;
            poly->b0 = 32;
        }
    }
}

static void s03e_evpanel_800C3898(EvPanelWork *work)
{
    GV_MSG msg;

    msg.address = work->field_3A;
    msg.message[0] = HASH_ENTER;
    msg.message[1] = CHARA_SNAKE;
    msg.message_len = 2;

    GV_SendMessage(&msg);

    work->field_42 = 2;
    work->field_38 = 0x258;
}

static void s03e_evpanel_800C38F4(EvPanelWork *work)
{
    GV_MSG msg;

    msg.address = work->field_3A;
    msg.message[0] = HASH_LEAVE;
    msg.message[1] = CHARA_SNAKE;
    msg.message_len = 2;

    GV_SendMessage(&msg);

    printf((char *)s03e_aReqdoorclose_800CBF58);
    work->field_42 = 1;
}

static void s03e_evpanel_800C3950(EvPanelWork *work, short arg1)
{
    GV_MSG msg;

    if (work->field_46 != 0)
    {
        msg.address = work->field_46;
        msg.message[0] = 0xBCD2;
        msg.message[1] = arg1;
        msg.message_len = 2;

        GV_SendMessage(&msg);
    }
}

static void s03e_evpanel_800C3994(void)
{
    GM_Camera.eye = s03e_dword_800CC6B8->f84;
    GM_Camera.rotate = s03e_dword_800CC6B8->f8C;
    GM_Camera.field_28 = 1;
}

static void s03e_evpanel_800C39F8(EvPanelWork *work)
{
    s03e_dword_800CC6B8 = work;

    GM_SetCameraCallbackFunc_8002FD84(1, s03e_evpanel_800C3994);

    work->field_4C = GM_Camera.flags;
    work->f8C.vy = work->field_48;
    work->field_4A = work->field_48;

    GM_Camera.flags = 0x2;
    GM_Camera.field_2A = 2;
    GM_Camera.interp = 30;

    GM_PlayerStatus |= PLAYER_PAD_OFF;

    DG_InvisibleObjs(GM_PlayerBody->objs);

    if (((1 << GM_CurrentItemId) & 0x101E) != 0)
    {
        GM_CurrentItemId = IT_None;
    }

    if (((1 << GM_CurrentWeaponId) & 0x210) != 0)
    {
        GM_CurrentWeaponId = WP_None;
    }
}

static void s03e_evpanel_800C3AD0(EvPanelWork *work)
{
    GM_Camera.flags = work->field_4C;
    GM_Camera.field_2A = 2;
    GM_Camera.interp = 30;

    GM_SetCameraCallbackFunc_8002FD84(1, NULL);
}

static void s03e_evpanel_800C3B14(EvPanelWork *work, int message)
{
    if ((message & 0x104) == 0x104)
    {
        DG_VisiblePrim(work->field_20);

        work->field_2E = 3;

        if (work->field_42 == 1)
        {
            s03e_evpanel_800C3898(work);
        }
    }
}

static void Act(EvPanelWork *work)
{
    int message;
    int release;
    int status;
    int addend;
    int code;
    int offset;

    message = s03e_evpanel_800C3488(work);

    switch(work->field_2E)
    {
    case 0:
        if (message & 0x1)
        {
            if (work->field_36 < 0)
            {
                work->field_36 = 0;
            }
            else
            {
                work->field_36 = (GV_Time % 6) * 30;

                if ((GV_Time & 0x7) == 0)
                {
                    work->field_36 = 300;
                }
            }

            work->field_2E = 1;
        }
        else
        {
            s03e_evpanel_800C3B14(work, message);
        }

        if (!(message & 0x40))
        {
            return;
        }

        s03e_evpanel_800C39F8(work);

        if (message & 0x400)
        {
            work->f8C.vy = work->f8C.pad;
            work->field_4A = work->f8C.vy;
        }

        GM_Camera.field_2A = 0;
        GM_Camera.interp = -1;

        work->field_36 = 25;
        work->field_2E = 9;

        printf((char *)s03e_aInitopen_800CBF68);

        NewPadVibration(s03e_dword_800C3290, 1);
        NewPadVibration(s03e_dword_800C329C, 2);

        DG_UnDrawFrameCount = 0x7fff0000;

        GM_SetSound(0xff0000fe, SD_ASYNC);
        return;

    case 1:
        DG_VisiblePrim(work->field_24);

        s03e_evpanel_800C37FC(work, 1);
        s03e_evpanel_800C33E0(work->field_24, work->field_2A);

        if (work->field_36 == 30)
        {
            GM_SeSet2(0, 63, SE_ELEVATOR_STOP);
        }

        if (--work->field_36 < 0)
        {
            if (work->field_42 != 2)
            {
                s03e_evpanel_800C3898(work);
            }

            work->field_2E = 2;
            GM_SeSet2(0, 63, SE_ELEVATOR_CHIME);
        }

        s03e_evpanel_800C3B14(work, message);
        break;

    case 2:
        s03e_evpanel_800C37FC(work, 2);
        s03e_evpanel_800C3B14(work, message);

        if (GM_AlertMode != 0)
        {
            work->field_38 = 600;
        }

        if (work->field_42 == 0)
        {
            work->field_2E = 0;

            s03e_evpanel_800C37FC(work, 1);
            s03e_evpanel_800C33E0(work->field_24, work->field_28);

            DG_VisiblePrim(work->field_24);
            break;
        }

        if (work->field_44 < 1)
        {
            break;
        }

        if (work->field_42 == 1)
        {
            s03e_evpanel_800C3898(work);

            if ((message & 0x2010) == 0x2010)
            {
                message &= ~0x2010;
            }
        }
        else
        {
            work->field_38 = 600;
        }
        break;

    case 3:
        work->field_38 = 100;

        if (message & 0x2)
        {
            if (GM_AlertMode == 0)
            {
                if ((GM_Camera.first_person != 0) || (GM_PlayerStatus & PLAYER_WATCH))
                {
                    if ((GM_UnkFlagBE == 0) || !(GM_PlayerStatus & PLAYER_MOVE_WATCH))
                    {
                        break;
                    }
                }

                if (work->field_44 == 1)
                {
                    s03e_evpanel_800C39F8(work);
                    work->current_button_idx = work->field_34;
                    EvPanelUpdateHighlightedButton_800C3778(work);
                    work->field_2E = 5;
                    GM_SeSet2(0, 63, SE_ITEM_OPENWINDOW);
                }
            }
        }
        else if ((message & 0x108) == 0x108)
        {
            DG_InvisiblePrim(work->field_20);

            if (work->field_42 == 1)
            {
                s03e_evpanel_800C3898(work);
            }

            work->field_2E = 2;
        }
        break;

    case 5:
    case 6:
        work->field_38 = 100;

        DG_InvisibleObjs(GM_PlayerBody->objs);

        if (work->field_2E == 5)
        {
            if (!(GV_PadData[0].status & (PAD_SQUARE | PAD_CROSS | PAD_CIRCLE | PAD_TRIANGLE)))
            {
                work->field_2E = 6;
            }
        }
        else
        {
            release = GV_PadData[0].release;
            status = GV_PadData[0].status;

            if (GV_PadData[0].press & (PAD_DOWN | PAD_UP))
            {
                if (GV_PadData[0].press & PAD_UP)
                {
                    addend = -1 + work->button_count; // + modulo so that we don't go into negative numbers
                }
                else
                {
                    addend = 1;
                }

                work->current_button_idx = (work->current_button_idx + addend) % work->button_count;

                EvPanelUpdateHighlightedButton_800C3778(work);
                GM_SeSet2(0, 63, SE_MENU_CURSOR);
            }

            if (status & PAD_LEFT)
            {
                work->field_4A = (work->field_4A + 32) & 0xFFF;

                if (GV_DiffDirS(work->field_4A, work->field_3C) < 0)
                {
                    work->field_4A = work->field_3C;
                }
            }

            work->f8C.vy = GV_NearExp4P(work->f8C.vy, work->field_4A);

            if (status & PAD_RIGHT)
            {
                work->field_4A = (work->field_4A - 32) & 0xFFF;

                if (GV_DiffDirS(work->field_4A, work->field_3E) > 0)
                {
                    work->field_4A = work->field_3E;
                }

                work->f8C.vy = GV_NearExp4P(work->f8C.vy, work->field_4A);
            }

            if (release & PAD_CIRCLE)
            {
                if (work->current_button_idx == work->field_34 || work->current_button_idx == work->button_count - 1)
                {
                    message |= 0x20;
                }
                else
                {
                    work->field_2E = 7;
                    work->field_38 = 15;
                }

                GM_SeSet2(0, 63, SE_ELEVATOR_BUTTON);
            }

            if (release & PAD_CROSS)
            {
                message |= 0x20;
            }
        }

        if ((GM_AlertMode != 0) ||
            ((message & 0x20) != 0) ||
            ((GM_PlayerStatus & PLAYER_DAMAGED) != 0) ||
            (work->field_44 > 1))
        {
            s03e_evpanel_800C3AD0(work);

            if (work->field_42 != 2)
            {
                s03e_evpanel_800C3898(work);
            }

            work->field_2E = 11;
        }
        break;

    case 11:
        if (GM_Camera.interp < 24)
        {
            work->field_42 = 2;
            DG_VisibleObjs(GM_PlayerBody->objs);
            GM_PlayerStatus &= ~PLAYER_PAD_OFF;
            work->field_2E = 3;
        }
        break;

    case 7:
        if ((work->field_44 > 1) || (GM_PlayerStatus & PLAYER_DAMAGED))
        {
            s03e_evpanel_800C3AD0(work);

            if (work->field_42 != 2)
            {
                s03e_evpanel_800C3898(work);

                if ((message & 0x2010) == 0x2010)
                {
                    message &= ~0x2010;
                }
            }

            work->field_2E = 11;
            break;
        }

        if (work->field_42 == 0)
        {
            work->field_2E = 8;
            work->field_36 = 30;

            GM_GameStatus |= STATE_ALL_OFF | STATE_ENEMY_OFF;
            DG_InvisibleObjs(GM_PlayerBody->objs);

            if (work->current_button_idx < work->field_34)
            {
                code = 'a';
            }
            else
            {
                code = 'b';
            }

            s03e_evpanel_800C3950(work, code);

            NewPadVibration(s03e_dword_800C3278, 1);
            NewPadVibration(s03e_dword_800C327C, 2);
        }
        break;

    case 8:
        if (work->field_36 >= 1)
        {
            DG_InvisibleObjs(GM_PlayerBody->objs);

            work->field_36--;
            if ((work->field_36 > 2) && (work->field_36 < 10))
            {
                GM_CameraShakeOffset = work->field_36 / 2;

                if ((work->field_36 & 0x1) != 0)
                {
                    GM_CameraShakeOffset = -GM_CameraShakeOffset;
                }
            }
        }
        else
        {
            if (work->field_50 != 0)
            {
                s03e_evpanel_800C36B0(work);
                work->field_50 = 0;
            }

            DG_InvisibleObjs(GM_PlayerBody->objs);
        }
        break;

    case 9:
        GM_GameStatus |= STATE_PADRELEASE | STATE_PAUSE_ONLY;

        if (work->field_36 >= 1)
        {
            if (--work->field_36 < 10)
            {
                if ((work->field_36 & 1) != 0)
                {
                    offset = work->field_36 / 4;
                }
                else
                {
                    offset = 0;
                }

                DG_OffsetDispEnv(offset);
            }
        }
        else if (work->field_36 == 0)
        {
            work->field_36 = -1;
            DG_UnDrawFrameCount = 0;
            s03e_evpanel_800C3898(work);
            GM_SeSet2(0, 63, SE_ELEVATOR_CHIME);
        }

        if ((message & 0x1010) == 0x1010)
        {
            work->field_36 = 30;
            work->field_2E = 10;
        }
        break;

    case 10:
        if (work->field_36-- == 1)
        {
            s03e_evpanel_800C3AD0(work);
            work->field_2E = 11;
            GM_GameStatus &= ~( STATE_PADRELEASE | STATE_PAUSE_ONLY );
            s03e_evpanel_800C33E0(work->field_24, work->field_2A);
            break;
        }
        break;
    }

    if ((message & 0x2010) == 0x2010)
    {
        if (work->field_42 == 1)
        {
            work->field_42 = 0;
            work->field_38 = 0;
        }
    }
    else if (work->field_38 > 0)
    {
        if ((work->field_2E != 7) && (work->field_44 > 0))
        {
            work->field_38 = 30;
        }

        if (work->field_38-- == 1)
        {
            s03e_evpanel_800C38F4(work);
        }
    }
}

/*---------------------------------------------------------------------------*/

static void Die(EvPanelWork *work)
{
    GM_FreePrim(work->field_20);
    GM_FreePrim(work->field_24);
}

/*---------------------------------------------------------------------------*/

static void s03e_evpanel_800C45E4(POLY_FT4 *packs, DG_TEX *tex, int n_packs)
{
    int i;
    int x, y, w, h;

    for (i = 0; i < n_packs; i++)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);

        x = tex->off_x;
        w = tex->w;

        packs->u2 = x;
        packs->u0 = x;
        packs->u3 = w + x;
        packs->u1 = w + x;

        y = tex->off_y;
        h = tex->h + 1;

        packs->v1 = y + (h * i) / n_packs;
        packs->v0 = y + (h * i) / n_packs;
        packs->v3 = y + ((h * (i + 1)) / n_packs) - 1;
        packs->v2 = y + ((h * (i + 1)) / n_packs) - 1;

        packs->tpage = tex->tpage;
        packs->clut = tex->clut;

        packs->r0 = 128;
        packs->g0 = 128;
        packs->b0 = 128;

        packs++;
    }
}

static void s03e_evpanel_800C470C(SVECTOR *vecs, int n_vecs, int x, int y)
{
    int height;
    int top;
    int i;
    int x0, x1;
    int y0, y1;

    height = (y / n_vecs) / 2;
    top = (y / 2) - height;
    x1 = x / 2;

    for (i = 0; i < n_vecs; i++)
    {
        x0 = -x1;
        y0 = top + height;
        y1 = top - height;
        top -= height * 2;

        setVector(&vecs[0], x0, y0, 0);
        setVector(&vecs[1], x1, y0, 0);
        setVector(&vecs[2], x0, y1, 0);
        setVector(&vecs[3], x1, y1, 0);
        vecs += 4;
    }
}

static int s03e_evpanel_800C47D0(EvPanelWork *work, DG_PRIM **out, SVECTOR *vec, int n_prims)
{
    MATRIX   pos;
    SVECTOR  trans;
    SVECTOR  rot;
    SVECTOR  sp48;
    int      texid;
    int      k500;
    DG_PRIM *prim;
    DG_TEX  *tex;

    GCL_StrToSV(GCL_GetParamResult(), &trans);
    GCL_StrToSV(GCL_GetParamResult(), &rot);
    GCL_StrToSV(GCL_GetParamResult(), &sp48);

    k500 = GCL_GetNextParamValue();
    texid = GCL_GetNextParamValue();

    if (n_prims == 1)
    {
        work->field_28 = texid;

        if (GCL_GetParamResult())
        {
            work->field_2A = GCL_GetNextParamValue();
        }
        else
        {
            work->field_2A = texid;
        }
    }

    prim = DG_GetPrim(DG_PRIM_ONEFACE | DG_PRIM_POLY_FT4, n_prims, 0, vec, NULL);
    *out = prim;
    if (prim == NULL)
    {
        return 0;
    }

    tex = DG_GetTexture(texid);
    if (tex == NULL)
    {
        return 0;
    }

    RotMatrix(&rot, &pos);

    pos.t[0] = trans.vx;
    pos.t[1] = trans.vy;
    pos.t[2] = trans.vz;

    DG_SetPos(&pos);
    DG_PutPrim(&prim->world);

    prim->field_2E_k500 = k500;

    s03e_evpanel_800C45E4(&prim->packs[0]->poly_ft4, tex, n_prims);
    s03e_evpanel_800C45E4(&prim->packs[1]->poly_ft4, tex, n_prims);

    s03e_evpanel_800C470C(vec, n_prims, sp48.vx, sp48.vy);
    return 1;
}

static int GetResources(EvPanelWork *work, int map, int name, int button_count)
{
    GM_CurrentMap = map;

    if (!GCL_GetOption('p'))
    {
        return -1;
    }

    if (!s03e_evpanel_800C47D0(work, &work->field_20, work->field_B4, button_count))
    {
        return -1;
    }

    if (!GCL_GetOption('b'))
    {
        return -1;
    }

    if (!s03e_evpanel_800C47D0(work, &work->field_24, work->field_94, 1))
    {
        return -1;
    }

    s03e_evpanel_800C37FC(work, 0);

    work->field_34 = work->current_button_idx = THING_Gcl_GetInt('f');
    work->field_3A = THING_Gcl_GetInt('r');
    work->field_46 = THING_Gcl_GetInt('t');

    work->button_count = button_count;
    work->name = name;

    work->field_50 = GCL_GetOption('e');

    if (GCL_GetOption('c'))
    {
        GCL_StrToSV(GCL_GetParamResult(), &work->f84);
        GCL_StrToSV(GCL_GetParamResult(), &work->f8C);

        work->field_3C = GCL_GetNextParamValue();
        work->field_3E = GCL_GetNextParamValue();

        work->field_48 = work->f8C.vy;

        DG_VisiblePrim(work->field_24);
        DG_InvisiblePrim(work->field_20);

        s03e_evpanel_800C37FC(work, 1);
        EvPanelUpdateHighlightedButton_800C3778(work);
        return 0;
    }

    return -1;
}

/*---------------------------------------------------------------------------*/

void *NewEvPanel(int name, int where, int argc, char **argv)
{
    EvPanelWork *work;
    int          button_count;

    button_count = THING_Gcl_GetIntDefault('n', 3);
    work = GV_NewActor(EXEC_LEVEL, sizeof(EvPanelWork) + sizeof(SVECTOR) * button_count * 4);
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "evpanel.c");
        if (GetResources(work, where, name, button_count) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
