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
typedef struct tagMODELM1E1
{
    OBJECT  object[2][3];
    int     nIndex[2];
    int     field_560;
    SVECTOR field_564[2];
} MODELM1E1, *PMODELM1E1, *LPMODELM1E1;

typedef struct tagMODELMI24HIND
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
} MODELMI24HIND, *PMODELMI24HIND, *LPMODELMI24HIND;
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
    BYTE      dummy[32-(sizeof(int)*3)];
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
    void*      lpData;      /**/
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

// 0x03 EFFECT_FADEIN  --> NewFadeInOut
// 0x04 EFFECT_FADEOUT --> NewFadeInOut
typedef struct tagEFFECTFADEINOUT {
    int   field_14;
    short field_18;
} EFFECTFADEINOUT, *PEFFECTFADEINOUT, *LPEFFECTFADEINOUT;

// 0x05 EFFECT_TEXT
typedef struct tagEFFECTTEXT {
    int   field_14;
    short field_18;
    short field_1A;
    int   field_1C;
} EFFECTTEXT, *PEFFECTTEXT, *LPEFFECTTEXT;

// 0x06 EFFECT_SURPRISEDMARK
typedef struct tagEFFECTSURPRISEDMARK {
    short field_14;
} EFFECTSURPRISEDMARK, *PEFFECTSURPRISEDMARK, *LPEFFECTSURPRISEDMARK;

// 0x07 EFFECT_QUESTIONMARK
typedef struct tagEFFECTQUESTIONMARK {
    short field_14;
} EFFECTQUESTIONMARK, *PEFFECTQUESTIONMARK, *LPEFFECTQUESTIONMARK;

// 0x09 EFFECT_BLOOD
typedef struct tagEFFECTBLOOD {
    short field_14;
} EFFECTBLOOD, *PEFFECTBLOOD, *LPEFFECTBLOOD;

// 0x0A EFFECT_BULLET
typedef struct tagEFFECTBULLET {
    int   field_14;
    short field_18;
    short field_1A;
    short field_1C;
    short field_1E;
    short field_20;
    short field_22;
    short field_24;
} EFFECTBULLET, *PEFFECTBULLET, *LPEFFECTBULLET;

// 0x0C EFFECT_BLOODCIRCLE
typedef struct tagEFFECTBLOODCIRCLE {
    short field_14;
    short field_16;
    int   field_18;
    int   field_1C;
} EFFECTBLOODCIRCLE, *PEFFECTBLOODCIRCLE, *LPEFFECTBLOODCIRCLE;

// 0x0E EFFECT_SHADOW
typedef struct tagEFFECTSHADOW {
    int     field_14;
    SVECTOR field_18;
    short   field_20;
    short   field_22;
    short   field_24;
    short   field_26;
} EFFECTSHADOW, *PEFFECTSHADOW, *LPEFFECTSHADOW;

// 0x0F EFFECT_FOOTPRINTS
typedef struct tagEFFECTFOOTPRINTS {
    short field_14;
} EFFECTFOOTPRINTS, *PEFFECTFOOTPRINTS, *LPEFFECTFOOTPRINTS;

// 0x10 EFFECT_MESSAGE
typedef struct tagEFFECTMESSAGE {
    int address;
    int message[7];
} EFFECTMESSAGE, *PEFFECTMESSAGE, *LPEFFECTMESSAGE;

// 0x12 EFFECT_BUBBLE
typedef struct tagEFFECTBUBBLE {
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
} EFFECTBUBBLE, *PEFFECTBUBBLE, *LPEFFECTBUBBLE;

// 0x13 EFFECT_SCOPE
typedef struct tagEFFECTSCOPE {
    short field_14;
} EFFECTSCOPE, *PEFFECTSCOPE, *LPEFFECTSCOPE;

// 0x14 EFFECT_DARKVISIBLEGOGGLE
typedef struct tagEFFECTDARKVISIBLEGOGGLE {
    short field_14;
    short field_16;
} EFFECTDARKVISIBLEGOGGLE, *PEFFECTDARKVISIBLEGOGGLE, *LPEFFECTDARKVISIBLEGOGGLE;

// 0x15 EFFECT_IRRAYSGOGGLE
typedef struct tagEFFECTIRRAYSGOGGLE {
    short field_14;
    short field_16;
} EFFECTIRRAYSGOGGLE, *PEFFECTIRRAYSGOGGLE, *LPEFFECTIRRAYSGOGGLE;

