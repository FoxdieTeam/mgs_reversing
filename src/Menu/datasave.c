#include "linker.h"
#include "menuman.h"
#include "unknown.h"
#include "Game/game.h"
#include "Menu/radio.h"
#include "Game/linkvarbuf.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "memcard/memcard.h"

//------------------------------------------------------------------------------
// gp
extern int dword_800ABB48;
int        dword_800ABB48;

extern void *dword_800ABB50;
void        *dword_800ABB50;

extern int dword_800ABB58;
int        dword_800ABB58;

extern int dword_800ABB5C;
int        dword_800ABB5C;

extern int dword_800ABB54;
int        dword_800ABB54;

extern SELECT_INFO *dword_800ABB70;
SELECT_INFO        *dword_800ABB70;

extern SELECT_INFO *dword_800ABB74;
SELECT_INFO        *dword_800ABB74;

extern SELECT_INFO *dword_800ABB78;
SELECT_INFO        *dword_800ABB78;

extern SELECT_INFO *dword_800ABB88;
SELECT_INFO        *dword_800ABB88;

extern int dword_800ABB84;
int        dword_800ABB84;

extern int dword_800ABB80;
int        dword_800ABB80;

extern int dword_800ABB8C;
int        dword_800ABB8C;

extern int dword_800ABB90;
int        dword_800ABB90;

extern DATA_INFO *dword_800ABB4C;
DATA_INFO        *dword_800ABB4C;

//------------------------------------------------------------------------------

extern Menu_Triangle triangle_8009EBD0;
extern Menu_Triangle triangle_8009EBE0;

extern DATA_INFO *dword_800ABB4C;
DATA_INFO        *dword_800ABB4C;

extern int mcd_last_check_800ABB60[2];
int        mcd_last_check_800ABB60[2];

extern mem_card *mcd_last_file_800ABB68[2];
mem_card        *mcd_last_file_800ABB68[2];

extern DATA_INFO *dword_800ABB4C;
DATA_INFO        *dword_800ABB4C;

extern SELECT_INFO *dword_800ABB74;
SELECT_INFO        *dword_800ABB74;

extern RadioFileModeStru_800ABB7C *stru_800ABB7C;
RadioFileModeStru_800ABB7C        *stru_800ABB7C;

extern int GM_PadResetDisable_800AB3F4;

extern char *MGS_MemoryCardName_800AB2EC;

extern int GV_Time_800AB330;
extern int GV_Clock_800AB920;

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

extern Actor_MenuMan gMenuMan_800BD360;

extern mem_card  *mcd_last_file_800ABB68[];
extern const int  dword_800120B4[];
extern const int  dword_800120CC[];
extern const int  dword_800120E4[];

char aBislpm99999[] = "BISLPM-99999        ";

int dword_800AB6EC = 0;
int dword_800AB6F0 = -1;
int dword_800AB6F4 = 0;

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

const char *dword_8009EB4C[] = {
    "\x00", // Different from the other empty strings used below for some reason
    // セーブが完了しました。
    "\x82\x1b\xd0\x06\x82\x36\x81\x0c\x91\x07\x91\x08\x81\x17\x81\x3e\x81\x17\x81\x1f\xd0\x03",
    // セーブできませんでした。
    "\x82\x1b\xd0\x06\x82\x36\x81\x27\x81\x0d\x81\x3e\x81\x1b\x81\x53\x81\x27\x81\x17\x81\x1f\xd0\x03",
    // エラーが発生しました。
    "\x82\x08\x82\x49\xd0\x06\x81\x0c\x90\x7e\x90\xca\x81\x17\x81\x3e\x81\x17\x81\x1f\xd0\x03",
    // 空きブロックがたりません。
    "\x90\x92\x81\x0d\x82\x36\x82\x4d\xc2\x23\x82\x0f\x81\x0c\x81\x1f\x81\x4a\x81\x3e\x81\x1b\x81\x53\xd0\x03",
    // メモリーカードが初期化されていません。
    "\x82\x41\x82\x42\x82\x4a\xd0\x06\x82\x0b\xd0\x06\x82\x29\x81\x0c\x91\x10\x91\x11\x90\x64\x81\x15\x81\x4c\x81\x26\x81\x04\x81\x3e\x81\x1b\x81\x53\xd0\x03",
    // セーブしました。
    "\x82\x1b\xd0\x06\x82\x36\x81\x17\x81\x3e\x81\x17\x81\x1f\xd0\x03",
    // フォーマットに失敗しました。
    "\x82\x35\xc2\x09\xd0\x06\x82\x3e\xc2\x23\x82\x28\x81\x2b\x91\x09\x91\x0a\x81\x17\x81\x3e\x81\x17\x81\x1f\xd0\x03",
    // メモリーカードがさされていません。
    "\x82\x41\x82\x42\x82\x4a\xd0\x06\x82\x0b\xd0\x06\x82\x29\x81\x0c\x81\x15\x81\x15\x81\x4c\x81\x26\x81\x04\x81\x3e\x81\x1b\x81\x53\xd0\x03",
    // セーブ中です。
    "\x82\x1b\xd0\x06\x82\x36\x90\xcd\x81\x27\x81\x19\xd0\x03",
    // メモリーカードをチェックしています。
    "\x82\x41\x82\x42\x82\x4a\xd0\x06\x82\x0b\xd0\x06\x82\x29\x81\x52\x82\x21\xc2\x07\xc2\x23\x82\x0f\x81\x17\x81\x26\x81\x04\x81\x3e\x81\x19\xd0\x03",
    // フォーマットしています。
    "\x82\x35\xc2\x09\xd0\x06\x82\x3e\xc2\x23\x82\x28\x81\x17\x81\x26\x81\x04\x81\x3e\x81\x19\xd0\x03",
};

const char *dword_8009EB7C[] = {
    "\x00", // Different from the other empty strings used below for some reason
    // ロードが完了しました。
    "\x82\x4d\xd0\x06\x82\x29\x81\x0c\x91\x07\x91\x08\x81\x17\x81\x3e\x81\x17\x81\x1f\xd0\x03",
    // ロードできませんでした。
    "\x82\x4d\xd0\x06\x82\x29\x81\x27\x81\x0d\x81\x3e\x81\x1b\x81\x53\x81\x27\x81\x17\x81\x1f\xd0\x03",
    // エラーが発生しました。
    "\x82\x08\x82\x49\xd0\x06\x81\x0c\x90\x7e\x90\xca\x81\x17\x81\x3e\x81\x17\x81\x1f\xd0\x03",
    // セーブファイルがありません。
    "\x82\x1b\xd0\x06\x82\x36\x82\x35\xc2\x01\x82\x04\x82\x4b\x81\x0c\x81\x02\x81\x4a\x81\x3e\x81\x1b\x81\x53\xd0\x03",
    // メモリーカードが初期化されていません。
    "\x82\x41\x82\x42\x82\x4a\xd0\x06\x82\x0b\xd0\x06\x82\x29\x81\x0c\x91\x10\x91\x11\x90\x64\x81\x15\x81\x4c\x81\x26\x81\x04\x81\x3e\x81\x1b\x81\x53\xd0\x03",
    // ロードしました。
    "\x82\x4d\xd0\x06\x82\x29\x81\x17\x81\x3e\x81\x17\x81\x1f\xd0\x03",
    // フォーマットに失敗しました。
    "\x82\x35\xc2\x09\xd0\x06\x82\x3e\xc2\x23\x82\x28\x81\x2b\x91\x09\x91\x0a\x81\x17\x81\x3e\x81\x17\x81\x1f\xd0\x03",
    // メモリーカードがさされていません。
    "\x82\x41\x82\x42\x82\x4a\xd0\x06\x82\x0b\xd0\x06\x82\x29\x81\x0c\x81\x15\x81\x15\x81\x4c\x81\x26\x81\x04\x81\x3e\x81\x1b\x81\x53\xd0\x03",
    // ロード中です。
    "\x82\x4d\xd0\x06\x82\x29\x90\xcd\x81\x27\x81\x19\xd0\x03",
    // メモリーカードをチェックしています。
    "\x82\x41\x82\x42\x82\x4a\xd0\x06\x82\x0b\xd0\x06\x82\x29\x81\x52\x82\x21\xc2\x07\xc2\x23\x82\x0f\x81\x17\x81\x26\x81\x04\x81\x3e\x81\x19\xd0\x03",
    // フォーマットしています。
    "\x82\x35\xc2\x09\xd0\x06\x82\x3e\xc2\x23\x82\x28\x81\x17\x81\x26\x81\x04\x81\x3e\x81\x19\xd0\x03",
};

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

