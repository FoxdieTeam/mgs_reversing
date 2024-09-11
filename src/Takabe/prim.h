#ifndef _TAKABE_PRIM_H_
#define _TAKABE_PRIM_H_

#include <sys/types.h>
#include <libgte.h>

#include "libdg/libdg.h"

POLY_FT4 *Takabe_MakeIndividualRect3DPrim_helper_80079284(DG_PRIM *prim, POLY_FT4 *packs, int n_packs);
DG_PRIM  *Takabe_MakeIndividualRect3DPrim_800793E8(int n_vertices, SVECTOR *vertices);

#endif // _TAKABE_PRIM_H_
