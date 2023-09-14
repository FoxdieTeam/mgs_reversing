#include "linker.h"
#include "libgcl/libgcl.h"
#include "mts/mts_new.h"

extern const char aPrint[];
extern const char aS_2[];
extern const char aD_3[];
extern const char asc_800AB428[];

int GCL_Command_print_8002D0E4(unsigned char *pScript)
{
    int code;
    int value;

    printf(aPrint); // "print: "
    while (pScript)
    {
        pScript = GCL_GetNextValue_8002069C(pScript, &code, &value);
        if (code == GCLCODE_NULL)
            break;
        if (code == GCLCODE_STRING)
            printf(aS_2, value); // "%s"
        else
            printf(aD_3, value); // "%d"
    }
    printf(asc_800AB428); // "\n"
    return 0;
}
