#include "jpegcam.h"
#include "psyq.h"
#include "chara/snake/sna_init.h"
#include "Game/camera.h"
#include "Game/object.h"
#include "Game/linkvarbuf.h"
#include "Menu/menuman.h"
#include "libgcl/hash.h"
#include "memcard/memcard.h"

extern PlayerStatusFlag    GM_PlayerStatus_800ABA50;
extern int                 DG_CurrentGroupID_800AB968;
extern GM_Camera           GM_Camera_800B77E8;
extern CONTROL         *gSnaControl_800AB9F4;
extern int                 dword_8009F604;
extern int                 GM_LoadRequest_800AB3D0;
extern int                 GM_GameOverTimer_800AB3D4;
extern GV_PAD              GV_PadData_800B05C0[4];
extern TMat8x8B            gJpegcamMatrix1_8009F36C;
extern TMat8x8B            gJpegcamMatrix2_800BDCD8;
extern signed char         gJpegcamZigZagTable_8009F2EC[64];
extern signed char         gJpegcamQuantTable_8009F32C[64];
extern UnkCameraStruct     gUnkCameraStruct_800B77B8;
extern OBJECT             *dword_800ABA20;
extern SVECTOR             dword_8009F3AC;
extern int                 GM_Photocode_800ABA04;
extern SVECTOR             GM_PhotoViewPos_800ABA48;
extern int                 GV_PauseLevel_800AB928;
extern char               *dword_800BDCC8;
extern int                 dword_800BDCCC;
extern int                 dword_800BDCD0;
extern int                 DG_UnDrawFrameCount_800AB380;
extern UnkCameraStruct     gUnkCameraStruct_800B77B8;
extern menu_save_mode_data stru_8009F2D8;

extern short dword_800ABBD4;
short        SECTION(".sbss") dword_800ABBD4;

extern short dword_800ABBDC;
short        SECTION(".sbss") dword_800ABBDC;

extern char aBislpm99999[];          // = "BISLPM-99999        "

extern const char aPHOTO[];          // = "PHOTO %02d\n"
extern const char aJpegcamC[];       // = "jpegcam.c"
extern const char aGoggles[];        // = "goggles"
extern const char aSSSS[];           // = "%s%s%s%s"
extern const char aMGSIntegralEUC[]; // = "ＭＧＳ∫"
extern const char aSpaceEUC[];       // = "　"
extern const char aPhotoEUC[];       // = "ＰＨＯＴＯ"
extern const char aZoom4d[];         // = "zoom  : %4d\n"
extern const char aAngle4d4d[];      // = "angle : %4d, %4d\n"
extern const char aDTryQScaleDSiz[]; // = "%d try q_scale = %d size = %d\n"
extern const char aSaveHeaderX[];    // = "save header = %x\n"
extern const char aSinreiSyasinCh[]; // = "Sinrei Syasin Check Start\n"
extern const char aHereIsSinreiSp[]; // = "Here is Sinrei Spot!\n"
extern const char aGmPhotocodeD[];   // = "GM_Photocode = %d\n"
extern const char aPointCheck[];     // = "Point Check\n"
extern const char aResultD[];        // = "Result = %d\n"
extern const char aNotSinreiSpot[];  // = "Not Sinrei Spot!\n"

