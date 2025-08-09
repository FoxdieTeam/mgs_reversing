#ifndef __MGS_TAKABE_CINEMA_H__
#define __MGS_TAKABE_CINEMA_H__

void *NewCinemaScreen( int time, int event );
void *NewCinemaScreenClose( void *addr );
void *NewCinemaScreenSet( int name, int where, int argc, char **argv );

#endif // __MGS_TAKABE_CINEMA_H__
