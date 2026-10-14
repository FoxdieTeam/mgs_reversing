#include "mgstype.h"
#include <libgte.h>
#include "overlays/s19b/takabe/jeep/jeepdemo.h"

/* jeepdemo.c: chase camera eye and target of modes 3 and 4 */
const SVECTOR s19b_dword_800DDD4C = {-540, 1214, -963};
const SVECTOR s19b_dword_800DDD54 = {428, 597, 1718};
const SVECTOR s19b_dword_800DDD5C = {-689, 990, -431};
const SVECTOR s19b_dword_800DDD64 = {459, 879, 59};

void *SECTION(".bss") s19b_dword_800DE5B0; // jeep_srl.c work
int   SECTION(".bss") s19b_dword_800DE5B4;
void *SECTION(".bss") s19b_dword_800DE5B8; // jeepdemo.c blur effect
int   SECTION(".bss") s19b_dword_800DE5BC;
int   SECTION(".bss") s19b_dword_800DE5C0;
int   SECTION(".bss") s19b_dword_800DE5C4;

JlampState SECTION(".bss") s19b_dword_800DE5C8;
int SECTION(".bss") s19b_dword_800DE5EC;
