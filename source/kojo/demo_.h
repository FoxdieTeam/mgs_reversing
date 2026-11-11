#ifndef _INC_DEMO_
#define _INC_DEMO_

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/******************************************************************************
 * included
 */

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

#include "define.h"

/******************************************************************************
 * definitions and typedefs and structures
 */

#define IDMODEL_CACHEEFFECT     GV_CacheID2("null", 'k')
#define IDMODEL_EFFECT          GV_StrCode("null")

#define IDMODEL_M1E1DEMO        GV_StrCode("m1e1demo")
#define IDMODEL_MI24HINDDEMO    GV_StrCode("hinddemo")

/* no shade model */
#define IDMODEL_16O4A   GV_StrCode("16d_o4a")
#define IDMODEL_16O5A   GV_StrCode("16d_o5a")
#define IDMODEL_16O6A   GV_StrCode("16d_o6a")
#define IDMODEL_16O7A   GV_StrCode("16d_o7a")
#define IDMODEL_16O8A   GV_StrCode("16d_o8a")
#define IDMODEL_16O9A   GV_StrCode("16d_o9a")
#define IDMODEL_16O10A  GV_StrCode("16d_o10a")
#define IDMODEL_16O4B   GV_StrCode("16d_o4b")
#define IDMODEL_16O5B   GV_StrCode("16d_o5b")
#define IDMODEL_16O6B   GV_StrCode("16d_o6b")
#define IDMODEL_16O7B   GV_StrCode("16d_o7b")
#define IDMODEL_16O8B   GV_StrCode("16d_o8b")
#define IDMODEL_16O9B   GV_StrCode("16d_o9b")
#define IDMODEL_16O10B  GV_StrCode("16d_o10b")
#define IDMODEL_16O4C   GV_StrCode("16d_o4c")
#define IDMODEL_16O5C   GV_StrCode("16d_o5c")
#define IDMODEL_16O6C   GV_StrCode("16d_o6c")
#define IDMODEL_16O7C   GV_StrCode("16d_o7c")
#define IDMODEL_16O8C   GV_StrCode("16d_o8c")
#define IDMODEL_16O9C   GV_StrCode("16d_o9c")
#define IDMODEL_16O10C  GV_StrCode("16d_o10c")
#define IDMODEL_02A_R8  GV_StrCode("02a_r8")

