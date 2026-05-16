// Note that there are two "camera.c" actors,
// this is probably not the enemy/camera.c actor.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libpress.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "menu/menuman.h"
#include "menu/radio.h"
#include "memcard/memcard.h"
#include "game/game.h"
#include "linkvar.h"
#include "mts/mts.h"
#include "mts/taskid.h"
#include "sound/g_sound.h"

typedef struct CameraWork
{
    GV_ACT   actor;
    int      f20;
    GV_PAD  *pad;
    int      f28;
    char     padding1[0x4];
    DG_PRIM *prim1, *prim2, *prim3;
    char     padding2[0xA0];
    POLY_FT4 polys[9];
    POLY_FT4 polys2[26];
    int      field_654[4];
    GV_ACT  *field_664[9];
    GV_ACT  *field_688[26];
    char     padding3[0x30];
    void    *f720;
    char     padding4[0x1FC];
    void    *field_920;
    u_long  *field_924_mOrderingTable;
    int      field_928;
    void    *field_92C[2];
    char     padding5[0x4000];
    int      field_4934;
    int      field_4938;
    char     padding6[0xa4];
    int      f49E0;
    char    *f49E4;
} CameraWork;

#define EXEC_LEVEL GV_ACTOR_MANAGER

extern RadioFileModeStru_800ABB7C *camera_dword_800D075C;
extern RECT                        camera_dword_800C389C;
extern char                       *camera_dword_800D0760;
extern char                       *MGS_MemoryCardName; /* in main.c */
extern DATA_INFO                  *camera_dword_800D072C;
extern int                         camera_dword_800C342C;
extern int                         camera_dword_800C3434;
extern int                         camera_dword_800D0764;
extern DATA_INFO                   camera_dword_800C38E0;
extern SPRT                        camera_sprt_800D0780;
extern int                         camera_dword_800D0728;

extern char camera_dword_800C37F8[];
extern int camera_dword_800D0728;
extern int camera_dword_800C3884;
extern int camera_dword_800C3430;
extern void* camera_dword_800D0730;
extern int camera_dword_800D0738;
extern int camera_dword_800D073C;
extern int camera_dword_800D0770;
extern int camera_dword_800D0774;
extern const char camera_aNoplace_800D0110[];
extern const char camera_dword_800D011C[];
extern int camera_dword_800C3218;
extern int camera_dword_800C38D4;
extern const char camera_aOutx_800CFAB4[];
extern const char camera_aChecktextureid_800CFAC0[];
extern const char camera_aThisidisexistsoiclearthisid_800CFAD4[];
extern const char camera_aThisidisnotexist_800CFAFC[];
extern const char camera_aTextureloadimagefinish_800CFB14[];
extern const char camera_aCamexflush_800CFB30[];
extern const char camera_aSssss_800D0120[];
extern const char camera_dword_800D012C[];

extern const char camera_aNomemoryforobj_800CFF80[]; // = "NO MEMORY FOR OBJ\n";
extern const char camera_aNomemoryforfilebody_800CFCF8[];
extern const char camera_aCardnodfilenames_800CFD14[];
extern const char camera_aCloseinfo_800CFFE0[];
extern const char camera_aNomemoryforinfo_800CFFEC[];
extern const char camera_aAllocinfox_800D0000[];
extern const char camera_dword_800CFFC8[];
extern const char camera_aFiles_800D0010[];
extern const char camera_aThisissinreiphoto_800CFB40[];
extern const char camera_aSinreinod_800CFB58[];
extern char camera_aResultx_800CFF48[];
extern char camera_aRequestx_800CFF3C[];
extern char camera_aNomemoryforstack_800CFF54[];
extern const char camera_a_800D0144[];
extern const char camera_aPhotod_800D0138[];
extern int camera_dword_800D0700;
extern int camera_dword_800D0704;
extern char camera_dword_800D0708;
extern char camera_dword_800D0710[];
extern int camera_dword_800C38F4;
extern char camera_dword_800C3438[];
extern int camera_dword_800C3918;
extern int camera_dword_800C3914;
extern int camera_dword_800C391C;
extern int camera_dword_800C3928;
extern const char camera_aOverwriteok_800CFF2C[];
extern const char camera_aNo_800D0090[];
extern const char camera_aYes_800D0094[];
extern const char camera_aResx_800D03E4[];
extern const char camera_aS_800D03F0[];
extern const char camera_aSsss_800D03C4[];
extern const char camera_dword_800D03D0[];
extern const char camera_dword_800D03D8[];
extern const char camera_aFind_800D03F4[];
extern const char camera_aPhaseischangedbutdatafind_800D03FC[];
extern const char camera_aPhaseischanged_800D041C[];
extern const char camera_aPhaseisnotchanged_800D0430[];
extern const char camera_aSavedatadelete_800D0448[];
extern const char camera_aDeletesuccess_800D045C[];
extern const char camera_aNewmemdataget_800D046C[];
extern const char camera_aDeletefail_800D0480[];
extern const char camera_aNewdatacreate_800D0490[];
extern const char camera_aNewdatawrite_800D04A4[];
extern const char camera_aNewdatawriteok_800D04B4[];
extern const char camera_a_800D02DC[];
extern const char camera_a_800D0314[];
extern const char camera_aD_800D0318[];

void camera_800C3ED8(CameraWork *);
int camera_800CDF18(CameraWork *);
void camera_800C8AD4(CameraWork *);
extern int camera_dword_800C3880;
extern int camera_dword_800D0734;
extern int camera_dword_800D0740[];
extern int camera_dword_800D0748[];
extern int camera_dword_800C38A4;
extern int camera_dword_800C38B4;
extern const char camera_aEndsavemode_800D00D0[];
extern const char camera_aEndstated_800D00E0[];
extern const char camera_aLoading_800D0068[];
extern const char camera_aNofile_800D0074[];
extern const char camera_aNospace_800D0050[];
extern const char camera_aPhotodata_800D005C[];
extern const char camera_aPresstoexit_800D0098[];
extern const char camera_aPresstoselectmemorycard_800D00B0[];
extern const char camera_aResd_800D00A8[];
extern const char camera_aSaving_800D0044[];
extern const char camera_aSelectmemorycard_800D007C[];
extern int camera_dword_800D0750;
extern int camera_dword_800D0754;
extern int camera_dword_800D0758;
extern int camera_dword_800D0768;
extern int camera_dword_800D076C;
void camera_800C86BC(char *a0, int a1, int a2, int a3, int arg4, int arg5);
void camera_800C884C(char *a0, int a1, int a2, int a3, int arg4, int arg5);
extern void sub_8008E878(char *dest, char *src, int count, char *table) asm("0x8008E878");

void camera_800C3A7C(unsigned long *runlevel, RECT *pRect)
{
    int            x, y, w, h;
    int            x2, y2;
    unsigned long *cell;

    DecDCTReset(0);

    x = pRect->x;
    y = pRect->y;
    w = pRect->w;
    h = pRect->h;

    pRect->w = 16;
    pRect->h = 16;

    x2 = x + w;
    y2 = y + h;

    cell = (unsigned long *)0x80182000; // ori

    DecDCTin(runlevel, 0);

    while (pRect->x < x2)
    {
        pRect->y = y;
        while (pRect->y < y2)
        {
            DecDCTout(cell, 128);
            DecDCToutSync(0);
            LoadImage(pRect, cell);
            pRect->y += 16;
        }
        pRect->x += 16;
    }
    pRect->x = x;
    pRect->y = y;
}

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C3B9C.s")
#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C3D3C.s")
#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C3ED8.s")
#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C408C.s")
#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C4184.s")
void camera_800C4184(CameraWork* work);

void camera_800C4350(CameraWork* work) {

    printf((char *)camera_aThisissinreiphoto_800CFB40);
    printf((char *)camera_aSinreinod_800CFB58, work->field_4934);

    camera_800C4184(work);
}

void camera_800C4394(void *context)
{
    void *photo_data;
    int photo_type;
    int text_length;
    int i;
    int char_value;
    unsigned char *src_text;
    unsigned char *dst_text;
    int rgba_color;
    int r, g, b, a;
    int normalized_r, normalized_g, normalized_b;

    
    photo_data = camera_dword_800D0700;

    
    photo_type = *(unsigned char *)((char *)photo_data + 0xD);

    
    if (photo_type == 0x40)
    {
        printf((char *)0x800CB368);  

        
        ((char *)context)[0x49D4] = 'P';  
        ((char *)context)[0x49D5] = 'H';  
        ((char *)context)[0x49D6] = 'O';  
        ((char *)context)[0x49D7] = 'T';  
        ((char *)context)[0x49D8] = 'O';  
        ((char *)context)[0x49D9] = ' ';  
        ((char *)context)[0x49DA] = '0';  

        
        char_value = *(unsigned char *)((char *)photo_data + 0x1B);
        *(int *)((char *)context + 0x4990) = char_value - 0x4F;

        
        char_value = *(unsigned char *)((char *)context + 0x4990);
        *(int *)((char *)context + 0x4960) = 0;
        *(int *)((char *)context + 0x4964) = 0;

        ((char *)context)[0x49DC] = 0;
        ((char *)context)[0x49DD] = ':';
        ((char *)context)[0x49DE] = 0;
        ((char *)context)[0x49DB] = char_value + 0x30;  
    }
    
    else if (photo_type == 0x66)
    {
        printf((char *)0x800CB384);  

        
        char_value = *(unsigned char *)((char *)photo_data + 0x19);
        *(int *)((char *)context + 0x4990) = char_value - 0x4F;

        
        if (*(unsigned char *)((char *)photo_data + 0x1C) != 0)
        {
            text_length = 0;

            
            for (i = 0; i < 16; i++)
            {
                unsigned char byte1 = *(unsigned char *)((char *)photo_data + 0x1C + i * 2);
                unsigned char byte2 = *(unsigned char *)((char *)photo_data + 0x1D + i * 2);

                
                if (byte1 == 0x81)
                {
                    
                    int offset = byte2 - 0x40;

                    if (offset < 0x2F)
                    {
                        
                        switch (offset)
                        {
                            case 0x00: char_value = ' '; break;   
                            case 0x08: char_value = ':'; break;   
                            case 0x0D: char_value = '?'; break;   
                            case 0x09: char_value = '!'; break;   
                            case 0x1E: char_value = '['; break;   
                            case 0x1F: char_value = ']'; break;   
                            default:
                                continue;
                        }
                        ((char *)context)[0x494C + text_length] = char_value;
                    }
                }
                
                else if (byte1 == 0x82)
                {
                    
                    char_value = byte2 + 0xE1;
                    ((char *)context)[0x494C + text_length] = char_value;
                }

                text_length++;

                
                if (*(unsigned char *)((char *)photo_data + 0x1C + (i + 1) * 2) == 0)
                    break;
            }
        }

        
        ((char *)context)[0x49D4] = 'P';
        ((char *)context)[0x49D5] = 'H';
        ((char *)context)[0x49D6] = 'O';
        ((char *)context)[0x49D7] = 'T';
        ((char *)context)[0x49D8] = 'O';
        ((char *)context)[0x49D9] = ' ';
        ((char *)context)[0x49DA] = '0';

        *(int *)((char *)context + 0x4960) = 0;
        *(int *)((char *)context + 0x4964) = text_length;

        char_value = *(unsigned char *)((char *)photo_data + 0x19);

        ((char *)context)[0x49DC] = 0;
        ((char *)context)[0x49DD] = ':';
        ((char *)context)[0x49DE] = 0;
        ((char *)context)[0x49DB] = char_value + 0xE1;
    }

    
    printf((char *)0x800CB3A0, *(int *)((char *)context + 0x4964));  
    printf((char *)0x800CB3B4, (char *)context + 0x494C);            
    printf((char *)0x800CB3C8, *(int *)((char *)context + 0x4990));  

    
    camera_dword_800D0700 = (char *)photo_data + 0x100;
    rgba_color = *(int *)((char *)photo_data + 0x100);
    camera_dword_800D0700 = (char *)photo_data + 0x104;

    printf((char *)0x800CB3D8, rgba_color);

    
    
    g = (rgba_color & 0xFF00) >> 8;
    *(int *)((char *)context + 0x4980) = g;
    g -= 0x80;
    *(int *)((char *)context + 0x4980) = g;
    g += 0x64;

    
    r = (rgba_color >> 16) & 0xFF;
    *(int *)((char *)context + 0x4984) = r;
    r -= 0x80;
    *(int *)((char *)context + 0x4984) = r;
    r += 0x64;

    
    b = (rgba_color >> 24) & 0xFF;
    *(int *)((char *)context + 0x4988) = b;
    b -= 0x80;
    *(int *)((char *)context + 0x4988) = b;
    b += 0x64;

    
    a = rgba_color & 0xFF;
    *(int *)((char *)context + 0x4934) = a;

    
    
    normalized_r = ((g * 255) * 0x51EB851F) >> 38;
    *(int *)((char *)context + 0x4968) = normalized_r;

    normalized_g = ((r * 255) * 0x51EB851F) >> 38;
    *(int *)((char *)context + 0x496C) = normalized_g;

    normalized_b = ((b * 255) * 0x51EB851F) >> 38;
    *(int *)((char *)context + 0x4970) = normalized_b;

    
    printf((char *)0x800CB3E8, a);
    printf((char *)0x800CB3F8,
           *(int *)((char *)context + 0x4980),
           *(int *)((char *)context + 0x4984),
           *(int *)((char *)context + 0x4988));
    printf((char *)0x800CB410,
           *(int *)((char *)context + 0x4968),
           *(int *)((char *)context + 0x496C),
           *(int *)((char *)context + 0x4970));

    printf((char *)0x800CB42C, 0x801B1000);

    
    camera_800C3B9C(context, 0x801B1000);

    
    {
        short rect[4];
        rect[0] = 0;
        rect[1] = 0x100;
        rect[2] = 0x120;
        rect[3] = 0xB0;
        camera_800C3A7C(0x801B1000, rect);
    }

    
    camera_800C3D3C(context);

    
    if (*(int *)((char *)context + 0x4934) != 0)
    {
        camera_800C4350(context);
    }
}

int camera_800C4790(MEM_CARD *pMemcard)
{
    int   size;
    int   hours;
    int   minutes;
    int   file;
    char *buffer;
    char *buffer_copy;
    int   success;
    int   retries;
    int   flags1;
    int   flags2;
    int   i;
    int   idx;

    *(int *)0x800AB3F4 = 1;

    size = camera_dword_800D072C->blocks_count * MC_BLOCK_SIZE;
    buffer = GV_AllocMemory(GV_NORMAL_MEMORY, size);
    if (!buffer)
    {
        printf((char *)camera_aNomemoryforfilebody_800CFCF8);
    }

    GV_ZeroMemory(buffer, size);

    buffer[0] = 'S';
    buffer[1] = 'C';
    buffer[2] = 0x11;
    buffer[3] = camera_dword_800D072C->blocks_count;

    idx = camera_dword_800D072C->field_0[1];
    buffer_copy = buffer;

    if (idx == 0)
    {
        idx = *(short *)0x800B4D9E;
        flags1 = *(short *)0x800B4D9E;

        if (flags1 >= 4)
        {
            idx = 3;
            if (flags1 == 6)
            {
                idx = 0;
            }
        }

        flags2 = flags1 | ((*(short *)0x800B4DA0 - 1) * 8);
    }
    else
    {
        flags2 = idx;
    }

    memcpy(buffer_copy + 96, camera_dword_800C3438 + idx * 160, 160);

    hours = *(short *)0x800B4E4E;
    minutes = *(short *)0x800B4E50 / 15;

    camera_dword_800D072C->make_title(buffer_copy + 4, pMemcard, hours, minutes);
    strcpy(camera_dword_800C37F8, MGS_MemoryCardName);

    camera_dword_800C37F8[12] = camera_dword_800D072C->field_0[0];
    camera_dword_800C37F8[13] = (hours / 10) + '0';
    camera_dword_800C37F8[14] = (hours % 10) + '0';
    camera_dword_800C37F8[15] = (minutes / 10) + '0';
    camera_dword_800C37F8[16] = (minutes % 10) + '0';
    camera_dword_800C37F8[17] = flags2 + '@';
    camera_dword_800C37F8[18] = camera_dword_800D072C->field_2 + '@';

    for (i = 0; i < 16; i++)
    {
        flags1 = 0;
        camera_dword_800C37F8[19] = 'A' + i;
        for (file = 0; file < pMemcard->file_count; file++)
        {
            if (!strcmp(pMemcard->files[file].name, camera_dword_800C37F8))
            {
                flags1 = 1;
            }
        }

        if (!flags1)
        {
            break;
        }
    }

    camera_dword_800D072C->make_game_data(buffer_copy + 256);

    success = 0;
    for (retries = 4; retries > 0; retries--)
    {
        memcard_write(pMemcard->card_idx, camera_dword_800C37F8, 0, buffer, size);
        while ((flags2 = memcard_get_status()) > 0)
        {
            mts_wait_vbl(2);
        }

        if (memcard_get_status() == 0)
        {
            success = 1;
            break;
        }
    }

    GV_FreeMemory(GV_NORMAL_MEMORY, buffer);
    *(int *)0x800AB3F4 = 0;
    return success;
}

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C4BAC.s")

int camera_800C4D20(int arg0) {

    camera_dword_800D0738 = arg0;
    printf(camera_aRequestx_800CFF3C, arg0);

    mts_slp_tsk();
    printf(camera_aResultx_800CFF48, camera_dword_800D073C);

    return camera_dword_800D073C;
}

