#define DECLARE_NEWCHARA_PROTOS
#include "charalst.h"

/* not listed in charalst.h yet */
extern NEWCHARA NewPlasma_800CD268;     /* okajima/plasma.c */
extern NEWCHARA AN_Smoke_800CE0F8;      /* (black smoke) */
extern NEWCHARA NewBlastLine;           /* okajima/blst_ln.c */
extern NEWCHARA AN_Blast_high2;         /* bullet/blast.c */
extern NEWCHARA NewNinjaLaser;          /* kojo/ninjalzr.c */
extern NEWCHARA NewBloodHazard;         /* kojo/bloodhzd.c */
extern NEWCHARA NewWindcrcl_800CF784;   /* takabe/windcrcl.c */

CHARA _StageCharacterEntries[] = {
    CHARA_ASIOTOKUN,    /* chara 足音君 */
    CHARA_MGREX,
    CHARA_MG_DEMO1,
    CHARA_VOICESYS,     /* chara 音声制御 */
    CHARA_WALL,         /* chara 障害物 */
    CHARA_DRUMCAN2,     /* chara ドラム缶２ */
    CHARA_CINEMA,       /* chara シネマスクリーン */
    CHARA_FADEIO,       /* chara フェードイン・アウト */
    CHARA_TEXTURE,      /* chara テクスチャ */
    CHARA_BREAK_OBJECT,
    CHARA_PUTHZD,

    DEMO_EXPLOSION,
    DEMO_FADEIN,
    DEMO_FADEOUT,
    DEMO_BLOOD,
    DEMO_BLOOD2,
    DEMO_BULLET,
    DEMO_BLOODCIRCLE,
    DEMO_SHADOW,
    DEMO_PLASMA,
    DEMO_METALGEARLASER,
    { 0x0024, NewPlasma_800CD268 }, //  DEMO_PLASMA2,
    DEMO_BLUR,
    DEMO_MONOTONE,
    { 0x002a, AN_Smoke_800CE0F8 }, //  DEMO_BLACKSMOKE,
    { 0x0030, NewBlastLine }, //  DEMO_BLASTLINE,
    DEMO_SMOKELINE,
    DEMO_ENVIRONMENTLIGHT,
    DEMO_ENVIRONMENTLIGHT2,
    DEMO_CRASHSMOKE,
    DEMO_INVERSLIGHT,
    DEMO_SPACK,
    DEMO_SPACK2,
    { 0x003e, AN_Blast_high2 }, //  DEMO_STEAMEXPLOSION,
    DEMO_INVERSLIGHT2,
    { 0x0041, NewNinjaLaser }, //  DEMO_NINJALASER,
    DEMO_GHOST,
    { 0x0047, NewBloodHazard }, //  DEMO_BLOODHAZARD,
    DEMO_BLOODDRIP,
    { 0x0049, NewWindcrcl_800CF784 }, //  DEMO_NINJAGROUND,

    CHARA_END
};
