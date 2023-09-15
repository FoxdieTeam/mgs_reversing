#include "menuman.h"
#include "unknown.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "memcard/memcard.h"

//------------------------------------------------------------------------------
// gp
extern int dword_800AB6F4;
int        dword_800AB6F4;

extern int dword_800ABB48;
int        dword_800ABB48;

extern int dword_800AB6EC;
int        dword_800AB6EC;

extern int dword_800ABB58;
int        dword_800ABB58;

extern int dword_800ABB5C;
int        dword_800ABB5C;

extern int dword_800AB6F0;
int        dword_800AB6F0;

extern int dword_800AB700;
int        dword_800AB700;

extern int dword_800AB6FC;
int        dword_800AB6FC;

extern int dword_800ABB54;
int        dword_800ABB54;
//------------------------------------------------------------------------------

extern int       mcd_last_check_800ABB60[2];
extern mem_card *mcd_last_file_800ABB68[2];

extern menu_save_mode_data *dword_800ABB4C;
menu_save_mode_data        *dword_800ABB4C;

extern int GM_PadResetDisable_800AB3F4;
extern char *MGS_MemoryCardName_800AB2EC;

extern char aRequestX[];
extern char aResultX[];

extern char aBislpm99999[];

int dword_8009E774[] = {
    0x24A51421, 0x45AD3529, 0x88A5631,  0x217414EF, 0x363929D6, 0x10750C13, 0x195A14D8, 0xEEB19BC,  0x12211,
    0xEA00310,  0x20000000, 0xEC00331,  0x23210012, 0xEB20243,  0x33332213, 0xEA10134,  0x44422233, 0xEA10123,
    0x34322343, 0xED11212,  0x24444443, 0xEE02221,  0x24444343, 0xEE30132,  0x23444233, 0xEE00133,  0x22334301,
    0xEB00123,  0x21224420, 0xD000113,  0x22100100, 0xA100202,  0x32112344, 0x1100201,  0x23233200, 0x1000200,
    0x2212222,  0x1000220,  0,          0,          0x24A51421, 0x45AD3529, 0x88A5631,  0x217414EF, 0x363929D6,
    0x10750C13, 0x195A14D8, 0xEEB19BC,  0x11124444, 0x2221131,  0x21000134, 0x2210222,  0x1114,     0x1230,
    0x10000124, 0x241,      0x11123234, 0x20234,    0x43334444, 0x10234,    0x44444444, 0x221233,   0x44444444,
    0x1011133,  0x34444444, 0x2100123,  0x34444334, 0x1110023,  0x33444421, 0x1000012,  0x33433443, 0x100002,
    0x23320211, 0xB001001,  0x13333233, 0xAC10000,  0x1333322,  0xCB10100,  0,          0,          0x24A51421,
    0x45AD3529, 0x88A5631,  0x217414EF, 0x363929D6, 0x10750C13, 0x195A14D8, 0xEEB19BC,  0x1343023,  0x1102021,
    0x13444312, 0x1001020,  0x3444301,  0x120,      0x22343113, 0x10021,    0x32211213, 0x10012,    0x33334433,
    0x21002,    0x24444433, 0x1002002,  0x24444334, 0x2210001,  0x23444314, 0xB100010,  0x12444302, 0xDA10011,
    0x22344421, 0xEBA0002,  0x22212333, 0xEEC1001,  0x21310100, 0xEC10100,  0x12132344, 0xC312200,  0x2112222,
    0x4233101,  0,          0,          0x2CA51C21, 0x456B3908, 0x5E3151CE, 0x217414EF, 0x363929D6, 0x10550C13,
    0x151814B7, 0x19BC195A, 0x34455555, 0xFA12022,  0x255300,   0xFA12300,  0x241CD,    0xFA12240,  0x21000BDA,
    0xFA11234,  0x445521CD, 0xFB11223,  0x34455300, 0xFDA1123,  0x33445552, 0xFFA1122,  0x33445551, 0xFFA1112,
    0x12344551, 0xFFB1221,  0x31344551, 0xFFDA122,  0x31334451, 0xFFFA112,  0x22014451, 0xFFFB012,  0x24213451,
    0xFFFB111,  0x22313441, 0xFFFB201,  0x22312341, 0xFFFA310,  0,          0,          0x14A90425, 0x35B1252D,
    0x88A4635,  0x217414EF, 0x363929D6, 0x49035844, 0x2A4139A2, 0x1E8316E0, 0x10013444, 0xE021020,  0x12221234,
    0xA010031,  0x12224,    0x32,       0x10001224, 0x200030,   0x10022324, 0x410332,   0x32233434, 0x210333,
    0x44444444, 0x110233,   0x44444444, 0xA010133,  0x44444434, 0xCA10133,  0x34444432, 0xECBA023,  0x34433443,
    0xEEDD013,  0x33421211, 0xEEED102,  0x23333222, 0xEEEC101,  0x12334310, 0xEED0100,  0x1233444,  0xEEA1002,
    0,          0,          0x14A90425, 0x35B1252D, 0x88A4635,  0x217414EF, 0x363929D6, 0x44693427, 0x60CD508B,
    0x64896CEF, 0x11001123, 0xED00210,  0x10000003, 0xEB01100,  0x11201013, 0xB200210,  0x12212124, 0xB020221,
    0x22322234, 0xC211123,  0x44322144, 0xDB10123,  0x33321234, 0xEC01012,  0x23211023, 0xEEB0112,  0x22122102,
    0xEED1121,  0x21222332, 0xEED2122,  0x10121100, 0xEEC0122,  0x10123433, 0xEEA0021,  0x12222100, 0xEC00021,
    0x1221111,  0xEA00102,  0x22222333, 0xB000301,  0,          0
};

