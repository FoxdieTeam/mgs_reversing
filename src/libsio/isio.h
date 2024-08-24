/*
 * ref."beatmania APPEND 5thMIX"
 *  work.5th/include/isio.h (Apr.06,1998)
 */
#ifndef __ISIO_H__
#define __ISIO_H__

extern void             sio_output_start_8008C5A8(void);
extern void             sio_output_stop_8008C5B0(void);

extern void             sio_putchar_8008C5E0(unsigned char);
extern unsigned char    sio_getchar_8008C5E8(void);
extern int              sio_getchar2_8008C5D0(void);
//extern int            sio_chkbuf(void);
//extern void           sio_flush(void);
extern void             sio_puts_8008C5F0(unsigned char *);
extern int              sio_setup_8008C5F8(int);
extern void             sio_dump_8008C600(unsigned char *, unsigned long);
//extern int            sio_get_dsr(void);
//extern int            sio_get_cts(void);

#endif
