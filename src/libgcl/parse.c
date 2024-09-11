#include "common.h"
#include "libgcl.h"

/*** $gp ***/
int            *SECTION(".sbss") GCL_ArgStackP_800AB998;
unsigned char **SECTION(".sbss") GCL_CommandLineP_800AB99C;
unsigned char  *SECTION(".sbss") GCL_NextStrPtr_800AB9A0;

// I think these bottom two sbss are actually instantiated later in another file
int SECTION(".sbss") dword_800AB9A4;
int SECTION(".sbss") dword_800AB9A8[2];

/*** bss ***/
extern int            argstack_800B3C28[32];
extern unsigned char *commandlines_800B3CA8[8];

void GCL_SetArgTop(unsigned char *top)
{
    GCL_NextStrPtr_800AB9A0 = top;
}

unsigned char *GCL_GetNextValue(unsigned char *top, int *type_p, int *value_p)
{
    unsigned char *ptr;
    int            gcl_code;
    int            size;

    ptr = top;
    gcl_code = *ptr;
    ptr++;
    if (GCL_IsVariable(gcl_code))
    {
        return GCL_GetVar(top, type_p, value_p);
    }
    *type_p = gcl_code;
    switch (gcl_code)
    {
    case GCLCODE_NULL:
        ptr = 0;
        break;

    case GCLCODE_SHORT:
        *value_p = (short)GCL_GetShort(ptr);
        ptr += 2;
        break;

    case GCLCODE_SDCODE:
    case GCLCODE_TABLE_CODE:
        *value_p = (unsigned int)GCL_GetLong(ptr);
        ptr += 4;
        break;

    case GCLCODE_HASHED_STRING:
    case GCLCODE_PROC_CALL:
        *value_p = (unsigned short)GCL_GetShort(ptr);
        ptr += 2;
        break;

    case GCLCODE_BYTE:
    case GCLCODE_CHAR:
    case GCLCODE_FLAG:
        *value_p = (unsigned char)GCL_GetByte(ptr);
        ptr += 1;
        break;

    case GCLCODE_STRING:
        *value_p = (int)(ptr + 1);
        size = *ptr;
        goto ADD_SIZE_80020834;

    case GCLCODE_STACK_VAR:
        *value_p = GCL_GetArgs(*ptr);
        *type_p = 1;
        ptr += 1;
        break;

    case GCLCODE_SCRIPT_DATA:
        *value_p = (int)(ptr + 2);
        size = GCL_GetShort(ptr);
        ptr += size;
        break;

    case GCLCODE_EXPRESSION:
        *value_p = GCL_Expr(ptr + 1, value_p);
        size = *ptr;
        ptr += size;
        break;

    case GCLCODE_PARAMETER:
        *type_p |= *ptr << 16;
        *value_p = (int)(ptr + 2);
        size = ptr[1];
    ADD_SIZE_80020834:
        ptr += size + 1;
        break;

    default:
        printf("GCL:WRONG CODE %x\n", gcl_code);
        break;
    }
    GCL_NextStrPtr_800AB9A0 = ptr;
    return ptr;
}

STATIC void GCL_InitArgStack(void)
{
    GCL_ArgStackP_800AB998 = argstack_800B3C28;
}

int *GCL_SetArgStack(GCL_ARGS *args)
{
    if (!args)
    {
        return 0;
    }
    else
    {
        int *sp;
        int *sp2;
        int *argv = (int *)&args->argv[args->argc - 1];
        int  i = args->argc;
        int *org = GCL_ArgStackP_800AB998;

        while (i > 0)
        {
            // stack push
            sp = GCL_ArgStackP_800AB998;
            *sp = *argv;
            GCL_ArgStackP_800AB998 = sp + 1;

            argv--;
            i--;
        }

        // stack push
        sp2 = GCL_ArgStackP_800AB998;
        *sp2 = args->argc;
        GCL_ArgStackP_800AB998 = sp2 + 1;

        return org;
    }
}

void GCL_UnsetArgStack(void *stack)
{
    if (stack)
    {
        GCL_ArgStackP_800AB998 = stack;
    }
    return;
}

int GCL_GetArgs(int argno)
{
    return GCL_ArgStackP_800AB998[~argno];
}

STATIC void GCL_InitCommandLineBuffer(void)
{
    GCL_CommandLineP_800AB99C = commandlines_800B3CA8;
}

void GCL_SetCommandLine(unsigned char *argtop)
{
    unsigned char **pStackTmp = GCL_CommandLineP_800AB99C;
    (*pStackTmp) = argtop;
    pStackTmp++;
    GCL_CommandLineP_800AB99C = pStackTmp;
}

void GCL_UnsetCommandLine(void)
{
    GCL_CommandLineP_800AB99C--;
}

char *GCL_GetOption(char c)
{
    unsigned char *pScript;
    int            code;
    char          *value;

    pScript = *(GCL_CommandLineP_800AB99C - 1);
    do
    {
        pScript = GCL_GetNextValue(pScript, &code, (int*)&value);
        if (code == GCLCODE_NULL)
        {
            return 0;
        }
    } while (!GCL_IsParam(code) || (code >> 16 != (c & 0xff)));

    GCL_NextStrPtr_800AB9A0 = value; // TODO: Union/any type return ??
    return value;
}

// might be GCL_NextStr
int GCL_StrToInt(unsigned char *pScript)
{
    int code;
    int value;
    GCL_NextStrPtr_800AB9A0 = GCL_GetNextValue(pScript, &code, &value);
    return value;
}

int GCL_StrToSV(unsigned char *pInScript, SVECTOR *pOut3Words)
{
    int             counter = 0;
    unsigned short *pOutIter = (unsigned short *)pOut3Words;
    unsigned char  *pScript = pInScript;
    do
    {
        int code;
        int value;
        pScript = GCL_GetNextValue(pScript, &code, &value);
        counter++;
        *pOutIter = value;
        pOutIter++;
    } while (counter < 3);

    GCL_NextStrPtr_800AB9A0 = pScript;
    return 0;
}

char *GCL_ReadString(char *ptr)
{
    int type;
    int value;

    ptr = GCL_GetNextValue(ptr, &type, &value);
    GCL_NextStrPtr_800AB9A0 = ptr;

    if (ptr)
    {
        return (char *)value;
    }
    else
    {
        return 0;
    }
}

unsigned char *GCL_GetParamResult(void)
{
    if (!*GCL_NextStrPtr_800AB9A0 || GCL_IsParam(*GCL_NextStrPtr_800AB9A0))
    {
        return 0;
    }

    return GCL_NextStrPtr_800AB9A0;
}

int GCL_GetNextParamValue(void)
{
    return GCL_StrToInt(GCL_GetParamResult());
}

void GCL_ReadParamVector(SVECTOR *pOut3Words)
{
    GCL_StrToSV(GCL_GetParamResult(), pOut3Words);
    return;
}

void GCL_80020B2C(unsigned char *top)
{
    int code;
    int value;

    do {
        top = GCL_GetNextValue(top, &code, &value);
    } while (code != GCLCODE_NULL);
    return;
}

void GCL_ParseInit(void)
{
    GCL_InitArgStack();
    GCL_InitCommandLineBuffer();
    return;
}
