	opt	c+, at+, e+, n-

	section	.RDATA










    xdef aTlbl
    xdef aSending
    xdef aReceiving
    xdef aReady
    xdef aSleeping
    xdef aWaitvbl
    xdef aPending
    xdef aCdlsync
    xdef aCdlnop
    xdef aCdlsetloc
    xdef aCdlplay
    xdef aCdlforward
    xdef aCdlbackward
    xdef aCdlreadn
    xdef aCdlstandby
    xdef aCdlstop
    xdef aCdlpause
    xdef aCdlreset
    xdef aCdlmute
    xdef aCdldemute
    xdef dword_800141CC
    xdef dword_800141CC
    xdef dword_800141CC
    xdef aCdlgetlocl
    xdef aCdlgetlocp
    xdef dword_800141CC
    xdef aCdlgettn
    xdef aCdlgettd
    xdef aCdlseekl
    xdef aCdlseekp
    xdef dword_800141CC
    xdef dword_800141CC
    xdef dword_800141CC
    xdef dword_800141CC
    xdef aCdlreads
    xdef dword_800141CC
    xdef dword_800141CC
    xdef dword_800141CC
    xdef dword_800141CC
    xdef aNointr
    xdef aDataready
    xdef aComplete_0
    xdef aAcknowledge
    xdef aDataend
    xdef aDiskerror_0
    xdef dword_800141CC
    xdef dword_800141CC
    xdef aIdBiosCV186199
    xdef aIdSysCV1140199
    xdef aIdIntrCV175199


































aSoundStreaming:db "", 0xA              ; DATA XREF: sub_800827AC+880?o
                db "SOUND STREAMING ERROR:NO LAST LEFT DATA", 0xA, 0x0
                dh 0
aStrUnplaySizeX:db "str_unplay_size=%x", 0xA, 0x0
                                         ; DATA XREF: sub_800827AC+898?o
asc_800137E0:   db "*", 0x0            ; DATA XREF: sub_800827AC:loc_800830D8?o
                dh 0
jpt_80082820:   dw 0x80082828         ; DATA XREF: sub_800827AC+64?r
                dw 0x80082A28         ; jump table for switch statement
                dw 0x80082BC8
                dw 0x80082D20
                dw 0x800832BC
                dw 0x80083358
aErrorSeFileAlr:db "ERROR:SE File Already Opened.", 0xA, 0x0
                                         ; DATA XREF: sub_8008341C+14?o
                db 0
aLoadsefileFile:db "LoadSeFile:File Open Error(%x)", 0xA, 0x0
                                         ; DATA XREF: sub_8008341C+9C?o
aErrorWaveFileA:db "ERROR:Wave File Already Opened.", 0xA, 0x0
                                         ; DATA XREF: TEXT:8008351C?o
                db 0, 0, 0
aLoadwavefileFi:db "LoadWaveFile:File Open Error(%x)", 0xA, 0x0
                                         ; DATA XREF: TEXT:8008356C?o
                dh 0
aSupOffsetXSize:db "SUP OFFSET=%x:SIZE=%x", 0xA, 0x0
                                         ; DATA XREF: TEXT:800835C0?o
                db 0
aSrcXDstX:      db "    SRC=%x:DST=%x", 0xA, 0x0
                                         ; DATA XREF: TEXT:80083664?o
                db 0
aBinOffsetX:    db "BIN OFFSET=%x", 0xA, 0x0
                                         ; DATA XREF: TEXT:80083734?o
                db 0
aSpuOffsetXSize:db "SPU OFFSET=%x:SIZE=%x", 0xA, 0x0
                                         ; DATA XREF: TEXT:80083760?o
                db 0
aCompleteLoadSe:db "Complete Load Se:%x", 0xA, 0x0
                                         ; DATA XREF: TEXT:80083900?o
                db 0, 0, 0
aSdSngdataloadi:db "SD_SngDataLoadInit", 0xA, 0x0
                                         ; DATA XREF: sub_80083E8C+20?o
aLoadinitD:     db "LoadInit %d", 0xA, 0x0
                                         ; DATA XREF: sub_80083F08+14?o
                db 0, 0, 0
asc_80013914:   db "$", 0x0            ; DATA XREF: sub_80083F54+1F4?o
                dh 0
aSdWavLoadBufOv:db "!!! SD WAV LOAD BUF OVER !!!", 0xA, 0x0
                                         ; DATA XREF: sub_800841D4+DC?o
                dh 0