void jpegcam_unk1_80063704(char *buf, struct mem_card *pMemcard)
{
    char photo_id[8];
    unsigned int blocks_avail;
    int index;

    aBislpm99999[12] = 'C';

    blocks_avail = 0;

    for (index = 0; index < pMemcard->field_2_file_count; index++)
    {
        if (strncmp_8008E7F8(pMemcard->field_4_blocks[index].field_0_name, aBislpm99999, 13) == 0)
        {
            blocks_avail |= 1 << (pMemcard->field_4_blocks[index].field_0_name[18] - 64);
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

    sprintf_8008E878(buf, aSSSS, aMGSIntegralEUC, aSpaceEUC, aPhotoEUC, photo_id);
}

void jpegcam_unk2_80063888(char *param_1, int param_2)
{
    sprintf_8008E878(param_1, aPHOTO, *(char *)(param_2 + 6) - 0x40);
}

void jpegcam_unk3_800638B4(int *arg0)
{
    dword_800BDCD0 = (char)dword_800BDCD0 | 0x80808000;
    mts_printf_8008BBA0(aSaveHeaderX, dword_800BDCD0);

    GV_CopyMemory_800160D8(&dword_800BDCD0, &arg0[0], 4);
    GV_CopyMemory_800160D8(dword_800BDCC8, &arg0[1], dword_800BDCCC);
}

void jpegcam_act_helper2_helper_8006392C(Actor_jpegcam *pActor)
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

void jpegcam_act_colorcvt_xbgr1555_to_bgrx8888_80063988(unsigned short *pSrc, char *pDst)
{
    int i;

    for (i = 0; i < 256; i++, pDst += 4, pSrc++)
    {
        pDst[2] = (*pSrc << 3) & 0xF8;
        pDst[1] = (*pSrc >> 2) & 0xF8;
        pDst[0] = (*pSrc >> 7) & 0xF8;
    }
}

void jpegcam_act_macroblock_rgb_to_yuv_800639E8(char *pStream, char *pY, char *pU, char *pV)
{
    int i;
    int r, g, b;

    for (i = 0; i < 256; i++, pStream += 4)
    {
        r = pStream[0];
        g = pStream[1];
        b = pStream[2];

        *pY++ = (r *   299 + g *   587 + b *  114) / 1000 + 128;
        *pU++ = (r * -1687 + g * -3313 + b * 5000) / 10000;
        *pV++ = (r *  5000 - g *  4187 - b *  813) / 10000;
    }
}

void jpegcam_act_split_luma_blocks_80063B94(TMat16x16B *pSrcY, TMat8x8B *pY1, TMat8x8B *pY2, TMat8x8B *pY3, TMat8x8B *pY4)
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

void jpegcam_act_downsample_chroma420_80063C10(char *pInU, char *pInV, char *pOutU, char *pOutV)
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

void jpegcam_act_apply_dct_80063CD0(Actor_jpegcam *pActor, char *pIn, int *pOut)
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

    field_84 = (int *)pActor->field_84;
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

void jpegcam_act_quantize_zigzag_matrix_80063DDC(int *pIn, int *pOut, int q_scale)
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

int jpegcam_act_rle_stream_80063EB0(Actor_jpegcam *pActor, int *pData, int q_scale)
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

    pActor->field_88[pActor->field_80++] = temp_a1 >> 8;
    pActor->field_88[pActor->field_80++] = temp_a1;
    pActor->field_7C += 2;

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
            pActor->field_88[pActor->field_80++] = new_var2;
            pActor->field_7C++;
        }
        else
        {
            temp_v0 = temp_a1 + 256;

            if (temp_v0 < 0)
            {
                temp_v0 = 0;
            }

            temp_a1 = (q_scale << 9) | 0x8000 | (temp_v0 & 0x1FF);

            pActor->field_88[pActor->field_80++] = temp_a1 >> 8;
            pActor->field_88[pActor->field_80++] = temp_a1;
            pActor->field_7C += 2;
        }
    }

    pActor->field_88[pActor->field_80++] = 15;
    pActor->field_7C++;

    do { return end + 1; } while (0);
}

