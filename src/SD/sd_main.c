#include "SD/sd_incl.h"
#include "SD/sd_ext.h"

#include "libfs/libfs.h"
#include "mts/mts_new.h"
#include "mts/taskid.h"
#include "psyq.h"

extern unsigned char *se_exp_table_800C0520;

void sound_main_80081910(int argc, const char *argv[])
{
    int i;

    sd_debug_800BEFD4 = 0;
    printf("SOUND_LAUNCH(argc:%d)\n", argc);

    for (i = 0; i < argc; ++i)
    {
        if (argv[i][0] == '-' && argv[i][1] == 'd')
        {
            sd_debug_800BEFD4 = 1;
        }
        printf("ARG%d:[%s]\n", i, argv[i]);
    }

    mts_set_stack_check_8008B648(MTSID_SOUND_MAIN, sd_main_stack_800BE7C8, 2048);
    mts_sta_tsk_8008B47C(MTSID_SOUND_MAIN, SdMain_80081A18, sd_main_stack_800BE7C8);
}

void nullsub_7_80081A10(int *arg0, int arg1, int arg2)
{
    /* do nothing */
}

void SdMain_80081A18(void)
{
    sd_task_status_800C0BFC = 0;
    printf("Start Task:SdMain\n");
    sd_mem_alloc_80082194();
    mts_set_stack_check_8008B648(MTSID_SOUND_INT, &sd_int_stack_800BEFC8, 2048);
    mts_sta_tsk_8008B47C(MTSID_SOUND_INT, SdInt_80081BDC, &sd_int_stack_800BEFC8); // TODO: Alloc BSS stack buffer
    mts_slp_tsk_8008A400();
    sd_task_status_800C0BFC = 128;
    while (1)
    {
        mts_slp_tsk_8008A400();
        if (sng_status_800BF158 == 1)
        {
            if (SD_800854F0())
            {
                sng_status_800BF158 = 0;
            }
            else
            {
                sng_status_800BF158 = 2;
            }
        }

        if (str_fout_fg_800BF26C == 1)
        {
            str_fout_fg_800BF26C = 2;
        }

        if (dword_800BEFCC)
        {
            KeyOffStr_80081FE8();
            dword_800BEFCC = 0;
        }

        switch (str_status_800BF16C)
        {
        case 1:
            if (StartStream_80082448())
            {
                str_status_800BF16C = 0;
            }
            else
            {
                str_status_800BF16C = 2;
                dword_800BF1A4 = 0;
            }
            break;

        case 2: /* fallthrough */
        case 3: /* fallthrough */
        case 4: /* fallthrough */
        case 5:
            SD_nullsub_20_800827A4();
            break;

        case 7:
            KeyOffStr_80081FE8();
            printf("***BGM Terminate***\n");
            break;

        case 6: /* fallthrough */
        default:
            break;
        }

        if (se_load_code_800BF28C)
        {
            SD_LoadSeFile_8008341C();
        }
    }
}

void SdInt_80081BDC(void)
{
    char buf[98];
    (void)buf; // not enough stack used without this

    printf("Start Task:SdInt\n");
    sd_init_80081C7C();
    mts_wup_tsk_8008A540(MTSID_SOUND_MAIN);
    while (1)
    {
        mts_receive_80089D24(-1, 0);
        IntSdMain_80084494();
        if (SpuIsTransferCompleted(0) == 1)
        {
            WaveSpuTrans_80083944();
            mts_wup_tsk_8008A540(MTSID_SOUND_MAIN);
        }
        StrFadeInt_800839C8();
        if (SpuIsTransferCompleted(0) == 1)
        {
            StrSpuTrans_800833FC();
            mts_wup_tsk_8008A540(MTSID_SOUND_MAIN);
        }
    }
}

