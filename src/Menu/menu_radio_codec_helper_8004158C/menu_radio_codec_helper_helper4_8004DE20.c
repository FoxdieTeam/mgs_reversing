#include "Menu/radio.h"

extern RadioMemory gRadioMemory_800BDB38[];

extern RadioCodecStru_800ABB98 *stru_800ABB98;
RadioCodecStru_800ABB98        *stru_800ABB98;

extern int dword_800AB770;
int        dword_800AB770;

extern short word_800ABB9C;
short        word_800ABB9C;

void menu_radio_codec_helper_helper4_8004DE20(Actor_MenuMan *pActor)
{
    RadioCodecStru_800ABB98 *stru_800ABB98_copy;
    RadioMemory             *radioMemoryIter;
    int                      i;
    int                      count;

    init_radio_message_board_80040F74(pActor);
    stru_800ABB98 = (RadioCodecStru_800ABB98 *)GV_AllocMemory_80015EB8(0, sizeof(RadioCodecStru_800ABB98));
    stru_800ABB98_copy = stru_800ABB98;
    count = 0;
    i = 0;
    radioMemoryIter = gRadioMemory_800BDB38;

    for (; i < RADIO_MEMORY_COUNT; i++, radioMemoryIter++)
    {
        if (radioMemoryIter->frequency != 0)
        {
            stru_800ABB98_copy->field_10_array[count] = *radioMemoryIter;
            count++;
        }
    }

    stru_800ABB98_copy->field_4_count = count;
    stru_800ABB98_copy->field_0 = dword_800AB770;
    stru_800ABB98->field_2 = 0;
    stru_800ABB98_copy->field_6 = 2;
    stru_800ABB98_copy->field_8 = 14;
    word_800ABB9C = -1;
    stru_800ABB98->field_c_kcb = pActor->field_214_font;
    pActor->field_212 = 4;
    sub_8004D580(0);
    font_set_color_80044DC4(stru_800ABB98->field_c_kcb, 2, 0x1d05, 0);
}