aUnloadD:       db "unload %d", 0xA, 0x0  ; DATA XREF: sub_800843BC+B8?o
                db 0
aSngcodeX:      db "SngCode=%x", 0xA, 0x0
                                         ; DATA XREF: sub_80084494+34?o
aSongpauseon:   db "SongPauseOn", 0xA, 0x0
                                         ; DATA XREF: sub_80084494+15C?o
                db 0, 0, 0
aSongpauseoff:  db "SongPauseOff", 0xA, 0x0
                                         ; DATA XREF: sub_80084494+184?o
                dh 0
aSongfadein:    db "SongFadein", 0xA, 0x0
                                         ; DATA XREF: sub_80084494:loc_80084688?o
aSongfadeoutPau:db "SongFadeout&Pause", 0xA, 0x0
                                         ; DATA XREF: sub_80084494+214?o
                db 0
aSongfadeoutSto:db "SongFadeout&Stop", 0xA, 0x0
                                         ; DATA XREF: sub_80084494+234?o
                dh 0
aSongkaihimode: db "SongKaihiMode", 0xA, 0x0
                                         ; DATA XREF: sub_80084494+254?o
                db 0
aSongsyukanmode:db "SongSyukanMode On", 0xA, 0x0
                                         ; DATA XREF: sub_80084494+274?o
                db 0
aSongsyukanmode_0:db "SongSyukanMode Off", 0xA, 0x0
                                         ; DATA XREF: sub_80084494+294?o
aSongstop:      db "SongStop", 0xA, 0x0   ; DATA XREF: sub_80084494+2BC?o
                dh 0
aErrorSngPlayCo:db "ERROR:SNG PLAY CODE(%x/%x)", 0xA, 0x0
                                         ; DATA XREF: sub_80084494+320?o
aSngStatusX:    db "sng_status=%x", 0xA, 0x0
                                         ; DATA XREF: sub_80084494:loc_80084854?o
                db 0
aSamesonghasalr:db "SameSongHasAlreadyPlayed", 0xA, 0x0
                                         ; DATA XREF: sub_80084494:loc_8008486C?o
                dh 0
aSoundWorkIsBro:db "*** SOUND WORK IS BROKEN !!! ***", 0xA, 0x0
                                         ; DATA XREF: sub_80084494+4DC?o
                dh 0
aSongEndXX:     db "*** song_end:%x -> %x        ***", 0xA, 0x0
                                         ; DATA XREF: sub_80084494+4F4?o
                dh 0
aSngFadeoutStar:db "SNG FADEOUT START(status=%x)", 0xA, 0x0
                                         ; DATA XREF: sub_80084E48+E0?o
                dh 0
aSngFadeoutCanc:db "SNG FADEOUT CANCELED(status=%x)", 0xA, 0x0
                                         ; DATA XREF: sub_80084E48+11C?o
                db 0, 0, 0
aLoadsngdataFil:db "LoadSngData:File Open Error(%x)", 0xA, 0x0
                                         ; DATA XREF: sub_800854F0+78?o
                db 0, 0, 0
aCompletedloads:db "CompletedLoadSong(%x)", 0xA, 0x0
                                         ; DATA XREF: sub_800854F0+50?o
                db 0
aXaSoundStart:  db "***XA Sound Start***", 0xA, 0x0
                                         ; DATA XREF: TEXT:80088894?o
                dh 0
aXaSoundStop:   db "***XA Sound Stop***", 0xA, 0x0
                                         ; DATA XREF: TEXT:800888D8?o
                db 0, 0, 0
aSdcodeX:       db "SdCode=%x", 0xA, 0x0  ; DATA XREF: sub_80088CB0+1C?o
                                         ; sub_80088CB0+B8?o
                db 0
aToomuchbgmsoun:db "***TooMuchBGMSoundCode(%x)***", 0xA, 0x0
                                         ; DATA XREF: sub_80088CB0:loc_80088D50?o
                db 0
aSdsetLastStrea:db "SdSet:Last Stream Not Terminated.(status=%x)", 0xA, 0x0
                                         ; DATA XREF: sub_80088CB0+1B8?o
                dh 0
aSdsetSameStrea:db "SdSet:Same Stream is Already Played.(code=%x)", 0xA, 0x0
                                         ; DATA XREF: sub_80088CB0:loc_80088E80?o
                db 0