int jpegcam_act_compress_macroblock_80064054(Actor_jpegcam *pActor, char *pStream, int q_scale)
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

    pData = pActor->field_84;

    pY1 = pData + 0x300;
    pY2 = pData + 0x340;
    pY3 = pData + 0x380;
    pY4 = pData + 0x3C0;
    pU = pData + 0x400;
    pV = pData + 0x440;

    pActor->field_84 += 0x680;

    pDctResult = (int *)(pData + 0x480);
    pQuantZagResult = (int *)(pData + 0x580);

    pBlocks[0] = pU;
    pBlocks[1] = pV;
    pBlocks[2] = pY1;
    pBlocks[3] = pY2;
    pBlocks[4] = pY3;
    pBlocks[5] = pY4;

    jpegcam_act_macroblock_rgb_to_yuv_800639E8(pStream, pData, pData + 0x100, pData + 0x200);
    jpegcam_act_split_luma_blocks_80063B94((TMat16x16B *)pData, (TMat8x8B *)pY1, (TMat8x8B *)pY2, (TMat8x8B *)pY3, (TMat8x8B *)pY4);
    jpegcam_act_downsample_chroma420_80063C10(pData + 0x100, pData + 0x200, pU, pV);

    processed = 0;

    for (i = 0; i < 6; i++)
    {
        jpegcam_act_apply_dct_80063CD0(pActor, pBlocks[i], pDctResult);
        jpegcam_act_quantize_zigzag_matrix_80063DDC(pDctResult, pQuantZagResult, q_scale * 2);
        processed += jpegcam_act_rle_stream_80063EB0(pActor, pQuantZagResult, q_scale);
    }

    return processed;
}

#define ROUND(x, a) ((((x) / (a)) + 1) * (a)) /* Round up `x` to next multiple of `a` */

int jpegcam_act_compress_frame_800641C0(Actor_jpegcam *pActor, RECT *pRect, int q_scale)
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

    pColorCvtDst = pActor->field_84;
    pColorCvtSrc = (unsigned short *)(pActor->field_84 + 1024);
    pActor->field_84 += 1536;
    f84 = pActor->field_84;


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
            pActor->field_84 = f84;
            rect.y = pRect->y + y * 16;
            StoreImage_8008FB70(&rect, (u_long *)pColorCvtSrc);
            jpegcam_act_colorcvt_xbgr1555_to_bgrx8888_80063988(pColorCvtSrc, pColorCvtDst);
            processed += jpegcam_act_compress_macroblock_80064054(pActor, pColorCvtDst, q_scale);
        }
    }

    processed = ROUND(processed, 64);
    words = processed / 2;

    pActor->field_88[0] = words >> 8;
    pActor->field_88[1] = words;
    pActor->field_88[pActor->field_80] = 15;

    return processed * 2;
}

void jpegcam_act_try_compress_frame_80064378(Actor_jpegcam *pActor)
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
  pActor->field_8C_size = 20000;
  do
  {
    pActor->field_7C = 0;
    pActor->field_80 = 2;

    // Not matching with a pointer to the global array
    pActor->field_84 = (char *)0x801B1000;
    pActor->field_88 = (char *)0x801A1000;

    pActor->field_8C_size = jpegcam_act_compress_frame_800641C0(pActor, &rect, q_scale);
    mts_printf_8008BBA0(aDTryQScaleDSiz, iteration, q_scale, pActor->field_8C_size);
    iteration++;
    q_scale++;
    if (pActor->field_8C_size > 20000)
    {
      q_scale++;
    }
  }
  while (pActor->field_8C_size > 16124u);
}

int jpegcam_act_helper2_helper2_80064454(Actor_jpegcam *pActor)
{

    MATRIX  mtx;
    SVECTOR vector1;
    SVECTOR vector2;
    int     retval;
    int     cond;

    if (GM_GameStatus_800AB3CC < 0)
    {
        retval = 3200;
    }
    else
    {
        mtx = dword_800ABA20->objs->world;
        mtx.t[0] = gUnkCameraStruct_800B77B8.field_0.vx;
        mtx.t[1] = gUnkCameraStruct_800B77B8.field_0.vy;
        mtx.t[2] = gUnkCameraStruct_800B77B8.field_0.vz;
        DG_SetPos_8001BC44(&mtx);

        DG_PutVector_8001BE48(&dword_8009F3AC, &vector1, 2);

        cond = 0;
        if (sub_80028454(pActor->field_6C_pMap->field_8_hzd, &vector1, &vector2, 0xf, 0x81) != 0)
        {
            sub_80028890(&vector2);
            cond = 1;
        }

        retval = 3200;
        if (cond != 0)
        {
            GV_SubVec3_80016D40(&vector2, &vector1, &vector1);
            retval = GV_VecLen3_80016D80(&vector1);
        }
    }
    return retval;
}

