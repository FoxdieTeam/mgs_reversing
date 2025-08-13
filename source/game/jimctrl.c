#include "jimctrl.h"

#include <stdio.h>
#include "common.h"
#include "libfs/libfs.h"
#include "linkvar.h"
#include "menu/menuman.h"
#include "sd/sd_cli.h"

extern array_800B933C_child array_800B933C[array_800B933C_SIZE];

extern JimakuCtrlWork jimctrl_work;

extern int str_status;
extern int dword_800B9358;

char *dword_8009E28C = NULL;

static void jimctrl_act_helper_set_first_80037F2C(int index, int value)
{
    array_800B933C_child *helper = &array_800B933C[index];
    if (value == 4)
    {
        helper->field_2 = 1;
    }
    else if (value < 4)
    {
        helper->field_3 = value;
    }
}

// return the index for the face frame, 0 for idle face
unsigned int jimctrl_helper_80037F68(unsigned int header)
{
    u_short                  field_2_preClear;
    array_800B933C_child *pIter;
    u_char                 *pField;
    int                   i;

    pIter = &array_800B933C[1];
    i = 0;
    pField = &pIter->field_2;
    for (; i < array_800B933C_SIZE - 1; i++)
    {
        if (pIter->field_0 == header)
        {
            field_2_preClear = *pField;
            *pField = 0;
            return (field_2_preClear << 8 | *++pField);
        }
        pField += sizeof(array_800B933C_child);
        pIter++;
    }

    return 0;
}

static void jimctrl_init_helper_clear_80037FB8(void)
{
    int                   i = array_800B933C_SIZE - 2;
    array_800B933C_child *pIter = &array_800B933C[i] + 1;
    for (; i >= 0; i--)
    {
        pIter->field_0 = 0;
        pIter--;
    }
}

static void jimctrl_act_helper_clear_first_80037FE0(int index, int value)
{
    array_800B933C_child *pIter = &array_800B933C[1];
    pIter[--index].field_0 = value;
}


static void jimctrl_helper_null_80037FFC(int a, int b)
{
    /* do nothing */
}

static void jimctrl_kill_helper_clear_80038004(JimakuCtrlWork *work)
{
    array_800B933C_child *pIter;
    int                   i;

    if (work->field_44_subtitles)
    {
        MENU_JimakuClear();
    }

    if (work->field_38 != 0)
    {
        i = 0;
        pIter = &array_800B933C[i] + 1;
        for (; i < array_800B933C_SIZE - 1; i++)
        {
            pIter->field_2 = 0;
            pIter->field_3 = 0;
            pIter++;
        }
    }
}

static inline void jimctrl_act_helper_80038070(JimakuCtrlWork *work, int str_counter)
{
    int  *pSubtitles = work->field_44_subtitles;
    int   f48;
    char *pData;
    int   size;

    if (!pSubtitles)
    {
        return;
    }

    f48 = work->field_48;

    if (f48 == 0)
    {
        if (str_counter < pSubtitles[1])
        {
            return;
        }

        pData = (char *)(pSubtitles + 4);

        switch (work->field_24)
        {
        case 0:
        case 2:
            MENU_JimakuWrite(pData, 0);
            break;

        case 1:
            break;
        }

        dword_8009E28C = pData;
        dword_800B9358++;
        work->field_48 = pSubtitles[1] + pSubtitles[2];
    }
    else if (f48 <= str_counter)
    {
        switch (work->field_24)
        {
        case 0:
        case 2:
            MENU_JimakuClear();
            break;

        case 1:
            break;
        }

        work->field_48 = NULL;

        size = *pSubtitles;
        dword_8009E28C = NULL;

        if (size != 0)
        {
            pSubtitles = (int *)((char *)pSubtitles + size);
        }
        else
        {
            pSubtitles = NULL;
        }

        work->field_44_subtitles = pSubtitles;
    }
}

static inline void jimctrl_act_helper2_80038070(JimakuCtrlWork *work, int str_counter)
{
    int value;

    while (work->field_30 < str_counter)
    {
        work->field_30++;
        work->field_40--;

        while (work->field_40 < 1)
        {
            value = *work->field_38++;

            if (value & 0x80)
            {
                jimctrl_act_helper_set_first_80037F2C(work->field_3C, (value >> 4) & 0x7);
                work->field_40 = value & 0xF;
            }
            else
            {
                switch (value >> 4)
                {
                case 0:
                    printf("KUTIPAKU END\n");
                    jimctrl_act_helper_set_first_80037F2C(work->field_3C, 0);
                    work->field_38 = NULL;
                    return;

                case 1:
                    jimctrl_act_helper_set_first_80037F2C(work->field_3C, value & 0xF);
                    work->field_40 = *work->field_38++;
                    break;

                case 2:
                    jimctrl_act_helper_clear_first_80037FE0(value & 0xF, (work->field_38[0] << 8) | work->field_38[1]);
                    work->field_38 += 2;
                    break;

                case 4:
                    work->field_3C = value & 0xF;
                    break;

                case 5:
                    jimctrl_act_helper_set_first_80037F2C(work->field_3C, value & 0xF);
                    work->field_40 = (work->field_38[0] << 8) | work->field_38[1];
                    work->field_38 += 2;
                    break;

                case 6:
                    work->field_40 = *work->field_38++;
                    jimctrl_helper_null_80037FFC((work->field_38[0] << 8) | work->field_38[1], (work->field_38[2] << 8) | work->field_38[3]);
                    break;
                }
            }
        }
    }
}