aStrFoS:        db "*** STR FO(S) ***", 0xA, 0x0
                                         ; DATA XREF: sub_80088CB0+3AC?o
                db 0
aStrFoM:        db "*** STR FO(M) ***", 0xA, 0x0
                                         ; DATA XREF: sub_80088CB0+3CC?o
                db 0
aStrFoL:        db "*** STR FO(L) ***", 0xA, 0x0
                                         ; DATA XREF: sub_80088CB0+3EC?o
                db 0
aStrFoLl:       db "*** STR FO(LL) ***", 0xA, 0x0
                                         ; DATA XREF: sub_80088CB0+40C?o
aStrFiMAtNextSt:db "*** STR FI(M) at Next STR ***", 0xA, 0x0
                                         ; DATA XREF: sub_80088CB0+458?o
                db 0
aStrFiMStart:   db "*** STR FI(M) Start ***", 0xA, 0x0
                                         ; DATA XREF: sub_80088CB0+478?o
                db 0, 0, 0
aErrStrFiM:     db "*** ERR:STR FI(M) ***", 0xA, 0x0
                                         ; DATA XREF: sub_80088CB0:loc_80089140?o
                db 0
aStrFiLAtNextSt:db "*** STR FI(L) at Next STR***", 0xA, 0x0
                                         ; DATA XREF: sub_80088CB0+4DC?o
                dh 0
aStrFiLStart:   db "*** STR FI(L) Start ***", 0xA, 0x0
                                         ; DATA XREF: sub_80088CB0+4FC?o
                db 0, 0, 0
aErrStrFiL:     db "*** ERR:STR FI(L) ***", 0xA, 0x0
                                         ; DATA XREF: sub_80088CB0:loc_800891C4?o
                db 0
aStrFoSStop:    db "*** STR FO(S)+STOP ***", 0xA, 0x0
                                         ; DATA XREF: sub_80088CB0+534?o
aStrFoMStop:    db "*** STR FO(M)+STOP ***", 0xA, 0x0
                                         ; DATA XREF: sub_80088CB0+554?o
aStrFoLStop:    db "*** STR FO(L)+STOP ***", 0xA, 0x0
                                         ; DATA XREF: sub_80088CB0+574?o
aStrFoLlStop:   db "*** STR FO(LL)+STOP ***", 0xA, 0x0
                                         ; DATA XREF: sub_80088CB0+594?o
                db 0, 0, 0
dword_80013D10: dw 0x3F3F3F, 0xDDA1AAA5, 0xDDA1D0A5, 0xEDA5D5A5, 0xDDA1
                dw 0xD7A5B3A5, 0xEDA5, 0xF3CCBDCD, 0xE1CEBFCC, 0
                dw 0xECA5D6A5, 0xAFA5DDA1, 0xA4A5DDA5, 0xC8A5F3A5, 0
dword_80013D4C: dw 0xB9A5B7A5, 0xE0A5C6A5, 0xDDA1B3A5, 0xEBA5, 0xDDA1C7A5
                dw 0xD0A5BFA5, 0xA8A5B9A5, 0xDDA1E9A5, 0
dword_80013D70: dw 0xE1CEBFCC, 0xB9A5D0A5, 0xE9A5A8A5, 0xDDA1, 0xC8A5B9A5
                dw 0xFEBBA2A5, 0xC9A5A2A5, 0xB9A5ECA5, 0xE9A5A8A5, 0xDDA1
                dw 0xDDA1EDA5, 0xFEBBC9A5, 0xC9A5A2A5, 0xB9A5ECA5, 0xE9A5A8A5
                dw 0xDDA1, 0x53424C54, 0
aTlbl:          db "TLBL", 0x0         ; DATA XREF: TEXT:800A3D30?o
                db 0, 0, 0
dword_80013DC0: dw 0x646F4D, 0xF4C9B0B3, 0xEAA4E4B3, 0xDFA4FEB9, 0
aTaskStartDX:   db "TASK START: %d %X", 0xA, 0x0
                                         ; DATA XREF: sub_8008BBC8+2C?o
                db 0
aAssertionFaled:db "assertion faled : %s line %d : Task %d", 0xA, 0x0
                                         ; DATA XREF: sub_800892B8+80?o
                                         ; sub_800895F4+34?o ...
aMtsNewC:       db "mts_new.c", 0x0    ; DATA XREF: sub_800892B8+88?o
                                         ; sub_800895F4+3C?o ...
                dh 0
