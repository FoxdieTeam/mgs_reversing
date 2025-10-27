#ifndef S11D_ROPE_H
#define S11D_ROPE_H

#include "common.h"
#include "libgv/libgv.h"

// Rope work structure
typedef struct RopeWork
{
    char pad[0x1000];
} RopeWork;

// External data symbols
extern int s11d_dword_800C32B4;
extern int s11d_dword_800C32B8;
extern unsigned int GM_GameStatus;

// External function declarations - consolidated from inline externs
extern char linkvarbuf;
extern char DG_ZeroVector;
extern int s11d_dword_800C32B4;
extern int s11d_dword_800C32B8;
extern int s11d_dword_800C32BC;
extern int s11d_dword_800C32C4;
extern int s11d_dword_800C32CC;
extern int data_800BB9B4;    // Counter
extern int data_800BB9D4;
extern int data_800BB9F4;
extern int data_800BBA20;
extern int data_800BBA40;
extern int data_800D1F84;
extern int func_80016CCC(void *);
extern int func_80016D00(void *, void *, void *);
extern int func_80016D40(void *, void *, void *);
extern int func_80031298(void *);
extern int func_8003152948(void *);
extern int func_80044DE0(void *);
extern int func_80044FC8(void *);
extern int func_80045298(void *);
extern int func_80092508(void *);
extern int func_800925D8(void *);
extern int func_800C4DE0(void *);
extern int func_800C4F84(void *);
extern int func_800C4FC8(void *);
extern int func_800C52F0(void *);
extern short data_800B4DAE;
extern short data_800B77CA;  // At 0x800B77B8 + 0x12
extern short data_800D1F7C;
extern short data_800D1F7E;
extern short data_800D1F80;
extern short data_800D1F82;
extern unsigned int GM_GameStatus;
extern void *GM_WhereList;  // Array of pointers
extern void *GM_PlayerPosition;
extern void *func_80020968(int);
extern void *func_800209E8(void *);
extern void *func_80020A14(void *);
extern void *func_80020AA4(void);
extern void *func_8002D400(void *);
extern void func_8001511C8(void *, void *);
extern void func_80018C2E0(void *);
extern void func_8001BC04(void *);
extern void func_8001BC44(void *);
extern void func_8001BD20(void *);
extern void func_8001BD64(void *);
extern void func_8002099E(void *, void *);
extern void func_8002655C(void *, int, int);
extern void func_800266D4(void *, void *, int);
extern void func_80026C0C(void *);
extern void func_800292E4(void *);
extern void func_80029324(void *);
extern void func_8002B6C8(void);
extern void func_8002D4B0(void *);
extern void func_8002DC74(void *, int, int, void *);
extern void func_8002DCCC(void *, int, int, void *, void *, void *);
extern void func_80030938(void *);
extern void func_8003093C(void *);
extern void func_80030980(int);
extern void func_800329C4(void *, int, int);
extern void func_80032DC4(void *, void *, int);
extern void func_80034BF8(void *);
extern void func_80034CD4(void *, void *, int, int);
extern void func_80046240(void *);
extern void func_8005D58C(void *param, int value);
extern void func_80072728(void *, int);
extern void func_80092ED8(void *);
extern void func_800A9538(void *, void *);
extern void func_800AB6C8(void);
extern void func_800C44A4(void *);
extern void func_800C44F0(void *);
extern void func_800C4574(void *);
extern void func_800C45F8(void *);
extern void func_800C4648(void *);
extern void func_800C481C(void *);
extern void func_800C486C(void *);
extern void func_800C4898(void *, int);
extern void func_800C48EC(void *);
extern void func_800C4B78(void *);
extern void func_800C4ECC(void *);
extern void func_800C502C(void *);
extern void func_800C5348(void *);
extern void func_800C54CC(void);
extern void func_800C5538(void);
extern void func_800C5B10(void *);
extern void func_800C5E74(void *);
extern void func_800C6240(void *);
extern void func_800C6478(void *);
extern void func_800C650C(void);
extern void func_800CCDE0(void);
extern void func_800CE04C(void);
extern void func_800D1950(void *, void *, int);
extern void func_800D1AB0(void *, void *);

#endif // S11D_ROPE_H
