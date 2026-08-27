#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "libdg.h"
#include "common.h"
#include "libgv/libgv.h"
#include "fmt_sgt.h"

/*---------------------------------------------------------------------------*/

static void LinkModelToParent( DG_MDL *mdl, DG_MDL *parent )
{
    static u_char index_order[] = { 0, 1, 3, 2 };

    int flag, i;
    SVECTOR *verts;
    u_char *indices;

    int uVar2;
    int faces;
    u_char *indices2;
    SVECTOR *verts2;
    int index;
    u_short pad;
    int offset;

    flag = 0;
    verts = mdl->verts;
    indices = mdl->vindices;

    for ( i = mdl->n_faces * 4; i > 0; i-- )
    {
        index = *indices;
        verts2 = &verts[ index ];

        if ( verts2->pad != -1 )
        {
            flag |= index;
            *indices |= 0x80;
        }
        indices++;
    }
    if ( flag & 0x80 ) return;

    verts2 = mdl->verts;
    for ( i = mdl->n_verts; i > 0; i-- )
    {
        pad = verts2->pad;

        if (pad != 0xffff)
        {
            indices2 = parent->vindices;

            for (faces = parent->n_faces * 4; faces > 0; faces--)
            {
                if ((*indices2 & 0x7f) == pad)
                {
                    break;
                }

                indices2++;
            }

            offset = indices2 - parent->vindices;
            uVar2 = (offset / 4) * 52;

            verts2->pad = index_order[offset & 3] * 12 + uVar2 + 8;
        }

        verts2++;
    }
}

int DG_LoadInitKmd( void *buf, int id )
{
    DG_DEF *def;
    DG_MDL *mdl;
    int n_models;

    def = (DG_DEF *)buf;
    mdl = def->models;
    n_models = def->n_x_models;
    while ( --n_models >= 0 )
    {
        if ( mdl->verts != NULL ) mdl->verts = (SVECTOR *)( (int)mdl->verts + (int)def );
        if ( mdl->vindices != NULL ) mdl->vindices = (u_char *)( (int)mdl->vindices + (int)def );
        if ( mdl->norms != NULL ) mdl->norms = (SVECTOR *)( (int)mdl->norms + (int)def );
        if ( mdl->nindices != NULL ) mdl->nindices = (u_char *)( (int)mdl->nindices + (int)def );
        if ( mdl->uvs != NULL ) mdl->uvs = (u_char *)( (int)mdl->uvs + (int)def );
        if ( mdl->texids != NULL ) mdl->texids = (u_short *)( (int)mdl->texids + (int)def );
        if ( mdl->parent >= 0 ) LinkModelToParent( mdl, &def->models[ mdl->parent ] );
        mdl++;
    }
    return 1;
}

/*---------------------------------------------------------------------------*/

int DG_LoadInitNar( void *buf, int id )
{
    DG_NARS *nar;

    nar = (DG_NARS *)buf;
    nar->unknown1 = (u_char *)( (int)nar + (int)nar->unknown1 );
    return 1;
}

int DG_LoadInitOar( void *buf, int id )
{
    DG_OAR *oar;

    oar = (DG_OAR *)buf;
    oar->archive = &oar->data[ ( oar->n_joint + 2 ) * oar->n_motion ];
    oar->table = oar->data;
    return 1;
}

int DG_LoadInitImg( void *buf, int id )
{
    DG_IMG *img;

    img = (DG_IMG *)buf;
    img->textures = (u_short *)( (int)img + (int)img->textures );
    img->attribs = (DG_IMG_ATTRIB *)( (int)img + (int)img->attribs );
    img->tilemap = (u_char *)( (int)img + (int)img->tilemap );
    return 1;
}

int DG_LoadInitSgt( void *buf, int id )
{
    DG_SGT *sgt;

    sgt = (DG_SGT *)buf;
    sgt->unknown1 = (u_char *)( (int)sgt + (int)sgt->unknown1 );
    sgt->unknown2 = (u_char *)( (int)sgt + (int)sgt->unknown2 );
    sgt->unknown3 = (u_char *)( (int)sgt + (int)sgt->unknown3 );
    sgt->unknown4 = (u_char *)( (int)sgt + (int)sgt->unknown4 );
    sgt->unknown5 = (u_char *)( (int)sgt + (int)sgt->unknown5 );
    return 1;
}

int DG_LoadInitLit( void *buf, int id )
{
    return 1;
}

/*---------------------------------------------------------------------------*/

static u_char *PcxInflate8( u_char *pcxdata, u_char *buf, int size )
{
    int len;
    u_char code, data;
    
    do
    {
        code = *pcxdata++;
        if ( code <= PCX_RLE_CODE )
        {
            size--;
            *buf++ = code;
        }
        else
        {
            len = code - PCX_RLE_CODE;
            data = *pcxdata++;
            size -= len;
            while ( --len >= 0 ) *buf++ = data;
        }
    } while ( size > 0 );
    return pcxdata;
}

