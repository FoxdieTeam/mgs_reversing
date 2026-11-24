#ifndef __MGS_ONODA_SAFETY_H__
#define __MGS_ONODA_SAFETY_H__

int SafeCheck( int lba, int timeout );
void SafetyReset( void );
int NewSafetyCheck( void );

#endif // __MGS_ONODA_SAFETY_H__
