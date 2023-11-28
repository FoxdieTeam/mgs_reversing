#include "sd_data.c"
#include "SD/sd.h"
#include "libfs/libfs.h"
#include "mts/mts_new.h"
#include "psyq.h"
#include "unknown.h"

void                  sd_init_80081C7C();
void                  IntSdMain_80084494();
void                  WaveSpuTrans_80083944( void );
void                  StrSpuTrans_800833FC( void );
int                   StrFadeInt_800839C8();
void                  SdInt_Task_80081BDC();
void                  SD_nullsub_20_800827A4();
int                   SD_LoadSeFile_8008341C();
int                   SD_800854F0();
void                  KeyOffStr_80081FE8();
int                   StartStream_80082448();
void                  SD_80082170( int param_1 );
void                  sng_off_80087E2C();
void                  UserSpuIRQProc_80082640();
int                   sd_sng_alloc_80082194( void );
void                  StrSpuTransClose_80083394();


extern int            sng_status_800BF158;
extern int            se_load_code_800BF28C;
extern int            bstr_fade_inProgress_800BF0CC;
extern unsigned int   gStreamVol_800BF15C;
extern int            dword_800C04F4;
extern unsigned int   sng_status_800C04F8;
extern unsigned char *sd_sng_data_800C0420;
extern int            se_fp_800BF014;
extern int            dword_800C0500;
extern unsigned int   gStr_fadeout_2_800C0584;
extern char          *stream_data_ptr_800BEFE4;
extern int            dword_800BEFF0;
extern char          *dword_8009F7B8;
extern int            dword_8009F7B4;
extern int            dword_800C04EC;
extern int            wave_unload_size_800BF274;
extern int            spu_load_offset_800BF140;
extern char          *cdload_buf_800BF010;
extern char          *wave_load_ptr_800C0508;
extern int            sd_flags_800C0BFC;
extern int            dword_800BEFC8;
extern int            dword_800BEFCC;
extern int            dword_800BF1A4;
extern int            dword_800BF26C;
extern char          *cdload_buf_800BF010;
extern unsigned int   gStr_FadeOut1_800BF16C;
extern int            sd_debug_800BEFD4;
extern unsigned int   byte_800BE7C8[ 512 ];
extern int            gStream_800C04F0;
extern int            dword_800BF258;
extern int            dword_800C0580;
extern unsigned char *se_exp_table_800C0520;
extern int            dword_800C0650;
extern int            dword_800BF268;
extern int            wave_data_800BF294;
extern int            wave_load_code_800C0528;
extern int            dword_800BF168;
extern int            str_unplay_size_800BF1AC;
extern int            dword_800C0504;
extern int            dword_800C051C;
extern int            dword_800C0418;
extern int            dword_800BF1DC;
extern int            dword_800BEFF4;
extern int            dword_800BF270;
extern unsigned char  byte_800C056C;
extern int            wave_save_code_800C0578;
extern int            dword_800C050C;
extern int            se_rev_on_800C0574;
extern int            dword_800BF160;
extern int            dword_800BF144;
extern int            dword_800C040C;
extern int            dword_800BF164;
extern int            spu_bgm_start_ptr_l_800BF060;
extern int            spu_bgm_start_ptr_r_800BF0C8;
extern int            dword_800C0414;
extern int            dword_800BEFEC;
extern int            dword_800BF264;
extern int            dword_800BEFE8;
//extern unsigned char  byte_800A2D28[ 4096 ];
extern SEPLAYTBL      se_playing_800BF068[ 8 ];
extern int            dword_800BF210;
extern int            dword_800BF064;
extern int            dword_800BF1A8;
//extern unsigned char         blank_data_800A2B28[ 512 ];
extern unsigned int   dword_800BF27C;
extern unsigned char  byte_800C0588[ 200 ];
extern int            blank_data_addr_800BF00C;
extern int            spu_wave_start_ptr_800C052C;
extern SpuVoiceAttr   voiceAttr_800BF218;
extern WAVE_W        *voice_tbl_800BF1E0;
extern char          *se_header_800BF284;
extern char          *CDLOAD_BUF_800BF058;
extern char          *str_header_800C0514;
extern WAVE_W        *voice_tbl_800C0530;

void                  sub_80081910( int argc, const char **argv )
{
    int i;

    sd_debug_800BEFD4 = 0;
    printf( "SOUND_LAUNCH(argc:%d)\n", argc );

    for ( i = 0; i < argc; ++i )
    {
        if ( argv[ i ][ 0 ] == '-' && argv[ i ][ 1 ] == 'd' )
        {
            sd_debug_800BEFD4 = 1;
        }
        printf( "ARG%d:[%s]\n", i, argv[ i ] );
    }

    mts_set_stack_check_8008B648( 5, byte_800BE7C8, 0x800 );
    mts_sta_tsk_8008B47C( 5, SdMain_80081A18, byte_800BE7C8 );
}

void nullsub_7_80081A10( int *a1, int a2, int a3 )
{
}

void SdMain_80081A18()
{
    sd_flags_800C0BFC = 0;
    printf( "Start Task:SdMain\n" );
    sd_sng_alloc_80082194();
    mts_set_stack_check_8008B648( 1, &dword_800BEFC8, 2048 );
    mts_sta_tsk_8008B47C( 1, SdInt_Task_80081BDC, &dword_800BEFC8 ); // TODO: Alloc BSS stack buffer
    mts_slp_tsk_8008A400();
    sd_flags_800C0BFC = 128;
    while ( 1 )
    {
        mts_slp_tsk_8008A400();
        if ( sng_status_800BF158 == 1 )
        {
            if ( SD_800854F0() )
            {
                sng_status_800BF158 = 0;
            }
            else
            {
                sng_status_800BF158 = 2;
            }
        }

        if ( dword_800BF26C == 1 )
        {
            dword_800BF26C = 2;
        }

        if ( dword_800BEFCC )
        {
            KeyOffStr_80081FE8();
            dword_800BEFCC = 0;
        }

        switch ( gStr_FadeOut1_800BF16C )
        {
        case 1:
            if ( StartStream_80082448() )
            {
                gStr_FadeOut1_800BF16C = 0;
            }
            else
            {
                gStr_FadeOut1_800BF16C = 2;
                dword_800BF1A4 = 0;
            }
            break;

        case 2:
        case 3:
        case 4:
        case 5:
            SD_nullsub_20_800827A4();
            break;

        case 7:
            KeyOffStr_80081FE8();
            printf( "***BGM Terminate***\n" );
            break;

        case 6:
        default:
            break;
        }

        if ( se_load_code_800BF28C )
        {
            SD_LoadSeFile_8008341C();
        }
    }
}