static u_char *PcxInflate4( u_char *pcxdata, u_char *buf, int stride, int width, int height )
{
    static u_char pcx_temp_buf[ 128 ];

    int len, size;
    u_char *rp, *gp, *bp, *ap;
    u_char *tmp;

    while ( --height >= 0 )
    {
        tmp = pcx_temp_buf;
        size = stride * 4;

        do
        {
            u_char code, data;

            code = *pcxdata++;
            if ( code <= PCX_RLE_CODE )
            {
                size--;
                *tmp++ = code;
            }
            else
            {
                len = code - PCX_RLE_CODE;
                data = *pcxdata++;
                size -= len;
                while ( --len >= 0 ) *tmp++ = data;
            }
        } while ( size > 0 );

        rp = pcx_temp_buf;
        gp = rp + stride;
        bp = gp + stride;
        ap = bp + stride;
    
        for ( size = width; size > 0; size -= 4 )
        {
            int bit, end, r, g, b, a;
            u_char data;

            r = *rp++;
            g = *gp++;
            b = *bp++;
            a = *ap++;
            bit = 0x80;
            end = ( size < 4 ) * 8;

            do
            {
                data = 0;
                if ( bit & r ) data |= 0x01;
                if ( bit & g ) data |= 0x02;
                if ( bit & b ) data |= 0x04;
                if ( bit & a ) data |= 0x08;
                bit >>= 1;
                if ( bit & r ) data |= 0x10;
                if ( bit & g ) data |= 0x20;
                if ( bit & b ) data |= 0x40;
                if ( bit & a ) data |= 0x80;
                *buf++ = data;
                bit >>= 1;
            } while ( bit != end );
        }
    }
    return pcxdata;
}

static void LoadPalette( u_char *palette, u_short *buf, int width )
{
    u_char r, g, b, a;
    u_short color;

    while ( --width >= 0 )
    {
        r = palette[ 0 ];
        g = palette[ 1 ];
        b = palette[ 2 ];
        a = ( ( r | g | b ) & 7 ) != 0;
        color = a << 5;
        if ( r != 0 || g != 0 || b != 0 )
        {
            color |= b >> 3;
            color <<= 5;
            color |= g >> 3;
            color <<= 5;
            color |= r >> 3;
        }
        *buf++ = color;
        palette += 3;
    }
}

int DG_LoadInitPcx( void *buf, int id )
{
    PCXDATA *pcx;
    DG_IMAGE *im;
    int flag, x, y, w, h;

    pcx = (PCXDATA *)buf;
    flag = pcx->info.flag;
    x = pcx->min_x - 1;
    y = pcx->min_y - 1;
    w = pcx->max_x - x;
    h = pcx->max_y - y;
    if ( !( flag & 1 ) ) w /= 2;

    if ( GV_AllocMemory2( GV_Clock, w * h + 512 + 16, (void **)&im ) )
    {
        DG_IMAGE *clut, *tex;
        u_char *palette;

        clut = im;
        clut->dim.x = pcx->info.cx;
        clut->dim.y = pcx->info.cy;
        clut->dim.w = pcx->info.n_colors;
        clut->dim.h = 1;

        tex = im + 1;
        tex->dim.x = pcx->info.px;
        tex->dim.y = pcx->info.py;
        tex->dim.w = w / 2;
        tex->dim.h = h;

        if ( flag & 1 )
        {
            palette = PcxInflate8( pcx->data, tex->data, w * h ) + 1;
        }
        else
        {
            PcxInflate4( pcx->data, tex->data, pcx->bytes_per_line, w, h );
            palette = pcx->header_palette;
        }

        LoadPalette( palette, (u_short *)clut->data, clut->dim.w );
        LoadImage( &clut->dim, (u_long *)clut->data );
        LoadImage( &tex->dim, (u_long *)tex->data );
        GV_FreeMemory2( GV_Clock, (void **)&im );

        if ( id != 0 ) DG_SetTexture( id & 0xffff, flag & 1, ( flag & 0x30 ) >> 4, &tex->dim, &clut->dim, clut->dim.w );
        return 1;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

int DG_LoadInitKmdar( void *buf, int id )
{
    DG_ZMD_DEF *zmd;
    DG_KMDPACK *kmd;
    int offset, n_kmd;

    zmd = (DG_ZMD_DEF *)buf;
    kmd = zmd->kmd;
    offset = (int)kmd + zmd->vert_offset;
    n_kmd = zmd->n_kmd + 1;
    while ( --n_kmd > 0 )
    {
        DG_DEF *def;
        DG_MDL *mdl;
        int n_models;

        def = &kmd->def;
        mdl = def->models;
        n_models = def->n_x_models;
        while ( --n_models >= 0 )
        {
            mdl->verts = (SVECTOR *)( (int)mdl->verts + offset );
            if ( mdl->vindices != NULL ) mdl->vindices = (u_char *)( (int)mdl->vindices + offset );
            if ( mdl->norms != NULL ) mdl->norms = (SVECTOR *)( (int)mdl->norms + offset );
            if ( mdl->nindices != NULL ) mdl->nindices = (u_char *)( (int)mdl->nindices + offset );
            if ( mdl->uvs != NULL ) mdl->uvs = (u_char *)( (int)mdl->uvs + offset );
            if ( mdl->texids != NULL ) mdl->texids = (u_short *)( (int)mdl->texids + offset );
            if ( mdl->parent >= 0 ) LinkModelToParent( mdl, &def->models[ mdl->parent ] );
            mdl++;
        }

        GV_SetCache( GV_CacheID( kmd->id, 'k' ), def );
        kmd = (DG_KMDPACK *)mdl;
    }
    return 1;
}