int init_file_mode_helper_helper_helper_8004983C(struct mem_card *pMemcard)
{
  int size;
  int hours, minutes;
  int c99;
  int file;
  char *buffer, *buffer_copy;
  int ret;
  int retries;
  int difficulty;
  int flags1, flags2;
  int i, idx;

  GM_PadResetDisable_800AB3F4 = 1;

  size = dword_800ABB4C->field_3 * 8192;
  buffer = GV_AllocMemory_80015EB8(0, size);
  if (!buffer)
  {
    printf("NO MEMORY FOR FILE BODY\n");
  }

  GV_ZeroMemory_8001619C(buffer, size);

  buffer[0] = 'S';
  buffer[1] = 'C';
  buffer[2] = 17;
  buffer[3] = dword_800ABB4C->field_3;

  idx = dword_800ABB4C->field_0[1];
  buffer_copy = buffer;
  c99 = 99;

  if (idx == 0)
  {
    idx = GM_BonusItemsFlag;
    flags1 = GM_BonusItemsFlag;

    if (flags1 >= 4)
    {
      idx = 3;
      if (flags1 == 6)
      {
        idx = 0;
      }
    }

    flags2 = flags1 | ((GM_CurrentDiskFlag - 1) * 8);
  }
  else
  {
    flags2 = idx;
  }

  memcpy(buffer_copy + 96, &dword_8009E774[idx * 40], 160);

  hours = GM_TotalHours;
  minutes = GM_TotalSeconds / 60;
  if (hours > 99)
  {
    minutes = hours = c99;
  }

  dword_800ABB4C->field_8(buffer_copy + 4, pMemcard, hours, minutes);
  strcpy(aBislpm99999, MGS_MemoryCardName_800AB2EC);

  aBislpm99999[12] = dword_800ABB4C->field_0[0];
  aBislpm99999[13] = (hours / 10) + '0';
  aBislpm99999[14] = (hours % 10) + '0';

  if (dword_800ABB4C->field_0[0] == 71)
  {
    difficulty = GM_DifficultyFlag;
  }
  else
  {
    difficulty = 0;
  }

  if (difficulty < 0)
  {
    difficulty = 0;
    aBislpm99999[13] |= 0x40;
  }

  aBislpm99999[15] = ((minutes / 10) + '0') + ((difficulty & 2) << 5);
  aBislpm99999[16] = ((minutes % 10) + '0') + ((difficulty & 1) << 6);
  aBislpm99999[17] = flags2 + '@';
  aBislpm99999[18] = dword_800ABB4C->field_2 + '@';

  if (dword_800ABB4C->field_0[0] == 71 && dword_800ABB4C->field_2 == 1)
  {
    aBislpm99999[13] &= 0x40;
    aBislpm99999[13] |= 0x3A;
    aBislpm99999[14] = GM_LastResultFlag + '@';
  }

  for (i = 0; i < 16; i++)
  {
    flags1 = 0;
    aBislpm99999[19] = 'A' + i;
    for (file = 0; file < pMemcard->field_2_file_count; file++)
    {
      if (!strcmp(pMemcard->field_4_blocks[file].field_0_name, aBislpm99999))
      {
        flags1 = 1;
      }
    }

    if (!flags1)
    {
      break;
    }
  }

  dword_800ABB4C->field_10(buffer_copy + 256);

  ret = 0;
  for (retries = 4; retries > 0; retries--)
  {
    memcard_write_8002554C(pMemcard->field_0_card_idx, aBislpm99999, 0, buffer, size);
    while ((flags2 = memcard_get_status_800257B0()) > 0)
    {
      mts_wait_vbl_800895F4(2);
    }

    if (memcard_get_status_800257B0() == 0)
    {
      ret = 1;
      break;
    }
  }

  GV_FreeMemory_80015FD0(0, buffer);
  GM_PadResetDisable_800AB3F4 = 0;
  return ret;
}