void camera_800C4D70(void) {
    int port;
    int card_status;
    int available_count;
    int port_mask;
    int file_slot;
    int retry_count;
    void *file_list;
    int operation_result;

    
    mts_set_vsync_task();

    
    while (1)
    {
        
        camera_dword_800D0734 = 1;

        while (1)
        {
            
            camera_800C4D20(0x100000A);

            
            if (camera_dword_800C3880 == -1)
            {
                
                camera_dword_800C3884 = 0;
                available_count = 0;

                for (port = 0; port < 2; port++)
                {
                    card_status = memcard_check(port);
                    camera_dword_800D0740[port] = card_status & 0xFF;

                    
                    if (card_status & 0x100)
                    {
                        
                        if (camera_dword_800C3430 == port)
                        {
                            camera_dword_800C3430 = -1;
                        }
                    }
                    else
                    {
                        
                        if (card_status != 0x03)
                        {
                            
                            available_count++;
                            port_mask = 1 << port;
                            camera_dword_800C3884 |= port_mask;
                        }
                    }
                }

                
                if (available_count == 0)
                {
                    
                    camera_800C4D20(0x41000008);

                    
                    for (port = 0; port < 2; port++)
                    {
                        card_status = memcard_check(port);

                        if ((card_status & 0xFF) != 0x03)
                        {
                            
                            goto restart_scan;
                        }
                    }

                    
                    camera_dword_800D0734 = 2;
                    camera_dword_800C3430 = -1;
                    continue;
                }

                
                camera_dword_800D073C = -2;  
                camera_dword_800D0738 = 0x20000001;
                camera_dword_800C3884 &= ~0x80;  

                
                while (1)
                {
                    for (port = 0; port < 2; port++)
                    {
                        card_status = memcard_check(port);
                        card_status &= 0xFF;

                        
                        if (card_status != camera_dword_800D0740[port])
                        {
                            
                            if (card_status == 0x03)
                            {
                                
                                port_mask = 1 << port;
                                port_mask = ~port_mask;
                                camera_dword_800C3884 &= port_mask;

                                if (camera_dword_800C3430 == port)
                                {
                                    camera_dword_800C3430 = -1;
                                }
                            }
                            else if (card_status != 0x8000)
                            {
                                
                                port_mask = 1 << port;
                                camera_dword_800C3884 |= port_mask;
                            }

                            camera_dword_800D0734 = 1;
                            camera_dword_800C3884 |= 0x80;
                            camera_dword_800D0740[port] = card_status;
                        }
                    }

                    
                    if (camera_dword_800D073C >= 0)
                    {
                        
                        if (camera_dword_800C3884 == 0)
                        {
                            
                            camera_dword_800C3880 = -1;
                            camera_dword_800C3430 = -1;
                            goto restart_scan;
                        }

                        
                        port_mask = 1 << camera_dword_800D073C;
                        if ((camera_dword_800C3884 & port_mask) == 0)
                        {
                            camera_dword_800C3880 = -1;
                            camera_dword_800C3430 = -1;
                            goto restart_scan;
                        }

                        
                        if (camera_dword_800C3430 != camera_dword_800D073C)
                        {
                            camera_dword_800C342C = -1;
                        }

                        camera_dword_800C3430 = camera_dword_800D073C;
                        break;
                    }

                    
                    if (camera_dword_800D073C == -2)
                    {
                        continue;
                    }

                    
                    camera_800C4D20(0x80000000);
                    goto exit_function;
                }
            }
            else
            {
                
                card_status = memcard_check(camera_dword_800C3880);

                
                if (card_status & 0x100)
                {
                    camera_dword_800C342C = -1;
                }

                card_status &= 0xFF;
                camera_dword_800D0740[camera_dword_800C3880] = card_status;

                
                if (card_status == 0x03)
                {
                    camera_dword_800C3880 = -1;
                    camera_dword_800C342C = -1;
                    goto restart_scan;
                }
            }

            
            port = camera_dword_800C3880;
            card_status = camera_dword_800D0740[port];

            if (card_status == 0x8000)
            {
                
                goto error_state;
            }

            
            if (card_status == 0x01)
            {
                
                camera_800C4D20(0x43000005);

                
                if (camera_dword_800D0728 != 0)
                {
                    camera_dword_800D0734 = 4;
                    camera_dword_800C3880 = -1;
                    goto restart_scan;
                }

                
                camera_800C4D20(0x10000001);

                operation_result = 0;  

                if (operation_result == 0)
                {
                    
                    card_status = memcard_check(camera_dword_800C3880);

                    if ((card_status & 0xFF) == 1)
                    {
                        goto format_error;
                    }

                    
                    camera_800C4D20(0x100000B);

                    
                    if (memcard_format(camera_dword_800C3880) == 0)
                    {
                        
                        camera_dword_800C3880 = -1;
                        camera_800C4D20(0x45000007);
                        goto final_state;
                    }

                    
                    card_status = memcard_check(camera_dword_800C3880);
                    camera_dword_800D0740[camera_dword_800C3880] = card_status & 0xFF;

                    if (card_status != 0)
                    {
                        
                        goto error_state;
                    }

                    camera_dword_800C3434 = card_status;
                }
            }

            
            file_list = memcard_get_files(camera_dword_800C3880);
            camera_dword_800D0748[camera_dword_800C3880] = file_list;

            if (file_list == 0)
            {
                goto format_error;
            }

            
            while (1)
            {
                
                file_slot = camera_800C4D20(0x2000);

                if (file_slot < 0)
                {
                    
                    camera_dword_800C3880 = -1;
                    goto restart_scan;
                }

                
                card_status = memcard_check(camera_dword_800C3880);

                if (card_status != 0)
                {
                    goto format_error;
                }

                
                if (camera_dword_800D0728 != 0)
                {
                    goto error_state;
                }

                
                if (file_slot < 16)
                {
                    
                    camera_800C4D20(0x1000);

                    operation_result = 0;  

                    if (operation_result == 0)
                    {
                        
                        card_status = memcard_check(camera_dword_800C3880);

                        if (card_status != 0)
                        {
                            
                            int file_offset = (file_slot * 8) - file_slot;
                            file_offset = file_offset * 4 + 4;

                            
                            if (memcard_delete(camera_dword_800C3880,
                                             (char *)file_list + file_offset) == 0)
                            {
                                goto error_state;
                            }

                            
                            file_list = memcard_get_files(camera_dword_800C3880);
                            camera_dword_800D0748[camera_dword_800C3880] = file_list;
                        }
                    }
                }

                
                if (((unsigned char *)file_list)[3] == 0)
                {
                    
                    camera_800C4D20(0x43200004);
                    goto final_state;
                }

                
                camera_800C4D20(0x100009);

                if (camera_dword_800D0728 == 1)
                {
                    
                    operation_result = camera_800C4790(file_list);
                }
                else
                {
                    
                    camera_800C4D20(0x100009);
                    operation_result = camera_800C4BAC(file_list, file_slot);
                }

                if (operation_result != 0)
                {
                    
                    camera_dword_800D0728 = operation_result;
                    camera_dword_800D0734 = 0;
                    camera_800C4D20(0xC1000001);
                    goto exit_function;
                }

                
                goto error_state;
            }

format_error:
            camera_800C4D20(0x45000003);
            goto final_state;

error_state:
            camera_800C4D20(0x45000003);

final_state:
            camera_dword_800D0734 = 5;
            camera_800C4D20(0xC5000002);
            goto exit_function;

restart_scan:
            continue;
        }
    }

exit_function:
    camera_800C4D20(0);
}

void camera_800C4D70(void);
void camera_800C5308(int arg0) {

    void* temp_v0;

    temp_v0 = GV_AllocMemory(GV_NORMAL_MEMORY, 2048);
    camera_dword_800D0730 = temp_v0;

    if (temp_v0 == NULL) {

        printf(camera_aNomemoryforstack_800CFF54);
    }

    camera_dword_800D0728 = arg0;
    mts_start_task(MTSID_MEMORY_CARD, camera_800C4D70, camera_dword_800D0730 + 2048, 2048);
}


void move_coord_800C5388(int *arr, int len)
{
    int i;

    for (i = 0; i < len; i++, arr += 2)
    {
        arr[0] += arr[1];
    }
}

// Copy of menu_radio_do_file_mode_helper2_helper_8004A4C4
void camera_800C53B8(MenuPrim *pGlue, RadioFileModeStruElem *pElem)
{
    RadioFileModeUnk1 *pUnk;
    TextConfig         textConfig;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord_800C5388(&pUnk->field_8, 2);
        pUnk->field_18 = 0x3d482e;
    }
    textConfig.xpos = pUnk->field_8 >> 16;
    textConfig.ypos = pUnk->field_10 >> 16; // pUnk->field_10 / 65536 wouldn't match
    textConfig.flags = 0x12;
    textConfig.color = pUnk->field_18 | 0x66000000;

    _menu_number_draw_string2(pGlue, &textConfig, (char *)pUnk->field_4); // TODO: Fix cast
}

// Copy of menu_radio_do_file_mode_helper4_helper_8004A54C
void camera_800C5440(MenuPrim *pGlue, RadioFileModeStruElem *pElem)
{
    LINE_F2           *pPrim;
    RadioFileModeUnk1 *pUnk;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord_800C5388(&pUnk->field_4, 4);
    }

    if (pUnk->field_4 != pUnk->field_14 || pUnk->field_C != pUnk->field_1C)
    {
        _NEW_PRIM(pPrim, pGlue);

        LSTORE(pUnk->field_24, &pPrim->r0);
        pPrim->x0 = pUnk->field_4 >> 16;
        pPrim->y0 = pUnk->field_C >> 16;
        pPrim->x1 = pUnk->field_14 >> 16;
        pPrim->y1 = pUnk->field_1C >> 16; // pUnk->field_1C / 65536 wouldn't match
        setLineF2(pPrim);
        addPrim(pGlue->ot, pPrim);
    }
}

// duplicate of sub_8004A648
void camera_800C553C(MenuPrim *pGlue, RadioFileModeStruElem *pElem)
{
    RadioFileModeUnk1 *pUnk;
    int                x, y, w, h;
    TILE              *pTile;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord_800C5388(&pUnk->field_4, 4);
    }
    x = (pUnk->field_4 >> 16);
    y = (pUnk->field_C >> 16);
    w = pUnk->field_14 >> 16;
    h = pUnk->field_1C >> 16;
    x -= w / 2;
    y -= h / 2;

    _NEW_PRIM(pTile, pGlue);

    LSTORE(0x72A452, &pTile->r0);
    setTile(pTile);
    pTile->x0 = x;
    pTile->y0 = y;
    pTile->w = w;
    pTile->h = h;
    setSemiTrans(pTile, 0);
    addPrim(pGlue->ot, pTile);

    radio_draw_face_frame(pGlue, x, y, w, h);
    radio_draw_face_frame(pGlue, x, y, w, h);
}

void camera_800C714C(MenuPrim *pGlue, SELECT_INFO *info);

// duplicate of menu_radio_do_file_mode_helper3_helper_8004A790
void camera_800C5684(MenuPrim *pGlue, RadioFileModeStruElem *pElem)
{
    RadioFileModeUnk1 *pUnk;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord_800C5388(&pUnk->field_4, 2);
    }

    *(short *)pUnk->field_14 = pUnk->field_4 >> 16; // TODO: Fix type of field_14
    *(short *)(pUnk->field_14 + 2) = pUnk->field_C >> 16; // pUnk->field_C / 65536 wouldn't match
    camera_800C714C(pGlue, (SELECT_INFO *)pUnk->field_14);
}

// duplicate of init_file_mode_helper2_8004A800
// but with GV_AllocMemory(GV_NORMAL_MEMORY, ...)
// instead of GV_AllocMemory(0, ...)
void camera_800C56F4()
{
    int i;

    camera_dword_800D075C =
        (RadioFileModeStru_800ABB7C *)GV_AllocMemory(GV_NORMAL_MEMORY, sizeof(RadioFileModeStru_800ABB7C));
    if (camera_dword_800D075C == NULL)
    {
        printf((char *)camera_aNomemoryforobj_800CFF80);
    }

    for (i = 0; i < 12; i++)
    {
        camera_dword_800D075C->field_0_array[i].field_0 = 0;
    }
}

void camera_800C5750(void)
{
    GV_FreeMemory(GV_NORMAL_MEMORY, camera_dword_800D075C);
}

extern int camera_dword_800C3888;

void camera_800C5778(int idx, int param_2, int param_3, int divisor, int idx2)
{
    RadioFileModeUnk2     *pUnk;
    RadioFileModeStruElem *pElem;

    pUnk = &camera_dword_800D075C->field_c0_array[idx];
    pElem = &camera_dword_800D075C->field_0_array[idx];

    pUnk->field_4 = (const char *)((int *)&camera_dword_800C3888)[idx2];

    pElem->field_8_pFn = camera_800C53B8;
    pElem->field_C_unk1 = (RadioFileModeUnk1 *)pUnk;

    if (idx2 < 0)
    {
        pElem->field_0 = 0;
        return;
    }

    if (divisor <= 0)
    {
        pUnk->field_8 = param_2 * 65536;
        pUnk->field_10 = param_3 * 65536;
        pElem->field_0 = 2;
    }
    else
    {
        pUnk->field_C = (param_2 * 65536 - pUnk->field_8) / divisor;
        pUnk->field_14 = (param_3 * 65536 - pUnk->field_10) / divisor;
        pElem->field_0 = 1;
    }

    pUnk->field_18 = 0x748956;
    pElem->field_4 = divisor;
}

void camera_800C5898(int idx, int param_2, int param_3, int divisor, SELECT_INFO *field_14)
{
    RadioFileModeUnk1     *pUnk;
    RadioFileModeStruElem *pElem;

    pElem = &camera_dword_800D075C->field_0_array[idx];
    pUnk = &camera_dword_800D075C->field_220_unk1;

    pElem->field_8_pFn = camera_800C5684;
    pElem->field_C_unk1 = pUnk;

    if (divisor <= 0)
    {
        pUnk->field_4 = param_2 * 65536;
        pUnk->field_C = param_3 * 65536;
        pElem->field_0 = 2;
    }
    else
    {
        pUnk->field_8 = (param_2 * 65536 - pUnk->field_4) / divisor;
        pUnk->field_10 = (param_3 * 65536 - pUnk->field_C) / divisor;
        pElem->field_0 = 1;
    }

    pUnk->field_14 = (int)field_14;
    pElem->field_4 = divisor;
}

void camera_800C5440(MenuPrim *pGlue, RadioFileModeStruElem *pElem);

void camera_800C5970(int idx, int param_2, int param_3, int param_4, int param_5, int divisor) // duplicate of menu_radio_do_file_mode_helper4_8004AA68
{
    RadioFileModeUnk1     *pUnk;
    RadioFileModeStruElem *pElem;

    pElem = &camera_dword_800D075C->field_0_array[idx];

    // callers to this function use idx in range 5..8
    pUnk = &camera_dword_800D075C->field_130_array[idx - 5]; // TODO: really -5?

    pElem->field_8_pFn = camera_800C5440;
    pElem->field_C_unk1 = pUnk;
    if (divisor <= 0)
    {
        pUnk->field_4 = param_2 * 65536;
        pUnk->field_C = param_3 * 65536;
        pUnk->field_14 = param_4 * 65536;
        pUnk->field_1C = param_5 * 65536;
        pElem->field_0 = 2;
    }
    else
    {
        pUnk->field_8 = (param_2 * 65536 - pUnk->field_4) / divisor;
        pUnk->field_10 = (param_3 * 65536 - pUnk->field_C) / divisor;
        pUnk->field_18 = (param_4 * 65536 - pUnk->field_14) / divisor;
        pUnk->field_20 = (param_5 * 65536 - pUnk->field_1C) / divisor;
        pElem->field_0 = 1;
    }

    pUnk->field_24 = 0x3d482e;
    pElem->field_4 = divisor;
}

void camera_800C5AE8(int index)
{
    camera_dword_800D075C->field_0_array[index].field_0 = 0;
}
#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C5B00.s")
void camera_800C5B00(int param_1, int param_2, int param_3, int param_4, int divisor);

void camera_800C5C54(MenuPrim *pGlue) // duplicate of menu_radio_do_file_mode_helper6_8004AD40
{
    int                    i;
    RadioFileModeStruElem *pElem;

    pElem = camera_dword_800D075C->field_0_array;
    for (i = 0; i < 12; i++, pElem++)
    {
        if (pElem->field_0 != 0)
        {
            if (pElem->field_4 < 0)
            {
                pElem->field_4++;
            }
            else
            {
                pElem->field_8_pFn(pGlue, pElem);
                if (pElem->field_0 == 1 && --pElem->field_4 == 0)
                {
                    pElem->field_0 = 2;
                }
            }
        }
    }
}

void camera_800C5D2C(SPRT *sprt) // duplicate of menu/datasave.c: set_sprt_default
{
    LSTORE(0x80808080, &sprt->r0);
    setSprt(sprt);
    setClut(sprt, 960, 510);
}

