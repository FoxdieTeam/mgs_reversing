#include "sd_incl.h"
#include "sd_ext.h"

#include <stdio.h>
#include <libspu.h>
#include "common.h"
#include "mts/mts.h"
#include "mts/taskid.h"
#include "libfs/libfs.h"

extern unsigned char *se_header;

/* todo: should be declared static */
extern char sd_main_stack[SD_MAIN_STACK_SIZE];
extern char sd_int_stack[SD_INT_STACK_SIZE];

void sound_main(int argc, const char *argv[])
{
    int i;

    sd_debug_mode = 0;
    printf("SOUND_LAUNCH(argc:%d)\n", argc);

    for (i = 0; i < argc; ++i)
    {
        if (argv[i][0] == '-' && argv[i][1] == 'd')
        {
            sd_debug_mode = 1;
        }
        printf("ARG%d:[%s]\n", i, argv[i]);
    }

    mts_start_task(MTSID_SOUND_MAIN, SdMain, STACK_BOTTOM(sd_main_stack), SD_MAIN_STACK_SIZE);
}

void sub_80081A10(int *arg0, int arg1, int arg2)
{
    /* do nothing */
}

void SdMain(void)
{
    sd_task_status = 0;
    printf("Start Task:SdMain\n");
    sd_mem_alloc();

    mts_start_task(MTSID_SOUND_INT, SdInt, STACK_BOTTOM(sd_int_stack), SD_INT_STACK_SIZE);
    mts_slp_tsk();

    sd_task_status = 128;
    while (1)
    {
        mts_slp_tsk();
        if (sng_status == 1)
        {
            if (LoadSngData())
            {
                sng_status = 0;
            }
            else
            {
                sng_status = 2;
            }
        }

        if (str_fout_fg == 1)
        {
            str_fout_fg = 2;
        }

        if (dword_800BEFCC)
        {
            KeyOffStr();
            dword_800BEFCC = 0;
        }

        switch (str_status)
        {
        case 1:
            if (StartStream())
            {
                str_status = 0;
            }
            else
            {
                str_status = 2;
                dword_800BF1A4 = 0;
            }
            break;

        case 2: /* fallthrough */
        case 3: /* fallthrough */
        case 4: /* fallthrough */
        case 5:
            sub_800827A4();
            break;

        case 7:
            KeyOffStr();
            printf("***BGM Terminate***\n");
            break;

        case 6: /* fallthrough */
        default:
            break;
        }

        if (se_load_code)
        {
            LoadSeFile();
        }
    }
}

void SdInt(void)
{
    char buf[98];
    (void)buf; // not enough stack used without this

    printf("Start Task:SdInt\n");
    sd_init();
    mts_wup_tsk(MTSID_SOUND_MAIN);
    while (1)
    {
        mts_receive(MTS_TASK_INTR, NULL);
        IntSdMain();
        if (SpuIsTransferCompleted(SPU_TRANSFER_PEEK) == 1)
        {
            WaveSpuTrans();
            mts_wup_tsk(MTSID_SOUND_MAIN);
        }
        StrFadeInt();
        if (SpuIsTransferCompleted(SPU_TRANSFER_PEEK) == 1)
        {
            StrSpuTrans();
            mts_wup_tsk(MTSID_SOUND_MAIN);
        }
    }
}

