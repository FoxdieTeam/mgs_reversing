#ifndef __MGS_CHARALST_H__
#define __MGS_CHARALST_H__

#include <stddef.h>     // for NULL
#include "charadef.h"   // for NEWCHARA, CHARA

/*---------------------------------------------------------------------------*/
/*  CHARA table entry defintions                                             */
/*---------------------------------------------------------------------------*/

/* end-of-table marker */
#define CHARA_END               { 0, NULL }

// NOTE: These names should be kept in sync with the CHARAID_xxx defines
// in strcode.h as those are aliases for the 'class_id' field constants.

// TODO: We don't really need the source path listed for CHARA entries
// with decompiled functions (listing it next to the extern declaration
// is enough). Please don't remove the GV_StrCode("...") part, though.

/*--- MainCharacterEntries ---*/
#define CHARA_SNAKE             { 0x21ca, NewSnake }    // GV_StrCode("スネーク")
#define CHARA_DOOR              { 0xb997, NewDoor }     // GV_StrCode("ドア")
#define CHARA_ITEM              { 0x8767, NewItem }     // GV_StrCode("アイテム")

/*--- _StageCharacterEntries ---*/
#define CHARA_MOSAIC            { 0x0065, NewMosaic_800DCABC }      // GV_StrCode("モザイク") takabe/mosaic.c
#define CHARA_ASIATOKUN         { 0x02c4, NewAsiatoKun_800D1A70 }   // GV_StrCode("足跡君") enemy/asiato.c
#define CHARA_UNKNOWN_03BF      { 0x03bf, ? }                       // ??? (PC-ONLY)
#define CHARA_SHUTER            { 0x03d9, NewShuter_800DFB44 }      // GV_StrCode("シャッター") takabe/shuter.c
#define CHARA_RANK              { 0x04f2, ? }                       // onoda/rank/rank.c
#define CHARA_REVOLVER_050C     { 0x050c, NewRevolver_800C929C }    // chara/torture/revolver.c
#define CHARA_REVOLVER_05AF     { 0x05af, s04c_revolver_800D2028 }  // onoda/s04b/revolver.c
#define CHARA_A_SHOWER          { 0x05ef, ? }                       // okajima/a_shower.c (PC-ONLY)
#define CHARA_VMODEL            { 0x0a02, ? }                       // GV_StrCode("モデル") thing/vmodel.c (PC-ONLY)
#define CHARA_VRSPARK           { 0x0c09, ? }                       // koba/vr/vrspark.c
#define CHARA_BG_HEX_S          { 0x0d9b, ? }                       // okajima/photo/bg_hex_s.c
#define CHARA_VOICE_SYSTEM      { 0x0dc9, NewVoicesys_800CE944 }    // takabe/voicesys.c
#define CHARA_MOTION_SE         { 0x0fad, NewMotionSoundEffect }    // chara/others/motse.c
#define CHARA_ELECTRIC_DAMAGE   { 0x107c, NewElcDamg_800D4C68 }     // takabe/elc_damg.c
#define CHARA_PERAPICT          { 0x10ff, ? }                       // chara/others/perapict.c
#define CHARA_BLOODY_MERYL      { 0x1158, ? }                       // GV_StrCode("血まみれメリル") okajima/meryl10/mel10.c
#define CHARA_FIND_TRAP         { 0x118c, NewFindTrap_800D77DC }    // takabe/findtrap.c
#define CHARA_HIND_11E9         { 0x11e9, s11d_hind_800CB708 }      // chara/hind/hind.c
#define CHARA_BG2               { 0x1454, ? }                       // GV_StrCode("ＶＲ背景２") koba/vr/bg2.c
#define CHARA_BG3               { 0x1455, ? }                       // GV_StrCode("ＶＲ背景３") koba/vr/bg3.c
#define CHARA_11G_DEMO          { 0x153e, s11g_11g_demo_800CCB48 }  // okajima/11g_demo.c
#define CHARA_P_LAMP            { 0x169c, NewPLamp_800CD948 }       // okajima/p_lamp.c
#define CHARA_SMOKE             { 0x170c, NewSmoke_800D2BEC }       // GV_StrCode("煙") enemy/smoke.c
#define CHARA_UNKNOWN_173C      { 0x173c, ? }                       // (PSX-ONLY)
#define CHARA_SMKTRGT           { 0x175b, NewSmktrgt_800DC410 }     // okajima/smktrgt.c
#define CHARA_HIND_1787         { 0x1787, NewHind_800D1224 }        // chara/hind/hind.c
#define CHARA_BG_SP             { 0x17f5, ? }                       // okajima/photo/bg_sp.c (PC-ONLY)
#define CHARA_SNOW              { 0x18e3, NewSnow }                 // GV_StrCode("雪") thing/snow.c
#define CHARA_BUBBLE_S          { 0x1a02, NewBubbleS_800D5D9C }     // GV_StrCode("泡") okajima/bubble_s.c
#define CHARA_LAMP              { 0x1ad3, NewLamp }                 // game/lamp.c
#define CHARA_JOHNNY            { 0x1ef9, NewJohnny_800CA838 }      // GV_StrCode("ジョニー") chara/torture/johnny.c
#define CHARA_BG_STAGE          { 0x1fa5, ? }                       // okajima/photo/bg_stage.c
#define CHARA_PANEL             { 0x20f2, NewPanel_800D2680 }       // GV_StrCode("パネル") takabe/panel.c
#define CHARA_TIMER             { 0x22c6, ? }                       // GV_StrCode("カウントダウン") enemy/timer.c
#define CHARA_JEEP_EMY          { 0x2477, s19b_jeep_emy_800C4EC0 }  // takabe/jeep_emy/jeep_emy.c
#define CHARA_VR_CHECK          { 0x26bc, ? }                       // nobu/vr_slct/vr_check.c
#define CHARA_SNE_03C_27A2      { 0x27a2, NewSnake03c2_800CDF18 }   // chara/torture/sne_03c.c
#define CHARA_BED               { 0x2a21, NewBed_800C70DC }         // chara/torture/bed.c
#define CHARA_GCL_ARRAY         { 0x2a90, ? }                       // takabe/gclarray.c
#define CHARA_ELEVATOR          { 0x2abc, NewElevator_800D9F30 }    // GV_StrCode("エレベータ") takabe/elevator.c
#define CHARA_WALL_SPA          { 0x2b24, NewWallSpa_800CB4A4 }     // okajima/wall_spa.c
#define CHARA_SECOND_2D0A       { 0x2d0a, ? }                       // game/second.c
#define CHARA_NINJA             { 0x30ba, ? }                       // GV_StrCode("忍者") animal/ninja/ninja.c
#define CHARA_VR2               { 0x30c8, ? }                       // GV_StrCode("ＶＲ２") koba/vr/vr2.c
#define CHARA_PATO_LAMP         { 0x30ce, NewPatrolLamp_800D7A2C }  // GV_StrCode("パトランプ") okajima/pato_lmp.c
#define CHARA_ZAKO10            { 0x31e3, ? }                       // GV_StrCode("ざこ１０") animal/zako10/zako10.c
#define CHARA_ZAKO14            { 0x31e7, ? }                       // GV_StrCode("ざこ１４") animal/zako14/zako14.c
#define CHARA_ZAKO19            { 0x31ec, ? }                       // GV_StrCode("ざこ１９") animal/zako19/zako19.c
#define CHARA_EMITTER           { 0x32e5, NewEmitter }              // thing/emitter.c
#define CHARA_BREAK_OBJECT      { 0x32fc, NewBreakObject }          // takabe/breakobj.c
#define CHARA_DUCTMOUSE         { 0x3303, NewDuctmouse_800DACC8 }   // okajima/ductmous.c
#define CHARA_MOVIE_3453        { 0x3453, NewMovieGCL }             // game/movie.c
#define CHARA_DEMOSEL           { 0x3686, NewDemoSelect }           // onoda/demosel/demosel.c
#define CHARA_OPENA             { 0x3ac3, ? }                       // onoda/opena/opena.c
#define CHARA_UNKNOWN_3AD2      { 0x3ad2, ? }                       // ???
#define CHARA_CLAYMORE          { 0x3c0c, NewScenarioJirai }        // GV_StrCode("クレイモア地雷") bullet/jirai.c
#define CHARA_KOBA_WINMNGR      { 0x3d26, ? }                       // koba/vr_slct/winmngr.c
#define CHARA_UNKNOWN_3D78      { 0x3d78, ? }                       // (PSX-ONLY)
#define CHARA_PAD_DEMO          { 0x3ed7, NewPadDemo }              // GV_StrCode("パッドデモ") takabe/pad_demo.c
#define CHARA_ENV_SOUND         { 0x3f9a, NewEnvSnd_800DF424 }      // takabe/env_snd.c
#define CHARA_PLAY_DEMO         { 0x3f9d, ? }                       // nobu/vr_demo/playdemo.c (PC-ONLY)
#define CHARA_10A_DEMO          { 0x40e9, ? }                       // okajima/10a_demo.c
#define CHARA_BREATH            { 0x4170, NewBreath_800C3A1C }      // GV_StrCode("スネーク息") chara/snake/breath.c
#define CHARA_WAKE              { 0x41a3, NewWake_800C6298 }        // chara/wake/wake.c
#define CHARA_LIFT              { 0x425f, NewLift_800DE25C }        // GV_StrCode("リフト") takabe/lift.c
#define CHARA_HIYOKO            { 0x42e4, NewHiyoko_800D018C }      // okajima/hiyoko.c
#define CHARA_CENSOR            { 0x43a0, NewIrCens_800DA66C }      // GV_StrCode("赤外線センサー") takabe/ir_cens.c
#define CHARA_HAIR_M            { 0x450f, ? }                       // chara/others/hair_m.c
#define CHARA_MGREX             { 0x4754, ? }                       // kojo/mgrex.c
#define CHARA_OBJECT            { 0x4811, NewObjectChara_800DA3A4 } // enemy/object.c
#define CHARA_AB_DEMO1          { 0x4974, ? }                       // GV_StrCode("アブストデモ１") onoda/abst/ab_demo1.c
#define CHARA_AB_DEMO2          { 0x4975, ? }                       // GV_StrCode("アブストデモ２") onoda/abst/ab_demo2.c
#define CHARA_VRGLASS           { 0x49d2, ? }                       // GV_StrCode("ＶＲガラス") koba/vr/vrglass.c
#define CHARA_DRUM2             { 0x4be8, ? }                       // GV_StrCode("ドラム缶２") takabe/drum2.c
#define CHARA_VRCLEAR           { 0x4deb, ? }                       // GV_StrCode("ＶＲクリア") koba/vr/vrclear.c
#define CHARA_BLOOD_CL          { 0x4e95, NewBloodCl_800C9DF0 }     // GV_StrCode("血溜り") okajima/blood_cl.c
#define CHARA_SNDTST            { 0x4efc, NewSoundTest }            // game/sndtst.c
#define CHARA_JPEG_CAMERA       { 0x4f02, ? }                       // GV_StrCode("ＪＰＥＧカメラ")
#define CHARA_MERYL7            { 0x5078, NewEnemyMeryl_800D63A4 }  // enemy/meryl7.c
#define CHARA_POINT             { 0x5147, NewPoint }                // game/point.c
#define CHARA_CAT_IN            { 0x51c6, NewZoom_800DFA88 }        // takabe/cat_in.c
#define CHARA_KIKEN             { 0x52bf, NewKiken_800D6D24 }       // enemy/kiken.c (危険 = danger)
#define CHARA_MOVIE_5345        { 0x5345, ? }                       // movie.c
#define CHARA_UNKNOWN_53C7      { 0x53c7, ? }                       // ???
#define CHARA_VRBOX2_548E       { 0x548e, ? }                       // GV_StrCode("ＶＲＢＯＸ２") koba/vr/vrbox2.c
#define CHARA_VRBOX2_548F       { 0x548f, ? }                       // GV_StrCode("ＶＲＢＯＸ３") koba/vr/vrbox2.c
#define CHARA_VRBOX_5490        { 0x5490, ? }                       // GV_StrCode("ＶＲＢＯＸ４") koba/vr/vrbox.c
#define CHARA_VRTITLE           { 0x5667, ? }                       // GV_StrCode("ＶＲタイトル") chara/vrtitle/vrtitle.c
#define CHARA_ABST              { 0x566f, ? }                       // GV_StrCode("アブスト") onoda/abst/abst.c
#define CHARA_CAMERA2           { 0x56cc, ? }                       // GV_StrCode("カメラ２") enemy/camera2.c
#define CHARA_DMYWALL           { 0x58f0, NewDummyWall_800D7384 }   // GV_StrCode("塗り壁") takabe/dummy_wl.c
#define CHARA_GAS_EFFECT        { 0x5a50, NewGasEffect_800C4E5C }   // takabe/gas_efct.c
#define CHARA_O2_DAMAGE         { 0x5d64, NewO2Damage_800DE9C8 }    // takabe/o2_damge.c
#define CHARA_ZK11ACOM          { 0x5efa, ? }                       // GV_StrCode("ざこ１１ａコマンダー") animal/zako11a/zk11acom.c
#define CHARA_PAPER             { 0x5f02, ? }                       // takabe/paper.c
#define CHARA_ZK11ECOM          { 0x5f0a, NewZakoCommander_800DAF38 } // GV_StrCode("ざこ１１ｅコマンダー") animal/zako11e/zk11ecom.c
#define CHARA_ZK11FCOM          { 0x5f0e, NewZakoCommander_800D20D8 } // GV_StrCode("ざこ１１ｆコマンダー") animal/zako11f/zk11fcom.c
#define CHARA_GROUND_CAMERA     { 0x5f5a, ? }                       // thing/grd_cam.c (PC-ONLY)
#define CHARA_RASEN             { 0x5fd9, NewRasen2_800CB008 }      // takabe/rasen.c
#define CHARA_SCN_BOMB          { 0x600d, ? }                       // okajima/scn_bomb.c (PC-ONLY)
#define CHARA_RIPPLES           { 0x63aa, NewRipples_800D872C }     // takabe/ripples.c
#define CHARA_POCKET_6414       { 0x6414, ? }                       // --> menu/pocket.c
#define CHARA_BTN_CHK           { 0x6471, ? }                       // takabe/btn_chk.c
#define CHARA_SNWARP            { 0x672e, ? }                       // GV_StrCode("スネークワープ") enemy/snwarp.c
#define CHARA_TEX_SCRL          { 0x6865, NewTexScroll }            // takabe/tex_scrl.c
#define CHARA_WT_OBJ            { 0x69ad, ? }                       // takabe/wt_obj.c (PC-ONLY)
#define CHARA_JEEP_SRL          { 0x6a48, s19b_jeep_srl_800CE36C }  // takabe/jeep_srl.c
#define CHARA_BLOOD_BL_6A4C     { 0x6a4c, NewBloodBl_800CD7CC }     // GV_StrCode("血溜り２") okajima/blood_bl.c
#define CHARA_DSMOKE            { 0x6a98, ? }                       // chara/rope/dsmoke.c (PC-ONLY)
#define CHARA_B_SMOKE           { 0x6b6c, ? }                       // animal/liquid/b_smoke.c
#define CHARA_DOG               { 0x6c0e, NewDog_800D33C8 }         // okajima/dog/dog.c
#define CHARA_VIB_EDIT          { 0x6c66, NewVibEdit_800C47B4 }     // takabe/vib_edit.c
#define CHARA_PREOPE            { 0x6d1b, NewPreviousOperation }    // onoda/preope/preope.c
#define CHARA_MONITOR1          { 0x6d78, ? }                       // GV_StrCode("モニタ１") takabe/monitor1.c
#define CHARA_CAMERA            { 0x6e90, NewCamera_800D67F8 }      // GV_StrCode("カメラ") enemy/camera.c
#define CHARA_WATCHER           { 0x6e9a, NewSnakeWatcher_800C5034 }// GV_StrCode("巡回兵") enemy/watcher.c
#define CHARA_PSYOBJ            { 0x710d, ? }                       // chara/psyco/psyobj.c
#define CHARA_LIFE_UP           { 0x711f, NewLifeUp_800DF428 }      // takabe/life_up.c
#define CHARA_PADDEMO2          { 0x720d, ? }                       // GV_StrCode("パッドデモ２") nobu/vr_demo/paddemo2.c
#define CHARA_SPHERE            { 0x73ea, NewSphere }               // GV_StrCode("天球") thing/sphere.c
#define CHARA_DOOR2             { 0x73f8, NewDoor2_800DD9E4 }       // GV_StrCode("ドア２") takabe/door2.c
#define CHARA_SNAKE18           { 0x760e, d18a_snake18_800D4E94 }   // GV_StrCode("スネーク１８") animal/snake18/snake18.c
#define CHARA_DSMOKE2           { 0x76bc, s11d_dsmoke2_800CCD54 }   // chara/rope/dsmoke2.c
#define CHARA_ENV_TEST          { 0x76fe, ? }                       // takabe/env_test.c (PC-ONLY)
#define CHARA_CHAIR             { 0x788d, ? }                       // GV_StrCode("椅子") takabe/chair.c
#define CHARA_CINEMA            { 0x7a05, NewCinemaScreenSet }      // GV_StrCode("シネマスクリーン") takabe/cinema.c
#define CHARA_MODEL_DT          { 0x7acf, ? }                       // okajima/photo/model_dt.c (PC-ONLY)
#define CHARA_CAMERA_SHAKE      { 0x7bc2, NewCameraShake }          // takabe/camshake.c
#define CHARA_LIQUID            { 0x7bf2, ? }                       // GV_StrCode("リキッド") animal/liquid/liquid.c
#define CHARA_ZAKOCOM           { 0x7cf7, ? }                       // GV_StrCode("ざこコマンダー") animal/zako/zakocom.c
#define CHARA_WIRE              { 0x7eca, NewWire_800D709C }        // GV_StrCode("ワイヤ") onoda/s04b/wire.c
#define CHARA_TELOP_SET         { 0x7ff7, NewTelopSet_800DDB34 }    // GV_StrCode("テロップ") takabe/telop.c
#define CHARA_BLINK_TX          { 0x8185, NewBlinkTx_800DECD8 }     // okajima/blink_tx.c
#define CHARA_CAMERA_JPEG       { 0x81c7, NewCamera_800CF388 }      // GV_StrCode("ＪＰＥＧ") camera.c
#define CHARA_RSURFACE          { 0x81ea, NewRippleSurface_800D8244 } // takabe/rsurface.c
#define CHARA_SCN_ANIM          { 0x8427, ? }                       // okajima/scn_anim.c
#define CHARA_FONT_TEXT         { 0x84e1, NewFonttext_800C446C }    // chara/others/fonttext.c
#define CHARA_VRDEMO            { 0x8a46, ? }                       // GV_StrCode("ＶＲデモ") koba/demo/demomngr.c
#define CHARA_LANDING           { 0x8b1a, s11d_landing_800CDA20 }   // chara/rope/landing.c
#define CHARA_OPTA              { 0x8d31, ? }                       // onoda/optiona/opta.c
#define CHARA_GAS_DAMAGE        { 0x8d5a, NewGasDamage_800E14E8 }   // takabe/gasdamge.c
#define CHARA_WT_VIEW           { 0x8e45, NewWaterView }            // takabe/wt_view.c
#define CHARA_CROW              { 0x8e60, NewCrow_800DED08 }        // GV_StrCode("カラス") okajima/valcan/crow.c
#define CHARA_ZK10COM           { 0x8e64, ? }                       // GV_StrCode("ざこ１０コマンダー") animal/zako10/zk10com.c
#define CHARA_GLASS             { 0x8e70, NewGlass_800D37A4 }       // GV_StrCode("ガラス") takabe/glass.c
#define CHARA_ZK14COM           { 0x8e74, ? }                       // GV_StrCode("ざこ１４コマンダー") animal/zako14/zk14com.c
#define CHARA_ZK19COM           { 0x8e88, ? }                       // GV_StrCode("ざこ１９コマンダー") animal/zako19/zk19com.c
#define CHARA_POCKET_8FDC       { 0x8fdc, ? }                       // --> menu/pocket.c
#define CHARA_SNOWAREA          { 0x901e, ? }                       // okajima/snowarea.c
#define CHARA_UNKNOWN_9093      { 0x9093, ? }                       // GV_StrCode("ブラー") ???
#define CHARA_ITEM_DOT          { 0x917b, NewItemDot_800CC7D0 }     // okajima/item_dot.c
#define CHARA_PUTHZD            { 0x91aa, ? }                       // takabe/puthzd.c
#define CHARA_LIFT2             { 0x921b, ? }                       // GV_StrCode("リフト２") takabe/lift2.c (PC-ONLY)
#define CHARA_ASIOTO            { 0x92bc, NewAsioto_800C3E08 }      // enemy/asioto.c (足音 = footstep)
#define CHARA_MLOAD             { 0x9302, ? }                       // menu/mload.c
#define CHARA_B_SELECT          { 0x93b6, ? }                       // onoda/brf/b_select.c
#define CHARA_MG_DEMO1          { 0x954b, ? }                       // takabe/mg_demo1.c
#define CHARA_WOLF2             { 0x962c, NewWolf2 }                // GV_StrCode("ウルフ") okajima/wolf/wolf2.c
#define CHARA_WATER             { 0x96b5, ? }                       // takabe/water.c (PC-ONLY)
#define CHARA_OPT               { 0x976c, NewOption_800C9344 }      // onoda/option/opt.c
#define CHARA_AT                { 0x9988, NewAt_800D78A4 }          // GV_StrCode("ＡＴ") onoda/s04b/at.c
#define CHARA_ELE_CROW          { 0x9ab9, ? }                       // okajima/valcan/ele_crow.c
#define CHARA_PLASMA_9BC2       { 0x9bc2, NewPlasma_800CD110 }      // GV_StrCode("プラズマ") okajima/plasma.c
#define CHARA_PK_GATE           { 0x9c6c, ? }                       // takabe/pk_gate.c
#define CHARA_DMYFLOOR          { 0x9d00, NewDummyFloor_800D6BF8 }  // GV_StrCode("落とし穴") takabe/dummy_fl.c
#define CHARA_M1E1              { 0x9d71, ? }                       // kojo/m1e1.c
#define CHARA_GODZCOM           { 0x9eb7, ? }                       // GV_StrCode("ゴジラコマンダ") animal/godzila/godzcom.c
#define CHARA_DISPLAY           { 0x9f7d, ? }                       // chara/pocket/display/display.c
#define CHARA_VALCAN            { 0x9ff5, ? }                       // GV_StrCode("バルカン") okajima/valcan/valcan.c
#define CHARA_SECOND_9FFD       { 0x9ffd, GM_SetSecondAvailable }   // game/second.c
#define CHARA_FADE_IN_OUT       { 0xa12e, NewFadeIo_800C42BC }      // takabe/fadeio.c
#define CHARA_JDRUM             { 0xa27e, s19b_jdrum_800C95E4 }     // takabe/jeep/jdrum.c
#define CHARA_SAFETY            { 0xa2b5, Safety_800C47A0 }         // safety.c
#define CHARA_CRANE             { 0xa3fb, NewCrane_800D57A0 }       // GV_StrCode("クレーン") okajima/crane.c
#define CHARA_SNE_03C_A404      { 0xa404, NewSnake03c1_800CDAEC }   // chara/torture/sne_03c.c
#define CHARA_WT_AREA2          { 0xa480, NewWaterArea2 }           // takabe/wt_area2.c
#define CHARA_PAUSE_MENU        { 0xa5dc, ? }                       // koba/vr/pausmenu.c
#define CHARA_ZAKO11A           { 0xa608, ? }                       // GV_StrCode("ざこ１１ａ") animal/zako11a/zako11a.c
#define CHARA_ZAKO11E           { 0xa60c, s11e_zako11e_800D42E0 }   // GV_StrCode("ざこ１１ｅ") animal/zako11e/zako11e.c
#define CHARA_ZAKO11F           { 0xa60d, NewZako11F }              // GV_StrCode("ざこ１１ｆ") animal/zako11f/zako11f.c
#define CHARA_SNOWSTORM         { 0xa6f5, NewSnowStorm }            // GV_StrCode("雪嵐") kojo/sstorm.c
#define CHARA_UNKNOWN_A6F6      { 0xa6f6, ? }                       // --> kmdarutl.c
#define CHARA_PSYCO             { 0xa76f, ? }                       // GV_StrCode("サイコマンティス") chara/psyco/psyco.c
#define CHARA_SNE17A            { 0xa791, ? }                       // chara/sne17a/sne17a.c (PC-ONLY)
#define CHARA_GUNCAME           { 0xa9c5, NewGunCame_800C9190 }     // okajima/guncame.c
#define CHARA_EMITTER2          { 0xa9dd, ? }                       // thing/emitter2.c (PC-ONLY)
#define CHARA_UNKNOWN_AA13      { 0xaa13, ? }                       // ???
#define CHARA_RASEN_EL          { 0xaa21, NewRasenEl_800CCF38 }     // takabe/rasen_el.c
#define CHARA_FURNACE           { 0xadd8, NewFurnace }              // takabe/furnace.c
#define CHARA_NOBU_WINMNGR      { 0xae06, ? }                       // nobu/vr_slct/winmngr.c
#define CHARA_ELECTRIC_FLOOR    { 0xaef2, NewElcFlr_800D4A18 }      // takabe/elc_flr.c
#define CHARA_TOBCNT            { 0xaefb, NewToBeContinued }        // game/tobcnt.c
#define CHARA_DYNAMIC_FLOOR     { 0xaf6c, s15c_dymc_flr_800E1C70 }  // GV_StrCode("透明床") takabe/dymc_flr.c
#define CHARA_MEMPSY            { 0xaf72, ? }                       // chara/psyco/mempsy.c
#define CHARA_PRESENT           { 0xaf75, ? }                       // nobu/present/present.c (PC-ONLY)
#define CHARA_BG_ST1            { 0xb032, ? }                       // okajima/photo/bg_st1.c
#define CHARA_BG_ST2            { 0xb033, ? }                       // okajima/photo/bg_st2.c (PC-ONLY)
#define CHARA_DYNAMIC_SEGMENT   { 0xb103, NewDymcSeg_800C4BCC }     // GV_StrCode("透明壁") takabe/dymc_seg.c
#define CHARA_SNAKE_E1          { 0xb162, ? }                       // okajima/snake_e1.c
#define CHARA_UNKNOWN_B30A      { 0xb30a, ? }                       // (PSX-ONLY)
#define CHARA_PJEEP             { 0xb47a, ? }                       // takabe/pjeep.c
#define CHARA_CANCEL            { 0xb4e6, NewCancel }               // GV_StrCode("デモキャンセル") game/cancel.c
#define CHARA_DRUM              { 0xb58d, ? }                       // GV_StrCode("ドラム缶") takabe/drum.c
#define CHARA_ED_TELOP_B757     { 0xb757, EdTelop_800C4F18 }        // takabe/ed_telop.c (?)
#define CHARA_ENDING2           { 0xb789, NewEnding2_800C7BE8 }     // takabe/ending2.c
#define CHARA_BG_SP_CM          { 0xb7ae, ? }                       // okajima/photo/bg_sp_cm.c (PC-ONLY)
#define CHARA_NINJA_PLAYABLE    { 0xb8d4, ? }                       // chara/njaplay/njaplay.c
#define CHARA_OPTP              { 0xb916, ? }                       // onoda/optionp/optp.c
#define CHARA_HIND2             { 0xb959, NewHind2 }                // chara/hind2/hind2.c
#define CHARA_CLUTER            { 0xb95f, ? }                       // koba/vr/cluter.c (PC-ONLY)
#define CHARA_M_DOOR            { 0xb98c, ? }                       // enemy/m_door.c
#define CHARA_CAPE              { 0xb99f, NewCape_800D92F8 }        // onoda/s04b/cape.c
#define CHARA_SHAKE_MODEL       { 0xba52, NewShakemdl_800C54E8 }    // takabe/shakemdl.c
#define CHARA_BG_SP_ST          { 0xbc76, ? }                       // okajima/photo/bg_sp_st.c (PC-ONLY)
#define CHARA_ROPE              { 0xbda8, s11d_rope_800C9500 }      // --> chara/rope/rope.c
#define CHARA_DEATH_SP          { 0xbe79, NewDeathSp_800D025C }     // okajima/death_sp.c
#define CHARA_SPHERE2           { 0xbee1, ? }                       // GV_StrCode("天球２") thing/sphere2.c
#define CHARA_OTACOM            { 0xbf66, NewOtacom_800CC030 }      // chara/torture/otacom.c
#define CHARA_BUB_D_SN          { 0xc0fe, NewBubbleDisplayScene_800D90B4 } // okajima/bub_d_sn.c
#define CHARA_MIRROR            { 0xc218, NewMirror_800E085C }      // takabe/mirror.c
#define CHARA_VRCLEAR2          { 0xc249, ? }                       // GV_StrCode("ＶＲクリア２") koba/vr/vrclear2.c
#define CHARA_VRCLEAR3          { 0xc24a, ? }                       // GV_StrCode("ＶＲクリア３") koba/vr/vrclear3.c (PC-ONLY)
#define CHARA_PIPE              { 0xc35f, NewPipe_800CE73C }        // chara/rope/pipe.c
#define CHARA_SAVE_MANAGER      { 0xc5b7, ? }                       // nobu/vr_save/savemngr.c
#define CHARA_KEY_ITEM          { 0xc6ac, NewKeyItem_800C8E18 }     // okajima/key_item.c
#define CHARA_COMMANDER         { 0xc6d7, NewCommand_800D0908 }     // GV_StrCode("コマンダー") enemy/command.c
#define CHARA_FALL_SPLASH       { 0xc73e, NewFallSplash }           // okajima/fall_spl.c
#define CHARA_MERYL3            { 0xc755, ? }                       // animal/meryl3/meryl3.c
#define CHARA_LOADREP           { 0xc8ca, ? }                       // nobu/vr/loadrep.c
#define CHARA_GODZILA           { 0xcb1f, ? }                       // GV_StrCode("ゴジラ") animal/godzila/godzila.c
#define CHARA_TRUCK_TRAP        { 0xcb3a, NewTruckTrap }            // takabe/tracktrp.c
#define CHARA_BG_HEX            { 0xcbeb, ? }                       // okajima/photo/bg_hex.c (PC-ONLY)
#define CHARA_PAD               { 0xcbf8, NewPad }                  // GV_StrCode("パッドコントロール") game/pad.c
#define CHARA_DYNCON            { 0xcc45, s15c_dyncon_800D8C9C }    // GV_StrCode("コンテナ") okajima/valcan/dyncon.c
#define CHARA_BG_HEX_P          { 0xcc89, ? }                       // okajima/photo/bg_hex_p.c (PC-ONLY)
#define CHARA_UNKNOWN_CCD3      { 0xccd3, ? }                       // ??? (PC-ONLY)
#define CHARA_UNKNOWN_CF00      { 0xcf00, ? }                       // ???
#define CHARA_AB_CH             { 0xcf72, ? }                       // onoda/abst/ab_ch.c
#define CHARA_OPEN              { 0xcf79, NewOpen_800D6814 }        // GV_StrCode("タイトル") onoda/open/open.c
#define CHARA_OPENP             { 0xcfef, ? }                       // onoda/openp/openp.c
#define CHARA_BACKGROUND        { 0xd07f, ? }                       // GV_StrCode("ＶＲ背景") koba/vr/backgrnd.c
#define CHARA_SELECT            { 0xd2f6, NewSelect }               // game/select.c
#define CHARA_UNKNOWN_D3C0      { 0xd3c0, ? }                       // ???
#define CHARA_VRWINDOW          { 0xd44e, NewVrwindow_800D81AC }    // GV_StrCode("ＶＲウィンドウ") koba/vr/vrwindow.c
#define CHARA_MOUSE             { 0xd4a5, NewMouse_800D5234 }       // okajima/mouse.c
#define CHARA_11B_DEMO          { 0xd53c, ? }                       // okajima/11b_demo.c
#define CHARA_M1E1CAME          { 0xd5ec, ? }                       // kojo/m1e1came.c
#define CHARA_FOG               { 0xd6fb, NewFog_800D4208 }         // takabe/fog.c
#define CHARA_NINJA_D8DD        { 0xd8dd, NewNinja_800CC9B4 }       // chara/torture/ninja.c
#define CHARA_GOAL              { 0xdb1f, ? }                       // GV_StrCode("ゴール") koba/vr/goal.c
#define CHARA_WT_AREA           { 0xdba3, NewWaterArea }            // takabe/wt_area.c
#define CHARA_TEXANIME          { 0xdcac, ? }                       // enemy/texanime.c (PC-ONLY)
#define CHARA_INTR_CAM          { 0xdd8b, NewIntrudeCamera }        // chara/others/intr_cam.c
#define CHARA_PANEL2            { 0xdd95, ? }                       // GV_StrCode("パネル２") takabe/panel2.c
#define CHARA_VRBOX_DF07        { 0xdf0f, ? }                       // GV_StrCode("ＶＲＢＯＸ") koba/vr/vrbox.c
#define CHARA_S11_OBJS          { 0xe068, s11g_s11_objs_800CB388 }  // okajima/s11_objs.c
#define CHARA_ELEVATOR_PANEL    { 0xe253, NewEvPanel }              // game/evpanel.c
#define CHARA_MERYL72           { 0xe271, NewMeryl72_800C7BC4 }     // animal/meryl72/meryl72.c
#define CHARA_RED_ALERT_E397    { 0xe397, NewRedAlert_800C4DF0 }    // okajima/red_alrt.c
#define CHARA_DOLL2             { 0xe448, ? }                       // takabe/doll2.c
#define CHARA_TORTURE           { 0xe608, NewTorture_800C6E1C }     // chara/torture/torture.c
#define CHARA_ED_TELOP          { 0xe75a, NewEdTelop_800C563C }     // takabe/ed_telop.c
#define CHARA_DOLL              { 0xe97e, NewDoll_800DCD78 }        // GV_StrCode("デモ人形") animal/doll/doll.c
#define CHARA_WALL              { 0xec77, NewWall_800C3718 }        // GV_StrCode("障害物") enemy/wall.c
#define CHARA_PAUSE             { 0xeced, s19b_asioto_800C4268 }    // --> menu/countdwn.c
#define CHARA_VR                { 0xed86, ? }                       // GV_StrCode("ＶＲ") koba/vr/vr.c
#define CHARA_ZAKO              { 0xed87, ? }                       // GV_StrCode("ざこ") animal/zako/zako.c
#define CHARA_PHOTOSEL          { 0xedeb, ? }                       // chara/photosel/photosel.c
#define CHARA_SCN_MARK          { 0xee63, NewScnMark_800C9580 }     // okajima/scn_mark.c
#define CHARA_WSURFACE          { 0xeea7, NewWsurface_800DB9BC }    // takabe/wsurface.c
#define CHARA_HAIR_N            { 0xf002, ? }                       // chara/others/hair_n.c
#define CHARA_REC_DEMO          { 0xf364, ? }                       // nobu/vr_demo/recdemo.c (PC-ONLY)
#define CHARA_MERYL07B          { 0xf4b0, ? }                       // GV_StrCode("サイコメリル") chara/meryl07b/meryl07b.c
#define CHARA_PUT_OBJECT        { 0xf4c3, NewPutObject_800E25C0 }   // takabe/put_obj.c
#define CHARA_SEARCH_LIGHT      { 0xf50f, NewSearchlight_800D92BC } // GV_StrCode("サーチライト") enemy/searchli.c
#define CHARA_BELONG            { 0xf59e, NewBelong }               // chara/others/belong.c
#define CHARA_UJI               { 0xf5c5, NewUji_800C42F8 }         // okajima/uji.c
#define CHARA_CHANGE            { 0xf722, NewChange }               // onoda/change/change.c
#define CHARA_BOXALL            { 0xf74b, NewBoxall_800CA088 }      // chara/torture/boxall.c
#define CHARA_MOVIE_FAA8        { 0xfaa8, ? }                       // chara/movie/movie.c
#define CHARA_FLR_SPA           { 0xfc0b, NewFlrSpa_800D0F78 }      // okajima/flr_spa.c
#define CHARA_POCKET_FDB6       { 0xfdb6, ? }                       // menu/pocket.c
#define CHARA_VIBRATE           { 0xfed1, NewVibration }            // GV_StrCode("パッド振動") game/vibrate.c

