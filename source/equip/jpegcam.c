#include "equip.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "chara/snake/sna_init.h"
#include "game/game.h"
#include "game/camera.h"
#include "game/object.h"
#include "linkvar.h"
#include "menu/menuman.h"
#include "memcard/memcard.h"
#include "thing/sight.h"
#include "sd/g_sound.h"

extern int                 DG_CurrentGroupID;
extern GM_CAMERA           GM_Camera;
extern int                 dword_8009F604;
extern TMat8x8B            gJpegcamMatrix2_800BDCD8;
extern UnkCameraStruct     gUnkCameraStruct_800B77B8;
extern char               *dword_800BDCC8;
extern int                 dword_800BDCCC;
extern int                 dword_800BDCD0;
extern UnkCameraStruct     gUnkCameraStruct_800B77B8;

extern short dword_800ABBD4;
extern short dword_800ABBDC;

extern char memoryCardFileName[]; // = "BISLPM-99999        ";

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_MANAGER

#define CAMERA_SIGHT    0xeee9  // GV_StrCode("camera")
#define CAMERA_SIGHT2   0xb3cd  // GV_StrCode("camera_2")

typedef struct _Work
{
    GV_ACT         actor;
    CONTROL       *control;
    OBJECT        *parent;
    OBJECT_NO_ROTS goggles;
    short          head_saved_packs;
    short          head_saved_raise;
    GV_PAD        *pad_data;
    SVECTOR        field_54_vec;
    SVECTOR        field_5C_ang;
    int            state;
    int            field_68;
    MAP           *map;
    int            field_70;
    int            field_74;
    int            field_78;
    int            field_7C;
    int            field_80;
    char          *field_84;
    char          *field_88;
    int            field_8C_size;
    void          *field_90_pSight;
    int            field_94_bMakeVisible;
    int            field_98;
} Work;

/*---------------------------------------------------------------------------*/

static void jpegcam_unk1_80063704(char *buf, MEM_CARD *pMemcard, int arg2, int arg3);
static void jpegcam_unk2_80063888(char *param_1, int param_2);
static void jpegcam_unk3_800638B4(int *arg0);

STATIC DATA_INFO stru_8009F2D8 = {
    {67, 4}, 0, 2, "SAVE PHOTO",
    (void *)jpegcam_unk1_80063704,
    (void *)jpegcam_unk2_80063888,
    (void *)jpegcam_unk3_800638B4
};

STATIC signed char gJpegcamZigZagTable_8009F2EC[64] = {
    0x00, 0x01, 0x08, 0x10, 0x09, 0x02, 0x03, 0x0A,
    0x11, 0x18, 0x20, 0x19, 0x12, 0x0B, 0x04, 0x05,
    0x0C, 0x13, 0x1A, 0x21, 0x28, 0x30, 0x29, 0x22,
    0x1B, 0x14, 0x0D, 0x06, 0x07, 0x0E, 0x15, 0x1C,
    0x23, 0x2A, 0x31, 0x38, 0x39, 0x32, 0x2B, 0x24,
    0x1D, 0x16, 0x0F, 0x17, 0x1E, 0x25, 0x2C, 0x33,
    0x3A, 0x3B, 0x34, 0x2D, 0x26, 0x1F, 0x27, 0x2E,
    0x35, 0x3C, 0x3D, 0x36, 0x2F, 0x37, 0x3E, 0x3F
};

STATIC signed char gJpegcamQuantTable_8009F32C[64] = {
    0x02, 0x10, 0x13, 0x16, 0x1A, 0x1B, 0x1D, 0x22,
    0x10, 0x10, 0x16, 0x18, 0x1B, 0x1D, 0x22, 0x25,
    0x13, 0x16, 0x1A, 0x1B, 0x1D, 0x22, 0x22, 0x26,
    0x16, 0x16, 0x1A, 0x1B, 0x1D, 0x22, 0x25, 0x28,
    0x16, 0x1A, 0x1B, 0x1D, 0x20, 0x23, 0x28, 0x30,
    0x1A, 0x1B, 0x1D, 0x20, 0x23, 0x28, 0x30, 0x3A,
    0x1A, 0x1B, 0x1D, 0x22, 0x26, 0x2E, 0x38, 0x45,
    0x1B, 0x1D, 0x23, 0x26, 0x2E, 0x38, 0x45, 0x53
};