aTaskStartBody: db "task_start_body", 0x0
                                         ; DATA XREF: sub_8008BBC8+8C?o
asc_80013E2C:   db "", 0xA, 0x0           ; DATA XREF: sub_800892B8+B0?o
                                         ; sub_800895F4+64?o ...
                dh 0
aGetNewVblContr:db "get_new_vbl_control_table", 0x0
                                         ; DATA XREF: sub_800892B8+A0?o
                dh 0
aWaitvblD:      db "waitvbl %d", 0x0   ; DATA XREF: sub_800895F4+54?o
                db 0
aTaskCreateXX:  db "task_create %x %x", 0x0
                                         ; DATA XREF: sub_8008AAEC+184?o
                                         ; sub_8008AAEC+28C?o ...
                dh 0
aSendDstD:      db "send dst %d", 0x0  ; DATA XREF: sub_8008982C+4C?o
aSendStateDeadD:db "send state DEAD %d", 0x0
                                         ; DATA XREF: sub_8008982C+B4?o
                db 0
aIsendDstD:     db "isend dst %d", 0x0
                                         ; DATA XREF: sub_80089B04+40?o
                db 0, 0, 0
aIsendStateDead:db "isend state DEAD %d", 0x0
                                         ; DATA XREF: sub_80089B04+A8?o
aRcvSrcD:       db "rcv src %d", 0x0   ; DATA XREF: sub_80089D24+70?o
                db 0
aRcvStateDeadD: db "rcv state DEAD %d", 0x0
                                         ; DATA XREF: sub_80089D24+D8?o
                dh 0
aRcvCallerD:    db "rcv caller %d", 0x0
                                         ; DATA XREF: sub_80089D24+220?o
                dh 0
aRcvSpDStateD:  db "rcv sp %d state %d", 0x0
                                         ; DATA XREF: sub_80089D24+290?o
                                         ; sub_80089D24+45C?o
                db 0
aRcvSpMessageX: db "rcv sp message %X", 0x0
                                         ; DATA XREF: sub_80089D24+2EC?o
                dh 0
aSendTD:        db "send t %d", 0x0    ; DATA XREF: sub_80089D24+3D4?o
                dh 0
aRcvSpDMessageX:db "rcv sp %d message %x", 0x0
                                         ; DATA XREF: sub_80089D24+4B8?o
                db 0, 0, 0
aRecvSrcD:      db "RECV ?? SRC %d", 0x0
                                         ; DATA XREF: sub_80089D24+670?o
                db 0
aWupDeadD:      db "wup DEAD %d", 0x0  ; DATA XREF: sub_8008A540+54?o
aMultiTaskSched:db "Multi Task Scheduler for PSX ver2.02 %s %s", 0xA, 0x0
                                         ; DATA XREF: sub_8008AAEC+48?o
aJul111998:     db "Jul 11 1998", 0x0  ; DATA XREF: sub_8008AAEC+50?o
a221633:        db "22:16:33", 0x0     ; DATA XREF: sub_8008AAEC+58?o
                db 0, 0, 0
aProgramBottomX:db "PROGRAM BOTTOM %X", 0xA, 0x0
                                         ; DATA XREF: sub_8008AAEC+70?o
                db 0
aBootTasknrD:   db "boot tasknr %d", 0x0
                                         ; DATA XREF: sub_8008AAEC+364?o
                db 0
aSystemClientD: db "system client %d", 0x0
                                         ; DATA XREF: sub_8008B0A4+74?o
                db 0, 0, 0
aTaskDStart:    db "TASK %d START:", 0x0
                                         ; DATA XREF: sub_8008B0A4:loc_8008B160?o
                db 0
aTaskDAlreadyEx:db "TASK %d already exist", 0xA, 0x0
                                         ; DATA XREF: sub_8008B0A4+1C8?o
                db 0
aSystemExitDead:db "system exit DEAD %d", 0x0
                                         ; DATA XREF: sub_8008B0A4+234?o
aSystemExitCall:db "system exit caller %d", 0x0
                                         ; DATA XREF: sub_8008B0A4+2A0?o
                dh 0
aTaskExit:      db "TASK EXIT", 0x0    ; DATA XREF: sub_8008B0A4:loc_8008B36C?o
                dh 0
aSystemWrongCod:db "system wrong code %d", 0x0
                                         ; DATA XREF: sub_8008B0A4+368?o
                db 0, 0, 0
aMtsStaTskServe:db "mts_sta_tsk server %d", 0x0
                                         ; DATA XREF: sub_8008B47C+60?o
                dh 0