#define EFFECT_EXPLOSION             1
#define EFFECT_SMOKE                 2
#define EFFECT_FADEIN                3
#define EFFECT_FADEOUT               4
#define EFFECT_TEXT                  5
#define EFFECT_SURPRISEDMARK         6
#define EFFECT_QUESTIONMARK          7
#define EFFECT_SLEEPMARK             8
#define EFFECT_BLOOD                 9
#define EFFECT_BULLET               10
#define EFFECT_MISSILESMOKE         11
#define EFFECT_BLOODCIRCLE          12
#define EFFECT_BREATH               13
#define EFFECT_SHADOW               14
#define EFFECT_FOOTPRINTS           15
#define EFFECT_MESSAGE              16
#define EFFECT_NINJAEYE             17
#define EFFECT_BUBBLE               18
#define EFFECT_SCOPE                19
#define EFFECT_DARKVISIBLEGOGGLE    20
#define EFFECT_IRRAYSGOGGLE         21
#define EFFECT_GUNSMOKE             22
#define EFFECT_OPTICSCAMOUFLAGE     23
#define EFFECT_ENVIRONMENTMAPPING   24
#define EFFECT_PLASMA               25
#define EFFECT_WINDCIRCLE           26
#define EFFECT_SEPIA                27
#define EFFECT_METALGEARLASER       28
#define EFFECT_UNSHAPEVIEW          29
#define EFFECT_GUSMASK              30
#define EFFECT_STOP                 31
#define EFFECT_URINATIONCIRCLE      32
#define EFFECT_PLASMA2              33
#define EFFECT_BLUR                 34
#define EFFECT_STEAMSMOKE           35
#define EFFECT_MONOTONE             36
#define EFFECT_RIFLESIGHT           37
#define EFFECT_MI24HIND             38
#define EFFECT_BLACKSMOKE           39
#define EFFECT_URINATIONCIRCLE2     40
#define EFFECT_SIGHT                41
#define EFFECT_NINJASWORD           42
#define EFFECT_SUBMARINEROOM        43
#define EFFECT_BLACKSMOKE2          44
#define EFFECT_BLASTLINE            45
#define EFFECT_SMOKELINE            46
#define EFFECT_SHELLSMOKE           47
#define EFFECT_CATERPILLERSMOKE     48
#define EFFECT_CROWEYE              49
#define EFFECT_OCEROTTEBULLETFIRE   50
#define EFFECT_OCEROTTEBULLETSMOKE  51
#define EFFECT_ENVIRONMENTLIGHT     52
#define EFFECT_CRASHSMOKE           53
#define EFFECT_PADVIBRATION         54
#define EFFECT_CELOFAN              55
#define EFFECT_INVERSLIGHT          56
#define EFFECT_SPACK                57
#define EFFECT_STEAMEXPLOSION       58
#define EFFECT_INVERSLIGHT2         59
#define EFFECT_CELOFAN2             60
#define EFFECT_NINJALASER           61
#define EFFECT_GUSEFFECT            62
#define EFFECT_SUBMARINEWATER       63
#define EFFECT_PADVIBRATION2        64
#define EFFECT_GHOST                65
#define EFFECT_LIGHT                66
#define EFFECT_FAMASLIGHT           67
#define EFFECT_HUMANSHADOW          68
#define EFFECT_BLOODHAZARD          69
#define EFFECT_BLOODDRIP            70
#define EFFECT_NINJAGROUND          71
#define EFFECT_BOMBLIGHT            72
#define EFFECT_MGCROOMDISPLAY       73
#define EFFECT_TEXT2                74

/***** XXX *****/
typedef struct tagMGSDEMOM1E1
{
    OBJECT  object[2][3];
    int     field_558_idx[2];
    int     field_560;
    SVECTOR field_564[2];
} MGSDEMOM1E1, *PMGSDEMOM1E1, *LPMGSDEMOM1E1;

typedef struct tagMGSDEMOHIND
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
} MGSDEMOHIND, *PMGSDEMOHIND, *LPMGSDEMOHIND;
/***** XXX *****/

typedef struct tagMGSDEMOSTAGE  /* stage */
{
    int nCacheID;   /**/
    int nStrCode;   /**/
} MGSDEMOSTAGE, *PMGSDEMOSTAGE, *LPMGSDEMOSTAGE;

#define MGS_SCENETOSTAGE 0x00000001

typedef struct tagMGSDEMOSCENE  /* scene */
{
    int   nID;      /**/
    DWORD dwStyle;  /**/
    int   nCacheID; /**/
    int   nStrCode; /**/
    int   nName;    /**/
} MGSDEMOSCENE, *PMGSDEMOSCENE, *LPMGSDEMOSCENE;

typedef struct tagMGSDEMO   /* demo header */
{
    u_int          nSize;           /**/
    int            nTime;           /**/
    int            nFrameCount;     /**/
    int            nStageCount;     /**/
    int            nSceneCount;     /**/
    LPMGSDEMOSTAGE lpStage;         /**/
    LPMGSDEMOSCENE lpScene;         /**/
} MGSDEMO, *PMGSDEMO, *LPMGSDEMO;

typedef struct tagMGSDEMOEFFECT
{
    int       nID;          /**/
    int       nEffectID;    /**/
    SVECTOREX svectRotate;  /**/
    SVECTOREX svectMove;    /**/
//  BYTE      byBuffer[32]; /**/
    int       field_14_type;  // TODO: Replace
    int       field_18_xy;    // TODO: Replace
    int       field_1C_zpad;  // TODO: Replace
    BYTE      dummy2[20];     // TODO: Replace
} MGSDEMOEFFECT, *PMGSDEMOEFFECT, *LPMGSDEMOEFFECT;

