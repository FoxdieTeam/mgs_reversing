	opt	c+, at+, e+, n-

	section	.RDATA







    xdef aSaveData
    xdef aSnaChest1
    xdef aSnaChest2
    xdef aSnaChest3
    xdef aSnaHip1
    xdef aSnaArmer1
    xdef aSnaArmer2
    xdef aSnaArmer3
    xdef aSnaArmer4
    xdef aCbBox11
    xdef aCbBox12
    xdef aCbBox41
    xdef aCbBox42
    xdef aCbBox21
    xdef aCbBox22
    xdef aCbBox41
    xdef aCbBox42
    xdef aSnaFace
    xdef aSnaFace2
    xdef aSnaFace3
    xdef aSnaMf1
    xdef aSnaMf2
    xdef aSnaMf3
    xdef dword_80012F2C
    xdef dword_80012F50
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




















dword_800122F4: dw 0x66826C82, 0xE7817282, 0
                                         ; DATA XREF: sub_8004D008+130?o
aSaveData:      db "SAVE DATA", 0x0    ; DATA XREF: TEXT:8009EC34?o
                dh 0
jpt_8004C4E0:   dw 0x8004C4E8         ; DATA XREF: sub_8004C418+B4?o
                dw 0x8004C580         ; jump table for switch statement
                dw 0x8004CAF8
                dw 0x8004CB7C
                dw 0x8004CCD4
                dw 0x8004CC34
                dw 0x8004CDB4
dword_80012328: dw 0xCDA5B9A5, 0xAFA5BCA1, 0
                                         ; DATA XREF: sub_8004F8E4+34?o
aForceActCancel:db "force act cancel", 0xA, 0x0
                                         ; DATA XREF: sub_80050A64+200?o
                dh 0
aRunMoveCancel: db "run move cancel", 0xA, 0x0
                                         ; DATA XREF: sub_80050A64+39C?o
                db 0, 0, 0
aForceStanceCan:db "force stance cancel", 0xA, 0x0
                                         ; DATA XREF: sub_80050A64+4DC?o
                db 0, 0, 0
aPosDDD:        db "pos %d %d %d", 0xA, 0x0
                dh 0
aTurnDDD:       db "turn %d %d %d", 0xA, 0x0
                db 0
aCeilFloorDD:   db "ceil floor %d %d", 0xA, 0x0
                dh 0
aStatus4x:      db "status %4x", 0xA, 0x0
aWeaponD:       db "weapon %d", 0xA, 0x0
                db 0
aItemD:         db "item %d", 0xA, 0x0
                db 0, 0, 0
aFlag4x:        db "flag %4x", 0xA, 0x0
                dh 0
aFlag24x:       db "flag2 %4x", 0xA, 0x0
                db 0
aStanceD:       db "stance %d", 0xA, 0x0
                db 0
aPadtoD:        db "padto %d", 0xA, 0x0
                dh 0
aTrapCheckD:    db "trap check %d", 0xA, 0x0
                db 0
aSnaInitC:      db "sna_init.c", 0x0   ; DATA XREF: TEXT:8005B6B0?o
                db 0
jpt_8005611C:   dw 0x80056134         ; DATA XREF: sub_80055DD8+330?o
                dw 0x80056124         ; jump table for switch statement
                dw 0x8005615C
                dw 0x80056198
                dw 0x800561E4
                dw 0x8005624C
                dw 0x80056504
aNoReachZoneFro:db " no reach zone from %d to %d ", 0xA, 0x0
                                         ; DATA XREF: TEXT:8005CDFC?o
                db 0
aOverNoReachZon:db "over no reach zone from %d to %d ", 0xA, 0x0
                                         ; DATA XREF: TEXT:8005CF54?o
                db 0
aBoundNoReachZo:db "bound no reach zone from %d to %d ", 0xA, 0x0
                                         ; DATA XREF: TEXT:8005D0DC?o
aVibrateC:      db "vibrate.c", 0x0    ; DATA XREF: TEXT:8005D548?o
                                         ; sub_8005D58C+48?o
                dh 0
