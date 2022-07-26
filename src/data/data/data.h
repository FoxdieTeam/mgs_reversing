#ifndef DATA_H
#define DATA_H

enum TextConfig_Flags
{
    TextConfig_Flags_eRightAlign_01 = 0x01,
    TextConfig_Flags_eCentreAlign_02 = 0x02,
    TextConfig_Flags_eLargeFont_10 = 0x10,
    TextConfig_Flags_eSemiTransparent_20 = 0x20,
};

typedef struct TextConfig
{
    int xpos;
    int ypos;
    int flags;
    int colour;
} TextConfig;

extern struct TextConfig gMenuTextConfig_8009E2E4;  

typedef struct
{
    int dword_8009E280;
    int dword_8009E284;
    int dword_8009E288;
    int dword_8009E28C;
} unk_8009E280;

struct Anim_Data
{
  short field_0;
  short field_2;
  int field_4;
  short field_8_count;
  short field_A;
  short field_C;
  short field_E;
  short field_10;
  short field_12;
  int field_14;
  void *field_18;
};

#endif // DATA_H