// duplicate of init_radio_message_board_80040F74
// but with GV_AllocMemory(GV_NORMAL_MEMORY, ...)
// instead of GV_AllocMemory(0, ...)
// and with one font_set_color missing
void camera_800C5D54(MenuWork *work)
{
    KCB  local_kcb;
    KCB *allocated_kcb;

    if (work->field_214_font == NULL)
    {
        KCB *ptr_local_kcb = &local_kcb;

        GV_ZeroMemory(ptr_local_kcb, sizeof(KCB));
        ClearImage(&camera_dword_800C389C, 0, 0, 0);

        font_init_kcb(ptr_local_kcb, &camera_dword_800C389C, 960, 510);
        font_set_kcb(ptr_local_kcb, -1, -1, 0, 6, 2, 0);

        allocated_kcb = (KCB *)GV_AllocMemory(GV_NORMAL_MEMORY, font_get_buffer_size(ptr_local_kcb) + sizeof(KCB));
        font_set_buffer(ptr_local_kcb, allocated_kcb + 1);
        font_set_color(ptr_local_kcb, 0, 0x6739, 0);
        font_set_color(ptr_local_kcb, 1, 0x3bef, 0);
        font_set_color(ptr_local_kcb, 2, 0x3a4b, 0);
        // font_set_color(ptr_local_kcb, 3, 0x1094, 0);
        font_clut_update(ptr_local_kcb);

        work->field_214_font = allocated_kcb;
        memcpy(allocated_kcb, ptr_local_kcb, sizeof(KCB));

        camera_dword_800D0760 = NULL;
    }
}

// duplicate of drawCaption_8004AE3C
void drawCaption_800C5EB4(MenuWork *work, const char *caption)
{
    int  height;
    KCB *kcb;

    kcb = work->field_214_font;

    height = kcb->height_info;
    kcb->height_info = 14;
    font_clear(kcb);
    kcb->height_info = height;

    font_draw_string(kcb, 0, 0, caption, 0);
    font_update(kcb);
}

// duplicate of sub_8004AEA8
void camera_800C5F20(SELECT_INFO *info)
{
    int   top;
    int   i, y;
    int   count;
    int   x, val2;
    KCB  *kcb;
    char  mes[32];
    char *name;

    kcb = info->field_1C_kcb;
    x = 0;
    font_clear(kcb);

    val2 = 14;
    y = val2;
    count = info->max_num - info->top;
    if (count > 6)
    {
        count = 6;
    }

    top = info->top;
    for (i = 0; i < count; i++, y += 14)
    {
        if (i == 4)
        {
            x = 128;
            y = val2;
        }

        name = info->menu[i + top].mes;
        if (name[0] != '\0')
        {
            camera_dword_800D072C->make_menu(mes, name);
            font_draw_string(kcb, x, y, mes, 2);
        }
    }

    font_draw_string(kcb, 0, 0, info->message, 0);
    font_update(kcb);
}

// duplicate of show_message_8004AFE4
void camera_800C6054(MenuWork *work, u_long *ot, SELECT_INFO *info)
{
    unsigned int xoff;
    SPRT        *pPrim;
    KCB         *kcb;

    kcb = work->field_214_font;

    NEW_PRIM(pPrim, work);

    camera_800C5D2C(pPrim);

    xoff = kcb->max_width;

    pPrim->y0 = 200;
    pPrim->v0 = 4;
    pPrim->w = 252;
    pPrim->h = 14;
    pPrim->u0 = 0;
    pPrim->x0 = 160 - xoff / 2;

    addPrim(ot, pPrim);
}

void camera_800C6110(void* arg0, void* arg1, void* arg2)
{
    int   sp18, sp1c, sp20, sp24;
    char  sp28[6];
    char  sp38[16];
    char  sp48[32];
    char  sp68[32];
    int   sp88, sp8c, sp90, sp94, sp98, sp9c, spa0;
    int   spac;
    void* pkt_ctx;
    void* data_ptr;
    unsigned char    item_count;
    int   start_idx;
    int   visible_count;
    int   y_base;
    int   i;
    int   x_pos1, x_pos2;
    int   y_pos, y_inc;
    unsigned int   color;
    void* pkt;
    void* link;
    unsigned char*   item;
    int   type_val;
    int   temp;

    
    pkt_ctx = *(void**)((unsigned char*)arg0 + 0x20);

    item_count = *(unsigned char*)((unsigned char*)arg2 + 8);
    if (item_count == 0)
        return;

    
    start_idx = *(short*)((unsigned char*)arg2 + 6);
    sp90 = start_idx;

    visible_count = item_count - start_idx;
    sp8c = visible_count;
    if (visible_count > 6)
        sp8c = 6;

    
    y_base = 0xc8;
    sp94 = 0;
    sp98 = 0x112;

    
    temp = *(short*)((unsigned char*)arg2 + 0x16);
    if (temp > 0)
    {
        *(unsigned short*)((unsigned char*)arg2 + 0x16) = temp - 1;
        if (temp - 1 < 5)
        {
            sp9c = (4 - (temp - 1)) * 0x34;
            goto skip_timer;
        }
        return;
    }
    sp9c = 0xd2;

skip_timer:
    
    temp = *(short*)((unsigned char*)arg2 + 0x18);
    if (temp > 0)
    {
        *(unsigned short*)((unsigned char*)arg2 + 0x18) = temp - 1;
        spa0 = ((temp - 1) * 0x12 + 2) / 4;
    }
    else
    {
        spa0 = (temp == 0) ? 0 : 0x12;
    }

    
    if (sp8c <= 0)
        goto draw_borders;

    sp88 = 0;
    x_pos1 = 0x50;
    color = 0xFFFFFFFF;
    y_inc = sp9c / 2;
    spac = y_inc;

    for (i = start_idx; i < start_idx + sp8c; i++)
    {
        
        pkt = *(void**)pkt_ctx;
        *(void**)pkt_ctx = (unsigned char*)pkt + 0x10;

        *(unsigned char*)((unsigned char*)pkt + 3) = 3;
        *(unsigned int*)((unsigned char*)pkt + 4) = 0;
        *(short*)((unsigned char*)pkt + 8) = 0;
        *(short*)((unsigned char*)pkt + 0xa) = y_base;
        *(short*)((unsigned char*)pkt + 0xc) = 0xd2;
        *(short*)((unsigned char*)pkt + 0xe) = 0x12;
        *(unsigned char*)((unsigned char*)pkt + 7) = 0x60;

        
        link = *(void**)((unsigned char*)pkt_ctx + 4);
        *(unsigned int*)pkt = (*(unsigned int*)pkt & 0xFF000000) | (*(unsigned int*)link & 0xFFFFFF);
        *(unsigned int*)link = (*(unsigned int*)link & 0xFF000000) | ((unsigned int)pkt & 0xFFFFFF);

        
        if ((*(int *)0x800AB330) != 0)
            x_pos2 = 0x120;
        else
            x_pos2 = 0x125;

        
        pkt = *(void**)pkt_ctx;
        *(void**)pkt_ctx = (unsigned char*)pkt + 0x28;
        *(unsigned int*)((unsigned char*)pkt + 4) = 0x80808080;

        
        if (i == *(short*)((unsigned char*)arg2 + 4))
            y_pos = spa0;
        else
            y_pos = 0x12;

        *(short*)((unsigned char*)pkt + 0xa) = x_pos1;
        *(short*)((unsigned char*)pkt + 8) = 0xa0 - y_inc;
        *(short*)((unsigned char*)pkt + 0x18) = 0xa0 - y_inc;
        *(short*)((unsigned char*)pkt + 0x1a) = x_pos1 + y_pos;
        *(short*)((unsigned char*)pkt + 0x22) = x_pos1 + y_pos;
        *(short*)((unsigned char*)pkt + 0x12) = x_pos1;
        *(unsigned char*)((unsigned char*)pkt + 0xc) = 0;
        *(unsigned char*)((unsigned char*)pkt + 0xd) = y_base;
        *(unsigned char*)((unsigned char*)pkt + 0x14) = 0xd2;
        *(unsigned char*)((unsigned char*)pkt + 0x15) = y_base;
        *(unsigned char*)((unsigned char*)pkt + 0x1c) = 0;
        *(unsigned char*)((unsigned char*)pkt + 0x24) = 0xd2;
        *(short*)((unsigned char*)pkt + 0x16) = x_pos2;
        *(short*)((unsigned char*)pkt + 0x10) = sp9c + 0xa0 - y_inc;
        *(short*)((unsigned char*)pkt + 0x20) = sp9c + 0xa0 - y_inc;
        *(unsigned char*)((unsigned char*)pkt + 0x1d) = y_base + 0x12;
        *(unsigned char*)((unsigned char*)pkt + 0x25) = y_base + 0x12;
        *(unsigned char*)((unsigned char*)pkt + 3) = 9;
        *(unsigned char*)((unsigned char*)pkt + 7) = 0x2e;

        
        link = *(void**)((unsigned char*)pkt_ctx + 4);
        *(unsigned int*)pkt = (*(unsigned int*)pkt & 0xFF000000) | (*(unsigned int*)link & 0xFFFFFF);
        *(unsigned int*)link = (*(unsigned int*)link & 0xFF000000) | ((unsigned int)pkt & 0xFFFFFF);

        
        item = (unsigned char*)arg2 + (i * 9 + 9) * 4 + 0x24;

        
        if (*(unsigned int*)((unsigned char*)arg2 + (i * 9 + 9) * 4 + 0x44) < 0x10)
        {
            
            sp18 = 0xb2;
            sp1c = y_base + 3;

            if (*item == 0x47)
            {
                
                sub_8008E878(sp38, (char*)0x800D0F94,
                            (*(unsigned char*)(item + 5) - 0x40) / 8 + 1,
                            (char*)0x800D0F94);
                _menu_number_draw_string(pkt_ctx, &sp18, sp38);
            }
            else
            {
                
                _menu_number_draw_string(pkt_ctx, &sp18, (char*)0x800D0F9C);
            }

            
            sp18 = 0xb4;
            sp1c = y_base + 0xa;
            sp28[0] = item[1];
            sp28[1] = item[2];
            sp28[2] = ':';
            sp28[3] = item[3];
            sp28[4] = item[4];
            sp28[5] = 0;
            _menu_number_draw_string(pkt_ctx, &sp18, sp28);
        }
        else
        {
            
            sp18 = spac;
            sp1c = y_base + 8;
            sp20 = 2;
            sp24 = 0x66748956;

            type_val = ((int*)0x800D072C)[0];
            if (type_val >= 2)
                sub_8008E878(sp48, (char*)0x800D0FA4, type_val, (char*)0x800D0FC4);
            else
                sub_8008E878(sp48, (char*)0x800D0FA4, type_val, (char*)0x800D0FC8);

            _menu_number_draw_string2(pkt_ctx, &sp18, sp48);
        }

        
        if (sp88 == 4)
        {
            sp94 = 0x80;
            sp98 = 0x112;
        }

        
        pkt = *(void**)pkt_ctx;
        *(void**)pkt_ctx = (unsigned char*)pkt + 0x14;
        camera_800C5D2C(pkt);

        *(unsigned char*)((unsigned char*)pkt + 0xc) = sp94;
        *(unsigned char*)((unsigned char*)pkt + 0xd) = sp98;
        *(short*)((unsigned char*)pkt + 0x10) = 0x80;
        *(short*)((unsigned char*)pkt + 0x12) = 0xe;
        *(short*)((unsigned char*)pkt + 8) = 0;
        *(short*)((unsigned char*)pkt + 0xa) = y_base + 5;

        
        link = *(void**)arg1;
        *(unsigned int*)pkt = (*(unsigned int*)pkt & 0xFF000000) | (*(unsigned int*)link & 0xFFFFFF);
        *(unsigned int*)link = (*(unsigned int*)link & 0xFF000000) | ((unsigned int)pkt & 0xFFFFFF);

        
        pkt = *(void**)pkt_ctx;
        *(void**)pkt_ctx = (unsigned char*)pkt + 8;
        *(unsigned char*)((unsigned char*)pkt + 3) = 1;
        *(unsigned int*)((unsigned char*)pkt + 4) = 0xE100023F;

        link = *(void**)((unsigned char*)pkt_ctx + 4);
        *(unsigned int*)pkt = (*(unsigned int*)pkt & 0xFF000000) | (*(unsigned int*)link & 0xFFFFFF);
        *(unsigned int*)link = (*(unsigned int*)link & 0xFF000000) | ((unsigned int)pkt & 0xFFFFFF);

        sp88++;
        sp98 += 0xe;
        x_pos1 += y_pos;
    }

draw_borders:
    
    for (i = 0; i < 2; i++)
    {
        pkt = *(void**)pkt_ctx;
        *(void**)pkt_ctx = (unsigned char*)pkt + 0x10;

        temp = -(sp9c + 0xa);
        y_pos = (temp + (temp >> 31)) / 2;

        *(short*)((unsigned char*)pkt + 0xc) = 0xa0 + y_pos;
        *(short*)((unsigned char*)pkt + 8) = 0xa0 + y_pos;
        *(short*)((unsigned char*)pkt + 0xa) = 0x4e;
        *(short*)((unsigned char*)pkt + 0xe) = x_pos1 + 4;
        *(unsigned int*)((unsigned char*)pkt + 4) = 0x74008956;
        *(unsigned char*)((unsigned char*)pkt + 3) = 3;
        *(unsigned char*)((unsigned char*)pkt + 7) = 0x42;

        link = *(void**)((unsigned char*)pkt_ctx + 4);
        *(unsigned int*)pkt = (*(unsigned int*)pkt & 0xFF000000) | (*(unsigned int*)link & 0xFFFFFF);
        *(unsigned int*)link = (*(unsigned int*)link & 0xFF000000) | ((unsigned int)pkt & 0xFFFFFF);

        y_pos = y_pos + 0xa + sp9c;
    }

    
    if (*(short*)((unsigned char*)arg2 + 0x18) < 0)
    {
        type_val = ((int*)0x800D072C)[0];

        
        sp18 = (*(int*)0x800C3880 == 0 && *(unsigned char*)((unsigned char*)0x800D0754 + 8) != 1)
               ? 0x60
               : (*(int*)0x800C3880 != 0 ? 0xe0 : 0xa0);

        sp1c = 0x44;
        sp20 = 2;
        sp24 = 0x66748956;

        if (type_val >= 2)
            sub_8008E878(sp68, (char*)0x800D0FCC, type_val, (char*)0x800D0FC4);
        else
            sub_8008E878(sp68, (char*)0x800D0FCC, type_val, (char*)0x800D0FC8);

        _menu_number_draw_string2(pkt_ctx, &sp18, sp68);

        
        if (((*(int *)0x800BB920) % 32) >= 11)
        {
            if (start_idx > 0)
                menu_draw_triangle(*(void**)((unsigned char*)arg0 + 0x20), camera_dword_800C38A4);

            if (start_idx + 6 < item_count)
                menu_draw_triangle(*(void**)((unsigned char*)arg0 + 0x20), camera_dword_800C38B4);
        }
    }
}


void camera_800C68BC(char *arg0, char *arg1)
{
    strcpy(arg0, arg1 + 0xC);
}

void camera_800C68DC(void *ptr)
{
    printf((char *)camera_aCloseinfo_800CFFE0);
    if (ptr)
    {
        GV_FreeMemory(GV_NORMAL_MEMORY, ptr);
    }
}

void camera_800C6918(void **arg0, int arg1)
{
    void *temp_v0;

    if (*arg0 == NULL)
    {
        temp_v0 = GV_AllocMemory(GV_NORMAL_MEMORY, (arg1 * 0x24) + 0x24);
        *arg0 = temp_v0;
        if (temp_v0 == NULL)
        {
            printf((char *)camera_aNomemoryforinfo_800CFFEC);
        }
        printf((char *)camera_aAllocinfox_800D0000, *arg0);
    }
}

// See also updateCurrentEntry_8004B9C4() in datasave.c
void updateCurrentEntry_800C6984(SELECT_INFO *info, int dir)
{
    short top;
    short newIndex;
    int   previousIndex;

    previousIndex = info->current_index;
    newIndex = info->current_index + dir;
    info->current_index = newIndex;
    if (newIndex < 0)
    {
        info->current_index = 0;
    }
    else if (newIndex >= info->max_num)
    {
        info->current_index = info->max_num - 1;
    }
    else
    {
        top = info->top;
        if (newIndex < top)
        {
            info->top = newIndex;
        }
        else if (newIndex >= (top + 6))
        {
            info->top = newIndex - 5;
        }
    }
    if (info->current_index != previousIndex)
    {
        GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
    }
    camera_800C5F20(info);
}

// duplicate of menu_radio_do_file_mode_helper12_8004BA80
int camera_800C6A40(MenuWork *work, MEM_CARD *pMemcard, const char *param_3,
                    SELECT_INFO *info)
{
    MENU_CURPOS *pIter;
    MEM_CARD_FILE       *pMcFile;
    int                  i;

    pIter = info->menu;

    strcpy(camera_dword_800C37F8, MGS_MemoryCardName);
    camera_dword_800C37F8[12] = camera_dword_800D072C->field_0[0];

    for (i = 0; i < pMemcard->file_count; i++)
    {
        pMcFile = &pMemcard->files[i];
        printf((char *)camera_aFiles_800D0010, pMcFile->name);

        if (strncmp(pMcFile->name, camera_dword_800C37F8, 13) == 0)
        {
            camera_800C68BC(pIter->mes, pMcFile->name);
            pIter->field_20 = i;
            pIter++;
        }
    }

    if (camera_dword_800D0728 == 0 && pMemcard->free_blocks >= camera_dword_800D072C->blocks_count)
    {
        memcpy(pIter->mes, (char *)camera_dword_800CFFC8, 1);
        pIter->field_20 = 16;
        pIter++;
    }

    info->field_1C_kcb = work->field_214_font;
    info->max_num = pIter - info->menu;

    if (camera_dword_800D072C->field_0[0] != 71)
    {
        if (info->max_num && pIter[-1].field_20 == 16)
        {
            info->current_index = info->max_num - 1;
        }
        else
        {
            info->current_index = 0;
        }
    }
    else if (camera_dword_800C342C == -1 || camera_dword_800C342C >= info->max_num)
    {
        if (camera_dword_800D0728 == 0 && info->max_num && pIter[-1].field_20 == 16)
        {
            info->current_index = info->max_num - 1;
        }
        else
        {
            info->current_index = 0;
        }
    }
    else
    {
        info->current_index = camera_dword_800C342C;
    }

    info->top = 0;
    info->message = param_3;
    info->field_E = -1;
    info->field_0_xpos = 40;
    info->field_2_ypos = 40;
    info->open_count = 8;
    info->current_dir = 0;
    info->field_18 = -1;
    info->field_12 = 240;
    info->field_14 = 1;
    updateCurrentEntry_800C6984(info, 0);
    return info->max_num != 0;
}

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C6CCC.s")