STATIC TMat8x8B gJpegcamMatrix1_8009F36C = {
    { 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D },
    { 0x3F, 0x35, 0x23, 0x0C, 0xF4, 0xDD, 0xCB, 0xC1 },
    { 0x3B, 0x18, 0xE8, 0xC5, 0xC5, 0xE8, 0x18, 0x3B },
    { 0x35, 0xF4, 0xC1, 0xDD, 0x23, 0x3F, 0x0C, 0xCB },
    { 0x2D, 0xD3, 0xD3, 0x2D, 0x2D, 0xD3, 0xD3, 0x2D },
    { 0x23, 0xC1, 0x0C, 0x35, 0xCB, 0xF4, 0x3F, 0xDD },
    { 0x18, 0xC5, 0x3B, 0xE8, 0xE8, 0x3B, 0xC5, 0x18 },
    { 0x0C, 0xDD, 0x35, 0xC1, 0x3F, 0xCB, 0x23, 0xF4 }
};

STATIC SVECTOR dword_8009F3AC[2] = {
    {0, 0,    0, 0},
    {0, 0, 3200, 0}
};

/******************************************************************************
 * photo save functions
 */

static void jpegcam_unk1_80063704(char *buf, MEM_CARD *pMemcard, int arg2, int arg3)
{
    char photo_id[8];
    unsigned int blocks_avail;
    int index;

    memoryCardFileName[12] = 'C';

    blocks_avail = 0;

    for (index = 0; index < pMemcard->file_count; index++)
    {
        if (strncmp(pMemcard->files[index].name, memoryCardFileName, 13) == 0)
        {
            blocks_avail |= 1 << (pMemcard->files[index].name[18] - 64);
        }
    }

    for (index = 1; index <= 16; index++)
    {
        if (!(blocks_avail & (1 << index)))
        {
            break;
        }
    }

    photo_id[0] = '\x82';
    photo_id[1] = (index / 10) + 0x4F;
    photo_id[2] = '\x82';
    photo_id[3] = (index % 10) + 0x4F;
    photo_id[4] = '\x00';

    stru_8009F2D8.field_2 = index;

    /* ＭＧＳ∫ */
    /* 　 */
    /* ＰＨＯＴＯ */
    // Shift-JIS
    sprintf(buf, "%s%s%s%s", "\x82\x6C\x82\x66\x82\x72\x81\xE7", "\x81\x40", "\x82\x6F\x82\x67\x82\x6E\x82\x73\x82\x6E", photo_id);
}

static void jpegcam_unk2_80063888(char *param_1, int param_2)
{
    sprintf(param_1, "PHOTO %02d\n", *(char *)(param_2 + 6) - 0x40);
}

static void jpegcam_unk3_800638B4(int *arg0)
{
    dword_800BDCD0 = (char)dword_800BDCD0 | 0x80808000;
    printf("save header = %x\n", dword_800BDCD0);

    GV_CopyMemory(&dword_800BDCD0, &arg0[0], 4);
    GV_CopyMemory(dword_800BDCC8, &arg0[1], dword_800BDCCC);
}

/******************************************************************************
 * JPEG encoding functions
 */

static void JpegInitMatrix(Work *work)
{
    // Copy matrix gJpegcamMatrix1_8009F36C transposed to gJpegcamMatrix2_800BDCD8

    int i, j;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            gJpegcamMatrix2_800BDCD8[j][i] = gJpegcamMatrix1_8009F36C[i][j];
        }
    }
}

static void JpegColorCvt_XBGR1555_to_BGRX8888(unsigned short *src, char *dst)
{
    int i;

    for (i = 0; i < 256; i++, dst += 4, src++)
    {
        dst[2] = (*src << 3) & 0xF8;
        dst[1] = (*src >> 2) & 0xF8;
        dst[0] = (*src >> 7) & 0xF8;
    }
}

static void JpegMacroblock_RGB_to_YUV(char *stream, char *y_out, char *u_out, char *v_out)
{
    int i;
    int r, g, b;

    for (i = 0; i < 256; i++, stream += 4)
    {
        r = stream[0];
        g = stream[1];
        b = stream[2];

        *y_out++ = (r *   299 + g *   587 + b *  114) / 1000 + 128;
        *u_out++ = (r * -1687 + g * -3313 + b * 5000) / 10000;
        *v_out++ = (r *  5000 - g *  4187 - b *  813) / 10000;
    }
}

