#include "psyq.h"
#include "libdg.h"
#include "libgv/libgv.h"

#define STATIC
// #define STATIC static

/*---------------------------------------------------------------------------*/

// kVertexIndexingOrder_8009D46C provides the indexing order for referencing the transformed vertex sections
STATIC unsigned char kVertexIndexingOrder_8009D46C[] = {0, 1, 3, 2};

STATIC void kmd_link_vertices_to_parent(DG_MDL *pKmdObj, DG_MDL *parent)
{
    unsigned int uVar2;
    int faces;
    unsigned char *fio;
    unsigned char *fio2;
    short flag;
    SVECTOR *vio;
    SVECTOR *vio2;
    int index;
    unsigned short pad;
    int iter;
    int offset;

    vio = pKmdObj->vertices;
    flag = 0;
    fio = pKmdObj->vertex_indices;

    for (iter = pKmdObj->n_faces * 4; iter > 0; iter--)
    {
        index = *fio;
        vio2 = &vio[index];

        if (vio2->pad != -1)
        {
            flag |= index;
            *fio |= 0x80;
        }

        fio++;
    }

    if (flag & 0x80)
    {
        return;
    }

    vio2 = pKmdObj->vertices;

    for (iter = pKmdObj->n_verts; iter > 0; iter--)
    {
        pad = vio2->pad;

        if (pad != 0xffff)
        {
            fio2 = parent->vertex_indices;

            for (faces = parent->n_faces * 4; faces > 0; faces--)
            {
                if ((*fio2 & 0x7f) == pad)
                {
                    break;
                }

                fio2++;
            }

            offset = fio2 - parent->vertex_indices;
            uVar2 = (offset / 4) * 52;

            vio2->pad = kVertexIndexingOrder_8009D46C[offset & 3] * 12 + uVar2 + 8;
        }

        vio2++;
    }
}

int DG_LoadInitKmd(unsigned char *buf, int id)
{
    DG_KMD *kmd = (DG_KMD *)buf;
    DG_MDL *current = kmd->objects;
    int     remaining = kmd->n_objects;

    while (--remaining >= 0)
    {
        if (current->vertices)
        {
            (char *)current->vertices += (unsigned int)kmd;
        }
        if (current->vertex_indices)
        {
            (char *)current->vertex_indices += (unsigned int)kmd;
        }
        if (current->normals)
        {
            (char *)current->normals += (unsigned int)kmd;
        }
        if (current->normal_indices)
        {
            (char *)current->normal_indices += (unsigned int)kmd;
        }
        if (current->texcoords)
        {
            (char *)current->texcoords += (unsigned int)kmd;
        }
        if (current->materials)
        {
            (char *)current->materials += (unsigned int)kmd;
        }
        if (current->parent >= 0)
        {
            kmd_link_vertices_to_parent(current, &kmd->objects[current->parent]);
        }
        ++current;
    }
    return 1;
}

/*---------------------------------------------------------------------------*/

int DG_LoadInitNar(unsigned char *buf, int id)
{
    DG_NARS *n = (DG_NARS *)buf;
    n->unknown1 = (unsigned char *)n + (unsigned int)n->unknown1;
    return 1;
}

int DG_LoadInitOar(unsigned char *buf, int id)
{
    DG_OAR *oar = (DG_OAR *)buf;
    oar->archive = (MOTION_ARCHIVE*)&oar->oarData[ ( ( (oar->n_joint + 2) ) * oar->n_motion) * 2 ];
    oar->table   = (MOTION_TABLE*)oar->oarData;
    return 1;
}

int DG_LoadInitImg(unsigned char *buf, int id)
{
    DG_IMG *img = (DG_IMG *)buf;
    img->textures = (unsigned short *)((char *)img + (unsigned int)img->textures);
    img->attribs = (DG_IMG_ATTRIB *)((char *)img + (unsigned int)img->attribs);
    img->tilemap = (char *)img + (unsigned int)img->tilemap;
    return 1;
}