extern int camera_dword_800C3884;
extern const char *gMemoryCardNames_800C38C4[];
extern int camera_dword_800C3430;
extern const int camera_aNocard_800D003C[];

// duplicate of menu_radio_do_file_mode_helper14_8004BE98
void camera_800C6E78(MenuWork *work, char *param_2, SELECT_INFO *info)
{
    MENU_CURPOS *infoChild;
    int                  idx, idx_copy;
    int                  memoryCardNo;
    int                  bit;
    int                  minusOne;

    infoChild = info->menu;
    idx = -1;
    for (memoryCardNo = 0; memoryCardNo < 2; memoryCardNo++)
    {
        int *new_var;
        new_var = &camera_dword_800C3884;
        bit = 1;
        bit <<= memoryCardNo;

        if (*new_var & bit)
        {
            strcpy(infoChild->mes, gMemoryCardNames_800C38C4[memoryCardNo]);
            infoChild->field_20 = memoryCardNo;
            if (memoryCardNo == camera_dword_800C3430)
            {
                idx = infoChild - info->menu;
            }
            infoChild++;
        }
    }

    idx_copy = idx;
    if (infoChild == info->menu)
    {
        memcpy(&info->menu[0].mes, camera_aNocard_800D003C, 8);
        infoChild->field_20 = 2;
        infoChild = &info->menu[1];
    }

    info->field_1C_kcb = work->field_214_font;
    info->max_num = infoChild - info->menu;

    if (idx_copy < 0)
    {
        idx_copy = 0;
    }

    minusOne = -1;
    do {} while (0);

    info->field_0_xpos = 160;
    info->field_2_ypos = 100;
    info->current_index = idx_copy;
    info->top = 0;
    info->message = param_2;
    info->field_E = minusOne;
    info->field_10 = 128;
    info->field_18 = minusOne;
    info->open_count = 4;
    info->field_12 = 128;
    info->field_14 = 1;
    info->current_dir = 0;
}

// duplicate of menu_radio_do_file_mode_helper15_8004C04C, but with one missing line
void camera_800C703C(MenuWork *work, const char **srcs, int cnt, int field_4, const char *field_20,
                     SELECT_INFO *info)
{
    KCB                 *kcb;
    const char          *src;
    int                  i;
    MENU_CURPOS *dest;

    dest = info->menu;
    for (i = 0; i < cnt; i++, dest++)
    {
        src = srcs[i];
        strcpy(dest->mes, src);
        dest->field_20 = i;
    }

    kcb = work->field_214_font;

    info->max_num = dest - info->menu;
    info->current_index = field_4;
    info->top = 0;
    info->message = field_20;
    info->field_E = 1;
    info->field_0_xpos = 160;
    info->current_dir = 0;
    info->field_14 = 1;
    info->field_2_ypos = 128;
    info->field_10 = 64;
    info->field_12 = 32;
    // info->field_16 = 4;
    info->field_1C_kcb = kcb;
}

// duplicate of menu_radio_do_file_mode_helper16_8004C164
void camera_800C714C(MenuPrim *pGlue, SELECT_INFO *info)
{
    int        i;
    int        xpos, ypos;
    TextConfig textConfig;

    textConfig.flags = 0x12;
    if (info->field_14 != 0)
    {
        textConfig.color = 0x66748956;
    }
    else
    {
        textConfig.color = 0x663d482e;
    }
    textConfig.xpos = info->field_0_xpos;
    textConfig.ypos = info->field_2_ypos;
    _menu_number_draw_string2(pGlue, &textConfig, info->message);
    if (info->max_num == 1)
    {
        xpos = info->field_0_xpos;
    }
    else
    {
        xpos = info->field_0_xpos - info->field_10 / 2;
    }
    for (i = 0; i < info->max_num; i++, xpos += info->field_10)
    {
        textConfig.xpos = xpos;
        ypos = info->field_2_ypos;
        textConfig.ypos = ypos + 12;

        if (i == info->current_index)
        {
            textConfig.color = 0x66748956;
            if (info->field_14 != 0)
            {
                ypos += 16;
                camera_800C5B00(textConfig.xpos, ypos, info->field_12, 12, 2);
            }
        }
        else
        {
            textConfig.color = 0x663d482e;
        }
        _menu_number_draw_string2(pGlue, &textConfig, info->menu[i].mes);
    }
}

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C72CC.s")
int camera_800C73E4(void *work, void *gv_obj)
{
    void *font_work;
    void *game_state;
    void *menu_ptr;
    void *ptr1, *ptr2, *ptr3;
    int state;
    int input_flags;
    int temp, temp2;
    int field_val;
    int result;
    char string_buf[16];
    int output_val;

    game_state = *(void **)(work + 0x20);
    font_work = *(void **)(game_state + 4);

    
    if (camera_dword_800D0728 == 0) {
        
        menu_ptr = (void *)0x800C3888;
        *(void **)(menu_ptr) = *(void **)(*(int *)0x800D072C + 4);
        *(void **)(menu_ptr + 4) = camera_aSaving_800D0044;
        *(void **)(menu_ptr + 0xC) = camera_aNospace_800D0050;
    } else {
        
        menu_ptr = (void *)0x800C3888;
        *(void **)(menu_ptr) = camera_aPhotodata_800D005C;
        *(void **)(menu_ptr + 4) = camera_aLoading_800D0068;
        *(void **)(menu_ptr + 0xC) = camera_aNofile_800D0074;
    }

    
    state = camera_dword_800D0764;
    if (state >= 7) {
        goto END;
    }

    
    switch (state) {
    case 0:
        
        sub_80048124();

        
        ((void (*)(void *))0x800c5d54)(work);
        camera_dword_800D0768 = 0;

        
        font_set_color(*(void **)(work + 0x214), 1, 0x19F2, 0);
        font_clut_update(*(void **)(work + 0x214));

        
        ((void (*)(int, int, int, int, int))0x800c5778)(0, 0xA0, 0x64, 0, 0);

        camera_dword_800D0764 = 1;
        camera_dword_800D076C = 0;
        camera_dword_800D0758 = 0;
        camera_dword_800D0754 = 0;
        camera_dword_800D0750 = 0;

        
        ((void (*)(int, int, int, int, int))0x800c5b00)(0xA0, 0x67, 0x60, 0xC, 0);

        
        GM_SeSet2(0, 0x3F, 0x20);

        camera_dword_800C3434 = 0;
        camera_dword_800C3880 = -1;
        break;

    case 1:
        
        ((void (*)(int, int, int, int, int))0x800c5778)(3, 0xA0, 0x80, 0, -1);

        input_flags = camera_dword_800D0738;
        if (input_flags == 0) {
            goto END;
        }

        
        if (input_flags == 0xC1000001) {
            if (camera_dword_800D0728 == 0) {
                ptr1 = (void *)camera_dword_800D0750;
                temp = *(short *)(ptr1 + 4);

                
                ((void (*)(void *, void *))0x8008e768)(ptr1 + (temp * 9 * 4) + 0x24, (void *)0x800C3804);

                ptr1 = (void *)camera_dword_800D0750;
                temp = *(short *)(ptr1 + 4);
                *(int *)(ptr1 + (temp * 9 * 4) + 0x44) = 0;

                ((void (*)(void))0x800c5f20)();
            }

            ((void (*)(int, int, int, int, int))0x800c5778)(2, 0xA0, 0x80, 0, 2);
            goto SKIP1;
        }

SKIP1:
        
        if (input_flags == 0x1000009) {
            ((void (*)(int, int, int, int, int))0x800c5778)(2, 0xA0, 0x80, 0, 1);
            ((void (*)(int, int, int, int, int, int))0x800c5970)(8, 0xA0, 0x6E, 0xA0, 0x7A, 0);
            ((void (*)(int, int, int, int, int))0x800c5b00)(0xA0, 0x83, 0x60, 0xC, 4);
        }

        
        if (input_flags & 0x400) {
            ((void (*)(int, int, int, int, int))0x800c5778)(2, 0xA0, 0x80, 0, 4);
            ((void (*)(int, int, int, int, int))0x800c5b00)(0xA0, 0x83, 0x60, 0xC, 4);
        }

        
        if (input_flags & 0x100) {
            temp = *(unsigned char *)&camera_dword_800D0738;
            temp2 = temp << 2;
            temp2 += (int)menu_ptr;
            result = *(int *)temp2;

            ((void (*)(void *, void *))0x800c5eb4)(work, (void *)result);
            camera_dword_800D0768 = 0xF;
        }

        
        if (input_flags & 0x4000) {
            camera_dword_800D0764 = 2;
            goto STATE1_END;
        }

        
        if (input_flags & 0x2000) {
            camera_dword_800D0768 = 0;

            temp = *(unsigned char *)&camera_dword_800D0738;
            if (temp == 0) {
                
                ((void (*)(void *, int))0x800c6918)((void *)&camera_dword_800D0750, 0x11);
                camera_dword_800D0764 = 4;

                
                ((void (*)(void *, void *, void *))0x800c6a40)(
                    work,
                    *(void **)(camera_dword_800C3880 * 4 + 0x800D0748),
                    (void *)0x800CFFC8
                );

                camera_dword_800D076C = camera_dword_800D0750;

                result = 0; 
                if (result == 0) {
                    ((void (*)(void *, void *))0x800c5eb4)(work, *(void **)(menu_ptr + 0x10));
                    ((void (*)(int, int, int, int, int))0x800c5778)(3, 0xA0, 0x80, 0, 1);
                    camera_dword_800D0768 = 1;
                    ((void (*)(int, int, int, int, int))0x800c5b00)(0xA0, 0x83, 0x60, 0xC, 4);
                    camera_dword_800D0734 = 3;
                }

                
                if (camera_dword_800D0754 == 0) {
                    ((void (*)(void *, int))0x800c6918)((void *)&camera_dword_800D0754, 3);
                    ((void (*)(void *, void *, void *))0x800c6e78)(work, camera_aSelectmemorycard_800D007C, (void *)camera_dword_800D0754);

                    ptr1 = (void *)camera_dword_800D0754;
                    *(short *)(ptr1 + 0x14) = 0;
                    temp = -4;
                } else {
                    temp = 4;
                }

                
                ((void (*)(int, int, int, int, int))0x800c5778)(0, 0x40, 0x18, 4, 0);
                ((void (*)(int, int, int, int, void *))0x800c5898)(4, 0xA0, 0x28, temp, (void *)camera_dword_800D0754);
                ((void (*)(int, int, int, int, int, int))0x800c5970)(5, 0x6C, 0x1A, 0xA0, 0x1A, temp);
                ((void (*)(int, int, int, int, int, int))0x800c5970)(6, 0xA0, 0x1A, 0xA0, 0x24, temp);

                
                ptr2 = (void *)camera_dword_800D0754;
                field_val = *(unsigned char *)(ptr2 + 8);

                if (field_val == 1) {
                    temp = *(short *)ptr2;
                } else {
                    int val1 = *(unsigned short *)(ptr2 + 0x10);
                    int val2 = *(short *)ptr2;
                    int val3 = *(short *)(ptr2 + 4);

                    val1 = (val1 >> 1);
                    temp = val2 - val1;

                    if (val3 == 1) {
                        temp += val1 * 2;
                    }
                }

                ptr3 = (void *)camera_dword_800D076C;
                field_val = *(unsigned char *)(ptr3 + 8);

                if (field_val != 0) {
                    temp = *(short *)ptr2;
                    temp2 = 0x7A;
                } else {
                    temp2 = 0x40;
                }

                ((void (*)(int, int, int, int, int, int))0x800c5970)(7, 0x3C, temp, temp, temp2, -4);

                ((void (*)(int))0x800c5ae8)(8);
            } else if (temp == 1) {
                
                temp = -4;

                if (camera_dword_800D0754 != 0) {
                    temp = 4;
                }

                ptr1 = (void *)camera_dword_800D0750;
                if (ptr1 != 0) {
                    ((void (*)(void *))0x800c68dc)(ptr1);
                    camera_dword_800D0750 = 0;
                }

                ((void (*)(void *, int))0x800c6918)((void *)&camera_dword_800D0754, 3);
                ((void (*)(void *, void *, void *))0x800c6e78)(work, camera_aSelectmemorycard_800D007C, (void *)camera_dword_800D0754);

                camera_dword_800D076C = camera_dword_800D0754;
                camera_dword_800D0764 = 3;

                
                ((void (*)(int, int, int, int, int))0x800c5778)(0, 0xA0, 0x18, 4, 0);
                ((void (*)(int, int, int, int, void *))0x800c5898)(4, 0xA0, 0x64, temp, (void *)camera_dword_800D0754);
                ((void (*)(int, int, int, int, int, int))0x800c5970)(5, 0xA0, 0x1A, 0xA0, 0x1A, temp);
                ((void (*)(int, int, int, int, int, int))0x800c5970)(6, 0xA0, 0x20, 0xA0, 0x60, temp);

                ((void (*)(int))0x800c5ae8)(7);
            }

            ((void (*)(int))0x800c5ae8)(8);
            goto END;
        }

        
        if (input_flags & 0x1000) {
            temp = (input_flags >> 0x14) ^ 1;
            temp &= 1;

            ((void (*)(void *, int))0x800c6918)((void *)&camera_dword_800D0758, 2);
            camera_dword_800D0764 = 5;

            
            temp2 = *(unsigned char *)&camera_dword_800D0738;
            ((void (*)(void *, void *, int, int, void *, void *))0x800c703c)(
                work,
                (void *)0x800C38CC,
                2,
                temp,
                *(void **)(temp2 * 4 + 0x800C3878),
                (void *)camera_dword_800D0758
            );

            camera_dword_800D076C = camera_dword_800D0758;

            ((void (*)(void *, void *))0x800c5eb4)(work, *(void **)(temp2 * 4 + 0x800C3870));
        }

STATE1_END:
        camera_dword_800D0768 = 1;
        goto END;

    case 2:
        
        temp = *(unsigned short *)(work + 0x104 + 2);
        temp &= 0xF0;

        if (temp != 0) {
            temp = camera_dword_800D0738;

            camera_dword_800D0768 = 0;

            if (temp < 0) {
                camera_dword_800D0764 = 6;
            } else {
                camera_dword_800D0764 = 1;
            }

            mts_wup_tsk(7);
            camera_dword_800D0738 = 0;

            
            ((void (*)(int, int, int, int, int))0x800c5778)(3, 0xA0, 0x80, 0, -1);
            ((void (*)(int, int, int, int, int))0x800c5778)(2, 0xA0, 0x80, 0, -1);

            goto END;
        }

        draw_radio_wait_mark(work, font_work);
        goto END;

    case 3:
        
        if (camera_dword_800C3884 & 0x80) {
            ((void (*)(void *, void *, void *))0x800c6e78)(work, camera_aSelectmemorycard_800D007C, (void *)camera_dword_800D0754);
            camera_dword_800C3884 &= ~0x80;
        }

        
        string_buf[0] = 0xA0;
        string_buf[1] = 0xC8;
        string_buf[2] = 0x12;
        *(int *)(&string_buf[3]) = 0x66748956;

        _menu_number_draw_string2(*(void **)(work + 0x20), string_buf, (char *)camera_aPresstoexit_800D0098);

        
        result = ((int (*)(void *, int *, void *))0x800c72cc)(
            (void *)(work + 0x104),
            &output_val,
            (void *)camera_dword_800D0754
        );

        if (result != 0) {
            printf((char *)camera_aResd_800D00A8, output_val);

            camera_dword_800D0738 = 0;
            camera_dword_800D0764 = 1;
            camera_dword_800D0768 = 0;

            ptr1 = (void *)camera_dword_800D0754;
            *(short *)(ptr1 + 0x14) = 0;

            camera_dword_800D073C = output_val;
        }
        goto END;

    case 4:
        
        result = ((int (*)(void *, int *, void *))0x800c72cc)(
            (void *)(work + 0x104),
            &output_val,
            (void *)camera_dword_800D0758
        );

        if (result != 0) {
            printf((char *)camera_aResd_800D00A8, output_val);

            ptr1 = (void *)camera_dword_800D0758;
            *(short *)(ptr1 + 0x14) = 0;

            if (output_val == -1) {
                ((void (*)(int))0x800c5ae8)(8);
                ((void (*)(int))0x800c5ae8)(7);
            }

            camera_dword_800D0738 = 0;
            camera_dword_800D073C = output_val;

            mts_wup_tsk(7);

            camera_dword_800D0764 = 1;
            camera_dword_800D0768 = 0;
            goto END;
        }

        
        ((void (*)(void *, void *))0x800c714c)(*(void **)(work + 0x20), (void *)camera_dword_800D076C);

        if (camera_dword_800D0750 != 0) {
            ((void (*)(int, int, int, int, int, int))0x800c5970)(8, 0xA0, 0x6E, 0xA0, 0x7A, 0);
        }
        goto END;

    case 5:
        
        ptr1 = (void *)camera_dword_800D0750;
        if (*(unsigned char *)(ptr1 + 8) != 0) {
            
            string_buf[0] = 0xA0;
            string_buf[1] = 0xC8;
            string_buf[2] = 0x12;
            *(int *)(&string_buf[3]) = 0x66748956;

            _menu_number_draw_string2(*(void **)(work + 0x20), string_buf, (char *)camera_aPresstoselectmemorycard_800D00B0);
        }

        result = ((int (*)(void *, int *, void *))0x800c6ccc)(
            (void *)(work + 0x104),
            &output_val,
            (void *)camera_dword_800D0750
        );

        if (result != 0) {
            printf((char *)camera_aResd_800D00A8, output_val);

            ptr1 = (void *)camera_dword_800D0750;
            *(short *)(ptr1 + 0x14) = 0;

            if (output_val == -1) {
                ((void (*)(void *))0x800c68dc)(ptr1);
                camera_dword_800D0750 = 0;
            } else {
                *(short *)(ptr1 + 0x18) = 4;
            }

            camera_dword_800D073C = output_val;

            if (camera_dword_800D0764 == 4) {
                camera_dword_800D0738 = 0;
                mts_wup_tsk(7);
            }

            camera_dword_800D0764 = 1;
            camera_dword_800D0768 = 0;
        }
        goto END;

    case 6:
        
        if (mts_get_task_status(7) == 0) {
            printf((char *)camera_aEndsavemode_800D00D0);

            
            if (camera_dword_800D0750 != 0) {
                ((void (*)(void *))0x800c68dc)((void *)camera_dword_800D0750);
            }

            if (camera_dword_800D0754 != 0) {
                ((void (*)(void *))0x800c68dc)((void *)camera_dword_800D0754);
            }

            if (camera_dword_800D0758 != 0) {
                ((void (*)(void *))0x800c68dc)((void *)camera_dword_800D0758);
            }

            ((void (*)(void))0x800c5750)();

            GV_FreeMemory(2, (void *)camera_dword_800D0730);

            temp = *(unsigned short *)&camera_dword_800D0734;
            *(short *)0x800B4DA2 = temp;

            printf((char *)camera_aEndstated_800D00E0, (int)(short)temp);

            if (camera_dword_800D0728 == 2) {
                result = 1;
            } else {
                font_set_color(*(void **)(work + 0x214), 1, 0x3BEF, 0);
                result = 1;
            }

            goto RETURN;
        }
        goto END;

    default:
        goto END;
    }

END:
    
    temp = camera_dword_800D0768;
    if (temp >= 2) {
        camera_dword_800D0768 = temp - 1;
    } else if (temp > 0) {
        ((void (*)(void *, void *, void *))0x800c6054)(work, font_work, (void *)camera_dword_800D076C);
    }

    
    {
        void *dlist = *(void **)(work + 0x20);
        void *dlist_ptr = *(void **)dlist;
        unsigned int color1 = 0xE100023F;
        unsigned int color2;

        *(void **)dlist = dlist_ptr + 8;
        *(unsigned char *)(dlist_ptr + 3) = 1;
        *(unsigned int *)(dlist_ptr + 4) = color1;

        color2 = *(unsigned int *)dlist_ptr;
        color2 = (color2 & 0xFF000000) | (*(unsigned int *)font_work & 0x00FFFFFF);
        *(unsigned int *)dlist_ptr = color2;

        color2 = (unsigned int)dlist_ptr & 0x00FFFFFF;
        *(unsigned int *)font_work = (*(unsigned int *)font_work & 0xFF000000) | color2;

        if (camera_dword_800D0750 != 0) {
            ((void (*)(void *, void *))0x800c6110)(work, font_work);
        }

        ((void (*)(void *))0x800c5c54)(*(void **)(work + 0x20));
    }

    result = 0;

RETURN:
    return result;
}

