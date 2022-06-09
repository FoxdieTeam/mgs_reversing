#include "grenade.h"

extern Actor_Grenade *grenade_init_80066944(Unknown_Grenade_Member *a1, OBJECT *parent_obj, int num_parent, int a4, int a5, int index);

Actor_Grenade *NewChaffGrenade_80066AA0(Unknown_Grenade_Member *a1, OBJECT *a2, int num_parent, int a4, int a5)
{
    return grenade_init_80066944(a1, a2, num_parent, a4, a5, 2);
}