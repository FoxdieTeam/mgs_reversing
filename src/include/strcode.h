#ifndef _STRCODE_H_
#define _STRCODE_H_

//-----------------------------------------------------------------------------
// GCL StrCodes
//-----------------------------------------------------------------------------

// scenario codes
#define HASH_scenerio           0xea54 // GV_StrCode( "scenerio" )
#define HASH_demo               0xa242 // GV_StrCode( "demo" )

// basic commands
#define HASH_CMD_if             0x0d86 // GV_StrCode( "if" )
#define HASH_CMD_eval           0x64c0 // GV_StrCode( "eval" )
#define HASH_CMD_return         0xcd3a // GV_StrCode( "return" )
#define HASH_CMD_foreach        0x7636 // GV_StrCode( "foreach" )

// extended commands
#define HASH_CMD_mesg           0x22ff // GV_StrCode( "mesg" )
#define HASH_CMD_trap           0xd4cb // GV_StrCode( "trap" )
#define HASH_CMD_chara          0x9906 // GV_StrCode( "chara" )
#define HASH_CMD_map            0xc091 // GV_StrCode( "map" )
#define HASH_CMD_mapdef         0x7d50 // GV_StrCode( "mapdef" )
#define HASH_CMD_camera         0xeee9 // GV_StrCode( "camera" )
#define HASH_CMD_light          0x306a // GV_StrCode( "light" )
#define HASH_CMD_start          0x9a1f // GV_StrCode( "start" )
#define HASH_CMD_load           0xc8bb // GV_StrCode( "load" )
#define HASH_CMD_radio          0x24e1 // GV_StrCode( "radio" )
#define HASH_CMD_str_status     0xe43c // GV_StrCode( "str_status" )
#define HASH_CMD_demo           0xa242 // GV_StrCode( "demo" )
#define HASH_CMD_ntrap          0xdbab // GV_StrCode( "ntrap" )
#define HASH_CMD_delay          0x430d // GV_StrCode( "delay" )
#define HASH_CMD_pad            0xcc85 // GV_StrCode( "pad" )
#define HASH_CMD_varsave        0x5c9e // GV_StrCode( "varsave" )
#define HASH_CMD_system         0x4ad9 // GV_StrCode( "system" )
#define HASH_CMD_sound          0x698d // GV_StrCode( "sound" )
#define HASH_CMD_menu           0x226d // GV_StrCode( "menu" )
#define HASH_CMD_rand           0x925e // GV_StrCode( "rand" )
#define HASH_CMD_func           0xe257 // GV_StrCode( "func" )
#define HASH_CMD_demodebug      0xa2bf // GV_StrCode( "demodebug" )
#define HASH_CMD_print          0xb96e // GV_StrCode( "print" )
#define HASH_CMD_jimaku         0xec9d // GV_StrCode( "jimaku" ) // subtitle

//-----------------------------------------------------------------------------

#define HASH_PAN2               0x922b // GV_StrCode( "pan2" )

//-----------------------------------------------------------------------------
// Traps
//-----------------------------------------------------------------------------

#define HASH_TRAP_ALL           0x14c9

//  Events
#define HASH_ENTER              0x0dd2 // GV_StrCode( "入る" )
#define HASH_LEAVE              0xd5cc // GV_StrCode( "出る" )
#define HASH_KILL               0x3223 // GV_StrCode( "kill" )
#define HASH_OFF                0xc927 // GV_StrCode( "off" )
#define HASH_ON                 0x0e4e // GV_StrCode( "on" )
#define HASH_PADON              0x2580 // GV_StrCode( "padon" )
#define HASH_PADOFF             0xaf6a // GV_StrCode( "padoff" )
#define HASH_SLOW               0x3e92 // GV_StrCode( "slow" )
#define HASH_SOUND_ON           0x2761 // GV_StrCode( "音入れる" )
#define HASH_SOUND_OFF          0xed7F // GV_StrCode( "音切る" )