dword_800124A8: dw 0x38B00, 0x340009, 0x2FE0164, 0xC0100, 0x6FF0108
                dw 0xECFF0000, 0x20000, 0xC0D01, 0x6FF0104, 0xECFF0000
                dw 0xFF0A0000, 0x2F6FFF6, 0xF0D0100, 0xFF0AFE01, 0x2F6FFF6
                dw 0xC0100, 0x6FF0110, 0xECFF0000, 0x20000, 0xC0D01
                dw 0x6FF0104, 0xECFF0000, 0xFF0A0000, 0x2F6FFF6, 0xF0D0100
                dw 0xAFE01, 0x21E001E, 0xC0100, 0x6FF0110, 0xECFF0000
                dw 0x20000, 0xC0D01, 0x6FF0104, 0xECFF0000, 0xFF0A0000
                dw 0x2F6FFF6, 0xF0D0100, 0x48300, 0x33000B, 0x174005A
                dw 0x8FF01FE, 0xC010101, 0x2080500, 0xFF010202, 0xD010002
                dw 0x114000C, 0x1E000AFF, 0xFE081E00, 0x2FEFE, 0x10F0D01
                dw 0xD4FE0AFE, 0xCD4FE, 0x2020805, 0x2FF0102, 0xC0D0100
                dw 0xFF011400, 0x1E000A, 0xFEFE081E, 0x10002FE, 0xFE010F0D
                dw 0xFF9CFF0A, 0xE000C9C, 0xFFFEFF0A, 0xFEFE08FE, 0x2FF01FE
                dw 0xF0D0100, 0x10AFE01, 0xCF401F4, 0xA1D00, 0x8140014
                dw 0x1FFFFFF, 0x10002FF, 0xF0D, 0x31D00, 0x100009, 0xE803091B
                dw 0xF010002, 0xFF0A0307, 0x238FF38, 0x70F0100, 0xFCFE0A03
                dw 0x2FCFE, 0xF01, 0x31D00, 0x100009, 0xE803091B, 0xF010002
                dw 0xFD0A0307, 0x2A8FDA8, 0x70F0100, 0x7CFC0A03, 0x27CFC
                dw 0xF01, 0x10400, 0x1000205, 0xF, 0x10700, 0xE8030905
                dw 0xF010002, 0x2CB00, 0xC790007, 0x60B00, 0xECFF00
                dw 0x1000200, 0x52B0B0D, 0x14000000, 0xFF860000, 0xFF0100F6
                dw 0xA0086F6, 0xA000100, 0x104000C, 0x10002FF, 0x60D
                dw 0xD8FF, 0x104000C, 0x10002FF, 0x60D, 0
                dw 0x102000C, 0x22B0BFF, 0xC0D0200, 0xFF010200, 0xD020002
                dw 5, 0x7000000, 0xD8D80801, 0x4000CD8, 0xF0F0F008
                dw 0xD010002, 0xB000C0F, 0xFF000006, 0x20000EC, 0x50D0100
                dw 0
                dw 0xFF860000, 0xFF0100EC, 0x140086EC, 0x14000100, 0x102000C
                dw 0x22B0BFF, 0xC0D0100, 0xFF010400, 0xD010002, 0x104000C
                dw 0x20002FF, 0x50D, 0
dword_800126F4: dw 0xD8080107, 0xCD8D8, 0xF0F00804, 0x10002F0, 0xF0D
                dw 0x11900, 0xCFE0105, 0xFF011400, 0xD010002, 0x10A000C
                dw 0xF9F908FF, 0x10002F9, 0xF0D, 0x12300, 0xCFE0105
                dw 0xFF010A00, 0x50000A, 0x1000250, 0x5000C0D, 0x50000A
                dw 0x8FF0150, 0x2F2F2F2, 0xF0D0100, 0x24A00, 0x1200007
                dw 0x5000CFE, 0x2FF01, 0xC0D01, 0x8FF010A, 0x2F4F4F4
                dw 0xF0D0100, 0xCFE01, 0x2C010A04, 0xFF012C01, 0xD010002
                dw 0xA0A000C, 0x46004600, 0x2FF01, 0xC0D01, 0xAFF010A
                dw 0x50005000, 0xE7E7E708, 0xD010002, 0xF, 0x12700
                dw 0xCFE0105, 0xFF010500, 0x64000A, 0xF6F60864, 0x10002F6
                dw 0x5000C0D, 0xAFF01, 0x8C800C8, 0x2F3F3F3, 0xF0D0100
                dw 0x13900, 0xCFE0105, 0xFF011400, 0x1000A, 0x5050801
                dw 0x1000205, 0xC000C0D, 0xAFF01, 0x8050005, 0x2FBFBFB
                dw 0xC0D0100, 0xFF010A00, 0xA000A, 0xFBFB080A, 0x10002FB
                dw 0xF0D
aScriptActErr:  db " SCRIPT ACT ERR!! ", 0xA, 0x0
aAnimeC:        db "anime.c", 0x0      ; DATA XREF: sub_8005FBC8+88?o
aShadowC:       db "shadow.c", 0x0     ; DATA XREF: sub_800602CC+54?o
                db 0, 0, 0
aAfterseC:      db "afterse.c", 0x0    ; DATA XREF: sub_800604C0+58?o
                dh 0
aSnaHip1:       db "sna_hip1", 0x0     ; DATA XREF: TEXT:8009F270?o
                db 0, 0, 0
aSnaChest3:     db "sna_chest3", 0x0   ; DATA XREF: TEXT:8009F26C?o
                db 0
aSnaChest2:     db "sna_chest2", 0x0   ; DATA XREF: TEXT:8009F268?o
                db 0
aSnaChest1:     db "sna_chest1", 0x0   ; DATA XREF: TEXT:off_8009F264?o
                db 0
aSnaArmer4:     db "sna_armer4", 0x0   ; DATA XREF: TEXT:8009F280?o
                db 0
aSnaArmer3:     db "sna_armer3", 0x0   ; DATA XREF: TEXT:8009F27C?o
                db 0
aSnaArmer2:     db "sna_armer2", 0x0   ; DATA XREF: TEXT:8009F278?o
                db 0
aSnaArmer1:     db "sna_armer1", 0x0   ; DATA XREF: TEXT:off_8009F274?o
                db 0
aBodyarmC:      db "bodyarm.c", 0x0    ; DATA XREF: sub_80060940+40?o
                dh 0
aGasMask:       db "gas_mask", 0x0     ; DATA XREF: sub_80060B5C+1C?o
                db 0, 0, 0
aGasmaskC:      db "gasmask.c", 0x0    ; DATA XREF: sub_80060C14+54?o
                dh 0