// 0x17 EFFECT_OPTICSCAMOUFLAGE
typedef struct tagEFFECTOPTICSCAMOUFLAGE {
    short field_14;
    short field_16;
    int   field_18;
    short field_1C;
} EFFECTOPTICSCAMOUFLAGE, *PEFFECTOPTICSCAMOUFLAGE, *LPEFFECTOPTICSCAMOUFLAGE;

// 0x18 EFFECT_ENVIRONMENTMAPPING
typedef struct tagEFFECTENVIRONMENTMAPPING {
    short field_14;
    short field_16;
    int   field_18;
    int   field_1C;
} EFFECTENVIRONMENTMAPPING, *PEFFECTENVIRONMENTMAPPING, *LPEFFECTENVIRONMENTMAPPING;

// 0x19 EFFECT_PLASMA
typedef struct tagEFFECTPLASMA {
    int   field_14;
    short field_18;
    short field_1A;
    int   field_1C;
    short field_20;
} EFFECTPLASMA, *PEFFECTPLASMA, *LPEFFECTPLASMA;

// 0x1A EFFECT_WINDCIRCLE
typedef struct tagEFFECTWINDCIRCLE {
    int field_14;
} EFFECTWINDCIRCLE, *PEFFECTWINDCIRCLE, *LPEFFECTWINDCIRCLE;

// 0x1B EFFECT_SEPIA
typedef struct tagEFFECTSEPIA {
    short field_14;
    short field_16;
    short field_18;
    short field_1A;
} EFFECTSEPIA, *PEFFECTSEPIA, *LPEFFECTSEPIA;

// 0x1C EFFECT_METALGEARLASER
typedef struct tagEFFECTMETALGEARLASER {
    SVECTOREX svectMove;
    SVECTOREX svectRotate;
} EFFECTMETALGEARLASER, *PEFFECTMETALGEARLASER, *LPEFFECTMETALGEARLASER;

// 0x1D EFFECT_UNSHAPEVIEW
typedef struct tagEFFECTUNSHAPEVIEW {
    short field_14;
    short field_16;
    int   field_18;
    int   field_1C;
} EFFECTUNSHAPEVIEW, *PEFFECTUNSHAPEVIEW, *LPEFFECTUNSHAPEVIEW;

// 0x1E EFFECT_GUSMASK
typedef struct {
    short field_14;
} EFFECTGUSMASK, *PEFFECTGUSMASK, *LPEFFECTGUSMASK;

// 0x20 EFFECT_URINATIONCIRCLE
typedef struct tagEFFECTURINATIONCIRCLE {
    short field_14;
    short field_16;
    int   field_18;
    int   field_1C;
    short field_20;
} EFFECTURINATIONCIRCLE, *PEFFECTURINATIONCIRCLE, *LPEFFECTURINATIONCIRCLE;

// 0x21 EFFECT_PLASMA2
typedef struct tagEFFECTPLASMA2 {
    short field_14;
    short field_16;
    short field_18;
    short field_1A;
    int   field_1C;
} EFFECTPLASMA2, *PEFFECTPLASMA2, *LPEFFECTPLASMA2;

// 0x22 EFFECT_BLUR
typedef struct tagEFFECTBLUR {
    short field_14;
    short field_16;
    short field_18;
    short field_1A;
} EFFECTBLUR, *PEFFECTBLUR, *LPEFFECTBLUR;

// 0x23 EFFECT_STEAMSMOKE
typedef struct tagEFFECTSTEAMSMOKE {
    short field_14;
    short field_16;
    short field_18;
    short field_1A;
    short field_1C;
    short field_1E;
    int   field_20;
} EFFECTSTEAMSMOKE, *PEFFECTSTEAMSMOKE, *LPEFFECTSTEAMSMOKE;

// 0x24 EFFECT_MONOTONE
typedef struct tagEFFECTMONOTONE {
    short field_14;
} EFFECTMONOTONE, *PEFFECTMONOTONE, *LPEFFECTMONOTONE;

// 0x25 EFFECT_RIFLESIGHT
typedef struct tagEFFECTRIFLESIGHT {
    short field_14;
} EFFECTRIFLESIGHT, *PEFFECTRIFLESIGHT, *LPEFFECTRIFLESIGHT;

