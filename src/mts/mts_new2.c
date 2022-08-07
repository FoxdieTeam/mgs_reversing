#include <LIBSN.H>
#include "linker.h"

// Each overlay defines this symbol
extern char OverlayCharas[];

#pragma INCLUDE_ASM("asm/mts/mts_reset_graph_8008C534.s") // 88 bytes

void SetExMask_8008C58C()
{
    // unknown psyq-specific debug function ?
    __asm__("break 1030");
}

unsigned char *mts_get_bss_tail_8008C598()
{
    return &OverlayCharas[0];
}

void sio_output_start_8008C5A8(void)
{
}

void sio_output_stop_8008C5B0(void)
{
}

void sub_8008C5B8(void)
{
}

void sub_8008C5C0(void)
{
}

void sub_8008C5C8(void)
{
}

int sio_getchar2_8008C5D0(void)
{
    return -1;
}

int sub_8008C5D8(void)
{
    return 0;
}

void sub_8008C5E0(void)
{
}

void sub_8008C5E8(void)
{
}

void sub_8008C5F0(void)
{
}

void sub_8008C5F8(void)
{
}

void sub_8008C600(void)
{
}
