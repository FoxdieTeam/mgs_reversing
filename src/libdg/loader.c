#include "psyq.h"
#include "libdg.h"
#include "libgv/libgv.h"

// kVertexIndexingOrder_8009D46C provides the indexing order for referencing the transformed vertex sections
unsigned char kVertexIndexingOrder_8009D46C[] = {0, 1, 3, 2};

void kmd_file_handler_link_vertices_to_parent_8001F3CC(DG_MDL *pKmdObj, DG_MDL *pParentObj)
{
    unsigned int uVar2;
    int faces;
    unsigned char *fio;
    unsigned char *fio2;
    short uVar7;
    SVECTOR *vio;
    SVECTOR *vio2;
    int index;
    unsigned short pad;
    int iter;
    int offset;

    vio = pKmdObj->vertexIndexOffset_38;
    uVar7 = 0;
    fio = pKmdObj->faceIndexOffset_3C;

    for (iter = pKmdObj->numFaces_4 * 4; iter > 0; iter--)
    {
        index = *fio;
        vio2 = &vio[index];

        if (vio2->pad != -1)
        {
            uVar7 |= index;
            *fio |= 0x80;
        }

        fio++;
    }

    if (uVar7 & 0x80)
    {
        return;
    }

    vio2 = pKmdObj->vertexIndexOffset_38;

    for (iter = pKmdObj->numVertex_34; iter > 0; iter--)
    {
        pad = vio2->pad;

        if (pad != 0xffff)
        {
            fio2 = pParentObj->faceIndexOffset_3C;

            for (faces = pParentObj->numFaces_4 * 4; faces > 0; faces--)
            {
                if ((*fio2 & 0x7f) == pad)
                {
                    break;
                }

                fio2++;
            }

            offset = fio2 - pParentObj->faceIndexOffset_3C;
            uVar2 = (offset / 4) * 52;

            vio2->pad = kVertexIndexingOrder_8009D46C[offset & 3] * 12 + uVar2 + 8;
        }

        vio2++;
    }
}

int DG_LoadInitKmd_8001F4EC(unsigned char *pFileData, int fileNameHashed)
{
    DG_KmdFile *kmd = (DG_KmdFile *)pFileData;
    DG_MDL     *current = kmd->objects;
    int         remaining = kmd->num_objects;

    while (--remaining >= 0)
    {
        if (current->vertexIndexOffset_38)
        {
            (char *)current->vertexIndexOffset_38 += (unsigned int)kmd;
        }
        if (current->faceIndexOffset_3C)
        {
            (char *)current->faceIndexOffset_3C += (unsigned int)kmd;
        }
        if (current->normalIndexOffset_44)
        {
            (char *)current->normalIndexOffset_44 += (unsigned int)kmd;
        }
        if (current->normalFaceOffset_48)
        {
            (char *)current->normalFaceOffset_48 += (unsigned int)kmd;
        }
        if (current->uvOffset_4C)
        {
            (char *)current->uvOffset_4C += (unsigned int)kmd;
        }
        if (current->materialOffset_50)
        {
            (char *)current->materialOffset_50 += (unsigned int)kmd;
        }
        if (current->parent_2C >= 0)
        {
            kmd_file_handler_link_vertices_to_parent_8001F3CC(current, &kmd->objects[current->parent_2C]);
        }
        ++current;
    }
    return 1;
}

int DG_LoadInitNar_8001F5F8(unsigned char *pFileData, int fileNameHashed)
{
    DG_NARS *n = (DG_NARS *)pFileData;
    n->unknown1 = (unsigned char *)n + (unsigned int)n->unknown1;
    return 1;
}

int DG_LoadInitOar_8001F610(unsigned char *pFileData, int fileNameHashed)
{
    DG_OAR *oar = (DG_OAR *)pFileData;
    oar->archive = (MOTION_ARCHIVE*)&oar->oarData[ ( ( (oar->n_joint + 2) ) * oar->n_motion) * 2 ];
    oar->table   = (MOTION_TABLE*)oar->oarData;
    return 1;
}

int DG_LoadInitImg_8001F644(unsigned char *pFileData, int fileNameHashed)
{
    DG_IMG *img = (DG_IMG *)pFileData;
    img->textures = (unsigned short *)((char *)img + (unsigned int)img->textures);
    img->attribs = (DG_IMG_ATTRIB *)((char *)img + (unsigned int)img->attribs);
    img->tilemap = (char *)img + (unsigned int)img->tilemap;
    return 1;
}

int DG_LoadInitSgt_8001F670(unsigned char *pFileData, int fileNameHashed)
{
    SgtFile *sgt = (SgtFile *)pFileData;
    sgt->unknown1 = (unsigned char *)sgt + (unsigned int)sgt->unknown1;
    sgt->unknown2 = (unsigned char *)sgt + (unsigned int)sgt->unknown2;
    sgt->unknown3 = (unsigned char *)sgt + (unsigned int)sgt->unknown3;
    sgt->unknown4 = (unsigned char *)sgt + (unsigned int)sgt->unknown4;
    sgt->unknown5 = (unsigned char *)sgt + (unsigned int)sgt->unknown5;
    return 1;
}

