/*
 * ref."beatmania APPEND 5thMIX"
 *  work.5th/include/isio.h (Apr.06,1998)
 */
#ifndef __ISIO_H__
#define __ISIO_H__

extern void             sio_output_start(void);
extern void             sio_output_stop(void);

extern void             sio_putchar(unsigned char);
extern unsigned char    sio_getchar(void);
extern int              sio_getchar2(void);
//extern int            sio_chkbuf(void);
//extern void           sio_flush(void);
extern void             sio_puts(unsigned char *);
extern int              sio_setup(int);
extern void             sio_dump(unsigned char *, unsigned long);
//extern int            sio_get_dsr(void);
//extern int            sio_get_cts(void);

#endif
