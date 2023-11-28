#ifndef _SD_H_
#define _SD_H_

typedef struct     WAVE_W
{
    int            field_0_addr;
    char           field_4_sample_note;
    char           field_5_sample_tune;
    char           field_6_a_mode;
    char           field_7_ar;
    char           field_8_dr;
    char           field_9_s_mode;
    char           field_A_sr;
    char           field_B_sl;
    char           field_C_r_mode;
    char           field_D_rr;
    char           field_E_pan;
    char           field_F_decl_vol;
} WAVE_W;

typedef struct SOUND_W
{
    unsigned char *field_0_mpointer;
    char           field_4_ngc;
    char           field_5_ngo;
    char           field_6_ngs;
    char           field_7_ngg;
    char           field_8_lp1_cnt;
    char           field_9_lp2_cnt;
    short          field_A_pad;
    int            field_C_lp1_vol;
    int            field_10_lp2_vol;
    int            field_14_lp1_freq;
    int            field_18_lp2_freq;
    unsigned char *field_1C_lp1_addr;
    unsigned char *field_20_lp2_addr;
    unsigned char *field_24_lp3_addr;
    unsigned char  field_28_kakfg;
    char           field_29_pad[ 3 ];
    unsigned char *field_2C_kak1ptr;
    unsigned char *field_30_kak2ptr;
    char           field_34_pvoc;
    char           field_35;
    char           field_36;
    char           field_37;
    int            field_38_pvod;
    int            field_3C_pvoad;
    int            field_40_pvom;
    char           field_44_vol;
    char           field_45_panc;
    char           field_46;
    char           field_47;
    int            field_48_pand;
    int            field_4C_panad;
    int            field_50_panm;
    char           field_54_panf;
    char           field_55;
    char           field_56_panmod;
    char           field_57_swpc;
    char           field_58_swphc;
    char           field_59;
    char           field_5A;
    char           field_5B;
    int            field_5C_swpd;
    int            field_60_swpad;
    int            field_64_swpm;
    char           field_68_swsc;
    char           field_69_swshc;
    char           field_6A_swsk;
    char           field_6B;
    int            field_6C_swss;
    char           field_70_vibhc;
    char           field_71;
    char           field_72;
    char           field_73;
    int            field_74_vib_tmp_cnt;
    char           field_78_vib_tbl_cnt;
    char           field_79_vib_tc_ofst;
    char           field_7A;
    char           field_7B;
    int            field_7C_vibd;
    int            field_80_vibdm;
    char           field_84_vibhs;
    char           field_85_vibcs;
    char           field_86_vibcad;
    char           field_87_pad;
    int            field_88_vibad;
    unsigned int   field_8C_rdmc;
    int            field_90_rdmo;
    char           field_94_rdms;
    char           field_95_pad[ 3 ];
    int            field_98_rdmd;
    signed char    field_9C_trec;
    char           field_9D_trehc;
    char           field_9E_tred;
    char           field_9F_trecad;
    char           field_A0_trehs;
    char           field_A1_pad[ 3 ];
    unsigned int   field_A4_snos;
    int            field_A8_ptps;
    int            field_AC_dec_vol;
    int            field_B0_tund;
    int            field_B4_tmpd;
    char           field_B8_tmp;
    char           field_B9_pad[ 3 ];
    signed int     field_BC_tmpad;
    char           field_C0_tmpc;
    char           field_C1_pad[ 3 ];
    int            field_C4_tmpw;
    char           field_C8_tmpm;
    char           field_C9_pad[ 3 ];
    int            field_CC_rest_fg;
    char           field_D0_macro;
    char           field_D1_micro;
    unsigned short field_D2_rrd;
} SOUND_W;

typedef struct     SPU_TRACK_REG
{
    short          field_0_vol_l;
    short          field_2_vol_r;
    int            field_4_vol_fg;
    short          field_8_pitch;
    short          field_A_pad;
    int            field_C_pitch_fg;
    int            field_10_addr;
    int            field_14_addr_fg;
    int            field_18_a_mode;
    short          field_1C_ar;
    short          field_1E_dr;
    int            field_20_env1_fg;
    int            field_24_s_mode;
    short          field_28_sr;
    short          field_2A_sl;
    int            field_2C_env2_fg;
    int            field_30_r_mode;
    short          field_34_rr;
    short          field_36_pad;
    int            field_38_env3_fg;
} SPU_TRACK_REG;

typedef struct     SEPLAYTBL
{
    unsigned char  field_0_pri;
    char           field_1_kind;
    char           field_2_character;
    char           field_3_pad;
    unsigned char *field_4_addr;
    unsigned int   field_8_code;
} SEPLAYTBL;

typedef struct     SE_TBL
{
    char           field_0;
    char           field_1;
    char           field_2;
    char           field_3;
    int            field_4[ 3 ];
} SE_TBL;

typedef void (*TMDXFunc)();

void               keyoff_80087F80();
int                SD_8008395C( int a1, int a2 );
int                SD_80083954( int a1, unsigned char *a2, int a3 );
void               init_sng_work_8008559C();
int                SD_SongLoadData_8008394C( int a1, int a2 );
void               freq_set_800885D4( unsigned int a1 );
int                get_str_counter_80088CA0();
int                sd_str_play_800886DC();
int                sd_set_cli_800887EC( int sdCode, int unused );
unsigned char     *SD_SngDataLoadInit_80083E8C( unsigned short unused );
char              *LoadInit_80083F08( unsigned short );
void               SD_80083ED4();
unsigned char     *SD_80083EE8( unsigned short );
void               SD_Unload_800843BC();
char              *SD_WavLoadBuf_800841D4( char *arg0 );
void               StrFadeWkSet_80083964();
void               volxset_80086C98( unsigned char a1 );
void               pan_generate_80086198();
void               drum_set_80088694( unsigned char a1 );
void               vol_set_80088320( unsigned int vol );
void               StrFadeIn_800822C8( unsigned int a1 );
int                StrFadeOut_80082310( unsigned int a1 );
int                StrFadeOutStop_80082380( unsigned int fadeSpeed );
void               SdMain_80081A18();
int                sd_task_active_800886C4();

#endif // _SD_H_