int init_file_mode_helper_helper_helper2_80049CE8(mem_card *pMemcard, int idx)
{
    int   retval;
    int   statusFlag;
    short statusFlagTmp;
    int   i;
    void *buf;

    GM_PadResetDisable_800AB3F4 = 1;
    buf = GV_AllocMemory_80015EB8(0, 0x2000);
    if (buf == NULL)
    {
        printf("NO MEMORY FOR FILE BODY\n");
    }

    retval = 0;
    for (i = 4; i > 0; i--)
    {
        memcard_read_8002569C(pMemcard->field_0_card_idx, pMemcard->field_4_blocks[idx].field_0_name, 0, buf, 0x2000);

        while (memcard_get_status_800257B0() > 0)
        {
            mts_wait_vbl_800895F4(2);
        }

        if (memcard_get_status_800257B0() == 0)
        {
            statusFlagTmp = GM_GameStatusFlag & 0xF7FF;
            statusFlag = statusFlagTmp;
            if (GCL_SetLoadFile_80020EAC(buf + 0x100) != 0)
            {
                retval = 1;
                if (statusFlag & 0x10)
                {
                    GM_GameStatusFlag = (GM_GameStatusFlag & 0x1EFF) | (statusFlag & ~0x1EFF);
                }
                if (statusFlag & 8)
                {
                    GM_GameStatusFlag = (GM_GameStatusFlag & 0xEFF8) | (statusFlag & 0x1007);
                }
                GM_GameStatusFlag &= 0xFFE7;
                GCL_SaveLinkVar_80020B90(&GM_GameStatusFlag);
                if (GM_GameStatusFlag & 0x8000)
                {
                    GM_Sound_80032C48(-0xFFFFFB, 0);
                }
                else
                {
                    GM_Sound_80032C48(-0xFFFFFA, 0);
                }
            }
            break;
        }
    }

    GV_FreeMemory_80015FD0(0, buf);
    GM_PadResetDisable_800AB3F4 = 0;
    return retval;
}

int init_file_mode_helper_helper_helper3_80049E94(int param_1)
{
    dword_800ABB58 = param_1;
    printf(aRequestX, param_1);  // = "REQUEST %X\n"
    mts_slp_tsk_8008A400();
    printf(aResultX, dword_800ABB5C); // = "RESULT %X\n"
    return dword_800ABB5C;
}