const char *dword_8009EBAC[] = {
    // 上書きしてよろしいですか？
    "\x91\x0b\x90\x27\x81\x0d\x81\x17\x81\x26\x81\x48\x81\x4d\x81\x17\x81\x04\x81\x27\x81\x19\x81\x0b\xc0\x3f",
    // フォーマットしますか？
    "\x82\x35\xc2\x09\xd0\x06\x82\x3e\xc2\x23\x82\x28\x81\x17\x81\x3e\x81\x19\x81\x0b\xc0\x3f",
};

const char *dword_8009EBB4[] = {"OVERWRITE OK?", "FORMAT OK?"};

int init_file_mode_helper_helper_helper3_80049E94(int param_1)
{
    dword_800ABB58 = param_1;
    printf("REQUEST %X\n", param_1);  // = "REQUEST %X\n"
    mts_slp_tsk_8008A400();
    printf("RESULT %X\n", dword_800ABB5C); // = "RESULT %X\n"
    return dword_800ABB5C;
}

int dword_800AB6FC = -1;
int dword_800AB700 = 0;

void init_file_mode_helper_helper_80049EDC()
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
    int port;
    int var_s2;
    mem_card *pMemcard;
    int negone;
    int one;

    mts_set_vsync_task_800892B8();
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
                    dword_800ABB54 = 1;
                    goto loop_3;
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
                dword_800ABB54 = 1;
                goto loop_3;
            }
            dword_800AB6FC = temp_v1_2;
            if (dword_800AB6F0 != temp_v1_2)
            {
                dword_800AB6EC = negone;
            }
            dword_800AB6F0 = temp_v1_2;
            goto block_34;
        }

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
        init_file_mode_helper_helper_helper3_80049E94(0x80000000);
        return;
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
                        else
                        {
                            init_file_mode_helper_helper_helper3_80049E94(0x45000003);
                            goto block_72;
                        }
                    }

                    dword_800ABB54 = 4;
                    dword_800AB6FC = -1;
                    goto loop_3;
                }
                else
                {
                    dword_800ABB54 = 4;
                    dword_800AB6FC = -1;
                    goto loop_3;
                }
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
                        init_file_mode_helper_helper_helper3_80049E94(0x45000003);
                        goto block_72;
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
        }

        init_file_mode_helper_helper_helper3_80049E94(0x45000003);
        goto block_72;

block_69:
        dword_800ABB48 = 2;
block_75:
        dword_800ABB54 = 0;
        init_file_mode_helper_helper_helper3_80049E94(0xC1000001);
        return;

block_72:
        dword_800ABB54 = 5;

block_73:
        init_file_mode_helper_helper_helper3_80049E94(0xC5000002);
    }
}

void init_file_mode_helper_8004A424(int param_1)
{
    int size = 0x800;

    dword_800ABB50 = GV_AllocMemory_80015EB8(0, size);

    if (!dword_800ABB50)
    {
        printf("NO MEMORY FOR STACK\n"); // "NO MEMORY FOR STACK\n"
    }

    dword_800ABB48 = param_1;
    mts_set_stack_check_8008B648(7, (unsigned int *)(dword_800ABB50 + size), size);
    mts_sta_tsk_8008B47C(7, init_file_mode_helper_helper_80049EDC, (void *)(dword_800ABB50 + size));
}

const char *dword_8009EBBC[] = {
    NULL,
    NULL,
    "COMPLETE",
    NULL,
    "ERROR"
};

Menu_Triangle triangle_8009EBD0 = {155, 79, 160, 74, 165, 79, 0x80808080};
Menu_Triangle triangle_8009EBE0 = {156, 184, 160, 188, 164, 184, 0x80808080};

void move_coord_8004A494(int *arr, int len)
{
    int i;

    for (i = 0; i < len; i++, arr += 2) {
        arr[0] += arr[1];
    }
}

void menu_radio_do_file_mode_helper2_helper_8004A4C4(MenuPrim *pGlue, RadioFileModeStruElem *pElem)
{
    RadioFileModeUnk1 *pUnk;
    TextConfig         textConfig;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord_8004A494(&pUnk->field_8, 2);
        pUnk->field_18 = 0x3d482e;
    }
    textConfig.xpos = pUnk->field_8 >> 16;
    textConfig.ypos = pUnk->field_10 >> 16; // pUnk->field_10 / 65536 wouldn't match
    textConfig.flags = 0x12;
    textConfig.colour = pUnk->field_18 | 0x66000000;

    menu_number_draw_string2_80043220(pGlue, &textConfig, (char *)pUnk->field_4); // TODO: Fix cast
}

void menu_radio_do_file_mode_helper4_helper_8004A54C(MenuPrim *pGlue, RadioFileModeStruElem *pElem)
{
    LINE_F2           *pPrim;
    RadioFileModeUnk1 *pUnk;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord_8004A494(&pUnk->field_4, 4);
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
        addPrim(pGlue->mPrimBuf.mOt, pPrim);
    }
}

void sub_8004A648(MenuPrim *pGlue, RadioFileModeStruElem *pElem)
{
    RadioFileModeUnk1 *pUnk;
    int                x, y, w, h;
    TILE              *pTile;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord_8004A494(&pUnk->field_4, 4);
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
    addPrim(pGlue->mPrimBuf.mOt, pTile);

    radio_draw_face_frame_800481CC(pGlue, x, y, w, h);
    radio_draw_face_frame_800481CC(pGlue, x, y, w, h);
}

void menu_radio_do_file_mode_helper3_helper_8004A790(MenuPrim *pGlue, RadioFileModeStruElem *pElem)
{
    RadioFileModeUnk1 *pUnk;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord_8004A494(&pUnk->field_4, 2);
    }

    *(short *)pUnk->field_14 = pUnk->field_4 >> 16; // TODO: Fix type of field_14
    *(short *)(pUnk->field_14 + 2) = pUnk->field_C >> 16; // pUnk->field_C / 65536 wouldn't match
    menu_radio_do_file_mode_helper16_8004C164(pGlue, (SELECT_INFO *)pUnk->field_14);
}