static void JpegSplitLumaBlocks(TMat16x16B *pSrcY, TMat8x8B *pY1, TMat8x8B *pY2, TMat8x8B *pY3, TMat8x8B *pY4)
{
    // Given a "16 by 16B" luma matrix, copy its four quadrants into four "8 by 8B" matrices
    int i, j;

    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            (*pY1)[i][j] = (*pSrcY)[i + 0][j + 0];
            (*pY2)[i][j] = (*pSrcY)[i + 0][j + 8];
            (*pY3)[i][j] = (*pSrcY)[i + 8][j + 0];
            (*pY4)[i][j] = (*pSrcY)[i + 8][j + 8];
        }
    }
}

static void JpegDownsampleChroma420(char *pInU, char *pInV, char *pOutU, char *pOutV)
{
    int i, j;

    signed char *var_t0;
    signed char *var_t1;
    signed char *var_t2;
    signed char *var_t3;

    int resA;
    int resB;

    for (i = 0; i < 8; i++)
    {
        var_t1 = pInU + i * 16;
        var_t3 = var_t1 + 16;

        var_t0 = pInV + i * 16;
        var_t2 = var_t0 + 16;

        for (j = 0; j < 8; j++)
        {
            resA = var_t1[0] + var_t1[1] + var_t3[0] + var_t3[1];
            resB = var_t0[0] + var_t0[1] + var_t2[0] + var_t2[1];

            *pOutU = resA / 4;
            *pOutV = resB / 4;

            var_t1 += 2;
            var_t3 += 2;
            var_t0 += 2;
            var_t2 += 2;

            pOutU++;
            pOutV++;
        }
    }
}

static void JpegApplyDCT(Work *work, char *pIn, int *pOut)
{
    int      *field_84;
    int      *field_84_ptr;
    TMat8x8I *field_84_ptr2;

    int i;
    int j;
    int k;

    signed char *arg1_ptr;
    int          camIndex;
    int          accumulator;

    field_84 = (int *)work->field_84;
    field_84 += 256;
    field_84_ptr = field_84;

    i = 0;
    for (; i < 8; i++)
    {
        j = 0;
        for (; j < 8; j++)
        {
            arg1_ptr = pIn;
            *field_84_ptr = 0;
            k = 0;
            camIndex = j;
            for (; k < 8; k++)
            {
                *field_84_ptr += arg1_ptr[k] * gJpegcamMatrix2_800BDCD8[k][camIndex];
            }
            field_84_ptr++;
        }
        pIn += 8;
    }

    i = 0;
    for (; i < 8; i++)
    {
        j = 0;
        for (; j < 8; j++)
        {
            k = accumulator = 0;
            field_84_ptr2 = (TMat8x8I *)field_84;
            for (; k < 8; k++)
            {
                accumulator += gJpegcamMatrix1_8009F36C[i][k] * (*field_84_ptr2)[k][j];
            }
            *(pOut++) = (accumulator >> 14);
        }
    }
}

static void JpegQuantizeZigzagMatrix(int *pIn, int *pOut, int q_scale)
{
    signed char *pZigzag;
    int i;

    *pOut++ = pIn[0] / gJpegcamQuantTable_8009F32C[0];
    pZigzag = &gJpegcamZigZagTable_8009F2EC[1];

    for (i = 1; i < 64; i++, pZigzag++)
    {
        *pOut++ = (pIn[*pZigzag] * 16) / (gJpegcamQuantTable_8009F32C[*pZigzag] * q_scale);
    }
}

static int JpegRLEStream(Work *work, int *pData, int q_scale)
{
    int count;
    int i;
    int end;
    int zeros;
    unsigned short temp_a1;
    short temp_v0;
    unsigned char new_var2;

    count = 62;

    q_scale <<= 10;
    temp_a1 = (*pData & 0x3FF) | q_scale;

    work->field_88[work->field_80++] = temp_a1 >> 8;
    work->field_88[work->field_80++] = temp_a1;
    work->field_7C += 2;

    for (i = 1, end = 1; i < count; i++, end++)
    {
        zeros = 0;

        while ((pData[i] == 0) && (i < count))
        {
            zeros++;
            i++;
        }

        q_scale = zeros;
        if (i == count)
        {
            break;
        }

        temp_a1 = pData[i];

        if ((q_scale < 7) && ((short)temp_a1 < 7) && ((short)temp_a1 >= -8))
        {
            new_var2 = (temp_a1 + (q_scale << 4)) + 8;
            work->field_88[work->field_80++] = new_var2;
            work->field_7C++;
        }
        else
        {
            temp_v0 = temp_a1 + 256;

            if (temp_v0 < 0)
            {
                temp_v0 = 0;
            }

            temp_a1 = (q_scale << 9) | 0x8000 | (temp_v0 & 0x1FF);

            work->field_88[work->field_80++] = temp_a1 >> 8;
            work->field_88[work->field_80++] = temp_a1;
            work->field_7C += 2;
        }
    }

    work->field_88[work->field_80++] = 15;
    work->field_7C++;

    do { return end + 1; } while (0);
}