typedef struct tagMGSDEMOEFFECTACT
{
    void*         lpPrevious;   /**/
    void*         lpNext;       /**/
    BOOL          bCheck;       /**/
    void*         lpActor;      /**/
    void*         lpActor2;     /**/
    MGSDEMOEFFECT effect;       /**/
    int           nParam1;      /**/
    int           nParam2;      /**/
    SVECTOR       svect1;       /**/
    MATRIX        matrix;       /**/
} MGSDEMOEFFECTACT, *PMGSDEMOEFFECTACT, *LPMGSDEMOEFFECTACT;

typedef struct tagMGSDEMOSCENEMOTION
{
    int        nSceneID;        /**/
    short      bPreview;        /**/
    SVECTOREX  svectRotate;     /**/
    SVECTOREX  svectMove;       /**/
    short      nRotateCount;    /**/
    SVECTOREX* lpsvectRotate;   /**/
} MGSDEMOSCENEMOTION, *PMGSDEMOSCENEMOTION, *LPMGSDEMOSCENEMOTION;

typedef struct tagMGSDEMOFRAME
{
    u_int                nSize;             /**/
    int                  nTime;             /**/
    SVECTOREX            svectCamera;       /**/
    SVECTOREX            svectTarget;       /**/
    short                nZRotate;          /**/
    short                nScreen;           /**/
    short                nEffectCount;      /**/
    LPMGSDEMOEFFECT      lpEffect;          /**/
    short                nSMotionCount;     /**/
    LPMGSDEMOSCENEMOTION lpSMotion;         /**/
} MGSDEMOFRAME, *PMGSDEMOFRAME, *LPMGSDEMOFRAME;

typedef struct tagMGSDEMOMODEL
{
    CONTROL    control;     /**/
    OBJECT     object;      /**/
    MATRIX     light[2];    /**/
    MGSDEMOM1E1 *lpData; // TODO: void*
} MGSDEMOMODEL, *PMGSDEMOMODEL, *LPMGSDEMOMODEL;

typedef struct tagMGSDEMOACT
{
    GV_ACT              actor;              /**/
    DWORD               dwStyle;            /**/
    int                 nVSync;             /**/
    int                 nMap;               /**/
    int                 nTime;              /**/
    LPMGSDEMO           lpDemo;             /**/
    LPMGSDEMOMODEL      lpModel;            /**/
    void*               lpEffectPrevious;   /**/
    void*               lpEffectNext;       /**/
    char                szPath[128];        /**/
    LPMGSDEMO           lpExtMemory;        /**/
    MGSDEMOMODEL        modelEffect;        /**/
    BOOL                bEffectStop;        /**/
    BOOL                bEffectBubbleStop;  /**/
    DG_CHANLFUNC        lpfnDGScreenChanl;  /**/
    int                 nGameStatus;        /**/
    GM_CameraSystemWork GMCameraSave;       /**/
    int                 nItemSave;          /**/
    int                 nWeaponSave;        /**/
} MGSDEMOACT, *PMGSDEMOACT, *LPMGSDEMOACT;

/***** XXX *****/
/***** XXX *****/

