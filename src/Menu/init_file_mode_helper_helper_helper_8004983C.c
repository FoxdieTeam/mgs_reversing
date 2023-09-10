#include "menuman.h"
#include "Game/linkvarbuf.h"

extern menu_save_mode_data *dword_800ABB4C;
menu_save_mode_data        *dword_800ABB4C;

int memcard_get_status_800257B0();
int memcard_write_8002554C(unsigned char, char *, int, void *, int);

extern int GM_PadResetDisable_800AB3F4;
extern char *MGS_MemoryCardName_800AB2EC;
extern int dword_8009E774[];

extern char aBislpm99999[];
const char SECTION(".rdata") aNoMemoryForFil[] = "NO MEMORY FOR FILE BODY\n";

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
    mts_printf_8008BBA0(aNoMemoryForFil);
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
