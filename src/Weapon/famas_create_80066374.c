#include "famas.h"
#include "Script_tbl_map_8002BB44.h"

extern GameState_800B4D98 gGameState_800B4D98;

extern Actor_Famas *NewFAMAS_8006623C(int a1, OBJECT *parent_obj, int num_parent, int a4, int flag);

Actor_Famas *famas_create_80066374(int a1, OBJECT *a2, int num_parent, int a4)
{
    return NewFAMAS_8006623C(a1, a2, num_parent, a4, (unsigned int)gGameState_800B4D98.field_02_diffcultyLevel >> 31);
}