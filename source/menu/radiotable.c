#include <stdio.h>
#include <stddef.h>     // for NULL

typedef struct {
    int freq;
    int code;
} RADIO_ENTRY;

typedef struct {
    RADIO_ENTRY entries[ 8 ];
} RADIO_TABLE;

static RADIO_TABLE base_radio_table;
static RADIO_TABLE over_radio_table;

void MENU_InitRadioTable( void )
{
    int i;

    for ( i = 0; i < 8; i++ )
    {
        base_radio_table.entries[ i ].freq = 0;
        over_radio_table.entries[ i ].freq = 0;
    }
}

void MENU_ClearRadioTable( void )
{
    MENU_InitRadioTable();
}

static RADIO_ENTRY *FindEmpty( RADIO_TABLE *table, int freq )
{
    int empty, i;

    empty = -1;
    for ( i = 7; i >= 0; i-- )
    {
        if ( table->entries[ i ].freq == freq )
        {
            empty = i;
            break;
        }
        if ( table->entries[ i ].freq == 0 ) empty = i;
    }

    if ( empty < 0 )
    {
        printf( "RADIO CALL OVER!!\n" );
        return NULL;
    }

    return &table->entries[ empty ];
}

static void SetEntry( RADIO_TABLE *table, int freq, int code )
{
    RADIO_ENTRY *entry;

    entry = FindEmpty( table, freq );
    if ( entry == NULL ) return;

    if ( code >= 0 )
    {
        entry->freq = freq;
        entry->code = code;
    }
    else
    {
        entry->freq = 0;
        entry->code = 0;
    }
}

void MENU_SetRadioBaseCall( int freq, int code )
{
    SetEntry( &base_radio_table, freq, code );
}

void MENU_SetRadioOverCall( int freq, int code )
{
    SetEntry( &over_radio_table, freq, code );
}

int MENU_GetRadioCode( int freq )
{
    RADIO_ENTRY *entry;

    entry = FindEmpty( &over_radio_table, freq );
    if ( entry && entry->freq == freq ) return entry->code;

    entry = FindEmpty( &base_radio_table, freq );
    if ( entry && entry->freq == freq ) return entry->code;

    return -1;
}
