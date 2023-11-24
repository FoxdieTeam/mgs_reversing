#include "linker.h"
#include "jimctrl.h"
#include "Menu/menuman.h"
#include "unknown.h"
#include "libfs/libfs.h"
#include "Game/linkvarbuf.h"

extern array_800B933C_child array_800B933C[array_800B933C_SIZE];

extern Actor_JimCtrl jimCtrlActor_800B82F0;

extern int gStr_FadeOut1_800BF16C;
extern int dword_800B9358;

char *dword_8009E28C = NULL;

void jimctrl_act_helper_set_first_80037F2C(int index, int value)
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

void jimctrl_init_helper_clear_80037FB8(void)
{
    int                   i = array_800B933C_SIZE - 2;
    array_800B933C_child *pIter = &array_800B933C[i] + 1;
    for (; i >= 0; i--)
    {
        pIter->field_0 = 0;
        pIter--;
    }
}

void jimctrl_act_helper_clear_first_80037FE0(int index, int value)
{
    array_800B933C_child *pIter = &array_800B933C[1];
    pIter[--index].field_0 = value;
}


void jimctrl_helper_null_80037FFC(int a, int b)
{
}


void jimctrl_kill_helper_clear_80038004(Actor_JimCtrl *pJimCtrl)
{
    array_800B933C_child *pIter;
    int                   i;

    if (pJimCtrl->field_44_subtitles)
    {
        menu_JimakuClear_80049518();
    }

    if (pJimCtrl->field_38 != 0)
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



static inline void jimctrl_act_helper_80038070(Actor_JimCtrl *work, int str_counter)
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
            menu_JimakuWrite_800494E8(pData, 0);
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
            menu_JimakuClear_80049518();
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

static inline void jimctrl_act_helper2_80038070(Actor_JimCtrl *work, int str_counter)
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


void jimctrl_act_80038070(Actor_JimCtrl *work)
{
    int   str_counter;
    void *pStrData;
    void *pStrData2;
    int   size;
    int  *pSubtitles;
    SubtitleHeader *pHeader;
    SubtitleHeader *pHeader2;

    if (FS_StreamIsForceStop_800243C8())
    {
        GV_DestroyActor_800151C8(&work->field_0_actor);
    }

    str_counter = get_str_counter_80088CA0();
    if ((str_counter < 0) || (gStr_FadeOut1_800BF16C == 0))
    {
        if (work->field_30 < 0)
        {
            return;
        }

        GV_DestroyActor_800151C8(&work->field_0_actor);
        return;
    }

    str_counter >>= 2;

    pStrData2 = FS_StreamGetData_800240E0(work->field_27);
    if (pStrData2)
    {
        sub_800241B4(pStrData2);
    }

    if (work->field_30 < 0)
    {
        work->field_30 = 0;
    }

    switch (work->field_20)
    {
    case 0:
        pStrData = FS_StreamGetData_800240E0(work->field_26);

        if (!pStrData)
        {
            return;
        }

        size = FS_StreamGetSize_80024188(pStrData);
        memcpy(jimCtrlActor_800B82F0.field_50_buffer, pStrData, size);
        sub_800241B4(pStrData);

        if (!work->field_34)
        {
            pHeader = (SubtitleHeader *)jimCtrlActor_800B82F0.field_50_buffer;

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

            font_set_font_addr_80044BC0(3, (char *)pHeader + pHeader2->font_offset);
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


void jimctrl_kill_8003853C(Actor_JimCtrl *pJimCtrl)
{
    jimctrl_kill_helper_clear_80038004(pJimCtrl);
    dword_8009E28C = NULL;
    FS_StreamClose_80024098();
}

GV_ACT *jimctrl_init_80038568(u_long flags)
{
    int           *seekResult;
    u_long         toSeek = 4;
    Actor_JimCtrl *pJimActor = &jimCtrlActor_800B82F0;
    if (flags & 0x80)
    {
        toSeek = 7;
    }
    seekResult = FS_StreamGetData_800240E0(toSeek);

    if (GM_GameStatusFlag & 0x100)
    {
        jimCtrlActor_800B82F0.field_27 = 3;
        jimCtrlActor_800B82F0.field_26 = 6;
    }
    else
    {
        jimCtrlActor_800B82F0.field_27 = 6;
        jimCtrlActor_800B82F0.field_26 = 3;
    }

    if (seekResult != 0)
    {
        sub_800241B4(seekResult);
    }

    if (pJimActor->field_0_actor.mFnUpdate == (TActorFunction)jimctrl_act_80038070)
    {
        return &pJimActor->field_0_actor;
    }
    else
    {
        flags &= 0xf;
        pJimActor->field_28 = 0;
        jimctrl_init_helper_clear_80037FB8();
        GV_InitActor_800150A8(1, &pJimActor->field_0_actor, 0);

        GV_SetNamedActor_8001514C(&pJimActor->field_0_actor, (TActorFunction)jimctrl_act_80038070,
                                  (TActorFunction)jimctrl_kill_8003853C, "jimctrl.c");

        pJimActor->field_24 = flags;

        FS_StreamOpen_80024060();

        pJimActor->field_30 = -1;
        pJimActor->field_2C = 0;
        pJimActor->field_34 = 0;
        pJimActor->field_20 = 0;
        dword_800B9358 = 0;


        return &jimCtrlActor_800B82F0.field_0_actor;
    }
}

char* menu_radio_codec_helper_helper17_80038678(void)
{
    return dword_8009E28C;
}


int jimctrl_80038688(void)
{
    return dword_800B9358;
}


array_800B933C_child *sub_80038698(void)
{
    return &array_800B933C[1];
}
