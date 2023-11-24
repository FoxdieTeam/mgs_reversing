#ifndef _SPARK_H_
#define _SPARK_H_

typedef struct SparkWork
{
    GV_ACT    f000_actor;
    int      f020_map;
    DG_PRIM *f024_pPrim;
    SVECTOR  f028[8];
    SVECTOR  f068[8];
    int      f0A8;
    int      f0AC;
    int      f0B0;
    int      f0B4;
    int      f0B8;
    int      f0BC;
    int      f0C0;
    int      f0C4;
    int      f0C8;
    int      f0CC;
    int      f0D0;
    int      f0D4;
    int      f0D8;
    int      f0DC;
    int      f0E0;
    int      f0E4;
    int      f0E8;
    int      f0EC;
    int      f0F0;
    int      f0F4;
    int      f0F8;
    int      f0FC;
    int      f100;
    int      f104;
    int      f108;
    int      f10C;
    int      f110;
    int      f114;
    int      f118;
    int      f11C;
    int      f120;
    int      f124;
    int      f128;
    int      f12C;
    int      f130;
    int      f134;
    int      f138;
    int      f13C;
    int      f140;
    int      f144;
    int      f148;
    int      f14C;
    int      f150;
    int      f154;
    int      f158;
    int      f15C;
    int      f160;
    int      f164;
    SVECTOR  f168;
    int      f170_counter;
} SparkWork;

GV_ACT *NewSpark_80074564(MATRIX *pMatrix, int pCnt);

#endif // _SPARK_H_
