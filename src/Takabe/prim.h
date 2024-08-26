#ifndef _TAKABE_H_
#define _TAKABE_H_

#include <sys/types.h>
#include <libgte.h>

#include "libdg/libdg.h"

POLY_FT4 * Takabe_MakeIndividualRect3DPrim_helper_80079284(DG_PRIM *pPrim, POLY_FT4 *pPolys, int numPrims);
DG_PRIM  * Takabe_MakeIndividualRect3DPrim_800793E8(int prim_count, SVECTOR *pVec);

#endif // _TAKABE_H_
