#include "bss.h"
#include "linker.h"


unsigned char SECTION(".0x800ABBF0") main_task_stack_800ABBF0[2048]; // 800ABBEC

unsigned int SECTION(".0x800AC3F0") sdStack_800AC3F0[512]; // 800AC3F0

int SECTION(".gDiskNum_800ACBF0") gDiskNum_800ACBF0;
