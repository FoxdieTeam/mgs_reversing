#ifndef _MAP_H_
#define _MAP_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "map/hzd.h"

typedef struct map_record
{
    int               field_0_map_index_bit;
    unsigned short    field_4_mapNameHash;
    unsigned short    field_6_bUsed;
    HZD_MAP          *field_8_hzd;
    struct LitHeader *field_C_lit_file;
    int               field_10_zone_id;
} map_record;

struct LitHeader
{
    int field_0_num_lights;
};

map_record *Map_FindByNum_80031504(int mapNameHash);

#endif // _MAP_H_