static int JpegCompressMacroblock(Work *work, char *pStream, int q_scale)
{
    char *pY1;
    char *pY2;
    char *pY3;
    char *pY4;
    char *pU;
    char *pV;

    char *pData;
    int  *pDctResult;
    int  *pQuantZagResult;
    char *pBlocks[6];
    int   processed;
    int   i;

    pData = work->field_84;

    pY1 = pData + 0x300;
    pY2 = pData + 0x340;
    pY3 = pData + 0x380;
    pY4 = pData + 0x3C0;
    pU = pData + 0x400;
    pV = pData + 0x440;

    work->field_84 += 0x680;

    pDctResult = (int *)(pData + 0x480);
    pQuantZagResult = (int *)(pData + 0x580);

    pBlocks[0] = pU;
    pBlocks[1] = pV;
    pBlocks[2] = pY1;
    pBlocks[3] = pY2;
    pBlocks[4] = pY3;
    pBlocks[5] = pY4;

    JpegMacroblock_RGB_to_YUV(pStream, pData, pData + 0x100, pData + 0x200);
    JpegSplitLumaBlocks((TMat16x16B *)pData, (TMat8x8B *)pY1, (TMat8x8B *)pY2, (TMat8x8B *)pY3, (TMat8x8B *)pY4);
    JpegDownsampleChroma420(pData + 0x100, pData + 0x200, pU, pV);

    processed = 0;

    for (i = 0; i < 6; i++)
    {
        JpegApplyDCT(work, pBlocks[i], pDctResult);
        JpegQuantizeZigzagMatrix(pDctResult, pQuantZagResult, q_scale * 2);
        processed += JpegRLEStream(work, pQuantZagResult, q_scale);
    }

    return processed;
}

#define ROUND(x, a) ((((x) / (a)) + 1) * (a)) /* Round up `x` to next multiple of `a` */

static int JpegCompressFrame(Work *work, RECT *pRect, int q_scale)
{
    RECT rect;
    int processed;
    unsigned short *pColorCvtSrc;
    char *f84;
    char *pColorCvtDst;
    int x, y;
    short w, h;
    int words;

    processed = 0;

    pColorCvtDst = work->field_84;
    pColorCvtSrc = (unsigned short *)(work->field_84 + 1024);
    work->field_84 += 1536;
    f84 = work->field_84;


    rect.x = 0;
    rect.y = 0;
    rect.w = 16;
    rect.h = 16;

    w = pRect->w / 16;
    h = pRect->h / 16;

    for (x = 0; x < w; x++)
    {
        rect.x = pRect->x + x * 16;

        for (y = 0; y < h; y++)
        {
            work->field_84 = f84;
            rect.y = pRect->y + y * 16;
            StoreImage(&rect, (u_long *)pColorCvtSrc);
            JpegColorCvt_XBGR1555_to_BGRX8888(pColorCvtSrc, pColorCvtDst);
            processed += JpegCompressMacroblock(work, pColorCvtDst, q_scale);
        }
    }

    processed = ROUND(processed, 64);
    words = processed / 2;

    work->field_88[0] = words >> 8;
    work->field_88[1] = words;
    work->field_88[work->field_80] = 15;

    return processed * 2;
}

static void JpegTryCompressFrame(Work *work)
{
    int q_scale;
    int iteration;
    RECT rect;
    q_scale = 5;
    iteration = 1;
    rect.x = 16;
    rect.y = 16;
    rect.w = 288;
    rect.h = 176;
    work->field_8C_size = 20000;

    do {
        work->field_7C = 0;
        work->field_80 = 2;

        // Not matching with a pointer to the global array
        work->field_84 = (char *)0x801B1000;
        work->field_88 = (char *)0x801A1000;

        work->field_8C_size = JpegCompressFrame(work, &rect, q_scale);
        printf("%d try q_scale = %d size = %d\n", iteration, q_scale, work->field_8C_size);
        iteration++;
        q_scale++;

        if (work->field_8C_size > 20000)
        {
            q_scale++;
        }
    }
    while (work->field_8C_size > 16124u);
}

