#include "linker.h"
#include "menuman.h"

extern RadioMemory gRadioMemory_800BDB38[ RADIO_MEMORY_COUNT ];

RadioMemory       *menu_radio_table_find_8004D380( int frequency )
{
    RadioMemory *contact;
    int          i;

    contact = &gRadioMemory_800BDB38[ 0 ];
    for ( i = 0; i < RADIO_MEMORY_COUNT; i++ )
    {
        if ( contact->frequency == frequency )
        {
            return contact;
        }
        contact++;
    }
    return 0;
}

RadioMemory *menu_radio_table_next_free_8004D3B8( void )
{
    // Try to find a free entry
    return menu_radio_table_find_8004D380( 0 );
}

void menu_radio_compact_free_vars_8004D3D8( void )
{
    RadioMemory *contact, *next;
    int          i, j;

    contact = &gRadioMemory_800BDB38[ 0 ];
    for ( i = 0; i < RADIO_MEMORY_COUNT; i++, contact++ )
    {
        j = i + 1;
        if ( contact->frequency == 0 )
        {
            for ( next = contact + 1; j < RADIO_MEMORY_COUNT; j++, next++ )
            {
                if ( next->frequency != 0 )
                {
                    *contact = *next;
                    next->frequency = 0;
                    break;
                }
            }
            if ( j == RADIO_MEMORY_COUNT )
            {
                return;
            }
        }
    }
}