void sd_init(void)
{
    int           spuMem;
    int           i;
    SpuCommonAttr c_attr;
    SpuReverbAttr r_attr;

    SpuInit();
    SpuInitMalloc(24, spu_malloc_rec);
    c_attr.mask = SPU_COMMON_MVOLL | SPU_COMMON_MVOLR;
    c_attr.mvol.left = 0;
    c_attr.mvol.right = 0;
    SpuSetCommonAttr(&c_attr);
    SpuSetPitchLFOVoice(SPU_OFF, SPU_ALLCH);
    SpuSetNoiseVoice(SPU_OFF, SPU_ALLCH);
    SpuSetReverb(SPU_OFF);
    SpuSetTransferMode(SPU_TRANSFER_BY_DMA);
    blank_data_addr = SpuMalloc(512);
    printf("blank_data_addr=%x\n", blank_data_addr);
    spu_wave_start_ptr = SpuMalloc(0x73E00);
    printf("spu_wave_start_ptr=%x\n", spu_wave_start_ptr);
    spu_bgm_start_ptr_r = SpuMalloc(0x2000);
    printf("spu_bgm_start_ptr_r=%x\n", spu_bgm_start_ptr_r);
    spuMem = SpuMalloc(0x2000);
    spu_bgm_start_ptr_l = spuMem;
    if (spuMem == -1)
    {
        printf("SPU Buffer Over!!\n");
    }
    else
    {
        printf("spu_bgm_start_ptr_l=%x\n", spuMem);
    }
    SpuSetReverb(SPU_OFF);
    SpuReserveReverbWorkArea(SPU_ON);
    SpuClearReverbWorkArea(SPU_REV_MODE_STUDIO_C);
    r_attr.mask = SPU_REV_MODE;
    r_attr.mode = SPU_REV_MODE_STUDIO_C;
    if (SpuSetReverbModeParam(&r_attr))
    {
        printf("SPU Reverb Buffer Over!!\n");
    }
    r_attr.mask = SPU_REV_DEPTHL | SPU_REV_DEPTHR;
    r_attr.depth.left = 0x4000;
    r_attr.depth.right = 0x4000;
    SpuSetReverbDepth(&r_attr);
    SpuSetReverb(SPU_ON);
    eoffs = 0;
    eons = 0x1FFF;
    SpuSetReverbVoice(SPU_ON, SPU_13CH - 1); // channels 0-12
    init_sng_work();
    dword_800BF27C = 0;
    str_status = 0;
    for (i = 0; i < 8; i++)
    {
        se_playing[i].code = 0;
    }
    SpuSetTransferStartAddr(blank_data_addr);
    SpuWrite(blank_data, 512);
    SpuIsTransferCompleted(SPU_TRANSFER_WAIT);
    SpuSetIRQ(SPU_OFF);
    SpuSetIRQAddr(blank_data_addr);
    dword_800BF1A8 = 0;
    SpuSetIRQCallback(UserSpuIRQProc);
    SpuSetIRQ(SPU_ON);
    sd_blank_attr.mask = SPU_VOICE_VOLL | SPU_VOICE_VOLR | SPU_VOICE_PITCH | SPU_VOICE_WDSA |
                           SPU_VOICE_ADSR_AMODE | SPU_VOICE_ADSR_SMODE | SPU_VOICE_ADSR_RMODE | SPU_VOICE_ADSR_AR |
                           SPU_VOICE_ADSR_DR | SPU_VOICE_ADSR_SR | SPU_VOICE_ADSR_RR | SPU_VOICE_ADSR_SL;
    sd_blank_attr.voice = SPU_23CH;
    sd_blank_attr.pitch = 4096;
    sd_blank_attr.a_mode = SPU_VOICE_LINEARIncN;
    sd_blank_attr.s_mode = SPU_VOICE_LINEARIncN;
    sd_blank_attr.volume.left = 0;
    sd_blank_attr.volume.right = 0;
    sd_blank_attr.r_mode = SPU_VOICE_LINEARDecN;
    sd_blank_attr.ar = 0;
    sd_blank_attr.dr = 0;
    sd_blank_attr.sr = 0;
    sd_blank_attr.rr = 0;
    sd_blank_attr.sl = 15;
    sd_blank_attr.addr = blank_data_addr;
    SpuSetVoiceAttr(&sd_blank_attr);
    keyOn(SPU_23CH);
    c_attr.mask = SPU_COMMON_MVOLL | SPU_COMMON_MVOLR;
    c_attr.mvol.left = 0x3FFF;
    c_attr.mvol.right = 0x3FFF;
    SpuSetCommonAttr(&c_attr);
}

void SdTerm(void)
{
    SpuSetIRQCallback(NULL);
    SpuSetKey(SPU_OFF, SPU_ALLCH);
    SpuQuit();
}

void keyOff(unsigned int ch)
{
    SpuSetKey(SPU_OFF, ch);
}

void KeyOffStr(void)
{
    SpuVoiceAttr attr;

    switch (SpuGetKeyStatus(SPU_21CH | SPU_22CH))
    {
    case SPU_OFF:
        break;

    case SPU_ON:
    case SPU_ON_ENV_OFF:
        SpuSetKey(SPU_OFF, SPU_21CH | SPU_22CH);
        break;

    case SPU_OFF_ENV_ON:
        attr.voice = SPU_21CH;
        SpuGetVoiceAttr(&attr);
        if (attr.rr != 8)
        {
            printf("SOUND ERROR:SPU OFF ENV ON(STR_TRACK_R=%x)\n", attr.rr);
        }
        attr.voice = SPU_22CH;
        SpuGetVoiceAttr(&attr);
        if (attr.rr != 8)
        {
            printf("SOUND ERROR:SPU OFF ENV ON(STR_TRACK_L=%x)\n", attr.rr);
        }
    }

    dword_800C0580 = 0;
    str_load_code = 0;

    if (str_fp)
    {
        PcmClose(str_fp, 1);
        str_fp = 0;
    }
    str_status = 0;
    StrSpuTransClose();
}

void KeyOffStr2(void)
{
    switch (SpuGetKeyStatus(SPU_21CH | SPU_22CH))
    {
    case SPU_OFF:
        break;

    case SPU_ON:
    case SPU_ON_ENV_OFF:
        SpuSetKey(SPU_OFF, SPU_21CH | SPU_22CH);
        break;

    case SPU_OFF_ENV_ON:
        break;
    }

    dword_800C0580 = 0;
    if (str_fp)
    {
        PcmClose(str_fp, 1);
        str_fp = 0;
    }
    str_status = 0;
}

void keyOn(unsigned int ch)
{
    SpuSetKey(SPU_ON, ch);
}

int sd_mem_alloc(void)
{
    sng_data = (unsigned char *)0x801E0000;
    printf("sng_data %X\n", (unsigned int)sng_data);

    wave_header = (WAVE_W *)(sng_data + 0x4000);
    printf("wave_header %X\n", (unsigned int)sng_data + 0x4000);

    voice_tbl = wave_header;
    printf("voice_tbl %X\n", (unsigned int)wave_header);

    se_header = (unsigned char *)&wave_header[256];
    printf("se_header %X\n", (unsigned int)se_header);

    se_data = se_header + 0x800;
    printf("se_data %X\n", (unsigned int)se_data);

    cdload_buf = se_data + 0x2000;
    printf("CDLOAD_BUF %X %X %X\n", (unsigned int)cdload_buf, CDLOAD_BUF_SIZE, (unsigned int)cdload_buf + CDLOAD_BUF_SIZE);

    str_header = cdload_buf + CDLOAD_BUF_SIZE;
    printf("str_header %X\n", (unsigned int)str_header);

    str_trans_buf = cdload_buf;
    return 0;
}
