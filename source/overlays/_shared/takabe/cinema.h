#ifndef _CINEMA_H_
#define _CINEMA_H_

void *NewCinemaScreen( int time, int event, int argc, char **argv );
void *NewCinemaScreenClose( void *addr );
void *NewCinemaScreenSet( int name, int where, int argc, char **argv );

#endif // _CINEMA_H_
