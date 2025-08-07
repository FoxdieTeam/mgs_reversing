#ifndef __MGS_TAKABE_CINEMA_H__
#define __MGS_TAKABE_CINEMA_H__

void *NewCinemaScreen( int time, int event, int argc, char **argv );
void *NewCinemaScreenClose( void *addr );
void *NewCinemaScreenSet( int name, int where, int argc, char **argv );

#endif // __MGS_TAKABE_CINEMA_H__
