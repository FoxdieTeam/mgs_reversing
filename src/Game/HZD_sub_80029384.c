#include "libdg/libdg.h"

//probably uses inlines
int HZD_sub_80029384( VECTOR *a0 )
{
    int a2, a3, t0, v1;

    a2 = *( int * )0x1F80000C;
    t0 = a0[ 1 ].vx;
    v1 = a0[ 1 ].vz; 
    
    gte_ldsxy3( t0, v1, a2 );
    gte_nclip();
    a3 = a0[ 2 ].vx;
    gte_stopz( 0x1F800008 );

    if ( *( int * )0x1F800008 >= 0 )
    {
        
        gte_ldsxy3( v1, a3, a2 );
        gte_nclip();
        a0 = ( VECTOR* )a0[ 2 ].vz; //shouldn't really be a vector ptr, probably inline
        gte_stopz( 0x1F800008 );
        
        if ( *( int * )0x1F800008 < 0 ) return 0;

        gte_ldsxy3( a3, a0, a2 );
        gte_nclip();
        gte_stopz( 0x1F800008 );

        if ( *( int * )0x1F800008 < 0 ) return 0;

        gte_ldsxy3( a0, t0, a2 );
        gte_nclip();
        gte_stopz( 0x1F800008 );
        
        return *( int * )0x1F800008 >= 0;
    }
    else
    {
        gte_ldsxy3( v1, a3, a2 );
        gte_nclip();
        a0 = ( VECTOR* )a0[ 2 ].vz; //shouldn't really be a vector ptr, probably inline
        gte_stopz( 0x1F800008 );

        if (*( int * )0x1F800008 > 0 ) return 0;
       
        gte_ldsxy3( a3, a0, a2 ); 
        gte_nclip();       
        gte_stopz( 0x1F800008 );

        if (* ( int * )0x1F800008 > 0 ) return 0;

        gte_NormalClip( a0, t0, a2, 0x1F800008 );
        return *( int * )0x1F800008 <= 0;
    } 
    
}