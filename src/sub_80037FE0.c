#include <util/idaTypes.h>
#include "linker.h"

typedef struct someStruct
{
    short thing[100];
} someStruct;

someStruct SECTION(".gStuff_800B9340") randomStruct; //todo figure out

void sub_80037FE0(int param_1, WORD param_2)
{
  randomStruct.thing[(param_1 + -1) * 2] = param_2;
}