void jpegcam_act_process_input_80064588(Actor_jpegcam *pActor)
{
    SVECTOR vec;
    unsigned short status;
    unsigned short press;
    int zoom;
    int vx, vy;
    int zoom_adj;
    int zoom_lim;
    int xmin, xmax;
    int speed;

    status = pActor->field_50_pInput->status;
    press = pActor->field_50_pInput->press;

    GM_CheckShukanReverse_8004FBF8(&status);
    GM_CheckShukanReverse_8004FBF8(&press);

    if (GV_PauseLevel_800AB928 != 0)
    {
        status = 0;
        press = 0;
    }

    if (!(dword_800ABA20->objs->flag & DG_FLAG_INVISIBLE))
    {
        status = 0;
        press = 0;
    }

    if ((GM_Camera_800B77E8.field_22 != 1) || (GM_Camera_800B77E8.field_18_flags & 0x100))
    {
        status = 0;
        press = 0;
    }

    if (dword_8009F604 != HASH_CMD_camera)
    {
        status = 0;
        press = 0;
    }

    if (GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF)
    {
        status = 0;
        press = 0;
    }

    zoom = GM_Camera_800B77E8.field_20;

    if (gSnaControl_800AB9F4)
    {
        vx = pActor->field_5C_ang.vx;

        if (vx < dword_800ABBDC)
        {
            vx = dword_800ABBDC;
        }
        else if (vx > dword_800ABBD4)
        {
            vx = dword_800ABBD4;
        }

        pActor->field_5C_ang.vx = vx;
    }

    if (status & (PAD_LEFT | PAD_DOWN | PAD_RIGHT | PAD_UP))
    {
        vx = pActor->field_5C_ang.vx;
        vy = pActor->field_5C_ang.vy;

        vec = pActor->field_54_vec;

        if (gSnaControl_800AB9F4)
        {
            vec.vx = gSnaControl_800AB9F4->field_4C_turn_vec.vx;
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

        if (gSnaControl_800AB9F4)
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

        pActor->field_5C_ang.vx = vx;
        pActor->field_5C_ang.vy = vy;
    }

    zoom_adj = 3200;

    if (status & 0xF060)
    {
        zoom_lim = jpegcam_act_helper2_helper2_80064454(pActor);

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

        if (GV_PauseLevel_800AB928 == 0)
        {
            if ((pActor->field_68 & 0x3) == 0)
            {
                GM_SeSet2_80032968(0, 63, 36);
            }

            pActor->field_68++;
        }
    }

    if (press & PAD_SQUARE)
    {
        if (!(GM_GameStatus_800AB3CC & 0x20))
        {
            pActor->field_70 = 1;
            jpegcam_act_helper2_helper_8006392C(pActor);
            pActor->field_64_state = 0;
            pActor->field_68 = 0;
            GM_GameStatus_800AB3CC |= 0x400;

            if (!(GV_PauseLevel_800AB928 & 0x1))
            {
                GV_PauseLevel_800AB928 |= 0x4;
            }

            if (pActor->field_90_pSight)
            {
                GV_DestroyActor_800151C8(&pActor->field_90_pSight->field_0_actor);
            }
        }
        else
        {
            GM_SeSet2_80032968(0, 63, 35);
        }
    }

    GM_Camera_800B77E8.field_20 = zoom;
}

int jpegcam_act_helper3_helper2_800649F4(Actor_jpegcam *pActor)
{
    int retval;

    mts_printf_8008BBA0(aSinreiSyasinCh);
    if (GM_Photocode_800ABA04 != 0)
    {
        mts_printf_8008BBA0(aHereIsSinreiSp);
        mts_printf_8008BBA0(aGmPhotocodeD, GM_Photocode_800ABA04);

        retval = DG_PointCheckOne_8001C18C((DVECTOR *)&GM_PhotoViewPos_800ABA48);
        mts_printf_8008BBA0(aPointCheck);

        mts_printf_8008BBA0(aResultD, retval);
    }
    else
    {
        mts_printf_8008BBA0(aNotSinreiSpot);
        retval = 0;
    }
    return retval;
}

void jpegcam_act_helper3_80064A94(Actor_jpegcam *pActor)
{
    int state = pActor->field_64_state;

    if (state < 3)
    {
        return;
    }

    if (state == 3)
    {
        GM_SeSet2_80032968(0, 63, 17);
    }
    else if (state == 4)
    {
        GV_PauseLevel_800AB928 &= ~0x4;
        GV_PauseLevel_800AB928 |= 0x1;
        DG_FreeObjectQueue_800183D4();
        GV_SetPacketTempMemory_80014C28();
        DG_UnDrawFrameCount_800AB380 = 1;
    }
    else if (state < 9)
    {
        DG_ClipDispEnv_800177EC(256, (state - 4) * 56);
        DG_UnDrawFrameCount_800AB380 = 1;
    }
    else if (state == 9)
    {
        jpegcam_act_try_compress_frame_80064378(pActor);

        if (jpegcam_act_helper3_helper2_800649F4(pActor) == 1)
        {
            dword_800BDCD0 = GM_Photocode_800ABA04;
        }
        else
        {
            dword_800BDCD0 = 0;
        }

        menu_radio_8004D2FC(&stru_8009F2D8);
        DG_UnDrawFrameCount_800AB380 = 1;
        dword_800BDCC8 = pActor->field_88;
        dword_800BDCCC = pActor->field_8C_size;
    }
    else if (state == 10)
    {
        if (!menu_radio_8004D334(pActor->field_50_pInput))
        {
            --pActor->field_64_state;
        }
    }
    else if (state == 11)
    {
        pActor->field_70 = 0;
        menu_radio_8004D35C();
        GM_GameStatus_800AB3CC &= ~0x400;
        GV_ResetPacketMemory_80014BD8();
        GV_PauseLevel_800AB928 &= ~0x1;
        DG_8001844C();
        pActor->field_64_state = 0;
        pActor->field_90_pSight = NewSight_80071CDC(SGT_CAMERA_2, SGT_CAMERA, &GM_CurrentItemId, 12, 0);
    }
}

void jpegcam_act_80064C50(Actor_jpegcam *pActor)
{
    OBJECT *pParent;
    OBJECT *pGoggleObject;

    if (GM_PlayerStatus_800ABA50 & PLAYER_USING_CONTROLLER_PORT_2)
    {
        pActor->field_50_pInput = &GV_PadData_800B05C0[3];
    }
    else
    {
        pActor->field_50_pInput = &GV_PadData_800B05C0[2];
    }

    if (pActor->field_98 < 16)
    {
        pActor->field_98++;
    }

    if (!pActor->field_94_bMakeVisible)
    {
        pParent = pActor->field_24_parent;
        if (pParent->objs->flag & DG_FLAG_INVISIBLE)
        {
            pGoggleObject = (OBJECT *)(&pActor->field_28_goggles);
            GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *) pGoggleObject, GV_StrCode_80016CCC(aGoggles), 109, 0);
            if (pActor->field_28_goggles.objs)
            {
                GM_ConfigObjectRoot_80034C5C(pGoggleObject, pParent, 6);
                GM_ConfigObjectLight_80034C44(pGoggleObject, pParent->light);
                EQ_InvisibleHead_80060D5C(pParent, &pActor->field_4c_head_saved_packs, &pActor->field_4e_head_saved_raise);
                pActor->field_94_bMakeVisible = 1;
            }
        }
    }

    if (pActor->field_94_bMakeVisible)
    {
        GM_SetCurrentMap(pActor->field_20_pCtrl->field_2C_map->field_0_map_index_bit);

        DG_GroupObjs(pActor->field_28_goggles.objs, DG_CurrentGroupID_800AB968);

        if (GM_PlayerStatus_800ABA50 & PLAYER_UNK4000000)
        {
            if ( !(pActor->field_24_parent->objs->flag & DG_FLAG_INVISIBLE) )
            {
                DG_VisibleObjs(pActor->field_28_goggles.objs);
            }
            GM_Camera_800B77E8.field_20 = 320;
            return;
        }

        DG_InvisibleObjs(pActor->field_28_goggles.objs);
    }

    if (GM_LoadRequest_800AB3D0)
    {
        if ((pActor->field_70 == 1) && (pActor->field_64_state < 4))
        {
            GV_PauseLevel_800AB928 &= ~4u;
        }

        GV_DestroyActor_800151C8(&pActor->field_0_actor);
        return;
    }

    if (GM_GameOverTimer_800AB3D4)
    {
        return;
    }

    switch (pActor->field_70)
    {
    case 0:
        if (GV_PauseLevel_800AB928)
        {
            return;
        }

        jpegcam_act_process_input_80064588(pActor);

        if (dword_8009F604 != SGT_CAMERA)
        {
            NewSight_80071CDC(SGT_CAMERA, SGT_CAMERA, &GM_CurrentItemId, 12, 0);
            pActor->field_90_pSight = NewSight_80071CDC(SGT_CAMERA_2, SGT_CAMERA, &GM_CurrentItemId, 12, 0);
            GM_SeSet2_80032968(0, 63, 0x15u);
        }

        if ( !(GM_PlayerStatus_800ABA50 & PLAYER_UNK4000000) )
        {
            menu_Text_XY_Flags_80038B34(200, 25, 0);
            menu_Color_80038B4C(192, 144, 128);
            menu_Text_80038C38(aZoom4d, GM_Camera_800B77E8.field_20);
            menu_Text_80038C38(aAngle4d4d, -pActor->field_5C_ang.vx, pActor->field_5C_ang.vy);
        }
        break;

    case 1:
        if ((pActor->field_64_state < 5) && (GV_PauseLevel_800AB928 & 1))
        {
            pActor->field_64_state = 0;
            return;
        }

        jpegcam_act_helper3_80064A94(pActor);
        break;
    }

    pActor->field_64_state++;

    gSnaControl_800AB9F4->field_8_rotator = pActor->field_5C_ang;
    gSnaControl_800AB9F4->field_4C_turn_vec = pActor->field_5C_ang;
}