//file may be split here

void init_file_mode_helper2_8004A800()
{
    int i;

    stru_800ABB7C = (RadioFileModeStru_800ABB7C *)GV_AllocMemory_80015EB8(0, sizeof(RadioFileModeStru_800ABB7C));
    if (stru_800ABB7C == NULL)
    {
        printf("NO MEMORY FOR OBJ\n");
    }

    for (i = 0; i < 12; i++)
    {
        stru_800ABB7C->field_0_array[i].field_0 = 0;
    }
}

void menu_radio_do_file_mode_helper_8004A858()
{
    GV_FreeMemory_80015FD0(0, stru_800ABB7C);
}

void menu_radio_do_file_mode_helper2_8004A87C(int idx, int param_2, int param_3, int divisor, int idx2)
{
    RadioFileModeStruElem *pElem;
    RadioFileModeUnk2     *pUnk;

    pUnk = &stru_800ABB7C->field_c0_array[idx];
    pElem = &stru_800ABB7C->field_0_array[idx];

    // Callers call this function with: idx2 = -1 ... 4
    pUnk->field_4 = dword_8009EBBC[idx2];

    pElem->field_8_pFn = menu_radio_do_file_mode_helper2_helper_8004A4C4;
    pElem->field_C_unk1 = (RadioFileModeUnk1 *)pUnk; // TODO: Fix cast

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

void menu_radio_do_file_mode_helper3_8004A994(int idx, int param_2, int param_3, int divisor, SELECT_INFO *field_14)
{
    RadioFileModeUnk1     *pUnk;
    RadioFileModeStruElem *pElem;

    pElem = &stru_800ABB7C->field_0_array[idx];
    pUnk = &stru_800ABB7C->field_220_unk1;

    pElem->field_8_pFn = menu_radio_do_file_mode_helper3_helper_8004A790;
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

void menu_radio_do_file_mode_helper4_8004AA68(int idx, int param_2, int param_3, int param_4, int param_5, int divisor)
{
    RadioFileModeUnk1     *pUnk;
    RadioFileModeStruElem *pElem;

    pElem = &stru_800ABB7C->field_0_array[idx];

    // callers to this function use idx in range 5..8
    pUnk = &stru_800ABB7C->field_130_array[idx - 5]; // TODO: really -5?

    pElem->field_8_pFn = menu_radio_do_file_mode_helper4_helper_8004A54C;
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

int *menu_radio_do_file_mode_helper5_8004ABDC(int idx)
{
    int *result;

    result = &stru_800ABB7C->field_0_array[idx].field_0;
    *result = 0;
    return result;
}

void sub_8004ABF0(int param_1, int param_2, int param_3, int param_4, int divisor)

{
    RadioFileModeStruElem *pElem = &stru_800ABB7C->field_0_array[11];

    // TODO: WTF??? Why is it reinterpreting a middle of RadioFileModeUnk1 as another RadioFileModeUnk1,
    // going past the memory of original RadioFileModeUnk1?
    RadioFileModeUnk1 *pUnk = (RadioFileModeUnk1 *)&(stru_800ABB7C->field_220_unk1).field_18;

    pElem->field_8_pFn = sub_8004A648;
    pElem->field_C_unk1 = pUnk;

    if (divisor <= 0)
    {
        pUnk->field_4 = param_1 * 65536;
        pUnk->field_C = param_2 * 65536;
        pUnk->field_14 = param_3 * 65536;
        pUnk->field_1C = param_4 * 65536;
        pElem->field_0 = 2;
    }
    else
    {
        pUnk->field_8 = (param_1 * 65536 - pUnk->field_4) / divisor;
        pUnk->field_10 = (param_2 * 65536 - pUnk->field_C) / divisor;
        pUnk->field_18 = (param_3 * 65536 - pUnk->field_14) / divisor;
        pUnk->field_20 = (param_4 * 65536 - pUnk->field_1C) / divisor;
        pElem->field_0 = 1;
    }

    pElem->field_4 = divisor;
}

void menu_radio_do_file_mode_helper6_8004AD40(MenuPrim *pGlue)
{
    int                    i;
    RadioFileModeStruElem *pElem;

    pElem = stru_800ABB7C->field_0_array;
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

#define setRGB0_Fast(prim, rgbExtra) *(unsigned int *)&prim->r0 = rgbExtra

void set_sprt_default_8004AE14(SPRT *pSprt)
{
    setRGB0_Fast(pSprt, 0x80808080);
    setSprt(pSprt);
    pSprt->clut = 32700;
}

void menu_radio_do_file_mode_helper7_8004AE3C(Actor_MenuMan *param_1, const char *str)
{
    int height;
    KCB  *kcb;

    kcb = param_1->field_214_font;

    height = kcb->height_info;
    kcb->height_info = 14;
    font_clear_800468FC(kcb);
    kcb->height_info = height;

    font_draw_string_80045D0C(kcb, 0, 0, str, 0);
    font_update_8004695C(kcb);
}

void sub_8004AEA8(SELECT_INFO *info)
{
    int   top;
    int   i, y;
    int   count;
    int   x, val2;
    KCB  *kcb;
    char  msg[32];
    char *base;

    kcb = info->field_1C_kcb;
    x = 0;
    font_clear_800468FC(kcb);

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

        base = info->menu[i + top].mes;
        if (base[0] != '\0')
        {
            dword_800ABB4C->make_menu(msg, base);
            font_draw_string_80045D0C(kcb, x, y, msg, 2);
        }
    }

    font_draw_string_80045D0C(kcb, 0, 0, info->message, 0);
    font_update_8004695C(kcb);
}

void menu_radio_do_file_mode_helper8_8004AFE4(Actor_MenuMan *work, char *pOt, SELECT_INFO *info)
{
    KCB  *kcb;
    SPRT *sprt;

    kcb = work->field_214_font;

    NEW_PRIM(sprt, work);

    set_sprt_default_8004AE14(sprt);
    setXY0(sprt, 160 - kcb->char_arr[7] / 2, 200);
    setUV0(sprt, 0, 4);
    setWH(sprt, 252, 14);
    addPrim(pOt, sprt);
}

void menu_radio_do_file_mode_save_memcard_8004B0A0(Actor_MenuMan *work, char *pOt, SELECT_INFO *info)
{
    TextConfig config;

    char saveid[16];
    char discnum[16];
    char newfile[32];
    char freeblocks[32];

    LINE_F2  *pLine;
    SPRT     *pSprt;
    TILE     *pTile;
    POLY_FT4 *pPoly;
    DR_TPAGE *pTpage;

    int                  sp88;
    int                  blocks_req;
    int                  difficulty;
    int                  sp8C;
    int                  sp90;
    int                  sp94;
    int                  sp98;
    int                  sp9C;
    int                  spA0;
    SELECT_MENU *temp_s1;
    MenuPrim            *pOtBuf;

    int var_a2;
    int var_s5;
    int i;
    int var_s0;
    int var_t0;

    int mult;
    int mult2;

    unsigned int s8;
    unsigned int s6;

    int new_var;
    int new_var2, new_var3;

    do
    {
    } while (0);

    pOtBuf = work->field_20_otBuf;
    s8 = 0;

    if (info->max_num == 0)
    {
        return;
    }

    sp90 = info->top;
    sp8C = info->max_num - info->top;

    s6 = 200;
    if (sp8C > 6)
    {
        sp8C = 6;
    }
    sp94 = 0;
    sp98 = 274;

    var_s5 = 80;

    mult = 52;
    mult2 = 18;

    new_var2 = 18;
    if (info->open_count > 0)
    {
        if (--info->open_count >= 5)
        {
            return;
        }

        sp9C = (4 - info->open_count) * mult;
    }
    else
    {
        sp9C = s6 + 10;
    }

    if (info->field_18 > 0)
    {
        spA0 = --info->field_18 * (mult2 / 4);
    }
    else if (info->field_18 == 0)
    {
        spA0 = 0;
    }
    else
    {
        spA0 = 18;
    }

    new_var3 = 210;
    for (sp88 = 0; sp88 < sp8C; sp88++)
    {
        new_var = 'A' - 1;

        _NEW_PRIM(pTile, pOtBuf);
        LSTORE(0, &pTile->r0);

        setXY0(pTile, s8, s6);
        setWH(pTile, new_var3, new_var2);

        setTile(pTile);
        addPrim(pOtBuf->mPrimBuf.mOt, pTile);

        var_a2 = 293;
        if (GV_Clock_800AB920 == 0)
        {
            var_a2 = 288;
        }

        _NEW_PRIM(pPoly, pOtBuf);
        LSTORE(0x80808080, &pPoly->r0);

        if ((sp90 + sp88) == info->field_4)
        {
            var_s0 = 18;
        }
        else
        {
            var_s0 = spA0;
        }

        pPoly->x0 = 160 - (sp9C / 2);
        pPoly->y0 = var_s5;

        pPoly->x1 = 160 - (sp9C / 2) + sp9C;
        pPoly->y1 = var_s5;

        pPoly->x2 = 160 - (sp9C / 2);
        pPoly->y2 = var_s5 + var_s0;

        pPoly->x3 = 160 - (sp9C / 2) + sp9C;
        pPoly->y3 = var_s5 + var_s0;

        setUVWH(pPoly, s8, s6, 210, 18);

        pPoly->tpage = var_a2;

        setPolyFT4(pPoly);
        setSemiTrans(pPoly, 1);

        addPrim(pOtBuf->mPrimBuf.mOt, pPoly);

        if (((sp90 + sp88) == info->field_4) && (info->field_14 != 0))
        {
            do
            {
                sub_8004ABF0(160, var_s5 + 9, info->field_12, 16, 2);
            } while (0);
        }

        config.colour = 0x66748956;
        config.flags = 0;
        var_s5 += var_s0;

        if ((info->menu[sp90 + sp88].field_20 >= 0) && (info->menu[sp90 + sp88].field_20 < 16))
        {
            temp_s1 = &info->menu[sp90 + sp88];

            if (temp_s1->mes[0] == 'G')
            {
                config.xpos = s8 + 178;
                config.ypos = s6 + 3;
                sprintf(discnum, "DISC %d", ((temp_s1->mes[5] - new_var) >> 3) + 1);
                menu_number_draw_string_80042BF4(pOtBuf, &config, discnum);
            }
            else
            {
                config.xpos = s8 + 178;
                config.ypos = s6 + 3;
                menu_number_draw_string_80042BF4(pOtBuf, &config, "TIME");
            }

            if (temp_s1->mes[0] == 'G')
            {
                static const char *difficulty_str_8009EBF0[] = {"EZ", "NM", "HD", "EX"};
                difficulty = ((temp_s1->mes[3] & 0x40) >> 5) | ((temp_s1->mes[4] & 0x40) >> 6);

                config.xpos = s8 + 164;
                config.ypos = s6 + 10;

                if (temp_s1->mes[1] & 0x40)
                {
                    menu_number_draw_string_80042BF4(pOtBuf, &config, "VE");
                }
                else
                {
                    menu_number_draw_string_80042BF4(pOtBuf, &config, difficulty_str_8009EBF0[difficulty]);
                }
            }

            config.xpos = s8 + 180;
            config.ypos = s6 + 10;

            saveid[0] = temp_s1->mes[1];
            saveid[1] = temp_s1->mes[2];
            saveid[2] = ':';
            saveid[3] = temp_s1->mes[3] & 0x3F;
            saveid[4] = temp_s1->mes[4] & 0x3F;

            saveid[0] = saveid[0] & 0x3F;

            if (saveid[0] == ':')
            {
                memcpy(saveid, "CLEAR", 6);
            }

            saveid[5] = 0;
            menu_number_draw_string_80042BF4(pOtBuf, &config, saveid);
        }
        else
        {
            const char   *msg;
            char         *dst = newfile;
            const char   *ptr;
            unsigned char field3;
            long          new_var4;
            config.ypos = s6 + 8;
            config.flags = 0x2;
            config.xpos = s8 + (sp9C / 2);
            msg = "NEW FILE [ NEED %d BLOCK%s ]";
            field3 = dword_800ABB4C->field_3;
            new_var4 = field3;
            if (new_var4 >= 2)
                ptr = "S";
            else
                ptr = "";

            sprintf(dst, msg, field3, ptr);

            menu_number_draw_string2_80043220(pOtBuf, &config, newfile);
        }

        if (sp88 == 4)
        {
            sp94 = 128;
            sp98 = 274;
        }

        _NEW_PRIM(pSprt, pOtBuf);
        set_sprt_default_8004AE14(pSprt);

        pSprt->u0 = sp94;
        pSprt->v0 = sp98;

        pSprt->w = 128;
        pSprt->h = 14;
        pSprt->x0 = s8;
        pSprt->y0 = s6 + 2;

        addPrim(pOt, pSprt);

        _NEW_PRIM(pTpage, pOtBuf);
        setDrawTPage(pTpage, 0, 1, getTPage(0, 1, 960, 256));
        addPrim(pOtBuf->mPrimBuf.mOt, pTpage);

        sp98 += 14;
    }

    var_t0 = -(sp9C + 10) / 2;

    for (i = 0; i < 2; i++)
    {
        _NEW_PRIM(pLine, pOtBuf);

        pLine->x0 = pLine->x1 = var_t0 + 160;
        pLine->y0 = 78;
        pLine->y1 = var_s5 + 4;

        LSTORE(0x748956, &pLine->r0);

        setLineF2(pLine);
        setSemiTrans(pLine, 1);
        addPrim(pOtBuf->mPrimBuf.mOt, pLine);

        var_t0 += 10 + sp9C;
    }

    if (info->field_18 >= 0)
    {
        return;
    }

    blocks_req = mcd_last_file_800ABB68[dword_800AB6FC]->field_3_free_blocks;

    if (dword_800ABB74->max_num == 1)
    {
        config.xpos = 160;
    }
    else if (dword_800AB6FC == 0)
    {
        config.xpos = 96;
    }
    else
    {
        config.xpos = 224;
    }

    config.ypos = 68;
    config.flags = 0x2;
    config.colour = 0x66748956;

    sprintf(freeblocks, "FREE: %d BLOCK%s", blocks_req, (blocks_req > 1) ? "S" : "");
    menu_number_draw_string2_80043220(pOtBuf, &config, freeblocks);

    if ((GV_Time_800AB330 % 32) > 10)
    {
        if (sp90 > 0)
        {
            menu_draw_triangle_800435EC(work->field_20_otBuf, &triangle_8009EBD0);
        }

        if ((sp90 + 6) < info->max_num)
        {
            menu_draw_triangle_800435EC(work->field_20_otBuf, &triangle_8009EBE0);
        }
    }
}

void menu_radio_do_file_mode_helper12_helper_8004B8FC(char *param_1, char *param_2)
{
    strcpy(param_1, param_2 + 0xc);
}

void menu_radio_do_file_mode_helper10_8004B91C(SELECT_INFO *info)
{
    printf("close info\n");
    if (info)
    {
        GV_FreeMemory_80015FD0(0, info);
    }
}

// a1 is &dword_800ABB74
void menu_radio_do_file_mode_helper11_8004B958(SELECT_INFO **a1, int num)
{
    if (!*a1)
    {
        *a1 = GV_AllocMemory_80015EB8(0, (sizeof(SELECT_MENU) * num) + sizeof(SELECT_INFO));

        if (!*a1)
        {
            printf("NO MEMORY FOR INFO\n"); // "NO MEMORY FOR INFO\n"
        }

        printf("alloc info %X\n", (unsigned int)*a1); // "alloc info %X\n"
    }
}

void sub_8004B9C4(SELECT_INFO *info, int param_2)
{
    short field_6;
    short new_field_6;
    int   field_4;

    field_4 = info->field_4;
    new_field_6 = info->field_4 + param_2;
    info->field_4 = new_field_6;
    if (new_field_6 < 0)
    {
        info->field_4 = 0;
    }
    else if (new_field_6 >= info->max_num)
    {
        info->field_4 = info->max_num - 1;
    }
    else
    {
        field_6 = info->top;
        if (new_field_6 < field_6)
        {
            info->top = new_field_6;
        }
        else if (new_field_6 >= (field_6 + 6))
        {
            info->top = new_field_6 - 5;
        }
    }
    if (info->field_4 != field_4)
    {
        GM_SeSet2_80032968(0, 0x3F, 0x1F);
    }
    sub_8004AEA8(info);
}


int menu_radio_do_file_mode_helper12_8004BA80(Actor_MenuMan *work, mem_card *pMemcard, const char *param_3,
                                              SELECT_INFO *info)
{
    SELECT_MENU *pIter;
    mem_card_block      *pBlock;
    int                  i;

    pIter = info->menu;

    strcpy(aBislpm99999, MGS_MemoryCardName_800AB2EC);
    aBislpm99999[12] = dword_800ABB4C->field_0[0];

    for (i = 0; i < pMemcard->field_2_file_count; i++)
    {
        pBlock = &pMemcard->field_4_blocks[i];
        printf("FILE %s\n", pBlock->field_0_name);

        if (strncmp(pBlock->field_0_name, aBislpm99999, 13) == 0)
        {
            menu_radio_do_file_mode_helper12_helper_8004B8FC(pIter->mes, pBlock->field_0_name);
            pIter->field_20 = i;
            pIter++;
        }
    }

    if (dword_800ABB48 == 0 && pMemcard->field_3_free_blocks >= dword_800ABB4C->field_3)
    {
        memcpy(pIter->mes, "", 1);
        pIter->field_20 = 16;
        pIter++;
    }

    info->field_1C_kcb = work->field_214_font;
    info->max_num = pIter - info->menu;

    if (dword_800ABB4C->field_0[0] != 71)
    {
        if (info->max_num && pIter[-1].field_20 == 16)
        {
            info->field_4 = info->max_num - 1;
        }
        else
        {
            info->field_4 = 0;
        }
    }
    else if (dword_800AB6EC == -1 || dword_800AB6EC >= info->max_num)
    {
        if (dword_800ABB48 == 0 && info->max_num && pIter[-1].field_20 == 16)
        {
            info->field_4 = info->max_num - 1;
        }
        else
        {
            info->field_4 = 0;
        }
    }
    else
    {
        info->field_4 = dword_800AB6EC;
    }

    info->top = 0;
    info->message = param_3;
    info->field_E = -1;
    info->field_0_xpos = 40;
    info->field_2_ypos = 40;
    info->open_count = 8;
    info->field_A = 0;
    info->field_18 = -1;
    info->field_12 = 240;
    info->field_14 = 1;
    sub_8004B9C4(info, 0);
    return info->max_num != 0;
}

int menu_radio_do_file_mode_helper13_8004BCF8(GV_PAD *pPad, int *pOut, SELECT_INFO *info)
{
    int field_A;
    int field_20;
    int press;
    int status;

    if (dword_800AB6F4 != 0)
    {
        dword_800AB6F4 = 0;
        pPad->press |= PAD_CIRCLE;
    }
    else
    {
        status = pPad->status;
        if (info->max_num != 0)
        {
            if (status & (PAD_DOWN | PAD_UP))
            {
                field_A = 1;
                if (status & PAD_UP)
                {
                    field_A = -1;
                }
                if (info->field_A == field_A)
                {
                    if (--info->field_C < 0)
                    {
                        sub_8004B9C4(info, field_A);
                        info->field_C = 2;
                    }
                }
                else
                {
                    sub_8004B9C4(info, field_A);
                    info->field_C = 10;
                    info->field_A = field_A;
                }
            }
            else
            {
                info->field_A = 0;
            }
        }
    }
    press = pPad->press;
    if (press & PAD_CIRCLE)
    {
        GM_SeSet2_80032968(0, 0x3F, 0x20);
        if (info->max_num == 0)
        {
            *pOut = -1;
            return 1;
        }
        field_20 = info->menu[info->field_4].field_20;
        *pOut = field_20;
        if (dword_800ABB4C->field_0[0] == 71)
        {
            if (field_20 < 16)
            {
                dword_800AB6EC = info->field_4;
            }
            else
            {
                dword_800AB6EC = -1;
            }
        }
        return 1;
    }
    if (press & PAD_CROSS)
    {
        GM_SeSet2_80032968(0, 0x3F, 0x21);
        *pOut = info->field_E;
        return 1;
    }
    return 0;
}

const char *gMemoryCardNames_8009EC00[] = {"MEMORY CARD 1", "MEMORY CARD 2"};

void menu_radio_do_file_mode_helper14_8004BE98(Actor_MenuMan *work, char *param_2, SELECT_INFO *info)
{
    SELECT_MENU *infoChild;
    int                  idx, idx_copy;
    int                  memoryCardNo;
    int                  bit;
    int                  minusOne;

    infoChild = info->menu;
    idx = -1;
    for (memoryCardNo = 0; memoryCardNo < 2; memoryCardNo++)
    {
        bit = 1;
        bit <<= memoryCardNo;

        if (dword_800AB700 & bit)
        {
            strcpy(infoChild->mes, gMemoryCardNames_8009EC00[memoryCardNo]);
            infoChild->field_20 = memoryCardNo;
            if (memoryCardNo == dword_800AB6F0)
            {
                idx = infoChild - info->menu;
            }
            infoChild++;
        }
    }

    idx_copy = idx;
    if (infoChild == info->menu)
    {
        memcpy(&info->menu[0].mes, "NO CARD", 8);
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
    info->field_4 = idx_copy;
    info->top = 0;
    info->message = param_2;
    info->field_E = minusOne;
    info->field_10 = 128;
    info->field_18 = minusOne;
    info->open_count = 4;
    info->field_12 = 128;
    info->field_14 = 1;
    info->field_A = 0;
}

void menu_radio_do_file_mode_helper15_8004C04C(Actor_MenuMan *work, const char **srcs, int cnt, int field_4, const char *field_20,
                                               SELECT_INFO *info)
{
    KCB                 *kcb;
    const char          *src;
    int                  i;
    SELECT_MENU *dest;

    dest = info->menu;
    for (i = 0; i < cnt; i++, dest++)
    {
        src = srcs[i];
        strcpy(dest->mes, src);
        dest->field_20 = i;
    }

    kcb = work->field_214_font;

    info->max_num = dest - info->menu;
    info->field_4 = field_4;
    info->top = 0;
    info->message = field_20;
    info->field_E = 1;
    info->field_0_xpos = 160;
    info->field_A = 0;
    info->field_14 = 1;
    info->field_2_ypos = 128;
    info->field_10 = 64;
    info->field_12 = 32;
    info->open_count = 4;
    info->field_1C_kcb = kcb;
}

void menu_radio_do_file_mode_helper16_8004C164(MenuPrim *pGlue, SELECT_INFO *info)
{
    int        i;
    int        xpos, ypos;
    TextConfig textConfig;

    textConfig.flags = 0x12;
    if (info->field_14 != 0)
    {
        textConfig.colour = 0x66748956;
    }
    else
    {
        textConfig.colour = 0x663d482e;
    }
    textConfig.xpos = info->field_0_xpos;
    textConfig.ypos = info->field_2_ypos;
    menu_number_draw_string2_80043220(pGlue, &textConfig, info->message);
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

        if (i == info->field_4)
        {
            textConfig.colour = 0x66748956;
            if (info->field_14 != 0)
            {
                ypos += 16;
                sub_8004ABF0(textConfig.xpos, ypos, info->field_12, 12, 2);
            }
        }
        else
        {
            textConfig.colour = 0x663d482e;
        }
        menu_number_draw_string2_80043220(pGlue, &textConfig, info->menu[i].mes);
    }
}

int menu_radio_do_file_mode_helper17_8004C2E4(GV_PAD *pPad, int *outParam, SELECT_INFO *info)
{
    short status;

    if (info->open_count > 0)
    {
        info->open_count--;
        return 0;
    }

    status = pPad->status;
    if (info->max_num >= 2)
    {
        if (status & PAD_LEFT)
        {
            if (info->field_4 != 0)
            {
                GM_SeSet2_80032968(0, 0x3F, 0x1F);
                info->field_4 = 0;
            }
        }
        else if ((status & PAD_RIGHT) && info->field_4 == 0)
        {
            GM_SeSet2_80032968(0, 0x3F, 0x1F);
            info->field_4 = 1;
        }
    }
    if (pPad->press & PAD_CIRCLE)
    {
        *outParam = info->menu[info->field_4].field_20;
        GM_SeSet2_80032968(0, 0x3F, 0x20);
        return 1;
    }
    if (pPad->press & PAD_CROSS)
    {
        GM_SeSet2_80032968(0, 0x3F, 0x21);
        *outParam = info->field_E;
        return 1;
    }
    return 0;
}

int menu_radio_do_file_mode_8004C418(Actor_MenuMan *work, GV_PAD *pPad)
{
    TextConfig     textConfig1, textConfig2;
    int            res1, res2, res3;
    char         **strArr;
    SELECT_INFO *info;
    int            xpos;
    int            divisor;
    int            var_v0_2; // ypos?
    unsigned int   flags;
    DR_TPAGE      *tpage;
    unsigned char *mOt;
    int            flagsExtracted;

    mOt = work->field_20_otBuf->mPrimBuf.mOt;
    if (dword_800ABB48 == 0)
    {
        strArr = (char **)dword_8009EB4C;
        dword_8009EBBC[0] = dword_800ABB4C->field_4_name;
        dword_8009EBBC[1] = "SAVING...";
        dword_8009EBBC[3] = "NO SPACE";
    }
    else
    {
        strArr = (char **)dword_8009EB7C;
        dword_8009EBBC[0] = "LOAD DATA";
        dword_8009EBBC[1] = "LOADING...";
        dword_8009EBBC[3] = "NO FILE";
    }
    switch (dword_800ABB80)
    {
    case 0:
        sub_80048124();
        dword_800ABB84 = 0;
        font_set_color_80044DC4(work->field_214_font, 1, 0x19F2, 0);
        font_clut_update_80046980(work->field_214_font);
        dword_800ABB80 = 1;
        dword_800ABB88 = NULL;
        dword_800ABB78 = NULL;
        dword_800ABB74 = NULL;
        dword_800ABB70 = NULL;
        menu_radio_do_file_mode_helper2_8004A87C(0, 160, 100, 0, 0);
        sub_8004ABF0(160, 0x67, 0x60, 0xC, 0);
        GM_SeSet2_80032968(0, 0x3F, 0x20);
        dword_800AB6F4 = 0;
        dword_800AB6FC = -1;
        break;
    case 1:
        menu_radio_do_file_mode_helper2_8004A87C(3, 160, 0x80, 0, -1);
        flags = dword_800ABB58;
        if (flags == 0)
        {
            break;
        }
        if (flags == 0xC1000001)
        {
            if (dword_800ABB48 == 0)
            {
                strcpy(dword_800ABB70->menu[dword_800ABB70->field_4].mes, aBislpm99999 + 0xc);
                dword_800ABB70->menu[dword_800ABB70->field_4].field_20 = 0;
                sub_8004AEA8(dword_800ABB70);
            }
            menu_radio_do_file_mode_helper2_8004A87C(2, 160, 0x80, 0, 2);
        }
        if (flags == 0x1000009)
        {
            menu_radio_do_file_mode_helper2_8004A87C(2, 160, 0x80, 0, 1);
            menu_radio_do_file_mode_helper4_8004AA68(8, 160, 0x6E, 160, 0x7A, 0);
            sub_8004ABF0(160, 0x83, 0x60, 0xC, 4);
        }
        if (flags & 0x04000000)
        {
            menu_radio_do_file_mode_helper2_8004A87C(2, 160, 0x80, 0, 4);
            sub_8004ABF0(160, 0x83, 0x60, 0xC, 4);
        }
        if (flags & 0x01000000)
        {
            menu_radio_do_file_mode_helper7_8004AE3C(work, strArr[(unsigned char)dword_800ABB58]);
            dword_800ABB84 = 0xF;
        }
        if (flags & 0x40000000)
        {
            dword_800ABB80 = 2;
            dword_800ABB84 = 1;
        }
        else if (flags & 0x20000000)
        {
            dword_800ABB84 = 0;
            switch ((unsigned char)dword_800ABB58)
            {
            case 0:
                dword_800ABB80 = 4;
                menu_radio_do_file_mode_helper11_8004B958(&dword_800ABB70, 0x11);
                dword_800ABB88 = dword_800ABB70;
                if (menu_radio_do_file_mode_helper12_8004BA80(work, mcd_last_file_800ABB68[dword_800AB6FC], "", dword_800ABB70) == 0)
                {
                    menu_radio_do_file_mode_helper7_8004AE3C(work, strArr[4]);
                    dword_800ABB84 = 1;
                    menu_radio_do_file_mode_helper2_8004A87C(3, 160, 0x80, 0, 3);
                    sub_8004ABF0(160, 0x83, 0x60, 0xC, 4);
                    dword_800ABB54 = 3;
                }
                if (dword_800ABB74 == NULL)
                {
                    menu_radio_do_file_mode_helper11_8004B958(&dword_800ABB74, 3);
                    menu_radio_do_file_mode_helper14_8004BE98(work, "SELECT MEMORY CARD", dword_800ABB74);
                    divisor = -4;
                    dword_800ABB74->field_14 = 0;
                }
                else
                {
                    divisor = 4;
                }
                menu_radio_do_file_mode_helper2_8004A87C(0, 0x40, 0x18, 4, 0);
                menu_radio_do_file_mode_helper3_8004A994(4, 160, 0x28, divisor, dword_800ABB74);
                menu_radio_do_file_mode_helper4_8004AA68(5, 0x6C, 0x1A, 160, 0x1A, divisor);
                menu_radio_do_file_mode_helper4_8004AA68(6, 160, 0x1A, 160, 0x24, divisor);
                info = dword_800ABB74;
                if (dword_800ABB74->max_num == 1)
                {
                    xpos = info->field_0_xpos;
                }
                else
                {
                    xpos = info->field_0_xpos - info->field_10 / 2;
                    if (info->field_4 == 1)
                    {
                        xpos += info->field_10;
                    }
                }

                if (dword_800ABB88->max_num == 0)
                {
                    xpos = info->field_0_xpos;
                    var_v0_2 = 0x7A;
                }
                else
                {
                    var_v0_2 = 0x40;
                }
                menu_radio_do_file_mode_helper4_8004AA68(7, xpos, 0x3C, xpos, var_v0_2, -4);
                menu_radio_do_file_mode_helper5_8004ABDC(8);
                break;
            case 1:
                if (dword_800ABB74 != NULL)
                {
                    divisor = 4;
                }
                else
                {
                    divisor = -4;
                }
                if (dword_800ABB70 != NULL)
                {
                    menu_radio_do_file_mode_helper10_8004B91C(dword_800ABB70);
                    dword_800ABB70 = NULL;
                }
                menu_radio_do_file_mode_helper11_8004B958(&dword_800ABB74, 3);
                dword_800ABB88 = dword_800ABB74;
                menu_radio_do_file_mode_helper14_8004BE98(work, "SELECT MEMORY CARD", dword_800ABB74);
                dword_800ABB80 = 3;
                menu_radio_do_file_mode_helper2_8004A87C(0, 160, 0x18, 4, 0);
                menu_radio_do_file_mode_helper3_8004A994(4, 160, 100, divisor, dword_800ABB74);
                menu_radio_do_file_mode_helper4_8004AA68(5, 160, 0x1A, 160, 0x1A, divisor);
                menu_radio_do_file_mode_helper4_8004AA68(6, 160, 0x20, 160, 0x60, divisor);
                menu_radio_do_file_mode_helper5_8004ABDC(7);
                menu_radio_do_file_mode_helper5_8004ABDC(8);
                break;
            }
        }
        else if (flags & 0x10000000)
        {
            static const char *off_8009EC08[] = {"YES", "NO"};

            flagsExtracted = ((flags >> 0x14) ^ 1);
            flagsExtracted &= 1;
            dword_800ABB80 = 5;
            menu_radio_do_file_mode_helper11_8004B958(&dword_800ABB78, 2);
            dword_800ABB88 = dword_800ABB78;
            menu_radio_do_file_mode_helper15_8004C04C(work, off_8009EC08, 2, flagsExtracted,
                                                      dword_8009EBB4[(unsigned char)dword_800ABB58], dword_800ABB78);
            menu_radio_do_file_mode_helper7_8004AE3C(work, dword_8009EBAC[(unsigned char)dword_800ABB58]);
            dword_800ABB84 = 1;
        }
        else if ((int)flags < 0)
        {
            dword_800ABB80 = 6;
            dword_800ABB58 = 0;
            mts_wup_tsk_8008A540(7);
        }
        else
        {
            dword_800ABB80 = 1;
            dword_800ABB58 = 0;
            mts_wup_tsk_8008A540(7);
        }
        break;
    case 2:
        if (pPad->press & (PAD_TRIANGLE | PAD_CROSS | PAD_SQUARE | PAD_CIRCLE))
        {
            dword_800ABB84 = 0;
            if (dword_800ABB58 < 0)
            {
                dword_800ABB80 = 6;
                dword_800ABB58 = 0;
            }
            else
            {
                dword_800ABB80 = 1;
                dword_800ABB58 = 0;
            }
            mts_wup_tsk_8008A540(7);
            menu_radio_do_file_mode_helper2_8004A87C(3, 160, 0x80, 0, -1);
            menu_radio_do_file_mode_helper2_8004A87C(2, 160, 0x80, 0, -1);
        }
        else
        {
            draw_radio_wait_mark_8004143C(work, mOt);
        }
        break;
    case 3:
        if (dword_800AB700 & 0x80)
        {
            menu_radio_do_file_mode_helper14_8004BE98(work, "SELECT MEMORY CARD", dword_800ABB74);
            dword_800AB700 &= ~0x80;
        }
        textConfig1.xpos = 160;
        textConfig1.ypos = 0xC8;
        textConfig1.flags = 0x12;
        textConfig1.colour = 0x66748956;
        menu_number_draw_string2_80043220(work->field_20_otBuf, &textConfig1, "PRESS * TO EXIT");
        if (menu_radio_do_file_mode_helper17_8004C2E4(pPad, &res1, dword_800ABB74) != 0)
        {
            printf("Res %d\n", res1);
            dword_800ABB58 = 0;
            dword_800ABB80 = 1;
            dword_800ABB84 = 0;
            dword_800ABB74->field_14 = 0;
            dword_800ABB5C = res1;
        }
        break;
    case 5:
        if (menu_radio_do_file_mode_helper17_8004C2E4(pPad, &res2, dword_800ABB78) != 0)
        {
            printf("Res %d\n", res2);
            dword_800ABB78->field_14 = 0;
            if (res2 == -1)
            {
                menu_radio_do_file_mode_helper5_8004ABDC(8);
            }
            dword_800ABB58 = 0;
            dword_800ABB5C = res2;
            mts_wup_tsk_8008A540(7);
            dword_800ABB80 = 1;
            dword_800ABB84 = 0;
        }
        else
        {
            menu_radio_do_file_mode_helper16_8004C164(work->field_20_otBuf, dword_800ABB88);
            if (dword_800ABB70 != NULL)
            {
                menu_radio_do_file_mode_helper4_8004AA68(8, 160, 0x6E, 160, 0x7A, 0);
            }
        }
        break;
    case 4:
        if (dword_800ABB70->max_num != 0)
        {
            textConfig2.xpos = 160;
            textConfig2.ypos = 0xC8;
            textConfig2.flags = 0x12;
            textConfig2.colour = 0x66748956;
            menu_number_draw_string2_80043220(work->field_20_otBuf, &textConfig2, "PRESS * TO SELECT MEMORY CARD");
        }
        if (menu_radio_do_file_mode_helper13_8004BCF8(pPad, &res3, dword_800ABB70) != 0)
        {
            printf("Res %d\n", res3);
            dword_800ABB70->field_14 = 0;
            if (res3 == -1)
            {
                menu_radio_do_file_mode_helper10_8004B91C(dword_800ABB70);
                dword_800ABB70 = NULL;
            }
            else
            {
                dword_800ABB70->field_18 = 4;
            }
            dword_800ABB5C = res3;
            if (dword_800ABB80 == 4)
            {
                dword_800ABB58 = 0;
                mts_wup_tsk_8008A540(7);
            }
            dword_800ABB80 = 1;
            dword_800ABB84 = 0;
        }
        break;
    case 6:
        if (mts_get_task_status_8008B618(7) == 0)
        {
            printf("END SAVE MODE\n");
            menu_radio_do_file_mode_helper10_8004B91C(dword_800ABB70);
            menu_radio_do_file_mode_helper10_8004B91C(dword_800ABB74);
            menu_radio_do_file_mode_helper10_8004B91C(dword_800ABB78);
            menu_radio_do_file_mode_helper_8004A858();
            GV_FreeMemory_80015FD0(0, dword_800ABB50);
            GM_LastResultFlag = dword_800ABB54;
            printf("END STATE %d\n", GM_LastResultFlag);
            if (dword_800ABB48 != 2)
            {
                font_set_color_80044DC4(work->field_214_font, 1, 0x3BEF, 0);
                return 1;
            }
            return 2;
        }
        break;
    }
    if (dword_800ABB84 >= 2)
    {
        dword_800ABB84--;
    }
    else if (dword_800ABB84 > 0)
    {
        menu_radio_do_file_mode_helper8_8004AFE4(work, mOt, dword_800ABB88);
    }
    NEW_PRIM(tpage, work);
    setDrawTPage(tpage, 0, 1, getTPage(0, 1, 960, 256));
    addPrim(mOt, tpage);
    if (dword_800ABB70 != NULL)
    {
        menu_radio_do_file_mode_save_memcard_8004B0A0(work, mOt, dword_800ABB70);
    }
    menu_radio_do_file_mode_helper6_8004AD40(work->field_20_otBuf);
    return 0;
}

void sub_8004CF20(int code, char **param_2, char **param_3)
{
    int i;

    if (code == 0)
    {
        *param_2 = "NO PLACE";
        *param_3 = "\x81\x40";
    }
    GCL_SetArgTop_80020690((char *)dword_800ABB8C);
    printf("code %d\n", code);
    for (i = 0; i < code; i++) {
        if (GCL_Get_Param_Result_80020AA4() == 0)
        {
            return;
        }
        *param_2 = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
        if (dword_800ABB90 > 0 && dword_800ABB48 == 0)
        {
            *param_3 = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
        }
    }
}

extern char  dword_800122F4[];

char dword_8009EC10[] = {0x82, 0x63, 0x82, 0x8F, 0x82, 0x83, 0x82, 0x8B, 0x00}; // Ｄｏｃｋ

const char *diff_names_8009EC1C[] = {
    "\x81\x6D\x82\x75\x82\x64\x81\x6E", /* ［ＶＥ］ */
    "\x81\x6D\x82\x64\x82\x79\x81\x6E", /* ［ＥＺ］ */
    "\x81\x6D\x82\x6D\x82\x6C\x81\x6E", /* ［ＮＭ］ */
    "\x81\x6D\x82\x67\x82\x63\x81\x6E", /* ［ＨＤ］ */
    "\x81\x6D\x82\x64\x82\x77\x81\x6E"  /* ［ＥＸ］ */
};

void sub_8004D008(char *outStr, mem_card *pMemcard, int arg2, int arg3)
{
    char  str1[11];
    char *str2;
    char *str3;

    str1[0] = 0x82;
    str1[1] = (arg2 / 10) + 0x4f;
    str1[2] = 0x82;
    str1[3] = (arg2 % 10) + 0x4f;
    str1[4] = 0x81;
    str1[5] = 0x46;
    str1[6] = 0x82;
    str1[7] = (arg3 / 10) + 0x4f;
    str1[8] = 0x82;
    str1[9] = (arg3 % 10) + 0x4f;
    str1[10] = '\0';
    if (dword_800ABB90 == 0)
    {
        sub_8004CF20(1, &str2, &str3);
        str3 = dword_8009EC10;
    }
    else
    {
        sub_8004CF20(dword_800ABB90, &str2, &str3);
    }

    /* ＭＧＳ∫ */
    sprintf(outStr, "%s%s%s%s%s%s", "\x82\x6C\x82\x66\x82\x72\x81\xE7", diff_names_8009EC1C[GM_DifficultyFlag + 1], "\x81\x40", str1, "\x81\x40", str3);
}

void sub_8004D14C(char *outstr, char *param_2)
{
    char *str1;
    char *str2;
    int   val;

    sub_8004CF20(param_2[6] - 0x40, &str1, &str2);

    val = (param_2[5] - 0x40) & 7;
    if (val == 0)
    {
        val = 2;
    }
    else if (val < 3)
    {
        val = 1;
    }
    else
    {
        val = 3;
    }
    sprintf(outstr, "\f%c%s", val | 0x30, str1);
}

void sub_8004D1D0(char *saveBuf)
{
    int   currentOffset;
    int   size;
    char *saveBufIter;

    currentOffset = 0x100;
    saveBufIter = saveBuf;
    GM_TotalSaves++;
    for (;;)
    {
        size = GCL_MakeSaveFile_80020C0C(saveBufIter);
        currentOffset += size;

        if (currentOffset + size > 0x2000)
        {
            break;
        }

        saveBufIter += size;
        printf("*");
    }
}

void init_file_mode_8004D24C(DATA_INFO *pSaveMode, int param_2)
{
    dword_800ABB80 = 0;
    dword_800ABB4C = pSaveMode;
    init_file_mode_helper2_8004A800();
    init_file_mode_helper_8004A424(param_2);
}

DATA_INFO stru_8009EC30 = {{0x47, 0}, 0, 1, "SAVE DATA", (void *)sub_8004D008, (void *)sub_8004D14C, (void *)sub_8004D1D0};

void menu_radio_init_save_mode_8004D280(int param_1, int param_2)

{
    stru_8009EC30.field_0[1] = 0;
    if (param_2 == 0)
    {
        stru_8009EC30.field_2 = 1;
    }
    else
    {
        stru_8009EC30.field_2 = param_2;
    }
    dword_800ABB8C = param_1;
    dword_800ABB90 = param_2;
    init_file_mode_8004D24C(&stru_8009EC30, 0);
}

void menu_radio_update_helper4_8004D2D0(int param_1)
{
    dword_800ABB8C = param_1;
    init_file_mode_8004D24C(&stru_8009EC30, 1);
}

void menu_radio_8004D2FC(DATA_INFO *pSaveMode)
{
    init_radio_message_board_80040F74(&gMenuMan_800BD360);
    init_file_mode_8004D24C(pSaveMode, 0);
}

int menu_radio_8004D334(GV_PAD *pPad)
{
    return menu_radio_do_file_mode_8004C418(&gMenuMan_800BD360, pPad);
}

void menu_radio_8004D35C()
{
    sub_8004124C(&gMenuMan_800BD360);
}