aKogaku2C:      db "kogaku2.c", 0x0    ; DATA XREF: sub_800615FC+54?o
                                         ; TEXT:8006175C?o
                dh 0
aCbBox22:       db "cb_box22", 0x0     ; DATA XREF: TEXT:8009F29C?o
                db 0, 0, 0
aCbBox21:       db "cb_box21", 0x0     ; DATA XREF: TEXT:8009F298?o
                db 0, 0, 0
aCbBox42:       db "cb_box42", 0x0     ; DATA XREF: TEXT:8009F294?o
                                         ; TEXT:8009F2A4?o
                db 0, 0, 0
aCbBox41:       db "cb_box41", 0x0     ; DATA XREF: TEXT:8009F290?o
                                         ; TEXT:8009F2A0?o
                db 0, 0, 0
aCbBox12:       db "cb_box12", 0x0     ; DATA XREF: TEXT:8009F28C?o
                db 0, 0, 0
aCbBox11:       db "cb_box11", 0x0     ; DATA XREF: TEXT:off_8009F288?o
                db 0, 0, 0
                dw 0xDCA5CAC3, 0xEBA5BCA1, 0
aCbBox:         db "cb_box", 0x0       ; DATA XREF: sub_80061BA0+14?o
                db 0
aBoxC:          db "box.c", 0x0        ; DATA XREF: sub_80061C7C+4C?o
                dh 0
aSnaFace3:      db "sna_face3", 0x0    ; DATA XREF: TEXT:8009F2B0?o
                dh 0
aSnaFace2:      db "sna_face2", 0x0    ; DATA XREF: TEXT:8009F2AC?o
                dh 0
aSnaFace:       db "sna_face", 0x0     ; DATA XREF: TEXT:off_8009F2A8?o
                db 0, 0, 0
aSnaMf3:        db "sna_mf3", 0x0      ; DATA XREF: TEXT:8009F2BC?o
aSnaMf2:        db "sna_mf2", 0x0      ; DATA XREF: TEXT:8009F2B8?o
aSnaMf1:        db "sna_mf1", 0x0      ; DATA XREF: TEXT:off_8009F2B4?o
aBandanaC:      db "bandana.c", 0x0    ; DATA XREF: sub_80061E40+44?o
                dh 0
aCigar:         db "cigar", 0x0        ; DATA XREF: sub_800620B4+1C?o
                dh 0
aRcmL:          db "rcm_l", 0x0        ; DATA XREF: sub_800620B4:loc_80062184?o
                dh 0
aTabakoC:       db "tabako.c", 0x0     ; DATA XREF: sub_80062274+54?o
                db 0, 0, 0
aZoomLevelD:    db "- ZOOM LEVEL - - %d -", 0x0
                                         ; DATA XREF: sub_80062DA8+60?o
                dh 0
dword_800129B4: dw 0x6425, 0x67676F67, 0x73656C, 0x706F6373, 0x632E65
                                         ; DATA XREF: sub_80062DA8+C0?o
                                         ; sub_80062E8C+64?o ...
                dw 0x69736D67, 0x2E746867, 0x63, 0x45564153, 0x4F485020
                dw 0x4F54, 0x73257325, 0x73257325, 0
dword_800129EC: dw 0x66826C82, 0xE7817282, 0
                                         ; DATA XREF: sub_80063704+E8?o
dword_800129F8: dw 0x4081, 0x67826F82, 0x73826E82, 0x6E82, 0x544F4850
                                         ; DATA XREF: sub_80063704+108?o
                                         ; sub_80063704+140?o
                dw 0x3025204F, 0xA6432
aSaveHeaderX:   db "save header = %x", 0xA, 0x0
                                         ; DATA XREF: sub_800638B4+24?o
                dh 0
aDTryQScaleDSiz:db "%d try q_scale = %d size = %d", 0xA, 0x0
                                         ; DATA XREF: sub_80064378+7C?o
                db 0
aSinreiSyasinCh:db "Sinrei Syasin Check Start", 0xA, 0x0
                                         ; DATA XREF: sub_800649F4+4?o
                db 0
aHereIsSinreiSp:db "Here is Sinrei Spot!", 0xA, 0x0
                                         ; DATA XREF: sub_800649F4+34?o
                dh 0
aGmPhotocodeD:  db "GM_Photocode = %d", 0xA, 0x0
                                         ; DATA XREF: sub_800649F4+44?o
                db 0
aPointCheck:    db "Point Check", 0xA, 0x0
                                         ; DATA XREF: sub_800649F4+60?o
                db 0, 0, 0
aResultD:       db "Result = %d", 0xA, 0x0
                                         ; DATA XREF: sub_800649F4+64?o
                db 0, 0, 0
aNotSinreiSpot: db "Not Sinrei Spot!", 0xA, 0x0
                                         ; DATA XREF: sub_800649F4+84?o
                dh 0
aGoggles:       db "goggles", 0x0      ; DATA XREF: sub_80064C50+90?o
aZoom4d:        db "zoom  : %4d", 0xA, 0x0
                                         ; DATA XREF: sub_80064C50+2EC?o
                db 0, 0, 0
aAngle4d4d:     db "angle : %4d, %4d", 0xA, 0x0
                                         ; DATA XREF: sub_80064C50+2F0?o
                dh 0
aJpegcamC:      db "jpegcam.c", 0x0    ; DATA XREF: sub_80065118+4C?o
                dh 0
