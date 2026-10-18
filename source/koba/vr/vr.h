#ifndef __MGS_KOBA_VR_VR_H__
#define __MGS_KOBA_VR_VR_H__

// VR_Status: state of the VR training mission (vr.c)
enum {
    VR_STATUS_0 = 0,
    VR_STATUS_PLAY = 1,     // mission running
    VR_STATUS_CLEAR = 2,    // mission cleared ("clear" message / goal reached)
    VR_STATUS_NO_HUD = 4,   // time/target HUD hidden, background panels fade in
    VR_STATUS_END = 5,      // mission over
};

// Messages and constants shared by the mission managers (vr.c, vr2.c)
#define HASH_VR_START       0xB247  // mission start
#define HASH_VR_NO_HUD      0xEC10  // switch to VR_STATUS_NO_HUD

#define VR_SE_LIMIT_COUNT   185     // last seconds of the time limit
#define VR_SE_TARGET        180

#define TIME_FPS            30      // the mission time counts frames
#define DEAD_TIME           90      // frames between the player's death and the game over screen

#define WEAPON_NONE         -1
#define ITEM_NONE           -1

#define STANCE_GROUND       2

// VR_Flags
#define VRFLAG_RANK_MASK    0x06    // record rank of this run (1st..3rd)
#define VRFLAG_RESULT       0x08    // record times available
#define VRFLAG_AMMO_BONUS   0x10    // remaining ammo is counted down
#define VRFLAG_NO_NEXT      0x20    // the mission time is kept in a GCL variable

// vr.c defines these itself (VR_DEFINES_DATA): a prior extern declaration would turn its SECTION(".bss") definitions
// into .comm symbols (alphabetical layout, no xdef) instead of ordered .bss data of vr.obj
#ifndef VR_DEFINES_DATA
extern int vr_end_timer;
extern int VR_FoundCount;   // times the player has been spotted (sneaking mode)
extern int VR_TargetCount;  // targets destroyed ("plus" messages)
extern int VR_Flags;        // VRFLAG_*
extern int VR_Records[4];   // record times, [3] = time of this run
#endif

// VR_Status (VR_STATUS_*) is NOT part of vr.obj: the original links it in the bss of backgrnd.c (VR_DEFINES_STATUS), which
// sits at a different place relative to vr.obj in the overlays
#ifndef VR_DEFINES_STATUS
extern int VR_Status;
#endif

void *NewVr(int name, int where);

#endif // __MGS_KOBA_VR_VR_H__