extern int        camera_dword_800D0770;
extern int        camera_dword_800D0728;
extern int        camera_dword_800D0774;
extern const char camera_aNoplace_800D0110[];
extern const char camera_dword_800D011C[];

void camera_800C7FF4(int code, char **pAreaNameForMenu, char **pAreaNameForSaveData)
{
    int i;

    if (code == 0)
    {
        *pAreaNameForMenu = (char *)camera_aNoplace_800D0110;
        *pAreaNameForSaveData = (char *)camera_dword_800D011C;
    }

    GCL_SetArgTop((unsigned char *)camera_dword_800D0770);

    for (i = 0; i < code; i++)
    {
        if (GCL_GetParamResult() == 0)
        {
            return;
        }
        *pAreaNameForMenu = GCL_ReadString((char *)GCL_GetParamResult());
        if (camera_dword_800D0774 > 0 && camera_dword_800D0728 == 0)
        {
            *pAreaNameForSaveData = GCL_ReadString((char *)GCL_GetParamResult());
        }
    }
}

extern const char camera_aSssss_800D0120[];
extern const char camera_dword_800D011C[];
extern const char camera_dword_800D012C[];
extern int        camera_dword_800C38D4;
extern int        camera_dword_800D0774;

void camera_800C80E4(char *out, MEM_CARD *unused, int hours, int minutes)
{
    char  playTime[11];
    char *discard;
    char *areaName;

    playTime[0] = 0x82;
    playTime[1] = (hours / 10) + 0x4F;
    playTime[2] = 0x82;
    playTime[3] = (hours % 10) + 0x4F;
    playTime[4] = 0x81;
    playTime[5] = 0x46;
    playTime[6] = 0x82;
    playTime[7] = (minutes / 10) + 0x4F;
    playTime[8] = 0x82;
    playTime[9] = (minutes % 10) + 0x4F;
    playTime[10] = '\0';

    if (camera_dword_800D0774 == 0)
    {
        camera_800C7FF4(1, &discard, &areaName);
        areaName = (char *)&camera_dword_800C38D4;
    }
    else
    {
        camera_800C7FF4(camera_dword_800D0774, &discard, &areaName);
    }

    sprintf(out, (char *)camera_aSssss_800D0120,
            camera_dword_800D012C, camera_dword_800D011C, playTime, camera_dword_800D011C, areaName);
}

extern const char camera_aPhotod_800D0138[];

void camera_800C8208(char *out, char *in)
{
    sprintf(out, (char *)camera_aPhotod_800D0138, in[6] - 0x40);
}

void jpegcam_initSaveBuffer_800C8234(char *arg0)
{
    int chunkSize;
    int totalSavedSize = 0x100;
    char *buff = arg0;

    GM_TotalSaves++;

    while (1)
    {
        chunkSize = GCL_MakeSaveFile(buff);
        totalSavedSize += chunkSize;
        if (totalSavedSize + chunkSize > MC_BLOCK_SIZE)
        {
            break;
        }
        buff += chunkSize;
        printf((char *)camera_a_800D0144);
    }
}

void        camera_800C5308(int);

void camera_800C82B0(DATA_INFO *arg0, int arg1)
{
    camera_dword_800D0764 = 0;
    camera_dword_800D072C = arg0;
    camera_800C56F4();
    camera_800C5308(arg1);
}

void camera_800C82EC(void)
{
    camera_800C82B0(&camera_dword_800C38E0, 1);
}

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C8314.s")
#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C838C.s")

void camera_800C8554(int *arg0, int arg1, int arg2, int arg3)
{
    arg0[0] = arg1;
    arg0[1] = arg2;
    arg0[2] = arg3;
}

int camera_800C8314(int, int);
int camera_800C838C(int, int, char *);

void camera_800C8564(int arg0, int arg1, char *arg2)
{
    char sp10[64];

    sprintf(sp10, arg2);
    camera_800C838C(arg0, arg1, sp10);
    camera_800C8314(arg0, arg1);
}

void camera_800C85B8(int *arg0, int r, int g, int b)
{
    arg0[3] = (r | (g << 8) | (b << 16) | (GPU_CODE_SPRT << 24));
}

void camera_800C85D8(void)
{
    short sp0[4];
    SPRT *sprt;

    // Let's waste cycles by puting unused stuff on stack:
    sp0[0] = 976;
    sp0[1] = 511;
    sp0[2] = 16;
    sp0[3] = 1;

    sprt = &camera_sprt_800D0780;
    LSTORE(0x80808080, &sprt->r0);
    setUV0(sprt, 0, 242);
    setWH(sprt, 8, 6);
    setSprt(sprt);
    setClut(sprt, 976, 511);
}

void camera_800C864C(CameraWork *work)
{
    int i;

    for (i = 3; i >= 0; i--)
    {
        work->field_654[i] = 0;
    }

    for (i = 8; i >= 0; i--)
    {
        work->field_664[i] = NULL;
    }

    for (i = 0x19; i >= 0; i--)
    {
        work->field_688[i] = NULL;
    }
}

