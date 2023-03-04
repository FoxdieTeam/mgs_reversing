#include "Menu/menuman.h"
#include "Menu/radio.h"
#include "libfs/libfs.h"

extern menu_chara_struct *dword_800ABB38;
menu_chara_struct        *SECTION(".sbss") dword_800ABB38;

extern const char aNoMemoryForFac[]; // = "NO MEMORY FOR FACE %d\n";
extern const char aFaceDataNumD[];   // = "face data num %d\n";

#define load_big_endian_int(addr) ((int)((addr[0] << 24) | (addr[1] << 16) | (addr[2] << 8) | addr[3]))
#define load_big_endian_short_1(addr) ((short)((addr[0] << 8) | addr[1]))
#define load_big_endian_short_2(addr) (((addr)[1] | ((addr)[0] << 8)))

void menu_radio_codec_task_proc_80047AA0()
{
    int      field_18;
    unsigned sectorAndSize;
    char    *radioDatIter;
    unsigned startSector;

    void    *pFaceMemory;
    unsigned pFaceMemorySize;

    unsigned fontAddrOffset;

    mts_set_vsync_task_800892B8();
    radioDatIter = dword_800ABB38->field_8_radioDatFragment;
    radioDatIter += 2;

    sectorAndSize = load_big_endian_int(radioDatIter);
    radioDatIter += 4;

    field_18 = load_big_endian_short_1(radioDatIter);
    radioDatIter += 2;

    while (FS_StreamTaskState_80023E0C())
    {
        mts_wait_vbl_800895F4(2);
    }

    pFaceMemorySize = (sectorAndSize / 16777216) * 2048;
    sectorAndSize &= 0xFFFFFF; // % 16777216
    startSector = sectorAndSize;

    dword_800ABB38->field_20_pFaceMemory = GV_AllocMemory_80015EB8(0, pFaceMemorySize);
    if (dword_800ABB38->field_20_pFaceMemory == 0)
    {
        mts_printf_8008BBA0(aNoMemoryForFac, pFaceMemorySize);
    }

    // TODO: Reverse engineer pFaceMemory structure
    pFaceMemory = dword_800ABB38->field_20_pFaceMemory;
    FS_LoadFileRequest_80021F0C(2, startSector, pFaceMemorySize, pFaceMemory);
    while (FS_LoadFileSync_80021F48() > 0)
    {
        mts_wait_vbl_800895F4(1);
    }

    menu_radio_codec_task_proc_helper_80046F3C(dword_800ABB38, pFaceMemory);
    mts_printf_8008BBA0(aFaceDataNumD, dword_800ABB38->field_30_face_data_num);

    dword_800ABB38->field_14_bInExecBlock = 0;
    field_18 &= ~0x1;
    dword_800ABB38->field_18 = field_18;

    fontAddrOffset = load_big_endian_short_2(radioDatIter + 1) + 1;
    font_set_font_addr_80044BC0(1, radioDatIter + fontAddrOffset);

    dword_800ABB38->field_0_state = 0;
    menu_gcl_exec_block_800478B4(dword_800ABB38, radioDatIter);
    dword_800ABB38->field_0_state = 2;

    mts_8008B51C();
}