void SdInt_Task_80081BDC()
{
    char buf[ 98 ];
    (void)buf; // not enough stack used without this

    printf( "Start Task:SdInt\n" );
    sd_init_80081C7C();
    mts_wup_tsk_8008A540( 5 );
    while ( 1 )
    {
        mts_receive_80089D24( -1, 0 );
        IntSdMain_80084494();
        if ( SpuIsTransferCompleted( 0 ) == 1 )
        {
            WaveSpuTrans_80083944();
            mts_wup_tsk_8008A540( 5 );
        }
        StrFadeInt_800839C8();
        if ( SpuIsTransferCompleted( 0 ) == 1 )
        {
            StrSpuTrans_800833FC();
            mts_wup_tsk_8008A540( 5 );
        }
    }
}

void sd_init_80081C7C()
{
    int           spuMem;
    int           i;
    SpuCommonAttr attr;
    SpuReverbAttr reverbAttr;

    SpuInit();
    SpuInitMalloc( 24, byte_800C0588 );
    attr.mask = 3;
    attr.mvol.left = 0;
    attr.mvol.right = 0;
    SpuSetCommonAttr( &attr );
    SpuSetPitchLFOVoice( 0, 0xFFFFFF );
    SpuSetNoiseVoice( 0, 0xFFFFFF );
    SpuSetReverb( 0 );
    SpuSetTransferMode( 0 );
    blank_data_addr_800BF00C = SpuMalloc( 512 );
    printf( "blank_data_addr=%x\n", blank_data_addr_800BF00C );
    spu_wave_start_ptr_800C052C = SpuMalloc( 0x73E00 );
    printf( "spu_wave_start_ptr=%x\n", spu_wave_start_ptr_800C052C );
    spu_bgm_start_ptr_r_800BF0C8 = SpuMalloc( 0x2000 );
    printf( "spu_bgm_start_ptr_r=%x\n", spu_bgm_start_ptr_r_800BF0C8 );
    spuMem = SpuMalloc( 0x2000 );
    spu_bgm_start_ptr_l_800BF060 = spuMem;
    if ( spuMem == -1 )
    {
        printf( "SPU Buffer Over!!\n" );
    }
    else
    {
        printf( "spu_bgm_start_ptr_l=%x\n", spuMem );
    }
    SpuSetReverb( 0 );
    SpuReserveReverbWorkArea( 1 );
    SpuClearReverbWorkArea( 4 );
    reverbAttr.mask = 1;
    reverbAttr.mode = 4;
    if ( SpuSetReverbModeParam( &reverbAttr ) )
    {
        printf( "SPU Reverb Buffer Over!!\n" );
    }
    reverbAttr.mask = 6;
    reverbAttr.depth.left = 0x4000;
    reverbAttr.depth.right = 0x4000;
    SpuSetReverbDepth( &reverbAttr );
    SpuSetReverb( 1 );
    dword_800BF210 = 0;
    dword_800BF064 = 0x1FFF;
    SpuSetReverbVoice( 1, 0x1FFF );
    init_sng_work_8008559C();
    dword_800BF27C = 0;
    gStr_FadeOut1_800BF16C = 0;
    for ( i = 0; i < 8; i++ )
    {
        se_playing_800BF068[ i ].field_8_code = 0;
    }
    SpuSetTransferStartAddr( blank_data_addr_800BF00C );
    SpuWrite( blank_data_800A2B28, 512 );
    SpuIsTransferCompleted( 1 );
    SpuSetIRQ( 0 );
    SpuSetIRQAddr( blank_data_addr_800BF00C );
    dword_800BF1A8 = 0;
    SpuSetIRQCallback( UserSpuIRQProc_80082640 );
    SpuSetIRQ( 1 );
    voiceAttr_800BF218.mask = 0xFF93;
    voiceAttr_800BF218.voice = 0x800000;
    voiceAttr_800BF218.pitch = 4096;
    voiceAttr_800BF218.a_mode = 1;
    voiceAttr_800BF218.s_mode = 1;
    voiceAttr_800BF218.volume.left = 0;
    voiceAttr_800BF218.volume.right = 0;
    voiceAttr_800BF218.r_mode = 3;
    voiceAttr_800BF218.ar = 0;
    voiceAttr_800BF218.dr = 0;
    voiceAttr_800BF218.sr = 0;
    voiceAttr_800BF218.rr = 0;
    voiceAttr_800BF218.sl = 15;
    voiceAttr_800BF218.addr = blank_data_addr_800BF00C;
    SpuSetVoiceAttr( &voiceAttr_800BF218 );
    SD_80082170( 0x800000 );
    attr.mask = 3;
    attr.mvol.left = 0x3FFF;
    attr.mvol.right = 0x3FFF;
    SpuSetCommonAttr( &attr );
}

void sub_80081F8C( void )
{
    SpuSetIRQCallback( NULL );
    SpuSetKey( 0, 0xffffff );
    SpuQuit();
}

void SD_80081FC4( int param_1 )
{
    SpuSetKey( 0, param_1 );
}

void KeyOffStr_80081FE8()
{
    SpuVoiceAttr attr; // [sp+10h] [-40h] BYREF

    switch ( SpuGetKeyStatus( 0x600000 ) )
    {
    case SPU_OFF:
        break;

    case SPU_ON:
    case SPU_ON_ENV_OFF:
        SpuSetKey( 0, 0x600000 );
        break;

    case SPU_OFF_ENV_ON:
        attr.voice = 0x200000;
        SpuGetVoiceAttr( &attr );
        if ( attr.rr != 8 )
        {
            printf( "SOUND ERROR:SPU OFF ENV ON(STR_TRACK_R=%x)\n", attr.rr );
        }
        attr.voice = 0x400000;
        SpuGetVoiceAttr( &attr );
        if ( attr.rr != 8 )
        {
            printf( "SOUND ERROR:SPU OFF ENV ON(STR_TRACK_L=%x)\n", attr.rr );
        }
    }

    dword_800C0580 = 0;
    gStream_800C04F0 = 0;

    if ( dword_800BF258 )
    {
        SD_8008395C( dword_800BF258, 1 );
        dword_800BF258 = 0;
    }
    gStr_FadeOut1_800BF16C = 0;
    StrSpuTransClose_80083394();
}

void sub_800820EC()
{
    switch ( SpuGetKeyStatus( 0x600000 ) )
    {
    case SPU_OFF:
        break;

    case SPU_ON:
    case SPU_ON_ENV_OFF:
        SpuSetKey( 0, 0x600000 );
        break;

    case SPU_OFF_ENV_ON:
        break;
    }

    dword_800C0580 = 0;
    if ( dword_800BF258 )
    {
        SD_8008395C( dword_800BF258, 1 );
        dword_800BF258 = 0;
    }
    gStr_FadeOut1_800BF16C = 0;
}

void SD_80082170( int param_1 )
{
    SpuSetKey( 1, param_1 );
}

