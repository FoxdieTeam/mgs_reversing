#include "famas.h"

extern void GM_FreeObject_80034BF8(OBJECT *obj);

void famas_act_80066188(Actor_Famas *famas)
{
    GM_FreeObject_80034BF8(&famas->f20_obj);
}