/******************************************************************************
 * camera item logic
 */

static int JpegcamGetZoomLimit(Work *work)
{
    MATRIX  world;
    SVECTOR vector1;
    SVECTOR vector2;
    int     retval;
    int     cond;

    if (GM_GameStatus < 0)
    {
        retval = 3200;
    }
    else
    {
        world = GM_PlayerBody->objs->world;
        world.t[0] = gUnkCameraStruct_800B77B8.eye.vx;
        world.t[1] = gUnkCameraStruct_800B77B8.eye.vy;
        world.t[2] = gUnkCameraStruct_800B77B8.eye.vz;
        DG_SetPos(&world);

        DG_PutVector(dword_8009F3AC, &vector1, 2);

        cond = 0;
        if (HZD_LineCheck(work->map->hzd, &vector1, &vector2, HZD_CHECK_ALL, 0x81) != 0)
        {
            HZD_80028890(&vector2);
            cond = 1;
        }

        retval = 3200;
        if (cond != 0)
        {
            GV_SubVec3(&vector2, &vector1, &vector1);
            retval = GV_VecLen3(&vector1);
        }
    }
    return retval;
}

static void JpegcamProcessInput(Work *work)
{
    SVECTOR vec;
    u_short status;
    u_short press;
    int zoom;
    int vx, vy;
    int zoom_adj;
    int zoom_lim;
    int xmin, xmax;
    int speed;

    status = work->pad_data->status;
    press = work->pad_data->press;

    GM_CheckShukanReverse(&status);
    GM_CheckShukanReverse(&press);

    if (GV_PauseLevel != 0)
    {
        status = 0;
        press = 0;
    }

    if (!(GM_PlayerBody->objs->flag & DG_FLAG_INVISIBLE))
    {
        status = 0;
        press = 0;
    }

    if ((GM_Camera.first_person != 1) || (GM_Camera.flags & 0x100))
    {
        status = 0;
        press = 0;
    }

    if (dword_8009F604 != CMD_camera)
    {
        status = 0;
        press = 0;
    }

    if (GM_PlayerStatus & PLAYER_PAD_OFF)
    {
        status = 0;
        press = 0;
    }

    zoom = GM_Camera.zoom;

    if (GM_PlayerControl)
    {
        vx = work->field_5C_ang.vx;

        if (vx < dword_800ABBDC)
        {
            vx = dword_800ABBDC;
        }
        else if (vx > dword_800ABBD4)
        {
            vx = dword_800ABBD4;
        }

        work->field_5C_ang.vx = vx;
    }

    if (status & (PAD_LEFT | PAD_DOWN | PAD_RIGHT | PAD_UP))
    {
        vx = work->field_5C_ang.vx;
        vy = work->field_5C_ang.vy;

        vec = work->field_54_vec;

        if (GM_PlayerControl)
        {
            vec.vx = GM_PlayerControl->turn.vx;
        }

        if (zoom >= 1024)
        {
            speed = 1;

            if (zoom < 2048)
            {
                speed = 4;
            }
        }
        else
        {
            speed = 16;
        }

        xmin = vec.vx - 512;
        xmax = vec.vx + 512;

        if (GM_PlayerControl)
        {
            if (xmin < dword_800ABBDC)
            {
                xmin = dword_800ABBDC;
            }

            if (xmax > dword_800ABBD4)
            {
                xmax = dword_800ABBD4;
            }
        }

        if (status & (PAD_DOWN | PAD_UP))
        {
            if (status & PAD_UP)
            {
                vx -= speed;
            }
            else
            {
                vx += speed;
            }
        }

        if (vx < xmin)
        {
            vx = xmin;
        }

        if (vx > xmax)
        {
            vx = xmax;
        }

        if (status & (PAD_LEFT | PAD_RIGHT))
        {
            if (status & PAD_RIGHT)
            {
                vy -= speed;
            }
            else
            {
                vy += speed;
            }

            vy &= 0xFFF;
        }

        work->field_5C_ang.vx = vx;
        work->field_5C_ang.vy = vy;
    }

    zoom_adj = 3200;

    if (status & 0xF060)
    {
        zoom_lim = JpegcamGetZoomLimit(work);

        if (zoom_lim < 3200)
        {
            zoom_adj = zoom_lim;
        }

        if (zoom_lim < 320)
        {
            zoom_adj = 320;
        }

        if (zoom > zoom_adj)
        {
            zoom = zoom_adj;
        }
    }

    if ((status & (PAD_CROSS | PAD_CIRCLE)) && (((status & PAD_CIRCLE) && (zoom != zoom_adj)) || ((status & PAD_CROSS) && (zoom != 320))))
    {
        if ((status & PAD_CIRCLE) && (zoom != zoom_adj))
        {
            zoom += zoom / 32;

            if (zoom >= zoom_adj)
            {
                zoom = zoom_adj;
            }
        }
        else if ((status & PAD_CROSS) && (zoom != 320))
        {
            zoom -= zoom / 32;

            if (zoom <= 320)
            {
                zoom = 320;
            }
        }

        if (GV_PauseLevel == 0)
        {
            if ((work->field_68 & 0x3) == 0)
            {
                GM_SeSet2(0, 63, SE_SCOPE_ZOOM);
            }

            work->field_68++;
        }
    }

    if (press & PAD_SQUARE)
    {
        if (!(GM_GameStatus & STATE_VOX_STREAM))
        {
            work->field_70 = 1;
            JpegInitMatrix(work);
            work->state = 0;
            work->field_68 = 0;
            GM_GameStatus |= STATE_TAKING_PHOTO;

            if (!(GV_PauseLevel & 1))
            {
                GV_PauseLevel |= 4;
            }

            if (work->field_90_pSight)
            {
                GV_DestroyActor(work->field_90_pSight);
            }
        }
        else
        {
            GM_SeSet2(0, 63, SE_BUZZER);
        }
    }

    GM_Camera.zoom = zoom;
}