int sd_sng_alloc_80082194( void )
{
    sd_sng_data_800C0420 = (unsigned char *)0x801E0000;
    printf( "sng_data %X\n", (unsigned int)sd_sng_data_800C0420 );

    voice_tbl_800BF1E0 = (WAVE_W *)( sd_sng_data_800C0420 + 0x4000 );
    printf( "wave_header %X\n", (unsigned int)sd_sng_data_800C0420 + 0x4000 );

    voice_tbl_800C0530 = voice_tbl_800BF1E0;
    printf( "voice_tbl %X\n", (unsigned int)voice_tbl_800BF1E0 );

    se_exp_table_800C0520 = (unsigned char *)&voice_tbl_800BF1E0[ 256 ];
    printf( "se_header %X\n", (unsigned int)se_exp_table_800C0520 );

    se_header_800BF284 = se_exp_table_800C0520 + 0x800;
    printf( "se_data %X\n", (unsigned int)se_header_800BF284 );

    cdload_buf_800BF010 = se_header_800BF284 + 0x2000;
    printf( "CDLOAD_BUF %X %X %X\n", (unsigned int)cdload_buf_800BF010, 0x18000, (unsigned int)cdload_buf_800BF010 + 0x18000 );

    CDLOAD_BUF_800BF058 = cdload_buf_800BF010 + 0x18000;
    printf( "str_header %X\n", (unsigned int)CDLOAD_BUF_800BF058 );

    str_header_800C0514 = cdload_buf_800BF010;
    return 0;
}

void StrFadeIn_800822C8( unsigned int a1 )
{
    bstr_fade_inProgress_800BF0CC = gStreamVol_800BF15C / a1;
    if ( !( gStreamVol_800BF15C / a1 ) )
    {
        bstr_fade_inProgress_800BF0CC = 1;
    }
    dword_800C04F4 = 0;
}

int StrFadeOut_80082310( unsigned int a1 )
{
    if ( gStr_FadeOut1_800BF16C )
    {
        if ( gStr_fadeout_2_800C0584 != gStreamVol_800BF15C )
        {
            dword_800C04F4 = gStreamVol_800BF15C / a1;
            if ( !( gStreamVol_800BF15C / a1 ) )
            {
                dword_800C04F4 = 1;
            }
            bstr_fade_inProgress_800BF0CC = 0;
            return 0;
        }
    }
    return -1;
}

int StrFadeOutStop_80082380( unsigned int fadeSpeed )
{
    if ( gStr_FadeOut1_800BF16C &&
         ( gStr_fadeout_2_800C0584 != gStreamVol_800BF15C || bstr_fade_inProgress_800BF0CC ) )
    {
        dword_800C04F4 = gStreamVol_800BF15C / fadeSpeed;
        if ( !( gStreamVol_800BF15C / fadeSpeed ) )
        {
            dword_800C04F4 = 1;
        }
        bstr_fade_inProgress_800BF0CC = 0;
        gStream_800C04F0 = -1;
        return 0;
    }
    else
    {
        printf( "Canceled STR FadeOut(%x:%x:%x)",
                             gStr_FadeOut1_800BF16C,
                             gStr_fadeout_2_800C0584,
                             gStreamVol_800BF15C );
        return -1;
    }
}

int StartStream_80082448()
{
    if ( !dword_800C04EC )
    {
        bstr_fade_inProgress_800BF0CC = 0;
        gStr_fadeout_2_800C0584 = 0;
        dword_800C04F4 = 0;
    }
    dword_800BF26C = 0;
    dword_8009F7B4 = -1;
    FS_StreamOpen_80024060();

    CDLOAD_BUF_800BF058 = FS_StreamGetData_800240E0( 2 );

    if ( !CDLOAD_BUF_800BF058 )
    {
        printf( "Stream:File Pos Error\n" );
        FS_StreamClose_80024098();
        return -1;
    }

    // Consume big-endian int from CDLOAD_BUF_800BF058
    dword_800C051C = CDLOAD_BUF_800BF058[ 0 ] << 24;
    dword_800C051C |= CDLOAD_BUF_800BF058[ 1 ] << 16;
    dword_800C051C |= CDLOAD_BUF_800BF058[ 2 ] << 8;
    dword_800C051C |= CDLOAD_BUF_800BF058[ 3 ];

    str_unplay_size_800BF1AC = dword_800BF168 = dword_800C051C;

    // Consume big-endian short from CDLOAD_BUF_800BF058
    gStreamVol_800BF15C = CDLOAD_BUF_800BF058[ 4 ] << 8;
    gStreamVol_800BF15C |= CDLOAD_BUF_800BF058[ 5 ];

    // Consume big-endian short from CDLOAD_BUF_800BF058
    dword_800C0504 = CDLOAD_BUF_800BF058[ 6 ] << 8;
    dword_800C0504 |= CDLOAD_BUF_800BF058[ 7 ];

    // Consume byte from CDLOAD_BUF_800BF058
    if ( CDLOAD_BUF_800BF058[ 8 ] == 1 )
    {
        dword_800BF268 = CDLOAD_BUF_800BF058[ 8 ];
    }
    else
    {
        dword_800BF268 = 0;
    }

    // Consume byte from CDLOAD_BUF_800BF058
    dword_800C0580 = CDLOAD_BUF_800BF058[ 9 ];

    printf( "StartStream(%x:vol=%x)\n", gStream_800C04F0, gStreamVol_800BF15C );
    if ( dword_800C04EC )
    {
        StrFadeWkSet_80083964();
    }

    SD_80081FC4( 0x600000 );
    dword_800BEFF0 = NULL;
    sub_800241B4( CDLOAD_BUF_800BF058 );
    dword_800C0418 = NULL;
    dword_800BF1DC = NULL;
    return 0;
}

void UserSpuIRQProc_80082640( void )
{
    switch ( gStr_FadeOut1_800BF16C & 0xf )
    {
    case 2:
    case 3:
        break;

    case 4:
        dword_800BEFF4 = 0;
        break;

    case 5:
        switch ( dword_800C0504 )
        {
        case 0x800:
            if ( ( dword_800BEFF4++ & 1 ) != 0 )
            {
                dword_800BF270 += 0x100;
                dword_800BF270 &= 0x1fff;
            }
            break;

        case 0xc00:
            if ( ( dword_800BEFF4++ & 3 ) != 0 )
            {
                dword_800BF270 += 0x100;
                dword_800BF270 &= 0x1fff;
            }
            break;

        default:
            dword_800BF270 += 0x100;
            dword_800BF270 &= 0x1fff;
            break;
        }
        break;

    case 6:
        switch ( dword_800C0504 )
        {
        case 0x800:
            if ( ( dword_800BEFF4++ & 1 ) != 0 )
            {
                dword_800BF270 += 0x100;
                dword_800BF270 &= 0x1fff;
            }
            break;

        case 0xc00:
            if ( ( dword_800BEFF4++ & 3 ) != 0 )
            {
                dword_800BF270 += 0x100;
                dword_800BF270 &= 0x1fff;
            }
            break;

        default:
            dword_800BF270 += 0x100;
            dword_800BF270 &= 0x1fff;
            break;
        }
        break;
    }

    mts_isend_80089B04( 1 );

    if ( ( dword_800BF1A8 & 1 ) == 0 )
    {
        SpuSetIRQAddr( blank_data_addr_800BF00C + 256 );
    }
    else
    {
        SpuSetIRQAddr( blank_data_addr_800BF00C );
    }

    dword_800BF1A8++;
    SpuSetIRQ( SPU_RESET );
}

