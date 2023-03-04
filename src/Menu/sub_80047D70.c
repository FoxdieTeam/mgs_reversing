#include "Menu/menuman.h"
#include "Game/linkvarbuf.h"
#include "libfs/libfs.h"

extern const char aNoMemory[]; // = "no memory\n";

void sub_80047D70(Actor_MenuMan *pActor, int param_2, int pRadioCode)
{
    menu_chara_struct_sub *pCharaStructSub;
    menu_chara_struct     *pCharaStruct;

    int   startSector, size;
    void *radioDatFragment;

    int i, i2;

    short  *pImgData256Iter;
    int     rgb;
    int     tmpRgb1, tmpRgb2;

    char pad[8]; // unused stack...

    startSector = pRadioCode & 0xffff;
    if (GM_GameStatusFlag & 0x100)
    {
        size = ((pRadioCode >> 0x10) & 0xff) * 2048;
        startSector = startSector + ((unsigned int)pRadioCode / 16777216);
    }
    else
    {
        size = ((unsigned int)pRadioCode / 16777216) * 2048;
    }

    // At the start of the game if you manually call
    // after the initial call, radioDatFragment is 0x800 bytes
    // large and it is read from RADIO.DAT offset 0x1f1000.
    radioDatFragment = GV_AllocMemory_80015EB8(0, size);
    if (radioDatFragment == NULL)
    {
        mts_printf_8008BBA0(aNoMemory);
    }

    pCharaStruct = pActor->field_218;

    sub_80048124();
    sub_800469F0(pCharaStruct);
    pCharaStruct->field_1C_radioDatFragment = radioDatFragment;
    pCharaStruct->field_8_radioDatFragment = radioDatFragment;
    pCharaStruct->field_C_pScript = NULL;
    pCharaStruct->field_4 = param_2;
    pCharaStruct->field_0_state = 0;
    pCharaStruct->field_38 = 0;

    for (i = 0; i < 2; i++)
    {
        pCharaStructSub = &pCharaStruct->field_3C[i];
        pCharaStructSub->field_0_state = 0;
        pCharaStructSub->field_4 = 0;
    }

    // radioDatFragment is parsed in menu_radio_codec_task_proc_80047AA0()
    FS_LoadFileRequest_80021F0C(1, startSector, size, radioDatFragment);

    pCharaStruct->field_24_pImgData256 = GV_AllocMemory_80015EB8(0, 0x200);
    if (pCharaStruct->field_24_pImgData256 == NULL)
    {
        mts_printf_8008BBA0(aNoMemory);
    }

    pImgData256Iter = (short *)pCharaStruct->field_24_pImgData256;
    for (i2 = 0; i2 < 0x100; i2++)
    {
        tmpRgb1 = (i2 % 6) * 4 + 2;
        tmpRgb2 = tmpRgb1 * 0x30;
        while (0);
        rgb = tmpRgb1 << 0xA;
        tmpRgb2 &= 0x3E0;
        tmpRgb2 |= ~0x7FFF;
        rgb |= tmpRgb2;
        rgb |= tmpRgb1;
        pImgData256Iter[i2] = rgb;
    }
}