int DG_LoadInitSgt(unsigned char *buf, int id)
{
    SgtFile *sgt = (SgtFile *)buf;
    sgt->unknown1 = (unsigned char *)sgt + (unsigned int)sgt->unknown1;
    sgt->unknown2 = (unsigned char *)sgt + (unsigned int)sgt->unknown2;
    sgt->unknown3 = (unsigned char *)sgt + (unsigned int)sgt->unknown3;
    sgt->unknown4 = (unsigned char *)sgt + (unsigned int)sgt->unknown4;
    sgt->unknown5 = (unsigned char *)sgt + (unsigned int)sgt->unknown5;
    return 1;
}

int DG_LoadInitLit(unsigned char *buf, int id)
{
    return 1;
}

/*---------------------------------------------------------------------------*/

extern int GV_Clock_800AB920;

// The size of this buffer is just a guess based on the next address of a
// variable that IDA knows about.
extern unsigned char pcxBuffer_800B3798[128];

#define PCX_RLE_THRESHOLD 0xC0

STATIC unsigned char *pcx_read_8bpp(unsigned char *pcxData, unsigned char *imageData, int imageSize)
{
    unsigned char *palette;
    do
    {
        char maybeRunLength = *pcxData++;
        if (maybeRunLength <= PCX_RLE_THRESHOLD)
        {
            --imageSize;
            *imageData++ = maybeRunLength;
        }
        else
        {
            int  runLength = maybeRunLength - PCX_RLE_THRESHOLD;
            char color = *pcxData++;
            imageSize -= runLength;
            while (--runLength >= 0)
            {
                *imageData++ = color;
            }
        }
        palette = pcxData;
    } while (imageSize > 0);
    return palette;
}

STATIC unsigned char *pcx_read_4bpp(unsigned char *pcxData, unsigned char *imageData,
                                    int bytes_per_line, int width, int height)
{
    int i = height;
    while (--i >= 0)
    {
        unsigned char *rp;
        unsigned char *gp;
        unsigned char *bp;
        unsigned char *ap;
        int            lineRemaining;

        unsigned char *pos = pcxBuffer_800B3798;
        lineRemaining = 4 * bytes_per_line;
        do
        {
            char maybeRunLength = *pcxData++;
            if (maybeRunLength <= PCX_RLE_THRESHOLD)
            {
                --lineRemaining;
                *pos++ = maybeRunLength;
            }
            else
            {
                int           runLength = maybeRunLength - PCX_RLE_THRESHOLD;
                unsigned char color = *pcxData++;
                lineRemaining -= runLength;
                while (--runLength >= 0)
                {
                    *pos++ = color;
                }
            }
        } while (lineRemaining > 0);

        rp = pcxBuffer_800B3798;
        gp = rp + bytes_per_line;
        bp = gp + bytes_per_line;
        ap = bp + bytes_per_line;
        for (lineRemaining = width; lineRemaining > 0; lineRemaining -= 4)
        {
            int r = *rp++;
            int g = *gp++;
            int b = *bp++;
            int a = *ap++;
            int shift = 128;
            int shiftEnd = 8 * (lineRemaining < 4);
            do
            {
                unsigned char color = 0;

                if (shift & r)
                    color |= 1;
                if (shift & g)
                    color |= 2;
                if (shift & b)
                    color |= 4;
                if (shift & a)
                    color |= 8;
                shift >>= 1;

                if (shift & r)
                    color |= 0x10;
                if (shift & g)
                    color |= 0x20;
                if (shift & b)
                    color |= 0x40;
                if (shift & a)
                    color |= 0x80;

                *imageData++ = color;
                shift >>= 1;
            } while (shift != shiftEnd);
        }
    }
    return pcxData;
}