void sub_8008279C( void )
{
}

void SD_nullsub_20_800827A4( void )
{
}

int StrSpuTransWithNoLoop_800827AC( void )
{
    SpuVoiceAttr attr;
    int          result;
    int          bVar1;
    u_long       start_addr;

    result = 0;

    if ( dword_8009F7B8 != 0 )
    {
        sub_800241B4( dword_8009F7B8 );
        dword_8009F7B8 = 0;
    }

    switch ( gStr_FadeOut1_800BF16C & 0xf )
    {
    case 2:
        if ( dword_800BF1A4 == 0 )
        {
            if ( ( se_rev_on_800C0574 != 0 ) && ( dword_800BF160 != 0 ) && ( dword_800BF144 != 0 ) )
            {
                SpuSetReverbVoice( 1, 0x600000 );
            }
            else
            {
                SpuSetReverbVoice( 0, 0x600000 );
            }

            stream_data_ptr_800BEFE4 = FS_StreamGetData_800240E0( 1 );

            if ( stream_data_ptr_800BEFE4 )
            {
                dword_800C040C = 0;
                dword_800BF164 = 0;
                stream_data_ptr_800BEFE4[ 1 ] |= 0x4;
                SpuSetTransferStartAddr( spu_bgm_start_ptr_r_800BF0C8 );
                SpuWrite( stream_data_ptr_800BEFE4, 4096 );

                if ( dword_800BF268 == 0 )
                {
                    dword_800BF164 = 4096;
                    str_unplay_size_800BF1AC -= 4096;
                }

                dword_800BF1A4 = 1;
                dword_8009F7B4 = -1;
            }
            else
            {
                gStr_FadeOut1_800BF16C = 7;
                break;
            }
        }
        else
        {
            stream_data_ptr_800BEFE4[ dword_800BF164 + 1 ] |= 0x4;
            SpuSetTransferStartAddr( spu_bgm_start_ptr_l_800BF060 );
            SpuWrite( stream_data_ptr_800BEFE4 + dword_800BF164, 4096 );
            dword_800BF164 += 4096;
            str_unplay_size_800BF1AC -= 4096;

            if ( dword_800BF268 == 0 )
            {
                dword_8009F7B8 = stream_data_ptr_800BEFE4;
                stream_data_ptr_800BEFE4 = FS_StreamGetData_800240E0( 1 );

                if ( !stream_data_ptr_800BEFE4 )
                {
                    gStr_FadeOut1_800BF16C = 7;
                    break;
                }

                dword_800BF164 = 0;
            }

            dword_800BF1A4 = 0;
            gStr_FadeOut1_800BF16C++;
        }

        result = 1;
        break;

    case 3:
        if ( ( str_unplay_size_800BF1AC == 0 ) || ( str_unplay_size_800BF1AC < 0 ) )
        {
            gStr_FadeOut1_800BF16C++;
        }

        if ( dword_800BF1A4 == 0 )
        {
            stream_data_ptr_800BEFE4[ dword_800BF164 + 4081 ] |= 0x1;
            SpuSetTransferStartAddr( spu_bgm_start_ptr_r_800BF0C8 + 4096 );
            SpuWrite( stream_data_ptr_800BEFE4 + dword_800BF164, 4096 );

            if ( dword_800BF268 == 0 )
            {
                dword_800BF164 += 4096;
                str_unplay_size_800BF1AC -= 4096;
            }

            dword_800BF1A4 = 1;
            result = 1;
        }
        else
        {
            stream_data_ptr_800BEFE4[ dword_800BF164 + 4081 ] |= 0x1;
            SpuSetTransferStartAddr( spu_bgm_start_ptr_l_800BF060 + 4096 );
            SpuWrite( stream_data_ptr_800BEFE4 + dword_800BF164, 4096 );
            str_unplay_size_800BF1AC -= 4096;
            dword_8009F7B8 = stream_data_ptr_800BEFE4;
            stream_data_ptr_800BEFE4 = FS_StreamGetData_800240E0( 1 );
            dword_800BF164 = 0;
            dword_800BF1A4 = 0;
            result = 1;
            gStr_FadeOut1_800BF16C++;
        }
        break;

    case 4:
        attr.mask = 0xff93;
        attr.voice = 0x200000;
        attr.volume.left = 0;
        attr.volume.right = 0;
        attr.a_mode = 1;
        attr.s_mode = 1;
        attr.r_mode = 3;
        attr.ar = 0x10;
        attr.dr = 0;
        attr.sr = 0;
        attr.rr = 8;
        attr.sl = 0xf;
        attr.pitch = dword_800C0504;
        attr.addr = spu_bgm_start_ptr_r_800BF0C8;
        SpuSetVoiceAttr( &attr );
        attr.mask = 0xff93;
        attr.voice = 0x400000;
        attr.volume.left = 0;
        attr.volume.right = 0;
        attr.a_mode = 1;
        attr.s_mode = 1;
        attr.r_mode = 3;
        attr.ar = 0x10;
        attr.dr = 0;
        attr.sr = 0;
        attr.rr = 8;
        attr.sl = 0xf;
        attr.pitch = (ushort)dword_800C0504;
        attr.addr = spu_bgm_start_ptr_l_800BF060;
        SpuSetVoiceAttr( &attr );
        dword_800BF270 = 0;
        SD_80082170( 0x600000 );
        dword_800C0414 = 4096;
        dword_800BEFEC = 0;
        dword_8009F7B4 = 0;
        gStr_FadeOut1_800BF16C++;

        if ( ( str_unplay_size_800BF1AC == 0 ) || ( str_unplay_size_800BF1AC < 0 ) )
        {
            if ( ( dword_800C051C < 0 ) || ( dword_800C051C > 768 ) )
            {
                dword_800BF264 = ( dword_800C051C - 768 ) & ~0xff;
            }
            else
            {
                dword_800BF264 = 256;
            }

            gStr_FadeOut1_800BF16C++;
        }
        break;

    case 5:
        if ( stream_data_ptr_800BEFE4 && ( dword_800BEFEC == 0 ) )
        {
            dword_8009F7B4++;
        }

        if ( ( ( dword_800C0414 == ( dword_800BF270 & 4096 ) ) || ( dword_800BF1A4 != 0 ) ) ||
             ( dword_800BEFEC != 0 ) )
        {
            result = 1;

            if ( ( stream_data_ptr_800BEFE4 ) && ( dword_800BEFEC == 0 ) )
            {
                dword_800BEFF0 = 0;
                bVar1 = 0;

                if ( dword_800BF268 != 0 )
                {
                    dword_800BEFE8 = 0;
                }

                if ( dword_800BF270 >= 4096u )
                {
                    if ( dword_800BF1A4 == 0 )
                    {
                        SpuSetTransferStartAddr( spu_bgm_start_ptr_r_800BF0C8 );
                        dword_800BF1A4 = 1;
                    }
                    else
                    {
                        SpuSetTransferStartAddr( spu_bgm_start_ptr_l_800BF060 );
                        dword_800BF1A4 = 0;
                        dword_800C0414 = ( dword_800C0414 + 4096 ) & 0x1fff;

                        if ( dword_800BF268 == 0 )
                        {
                            bVar1 = 1;
                        }
                        else
                        {
                            dword_800BEFE8 = 1;
                        }
                    }

                    ( stream_data_ptr_800BEFE4 + dword_800BF164 )[ 1 ] |= 4; // (temporary?) hack, maybe this was an inline like STOREL?
                }
                else
                {
                    if ( dword_800BF1A4 == 0 )
                    {
                        dword_800BF1A4 = 1;
                        SpuSetTransferStartAddr( spu_bgm_start_ptr_r_800BF0C8 + 4096 );
                    }
                    else
                    {
                        dword_800BF1A4 = 0;
                        dword_800C0414 = ( dword_800C0414 + 4096 ) & 0x1fff;
                        SpuSetTransferStartAddr( spu_bgm_start_ptr_l_800BF060 + 4096 );
                        bVar1 = 1;

                        if ( dword_800BF268 != 0 )
                        {
                            dword_800BEFE8 = 1;
                        }
                    }

                    ( stream_data_ptr_800BEFE4 + dword_800BF164 )[ 4081 ] |= 1; // (temporary?) hack
                }

                SpuWrite( stream_data_ptr_800BEFE4 + dword_800BF164, 4096 );

                if ( dword_800BF268 != 0 )
                {
                    if ( dword_800BEFE8 != 0 )
                    {
                        dword_800BF164 = dword_800BF164 + 4096;

                        if ( str_unplay_size_800BF1AC > 4096u )
                        {
                            str_unplay_size_800BF1AC -= 4096;
                        }
                        else
                        {
                            dword_800BF164 = 0;

                            dword_800BF264 = 4096 + dword_800BF270 + str_unplay_size_800BF1AC;
                            dword_800BF264 &= 0xffffff00;
                            dword_800BF264 -= 0x300;
                            dword_800BF264 &= 0x1fff;

                            gStr_FadeOut1_800BF16C++;
                        }
                    }
                }
                else
                {
                    dword_800BF164 += 4096;

                    if ( str_unplay_size_800BF1AC > 4096u )
                    {
                        str_unplay_size_800BF1AC -= 4096;
                    }
                    else
                    {
                        if ( dword_800BF1A4 != 0 )
                        {
                            printf( "\nSOUND STREAMING ERROR:NO LAST LEFT DATA\n" );
                        }

                        printf( "str_unplay_size=%x\n", str_unplay_size_800BF1AC );

                        dword_800BF164 = 0;

                        dword_800BF264 = 4096 + dword_800BF270 + str_unplay_size_800BF1AC;
                        dword_800BF264 &= 0xffffff00;
                        dword_800BF264 -= 0x300;
                        dword_800BF264 &= 0x1fff;

                        gStr_FadeOut1_800BF16C++;
                    }
                }

                if ( bVar1 )
                {
                    dword_8009F7B8 = stream_data_ptr_800BEFE4;
                    stream_data_ptr_800BEFE4 = FS_StreamGetData_800240E0( 1 );
                    dword_800BF164 = 0;
                }
            }
            else
            {
                dword_800BEFF0 = 1;
                printf( "*" );

                if ( dword_800BF270 >= 4096u )
                {
                    if ( dword_800BEFEC == 0 )
                    {
                        SpuSetTransferStartAddr( spu_bgm_start_ptr_r_800BF0C8 );
                        start_addr = spu_bgm_start_ptr_r_800BF0C8;
                        dword_800BEFEC = 1;
                    }
                    else
                    {
                        SpuSetTransferStartAddr( spu_bgm_start_ptr_l_800BF060 );
                        start_addr = spu_bgm_start_ptr_l_800BF060;
                        dword_800C0414 = ( dword_800C0414 + 4096 ) & 0x1fff;
                        dword_800BEFEC = 0;
                    }

                    byte_800A2D28[ 1 ] = 6;
                    byte_800A2D28[ 4081 ] = 2;
                    SpuWrite( byte_800A2D28, 4096 );
                }
                else
                {
                    if ( dword_800BEFEC == 0 )
                    {
                        start_addr = spu_bgm_start_ptr_r_800BF0C8 + 4096;
                        dword_800BEFEC = 1;
                        SpuSetTransferStartAddr( start_addr );
                    }
                    else
                    {
                        dword_800C0414 = ( dword_800C0414 + 4096 ) & 0x1fff;
                        start_addr = spu_bgm_start_ptr_l_800BF060 + 4096;
                        dword_800BEFEC = 0;
                        SpuSetTransferStartAddr( start_addr );
                    }

                    byte_800A2D28[ 1 ] = 2;
                    byte_800A2D28[ 4081 ] = 3;
                    SpuWrite( byte_800A2D28, 4096 );
                }

                if ( ( dword_800BEFEC == 0 ) && ( dword_800C0414 != 0 ) )
                {
                    dword_8009F7B8 = stream_data_ptr_800BEFE4;
                    stream_data_ptr_800BEFE4 = FS_StreamGetData_800240E0( 1 );

                    if ( ( stream_data_ptr_800BEFE4 == NULL ) && FS_StreamGetEndFlag_800243B8() )
                    {
                        dword_800BF264 = -1;
                        gStr_FadeOut1_800BF16C++;
                        break;
                    }
                }
            }
        }

        if ( FS_StreamIsForceStop_800243C8() )
        {
            dword_800BF264 = -1;
            gStr_FadeOut1_800BF16C++;
        }
        break;

    case 6:
        if ( ( dword_800BF270 == dword_800BF264 ) || ( dword_800BF264 == -1 ) )
        {
            attr.mask = 0x4000;
            attr.voice = 0x200000;
            attr.rr = 8;
            SpuSetVoiceAttr( &attr );
            attr.mask = 0x4000;
            attr.voice = 0x400000;
            attr.rr = 8;
            SpuSetVoiceAttr( &attr );
            SD_80081FC4( 0x600000 );
            dword_8009F7B4 = -1;
            gStr_FadeOut1_800BF16C++;
        }
        else
        {
            dword_8009F7B4++;
        }
        break;

    case 7:
        dword_8009F7B4 = -1;
        break;
    }

    return result;
}