int DG_LoadInitLit_8001F6B4(unsigned char *pFileData, int fileNameHashed)
{
    return 1;
}

extern int GV_Clock_800AB920;

// The size of this buffer is just a guess based on the next address of a
// variable that IDA knows about.
extern unsigned char pcxBuffer_800B3798[128];

#define PCX_RLE_THRESHOLD 0xC0

unsigned char *pcx_file_read_8BPP_8001F6BC(unsigned char *pcxData, unsigned char *imageData, int imageSize)
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

unsigned char *pcx_file_read_4BPP_8001F71C(unsigned char *pcxData, unsigned char *imageData, int bytesPerLine,
                                           int width, int height)
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
        lineRemaining = 4 * bytesPerLine;
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
        gp = rp + bytesPerLine;
        bp = gp + bytesPerLine;
        ap = bp + bytesPerLine;
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

void pcx_file_read_palette_8001F89C(unsigned char *pcxPalette, unsigned char *imageData, int width)
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

int DG_LoadInitPcx_8001F920(unsigned char *pFileData, int fileNameHashed)
{
    DG_PcxFile    *pcx;
    unsigned short flags;
    int            xMin, yMin;
    int            width, height;
    DG_Image      *images;

    pcx = (DG_PcxFile *)pFileData;
    flags = pcx->flags;

    xMin = pcx->xMin - 1;
    yMin = pcx->yMin - 1;
    width = pcx->xMax - xMin;
    height = pcx->yMax - yMin;
    if (!(flags & 1))
    {
        width /= 2;
    }

    if (GV_AllocMemory2_80015ED8(GV_Clock_800AB920, width * height + 528, (void **)&images))
    {
        DG_Image      *imageA;
        DG_Image      *imageB;
        unsigned char *palette;

        imageB = images;
        imageB->dim.x = pcx->cx;
        imageB->dim.y = pcx->cy;
        imageB->dim.w = pcx->n_colors;
        imageB->dim.h = 1;

        imageA = images + 1;
        imageA->dim.x = pcx->px;
        imageA->dim.y = pcx->py;
        imageA->dim.w = width / 2;
        imageA->dim.h = height;

        if (flags & 1)
        {
            palette = pcx_file_read_8BPP_8001F6BC(pcx->data, imageA->data, width * height) + 1;
        }
        else
        {
            pcx_file_read_4BPP_8001F71C(pcx->data, imageA->data, pcx->bytesPerLine, width, height);
            palette = pcx->palette;
        }

        pcx_file_read_palette_8001F89C(palette, imageB->data, imageB->dim.w);
        LoadImage(&imageB->dim, (u_long *)imageB->data);
        LoadImage(&imageA->dim, (u_long *)imageA->data);
        GV_FreeMemory2_80016078(GV_Clock_800AB920, (void **)&images);

        if (fileNameHashed)
        {
            DG_SetTexture_8001D880((unsigned short)fileNameHashed, flags & 1, (flags & 0x30) >> 4, imageA,
                                           imageB, imageB->dim.w);
        }
        return 1;
    }

    return 0;
}

int DG_LoadInitKmdar_8001FAD0(unsigned char *pFileData, int fileNameHashed)
{
    DG_ZmdFile  *zmdFile = (DG_ZmdFile *)pFileData;
    DG_ZmdEntry *zmdEntry = &zmdFile->zmdEntries[0];
    unsigned int offset = (unsigned int)zmdEntry + zmdFile->vertOffset;
    int          numZmds = zmdFile->numZmds + 1;
    while (--numZmds > 0)
    {
        DG_ZmdObject *zmdObject = &zmdEntry->data;
        int           nameHashed;
        int           numMeshes = zmdObject->numMeshes;
        DG_MDL       *kmdObject = &zmdObject->kmdObjects[0];
        while (--numMeshes >= 0)
        {
            (char *)kmdObject->vertexIndexOffset_38 += offset;
            if (kmdObject->faceIndexOffset_3C)
            {
                (char *)kmdObject->faceIndexOffset_3C += offset;
            }
            if (kmdObject->normalIndexOffset_44)
            {
                (char *)kmdObject->normalIndexOffset_44 += offset;
            }
            if (kmdObject->normalFaceOffset_48)
            {
                (char *)kmdObject->normalFaceOffset_48 += offset;
            }
            if (kmdObject->uvOffset_4C)
            {
                (char *)kmdObject->uvOffset_4C += offset;
            }
            if (kmdObject->materialOffset_50)
            {
                (char *)kmdObject->materialOffset_50 += offset;
            }
            if (kmdObject->parent_2C >= 0)
            {
                kmd_file_handler_link_vertices_to_parent_8001F3CC(kmdObject,
                                                                  &zmdObject->kmdObjects[kmdObject->parent_2C]);
            }
            ++kmdObject;
        }
        nameHashed = GV_CacheID_800152DC(zmdEntry->fileNameHashed, 'k');
        zmdEntry = (DG_ZmdEntry *)kmdObject;
        GV_SetCache_800153C0(nameHashed, zmdObject);
    }
    return 1;
}