static void Act(JimakuCtrlWork *work)
{
    int   str_counter;
    void *pStrData;
    void *pStrData2;
    int   size;
    int  *pSubtitles;
    SubtitleHeader *pHeader;
    SubtitleHeader *pHeader2;

    if (FS_StreamIsForceStop())
    {
        GV_DestroyActor(&work->actor);
    }

    str_counter = get_str_counter();
    if ((str_counter < 0) || (str_status == 0))
    {
        if (work->field_30 < 0)
        {
            return;
        }

        GV_DestroyActor(&work->actor);
        return;
    }

    str_counter >>= 2;

    pStrData2 = FS_StreamGetData(work->field_27);
    if (pStrData2)
    {
        FS_StreamClear(pStrData2);
    }

    if (work->field_30 < 0)
    {
        work->field_30 = 0;
    }

    switch (work->field_20)
    {
    case 0:
        pStrData = FS_StreamGetData(work->field_26);

        if (!pStrData)
        {
            return;
        }

        size = FS_StreamGetSize(pStrData);
        memcpy(jimctrl_work.field_50_buffer, pStrData, size);
        FS_StreamClear(pStrData);

        if (!work->field_34)
        {
            pHeader = (SubtitleHeader *)jimctrl_work.field_50_buffer;

            work->field_34 = (int *)pHeader;
            work->field_38 = (char *)pHeader + pHeader->data_offset;

            pSubtitles = (int *)((char *)pHeader + pHeader->subtitle_offset);
            pHeader2 = pHeader;

            if ((pSubtitles[0] == 0) && (pSubtitles[1] == 0) && (pSubtitles[2] == 0))
            {
                pSubtitles = NULL;
            }

            work->field_44_subtitles = pSubtitles;
            work->field_48 = 0;
            work->field_40 = 0;

            font_set_font_addr(3, (char *)pHeader + pHeader2->font_offset);
        }

        work->field_20 = 1;

    case 1:
        if (str_counter < *work->field_34)
        {
            return;
        }

        work->field_30 = *work->field_34;
        work->field_20 = 2;
        break;

    case 2:
        break;

    default:
        return;
    }

    jimctrl_act_helper_80038070(work, str_counter);

    if (work->field_38)
    {
        jimctrl_act_helper2_80038070(work, str_counter);
    }

    if (work->field_34[1] < str_counter)
    {
        work->field_34 = NULL;
        work->field_20 = 0;
    }
}


static void Die(JimakuCtrlWork *work)
{
    jimctrl_kill_helper_clear_80038004(work);
    dword_8009E28C = NULL;
    FS_StreamClose();
}

void *NewJimakuControl(u_long flags)
{
    int           *seekResult;
    u_long         toSeek = 4;
    JimakuCtrlWork *work = &jimctrl_work;

    if (flags & 0x80)
    {
        toSeek = 7;
    }
    seekResult = FS_StreamGetData(toSeek);

    if (GM_GameStatusFlag & STATUS_ENGLISH)
    {
        jimctrl_work.field_27 = 3;
        jimctrl_work.field_26 = 6;
    }
    else
    {
        jimctrl_work.field_27 = 6;
        jimctrl_work.field_26 = 3;
    }

    if (seekResult != 0)
    {
        FS_StreamClear(seekResult);
    }

    if (work->actor.act == (GV_ACTFUNC)Act)
    {
        return (void *)work;
    }
    else
    {
        flags &= 0xf;
        work->field_28 = 0;
        jimctrl_init_helper_clear_80037FB8();
        GV_InitActor(GV_ACTOR_MANAGER, &work->actor, NULL);

        GV_SetNamedActor(&work->actor, Act, Die, "jimctrl.c");

        work->field_24 = flags;

        FS_StreamOpen();

        work->field_30 = -1;
        work->field_2C = 0;
        work->field_34 = 0;
        work->field_20 = 0;
        dword_800B9358 = 0;


        return (void *)&jimctrl_work;
    }
}

/*---------------------------------------------------------------------------*/

char* menu_radio_codec_helper_helper17_80038678(void)
{
    return dword_8009E28C;
}


int jimctrl_80038688(void)
{
    return dword_800B9358;
}


array_800B933C_child *jimctrl_80038698(void)
{
    return &array_800B933C[1];
}