aMtsExtTsk:     db "mts_ext_tsk", 0x0  ; DATA XREF: sub_8008B51C+3C?o
aPending:       db "Pending", 0x0      ; DATA XREF: TEXT:800A3DAC?o
aWaitvbl:       db "WaitVBL", 0x0      ; DATA XREF: TEXT:800A3DA8?o
aSleeping:      db "Sleeping", 0x0     ; DATA XREF: TEXT:800A3DA4?o
                db 0, 0, 0
aReady:         db "Ready", 0x0        ; DATA XREF: TEXT:800A3DA0?o
                dh 0
aReceiving:     db "Receiving", 0x0    ; DATA XREF: TEXT:800A3D9C?o
                dh 0
aSending:       db "Sending", 0x0      ; DATA XREF: TEXT:800A3D98?o
aProcessList:   db "", 0xA              ; DATA XREF: sub_8008B77C+4?o
                db "Process list", 0xA, 0x0
                db 0
aC:             db "%c", 0x0           ; DATA XREF: sub_8008B77C+30?o
                db 0
aTask02dSp04dUs:db "Task %02d SP %04d USE %04d/%04d", 0x0
                                         ; DATA XREF: sub_8008B77C:loc_8008B884?o
aTask02dSpUse:  db " Task %02d SP ---- USE ----/----", 0x0
                                         ; DATA XREF: sub_8008B77C:loc_8008B8CC?o
                db 0, 0, 0
dword_800140F0: dw 0x732520           ; DATA XREF: sub_8008B77C+40?o
aRunning:       db "Running", 0x0      ; DATA XREF: sub_8008B77C:loc_8008B910?o
aD_0:           db " %d", 0xA, 0x0        ; DATA XREF: sub_8008B77C:loc_8008B974?o
                db 0, 0, 0
aTaskState08x:  db "TASK STATE = %08X", 0xA, 0x0
                                         ; DATA XREF: sub_8008B77C+23C?o
                db 0
aVblWaitCue:    db "VBL wait cue", 0x0
                                         ; DATA XREF: sub_8008B77C+260?o
                db 0, 0, 0
a02dD:          db " : %02d (%d)", 0x0
                                         ; DATA XREF: sub_8008B77C+278?o
                db 0, 0, 0
aTickCountD:    db "Tick count %d", 0xA
                                         ; DATA XREF: sub_8008B77C+2B0?o
                db "", 0xA, 0x0
aCdinitInitFail:db "CdInit: Init failed", 0xA, 0x0
                                         ; DATA XREF: CdInit+78?o
                db 0, 0, 0
                dw 0, 0
aNone_0:        db "none", 0x0         ; DATA XREF: TEXT:loc_8008C858?o
                                         ; TEXT:loc_8008C88C?o
                db 0, 0, 0
                dw 0, 0
aCdlreads:      db "CdlReadS", 0x0     ; DATA XREF: TEXT:800A3EF8?o
                db 0, 0, 0
aCdlseekp:      db "CdlSeekP", 0x0     ; DATA XREF: TEXT:800A3EE4?o
                db 0, 0, 0
aCdlseekl:      db "CdlSeekL", 0x0     ; DATA XREF: TEXT:800A3EE0?o
                db 0, 0, 0
aCdlgettd:      db "CdlGetTD", 0x0     ; DATA XREF: TEXT:800A3EDC?o
                db 0, 0, 0
aCdlgettn:      db "CdlGetTN", 0x0     ; DATA XREF: TEXT:800A3ED8?o
                db 0, 0, 0
aCdlgetlocp:    db "CdlGetlocP", 0x0   ; DATA XREF: TEXT:800A3ED0?o
                db 0
aCdlgetlocl:    db "CdlGetlocL", 0x0   ; DATA XREF: TEXT:800A3ECC?o
                db 0
dword_800141CC: dw 0x3F, 0x536C6443, 0x6F6D7465, 0x6564, 0x536C6443
                                         ; DATA XREF: TEXT:800A3EC8?o
                                         ; TEXT:800A3ED4?o ...
                dw 0x69667465, 0x7265746C, 0
aCdldemute:     db "CdlDemute", 0x0    ; DATA XREF: TEXT:800A3EBC?o
                dh 0
aCdlmute:       db "CdlMute", 0x0      ; DATA XREF: TEXT:800A3EB8?o
aCdlreset:      db "CdlReset", 0x0     ; DATA XREF: TEXT:800A3EB4?o
                db 0, 0, 0