void StrSpuTransClose_80083394()
{
    if ( stream_data_ptr_800BEFE4 )
    {
        sub_800241B4( stream_data_ptr_800BEFE4 );
        stream_data_ptr_800BEFE4 = NULL;
    }

    if ( dword_8009F7B8 )
    {
        sub_800241B4( dword_8009F7B8 );
        dword_8009F7B8 = NULL;
    }

    dword_800BEFF0 = 0;
    FS_StreamClose_80024098();
}

void StrSpuTrans_800833FC( void )
{
    StrSpuTransWithNoLoop_800827AC();
}

int SD_LoadSeFile_8008341C()
{
    if ( se_fp_800BF014 )
    {
        printf( "ERROR:SE File Already Opened.\n" );
        SD_8008395C( se_fp_800BF014, 4 );
        se_fp_800BF014 = 0;
    }
    se_fp_800BF014 = SD_SongLoadData_8008394C( se_load_code_800BF28C, 4 );
    if ( se_fp_800BF014 < 0 )
    {
        se_fp_800BF014 = 0;
        printf( "LoadSeFile:File Open Error(%x)\n", se_load_code_800BF28C );
        nullsub_7_80081A10( &dword_800C0500, -4, se_load_code_800BF28C ); // TODO: Not sure if last arg exists
        return -1;
    }
    else
    {
        SD_80083954( se_fp_800BF014, se_exp_table_800C0520, 0x2800 );
        SD_8008395C( se_fp_800BF014, 4 );
        se_load_code_800BF28C = 0;
        se_fp_800BF014 = 0;
        return 0;
    }
}