// 0x26 EFFECT_MI24HIND
typedef struct tagEFFECTMI24HIND {
    DG_OBJS* lpObjs;
    int      nFlags;
} EFFECTMI24HIND, *PEFFECTMI24HIND, *LPEFFECTMI24HIND;

// 0x28 EFFECT_URINATIONCIRCLE2
typedef struct tagEFFECTURINATIONCIRCLE2 {
    short field_14;
    short field_16;
    int   field_18;
    int   field_1C;
} EFFECTURINATIONCIRCLE2, *PEFFECTURINATIONCIRCLE2, *LPEFFECTURINATIONCIRCLE2;

// 0x29 EFFECT_SIGHT
typedef struct tagEFFECTSIGHT {
    short field_14;
    short field_16;
    short field_18;
    short field_1A;
    int   field_1C;
} EFFECTSIGHT, *PEFFECTSIGHT, *LPEFFECTSIGHT;

// 0x2A EFFECT_NINJASWORD
typedef struct tagEFFECTNINJASWORD {
    int   field_14;
    short field_18;
} EFFECTNINJASWORD, *PEFFECTNINJASWORD, *LPEFFECTNINJASWORD;

// 0x2B EFFECT_SUBMARINEROOM
typedef struct tagEFFECTSUBMARINEROOM {
    short field_14;
} EFFECTSUBMARINEROOM, *PEFFECTSUBMARINEROOM, *LPEFFECTSUBMARINEROOM;

// 0x2C EFFECT_BLACKSMOKE2
typedef struct tagEFFECTBLACKSMOKE2 {
    short field_14;
    short field_16;
    short field_18;
    short field_1A;
    short field_1C;
} EFFECTBLACKSMOKE2, *PEFFECTBLACKSMOKE2, *LPEFFECTBLACKSMOKE2;

// 0x2D EFFECT_BLASTLINE
typedef struct tagEFFECTBLASTLINE {
    short field_14;
    short field_16;
    short field_18;
    short field_1A;
    int   field_1C;
    short field_20;
    short field_22;
} EFFECTBLASTLINE, *PEFFECTBLASTLINE, *LPEFFECTBLASTLINE;

// 0x2E EFFECT_SMOKELINE
typedef struct tagEFFECTSMOKELINE {
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
} EFFECTSMOKELINE, *PEFFECTSMOKELINE, *LPEFFECTSMOKELINE;

// 0x2F EFFECT_SHELLSMOKE
typedef struct tagEFFECTSHELLSMOKE {
    short field_14;
} EFFECTSHELLSMOKE, *PEFFECTSHELLSMOKE, *LPEFFECTSHELLSMOKE;

// 0x34 EFFECT_ENVIRONMENTLIGHT
typedef struct tagEFFECTENVIRONMENTLIGHT {
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
} EFFECTENVIRONMENTLIGHT, *PEFFECTENVIRONMENTLIGHT, *LPEFFECTENVIRONMENTLIGHT;

// 0x35 EFFECT_CRASHSMOKE
typedef struct tagEFFECTCRASHSMOKE {
    short field_14;
    short field_16;
    int   field_18;
    short field_1C;
    short field_1E;
    short field_20;
    short field_22;
    short field_24;
    short field_26;
} EFFECTCRASHSMOKE, *PEFFECTCRASHSMOKE, *LPEFFECTCRASHSMOKE;

// 0x36 EFFECT_PADVIBRATION(2)
typedef struct tagEFFECTPADVIBRATION {
    short field_14;
    short field_16;
    int   field_18;
} EFFECTPADVIBRATION, *PEFFECTPADVIBRATION, *LPEFFECTPADVIBRATION;

// 0x37 EFFECT_CELOFAN
typedef struct tagEFFECTCELOFAN {
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
} EFFECTCELOFAN, *PEFFECTCELOFAN, *LPEFFECTCELOFAN;

// 0x39 EFFECT_SPACK
typedef struct tagEFFECTSPACK {
    short field_14;
} EFFECTSPACK, *PEFFECTSPACK, *LPEFFECTSPACK;

// 0x3A EFFECT_STEAMEXPLOSION
typedef struct tagEFFECTSTEAMEXPLOSION {
    short field_14;
    short field_16;
    short field_18;
} EFFECTSTEAMEXPLOSION, *PEFFECTSTEAMEXPLOSION, *LPEFFECTSTEAMEXPLOSION;

