#include "libgcl.h"

#include <stdio.h>
#include "common.h"

/*** $gp ***/
int   *SECTION(".sbss") argstack_p;
char **SECTION(".sbss") commandline_p;
char  *SECTION(".sbss") next_str_ptr;

/*** bss ***/
extern int   argbuffer[32];
extern char *commandlines[8];

void GCL_SetArgTop( char *top )
{
    next_str_ptr = top;
}

char *GCL_GetNextValue( char *top, int *type_p, int *value_p )
{
    int type, size;
    unsigned char *p;

    p = (unsigned char *)top;
    type = *p;
    p++;

    if ( GCL_TAG( type ) == GCL_VAR )
    {
        return GCL_GetVar( top, type_p, value_p );
    }

    *type_p = type;

    switch ( type )
    {
    case GCL_END:
        p = NULL;
        break;
    case GCL_SHORT:
        *value_p = GCL_GetShort( p );
        p += 2;
        break;
    case GCL_INT:
    case GCL_SYMBOL:
        *value_p = GCL_GetLong( p );
        p += 4;
        break;
    case GCL_STRID:
    case GCL_PROCID:
        *value_p = (unsigned short)GCL_GetShort( p );
        p += 2;
        break;
    case GCL_BYTE:
    case GCL_CHAR:
    case GCL_BOOL:
        *value_p = (unsigned char)GCL_GetByte( p );
        p++;
        break;
    case GCL_STRING:
        *value_p = (int)( p + 1 );
        p += *p + 1;
        break;
    case GCL_ARRAY:
        *value_p = GCL_GetArgs( *p );
        *type_p = GCL_SHORT;
        p++;
        break;
    case GCL_ARG:
        *value_p = (int)( p + 2 );
        size = GCL_GetShort( p );
        p += size;
        break;
    case GCL_EXPR:
        *value_p = GCL_Expr( p + 1, value_p );
        p += *p;
        break;
    case GCL_OPTION:
        *type_p |= *p << 16;
        *value_p = (int)( p + 2 );
        p += p[ 1 ] + 1;
        break;
    default:
        printf( "GCL:WRONG CODE %x\n", type );
        break;
    }

    next_str_ptr = p;
    return p;
}

static void GCL_InitArgStack(void)
{
    argstack_p = argbuffer;
}

void *GCL_SetArgStack( GCL_ARGS *args )
{
    int *org, *argv;
    int i;

    if ( args == NULL )
    {
        return NULL;
    }

    org = argstack_p;
    argv = (int *)( args->argv + ( args->argc - 1 ) );

    for ( i = args->argc; i > 0; i-- )
    {
        *argstack_p++ = *argv--;
    }

    *argstack_p++ = args->argc;
    return org;
}

void GCL_UnsetArgStack( void *stack )
{
    if ( stack != NULL )
    {
        argstack_p = stack;
    }
}

int GCL_GetArgs( int argno )
{
    return argstack_p[ -( argno + 1 ) ];
}

static void GCL_InitCommandLineBuffer( void )
{
    commandline_p = commandlines;
}

void GCL_SetCommandLine( char *argtop )
{
    *commandline_p++ = argtop;
}

void GCL_UnsetCommandLine( void )
{
    commandline_p--;
}

char *GCL_GetOption( char c )
{
    char *p;

    p = commandline_p[ -1 ];

    for ( ;; )
    {
        int type, value;

        p = GCL_GetNextValue( p, &type, &value );
        if ( type == GCL_END ) return NULL;
        if ( ( type & 0xFF ) == GCL_OPTION )
        {
            if ( ( type >> 16 ) == c )
            {
                next_str_ptr = (char *)value;
                return (char *)value;
            }
        }
    }
}

int GCL_StrToInt( char *ptr )
{
    int type, value;

    next_str_ptr = GCL_GetNextValue( ptr, &type, &value );
    return value;
}

int GCL_StrToSV( char *ptr, short *vec )
{
    int i, type, value;

    for ( i = 0; i < 3; i++ )
    {
        ptr = GCL_GetNextValue( ptr, &type, &value );
        vec[ i ] = value;
    }

    next_str_ptr = ptr;
    return 0;
}

char *GCL_GetString( char *ptr )
{
    int type, value;

    if ( ( next_str_ptr = GCL_GetNextValue( ptr, &type, &value ) ) == NULL )
    {
        return NULL;
    }

    return (char *)value;
}

char *GCL_NextStr( void )
{
    if ( *next_str_ptr == GCL_END || *next_str_ptr == GCL_OPTION )
    {
        return NULL;
    }

    return next_str_ptr;
}

int GCL_GetNextInt( void )
{
    return GCL_StrToInt( GCL_NextStr() );
}

void GCL_GetNextSV( short *vec )
{
    GCL_StrToSV( GCL_NextStr(), vec );
}

void GCL_SkipCommand( char *ptr )
{
    for ( ;; )
    {
        int type, value;

        ptr = GCL_GetNextValue( ptr, &type, &value );
        if ( type == GCL_END ) break;
    }
}

void GCL_ParseInit( void )
{
    GCL_InitArgStack();
    GCL_InitCommandLineBuffer();
}