int SD_LoadWaveFile_800834FC( void )
{
    unsigned int offset;
    unsigned int size;
    char        *dst;

    if ( wave_data_800BF294 != 0 )
    {
        printf( "ERROR:Wave File Already Opened.\n" );
        SD_8008395C( wave_data_800BF294, 2 );
        wave_data_800BF294 = 0;
    }

    wave_data_800BF294 = SD_SongLoadData_8008394C( wave_load_code_800C0528, 2 );

    if ( wave_data_800BF294 < 0 )
    {
        wave_data_800BF294 = 0;
        printf( "LoadWaveFile:File Open Error(%x)\n", wave_load_code_800C0528 );
        nullsub_7_80081A10( &dword_800C0500, -4, wave_load_code_800C0528 );
        wave_load_code_800C0528 = 0;
        return -1;
    }

    SD_80083954( wave_data_800BF294, cdload_buf_800BF010, 0x18000 );
    byte_800C056C = 0x4F;

    offset = cdload_buf_800BF010[ 0 ] << 24;
    offset |= cdload_buf_800BF010[ 1 ] << 16;
    offset |= cdload_buf_800BF010[ 2 ] << 8;
    offset |= cdload_buf_800BF010[ 3 ];

    size = cdload_buf_800BF010[ 4 ] << 24;
    size |= cdload_buf_800BF010[ 5 ] << 16;
    size |= cdload_buf_800BF010[ 6 ] << 8;
    size |= cdload_buf_800BF010[ 7 ];

    printf( "SUP OFFSET=%x:SIZE=%x\n", offset, size );

    wave_load_ptr_800C0508 = cdload_buf_800BF010 + 16;
    dst = (char *)voice_tbl_800BF1E0 + offset;
    memcpy( dst, wave_load_ptr_800C0508, size );

    printf( "    SRC=%x:DST=%x\n", (unsigned int)wave_load_ptr_800C0508, (unsigned int)dst );

    wave_load_ptr_800C0508 += size;

    spu_load_offset_800BF140 = wave_load_ptr_800C0508[ 0 ] << 24;
    spu_load_offset_800BF140 |= wave_load_ptr_800C0508[ 1 ] << 16;
    spu_load_offset_800BF140 |= wave_load_ptr_800C0508[ 2 ] << 8;
    spu_load_offset_800BF140 |= wave_load_ptr_800C0508[ 3 ];

    wave_unload_size_800BF274 = wave_load_ptr_800C0508[ 4 ] << 24;
    wave_unload_size_800BF274 |= wave_load_ptr_800C0508[ 5 ] << 16;
    wave_unload_size_800BF274 |= wave_load_ptr_800C0508[ 6 ] << 8;
    wave_unload_size_800BF274 |= wave_load_ptr_800C0508[ 7 ];

    printf( "BIN OFFSET=%x\n", (unsigned int)wave_load_ptr_800C0508 );
    printf( "SPU OFFSET=%x:SIZE=%x\n",
                         spu_load_offset_800BF140, wave_unload_size_800BF274 );

    wave_load_ptr_800C0508 += 16;

    if ( wave_unload_size_800BF274 > ( 0x17FE0 - size ) )
    {
        dword_800C0650 = 0x17FE0 - size;
    }
    else
    {
        dword_800C0650 = wave_unload_size_800BF274;
    }

    wave_unload_size_800BF274 -= dword_800C0650;
    wave_save_code_800C0578 = wave_load_code_800C0528;
    return 0;
}

void sub_80083804( void )
{
    int temp;

    if ( wave_unload_size_800BF274 > 0x18000U )
    {
        SD_80083954( wave_data_800BF294, cdload_buf_800BF010, 0x18000 );
        dword_800C0650 = 0x18000;
        dword_800BF27C = 2;
        wave_load_ptr_800C0508 = cdload_buf_800BF010;
        wave_unload_size_800BF274 -= 0x18000U;
        return;
    }
    if ( wave_unload_size_800BF274 != 0 )
    {
        SD_80083954( wave_data_800BF294, cdload_buf_800BF010, wave_unload_size_800BF274 );
        temp = wave_unload_size_800BF274;
        wave_unload_size_800BF274 = 0;
        dword_800BF27C = 2;
        wave_load_ptr_800C0508 = cdload_buf_800BF010;
        dword_800C0650 = temp;
        return;
    }
    dword_800BF27C = 0;
    SD_8008395C( wave_data_800BF294, 2 );
    printf( "Complete Load Se:%x\n", wave_load_code_800C0528 );
    wave_data_800BF294 = 0;
    nullsub_7_80081A10( &dword_800C0500, 0, wave_load_code_800C0528 );
}