void camera_800C869C(CameraWork *work)
{
    int i;

    for (i = 8; i >= 0; i--)
    {
        work->field_664[i] = NULL;
    }
}
#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C86BC.s")
#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C884C.s")
#pragma INCLUDE_ASM("asm/overlays/camera/camera_800C89DC.s")
void camera_800C8AD4(CameraWork *work)
{
    unsigned short* input_ptr;
    unsigned short  input_0;
    unsigned short  input_2;
    int  counter;
    int  state;
    int  menu_state;
    int  new_state;
    int  temp;
    int  i;
    unsigned char*  byte_ptr;
    int  val_4934;
    int  val_4960;
    int  val_4964;

    // Read input structure from offset 0x24
    input_ptr = (unsigned short*)((unsigned char *)work + 0x24);
    input_0 = input_ptr[0];
    input_2 = input_ptr[1];

    // If no input, reset counter and return
    if (input_0 == 0) {
        *(int*)((unsigned char *)work + 0x49c0) = 0;
        return;
    }

    // Load counter at offset 0x49c0
    counter = *(int*)((unsigned char *)work + 0x49c0);

    if (counter == 0) {
        // Counter is 0 - process input flags to determine new state
        new_state = 0;

        // Check input_2 flags first
        if (input_2 & 0x20) {
            new_state = 4;
        } else if (input_2 & 0x40) {
            new_state = 5;
        } else if (input_2 & 0x2000) {
            new_state = 2;
        } else if (input_2 & 0x8000) {
            new_state = 3;
        } else if (input_2 & 0x1000) {
            new_state = 6;
            *(int*)((unsigned char *)work + 0x49c4) = 0;
            *(int*)((unsigned char *)work + 0x49c0) = new_state;
            goto update_counter_check;
        } else if (input_2 & 0x4000) {
            new_state = 1;
        } else {
            // Check input_0 flags
            if (input_0 & 0x2000) {
                new_state = 2;
            } else if (input_0 & 0x8000) {
                new_state = 3;
            } else if (input_0 & 0x1000) {
                new_state = 6;
                *(int*)((unsigned char *)work + 0x49c4) = 0;
                *(int*)((unsigned char *)work + 0x49c0) = new_state;
                goto update_counter_check;
            } else if (input_0 & 0x4000) {
                new_state = 1;
                *(int*)((unsigned char *)work + 0x49c4) = new_state;
                *(int*)((unsigned char *)work + 0x49c0) = new_state;
                goto update_counter_check;
            } else {
                *(int*)((unsigned char *)work + 0x49c0) = 0;
                goto update_counter_check;
            }
        }

        // Set state and counter to 6
        *(int*)((unsigned char *)work + 0x49c4) = new_state;
        *(int*)((unsigned char *)work + 0x49c0) = 6;
    } else {
        // Counter is non-zero - dispatch based on state at 0x49c4
        state = *(int*)((unsigned char *)work + 0x49c4);

        if (state < 6) {
            // Jump table dispatch for states 0-5
            switch (state) {
            case 0:
                // State 0
                if (input_0 & 0x2000) {
                    new_state = 2;
                } else if (input_0 & 0x8000) {
                    new_state = 3;
                } else if (input_0 & 0x1000) {
                    new_state = 6;
                    *(int*)((unsigned char *)work + 0x49c4) = 0;
                    *(int*)((unsigned char *)work + 0x49c0) = new_state;
                    goto update_counter_check;
                } else if (input_0 & 0x4000) {
                    new_state = 1;
                    *(int*)((unsigned char *)work + 0x49c4) = new_state;
                    *(int*)((unsigned char *)work + 0x49c0) = new_state;
                    goto update_counter_check;
                } else {
                    *(int*)((unsigned char *)work + 0x49c0) = 0;
                    goto update_counter_check;
                }
                *(int*)((unsigned char *)work + 0x49c4) = new_state;
                *(int*)((unsigned char *)work + 0x49c0) = 1;
                goto update_counter_check;

            case 1:
                // State 1
                if (input_0 & 0x2000) {
                    new_state = 2;
                } else if (input_0 & 0x8000) {
                    new_state = 3;
                    *(int*)((unsigned char *)work + 0x49c4) = new_state;
                    *(int*)((unsigned char *)work + 0x49c0) = 1;
                    goto update_counter_check;
                } else if (input_0 & 0x1000) {
                    temp = *(int*)((unsigned char *)work + 0x49c0);
                    temp++;
                    *(int*)((unsigned char *)work + 0x49c0) = temp;
                    goto update_counter_check;
                } else if (input_0 & 0x4000) {
                    temp = *(int*)((unsigned char *)work + 0x49c0);
                    temp++;
                    *(int*)((unsigned char *)work + 0x49c0) = temp;
                    goto update_counter_check;
                } else {
                    *(int*)((unsigned char *)work + 0x49c0) = 0;
                    goto update_counter_check;
                }
                *(int*)((unsigned char *)work + 0x49c4) = new_state;
                *(int*)((unsigned char *)work + 0x49c0) = 1;
                goto update_counter_check;

            case 2:
                // State 2
                if (input_0 & 0x1000) {
                    temp = *(int*)((unsigned char *)work + 0x49c0);
                    temp++;
                    *(int*)((unsigned char *)work + 0x49c0) = temp;
                    goto update_counter_check;
                } else if (input_0 & 0x2000) {
                    new_state = 2;
                } else if (input_0 & 0x8000) {
                    new_state = 3;
                    *(int*)((unsigned char *)work + 0x49c4) = new_state;
                    *(int*)((unsigned char *)work + 0x49c0) = 1;
                    goto update_counter_check;
                } else if (input_0 & 0x4000) {
                    temp = *(int*)((unsigned char *)work + 0x49c0);
                    temp++;
                    *(int*)((unsigned char *)work + 0x49c0) = temp;
                    goto update_counter_check;
                } else {
                    *(int*)((unsigned char *)work + 0x49c0) = 0;
                    goto update_counter_check;
                }
                *(int*)((unsigned char *)work + 0x49c4) = new_state;
                *(int*)((unsigned char *)work + 0x49c0) = 1;
                goto update_counter_check;

            case 3:
                // State 3
                if (input_0 & 0x4000) {
                    temp = *(int*)((unsigned char *)work + 0x49c0);
                    temp++;
                    *(int*)((unsigned char *)work + 0x49c0) = temp;
                    goto update_counter_check;
                } else if (input_0 & 0x2000) {
                    new_state = 2;
                } else if (input_0 & 0x8000) {
                    new_state = 3;
                } else if (input_0 & 0x1000) {
                    new_state = 6;
                    *(int*)((unsigned char *)work + 0x49c4) = 0;
                    *(int*)((unsigned char *)work + 0x49c0) = new_state;
                    goto update_counter_check;
                } else {
                    *(int*)((unsigned char *)work + 0x49c0) = 0;
                    goto update_counter_check;
                }
                *(int*)((unsigned char *)work + 0x49c4) = new_state;
                *(int*)((unsigned char *)work + 0x49c0) = 1;
                goto update_counter_check;

            case 4:
                // State 4
                if (input_0 & 0x2000) {
                    temp = *(int*)((unsigned char *)work + 0x49c0);
                    temp++;
                    *(int*)((unsigned char *)work + 0x49c0) = temp;
                    goto update_counter_check;
                } else if (input_0 & 0x8000) {
                    new_state = 3;
                    *(int*)((unsigned char *)work + 0x49c4) = new_state;
                    *(int*)((unsigned char *)work + 0x49c0) = 1;
                    goto update_counter_check;
                } else if (input_0 & 0x1000) {
                    new_state = 6;
                    *(int*)((unsigned char *)work + 0x49c4) = 0;
                    *(int*)((unsigned char *)work + 0x49c0) = new_state;
                    goto update_counter_check;
                } else if (input_0 & 0x4000) {
                    new_state = 1;
                    *(int*)((unsigned char *)work + 0x49c4) = new_state;
                    *(int*)((unsigned char *)work + 0x49c0) = new_state;
                    goto update_counter_check;
                } else {
                    *(int*)((unsigned char *)work + 0x49c0) = 0;
                    goto update_counter_check;
                }

            case 5:
                // State 5
                if (input_0 & 0x8000) {
                    new_state = 3;
                    *(int*)((unsigned char *)work + 0x49c4) = new_state;
                    *(int*)((unsigned char *)work + 0x49c0) = 1;
                    goto update_counter_check;
                } else if (input_0 & 0x2000) {
                    new_state = 2;
                    *(int*)((unsigned char *)work + 0x49c4) = new_state;
                    *(int*)((unsigned char *)work + 0x49c0) = 1;
                    goto update_counter_check;
                } else if (input_0 & 0x1000) {
                    new_state = 6;
                    *(int*)((unsigned char *)work + 0x49c4) = 0;
                    *(int*)((unsigned char *)work + 0x49c0) = new_state;
                    goto update_counter_check;
                } else if (input_0 & 0x4000) {
                    new_state = 1;
                    *(int*)((unsigned char *)work + 0x49c4) = new_state;
                    *(int*)((unsigned char *)work + 0x49c0) = new_state;
                    goto update_counter_check;
                } else {
                    *(int*)((unsigned char *)work + 0x49c0) = 0;
                    goto update_counter_check;
                }
            }
        }
    }

update_counter_check:
    // Check if counter exceeds limit
    counter = *(int*)((unsigned char *)work + 0x49c0);
    if (counter >= 6) {
        *(int*)((unsigned char *)work + 0x49c0) = 1;
        temp = 1;
    } else {
        temp = 0;
    }

    if (temp == 0) {
        return;
    }

    // Play sound effect based on state
    state = *(int*)((unsigned char *)work + 0x49c4);

    // Check if state is 2 or 3 (range check)
    if ((state - 2) < 2 || state == 0 || state == 1) {
        GM_SeSet2(0, 0x3f, 0x67);
    }

    // Main menu state machine - dispatch to handle 46 different menu positions
    menu_state = *(int*)((unsigned char *)work + 0x4940);

    if (menu_state < 0x2e) {
        // Large switch statement for menu positions
        // Each case positions UI elements and updates state based on input
        switch (menu_state) {
        case 0:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x54, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xd;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x62, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xd;
            } else if (state == 0) {
                *(int*)((unsigned char *)work + 0x4940) = 0x1b;
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x54, 0x57, 0xa, 8, 0xff, 0);
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x87, 0x41, 0x9, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x2a;
            }
            break;

        case 1:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x46, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = state;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x54, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xe;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x46, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1c;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x62, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0;
            }
            break;

        case 2:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x38, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 3;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x46, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xf;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x38, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1d;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x54, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 1;
            }
            break;

        case 3:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x2a, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 4;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x38, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x10;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x2a, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1e;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x46, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 2;
            }
            break;

        case 4:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x1c, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 5;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x2a, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x11;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x2a, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1f;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x38, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 3;
            }
            break;

        case 5:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0xe, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 6;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x1c, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x12;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x1c, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x20;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x2a, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 4;
            }
            break;

        case 6:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 7;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0xe, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x13;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x1c, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 5;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0xe, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x21;
            }
            break;

        case 7:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0xe, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 8;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x14;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x22;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0xe, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 6;
            }
            break;

        case 8:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x1c, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 9;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0xe, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x15;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0xe, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x23;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 7;
            }
            break;

        case 9:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x2a, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xa;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x1c, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x16;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x1c, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x24;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0xe, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 8;
            }
            break;

        case 10:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x38, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xb;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x2a, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x17;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x2a, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x25;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x1c, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 9;
            }
            break;

        case 11:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x46, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xc;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x38, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x18;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x38, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x26;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x2a, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xa;
            }
            break;

        case 12:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x54, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x2b;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x46, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x19;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x46, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x27;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x38, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xb;
            }
            break;

        case 13:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x62, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xe;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x62, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1a;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x62, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x7f, 0x4c, 0x9, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x2a;
            }
            break;

        case 14:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x54, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xf;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x54, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1b;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x54, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x62, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xd;
            }
            break;

        case 15:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x46, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x10;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x46, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1c;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x46, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 1;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x54, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xe;
            }
            break;

        case 16:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x38, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x11;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x38, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1d;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x38, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 2;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x46, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xf;
            }
            break;

        case 17:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x2a, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x12;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x2a, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1e;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x2a, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 3;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x38, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x10;
            }
            break;

        case 18:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x1c, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x13;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x1c, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1f;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x1c, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 4;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x2a, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x11;
            }
            break;

        case 19:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0xe, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x14;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0xe, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x20;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0xe, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 5;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x1c, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x12;
            }
            break;

        case 20:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x15;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x21;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 6;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0xe, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x13;
            }
            break;

        case 21:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0xe, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x16;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0xe, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x22;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0xe, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 7;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x14;
            }
            break;

        case 22:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x1c, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x17;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x1c, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x23;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x1c, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 8;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0xe, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x15;
            }
            break;

        case 23:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x2a, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x18;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x2a, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x24;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x2a, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 9;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x1c, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x16;
            }
            break;

        case 24:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x38, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x19;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x38, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x25;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x38, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xa;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x2a, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x17;
            }
            break;

        case 25:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x46, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x2d;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x46, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x26;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x46, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xb;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x38, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x18;
            }
            break;

        case 26:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x62, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1b;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x62, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xd;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x62, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x7f, 0x57, 0x9, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x29;
            }
            break;

        case 27:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x54, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1c;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x54, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xe;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x54, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x62, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1a;
            }
            break;

        case 28:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x46, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1d;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x46, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xf;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x46, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 1;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x54, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1b;
            }
            break;

        case 29:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x38, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1e;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x38, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x10;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x38, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 2;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x46, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1c;
            }
            break;

        case 30:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x2a, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1f;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x2a, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x11;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x2a, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 3;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x38, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1d;
            }
            break;

        case 31:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x1c, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x20;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x1c, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x12;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x1c, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 4;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x2a, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1e;
            }
            break;

        case 32:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0xe, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x21;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0xe, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x13;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0xe, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 5;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x1c, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1f;
            }
            break;

        case 33:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x22;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x14;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 6;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0xe, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x20;
            }
            break;

        case 34:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0xe, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x23;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0xe, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x15;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0xe, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 7;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x21;
            }
            break;

        case 35:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x1c, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x24;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x1c, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x16;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x1c, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 8;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0xe, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x22;
            }
            break;

        case 36:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x2a, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x25;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x2a, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x17;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x2a, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 9;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x1c, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x23;
            }
            break;

        case 37:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x38, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x26;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x38, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x18;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x38, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xa;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x2a, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x24;
            }
            break;

        case 38:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x46, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x27;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x46, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x19;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x46, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xb;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x38, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x25;
            }
            break;

        case 39:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x54, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x28;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x54, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x2b;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x54, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xc;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x46, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x26;
            }
            break;

        case 40:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x62, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x29;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x62, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x2c;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x62, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x2b;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x54, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x27;
            }
            break;

        case 41:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x7f, 0x57, 0x9, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x2a;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x7f, 0x4c, 0x9, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x2a;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x7f, 0x41, 0x9, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x2a;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x62, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x28;
            }
            break;

        case 42:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x7f, 0x41, 0x9, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x2a;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x7f, 0x57, 0x9, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x29;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x7f, 0x4c, 0x9, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x2a;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x54, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0xc;
            }
            break;

        case 43:
            if (state == 2) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x62, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x2d;
            } else if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x62, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x28;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x62, 0x41, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x2b;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x46, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x19;
            }
            break;

        case 44:
            if (state == 1) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x54, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x2b;
            } else if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x54, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x27;
            } else if (state == 3) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x62, 0x4c, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x2c;
            }
            break;

        case 45:
            if (state == 0) {
                ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x62, 0x57, 0xa, 8, 0xff, 0);
                *(int*)((unsigned char *)work + 0x4940) = 0x1a;
            }
            break;

        default:
            break;
        }
    }

    // Handle state 4 and 5 actions
    state = *(int*)((unsigned char *)work + 0x49c4);

    if (state == 5) {
        // State 5: Handle scroll down
        val_4964 = *(int*)((unsigned char *)work + 0x4964);
        val_4960 = *(int*)((unsigned char *)work + 0x4960);

        if (val_4960 < val_4964) {
            val_4960++;
            *(int*)((unsigned char *)work + 0x4960) = val_4960;
        }
        return;
    }

    if (state == 4) {
        // State 4: Main action/select
        menu_state = *(int*)((unsigned char *)work + 0x4940);

        if (menu_state < 0x2e) {
            // Jump table for state 4 actions
            switch (menu_state) {
            case 0:
            case 1:
                // Save/Load action
                GM_SeSet2(0, 0x3f, 0x20);

                val_4934 = *(int*)((unsigned char *)work + 0x4934);
                if (val_4934 != 0) {
                    *(int*)((unsigned char *)work + 0x493c) = 4;
                } else {
                    *(int*)((unsigned char *)work + 0x493c) = 2;
                }

                *(int*)((unsigned char *)work + 0x4938) = 0;

                // Copy data from 0x4994 to 0x494c (16 bytes)
                byte_ptr = (unsigned char *)work + 0x4994;
                for (i = 0; i < 0x10; i++) {
                    ((unsigned char *)work)[0x494c + i] = byte_ptr[i];
                }

                if (menu_state == 0) {
                    camera_800C869C(work);
                } else {
                    GM_SeSet2(0, 0x3f, 0x21);

                    val_4934 = *(int*)((unsigned char *)work + 0x4934);
                    if (val_4934 != 0) {
                        *(int*)((unsigned char *)work + 0x493c) = 4;
                    } else {
                        *(int*)((unsigned char *)work + 0x493c) = 2;
                    }

                    *(int*)((unsigned char *)work + 0x4938) = 0;
                    camera_800C869C(work);
                }
                break;

            case 44:
                // Scroll up case
                val_4960 = *(int*)((unsigned char *)work + 0x4960);
                if (val_4960 > 0) {
                    val_4960--;
                    *(int*)((unsigned char *)work + 0x4960) = val_4960;
                }
                break;

            case 13:
            case 42:
                // Specific menu item handling with character data
                val_4960 = *(int*)((unsigned char *)work + 0x4960);

                if (val_4960 < 0xf) {
                    GM_SeSet2(0, 0x3f, 0xb2);

                    temp = 0x20;
                    ((unsigned char *)work)[0x4994 + val_4960] = temp;

                    val_4964 = *(int*)((unsigned char *)work + 0x4964);
                    if (val_4960 == val_4964) {
                        val_4964++;
                        *(int*)((unsigned char *)work + 0x4964) = val_4964;
                    }

                    val_4960++;
                    *(int*)((unsigned char *)work + 0x4960) = val_4960;
                } else if (val_4960 == 0xf) {
                    GM_SeSet2(0, 0x3f, 0xb2);

                    temp = 0x20;
                    ((unsigned char *)work)[0x4994 + val_4960] = temp;

                    *(int*)((unsigned char *)work + 0x4940) = 0x2c;
                    ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x62, 0x4c, 0x2e, 8, 0xff, 0);
                }
                break;

            default:
                // Default character selection for menu states 2-12, 14-41, 43, 45
                val_4960 = *(int*)((unsigned char *)work + 0x4960);

                if (val_4960 < 0xf) {
                    GM_SeSet2(0, 0x3f, 0xb2);

                    // Calculate character code based on menu_state
                    // This appears to be a character table mapping
                    temp = 0x20 + menu_state;  // Simplified - actual mapping is complex
                    ((unsigned char *)work)[0x4994 + val_4960] = temp;

                    val_4964 = *(int*)((unsigned char *)work + 0x4964);
                    if (val_4960 == val_4964) {
                        val_4964++;
                        *(int*)((unsigned char *)work + 0x4964) = val_4964;
                    }

                    val_4960++;
                    *(int*)((unsigned char *)work + 0x4960) = val_4960;
                } else if (val_4960 == 0xf) {
                    GM_SeSet2(0, 0x3f, 0xb2);

                    temp = 0x20 + menu_state;  // Simplified
                    ((unsigned char *)work)[0x4994 + val_4960] = temp;

                    *(int*)((unsigned char *)work + 0x4940) = 0x2c;
                    ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, 0x62, 0x4c, 0x2e, 8, 0xff, 0);
                }
                break;
            }
        }
    }
}

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800CA918.s")
void camera_800CB024(CameraWork *work)
{
    unsigned short* input_ptr;
    unsigned short  input_0;
    unsigned short  input_2;
    int  state;
    int  temp;
    int  val_4980;
    int  val_4984;
    int  val_4988;
    int  val_4974;
    int  val_4978;
    int  val_497c;
    int  val_4934;

    // Read input structure from offset 0x24
    input_ptr = *(unsigned short**)((unsigned char *)work + 0x24);
    input_2 = input_ptr[1];  // offset 2 of input
    input_0 = input_ptr[0];  // offset 0 of input

    // Load state from offset 0x4948
    state = *(int*)((unsigned char *)work + 0x4948);

    // State bounds check - if state >= 6, skip to end logic
    if ((unsigned int)state >= 6) {
        goto check_end_flags;
    }

    // State machine dispatch using jump table
    switch (state) {
    case 0:
        // State 0: Initial state - check for state transitions
        if (input_2 & 0x4000) {
            // Transition to state 1
            GM_SeSet2(0, 0x3f, 0x1f);
            *(int*)((unsigned char *)work + 0x4948) = 1;
            ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x8f, 0x41, 0xa, 8, 0xff, 0);
            goto check_end_flags;
        }

        if (input_0 & 0x2000) {
            // D-pad right - increase value at 0x4980
            val_4980 = *(int*)((unsigned char *)work + 0x4980);
            if (val_4980 < 100) {
                GM_SeSet2(0, 0x3f, 0x67);
                val_4980 = *(int*)((unsigned char *)work + 0x4980);
                val_4980 += 1;
                *(int*)((unsigned char *)work + 0x4980) = val_4980;
            }
            goto check_end_flags;
        }

        if (input_0 & 0x8000) {
            // D-pad left - decrease value at 0x4980
            val_4980 = *(int*)((unsigned char *)work + 0x4980);
            if (val_4980 >= -99) {
                GM_SeSet2(0, 0x3f, 0x67);
                val_4980 = *(int*)((unsigned char *)work + 0x4980);
                val_4980 -= 1;
                *(int*)((unsigned char *)work + 0x4980) = val_4980;
            }
            goto check_end_flags;
        }

        if (input_0 & 8) {
            // Fast increase - add 10 or cap at 100
            val_4980 = *(int*)((unsigned char *)work + 0x4980);
            if (val_4980 < 91) {
                GM_SeSet2(0, 0x3f, 0x67);
                val_4980 = *(int*)((unsigned char *)work + 0x4980);
                val_4980 += 10;
                *(int*)((unsigned char *)work + 0x4980) = val_4980;
            } else if (val_4980 < 100) {
                GM_SeSet2(0, 0x3f, 0x67);
                *(int*)((unsigned char *)work + 0x4980) = 100;
            }
            goto check_end_flags;
        }

        if (input_0 & 4) {
            // Fast decrease - subtract 10 or cap at -100
            val_4980 = *(int*)((unsigned char *)work + 0x4980);
            if (val_4980 >= -90) {
                GM_SeSet2(0, 0x3f, 0x67);
                val_4980 = *(int*)((unsigned char *)work + 0x4980);
                val_4980 -= 10;
                *(int*)((unsigned char *)work + 0x4980) = val_4980;
            } else if (val_4980 >= -99) {
                GM_SeSet2(0, 0x3f, 0x67);
                *(int*)((unsigned char *)work + 0x4980) = -100;
            }
            goto check_end_flags;
        }
        goto check_end_flags;

    case 1:
        // State 1: Second parameter adjustment
        if (input_2 & 0x4000) {
            // Transition to state 2
            GM_SeSet2(0, 0x3f, 0x1f);
            *(int*)((unsigned char *)work + 0x4948) = 2;
            ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x8f, 0x4d, 0xa, 8, 0xff, 0);
            goto check_end_flags;
        }

        if (input_2 & 0x1000) {
            // Transition back to state 0
            GM_SeSet2(0, 0x3f, 0x1f);
            *(int*)((unsigned char *)work + 0x4948) = 0;
            ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x8f, 0x35, 0xa, 8, 0xff, 0);
            goto check_end_flags;
        }

        if (input_0 & 0x2000) {
            // D-pad right - increase value at 0x4984
            val_4984 = *(int*)((unsigned char *)work + 0x4984);
            if (val_4984 < 100) {
                GM_SeSet2(0, 0x3f, 0x67);
                val_4984 = *(int*)((unsigned char *)work + 0x4984);
                val_4984 += 1;
                *(int*)((unsigned char *)work + 0x4984) = val_4984;
            }
            goto check_end_flags;
        }

        if (input_0 & 0x8000) {
            // D-pad left - decrease value at 0x4984
            val_4984 = *(int*)((unsigned char *)work + 0x4984);
            if (val_4984 >= -99) {
                GM_SeSet2(0, 0x3f, 0x67);
                val_4984 = *(int*)((unsigned char *)work + 0x4984);
                val_4984 -= 1;
                *(int*)((unsigned char *)work + 0x4984) = val_4984;
            }
            goto check_end_flags;
        }

        if (input_0 & 8) {
            // Fast increase - add 10 or cap at 100
            val_4984 = *(int*)((unsigned char *)work + 0x4984);
            if (val_4984 < 91) {
                GM_SeSet2(0, 0x3f, 0x67);
                val_4984 = *(int*)((unsigned char *)work + 0x4984);
                val_4984 += 10;
                *(int*)((unsigned char *)work + 0x4984) = val_4984;
            } else if (val_4984 < 100) {
                GM_SeSet2(0, 0x3f, 0x67);
                *(int*)((unsigned char *)work + 0x4984) = 100;
            }
            goto check_end_flags;
        }

        if (input_0 & 4) {
            // Fast decrease - subtract 10 or cap at -100
            val_4984 = *(int*)((unsigned char *)work + 0x4984);
            if (val_4984 >= -90) {
                GM_SeSet2(0, 0x3f, 0x67);
                val_4984 = *(int*)((unsigned char *)work + 0x4984);
                val_4984 -= 10;
                *(int*)((unsigned char *)work + 0x4984) = val_4984;
            } else if (val_4984 >= -99) {
                GM_SeSet2(0, 0x3f, 0x67);
                *(int*)((unsigned char *)work + 0x4984) = -100;
            }
            goto check_end_flags;
        }
        goto check_end_flags;

    case 2:
        // State 2: Third parameter adjustment
        if (input_2 & 0x4000) {
            // Transition to state 3
            GM_SeSet2(0, 0x3f, 0x1f);
            *(int*)((unsigned char *)work + 0x4948) = 3;
            ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x81, 0x5c, 0x1c, 8, 0xff, 0);
            goto check_end_flags;
        }

        if (input_2 & 0x1000) {
            // Transition back to state 1
            GM_SeSet2(0, 0x3f, 0x1f);
            *(int*)((unsigned char *)work + 0x4948) = 1;
            ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x8f, 0x41, 0xa, 8, 0xff, 0);
            goto check_end_flags;
        }

        if (input_0 & 0x2000) {
            // D-pad right - increase value at 0x4988
            val_4988 = *(int*)((unsigned char *)work + 0x4988);
            if (val_4988 < 100) {
                GM_SeSet2(0, 0x3f, 0x67);
                val_4988 = *(int*)((unsigned char *)work + 0x4988);
                val_4988 += 1;
                *(int*)((unsigned char *)work + 0x4988) = val_4988;
            }
            goto check_end_flags;
        }

        if (input_0 & 0x8000) {
            // D-pad left - decrease value at 0x4988
            val_4988 = *(int*)((unsigned char *)work + 0x4988);
            if (val_4988 >= -99) {
                GM_SeSet2(0, 0x3f, 0x67);
                val_4988 = *(int*)((unsigned char *)work + 0x4988);
                val_4988 -= 1;
                *(int*)((unsigned char *)work + 0x4988) = val_4988;
            }
            goto check_end_flags;
        }

        if (input_0 & 8) {
            // Fast increase - add 10 or cap at 100
            val_4988 = *(int*)((unsigned char *)work + 0x4988);
            if (val_4988 < 91) {
                GM_SeSet2(0, 0x3f, 0x67);
                val_4988 = *(int*)((unsigned char *)work + 0x4988);
                val_4988 += 10;
                *(int*)((unsigned char *)work + 0x4988) = val_4988;
            } else if (val_4988 < 100) {
                GM_SeSet2(0, 0x3f, 0x67);
                *(int*)((unsigned char *)work + 0x4988) = 100;
            }
            goto check_end_flags;
        }

        if (input_0 & 4) {
            // Fast decrease - subtract 10 or cap at -100
            val_4988 = *(int*)((unsigned char *)work + 0x4988);
            if (val_4988 >= -90) {
                GM_SeSet2(0, 0x3f, 0x67);
                val_4988 = *(int*)((unsigned char *)work + 0x4988);
                val_4988 -= 10;
                *(int*)((unsigned char *)work + 0x4988) = val_4988;
            } else if (val_4988 >= -99) {
                GM_SeSet2(0, 0x3f, 0x67);
                *(int*)((unsigned char *)work + 0x4988) = -100;
            }
            goto check_end_flags;
        }
        goto check_end_flags;

    case 3:
        // State 3: Confirm/reset state
        if (input_2 & 0x1000) {
            // Transition to state 2
            GM_SeSet2(0, 0x3f, 0x1f);
            *(int*)((unsigned char *)work + 0x4948) = 2;
            ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x8f, 0x4d, 0xa, 8, 0xff, 0);
            goto check_end_flags;
        }

        if (input_2 & 0x2000) {
            goto check_for_reset;
        }

        if (input_2 & 0x8000) {
            goto check_for_confirm;
        }
        goto check_end_flags;

    case 4:
        // State 4: Another transition state
        if (input_2 & 0x1000) {
            // Transition to state 2
            GM_SeSet2(0, 0x3f, 0x1f);
            *(int*)((unsigned char *)work + 0x4948) = 2;
            ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x8f, 0x4d, 0xa, 8, 0xff, 0);
            goto check_end_flags;
        }

        if (input_2 & 0x2000) {
            // Transition to state 5
            GM_SeSet2(0, 0x3f, 0x1f);
            *(int*)((unsigned char *)work + 0x4948) = 5;
            ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x19, 0x5c, 0x38, 8, 0xff, 0);
            goto check_end_flags;
        }

        if (input_2 & 0x8000) {
            // Transition to state 3
            GM_SeSet2(0, 0x3f, 0x1f);
            *(int*)((unsigned char *)work + 0x4948) = 3;
            ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x81, 0x5c, 0x1c, 8, 0xff, 0);
            goto check_end_flags;
        }
        goto check_end_flags;

    case 5:
        // State 5: Final/exit state
        if (input_2 & 0x1000) {
            // Transition to state 2
            GM_SeSet2(0, 0x3f, 0x1f);
            *(int*)((unsigned char *)work + 0x4948) = 2;
            ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x8f, 0x4d, 0xa, 8, 0xff, 0);
            goto check_end_flags;
        }

        if (input_2 & 0x8000) {
            goto check_for_confirm;
        }
        goto check_end_flags;
    }