aGrenadeC:      db "grenade.c", 0x0    ; DATA XREF: sub_80066944+64?o
                dh 0
aClaymore_0:    db "claymore", 0x0     ; DATA XREF: sub_80067730+1C?o
                db 0, 0, 0
aLockOn:        db "LOCK_ON", 0xA, 0x0    ; DATA XREF: sub_8006837C+88?o
                db 0, 0, 0
aStnsightC:     db "stnsight.c", 0x0   ; DATA XREF: sub_800693E0+54?o
                db 0
aRfsightC:      db "rfsight.c", 0x0    ; DATA XREF: sub_8006989C+3C?o
                                         ; TEXT:8006995C?o
                dh 0
aTenageC:       db "tenage.c", 0x0     ; DATA XREF: sub_8006A010+74?o
                                         ; TEXT:8006A184?o
                db 0, 0, 0
aBakudanC:      db "bakudan.c", 0x0    ; DATA XREF: sub_8006A6CC+6C?o
                dh 0
aClaymore_1:    db "CLAYMORE", 0x0     ; DATA XREF: sub_8006A950+168?o
                db 0, 0, 0
aFull_0:        db "FULL", 0x0         ; DATA XREF: sub_8006A950+170?o
                db 0, 0, 0
aClaymore_2:    db "claymore", 0x0     ; DATA XREF: sub_8006B2A4+D8?o
                                         ; sub_8006B564+1C?o
                db 0, 0, 0
aJiraiC:        db "jirai.c", 0x0      ; DATA XREF: sub_8006B48C+90?o
                                         ; TEXT:8006B7B8?o
aEnemy:         db "ENEMY", 0xA, 0x0      ; DATA XREF: sub_8006BA70+84?o
                db 0
dword_80012B80: dw 0x6425, 0x6F636F73, 0x665F6D, 0x73696D72, 0x656C6973
                                         ; DATA XREF: sub_8006BB10+1A8?o
                                         ; sub_8006CE54+C?o ...
                dw 0x632E, 0x73696D61, 0x656C6973, 0x632E, 0x73616C62
                dw 0x632E74, 0x13B00, 0x2000105, 0xC0100, 0xAFF0102
                dw 0xB004B004, 0xD010002, 0x106000C, 0x10002FF, 0x7000C0D
                dw 0xAFF01, 0x8640064, 0x2F8F8F8, 0xA0100, 0x8500050
                dw 0x2F8F8F8, 0xF0D0100, 0x13B00, 0x2000105, 0xC0100
                dw 0xAFF0104, 0xB004B004, 0xD010002, 0x10C000C, 0x10002FF
                dw 0x8000C0D, 0xAFF01, 0x8640064, 0x2F8F8F8, 0xA0100
                dw 0x8500050, 0x2F8F8F8, 0xF0D0100, 0x13B00, 0x2000105
                dw 0xC0100, 0xAFF0102, 0x58025802, 0xD010002, 0x106000C
                dw 0x10002FF, 0x7000C0D, 0xAFF01, 0x8320032, 0x2F8F8F8
                dw 0xA0100, 0x8280028, 0x2F8F8F8, 0xF0D0100, 0x13B00
                dw 0x2000105, 0xC0100, 0xAFF0102, 0xC800C800, 0xD010002
                dw 0x106000C, 0x10002FF, 0x7000C0D, 0xAFF01, 0x8140014
                dw 0x2F8F8F8, 0xA0100, 0x8140014, 0x2F8F8F8, 0xF0D0100
                dw 0x41701, 0x4B000B, 0x1D90090, 0x1000200, 0x102000C
                dw 0xB0040AFF, 0x2B004, 0xC0D01, 0xAFF0106, 0xC800C800
                dw 0xD010002, 0x107000C, 0x64000AFF, 0xF8086400, 0x2F8F8
                dw 0x50000A01, 0xF8085000, 0x2F8F8, 0x10F0D01, 0x1000200
                dw 0x20001, 0x2000C01, 0x30AFF01, 0x2E803E8, 0xC0D0100
                dw 0xFF010600, 0xB4000A, 0x10002B4, 0x7000C0D, 0xAFF01
                dw 0x8640064, 0x2F8F8F8, 0xA0100, 0x8500050, 0x2F8F8F8
                dw 0xF0D0100, 0x102000C, 0x1000200, 0x200010D, 0xC0100
                dw 0xAFF0102, 0x20032003, 0xD010002, 0x106000C, 0xA0000AFF
                dw 0x2A000, 0xC0D01, 0xAFF0107, 0x64006400, 0xF8F8F808
                dw 0xA010002, 0x50005000, 0xF8F8F808, 0xD010002, 0x3000C0F
                dw 0x20001, 0x10D01, 0xC010002, 0xFF010200, 0x258020A
                dw 0x1000258, 0x6000C0D, 0xAFF01, 0x28C008C, 0xC0D0100
                dw 0xFF010700, 0x64000A, 0xF8F80864, 0x10002F8, 0x50000A
                dw 0xF8F80850, 0x10002F8, 0xF0D, 0x65706F20, 0x2021216E
                dw 0xA, 0x6F6C6320, 0x21216573, 0xA20, 0x726F6F64, 0x6F6C633A
                dw 0x25206573, 0xA64, 0x636E6163, 0xA6C65, 0x726F6F64
                dw 0x65706F3A, 0x6425206E, 0xA, 0x6B616E53, 0x6F442065
                dw 0x2520726F, 0xA58
