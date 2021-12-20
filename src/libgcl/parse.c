#include "linker.h"
#include "mts_new.h"
#include "gcl.h"

/***$gp*************************************************/
int*			SECTION(".sbss") argstack_p_800AB998;
unsigned char**	SECTION(".sbss") commandline_p_800AB99C;
unsigned char*	SECTION(".sbss") pScript_800AB9A0;

//I think these bottom two sbss are actually instantiated later in another file
int				SECTION(".sbss") dword_800AB9A4;
int				SECTION(".sbss") dword_800AB9A8[2];
/*******************************************************/

/***** bss ************************************************************/
int		        SECTION(".argstack_800B3C28") argstack_800B3C28[32];
unsigned char*	SECTION(".commandlines_800B3CA8") commandlines_800B3CA8[8];
/*********************************************************************/

void GCL_SetArgTop_80020690( unsigned char *top )
{
    pScript_800AB9A0 = top;
}

extern int              GCL_Expr_8002058C(unsigned char *pScript, void *ptr);
extern unsigned char *  GCL_GetVar_80021634(unsigned char *pScript, int *retCode, int *retValue);
extern int              GCL_GetArgs_80020904(int param_1);

unsigned char*  GCL_GetNextValue_8002069C(unsigned char *pScript, int *retCode, int *retValue)
{
    unsigned char   *ptr;
    int             gcl_code;
    int             size;

    ptr = pScript;
    gcl_code = *ptr;
    ptr++;
    if (GCL_IsVariable(gcl_code))
    {
        return GCL_GetVar_80021634(pScript, retCode, retValue);
    }
    *retCode = gcl_code;
    switch (gcl_code)
    {
        case GCLCODE_NULL:
            ptr = 0;
            break;

        case GCLCODE_SHORT:
            *retValue = (short)GCL_GetShort(ptr);
            ptr += 2;
            break;

        case GCLCODE_SDCODE:
        case GCLCODE_TABLE_CODE:
            *retValue = (unsigned int)GCL_GetLong(ptr);
            ptr += 4;
            break;

        case GCLCODE_HASHED_STRING:
        case GCLCODE_PROC_CALL:
            *retValue = (unsigned short)GCL_GetShort(ptr);
            ptr += 2;
            break;

        case GCLCODE_BYTE:
        case GCLCODE_CHAR:
        case GCLCODE_BOOL:
            *retValue = (unsigned char)GCL_GetByte(ptr);
            ptr += 1;
            break;

        case GCLCODE_STRING:
            *retValue = (int)(ptr + 1);
            size = *ptr;
            goto ADD_SIZE_80020834;

        case GCLCODE_STACK_VAR:
            *retValue = GCL_GetArgs_80020904(*ptr);
            *retCode = 1;
            ptr += 1;
            break;

        case GCLCODE_SCRIPT_DATA:
            *retValue = (int)(ptr + 2);
            size = GCL_GetShort(ptr);
            ptr += size;
            break;

        case GCLCODE_EXPRESSION:
            *retValue = GCL_Expr_8002058C(ptr + 1, retValue);
            size = *ptr;
            ptr += size;
            break;

        case GCLCODE_PARAMETER:
            *retCode |= *ptr << 16;
            *retValue = (int)(ptr + 2);
            size = ptr[1];
ADD_SIZE_80020834:
            ptr += size + 1;
            break;

        default:
            mts_printf_8008BBA0("GCL:WRONG CODE %x\n", gcl_code);
            break;
    }
    pScript_800AB9A0 = ptr;
    return ptr;
}

void GCL_InitArgStack_80020868( void )
{
	argstack_p_800AB998 = argstack_800B3C28;
}

int *GCL_SetArgStack_8002087C( GCL_ARGS *args )
{
	if ( !args ) 
	{
		return 0;
	}
	else
	{
		int* sp;
		int* sp2;
		int* argv = ( int* )&args->argv[args->argc - 1];
		int i = args->argc;
		int* org = argstack_p_800AB998;

		while ( i > 0 )
		{
			//stack push
			sp = argstack_p_800AB998;
			*sp = *argv;
			argstack_p_800AB998 = sp + 1;

			argv--;
			i--;
		}

		//stack push
		sp2 = argstack_p_800AB998;
		*sp2 = args->argc;
		argstack_p_800AB998 = sp2 + 1;

		return org;
	}
}

void GCL_UnsetArgStack_800208F0( void* stack )
{
    if ( stack )
    {
        argstack_p_800AB998 = stack;
    }
    return;
}

int GCL_GetArgs_80020904( int argno )
{
    return argstack_p_800AB998[~argno];
}

void GCL_InitCommandLineBuffer_80020920( void )
{
    commandline_p_800AB99C = commandlines_800B3CA8;
}

void GCL_SetCommandLine_80020934(unsigned char* pValue)
{
    unsigned char** pStackTmp = commandline_p_800AB99C;
    (*pStackTmp) = pValue;
    pStackTmp++;
    commandline_p_800AB99C = pStackTmp;
}

void GCL_UnsetCommandLine_80020950()
{
    commandline_p_800AB99C--;
}

int GCL_GetParam_80020968(char paramName)
{
    unsigned char* pScript;
    int code;
    int value;
  
    pScript = *(commandline_p_800AB99C - 1);
    do 
    {
        pScript = GCL_GetNextValue_8002069C(pScript, &code, &value);
        if (code == GCLCODE_NULL)
        {
            return 0;
        }
    }
    while (!GCL_IsParam(code) || (code >> 0x10 != (paramName & 0xff)));

    pScript_800AB9A0 = (unsigned char*)value; // TODO: Union/any type return ??
    return value;
}

//might be GCL_NextStr
int GCL_GetNextInt_800209E8(unsigned char* pScript)
{
    int code;
    int value;  
    pScript_800AB9A0 = GCL_GetNextValue_8002069C(pScript, &code, &value);
    return value;
}

int GCL_ReadVector_80020A14(unsigned char* pInScript, short* pOut3Words)
{
    int counter = 0;
    unsigned short* pOutIter = pOut3Words;
    unsigned char* pScript = pInScript;
    do
    {
        int code;
        int value;
        pScript = GCL_GetNextValue_8002069C(pScript, &code, &value);
        counter++;
        *pOutIter = value;
        pOutIter++;
    } while (counter < 3);

    pScript_800AB9A0 = pScript;
    return 0;
}

char *GCL_Read_String_80020A70( char *ptr )
{
	int type;
	int value;

	ptr = GCL_GetNextValue_8002069C( ptr, &type, &value );
	pScript_800AB9A0 = ptr;
	
	if ( ptr )
	{
		return ( char * )value;
	}
	else
	{
		return 0;
	}
}

unsigned char *GCL_Get_Param_Result_80020AA4( void )
{
	if ( !*pScript_800AB9A0 || GCL_IsParam( *pScript_800AB9A0 ) )
	{
		return 0;
	}

	return pScript_800AB9A0;
}

int GCL_GetNextParamValue_80020AD4(void)
{
    return GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
}

void GCL_ReadParamVector_80020AFC(short *pOut3Words)
{
	GCL_ReadVector_80020A14(GCL_Get_Param_Result_80020AA4(), pOut3Words);
	return;
}

void GCL_80020B2C(unsigned char *pScript)
{
	int	code;
	int value;
  
	do {
		pScript = GCL_GetNextValue_8002069C(pScript, &code, &value);
	} while (code != GCLCODE_NULL);
	return;
}

void GCL_ParseInit_80020B68( void )
{
    GCL_InitArgStack_80020868();
    GCL_InitCommandLineBuffer_80020920();
    return;
}