typedef struct tagMGSDEMOEFFECT_
{
    int       nID;          /**/
    int       nEffectID;    /**/
    SVECTOREX svectRotate;  /**/
    SVECTOREX svectMove;    /**/
//  BYTE      byBuffer[32]; /**/
    union {
        struct {
            int   field_14;
            short field_18;
        } variant_0x3;  // EFFECT_FADEIN --> EFFECTFADEINOUT

        struct {
            int   field_14;
            short field_18;
        } variant_0x4;  // EFFECT_FADEOUT --> EFFECTFADEINOUT

        struct {
            int   field_14;
            short field_18;
            short field_1A;
            int   field_1C;
        } variant_0x5;  // EFFECT_TEXT

        struct {
            short field_14;
        } variant_0x6;  // EFFECT_SURPRISEDMARK

        struct {
            short field_14;
        } variant_0x7;  // EFFECT_QUESTIONMARK

        struct {
            short field_14;
        } variant_0x9;  // EFFECT_BLOOD

        struct {
            int   field_14;
            short field_18;
            short field_1A;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
            short field_24;
        } variant_0xA;  // EFFECT_BULLET

        struct {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
        } variant_0xC;  // EFFECT_BLOODCIRCLE

        struct {
            int     field_14;
            SVECTOR field_18;
            short   field_20;
            short   field_22;
            short   field_24;
            short   field_26;
        } variant_0xE;  // EFFECT_SHADOW

        struct {
            short field_14;
        } variant_0xF;  // EFFECT_FOOTPRINTS

        struct {
            int address;
            int message[7];
        } variant_0x10; // EFFECT_MESSAGE

        struct {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            int   field_1C;
            int   field_20;
            short field_24;
            short field_26;
            short field_28;
            short field_2A;
        } variant_0x12; // EFFECT_BUBBLE

        struct {
            short field_14;
        } variant_0x13; // EFFECT_SCOPE

        struct {
            short field_14;
            short field_16;
        } variant_0x14; // EFFECT_DARKVISIBLEGOGGLE

        struct {
            short field_14;
            short field_16;
        } variant_0x15; // EFFECT_IRRAYSGOGGLE

        struct {
            short field_14;
            short field_16;
            int   field_18;
            short field_1C;
        } variant_0x17; // EFFECT_OPTICSCAMOUFLAGE

        struct {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
        } variant_0x18; // EFFECT_ENVIRONMENTMAPPING

        struct {
            int   field_14;
            short field_18;
            short field_1A;
            int   field_1C;
            short field_20;
        } variant_0x19; // EFFECT_PLASMA

        struct {
            int field_14;
        } variant_0x1A; // EFFECT_WINDCIRCLE

        struct {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
        } variant_0x1B; // EFFECT_SEPIA

        struct {
            SVECTOREX svectMove;
            SVECTOREX svectRotate;
        } variant_0x1C; // EFFECT_METALGEARLASER --> EFFECTMETALGEARLASER

        struct {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
        } variant_0x1D; // EFFECT_UNSHAPEVIEW

        struct {
            short field_14;
        } variant_0x1E; // EFFECT_GUSMASK

        struct {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
            short field_20;
        } variant_0x20; // EFFECT_URINATIONCIRCLE -- > EFFECTURINATIONCIRCLE

        struct {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            int   field_1C;
        } variant_0x21; // EFFECT_PLASMA2

        struct {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
        } variant_0x22; // EFFECT_BLUR

        struct {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            short field_1C;
            short field_1E;
            int   field_20;
        } variant_0x23; // EFFECT_STEAMSMOKE

        struct {
            short field_14;
        } variant_0x24; // EFFECT_MONOTONE

        struct {
            short field_14;
        } variant_0x25; // EFFECT_RIFLESIGHT

        struct {
            DG_OBJS *field_14;
            int      field_18;
        } variant_0x26; // EFFECT_MI24HIND

        struct {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
        } variant_0x28; // EFFECT_URINATIONCIRCLE2

        struct {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            int   field_1C;
        } variant_0x29; // EFFECT_SIGHT

        struct {
            int   field_14;
            short field_18;
        } variant_0x2A; // EFFECT_NINJASWORD

        struct {
            short field_14;
        } variant_0x2B; // EFFECT_SUBMARINEROOM

        struct {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            short field_1C;
        } variant_0x2C; // EFFECT_BLACKSMOKE2

        struct {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            int   field_1C;
            short field_20;
            short field_22;
        } variant_0x2D; // EFFECT_BLASTLINE

        struct {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            short field_1C;
            short field_1E;
            int   field_20;
            short field_24;
            short field_26;
            short field_28;
            short field_2A;
            short field_2C;
        } variant_0x2E; // EFFECT_SMOKELINE

        struct {
            short field_14;
        } variant_0x2F; // EFFECT_SHELLSMOKE

        struct {
            int   field_14;
            int   field_18;
            short field_1C;
            short field_1E;
            int   field_20;
            short field_24;
            short field_26;
            short field_28;
            short field_2A;
            short field_2C;
            short field_2E;
            short field_30;
        } variant_0x34; // EFFECT_ENVIRONMENTLIGHT

        struct {
            short field_14;
            short field_16;
            int   field_18;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
            short field_24;
            short field_26;
        } variant_0x35; // EFFECT_CRASHSMOKE

        struct {
            short field_14;
            short field_16;
            int   field_18;
        } variant_0x36; // EFFECT_PADVIBRATION(2)

        struct {
            short field_14;
            short field_16;
            int   field_18;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
            short field_24;
            short field_26;
            short field_28;
            short field_2A;
            short field_2C;
            short field_2E;
            short field_30;
            short field_32;
        } variant_0x37; // EFFECT_CELOFAN

        struct {
            short field_14;
        } variant_0x39; // EFFECT_SPACK

        struct {
            short field_14;
            short field_16;
            short field_18;
        } variant_0x3A; // EFFECT_STEAMEXPLOSION

        struct {
            int   field_14;
            int   field_18;
            int   field_1C;
            short field_20;
            short field_22;
            short field_24;
            short field_26;
            short field_28;
        } variant_0x3B; // EFFECT_INVERSLIGHT2

        struct {
            short field_14;
            short field_16;
            int   field_18;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
            short field_24;
            short field_26;
            short field_28;
            short field_2A;
            short field_2C;
            short field_2E;
            short field_30;
            short field_32;
            short field_34;
        } variant_0x3C; // EFFECT_CELOFAN2

        struct {
            short field_14;
            short field_16;
            int   field_18;
        } variant_0x3D; // EFFECT_NINJALASER

        struct {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
        } variant_0x3E; // EFFECT_GUSEFFECT

        struct {
            short field_14;
            short field_16;
            int   field_18;
        } variant_0x3F; // EFFECT_SUBMARINEWATER

        struct {
            short field_14;
        } variant_0x41; // EFFECT_GHOST

        struct {
            short nBrightness;
            short nRadius;
        } variant_0x42; // EFFECT_LIGHT

        struct {
            int   field_14;
            short field_18;
        } variant_0x43; // EFFECT_FAMASLIGHT

        struct {
            short field_14;
            short field_16;
            int   field_18;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
        } variant_0x44; // EFFECT_HUMANSHADOW

        struct {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
        } variant_0x45; // EFFECT_BLOODHAZARD

        struct {
            short field_14;
            short field_16;
        } variant_0x46; // EFFECT_BLOODDRIP

        struct {
            short field_14;
        } variant_0x49; // EFFECT_MGCROOMDISPLAY

        struct {
            int   field_14;
            short field_18;
            short field_1A;
            int   field_1C;
            int   field_20;
        } variant_0x4A; // EFFECT_TEXT2
    } data;
} MGSDEMOEFFECT_, *PMGSDEMOEFFECT_, *LPMGSDEMOEFFECT_;

/******************************************************************************
 * prototypes
 */

/* demoexec.c */
extern BOOL CreateDemo(LPMGSDEMOACT lpAct, LPMGSDEMO lpDemo);
extern BOOL DestroyDemo(LPMGSDEMOACT lpAct);
extern BOOL FrameRunDemo(LPMGSDEMOACT lpAct, LPMGSDEMOFRAME lpDFrame);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _INC_DEMO_ */