void WaveSpuTrans_80083944( void )
{
}

int SD_SongLoadData_8008394C( int a1, int a2 )
{
    return -1;
}

int SD_80083954( int a1, unsigned char *a2, int a3 )
{
    return -1;
}

int SD_8008395C( int a1, int a2 )
{
    return -1;
}

void StrFadeWkSet_80083964()
{
    unsigned int amount; // $a0

    if ( dword_800C04EC == 0xFF0000F8 )
    {
        amount = 100;
    }
    else
    {
        amount = 400;
        if ( dword_800C04EC != 0xFF0000F9 )
        {
            return;
        }
    }
    StrFadeIn_800822C8( amount );
    dword_800C04EC = 0;
    gStr_fadeout_2_800C0584 = gStreamVol_800BF15C;
}

int StrFadeInt_800839C8( void )
{
    SpuVoiceAttr attr;
    unsigned int diff;

    if ( gStr_FadeOut1_800BF16C < 5 )
    {
        return 0;
    }

    if ( dword_800C04F4 != 0 )
    {
        gStr_fadeout_2_800C0584 += dword_800C04F4;

        if ( gStr_fadeout_2_800C0584 >= gStreamVol_800BF15C )
        {
            if ( gStream_800C04F0 == -1 )
            {
                SD_80081FC4( 0x600000 );
                gStr_FadeOut1_800BF16C = 7;
            }
            else
            {
                dword_800BF26C = 1;
            }

            dword_800C04F4 = 0;
            gStr_fadeout_2_800C0584 = gStreamVol_800BF15C;
        }
        else
        {
            dword_800BF26C = 0;
        }
    }

    attr.mask = SPU_VOICE_VOLL | SPU_VOICE_VOLR;
    attr.voice = SPU_21CH;

    diff = gStreamVol_800BF15C - gStr_fadeout_2_800C0584;

    if ( ( dword_800BF1DC != 0 ) && ( dword_800C0418 < 2 ) )
    {
        attr.volume.left = 0;
        attr.volume.right = 0;
    }
    else if ( dword_800C050C != 0 )
    {
        attr.volume.left = ( diff * 0xA6 ) >> 8;
        attr.volume.right = ( diff * 0xA6 ) >> 8;
    }
    else
    {
        attr.volume.left = 0;
        attr.volume.right = diff;
    }

    SpuSetVoiceAttr( &attr );

    attr.mask = SPU_VOICE_VOLL | SPU_VOICE_VOLR;
    attr.voice = SPU_22CH;

    if ( ( dword_800BF1DC != 0 ) && ( dword_800C0418 < 2 ) )
    {
        attr.volume.left = 0;
        attr.volume.right = 0;
    }
    else if ( dword_800C050C != 0 )
    {
        attr.volume.left = ( diff * 0xA6 ) >> 8;
        attr.volume.right = ( diff * 0xA6 ) >> 8;
    }
    else
    {
        attr.volume.left = diff;
        attr.volume.right = 0;
    }

    SpuSetVoiceAttr( &attr );
    return 0;
}

int  num2char_80083E68( unsigned int num );

void sub_80083BB4( unsigned int arg0, char *outStr )
{
    if ( ( arg0 + 0xFF000000 ) <= 0xFFFF )
    {
        outStr[ 0 ] = 'S';
        outStr[ 1 ] = 'G';
        outStr[ 2 ] = num2char_80083E68( ( arg0 >> 0x14 ) & 0xF );
        outStr[ 3 ] = num2char_80083E68( ( arg0 >> 0x10 ) & 0xF );
        outStr[ 4 ] = num2char_80083E68( ( arg0 >> 0xC ) & 0xF );
        outStr[ 5 ] = num2char_80083E68( ( arg0 >> 8 ) & 0xF );
        outStr[ 6 ] = num2char_80083E68( ( arg0 >> 4 ) & 0xF );
        outStr[ 7 ] = num2char_80083E68( arg0 & 0xF );
        outStr[ 8 ] = '.';
        outStr[ 9 ] = 'M';
        outStr[ 10 ] = 'D';
        outStr[ 11 ] = 'X';
        outStr[ 12 ] = '\0';
        return;
    }
    if ( ( arg0 + 0xFE000000 ) <= 0xFFFF )
    {
        outStr[ 0 ] = 'S';
        outStr[ 1 ] = 'E';
        outStr[ 2 ] = num2char_80083E68( ( arg0 >> 0x14 ) & 0xF );
        outStr[ 3 ] = num2char_80083E68( ( arg0 >> 0x10 ) & 0xF );
        outStr[ 4 ] = num2char_80083E68( ( arg0 >> 0xC ) & 0xF );
        outStr[ 5 ] = num2char_80083E68( ( arg0 >> 8 ) & 0xF );
        outStr[ 6 ] = num2char_80083E68( ( arg0 >> 4 ) & 0xF );
        outStr[ 7 ] = num2char_80083E68( arg0 & 0xF );
        outStr[ 8 ] = '.';
        outStr[ 9 ] = 'E';
        outStr[ 10 ] = 'F';
        outStr[ 11 ] = 'X';
        outStr[ 12 ] = '\0';
        return;
    }
    if ( ( arg0 + 0x20000000 ) <= 0xFFFF )
    {
        outStr[ 0 ] = 'S';
        outStr[ 1 ] = 'D';
        outStr[ 2 ] = num2char_80083E68( ( arg0 >> 0x14 ) & 0xF );
        outStr[ 3 ] = num2char_80083E68( ( arg0 >> 0x10 ) & 0xF );
        outStr[ 4 ] = num2char_80083E68( ( arg0 >> 0xC ) & 0xF );
        outStr[ 5 ] = num2char_80083E68( ( arg0 >> 8 ) & 0xF );
        outStr[ 6 ] = num2char_80083E68( ( arg0 >> 4 ) & 0xF );
        outStr[ 7 ] = num2char_80083E68( arg0 & 0xF );
        outStr[ 8 ] = '.';
        outStr[ 9 ] = 'P';
        outStr[ 10 ] = 'C';
        outStr[ 11 ] = 'M';
        outStr[ 12 ] = '\0';
        // return; // Why missing return here?
    }
    if ( ( arg0 + 0x02000000 ) <= 0xFFFF )
    {
        outStr[ 0 ] = 'W';
        outStr[ 1 ] = 'V';
        outStr[ 2 ] = num2char_80083E68( ( arg0 >> 0x14 ) & 0xF );
        outStr[ 3 ] = num2char_80083E68( ( arg0 >> 0x10 ) & 0xF );
        outStr[ 4 ] = num2char_80083E68( ( arg0 >> 0xC ) & 0xF );
        outStr[ 5 ] = num2char_80083E68( ( arg0 >> 8 ) & 0xF );
        outStr[ 6 ] = num2char_80083E68( ( arg0 >> 4 ) & 0xF );
        outStr[ 7 ] = num2char_80083E68( arg0 & 0xF );
        outStr[ 8 ] = '.';
        outStr[ 9 ] = 'W';
        outStr[ 10 ] = 'V';
        outStr[ 11 ] = 'X';
        outStr[ 12 ] = '\0';
        return;
    }
}