void sd_init_80081C7C(void)
{
    int           spuMem;
    int           i;
    SpuCommonAttr c_attr;
    SpuReverbAttr r_attr;

    SpuInit();
    SpuInitMalloc(24, spu_malloc_rec_800C0588);
    c_attr.mask = 3;
    c_attr.mvol.left = 0;
    c_attr.mvol.right = 0;
    SpuSetCommonAttr(&c_attr);
    SpuSetPitchLFOVoice(0, 0x00FFFFFF);
    SpuSetNoiseVoice(0, 0x00FFFFFF);
    SpuSetReverb(0);
    SpuSetTransferMode(0);
    blank_data_addr_800BF00C = SpuMalloc(512);
    printf("blank_data_addr=%x\n", blank_data_addr_800BF00C);
    spu_wave_start_ptr_800C052C = SpuMalloc(0x73E00);
    printf("spu_wave_start_ptr=%x\n", spu_wave_start_ptr_800C052C);
    spu_bgm_start_ptr_r_800BF0C8 = SpuMalloc(0x2000);
    printf("spu_bgm_start_ptr_r=%x\n", spu_bgm_start_ptr_r_800BF0C8);
    spuMem = SpuMalloc(0x2000);
    spu_bgm_start_ptr_l_800BF060 = spuMem;
    if (spuMem == -1)
    {
        printf("SPU Buffer Over!!\n");
    }
    else
    {
        printf("spu_bgm_start_ptr_l=%x\n", spuMem);
    }
    SpuSetReverb(0);
    SpuReserveReverbWorkArea(1);
    SpuClearReverbWorkArea(4);
    r_attr.mask = 1;
    r_attr.mode = 4;
    if (SpuSetReverbModeParam(&r_attr))
    {
        printf("SPU Reverb Buffer Over!!\n");
    }
    r_attr.mask = 6;
    r_attr.depth.left = 0x4000;
    r_attr.depth.right = 0x4000;
    SpuSetReverbDepth(&r_attr);
    SpuSetReverb(1);
    dword_800BF210 = 0;
    dword_800BF064 = 0x1FFF;
    SpuSetReverbVoice(1, 0x1FFF);
    init_sng_work_8008559C();
    dword_800BF27C = 0;
    str_status_800BF16C = 0;
    for (i = 0; i < 8; i++)
    {
        se_playing_800BF068[i].code = 0;
    }
    SpuSetTransferStartAddr(blank_data_addr_800BF00C);
    SpuWrite(blank_data_800A2B28, 512);
    SpuIsTransferCompleted(1);
    SpuSetIRQ(0);
    SpuSetIRQAddr(blank_data_addr_800BF00C);
    dword_800BF1A8 = 0;
    SpuSetIRQCallback(UserSpuIRQProc_80082640);
    SpuSetIRQ(1);
    s_attr_800BF218.mask = 0xFF93;
    s_attr_800BF218.voice = 0x800000;
    s_attr_800BF218.pitch = 4096;
    s_attr_800BF218.a_mode = 1;
    s_attr_800BF218.s_mode = 1;
    s_attr_800BF218.volume.left = 0;
    s_attr_800BF218.volume.right = 0;
    s_attr_800BF218.r_mode = 3;
    s_attr_800BF218.ar = 0;
    s_attr_800BF218.dr = 0;
    s_attr_800BF218.sr = 0;
    s_attr_800BF218.rr = 0;
    s_attr_800BF218.sl = 15;
    s_attr_800BF218.addr = blank_data_addr_800BF00C;
    SpuSetVoiceAttr(&s_attr_800BF218);
    keyOn_80082170(0x800000);
    c_attr.mask = 3;
    c_attr.mvol.left = 0x3FFF;
    c_attr.mvol.right = 0x3FFF;
    SpuSetCommonAttr(&c_attr);
}

void SdTerm_80081F8C(void)
{
    SpuSetIRQCallback(NULL);
    SpuSetKey(0, 0x00ffffff);
    SpuQuit();
}

void keyOff_80081FC4(unsigned int ch)
{
    SpuSetKey(0, ch);
}

void KeyOffStr_80081FE8(void)
{
    SpuVoiceAttr attr;

    switch (SpuGetKeyStatus(0x600000))
    {
    case SPU_OFF:
        break;

    case SPU_ON:
    case SPU_ON_ENV_OFF:
        SpuSetKey(0, 0x600000);
        break;

    case SPU_OFF_ENV_ON:
        attr.voice = 0x200000;
        SpuGetVoiceAttr(&attr);
        if (attr.rr != 8)
        {
            printf("SOUND ERROR:SPU OFF ENV ON(STR_TRACK_R=%x)\n", attr.rr);
        }
        attr.voice = 0x400000;
        SpuGetVoiceAttr(&attr);
        if (attr.rr != 8)
        {
            printf("SOUND ERROR:SPU OFF ENV ON(STR_TRACK_L=%x)\n", attr.rr);
        }
    }

    dword_800C0580 = 0;
    str_load_code_800C04F0 = 0;

    if (str_fp_800BF258)
    {
        SD_8008395C(str_fp_800BF258, 1);
        str_fp_800BF258 = 0;
    }
    str_status_800BF16C = 0;
    StrSpuTransClose_80083394();
}

void sub_800820EC(void)
{
    switch (SpuGetKeyStatus(0x600000))
    {
    case SPU_OFF:
        break;

    case SPU_ON:
    case SPU_ON_ENV_OFF:
        SpuSetKey(0, 0x600000);
        break;

    case SPU_OFF_ENV_ON:
        break;
    }

    dword_800C0580 = 0;
    if (str_fp_800BF258)
    {
        SD_8008395C(str_fp_800BF258, 1);
        str_fp_800BF258 = 0;
    }
    str_status_800BF16C = 0;
}

void keyOn_80082170(unsigned int ch)
{
    SpuSetKey(1, ch);
}

int sd_mem_alloc_80082194(void)
{
    sng_data_800C0420 = (unsigned char *)0x801E0000;
    printf("sng_data %X\n", (unsigned int)sng_data_800C0420);

    wave_header_800BF1E0 = (WAVE_W *)(sng_data_800C0420 + 0x4000);
    printf("wave_header %X\n", (unsigned int)sng_data_800C0420 + 0x4000);

    voice_tbl_800C0530 = wave_header_800BF1E0;
    printf("voice_tbl %X\n", (unsigned int)wave_header_800BF1E0);

    se_exp_table_800C0520 = (unsigned char *)&wave_header_800BF1E0[256];
    printf("se_header %X\n", (unsigned int)se_exp_table_800C0520);

    se_header_800BF284 = se_exp_table_800C0520 + 0x800;
    printf("se_data %X\n", (unsigned int)se_header_800BF284);

    cdload_buf_800BF010 = se_header_800BF284 + 0x2000;
    printf("CDLOAD_BUF %X %X %X\n", (unsigned int)cdload_buf_800BF010, 0x18000, (unsigned int)cdload_buf_800BF010 + 0x18000);

    str_header_800BF058 = cdload_buf_800BF010 + 0x18000;
    printf("str_header %X\n", (unsigned int)str_header_800BF058);

    str_trans_buf_800C0514 = cdload_buf_800BF010;
    return 0;
}