//-----------------------------------------------------------------------------
// HZD
//-----------------------------------------------------------------------------

#define HASH_MAIN               0x7df9 // GV_StrCode( "メイン" ) - Refers to the main area of the map to load
#define HASH_ASIATO             0xdc55 // GV_StrCode( "asiato" )
#define HASH_POOL               0xca85 // GV_StrCode( "pool" )
#define HASH_POOLATO            0x7833 // GV_StrCode( "poolato" )

//-----------------------------------------------------------------------------
// Textures files (.pcx)
//-----------------------------------------------------------------------------
#define PCX_GO_EXIT             0x4d9a // GV_StrCode( "GO_EXIT" )
#define PCX_GO_CONTINUE         0x669d // GV_StrCode( "GO_CONTINUE" )
#define PCX_EMPTY2              0xb05c // GV_StrCode( "empty2" )
#define PCX_LSIGHT              0x08db // GV_StrCode( "lsight" )
#define PCX_SOCOM_F             0xe4cc // GV_StrCode( "socom_f" )
#define PCX_MG_SOLID            0x3f37 // GV_StrCode( "MG_SOLID" )
#define PCX_COMING_SOON         0x0abb // GV_StrCode( "COMING_SOON" )
#define PCX_SMOKE               0x512d // GV_StrCode( "smoke" )
#define PCX_WT_SUD11            0xdf92 // GV_StrCode( "wt_sud11" )
#define PCX_MAGAZIN             0x7e4c // GV_StrCode( "magazin" )
#define PCX_FA_FL10             0xfe8e // GV_StrCode( "fa_fl10" )
#define PCX_BOMB1_FL            0xac92 // GV_StrCode( "bomb1_fl" )
#define PCX_CANON_SEQ           0x2447 // GV_StrCode( "canon_seq" )
#define PCX_BLOOD_2             0x7b54 // GV_StrCode( "blood_2" )
#define PCX_SONIC               0x4cec // GV_StrCode( "sonic" )
#define PCX_LENSE_FLARE1        0x55a6 // GV_StrCode( "lense_flare1" )
#define PCX_B_MARK              0xdcd3 // GV_StrCode( "b_mark" )
#define PCX_Q_MARK              0xfad3 // GV_StrCode( "q_mark" )
#define PCX_HEART               0x1968 // GV_StrCode( "heart" )
#define PCX_PCH_FOG             0xf314 // GV_StrCode( "pch_fog" )
#define PCX_HOSI                0xcafe // GV_StrCode( "hosi" )
#define PCX_ZZZ                 0xf7bb // GV_StrCode( "zzz" )
#define PCX_ASIATO              0xdc55 // GV_StrCode( "asiato" )
#define PCX_RCM_L               0x479f // GV_StrCode( "rcm_l" )
#define PCX_W_BONBORI           0xa9cd // GV_StrCode( "w_bonbori" )
#define PCX_DOOR2               0x50eb // GV_StrCode( "door2" )

//-----------------------------------------------------------------------------
// Sight files (.sgt)
//-----------------------------------------------------------------------------
#define SGT_SCOPE               0x51c8 // GV_StrCode( "scope" )
#define SGT_NIKITA              0x15a9 // GV_StrCode( "nikita" )
#define SGT_CB_BOX              0xe2a9 // GV_StrCode( "cb_box" )
#define SGT_IR_GGLE1            0x84db // GV_StrCode( "ir_ggle1" )
#define SGT_IR_GGLE2            0x84dc // GV_StrCode( "ir_ggle2" )
#define SGT_IR_GGLE3            0x84dd // GV_StrCode( "ir_ggle3" )
#define SGT_NV_GGLE1            0x8504 // GV_StrCode( "nv_ggle1" )
#define SGT_NV_GGLE2            0x8505 // GV_StrCode( "nv_ggle2" )
#define SGT_NV_GGLE3            0x8506 // GV_StrCode( "nv_ggle3" )
#define SGT_MASK                0x1303 // GV_StrCode( "mask" )
#define SGT_CAMERA              0xeee9 // GV_StrCode( "camera" )
#define SGT_CAMERA_2            0xb3cd // GV_StrCode( "camera_2" )

