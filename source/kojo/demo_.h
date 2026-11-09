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

typedef struct tagMGSDEMOSTAGE
{
    int nCacheID;
    int nStrCode;
} MGSDEMOSTAGE, *PMGSDEMOSTAGE, *LPMGSDEMOSTAGE;

#define MGS_SCENETOSTAGE 0x00000001

typedef struct tagMGSDEMOSCENE
{
    int   nID;
    DWORD dwStyle;
    int   nCacheID;
    int   nStrCode;
    int   nName;
} MGSDEMOSCENE, *PMGSDEMOSCENE, *LPMGSDEMOSCENE;

typedef struct tagMGSDEMO   /* demo header */
{
    u_int          nSize;
    int            nTime;
    int            nFrameCount;
    int            nStageCount;
    int            nSceneCount;
    LPMGSDEMOSTAGE lpStage;
    LPMGSDEMOSCENE lpScene;
} MGSDEMO, *PMGSDEMO, *LPMGSDEMO;

typedef struct tagMGSDEMOEFFECT
{
    int      field_0;
    int      field_4_type;
    short    field_8_x;
    short    field_A_y;
    short    field_C_z;
    short    field_E_x;
    short    field_10_y;
    short    field_12_z;
    int      field_14_type;
    int      field_18_xy;
    int      field_1C_zpad;
    int      field_20;
    char     field_24;
    char     field_25;
    char     field_26;
    char     field_27;
    short    field_28;
    short    field_2A;
    int      field_2C;
    short    field_30;
    short    field_32;
} MGSDEMOEFFECT, *PMGSDEMOEFFECT, *LPMGSDEMOEFFECT;

typedef struct tagMGSDEMOEFFECTACT
{
    struct tagMGSDEMOEFFECTACT *lpPrevious; // TODO: void*
    struct tagMGSDEMOEFFECTACT *lpNext;     // TODO: void*
    BOOL          bCheck;
    void*         lpActor;
    void*         lpActor2;
    MGSDEMOEFFECT effect;
    int           nParam1;
    int           nParam2;
    SVECTOR       svect1;
    MATRIX        matrix;
} MGSDEMOEFFECTACT, *PMGSDEMOEFFECTACT, *LPMGSDEMOEFFECTACT;

typedef struct tagMGSDEMOSCENEMOTION
{
    int     nSceneID;
    short   bPreview;
    short   svectRotate_x;
    short   svectRotate_y;
    short   svectRotate_z;
    short   svectMove_x;
    short   svectMove_y;
    short   svectMove_z;
    short   nRotateCount;
    short*  lpsvectRotate;
} MGSDEMOSCENEMOTION, *PMGSDEMOSCENEMOTION, *LPMGSDEMOSCENEMOTION;

typedef struct tagMGSDEMOFRAME
{
    u_int               nSize;
    int                 nTime;
    short               svectCamera_x;
    short               svectCamera_y;
    short               svectCamera_z;
    short               svectTarget_x;
    short               svectTarget_y;
    short               svectTarget_z;
    short               nZRotate;
    short               nScreen;
    short               nEffectCount;
    LPMGSDEMOEFFECT     lpEffect;
    short               nSMotionCount;
    LPMGSDEMOSCENEMOTION lpSMotion;
} MGSDEMOFRAME, *PMGSDEMOFRAME, *LPMGSDEMOFRAME;

typedef struct tagMGSDEMOMODEL
{
    CONTROL     control;
    OBJECT      object;
    MATRIX      light[2];
    MGSDEMOM1E1 *lpData; // TODO: void*
} MGSDEMOMODEL, *PMGSDEMOMODEL, *LPMGSDEMOMODEL;

typedef struct tagMGSDEMOACT
{
    GV_ACT              actor;
    DWORD               dwStyle;
    int                 nVSync;
    int                 nMap;
    int                 nTime;
    LPMGSDEMO           lpDemo;
    LPMGSDEMOMODEL      lpModel;
    MGSDEMOEFFECTACT    chain;
    int                 field_B0; /* unused */
    int                 field_B4; /* unused */
    int                 field_B8; /* unused */
    int                 field_BC; /* unused */
    LPMGSDEMO           lpExtMemory;
    CONTROL             control;        // MGSDEMOMODEL modelEffect
    OBJECT              object;         // MGSDEMOMODEL modelEffect
    MATRIX              light[2];       // MGSDEMOMODEL modelEffect
    int                 field_264;      // MGSDEMOMODEL modelEffect
    int                 field_268; /* unused */
    int                 field_26C; /* unused */
    DG_CHANLFUNC        lpfnDGScreenChanl;
    int                 nGameStatus;
    GM_CameraSystemWork old_camera;
    int                 nItemSave;
    int                 nWeaponSave;
} MGSDEMOACT, *PMGSDEMOACT, *LPMGSDEMOACT;