aCdlpause:      db "CdlPause", 0x0     ; DATA XREF: TEXT:800A3EB0?o
                db 0, 0, 0
aCdlstop:       db "CdlStop", 0x0      ; DATA XREF: TEXT:800A3EAC?o
aCdlstandby:    db "CdlStandby", 0x0   ; DATA XREF: TEXT:800A3EA8?o
                db 0
aCdlreadn:      db "CdlReadN", 0x0     ; DATA XREF: TEXT:800A3EA4?o
                db 0, 0, 0
aCdlbackward:   db "CdlBackward", 0x0  ; DATA XREF: TEXT:800A3EA0?o
aCdlforward:    db "CdlForward", 0x0   ; DATA XREF: TEXT:800A3E9C?o
                db 0
aCdlplay:       db "CdlPlay", 0x0      ; DATA XREF: TEXT:800A3E98?o
aCdlsetloc:     db "CdlSetloc", 0x0    ; DATA XREF: TEXT:800A3E94?o
                dh 0
aCdlnop:        db "CdlNop", 0x0       ; DATA XREF: TEXT:800A3E90?o
                db 0
aCdlsync:       db "CdlSync", 0x0      ; DATA XREF: TEXT:off_800A3E8C?o
aDiskerror_0:   db "DiskError", 0x0    ; DATA XREF: TEXT:800A3F20?o
                dh 0
aDataend:       db "DataEnd", 0x0      ; DATA XREF: TEXT:800A3F1C?o
aAcknowledge:   db "Acknowledge", 0x0  ; DATA XREF: TEXT:800A3F18?o
aComplete_0:    db "Complete", 0x0     ; DATA XREF: TEXT:800A3F14?o
                db 0, 0, 0
aDataready:     db "DataReady", 0x0    ; DATA XREF: TEXT:800A3F10?o
                dh 0
aNointr:        db "NoIntr", 0x0       ; DATA XREF: TEXT:off_800A3F0C?o
                db 0
aCdTimeout:     db "CD timeout: ", 0x0
                                         ; DATA XREF: CD_sync+D4?o
                                         ; CD_ready+D4?o ...
                db 0, 0, 0
aSSSyncSReadyS: db "%s:(%s) Sync=%s, Ready=%s", 0xA, 0x0
                                         ; DATA XREF: CD_sync+120?o
                                         ; CD_ready+120?o ...
                db 0
aDiskerror:     db "DiskError: ", 0x0  ; DATA XREF: sub_8008CEE8+1E0?o
aComSCode02x02x:db "com=%s,code=(%02x:%02x)", 0xA, 0x0
                                         ; DATA XREF: sub_8008CEE8+228?o
                db 0, 0, 0
aCdromUnknownIn:db "CDROM: unknown intr", 0x0
                                         ; DATA XREF: sub_8008CEE8+530?o
aD_1:           db "(%d)", 0xA, 0x0       ; DATA XREF: sub_8008CEE8+540?o
                dh 0
                dw 0
jpt_8008D13C:   dw 0x8008D290         ; DATA XREF: sub_8008CEE8+244?r
                dw 0x8008D244         ; jump table for switch statement
                dw 0x8008D144
                dw 0x8008D310
                dw 0x8008D390
aCdSync:        db "CD_sync", 0x0      ; DATA XREF: CD_sync+68?o
aCdReady:       db "CD_ready", 0x0     ; DATA XREF: CD_ready+68?o
                db 0, 0, 0
aS:             db "%s...", 0xA, 0x0      ; DATA XREF: CD_cw+60?o
                db 0
aSNoParam:      db "%s: no param", 0xA, 0x0
                                         ; DATA XREF: CD_cw+B4?o
                dh 0
aCdCw:          db "CD_cw", 0x0        ; DATA XREF: CD_cw+1E4?o
                dh 0
aIdBiosCV186199:db "$Id: bios.c,v 1.86 1997/03/28 07:42:42 makoto Exp yos $", 0x0
                                         ; DATA XREF: TEXT:800A415C?o
aCdInit:        db "CD_init:", 0x0     ; DATA XREF: CD_init+4?o
                db 0, 0, 0
aAddr08x:       db "addr=%08x", 0xA, 0x0  ; DATA XREF: CD_init+18?o
                db 0