check_for_reset:
    // Check for 0x2000 flag (reset action)
    if (!(input_2 & 0x2000)) {
        goto check_end_flags;
    }
    // Transition to state 5
    GM_SeSet2(0, 0x3f, 0x1f);
    *(int*)((unsigned char *)work + 0x4948) = 5;
    ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x19, 0x5c, 0x38, 8, 0xff, 0);
    goto check_end_flags;

check_for_confirm:
    // Check for 0x8000 flag (confirm action)
    if (!(input_2 & 0x8000)) {
        goto check_end_flags;
    }
    // Transition to state 4
    GM_SeSet2(0, 0x3f, 0x1f);
    *(int*)((unsigned char *)work + 0x4948) = 4;
    ((void (*)(char *, int, int, int, int, int, int))camera_800C884C)((char *)work, -0x51, 0x5c, 0x30, 8, 0xff, 0);
    goto check_end_flags;

check_end_flags:
    // Check input_2 flag 0x40 for confirm action
    if (input_2 & 0x40) {
        // Confirm - save values and clear state
        val_4934 = *(int*)((unsigned char *)work + 0x4934);
        if (val_4934 != 0) {
            *(int*)((unsigned char *)work + 0x4944) = 4;
        } else {
            *(int*)((unsigned char *)work + 0x4944) = 2;
        }

        *(int*)((unsigned char *)work + 0x4938) = 0;
        camera_800C869C(work);

        // Copy values from 0x4974-0x497c to 0x4980-0x4988
        val_4974 = *(int*)((unsigned char *)work + 0x4974);
        *(int*)((unsigned char *)work + 0x4980) = val_4974;

        val_4978 = *(int*)((unsigned char *)work + 0x4978);
        *(int*)((unsigned char *)work + 0x4984) = val_4978;

        val_497c = *(int*)((unsigned char *)work + 0x497c);
        *(int*)((unsigned char *)work + 0x4988) = val_497c;

        // Calculate scaled values for 0x4968, 0x496c, 0x4970
        // Formula: ((value + 100) * 255) / 200 = ((value + 100) * 255 + 199) / 200
        // Implemented as: ((value + 100) << 8) - (value + 100)) >> 6
        // which is: (value + 100) * 255 / 64 (approximation)
        temp = val_4974 + 100;
        temp = (temp << 8) - temp;
        *(int*)((unsigned char *)work + 0x4968) = temp >> 6;

        temp = val_4978 + 100;
        temp = (temp << 8) - temp;
        *(int*)((unsigned char *)work + 0x496c) = temp >> 6;

        temp = val_497c + 100;
        temp = (temp << 8) - temp;
        *(int*)((unsigned char *)work + 0x4970) = temp >> 6;

        GM_SeSet2(0, 0x3f, 0x21);
        return;
    }

    // Check input_2 flag 0x20 for cancel/reset action
    if (!(input_2 & 0x20)) {
        return;
    }

    state = *(int*)((unsigned char *)work + 0x4948);

    if (state == 3) {
        // State 3: Reset mode - clear state and values
        val_4934 = *(int*)((unsigned char *)work + 0x4934);
        if (val_4934 != 0) {
            *(int*)((unsigned char *)work + 0x4944) = 4;
        } else {
            *(int*)((unsigned char *)work + 0x4944) = 2;
        }

        *(int*)((unsigned char *)work + 0x4938) = 0;
        camera_800C869C(work);

        GM_SeSet2(0, 0x3f, 0x20);
        return;
    }

    if (state == 5) {
        // State 5: Reset values from saved state
        val_4934 = *(int*)((unsigned char *)work + 0x4934);
        if (val_4934 != 0) {
            *(int*)((unsigned char *)work + 0x4944) = 4;
        } else {
            *(int*)((unsigned char *)work + 0x4944) = 2;
        }

        *(int*)((unsigned char *)work + 0x4938) = 0;
        camera_800C869C(work);

        // Copy values from 0x4974-0x497c to 0x4980-0x4988
        val_4974 = *(int*)((unsigned char *)work + 0x4974);
        *(int*)((unsigned char *)work + 0x4980) = val_4974;

        val_4978 = *(int*)((unsigned char *)work + 0x4978);
        *(int*)((unsigned char *)work + 0x4984) = val_4978;

        val_497c = *(int*)((unsigned char *)work + 0x497c);
        *(int*)((unsigned char *)work + 0x4988) = val_497c;

        // Calculate scaled values for 0x4968, 0x496c, 0x4970
        temp = val_4974 + 100;
        temp = (temp << 8) - temp;
        *(int*)((unsigned char *)work + 0x4968) = temp >> 6;

        temp = val_4978 + 100;
        temp = (temp << 8) - temp;
        *(int*)((unsigned char *)work + 0x496c) = temp >> 6;

        temp = val_497c + 100;
        temp = (temp << 8) - temp;
        *(int*)((unsigned char *)work + 0x4970) = temp >> 6;

        GM_SeSet2(0, 0x3f, 0x21);
        return;
    }

    if (state == 4) {
        // State 4: Reset to zero
        *(int*)((unsigned char *)work + 0x4980) = 0;
        *(int*)((unsigned char *)work + 0x4984) = 0;
        *(int*)((unsigned char *)work + 0x4988) = 0;

        // Calculate scaled values for zero (100 base)
        // (0 + 100) * 255 / 64 = 100 * 255 / 64 = 398
        temp = 100;  // 0 + 100
        temp = (temp << 8) - temp;
        *(int*)((unsigned char *)work + 0x4968) = temp >> 6;

        temp = 100;
        temp = (temp << 8) - temp;
        *(int*)((unsigned char *)work + 0x496c) = temp >> 6;

        temp = 100;
        temp = (temp << 8) - temp;
        *(int*)((unsigned char *)work + 0x4970) = temp >> 6;

        GM_SeSet2(0, 0x3f, 0x20);
    }
}

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800CB8AC.s")
#pragma INCLUDE_ASM("asm/overlays/camera/camera_800CBCC8.s")
#pragma INCLUDE_ASM("asm/overlays/camera/camera_800CBDE4.s")
#pragma INCLUDE_ASM("asm/overlays/camera/camera_800CC3C8.s")
#pragma INCLUDE_ASM("asm/overlays/camera/camera_800CCBB0.s")
#pragma INCLUDE_ASM("asm/overlays/camera/camera_800CD0A0.s")
void camera_800CD198(void *a0)
{
    unsigned short *input_ptr;
    unsigned short input_flags;
    int state;
    int anim_counter;
    int y_offset;
    int temp;
    unsigned int *dlist_ptr;
    unsigned int *prim_ptr;
    unsigned int prim_addr;
    unsigned int mask_lo;
    unsigned int mask_hi;
    unsigned int *tex_ptr;
    unsigned int prim_val;
    unsigned int tex_val;

    
    input_ptr = *(unsigned short **)((unsigned char *)a0 + 0x24);
    input_flags = input_ptr[1];  

    
    state = *(int *)((unsigned char *)a0 + 0x498c);

    
    if (state == 1)
    {
        
        goto state_1;
    }
    else if (state < 2)
    {
        if (state == 0)
        {
            
            goto state_0;
        }
        
        return;
    }
    else if (state == 2)
    {
        
        goto state_2;
    }
    
    return;

state_0:
    
    anim_counter = *(int *)((unsigned char *)a0 + 0x4938);

    if (anim_counter < 5)
    {
        
        MENU_Locate(100, 90, 16);
        MENU_Color(86, 137, 116);  
        goto print_and_draw_initial;
    }

    if (anim_counter < 10)
    {
        
        y_offset = 90 - ((anim_counter - 4) << 3);
        MENU_Locate(100, y_offset, 16);
        MENU_Color(86, 137, 116);
        goto print_and_draw_initial;
    }

    if (anim_counter == 10)
    {
        
        MENU_Locate(100, 50, 16);
        MENU_Color(86, 137, 116);
        MENU_Printf(camera_aOverwriteok_800CFF2C);

        
        MENU_Locate(100, 105, 16);
        MENU_Color(46, 72, 61);  
        MENU_Printf(camera_aYes_800D0094);

        
        MENU_Locate(200, 105, 16);
        MENU_Color(192, 192, 192);  
        MENU_Printf(camera_aNo_800D0090);

        
        camera_800CD0A0((void *)((unsigned char *)a0 + 0x920), 92, 85, 130, 15);

        return;
    }

    if (anim_counter < 14)
    {
        
        MENU_Locate(100, 50, 16);
        MENU_Color(86, 137, 116);
        MENU_Printf(camera_aOverwriteok_800CFF2C);

        MENU_Locate(100, 105, 16);
        MENU_Color(46, 72, 61);
        MENU_Printf(camera_aYes_800D0094);

        MENU_Locate(200, 105, 16);
        MENU_Color(192, 192, 192);
        MENU_Printf(camera_aNo_800D0090);

        
        temp = anim_counter - 10;
        camera_800CD0A0((void *)((unsigned char *)a0 + 0x920),
                        (temp << 5) + 92,              
                        temp * 5 + 85,                 
                        130 - ((temp << 4) - temp) * 2, 
                        15);

        return;
    }

    
    *(int *)((unsigned char *)a0 + 0x498c) = 2;

    MENU_Locate(100, 50, 16);
    MENU_Color(86, 137, 116);
    MENU_Printf(camera_aOverwriteok_800CFF2C);

    MENU_Locate(100, 105, 16);
    MENU_Color(46, 72, 61);
    MENU_Printf(camera_aYes_800D0094);

    MENU_Locate(200, 105, 16);
    MENU_Color(192, 192, 192);
    MENU_Printf(camera_aNo_800D0090);

    
    camera_800CD0A0((void *)((unsigned char *)a0 + 0x920), 188, 100, 40, 15);

    
    drawCaption_800C5EB4((unsigned char *)a0 + 0x700, *(void **)((unsigned char *)a0 + 0x49e4));
    *(int *)((unsigned char *)a0 + 0x49d0) = 3;

    return;

print_and_draw_initial:
    
    MENU_Printf(camera_aOverwriteok_800CFF2C);
    camera_800CD0A0((void *)((unsigned char *)a0 + 0x920), 92, 85, 130, 15);
    return;

state_1:
    
    MENU_Locate(100, 50, 16);
    MENU_Color(86, 137, 116);
    MENU_Printf(camera_aOverwriteok_800CFF2C);

    
    MENU_Locate(100, 105, 16);
    MENU_Color(192, 192, 192);  
    MENU_Printf(camera_aYes_800D0094);

    
    MENU_Locate(200, 105, 16);
    MENU_Color(46, 72, 61);  
    MENU_Printf(camera_aNo_800D0090);

    
    camera_800CD0A0((void *)((unsigned char *)a0 + 0x920), 92, 100, 40, 15);

    
    camera_800C6054((unsigned char *)a0 + 0x700, *(void **)((unsigned char *)a0 + 0x924), 0);

    
    dlist_ptr = *(unsigned int **)((unsigned char *)a0 + 0x720);
    prim_addr = *dlist_ptr;

    
    *dlist_ptr = prim_addr + 8;

    prim_ptr = (unsigned int *)prim_addr;

    
    prim_ptr[1] = 0xE100023F;

    
    ((unsigned char *)prim_ptr)[3] = 1;

    
    mask_lo = 0x00FFFFFF;
    mask_hi = 0xFF000000;

    
    tex_ptr = *(unsigned int **)((unsigned char *)a0 + 0x924);
    prim_val = prim_ptr[0];
    tex_val = *tex_ptr;

    
    prim_ptr[0] = (prim_val & mask_hi) | (tex_val & mask_lo);

    
    *tex_ptr = (tex_val & mask_hi) | ((unsigned int)prim_ptr & mask_lo);

    
    if (input_flags & 0x2000)
    {
        
        *(int *)((unsigned char *)a0 + 0x498c) = 2;
        goto play_select_sound;
    }

    if (input_flags & 0x20)
    {
        
        *(int *)((unsigned char *)a0 + 0x28) = 8;
        *(int *)((unsigned char *)a0 + 0x49c8) = 0;
        GM_SeSet2(0, 63, 32);  
        return;
    }

    
    goto check_exit_buttons;

state_2:
    
    MENU_Locate(100, 50, 16);
    MENU_Color(86, 137, 116);
    MENU_Printf(camera_aOverwriteok_800CFF2C);

    
    MENU_Locate(100, 105, 16);
    MENU_Color(46, 72, 61);  
    MENU_Printf(camera_aYes_800D0094);

    
    MENU_Locate(200, 105, 16);
    MENU_Color(192, 192, 192);  
    MENU_Printf(camera_aNo_800D0090);

    
    camera_800CD0A0((void *)((unsigned char *)a0 + 0x920), 188, 100, 40, 15);

    
    camera_800C6054((unsigned char *)a0 + 0x700, *(void **)((unsigned char *)a0 + 0x924), 0);

    
    dlist_ptr = *(unsigned int **)((unsigned char *)a0 + 0x720);
    prim_addr = *dlist_ptr;
    *dlist_ptr = prim_addr + 8;

    prim_ptr = (unsigned int *)prim_addr;
    prim_ptr[1] = 0xE100023F;
    ((unsigned char *)prim_ptr)[3] = 1;

    mask_lo = 0x00FFFFFF;
    mask_hi = 0xFF000000;

    tex_ptr = *(unsigned int **)((unsigned char *)a0 + 0x924);
    prim_val = prim_ptr[0];
    tex_val = *tex_ptr;

    prim_ptr[0] = (prim_val & mask_hi) | (tex_val & mask_lo);
    *tex_ptr = (tex_val & mask_hi) | ((unsigned int)prim_ptr & mask_lo);

    
    if (input_flags & 0x8000)
    {
        
        *(int *)((unsigned char *)a0 + 0x498c) = 1;
        goto play_select_sound;
    }

    if (input_flags & 0x20)
    {
        
        goto exit_menu;
    }

check_exit_buttons:
    
    if (input_flags & 0x40)
    {
        goto exit_menu;
    }
    return;

play_select_sound:
    
    GM_SeSet2(0, 63, 31);
    return;

exit_menu:
    
    GM_SeSet2(0, 63, 33);  

    *(int *)((unsigned char *)a0 + 0x28) = 0;

    GV_FreeMemory(2, camera_dword_800D0704);

    camera_800C82EC();
}

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800CD790.s")
#pragma INCLUDE_ASM("asm/overlays/camera/camera_800CDAB4.s")
#pragma INCLUDE_ASM("asm/overlays/camera/camera_800CDCA4.s")
int camera_800CDF18(CameraWork *a0) {
    int state;
    int result;
    int i;
    int mode;
    short *coord_ptr;
    unsigned int *dlist_ptr;
    unsigned int *prim_ptr;
    unsigned int prim_addr;
    unsigned int prim_val;
    unsigned int *tex_ptr;
    unsigned int tex_val;
    unsigned int mask_lo;
    unsigned int mask_hi;

    
    coord_ptr = (short *)((unsigned char *)a0 + 0x244);

    
    state = *(int *)((unsigned char *)a0 + 0x28);

    
    if ((unsigned int)state >= 10)
    {
        return;
    }

    
    switch (state)
    {
    case 0:
        
        result = camera_800C73E4((unsigned char *)a0 + 0x700, (*(int *)0x800B05E0));

        if (result == 1)
        {
            
            *(int *)((unsigned char *)a0 + 0x28) = 9;
        }
        else if (result == 2)
        {
            
            *(int *)((unsigned char *)a0 + 0x28) = 1;

            
            *(int *)((unsigned char *)a0 + 0x49e0) = 0;

            
            for (i = 0; i < 16; i++)
            {
                *((unsigned char *)a0 + 0x494c + i) = 0x20;
                *((unsigned char *)a0 + 0x4994 + i) = 0x20;
            }

            
            *((unsigned char *)a0 + 0x495c) = 0;
            *((unsigned char *)a0 + 0x49a4) = 0;
        }
        break;

    case 1:
        
        camera_800C4394(a0);

        
        *(int *)((unsigned char *)a0 + 0x28) = 3;

        
        mode = *(int *)((unsigned char *)a0 + 0x4934);

        if (mode == 0)
        {
            

            
            *(int *)((unsigned char *)a0 + 0x2c) = 0;

            
            *(int *)((unsigned char *)a0 + 0x4938) = 0;

            
            
            *(int *)((unsigned char *)a0 + 0x688) = 0x600;
            *(int *)((unsigned char *)a0 + 0x68c) = 0x600;
            *(int *)((unsigned char *)a0 + 0x69c) = 0x600;
            *(int *)((unsigned char *)a0 + 0x6a0) = 0x600;
            *(int *)((unsigned char *)a0 + 0x6a4) = 0x600;

            
            *(int *)((unsigned char *)a0 + 0x690) = 0x200;
            *(int *)((unsigned char *)a0 + 0x694) = 0x200;
            *(int *)((unsigned char *)a0 + 0x698) = 0x200;

            
            camera_800C86BC(a0, -0x90, 0x5a, 0x70, 0xc, 0xff);
        }
        else
        {
            

            
            *(int *)((unsigned char *)a0 + 0x2c) = 3;

            
            *(int *)((unsigned char *)a0 + 0x4938) = 0;

            
            *(int *)((unsigned char *)a0 + 0x688) = 0x600;
            *(int *)((unsigned char *)a0 + 0x68c) = 0x600;
            *(int *)((unsigned char *)a0 + 0x69c) = 0x600;
            *(int *)((unsigned char *)a0 + 0x6a0) = 0x600;
            *(int *)((unsigned char *)a0 + 0x6a4) = 0x600;

            
            *(int *)((unsigned char *)a0 + 0x6c8) = 0x200;
            *(int *)((unsigned char *)a0 + 0x6cc) = 0x200;
            *(int *)((unsigned char *)a0 + 0x6d0) = 0x200;
            *(int *)((unsigned char *)a0 + 0x6d4) = 0x200;

            
            camera_800C86BC(a0, -0x90, 0x5a, 0x68, 0xc, 0xff);

            

            
            coord_ptr[0x288 / 2] = -0x90;   
            coord_ptr[0x28a / 2] = 0x5a;    
            coord_ptr[0x290 / 2] = -0x28;   
            coord_ptr[0x292 / 2] = 0x5a;    
            coord_ptr[0x298 / 2] = -0x90;   
            coord_ptr[0x29a / 2] = 0x66;    
            coord_ptr[0x2a0 / 2] = -0x28;   
            coord_ptr[0x2a2 / 2] = 0x66;    

            
            coord_ptr[0x2b0 / 2] = -0x2a;   
            coord_ptr[0x2b2 / 2] = 0x5a;    
            coord_ptr[0x2b8 / 2] = 0x12;    
            coord_ptr[0x2ba / 2] = 0x5a;    
            coord_ptr[0x2c0 / 2] = -0x2a;   
            coord_ptr[0x2c2 / 2] = 0x66;    
            coord_ptr[0x2c8 / 2] = 0x12;    
            coord_ptr[0x2ca / 2] = 0x66;    

            
            coord_ptr[0x2d8 / 2] = 0x11;    
            coord_ptr[0x2da / 2] = 0x5a;    
            coord_ptr[0x2e0 / 2] = 0x65;    
            coord_ptr[0x2e2 / 2] = 0x5a;    
            coord_ptr[0x2e8 / 2] = 0x11;    
            coord_ptr[0x2ea / 2] = 0x66;    
            coord_ptr[0x2f0 / 2] = 0x65;    
            coord_ptr[0x2f2 / 2] = 0x66;    

            
            coord_ptr[0x300 / 2] = 0x64;    
            coord_ptr[0x302 / 2] = 0x5a;    
            coord_ptr[0x308 / 2] = 0x90;    
            coord_ptr[0x30a / 2] = 0x5a;    
            coord_ptr[0x310 / 2] = 0x64;    
            coord_ptr[0x312 / 2] = 0x66;    
            coord_ptr[0x318 / 2] = 0x90;    
            coord_ptr[0x31a / 2] = 0x66;    
        }
        break;

    case 2:
        
        break;

    case 3:
        

        
        MENU_Locate(0x1a, 0xe, 0);
        MENU_Color(0x3a, 0x5c, 0x4e);  
        MENU_Printf((const char *)((unsigned char *)a0 + 0x49d4));

        
        MENU_Locate(0x4b, 0xe, 0);
        MENU_Color(0x3a, 0x5c, 0x4e);
        MENU_Printf((const char *)((unsigned char *)a0 + 0x49dd));

        
        {
            void *menu_ctx = (unsigned char *)a0 + 0x49a8;

            camera_800C8554(menu_ctx, 0x53, 0xd, 0x10);
            camera_800C85B8(menu_ctx, 0x56, 0x89, 0x74);  
            camera_800C8564((unsigned char *)a0 + 0x920, menu_ctx, (unsigned char *)a0 + 0x494c);
        }

        
        camera_800CCBB0(a0);
        break;

    case 4:
        

        
        MENU_Locate(0x1a, 0xe, 0);
        MENU_Color(0x3a, 0x5c, 0x4e);
        MENU_Printf((const char *)((unsigned char *)a0 + 0x49d4));

        MENU_Locate(0x4b, 0xe, 0);
        MENU_Color(0x3a, 0x5c, 0x4e);
        MENU_Printf((const char *)((unsigned char *)a0 + 0x49dd));

        
        {
            void *menu_ctx = (unsigned char *)a0 + 0x49a8;

            camera_800C8554(menu_ctx, 0x53, 0xd, 0x10);
            camera_800C85B8(menu_ctx, 0x56, 0x89, 0x74);
            camera_800C8564((unsigned char *)a0 + 0x920, menu_ctx, (unsigned char *)a0 + 0x494c);
        }

        
        camera_800CA918(a0);
        break;

    case 5:
        

        
        MENU_Locate(0x1a, 0xe, 0);
        MENU_Color(0x3a, 0x5c, 0x4e);
        MENU_Printf((const char *)((unsigned char *)a0 + 0x49d4));

        MENU_Locate(0x4b, 0xe, 0);
        MENU_Color(0x3a, 0x5c, 0x4e);
        MENU_Printf((const char *)((unsigned char *)a0 + 0x49dd));

        
        {
            void *menu_ctx = (unsigned char *)a0 + 0x49a8;

            camera_800C8554(menu_ctx, 0x53, 0xd, 0x10);
            camera_800C85B8(menu_ctx, 0x56, 0x89, 0x74);
            camera_800C8564((unsigned char *)a0 + 0x920, menu_ctx, (unsigned char *)a0 + 0x494c);
        }

        
        camera_800CC3C8(a0);
        break;

    case 6:
        
        camera_800CBDE4(a0);
        break;

    case 7:
        
        camera_800CD198(a0);
        break;

    case 8:
        
        camera_800CDCA4(a0);

        
        {
            int countdown = *(int *)((unsigned char *)a0 + 0x49d0);

            if (countdown >= 2)
            {
                
                *(int *)((unsigned char *)a0 + 0x49d0) = countdown - 1;
            }
            else
            {
                

                
                camera_800C6054((unsigned char *)a0 + 0x700, *(void **)((unsigned char *)a0 + 0x924), 0);

                
                dlist_ptr = *(unsigned int **)((unsigned char *)a0 + 0x720);
                prim_addr = *dlist_ptr;

                
                *dlist_ptr = prim_addr + 8;

                prim_ptr = (unsigned int *)prim_addr;

                
                prim_ptr[1] = 0xE100023F;

                
                ((unsigned char *)prim_ptr)[3] = 1;

                
                mask_lo = 0x00FFFFFF;
                mask_hi = 0xFF000000;

                
                tex_ptr = *(unsigned int **)((unsigned char *)a0 + 0x924);
                prim_val = prim_ptr[0];
                tex_val = *tex_ptr;

                
                prim_ptr[0] = (prim_val & mask_hi) | (tex_val & mask_lo);

                
                *tex_ptr = (tex_val & mask_hi) | ((unsigned int)prim_ptr & mask_lo);
            }
        }
        break;

    case 9:
        

        
        GCL_ExecProc(*(void **)((unsigned char *)a0 + 0x20), 0);

        
        GV_DestroyActor(a0);
        break;

    default:
        
        break;
    }
}


