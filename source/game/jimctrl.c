#include "jimctrl.h"

#include <stdio.h>
#include "common.h"
#include "linkvar.h"
#include "libfs/libfs.h"
#include "game/game.h"
#include "menu/menuman.h"
#include "sound/sd_cli.h"

typedef struct {
    GV_ACT actor;
    int   field_20;
    short field_24;
    char  field_26;
    char  field_27;
    int   field_28;
    int   field_2C;
    int   field_30;
    int  *field_34;
    char *field_38; // Pointer to data used to update Codec portraits, mainly by 80038070().
    int   field_3C;
    int   field_40;
    // Pointer to subtitles, mainly used by 80038070():
    // - @ 0x80038240 (R): reads the current subtitle; if disabled, the subtitles no longer update.
    // - @ 0x80038340 (W): updates the pointer; if disabled, all the subtitles play in one go.
    int  *field_44_subtitles;
    int   field_48;
    int   field_4C;
} Work;

typedef struct
{
    char *field_0;
    int  *field_4;
    short data_offset;
    short subtitle_offset;
    int   font_offset;
} SubtitleHeader;

Work SECTION(".bss") jimaku_work;
char SECTION(".bss") jimaku_buffer[ 4090 ];
PAKU SECTION(".bss") chara_work[ PAKU_MAX ];
int SECTION(".bss") GM_JimakuCounter;

extern int str_status;

char *dword_8009E28C = NULL;

static void do_paku( int index, int value )
{
    PAKU *chara;

    chara = &chara_work[ index ];
    if ( value == 4 )
    {
        chara->eye = 1;
    }
    else if ( value < 4 )
    {
        chara->mouth = value;
    }
}

// return the index for the face frame, 0 for idle face
unsigned int jimctrl_helper_80037F68(unsigned int header)
{
    u_short                  field_2_preClear;
    PAKU *pIter;
    u_char                 *pField;
    int                   i;

    pIter = &chara_work[1];
    i = 0;
    pField = &pIter->eye;
    for (; i < PAKU_MAX - 1; i++)
    {
        if (pIter->id == header)
        {
            field_2_preClear = *pField;
            *pField = 0;
            return (field_2_preClear << 8 | *++pField);
        }
        pField += sizeof(PAKU);
        pIter++;
    }

    return 0;
}

static void init_id( void )
{
    int i;
    PAKU *chara;

    i = PAKU_MAX - 2;
    chara = &chara_work[ i + 1 ];
    for ( ; i >= 0; i-- )
    {
        chara->id = 0;
        chara--;
    }
}

static void set_id( int index, int id )
{
    PAKU *chara;

    chara = &chara_work[ 1 ];
    chara[ --index ].id = id;
}

static void do_motion( int a, int b )
{
    /* do nothing */
}

static void reset_paku( Work *work )
{
    int i;
    PAKU *chara;

    if ( work->field_44_subtitles != NULL )
    {
        MENU_JimakuClear();
    }

    if ( work->field_38 != 0 )
    {
        chara = &chara_work[ 1 ];
        for ( i = 0; i < PAKU_MAX - 1; i++ )
        {
            chara->eye = 0;
            chara->mouth = 0;
            chara++;
        }
    }
}

static inline void jimctrl_act_helper_80038070(Work *work, int str_counter)
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
        GM_JimakuCounter++;
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

static inline void jimctrl_act_helper2_80038070(Work *work, int str_counter)
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
                do_paku(work->field_3C, (value >> 4) & 0x7);
                work->field_40 = value & 0xF;
            }
            else
            {
                switch (value >> 4)
                {
                case 0:
                    printf("KUTIPAKU END\n");
                    do_paku(work->field_3C, 0);
                    work->field_38 = NULL;
                    return;

                case 1:
                    do_paku(work->field_3C, value & 0xF);
                    work->field_40 = *work->field_38++;
                    break;

                case 2:
                    set_id(value & 0xF, (work->field_38[0] << 8) | work->field_38[1]);
                    work->field_38 += 2;
                    break;

                case 4:
                    work->field_3C = value & 0xF;
                    break;

                case 5:
                    do_paku(work->field_3C, value & 0xF);
                    work->field_40 = (work->field_38[0] << 8) | work->field_38[1];
                    work->field_38 += 2;
                    break;

                case 6:
                    work->field_40 = *work->field_38++;
                    do_motion((work->field_38[0] << 8) | work->field_38[1], (work->field_38[2] << 8) | work->field_38[3]);
                    break;
                }
            }
        }
    }
}

static void Act(Work *work)
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
        memcpy(jimaku_buffer, pStrData, size);
        FS_StreamClear(pStrData);

        if (!work->field_34)
        {
            pHeader = (SubtitleHeader *)jimaku_buffer;

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


static void Die(Work *work)
{
    reset_paku(work);
    dword_8009E28C = NULL;
    FS_StreamClose();
}

void *NewJimakuControl(u_long flags)
{
    int           *seekResult;
    u_long         toSeek = 4;
    Work *work = &jimaku_work;

    if (flags & 0x80)
    {
        toSeek = 7;
    }
    seekResult = FS_StreamGetData(toSeek);

    if (GM_Configuration & GM_CONFIG_ENGLISH)
    {
        jimaku_work.field_27 = 3;
        jimaku_work.field_26 = 6;
    }
    else
    {
        jimaku_work.field_27 = 6;
        jimaku_work.field_26 = 3;
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
        init_id();
        GV_InitActor(GV_ACTOR_MANAGER, &work->actor, NULL);

        GV_SetNamedActor(&work->actor, Act, Die, "jimctrl.c");

        work->field_24 = flags;

        FS_StreamOpen();

        work->field_30 = -1;
        work->field_2C = 0;
        work->field_34 = 0;
        work->field_20 = 0;
        GM_JimakuCounter = 0;

        return (void *)&jimaku_work;
    }
}

/*---------------------------------------------------------------------------*/

char* menu_radio_codec_helper_helper17_80038678(void)
{
    return dword_8009E28C;
}


int jimctrl_80038688(void)
{
    return GM_JimakuCounter;
}


PAKU *jimctrl_80038698(void)
{
    return &chara_work[1];
}
