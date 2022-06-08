#include "grenade.h"

extern Actor_Grenade *grenade_init_80066944(Unknown_Grenade_Member *a1, OBJECT *parent_obj, int num_parent, int a4, int a5, int index);

void NewStanGrenade_80066A74(Unknown_Grenade_Member *a1, OBJECT *obj, int num_parent, int a4, int a5)
{
    grenade_init_80066944(a1, obj, num_parent, a4, a5, 1);
}