/**
 * Check if the player is standing in a ghost photo spot.
 */
static int JpegcamCheckShinreiSpot(Work *work)
{
    int retval;

    printf("Sinrei Syasin Check Start\n");  // 心霊写真 (lit. "ghost photo")
    if (GM_Photocode != 0)
    {
        printf("Here is Sinrei Spot!\n");
        printf("GM_Photocode = %d\n", GM_Photocode);

        retval = DG_PointCheckOne((DVECTOR *)&GM_PhotoViewPos);
        printf("Point Check\n");

        printf("Result = %d\n", retval);
    }
    else
    {
        printf("Not Sinrei Spot!\n");
        retval = 0;
    }
    return retval;
}

static void JpegcamTakePhoto(Work *work)
{
    int state = work->state;

    if (state < 3)
    {
        return;
    }

    if (state == 3)
    {
        GM_SeSet2(0, 63, SE_PHOTO_SHUTTER);
    }
    else if (state == 4)
    {
        GV_PauseLevel &= ~4;
        GV_PauseLevel |= 1;
        DG_FreeObjectQueue();
        GV_SetPacketTempMemory();
        DG_UnDrawFrameCount = 1;
    }
    else if (state < 9)
    {
        DG_ClipDispEnv(256, (state - 4) * 56);
        DG_UnDrawFrameCount = 1;
    }
    else if (state == 9)
    {
        JpegTryCompressFrame(work);

        if (JpegcamCheckShinreiSpot(work) == 1)
        {
            dword_800BDCD0 = GM_Photocode;
        }
        else
        {
            dword_800BDCD0 = 0;
        }

        menu_radio_8004D2FC(&stru_8009F2D8);
        DG_UnDrawFrameCount = 1;
        dword_800BDCC8 = work->field_88;
        dword_800BDCCC = work->field_8C_size;
    }
    else if (state == 10)
    {
        if (!menu_radio_8004D334(work->pad_data))
        {
            --work->state;
        }
    }
    else if (state == 11)
    {
        work->field_70 = 0;
        menu_radio_8004D35C();
        GM_GameStatus &= ~STATE_TAKING_PHOTO;
        GV_ResetPacketMemory();
        GV_PauseLevel &= ~1;
        DG_RestartMainChanlSystem();
        work->state = 0;
        work->field_90_pSight = NewSight(CAMERA_SIGHT2, CAMERA_SIGHT, &GM_CurrentItemId, IT_Camera, NULL);
    }
}

/******************************************************************************
 * standard actor functions
 */