//-----------------------------------------------------------------------------
// Model files (.kmd)
//-----------------------------------------------------------------------------

// Init "stage" (always loaded before each stage)
#define KMD_NULL                0xe224 // GV_StrCode( "null" )
#define KMD_SNAKE               0x992d // GV_StrCode( "snake" )
#define KMD_GOGGLES             0xe1d2 // GV_StrCode( "goggles" )
#define KMD_GAS_MASK            0x4244 // GV_StrCode( "gas_mask" )
#define KMD_RIFLE               0x2d3b // GV_StrCode( "rifle" )
#define KMD_STINGER             0x57f8 // GV_StrCode( "stinger" )
#define KMD_NIKITA              0x15a9 // GV_StrCode( "nikita" )
#define KMD_STN_FR              0x76ab // GV_StrCode( "stn_fr" )
#define KMD_NIK_MIS             0x9a90 // GV_StrCode( "nik_mis" )
#define KMD_FAMAS               0x4725 // GV_StrCode( "famas" )
#define KMD_SOCOM2              0x36f6 // GV_StrCode( "socom2" )
#define KMD_STN_BA              0x761a // GV_StrCode( "stn_ba" )
#define KMD_CAN_GREN            0x7a64 // GV_StrCode( "can_gren" )
#define KMD_GRENADE             0x3b88 // GV_StrCode( "grenade" )
#define KMD_SOCOM               0x21b6 // GV_StrCode( "socom" )
#define KMD_CLAYMORE            0x17a1 // GV_StrCode( "claymore" )
#define KMD_C4_BOMB             0xf83d // GV_StrCode( "c4_bomb" )
#define KMD_CB_BOX              0xe2a9 // GV_StrCode( "cb_box" )
#define KMD_CIGAR               0x2ef8 // GV_StrCode( "cigar" )
#define KMD_BANDANA             0xdb4d // GV_StrCode( "bandana" )
#define KMD_KAGE                0x117c // GV_StrCode( "kage" )
#define KMD_IPPANHEI            0x96b6 // GV_StrCode( "ippanhei" )

// Stage s00a/d00a (docks)
#define KMD_SNE_WET2            0x7693 // GV_StrCode( "sne_wet2" )

//-----------------------------------------------------------------------------
// Animation files (.oar)
//-----------------------------------------------------------------------------
#define OAR_SNAKE               0x992d // GV_StrCode( "snake" )

//-----------------------------------------------------------------------------
// Sprites files (.pcc)
//-----------------------------------------------------------------------------
#define PCC_READ                0xa0be // GV_StrCode( "read" ) // for loading ?

//-----------------------------------------------------------------------------
// Charas (in .bin overlays files)
//-----------------------------------------------------------------------------

#define CHARA_SNAKE             0x21ca // GV_StrCode( "スネーク" )
#define CHARA_DOOR              0xb997 // GV_StrCode( "ドア" )
#define CHARA_ITEM              0x8767 // GV_StrCode( "アイテム" )

