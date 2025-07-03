#ifndef _SIGHT_H_
#define _SIGHT_H_

void *NewSight(int hashedFileName0, int hashedFileName1,
               short *itemEquippedIndicator, short itemId,
               short *xyOffsetBuffer);

void *sight_init_80071DC8(int hashedFileName, short *xyOffsetBuffer);

void *NewSightFast(int hashedFileName0, int hashedFileName1,
                   short *itemEquippedIndicator, short itemId,
                   short *xyOffsetBuffer);

void *sight_init_80071F98(int hashedFileName, short *xyOffsetBuffer);

#endif // _SIGHT_H_
