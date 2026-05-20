#include "libgcl.h"
#include "common.h"
#include "strcode.h"

static int GCL_Command_if( char *top )
{
    int type, res;
    char *p, *block;

    p = top;

EXEC_IF:
    p = GCL_GetNextValue( p, &type, &res );

EXEC_ELSE:
    p = GCL_GetNextValue( p, &type, (int *)&block );

    if ( res )
    {
        GCL_ExecBlock( block, NULL );
    }
    else
    {
        p = GCL_GetNextValue( p, &type, &res );
        if ( p != NULL )
        {
            type >>= 16;
            p = (char *)res;

            if ( type == 'e' )
            {
                res = 1;
                goto EXEC_ELSE;
            }
            else if ( type == 'i' )
            {
                goto EXEC_IF;
            }
        }
    }

    return GCL_OK;
}

static int GCL_Command_eval( char *top )
{
    int type, res;

    GCL_GetNextValue( top, &type, &res );

    return GCL_OK;
}

static int GCL_Command_foreach( char *top )
{
    long argbuf[ GCL_PROC_MAX_ARGS ];
    int i, type, value;
    GCL_ARGS arg;
    long *p;
    char *block;

    p = argbuf;
    for ( ;; )
    {
        top = GCL_GetNextValue( top, &type, &value );
        if ( ( type & 0xFF ) == GCL_OPTION )
        {
            break;
        }
        *p++ = value;
    }

    top = GCL_GetNextValue( (char *)value, &type, &value );
    block = (char *)value; // "-do" parameter

    arg.argc = 1;
    arg.argv = argbuf;

    for ( i = p - argbuf; i > 0; i-- )
    {
        GCL_ExecBlock( block, &arg );
        arg.argv++;
    }

    return GCL_OK;
}

static int GCL_Command_return( char *top )
{
    return GCL_RETURN;
}

static GCL_COMMANDLIST commlist[] = {
    { 0x0d86, GCL_Command_if },         // GV_StrCode("if")
    { 0x64c0, GCL_Command_eval },       // GV_StrCode("eval")
    { 0xcd3a, GCL_Command_return },     // GV_StrCode("return")
    { 0x7636, GCL_Command_foreach },    // GV_StrCode("foreach")
};

static GCL_COMMANDDEF builtin_commands = GCL_COMMANDS( commlist );

void GCL_InitBasicCommands( void )
{
    GCL_AddCommMulti( &builtin_commands );
}