#define CHARA_SNDTST            0x4efc
#define CHARA_SELECT            0xd2f6
#define CHARA_RIPPLES           0x63aa
#define CHARA_PAD               0xcbf8
#define CHARA_VIBRATE           0xfed1
#define CHARA_BREATH            0x4170
#define CHARA_ENV_SOUND         0x3f9a // env_snd.c
#define CHARA_CAMERA_SHAKE      0x7bc2 // camshake.c
#define CHARA_CAT_IN            0x51c6
#define CHARA_CINEMA            0x7a05
#define CHARA_PAD_DEMO          0x3ed7
#define CHARA_DYNAMIC_SEGMENT   0xb103 // DYMC_SEG
#define CHARA_ASIOTO            0x92bc // FOOTSTEPS ?
#define CHARA_ASIATO            0x02c4 // FOOTPRINTS ?
#define CHARA_OBSTACLE          0xec77
#define CHARA_SHAKE_MODEL       0xba52 // shakemdl.c
#define CHARA_PATO_LAMP         0x30ce // pato_lmp.c
#define CHARA_COMMAND           0xc6d7
#define CHARA_WT_AREA           0xdba3
#define CHARA_WATCHER           0x6e9a
#define CHARA_SMOKE             0x170c
#define CHARA_EMITTER           0x32e5
#define CHARA_ELEVATOR          0x2abc
#define CHARA_MOUSE             0xd4a5
#define CHARA_RSURFACE          0x81ea
#define CHARA_TELOP             0x7ff7
#define CHARA_BUBBLE_S          0x1a02
#define CHARA_O2_DAMAGE         0x5d64 // o2_damge.c
#define CHARA_FADE_IN_OUT       0xa12e // fadeio.c
#define CHARA_TOBCNT            0xaefb
#define CHARA_MOTION_SEQUENCE   0x0fad // motse.c
#define CHARA_CANCEL            0xb4e6
#define CHARA_GAS_EFFECT        0x5a50 // gas_efct
#define CHARA_DOLL              0xe97e
#define CHARA_TRACK_TRAP        0xcb3a // tracktrp.c
#define CHARA_CAMERA            0x6e90 // カメラ
#define CHARA_SPHERE            0x73ea
#define CHARA_BLINK_TX          0x8185
#define CHARA_OBJECT            0x4811
#define CHARA_SEARCH_LIGHT      0xf50f // searchli.c
#define CHARA_SNOW              0x18e3 // 雪
#define CHARA_LAMP              0x1ad3
#define CHARA_DOOR              0xb997
#define CHARA_FADEIO            0x0003
#define CHARA_FADEIO_0004       0x0004
#define CHARA_SHUTER            0x0005
#define CHARA_SHUTER_03D9       0x03d9
#define CHARA_BUBBLE_T          0x0012
#define CHARA_BUBBLE_P          0x0013
#define CHARA_DEMOKAGE          0x000f
#define CHARA_UNKNOWN_000E      0x000e // ???
#define CHARA_KOGAKU2_001A      0x001a
#define CHARA_KOGAKU2_001B      0x001b
#define CHARA_WINDCRCL          0x001e
#define CHARA_SUB_EFCT          0x0021 // Focus
#define CHARA_BLOOD_BL          0x0025 // Blur without blood?
#define CHARA_SEPIA             0x0028
#define CHARA_D_BLOODS_002B     0x002b
#define CHARA_SMKE_LN           0x0031
#define CHARA_RED_ALERT         0x0037 // red_alrt.c
#define CHARA_RED_ALERT_0038    0x0038
#define CHARA_SPARK2            0x003c
#define CHARA_SPARK             0x003d
#define CHARA_INVERLT2          0x003f
#define CHARA_GAS_EFCT          0x0042
#define CHARA_FALL_SPL          0x0044
#define CHARA_FAMASLIT          0x0045
#define CHARA_CAMERA_JPEG       0x81c7 // GV_StrCode( "ＪＰＥＧ" )
#define CHARA_WT_VIEW           0x8e45
#define CHARA_UJI               0xf5c5
#define CHARA_INTR_CAM          0xdd8b
#define CHARA_BUB_D_SN          0xc0fe
#define CHARA_PUT_OBJECT        0xf4c3 // put_obj.c
#define CHARA_DUCTMOUS          0x3303
#define CHARA_ELEVATOR_PANEL    0xe253 // evpanel.c
#define CHARA_GAS_EFFECT        0x5a50 // gas_efct
#define CHARA_KIKEN             0x52bf
#define CHARA_WSURFACE          0xeea7
#define CHARA_INFRARED_CENSOR   0x43a0 // ir_cens.c
#define CHARA_GAS_DAMAGE        0x8d5a // gasdamge
#define CHARA_GUNCAME           0xa9c5
#define CHARA_VIB_EDIT          0x6c66
#define CHARA_DUMMY_WALL        0x58f0 // dummy_wl.c
#define CHARA_DUMMY_FLOOR       0x9d00 // dummy_fl.c
#define CHARA_FIND_TRAP         0x118c // findtrap.c
#define CHARA_MOSAIC            0x0065
#define CHARA_HIYOKO            0x42e4
#define CHARA_POINT             0x5147
#define CHARA_PAD_CBF8          0xcbf8
#define CHARA_BULLET            0x000b
#define CHARA_UNKNOWN_004C      0x004c
#define CHARA_CHANGE            0xf722