// 0x3B EFFECT_INVERSLIGHT2
typedef struct tagEFFECTINVERSLIGHT2 {
    int   field_14;
    int   field_18;
    int   field_1C;
    short field_20;
    short field_22;
    short field_24;
    short field_26;
    short field_28;
} EFFECTINVERSLIGHT2, *PEFFECTINVERSLIGHT2, *LPEFFECTINVERSLIGHT2;

// 0x3C EFFECT_CELOFAN2
typedef struct tagEFFECTCELOFAN2 {
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
} EFFECTCELOFAN2, *PEFFECTCELOFAN2, *LPEFFECTCELOFAN2;

// 0x3D EFFECT_NINJALASER
typedef struct tagEFFECTNINJALASER {
    short field_14;
    short field_16;
    int   field_18;
} EFFECTNINJALASER, *PEFFECTNINJALASER, *LPEFFECTNINJALASER;

// 0x3E EFFECT_GUSEFFECT
typedef struct tagEFFECTGUSEFFECT {
    short field_14;
    short field_16;
    short field_18;
    short field_1A;
    short field_1C;
    short field_1E;
    short field_20;
    short field_22;
} EFFECTGUSEFFECT, *PEFFECTGUSEFFECT, *LPEFFECTGUSEFFECT;

// 0x3F EFFECT_SUBMARINEWATER
typedef struct tagEFFECTSUBMARINEWATER {
    short field_14;
    short field_16;
    int   field_18;
} EFFECTSUBMARINEWATER, *PEFFECTSUBMARINEWATER, *LPEFFECTSUBMARINEWATER;

// 0x41 EFFECT_GHOST
typedef struct tagEFFECTGHOST {
    short field_14;
} EFFECTGHOST, *PEFFECTGHOST, *LPEFFECTGHOST;

// 0x42 EFFECT_LIGHT
typedef struct tagEFFECTLIGHT {
    short nBrightness;
    short nRadius;
} EFFECTLIGHT, *PEFFECTLIGHT, *LPEFFECTLIGHT;

// 0x43 EFFECT_FAMASLIGHT
typedef struct tagEFFECTFAMASLIGHT {
    int   field_14;
    short field_18;
} EFFECTFAMASLIGHT, *PEFFECTFAMASLIGHT, *LPEFFECTFAMASLIGHT;

// 0x44 EFFECT_HUMANSHADOW
typedef struct tagEFFECTHUMANSHADOW {
    short field_14;
    short field_16;
    int   field_18;
    short field_1C;
    short field_1E;
    short field_20;
    short field_22;
} EFFECTHUMANSHADOW, *PEFFECTHUMANSHADOW, *LPEFFECTHUMANSHADOW;

// 0x45 EFFECT_BLOODHAZARD
typedef struct tagEFFECTBLOODHAZARD {
    short field_14;
    short field_16;
    short field_18;
    short field_1A;
} EFFECTBLOODHAZARD, *PEFFECTBLOODHAZARD, *LPEFFECTBLOODHAZARD;

// 0x46 EFFECT_BLOODDRIP
typedef struct tagEFFECTBLOODDRIP {
    short field_14;
    short field_16;
} EFFECTBLOODDRIP, *PEFFECTBLOODDRIP, *LPEFFECTBLOODDRIP;

// 0x49 EFFECT_MGCROOMDISPLAY
typedef struct tagEFFECTMGCROOMDISPLAY {
    short field_14;
} EFFECTMGCROOMDISPLAY, *PEFFECTMGCROOMDISPLAY, *LPEFFECTMGCROOMDISPLAY;

// 0x4A EFFECT_TEXT2
typedef struct tagEFFECTTEXT2 {
    int   field_14;
    short field_18;
    short field_1A;
    int   field_1C;
    int   field_20;
} EFFECTTEXT2, *PEFFECTTEXT2, *LPEFFECTTEXT2;

/***** XXX *****/
/***** XXX *****/

typedef struct tagMGSDEMOEFFECT_
{
    int       nID;          /**/
    int       nEffectID;    /**/
    SVECTOREX svectRotate;  /**/
    SVECTOREX svectMove;    /**/
    BYTE      byBuffer[32]; /**/
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