STATIC void pcx_read_palette(unsigned char *pcxPalette, unsigned char *imageData, int width)
{
    unsigned short *imagePalette;
    int             remaining;
    unsigned char   r, g, b;
    unsigned short  color;

    imagePalette = (unsigned short *)imageData;
    remaining = width;
    while (--remaining >= 0)
    {
        r = *pcxPalette;
        g = *(pcxPalette + 1);
        b = *(pcxPalette + 2);
        color = !!((r | g | b) & 7) << 5;
        if (r || g || b)
        {
            color |= b >> 3;
            color <<= 5;
            color |= g >> 3;
            color <<= 5;
            color |= r >> 3;
        }
        *imagePalette++ = color;
        pcxPalette += 3;
    }
}

int DG_LoadInitPcx(unsigned char *buf, int id)
{
    PCXDATA       *pcx;
    unsigned short flags;
    int            min_x, min_y;
    int            width, height;
    DG_Image      *images;

    pcx = (PCXDATA *)buf;
    flags = pcx->info.flags;

    min_x = pcx->min_x - 1;
    min_y = pcx->min_y - 1;
    width = pcx->max_x - min_x;
    height = pcx->max_y - min_y;

    if (!(flags & 1))
    {
        width /= 2;
    }

    if (GV_AllocMemory2(GV_Clock_800AB920, width * height + 528, (void **)&images))
    {
        DG_Image      *imageA;
        DG_Image      *imageB;
        unsigned char *palette;

        imageB = images;
        imageB->dim.x = pcx->info.cx;
        imageB->dim.y = pcx->info.cy;
        imageB->dim.w = pcx->info.n_colors;
        imageB->dim.h = 1;

        imageA = images + 1;
        imageA->dim.x = pcx->info.px;
        imageA->dim.y = pcx->info.py;
        imageA->dim.w = width / 2;
        imageA->dim.h = height;

        if (flags & 1)
        {
            palette = pcx_read_8bpp(pcx->data, imageA->data, width * height) + 1;
        }
        else
        {
            pcx_read_4bpp(pcx->data, imageA->data, pcx->bytes_per_line, width, height);
            palette = &pcx->header_palette[0];
        }

        pcx_read_palette(palette, imageB->data, imageB->dim.w);
        LoadImage(&imageB->dim, (u_long *)imageB->data);
        LoadImage(&imageA->dim, (u_long *)imageA->data);
        GV_FreeMemory2(GV_Clock_800AB920, (void **)&images);

        if (id)
        {
            DG_SetTexture((unsigned short)id, flags & 1, (flags & 0x30) >> 4,
                          imageA, imageB, imageB->dim.w);
        }
        return 1;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

int DG_LoadInitKmdar(unsigned char *buf, int id)
{
    DG_ZmdFile  *zmdFile = (DG_ZmdFile *)buf;
    DG_ZmdEntry *zmdEntry = &zmdFile->zmdEntries[0];
    unsigned int offset = (unsigned int)zmdEntry + zmdFile->vertOffset;
    int          numZmds = zmdFile->numZmds + 1;

    while (--numZmds > 0)
    {
        DG_KMD       *zmdObject = &zmdEntry->data;
        int           nameHashed;
        int           numMeshes = zmdObject->n_objects;
        DG_MDL       *kmdObject = &zmdObject->objects[0];

        while (--numMeshes >= 0)
        {
            (char *)kmdObject->vertices += offset;
            if (kmdObject->vertex_indices)
            {
                (char *)kmdObject->vertex_indices += offset;
            }
            if (kmdObject->normals)
            {
                (char *)kmdObject->normals += offset;
            }
            if (kmdObject->normal_indices)
            {
                (char *)kmdObject->normal_indices += offset;
            }
            if (kmdObject->texcoords)
            {
                (char *)kmdObject->texcoords += offset;
            }
            if (kmdObject->materials)
            {
                (char *)kmdObject->materials += offset;
            }
            if (kmdObject->parent >= 0)
            {
                kmd_link_vertices_to_parent(kmdObject,
                                            &zmdObject->objects[kmdObject->parent]);
            }
            ++kmdObject;
        }
        nameHashed = GV_CacheID(zmdEntry->id, 'k');
        zmdEntry = (DG_ZmdEntry *)kmdObject;
        GV_SetCache(nameHashed, zmdObject);
    }
    return 1;
}
