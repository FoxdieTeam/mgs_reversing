#include "linker.h"

short        SECTION( ".sbss" ) GM_RadarMode_800ABA80; // GM_RadarMode_800ABA80
extern short GM_RadarMode_800ABA80;                    // 79c
int          SECTION( ".sbss" ) dword_800ABA70;
extern int   dword_800ABA70; // 78c
int          SECTION( ".sbss" ) dword_800ABA78[2];
extern int   dword_800ABA78[2]; // 794

extern int   GM_GameStatus_800AB3CC;
extern int   GM_AlertMode_800ABA00;
extern int   GM_AlertLevel_800ABA18;

void         GM_Sound_80032968( int byte_2, int byte_1, int byte_0 );
void         GM_Sound_80032C48( int code, int notUsed );
void         sub_8002E508( int a1 );

typedef enum
{
	RADAR_VISIBLE = 0,
	RADAR_JAMMED = 1,
	RADAR_EVASION = 2,
	RADAR_ALERT = 3
} RadarMode;

typedef enum
{
	ALERT_DISABLED = 0,
	ALERT_ENABLED = 1,
	ALERT_EVASION = 2 // > 2 = ALERT_EVASION
} AlertMode;

void GM_AlertAct_8002E91C( void )
{
	if ( !( GM_GameStatus_800AB3CC & 0x04000000 ) )
	{
		if ( GM_RadarMode_800ABA80 >= 0 )
		{
			if ( GM_RadarMode_800ABA80 != GM_AlertMode_800ABA00 )
			{
				if ( dword_800ABA70 == 0 )
				{
					switch ( GM_RadarMode_800ABA80 )
					{
					case RADAR_ALERT:
						if ( GM_AlertMode_800ABA00 == ALERT_DISABLED )
						{
							GM_Sound_80032968( 0, 0x3F, 0x2A );
							GM_Sound_80032C48( 0x01FFFF0B, 0 );
							sub_8002E508( dword_800ABA78[1] );
						}
						else if ( GM_AlertMode_800ABA00 == ALERT_EVASION )
						{
							GM_Sound_80032C48( 0x01FFFF03, 0 );
						}
						break;
					case RADAR_EVASION:
						GM_Sound_80032C48( 0x01FFFF10, 0 );
						break;
					case RADAR_VISIBLE:
						sub_8002E508( dword_800ABA78[0] );
						break;
					}
				}
				GM_AlertMode_800ABA00 = GM_RadarMode_800ABA80;
			}
		}
		if ( ( GM_AlertMode_800ABA00 == ALERT_EVASION ) && ( dword_800ABA70 == 0 ) &&
			 ( GM_AlertLevel_800ABA18 == 0x3C ) )
		{
			GM_Sound_80032C48( 0x01FFFF08, 0 );
		}
		GM_RadarMode_800ABA80 = -1;
	}
}
