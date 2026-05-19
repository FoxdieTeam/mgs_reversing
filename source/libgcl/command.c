#include "libgcl.h"

#include <stdio.h>
#include "common.h"
#include "game/game.h"

extern GCL_SCRIPT current_script;

STATIC GCL_COMMANDDEF *commdef = NULL;

/*---------------------------------------------------------------------------*/

int GCL_AddCommMulti( GCL_COMMANDDEF *def )
{
    def->next = commdef;
    commdef = def;

    return 0;
}

static GCL_COMMANDLIST *FindCommand( int id )
{
    GCL_COMMANDDEF *def;

    for ( def = commdef; def != NULL; def = def->next )
    {
        int i;
        GCL_COMMANDLIST *cl = def->commlist;

        for ( i = def->n_commlist; i > 0; i-- )
        {
            if ( cl->id == id ) return cl;
            cl++;
        }
    }

    printf( "command not found\n" );
    return NULL;
}

int GCL_Command( char *ptr )
{
    u_short id;
    GCL_COMMANDLIST *cl;
    int ret, ofs;

    id = GCL_GetShort( ptr );
    cl = FindCommand( id );
    ptr += sizeof(short);

    ofs = GCL_GetByte( ptr );
    GCL_SetCommandLine( ptr + ofs );
    ptr += sizeof(char);

    GCL_SetArgTop( ptr );

    ret = ( *cl->func )( ptr );

    GCL_UnsetCommandLine();

    return ret;
}

static char *set_proc_table( char *proc_table )
{
    GCL_PROC_TABLE *pt;

    pt = (GCL_PROC_TABLE *)proc_table;
    while ( *(int *)pt != 0 )
    {
        pt->proc_id = GCL_GetShort( (char *)&pt->proc_id );
        pt->offset = GCL_GetShort( (char *)&pt->offset );
        pt++;
    }

    return (char *)( pt + 1 );
}

static char *get_proc_block( int id )
{
    GCL_PROC_TABLE *pt;

    pt = (GCL_PROC_TABLE *)current_script.proc_table;
    while ( *(int *)pt != 0 )
    {
        if ( pt->proc_id == id ) return current_script.proc_body + pt->offset;
        pt++;
    }

    printf( "PROC %X NOT FOUND\n", id );
    return NULL;
}

void GCL_ForceExecProc( int proc_id, GCL_ARGS *arg )
{
    GCL_ExecBlock( get_proc_block( proc_id ) + 3, arg );
}

int GCL_ExecProc( int proc_id, GCL_ARGS *arg )
{
    if ( GM_LoadRequest != 0 || ( GM_PlayerStatus & PLAYER_GAME_OVER ) )
    {
        printf( "proc %d cancel\n", proc_id );
        return 0;
    }

    return GCL_ExecBlock( get_proc_block( proc_id ) + 3, arg );
}

static int GCL_Proc( char *p )
{
    long     argbuf[ GCL_MAX_ARGS ];
    int      i, id;
    GCL_ARGS arg;

    id = (unsigned short)GCL_GetShort( p );
    p += sizeof(short);

    for ( i = 0; ; i++ )
    {
        int type, value;

        p = GCL_GetNextValue( p, &type, &value );
        if ( type == GCL_END ) break;
        if ( i >= 8 )
        {
            printf( "TOO MANY ARGS PROC\n" );
        }
        argbuf[ i ] = value;
    }

    arg.argc = i;
    arg.argv = argbuf;

    GCL_ExecProc( id, &arg );
    return 0;
}

int GCL_LoadScript( char *datatop )
{
    char *proc, *script, *font;
    int proclen;

    proc = datatop + sizeof(int);
    proclen = GCL_GetLong( datatop );
    current_script.proc_table = proc;
    current_script.proc_body = set_proc_table( proc );

    script = current_script.proc_table + proclen;
    current_script.script_body = script + sizeof(int);

    font = current_script.script_body + GCL_GetLong( script );
    font_set_font_addr( 2, font + sizeof(int) );

    return 0;
}

int GCL_ExecBlock( char *top, GCL_ARGS *arg )
{
    int value[ 2 ];
    void *org_stack;

    org_stack = GCL_SetArgStack( arg );
    while ( top != NULL )
    {
        switch ( *top )
        {
        case GCL_EXPR:
            GCL_Expr( top + 2, value );
            top++;
            top += *top;
            break;
        case GCL_COMMAND:
            if (GCL_Command( top + 3 ) == GCL_RETURN)
            {
                return GCL_RETURN;
            }

            top++;
            top += GCL_GetShort( top );
            break;
        case GCL_PROC:
            GCL_Proc( top + 2 );
            top++;
            top += *top;
            break;
        case GCL_END:
            GCL_UnsetArgStack( org_stack );
            return 0;
        default:
            printf( "SCRIPT COMMAND ERROR %x\n", *top );
        }
    }

    printf( "ERROR in script\n" );
    return 1;
}

GCL_ARGS gcl_null_args = {};

void GCL_ExecScript( void )
{
    unsigned char *datatop;

    datatop = (unsigned char *)current_script.script_body;
    if ( *datatop != GCL_ARG )
    {
        printf( "NOT SCRIPT DATA !!\n" );
    }

    GCL_ExecBlock( datatop + 3, &gcl_null_args );
}