static void Act(Work *work)
{
    OBJECT         *parent;
    OBJECT_NO_ROTS *object;

    if (GM_PlayerStatus & PLAYER_SECOND_CONTROLLER)
    {
        work->pad_data = &GV_PadData[3];
    }
    else
    {
        work->pad_data = &GV_PadData[2];
    }

    if (work->field_98 < 16)
    {
        work->field_98++;
    }

    if (!work->field_94_bMakeVisible)
    {
        parent = work->parent;
        if (parent->objs->flag & DG_FLAG_INVISIBLE)
        {
            object = &work->goggles;
            GM_InitObjectNoRots(object, GV_StrCode("goggles"), 109, 0);
            if (work->goggles.objs)
            {
                GM_ConfigObjectRoot((OBJECT *)object, parent, 6);
                GM_ConfigObjectLight((OBJECT *)object, parent->light);
                EQ_InvisibleHead(parent, &work->head_saved_packs, &work->head_saved_raise);
                work->field_94_bMakeVisible = 1;
            }
        }
    }

    if (work->field_94_bMakeVisible)
    {
        GM_SetCurrentMap(work->control->map->index);

        DG_GroupObjs(work->goggles.objs, DG_CurrentGroupID);

        if (GM_PlayerStatus & PLAYER_NOT_SIGHT)
        {
            if ( !(work->parent->objs->flag & DG_FLAG_INVISIBLE) )
            {
                DG_VisibleObjs(work->goggles.objs);
            }
            GM_Camera.zoom = 320;
            return;
        }

        DG_InvisibleObjs(work->goggles.objs);
    }

    if (GM_LoadRequest)
    {
        if ((work->field_70 == 1) && (work->state < 4))
        {
            GV_PauseLevel &= ~4;
        }

        GV_DestroyActor(&work->actor);
        return;
    }

    if (GM_GameOverTimer)
    {
        return;
    }

    switch (work->field_70)
    {
    case 0:
        if (GV_PauseLevel)
        {
            return;
        }

        JpegcamProcessInput(work);

        if (dword_8009F604 != CAMERA_SIGHT)
        {
            NewSight(CAMERA_SIGHT, CAMERA_SIGHT, &GM_CurrentItemId, IT_Camera, NULL);
            work->field_90_pSight = NewSight(CAMERA_SIGHT2, CAMERA_SIGHT, &GM_CurrentItemId, IT_Camera, NULL);
            GM_SeSet2(0, 63, SE_ITEM_OPENWINDOW);
        }

        if ( !(GM_PlayerStatus & PLAYER_NOT_SIGHT) )
        {
            MENU_Locate(200, 25, 0);
            MENU_Color(192, 144, 128);
            MENU_Printf("zoom  : %4d\n", GM_Camera.zoom);
            MENU_Printf("angle : %4d, %4d\n", -work->field_5C_ang.vx, work->field_5C_ang.vy);
        }
        break;

    case 1:
        if ((work->state < 5) && (GV_PauseLevel & 1))
        {
            work->state = 0;
            return;
        }

        JpegcamTakePhoto(work);
        break;
    }

    work->state++;

    GM_PlayerControl->rot = work->field_5C_ang;
    GM_PlayerControl->turn = work->field_5C_ang;
}

static void Die(Work *work)
{
    GM_Camera.zoom = 320;
    gUnkCameraStruct_800B77B8.rotate2 = work->field_54_vec;

    GM_GameStatus &= ~STATE_JPEGCAM;
    GM_GameStatus &= ~STATE_TAKING_PHOTO;

    if (work->field_94_bMakeVisible != 0)
    {
        EQ_VisibleHead(work->parent, &work->head_saved_packs, &work->head_saved_raise);
        GM_FreeObject((OBJECT *)&work->goggles);
    }
}

static int GetResources(Work *work, CONTROL *control, OBJECT *parent)
{
    work->parent = parent;
    work->pad_data = &GV_PadData[2];
    work->field_54_vec = control->rot;
    work->field_5C_ang = work->field_54_vec;
    work->state = 0;
    work->field_68 = 0;
    work->map = control->map;
    work->field_70 = 0;
    work->field_98 = 0;
    GM_GameStatus |= STATE_JPEGCAM;
    return 0;
}

/******************************************************************************
 * public functions
 */

void *NewJpegcam(CONTROL *control, OBJECT *parent, int num_parent)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "jpegcam.c");
        if (GetResources(work, control, parent) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        work->control = control;
    }

    return (void *)work;
}
