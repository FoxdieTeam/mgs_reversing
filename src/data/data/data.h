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

typedef struct FS_FILE_INFO_8009D49C
{
	const char *pDatName;
	int field_4_sector;
} FS_FILE_INFO_8009D49C;

#endif // DATA_H
