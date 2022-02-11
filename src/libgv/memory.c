typedef struct _gv_mem_unknown {
    void* field_00;
    void* field_04;
    void* field_08;
    void* field_0C;
} GV_MEM_UNKNOWN;

//todo: return to clean this up when we understand more of 
//how the memory system works
void* System_FindAlloc_80015758(GV_MEM_UNKNOWN* a0, void* a1)
{
    void    *addr ;
    int      i ;

    if ( a1 < a0->field_04 || a1 >= a0->field_08) return 0 ;

    i = (int)a0->field_0C ;
    a0 ++ ;

    while (i >= 2)
    {
        addr = &((long long*)a0)[ i / 2 ] ;

        if (a1 == (void*)(*(long*)addr)) return addr ;

        if ((void*)(*(long*)addr) < a1)
        {
            i--;
            a0 = addr + 8;
        }

        i /=  2;
    }

    if ( i <= 0 || a0->field_00 != a1) return 0;

    return a0;
}

void* sub_80015818(GV_MEM_UNKNOWN* a0, int a1)
{
    int i, j, k;
    GV_MEM_UNKNOWN* next;

    j = (int)a0[1].field_00;
    next = &a0[1];

    for ( i = (int)a0->field_0C ; i > 0 ; --i )
    {
        k = (int)next->field_08;
        j = k - j;

        if (j >= a1)
        {
            if (!next->field_04) return next;
        }
        j = k;
        a0 = (void*)a0 + 8;
        next = (void*)next + 8;
    }
    return 0;
}

//GV_JoinMemory?
void sub_80015874( int which, void* addr )
{
    typedef	struct	{ long d0, d1 ; } Unit ;

    int     i, x ; 
    int     size ;
    Unit*   next ;
    Unit*   u  ; 
    Unit*   u2 ;

    u  = (Unit* )which;
    u2 = (Unit* )addr;

    x = u[1].d1;
    next  = &u[x + 2] ;

    size = 2;
    size = ( ( (int) (&u2[-size]) ) - which ) >> 3;	

    for ( i = x - size ; i > -1 ; --i )
    {
        next[1] = next[0];
        next--;
    }

    u[1].d1++;
}

void *GV_SplitMemory_800158C8( int which, void *addr, int size )
{
    typedef	struct	{ long d0, d1 ; } Unit ;

    int     i ; 
    int     temp ;
    Unit*   next ;
    Unit*   u ; 
    Unit*   u2 ;

    u    = (Unit *)which ;
    u2   = (Unit* )addr ;

    next = &u2[ size ] ;

    temp = (int )&u2[-2] ;
    temp = temp - which ;
    temp = temp >> 3 ;

    i = u[1].d1 ;
    i = i - temp ;

    for ( i = i - size ; i > -1 ; --i )
    {
        *u2 = *next ;
        u2++ ;
        next++ ;
    }

    u[1].d1 -= size ;
    return (void* )u[1].d1;
}