//-----------------------------------------------------------------------------
// Stages
//-----------------------------------------------------------------------------

#define HASH_s00a               0x469b // GV_StrCode( "s00a" )

// Other charas shouldn't be needed for the main exe
/*
#define CHARA_UNKNOWN_002A      0x002a // ???
#define CHARA_UNKNOWN_002F      0x002f // ???
#define CHARA_BLST_LN           0x0030
#define CHARA_BLOOD             0x0009 // not sure!
#define CHARA_D_BLOODS          0x000d
#define CHARA_BLOOD_DRP         0x0048 // blooddrp.c
#define CHARA_BLOOD_HZD         0x0047 // bloodhzd.c
#define CHARA_SPLASH            0x000a
#define CHARA_BOMBLED           0x004a
#define CHARA_UNKNOWN_0033      0x0033 // ???
#define CHARA_CELOFAN           0x003a
#define CHARA_CELOFAN2          0x0040
#define CHARA_CRSH_SMK          0x0039
#define CHARA_UNKNOWN_0034      0x0034 // ???
#define CHARA_GOGGLE            0x0015
#define CHARA_GGLSIGHT          0x0016
#define CHARA_ENVMAP3           0x001c
#define CHARA_BLAST             0x0001
#define CHARA_DEMOASI           0x0010
#define CHARA_UNKNOWN_0019      0x0019 // ???
#define CHARA_GASMASK_SIGHT     0x0022 // gmsight.c
#define CHARA_REALSHDW          0x0046
#define CHARA_INVERLT           0x003b
#define CHARA_GOGGLE_IR         0x0017 // goggleir.c
#define CHARA_GOGGLE_SIGHT      0x0018 // gglsight.c
#define CHARA_MGREXLZR          0x0020
#define CHARA_METAL_GEAR_ROOM   0x004b // mg_room.c
#define CHARA_UNKNOWN_000C      0x000c // ???
#define CHARA_UNKNOWN_0011      0x0011 // ???
#define CHARA_WINDCRCL          0x0049
#define CHARA_NINJALZR          0x0041
#define CHARA_KATANA            0x002d
#define CHARA_UNKNOWN_0035      0x0035 // ??
#define CHARA_UNKNOWN_0036      0x0036 // ??
#define CHARA_PLASMA_001D       0x001d
#define CHARA_PLASMA_0024       0x0024
#define CHARA_UNKNOWN_0007      0x0007
#define CHARA_RFSIGHT           0x0029
#define CHARA_SCOPE             0x0014
#define CHARA_SEPIA             0x001f
#define CHARA_M1E1SMKE          0x0032
#define CHARA_SIGHT             0x002c
#define CHARA_UNKNOWN_0008      0x0008 // ???
#define CHARA_UNKNOWN_0002      0x0002 // ???
#define CHARA_UNKNOWN_003E      0x003e // ???
#define CHARA_UNKNOWN_0026      0x0026 // ???
#define CHARA_UNKNOWN_0027      0x0027 // ???
#define CHARA_SUB_ROOM          0x002e
#define CHARA_SUB_EFFECT        0x0043 // sub_efct.c
#define CHARA_UNKNOWN_0006      0x0006 // ???
#define CHARA_D_BLOODS_0023     0x0023
#define CHARA_10A_DEMO          0x40e9
#define CHARA_S11_OBJS          0xe068
#define CHARA_11B_DEMO          0xd53c
#define CHARA_11G_DEMO          0x153e
#define CHARA_LOADER            0x9ffd
#define CHARA_SECOND            0x2d0a
#define CHARA_ABST              0x566f
#define CHARA_AB_DEMO1          0x4974
#define CHARA_AB_DEMO2          0x4975
#define CHARA_A_SHOWER          0x05ef
#define CHARA_GCL_ARRAY         0x2a90 // gclarray.c
#define CHARA_AT                0x9988
#define CHARA_BELONG            0xf59e
#define CHARA_B_SMOKE           0x6b6c
#define CHARA_BLOODY_MERYL      0x1158 // mel10.c - 血まみれメリル
#define CHARA_BLOOD_CL          0x4e95
#define CHARA_BLOOD_BL_6A4C     0x6a4c
#define CHARA_BLOOD_BL_9093     0x9093
#define CHARA_BOXALL            0xf74b
#define CHARA_BREAK_OBJECT      0x32fc // breakobj.c
#define CHARA_BTN_CHK           0x6471
#define CHARA_B_SELECT          0x93b6
#define CHARA_WIRE              0x7eca
#define CHARA_CAMERA2           0x56cc
#define CHARA_CAPE              0xb99f
#define CHARA_CHAIR             0x788d
#define CHARA_LAND_MINE         0x3c0c // jirai
#define CHARA_DYNCON            0xcc45
#define CHARA_TIMER             0x22c6
#define CHARA_PAUSE             0xeced // not sure!
#define CHARA_CRANE             0xa3fb
#define CHARA_CROW              0x8e60
#define CHARA_DEATH_SP          0xbe79
#define CHARA_DSMOKE            0x6a98
#define CHARA_DSMOKE2           0x76bc
#define CHARA_DEMOSEL           0x3686
#define CHARA_DISPLAY           0x9f7d // displ.c
#define CHARA_DOG               0x6c0e
#define CHARA_DOOR2             0x73f8
#define CHARA_DRUM              0xb58d
#define CHARA_DRUM2             0x4be8
#define CHARA_DYNAMIC_FLOOR     0xaf6c // DYMC_FLR
#define CHARA_ED_TELOP          0xe75a
#define CHARA_ELECTRIC_DAMAGE   0x107c // elc_damg.c
#define CHARA_ELECTRIC_FLOOR    0xaef2 // elc_flr.c
#define CHARA_ELE_CROW          0x9ab9
#define CHARA_EMITTER2          0xa9dd
#define CHARA_ENDING2           0xb789
#define CHARA_ENV_TEST          0x76fe
#define CHARA_FALL_SPLASH       0xc73e // fall_spl.c
#define CHARA_FOG               0xd6fb
#define CHARA_FONT_TEXT         0x84e1 // fonttext.c
#define CHARA_FURNACE           0xadd8
#define CHARA_JEEP_EMY          0x2477
#define CHARA_FALL_SPLASH       0xccd3 // fall_spl.c
#define CHARA_GLASS             0x8e70
#define CHARA_GOAL              0xdb1f
#define CHARA_GODZCOM           0x9eb7
#define CHARA_GODZILA           0xcb1f
#define CHARA_GROUND_CAMERA     0x5f5a // grd_cam
#define CHARA_BG_HEX            0xcbeb
#define CHARA_BG_HEX_S          0x0d9b
#define CHARA_ITEM              0x8767
#define CHARA_JEEP_SRL          0x6a48
#define CHARA_JDRUM             0xa27e
#define CHARA_COUNTDWN          0xb757
#define CHARA_JOHNNY            0x1ef9
#define CHARA_DEMOSEL           0x81c7
#define CHARA_SCOPE             0x4f02
#define CHARA_KEY_ITEM          0xc6ac
#define CHARA_KMDARUTL          0xa6f6 // not sure!
#define CHARA_LANDING           0x8b1a
#define CHARA_LIFE_UP           0x711f
#define CHARA_LIFT              0x425f
#define CHARA_LIFT2             0x921b
#define CHARA_LIQUID            0x7bf2
#define CHARA_AB_CH             0xcf72
#define CHARA_MLOAD             0x53c7
#define CHARA_M1E1              0x9d71
#define CHARA_M1E1CAME          0xd5ec
#define CHARA_DOLL2             0xe448
#define CHARA_HAIR_M            0x450f
#define CHARA_MEMPSY            0xaf72
#define CHARA_MERYL3            0xc755
#define CHARA_MERYL7            0x5078
#define CHARA_MERYL72           0xe271
#define CHARA_MGREX             0x4754
#define CHARA_MG_DEMO1          0x954b
#define CHARA_HIND_s11g         0x1787
#define CHARA_MIRROR            0xc218
#define CHARA_EVPANEL           0xa2b5
#define CHARA_MODEL_DT          0x7acf
#define CHARA_MONITOR1          0x6d78
#define CHARA_UNKNOWN_3453      0x3453 // ???
#define CHARA_MOVIE             0x5345
#define CHARA_M_DOOR            0xb98c
#define CHARA_MEMPSY            0xd3c0
#define CHARA_HAIR_N            0xf002
#define CHARA_NINJA             0x30ba
#define CHARA_OPEN              0xcf79
#define CHARA_OPENA             0x3ac3
#define CHARA_OPENP             0xcfef
#define CHARA_OPT               0x976c
#define CHARA_OPTA              0x8d31
#define CHARA_OPTP              0xb916
#define CHARA_PADDEMO2          0x720d
#define CHARA_PANEL             0x20f2
#define CHARA_PANEL2            0xdd95
#define CHARA_PAPER             0x5f02
#define CHARA_POCKET            0xfdb6
#define CHARA_COUNTDWN          0x8fdc
#define CHARA_POCKET            0x6414
#define CHARA_UNKNOWN_AA13      0xaa13 // ???
#define CHARA_UNKNOWN_CF00      0xcf00 // ???
#define CHARA_PERAPICT          0x10ff
#define CHARA_PHOTOSEL          0xedeb
#define CHARA_SCN_ANIM          0x8427
#define CHARA_BG_SP             0x17f5
#define CHARA_BG_STAGE          0x1fa5
#define CHARA_BG_ST1            0xb032
#define CHARA_BG_ST2            0xb033
#define CHARA_BG_SP_CM          0xb7ae
#define CHARA_BG_SP_ST          0xbc76
#define CHARA_PK_GATE           0x9c6c
#define CHARA_PJEEP             0xb47a
#define CHARA_PLASMA            0x9bc2
#define CHARA_FLR_SPA           0xfc0b
#define CHARA_UNKNOWN_3AD2      0x3ad2 // ???
#define CHARA_BG_HEX_P          0xcc89
#define CHARA_PREOPE            0x6d1b
#define CHARA_NINJA_D8DD        0xd8dd
#define CHARA_OTACOM            0xbf66
#define CHARA_SNE_03C_A404      0xa404
#define CHARA_SNE_03C_27A2      0x27a2
#define CHARA_PSYCO             0xa76f
#define CHARA_MERYL07B          0xf4b0
#define CHARA_PSYOBJ            0x710d
#define CHARA_PUTHZD            0x91aa
#define CHARA_P_LAMP            0x169c
#define CHARA_ITEM_DOT          0x917b
#define CHARA_RANK              0x04f2
#define CHARA_RASEN             0x5fd9
#define CHARA_RASEN_EL          0xaa21
#define CHARA_RED_ALERT         0xe397 // red_alrt.c
#define CHARA_REVOLVER          0x05af
#define CHARA_ROPE              0xbda8
#define CHARA_PIPE              0xc35f
#define CHARA_HIND              0x11e9
#define CHARA_HIND2             0xb959
#define CHARA_MLOAD             0x9302
#define CHARA_SCN_BOMB          0x600d
#define CHARA_SCN_MARK          0xee63
#define CHARA_SNAKE             0x21ca // スネーク
#define CHARA_SNAKE18           0x760e
#define CHARA_SNWARP            0x672e
#define CHARA_SNE17A            0xa791
#define CHARA_SSTORM            0xa6f5
#define CHARA_SNOWAREA          0x901e
#define CHARA_MOVIE             0xfaa8,
#define CHARA_SPHERE2           0xbee1
#define CHARA_SMKTRGT           0x175b
#define CHARA_TEXANIME          0xdcac
#define CHARA_TEX_SCRL          0x6865
#define CHARA_TORTURE           0xe608
#define CHARA_BED               0x2a21
#define CHARA_REVOLVER          0x050c
#define CHARA_VALCAN            0x9ff5
#define CHARA_VMODEL            0x0a02
#define CHARA_VOICE_SYSTEM      0x0dc9 // voicesys.c
#define CHARA_VR                0xed86
#define CHARA_VR2               0x30c8
#define CHARA_BACKGROUND        0xd07f // backgrnd.c
#define CHARA_BG2               0x1454
#define CHARA_BG3               0x1455
#define CHARA_VRBOX_DF07        0xdf0f
#define CHARA_VRBOX2_548E       0x548e
#define CHARA_VRBOX2_548F       0x548f
#define CHARA_VRBOX_5490        0x5490
#define CHARA_VRCLEAR           0x4deb
#define CHARA_VRCLEAR2_C249     0xc249
#define CHARA_VRCLEAR2_C24A     0xc24a
#define CHARA_CLUTER            0xb95f
#define CHARA_DEMOMNGR          0x8a46
#define CHARA_VRGLASS_49D2      0x49d2
#define CHARA_VRGLASS_03BF      0x03bf
#define CHARA_VRSPARK           0x0c09
#define CHARA_VRTITLE           0x5667
#define CHARA_VRWINDOW          0xd44e
#define CHARA_WINMNGR           0x3d26
#define CHARA_PAUSE_MENU        0xa5dc // pausmenu.c
#define CHARA_SNAKE_E1          0xb162
#define CHARA_WAKE              0x41a3
#define CHARA_WALL_SPA          0x2b24
#define CHARA_WATER             0x96b5
#define CHARA_WOLF2             0x962c
#define CHARA_WT_AREA2          0xa480
#define CHARA_WT_OBJ            0x69ad
#define CHARA_ZAKO              0xed87
#define CHARA_ZAKO10            0x31e3
#define CHARA_ZK10COM           0x8e64
#define CHARA_ZAKO11A           0xa608
#define CHARA_ZK11ACOM          0x5efa
#define CHARA_ZAKO11E           0xa60c
#define CHARA_ZK11ECOM          0x5f0a
#define CHARA_ZAKO11F           0xa60d
#define CHARA_ZK11FCOM          0x5f0e
#define CHARA_ZAKO14            0x31e7
#define CHARA_ZK14COM           0x8e74
#define CHARA_ZAKO19            0x31ec
#define CHARA_ZK19COM           0x8e88
#define CHARA_ZAKOCOM           0x7cf7
#define CHARA_NINJA_PLAYABLE    0xb8d4 // njaplay.c
#define CHARA_WINMNGR           0xae06
#define CHARA_LOADREP           0xc8ca
#define CHARA_SAVE_MANAGER      0xc5b7 // savemngr.c
#define CHARA_PLAY_DEMO         0x3f9d // playdemo.c
#define CHARA_REC_DEMO          0xf364 // recdemo.c
#define CHARA_VR_CHECK          0x26bc
#define CHARA_PRESENT           0xaf75

*/

#endif // _STRCODE_H_