/*--- Polygon Demo Charas ---*/
#define CHARA_BLAST             { 0x0001, ? }                       // bullet/blast.c
#define CHARA_UNKNOWN_0002      { 0x0002, ? }                       // --> anime/animconv/anime.c
#define CHARA_FADEIO_0003       { 0x0003, NewFadeIo_800C4224 }      // takabe/fadeio.c
#define CHARA_FADEIO_0004       { 0x0004, NewFadeIo_800C4224 }      // takabe/fadeio.c
#define CHARA_TELOP_0005        { 0x0005, NewTelop_800DDD7C }       // takabe/telop.c
#define CHARA_UNKNOWN_0006      { 0x0006, ? }                       // --> anime/animconv/anime.c (PC-ONLY)
#define CHARA_UNKNOWN_0007      { 0x0007, ? }                       // --> anime/animconv/anime.c (PC-ONLY)
#define CHARA_UNKNOWN_0008      { 0x0008, ? }                       // --> anime/animconv/anime.c (PC-ONLY)
#define CHARA_BLOOD             { 0x0009, NewBlood }                // okajima/blood.c
#define CHARA_SPLASH            { 0x000a, NewSplash_800C8D6C }      // okajima/splash.c
#define CHARA_BULLET            { 0x000b, NewBulletEx }             // okajima/bullet.c
#define CHARA_UNKNOWN_000C      { 0x000c, ? }                       // --> anime/animconv/anime.c
#define CHARA_D_BLOODS          { 0x000d, NewDBloods_800D5B70 }     // okajima/d_bloods.c
#define CHARA_UNKNOWN_000E      { 0x000e, AN_Breath }               // --> anime/animconv/anime.c
#define CHARA_DEMOKAGE          { 0x000f, NewDemoKage_800C48A4 }    // enemy/demokage.c
#define CHARA_DEMOASI           { 0x0010, NewDemoasi_800C414C }     // enemy/demoasi.c
#define CHARA_UNKNOWN_0011      { 0x0011, s08c_800C4194 }           // --> anime/animconv/anime.c
#define CHARA_BUBBLE_T          { 0x0012, NewBubbleT_800DA380 }     // okajima/bubble_t.c
#define CHARA_BUBBLE_P          { 0x0013, NewBubbleP_800D9D94 }     // okajima/bubble_p.c
#define CHARA_SCOPE_0014        { 0x0014, NewScope }                // equip/scope.c
#define CHARA_GOGGLE            { 0x0015, NewGoggle }               // takabe/goggle.c
#define CHARA_GGLSIGHT          { 0x0016, NewGoggleSight }          // equip/gglsight.c
#define CHARA_GOGGLE_IR         { 0x0017, NewGoggleIr }             // takabe/goggleir.c
#define CHARA_GOGGLE_SIGHT      { 0x0018, NewGoggleSight }          // equip/gglsight.c
#define CHARA_UNKNOWN_0019      { 0x0019, ? }                       // --> anime/animconv/anime.c (PC-ONLY)
#define CHARA_KOGAKU2           { 0x001a, NewKogaku2 }              // equip/kogaku2.c
#define CHARA_KOGAKU3           { 0x001b, NewKogaku3 }              // equip/kogaku2.c
#define CHARA_ENVMAP3           { 0x001c, NewEnvmap3_800CA3A4 }     // takabe/envmap3.c
#define CHARA_PLASMA_001D       { 0x001d, ? }                       // okajima/plasma.c
#define CHARA_WINDCIRCLE        { 0x001e, NewWindcrcl_800CF6BC }    // takabe/windcrcl.c
#define CHARA_SEPIA_001F        { 0x001f, NewSepia_800C4F9C }       // takabe/sepia.c
#define CHARA_MGREXLZR          { 0x0020, ? }                       // kojo/mgrexlzr.c
#define CHARA_FOCUS             { 0x0021, NewFocus_800CEFF8 }       // takabe/focus.c
#define CHARA_GASMASK_SIGHT     { 0x0022, ? }                       // equip/gmsight.c
#define CHARA_D_BLOODS_0023     { 0x0023, ? }                       // okajima/d_bloods.c
#define CHARA_PLASMA_0024       { 0x0024, ? }                       // okajima/plasma.c
#define CHARA_BLOOD_BL          { 0x0025, NewBlur_800CD530 }        // okajima/blood_bl.c
#define CHARA_UNKNOWN_0026      { 0x0026, ? }                       // --> anime/animconv/anime.c (PC-ONLY)
#define CHARA_UNKNOWN_0027      { 0x0027, ? }                       // --> anime/animconv/anime.c
#define CHARA_SEPIA_0028        { 0x0028, NewSepia_800C5214 }       // takabe/sepia.c
#define CHARA_RFSIGHT           { 0x0029, ? }                       // weapon/rfsight.c (PC-ONLY)
#define CHARA_UNKNOWN_002A      { 0x002a, ? }                       // ???
#define CHARA_D_BLOODS_002B     { 0x002b, NewDBloods_800D5B70 }     // okajima/d_bloods.c
#define CHARA_SIGHT             { 0x002c, ? }                       // thing/sight.c (PC-ONLY)
#define CHARA_KATANA            { 0x002d, NewKatana_800C5660 }      // enemy/katana.c
#define CHARA_SUB_ROOM          { 0x002e, NewSubRoom_800C815C }     // okajima/sub_room.c
#define CHARA_UNKNOWN_002F      { 0x002f, AN_Smoke_800CE164 }       // ???
#define CHARA_BLST_LN           { 0x0030, ? }                       // okajima/blst_ln.c
#define CHARA_SMKE_LN           { 0x0031, NewSmokeLn_800CDFA4 }     // okajima/smke_ln.c
#define CHARA_M1E1SMKE          { 0x0032, ? }                       // kojo/m1e1smke.c
#define CHARA_UNKNOWN_0033      { 0x0033, demothrd_2_8007DA94 }     // --> anime/animconv/anime.c
#define CHARA_UNKNOWN_0034      { 0x0034, ? }                       // --> anime/animconv/anime.c (PC-ONLY)
#define CHARA_UNKNOWN_0035      { 0x0035, NewAnime_8005E574 }       // --> anime/animconv/anime.c
#define CHARA_UNKNOWN_0036      { 0x0036, NewAnime_8005E6A4 }       // --> anime/animconv/anime.c
#define CHARA_RED_ALERT_0037    { 0x0037, NewRedAlert2_800C4E84 }   // okajima/red_alrt.c
#define CHARA_RED_ALERT_0038    { 0x0038, RedAlert_800C4F48 }       // okajima/red_alrt.c
#define CHARA_CRSH_SMK          { 0x0039, ? }                       // okajima/crsh_smk.c
#define CHARA_CELOFAN           { 0x003a, ? }                       // kojo/celofan.c (PC-ONLY)
#define CHARA_INVERLT           { 0x003b, ? }                       // kojo/inverlt.c
#define CHARA_SPARK2            { 0x003c, NewSpark2_800CA714 }      // takabe/spark2.c
#define CHARA_SPARK             { 0x003d, NewSpark }                // okajima/spark.c
#define CHARA_UNKNOWN_003E      { 0x003e, ? }                       // --> anime/animconv/anime.c
#define CHARA_INVERLT2          { 0x003f, NewInverlt2_800D0FF4 }    // kojo/inverlt2.c
#define CHARA_CELOFAN2          { 0x0040, ? }                       // kojo/celofan2.c (PC-ONLY)
#define CHARA_NINJALZR          { 0x0041, ? }                       // kojo/ninjalzr.c
#define CHARA_GAS_EFCT          { 0x0042, NewGasEffect_800C4EF8 }   // takabe/gas_efct.c
#define CHARA_SUB_EFFECT        { 0x0043, NewSubEfct_800CCB10 }     // takabe/sub_efct.c
#define CHARA_BLURPURE          { 0x0044, NewBlurPure_800C54D4 }    // okajima/blurpure.c
#define CHARA_FAMASLIT          { 0x0045, NewFamasLight }           // kojo/famaslit.c
#define CHARA_REALSHDW          { 0x0046, ? }                       // takabe/realshdw.c (PC-ONLY)
#define CHARA_BLOOD_HZD         { 0x0047, ? }                       // kojo/bloodhzd.c
#define CHARA_BLOOD_DRP         { 0x0048, ? }                       // kojo/blooddrp.c
#define CHARA_WINDCRCL_0049     { 0x0049, ? }                       // takabe/windcrcl.c
#define CHARA_BOMBLED           { 0x004a, NewBombLed }              // animal/liquid/bombled.c
#define CHARA_METAL_GEAR_ROOM   { 0x004b, NewMgRoom_800DB458 }      // okajima/mg_room.c
#define CHARA_TELOP_004C        { 0x004c, NewTelop2_800DDC60 }      // takabe/telop.c