aDoorOpencancel:db "door:opencancel %d", 0xA, 0x0
                                         ; DATA XREF: sub_8006EDB8+31C?o
aCloseDoorX:    db "close door %X", 0xA, 0x0
                                         ; DATA XREF: sub_8006F318+204?o
                db 0
aCloseDoorX_0:  db "CLOSE door %X", 0xA, 0x0
                                         ; DATA XREF: sub_8006F318+26C?o
                db 0
aDoorC:         db "door.c", 0x0       ; DATA XREF: TEXT:8006FD8C?o
                db 0
aSgtrect3C:     db "sgtrect3.c", 0x0   ; DATA XREF: sub_80071010+6C?o
                db 0
dword_80012E68: dw 0x7325, 0x68676973, 0x632E74, 0x6F6F6C62, 0x315F64
                                         ; DATA XREF: sub_80071498+34?o
                                         ; sub_80071CDC+74?o ...
                dw 0x6F6F6C62, 0x632E64, 0x12A00, 0x2FE0105, 0x80100
                dw 0xCB0B0, 0xAFF0105, 0x64006400, 0xD010002, 0x105000C
                dw 0x1E000AFF, 0xE8081E00, 0x2F8F8, 0xF0D01, 0x6C625F64
                dw 0x2E646F6F, 0x63, 0x6374656B, 0x5F706168, 0x79657267
                dw 0
aDBloodrC:      db "d_bloodr.c", 0x0   ; DATA XREF: sub_80073148+44?o
                db 0
byte_80012EDC:  db 0                  ; DATA XREF: sub_800739EC+30?o
                                         ; sub_800739EC+38?r
                db    0
                db    0
byte_80012EDF:  db 0                  ; DATA XREF: sub_800739EC+34?r
dword_80012EE0: dw 0x5DC, 0x6C6C7562, 0x7465, 0xC800C8, 0xC8, 0x79616C63
                                         ; DATA XREF: sub_800739EC+40?r
                                         ; sub_800739EC+3C?r ...
                dw 0x65726F6D, 0x632E, 0x72617073, 0x6C665F6B, 0
aSparkC:        db "spark.c", 0x0      ; DATA XREF: sub_80074564+5C?o
aRefrection6:   db "refrection6", 0x0  ; DATA XREF: sub_800748D8+1B4?o
aStngrndC:      db "stngrnd.c", 0x0    ; DATA XREF: sub_80074B5C+5C?o
                dh 0
dword_80012F2C: dw 0x11F00            ; DATA XREF: TEXT:8009F688?o
                dw 0xC000105
                dw 0x10A0400
                dw 0x2F401F4
                dw 0xC0D0100
                dw 0x10A0700
                dw 0x8F401F4
                dw 0x2F0F0F0
                dw 0xF0D0100
dword_80012F50: dw 0x11F00            ; DATA XREF: TEXT:8009F6A4?o
                dw 0xC000105
                dw 0x20A0500
                dw 0x2580258
                dw 0xC0D0100
                dw 0xA0900
                dw 0x81E001E
                dw 0x2EEEEEE
                dw 0xF0D0100
dword_80012F74: dw 0x80075084         ; DATA XREF: sub_80074F5C+10C?o
                dw 0x80075098         ; jump table for switch statement
                dw 0x800750B0
                dw 0x800750D4
                dw 0x800750EC
                dw 0x80075104
                dw 0x8007511C
aStgfdIoC:      db "stgfd_io.c", 0x0   ; DATA XREF: sub_800752A0+3C?o
                db    0
aBullet:        db "bullet", 0x0       ; DATA XREF: sub_80076274+144?o
                db    0
aBulletC:       db "bullet.c", 0x0     ; DATA XREF: TEXT:8007647C?o
                                         ; sub_80076584+5C?o ...
                db    0
                db    0
                db    0
aEffect:        db "effect", 0x0       ; DATA XREF: sub_80076B28+C?o
                db 0
aChafgrndC:     db "chafgrnd.c", 0x0   ; DATA XREF: sub_80077264+118?o
                db 0
aGoggles_0:     db "goggles", 0x0      ; DATA XREF: sub_8007773C+3C?o
aGoggleC:       db "goggle.c", 0x0     ; DATA XREF: sub_8007781C+4C?o
                db 0, 0, 0
aGglmngC:       db "gglmng.c", 0x0     ; DATA XREF: sub_800779B8+44?o
                db 0, 0, 0
a02d:           db "%02d", 0x0         ; DATA XREF: sub_80077A24+1BC?o
                db 0, 0, 0
aLd:            db "%ld", 0xA, 0x0        ; DATA XREF: sub_80077C6C+6C?o
                db 0, 0, 0
aScan:          db "SCAN", 0x0         ; DATA XREF: sub_80077F70+94?o
                db 0, 0, 0
aModeB:         db "MODE - B", 0x0     ; DATA XREF: sub_80077F70+BC?o
                db 0, 0, 0
aModeA:         db "MODE - A", 0x0     ; DATA XREF: sub_80077F70:loc_80078030?o
                db 0, 0, 0
aGglsightC:     db "gglsight.c", 0x0   ; DATA XREF: sub_80078520+44?o
                db 0
aScnMaskC:      db "scn_mask.c", 0x0   ; DATA XREF: sub_8007895C+44?o
                db 0