/***** XXX *****/
/***** XXX *****/

/* This should be replaced by loads of individual structs */
typedef struct DMO_DATA_0x36
{
    int field_0;
    int field_4_type;

    SVECTOREX field_8_vec1;
    SVECTOREX field_E_vec2;

    // TODO: Is there a cleaner way to model this structure?
    // Some of the variants are very similar. Once all
    // ShowEffect functions are decompiled those fields
    // should be named properly (and maybe it'll be easier
    // to find patterns then).
    union {
        struct
        {
            int   field_14;
            short field_18;
        } variant_0x3;

        struct
        {
            int   field_14;
            short field_18;
        } variant_0x4;

        struct
        {
            int   field_14;
            short field_18;
            short field_1A;
            int   field_1C;
        } variant_0x5;

        struct
        {
            short field_14;
        } variant_0x6;

        struct
        {
            short field_14;
        } variant_0x7;

        struct
        {
            short field_14;
        } variant_0x9;

        struct
        {
            int   field_14;
            short field_18;
            short field_1A;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
            short field_24;
        } variant_0xA;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
        } variant_0xC;

        struct
        {
            int     field_14;
            SVECTOR field_18;
            short   field_20;
            short   field_22;
            short   field_24;
            short   field_26;
        } variant_0xE;

        struct
        {
            short field_14;
        } variant_0xF;

        struct
        {
            int address;
            int message[7];
        } variant_0x10;

        struct
        {
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
        } variant_0x12;

        struct
        {
            short field_14;
        } variant_0x13;

        struct
        {
            short field_14;
            short field_16;
        } variant_0x14;

        struct
        {
            short field_14;
            short field_16;
        } variant_0x15;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            short field_1C;
        } variant_0x17;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
        } variant_0x18;

        struct
        {
            int   field_14;
            short field_18;
            short field_1A;
            int   field_1C;
            short field_20;
        } variant_0x19;

        struct
        {
            int field_14;
        } variant_0x1A;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
        } variant_0x1B;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            short field_1C;
            short field_1E;
        } variant_0x1C;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
        } variant_0x1D;

        struct
        {
            short field_14;
        } variant_0x1E;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
            short field_20;
        } variant_0x20;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            int   field_1C;
        } variant_0x21;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
        } variant_0x22;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            short field_1C;
            short field_1E;
            int   field_20;
        } variant_0x23;

        struct
        {
            short field_14;
        } variant_0x24;

        struct
        {
            short field_14;
        } variant_0x25;

        struct
        {
            DG_OBJS *field_14;
            int      field_18;
        } variant_0x26;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
        } variant_0x28;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            int   field_1C;
        } variant_0x29;

        struct
        {
            int   field_14;
            short field_18;
        } variant_0x2A;

        struct
        {
            short field_14;
        } variant_0x2B;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            short field_1C;
        } variant_0x2C;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            int   field_1C;
            short field_20;
            short field_22;
        } variant_0x2D;

        struct
        {
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
        } variant_0x2E;

        struct
        {
            short field_14;
        } variant_0x2F;

        struct
        {
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
        } variant_0x34;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
            short field_24;
            short field_26;
        } variant_0x35;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
        } variant_0x36;

        struct
        {
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
        } variant_0x37;

        struct
        {
            short field_14;
        } variant_0x39;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
        } variant_0x3A;

        struct
        {
            int   field_14;
            int   field_18;
            int   field_1C;
            short field_20;
            short field_22;
            short field_24;
            short field_26;
            short field_28;
        } variant_0x3B;

        struct
        {
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
        } variant_0x3C;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
        } variant_0x3D;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
        } variant_0x3E;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
        } variant_0x3F;

        struct
        {
            short field_14;
        } variant_0x41;

        struct
        {
            short field_14;
            short field_16;
        } variant_0x42;

        struct
        {
            int   field_14;
            short field_18;
        } variant_0x43;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
        } variant_0x44;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
        } variant_0x45;

        struct
        {
            short field_14;
            short field_16;
        } variant_0x46;

        struct
        {
            short field_14;
        } variant_0x49;

        struct
        {
            int   field_14;
            short field_18;
            short field_1A;
            int   field_1C;
            int   field_20;
        } variant_0x4A;
    } data;
} DMO_DATA_0x36;

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
