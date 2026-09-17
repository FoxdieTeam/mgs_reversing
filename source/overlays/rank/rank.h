#ifndef _RANK_H_
#define _RANK_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "menu/menuman.h"
#include "menu/radio.h"

typedef struct _RankEntry
{
    int                field_0;
    struct _RankEntry *field_4;
    int                field_8;
    short              field_C;
    short              field_E;
    char               field_10;
    char               field_11;
    char               field_12;
    char               field_13;
    int                field_14;
    int                field_18;
    char               field_1C;
    char               field_1D;
    unsigned short     field_1E;
    int                field_20;
    unsigned short     field_24;
    short              field_26;
} RankEntry;

typedef struct _RankEntryUpdate
{
    unsigned short field_0;
    unsigned short field_2;
} RankEntryUpdate;

extern RadioFileModeStru_800ABB7C *rank_dword_800E189C;
extern int                         rank_dword_800C330C;
extern MenuPrim                    rank_dword_800E1978;
extern Menu_Triangle               rank_dword_800CB454;
extern TextConfig                  rank_dword_800E1998;
extern const char                  rank_dword_800E06D0[];
extern int                         rank_dword_800E1874;
extern int                         rank_dword_800E1878;
extern RankEntry                  *rank_dword_800E1974;
extern RankEntry                  *rank_dword_800E59F4;
extern int                         rank_dword_800E59F8;

void       rank_800CD178(int *arr, int len);
void       rank_800CD1A8(MenuPrim *prim, RadioFileModeStruElem *pElem);
void       rank_800CD230(MenuPrim *prim, RadioFileModeStruElem *pElem);
void       rank_800CD32C(MenuPrim *prim, RadioFileModeStruElem *pElem);
void       rank_800CD474(MenuPrim *prim, RadioFileModeStruElem *pElem);
void       rank_800CD8F0(int param_1, int param_2, int param_3, int param_4, int divisor);
void       rank_800CDFC8(MenuPrim *prim, SELECT_INFO *info);
void       rank_800CECC0(int arg);
void       rank_800CF1D4(RankEntry *entry);
RankEntry *rank_800CF328(int id);

RankEntry *rank_800D2144(int id);
void       rank_800D2188(int id, int bits);

int            rank_800D45D8(char param, int def);
unsigned short rank_800D463C(char param, unsigned short def);
void           rank_800D46A4(char param, short x, short y, short z, SVECTOR *vec);

#endif