aGoggles_1:     db "goggles", 0x0      ; DATA XREF: sub_80078D8C+3C?o
aGoggleirC:     db "goggleir.c", 0x0   ; DATA XREF: sub_80078E6C+4C?o
                db 0
aDemothrdC:     db "demothrd.c", 0x0   ; DATA XREF: sub_80079460+44?o
                                         ; sub_800794E4+58?o
                db 0
aDemoFileS:     db "Demo file = ""%s""", 0xA, 0x0
                                         ; DATA XREF: sub_800794E4+9C?o
                dh 0
aSNotFound:     db """%s"" not found", 0xA, 0x0
                                         ; DATA XREF: sub_800794E4+C8?o
aErrorInitializ:db "Error:Initialize demo", 0xA, 0x0
                                         ; DATA XREF: sub_800797FC+4C?o
                db 0
aPlaydemosound: db "PlayDemoSound", 0xA, 0x0
                                         ; DATA XREF: sub_800797FC+7C?o
                db 0
aCacheBufferCle:db "Cache Buffer Cleared", 0xA, 0x0
                                         ; DATA XREF: sub_800799A8+2C?o
                dh 0
aCacheReadEnabl:db "Cache Read Enable", 0xA, 0x0
                                         ; DATA XREF: sub_800799A8+60?o
                db 0
aNoloadModelSta:db "Noload model ( Stage )", 0xA, 0x0
                                         ; DATA XREF: sub_80079B50+AB0?o
aNoloadModelSce:db "Noload model ( Scene = No.%d )", 0xA, 0x0
                                         ; DATA XREF: sub_80079B50:loc_8007A604?o
aErrorInitContr:db "Error init control ( Scene = No.%d )", 0xA, 0x0
                                         ; DATA XREF: sub_80079B50:loc_8007A618?o
                dh 0
a16dO4a:        db "16d_o4a", 0x0      ; DATA XREF: sub_80079B50+2EC?o
a16dO5a:        db "16d_o5a", 0x0      ; DATA XREF: sub_80079B50+308?o
a16dO6a:        db "16d_o6a", 0x0      ; DATA XREF: sub_80079B50+324?o
a16dO7a:        db "16d_o7a", 0x0      ; DATA XREF: sub_80079B50+340?o
a16dO8a:        db "16d_o8a", 0x0      ; DATA XREF: sub_80079B50+35C?o
a16dO9a:        db "16d_o9a", 0x0      ; DATA XREF: sub_80079B50+378?o
a16dO10a:       db "16d_o10a", 0x0     ; DATA XREF: sub_80079B50+394?o
                db 0, 0, 0
a16dO4b:        db "16d_o4b", 0x0      ; DATA XREF: sub_80079B50+3B0?o
a16dO5b:        db "16d_o5b", 0x0      ; DATA XREF: sub_80079B50+3CC?o
a16dO6b:        db "16d_o6b", 0x0      ; DATA XREF: sub_80079B50+3E8?o
a16dO7b:        db "16d_o7b", 0x0      ; DATA XREF: sub_80079B50+404?o
a16dO8b:        db "16d_o8b", 0x0      ; DATA XREF: sub_80079B50+420?o
a16dO9b:        db "16d_o9b", 0x0      ; DATA XREF: sub_80079B50+43C?o
a16dO10b:       db "16d_o10b", 0x0     ; DATA XREF: sub_80079B50+458?o
                db 0, 0, 0
a16dO4c:        db "16d_o4c", 0x0      ; DATA XREF: sub_80079B50+474?o
a16dO5c:        db "16d_o5c", 0x0      ; DATA XREF: sub_80079B50+490?o
a16dO6c:        db "16d_o6c", 0x0      ; DATA XREF: sub_80079B50+4AC?o
a16dO7c:        db "16d_o7c", 0x0      ; DATA XREF: sub_80079B50+4C8?o
a16dO8c:        db "16d_o8c", 0x0      ; DATA XREF: sub_80079B50+4E4?o
a16dO9c:        db "16d_o9c", 0x0      ; DATA XREF: sub_80079B50+500?o
a16dO10c:       db "16d_o10c", 0x0     ; DATA XREF: sub_80079B50+51C?o
                db 0, 0, 0
a02aR8:         db "02a_r8", 0x0       ; DATA XREF: sub_80079B50+548?o
                db 0
aMgrexw:        db "mgrexw", 0x0       ; DATA XREF: sub_80079B50+584?o
                db 0
aMgrexll:       db "mgrexll", 0x0      ; DATA XREF: sub_80079B50+5A0?o
aMgrexrl:       db "mgrexrl", 0x0      ; DATA XREF: sub_80079B50+5BC?o
aPitT:          db "pit_t", 0x0        ; DATA XREF: sub_80079B50+5D8?o
                dh 0
aPitU:          db "pit_u", 0x0        ; DATA XREF: sub_80079B50+5F4?o
                dh 0
aPitLiq:        db "pit_liq", 0x0      ; DATA XREF: sub_80079B50+610?o
aRadarF1:       db "radar_f1", 0x0     ; DATA XREF: sub_80079B50+62C?o
                db 0, 0, 0
aRadarF2:       db "radar_f2", 0x0     ; DATA XREF: sub_80079B50+648?o
                db 0, 0, 0
aRadarF3:       db "radar_f3", 0x0     ; DATA XREF: sub_80079B50+664?o
                db 0, 0, 0
aLHatch1:       db "l_hatch1", 0x0     ; DATA XREF: sub_80079B50+680?o
                db 0, 0, 0
aLHatch2:       db "l_hatch2", 0x0     ; DATA XREF: sub_80079B50+69C?o
                db 0, 0, 0
aLHatch3:       db "l_hatch3", 0x0     ; DATA XREF: sub_80079B50+6B8?o
                db 0, 0, 0
aLHatch4:       db "l_hatch4", 0x0     ; DATA XREF: sub_80079B50+6D4?o
                db 0, 0, 0
aRHatch1:       db "r_hatch1", 0x0     ; DATA XREF: sub_80079B50+6F0?o
                db 0, 0, 0
aRHatch2:       db "r_hatch2", 0x0     ; DATA XREF: sub_80079B50+70C?o
                db 0, 0, 0
aRHatch3:       db "r_hatch3", 0x0     ; DATA XREF: sub_80079B50+728?o
                db 0, 0, 0
aRHatch4:       db "r_hatch4", 0x0     ; DATA XREF: sub_80079B50+744?o
                db 0, 0, 0
aM1e1:          db "m1e1", 0x0         ; DATA XREF: sub_80079B50+7A8?o
                                         ; sub_8007A66C+FC?o ...
                db 0, 0, 0
aM1e1demo:      db "m1e1demo", 0x0     ; DATA XREF: sub_80079B50+7CC?o
                                         ; sub_8007A66C+118?o ...
                db 0, 0, 0
aM1e1cl1:       db "m1e1cl1", 0x0      ; DATA XREF: sub_80079B50+808?o
aM1e1cl2:       db "m1e1cl2", 0x0      ; DATA XREF: sub_80079B50+828?o
aM1e1cl3:       db "m1e1cl3", 0x0      ; DATA XREF: sub_80079B50+84C?o
aM1e1cr1:       db "m1e1cr1", 0x0      ; DATA XREF: sub_80079B50+870?o
aM1e1cr2:       db "m1e1cr2", 0x0      ; DATA XREF: sub_80079B50+894?o
aM1e1cr3:       db "m1e1cr3", 0x0      ; DATA XREF: sub_80079B50+8B8?o
aHind:          db "hind", 0x0         ; DATA XREF: sub_80079B50+98C?o
                                         ; sub_8007CFE8+38C?o
                db 0, 0, 0
aHinddemo:      db "hinddemo", 0x0     ; DATA XREF: sub_80079B50+9A4?o
                                         ; sub_8007CFE8+3A8?o
                db 0, 0, 0
aNull:          db "null", 0x0         ; DATA XREF: sub_80079B50+A04?o
                db 0, 0, 0
aNoloadModelNul:db "Noload model ( null.kmd )", 0xA, 0x0
                                         ; DATA XREF: sub_80079B50+A28?o
                db 0
aErrorInitContr_0:db "Error init control ( null.kmd )", 0xA, 0x0
                                         ; DATA XREF: sub_80079B50:loc_8007A630?o
                db 0, 0, 0
jpt_8007AECC:   dw 0x8007AED4, 0x8007AEFC, 0x8007AF04, 0x8007AF04, 0x8007AFB8
                                         ; DATA XREF: sub_8007AE10+A8?o
                dw 0x8007AFE0, 0x8007B014, 0x8007B048, 0x8007B050, 0x8007B0A4  ; jump table for switch statement
                dw 0x8007B10C, 0x8007B114, 0x8007B170, 0x8007B178, 0x8007B2B4
                dw 0x8007B340, 0x8007B3C4, 0x8007B3CC, 0x8007B498, 0x8007B498
                dw 0x8007B498, 0x8007B66C, 0x8007B674, 0x8007B7A8, 0x8007B89C
                dw 0x8007B928, 0x8007B950, 0x8007B994, 0x8007BA64, 0x8007B498
                dw 0x8007BAA4, 0x8007BB10, 0x8007BBDC, 0x8007BC24, 0x8007BC68
                dw 0x8007BCF8, 0x8007BD1C, 0x8007BD40, 0x8007BDF0, 0x8007BDF8
                dw 0x8007BE58, 0x8007BF3C, 0x8007C030, 0x8007C09C, 0x8007C0E8
                dw 0x8007C134, 0x8007C1D8, 0x8007C200, 0x8007C224, 0x8007C22C
                dw 0x8007C254, 0x8007C27C, 0x8007C348, 0x8007C8D8, 0x8007C3AC
                dw 0x8007C430, 0x8007C438, 0x8007C4DC, 0x8007C520, 0x8007C58C
                dw 0x8007C61C, 0x8007C6A8, 0x8007C7DC, 0x8007C8D8, 0x8007C90C
                dw 0x8007C930, 0x8007C948, 0x8007CA4C, 0x8007CBB8, 0x8007CBEC
                dw 0x8007CC18, 0x8007CC44, 0x8007CC6C, 0x8007CCF4
dword_8001345C: dw 0x12700, 0xCFE0105, 0xFF010500, 0x64000A, 0xF1F10864
                dw 0x10002F1, 0x5000C0D, 0x10AFF01, 0x82C012C, 0x2E2E2E2
                dw 0xF0D0100, 0x24A00, 0x1200007, 0x5000CFE, 0x2FF01
                dw 0xC0D01, 0x8FF010A, 0x2FAFAFA, 0xF0D0100, 0xCFE01
                dw 0x2C010A04, 0xFF012C01, 0xD010002, 0xA0A000C, 0x46004600
                dw 0x2FF01, 0xC0D01, 0xAFF010A, 0x50005000, 0xF0F0F008
                dw 0xD010002, 0xF, 0x12C00, 0xCFE0105, 0xFF010500, 0xD010002
                dw 0x105000C, 0x5000AFF, 0x20500, 0xC0D01, 0x8FF010F
                dw 0xAF0F0F0, 0x5000500, 0xD010002, 0xF, 0x34900, 0x1E0009
                dw 0xCFE0138, 0x20400, 0xC0D01, 0xECEC0804, 0x10002EC
                dw 0xFE010F0D, 0xFC18FC0A, 0x4000C18, 0xD010002, 0x804000C
                dw 0x2ECECEC, 0xF0D0100, 0xFB0AFE01, 0xC50FB50, 0x20400
                dw 0xC0D01, 0xECEC0804, 0x10002EC, 0xF0D
aSoundLaunchArg:db "SOUND_LAUNCH(argc:%d)", 0xA, 0x0
                                         ; DATA XREF: TEXT:80081924?o
                db 0
aArgDS:         db "ARG%d:[%s]", 0xA, 0x0
                                         ; DATA XREF: TEXT:loc_80081994?o
aStartTaskSdmai:db "Start Task:SdMain", 0xA, 0x0
                                         ; DATA XREF: sub_80081A18+4?o
                db 0
aBgmTerminate:  db "***BGM Terminate***", 0xA, 0x0
                                         ; DATA XREF: sub_80081A18+178?o
                db 0, 0, 0
jpt_80081B38:   dw 0x80081B40         ; DATA XREF: sub_80081A18+110?r
                dw 0x80081B78         ; jump table for switch statement
                dw 0x80081B78
                dw 0x80081B78
                dw 0x80081B78
                dw 0x80081BA0
                dw 0x80081B88
aStartTaskSdint:db "Start Task:SdInt", 0xA, 0x0
                                         ; DATA XREF: sub_80081BDC+4?o
                dh 0
aBlankDataAddrX:db "blank_data_addr=%x", 0xA, 0x0
                                         ; DATA XREF: sub_80081C7C+70?o
aSpuWaveStartPt:db "spu_wave_start_ptr=%x", 0xA, 0x0
                                         ; DATA XREF: sub_80081C7C+98?o
                db 0
aSpuBgmStartPtr:db "spu_bgm_start_ptr_r=%x", 0xA, 0x0
                                         ; DATA XREF: sub_80081C7C+BC?o
aSpuBufferOver: db "SPU Buffer Over!!", 0xA, 0x0
                                         ; DATA XREF: sub_80081C7C+F8?o
                db 0
aSpuBgmStartPtr_0:db "spu_bgm_start_ptr_l=%x", 0xA, 0x0
                                         ; DATA XREF: sub_80081C7C:loc_80081D8C?o
aSpuReverbBuffe:db "SPU Reverb Buffer Over!!", 0xA, 0x0
                                         ; DATA XREF: sub_80081C7C+15C?o
                dh 0
aSoundErrorSpuO:db "SOUND ERROR:SPU OFF ENV ON(STR_TRACK_R=%x)", 0xA, 0x0
                                         ; DATA XREF: sub_80081FE8+70?o
aSoundErrorSpuO_0:db "SOUND ERROR:SPU OFF ENV ON(STR_TRACK_L=%x)", 0xA, 0x0
                                         ; DATA XREF: sub_80081FE8+A0?o
aSngDataX:      db "sng_data %X", 0xA, 0x0
                                         ; DATA XREF: sub_80082194+4?o
                db 0, 0, 0
aWaveHeaderX:   db "wave_header %X", 0xA, 0x0
                                         ; DATA XREF: sub_80082194+28?o
aVoiceTblX:     db "voice_tbl %X", 0xA, 0x0
                                         ; DATA XREF: sub_80082194+5C?o
                dh 0
aSeHeaderX:     db "se_header %X", 0xA, 0x0
                                         ; DATA XREF: sub_80082194+7C?o
                dh 0
aSeDataX:       db "se_data %X", 0xA, 0x0
                                         ; DATA XREF: sub_80082194+A0?o
aCdloadBufXXX:  db "CDLOAD_BUF %X %X %X", 0xA, 0x0
                                         ; DATA XREF: sub_80082194+BC?o
                db 0, 0, 0
aStrHeaderX:    db "str_header %X", 0xA, 0x0
                                         ; DATA XREF: sub_80082194+F0?o
                db 0
aCanceledStrFad:db "Canceled STR FadeOut(%x:%x:%x)", 0x0
                                         ; DATA XREF: sub_80082380+A4?o
                db 0
aStreamFilePosE:db "Stream:File Pos Error", 0xA, 0x0
                                         ; DATA XREF: sub_80082448+64?o
                db 0
aStartstreamXVo:db "StartStream(%x:vol=%x)", 0xA, 0x0
                                         ; DATA XREF: sub_80082448+180?o
jpt_80082674:   dw 0x8008272C         ; DATA XREF: sub_80082640+24?r
                dw 0x8008272C         ; jump table for switch statement
                dw 0x8008267C
                dw 0x8008268C
                dw 0x800826CC
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