aCdDatasync:    db "CD_datasync", 0x0  ; DATA XREF: CD_datasync+50?o
                dw 0, 0, 0
a0123456789abcd:db "0123456789ABCDEF", 0x0
                                         ; DATA XREF: sprintf+598?o
                db 0, 0, 0
a0123456789abcd_0:db "0123456789abcdef", 0x0
                                         ; DATA XREF: sprintf:loc_8008EE14?o
                db 0, 0, 0
jpt_8008EB30:   dw 0x8008EB50         ; DATA XREF: sprintf+2A8?r
                dw 0x8008F000         ; jump table for switch statement
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008EE08
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008EF20
                dw 0x8008EB7C
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008EB38
                dw 0x8008EB7C
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008EB44
                dw 0x8008F000
                dw 0x8008EFCC
                dw 0x8008ECF4
                dw 0x8008EDF4
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008EF40
                dw 0x8008F000
                dw 0x8008EBD4
                dw 0x8008F000
                dw 0x8008F000
                dw 0x8008EE14
                dw 0
aNull_0:        db "<NULL>", 0x0       ; DATA XREF: puts+1C?o
                db 0
                dw 0, 0
aIdSysCV1140199:db "$Id: sys.c,v 1.140 1998/01/12 07:52:27 noda Exp yos $", 0x0
                                         ; DATA XREF: TEXT:off_800A4248?o
                dh 0
aResetgraphJtb0:db "ResetGraph:jtb=%08x,env=%08x", 0xA, 0x0
                                         ; DATA XREF: ResetGraph:loc_8008F534?o
                dh 0
aResetgraphD:   db "ResetGraph(%d)...", 0xA, 0x0
                                         ; DATA XREF: ResetGraph+128?o
                db 0
aSetgraphdebugL:db "SetGraphDebug:level:%d,type:%d reverse:%d", 0xA, 0x0
                                         ; DATA XREF: SetGraphDebug+44?o
                db 0
aSetgrapqueD:   db "SetGrapQue(%d)...", 0xA, 0x0
                                         ; DATA XREF: SetGraphQueue+30?o
                db 0
aDrawsynccallba:db "DrawSyncCallback(%08x)...", 0xA, 0x0
                                         ; DATA XREF: DrawSyncCallback+34?o
                db 0
aSetdispmaskD:  db "SetDispMask(%d)...", 0xA, 0x0
                                         ; DATA XREF: SetDispMask+2C?o
aDrawsyncD:     db "DrawSync(%d)...", 0xA, 0x0
                                         ; DATA XREF: DrawSync+20?o
                db 0, 0, 0
aSBadRect:      db "%s:bad RECT", 0x0  ; DATA XREF: sub_8008F8CC+C4?o
aDDDD:          db "(%d,%d)-(%d,%d)", 0xA, 0x0
                                         ; DATA XREF: sub_8008F8CC+FC?o
                db 0, 0, 0
aS_0:           db "%s:", 0x0          ; DATA XREF: sub_8008F8CC:loc_8008F994?o
aClearimage:    db "ClearImage", 0x0   ; DATA XREF: ClearImage+C?o
                db 0
aClearimage2:   db "ClearImage2", 0x0  ; DATA XREF: ClearImage2+C?o
aLoadimage:     db "LoadImage", 0x0    ; DATA XREF: LoadImage+14?o
                dh 0
aStoreimage:    db "StoreImage", 0x0   ; DATA XREF: StoreImage+14?o
                                         ; sub_8009209C+14?o
                db 0
aMoveimage:     db "MoveImage", 0x0    ; DATA XREF: MoveImage+1C?o
                                         ; TEXT:800921A4?o
                dh 0
aClearotag08xD: db "ClearOTag(%08x,%d)...", 0xA, 0x0
                                         ; DATA XREF: TEXT:8008FCB8?o
                db 0
aClearotagr08xD:db "ClearOTagR(%08x,%d)...", 0xA, 0x0
                                         ; DATA XREF: ClearOTagR+28?o
aDrawotag08x:   db "DrawOTag(%08x)...", 0xA, 0x0
                                         ; DATA XREF: DrawOTag+20?o
                                         ; TEXT:800922EC?o
                db 0
aPutdrawenv08x: db "PutDrawEnv(%08x)...", 0xA, 0x0
                                         ; DATA XREF: PutDrawEnv+30?o
                db 0, 0, 0
aDrawotagenv08x:db "DrawOTagEnv(%08x,&08x)...", 0xA, 0x0
                                         ; DATA XREF: DrawOTagEnv+38?o
                db 0
