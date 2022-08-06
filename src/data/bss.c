#include "bss.h"
#include "linker.h"
#include "libgv\libgv.h"

unsigned char SECTION(".bss") main_task_stack_800ABBF0[2048]; // 800ABBEC

unsigned int SECTION(".bss") sdStack_800AC3F0[512]; // 800AC3F0

int SECTION(".bss") gDiskNum_800ACBF0;
int SECTION(".bss") pad_800ACBF0;

struct Actor SECTION(".bss") gGVActor_800acbf8;