void CameraAct_800CE404(CameraWork *work)
{
    work->field_920 = work->field_92C[GV_Clock];
    work->field_924_mOrderingTable = DG_Chanl(1)->ot[GV_Clock];
    camera_800CDF18(work);
    camera_800C3ED8(work);
    work->field_4938++;
}

void CameraDie_800CE470(CameraWork *work)
{
    GM_FreePrim(work->prim1);
    GM_FreePrim(work->prim2);
    GM_FreePrim(work->prim3);
}

int camera_800CE6EC(CameraWork *work, int where);

void camera_800CE4F8(CameraWork *work, POLY_FT4 *pPoly, int x0, int y0, int x1, int y1, int semiTrans)
{
    setPolyFT4(pPoly);
    setRGB0(pPoly, 128, 128, 128);
    pPoly->x0 = x0;
    pPoly->y0 = y0;
    pPoly->y1 = y0;
    pPoly->x2 = x0;
    pPoly->x1 = x1;
    pPoly->y2 = y1;
    pPoly->x3 = x1;
    pPoly->y3 = y1;
    SetSemiTrans(pPoly, semiTrans);
}

void camera_800CE568(CameraWork *work, int hashCode, POLY_FT4 *pPoly, int x0, int y0, int x1, int y1, int semiTrans, int arg9)
{
    DG_TEX *tex;
    camera_800CE4F8(work, pPoly, x0, y0, x1, y1, semiTrans);
    tex = DG_GetTexture(hashCode);

    if (arg9 == 0)
    {
        int offx, offx2, offx3;
        int offy, offy2;

        offx = tex->off_x;
        offx2 = offx + tex->w;
        offy = tex->off_y;
        offx3 = offx2 + 1;
        offy2 = offy + tex->h + 1;

        setUV4(pPoly, offx, offy, offx3, offy, offx, offy2, offx3, offy2);
        pPoly->tpage = tex->tpage;
        pPoly->clut = tex->clut;
    }

    else if (arg9 == 1)
    {
        int offx, offx2, offx3;
        int offy, offy2;

        offx = tex->off_x;
        offx2 = offx + tex->w;
        offy = tex->off_y;
        offx3 = offx2 + 1;
        offy2 = offy + tex->h;

        setUV4(pPoly, offx, offy, offx3, offy, offx, offy2, offx3, offy2);
        pPoly->tpage = tex->tpage;
        pPoly->clut = tex->clut;
    }

    else if (arg9 == 2)
    {
        int offx, offx2;
        int offy, offy2;

        offx = tex->off_x;
        offx2 = offx + tex->w;
        offy = tex->off_y;
        offy2 = offy + tex->h + 1;

        setUV4(pPoly, offx, offy, offx2, offy, offx, offy2, offx2, offy2);
        pPoly->tpage = tex->tpage;
        pPoly->clut = tex->clut;
    }

    else if (arg9 == 3)
    {
        int offx, offx2;
        int offy, offy2;

        offx = tex->off_x;
        offx2 = offx + tex->w;
        offy = tex->off_y;
        offy2 = offy + tex->h;

        setUV4(pPoly, offx, offy, offx2, offy, offx, offy2, offx2, offy2);
        pPoly->tpage = tex->tpage;
        pPoly->clut = tex->clut;
    }
}

int CameraGetResources_800CE6EC(CameraWork *work, int map)
{
    POLY_FT4 *poly;
    int       i;

    GM_CurrentMap = map;

    work->prim1 = GM_MakePrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 4, NULL, NULL);
    work->prim2 = GM_MakePrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 9, NULL, NULL);
    work->prim3 = GM_MakePrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 26, NULL, NULL);

    for (i = 3; i >= 0; i--)
    {
        work->field_654[i] = 0;
    }

    poly = work->polys;
    i = 0;

    camera_800CE568(work, GV_StrCode("cur_lu"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->field_664[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cur_ru"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->field_664[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cur_ld"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->field_664[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cur_rd"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->field_664[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cur_u"), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->field_664[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cur_d"), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->field_664[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cur_l"), poly, 0, 0, 0, 0, 1, 1);
    poly++;
    work->field_664[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cur_r"), poly, 0, 0, 0, 0, 1, 1);
    poly++;
    work->field_664[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cur_c"), poly, 0, 0, 0, 0, 1, 3);
    poly++;
    work->field_664[i] = NULL;
    i++;

    poly = work->polys2;
    i = 0;

    camera_800CE568(work, GV_StrCode("cam_album"), poly, 60, -102, 144, -90, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_frame"), poly, -144, -102, 60, -90, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_name"), poly, -144, 90, -32, 102, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_color"), poly, -5, 90, 63, 102, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_exit"), poly, 90, 90, 144, 102, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_line1"), poly, -144, 84, 144, 86, 0, 2);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_line2"), poly, 142, -90, 146, 86, 0, 1);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_line3"), poly, -146, -90, -142, 86, 0, 1);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_name_b"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_name_entry_l"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_name_entry_r"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_color_b"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_color_ad"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_color_cur"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_color_cur"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_color_cur"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_name"), poly, -144, 90, -40, 102, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_color"), poly, -42, 90, 18, 102, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_exor"), poly, 17, 90, 101, 102, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_exit"), poly, 100, 90, 144, 102, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_ji1_l"), poly, -139, 90, 5, 104, 1, 0);
    setRGB0(poly, 192, 192, 192);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_ji1_r"), poly, 5, 90, 133, 104, 1, 0);
    setRGB0(poly, 192, 192, 192);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_ji2"), poly, -139, 90, 89, 104, 1, 0);
    setRGB0(poly, 192, 192, 192);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_name_b"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_color_b"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    camera_800CE568(work, GV_StrCode("cam_ex_exor_b"), poly, -146, -90, -142, 86, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_688[i] = NULL;
    i++;

    if (GCL_GetOption('e') != NULL)
    {
        work->f20 = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->f20 = -1;
    }

    for (i = 0; i <= 0; i++)
    {
        work->f49E4 = GCL_ReadString(GCL_GetParamResult());
    }

    work->pad = &GV_PadData[2];
    work->f28 = 0;

    work->f720 = &work->field_920;
    work->field_92C[0] = work->padding4 + 0x210;
    work->field_4938 = 0;
    work->field_92C[1] = work->padding4 + 0x2210;

    camera_800C85D8();
    camera_800C82EC();

    work->f49E0 = 0;
    return 0;
}

void *NewCamera_800CF388(int name, int where, int argc, char **argv)
{
    CameraWork *work;

    GM_GameStatus |= STATE_ALL_OFF;
    work = GV_NewActor(EXEC_LEVEL, sizeof(CameraWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, CameraAct_800CE404, CameraDie_800CE470, "camera.c");

        if (CameraGetResources_800CE6EC(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
