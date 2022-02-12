#include <util/idaTypes.h>

// from leaked original MGS source code

void            GV_ZeroMemory_8001619C( to, size )
void            *to ;
int             size ;
{
        typedef struct  { long d0, d1, d2, d3 ; } Unit ;
        Unit            *u ;
        char            *c ;
        int             i ;

        c = (char *)to ;
        i = 3 & (long)to ;
        size -= i ;
        for ( ; i > 0 ; -- i ) {
                *( c ++ ) = 0 ;
        }
        u = (Unit *)c ;
        for ( i = size / sizeof( Unit ) ; i > 0 ; -- i ) {
                u->d0 = 0 ;
                u->d1 = 0 ;
                u->d2 = 0 ;
                u->d3 = 0 ;
                u ++ ;
        }
        c = (char *)u ;
        for ( i = ( sizeof( Unit ) - 1 ) & size ; i > 0 ; -- i ) {
                *( c ++ ) = 0 ;
        }
        
}
