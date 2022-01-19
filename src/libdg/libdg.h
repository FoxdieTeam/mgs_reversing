#ifndef LIBDG_H
#define LIBDG_H

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct _DG_MDL { } DG_MDL;

typedef struct _DG_DEF { } DG_DEF;

typedef	struct _DG_OBJ {
	MATRIX		world ;			//0x00
	MATRIX		screen ;		//0x20
	DG_MDL		*model ;		//0x40
	CVECTOR		*rgbs;			//0x44
	struct _DG_OBJ	*extend ;	//0x48
	short		bound_mode ;	//0x4C
	short		free_count ;	//0x4E
	short		raise ;			//0x50
	short		n_packs ;		//0x52
	POLY_GT4	*packs[ 2 ] ;	//0x54
} DG_OBJ ;

typedef	struct _DG_OBJS {
	MATRIX		world ;		 //0x00 
	MATRIX		*root ;		 //0x20
	DG_DEF		*def ;		 //0x24
	u_long		flag ;		 //0x28
	u_short		group_id ;	 //0x2C
	short		n_models ;	 //0x2E
	short		chanl ;		 //0x30
	short		bound_mode ; //0x32
	MATRIX		*light ;	 //0x34
	SVECTOR		*rots ;		 //0x38
	SVECTOR		*adjust ;	 //0x3C
	SVECTOR		*waist_rot;	 //0x40
	SVECTOR		*movs ;		 //0x44
	DG_OBJ		objs[ 0 ] ;	 //0x48
} DG_OBJS ;

static    inline    u_long    LLOAD( from )
void            *from ;
{
    return *(u_long *)from ;
}

static    inline    void    LSTORE( from, to )
u_long            from ;
void            *to ;
{
    *(u_long *)to = from ;
}

static	inline	u_short	SLOADL( from )
void			*from ;
{
	return *(u_short *)from ;
}

static	inline	void	SSTOREL( from, to ) // name restored
u_short			from ;
void			*to ;
{
	*(u_short *)to = from ;
}

static	inline	void	LCOPY( s1, d1 )
void		*s1, *d1 ;
{
	*(u_long *)d1 = *(u_long *)s1 ;
}

static    inline    void    LCOPY2( s1, d1, s2, d2 )
void        *s1, *d1 ;
void        *s2, *d2 ;
{
    u_long        r1, r2 ;

    r1 = *(u_long *)s1 ;
    r2 = *(u_long *)s2 ;
    *(u_long *)d1 = r1 ;
    *(u_long *)d2 = r2 ;
}

// TODO: There are others like this as seen in the memleak

#endif //LIBDG_H