void init_file_mode_helper_helper_80049EDC(void)
{
    int temp_a0;
    int temp_a0_2;
    int temp_s0;
    int err;
    int temp_v0;
    int temp_v0_2;
    int fidx;
    int temp_v1;
    int temp_v1_2;
    int var_a0;
    int port;
    int var_s2;
    mem_card *pMemcard;
    int negone;
    int one;

    mts_set_vsync_task_800892B8();

loop_1:
    dword_800ABB54 = 1;

loop_3:
    init_file_mode_helper_helper_helper3_80049E94(0x100000A);

    temp_a0 = dword_800AB6FC;
    var_s2 = 0;

    if (temp_a0 == -1)
    {
        int mask;
        dword_800AB700 = 0;

        for (port = 0; port < 2; port++)
        {
            mask = 0x1000000;
            temp_v0 = memcard_check_80024A54(port);
            temp_v1 = temp_v0 & 0xFF;
            mcd_last_check_800ABB60[port] = temp_v1;

            if ((temp_v0 & mask) && dword_800AB6F0 == port)
            {
                dword_800AB6F0 = -1;
            }

            if (temp_v1 != 3)
            {
                var_s2 += 1;
                dword_800AB700 |= 1 << port;
            }
        }

        if (var_s2 == 0)
        {
            init_file_mode_helper_helper_helper3_80049E94(0x41000008);

            for (port = 0; port < 2; port++)
            {
                if ((memcard_check_80024A54(port) & 0xFF) != 3)
                {
                    goto loop_1;
                }
            }

            dword_800ABB54 = 2;
            dword_800AB6F0 = -1;
            goto block_73;
        }

        dword_800ABB5C = -2;
        dword_800ABB58 = 0x20000001;
        dword_800AB700 &= ~0x80;
        one = 1;
        negone = -1;

loop_18:
        for (port = 0; port < 2; port++)
        {
            temp_a0_2 = memcard_check_80024A54(port) & 0xFF;
            if (temp_a0_2 != mcd_last_check_800ABB60[port])
            {
                mcd_last_check_800ABB60[port] = temp_a0_2;
                if (temp_a0_2 == 3)
                {
                    dword_800AB700 &= ~(one << port);
                    if (dword_800AB6F0 == port)
                    {
                        dword_800AB6F0 = negone;
                    }
                }
                else if (temp_a0_2 != 0x80000000)
                {
                    dword_800AB700 |= (one << port);
                }
                dword_800ABB54 = one;
                dword_800AB700 |= 0x80;
            }
        }

        temp_v1_2 = dword_800ABB5C;

        if (temp_v1_2 >= 0)
        {
            if ((dword_800AB700 == 0) || !(dword_800AB700 & (one << temp_v1_2)))
            {
                dword_800AB6FC = negone;
                dword_800AB6F0 = negone;
                goto loop_1;
            }
            dword_800AB6FC = temp_v1_2;
            if (dword_800AB6F0 != temp_v1_2)
            {
                dword_800AB6EC = negone;
            }
            dword_800AB6F0 = temp_v1_2;
            goto block_34;
        }

        var_a0 = 0x80000000;

        if (temp_v1_2 != negone)
        {
block_34:
            port = 0;
            if (dword_800ABB5C == -2)
            {
                goto loop_18;
            }

            goto block_40;
        }
    }
    else
    {
        temp_v0_2 = memcard_check_80024A54(temp_a0);
        if (temp_v0_2 & 0x1000000)
        {
            dword_800AB6EC = -1;
        }
        temp_v0_2 &= 0xFF;

        mcd_last_check_800ABB60[dword_800AB6FC] = temp_v0_2;
        if (mcd_last_check_800ABB60[dword_800AB6FC] == 3)
        {
            dword_800AB6FC = -1;
            dword_800AB6EC = -1;
            goto loop_3;
        }

block_40:
        temp_s0 = mcd_last_check_800ABB60[dword_800AB6FC];
        if (temp_s0 != 0x80000000)
        {
            if (temp_s0 == 1)
            {
                init_file_mode_helper_helper_helper3_80049E94(0x43000005);
                if (dword_800ABB48 == 0)
                {
                    if (init_file_mode_helper_helper_helper3_80049E94(0x10000001) == 0)
                    {
                        err = memcard_check_80024A54(dword_800AB6FC) & 0xFF;
                        if (err != temp_s0)
                        {
                            init_file_mode_helper_helper_helper3_80049E94(0x45000003);
                            goto loop_3;
                        }

                        init_file_mode_helper_helper_helper3_80049E94(0x0100000B);

                        if (!memcard_format_800257C0(dword_800AB6FC))
                        {
                            dword_800AB6FC = -1;
                            init_file_mode_helper_helper_helper3_80049E94(0x45000007);
                            goto block_72;
                        }

                        mcd_last_check_800ABB60[dword_800AB6FC] = memcard_check_80024A54(dword_800AB6FC) & 0xFF;

                        if (mcd_last_check_800ABB60[dword_800AB6FC] == 0)
                        {
                            dword_800AB6F4 = err;
                            goto block_51;
                        }

                        goto block_59;
                    }

                    dword_800ABB54 = 4;
                    asm(""); // temporary scaffolding
                    goto block_53;
                }

                dword_800ABB54 = 4;
                goto block_53;
            }
block_51:
            pMemcard = memcard_get_files_80025350(dword_800AB6FC);
            mcd_last_file_800ABB68[dword_800AB6FC] = pMemcard;

            if (pMemcard == NULL)
            {
                init_file_mode_helper_helper_helper3_80049E94(0x45000003);
                goto loop_3;
            }

loop_52:
            fidx = init_file_mode_helper_helper_helper3_80049E94(0x20000000);

            if (fidx < 0)
            {
block_53:
                dword_800AB6FC = -1;
                goto loop_3;
            }

            if (memcard_check_80024A54(dword_800AB6FC) != 0)
            {
                init_file_mode_helper_helper_helper3_80049E94(0x45000003);
                goto loop_3;
            }

            if (dword_800ABB48 == 0)
            {
                if (fidx < 16)
                {
                    if (init_file_mode_helper_helper_helper3_80049E94(0x10000000) != 0)
                    {
                        goto loop_52;
                    }

                    if (memcard_check_80024A54(dword_800AB6FC) != 0)
                    {
                        init_file_mode_helper_helper_helper3_80049E94(0x45000003);
                        goto loop_3;
                    }

                    if (memcard_delete_800253C4(dword_800AB6FC, pMemcard->field_4_blocks[fidx].field_0_name) == 0)
                    {
                        goto block_59;
                    }

                    pMemcard = memcard_get_files_80025350(dword_800AB6FC);
                    mcd_last_file_800ABB68[dword_800AB6FC] = pMemcard;
                }

                if (pMemcard->field_3_free_blocks == 0)
                {
                    init_file_mode_helper_helper_helper3_80049E94(0x43200004);
                    goto block_72;
                }

                init_file_mode_helper_helper_helper3_80049E94(0x01000009);

                if (init_file_mode_helper_helper_helper_8004983C(pMemcard) != 0)
                {
                    goto block_75;
                }
            }
            else
            {
                init_file_mode_helper_helper_helper3_80049E94(0x01000009);

                if (init_file_mode_helper_helper_helper2_80049CE8(pMemcard, fidx) != 0)
                {
                    goto block_69;
                }
            }

            var_a0 = 0xC1000001;
        }

block_59:
        init_file_mode_helper_helper_helper3_80049E94(0x45000003);
        goto block_72;

block_69:
        dword_800ABB48 = 2;
block_75:
        dword_800ABB54 = 0;
        var_a0 = 0xC1000001;
        goto block_74;

block_72:
        dword_800ABB54 = 5;
block_73:
        var_a0 = 0xC5000002;
    }

block_74:
    init_file_mode_helper_helper_helper3_80049E94(var_a0);
}
