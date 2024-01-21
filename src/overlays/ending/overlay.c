#include "libgcl/libgcl.h"

GCL_ActorTableEntry endingOverlayCharas[] =
{
    { 0x02C4, (TGCL_ActorCreateFn)0x800C6CA0 },
    { 0x3453, (TGCL_ActorCreateFn)0x800C4F34 },
    { 0x7A05, (TGCL_ActorCreateFn)0x800C9E6C },
    { 0x73EA, (TGCL_ActorCreateFn)0x800C5F7C },
    { 0x0003, (TGCL_ActorCreateFn)0x800C8F18 },
    { 0x0004, (TGCL_ActorCreateFn)0x800C8F18 },
    { 0x000F, (TGCL_ActorCreateFn)0x800C7864 },
    { 0x0010, (TGCL_ActorCreateFn)0x800C70C0 },
    { 0x001C, (TGCL_ActorCreateFn)0x800CA3A4 },
    { 0x0021, (TGCL_ActorCreateFn)0x800CAAA8 },
    { 0x0025, (TGCL_ActorCreateFn)0x800C89D4 },
    { 0x002F, (TGCL_ActorCreateFn)0x800C50C0 },
    { 0x0033, (TGCL_ActorCreateFn)0x8007DA94 },
    { 0x0044, (TGCL_ActorCreateFn)0x800C7ED0 },
    { 0, 0 }
};

const char ending_aMovied_800CC78C[] = "MOVIE %d\n";
const char ending_aNotfound_800CC798[] = "NOT FOUND\n";
const char ending_aMoviec_800CC7A4[] = "movie.c";

int SECTION("overlay.bss") ending_dword_800CCD9C;
