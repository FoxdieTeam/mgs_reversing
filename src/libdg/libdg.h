#ifndef LIBDG_H
#define LIBDG_H

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct			DG_TEX
{
    unsigned short		field_0_hash;
    char				field_2_bUsed;
    char				field_3_pad; // ?
    short				field_4_tPage;
    short				field_6_clut;
    char				field_8_offx;
    char				field_9_offy;
    char				field_A_width;
    char				field_B_height;
} DG_TEX;

struct					KmdVec3
{
	int					field_0_x;
	int					field_4_y;
	int					field_8_z;
};

typedef struct			_DG_MDL
{
	int					flags_0;
	int					numFaces_4;
	struct KmdVec3		max_8;
	struct KmdVec3		min_14;
	struct KmdVec3		pos_20;
	int					parent_2C;
	int					unknownA_30;
	int					numVertex_34;
	SVECTOR				*vertexIndexOffset_38;
	unsigned char		*faceIndexOffset_3C;
	int					numNormals_40;
	SVECTOR				*normalIndexOffset_44;
	unsigned char		*normalFaceOffset_48;
	unsigned char		*uvOffset_4C;
	unsigned short int	*materialOffset_50; // hashed texture names
	int					pad_54;
} DG_MDL;

typedef struct			_DG_DEF
{
	int					num_bones_0; // or "model" count ?
	int					num_mesh_4;
	struct KmdVec3		max;
	struct KmdVec3		min;
} DG_DEF;

typedef struct			_DG_OBJ
{
	MATRIX				world;			//0x00
	MATRIX				screen;			//0x20
	DG_MDL				*model;			//0x40
	CVECTOR				*rgbs;			//0x44
	struct _DG_OBJ		*extend; //0x48
	short				bound_mode;		//0x4C
	short				free_count;		//0x4E
	short				raise;			//0x50
	short				n_packs;			//0x52
	POLY_GT4			*packs[2];		//0x54
} DG_OBJ;

typedef struct			_DG_OBJS
{
	MATRIX				world;		//0x00
	MATRIX				*root;		//0x20
	DG_DEF				*def;		//0x24
	u_long				flag;		//0x28
	u_short				group_id;	//0x2C
	short				n_models;		//0x2E
	short				chanl;		//0x30
	short				bound_mode;	//0x32
	MATRIX				*light;		//0x34
	SVECTOR				*rots;		//0x38
	SVECTOR				*adjust;	//0x3C
	SVECTOR				*waist_rot; //0x40
	SVECTOR				*movs;		//0x44
	DG_OBJ				objs[0];		//0x48
} DG_OBJS;

union					Prim_Union
{
	LINE_G2				line_g2;
	LINE_F4				line_f4;
	POLY_FT4			poly_ft4;
	TILE*				tiles;
};

struct					DG_Rec_Unknown
{
	unsigned char		field_0_prim_size;
	unsigned char		field_1;
	unsigned char		field_2;
	unsigned char		field_3;
};

struct DG_PRIM;
typedef void    (*TPrim_Fn)(struct DG_PRIM* pVec, void* primBuffer, int numPrims);

typedef struct			_DG_PRIM
{
	MATRIX				world;
	MATRIX				*root;
	int					type;
	u_short				group_id;
	signed short		n_prims;
	u_short				chanl;
	u_short				field_2E_k500;
	u_short				field_30_prim_size;
	u_short				field_32;
	u_short				field_34;
	u_short				field_36;
	SVECTOR*			field_38_pUnknown;
	RECT*				field_3C;
	union Prim_Union	*field_40_pBuffers[2];
	signed short				field_48_prim_count;
	u_short				field_4A;
	int					field_4C;
	TPrim_Fn			field_50_pFn;
} DG_PRIM;

typedef struct
{
    short int field_0_x;
    short int field_2_y;
    short int field_4_z;
    short int field_6_w; // padding?
    short int field_8_brightness;
    short int field_A_radius;
    CVECTOR field_C_colour;
} Light;

typedef struct
{
    int field_0_lightCount;
    Light *field_4_pLights;
} DG_FixedLight;

static inline u_long	LLOAD(from) void *from;
{
	return *(u_long *)from;
}

static inline void		LSTORE(from, to)
	u_long from;
void *to;
{
	*(u_long *)to = from;
}

static inline u_short	SLOADL(from) void *from;
{
	return *(u_short *)from;
}

static inline void		SSTOREL(from, to) // name restored
	u_short from;
void *to;
{
	*(u_short *)to = from;
}

static inline void		LCOPY(s1, d1) void *s1, *d1;
{
	*(u_long *)d1 = *(u_long *)s1;
}

static inline void		LCOPY2(s1, d1, s2, d2) void *s1, *d1;
void *s2, *d2;
{
	u_long r1, r2;

	r1 = *(u_long *)s1;
	r2 = *(u_long *)s2;
	*(u_long *)d1 = r1;
	*(u_long *)d2 = r2;
}

// TODO: There are others like this as seen in the memleak

// invented name
static inline void DG_SetObjectGroupId(DG_OBJS* objs, int id)
{
    objs->group_id = id;
}

// invented name
static inline void DG_SetPrimGroupId(DG_PRIM* pPrim, int id)
{
    pPrim->group_id = id;
}


void DG_DequeuePrim_800182E0(DG_OBJS *pObjs);
void DG_FreePrim_8001BC04(DG_OBJS *pPrim);

void DG_SetPos_8001BC44( MATRIX* matrix );
void DG_SetPos2_8001BC8C(SVECTOR *svector, SVECTOR *svector2);
void DG_PutVector_8001BE48( SVECTOR* svector, SVECTOR* svector2, int count );
void DG_FreeObjPacket_8001AAD0(DG_OBJ *pObj, int idx);

#endif //LIBDG_H
