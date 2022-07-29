#include "Menu/menuMan.h"
#include "data/data/data.h"

extern MenuGlue gMenuPrimBuffer_8009E2D0;
extern TextConfig gMenuTextConfig_8009E2E4;

extern int sprintf_8008E878(char *buffer, const char *fmt, ...);
extern int strlen_8008E7B8(char *s);
extern void _menu_number_draw_string_80042BF4(MenuGlue *param_1, int *param_2, char *param_3);
extern void _menu_number_draw_string2_80043220(MenuGlue *param_1, int *param_2, char *param_3);
extern void sub_80038BB4();

int MENU_Text_80038C38(char *fmt, const char *str, int param_3, int param_4, int param_5)
{
    int string_length;
    unsigned int free_space;
    char string_buffer[64];

    if (gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation)
    {
        sprintf_8008E878(string_buffer, fmt, str, param_3, param_4, param_5);
        free_space = gMenuPrimBuffer_8009E2D0.mPrimBuf.mOtEnd - gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation;
        string_length = strlen_8008E7B8(string_buffer);
        if (string_length * 0x14 + 0x28U <= free_space)
        {
            if (gMenuTextConfig_8009E2E4.flags & 0x10U)
            {
                _menu_number_draw_string2_80043220(&gMenuPrimBuffer_8009E2D0, &gMenuTextConfig_8009E2E4.xpos, string_buffer);
            }
            else
            {
                _menu_number_draw_string_80042BF4(&gMenuPrimBuffer_8009E2D0, &gMenuTextConfig_8009E2E4.xpos,
                                                   string_buffer);
            }
            sub_80038BB4();
        }
    }
    return gMenuTextConfig_8009E2E4.xpos;
}