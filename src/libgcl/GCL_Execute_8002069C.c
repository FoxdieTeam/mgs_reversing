#include "linker.h"
#include "mts_new.h"
#include "gcl.h"

// $gp
extern unsigned char*   dword_800AB9A0;
unsigned char* SECTION(".sbss") dword_800AB9A0;

extern int              GCL_8002058C(unsigned char *pScript, void *ptr);
extern unsigned char *  sub_80021634(unsigned char *param_1, int *param_2, int *param_3);
extern int              GCL_GetStackPointer_80020904(int param_1);

unsigned char*  GCL_Execute_8002069C(unsigned char *pScript, int *exec_ret, int *arg_value)
{
    unsigned char   *ptr;
    int             gcl_code;
    int             size;

    ptr = pScript;
    gcl_code = *ptr;
    ptr++;
    if ((gcl_code & 0xF0) == 16)
    {
        return sub_80021634(pScript, exec_ret, arg_value);
    }
    *exec_ret = gcl_code;
    switch (gcl_code)
    {
        case 0: // stop script
            ptr = 0;
            break;

        case 1: // value
            *arg_value = (short)ToSHORT(ptr);
            ptr += 2;
            break;

        case 9: // SdCode
        case 10: // sound file/id
            *arg_value = (unsigned int)ToINT(ptr);
            ptr += 4;
            break;

        // hashed strings without spaces: mostly in japanese
        case 6: // string hash: elements from the map, actions [ex: "enter"/"leave"(jp), "on"/"off"(en)], etc..
        case 8: // function name hash: (example of function/proc call: 70 04 XX XX 00)
            *arg_value = (unsigned short)ToSHORT(ptr);
            ptr += 2;
            break;

        case 2: // value (many of them uses defines inside of gcl scripts as seen from leaked scripts chunks)
        case 3: // value
        case 4: // value
            *arg_value = (unsigned char)*ptr;
            ptr += 1;
            break;

        case 7: // long string: ground item descriptions etc..
            *arg_value = (int)(ptr + 1);
            size = *ptr;
            goto ADD_SIZE_80020834;

        case 0x20: // stack variable
            *arg_value = GCL_GetStackPointer_80020904(*ptr);
            *exec_ret = 1;
            ptr += 1;
            break;

        case 0x40: // script data: followed by 0x60 (if, chara, -exec) or 0x70 (function call)
            *arg_value = (int)(ptr + 2);
            size = ToSHORT(ptr);
            ptr += size;
            break;

        case 0x30: // if condition or eval assignation
            *arg_value = GCL_8002058C(ptr + 1, arg_value);
            size = *ptr;
            ptr += size;
            break;

        case 0x50: // ??
            *exec_ret |= *ptr << 16;
            *arg_value = (int)(ptr + 2);
            size = ptr[1];
ADD_SIZE_80020834:
            ptr += size + 1;
            break;

        default:
            mts_printf_8008BBA0("GCL:WRONG CODE %x\n", gcl_code);
            break;
    }
    dword_800AB9A0 = ptr;
    return ptr;
}
