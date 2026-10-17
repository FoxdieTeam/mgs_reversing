#ifndef __MGS_KOBA_VR_VR_H__
#define __MGS_KOBA_VR_VR_H__

// VR_Status: state of the VR training mission (vr.c)
enum {
    VR_STATUS_0 = 0,
    VR_STATUS_PLAY = 1,     // mission running
    VR_STATUS_CLEAR = 2,    // mission cleared ("clear" message / goal reached)
    VR_STATUS_4 = 4,
    VR_STATUS_END = 5,      // mission over
};

// VR_Flags
#define VRFLAG_RANK_MASK    0x06    // record rank of this run (1st..3rd)
#define VRFLAG_RESULT       0x08    // record times available
#define VRFLAG_AMMO_BONUS   0x10    // remaining ammo is counted down
#define VRFLAG_NO_NEXT      0x20    // the mission time is kept in a GCL variable

extern int vr_end_timer;
extern int VR_FoundCount;   // times the player has been spotted (sneaking mode)
extern int VR_TargetCount;  // targets destroyed ("plus" messages)
extern int VR_Flags;        // VRFLAG_*
extern int VR_Records[4];   // record times, [3] = time of this run
extern int VR_Status;       // VR_STATUS_*

void *NewVr(int name, int where);

#endif // __MGS_KOBA_VR_VR_H__