/*---------------------------------------------------------------------------*/
/*  NEWCHARA external declarations                                           */
/*---------------------------------------------------------------------------*/

// XXX You CAN NOT let any code that knows the real signatures of these
// XXX functions see these prototypes!! These declarations are meant to
// XXX match the signature of NEWCHARA so we can compile CHARA tables
// XXX without warnings about incompatible pointer types.
// XXX
// XXX TODO: Include all the proper headers and pre-emptively cast the
// XXX CHARA.func fields to (NEWCHARA) in the defines section above.
// XXX
// XXX Or just leave it since nobody has the patience for that...

void *AN_Breath();                      /* --> anime/animconv/anime.c   */
void *AN_Smoke_800CE164();              /* --> anime/animconv/anime.c   */
void *NewAnime_8005E574();              /* --> anime/animconv/anime.c   */
void *NewAnime_8005E6A4();              /* --> anime/animconv/anime.c   */
void *demothrd_2_8007DA94();            /* --> anime/animconv/anime.c   */
void *s08c_800C4194();                  /* --> anime/animconv/anime.c   */
void *s11d_rope_800C9500();             /* --> chara/rope/rope.c        */
void *s19b_asioto_800C4268();           /* --> menu/countdwn.c          */
void *NewCamera_800CF388();             /* ???/camera.c                 */
void *NewDoll_800DCD78();               /* animal/doll/doll.c           */
void *NewBombLed();                     /* animal/liquid/bombled.c      */
void *NewMeryl72_800C7BC4();            /* animal/meryl72/meryl72.c     */
void *d18a_snake18_800D4E94();          /* animal/snake18/snake18.c     */
void *s11e_zako11e_800D42E0();          /* animal/zako11e/zako11e.c     */
void *NewZakoCommander_800DAF38();      /* animal/zako11e/zk11ecom.c    */
void *NewZako11F();                     /* animal/zako11f/zako11f.c     */
void *NewZakoCommander_800D20D8();      /* animal/zako11f/zk11fcom.c    */
void *NewScenarioJirai();               /* bullet/jirai.c               */
void *NewHind_800D1224();               /* chara/hind/hind.c            */
void *s11d_hind_800CB708();             /* chara/hind/hind.c            */
void *NewHind2();                       /* chara/hind2/hind2.c          */
void *NewBelong();                      /* chara/others/belong.c        */
void *NewFonttext_800C446C();           /* chara/others/fonttext.c      */
void *NewIntrudeCamera();               /* chara/others/intr_cam.c      */
void *NewMotionSoundEffect();           /* chara/others/motse.c         */
void *s11d_dsmoke2_800CCD54();          /* chara/rope/dsmoke2.c         */
void *s11d_landing_800CDA20();          /* chara/rope/landing.c         */
void *NewPipe_800CE73C();               /* chara/rope/pipe.c            */
void *NewBreath_800C3A1C();             /* chara/snake/breath.c         */
void *NewSnake();                       /* chara/snake/sna_init.c       */
void *NewBed_800C70DC();                /* chara/torture/bed.c          */
void *NewBoxall_800CA088();             /* chara/torture/boxall.c       */
void *NewJohnny_800CA838();             /* chara/torture/johnny.c       */
void *NewNinja_800CC9B4();              /* chara/torture/ninja.c        */
void *NewOtacom_800CC030();             /* chara/torture/otacom.c       */
void *NewRevolver_800C929C();           /* chara/torture/revolver.c     */
void *NewSnake03c1_800CDAEC();          /* chara/torture/sne_03c.c      */
void *NewSnake03c2_800CDF18();          /* chara/torture/sne_03c.c      */
void *NewTorture_800C6E1C();            /* chara/torture/torture.c      */
void *NewWake_800C6298();               /* chara/wake/wake.c            */
void *NewAsiatoKun_800D1A70();          /* enemy/asiato.c               */
void *NewAsioto_800C3E08();             /* enemy/asioto.c               */
void *NewCamera_800D67F8();             /* enemy/camera.c               */
void *NewCommand_800D0908();            /* enemy/command.c              */
void *NewDemoasi_800C414C();            /* enemy/demoasi.c              */
void *NewDemoKage_800C48A4();           /* enemy/demokage.c             */
void *NewKatana_800C5660();             /* enemy/katana.c               */
void *NewKiken_800D6D24();              /* enemy/kiken.c                */
void *NewEnemyMeryl_800D63A4();         /* enemy/meryl7.c               */
void *NewObjectChara_800DA3A4();        /* enemy/object.c               */
void *NewSearchlight_800D92BC();        /* enemy/searchli.c             */
void *NewSmoke_800D2BEC();              /* enemy/smoke.c                */
void *NewWall_800C3718();               /* enemy/wall.c                 */
void *NewSnakeWatcher_800C5034();       /* enemy/watcher.c              */
void *NewGoggleSight();                 /* equip/gglsight.c             */
void *NewKogaku2();                     /* equip/kogaku2.c              */
void *NewKogaku3();                     /* equip/kogaku2.c              */
void *NewScope();                       /* equip/scope.c                */
void *NewCancel();                      /* game/cancel.c                */
void *NewEvPanel();                     /* game/evpanel.c               */
void *NewItem();                        /* game/item.c                  */
void *NewLamp();                        /* game/lamp.c                  */
void *NewMovieGCL();                    /* game/movie.c                 */
void *NewPad();                         /* game/pad.c                   */
void *NewPoint();                       /* game/point.c                 */
void *GM_SetSecondAvailable();          /* game/second.c                */
void *NewSelect();                      /* game/select.c                */
void *NewSoundTest();                   /* game/sndtst.c                */
void *NewToBeContinued();               /* game/tobcnt.c                */
void *NewVibration();                   /* game/vibrate.c               */
void *NewVrwindow_800D81AC();           /* koba/vr/vrwindow.c           */
void *NewFamasLight();                  /* kojo/famaslit.c              */
void *NewInverlt2_800D0FF4();           /* kojo/inverlt2.c              */
void *NewSnowStorm();                   /* kojo/sstorm.c                */
void *s11g_11g_demo_800CCB48();         /* okajima/11g_demo.c           */
void *NewBlinkTx_800DECD8();            /* okajima/blink_tx.c           */
void *NewBlood();                       /* okajima/blood.c              */
void *NewBloodBl_800CD7CC();            /* okajima/blood_bl.c           */
void *NewBlur_800CD530();               /* okajima/blood_bl.c           */
void *NewBloodCl_800C9DF0();            /* okajima/blood_cl.c           */
void *NewBlurPure_800C54D4();           /* okajima/blurpure.c           */
void *NewBubbleDisplayScene_800D90B4(); /* okajima/bub_d_sn.c           */
void *NewBubbleP_800D9D94();            /* okajima/bubble_p.c           */
void *NewBubbleS_800D5D9C();            /* okajima/bubble_s.c           */
void *NewBubbleT_800DA380();            /* okajima/bubble_t.c           */
void *NewBulletEx();                    /* okajima/bullet.c             */
void *NewCrane_800D57A0();              /* okajima/crane.c              */
void *NewDBloods_800D5B70();            /* okajima/d_bloods.c           */
void *NewDeathSp_800D025C();            /* okajima/death_sp.c           */
void *NewDog_800D33C8();                /* okajima/dog/dog.c            */
void *NewDuctmouse_800DACC8();          /* okajima/ductmous.c           */
void *NewFallSplash();                  /* okajima/fall_spl.c           */
void *NewFlrSpa_800D0F78();             /* okajima/flr_spa.c            */
void *NewGunCame_800C9190();            /* okajima/guncame.c            */
void *NewHiyoko_800D018C();             /* okajima/hiyoko.c             */
void *NewItemDot_800CC7D0();            /* okajima/item_dot.c           */
void *NewKeyItem_800C8E18();            /* okajima/key_item.c           */
void *NewMgRoom_800DB458();             /* okajima/mg_room.c            */
void *NewMouse_800D5234();              /* okajima/mouse.c              */
void *NewPLamp_800CD948();              /* okajima/p_lamp.c             */
void *NewPatrolLamp_800D7A2C();         /* okajima/pato_lmp.c           */
void *NewPlasma_800CD110();             /* okajima/plasma.c             */
void *NewRedAlert2_800C4E84();          /* okajima/red_alrt.c           */
void *NewRedAlert_800C4DF0();           /* okajima/red_alrt.c           */
void *RedAlert_800C4F48();              /* okajima/red_alrt.c           */
void *s11g_s11_objs_800CB388();         /* okajima/s11_objs.c           */
void *NewScnMark_800C9580();            /* okajima/scn_mark.c           */
void *NewSmokeLn_800CDFA4();            /* okajima/smke_ln.c            */
void *NewSmktrgt_800DC410();            /* okajima/smktrgt.c            */
void *NewSpark();                       /* okajima/spark.c              */
void *NewSplash_800C8D6C();             /* okajima/splash.c             */
void *NewSubRoom_800C815C();            /* okajima/sub_room.c           */
void *NewUji_800C42F8();                /* okajima/uji.c                */
void *NewCrow_800DED08();               /* okajima/valcan/crow.c        */
void *s15c_dyncon_800D8C9C();           /* okajima/valcan/dyncon.c      */
void *NewWallSpa_800CB4A4();            /* okajima/wall_spa.c           */
void *NewWolf2();                       /* okajima/wolf/wolf2.c         */
void *NewChange();                      /* onoda/change/change.c        */
void *Safety_800C47A0();                /* onoda/change/safety.c (?)    */
void *NewDemoSelect();                  /* onoda/demosel/demosel.c      */
void *NewOpen_800D6814();               /* onoda/open/open.c            */
void *NewOption_800C9344();             /* onoda/option/opt.c           */
void *NewPreviousOperation();           /* onoda/preope/preope.c        */
void *NewAt_800D78A4();                 /* onoda/s04b/at.c              */
void *NewCape_800D92F8();               /* onoda/s04b/cape.c            */
void *s04c_revolver_800D2028();         /* onoda/s04b/revolver.c        */
void *NewWire_800D709C();               /* onoda/s04b/wire.c            */
void *NewBreakObject();                 /* takabe/breakobj.c            */
void *NewCameraShake();                 /* takabe/camshake.c            */
void *NewZoom_800DFA88();               /* takabe/cat_in.c              */
void *NewCinemaScreenSet();             /* takabe/cinema.c              */
void *NewDoor2_800DD9E4();              /* takabe/door2.c               */
void *NewDummyFloor_800D6BF8();         /* takabe/dummy_fl.c            */
void *NewDummyWall_800D7384();          /* takabe/dummy_wl.c            */
void *s15c_dymc_flr_800E1C70();         /* takabe/dymc_flr.c            */
void *NewDymcSeg_800C4BCC();            /* takabe/dymc_seg.c            */
void *NewEdTelop_800C563C();            /* takabe/ed_telop.c            */
void *EdTelop_800C4F18();               /* takabe/ed_telop.c (?)        */
void *NewElcDamg_800D4C68();            /* takabe/elc_damg.c            */
void *NewElcFlr_800D4A18();             /* takabe/elc_flr.c             */
void *NewElevator_800D9F30();           /* takabe/elevator.c            */
void *NewEnding2_800C7BE8();            /* takabe/ending2.c             */
void *NewEnvSnd_800DF424();             /* takabe/env_snd.c             */
void *NewEnvmap3_800CA3A4();            /* takabe/envmap3.c             */
void *NewFadeIo_800C4224();             /* takabe/fadeio.c              */
void *NewFadeIo_800C42BC();             /* takabe/fadeio.c              */
void *NewFindTrap_800D77DC();           /* takabe/findtrap.c            */
void *NewFocus_800CEFF8();              /* takabe/focus.c               */
void *NewFog_800D4208();                /* takabe/fog.c                 */
void *NewFurnace();                     /* takabe/furnace.c             */
void *NewGasEffect_800C4E5C();          /* takabe/gas_efct.c            */
void *NewGasEffect_800C4EF8();          /* takabe/gas_efct.c            */
void *NewGasDamage_800E14E8();          /* takabe/gasdamge.c            */
void *NewGlass_800D37A4();              /* takabe/glass.c               */
void *NewGoggle();                      /* takabe/goggle.c              */
void *NewGoggleIr();                    /* takabe/goggleir.c            */
void *NewIrCens_800DA66C();             /* takabe/ir_cens.c             */
void *s19b_jdrum_800C95E4();            /* takabe/jeep/jdrum.c          */
void *s19b_jeep_emy_800C4EC0();         /* takabe/jeep_emy/jeep_emy.c   */
void *s19b_jeep_srl_800CE36C();         /* takabe/jeep_srl.c            */
void *NewLifeUp_800DF428();             /* takabe/life_up.c             */
void *NewLift_800DE25C();               /* takabe/lift.c                */
void *NewMirror_800E085C();             /* takabe/mirror.c              */
void *NewMosaic_800DCABC();             /* takabe/mosaic.c              */
void *NewO2Damage_800DE9C8();           /* takabe/o2_damge.c            */
void *NewPadDemo();                     /* takabe/pad_demo.c            */
void *NewPanel_800D2680();              /* takabe/panel.c               */
void *NewPutObject_800E25C0();          /* takabe/put_obj.c             */
void *NewRasen2_800CB008();             /* takabe/rasen.c               */
void *NewRasenEl_800CCF38();            /* takabe/rasen_el.c            */
void *NewRipples_800D872C();            /* takabe/ripples.c             */
void *NewRippleSurface_800D8244();      /* takabe/rsurface.c            */
void *NewSepia_800C4F9C();              /* takabe/sepia.c               */
void *NewSepia_800C5214();              /* takabe/sepia.c               */
void *NewShakemdl_800C54E8();           /* takabe/shakemdl.c            */
void *NewShuter_800DFB44();             /* takabe/shuter.c              */
void *NewSpark2_800CA714();             /* takabe/spark2.c              */
void *NewSubEfct_800CCB10();            /* takabe/sub_efct.c            */
void *NewTelop2_800DDC60();             /* takabe/telop.c               */
void *NewTelopSet_800DDB34();           /* takabe/telop.c               */
void *NewTelop_800DDD7C();              /* takabe/telop.c               */
void *NewTexScroll();                   /* takabe/tex_scrl.c            */
void *NewTruckTrap();                   /* takabe/tracktrp.c            */
void *NewVibEdit_800C47B4();            /* takabe/vib_edit.c            */
void *NewVoicesys_800CE944();           /* takabe/voicesys.c            */
void *NewWindcrcl_800CF6BC();           /* takabe/windcrcl.c            */
void *NewWsurface_800DB9BC();           /* takabe/wsurface.c            */
void *NewWaterArea();                   /* takabe/wt_area.c             */
void *NewWaterArea2();                  /* takabe/wt_area2.c            */
void *NewWaterView();                   /* takabe/wt_view.c             */
void *NewDoor();                        /* thing/door.c                 */
void *NewEmitter();                     /* thing/emitter.c              */
void *NewSnow();                        /* thing/snow.c                 */
void *NewSphere();                      /* thing/sphere.c               */

#endif // __MGS_CHARALST_H__