aPutdispenv08x: db "PutDispEnv(%08x)...", 0xA, 0x0
                                         ; DATA XREF: PutDispEnv+34?o
                db 0, 0, 0
aGpuTimeoutQueD:db "GPU timeout:que=%d,stat=%08x,chcr=%08x,madr=%08x", 0xA, 0x0
                                         ; DATA XREF: sub_80091DCC+5C?o
                dh 0
aLoadimage2:    db "LoadImage2", 0x0   ; DATA XREF: sub_80091FB0+14?o
                db 0
aSpuTOS:        db "SPU:T/O [%s]", 0xA, 0x0
                                         ; DATA XREF: _spu_init+94?o
                                         ; sub_80094968+D4?o ...
                dh 0
aWaitReset:     db "wait (reset)", 0x0
                                         ; DATA XREF: _spu_init+A4?o
                db 0, 0, 0
aWaitWrdyHL:    db "wait (wrdy H -> L)", 0x0
                                         ; DATA XREF: sub_80094968+E4?o
                db 0
aWaitDmafClearW:db "wait (dmaf clear/W)", 0x0
                                         ; DATA XREF: sub_80094968+178?o
                dw 0, 0
aSpuTOS_0:      db "SPU:T/O [%s]", 0xA, 0x0
                                         ; DATA XREF: SpuSetIRQ+58?o
                                         ; SpuSetIRQ+E4?o
                dh 0
aWaitIrqOn:     db "wait (IRQ/ON)", 0x0
                                         ; DATA XREF: SpuSetIRQ+68?o
                dh 0
aWaitIrqOff:    db "wait (IRQ/OFF)", 0x0
                                         ; DATA XREF: SpuSetIRQ+EC?o
                db 0
jpt_80097088:   dw 0x800970C8         ; DATA XREF: SpuSetCommonAttr+40?r
                dw 0x80097090         ; jump table for switch statement
                dw 0x80097098
                dw 0x800970A0
                dw 0x800970A8
                dw 0x800970B0
                dw 0x800970B8
                dw 0x800970C0
jpt_80097148:   dw 0x80097188         ; DATA XREF: SpuSetCommonAttr+100?r
                dw 0x80097150         ; jump table for switch statement
                dw 0x80097158
                dw 0x80097160
                dw 0x80097168
                dw 0x80097170
                dw 0x80097178
                dw 0x80097180
jpt_8009764C:   dw 0x80097654         ; DATA XREF: SpuSetVoiceAttr+124?r
                dw 0x8009765C         ; jump table for switch statement
                dw 0x80097664
                dw 0x8009766C
                dw 0x80097674
                dw 0x8009767C
                dw 0x80097684
                dw 0
jpt_8009772C:   dw 0x80097734         ; DATA XREF: SpuSetVoiceAttr+204?r
                dw 0x8009773C         ; jump table for switch statement
                dw 0x80097744
                dw 0x8009774C
                dw 0x80097754
                dw 0x8009775C
                dw 0x80097764
                dw 0
aVsyncTimeout:  db "VSync: timeout", 0xA, 0x0
                                         ; DATA XREF: sub_80098280+50?o
aIdIntrCV175199:db "$Id: intr.c,v 1.75 1997/02/07 09:00:36 makoto Exp $", 0x0
                                         ; DATA XREF: TEXT:off_800AB100?o
aUnexpectedInte:db "unexpected interrupt(%04x)", 0xA, 0x0
                                         ; DATA XREF: sub_80098584+4C?o
aIntrTimeout04x:db "intr timeout(%04x:%04x)", 0xA, 0x0
                                         ; DATA XREF: sub_80098584+16C?o
                db 0, 0, 0
                dw 0
aDmaBusErrorCod:db "DMA bus error: code=%08x", 0xA, 0x0
                                         ; DATA XREF: sub_80098BC4:loc_80098CD8?o
                dh 0
aMadrD08x:      db "MADR[%d]=%08x", 0xA, 0x0
                                         ; DATA XREF: sub_80098BC4:loc_80098CEC?o
                db 0
                dw 0
jpt_8009A4F4:   dw 0x8009A4FC         ; DATA XREF: sub_8009A47C+68?r
                dw 0x8009A508         ; jump table for switch statement
                dw 0x8009A514
                dw 0x8009A520
                dw 0x8009A52C
                dw 0, 0, 0
