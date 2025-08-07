#ifndef __MGS_THING_SIGHT_H__
#define __MGS_THING_SIGHT_H__

void *NewSight(int hashedFileName0, int hashedFileName1,
               short *itemEquippedIndicator, short itemId,
               short *xyOffsetBuffer);

void *NewSight_80071DC8(int hashedFileName, short *xyOffsetBuffer);

void *NewSightFast(int hashedFileName0, int hashedFileName1,
                   short *itemEquippedIndicator, short itemId,
                   short *xyOffsetBuffer);

void *NewSight_80071F98(int hashedFileName, short *xyOffsetBuffer);

void sub_80072074(void);

#endif // __MGS_THING_SIGHT_H__