int num2char_80083E68( unsigned int num )
{
    num &= 0xf;
    if ( num < 10 )
    {
        num += 0x30;
    }
    else
    {
        num += 0x57;
    }
    return num & 0xff;
}

unsigned char *SD_SngDataLoadInit_80083E8C( unsigned short unused )
{
    sng_status_800C04F8 = 0;
    sng_status_800BF158 = 0;
    sng_off_80087E2C();
    printf( "SD_SngDataLoadInit\n" );
    return sd_sng_data_800C0420;
}

void SD_80083ED4( void )
{
    sng_status_800BF158 = 2;
}

unsigned char *SD_80083EE8( unsigned short unused )
{
    return se_exp_table_800C0520;
}

void SD_80083EF8( void )
{
    se_load_code_800BF28C = 0;
}

char *LoadInit_80083F08( unsigned short unused )
{
    char *ret;

    if ( dword_800BF27C != 0 )
    {
        printf( "LoadInit %d\n", dword_800BF27C );
        *(int *)1 = 0;
    }
    ret = cdload_buf_800BF010;
    dword_800BF27C = 1;
    return ret;
}

int SD_80083F54( char *end )
{
    char        *src;
    char        *dst;
    int          offset;
    int          size;
    unsigned int used;

    byte_800C056C = 0x4F;

    src = cdload_buf_800BF010 + 16;

    offset = cdload_buf_800BF010[ 0 ] << 24;
    offset |= cdload_buf_800BF010[ 1 ] << 16;
    offset |= cdload_buf_800BF010[ 2 ] << 8;
    offset |= cdload_buf_800BF010[ 3 ];

    dst = (char *)voice_tbl_800BF1E0 + offset;

    size = cdload_buf_800BF010[ 4 ] << 24;
    size |= cdload_buf_800BF010[ 5 ] << 16;
    size |= cdload_buf_800BF010[ 6 ] << 8;
    size |= cdload_buf_800BF010[ 7 ];

    wave_load_ptr_800C0508 = cdload_buf_800BF010 + 16;

    if ( ( src + size ) >= end )
    {
        return 0;
    }

    memcpy( dst, src, size );

    wave_load_ptr_800C0508 += size;

    spu_load_offset_800BF140 = wave_load_ptr_800C0508[ 0 ] << 24;
    spu_load_offset_800BF140 |= wave_load_ptr_800C0508[ 1 ] << 16;
    spu_load_offset_800BF140 |= wave_load_ptr_800C0508[ 2 ] << 8;
    spu_load_offset_800BF140 |= wave_load_ptr_800C0508[ 3 ];

    wave_unload_size_800BF274 = wave_load_ptr_800C0508[ 4 ] << 24;
    wave_unload_size_800BF274 |= wave_load_ptr_800C0508[ 5 ] << 16;
    wave_unload_size_800BF274 |= wave_load_ptr_800C0508[ 6 ] << 8;
    wave_unload_size_800BF274 |= wave_load_ptr_800C0508[ 7 ];

    wave_load_ptr_800C0508 += 16;

    used = ( end - cdload_buf_800BF010 ) - ( size + 32 );
    if ( used < wave_unload_size_800BF274 )
    {
        dword_800C0650 = used;
    }
    else
    {
        dword_800C0650 = wave_unload_size_800BF274;
    }

    wave_unload_size_800BF274 -= dword_800C0650;
    wave_save_code_800C0578 = wave_load_code_800C0528;

    if ( !SpuIsTransferCompleted( SPU_TRANSFER_PEEK ) )
    {
        printf( "$" );
    }

    SpuSetTransferStartAddr( spu_wave_start_ptr_800C052C + spu_load_offset_800BF140 );
    SpuWrite( wave_load_ptr_800C0508, dword_800C0650 );

    spu_load_offset_800BF140 += dword_800C0650;
    wave_load_ptr_800C0508 += dword_800C0650;

    return 1;
}

char *SD_WavLoadBuf_800841D4( char *arg0 )
{
    char *buf;

    if ( dword_800BF27C != 1 && wave_unload_size_800BF274 == 0 )
    {
        dword_800BF27C = 0;
        return arg0;
    }

    switch ( dword_800BF27C )
    {
    case 1:
        if ( SD_80083F54( arg0 ) != 0 )
        {
            dword_800BF27C = 3;
        }
        break;

    case 2:
        break;

    case 3:
        buf = cdload_buf_800BF010 + 0x18000;
        if ( wave_load_ptr_800C0508 == buf )
        {
            wave_load_ptr_800C0508 = cdload_buf_800BF010;
        }
        else if ( buf < wave_load_ptr_800C0508 )
        {
            printf( "!!! SD WAV LOAD BUF OVER !!!\n" );
            *(int *)1 = 0;
        }
        if ( arg0 < wave_load_ptr_800C0508 )
        {
            dword_800C0650 = 0x18000 + cdload_buf_800BF010 - ( wave_load_ptr_800C0508 );
        }
        else
        {
            dword_800C0650 = arg0 - wave_load_ptr_800C0508;
        }
        wave_unload_size_800BF274 -= dword_800C0650;
        SpuSetTransferStartAddr( spu_wave_start_ptr_800C052C + spu_load_offset_800BF140 );
        SpuWrite( wave_load_ptr_800C0508, dword_800C0650 );
        spu_load_offset_800BF140 += dword_800C0650;
        wave_load_ptr_800C0508 += dword_800C0650;
        break;
    }

    if ( arg0 >= cdload_buf_800BF010 + 0x18000 )
    {
        arg0 = cdload_buf_800BF010;
    }
    return arg0;
}

void SD_Unload_800843BC()
{
    if ( wave_unload_size_800BF274 )
    {
        if ( wave_load_ptr_800C0508 == cdload_buf_800BF010 + 0x18000 )
        {
            wave_load_ptr_800C0508 = cdload_buf_800BF010;
        }
        SpuSetTransferStartAddr( spu_wave_start_ptr_800C052C + spu_load_offset_800BF140 );
        SpuWrite( wave_load_ptr_800C0508, wave_unload_size_800BF274 );
        spu_load_offset_800BF140 += wave_unload_size_800BF274;
        wave_load_ptr_800C0508 += wave_unload_size_800BF274;
    }
    dword_800BF27C = 0;
    if ( wave_unload_size_800BF274 )
    {
        printf( "unload %d\n", wave_unload_size_800BF274 );
    }
}