void jpegcam_kill_80065008(Actor_jpegcam *pActor)
{
    GM_Camera_800B77E8.field_20 = 320;
    gUnkCameraStruct_800B77B8.field_28 = pActor->field_54_vec;

    GM_GameStatus_800AB3CC &= ~0x800;
    GM_GameStatus_800AB3CC &= ~0x400;

    if (pActor->field_94_bMakeVisible != 0)
    {
        EQ_VisibleHead_80060DF0(pActor->field_24_parent, &pActor->field_4c_head_saved_packs,
                                &pActor->field_4e_head_saved_raise);
        GM_FreeObject_80034BF8((OBJECT *)&pActor->field_28_goggles);
    }
}

int jpegcam_loader_80065098(Actor_jpegcam *pActor, CONTROL *pCtrl, OBJECT *pParent)
{
  pActor->field_24_parent = pParent;
  pActor->field_50_pInput = &GV_PadData_800B05C0[2];
  pActor->field_54_vec = pCtrl->field_8_rotator;
  pActor->field_5C_ang = pActor->field_54_vec;
  pActor->field_64_state = 0;
  pActor->field_68 = 0;
  pActor->field_6C_pMap = pCtrl->field_2C_map;
  pActor->field_70 = 0;
  pActor->field_98 = 0;
  GM_GameStatus_800AB3CC |= 0x800;
  return 0;
}

GV_ACT * NewJpegcam_80065118(CONTROL *pCtrl, OBJECT *pParent, int unused)
{
    Actor_jpegcam *pActor;

    pActor = (Actor_jpegcam *)GV_NewActor_800150E4(1, sizeof(Actor_jpegcam));
    if (pActor != NULL)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)jpegcam_act_80064C50,
                                  (TActorFunction)jpegcam_kill_80065008, aJpegcamC);
        if (jpegcam_loader_80065098(pActor, pCtrl, pParent) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return NULL;
        }
        pActor->field_20_pCtrl = pCtrl;
    }

    return &pActor->field_0_actor;
}
