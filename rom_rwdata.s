	opt	c+, at+, e+, n-

	section	.RWDATA


    xref aSlpm86247
    xref aSlpm86248
    xref aStageDir
    xref aRadioDat
    xref aFaceDat
    xref aZmovieStr
    xref aVoxDat
    xref aDemoDat
    xref aBrfDat
    xref aComplete
    xref aMemoryCard1
    xref aMemoryCard2
    xref dword_800122D8
    xref dword_800122CC
    xref dword_800122C0
    xref dword_800122B4
    xref dword_800122A8
    xref aSaveData
    xref aSnaChest1
    xref aSnaChest2
    xref aSnaChest3
    xref aSnaHip1
    xref aSnaArmer1
    xref aSnaArmer2
    xref aSnaArmer3
    xref aSnaArmer4
    xref aCbBox11
    xref aCbBox12
    xref aCbBox41
    xref aCbBox42
    xref aCbBox21
    xref aCbBox22
    xref aCbBox41
    xref aCbBox42
    xref aSnaFace
    xref aSnaFace2
    xref aSnaFace3
    xref aSnaMf1
    xref aSnaMf2
    xref aSnaMf3
    xref dword_80012F2C
    xref dword_80012F50
    xref aTlbl
    xref aSending
    xref aReceiving
    xref aReady
    xref aSleeping
    xref aWaitvbl
    xref aPending
    xref aCdlsync
    xref aCdlnop
    xref aCdlsetloc
    xref aCdlplay
    xref aCdlforward
    xref aCdlbackward
    xref aCdlreadn
    xref aCdlstandby
    xref aCdlstop
    xref aCdlpause
    xref aCdlreset
    xref aCdlmute
    xref aCdldemute
    xref dword_800141CC
    xref dword_800141CC
    xref dword_800141CC
    xref aCdlgetlocl
    xref aCdlgetlocp
    xref dword_800141CC
    xref aCdlgettn
    xref aCdlgettd
    xref aCdlseekl
    xref aCdlseekp
    xref dword_800141CC
    xref dword_800141CC
    xref dword_800141CC
    xref dword_800141CC
    xref aCdlreads
    xref dword_800141CC
    xref dword_800141CC
    xref dword_800141CC
    xref dword_800141CC
    xref aNointr
    xref aDataready
    xref aComplete_0
    xref aAcknowledge
    xref aDataend
    xref aDiskerror_0
    xref dword_800141CC
    xref dword_800141CC
    xref aIdBiosCV186199
    xref aIdSysCV1140199
    xref aIdIntrCV175199
    xref aBislpm86247

	xdef aMem
	xdef aPad
	xdef aGv
	xdef aFs
	xdef aDg
	xdef aGcl
	xdef aHzd
	xdef aSound
	xdef aGm
	xdef aStart

dword_8009D2DC: dw 0x21CA, 0x8005B650, 0x8767, 0x800344F8, 0xB997, 0x8006FD00
                                         ; DATA XREF: start+D0?o
                                         ; TEXT:80098FA4?o
                dw 0, 0
off_8009D2FC:   dw aSlpm86247         ; DATA XREF: sub_8002297C+EC?o
                                         ; sub_8002297C+F0?r ...
                                         ; "SLPM_862.47"
                dw aSlpm86248         ; "SLPM_862.48"
                dw 0
dword_8009D308: dw 0x70000, 0x70000, 0x40009, 0x40009, 0x4000F, 0x4000F
                                         ; DATA XREF: sub_80014D98+10?o
                dw 0x4000F, 0x40009, 0x70000
dword_8009D32C: dw 0x8000000, 0x6000400, 0
                                         ; DATA XREF: sub_8001682C+C8?o
                                         ; TEXT:80016C9C?o
                dw 0x200, 0xA000C00, 0
                dw 0xE00, 0
dword_8009D34C: dw 0                  ; DATA XREF: sub_800172D0+4C?o
                dw 0xFFFFF000, 0, 0
dword_8009D35C: dw 0x8001CEE0         ; DATA XREF: sub_80018028+5C?o
                                         ; sub_80018598?o
                dw 0x800189A4
                dw 0x8001E3C0
                dw 0x8001D324
                dw 0x8001B66C
                dw 0x80019D44
                dw 0x8001D5C8
dword_8009D378: dw 0, 0, 0            ; DATA XREF: sub_80018D90+48?o
dword_8009D384: dw 0                  ; DATA XREF: sub_80019FF8+2C?w
                                         ; sub_80019FF8+34?o ...
dword_8009D388: dw 0x1000             ; DATA XREF: sub_80019FF8+38?w
                                         ; sub_8001A3C4+50?r ...
dword_8009D38C: dw 0                  ; DATA XREF: sub_8001A3C4+54?r
dword_8009D390: dw 0                  ; DATA XREF: sub_8001A3C4+64?r
dword_8009D394: dw 0                  ; DATA XREF: sub_8001A3C4+68?r
                dw 0, 0, 0
dword_8009D3A4: dw 0x10001000         ; DATA XREF: sub_8001A048+8?w
                                         ; sub_8001A048+C?o ...
byte_8009D3A8:  db 0, 0x10            ; DATA XREF: sub_8001A3C4+88?r
word_8009D3AA:  dh 0x1000             ; DATA XREF: sub_8001A048+18?w
                                         ; sub_80031BD4+1C?r
dword_8009D3AC: dw 0x10001000         ; DATA XREF: sub_8001A3C4+8C?r
dword_8009D3B0: dw 0x10001000         ; DATA XREF: sub_8001A048+20?w
                                         ; sub_8001A3C4+9C?r ...
dword_8009D3B4: dw 0x1000             ; DATA XREF: sub_8001A3C4+A0?r
                dw 0, 0, 0
dword_8009D3C4: dw 0, 0, 0            ; DATA XREF: sub_8001A774+44?o
dword_8009D3D0: dw 0x4080210, 0x4080318, 0x408041C, 0x8080214, 0x8080320
                                         ; DATA XREF: sub_8001BABC+14?o
                dw 0x8080428, 0x80114, 0x80110, 0x80110, 0x80110, 0x8010C
                dw 0x8010C, 0x8010C, 0x4080314, 0x4080418, 0x808031C
                dw 0x8080424, 0x8080320, 0x8080428, 0xC080328, 0xC080434
                dw 0x8080228, 0xC080234
byte_8009D42C:  db 0xC                ; DATA XREF: TEXT:8001BC2C?w
                                         ; TEXT:8001BC30?o
byte_8009D42D:  db 1                  ; DATA XREF: TEXT:8001BC34?w
byte_8009D42E:  db 8                  ; DATA XREF: TEXT:8001BC38?w
byte_8009D42F:  db 0                  ; DATA XREF: TEXT:8001BC40?w
dword_8009D430: dw 0x1000             ; DATA XREF: sub_8001B31C+64?o
                                         ; sub_8001B31C+6C?r ...
dword_8009D434: dw 0                  ; DATA XREF: sub_8001B31C+70?r
                                         ; sub_8001B66C+33C?r ...
dword_8009D438: dw 0x1000             ; DATA XREF: sub_8001B31C+7C?r
                                         ; sub_8001B66C+348?r ...
dword_8009D43C: dw 0                  ; DATA XREF: sub_8001B31C+80?r
                                         ; sub_8001B66C+34C?r ...
dword_8009D440: dw 0x1000             ; DATA XREF: sub_8001B31C+84?r
                                         ; sub_8001B66C+350?r ...
dword_8009D444: dw 0                  ; DATA XREF: sub_8001B66C+368?r
                                         ; sub_8001BABC+9C?r ...
dword_8009D448: dw 0                  ; DATA XREF: sub_8001B66C+36C?r
                                         ; sub_8001BABC+AC?r ...
dword_8009D44C: dw 0                  ; DATA XREF: sub_8001B66C+374?r
                                         ; sub_8001BABC+B0?r ...
dword_8009D450: dw 0, 0, 0            ; DATA XREF: sub_8001D830:loc_8001D864?o
dword_8009D45C: dw 2                  ; DATA XREF: sub_8001F078+70?r
                                         ; sub_8001F078+C4?r ...
dword_8009D460: dw 0                  ; DATA XREF: TEXT:80014B80?r
                                         ; sub_80018028+60?r ...
dword_8009D464: dw 0                  ; DATA XREF: sub_80017194+A0?r
                                         ; sub_80017194+D0?r ...
dword_8009D468: dw 0xFFFFFFFF         ; DATA XREF: sub_8001F078+40?r
                                         ; sub_8001F078+58?w ...
dword_8009D46C: dw 0x2030100, 0xD86, 0x80020274, 0x64C0, 0x80020318
                                         ; DATA XREF: sub_8001F3CC+74?o
                dw 0xCD3A, 0x80020404, 0x7636, 0x8002033C
dword_8009D490: dw 0                  ; DATA XREF: sub_8002040C+10?o
                dw 4, 0x8009D470
off_8009D49C:   dw aStageDir          ; DATA XREF: sub_80021E2C+14?o
                                         ; sub_80021F0C+4?o ...
                                         ; "STAGE.DIR"
dword_8009D4A0: dw 0                  ; DATA XREF: sub_80021E2C+50?r
                dw aRadioDat          ; "RADIO.DAT"
                dw 0
                dw aFaceDat           ; "FACE.DAT"
                dw 0
                dw aZmovieStr         ; "ZMOVIE.STR"
dword_8009D4B8: dw 0                  ; DATA XREF: sub_80021E2C+5C?r
                dw aVoxDat            ; "VOX.DAT"
                dw 0
                dw aDemoDat           ; "DEMO.DAT"
                dw 0
                dw aBrfDat            ; "BRF.DAT"
                dw 0, 0, 0
dword_8009D4DC: dw 0xFFFFFFFF         ; DATA XREF: sub_80021FE0+38?w
                                         ; sub_80022024+40?w ...
dword_8009D4E0: dw 0                  ; DATA XREF: sub_80022264:loc_80022300?r
                                         ; sub_80022264+B8?w ...
dword_8009D4E4: dw 0                  ; DATA XREF: sub_80022090?r
                                         ; sub_800227A8+3C?w ...
dword_8009D4E8: dw 0                  ; DATA XREF: sub_80022D00+2C?w
                                         ; sub_80022D00:loc_80022D50?o ...
dword_8009D4EC: dw 0                  ; DATA XREF: sub_80022CBC+38?w
                                         ; sub_80022D00+58?r
dword_8009D4F0: dw 0                  ; DATA XREF: sub_80022D00+B0?w
                                         ; sub_80022DCC+20?r
dword_8009D4F4: dw 0                  ; DATA XREF: sub_80022D00+54?r
                                         ; sub_80022D00+6C?w ...
dword_8009D4F8: dw 0                  ; DATA XREF: sub_80022E50+50?w
                                         ; sub_80022E50+130?w ...
dword_8009D4FC: dw 0                  ; DATA XREF: sub_80022E50+C?r
                                         ; sub_80022E50+48?w ...
dword_8009D500: dw 0                  ; DATA XREF: sub_80022E50+EC?o
word_8009D504:  dh 0                  ; DATA XREF: sub_80022E50+E8?r
                                         ; sub_80022E50+128?r ...
word_8009D506:  dh 0                  ; DATA XREF: sub_80022E50+168?r
                                         ; sub_80022E50+19C?w
word_8009D508:  dh 0                  ; DATA XREF: sub_80022E50+1A4?r
                                         ; sub_80022E50+1D8?w
                dh 0
dword_8009D50C: dw 0                  ; DATA XREF: sub_80023860+40?w
                                         ; sub_80023860+88?r ...
dword_8009D510: dw 0xFFFFFFFF         ; DATA XREF: sub_80023D94+24?w
                                         ; sub_800243D8+1C?w ...
dword_8009D514: dw 0                  ; DATA XREF: sub_80023D94+2C?w
                                         ; sub_80024404+18?w ...
dword_8009D518: dw 0                  ; DATA XREF: TEXT:80023A00?r
                                         ; sub_80023D94+10?w ...
dword_8009D51C: dw 1                  ; DATA XREF: TEXT:80023A18?r
                                         ; sub_80023D94+8?w ...
dword_8009D520: dw 0                  ; DATA XREF: TEXT:80023C1C?w
                                         ; sub_80023C40?r ...
dword_8009D524: dw 0                  ; DATA XREF: sub_80024E48+4?r
                                         ; sub_80024E48+40?w ...
dword_8009D528: dw 0x8000000, 0x4000555, 0x2AA0333, 0x2000249, 0x19901C7
                                         ; DATA XREF: sub_800264B0:loc_800264C0?o
                                         ; TEXT:loc_80026614?o ...
                dw 0x1550174, 0x124013B, 0x1000111
dword_8009D548: dw 0                  ; DATA XREF: sub_80029D50+148?o
                dw 0x20
                dw 0x40, 8, 0x800, 0x10000, 0x20000, 0x1000, 4, 1
byte_8009D570:  db 0x20, 0, 0, 0      ; DATA XREF: sub_80029D50+208?o
                dw 0x80, 0x40, 0x10
word_8009D580:  dh 0x110              ; DATA XREF: sub_8003B6D0+C?o
                                         ; sub_8003DF30+30?o ...
                dh 0x9042
                dw 0x414C9043, 0x222020C0, 0x41104110, 0x414C414C, 0x9220
dword_8009D598: dw 0x80000000         ; DATA XREF: sub_800333F8:loc_80033418?o
                                         ; sub_8003B6D0+30?o ...
                dw 0x80018003
                dw 0x80018001
                dw 0x80008000
                dw 0x80008000
                dw 0x80008000
                dw 0x80038000
                dw 0x20002000, 0x2000, 0, 0, 0, 0
                dw 0x22FF, 0x8002C138, 0xD4CB, 0x8002BD34, 0x9906, 0x8002C1B0
                dw 0xC091, 0x8002BB44, 0x7D50, 0x8002BD04, 0xEEE9, 0x8002B8F0
                dw 0x306A, 0x8002B854, 0x9A1F, 0x8002C22C, 0xC8BB, 0x8002C308
                dw 0x24E1, 0x8002C4A8, 0xE43C, 0x8002C6A4, 0xA242, 0x8002C890
                dw 0xDBAB, 0x8002BE20, 0x430D, 0x8002C074, 0xCC85, 0x8002C988
                dw 0x5C9E, 0x8002C72C, 0x4AD9, 0x8002C7C8, 0x698D, 0x8002CA28
                dw 0x226D, 0x8002CAAC, 0x925E, 0x8002CD94, 0xE257, 0x8002CDF4
                dw 0xA2BF, 0x8002CFBC, 0xB96E, 0x8002D0E4, 0xEC9D, 0x8002D188
dword_8009D68C: dw 0                  ; DATA XREF: sub_8002D1DC+18?o
                dw 0x18, 0x8009D5CC
dword_8009D698: dw 0x2010000          ; DATA XREF: TEXT:8002EA7C?o
dword_8009D69C: dw 0x42801EE, 0x666056E, 0x7DA072E, 0x8F4086E, 0x9DA096C
                                         ; DATA XREF: sub_80035F34+2C?o
                dw 0xA9A0A3E, 0xB3E0AEE, 0xBCE0B88, 0xC4C0C0E, 0xCBC0C86
                dw 0xD200CEF, 0xD780D4E, 0xDC80DA2, 0xE100DEE, 0xE520E32
                dw 0xE8C0E6F, 0xEC00EA6, 0xEEF0ED8, 0xF190F04, 0xF3F0F2C
                dw 0xF600F50, 0xF7E0F6F, 0xF980F8B, 0xFAE0FA3, 0xFC20FB8
                dw 0xFD20FCA, 0xFE00FD9, 0xFEB0FE6, 0xFF30FEF, 0xFFA0FF7
                dw 0xFFE0FFC, 0xFFF0FFF, 0x28800B2, 0x4C003C6, 0x6440590
                dw 0x77406E4, 0x86C07F6, 0x94008DA, 0x9F809A0, 0xA9A0A4C
                dw 0xB280AE2, 0xBA80B6A, 0xC1C0BE4, 0xC860C52, 0xCE40CB6
                dw 0xD3A0D10, 0xD8A0D62, 0xDD10DAE, 0xE130DF2, 0xE4F0E32
                dw 0xE860E6B, 0xEB80E9F, 0xEE50ECF, 0xF0E0EFA, 0xF340F22
                dw 0xF560F46, 0xF750F66, 0xF900F83, 0xFA90F9D, 0xFBE0FB4
                dw 0xFD10FC8, 0xFE20FDA, 0xFF00FE9, 0xFFC0FF6, 0x196005C
                dw 0x3740298, 0x4E00434, 0x60C057C, 0x70A0690, 0x7E6077C
                dw 0x8AA084A, 0x9580902, 0x9F409A8, 0xA840A3E, 0xB060AC6
                dw 0xB7C0B42, 0xBEA0BB4, 0xC4E0C1D, 0xCAC0C7E, 0xD020CD7
                dw 0xD510D2A, 0xD9A0D76, 0xDDF0DBE, 0xE1E0E00, 0xE590E3C
                dw 0xE900E75, 0xEC20EAA, 0xEF10EDA, 0xF1C0F07, 0xF440F30
                dw 0xF690F57, 0xF8B0F7A, 0xFAA0F9A, 0xFC60FB8, 0xFE00FD3
                dw 0xFF70FEC, 0x1100038, 0x28401D2, 0x3BE0326, 0x4D0044C
                dw 0x5C2054C, 0x69C0632, 0x7600700, 0x81407BC, 0x8BA0868
                dw 0x9520906, 0x9DE099A, 0xA620A20, 0xADC0AA0, 0xB4C0B14
                dw 0xBB80B83, 0xC1B0BEA, 0xC780C4A, 0xCD00CA6, 0xD230CFA
                dw 0xD710D4A, 0xDBA0D96, 0xDFE0DDD, 0xE400E20, 0xE7C0E5E
                dw 0xEB60E9A, 0xEEC0ED1, 0xF1F0F06, 0xF4E0F37, 0xF7C0F65
                dw 0xFA60F91, 0xFCD0FBA, 0xFF20FE0, 0xC00026, 0x1DC0152
                dw 0x2DE0260, 0x3CA0356, 0x4A4043A, 0x56E050C, 0x62C05CE
                dw 0x6DC0684, 0x7800730, 0x81C07D0, 0x8AE0866, 0x93A08F6
                dw 0x9BC097C, 0xA3A09FC, 0xAAF0A74, 0xB200AE8, 0xB8A0B56
                dw 0xBF00BBE, 0xC500C20, 0xCAC0C7F, 0xD040CD9, 0xD580D2F
                dw 0xDA80D81, 0xDF60DD0, 0xE3E0E1A, 0xE840E62, 0xEC80EA6
                dw 0xF080EE8, 0xF440F26, 0xF7F0F62, 0xFB60F9B, 0xFEC0FD2
                dw 0x8C001C, 0x16600FA, 0x23401CE, 0x2F80298, 0x3B40358
                dw 0x4680410, 0x51404BE, 0x5B80568, 0x6560608, 0x6EE06A4
                dw 0x7820738, 0x80E07C8, 0x8960852, 0x91808D8, 0x9960958
                dw 0xA1009D4, 0xA860A4C, 0xAF80AC0, 0xB660B2F, 0xBD00B9C
                dw 0xC360C04, 0xC9A0C69, 0xCFB0CCB, 0xD580D2A, 0xDB30D86
                dw 0xE0A0DE0, 0xE600E36, 0xEB20E8A, 0xF020EDA, 0xF500F2A
                dw 0xF9C0F76, 0xFE40FC0, 0x680014, 0x11000BC, 0x1B20162
                dw 0x2520204, 0x2F002A2, 0x38A033C, 0x42003D4, 0x4B4046A
                dw 0x54404FC, 0x5D2058C, 0x65E0618, 0x6E806A4, 0x76E072A
                dw 0x7F207B0, 0x8740832, 0x8F208B4, 0x9700932, 0x9EC09AE
                dw 0xA640A28, 0xADA0AA0, 0xB500B16, 0xBC20B8A, 0xC340BFA
                dw 0xCA20C6A, 0xD100CD8, 0xD7A0D46, 0xDE40DB0, 0xE4C0E18
                dw 0xEB20E80, 0xF160EE4, 0xF7A0F48, 0xFDB0FAA, 0x4F000F
                dw 0xCF008F, 0x14F010F, 0x1CF018F, 0x24F020F, 0x2CF028F
                dw 0x34F030F, 0x3CF038F, 0x44F040F, 0x4CF048F, 0x54F050F
                dw 0x5CF058F, 0x64F060F, 0x6CF068F, 0x74F070F, 0x7CF078F
                dw 0x84F080F, 0x8CF088F, 0x94F090F, 0x9CF098F, 0xA4F0A0F
                dw 0xACF0A8F, 0xB4F0B0F, 0xBCF0B8F, 0xC4F0C0F, 0xCCF0C8F
                dw 0xD4F0D0F, 0xDCF0D8F, 0xE4F0E0F, 0xECF0E8F, 0xF4F0F0F
                dw 0xFCF0F8F, 0x3C000C, 0x9E006C, 0x10000CE, 0x1660132
                dw 0x1CC0198, 0x2340200, 0x29E0269, 0x30A02D4, 0x3780340
                dw 0x3E803B0, 0x4580420, 0x4CC0492, 0x5400506, 0x5B8057C
                dw 0x63205F4, 0x6AE066F, 0x72A06EC, 0x7AA076A, 0x82C07EC
                dw 0x8B2086E, 0x93808F4, 0x9C2097E, 0xA4E0A08, 0xADE0A96
                dw 0xB700B26, 0xC040BB8, 0xC9A0C4E, 0xD360CE8, 0xDD20D84
                dw 0xE740E22, 0xF180EC6, 0xFC00F6C, 0x2C0008, 0x760050
                dw 0xC2009C, 0x11000E8, 0x1600138, 0x1B4018A, 0x20A01DE
                dw 0x2620235, 0x2BD028F, 0x31C02EC, 0x37C034C, 0x3E003AE
                dw 0x4480414, 0x4B4047E, 0x52204EA, 0x596055C, 0x60C05D0
                dw 0x6860648, 0x70606C6, 0x78A0748, 0x81207CE, 0x8A0085A
                dw 0x93408EA, 0x9CE0980, 0xA6E0A1E, 0xB140AC0, 0xBC20B6A
                dw 0xC780C1C, 0xD360CD6, 0xDFC0D98, 0xECE0E64, 0xFAA0F3A
                dw 0x200006, 0x56003A, 0x8E0072, 0xC900AB, 0x10700E8
                dw 0x1480127, 0x18B0169, 0x1D201AE, 0x21C01F6, 0x26A0242
                dw 0x2BA0292, 0x31002E4, 0x368033C, 0x3C60396, 0x42803F6
                dw 0x48E045A, 0x4FA04C4, 0x56C0532, 0x5E405A6, 0x6620622
                dw 0x6E606A2, 0x772072C, 0x80807BC, 0x8A60856, 0x94E08F8
                dw 0xA0009A6, 0xAC00A5E, 0xB8E0B26, 0xC6C0BFC, 0xD5E0CE4
                dw 0xE660DE0, 0xF8A0EF4, 0x160004, 0x3B0028, 0x64004F
                dw 0x8E0078, 0xBC00A4, 0xEC00D4, 0x1200106, 0x157013B
                dw 0x1910174, 0x1CF01B0, 0x21001EF, 0x2560233, 0x2A0027B
                dw 0x2F002C8, 0x3440318, 0x39C036F, 0x3FC03CC, 0x460042E
                dw 0x4CD0496, 0x5400506, 0x5BC057E, 0x64205FE, 0x6D20688
                dw 0x76C071E, 0x81607C0, 0x8CC086E, 0x9960930, 0xA760A04
                dw 0xB700AEE, 0xC8A0BF8, 0xDD20D28, 0xF560E8A, 0xD0002
                dw 0x250019, 0x400032, 0x5C004E, 0x7C006C, 0x9F008D
                dw 0xC400B1, 0xED00D8, 0x1190102, 0x1480130, 0x17C0162
                dw 0x1B40198, 0x1F001D1, 0x230020F, 0x2760252, 0x2C1029A
                dw 0x31202E8, 0x36A033D, 0x3C80398, 0x42F03FA, 0x49E0466
                dw 0x51804DA, 0x59E055A, 0x62E05E4, 0x6D0067E, 0x7840728
                dw 0x84C07E4, 0x93008BA, 0xA3809B0, 0xB720ACE, 0xCF40C28
                dw 0xEFC0DE2, 0x60001, 0x12000C, 0x210019, 0x320029
                dw 0x46003C, 0x5C0050, 0x750068, 0x920083, 0xB100A1
                dw 0xD400C2, 0xFA00E6, 0x124010F, 0x153013B, 0x186016C
                dw 0x1BE01A2, 0x1FC01DC, 0x23E021C, 0x2880262, 0x2D802B0
                dw 0x3310304, 0x3920360, 0x3FE03C6, 0x4740438, 0x4F804B4
                dw 0x58C0540, 0x63205DC, 0x6F0068E, 0x7CC075A, 0x8D00848
                dw 0xA100968, 0xBB40AD2, 0xE420CCC, 0
                dw 0x20001, 0x70004, 0xD000A, 0x170012, 0x22001C, 0x310029
                dw 0x420039, 0x56004C, 0x6D0061, 0x88007A, 0xA60097
                dw 0xC900B7, 0xF000DC, 0x11B0105, 0x14B0132, 0x1810166
                dw 0x1BC019E, 0x1FF01DD, 0x2490223, 0x29B0271, 0x2F602C8
                dw 0x35D0328, 0x3D00394, 0x4520410, 0x4E6049A, 0x5920538
                dw 0x65A05F2, 0x74A06CC, 0x87807D8, 0xA0C0930, 0xCB80B24
dword_8009DE1C: dw 0x10000, 0x10000, 0x8000, 0x5555, 0x4000, 0x3333
                                         ; DATA XREF: sub_800353E4+50?o
                                         ; sub_80036388+D0?o
                dw 0x2AAA, 0x2492, 0x2000, 0x1C71, 0x1999, 0x1745, 0x1555
                dw 0x13B1, 0x1249, 0x1111
dword_8009DE5C: dw 0x8001000, 0x4000555, 0x2AA0333, 0x2000249, 0x19901C7
                                         ; DATA XREF: sub_800356FC+68?o
                dw 0x1550174, 0x124013B, 0x1000111
dword_8009DE7C: dw 0                  ; DATA XREF: sub_800356FC+7C?w
                                         ; sub_800356FC+80?o ...
dword_8009DE80: dw 0                  ; DATA XREF: sub_800356FC+90?r
dword_8009DE84: dw 0                  ; DATA XREF: sub_800356FC+84?w
                                         ; sub_800356FC+9C?r
dword_8009DE88: dw 0                  ; DATA XREF: sub_800356FC+A0?r
dword_8009DE8C: dw 0                  ; DATA XREF: sub_800356FC+88?w
                                         ; sub_800356FC+A4?r
                dw 0, 0, 0
dword_8009DE9C: dw 0                  ; DATA XREF: sub_80035F34:loc_80035F8C?w
                                         ; sub_80035F34+5C?o ...
dword_8009DEA0: dw 0                  ; DATA XREF: sub_80035F34+6C?r
dword_8009DEA4: dw 0                  ; DATA XREF: sub_80035F34+60?w
                                         ; sub_80035F34+78?r
dword_8009DEA8: dw 0                  ; DATA XREF: sub_80035F34+7C?r
dword_8009DEAC: dw 0                  ; DATA XREF: sub_80035F34+64?w
                                         ; sub_80035F34+80?r
                dw 0, 0, 0
word_8009DEBC:  dh 0x78               ; DATA XREF: sub_80036BA4+C?o
                                         ; sub_80036BA4+54?r ...
word_8009DEBE:  dh 0x25               ; DATA XREF: sub_80036BA4+14?o
                                         ; sub_80037600+18?o
                dw 0x190058
dword_8009DEC4: dw 0x190068, 0x1F0068, 0x1F0079, 0x280079, 0x280079
                                         ; DATA XREF: sub_80037600+40?o
                dw 0x200079, 0x200087, 0x2A0087, 0x450087, 0x250058
                dw 0x400058, 0x290060, 0x290060, 0x230060, 0x230068
                dw 0x260068, 0x260071, 0x2D0071, 0x3E0071, 0x2D0064
                dw 0x2D0064, 0x280064, 0x28006C, 0x30006C, 0x30006C
                dw 0x2D006C, 0x450071, 0x400058, 0x370060, 0x410079
                dw 0x4A0079, 0x540058, 0x430058, 0x550064, 0x450064
                dw 0x550060, 0x430060, 0x370064, 0x450079, 0x4A0060
                dw 0x540058, 0x550058, 0x550060, 0x570064, 0x570079
                dw 0x4E0079, 0x490079, 0x4D006C, 0x4E006C, 0x4D0079
                dw 0x49006C, 0x41006C, 0x3E0079, 0x2A0064, 0x590087
                dw 0x620079, 0x610079, 0x6C0058, 0x760058, 0x820058
                dw 0x7A0058, 0x710079, 0x710079, 0x750079, 0x750068
                dw 0x6C0068, 0x6C0079, 0x670079, 0x670079, 0x660079
                dw 0x660068, 0x620068, 0x5F0079, 0x6C0060, 0x720060
                dw 0x800060, 0x5E0060, 0x6C0064, 0x700064, 0x7F0064
                dw 0x610064, 0x5F0058, 0x5E0060, 0x590064, 0x6C0079
                dw 0x6C0058, 0x6C0060, 0x6C0064, 0x70006C, 0x6C0064
                dw 0x72006C, 0x760060, 0x7F0058, 0x7A0064, 0x800079
                dw 0x820060, 0x860058, 0x9C0058, 0x7E0058, 0x940079
                dw 0x840079, 0x9A0060, 0x830060, 0x990064, 0x8A0064
                dw 0x97006B, 0x8A006B, 0x89006B, 0x960071, 0x890071
                dw 0x860071, 0x840058, 0x830060, 0x7E0064, 0x960079
                dw 0x940071, 0x970079, 0x99006B, 0x9A0064, 0x9C0060
                dw 0xAD0058, 0xC70079, 0xB50079, 0xCF0058, 0xB30058
                dw 0xCD0060, 0xBB0060, 0xB80064, 0xB80071, 0xC00071
                dw 0xC30071, 0xC00064, 0xCF0071, 0xCD0058, 0xCC0060
                dw 0xC70064, 0xB50079, 0xB30058, 0xB20060, 0xAD0064
                dw 0xB20079, 0xBB0064, 0xC30064, 0xCC0064, 0xD50064
                dw 0xE00079, 0xF10079, 0xE70058, 0xD20058, 0xDB0058
                dw 0xD30058, 0xDC0060, 0xD30060, 0xDC0064, 0xE10064
                dw 0xEB0064, 0xE30064, 0xED0060, 0xE10060, 0xDD0064
                dw 0xE7006C, 0xE30058, 0xEB0060, 0xE00064, 0xED0079
                dw 0xF10060, 0xD30058, 0xD50064, 0xD20079, 0xD30058
                dw 0xDB0060, 0xDC0058, 0xDC0060, 0xDD0064, 0xF4006C
                dw 0x10A0058, 0xEC0058, 0x1020079, 0xF20079, 0x1080060
                dw 0xF10060, 0x1070064, 0xF70064, 0x1040071, 0xF80071
                dw 0x105006C, 0xF8006C, 0xF7006C, 0xF40071, 0xF20058
                dw 0xF10060, 0xEC0064, 0x1070079, 0x1050064, 0x104006C
                dw 0x1020071, 0x10A0079, 0x1080058, 0x10E0060, 0x1240058
                dw 0x10C0058, 0x11E0060, 0x1240060, 0x1270058, 0x10B0061
                dw 0x11A0064, 0x1130064, 0x115006B, 0x106006B, 0x1100079
                dw 0x1130079, 0x110006B, 0x1150079, 0x11D006B, 0x11D0087
                dw 0x1270087, 0x11E0087, 0x127006A, 0x11E0087, 0x120006A
                dw 0x120006A, 0x127006A, 0x11A0061, 0x11E0064, 0x10B0060
                dw 0x1060064, 0x10C0079, 0x10E0060, 0x430058, 0x370064
                dw 0x350079, 0x2F007D, 0x350087, 0x117007D, 0x11A007D
                dw 0x2F0087, 0x11A0087, 0x1170087, 0x7D
dword_8009E280: dw 0                  ; DATA XREF: sub_80037AE4+48?r
                                         ; sub_80037AE4+6C?w ...
dword_8009E284: dw 0                  ; DATA XREF: sub_80037AE4+58?r
                                         ; sub_80037B64+68?r ...
dword_8009E288: dw 0                  ; DATA XREF: sub_80037AE4+60?r
                                         ; sub_80037B64+A8?w
dword_8009E28C: dw 0                  ; DATA XREF: sub_80038070:loc_800382BC?w
                                         ; sub_80038070+2C0?w ...
dword_8009E290: dw 0x8003CC94         ; DATA XREF: sub_8003884C+B4?r
                                         ; sub_8003884C+C0?o ...
                dw 0x8003B474
                dw 0x80042700
                dw 0x8003CBF0
                dw 0x8003EC2C
                dw 0x8003F7E0
                dw 0x80042848
                dw 0x800494C4
                dw 0
dword_8009E2B4: dw 0x8003B554         ; DATA XREF: sub_800387E8+4?r
                                         ; sub_800387E8+18?o ...
                dw 0x8004271C
                dw 0x8003CC74
                dw 0x8003ECAC
                dw 0x8003F838
                dw 0x80042980
                dw 0
dword_8009E2D0: dw 0                  ; DATA XREF: sub_8003884C+1C?o
                                         ; sub_80038A88+C?r ...
dword_8009E2D4: dw 0                  ; DATA XREF: sub_800386A4+14?r
                                         ; sub_80038A88+94?w ...
dword_8009E2D8: dw 0                  ; DATA XREF: sub_80038A88+1C?r
                                         ; sub_80038A88+7C?w ...
dword_8009E2DC: dw 0                  ; DATA XREF: sub_8003884C+48?w
dword_8009E2E0: dw 0                  ; DATA XREF: sub_8003884C+54?w
dword_8009E2E4: dw 0                  ; DATA XREF: sub_80038B34+4?w
                                         ; sub_80038B34+8?o ...
dword_8009E2E8: dw 0                  ; DATA XREF: sub_80038B34+C?w
dword_8009E2EC: dw 0                  ; DATA XREF: sub_80038B34+14?w
                                         ; sub_80038B4C+8?r ...
dword_8009E2F0: dw 0x64808080         ; DATA XREF: sub_80038B4C+48?w
                                         ; sub_80038B98+10?w
dword_8009E2F4: dw 0x808000, 0x100000, 0xA0, 0x10, 0xA0A0, 0x808
                                         ; DATA XREF: sub_800391D0+4F0?o
dword_8009E30C: dw 0xC1C5080          ; DATA XREF: sub_8003A978+4C?o
dword_8009E310: dw 0x72C5C80, 0xC1C509C, 0x73A6380, 0xC1C50B8, 0x72C5CB4
                                         ; DATA XREF: sub_80039EC4+B8?o
                dw 0xC3A6A8A, 0x73A768A
byte_8009E32C:  db 0xBC, 0x63         ; DATA XREF: sub_80039EC4+150?o
byte_8009E32E:  db 0x24               ; DATA XREF: sub_80039EC4+16C?r
                db 3
dword_8009E330: dw 0x100A6A80         ; DATA XREF: sub_8003A664+214?o
byte_8009E334:  db 0xC4               ; DATA XREF: sub_8003A0BC+38?o
                                         ; sub_8003A0BC+6C?r ...
byte_8009E335:  db 0x66               ; DATA XREF: sub_8003A0BC+9C?r
                                         ; sub_8003A2D0+98?r ...
                dh 0x161C
byte_8009E338:  db 0, 0               ; DATA XREF: sub_8003A664+144?o
                                         ; sub_8003AA2C+48?o
word_8009E33A:  dh 0                  ; DATA XREF: sub_8003A664+80?o
                dw 0, 0, 0, 0, 0, 0
                dw 0xC2100000, 0, 0, 0, 0, 0, 0, 0
                dw 0xC2100000, 0, 0, 0, 0, 0, 0, 0
                dw 0xC2100000, 0, 0, 0, 0, 0, 0, 0
                dw 0xC2100000
dword_8009E3B8: dw 0x182589, 0x184789, 0x182589, 0x338918
                                         ; DATA XREF: sub_80039EC4+14?o
                                         ; sub_8003A0BC+10?o ...
dword_8009E3C8: dw 0x1371D07, 0x1373207, 0x2032E21
                                         ; DATA XREF: sub_8003A664+14C?o
dword_8009E3D4: dw 0x48A000, 0x6E6E, 0xDE, 0x181800
                                         ; DATA XREF: sub_8003AA2C+134?o
                                         ; sub_8003AA2C+268?o
dword_8009E3E4: dw 0x800115CC         ; DATA XREF: sub_8003B614+8?o
                dw 0x8001158C
                dw 0x80011558
                dw 0x80011524
                dw 0x800114F8
                dw 0x80011494
                dw 0x80011434
                dw 0x800113D0
                dw 0x80011378
                dw 0x80011330
                dw 0x800112D4
                dw 0x8001127C
                dw 0x80011224
                dw 0x800111B0
                dw 0x80011150
                dw 0x800110E8
                dw 0x800110AC
                dw 0x80011060
                dw 0x8001101C
                dw 0x80010FD0
                dw 0x80010F84
                dw 0x80010F50
                dw 0x80010F08
                dw 0x80010EAC
dword_8009E444: dw 0x80011644         ; DATA XREF: sub_8003B614+4C?r
dword_8009E448: dw 0x80011614         ; DATA XREF: sub_8003B614+5C?r
dword_8009E44C: dw 0x6A9014B0, 0x6C906B90, 0x6E906D90, 0x7C8015D0, 0x44524148
                                         ; DATA XREF: sub_8003B614+A0?o
                dw 0x5845202C, 0x4D455254, 0xD0428220, 0x81298206, 0x902F8127
                dw 0x81499048, 0x810D8127, 0xD004812A, 3
off_8009E484:   dw aCigs              ; DATA XREF: sub_8003B5E0?o
                                         ; sub_8003B8F0+258?o
                                         ; "CIGS"
                dw 0xE, 0x800AB558, 0x1E, 0x800AB550, 0x11, 0x800AB548
                dw 0x11, 0x800AB540, 0x11, 0x800AB538, 0xF, 0x800AB530
                dw 0x10, 0x800AB528, 0x13, 0x800AB520, 0x12, 0x800AB518
                dw 0x19, 0x800AB510, 0x20, 0x800AB508, 0x1F, 0x800AB500
                dw 0xC, 0x800AB4F8, 0x16, 0x80011680, 0x15, 0x80011674
                dw 0x15, 0x800AB4F0, 0x17, 0x800AB4E8, 0x1B, 0x800AB4E0
                dw 0x1A, 0x800AB4D8, 0x14, 0x800AB4D0, 0x1C, 0x800AB4C8
                dw 0x18, 0x800AB4C0, 0x1D, 0x800AB4B8, 0xD
dword_8009E544: dw 0xB80010, 1, 0x6000, 0x9000, 0x8003D64C, 0x8003D594
                                         ; DATA XREF: sub_8003D6A8+C?o
                dw 0
                dw 0xB80100, 2, 0x3000, 0xC000, 0x8003D594, 0x8003D5F0
                dw 0
off_8009E57C:   dw aSocom             ; DATA XREF: sub_8003DED8+18?o
                                         ; sub_8003DED8:loc_8003DEFC?o ...
                                         ; "SOCOM"
                dw 1, 0x800AB5BC, 3, 0x800AB5B4, 5, 0x800AB5AC, 0xA
                dw 0x800AB5A4, 9, 0x800116DC, 8, 0x800AB5A0, 7, 0x800AB598
                dw 6, 0x800AB590, 0xB, 0x800AB588, 4
dword_8009E5CC: dw 0x80011A8C         ; DATA XREF: sub_8003E030+8?o
                                         ; sub_8003E030+38?r ...
                dw 0x80011A30
                dw 0x800119C0
                dw 0x80011954
                dw 0x800118DC
                dw 0x8001187C
                dw 0x80011838
                dw 0x800117C4
                dw 0x80011750
                dw 0x800116E8
off_8009E5F4:   dw aLife              ; DATA XREF: sub_8003F30C+18?o
                                         ; sub_8003F4B8+4?o
                                         ; "LIFE"
                dw 0x1F7F8F10, 0x3FDF
off_8009E600:   dw aO2                ; DATA XREF: sub_8003F30C+D4?o
                                         ; "O2"
                dw 0x1FC03F1F, 0x1FF7F
dword_8009E60C: dw 0x6D5D2477, 0x257B6B2E, 0x6F7F
                                         ; DATA XREF: sub_8003A664+88?o
                                         ; sub_8003FD50+18?o
dword_8009E618: dw 0x2070001, 0x7020100, 0x7020107, 0x2070701, 0x7020900
                                         ; DATA XREF: sub_80040034+108?o
                                         ; sub_800401AC+80?o
                dw 0x7020907, 0x2070F01
dword_8009E634: dw 0x3D472E           ; DATA XREF: sub_80040034+110?w
                                         ; sub_800401AC+84?w
dword_8009E638: dw 0x3D472E           ; DATA XREF: sub_80040034+114?w
dword_8009E63C: dw 0x2050001, 0x6020100, 0x6020105, 0x2050601, 0x6020800
                                         ; DATA XREF: sub_80040034+38?o
                                         ; sub_800401AC+30?o
                dw 0x6020805, 0x2050D01
dword_8009E658: dw 0x3D472E           ; DATA XREF: sub_80040034+5C?w
                                         ; sub_800401AC+54?w
dword_8009E65C: dw 0x3D472E           ; DATA XREF: sub_80040034+60?w
dword_8009E660: dw 0xC0F0A0A          ; DATA XREF: sub_80040034:loc_8004014C?o
                                         ; sub_800401AC+4C?o
dword_8009E664: dw 0x30503A78, 0x601A1F13, 0x2053774, 0x60293020, 0x20537C7
                                         ; DATA XREF: sub_80040DC4+D0?o
                dw 0x60293020, 0x2056B74, 0x60293020, 0x2056BC7, 0x60293020
                dw 0x14E3779, 0x60293020, 0x14E6C79, 0x60293020, 0xA3E2681
                dw 0x601A1F13, 0xA3E7581, 0x601A1F13, 0xB194C5A, 0x601A1F13
                dw 0xB194CCD, 0x601A1F13, 0x12B2654, 0x601A1F13, 0x12B26C1
                dw 0x601A1F13, 0x12B7E54, 0x601A1F13, 0x12B7EC1, 0x601A1F13
                dw 0x1242E5B, 0x601A1F13, 0x1242EC1, 0x601A1F13, 0x124765B
                dw 0x601A1F13, 0x12476C1, 0x601A1F13
dword_8009E6FC: dw 0x4DD651DE, 0x516255D6, 0x556A4D6A
                                         ; DATA XREF: sub_8004064C+54?o
word_8009E708:  dh 0                  ; DATA XREF: sub_8004158C+E8?r
                                         ; sub_8004158C+F4?o ...
word_8009E70A:  dh 0                  ; DATA XREF: sub_8004158C+F8?r
                                         ; sub_8004158C+FC?r ...
dword_8009E70C: dw 0xFFFFFFFF         ; DATA XREF: sub_8004158C+128?r
                                         ; sub_80042198+228?r ...
dword_8009E710: dw 0                  ; DATA XREF: sub_80042198+178?r
                                         ; sub_80042198+290?r ...
dword_8009E714: dw 0x240022E, 0x45F023A, 0x63F0221, 0x62D062B, 0x62A062F
                                         ; DATA XREF: sub_80042BF4+114?o
                                         ; sub_80043220+110?o
                dw 0x37D037B, 0
dword_8009E730: dw 0x80043678         ; DATA XREF: TEXT:80044A3C?o
                dw 0x80043A24
                dw 0x80043FD0
                dw 0x800442E4
                dw 0x800445F8
dword_8009E744: dw 0x800AB6A4         ; DATA XREF: TEXT:80044A18?o
                dw 0x800AB6A0
                dw 0x800AB69C
                dw 0x800AB698
                dw 0x800AB694
                dw 0x800AB690
dword_8009E75C: dw 0                  ; DATA XREF: sub_80044A9C+CC?w
                                         ; sub_80044BC0?o ...
                dw 0, 0, 0
dword_8009E76C: dw 0x100FF, 0xFF000100
                                         ; DATA XREF: sub_80048FD4+A4?o
dword_8009E774: dw 0x24A51421, 0x45AD3529, 0x88A5631, 0x217414EF, 0x363929D6
                                         ; DATA XREF: sub_8004983C+108?o
                dw 0x10750C13, 0x195A14D8, 0xEEB19BC, 0x12211, 0xEA00310
                dw 0x20000000, 0xEC00331, 0x23210012, 0xEB20243, 0x33332213
                dw 0xEA10134, 0x44422233, 0xEA10123, 0x34322343, 0xED11212
                dw 0x24444443, 0xEE02221, 0x24444343, 0xEE30132, 0x23444233
                dw 0xEE00133, 0x22334301, 0xEB00123, 0x21224420, 0xD000113
                dw 0x22100100, 0xA100202, 0x32112344, 0x1100201, 0x23233200
                dw 0x1000200, 0x2212222, 0x1000220, 0, 0
                dw 0x24A51421, 0x45AD3529, 0x88A5631, 0x217414EF, 0x363929D6
                dw 0x10750C13, 0x195A14D8, 0xEEB19BC, 0x11124444, 0x2221131
                dw 0x21000134, 0x2210222, 0x1114, 0x1230, 0x10000124
                dw 0x241, 0x11123234, 0x20234, 0x43334444, 0x10234
                dw 0x44444444, 0x221233, 0x44444444, 0x1011133, 0x34444444
                dw 0x2100123, 0x34444334, 0x1110023, 0x33444421, 0x1000012
                dw 0x33433443, 0x100002, 0x23320211, 0xB001001, 0x13333233
                dw 0xAC10000, 0x1333322, 0xCB10100, 0, 0
                dw 0x24A51421, 0x45AD3529, 0x88A5631, 0x217414EF, 0x363929D6
                dw 0x10750C13, 0x195A14D8, 0xEEB19BC, 0x1343023, 0x1102021
                dw 0x13444312, 0x1001020, 0x3444301, 0x120, 0x22343113
                dw 0x10021, 0x32211213, 0x10012, 0x33334433, 0x21002
                dw 0x24444433, 0x1002002, 0x24444334, 0x2210001, 0x23444314
                dw 0xB100010, 0x12444302, 0xDA10011, 0x22344421, 0xEBA0002
                dw 0x22212333, 0xEEC1001, 0x21310100, 0xEC10100, 0x12132344
                dw 0xC312200, 0x2112222, 0x4233101, 0, 0
                dw 0x2CA51C21, 0x456B3908, 0x5E3151CE, 0x217414EF, 0x363929D6
                dw 0x10550C13, 0x151814B7, 0x19BC195A, 0x34455555, 0xFA12022
                dw 0x255300, 0xFA12300, 0x241CD, 0xFA12240, 0x21000BDA
                dw 0xFA11234, 0x445521CD, 0xFB11223, 0x34455300, 0xFDA1123
                dw 0x33445552, 0xFFA1122, 0x33445551, 0xFFA1112, 0x12344551
                dw 0xFFB1221, 0x31344551, 0xFFDA122, 0x31334451, 0xFFFA112
                dw 0x22014451, 0xFFFB012, 0x24213451, 0xFFFB111, 0x22313441
                dw 0xFFFB201, 0x22312341, 0xFFFA310, 0, 0
                dw 0x14A90425, 0x35B1252D, 0x88A4635, 0x217414EF, 0x363929D6
                dw 0x49035844, 0x2A4139A2, 0x1E8316E0, 0x10013444, 0xE021020
                dw 0x12221234, 0xA010031, 0x12224, 0x32, 0x10001224
                dw 0x200030, 0x10022324, 0x410332, 0x32233434, 0x210333
                dw 0x44444444, 0x110233, 0x44444444, 0xA010133, 0x44444434
                dw 0xCA10133, 0x34444432, 0xECBA023, 0x34433443, 0xEEDD013
                dw 0x33421211, 0xEEED102, 0x23333222, 0xEEEC101, 0x12334310
                dw 0xEED0100, 0x1233444, 0xEEA1002, 0, 0
                dw 0x14A90425, 0x35B1252D, 0x88A4635, 0x217414EF, 0x363929D6
                dw 0x44693427, 0x60CD508B, 0x64896CEF, 0x11001123, 0xED00210
                dw 0x10000003, 0xEB01100, 0x11201013, 0xB200210, 0x12212124
                dw 0xB020221, 0x22322234, 0xC211123, 0x44322144, 0xDB10123
                dw 0x33321234, 0xEC01012, 0x23211023, 0xEEB0112, 0x22122102
                dw 0xEED1121, 0x21222332, 0xEED2122, 0x10121100, 0xEEC0122
                dw 0x10123433, 0xEEA0021, 0x12222100, 0xEC00021, 0x1221111
                dw 0xEA00102, 0x22222333, 0xB000301, 0, 0
aBislpm99999:   db "BISLPM-99999        ", 0x0
                                         ; DATA XREF: sub_8004983C+224?o
                                         ; sub_8004983C+2B8?o ...
                db 0, 0, 0
dword_8009EB4C: dw 0x800AB6F8         ; DATA XREF: sub_8004C418+38?o
                dw 0x8001203C
                dw 0x80012020
                dw 0x80012008
                dw 0x80011FEC
                dw 0x80011FC4
                dw 0x80011FB0
                dw 0x80011F90
                dw 0x80011F6C
                dw 0x80011F5C
                dw 0x80011F34
                dw 0x80011F18
dword_8009EB7C: dw 0x800AB6F8         ; DATA XREF: sub_8004C418+70?o
                dw 0x800120B4
                dw 0x80012098
                dw 0x80012008
                dw 0x80012078
                dw 0x80011FC4
                dw 0x80012064
                dw 0x80011F90
                dw 0x80011F6C
                dw 0x80012054
                dw 0x80011F34
                dw 0x80011F18
dword_8009EBAC: dw 0x800120E4         ; DATA XREF: sub_8004C418+68C?o
                dw 0x800120CC
dword_8009EBB4: dw 0x8001210C         ; DATA XREF: sub_8004C418+65C?o
                dw 0x80012100
dword_8009EBBC: dw 0                  ; DATA XREF: sub_8004A87C+18?o
                                         ; sub_8004C418+40?o ...
dword_8009EBC0: dw 0                  ; DATA XREF: sub_8004C418+54?w
                                         ; sub_8004C418+90?w
                dw aComplete          ; "COMPLETE"
dword_8009EBC8: dw 0                  ; DATA XREF: sub_8004C418+60?w
                                         ; sub_8004C418+9C?w
                dw aError             ; "ERROR"
dword_8009EBD0: dw 0x4F009B, 0x4A00A0, 0x4F00A5, 0x80808080
                                         ; DATA XREF: sub_8004B0A0+7F8?o
dword_8009EBE0: dw 0xB8009C, 0xBC00A0, 0xB800A4, 0x80808080
                                         ; DATA XREF: sub_8004B0A0+828?o
off_8009EBF0:   dw dword_800AB728     ; DATA XREF: sub_8004B0A0+418?o
                dw dword_800AB724
                dw dword_800AB720
                dw aEx                ; "EX"
off_8009EC00:   dw aMemoryCard1       ; DATA XREF: sub_8004BE98+3C?o
                                         ; "MEMORY CARD 1"
                dw aMemoryCard2       ; "MEMORY CARD 2"
off_8009EC08:   dw dword_800AB754     ; DATA XREF: sub_8004C418+648?o
                dw aNo                ; "NO"
dword_8009EC10: dw 0x8F826382, 0x8B828382, 0
                                         ; DATA XREF: sub_8004D008+C0?o
off_8009EC1C:   dw dword_800122D8     ; DATA XREF: sub_8004D008+118?o
                dw dword_800122CC
                dw dword_800122C0
                dw dword_800122B4
                dw dword_800122A8
byte_8009EC30:  db 0x47               ; DATA XREF: sub_8004D280+8?o
                                         ; sub_8004D280+2C?o ...
byte_8009EC31:  db 0                  ; DATA XREF: sub_8004D280+14?w
byte_8009EC32:  db 0                  ; DATA XREF: sub_8004D280+20?w
                                         ; sub_8004D280:loc_8004D2A4?w
                db 1
                dw aSaveData          ; "SAVE DATA"
                dw 0x8004D008
                dw 0x8004D14C
                dw 0x8004D1D0
dword_8009EC44: dw 0x7D009B, 0x7800A0, 0x7D00A5, 0x80808080
                                         ; DATA XREF: sub_8004D628+98?o
dword_8009EC54: dw 0xD4009C, 0xD800A0, 0xD400A4, 0x80808080, 0x1713520C
                                         ; DATA XREF: sub_8004D628+CC?o
                dw 0xC1E1D18, 0
dword_8009EC70: dw 0x1711080A, 0x501C1B18, 0x6B6A, 0x1712090B, 0x491C1B18
                dw 0x6F6E, 0x174F4D4B, 0x4B1C1B18, 0
                dw 0x175D5B5C, 0x5C1E1D18, 0
                dw 0x65626061, 0x611E1D18, 0
                dw 0x17136768, 0x681E1D18, 0
                dw 0x4443413F, 0x48474645, 0x83827B42, 0x4443403D, 0x48474645
                dw 0x83827B42, 0x4443533E, 0x48474645, 0x83827B42, 0x88238888
                dw 0x27262524, 0
                dw 0x2D23332A
                dw 0x2F
                dw 0
                dw 0x2E223405, 0x30, 0
                dw 0x8888884A, 0x69, 0
                dw 0x2E22884A, 0x51, 0
                dw 0x8823882B, 0x36313735, 0x38, 0x88238839, 0x3B3A
                dw 0
                dw 0x8823883C, 0x32, 0
                dw 0x8888882C, 0x88, 0
dword_8009ED48: dw 0x8573, 0x8570, 0x8571, 0x8888, 0x8472, 0x8574, 0x8575
                dw 0x8576, 0xE040D07, 0x7C7720
dword_8009ED70: dw 0x800AB78C         ; DATA XREF: sub_8004F14C+48?o
                dw 0x8009EC64
                dw 0x800AB7C4
                dw 0x8009ECB8
                dw 0x8009ECDC
                dw 0x8009ED48
                dw 0x8009ED68
dword_8009ED8C: dw 0x800AB794         ; DATA XREF: sub_800511BC+270?o
                                         ; TEXT:8005BA0C?o
                dw 0x8009EC70
                dw 0x800AB7C4
                dw 0x8009ECC4
                dw 0x8009ECE8
                dw 0x8009ED4C
                dw 0x8009ED68
                dw 0x800AB79C
                dw 0x8009EC7C
                dw 0x800AB7C4
                dw 0x8009ECD0
                dw 0x8009ECF4
                dw 0x8009ED50
                dw 0x8009ED68
                dw 0x800AB7A4
                dw 0x8009ECAC
                dw 0x800AB7C4
                dw 0x8009ECB8
                dw 0x8009ED30
                dw 0x8009ED64
                dw 0x8009ED68
                dw 0x800AB7B4
                dw 0x8009EC88
                dw 0x800AB7C4
                dw 0x8009ECD0
                dw 0x8009ED0C
                dw 0x8009ED58
                dw 0x8009ED68
                dw 0x800AB79C
                dw 0x8009EC7C
                dw 0x800AB7C4
                dw 0x8009ECD0
                dw 0x8009ED00
                dw 0x8009ED54
                dw 0x8009ED68
                dw 0x800AB7BC
                dw 0x8009ECA0
                dw 0x800AB7C4
                dw 0x8009ECB8
                dw 0x8009ED24
                dw 0x8009ED60
                dw 0x8009ED68
                dw 0x800AB7AC
                dw 0x8009EC94
                dw 0x800AB7C4
                dw 0x8009ECB8
                dw 0x8009ED18
                dw 0x8009ED5C
                dw 0x8009ED68
                dw 0x800AB7A4
                dw 0x8009ECAC
                dw 0x800AB7C4
                dw 0x8009ECB8
                dw 0x8009ED30
                dw 0x8009ED64
                dw 0x8009ED68
                dw 0x800AB7A4
                dw 0x8009ECAC
                dw 0x800AB7C4
                dw 0x8009ECB8
                dw 0x8009ED30
                dw 0x8009ED64
                dw 0x8009ED68
                dw 0x800AB78C
                dw 0
                dw 0x800AB7C4
                dw 0x8009ECB8
                dw 0x8009ED3C
                dw 0x8009ED54
                dw 0x8009ED68
dword_8009EEA4: dw 0x8005275C         ; DATA XREF: sub_800507D8+40?o
                                         ; sub_800511BC+3BC?o ...
                dw 0x800527DC
                dw 0x800528BC
dword_8009EEB0: dw 0x80052A5C         ; DATA XREF: sub_800511BC+394?o
                                         ; sub_800515BC+2A4?o
                dw 0x80052CCC
dword_8009EEB8: dw 0x8005292C         ; DATA XREF: sub_800511BC+3B0?o
                dw 0x8005292C
                dw 0x800529C0
dword_8009EEC4: dw 0xFA02EE, 0xFA     ; DATA XREF: sub_8005AD10:loc_8005B030?o
dword_8009EECC: dw 0x1F0044C, 0x88    ; DATA XREF: sub_800596FC+6AC?o
dword_8009EED4: dw 0x47F              ; DATA XREF: sub_800596FC+B54?o
                                         ; sub_800596FC+CE8?o
dword_8009EED8: dw 0x2FF01E1, 0       ; DATA XREF: sub_800596FC+B64?o
                                         ; sub_800596FC+D00?o
dword_8009EEE0: dw 0x67F              ; DATA XREF: sub_800596FC+C58?o
                                         ; sub_800596FC+D10?o
dword_8009EEE4: dw 0x4FF01E1, 0x84B02E1, 0
                                         ; DATA XREF: sub_800596FC+C68?o
                                         ; sub_800596FC+D20?o
dword_8009EEF0: dw 0x17F              ; DATA XREF: sub_800596FC:loc_8005A688?o
dword_8009EEF4: dw 0x39B              ; DATA XREF: sub_800596FC+F9C?o
dword_8009EEF8: dw 0x27F0200, 0       ; DATA XREF: sub_80054EFC:loc_80055064?o
dword_8009EF00: dw 0x650048C, 0       ; DATA XREF: sub_80054EFC+174?o
dword_8009EF08: dw 0x27F0A00, 0       ; DATA XREF: sub_80054EFC+F0?o
dword_8009EF10: dw 0x8320250, 0x650048C, 0
                                         ; DATA XREF: sub_80054EFC+100?o
dword_8009EF1C: dw 0x4C4              ; DATA XREF: sub_80057FD4+2A4?o
dword_8009EF20: dw 0x494              ; DATA XREF: sub_80057FD4+294?o
dword_8009EF24: dw 0x27F0200, 0       ; DATA XREF: sub_8005961C+6C?o
dword_8009EF2C: dw 0x4C8023C, 0x228, 0
                                         ; DATA XREF: sub_8005961C+78?o
                dw 0x80054210
dword_8009EF3C: dw 0x80065D74         ; DATA XREF: sub_800511BC+160?o
                dw 0x800540D0
                dw 0x80066374
                dw 0x800540D0
                dw 0x80066A4C
                dw 0x80058470
                dw 0x80066FF0
                dw 0x800540D0
                dw 0x80067480
                dw 0x800570C0
                dw 0x800677BC
                dw 0x80057474
                dw 0x80067B20
                dw 0x800541A8
                dw 0x80066A74
                dw 0x80058470
                dw 0x80066AA0
                dw 0x80058470
                dw 0x80068214
                dw 0x80056DDC
dword_8009EF8C: dw 0x80062274         ; DATA XREF: sub_800515BC:loc_800516F0?o
                dw 0x80063508
                dw 0x80061C7C
                dw 0x80061C7C
                dw 0x80061C7C
                dw 0x8007781C
                dw 0x80078E6C
                dw 0x80060C14
                dw 0x80060940
                dw 0x80072B60
                dw 0x800615FC
                dw 0x80061E40
                dw 0x80065118
byte_8009EFC0:  db 0                  ; DATA XREF: sub_8004EB14+4?o
                                         ; sub_8004EB14+C?r
                db 0, 0xF4
byte_8009EFC3:  db 1                  ; DATA XREF: sub_8004EB14+8?r
byte_8009EFC4:  db 0                  ; DATA XREF: sub_8004EB14+14?r
                db 0, 0x40
byte_8009EFC7:  db 1                  ; DATA XREF: sub_8004EB14+10?r
byte_8009EFC8:  db 0x90               ; DATA XREF: sub_8004EB14+1C?r
                db 1, 0x40
byte_8009EFCB:  db 1                  ; DATA XREF: sub_8004EB14+18?r
byte_8009EFCC:  db 0x90               ; DATA XREF: sub_8004EB14+3C?r
                db 1, 0x20
byte_8009EFCF:  db 0                  ; DATA XREF: sub_8004EB14+38?r
byte_8009EFD0:  db 0x20               ; DATA XREF: sub_8004EB14+44?r
                db 0, 0
byte_8009EFD3:  db 0                  ; DATA XREF: sub_8004EB14+40?r
dword_8009EFD4: dw 0xC8FF9C, 0xC8     ; DATA XREF: sub_8005027C+B4?o
dword_8009EFDC: dw 0x12FF6A, 0xC8     ; DATA XREF: sub_8005027C+B8?o
dword_8009EFE4: dw 0                  ; DATA XREF: sub_800541A8+1C?o
                db 0x2C, 1, 0, 0
                dw 0x2580190, 0x190, 0, 0
                dw 0x40, 0
dword_8009F004: dw 0xFE70, 0x258, 0x2580190, 0x190, 0, 0
                                         ; DATA XREF: sub_800589C8+30?o
                dw 0x24, 5
dword_8009F024: dw 0x190, 0x258, 0x2580190, 0x190, 0, 0
                                         ; DATA XREF: sub_800589C8+68?o
                dw 0x24, 5
dword_8009F044: dw 0, 0               ; DATA XREF: sub_80058C80+4C?o
                dw 0x25801F5, 0x1F5, 0, 0
                dw 7, 0
dword_8009F064: dw 0xC8FF38, 0x258, 0xC80190, 0x190, 5, 0x32, 0
                                         ; DATA XREF: sub_800591F4+80?o
                dw 1
dword_8009F084: dw 0xC800C8           ; DATA XREF: sub_800591F4+158?o
                dw 0x258
                dw 0xC80190, 0x190, 0xFFFB, 0x32, 0
                dw 1
dword_8009F0A4: dw 0xC80000, 0x258, 0xFA01F4, 0x1F4, 0
                                         ; DATA XREF: sub_800591F4+228?o
                dw 0x64, 0
                dw 3
dword_8009F0C4: dw 0, 0               ; DATA XREF: sub_800596FC+B4?o
                dw 0xFFFF, 0
dword_8009F0D4: dw 0x2DF92, 0x40002, 1, 0x320005, 0xFA0032
                                         ; DATA XREF: sub_8005D6BC+DC?o
                                         ; sub_8005D988+C4?o
dword_8009F0E8: dw 0                  ; DATA XREF: sub_8005D6BC+128?w
                                         ; sub_8005D988+114?w
                dw 0x800124A8
dword_8009F0F0: dw 0x8512D, 0x1E0004, 0x12C0001, 0x1900001, 0x200190
                                         ; DATA XREF: sub_8005D6BC+224?o
                                         ; sub_8005D988+318?o ...
dword_8009F104: dw 0                  ; DATA XREF: sub_8005D6BC+270?w
                                         ; sub_8005D988+360?w ...
                dw 0x8001253C
dword_8009F10C: dw 0x2E4CC, 0x40002, 0x12C0001, 0x1900001, 0x800190
                                         ; DATA XREF: sub_8005D988+198?o
                                         ; TEXT:loc_8005E22C?o ...
dword_8009F120: dw 0                  ; DATA XREF: sub_8005D988+1A4?w
                                         ; TEXT:8005E244?w ...
                dw 0x800125CC
dword_8009F128: dw 0x2E4CC, 0x40002, 0x12C0001, 0x5780001, 0x800578
                                         ; DATA XREF: sub_8005E334+9C?o
dword_8009F13C: dw 0                  ; DATA XREF: sub_8005E334+A8?w
                dw 0x800125F4
dword_8009F144: dw 0x2E4CC, 0x40002, 0x12C0001, 0x1900001, 0x800190
                                         ; DATA XREF: TEXT:8005E7A4?o
dword_8009F158: dw 0                  ; DATA XREF: TEXT:8005E7D8?w
                dw 0x8001261C
dword_8009F160: dw 0x2FE8E, 0x30002, 0x12C0001, 0x2580001, 0x640258
                                         ; DATA XREF: sub_8005D604:loc_8005D690?o
dword_8009F174: dw 0                  ; DATA XREF: sub_8005D604+A4?w
                dw 0x80012628
dword_8009F17C: dw 0x27E4C, 0x40002, 0xC80001, 0x640005, 0x800064
                                         ; DATA XREF: sub_8005DDE0+60?o
dword_8009F190: dw 0                  ; DATA XREF: sub_8005DDE0+7C?w
                dw 0x80012634
dword_8009F198: dw 0x8512D, 0x1E0004, 8, 0x8980003, 0x4D0898
                                         ; DATA XREF: TEXT:8005E164?o
dword_8009F1AC: dw 0                  ; DATA XREF: TEXT:8005E178?w
                dw 0x80012708
dword_8009F1B4: dw 0x8512D, 0x1E0004, 1, 0x3E80001, 0x4D03E8
                                         ; DATA XREF: sub_8005DE70+84?o
                                         ; TEXT:8005E2D8?o
dword_8009F1C8: dw 0                  ; DATA XREF: sub_8005DE70+C0?w
                                         ; TEXT:8005E314?w
                dw 0x80012728
dword_8009F1D0: dw 0x8512D, 0x1E0004, 4, 0x8980001, 0x800898
                                         ; DATA XREF: sub_8005DF50+C0?o
dword_8009F1E4: dw 0                  ; DATA XREF: sub_8005DF50+124?w
                dw 0x80012750
dword_8009F1EC: dw 0x8512D, 0x1E0004, 0x3E80001, 0x1900003, 0x800190
                                         ; DATA XREF: sub_8005E508+28?o
dword_8009F200: dw 0                  ; DATA XREF: sub_8005E508+58?w
                dw 0x800127A4
dword_8009F208: dw 0x8512D, 0x1E0004, 0x3E80001, 0x1E0003, 0xA001E
                                         ; DATA XREF: sub_8005E6A4+A8?o
dword_8009F21C: dw 0                  ; DATA XREF: sub_8005E6A4+BC?w
                dw 0x800127D0
dword_8009F224: dw 0                  ; DATA XREF: sub_8005D6BC?r
                                         ; sub_8005D6BC:loc_8005D810?r ...
dword_8009F228: dw 0x8005EC1C         ; DATA XREF: sub_8005F4AC+58?o
                dw 0x8005ED0C
                dw 0x8005ED74
                dw 0x8005EDDC
                dw 0x8005EE44
                dw 0x8005EEA4
                dw 0x8005EF04
                dw 0x8005EFF8
                dw 0x8005F0F0
                dw 0x8005F180
                dw 0x8005F288
                dw 0x8005F2F4
                dw 0x8005F37C
                dw 0x8005F408
                dw 0x8005F438
off_8009F264:   dw aSnaChest1         ; DATA XREF: sub_80060874+58?o
                                         ; "sna_chest1"
                dw aSnaChest2         ; "sna_chest2"
                dw aSnaChest3         ; "sna_chest3"
                dw aSnaHip1           ; "sna_hip1"
off_8009F274:   dw aSnaArmer1         ; DATA XREF: sub_80060874+50?o
                                         ; "sna_armer1"
                dw aSnaArmer2         ; "sna_armer2"
                dw aSnaArmer3         ; "sna_armer3"
                dw aSnaArmer4         ; "sna_armer4"
dword_8009F284: dw 0                  ; DATA XREF: sub_80061A14+D4?w
                                         ; sub_80061A14+D8?o ...
off_8009F288:   dw aCbBox11           ; DATA XREF: sub_80061B30+28?o
                                         ; sub_80061BA0+78?o
                                         ; "cb_box11"
                dw aCbBox12           ; "cb_box12"
                dw aCbBox41           ; "cb_box41"
                dw aCbBox42           ; "cb_box42"
                dw aCbBox21           ; "cb_box21"
                dw aCbBox22           ; "cb_box22"
                dw aCbBox41           ; "cb_box41"
                dw aCbBox42           ; "cb_box42"
off_8009F2A8:   dw aSnaFace           ; DATA XREF: sub_80061D14+4C?o
                                         ; "sna_face"
                dw aSnaFace2          ; "sna_face2"
                dw aSnaFace3          ; "sna_face3"
off_8009F2B4:   dw aSnaMf1            ; DATA XREF: sub_80061D14+44?o
                                         ; "sna_mf1"
                dw aSnaMf2            ; "sna_mf2"
                dw aSnaMf3            ; "sna_mf3"
dword_8009F2C0: dw 0                  ; DATA XREF: sub_80050A64+588?w
                                         ; TEXT:8005BF14?w ...
word_8009F2C4:  dh 0                  ; DATA XREF: sub_8006317C+B0?w
                                         ; sub_80063508+C?r ...
                dh 0
dword_8009F2C8: dw 0, 0, 0            ; DATA XREF: sub_8006237C+B0?o
                dw 0xC80
byte_8009F2D8:  db 0x43, 4            ; DATA XREF: sub_80064A94+EC?o
byte_8009F2DA:  db 0                  ; DATA XREF: sub_80063704+100?w
                db 2
                dw 0x800129D4
                dw 0x80063704
                dw 0x80063888
                dw 0x800638B4
                db 0
                db 1, 8, 0x10         ; DATA XREF: sub_80063DDC+4C?o
                dw 0xA030209, 0x19201811, 0x5040B12, 0x211A130C, 0x22293028
                dw 0x60D141B, 0x1C150E07, 0x38312A23, 0x242B3239, 0x170F161D
                dw 0x332C251E, 0x2D343B3A, 0x2E271F26, 0x363D3C35, 0x3F3E372F
byte_8009F32C:  db 2                  ; DATA XREF: sub_80063DDC+8?r
                                         ; sub_80063DDC+44?o
                db 0x10, 0x13, 0x16
                dw 0x221D1B1A, 0x18161010, 0x25221D1B, 0x1B1A1613, 0x2622221D
                dw 0x1B1A1616, 0x2825221D, 0x1D1B1A16, 0x30282320, 0x201D1B1A
                dw 0x3A302823, 0x221D1B1A, 0x45382E26, 0x26231D1B, 0x5345382E
dword_8009F36C: dw 0x2D2D2D2D, 0x2D2D2D2D, 0xC23353F, 0xC1CBDDF4, 0xC5E8183B
                                         ; DATA XREF: sub_8006392C+10?o
                                         ; sub_80063CD0+8C?o
                dw 0x3B18E8C5, 0xDDC1F435, 0xCB0C3F23, 0x2DD3D32D, 0x2DD3D32D
                dw 0x350CC123, 0xDD3FF4CB, 0xE83BC518, 0x18C53BE8, 0xC135DD0C
                dw 0xF423CB3F
dword_8009F3AC: dw 0, 0, 0            ; DATA XREF: sub_80064454+A8?o
                dw 0xC80
dword_8009F3BC: dw 0xFE8E0014, 0x3C   ; DATA XREF: sub_80065518+3EC?o
byte_8009F3C4:  db 0                  ; DATA XREF: sub_80065B04+1C0?o
                                         ; sub_80065B04+1C8?r
                db 0, 0x29
byte_8009F3C7:  db 0xFF               ; DATA XREF: sub_80065B04+1C4?r
byte_8009F3C8:  db 0x20               ; DATA XREF: sub_80065B04+1D0?r
                db 0, 0
byte_8009F3CB:  db 0                  ; DATA XREF: sub_80065B04+1CC?r
                dw 0xD7290000, 0x20
dword_8009F3D4: dw 0x2580000, 0x20, 0xDA580000, 0x20
                                         ; DATA XREF: sub_80065408+48?o
dword_8009F3E4: dw 0x7A643B88, 0xF83D7A64
                                         ; DATA XREF: sub_8006641C+2EC?o
                                         ; sub_800668B4+2C?o
dword_8009F3EC: dw 0x800000, 0x96     ; DATA XREF: sub_8006641C+228?o
                                         ; sub_8006641C:loc_80066664?o
dword_8009F3F4: dw 0x320000, 0xC8     ; DATA XREF: sub_8006641C:loc_8006665C?o
dword_8009F3FC: dw 0x200000, 0x20, 0x1180000, 0x50
                                         ; DATA XREF: sub_8006641C+23C?o
dword_8009F40C: dw 0x47F0200, 0       ; DATA XREF: sub_800670CC:loc_80067378?o
dword_8009F414: dw 0xA4B0491, 0       ; DATA XREF: sub_800670CC+2BC?o
dword_8009F41C: dw 0, 0, 0            ; DATA XREF: sub_80067BFC+B8?o
                dw 0xBB8
dword_8009F42C: dw 0                  ; DATA XREF: sub_8005027C+90?r
                                         ; sub_80057118+14?r ...
dword_8009F430: dw 0                  ; DATA XREF: TEXT:8006A310?r
                                         ; TEXT:8006A3E8?w
dword_8009F434: dw 0                  ; DATA XREF: TEXT:8005BE90?w
                                         ; TEXT:loc_8006A39C?r
dword_8009F438: dw 0xC00, 0           ; DATA XREF: TEXT:8006A294?o
dword_8009F440: dw 0                  ; DATA XREF: TEXT:8005BECC?w
                                         ; sub_8006AB5C+330?r ...
dword_8009F444: dw 0                  ; DATA XREF: TEXT:8005BED4?w
                                         ; sub_8006AB5C+310?r ...
dword_8009F448: dw 0                  ; DATA XREF: sub_80057474+28?r
                                         ; TEXT:8005BEDC?w ...
dword_8009F44C: dw 0xFF06FD8F, 0x2EE  ; DATA XREF: sub_8006B124+AC?o
dword_8009F454: dw 0xFF06FE0C, 0x2EE  ; DATA XREF: sub_8006B124+A4?o
byte_8009F45C:  db 0xF4               ; DATA XREF: sub_8006B124+44?o
                                         ; sub_8006B124+4C?r
                db 1, 0xC8
byte_8009F45F:  db 0                  ; DATA XREF: sub_8006B124+48?r
byte_8009F460:  db 0xF4               ; DATA XREF: sub_8006B124+54?r
                db 1, 0
byte_8009F463:  db 0                  ; DATA XREF: sub_8006B124+50?r
byte_8009F464:  db 0x2C               ; DATA XREF: sub_8006B124+74?o
                                         ; sub_8006B124+7C?r
                db 1, 0xC8
byte_8009F467:  db 0                  ; DATA XREF: sub_8006B124+78?r
byte_8009F468:  db 0x2C               ; DATA XREF: sub_8006B124+84?r
                db 1, 0
byte_8009F46B:  db 0                  ; DATA XREF: sub_8006B124+80?r
dword_8009F46C: dw 0                  ; DATA XREF: TEXT:8002CF74?r
                                         ; sub_8003B6D0:loc_8003B750?r ...
dword_8009F470: dw 0                  ; DATA XREF: sub_80057BF0+244?r
                                         ; TEXT:8005BEE8?w ...
dword_8009F474: dw 0                  ; DATA XREF: TEXT:8005BEF0?w
                                         ; sub_8006BEEC+34?r ...
word_8009F478:  dh 0                  ; DATA XREF: TEXT:8002CF7C?r
                                         ; sub_8006C5C4+400?o ...
word_8009F47A:  dh 0                  ; DATA XREF: TEXT:8002CF84?r
                                         ; sub_8006C5C4+414?w ...
word_8009F47C:  dh 0                  ; DATA XREF: TEXT:8002CF8C?r
                                         ; sub_8006C5C4+420?w ...
                db 0
byte_8009F47F:  db 0                  ; DATA XREF: sub_8006C5C4+41C?w
                                         ; sub_8006CF44+104?w ...
dword_8009F480: dw 0                  ; DATA XREF: sub_8006C114+A0?r
                                         ; sub_8006C114+180?w ...
word_8009F484:  dh 0                  ; DATA XREF: sub_8006B9B0+1C?o
                                         ; sub_8006B9B0+20?w ...
                dh 0
dword_8009F488: dw 0x640064           ; DATA XREF: sub_8006CBD8+2C?o
                dw 0x64
dword_8009F490: dw 0                  ; DATA XREF: sub_800670CC+148?r
                                         ; sub_80068A24+4?r ...
word_8009F494:  dh 0                  ; DATA XREF: sub_80068A24+8C?o
                                         ; sub_80068A24+178?r ...
word_8009F496:  dh 0                  ; DATA XREF: sub_80068A24+180?r
                                         ; sub_8006D608+E4?w
byte_8009F498:  db 0                  ; DATA XREF: sub_8006D608+F0?w
                db 0, 0
byte_8009F49B:  db 0                  ; DATA XREF: sub_8006D608+EC?w
dword_8009F49C: dw 0                  ; DATA XREF: sub_8006D608+298?r
dword_8009F4A0: dw 0xFCE00000         ; DATA XREF: sub_8006D37C:loc_8006D3FC?o
word_8009F4A4:  dh 0                  ; DATA XREF: sub_8006D37C+74?w
                                         ; sub_8006D37C+7C?w
                dh 0
dword_8009F4A8: dw 0xFEA20000, 0      ; DATA XREF: sub_8006D37C+2C?o
dword_8009F4B0: dw 0xFF9C0000, 0xFFBA
                                         ; DATA XREF: sub_8006D37C+3C?o
dword_8009F4B8: dw 0x100, 5, 0x3E8, 0x7D0, 2
                                         ; DATA XREF: sub_8006641C+130?o
                                         ; TEXT:80069B54?o
dword_8009F4CC: dw 0x100, 5, 0x3E8, 0x7D0, 6, 0x100, 5, 0x3E8, 0x7D0
                                         ; DATA XREF: TEXT:8006A434?o
                dw 5
dword_8009F4F4: dw 0x100, 5, 0x3E8, 0x7D0, 4
                                         ; DATA XREF: sub_8006D608+35C?o
                                         ; sub_8007AE10+E0?o
dword_8009F508: dw 0x100, 5, 0x3E8, 0x7D0, 3, 0x100, 5, 0x3E8, 0x7D0
                                         ; DATA XREF: sub_8006C114+244?o
                                         ; sub_8006C5C4:loc_8006C7A8?o
                dw 0xFFFFFFFF
dword_8009F530: dw 0x400, 5, 0x3E8, 0x7D0, 0xA
                                         ; DATA XREF: TEXT:80069B44?o
dword_8009F544: dw 0, 0               ; DATA XREF: sub_8006C114+23C?o
                                         ; sub_8006C5C4+1E0?o ...
                dw 1, 1, 0xFFFFFFFF
word_8009F558:  dh 0x64               ; DATA XREF: sub_8006DDEC+7C?o
                                         ; sub_8006DDEC+B4?w ...
                dh 0
                dw 0
                dw 0x7D007D0, 0xFA00FA0
dword_8009F568: dw 0x4AC92, 0x100004, 0x7D00001, 0x3E80001, 0x8003E8
                                         ; DATA XREF: sub_8006E224+54?o
                                         ; TEXT:8006E474?o
dword_8009F57C: dw 0                  ; DATA XREF: sub_8006E224+70?w
                dw 0x80012BAC
dword_8009F584: dw 0x4AC92, 0x100004, 0x7D00001, 0x3E80001, 0x8003E8
                                         ; DATA XREF: TEXT:loc_8006E478?o
                dw 0
                dw 0x80012BEC
dword_8009F5A0: dw 0x4AC92, 0x100004, 0x7D00001, 0x1F40001, 0x8001F4
                                         ; DATA XREF: TEXT:8006E2FC?o
dword_8009F5B4: dw 0                  ; DATA XREF: TEXT:8006E310?w
                dw 0x80012C2C
dword_8009F5BC: dw 0x4AC92, 0x100004, 0x7D00001, 0xC80001, 0x8000C8
                                         ; DATA XREF: sub_8006E32C+54?o
                                         ; sub_80085B84+18?o
dword_8009F5D0: dw 0                  ; DATA XREF: sub_8006E32C+68?w
                dw 0x80012C6C
dword_8009F5D8: dw 0x4AC92, 0x100004, 0x7D00001, 0x3E80001, 0x8003E8
                                         ; DATA XREF: TEXT:8006E4BC?o
                                         ; TEXT:8006E7E8?o
dword_8009F5EC: dw 0                  ; DATA XREF: TEXT:8006E530?w
                                         ; TEXT:8006E578?w ...
                dw 0x80012CAC
dword_8009F5F4: dw 0                  ; DATA XREF: sub_8006F318+1CC?r
                                         ; sub_8006F318+264?r ...
byte_8009F5F8:  db 0                  ; DATA XREF: sub_80070EC0+8?w
                                         ; sub_80071010+C?r ...
                db 0, 0, 0
word_8009F5FC:  dh 1                  ; DATA XREF: TEXT:80071E40?o
                                         ; TEXT:80071E7C?w ...
                dh 0
dword_8009F600: dw 0                  ; DATA XREF: sub_800719C8:loc_80071A0C?r
                                         ; sub_800719C8+58?w ...
dword_8009F604: dw 0xFFFFFFFF         ; DATA XREF: sub_80061A14+B8?r
                                         ; sub_80062E8C+1A8?r ...
dword_8009F608: dw 0                  ; DATA XREF: sub_800714EC+358?r
                                         ; sub_800714EC:loc_8007187C?r ...
dword_8009F60C: dw 0x320032           ; DATA XREF: sub_80072608+74?o
                dw 0x640064
dword_8009F614: dw 0x17B54, 0x10001, 0x1F40001, 0x12C0003, 0xC8012C
                                         ; DATA XREF: sub_80072934+30?o
dword_8009F628: dw 0                  ; DATA XREF: sub_80072934+5C?w
                dw 0x80012E84
dword_8009F630: dw 0x14, 0            ; DATA XREF: sub_800731CC+8?o
                dw 0xFFEC, 0
                dw 0x140000, 0
                dw 0xFFEC0000, 0
dword_8009F650: dw 0                  ; DATA XREF: sub_800735A0+24?o
                dw 0xC8, 0
                dw 0x2710
dword_8009F660: dw 0x640064           ; DATA XREF: sub_80073930+2C?o
                dw 0x64
dword_8009F668: dw 0xFFFFFFFF         ; DATA XREF: sub_80073DB0+C?r
                                         ; sub_80073DB0+30?r ...
dword_8009F66C: dw 0                  ; DATA XREF: sub_80073DB0+68?w
dword_8009F670: dw 0x14CEC, 0x10001, 0x1F40001, 0x3200003, 0x800320
                                         ; DATA XREF: sub_80074CA4+54?o
dword_8009F684: dw 0                  ; DATA XREF: sub_80074CA4+70?w
                dw dword_80012F2C
dword_8009F68C: dw 0x155A6, 0x10001, 0x1F40001, 0x2580003, 0xB40258
                                         ; DATA XREF: sub_80074D28+54?o
dword_8009F6A0: dw 0                  ; DATA XREF: sub_80074D28+70?w
                dw dword_80012F50
dword_8009F6A8: dw 0                  ; DATA XREF: sub_80075DD4+258?r
                                         ; sub_80076708:loc_800768F4?r ...
word_8009F6AC:  dh 0                  ; DATA XREF: sub_80075314+C?w
                                         ; sub_80075314+10?o
                dh 0
                dw 0
word_8009F6B4:  dh 0                  ; DATA XREF: sub_80075314+28?w
                dh 0
                dh 0
                dh 0
                dw 0
word_8009F6C0:  dh 0                  ; DATA XREF: sub_80075314+1C?w
                dh 0
                dh 0
                dh 0
word_8009F6C8:  dh 0                  ; DATA XREF: sub_80075314+30?w
                dh 0
dword_8009F6CC: dw 0x1900000, 0       ; DATA XREF: sub_8007575C+C?o
dword_8009F6D4: dw 0                  ; DATA XREF: sub_8007575C+34?o
dword_8009F6D8: dw 0                  ; DATA XREF: sub_8007575C+6C?w
                dw 0, 0
dword_8009F6E4: dw 0xD8F00000, 0      ; DATA XREF: sub_8007575C+40C?o
dword_8009F6EC: dw 0x640064           ; DATA XREF: sub_800761A0+2C?o
                dw 0x64
byte_8009F6F4:  db 0, 0               ; DATA XREF: sub_80076274+98?o
word_8009F6F6:  dh 0                  ; DATA XREF: sub_80076274+B4?w
                dw 0
dword_8009F6FC: dw 0x1900000, 0       ; DATA XREF: sub_80076274+84?o
byte_8009F704:  db 0, 3               ; DATA XREF: sub_800774C0+28?o
word_8009F706:  dh 0xE2               ; DATA XREF: sub_800774C0+54?w
                dw 0x20100
byte_8009F70C:  db 0, 3               ; DATA XREF: sub_800774C0+38?o
word_8009F70E:  dh 0xC4               ; DATA XREF: sub_800774C0+5C?w
                dw 0x20100
word_8009F714:  dh 0                  ; DATA XREF: sub_80078228+14?o
                                         ; sub_80078228+6C?w ...
                dh 0
byte_8009F718:  db 0, 3               ; DATA XREF: sub_80078AB8+28?o
word_8009F71A:  dh 0xE2               ; DATA XREF: sub_80078AB8+54?w
                dw 0x20100
byte_8009F720:  db 0, 3               ; DATA XREF: sub_80078AB8+38?o
word_8009F722:  dh 0xC4               ; DATA XREF: sub_80078AB8+5C?w
                dw 0x20100
dword_8009F728: dw 0                  ; DATA XREF: sub_80078FF8+8?w
                                         ; sub_800790E8+8?r ...
byte_8009F72C:  db 0                  ; DATA XREF: sub_80078F30+20?o
                                         ; sub_80078F30+28?r ...
                db 3, 0xE2
byte_8009F72F:  db 0                  ; DATA XREF: sub_80078F30+24?r
                                         ; sub_80079004+30?r
byte_8009F730:  db 0                  ; DATA XREF: sub_80078F30+30?r
                                         ; sub_80079004+3C?r
                db 1, 2
byte_8009F733:  db 0                  ; DATA XREF: sub_80078F30+2C?r
                                         ; sub_80079004+38?r
byte_8009F734:  db 0                  ; DATA XREF: TEXT:80078F10?o
                                         ; sub_80078F30+48?o ...
                db 3, 0xC4
byte_8009F737:  db 0                  ; DATA XREF: sub_80078F30+4C?r
byte_8009F738:  db 0                  ; DATA XREF: sub_80078F30+58?r
                db 1, 2
byte_8009F73B:  db 0                  ; DATA XREF: sub_80078F30+54?r
dword_8009F73C: dw 0x8512D, 0x1E0004, 0x3E80001, 0x1F40003, 0xFF01F4
                                         ; DATA XREF: sub_8007DA28+28?o
dword_8009F750: dw 0                  ; DATA XREF: sub_8007DA28+58?w
                dw 0x8001345C
dword_8009F758: dw 0x8512D, 0x1E0004, 3, 0x3E80001, 0x4003E8
                                         ; DATA XREF: sub_8007DA94+F8?o
dword_8009F76C: dw 0                  ; DATA XREF: sub_8007DA94+100?w
                dw 0x80013488
dword_8009F774: dw 0x8512D, 0x1E0004, 8, 0x8980003, 0xFF0898
                                         ; DATA XREF: TEXT:8007DD48?o
                                         ; TEXT:8007DED8?o ...
dword_8009F788: dw 0                  ; DATA XREF: TEXT:8007DD5C?w
                                         ; TEXT:8007DEEC?w ...
                dw 0x800134DC
dword_8009F790: dw 0x22447, 0x40002, 0x12C0001, 0x13880001, 0x801388
                                         ; DATA XREF: TEXT:8007DFF0?o
dword_8009F7A4: dw 0                  ; DATA XREF: TEXT:8007E000?w
                dw 0x80013510
dword_8009F7AC: dw 0xFF0000, 0        ; DATA XREF: TEXT:8007F42C?o
dword_8009F7B4: dw 0xFFFFFFFF         ; DATA XREF: sub_80082448+38?w
                                         ; sub_800827AC+178?w ...
dword_8009F7B8: dw 0                  ; DATA XREF: sub_800827AC?r
                                         ; sub_800827AC+3C?w ...
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x800873CC
                dw 0x800873E4
                dw 0x80086E38
                dw 0x80086E78
                dw 0x80086EB8
                dw 0x8008756C
                dw 0x8008758C
                dw 0x80087904
                dw 0x8008798C
                dw 0x800879E4
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80086F00
                dw 0x80086F50
                dw 0x8008750C
                dw 0x80087730
                dw 0x80087018
                dw 0x80087120
                dw 0x8008716C
                dw 0x8008774C
                dw 0x800876D4
                dw 0x80087670
                dw 0x800871B4
                dw 0x800871E0
                dw 0x800872C0
                dw 0x800872EC
                dw 0x8008736C
                dw 0x80087384
                dw 0x80087834
                dw 0x80087854
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80086EF8
                dw 0x80086D18
                dw 0x80086D9C
                dw 0x80087754
                dw 0x8008775C
                dw 0x80087764
                dw 0x800877CC
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A80
                dw 0x80087A58
byte_8009F9BC:  db 0x9F               ; DATA XREF: sub_80086B84+58?r
byte_8009F9BD:  db 0x3C               ; DATA XREF: sub_80086B84+4C?r
                dh 0x52B2
                dw 0x89C745AF, 0x9DE07F10, 0x16611FDC, 0xEB9CC939, 0xF8660857
                dw 0xEBF245A, 0xDB4B153E, 0xC31F5AB, 0xDE550243, 0xAEBDDA41
                dw 0x5748B019, 0xB36A3BA, 0xA817DFF9, 0x91E00C04, 0xD3DD5D18
                dw 0x11F28A28, 0xA066F59, 0xAC792A34, 0xC683A75E, 0x3AB4C139
                dw 0xEF4FFE3F, 0x9930001F, 0xED83284C, 0x662C2F8A, 0xB76CD63F
                dw 0x65BC2249, 0xB102CFFA, 0xD79AF046, 0xC5110FE2, 0x2C7AF674
                dw 0x6A19FB8F, 0xE5
byte_8009FA40:  db 0                  ; DATA XREF: sub_800865CC+5C?r
                                         ; sub_8008686C+26C?r
                db 0x20, 0x38, 0x50
                dw 0xA0908068, 0xE0D0C0B0, 0xF8F0F0E8, 0xF0F4F8FF, 0xC0D0E0E8
                dw 0x8090A0B0, 0x20385068
dword_8009FA60: dw 0                  ; DATA XREF: sub_80088320+C0?r
                                         ; sub_80088320+120?r ...
                dw 2, 4, 7, 0xA, 0xD, 0x10, 0x14, 0x18, 0x1C, 0x20
                dw 0x24, 0x28, 0x2D, 0x32, 0x37, 0x3C, 0x41, 0x46, 0x4B
                dw 0x50, 0x54, 0x58, 0x5C, 0x60, 0x64, 0x68, 0x6B, 0x6E
                dw 0x70, 0x72, 0x74, 0x76, 0x78, 0x7A, 0x7B, 0x7C, 0x7D
                dw 0x7E, 0x7F, 0x7F
dword_8009FB04: dw 0                  ; DATA XREF: sub_80088320+238?r
                                         ; sub_80088320+274?r
                dw 2, 4, 6, 8, 0xA, 0xE, 0x12, 0x16, 0x1C, 0x22, 0x28
                dw 0x2E, 0x34, 0x3A, 0x40, 0x46, 0x4C, 0x52, 0x58, 0x5E
                dw 0x64, 0x6A, 0x70, 0x76, 0x7C, 0x82, 0x88, 0x8E, 0x94
                dw 0x9A, 0xA0, 0xA6, 0xAC, 0xB2, 0xB7, 0xBC, 0xC1, 0xC6
                dw 0xCB, 0xD0, 0xD5, 0xD9, 0xDD, 0xE0, 0xE3, 0xE6, 0xE9
                dw 0xEC, 0xEE, 0xF0, 0xF2, 0xF4, 0xF6, 0xF8, 0xF9, 0xFA
                dw 0xFB, 0xFC, 0xFD, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF
dword_8009FC08: dw 0x10B, 0x11B, 0x12C, 0x13E, 0x151, 0x165, 0x17A
                                         ; DATA XREF: sub_800885D4+24?o
                dw 0x191, 0x1A9, 0x1C2, 0x1DD, 0x1F9, 0x217, 0x237
                dw 0x259, 0x27D, 0x2A3, 0x2CB, 0x2F5, 0x322, 0x352
                dw 0x385, 0x3BA, 0x3F3, 0x42F, 0x46F, 0x4B2, 0x4FA
                dw 0x546, 0x596, 0x5EB, 0x645, 0x6A5, 0x70A, 0x775
                dw 0x7E6, 0x85F, 0x8DE, 0x965, 0x9F4, 0xA8C, 0xB2C
                dw 0xBD6, 0xC8B, 0xD4A, 0xE14, 0xEEA, 0xFCD, 0x10BE
                dw 0x11BD, 0x12CB, 0x13E9, 0x1518, 0x1659, 0x17AD, 0x1916
                dw 0x1A94, 0x1C28, 0x1DD5, 0x1F9B, 0x217C, 0x237A, 0x2596
                dw 0x27D2, 0x2A30, 0x2CB2, 0x2F5A, 0x322C, 0x3528, 0x3850
                dw 0x3BAC, 0x3F36, 0x21, 0x23, 0x26, 0x28, 0x2A, 0x2D
                dw 0x2F, 0x32, 0x35, 0x38, 0x3C, 0x3F, 0x42, 0x46, 0x4B
                dw 0x4F, 0x54, 0x59, 0x5E, 0x64, 0x6A, 0x70, 0x77, 0x7E
                dw 0x85, 0x8D, 0x96, 0x9F, 0xA8, 0xB2, 0xBD, 0xC8, 0xD4
                dw 0xE1, 0xEE, 0xFC, 0xD0780000, 0xD5FF0000, 0xD2290000
                dw 0xD77F0F08, 0xD8440000, 0xD9100000, 0x2B095A40, 0xFFFE0000
                dw 0xD0780000, 0xD5FF0000, 0xD22A0000, 0xD77F0F08, 0xD8440000
                dw 0xD9100000, 0x2B095A40, 0xFFFE0000, 0xD0FF0000, 0xD5C00000
                dw 0xD22B0000, 0xD77F000F, 0xD8000000, 0xD9140000, 0x170C3C7F
                dw 0xFFFE0000, 0xD0FF0100, 0xD57F0000, 0xD2280000, 0xD77F000F
                dw 0xD8000000, 0xD9140000, 0x210C5A57, 0xFFFE0000, 0xD0FF0000
                dw 0xD5FF0000, 0xD2180000, 0xD77F000F, 0xD8000000, 0xD9100000
                dw 0x1F09501E, 0x25095032, 0x2B095046, 0x3130145A, 0xFFFE0000
                dw 0xD0FF0000, 0xD5FF0000, 0xD2170000, 0xD77F0F08, 0xD8400000
                dw 0xD9120000, 0x25095028, 0x2B095050, 0x31095064, 0x37301478
                dw 0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xD24900FF, 0xD77F000F
                dw 0xD8000000, 0xD91A0000, 0x29020114, 0xD24A0000, 0xD77F0F08
                dw 0xD8200000, 0xD9170000, 0x18040140, 0xD2220000, 0xD77F0F08
                dw 0xD8200000, 0xD9170000, 0x303C0120, 0xFFFE0000, 0xD0FF0100
                dw 0xD57F0000, 0xD2260000, 0xDF00000F, 0xD77F0E08, 0xD8400000
                dw 0xD91F0000, 0x43060A7F, 0x3703237F, 0xD2171430, 0xD77F0E08
                dw 0xD8400000, 0xD91F0000, 0x450C1440, 0xFFFE0000, 0xD0FF0100
                dw 0xD5E00000, 0xD2400000, 0xD77F000F, 0xD8000000, 0xD91F0000
                dw 0x21065A50, 0xD2040000, 0xD77F000F, 0xD8000000, 0xD91F0000
                dw 0x34010130, 0x21065060, 0xE4010210, 0xD9122040, 0x1A182020
                dw 0xE4000209, 0xFFFE0000, 0xD0FF0000, 0xD57F0000, 0xD2260000
                dw 0xD77F000F, 0xD8000000, 0xD91F0000, 0x2803017F, 0xD9180000
                dw 0x4503017F, 0x2F12017F, 0xFFFE0000, 0xD0FF0000, 0xD5C00000
                dw 0xD226000F, 0xD77F000F, 0xD8000000, 0xD9180000, 0x37090154
                dw 0x2E120154, 0xFFFE0000, 0xD0FF0100, 0xD57F0000, 0xD2260000
                dw 0xDF00000F, 0xD77F000F, 0xD8000000, 0xD91F0000, 0x4004017F
                dw 0xD20D1430, 0xD77F0E08, 0xD8400000, 0xD91F0000, 0x450C147F
                dw 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xD2040000, 0xD75C000F
                dw 0xD8000000, 0xD9140000, 0x1C0C147F, 0xE4000C04, 0xD77F0F0F
                dw 0xD8360000, 0xD9110000, 0x3C303254, 0xE4000C02, 0xFFFE0000
                dw 0xD0FF0000, 0xD5FF0000, 0xD2040000, 0xDF000F0F, 0xD77F000F
                dw 0x1008287F, 0xE4000804, 0x406287F, 0xD2262854, 0x28102868
                dw 0xE4000604, 0xFFFE0000, 0xD0FF0000, 0xD57F0000, 0xD204507F
                dw 0xD77F000F, 0xD8000000, 0xD9180000, 0x47030168, 0x23030168
                dw 0xE7060140, 0x3B015A68, 0x3A015A68, 0xE803009D, 0xD91F0000
                dw 0xE7060140, 0x20015A40, 0x21015A40, 0xE820FCD8, 0xFFFE0000
                dw 0xD0FF0000, 0xD5FF0000, 0xD203507F, 0xD752000F, 0xD8000000
                dw 0xD9180000, 0x1312327F, 0xE4030909, 0xFFFE0000, 0xD0FF0000
                dw 0xD5FF0000, 0xD2040000, 0xD77F000F, 0xC052854, 0xE4000C07
                dw 0xD210507F, 0xD77F000F, 0xD8000000, 0xD9180000, 0xE7060140
                dw 0x2B015A40, 0x2C015A30, 0xE802E000, 0xE7060140, 0x34015A20
                dw 0x3A025A18, 0xE808FC00, 0xFFFE0000, 0xD0FF0000, 0xD57F0000
                dw 0xD204507F, 0xD75E000F, 0xD8000000, 0xD9180000, 0x43080154
                dw 0x44090140, 0x42080154, 0x3C090140, 0xFFFE0000, 0xD0FF0000
                dw 0xD5FF0000, 0xD2000000, 0xD77F000F, 0xD8000000, 0xD9000000
                dw 0xE3000000, 0xC06637F, 0x3C076330, 0xE4000607, 0xE3FF0FFF
                dw 0xD77F0F0C, 0xD8405A64, 0xD9115A64, 0x1530287F, 0xE4006007
                dw 0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xD24900FF, 0xD77F000F
                dw 0xD8000000, 0xD91A0000, 0x29020114, 0xD21000FF, 0xD77F0F06
                dw 0xD8000000, 0xD9180000, 0x32090A50, 0xFFFE0000, 0xD0FF0000
                dw 0xD5FF0000, 0xD20000FF, 0xD753000F, 0xD8480000, 0xD9100000
                dw 0x3009637F, 0xE4000618, 0x1809637F, 0xE400060C, 0xD58C01FF
                dw 0xD22601FF, 0xD77F000F, 0xD8400000, 0xD9100000, 0xE7010120
                dw 0x40016404, 0xE80A0400, 0xE7010120, 0x40016430, 0xE830FFFD
                dw 0xF2020000, 0xFFFE0000, 0xD0800000, 0xD5FF0000, 0xD204507F
                dw 0xD7570F07, 0xD8000000, 0xD9180000, 0xE7060140, 0x40055A2C
                dw 0x45045A40, 0xE804F0D0, 0xFFFE0000, 0xD0FF0000, 0xD5C00000
                dw 0xD202637F, 0xD7520808, 0xD8480C0C, 0xD911637F, 0x46302840
                dw 0xE4000645, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF607507F
                dw 0xD207507F, 0xD77F000F, 0xD8000000, 0xD9180000, 0xDD000018
                dw 0xDF0C3218, 0x43062814, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000
                dw 0xD203637F, 0xD75A0808, 0xD8480C0C, 0xD911637F, 0x47182828
                dw 0xE4000645, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xD204507F
                dw 0xD760000F, 0xD8000000, 0xD9180000, 0x4030A7F, 0x90C0A7F
                dw 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xD24000FF, 0xD77F000F
                dw 0xD8000000, 0xD9180000, 0x1F093C48, 0xD20400FF, 0xD75C000F
                dw 0xD8000000, 0xD9180000, 0x2606632C, 0xE400060C, 0xFFFE0000
                dw 0xD0FF0000, 0xD5FF0000, 0xF6020000, 0xD2020000, 0xD77F0F0F
                dw 0xD8000000, 0xD9000000, 0x402A0450, 0xE4010C46, 0xE00A0A3C
                dw 0x402E0458, 0xE4010C46, 0x40270450, 0xE4010C46, 0xFFFE0000
                dw 0xD0FF0000, 0xD5FF0000, 0xF6170000, 0xD2170000, 0xD77F0F0F
                dw 0xD8000000, 0xD9140000, 0x1301640A, 0x1903641E, 0x1F036432
                dw 0x25036446, 0x2B03645A, 0x3103646E, 0xD77F0F03, 0xD840FF10
                dw 0x34243C7F, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF6170000
                dw 0xD2170000, 0xD77F000F, 0xD8000000, 0xD9140000, 0x1903640A
                dw 0x1F03641E, 0x25036432, 0x2B036446, 0x3103645A, 0x3703646E
                dw 0xD77F0F03, 0xD848FF10, 0xE128FF10, 0x3A481E7F, 0xFFFE0000
                dw 0xD0FF0000, 0xD5FF0000, 0xF6170000, 0xD2170000, 0xD77F000F
                dw 0xD8000000, 0xD9140000, 0x1602640A, 0x1C03641E, 0x22036432
                dw 0x28036446, 0x2E03645A, 0x3403646E, 0xD77F000F, 0xD8480F0F
                dw 0xE128FF20
                dw 0x37481E7F, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF60E507F
                dw 0xD20E507F, 0xD77F080C, 0xD8000000, 0xD9110000, 0xE7065040
                dw 0x3E045020, 0x42035018, 0xE8040000, 0xE7065040, 0x3E045009
                dw 0x42035006, 0xE8020000, 0xE7065040, 0x3E045020, 0x42035018
                dw 0xE8040000, 0xE7065040, 0x3E045009, 0x42035006, 0xE8030000
                dw 0xFFFE0000, 0xD0780000, 0xF7FF0000, 0xD5FF0000, 0xD2410000
                dw 0xDF00000F, 0xD77F000F, 0xD8000000, 0xD91F0000, 0x181A6364
                dw 0xFFFE0000, 0xD0780000, 0xF7FF0000, 0xD5FF0000, 0xD2400000
                dw 0xDF00000F, 0xD77F000F, 0xD8000000, 0xD9130000, 0x18181E64
                dw 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF713507F, 0xD213507F
                dw 0xD758080C, 0xD8400000, 0xD9120000, 0x37180A7F, 0xE404083E
                dw 0x37180A30, 0xE404083E, 0x37180A18, 0xE404083E, 0xFFFE0000
                dw 0xD0FF0000, 0xF6FF0000, 0xD5FF0000, 0xD213507F, 0xD7550802
                dw 0xD8000000, 0xD9110000, 0x26066470, 0xE400061A, 0x1A262870
                dw 0xE400203E, 0xFFFE0000, 0xD0FF0000, 0xF7FF0000, 0xD5FF0000
                dw 0xD241507F, 0xD77F000F, 0xD8000000, 0xD9110000, 0x24066360
                dw 0xD242507F, 0xD77F000F, 0xD8000000, 0xD9110000, 0x181C6360
                dw 0xD213507F, 0xD7550802, 0xD8000000, 0xD9110000, 0x26066420
                dw 0xE400061A, 0x1A262820, 0xE400203E, 0xFFFE0000, 0xD0FF0000
                dw 0xD5FF0000, 0xF713507F, 0xD213507F, 0xD77F0905, 0xD8000000
                dw 0xD9110000, 0x3912017F, 0xFFFE0000, 0xD0780000, 0xF7FF0000
                dw 0xD5FF0000, 0xD23F0000, 0xDF00000F, 0xD77F000F, 0xD8000000
                dw 0xD91F0000, 0x1D2C6350, 0xE4061811, 0xFFFE0000, 0xD0800000
                dw 0xD5FF0000, 0xF738507F, 0xD238507F, 0xD77F000F, 0xD8000000
                dw 0xD9120000, 0x17126368, 0xE4000C15, 0xFFFE0000, 0xD0800000
                dw 0xD5FF0000, 0xD239507F, 0xD77F000F, 0xD8000000, 0xD9100000
                dw 0x18185058, 0xE4000C15, 0xFFFE0000, 0xD0800000, 0xD5FF0000
                dw 0xF63D507F, 0xD23D507F, 0xD77F000F, 0xD8000000, 0xD9110000
                dw 0x16283C78, 0x16283C40, 0x16283C20, 0x16283C10, 0x16283C08
                dw 0xFFFE0000, 0xD0780000, 0xF7FF0000, 0xD5FF0000, 0xD2270000
                dw 0xDF00000F, 0xD77F000F, 0xD8000000, 0xD91F0000, 0x1B326350
                dw 0xE403180F, 0xFFFE0000, 0xD0780000, 0xF7FF0000, 0xD5FF0000
                dw 0xD2270000, 0xDF00000F, 0xD77F000F, 0xD8000000, 0xD91F0000
                dw 0x1D206350, 0xFFFE0000, 0xD0800000, 0xD5DF0000, 0xF73C507F
                dw 0xD23C507F, 0xD77F000F, 0xD8000000, 0xD9100000, 0x18285048
                dw 0xFFFE0000, 0xD0FF0100, 0xD5A80000, 0xF7040000, 0xD24A0000
                dw 0xD77F000F, 0xD8002854, 0xD9182854, 0x1C045A30, 0xD22A507F
                dw 0xD77F000F, 0xD8000000, 0xD9180000, 0x2B065A40, 0xD229507F
                dw 0xD77F000F, 0xD8000000, 0xD9180000, 0x2B0C5A40, 0xFFFE0000
                dw 0xD0800000, 0xD5FF0000, 0xF6800000, 0xD2430000, 0xD77F0F08
                dw 0xD840647F, 0xD90F647F, 0x1A18507F, 0xFFFE0000, 0xD0FF0100
                dw 0xD5FF0000, 0xF6060118, 0xD20A0130, 0xD7620F06, 0xD8441430
                dw 0xD9181430, 0x3C0C5068, 0xFFFE0000, 0xD0FF0100, 0xD5FF0000
                dw 0xF6060118, 0xD2050130, 0xD74E0C08, 0xD8451430, 0xD9121430
                dw 0xDD000430, 0xDF061430, 0x47601428, 0xE400201B, 0xFFFE0000
                dw 0xD0FF0100, 0xD5FF0000, 0xF6060118, 0xD20A0130, 0xD74E0C08
                dw 0xD8451430, 0xD9111430, 0xDD000050, 0x2D600A64, 0xFFFE0000
                dw 0xD0FF0100, 0xD5FF0000, 0xF6060118, 0xD2370130, 0xD74E0C08
                dw 0xD8451430, 0xD9111430, 0xDD00FC20, 0x39600D3C, 0xFFFE0000
                dw 0xD0FF0100, 0xD5FF0000, 0xF6060118, 0xD2370130, 0xD7520E04
                dw 0xD8441430, 0xD9101430, 0xDD00FC30, 0x37603C23, 0xFFFE0000
                dw 0xD0FF0100, 0xD5FF0000, 0xF6060118, 0xD2260130, 0xD7500F03
                dw 0xD8441430, 0xD9161430, 0xDD000440, 0x43600A20, 0xFFFE0000
                dw 0xD0FF0000, 0xD5FF0000, 0xF613507F, 0xD213507F, 0xD7560808
                dw 0xD8400000, 0xD9120000, 0x37180A7F, 0xE404083E, 0x37180A30
                dw 0xE404083E, 0x37180A18, 0xE404083E, 0xFFFE0000, 0xD0FF0000
                dw 0xD5FF0000, 0xF716507F, 0xD216507F, 0xD7560806, 0xD8400000
                dw 0xD9120000, 0x2B180A20, 0xE4040832, 0xFFFE0000, 0xD0800000
                dw 0xD5FF0000, 0xD242507F, 0xD77F000F, 0xD8400000, 0xD9120000
                dw 0x1C050A40, 0x26180A40, 0xFFFE0000, 0xD0FF0100, 0xD5FF0000
                dw 0xD2250000, 0xD77F000F, 0xD8480000, 0xD9140000, 0x18060118
                dw 0xD2220000, 0xD77F000F, 0xD8480000, 0xD9130000, 0xC180130
                dw 0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xD2250000, 0xD77F000F
                dw 0xD8480000, 0xD9140000, 0x18060120, 0xD2240000, 0xD77F000F
                dw 0xD8480000, 0xD9130000, 0xC180120, 0xFFFE0000, 0xD0FF0100
                dw 0xD5FF0000, 0xF7260000, 0xD2320000, 0xD760000F, 0xD8400000
                dw 0xD9100000, 0xC070A30, 0x1060037F, 0xFFFE0000, 0xD0FF0100
                dw 0xD5FF0000, 0xF7260000, 0xD21E0000, 0xD77F000F, 0xD8000000
                dw 0xD9140000, 0x15060A40, 0xD2240000, 0xD77F000F, 0xD8400000
                dw 0xD9110000, 0x13401430, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000
                dw 0xF7260000, 0xD24B0000, 0xD7500F0D, 0xD8400000, 0xD9100000
                dw 0x284C0A30, 0xE4000329, 0xFFFE0000, 0xD0FF0100, 0xD5FF0000
                dw 0xF7260000, 0xD2320000, 0xD74E000F, 0xD8400000, 0xD9100000
                dw 0x11903C7F, 0xFFFE0000, 0xD0FF0130, 0xD5FF0130, 0xF6160130
                dw 0xD2130130, 0xD77F000F, 0xD8001430, 0xD91C1430, 0x390C5030
                dw 0xFFFE0000, 0xD0FF0000, 0xD5A80000, 0xF60E507F, 0xD202507F
                dw 0xD77F080C, 0xD8000000, 0xD9110000, 0xE7065040, 0x32045050
                dw 0x36035040, 0xE8040000, 0xE7065040, 0x32045012, 0x3603500C
                dw 0xE8020000, 0xE7065040, 0x32045050, 0x36035040, 0xE8040000
                dw 0xE7065040, 0x32045012, 0x3603500C, 0xE8030000, 0xFFFE0000
                dw 0xD0800100, 0xD5FF0000, 0xF7000000, 0xD2420130, 0xD77F000F
                dw 0xD8001430, 0xD9181430, 0x260C0140, 0xFFFE0000, 0xD0FF0000
                dw 0xD5C00000, 0xD23F0100, 0xD77F000F, 0xD8000000, 0xD9000000
                dw 0x24036330, 0xE4000707, 0xD2470FFF, 0xD77F0F0C, 0xD8405A64
                dw 0xD9115A64, 0x15062860, 0x1A182860, 0xFFFE0000, 0xD0FF0100
                dw 0xD5A00000, 0xF7260000, 0xD2260000, 0xD77F000F, 0xD8000000
                dw 0xD9130000, 0x34015A60, 0x28015A60, 0x34015A60, 0x28015A60
                dw 0xD2280000, 0xD77F000F, 0xD8000000, 0xD9130000, 0x28185A40
                dw 0xFFFE0000, 0xD0FF0100, 0xD5B00000, 0xD2400000, 0xD77F000F
                dw 0xD8000000, 0xD91F0000, 0x1B095A7F, 0xD77F0F01, 0xD9132040
                dw 0x13205060, 0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xF7040000
                dw 0xD23F0000, 0xD77F000F, 0xD8000000, 0xD9000000, 0x1106637F
                dw 0x1806637F, 0xD23F0000, 0xDF10000F, 0xD77F000F, 0xD8000000
                dw 0xD9000000, 0xC07647F, 0xE4000705, 0xD77F0F0C, 0xD8405A64
                dw 0xD9105A64, 0x890467F, 0xE4009000, 0xFFFE0000, 0xD0FF0000
                dw 0xD5FF0000, 0xD210507F, 0xD77F000F, 0xD8000000, 0xD9180000
                dw 0x26030140, 0xE4000328, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000
                dw 0xD210507F, 0xD77F000F, 0xD8000000, 0xD9180000, 0x26030140
                dw 0xE4000328, 0xD210507F, 0xD77F000F, 0xD8000000, 0xD9140000
                dw 0x150C0A40, 0xE4000C21, 0x150C0A20, 0xE4000C21, 0x150C0A10
                dw 0xE4000C21, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xD20D507F
                dw 0xD77F0F08, 0xD8000000, 0xD91F0000, 0x280C1E30, 0x281C6330
                dw 0xFFFE0000, 0xD0FF0000
                dw 0xD5600000
                dw 0xD204507F
                dw 0xD77F000F
                dw 0xD8000000
                dw 0xD9180000
                dw 0x47030168
                dw 0x23030168
                dw 0xE7060140
                dw 0x3B015A60
                dw 0x3A015A60
                dw 0xE803009D
                dw 0x47030158
                dw 0x23030158
                dw 0xE7060140
                dw 0x3B015A50
                dw 0x3A015A50
                dw 0xE803009D
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5C00000
                dw 0xD241507F
                dw 0xD77F000F
                dw 0xD8000000
                dw 0xD9180000
                dw 0x3C01647F
                dw 0x240E507F
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xF707507F
                dw 0xD23F507F
                dw 0xD77F000F
                dw 0xD8000000
                dw 0xD90F0000
                dw 0x15056360
                dw 0x9056332
                dw 0x405637F
                dw 0x10FF6360
                dw 0xFFFE0000
                dw 0xD0FF0100
                dw 0xD5FF0000
                dw 0xF707507F
                dw 0xD204507F
                dw 0xD77F000F
                dw 0xD800507F
                dw 0xD914507F
                dw 0x1805017F
                dw 0xC050150
                dw 0xD204507F
                dw 0xD77F0008
                dw 0xD87F0000
                dw 0xD9100000
                dw 0x13F637F
                dw 0xD77F0004
                dw 0x3C02830
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xF707507F
                dw 0xD242507F
                dw 0xD77F000F
                dw 0xD8000000
                dw 0xD9190000
                dw 0x24090140
                dw 0x2B0C0120
                dw 0xFFFE0000
                dw 0xD0FF0100
                dw 0xD5FF0000
                dw 0xF7260000
                dw 0xD21E0000
                dw 0xD77F000F
                dw 0xD8480000
                dw 0xD9140000
                dw 0x18060130
                dw 0xD2320000
                dw 0xD77F000F
                dw 0xD8420000
                dw 0xD9130000
                dw 0xC303C60
                dw 0xFFFE0000
                dw 0xD0FF0100
                dw 0xD5FF0000
                dw 0xF7260000
                dw 0xD2320000
                dw 0xD74A000F
                dw 0xD8400000
                dw 0xD9100000
                dw 0x17905A7F
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xF707507F
                dw 0xD229507F
                dw 0xD75E000F
                dw 0xD8000000
                dw 0xD9120000
                dw 0x2D0A0148
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xF707507F
                dw 0xD22A507F
                dw 0xD75E000F
                dw 0xD8000000
                dw 0xD9120000
                dw 0x2E0A0148
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xF607507F
                dw 0xE3FF00FF
                dw 0xD226507F
                dw 0xD74C0608
                dw 0xD8000000
                dw 0xD9100000
                dw 0xE5004006
                dw 0x70C6430
                dw 0xE70C6446
                dw 0xF30C6446
                dw 0xE8000000
                dw 0xF3600100
                dw 0xE4006002
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xF607507F
                dw 0xD232507F
                dw 0xD750000F
                dw 0xD8000000
                dw 0xD90A0000
                dw 0xE500070C
                dw 0x12103260
                dw 0xD753000F
                dw 0xE5000100
                dw 0x18203C40
                dw 0xD219507F
                dw 0xD742000F
                dw 0xD8000000
                dw 0xD9110000
                dw 0x390C6403
                dw 0xE7C06446
                dw 0xF30C6446
                dw 0xE8000000
                dw 0xF3180100
                dw 0xE4001835
                dw 0xD232507F
                dw 0xD750000F
                dw 0xD8000000
                dw 0xD9100000
                dw 0xE5000803
                dw 0x12153260
                dw 0x18303C40
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xF607507F
                dw 0xD24B507F
                dw 0xD742000F
                dw 0xD8000000
                dw 0xD9110000
                dw 0x1D0C6410
                dw 0xE7605A32
                dw 0xF30C6432
                dw 0xE8000000
                dw 0xF318017F
                dw 0xD203507F
                dw 0xD74A0808
                dw 0xD83C0000
                dw 0xD9100000
                dw 0x2B603218
                dw 0xE4006010
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5C80000
                dw 0xF625507F
                dw 0xD225507F
                dw 0xD760000F
                dw 0xD8000000
                dw 0xD91B0000
                dw 0x39030120
                dw 0xD9170000
                dw 0x3A05017F
                dw 0xD91A0000
                dw 0x38030120
                dw 0xD9160000
                dw 0x39060178
                dw 0xD91B0000
                dw 0x37030120
                dw 0xD9160000
                dw 0x3804016F
                dw 0xD91A0000
                dw 0x38030120
                dw 0xD9170000
                dw 0x39060166
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xF704507F
                dw 0xD229507F
                dw 0xD760000F
                dw 0xD8000000
                dw 0xD90F0000
                dw 0x2D06637F
                dw 0xD22A507F
                dw 0xD760000F
                dw 0x2803637F
                dw 0xD227507F
                dw 0xD74F0A0F
                dw 0xD8000000
                dw 0xD91E0000
                dw 0x350C5A40
                dw 0xD7440A0F
                dw 0x37125A50
                dw 0xFFFE0000
                dw 0xD09B0000
                dw 0xD5B40000
                dw 0xF607507F
                dw 0xD20D507F
                dw 0xD75C000F
                dw 0xD8360000
                dw 0xD9100000
                dw 0xE106FF10
                dw 0xE5000604
                dw 0x22301434
                dw 0x210E630C
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5A80000
                dw 0xF707507F
                dw 0xD204507F
                dw 0xD75D000F
                dw 0xD8000000
                dw 0xD9150000
                dw 0x23060A40
                dw 0x200C0A40
                dw 0xD229507F
                dw 0xD75D000F
                dw 0xD8000000
                dw 0xD90F0000
                dw 0x2D0C6340
                dw 0xD75D000F
                dw 0x28086320
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xF7420000
                dw 0xD2420000
                dw 0xD77F000F
                dw 0xD8000000
                dw 0xD91F0000
                dw 0x1F040160
                dw 0xD9180000
                dw 0x24040160
                dw 0x21205040
                dw 0xFFFE0000
                dw 0xD0800000
                dw 0xD5C00000
                dw 0xF6800000
                dw 0xD2440000
                dw 0xD77F000F
                dw 0xD8466350
                dw 0xD9106350
                dw 0xDD00F250
                dw 0x1C0E3C40
                dw 0xDD000E50
                dw 0x1A303C10
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5800000
                dw 0xF607507F
                dw 0xD23F507F
                dw 0xD77F000F
                dw 0xD8000000
                dw 0xD9140000
                dw 0x39035A40
                dw 0xE4000321
                dw 0xD246507F
                dw 0xD77F000F
                dw 0xD8000000
                dw 0xD9140000
                dw 0x24065A40
                dw 0x260C5A40
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xD245507F
                dw 0xD77F000F
                dw 0xD8000000
                dw 0xD9130000
                dw 0x1F245A50
                dw 0xE4081022
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xD248507F
                dw 0xD757000F
                dw 0xD8000000
                dw 0xD9190000
                dw 0xE5001208
                dw 0x29185A50
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xD248507F
                dw 0xD757000F
                dw 0xD8000000
                dw 0xD9190000
                dw 0xE5001208
                dw 0x21185A50
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xD23F507F
                dw 0xD77F0F07
                dw 0xD8440000
                dw 0xD9190000
                dw 0x1C035040
                dw 0xD247507F
                dw 0xD77F0F0A
                dw 0xD8000000
                dw 0xD9120000
                dw 0x18200A60
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xD247507F
                dw 0xD77F0F0A
                dw 0xD8000000
                dw 0xD9120000
                dw 0x1A205050
                dw 0xE4061815
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xF707507F
                dw 0xD209507F
                dw 0xD7550A08
                dw 0xD84A0000
                dw 0xD90F0000
                dw 0xE100FF0F
                dw 0x3C303214
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xF604507F
                dw 0xD213507F
                dw 0xD7560C06
                dw 0xD8480000
                dw 0xD9110000
                dw 0xE5001224
                dw 0x32240A20
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xF604507F
                dw 0xD208507F
                dw 0xD7540C06
                dw 0xD8480000
                dw 0xD9110000
                dw 0xE5001218
                dw 0x45240A0C
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xF605507F
                dw 0xD204507F
                dw 0xD7580F0A
                dw 0xD8000000
                dw 0xD91C0000
                dw 0x2D105A18
                dw 0xD207507F
                dw 0xD7560C06
                dw 0xD8480000
                dw 0xD9110000
                dw 0xE50012F4
                dw 0x39240A10
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xF705507F
                dw 0xD20A507F
                dw 0xD77F000F
                dw 0xD8000000
                dw 0xD91C0000
                dw 0x2F0C5A12
                dw 0xF613507F
                dw 0xD213507F
                dw 0xD7560C08
                dw 0xD8480000
                dw 0xD9110000
                dw 0xE50012F4
                dw 0x34240A20
                dw 0xFFFE0000
                dw 0xD0FF0100
                dw 0xD5FF0000
                dw 0xF6000000
                dw 0xD2130130
                dw 0xD77F000F
                dw 0xD8001430
                dw 0xD91C1430
                dw 0x3C060130
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xF61B507F
                dw 0xD203507F
                dw 0xD755000F
                dw 0xD8000000
                dw 0xD9110000
                dw 0xE5002418
                dw 0x45245030
                dw 0xFFFE0000
                dw 0xD0FF0100
                dw 0xD5A00000
                dw 0xF6000000
                dw 0xD20A0130
                dw 0xD77F000F
                dw 0xD8001430
                dw 0xD91A1430
                dw 0x3C0C1430
                dw 0xFFFE0000
                dw 0xD0FF0100
                dw 0xD5A00000
                dw 0xF6000000
                dw 0xD2130130
                dw 0xD77F000F
                dw 0xD84D1430
                dw 0xD91C1430
                dw 0x39035030
                dw 0xD2160130
                dw 0xD77F000F
                dw 0xD8001430
                dw 0xD91A1430
                dw 0x390C0A12
                dw 0x390C0A04
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xF70E507F
                dw 0xD213507F
                dw 0xD77F000F
                dw 0xD8000000
                dw 0xD9160000
                dw 0xE7065040
                dw 0x3C010118
                dw 0x3C010118
                dw 0xE8080000
                dw 0xF3080140
                dw 0xE4000837
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5FF0000
                dw 0xF70E507F
                dw 0xD217507F
                dw 0xD77F000F
                dw 0xD8000000
                dw 0xD9140000
                dw 0x46183C07
                dw 0xE4100835
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5C00000
                dw 0xF613507F
                dw 0xD20A507F
                dw 0xD77F0F08
                dw 0xD8480000
                dw 0xD9140000
                dw 0x2B06017F
                dw 0xE4030339
                dw 0x37060140
                dw 0xE4030339
                dw 0x37060130
                dw 0xE4030339
                dw 0x37060120
                dw 0xE4030339
                dw 0x37060118
                dw 0xE4030339
                dw 0x3706010C
                dw 0xE4030339
                dw 0x37060106
                dw 0xE4030339
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5400000
                dw 0xF613507F
                dw 0xD211507F
                dw 0xD760000F
                dw 0xD8000000
                dw 0xD9120000
                dw 0x2F060140
                dw 0x36060160
                dw 0x3B06017F
                dw 0x42060130
                dw 0x47060140
                dw 0x42060118
                dw 0x47060120
                dw 0xFFFE0000
                dw 0xD0FF0000
                dw 0xD5A80000
                dw 0xF613507F
                dw 0xDF08507F
                dw 0xD20E507F
                dw 0xD758000F
                dw 0xD8360000
                dw 0xD9160000
                dw 0xE5010C18
                dw 0x3B0C5060
                dw 0x3E0B5050, 0x410A5040, 0x440A5030, 0x47095020, 0xFFFE0000
                dw 0xD0FF0000, 0xD5FF0000, 0xF607507F, 0xD226507F, 0xD77F0C08
                dw 0xD83A0000, 0xD90F0000, 0xDD00007F, 0x3CFF647F, 0xE400FF30
                dw 0xF3803C7F, 0xE400FF2A, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000
                dw 0xF607507F, 0xD219507F, 0xD77F0C08, 0xD83A0000, 0xD90F0000
                dw 0xDD00007F, 0x45FF6440, 0xF3803C00, 0xFFFE0000, 0xD0FF0000
                dw 0xD5800000, 0xF607507F, 0xD203507F, 0xD77F0F0A, 0xD8480000
                dw 0xD9160000, 0xD640FF40, 0xDF0BEC40, 0xED00EC40, 0xDD00EC40
                dw 0x3B04017F, 0xDD001440, 0x38040170, 0xDD00EC40, 0x36040160
                dw 0xDD001440, 0x39040170, 0xDD00EC40, 0x3B04017F, 0xDD001440
                dw 0x38040170, 0xDD00EC40, 0x36040160, 0xDD001440, 0x39040170
                dw 0xEE00EC40, 0xDF0AEC40, 0xEE00EC40, 0xDF09EC40, 0xEE00EC40
                dw 0xD6F40040, 0xDF08EC40, 0xEE00EC40, 0xDF07EC40, 0xEE00EC40
                dw 0xDF06EC40, 0xEE00EC40, 0xDF05EC40, 0xEE00EC40, 0xDF04EC40
                dw 0xEE00EC40, 0xDF03EC40, 0xEE00EC40, 0xDF02EC40, 0xEE00EC40
                dw 0xDF01EC40, 0xEE00EC40, 0xFFFE0000, 0xD0FF0000, 0xD5800000
                dw 0xF707507F, 0xDF0C507F, 0xD209507F, 0xD7600C0F, 0xD8440000
                dw 0xD9120000, 0xED00017F, 0xE000017F, 0x3B040130, 0xE00C2860
                dw 0x3C0C2820, 0xE0060150, 0x3B040118, 0xE0122860, 0x3C0C2818
                dw 0xE0062830, 0x3C0C2810, 0xEE04F400, 0xD5700740, 0xEE040740
                dw 0xD5600740, 0xEE040740, 0xD5400740, 0xEE040740, 0xFFFE0000
                dw 0xD0FF0000, 0xD5FF0000, 0xF707507F, 0xD229507F, 0xD77F0F08
                dw 0xD8000000, 0xD91F0000, 0x32020140, 0xD229507F, 0xD75E000F
                dw 0xD8000000, 0xD9120000, 0x2B0A0140, 0xFFFE0000, 0xD0FF0000
                dw 0xD5FF0000, 0xF707507F, 0xD229507F, 0xD77F0F08, 0xD8000000
                dw 0xD91F0000, 0x33020140, 0xD22A507F, 0xD75E000F, 0xD8000000
                dw 0xD9120000, 0x2D0A0140, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000
                dw 0xF732507F, 0xD247507F, 0xD758000F, 0xD8000000, 0xD9130000
                dw 0x21035050, 0x15065040, 0xD240507F, 0xD77F000F, 0xD8000000
                dw 0xD9130000, 0x14182830, 0xFFFE0000, 0xD0800000, 0xD5FF0000
                dw 0xF6800000, 0xD2270000, 0xD77F0F08, 0xD8420000, 0xD9110000
                dw 0x1A12507F, 0x1A125060, 0x1A125030, 0x1A125018, 0x1A12500C
                dw 0x1A125006, 0xFFFE0000, 0xD0800000, 0xD5FF0000, 0xF6800000
                dw 0xD2270000, 0xD77F000F, 0xD8420000, 0xD9110000, 0x24105060
                dw 0xD2490000, 0xD77F0F08, 0xD8420000, 0xD9110000, 0x2D0C507F
                dw 0x2D0A5020, 0x2D185010, 0xFFFE0000, 0xD0800000, 0xD5FF0000
                dw 0xF6800000, 0xD2160000, 0xD77F0F08, 0xD8420000, 0xD9110000
                dw 0xDD00F120, 0x47060410, 0x440C040C, 0xFFFE0000, 0xD0FF0000
                dw 0xD5FF0000, 0xF613507F, 0xD216507F, 0xD77F000F, 0xD8360000
                dw 0xD9180000, 0xDD000F7F, 0x3C091E10, 0xD77F0F0B, 0xD8420000
                dw 0xD9120000, 0x3C405018, 0xFFFE0000, 0xD0C00100, 0xD5C00000
                dw 0xF6390130, 0xD23A0130, 0xD754000F, 0xD8001430, 0xD9121430
                dw 0xE5001805, 0x1730507F, 0x17305040, 0x17305020, 0x17305018
                dw 0x1730500C, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF705507F
                dw 0xD20A507F, 0xD77F000F, 0xD83E0000, 0xD91C0000, 0xDD000018
                dw 0x2F0F4612, 0x2F23460C, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000
                dw 0xF605507F, 0xD204507F, 0xD77F0F0A, 0xD8000000, 0xD91C0000
                dw 0xDD000020, 0x3901640A, 0x2D016410, 0x32016418, 0xE7016420
                dw 0xED016410, 0x39016420, 0x2D016420, 0x32016420, 0xEE05FFF8
                dw 0xE80400F8, 0xE7000000, 0xEE000000, 0xE805FEF8, 0xFFFE0000
                dw 0xD0FF0000, 0xD5A80000, 0xF700507F, 0xD213507F, 0xD77F000F
                dw 0xD8000000, 0xD9140000, 0xE7066430, 0xE0006418, 0x2A016418
                dw 0xE0106410, 0x29016412, 0xE8080000, 0xE7066430, 0xE0006418
                dw 0x2A016418, 0xE0106410, 0x29016412, 0xE808FEF8, 0x2A020100
                dw 0xFFFE0000, 0xD0AA507F, 0xD5C8507F, 0xF745507F, 0xD232000F
                dw 0xD77F000F, 0xD8000000, 0xD9110000, 0x1108506E, 0xD754000F
                dw 0x1D40506E, 0xE418181C, 0xFFFE0000, 0xD0AA507F, 0xD5C8507F
                dw 0xF745507F, 0xD23F000F, 0xD77F000F, 0xD8000000, 0xD9120000
                dw 0xF2040A50, 0xC480A50, 0xFFFE0000, 0xD0800000, 0xD5AA0000
                dw 0xF704507F, 0xD24A507F, 0xD764000F, 0xD8000000, 0xD9120000
                dw 0x30063218, 0x2F063216, 0x30063218, 0x2F073216, 0xFFFE0000
                dw 0xD0800000, 0xD5AA0000, 0xF704507F, 0xD24B507F, 0xD768000F
                dw 0xD8000000, 0xD9120000, 0x1C303230, 0xFFFE0000, 0xD0800000
                dw 0xD5FF0000, 0xF642507F, 0xD242507F, 0xD77F000F, 0xD8400000
                dw 0xD9120000, 0x1C030A40, 0x24180A40, 0xFFFE0000, 0xD0FF0100
                dw 0xD5C00000, 0xF6330000, 0xD2110000, 0xD77F0F06, 0xD8400000
                dw 0xD9100000, 0x34400A50, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000
                dw 0xF607507F, 0xF218507F, 0xD232507F, 0xD750000F, 0xD8000000
                dw 0xD9100000, 0xE5000803, 0x12153240, 0x18303C28, 0xFFFE0000
                dw 0xD0FF0000, 0xD5FF0000, 0xF607507F, 0xD203507F, 0xD74A0F08
                dw 0xD83C0000, 0xD9100000, 0x1F601E40, 0xE4005E0C, 0xFFFE0000
                dw 0xD0FF0100, 0xD5A00000, 0xD204507F, 0xD75B000F, 0xD8000000
                dw 0xD9150000, 0x23060A30, 0x280C1420, 0xD2450000, 0xD75D0808
                dw 0xD8400000, 0xD9100000, 0x18061E20, 0x18061E10, 0xFFFE0000
                dw 0xD0FF0100, 0xD5A00000, 0xD204507F, 0xD75B000F, 0xD8000000
                dw 0xD9150000, 0x23060A30, 0x1F0C1420, 0xD2450000, 0xD75D0808
                dw 0xD8400000, 0xD9100000, 0x18061E20, 0x18061E10, 0xFFFE0000
                dw 0xD0FF0000, 0xD5FF0000, 0xF642507F, 0xD245507F, 0xD77F000F
                dw 0xD8000000, 0xD9140000, 0x24090A30, 0xD201507F, 0xD77F0F0A
                dw 0xD8440000, 0xD9130000, 0x30120A40, 0xFFFE0000, 0xD0FF0100
                dw 0xD5FF0000, 0xF6040000, 0xD24C0000, 0xD7500F0F, 0xD8000000
                dw 0xD9110000, 0x1C482830, 0xFFFE0000, 0xD0FF0100, 0xD5FF0000
                dw 0xF7040000, 0xD23F0000, 0xD77F000F, 0xD8000000, 0xD9130000
                dw 0x10093260, 0xD77F000F, 0xD8005A64, 0xD9105A64, 0x24485050
                dw 0xE4002C00, 0xFFFE0000, 0xD0FF0100, 0xD5780000, 0xF6040000
                dw 0xF2030000, 0xE0100000, 0xD2130000, 0xD77F0F08, 0xD8000000
                dw 0xD9120000, 0xDD00F630, 0x39050130, 0x36050138, 0x38050140
                dw 0x35050148, 0x3B050150, 0x38050158, 0x3A050160, 0x37050158
                dw 0x3A050150, 0x37050148, 0x39050140, 0x36050148, 0x3C050150
                dw 0x39050158, 0x3B050160, 0x38050158, 0x3B050150, 0x38050148
                dw 0x3A050140, 0x37050138, 0x3D050130, 0x3A050128, 0x3C050120
                dw 0x39050118, 0x3B050110, 0x3805010C, 0x3A050108, 0x37050105
                dw 0xFFFE0000, 0xD0FF0100, 0xD5780000, 0xF6040000, 0xD2130000
                dw 0xD77F0F08, 0xD8000000, 0xD9120000, 0xDD000A30, 0x3A050130
                dw 0x37050138, 0x39050140, 0x36050148, 0x3C050150, 0x39050158
                dw 0x3B050160, 0x38050158, 0x39050150, 0x36050148, 0x38050140
                dw 0x35050148, 0x3B050150, 0x38050158, 0x3A050160, 0x37050158
                dw 0x3B050150, 0x38050148, 0x3A050140, 0x37050138, 0x3D050130
                dw 0x3A050128, 0x3C050120, 0x39050118, 0x3B050110, 0x3805010C
                dw 0x3A050108, 0x37050105, 0xFFFE0000, 0xD0C00100, 0xD5DF0000
                dw 0xF6390130, 0xD23A0130, 0xD77F000F, 0xD8001430, 0xD9121430
                dw 0xE50B06FD, 0xDD000060, 0x132A5070, 0x132A5038, 0x132A501C
                dw 0x132A500E, 0xFFFE0000
                dw 0xD0FF0000, 0xD5800000, 0xF7066430, 0xD24B507F, 0xD768000F
                dw 0xD8000000, 0xD9130000, 0xDFF03210, 0x45303210, 0xE4181842
                dw 0xFFFE0000, 0xD0540000, 0xD5FF0000, 0xF6185A0A, 0xD2185A0A
                dw 0xD77F0F05, 0xD8005A0A, 0xD90E5A0A, 0xDD00000C, 0x33045A60
                dw 0x39045A70, 0x3F045A7F, 0x450C5A70, 0x33045A0C, 0x39045A0E
                dw 0x3F045A10, 0x45245A0E, 0xFFFE0000, 0xD0540000, 0xD5FF0000
                dw 0xF60C5A0A, 0xF20C5A0A, 0xD2185A0A, 0xD77F0F05, 0xD8005A0A
                dw 0xD90E5A0A, 0xDD00000C, 0x33045A18, 0x39045A1C, 0x3F045A20
                dw 0x450C5A1C, 0x33045A06, 0x39045A07, 0x3F045A08, 0x450C5A07
                dw 0xFFFE0000, 0xD0400000, 0xD5FF0000, 0xF6175A0A, 0xD2365A0A
                dw 0xD744060A, 0xD83C5A0A, 0xD9105A0A, 0xDD00FA0C, 0x3FA84620
                dw 0xFFFE0000, 0xD0400000, 0xD5FF0000, 0xF6365A0A, 0xD2365A0A
                dw 0xD744060A, 0xD83C5A0A, 0xD9105A0A, 0xDD00060C, 0x3CA84620
                dw 0xFFFE0000, 0xD0400000, 0xD5FF0000, 0xF6365A0A, 0xD2175A0A
                dw 0xD744060A, 0xD83C5A0A, 0xD9105A0A, 0xDD00000C, 0x39A84610
                dw 0xFFFE0000, 0xD0400000, 0xD5FF0000, 0xF6175A0A, 0xD2365A0A
                dw 0xD77F0806, 0xD8385A0A, 0xD90F5A0A, 0xDD00000C, 0x39903C50
                dw 0xFFFE0000, 0xD0400000, 0xD5FF0000, 0xF6175A0A, 0xD2365A0A
                dw 0xD77F0806, 0xD8385A0A, 0xD90F5A0A, 0xDD00000C, 0x38903C50
                dw 0xFFFE0000, 0xD0400000, 0xD5FF0000, 0xF6175A0A, 0xF2180A40
                dw 0xD2355A0A, 0xD754080A, 0xD8385A0A, 0xD90F5A0A, 0xDD00000C
                dw 0x22183C40, 0x21483230, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000
                dw 0xF607507F, 0xD206507F, 0xD77F0F06, 0xD8000000, 0xD9120000
                dw 0xDD000018, 0x46182860, 0xFFFE0000, 0xD0FF0100, 0xD5FF0000
                dw 0xF6390130, 0xDD01F660, 0xD2040130, 0xD758000F, 0xD8001430
                dw 0xD9121430, 0x300C0A60, 0x240C0A60, 0x18180560, 0xD2480130
                dw 0xD752000F, 0xD8001430, 0xD9121430, 0x1D095028, 0x1A095028
                dw 0x1C203C20, 0xE4002010, 0xFFFE0000, 0xD0FF0000, 0xD5C80000
                dw 0xF6800000, 0xD2420000, 0xD7600F08, 0xD844647F, 0xD91C647F
                dw 0xDD00007F, 0x37180A7F, 0x2B180A20, 0x34180A40, 0x2B180A20
                dw 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF607507F, 0xD207507F
                dw 0xD77F000F, 0xD8000000, 0xD9180000, 0xDD000018, 0x47062818
                dw 0x470C2818, 0xFFFE0000, 0xD0FF0000, 0xD57F0000, 0xF604507F
                dw 0xD204507F, 0xDD000F7F, 0xD77F000F, 0xD8001430, 0xD91C1430
                dw 0x240C5014, 0xD754000F, 0xD8001430, 0xD91C1430, 0x3030630E
                dw 0xFFFE0000, 0xD0FF0000, 0xD57F0000, 0xF604507F, 0xD20A507F
                dw 0xDD000F7F, 0xD754000F, 0xD8001430, 0xD91C1430, 0x30406318
                dw 0xE40C0637, 0xFFFE0000, 0xD0FF0100, 0xD5A00000, 0xD204507F
                dw 0xD759000F, 0xD8000000, 0xD9140000, 0x17060A40, 0x1C0C1430
                dw 0x100C3C18, 0xFFFE0000, 0xD0FF0100, 0xD5A00000, 0xD204507F
                dw 0xD759000F, 0xD8000000, 0xD9140000, 0x1C060A40, 0x170C1430
                dw 0xB0C3C18, 0xFFFE0000, 0xD0FC0000, 0xD5C00000, 0xF613507F
                dw 0xD20E507F, 0xD7540605, 0xD8400000, 0xD9120000, 0x2F202830
                dw 0xE4002047, 0xFFFE0000, 0xD0FC0100, 0xD5780000, 0xF613507F
                dw 0xD237507F, 0xD77F000F, 0xD8400000, 0xD9120000, 0x30302810
                dw 0xFFFE0000, 0xD0FC0100, 0xD5780000, 0xF613507F, 0xD213507F
                dw 0xD77F000F, 0xD8400000, 0xD9120000, 0x3030280C, 0xFFFE0000
                dw 0xD0780000, 0xF7FF0000, 0xD5FF0000, 0xD2270000, 0xDF00000F
                dw 0xD77F000F, 0xD8000000, 0xD91F0000, 0xE5000303, 0x1E206350
                dw 0xE4041C1B, 0xFFFE0000, 0xD0FF0000, 0xD5600000, 0xF604507F
                dw 0xD204507F, 0xDD00F67F, 0xD77F000F, 0xD8001430, 0xD91C1430
                dw 0x30035018, 0x24095018, 0xE4000C47, 0xFFFE0000, 0xD0FF0000
                dw 0xD5600000, 0xF604507F, 0xD20A507F, 0xDD00F67F, 0xD77F0F08
                dw 0xD8401430, 0xD9121430, 0x30186340, 0xE4001846, 0xFFFE0000
                dw 0xD080507F, 0xD5C8507F, 0xF204000F, 0xD227000F, 0xD77F000F
                dw 0xD83F0000, 0xD9110000, 0xE50004FA, 0x10302820, 0xFFFE0000
                dw 0xD080507F, 0xD5C8507F, 0xD232000F, 0xD754000F, 0xD8460000
                dw 0xD9110000, 0x1030637F, 0xFFFE0000, 0xD0FC0000, 0xD5FF0000
                dw 0xF604507F, 0xDD01007F, 0xD203507F, 0xD77F000F, 0xD8001430
                dw 0xD91F1430, 0x241A6320, 0xE4001A39, 0xD226507F, 0xD77F0905
                dw 0xD8471430, 0xD9121430, 0x3C145060, 0x3C145028, 0x3C1B3C14
                dw 0xD203507F, 0xD75C000F, 0xD8001430, 0xD9121430, 0x30302810
                dw 0xE4003000, 0xFF008D00, 0xFFFE0000, 0xD0FC0000, 0xD5FF0000
                dw 0xF604507F, 0xDD01007F, 0xF2286318, 0xD219507F, 0xD74E000F
                dw 0xD8001430, 0xD9121430, 0x2148320C, 0xD237000F, 0xD77F000F
                dw 0xD8001430, 0xD9121430, 0x39302808, 0xFFFE0000, 0xD0FC0000
                dw 0xD5C80000, 0xF6920000, 0xD24D0100, 0xD748000F, 0xD8000000
                dw 0xD9110000, 0x16186428, 0xE4001818, 0xE7C05A64, 0x180C642C
                dw 0xE8000000, 0xF3601464, 0xFFFE0000, 0xD0FC0000, 0xD5FF0000
                dw 0xF607507F, 0xD2190F0C, 0xD7440308, 0xD8400000, 0xD9110000
                dw 0x24FF4628, 0xFFFE0000, 0xD0FC0000, 0xD5FF0000, 0xF607507F
                dw 0xD2190F0C, 0xD7440308, 0xD8400000, 0xD9110000, 0x22FF4614
                dw 0xFFFE0000, 0xD0FC0000, 0xD5FF0000, 0xF607507F, 0xD2360F0C
                dw 0xD7440308, 0xD8400000, 0xD9110000, 0x2BFF4614, 0xFFFE0000
                dw 0xD0FF0000, 0xD5C00000, 0xF613507F, 0xD213507F, 0xD77F0905
                dw 0xD8000000, 0xD9110000, 0xDD000E60, 0x39120160, 0xFFFE0000
                dw 0xD0FF0100, 0xD5FF0000, 0xF6260000, 0xD21E0000, 0xD77F000F
                dw 0xD8000000, 0xD9140000, 0x15060A40, 0xD2240000, 0xD77F000F
                dw 0xD8400000, 0xD9110000, 0x13241430, 0xD2250000, 0xD77F000F
                dw 0xD8480000, 0xD9140000, 0x18060118, 0xD2220000, 0xD77F000F
                dw 0xD8480000, 0xD9130000, 0xC180130, 0xFFFE0000, 0xD0FF0100
                dw 0xD5FF0000, 0xF7260000, 0xD2320000, 0xD74E000F, 0xD8400000
                dw 0xD9100000, 0x11405A7F, 0xD2320000, 0xD760000F, 0xD8400000
                dw 0xD9100000, 0x1060037F, 0xFFFE0000, 0xD0FC0100, 0xD5960000
                dw 0xF6800000, 0xD2270100, 0xD77F000F, 0xD8006366, 0xD9196366
                dw 0x22010146, 0xD24E0100, 0xD77F000F, 0xD8006366, 0xD9126366
                dw 0xE00E6356, 0x220A635A, 0xD762000F, 0x240F6324, 0xFFFE0000
                dw 0xFFFE0000
byte_800A22C4:  db 1                  ; DATA XREF: sub_800888F8+F8?r
byte_800A22C5:  db 1                  ; DATA XREF: sub_800888F8+70?r
byte_800A22C6:  db 1                  ; DATA XREF: sub_800888F8+10C?r
byte_800A22C7:  db 0                  ; DATA XREF: sub_800888F8+84?r
dword_800A22C8: dw 0x800A22C0         ; DATA XREF: sub_800888F8+E0?o
                dw 0x800A22C0
                dw 0x800A22C0
                dw 0x10140, 0x800A067C, 0x800A22C0, 0x800A22C0, 0x10110
                dw 0x8009FDB8, 0x800A22C0, 0x800A22C0, 0x10110, 0x8009FDD8
                dw 0x800A22C0, 0x800A22C0, 0x10130, 0x800A0A48, 0x800A22C0
                dw 0x800A22C0, 0x10120, 0x800A1EE0, 0x800A22C0, 0x800A22C0
                dw 0x10120, 0x800A1F08, 0x800A22C0, 0x800A22C0, 0x10120
                dw 0x800A0F14, 0x800A22C0, 0x800A22C0, 0x10120, 0x800A0F90
                dw 0x800A22C0, 0x800A22C0, 0x10130, 0x800A0FD4, 0x800A22C0
                dw 0x800A22C0, 0x130, 0x800A1004, 0x800A22C0, 0x800A22C0
                dw 0x190, 0x800A1338, 0x800A22C0, 0x800A22C0, 0x1B0
                dw 0x800A13CC, 0x800A22C0, 0x800A22C0, 0x190, 0x800A1390
                dw 0x800A22C0, 0x800A22C0, 0x190, 0x800A16E8, 0x800A22C0
                dw 0x800A22C0, 0x3F0, 0x800A1408, 0x800A143C, 0x800A1468
                dw 0x120, 0x800A0410, 0x800A22C0, 0x800A22C0, 0x190
                dw 0x800A0470, 0x800A22C0, 0x800A22C0, 0x10101A0, 0x800A1BBC
                dw 0x800A22C0, 0x800A22C0, 0x10101A0, 0x800A06A4, 0x800A22C0
                dw 0x800A22C0, 0x10190, 0x800A088C, 0x800A22C0, 0x800A22C0
                dw 0x120, 0x800A04C0, 0x800A22C0, 0x800A22C0, 0x290
                dw 0x800A04F8, 0x800A0528, 0x800A22C0, 0x110, 0x800A0580
                dw 0x800A22C0, 0x800A22C0, 0x10101A0, 0x800A05D0, 0x800A22C0
                dw 0x800A22C0, 0x10101A0, 0x800A05F8, 0x800A22C0, 0x800A22C0
                dw 0x10001F0, 0x800A061C, 0x800A22C0, 0x800A22C0, 0x10140
                dw 0x800A0650, 0x800A22C0, 0x800A22C0, 0x10120, 0x800A06C8
                dw 0x800A22C0, 0x800A22C0, 0x10110, 0x800A0EB8, 0x800A22C0
                dw 0x800A22C0, 0x10120, 0x800A0714, 0x800A22C0, 0x800A22C0
                dw 0x190, 0x800A0738, 0x800A22C0, 0x800A22C0, 0x290
                dw 0x800A07DC, 0x800A0804, 0x800A22C0, 0x390, 0x800A075C
                dw 0x800A078C, 0x800A07B4, 0x290, 0x800A082C, 0x800A0864
                dw 0x800A22C0, 0x10190, 0x800A0BE0, 0x800A22C0, 0x800A22C0
                dw 0x220, 0x800A12D8, 0x800A1310, 0x800A22C0, 0x10160
                dw 0x800A0A6C, 0x800A22C0, 0x800A22C0, 0x10160, 0x8009FDF8
                dw 0x800A22C0, 0x800A22C0, 0x10110, 0x8009FE18, 0x800A22C0
                dw 0x800A22C0, 0x10140, 0x800A0AA8, 0x800A22C0, 0x800A22C0
                dw 0x10190, 0x800A0B18, 0x800A22C0, 0x800A22C0, 0x1A0
                dw 0x800A0300, 0x800A22C0, 0x800A22C0, 0x10120, 0x8009FE90
                dw 0x800A22C0, 0x800A22C0, 0x10130, 0x8009FED8, 0x800A22C0
                dw 0x800A22C0, 0x10130, 0x800A0AEC, 0x800A22C0, 0x800A22C0
                dw 0x10130, 0x8009FF14, 0x800A22C0, 0x800A22C0, 0x10130
                dw 0x8009FF5C, 0x800A22C0, 0x800A22C0, 0x10140, 0x800A0498
                dw 0x800A22C0, 0x800A22C0, 0x10140, 0x8009FF88, 0x800A22C0
                dw 0x800A22C0, 0x10140, 0x8009FFAC, 0x800A22C0, 0x800A22C0
                dw 0x10170, 0x800A1608, 0x800A22C0, 0x800A22C0, 0x10140
                dw 0x800A1114, 0x800A22C0, 0x800A22C0, 0x10140, 0x800A10E0
                dw 0x800A22C0, 0x800A22C0, 0x110, 0x800A21BC, 0x800A22C0
                dw 0x800A22C0, 0x10130, 0x800A0B70, 0x800A22C0, 0x800A22C0
                dw 0x10120, 0x800A1098, 0x800A22C0, 0x800A22C0, 0x10120
                dw 0x800A10BC, 0x800A22C0, 0x800A22C0, 0x290, 0x800A1A8C
                dw 0x800A1B28, 0x800A22C0, 0x10160, 0x800A0C04, 0x800A22C0
                dw 0x800A22C0, 0x10140, 0x800A004C, 0x800A22C0, 0x800A22C0
                dw 0x10130, 0x800A00B8, 0x800A22C0, 0x800A22C0, 0x10140
                dw 0x800A1034, 0x800A22C0, 0x800A22C0, 0x10160, 0x800A1074
                dw 0x800A22C0, 0x800A22C0, 0x10130, 0x800A0204, 0x800A22C0
                dw 0x800A22C0, 0x10290, 0x800A0C74, 0x800A0CA4, 0x800A22C0
                dw 0x10170, 0x800A1A54, 0x800A22C0, 0x800A22C0, 0x10130
                dw 0x800A21E4, 0x800A22C0, 0x800A22C0, 0x10130, 0x800A2244
                dw 0x800A22C0, 0x800A22C0, 1, 0x800A22C0, 0x800A22C0
                dw 0x800A22C0, 1, 0x800A22C0, 0x800A22C0, 0x800A22C0
                dw 1, 0x800A22C0, 0x800A22C0, 0x800A22C0, 0x10130, 0x800A0174
                dw 0x800A22C0, 0x800A22C0, 0x10140, 0x800A1FA0, 0x800A22C0
                dw 0x800A22C0, 0x280, 0x800A1FD0, 0x800A2000, 0x800A22C0
                dw 0x1FF, 0x800A2118, 0x800A22C0, 0x800A22C0, 0x10140
                dw 0x800A05A4, 0x800A22C0, 0x800A22C0, 0x10140, 0x800A01A8
                dw 0x800A22C0, 0x800A22C0, 0x10130, 0x800A0230, 0x800A22C0
                dw 0x800A22C0, 0x130, 0x800A0254, 0x800A22C0, 0x800A22C0
                dw 0x10130, 0x800A0280, 0x800A22C0, 0x800A22C0, 0x10160
                dw 0x800A02A4, 0x800A22C0, 0x800A22C0, 0x10140, 0x800A02C8
                dw 0x800A22C0, 0x800A22C0, 0x3A0, 0x800A033C, 0x800A0380
                dw 0x800A03C8, 0x280, 0x800A1160, 0x800A1188, 0x800A22C0
                dw 0x180, 0x800A09C4, 0x800A22C0, 0x800A22C0, 0x180
                dw 0x800A09E8, 0x800A22C0, 0x800A22C0, 0x280, 0x800A11B0
                dw 0x800A11EC, 0x800A22C0, 0x10130, 0x800A08B0, 0x800A22C0
                dw 0x800A22C0, 0x10130, 0x800A08E4, 0x800A22C0, 0x800A22C0
                dw 0x10130, 0x800A0918, 0x800A22C0, 0x800A22C0, 0x10130
                dw 0x800A0940, 0x800A22C0, 0x800A22C0, 0x10130, 0x800A0978
                dw 0x800A22C0, 0x800A22C0, 0x10130, 0x800A09A0, 0x800A22C0
                dw 0x800A22C0, 0x10110, 0x800A1BF4, 0x800A22C0, 0x800A22C0
                dw 0x10190, 0x800A0C50, 0x800A22C0, 0x800A22C0, 0x10120
                dw 0x800A0CE8, 0x800A22C0, 0x800A22C0, 0x10120, 0x800A0D10
                dw 0x800A22C0, 0x800A22C0, 0x10120, 0x800A0D48, 0x800A22C0
                dw 0x800A22C0, 0x10110, 0x800A1138, 0x800A22C0, 0x800A22C0
                dw 0x3FF, 0x800A0DB4, 0x800A0DF4, 0x800A0E6C, 0x10140
                dw 0x800A227C, 0x800A22C0, 0x800A22C0, 0x2F0, 0x800A1644
                dw 0x800A167C, 0x800A22C0, 0x120, 0x800A122C, 0x800A22C0
                dw 0x800A22C0, 0x180, 0x800A1278, 0x800A22C0, 0x800A22C0
                dw 0x180, 0x800A129C, 0x800A22C0, 0x800A22C0, 0x190
                dw 0x800A16BC, 0x800A22C0, 0x800A22C0, 0x1000190, 0x800A1720
                dw 0x800A22C0, 0x800A22C0, 0x280, 0x800A1758, 0x800A1784
                dw 0x800A22C0, 0x10120, 0x800A17DC, 0x800A22C0, 0x800A22C0
                dw 0x10240, 0x800A1830, 0x800A1860, 0x800A22C0, 0x10230
                dw 0x800A1888, 0x800A18B8, 0x800A22C0, 0x10120, 0x800A1904
                dw 0x800A22C0, 0x800A22C0, 0x10230, 0x800A1928, 0x800A1958
                dw 0x800A22C0, 0x190, 0x800A1A30, 0x800A22C0, 0x800A22C0
                dw 0x1B0, 0x800A19F8, 0x800A22C0, 0x800A22C0, 0x140
                dw 0x800A1E50, 0x800A22C0, 0x800A22C0, 0x1B0, 0x800A1E1C
                dw 0x800A22C0, 0x800A22C0, 0x180, 0x800A1DCC, 0x800A22C0
                dw 0x800A22C0, 0x1B0, 0x800A1DA4, 0x800A22C0, 0x800A22C0
                dw 0x290, 0x800A1E7C, 0x800A1EB4, 0x800A22C0, 0x2F0
                dw 0x800A1C20, 0x800A1C64, 0x800A22C0, 0x3F0, 0x800A1CAC
                dw 0x800A1CD4, 0x800A1CFC, 0x3F0, 0x800A2150, 0x800A2174
                dw 0x800A2198, 0x10240, 0x800A202C, 0x800A2054, 0x800A22C0
                dw 0x2F0, 0x800A2074, 0x800A20D8, 0x800A22C0, 0x3B0
                dw 0x800A1F30, 0x800A1F58, 0x800A1F7C, 0x190, 0x800A18DC
                dw 0x800A22C0, 0x800A22C0, 1
dword_800A2AC8: dw 1                  ; DATA XREF: sub_80084494+540?o
                                         ; sub_80084494+710?r ...
                dw 2, 4, 8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0x400
                dw 0x800, 0x1000, 0x2000, 0x4000, 0x8000, 0x10000, 0x20000
                dw 0x40000, 0x80000, 0x100000, 0x200000, 0x400000, 0x800000
dword_800A2B28: dw 0x60C, 0, 0, 0     ; DATA XREF: sub_80081C7C+1F4?o
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0
word_800A2BE0:  dh 0                  ; DATA XREF: rcos+68?r
                dh 0
                dw 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x30C, 0, 0, 0
byte_800A2D28:  db 0xC                ; DATA XREF: sub_800827AC+9CC?o
                                         ; sub_800827AC+A4C?o
byte_800A2D29:  db 2                  ; DATA XREF: sub_800827AC:loc_80083170?o
                                         ; sub_800827AC+9D8?w ...
                dh 0
                dw 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0
word_800A33E0:  dh 0                  ; DATA XREF: sin_1:loc_800925B8?r
                dh 0
                dw 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0
word_800A3BE0:  dh 0                  ; DATA XREF: rcos+44?r
                dh 0
                dw 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                dw 0x20C, 0, 0, 0
                db 0xC
byte_800A3D19:  db 2                  ; DATA XREF: sub_800827AC:loc_8008320C?w
                dh 0
                dw 0, 0, 0
                dw 0x80013DC4
                dw 0x80013DC0
                dw aTlbl              ; "TLBL"
                dw 0x80013DB0
                dw 0x80013D98
                dw 0x80013D80
                dw 0x80013D70
                dw 0x80013D5C
                dw 0x80013D4C
                dw 0x80013D38
                dw 0x80013D2C
                dw 0x80013D24
                dw 0x80013D14
                dw 0x80013D10
                dw 0x80013D10
                dw 0x80013D10
dword_800A3D68: dw 0                  ; DATA XREF: sub_800892A8?w
                dw 0
dword_800A3D70: dw 0                  ; DATA XREF: sub_8008AAEC+A8?w
                                         ; sub_8008B044+10?r
dword_800A3D74: dw 0                  ; DATA XREF: sub_800893D8?w
                                         ; sub_800893E8+1C?r
dword_800A3D78: dw 0xFFFFFFFF         ; DATA XREF: sub_800893E8+24?w
                                         ; sub_800893E8:loc_8008943C?r ...
dword_800A3D7C: dw 0                  ; DATA XREF: sub_800893E8:loc_80089424?o
                                         ; sub_800893E8+44?r ...
                dw 0
                dw 0xFFFFFFFF, 0, 0
dword_800A3D90: dw 0                  ; DATA XREF: sub_8008B044:loc_8008B070?r
dword_800A3D94: dw 0                  ; DATA XREF: sub_8008AAC4+8?w
                                         ; sub_8008AAEC:loc_8008AE78?r ...
                dw aSending           ; "Sending"
                dw aReceiving         ; "Receiving"
                dw aReady             ; "Ready"
                dw aSleeping          ; "Sleeping"
                dw aWaitvbl           ; "WaitVBL"
                dw aPending           ; "Pending"
dword_800A3DB0: dw 1                  ; DATA XREF: TEXT:8008BA64?w
                                         ; TEXT:8008BA78?w ...
dword_800A3DB4: dw 0                  ; DATA XREF: TEXT:8008BB60?r
                                         ; TEXT:8008BB68?w ...
dword_800A3DB8: dw 0                  ; DATA XREF: sub_8008BB88?w
dword_800A3DBC: dw 0                  ; DATA XREF: sub_8008C098?r
                                         ; sub_8008C098+78?w ...
dword_800A3DC0: dw 0, 0               ; DATA XREF: sub_8008BDEC+20?o
dword_800A3DC8: dw 1                  ; DATA XREF: TEXT:8008C3C4?r
                                         ; TEXT:8008C3D4?w ...
dword_800A3DCC: dw 0                  ; DATA XREF: TEXT:8008C534?r
                                         ; TEXT:8008C564?w
dword_800A3DD0: dw 0                  ; DATA XREF: CdInit+4C?w
dword_800A3DD4: dw 0                  ; DATA XREF: CdInit+5C?w
                dw 0
                dw 0
dword_800A3DE0: dw 0, 0, 0            ; DATA XREF: CdControl+2C?o
                                         ; CdControlF+2C?o ...
                dw 1, 0, 0
                dw 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 1, 1, 0, 0, 0, 0
                dw 1, 0, 0, 0, 0
                dw 0x47350, 0x440000
dword_800A3E68: dw 0                  ; DATA XREF: CdInit+2C?w
                                         ; CdSyncCallback?r ...
dword_800A3E6C: dw 0                  ; DATA XREF: CdInit+3C?w
                                         ; CdReadyCallback?r ...
dword_800A3E70: dw 0                  ; DATA XREF: TEXT:CdSetDebug?r
                                         ; TEXT:8008C830?w ...
dword_800A3E74: dw 0                  ; DATA XREF: TEXT:CdStatus?r
                                         ; CdControl+74?r ...
dword_800A3E78: dw 0                  ; DATA XREF: sub_8008CEE8+1AC?w
                                         ; sub_8008CEE8+208?r ...
dword_800A3E7C: dw 0                  ; DATA XREF: sub_8008CEE8+17C?r
                                         ; sub_8008CEE8+18C?w
byte_800A3E80:  db 2                  ; DATA XREF: TEXT:8008C790?o
                                         ; CD_cw+E4?w ...
                db 0, 0, 0
byte_800A3E84:  db 0                  ; DATA XREF: TEXT:CdMode?r
                                         ; CD_cw+114?w ...
byte_800A3E85:  db 0                  ; DATA XREF: TEXT:CdLastCom?r
                                         ; sub_8008CEE8+128?r ...
                dh 0
                dw 0
off_800A3E8C:   dw aCdlsync           ; DATA XREF: TEXT:8008C844?r
                                         ; sub_8008CEE8+214?r ...
                                         ; "CdlSync"
                dw aCdlnop            ; "CdlNop"
                dw aCdlsetloc         ; "CdlSetloc"
                dw aCdlplay           ; "CdlPlay"
                dw aCdlforward        ; "CdlForward"
                dw aCdlbackward       ; "CdlBackward"
                dw aCdlreadn          ; "CdlReadN"
                dw aCdlstandby        ; "CdlStandby"
                dw aCdlstop           ; "CdlStop"
                dw aCdlpause          ; "CdlPause"
                dw aCdlreset          ; "CdlReset"
                dw aCdlmute           ; "CdlMute"
                dw aCdldemute         ; "CdlDemute"
                dw dword_800141CC+0x10
                dw dword_800141CC+4
                dw dword_800141CC
                dw aCdlgetlocl        ; "CdlGetlocL"
                dw aCdlgetlocp        ; "CdlGetlocP"
                dw dword_800141CC
                dw aCdlgettn          ; "CdlGetTN"
                dw aCdlgettd          ; "CdlGetTD"
                dw aCdlseekl          ; "CdlSeekL"
                dw aCdlseekp          ; "CdlSeekP"
                dw dword_800141CC
                dw dword_800141CC
                dw dword_800141CC
                dw dword_800141CC
                dw aCdlreads          ; "CdlReadS"
                dw dword_800141CC
                dw dword_800141CC
                dw dword_800141CC
                dw dword_800141CC
off_800A3F0C:   dw aNointr            ; DATA XREF: TEXT:8008C878?r
                                         ; CD_sync+44?o ...
                                         ; "NoIntr"
                dw aDataready         ; "DataReady"
                dw aComplete_0        ; "Complete"
                dw aAcknowledge       ; "Acknowledge"
                dw aDataend           ; "DataEnd"
                dw aDiskerror_0       ; "DiskError"
                dw dword_800141CC
                dw dword_800141CC
dword_800A3F2C: dw 0                  ; DATA XREF: sub_8008CEE8+2B8?r
                dw 0, 0, 0, 0, 0, 0
                dw 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0
                dw 1, 0, 0
                dw 1, 1, 0, 0, 0
                dw 1, 0, 0, 0, 0, 0
dword_800A3FAC: dw 0                  ; DATA XREF: CD_cw+12C?r
                                         ; CD_cw+140?o
                dw 0, 0
                dw 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0
                dw 1, 1, 0, 0, 0, 0
                dw 1, 0, 0, 0, 0
dword_800A402C: dw 1                  ; DATA XREF: sub_8008CEE8+138?r
                dw 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0
                dw 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
dword_800A40AC: dw 0                  ; DATA XREF: CD_cw+6C?r
                                         ; CD_cw+158?o
                dw 0
                dw 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 2, 1, 0, 0, 0
                dw 1, 0
                dw 1, 0, 0, 0, 0
dword_800A4110: dw 0                  ; DATA XREF: TEXT:8008E56C?w
                dw 0, 0, 0, 0, 0, 0
dword_800A412C: dw 0x1F801800         ; DATA XREF: sub_8008CEE8+4?r
                                         ; sub_8008CEE8:loc_8008CF64?r ...
dword_800A4130: dw 0x1F801801         ; DATA XREF: sub_8008CEE8+9C?r
                                         ; CD_cw:loc_8008DB2C?r ...
dword_800A4134: dw 0x1F801802         ; DATA XREF: sub_8008CEE8+108?r
                                         ; CD_cw:loc_8008DB04?r ...
dword_800A4138: dw 0x1F801803         ; DATA XREF: sub_8008CEE8+20?r
                                         ; sub_8008CEE8+F8?r ...
dword_800A413C: dw 0x1F801020         ; DATA XREF: CD_flush+C0?r
                                         ; CD_init+138?r ...
dword_800A4140: dw 0x1F801C00         ; DATA XREF: CD_initvol?r
                                         ; CD_initvol+34?r
byte_800A4144:  db 0                  ; DATA XREF: sub_8008CEE8+264?o
                                         ; sub_8008CEE8+26C?w ...
byte_800A4145:  db 0                  ; DATA XREF: sub_8008CEE8+3D0?w
                                         ; sub_8008CEE8+448?w ...
byte_800A4146:  db 0                  ; DATA XREF: sub_8008CEE8+43C?w
                                         ; sub_8008CEE8+440?r ...
                db 0
off_800A4148:   dw byte_800A4144      ; DATA XREF: CD_init+28?o
                dw 0x800C14F8
                dw byte_800A3E85
                dw dword_800A3E74
                dw byte_800A3E80
                dw aIdBiosCV186199    ; "$Id: bios.c,v 1.86 1997/03/28 07:42:42 "...
dword_800A4160: dw 0x1F801018         ; DATA XREF: CD_getsector+20?r
                                         ; CD_getsector2+20?r
dword_800A4164: dw 0x1F8010F0         ; DATA XREF: CD_getsector+40?r
                                         ; CD_getsector2+40?r
dword_800A4168: dw 0x1F8010B0         ; DATA XREF: CD_getsector+5C?r
                                         ; CD_getsector2+5C?r
dword_800A416C: dw 0x1F8010B4         ; DATA XREF: CD_getsector+70?r
                                         ; CD_getsector2+70?r
dword_800A4170: dw 0x1F8010B8         ; DATA XREF: CD_datasync+120?r
                                         ; CD_getsector+A0?r ...
                dw 0
                dw 0
                dw 0
dword_800A4180: dw 0                  ; DATA XREF: sprintf+68?o
                                         ; sprintf+70?r
dword_800A4184: dw 0                  ; DATA XREF: sprintf+74?r
dword_800A4188: dw 0                  ; DATA XREF: sprintf+78?r
                dw 0
                dw 0x27350, 0x440000, 0, 0
dword_800A41A0: dw 0                  ; DATA XREF: _putchar+3C?w
                                         ; _putchar+48?r ...
dword_800A41A4: dw 0                  ; DATA XREF: _putchar:loc_8008F2B4?r
                                         ; _putchar+C4?w ...
                dw 0
                dw 0
                db 0
byte_800A41B1:  db 0x20               ; DATA XREF: _putchar:loc_8008F280?r
                                         ; putchar:loc_8008F3B8?r ...
                dh 0x2020
                dw 0x20202020, 0x8082020, 0x20080808, 0x20202020, 0x20202020
                dw 0x20202020, 0x20202020, 0x10101820, 0x10101010, 0x10101010
                dw 0x10101010, 0x4040410, 0x4040404, 0x10040404, 0x10101010
                dw 0x41411010, 0x41414141, 0x1010101, 0x1010101, 0x1010101
                dw 0x1010101, 0x1010101, 0x10101010, 0x42421010, 0x42424242
                dw 0x2020202, 0x2020202, 0x2020202, 0x2020202, 0x2020202
                dw 0x10101010, 0x20, 0, 0, 0
                dw 0x77350, 0x440000
off_800A4248:   dw aIdSysCV1140199    ; DATA XREF: ResetGraph+54?o
                                         ; TEXT:off_800A4288?o
                                         ; "$Id: sys.c,v 1.140 1998/01/12 07:52:27 "...
                dw 0x800915D8
                dw 0x800915FC
                dw 0x80090DFC
                dw 0x800914E8
                dw 0x80091520
                dw 0x80091560
                dw 0x80091268
                dw 0x8009102C
                dw 0x800918AC
                dw 0x8009150C
                dw 0x80090D1C
                dw 0x800915A8
                dw 0x80091B0C
                dw 0x80090D04
                dw 0x80091C5C
off_800A4288:   dw off_800A4248       ; DATA XREF: ResetGraph+8C?r
                                         ; ResetGraph:loc_8008F62C?r ...
dword_800A428C: dw 0x8008BBA0         ; DATA XREF: ResetGraph+130?r
                                         ; SetGraphDebug+28?r ...
byte_800A4290:  db 0                  ; DATA XREF: ResetGraph+64?o
                                         ; ResetGraph:loc_8008F550?o ...
byte_800A4291:  db 0                  ; DATA XREF: ResetGraph+B8?w
                                         ; SetGraphQueue+C?o ...
byte_800A4292:  db 0                  ; DATA XREF: ResetGraph:loc_8008F5F8?r
                                         ; SetGraphDebug+4?o ...
byte_800A4293:  db 0                  ; DATA XREF: SetGraphDebug+38?r
                                         ; PutDispEnv:loc_800901D4?r
word_800A4294:  dh 0                  ; DATA XREF: ResetGraph+D8?w
                                         ; sub_8008F8CC+40?r ...
word_800A4296:  dh 0                  ; DATA XREF: ResetGraph+F0?w
                                         ; sub_8008F8CC+70?r ...
dword_800A4298: dw 0                  ; DATA XREF: sub_800915FC+90?w
                                         ; sub_800918AC+1FC?o ...
dword_800A429C: dw 0                  ; DATA XREF: DrawSyncCallback:loc_8008F7B0?r
                                         ; DrawSyncCallback+48?w ...
dword_800A42A0: dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                                         ; DATA XREF: ResetGraph+A8?o
                                         ; PutDrawEnv+94?o ...
                dw 0, 0, 0, 0, 0, 0
word_800A42FC:  dh 0                  ; DATA XREF: ResetGraph+F4?o
                                         ; SetDispMask+4C?o ...
word_800A42FE:  dh 0                  ; DATA XREF: PutDispEnv+B0?r
word_800A4300:  dh 0                  ; DATA XREF: PutDispEnv+C8?r
word_800A4302:  dh 0                  ; DATA XREF: PutDispEnv+E0?r
word_800A4304:  dh 0                  ; DATA XREF: PutDispEnv:loc_80090278?o
                                         ; PutDispEnv+1EC?r
word_800A4306:  dh 0                  ; DATA XREF: PutDispEnv+204?r
word_800A4308:  dh 0                  ; DATA XREF: PutDispEnv+21C?r
word_800A430A:  dh 0                  ; DATA XREF: PutDispEnv+234?r
dword_800A430C: dw 0                  ; DATA XREF: PutDispEnv+84?r
word_800A4310:  dh 0x400              ; DATA XREF: ResetGraph+C0?r
                dh 0
                dw 0x400, 0x400
word_800A431C:  dh 0x200              ; DATA XREF: ResetGraph+DC?r
                dh 0
                dw 0x200, 0x400
dword_800A4328: dw 0x4FFFFFF, 0x80000000
                                         ; DATA XREF: MoveImage+84?o
                                         ; TEXT:800922AC?o
dword_800A4330: dw 0                  ; DATA XREF: MoveImage:loc_8008FC28?o
                                         ; MoveImage+7C?w ...
dword_800A4334: dw 0                  ; DATA XREF: MoveImage+78?w
                                         ; TEXT:8009228C?w
dword_800A4338: dw 0                  ; DATA XREF: MoveImage+88?w
                                         ; TEXT:8009229C?w
dword_800A433C: dw 0x4FFFFFF, 0, 0, 0, 0
                                         ; DATA XREF: TEXT:8008FD1C?o
                                         ; ClearOTagR+78?o
dword_800A4350: dw 0                  ; DATA XREF: TEXT:8008FD14?o
                                         ; TEXT:8008FD30?w ...
                dw 0x80000000
                dw 0
                dw 0
                dw 0x10002
word_800A4364:  dh 0x24E              ; DATA XREF: PutDispEnv+2FC?r
word_800A4366:  dh 0xC4E              ; DATA XREF: PutDispEnv+308?r
                dw 0xC580258, 0xC9B021B, 0xC670267, 0xC6C026C, 0xC620262
                dw 0xC700270, 0xCB00230, 0xC7B027B, 0xC800280
byte_800A438C:  db 0xA                ; DATA XREF: PutDispEnv+2D0?r
                                         ; PutDispEnv:loc_800903F4?r ...
                db 8, 7, 5
                dw 4
dword_800A4394: dw 0x1F801810         ; DATA XREF: sub_8009102C+14C?r
                                         ; sub_8009102C+15C?r ...
dword_800A4398: dw 0x1F801814         ; DATA XREF: sub_80090D04?r
                                         ; sub_80090DFC+110?r ...
dword_800A439C: dw 0x1F8010A0         ; DATA XREF: sub_8009102C+1E0?r
                                         ; sub_80091268+228?r ...
dword_800A43A0: dw 0x1F8010A4         ; DATA XREF: sub_8009102C+1F4?r
                                         ; sub_80091268+23C?r ...
dword_800A43A4: dw 0x1F8010A8         ; DATA XREF: sub_8009102C+204?r
                                         ; sub_80091268+24C?r ...
dword_800A43A8: dw 0x1F8010E0         ; DATA XREF: sub_80090D1C+44?r
dword_800A43AC: dw 0x1F8010E4         ; DATA XREF: sub_80090D1C+54?r
dword_800A43B0: dw 0x1F8010E8         ; DATA XREF: sub_80090D1C+2C?r
                                         ; sub_80090D1C+64?r ...
dword_800A43B4: dw 0x1F8010F0         ; DATA XREF: sub_80090D1C+C?r
                                         ; sub_80091B0C+80?r ...
dword_800A43B8: dw 0                  ; DATA XREF: sub_800915FC:loc_80091648?r
                                         ; sub_800915FC+94?r ...
dword_800A43BC: dw 0                  ; DATA XREF: sub_800915FC+54?r
                                         ; sub_800915FC+9C?r ...
dword_800A43C0: dw 0                  ; DATA XREF: sub_800915FC+7C?w
                                         ; sub_800915FC+10C?r ...
dword_800A43C4: dw 0                  ; DATA XREF: sub_800918AC+4C?w
                                         ; sub_800918AC:loc_80091A5C?r
dword_800A43C8: dw 0                  ; DATA XREF: sub_80091B0C+28?w
                                         ; sub_80091B0C:loc_80091C28?r ...
dword_800A43CC: dw 0                  ; DATA XREF: sub_80091D98+14?w
                                         ; sub_80091DCC+10?r ...
dword_800A43D0: dw 0                  ; DATA XREF: sub_80091D98+1C?w
                                         ; sub_80091DCC+28?o ...
                dw 0
                dw 0
                dw 0
word_800A43E0:  dh 0                  ; DATA XREF: sin_1+14?r
                                         ; sin_1+34?r ...
                dh 6
                dw 0x13000D, 0x1F0019, 0x2C0026, 0x390032, 0x45003F
                dw 0x52004B, 0x5E0058, 0x6B0065, 0x770071, 0x84007E
                dw 0x90008A, 0x9D0097, 0xAA00A3, 0xB600B0, 0xC300BC
                dw 0xCF00C9, 0xDC00D6, 0xE800E2, 0xF500EF, 0x10100FB
                dw 0x10E0108, 0x11B0114, 0x1270121, 0x134012D, 0x140013A
                dw 0x14D0146, 0x1590153, 0x166015F, 0x172016C, 0x17F0178
                dw 0x18B0185, 0x1980191, 0x1A4019E, 0x1B101AA, 0x1BD01B7
                dw 0x1CA01C3, 0x1D601D0, 0x1E301DC, 0x1EF01E9, 0x1FC01F5
                dw 0x2080202, 0x215020E, 0x221021B, 0x22D0227, 0x23A0234
                dw 0x2460240, 0x253024D, 0x25F0259, 0x26C0265, 0x2780272
                dw 0x284027E, 0x291028B, 0x29D0297, 0x2AA02A3, 0x2B602B0
                dw 0x2C202BC, 0x2CF02C9, 0x2DB02D5, 0x2E802E1, 0x2F402EE
                dw 0x30002FA, 0x30D0306, 0x3190313, 0x325031F, 0x332032B
                dw 0x33E0338, 0x34A0344, 0x3560350, 0x363035D, 0x36F0369
                dw 0x37B0375, 0x3880381, 0x394038E, 0x3A0039A, 0x3AC03A6
                dw 0x3B903B2, 0x3C503BF, 0x3D103CB, 0x3DD03D7, 0x3E903E3
                dw 0x3F603EF, 0x40203FC, 0x40E0408, 0x41A0414, 0x4260420
                dw 0x432042C, 0x43E0438, 0x44B0444, 0x4570451, 0x463045D
                dw 0x46F0469, 0x47B0475, 0x4870481, 0x493048D, 0x49F0499
                dw 0x4AB04A5, 0x4B704B1, 0x4C304BD, 0x4CF04C9, 0x4DB04D5
                dw 0x4E704E1, 0x4F304ED, 0x4FF04F9, 0x50B0505, 0x5170511
                dw 0x523051D, 0x52F0529, 0x53A0534, 0x5460540, 0x552054C
                dw 0x55E0558, 0x56A0564, 0x5760570, 0x581057C, 0x58D0587
                dw 0x5990593, 0x5A5059F, 0x5B105AB, 0x5BC05B6, 0x5C805C2
                dw 0x5D405CE, 0x5DF05DA, 0x5EB05E5, 0x5F705F1, 0x60205FD
                dw 0x60E0608, 0x61A0614, 0x625061F, 0x631062B, 0x63C0637
                dw 0x6480642, 0x654064E, 0x65F0659, 0x66B0665, 0x6760670
                dw 0x682067C, 0x68D0687, 0x6990693, 0x6A4069E, 0x6AF06AA
                dw 0x6BB06B5, 0x6C606C1, 0x6D206CC, 0x6DD06D7, 0x6E806E3
                dw 0x6F406EE, 0x6FF06F9, 0x70A0705, 0x7150710, 0x721071B
                dw 0x72C0726, 0x7370732, 0x742073D, 0x74E0748, 0x7590753
                dw 0x764075E, 0x76F076A, 0x77A0775, 0x7850780, 0x790078B
                dw 0x79B0796, 0x7A607A1, 0x7B207AC, 0x7BD07B7, 0x7C807C2
                dw 0x7D207CD, 0x7DD07D8, 0x7E807E3, 0x7F307EE, 0x7FE07F9
                dw 0x8090804, 0x814080E, 0x81F0819, 0x82A0824, 0x834082F
                dw 0x83F083A, 0x84A0845, 0x855084F, 0x85F085A, 0x86A0865
                dw 0x875086F, 0x87F087A, 0x88A0885, 0x895088F, 0x89F089A
                dw 0x8AA08A5, 0x8B408AF, 0x8BF08BA, 0x8C908C4, 0x8D408CF
                dw 0x8DE08D9, 0x8E908E4, 0x8F308EE, 0x8FE08F8, 0x9080903
                dw 0x912090D, 0x91D0918, 0x9270922, 0x931092C, 0x93C0937
                dw 0x9460941, 0x950094B, 0x95A0955, 0x965095F, 0x96F096A
                dw 0x9790974, 0x983097E, 0x98D0988, 0x9970992, 0x9A1099C
                dw 0x9AB09A6, 0x9B509B0, 0x9BF09BA, 0x9C909C4, 0x9D309CE
                dw 0x9DD09D8, 0x9E709E2, 0x9F109EC, 0x9FB09F6, 0xA0409FF
                dw 0xA0E0A09, 0xA180A13, 0xA220A1D, 0xA2B0A26, 0xA350A30
                dw 0xA3F0A3A, 0xA480A44, 0xA520A4D, 0xA5C0A57, 0xA650A60
                dw 0xA6F0A6A, 0xA780A73, 0xA820A7D, 0xA8B0A86, 0xA950A90
                dw 0xA9E0A99, 0xAA70AA3, 0xAB10AAC, 0xABA0AB5, 0xAC30ABF
                dw 0xACD0AC8, 0xAD60AD1, 0xADF0ADB, 0xAE80AE4, 0xAF20AED
                dw 0xAFB0AF6, 0xB040AFF, 0xB0D0B08, 0xB160B11, 0xB1F0B1B
                dw 0xB280B24, 0xB310B2D, 0xB3A0B36, 0xB430B3E, 0xB4C0B47
                dw 0xB550B50, 0xB5E0B59, 0xB660B62, 0xB6F0B6B, 0xB780B74
                dw 0xB810B7C, 0xB890B85, 0xB920B8E, 0xB9B0B97, 0xBA30B9F
                dw 0xBAC0BA8, 0xBB50BB0, 0xBBD0BB9, 0xBC60BC1, 0xBCE0BCA
                dw 0xBD70BD2, 0xBDF0BDB, 0xBE80BE3, 0xBF00BEC, 0xBF80BF4
                dw 0xC010BFC, 0xC090C05, 0xC110C0D, 0xC190C15, 0xC220C1E
                dw 0xC2A0C26, 0xC320C2E, 0xC3A0C36, 0xC420C3E, 0xC4A0C46
                dw 0xC520C4E, 0xC5A0C56, 0xC620C5E, 0xC6A0C66, 0xC720C6E
                dw 0xC7A0C76, 0xC820C7E, 0xC8A0C86, 0xC910C8E, 0xC990C95
                dw 0xCA10C9D, 0xCA90CA5, 0xCB00CAC, 0xCB80CB4, 0xCC00CBC
                dw 0xCC70CC3, 0xCCF0CCB, 0xCD60CD2, 0xCDE0CDA, 0xCE50CE1
                dw 0xCED0CE9, 0xCF40CF0, 0xCFB0CF8, 0xD030CFF, 0xD0A0D06
                dw 0xD110D0E, 0xD180D15, 0xD200D1C, 0xD270D23, 0xD2E0D2A
                dw 0xD350D32, 0xD3C0D39, 0xD430D40, 0xD4A0D47, 0xD510D4E
                dw 0xD580D55, 0xD5F0D5C, 0xD660D62, 0xD6D0D69, 0xD740D70
                dw 0xD7A0D77, 0xD810D7E, 0xD880D85, 0xD8F0D8B, 0xD950D92
                dw 0xD9C0D99, 0xDA20D9F, 0xDA90DA6, 0xDB00DAC, 0xDB60DB3
                dw 0xDBC0DB9, 0xDC30DC0, 0xDC90DC6, 0xDD00DCC, 0xDD60DD3
                dw 0xDDC0DD9, 0xDE30DDF, 0xDE90DE6, 0xDEF0DEC, 0xDF50DF2
                dw 0xDFB0DF8, 0xE010DFE, 0xE070E04, 0xE0D0E0A, 0xE130E10
                dw 0xE190E16, 0xE1F0E1C, 0xE250E22, 0xE2B0E28, 0xE310E2E
                dw 0xE370E34, 0xE3C0E3A, 0xE420E3F, 0xE480E45, 0xE4D0E4B
                dw 0xE530E50, 0xE590E56, 0xE5E0E5B, 0xE640E61, 0xE690E66
                dw 0xE6F0E6C, 0xE740E71, 0xE790E77, 0xE7F0E7C, 0xE840E81
                dw 0xE890E87, 0xE8F0E8C, 0xE940E91, 0xE990E96, 0xE9E0E9B
                dw 0xEA30EA1, 0xEA80EA6, 0xEAD0EAB, 0xEB20EB0, 0xEB70EB5
                dw 0xEBC0EBA, 0xEC10EBF, 0xEC60EC3, 0xECB0EC8, 0xECF0ECD
                dw 0xED40ED2, 0xED90ED6, 0xEDD0EDB, 0xEE20EE0, 0xEE70EE4
                dw 0xEEB0EE9, 0xEF00EEE, 0xEF40EF2, 0xEF90EF7, 0xEFD0EFB
                dw 0xF020EFF, 0xF060F04, 0xF0A0F08, 0xF0E0F0C, 0xF130F11
                dw 0xF170F15, 0xF1B0F19, 0xF1F0F1D, 0xF230F21, 0xF270F25
                dw 0xF2B0F29, 0xF2F0F2D, 0xF330F31, 0xF370F35, 0xF3B0F39
                dw 0xF3F0F3D, 0xF430F41, 0xF460F45, 0xF4A0F48, 0xF4E0F4C
                dw 0xF510F50, 0xF550F53, 0xF590F57, 0xF5C0F5A, 0xF600F5E
                dw 0xF630F61, 0xF670F65, 0xF6A0F68, 0xF6D0F6C, 0xF710F6F
                dw 0xF740F72, 0xF770F76, 0xF7A0F79, 0xF7D0F7C, 0xF810F7F
                dw 0xF840F82, 0xF870F85, 0xF8A0F88, 0xF8D0F8B, 0xF900F8E
                dw 0xF930F91, 0xF950F94, 0xF980F97, 0xF9B0F9A, 0xF9E0F9C
                dw 0xFA10F9F, 0xFA30FA2, 0xFA60FA5, 0xFA80FA7, 0xFAB0FAA
                dw 0xFAE0FAC, 0xFB00FAF, 0xFB30FB1, 0xFB50FB4, 0xFB70FB6
                dw 0xFBA0FB8, 0xFBC0FBB, 0xFBE0FBD, 0xFC00FBF, 0xFC30FC2
                dw 0xFC50FC4, 0xFC70FC6, 0xFC90FC8, 0xFCB0FCA, 0xFCD0FCC
                dw 0xFCF0FCE, 0xFD10FD0, 0xFD30FD2, 0xFD50FD4, 0xFD60FD5
                dw 0xFD80FD7, 0xFDA0FD9, 0xFDC0FDB, 0xFDD0FDC, 0xFDF0FDE
                dw 0xFE00FE0, 0xFE20FE1, 0xFE30FE3, 0xFE50FE4, 0xFE60FE6
                dw 0xFE80FE7, 0xFE90FE8, 0xFEA0FEA, 0xFEC0FEB, 0xFED0FEC
                dw 0xFEE0FED, 0xFEF0FEF, 0xFF00FF0, 0xFF10FF1, 0xFF20FF2
                dw 0xFF30FF3, 0xFF40FF4, 0xFF50FF5, 0xFF60FF6, 0xFF70FF7
                dw 0xFF80FF8, 0xFF90FF8, 0xFF90FF9, 0xFFA0FFA, 0xFFB0FFA
                dw 0xFFB0FFB, 0xFFC0FFC, 0xFFC0FFC, 0xFFD0FFD, 0xFFD0FFD
                dw 0xFFE0FFE, 0xFFE0FFE, 0xFFF0FFE, 0xFFF0FFF, 0xFFF0FFF
                dw 0xFFF0FFF, 0x10001000, 0x10001000, 0x10001000, 0x10001000
                dw 0x10001000, 0x1000
                dw 0, 0, 0
dword_800A4BF0: dw 0                  ; DATA XREF: sub_80092680?w
                                         ; sub_80092680+10?r
                dw 0
                dw 0
                dw 0
word_800A4C00:  dh 0x1000             ; DATA XREF: SquareRoot0+5C?r
                dh 0x101F
                dw 0x105E103F, 0x109C107E, 0x10DA10BB, 0x111610F8, 0x11521134
                dw 0x118C116F, 0x11C611A9, 0x120011E3, 0x1238121C, 0x12701254
                dw 0x12A7128C, 0x12DE12C2, 0x131412F9, 0x1349132E, 0x137E1364
                dw 0x13B21398, 0x13E613CC, 0x14191400, 0x144C1432, 0x147E1465
                dw 0x14B01497, 0x14E114C8, 0x151214F9, 0x1542152A, 0x1572155A
                dw 0x15A2158A, 0x15D115B9, 0x160015E8, 0x162E1617, 0x165C1645
                dw 0x16891673, 0x16B716A0, 0x16E416CD, 0x171016FA, 0x173C1726
                dw 0x17681752, 0x1794177E, 0x17BF17AA, 0x17EA17D5, 0x18151800
                dw 0x183F182A, 0x18691854, 0x1893187E, 0x18BD18A8, 0x18E618D1
                dw 0x190F18FA, 0x19381923, 0x1960194C, 0x19881974, 0x19B0199C
                dw 0x19D819C4, 0x1A0019EC, 0x1A271A13, 0x1A4E1A3A, 0x1A751A61
                dw 0x1A9B1A88, 0x1AC21AAE, 0x1AE81AD5, 0x1B0E1AFB, 0x1B331B21
                dw 0x1B591B46, 0x1B7E1B6C, 0x1BA31B91, 0x1BC81BB6, 0x1BED1BDB
                dw 0x1C121C00, 0x1C361C24, 0x1C5A1C48, 0x1C7E1C6C, 0x1CA21C90
                dw 0x1CC61CB4, 0x1CE91CD8, 0x1D0D1CFB, 0x1D301D1E, 0x1D531D41
                dw 0x1D761D64, 0x1D981D87, 0x1DBB1DAA, 0x1DDD1DCC, 0x1E001DEE
                dw 0x1E221E11, 0x1E431E33, 0x1E651E54, 0x1E871E76, 0x1EA81E98
                dw 0x1ECA1EB9, 0x1EEB1EDA, 0x1F0C1EFB, 0x1F2D1F1C, 0x1F4E1F3D
                dw 0x1F6E1F5E, 0x1F8F1F7E, 0x1FAF1F9F, 0x1FCF1FBF, 0x1FEF1FDF
                dw 0, 0, 0, 0, 0
word_800A4D94:  dh 0x1000             ; DATA XREF: TEXT:800927FC?r
                                         ; sub_80092898+74?r
                dh 0xFE0
                dw 0xFA30FC1, 0xF680F85, 0xF300F4C, 0xEFB0F15, 0xEC70EE1
                dw 0xE960EAE, 0xE660E7E, 0xE380E4F, 0xE0C0E22, 0xDE20DF7
                dw 0xDB90DCD, 0xD910DA5, 0xD6B0D7E, 0xD450D58, 0xD210D33
                dw 0xCFF0D10, 0xCDD0CEE, 0xCBC0CCC, 0xC9C0CAC, 0xC7D0C8D
                dw 0xC5F0C6E, 0xC420C51, 0xC260C34, 0xC0A0C18, 0xBEF0BFD
                dw 0xBD50BE2, 0xBBB0BC8, 0xBA20BAF, 0xB8A0B96, 0xB720B7E
                dw 0xB5B0B67, 0xB450B50, 0xB2E0B39, 0xB190B24, 0xB040B0E
                dw 0xAEF0AF9, 0xADB0AE5, 0xAC70AD1, 0xAB40ABD, 0xAA10AAA
                dw 0xA8E0A97, 0xA7C0A85, 0xA6A0A73, 0xA590A61, 0xA470A50
                dw 0xA370A3F, 0xA260A2E, 0xA160A1E, 0xA060A0E, 0x9F609FE
                dw 0x9E709EF, 0x9D809E0, 0x9C909D1, 0x9BB09C2, 0x9AD09B4
                dw 0x99E09A5, 0x9910998, 0x983098A, 0x976097C, 0x969096F
                dw 0x95C0962, 0x94F0955, 0x9430949, 0x936093C, 0x92A0930
                dw 0x91E0924, 0x9120918, 0x907090D, 0x8FB0901, 0x8F008F6
                dw 0x8E508EB, 0x8DA08E0, 0x8CF08D5, 0x8C508CA, 0x8BA08BF
                dw 0x8B008B5, 0x8A608AB, 0x89C08A1, 0x8920897, 0x888088D
                dw 0x87E0883, 0x875087A, 0x86B0870, 0x8620867, 0x859085E
                dw 0x8500855, 0x847084C, 0x83E0843, 0x836083A, 0x82D0831
                dw 0x8240829, 0x81C0820, 0x8140818, 0x80C0810, 0x8040808
                dw 0, 0, 0
dword_800A4F20: dw 0x10000000         ; DATA XREF: RotMatrix+20?r
                                         ; RotMatrix+48?r ...
                dw 0x10000006, 0x1000000D, 0x10000013, 0x10000019, 0x1000001F
                dw 0x10000026, 0x1000002C, 0x10000032, 0x10000039, 0x1000003F
                dw 0xFFF0045, 0xFFF004B, 0xFFF0052, 0xFFF0058, 0xFFF005E
                dw 0xFFF0065, 0xFFF006B, 0xFFE0071, 0xFFE0077, 0xFFE007E
                dw 0xFFE0084, 0xFFE008A, 0xFFD0090, 0xFFD0097, 0xFFD009D
                dw 0xFFD00A3, 0xFFC00AA, 0xFFC00B0, 0xFFC00B6, 0xFFC00BC
                dw 0xFFB00C3, 0xFFB00C9, 0xFFB00CF, 0xFFA00D6, 0xFFA00DC
                dw 0xFFA00E2, 0xFF900E8, 0xFF900EF, 0xFF900F5, 0xFF800FB
                dw 0xFF80101, 0xFF80108, 0xFF7010E, 0xFF70114, 0xFF6011B
                dw 0xFF60121, 0xFF50127, 0xFF5012D, 0xFF40134, 0xFF4013A
                dw 0xFF30140, 0xFF30146, 0xFF2014D, 0xFF20153, 0xFF10159
                dw 0xFF1015F, 0xFF00166, 0xFF0016C, 0xFEF0172, 0xFEF0178
                dw 0xFEE017F, 0xFED0185, 0xFED018B, 0xFEC0191, 0xFEC0198
                dw 0xFEB019E, 0xFEA01A4, 0xFEA01AA, 0xFE901B1, 0xFE801B7
                dw 0xFE801BD, 0xFE701C3, 0xFE601CA, 0xFE601D0, 0xFE501D6
                dw 0xFE401DC, 0xFE301E3, 0xFE301E9, 0xFE201EF, 0xFE101F5
                dw 0xFE001FC, 0xFE00202, 0xFDF0208, 0xFDE020E, 0xFDD0215
                dw 0xFDC021B, 0xFDC0221, 0xFDB0227, 0xFDA022D, 0xFD90234
                dw 0xFD8023A, 0xFD70240, 0xFD60246, 0xFD5024D, 0xFD50253
                dw 0xFD40259, 0xFD3025F, 0xFD20265, 0xFD1026C, 0xFD00272
                dw 0xFCF0278, 0xFCE027E, 0xFCD0284, 0xFCC028B, 0xFCB0291
                dw 0xFCA0297, 0xFC9029D, 0xFC802A3, 0xFC702AA, 0xFC602B0
                dw 0xFC502B6, 0xFC402BC, 0xFC302C2, 0xFC202C9, 0xFC002CF
                dw 0xFBF02D5, 0xFBE02DB, 0xFBD02E1, 0xFBC02E8, 0xFBB02EE
                dw 0xFBA02F4, 0xFB802FA, 0xFB70300, 0xFB60306, 0xFB5030D
                dw 0xFB40313, 0xFB30319, 0xFB1031F, 0xFB00325, 0xFAF032B
                dw 0xFAE0332, 0xFAC0338, 0xFAB033E, 0xFAA0344, 0xFA8034A
                dw 0xFA70350, 0xFA60356, 0xFA5035D, 0xFA30363, 0xFA20369
                dw 0xFA1036F, 0xF9F0375, 0xF9E037B, 0xF9C0381, 0xF9B0388
                dw 0xF9A038E, 0xF980394, 0xF97039A, 0xF9503A0, 0xF9403A6
                dw 0xF9303AC, 0xF9103B2, 0xF9003B9, 0xF8E03BF, 0xF8D03C5
                dw 0xF8B03CB, 0xF8A03D1, 0xF8803D7, 0xF8703DD, 0xF8503E3
                dw 0xF8403E9, 0xF8203EF, 0xF8103F6, 0xF7F03FC, 0xF7D0402
                dw 0xF7C0408, 0xF7A040E, 0xF790414, 0xF77041A, 0xF760420
                dw 0xF740426, 0xF72042C, 0xF710432, 0xF6F0438, 0xF6D043E
                dw 0xF6C0444, 0xF6A044B, 0xF680451, 0xF670457, 0xF65045D
                dw 0xF630463, 0xF610469, 0xF60046F, 0xF5E0475, 0xF5C047B
                dw 0xF5A0481, 0xF590487, 0xF57048D, 0xF550493, 0xF530499
                dw 0xF51049F, 0xF5004A5, 0xF4E04AB, 0xF4C04B1, 0xF4A04B7
                dw 0xF4804BD, 0xF4604C3, 0xF4504C9, 0xF4304CF, 0xF4104D5
                dw 0xF3F04DB, 0xF3D04E1, 0xF3B04E7, 0xF3904ED, 0xF3704F3
                dw 0xF3504F9, 0xF3304FF, 0xF310505, 0xF2F050B, 0xF2D0511
                dw 0xF2B0517, 0xF29051D, 0xF270523, 0xF250529, 0xF23052F
                dw 0xF210534, 0xF1F053A, 0xF1D0540, 0xF1B0546, 0xF19054C
                dw 0xF170552, 0xF150558, 0xF13055E, 0xF110564, 0xF0E056A
                dw 0xF0C0570, 0xF0A0576, 0xF08057C, 0xF060581, 0xF040587
                dw 0xF02058D, 0xEFF0593, 0xEFD0599, 0xEFB059F, 0xEF905A5
                dw 0xEF705AB, 0xEF405B1, 0xEF205B6, 0xEF005BC, 0xEEE05C2
                dw 0xEEB05C8, 0xEE905CE, 0xEE705D4, 0xEE405DA, 0xEE205DF
                dw 0xEE005E5, 0xEDD05EB, 0xEDB05F1, 0xED905F7, 0xED605FD
                dw 0xED40602, 0xED20608, 0xECF060E, 0xECD0614, 0xECB061A
                dw 0xEC8061F, 0xEC60625, 0xEC3062B, 0xEC10631, 0xEBF0637
                dw 0xEBC063C, 0xEBA0642, 0xEB70648, 0xEB5064E, 0xEB20654
                dw 0xEB00659, 0xEAD065F, 0xEAB0665, 0xEA8066B, 0xEA60670
                dw 0xEA30676, 0xEA1067C, 0xE9E0682, 0xE9B0687, 0xE99068D
                dw 0xE960693, 0xE940699, 0xE91069E, 0xE8F06A4, 0xE8C06AA
                dw 0xE8906AF, 0xE8706B5, 0xE8406BB, 0xE8106C1, 0xE7F06C6
                dw 0xE7C06CC, 0xE7906D2, 0xE7706D7, 0xE7406DD, 0xE7106E3
                dw 0xE6F06E8, 0xE6C06EE, 0xE6906F4, 0xE6606F9, 0xE6406FF
                dw 0xE610705, 0xE5E070A, 0xE5B0710, 0xE590715, 0xE56071B
                dw 0xE530721, 0xE500726, 0xE4D072C, 0xE4B0732, 0xE480737
                dw 0xE45073D, 0xE420742, 0xE3F0748, 0xE3C074E, 0xE3A0753
                dw 0xE370759, 0xE34075E, 0xE310764, 0xE2E076A, 0xE2B076F
                dw 0xE280775, 0xE25077A, 0xE220780, 0xE1F0785, 0xE1C078B
                dw 0xE190790, 0xE160796, 0xE13079B, 0xE1007A1, 0xE0D07A6
                dw 0xE0A07AC, 0xE0707B2, 0xE0407B7, 0xE0107BD, 0xDFE07C2
                dw 0xDFB07C8, 0xDF807CD, 0xDF507D2, 0xDF207D8, 0xDEF07DD
                dw 0xDEC07E3, 0xDE907E8, 0xDE607EE, 0xDE307F3, 0xDDF07F9
                dw 0xDDC07FE, 0xDD90804, 0xDD60809, 0xDD3080E, 0xDD00814
                dw 0xDCC0819, 0xDC9081F, 0xDC60824, 0xDC3082A, 0xDC0082F
                dw 0xDBC0834, 0xDB9083A, 0xDB6083F, 0xDB30845, 0xDB0084A
                dw 0xDAC084F, 0xDA90855, 0xDA6085A, 0xDA2085F, 0xD9F0865
                dw 0xD9C086A, 0xD99086F, 0xD950875, 0xD92087A, 0xD8F087F
                dw 0xD8B0885, 0xD88088A, 0xD85088F, 0xD810895, 0xD7E089A
                dw 0xD7A089F, 0xD7708A5, 0xD7408AA, 0xD7008AF, 0xD6D08B4
                dw 0xD6908BA, 0xD6608BF, 0xD6208C4, 0xD5F08C9, 0xD5C08CF
                dw 0xD5808D4, 0xD5508D9, 0xD5108DE, 0xD4E08E4, 0xD4A08E9
                dw 0xD4708EE, 0xD4308F3, 0xD4008F8, 0xD3C08FE, 0xD390903
                dw 0xD350908, 0xD32090D, 0xD2E0912, 0xD2A0918, 0xD27091D
                dw 0xD230922, 0xD200927, 0xD1C092C, 0xD180931, 0xD150937
                dw 0xD11093C, 0xD0E0941, 0xD0A0946, 0xD06094B, 0xD030950
                dw 0xCFF0955, 0xCFB095A, 0xCF8095F, 0xCF40965, 0xCF0096A
                dw 0xCED096F, 0xCE90974, 0xCE50979, 0xCE1097E, 0xCDE0983
                dw 0xCDA0988, 0xCD6098D, 0xCD20992, 0xCCF0997, 0xCCB099C
                dw 0xCC709A1, 0xCC309A6, 0xCC009AB, 0xCBC09B0, 0xCB809B5
                dw 0xCB409BA, 0xCB009BF, 0xCAC09C4, 0xCA909C9, 0xCA509CE
                dw 0xCA109D3, 0xC9D09D8, 0xC9909DD, 0xC9509E2, 0xC9109E7
                dw 0xC8E09EC, 0xC8A09F1, 0xC8609F6, 0xC8209FB, 0xC7E09FF
                dw 0xC7A0A04, 0xC760A09, 0xC720A0E, 0xC6E0A13, 0xC6A0A18
                dw 0xC660A1D, 0xC620A22, 0xC5E0A26, 0xC5A0A2B, 0xC560A30
                dw 0xC520A35, 0xC4E0A3A, 0xC4A0A3F, 0xC460A44, 0xC420A48
                dw 0xC3E0A4D, 0xC3A0A52, 0xC360A57, 0xC320A5C, 0xC2E0A60
                dw 0xC2A0A65, 0xC260A6A, 0xC220A6F, 0xC1E0A73, 0xC190A78
                dw 0xC150A7D, 0xC110A82, 0xC0D0A86, 0xC090A8B, 0xC050A90
                dw 0xC010A95, 0xBFC0A99, 0xBF80A9E, 0xBF40AA3, 0xBF00AA7
                dw 0xBEC0AAC, 0xBE80AB1, 0xBE30AB5, 0xBDF0ABA, 0xBDB0ABF
                dw 0xBD70AC3, 0xBD20AC8, 0xBCE0ACD, 0xBCA0AD1, 0xBC60AD6
                dw 0xBC10ADB, 0xBBD0ADF, 0xBB90AE4, 0xBB50AE8, 0xBB00AED
                dw 0xBAC0AF2, 0xBA80AF6, 0xBA30AFB, 0xB9F0AFF, 0xB9B0B04
                dw 0xB970B08, 0xB920B0D, 0xB8E0B11, 0xB890B16, 0xB850B1B
                dw 0xB810B1F, 0xB7C0B24, 0xB780B28, 0xB740B2D, 0xB6F0B31
                dw 0xB6B0B36, 0xB660B3A, 0xB620B3E, 0xB5E0B43, 0xB590B47
                dw 0xB550B4C, 0xB500B50
                dw 0xB4C0B55, 0xB470B59, 0xB430B5E, 0xB3E0B62, 0xB3A0B66
                dw 0xB360B6B, 0xB310B6F, 0xB2D0B74, 0xB280B78, 0xB240B7C
                dw 0xB1F0B81, 0xB1B0B85, 0xB160B89, 0xB110B8E, 0xB0D0B92
                dw 0xB080B97, 0xB040B9B, 0xAFF0B9F, 0xAFB0BA3, 0xAF60BA8
                dw 0xAF20BAC, 0xAED0BB0, 0xAE80BB5, 0xAE40BB9, 0xADF0BBD
                dw 0xADB0BC1, 0xAD60BC6, 0xAD10BCA, 0xACD0BCE, 0xAC80BD2
                dw 0xAC30BD7, 0xABF0BDB, 0xABA0BDF, 0xAB50BE3, 0xAB10BE8
                dw 0xAAC0BEC, 0xAA70BF0, 0xAA30BF4, 0xA9E0BF8, 0xA990BFC
                dw 0xA950C01, 0xA900C05, 0xA8B0C09, 0xA860C0D, 0xA820C11
                dw 0xA7D0C15, 0xA780C19, 0xA730C1E, 0xA6F0C22, 0xA6A0C26
                dw 0xA650C2A, 0xA600C2E, 0xA5C0C32, 0xA570C36, 0xA520C3A
                dw 0xA4D0C3E, 0xA480C42, 0xA440C46, 0xA3F0C4A, 0xA3A0C4E
                dw 0xA350C52, 0xA300C56, 0xA2B0C5A, 0xA260C5E, 0xA220C62
                dw 0xA1D0C66, 0xA180C6A, 0xA130C6E, 0xA0E0C72, 0xA090C76
                dw 0xA040C7A, 0x9FF0C7E, 0x9FB0C82, 0x9F60C86, 0x9F10C8A
                dw 0x9EC0C8E, 0x9E70C91, 0x9E20C95, 0x9DD0C99, 0x9D80C9D
                dw 0x9D30CA1, 0x9CE0CA5, 0x9C90CA9, 0x9C40CAC, 0x9BF0CB0
                dw 0x9BA0CB4, 0x9B50CB8, 0x9B00CBC, 0x9AB0CC0, 0x9A60CC3
                dw 0x9A10CC7, 0x99C0CCB, 0x9970CCF, 0x9920CD2, 0x98D0CD6
                dw 0x9880CDA, 0x9830CDE, 0x97E0CE1, 0x9790CE5, 0x9740CE9
                dw 0x96F0CED, 0x96A0CF0, 0x9650CF4, 0x95F0CF8, 0x95A0CFB
                dw 0x9550CFF, 0x9500D03, 0x94B0D06, 0x9460D0A, 0x9410D0E
                dw 0x93C0D11, 0x9370D15, 0x9310D18, 0x92C0D1C, 0x9270D20
                dw 0x9220D23, 0x91D0D27, 0x9180D2A, 0x9120D2E, 0x90D0D32
                dw 0x9080D35, 0x9030D39, 0x8FE0D3C, 0x8F80D40, 0x8F30D43
                dw 0x8EE0D47, 0x8E90D4A, 0x8E40D4E, 0x8DE0D51, 0x8D90D55
                dw 0x8D40D58, 0x8CF0D5C, 0x8C90D5F, 0x8C40D62, 0x8BF0D66
                dw 0x8BA0D69, 0x8B40D6D, 0x8AF0D70, 0x8AA0D74, 0x8A50D77
                dw 0x89F0D7A, 0x89A0D7E, 0x8950D81, 0x88F0D85, 0x88A0D88
                dw 0x8850D8B, 0x87F0D8F, 0x87A0D92, 0x8750D95, 0x86F0D99
                dw 0x86A0D9C, 0x8650D9F, 0x85F0DA2, 0x85A0DA6, 0x8550DA9
                dw 0x84F0DAC, 0x84A0DB0, 0x8450DB3, 0x83F0DB6, 0x83A0DB9
                dw 0x8340DBC, 0x82F0DC0, 0x82A0DC3, 0x8240DC6, 0x81F0DC9
                dw 0x8190DCC, 0x8140DD0, 0x80E0DD3, 0x8090DD6, 0x8040DD9
                dw 0x7FE0DDC, 0x7F90DDF, 0x7F30DE3, 0x7EE0DE6, 0x7E80DE9
                dw 0x7E30DEC, 0x7DD0DEF, 0x7D80DF2, 0x7D20DF5, 0x7CD0DF8
                dw 0x7C80DFB, 0x7C20DFE, 0x7BD0E01, 0x7B70E04, 0x7B20E07
                dw 0x7AC0E0A, 0x7A60E0D, 0x7A10E10, 0x79B0E13, 0x7960E16
                dw 0x7900E19, 0x78B0E1C, 0x7850E1F, 0x7800E22, 0x77A0E25
                dw 0x7750E28, 0x76F0E2B, 0x76A0E2E, 0x7640E31, 0x75E0E34
                dw 0x7590E37, 0x7530E3A, 0x74E0E3C, 0x7480E3F, 0x7420E42
                dw 0x73D0E45, 0x7370E48, 0x7320E4B, 0x72C0E4D, 0x7260E50
                dw 0x7210E53, 0x71B0E56, 0x7150E59, 0x7100E5B, 0x70A0E5E
                dw 0x7050E61, 0x6FF0E64, 0x6F90E66, 0x6F40E69, 0x6EE0E6C
                dw 0x6E80E6F, 0x6E30E71, 0x6DD0E74, 0x6D70E77, 0x6D20E79
                dw 0x6CC0E7C, 0x6C60E7F, 0x6C10E81, 0x6BB0E84, 0x6B50E87
                dw 0x6AF0E89, 0x6AA0E8C, 0x6A40E8F, 0x69E0E91, 0x6990E94
                dw 0x6930E96, 0x68D0E99, 0x6870E9B, 0x6820E9E, 0x67C0EA1
                dw 0x6760EA3, 0x6700EA6, 0x66B0EA8, 0x6650EAB, 0x65F0EAD
                dw 0x6590EB0, 0x6540EB2, 0x64E0EB5, 0x6480EB7, 0x6420EBA
                dw 0x63C0EBC, 0x6370EBF, 0x6310EC1, 0x62B0EC3, 0x6250EC6
                dw 0x61F0EC8, 0x61A0ECB, 0x6140ECD, 0x60E0ECF, 0x6080ED2
                dw 0x6020ED4, 0x5FD0ED6, 0x5F70ED9, 0x5F10EDB, 0x5EB0EDD
                dw 0x5E50EE0, 0x5DF0EE2, 0x5DA0EE4, 0x5D40EE7, 0x5CE0EE9
                dw 0x5C80EEB, 0x5C20EEE, 0x5BC0EF0, 0x5B60EF2, 0x5B10EF4
                dw 0x5AB0EF7, 0x5A50EF9, 0x59F0EFB, 0x5990EFD, 0x5930EFF
                dw 0x58D0F02, 0x5870F04, 0x5810F06, 0x57C0F08, 0x5760F0A
                dw 0x5700F0C, 0x56A0F0E, 0x5640F11, 0x55E0F13, 0x5580F15
                dw 0x5520F17, 0x54C0F19, 0x5460F1B, 0x5400F1D, 0x53A0F1F
                dw 0x5340F21, 0x52F0F23, 0x5290F25, 0x5230F27, 0x51D0F29
                dw 0x5170F2B, 0x5110F2D, 0x50B0F2F, 0x5050F31, 0x4FF0F33
                dw 0x4F90F35, 0x4F30F37, 0x4ED0F39, 0x4E70F3B, 0x4E10F3D
                dw 0x4DB0F3F, 0x4D50F41, 0x4CF0F43, 0x4C90F45, 0x4C30F46
                dw 0x4BD0F48, 0x4B70F4A, 0x4B10F4C, 0x4AB0F4E, 0x4A50F50
                dw 0x49F0F51, 0x4990F53, 0x4930F55, 0x48D0F57, 0x4870F59
                dw 0x4810F5A, 0x47B0F5C, 0x4750F5E, 0x46F0F60, 0x4690F61
                dw 0x4630F63, 0x45D0F65, 0x4570F67, 0x4510F68, 0x44B0F6A
                dw 0x4440F6C, 0x43E0F6D, 0x4380F6F, 0x4320F71, 0x42C0F72
                dw 0x4260F74, 0x4200F76, 0x41A0F77, 0x4140F79, 0x40E0F7A
                dw 0x4080F7C, 0x4020F7D, 0x3FC0F7F, 0x3F60F81, 0x3EF0F82
                dw 0x3E90F84, 0x3E30F85, 0x3DD0F87, 0x3D70F88, 0x3D10F8A
                dw 0x3CB0F8B, 0x3C50F8D, 0x3BF0F8E, 0x3B90F90, 0x3B20F91
                dw 0x3AC0F93, 0x3A60F94, 0x3A00F95, 0x39A0F97, 0x3940F98
                dw 0x38E0F9A, 0x3880F9B, 0x3810F9C, 0x37B0F9E, 0x3750F9F
                dw 0x36F0FA1, 0x3690FA2, 0x3630FA3, 0x35D0FA5, 0x3560FA6
                dw 0x3500FA7, 0x34A0FA8, 0x3440FAA, 0x33E0FAB, 0x3380FAC
                dw 0x3320FAE, 0x32B0FAF, 0x3250FB0, 0x31F0FB1, 0x3190FB3
                dw 0x3130FB4, 0x30D0FB5, 0x3060FB6, 0x3000FB7, 0x2FA0FB8
                dw 0x2F40FBA, 0x2EE0FBB, 0x2E80FBC, 0x2E10FBD, 0x2DB0FBE
                dw 0x2D50FBF, 0x2CF0FC0, 0x2C90FC2, 0x2C20FC3, 0x2BC0FC4
                dw 0x2B60FC5, 0x2B00FC6, 0x2AA0FC7, 0x2A30FC8, 0x29D0FC9
                dw 0x2970FCA, 0x2910FCB, 0x28B0FCC, 0x2840FCD, 0x27E0FCE
                dw 0x2780FCF, 0x2720FD0, 0x26C0FD1, 0x2650FD2, 0x25F0FD3
                dw 0x2590FD4, 0x2530FD5, 0x24D0FD5, 0x2460FD6, 0x2400FD7
                dw 0x23A0FD8, 0x2340FD9, 0x22D0FDA, 0x2270FDB, 0x2210FDC
                dw 0x21B0FDC, 0x2150FDD, 0x20E0FDE, 0x2080FDF, 0x2020FE0
                dw 0x1FC0FE0, 0x1F50FE1, 0x1EF0FE2, 0x1E90FE3, 0x1E30FE3
                dw 0x1DC0FE4, 0x1D60FE5, 0x1D00FE6, 0x1CA0FE6, 0x1C30FE7
                dw 0x1BD0FE8, 0x1B70FE8, 0x1B10FE9, 0x1AA0FEA, 0x1A40FEA
                dw 0x19E0FEB, 0x1980FEC, 0x1910FEC, 0x18B0FED, 0x1850FED
                dw 0x17F0FEE, 0x1780FEF, 0x1720FEF, 0x16C0FF0, 0x1660FF0
                dw 0x15F0FF1, 0x1590FF1, 0x1530FF2, 0x14D0FF2, 0x1460FF3
                dw 0x1400FF3, 0x13A0FF4, 0x1340FF4, 0x12D0FF5, 0x1270FF5
                dw 0x1210FF6, 0x11B0FF6, 0x1140FF7, 0x10E0FF7, 0x1080FF8
                dw 0x1010FF8, 0xFB0FF8, 0xF50FF9, 0xEF0FF9, 0xE80FF9
                dw 0xE20FFA, 0xDC0FFA, 0xD60FFA, 0xCF0FFB, 0xC90FFB
                dw 0xC30FFB, 0xBC0FFC, 0xB60FFC, 0xB00FFC, 0xAA0FFC
                dw 0xA30FFD, 0x9D0FFD, 0x970FFD, 0x900FFD, 0x8A0FFE
                dw 0x840FFE, 0x7E0FFE, 0x770FFE, 0x710FFE, 0x6B0FFF
                dw 0x650FFF, 0x5E0FFF, 0x580FFF, 0x520FFF, 0x4B0FFF
                dw 0x450FFF, 0x3F1000, 0x391000, 0x321000, 0x2C1000
                dw 0x261000, 0x1F1000, 0x191000, 0x131000, 0xD1000
                dw 0x61000, 0x1000
                dw 0xFFFA1000, 0xFFF31000, 0xFFED1000, 0xFFE71000, 0xFFE11000
                dw 0xFFDA1000, 0xFFD41000, 0xFFCE1000, 0xFFC71000, 0xFFC11000
                dw 0xFFBB0FFF, 0xFFB50FFF, 0xFFAE0FFF, 0xFFA80FFF, 0xFFA20FFF
                dw 0xFF9B0FFF, 0xFF950FFF, 0xFF8F0FFE, 0xFF890FFE, 0xFF820FFE
                dw 0xFF7C0FFE, 0xFF760FFE, 0xFF700FFD, 0xFF690FFD, 0xFF630FFD
                dw 0xFF5D0FFD, 0xFF560FFC, 0xFF500FFC, 0xFF4A0FFC, 0xFF440FFC
                dw 0xFF3D0FFB, 0xFF370FFB, 0xFF310FFB, 0xFF2A0FFA, 0xFF240FFA
                dw 0xFF1E0FFA, 0xFF180FF9, 0xFF110FF9, 0xFF0B0FF9, 0xFF050FF8
                dw 0xFEFF0FF8, 0xFEF80FF8, 0xFEF20FF7, 0xFEEC0FF7, 0xFEE50FF6
                dw 0xFEDF0FF6, 0xFED90FF5, 0xFED30FF5, 0xFECC0FF4, 0xFEC60FF4
                dw 0xFEC00FF3, 0xFEBA0FF3, 0xFEB30FF2, 0xFEAD0FF2, 0xFEA70FF1
                dw 0xFEA10FF1, 0xFE9A0FF0, 0xFE940FF0, 0xFE8E0FEF, 0xFE880FEF
                dw 0xFE810FEE, 0xFE7B0FED, 0xFE750FED, 0xFE6F0FEC, 0xFE680FEC
                dw 0xFE620FEB, 0xFE5C0FEA, 0xFE560FEA, 0xFE4F0FE9, 0xFE490FE8
                dw 0xFE430FE8, 0xFE3D0FE7, 0xFE360FE6, 0xFE300FE6, 0xFE2A0FE5
                dw 0xFE240FE4, 0xFE1D0FE3, 0xFE170FE3, 0xFE110FE2, 0xFE0B0FE1
                dw 0xFE040FE0, 0xFDFE0FE0, 0xFDF80FDF, 0xFDF20FDE, 0xFDEB0FDD
                dw 0xFDE50FDC, 0xFDDF0FDC, 0xFDD90FDB, 0xFDD30FDA, 0xFDCC0FD9
                dw 0xFDC60FD8, 0xFDC00FD7, 0xFDBA0FD6, 0xFDB30FD5, 0xFDAD0FD5
                dw 0xFDA70FD4, 0xFDA10FD3, 0xFD9B0FD2, 0xFD940FD1, 0xFD8E0FD0
                dw 0xFD880FCF, 0xFD820FCE, 0xFD7C0FCD, 0xFD750FCC, 0xFD6F0FCB
                dw 0xFD690FCA, 0xFD630FC9, 0xFD5D0FC8, 0xFD560FC7, 0xFD500FC6
                dw 0xFD4A0FC5, 0xFD440FC4, 0xFD3E0FC3, 0xFD370FC2, 0xFD310FC0
                dw 0xFD2B0FBF, 0xFD250FBE, 0xFD1F0FBD, 0xFD180FBC, 0xFD120FBB
                dw 0xFD0C0FBA, 0xFD060FB8, 0xFD000FB7, 0xFCFA0FB6, 0xFCF30FB5
                dw 0xFCED0FB4, 0xFCE70FB3, 0xFCE10FB1, 0xFCDB0FB0, 0xFCD50FAF
                dw 0xFCCE0FAE, 0xFCC80FAC, 0xFCC20FAB, 0xFCBC0FAA, 0xFCB60FA8
                dw 0xFCB00FA7, 0xFCAA0FA6, 0xFCA30FA5, 0xFC9D0FA3, 0xFC970FA2
                dw 0xFC910FA1, 0xFC8B0F9F, 0xFC850F9E, 0xFC7F0F9C, 0xFC780F9B
                dw 0xFC720F9A, 0xFC6C0F98, 0xFC660F97, 0xFC600F95, 0xFC5A0F94
                dw 0xFC540F93, 0xFC4E0F91, 0xFC470F90, 0xFC410F8E, 0xFC3B0F8D
                dw 0xFC350F8B, 0xFC2F0F8A, 0xFC290F88, 0xFC230F87, 0xFC1D0F85
                dw 0xFC170F84, 0xFC110F82, 0xFC0A0F81, 0xFC040F7F, 0xFBFE0F7D
                dw 0xFBF80F7C, 0xFBF20F7A, 0xFBEC0F79, 0xFBE60F77, 0xFBE00F76
                dw 0xFBDA0F74, 0xFBD40F72, 0xFBCE0F71, 0xFBC80F6F, 0xFBC20F6D
                dw 0xFBBC0F6C, 0xFBB50F6A, 0xFBAF0F68, 0xFBA90F67, 0xFBA30F65
                dw 0xFB9D0F63, 0xFB970F61, 0xFB910F60, 0xFB8B0F5E, 0xFB850F5C
                dw 0xFB7F0F5A, 0xFB790F59, 0xFB730F57, 0xFB6D0F55, 0xFB670F53
                dw 0xFB610F51, 0xFB5B0F50, 0xFB550F4E, 0xFB4F0F4C, 0xFB490F4A
                dw 0xFB430F48, 0xFB3D0F46, 0xFB370F45, 0xFB310F43, 0xFB2B0F41
                dw 0xFB250F3F, 0xFB1F0F3D, 0xFB190F3B, 0xFB130F39, 0xFB0D0F37
                dw 0xFB070F35, 0xFB010F33, 0xFAFB0F31, 0xFAF50F2F, 0xFAEF0F2D
                dw 0xFAE90F2B, 0xFAE30F29, 0xFADD0F27, 0xFAD70F25, 0xFAD10F23
                dw 0xFACC0F21, 0xFAC60F1F, 0xFAC00F1D, 0xFABA0F1B, 0xFAB40F19
                dw 0xFAAE0F17, 0xFAA80F15, 0xFAA20F13, 0xFA9C0F11, 0xFA960F0E
                dw 0xFA900F0C, 0xFA8A0F0A, 0xFA840F08, 0xFA7F0F06, 0xFA790F04
                dw 0xFA730F02, 0xFA6D0EFF, 0xFA670EFD, 0xFA610EFB, 0xFA5B0EF9
                dw 0xFA550EF7, 0xFA4F0EF4, 0xFA4A0EF2, 0xFA440EF0, 0xFA3E0EEE
                dw 0xFA380EEB, 0xFA320EE9, 0xFA2C0EE7, 0xFA260EE4, 0xFA210EE2
                dw 0xFA1B0EE0, 0xFA150EDD, 0xFA0F0EDB, 0xFA090ED9, 0xFA030ED6
                dw 0xF9FE0ED4, 0xF9F80ED2, 0xF9F20ECF, 0xF9EC0ECD, 0xF9E60ECB
                dw 0xF9E10EC8, 0xF9DB0EC6, 0xF9D50EC3, 0xF9CF0EC1, 0xF9C90EBF
                dw 0xF9C40EBC, 0xF9BE0EBA, 0xF9B80EB7, 0xF9B20EB5, 0xF9AC0EB2
                dw 0xF9A70EB0, 0xF9A10EAD, 0xF99B0EAB, 0xF9950EA8, 0xF9900EA6
                dw 0xF98A0EA3, 0xF9840EA1, 0xF97E0E9E, 0xF9790E9B, 0xF9730E99
                dw 0xF96D0E96, 0xF9670E94, 0xF9620E91, 0xF95C0E8F, 0xF9560E8C
                dw 0xF9510E89, 0xF94B0E87, 0xF9450E84, 0xF93F0E81, 0xF93A0E7F
                dw 0xF9340E7C, 0xF92E0E79, 0xF9290E77, 0xF9230E74, 0xF91D0E71
                dw 0xF9180E6F, 0xF9120E6C, 0xF90C0E69, 0xF9070E66, 0xF9010E64
                dw 0xF8FB0E61, 0xF8F60E5E, 0xF8F00E5B, 0xF8EB0E59, 0xF8E50E56
                dw 0xF8DF0E53, 0xF8DA0E50, 0xF8D40E4D, 0xF8CE0E4B, 0xF8C90E48
                dw 0xF8C30E45, 0xF8BE0E42, 0xF8B80E3F, 0xF8B20E3C, 0xF8AD0E3A
                dw 0xF8A70E37, 0xF8A20E34, 0xF89C0E31, 0xF8960E2E, 0xF8910E2B
                dw 0xF88B0E28, 0xF8860E25, 0xF8800E22, 0xF87B0E1F, 0xF8750E1C
                dw 0xF8700E19, 0xF86A0E16, 0xF8650E13, 0xF85F0E10, 0xF85A0E0D
                dw 0xF8540E0A, 0xF84E0E07, 0xF8490E04, 0xF8430E01, 0xF83E0DFE
                dw 0xF8380DFB, 0xF8330DF8, 0xF82E0DF5, 0xF8280DF2, 0xF8230DEF
                dw 0xF81D0DEC, 0xF8180DE9, 0xF8120DE6, 0xF80D0DE3, 0xF8070DDF
                dw 0xF8020DDC, 0xF7FC0DD9, 0xF7F70DD6, 0xF7F20DD3, 0xF7EC0DD0
                dw 0xF7E70DCC, 0xF7E10DC9, 0xF7DC0DC6, 0xF7D60DC3, 0xF7D10DC0
                dw 0xF7CC0DBC, 0xF7C60DB9, 0xF7C10DB6, 0xF7BB0DB3, 0xF7B60DB0
                dw 0xF7B10DAC, 0xF7AB0DA9, 0xF7A60DA6, 0xF7A10DA2, 0xF79B0D9F
                dw 0xF7960D9C, 0xF7910D99, 0xF78B0D95, 0xF7860D92, 0xF7810D8F
                dw 0xF77B0D8B, 0xF7760D88, 0xF7710D85, 0xF76B0D81, 0xF7660D7E
                dw 0xF7610D7A, 0xF75B0D77, 0xF7560D74, 0xF7510D70, 0xF74C0D6D
                dw 0xF7460D69, 0xF7410D66, 0xF73C0D62, 0xF7370D5F, 0xF7310D5C
                dw 0xF72C0D58, 0xF7270D55, 0xF7220D51, 0xF71C0D4E, 0xF7170D4A
                dw 0xF7120D47, 0xF70D0D43, 0xF7080D40, 0xF7020D3C, 0xF6FD0D39
                dw 0xF6F80D35, 0xF6F30D32, 0xF6EE0D2E, 0xF6E80D2A, 0xF6E30D27
                dw 0xF6DE0D23, 0xF6D90D20, 0xF6D40D1C, 0xF6CF0D18, 0xF6C90D15
                dw 0xF6C40D11, 0xF6BF0D0E, 0xF6BA0D0A, 0xF6B50D06, 0xF6B00D03
                dw 0xF6AB0CFF, 0xF6A60CFB, 0xF6A10CF8, 0xF69B0CF4, 0xF6960CF0
                dw 0xF6910CED, 0xF68C0CE9, 0xF6870CE5, 0xF6820CE1, 0xF67D0CDE
                dw 0xF6780CDA, 0xF6730CD6, 0xF66E0CD2, 0xF6690CCF, 0xF6640CCB
                dw 0xF65F0CC7, 0xF65A0CC3, 0xF6550CC0, 0xF6500CBC, 0xF64B0CB8
                dw 0xF6460CB4, 0xF6410CB0, 0xF63C0CAC, 0xF6370CA9, 0xF6320CA5
                dw 0xF62D0CA1, 0xF6280C9D, 0xF6230C99, 0xF61E0C95, 0xF6190C91
                dw 0xF6140C8E, 0xF60F0C8A, 0xF60A0C86, 0xF6050C82, 0xF6010C7E
                dw 0xF5FC0C7A, 0xF5F70C76, 0xF5F20C72, 0xF5ED0C6E, 0xF5E80C6A
                dw 0xF5E30C66, 0xF5DE0C62, 0xF5DA0C5E, 0xF5D50C5A, 0xF5D00C56
                dw 0xF5CB0C52, 0xF5C60C4E, 0xF5C10C4A, 0xF5BC0C46, 0xF5B80C42
                dw 0xF5B30C3E, 0xF5AE0C3A, 0xF5A90C36, 0xF5A40C32, 0xF5A00C2E
                dw 0xF59B0C2A, 0xF5960C26, 0xF5910C22, 0xF58D0C1E, 0xF5880C19
                dw 0xF5830C15, 0xF57E0C11, 0xF57A0C0D, 0xF5750C09, 0xF5700C05
                dw 0xF56B0C01, 0xF5670BFC, 0xF5620BF8, 0xF55D0BF4, 0xF5590BF0
                dw 0xF5540BEC, 0xF54F0BE8, 0xF54B0BE3, 0xF5460BDF, 0xF5410BDB
                dw 0xF53D0BD7, 0xF5380BD2, 0xF5330BCE, 0xF52F0BCA, 0xF52A0BC6
                dw 0xF5250BC1, 0xF5210BBD, 0xF51C0BB9, 0xF5180BB5, 0xF5130BB0
                dw 0xF50E0BAC, 0xF50A0BA8, 0xF5050BA3, 0xF5010B9F, 0xF4FC0B9B
                dw 0xF4F80B97, 0xF4F30B92, 0xF4EF0B8E, 0xF4EA0B89, 0xF4E50B85
                dw 0xF4E10B81, 0xF4DC0B7C, 0xF4D80B78, 0xF4D30B74, 0xF4CF0B6F
                dw 0xF4CA0B6B, 0xF4C60B66, 0xF4C20B62, 0xF4BD0B5E, 0xF4B90B59
                dw 0xF4B40B55, 0xF4B00B50
                dw 0xF4AB0B4C, 0xF4A70B47, 0xF4A20B43, 0xF49E0B3E, 0xF49A0B3A
                dw 0xF4950B36, 0xF4910B31, 0xF48C0B2D, 0xF4880B28, 0xF4840B24
                dw 0xF47F0B1F, 0xF47B0B1B, 0xF4770B16, 0xF4720B11, 0xF46E0B0D
                dw 0xF4690B08, 0xF4650B04, 0xF4610AFF, 0xF45D0AFB, 0xF4580AF6
                dw 0xF4540AF2, 0xF4500AED, 0xF44B0AE8, 0xF4470AE4, 0xF4430ADF
                dw 0xF43F0ADB, 0xF43A0AD6, 0xF4360AD1, 0xF4320ACD, 0xF42E0AC8
                dw 0xF4290AC3, 0xF4250ABF, 0xF4210ABA, 0xF41D0AB5, 0xF4180AB1
                dw 0xF4140AAC, 0xF4100AA7, 0xF40C0AA3, 0xF4080A9E, 0xF4040A99
                dw 0xF3FF0A95, 0xF3FB0A90, 0xF3F70A8B, 0xF3F30A86, 0xF3EF0A82
                dw 0xF3EB0A7D, 0xF3E70A78, 0xF3E20A73, 0xF3DE0A6F, 0xF3DA0A6A
                dw 0xF3D60A65, 0xF3D20A60, 0xF3CE0A5C, 0xF3CA0A57, 0xF3C60A52
                dw 0xF3C20A4D, 0xF3BE0A48, 0xF3BA0A44, 0xF3B60A3F, 0xF3B20A3A
                dw 0xF3AE0A35, 0xF3AA0A30, 0xF3A60A2B, 0xF3A20A26, 0xF39E0A22
                dw 0xF39A0A1D, 0xF3960A18, 0xF3920A13, 0xF38E0A0E, 0xF38A0A09
                dw 0xF3860A04, 0xF38209FF, 0xF37E09FB, 0xF37A09F6, 0xF37609F1
                dw 0xF37209EC, 0xF36F09E7, 0xF36B09E2, 0xF36709DD, 0xF36309D8
                dw 0xF35F09D3, 0xF35B09CE, 0xF35709C9, 0xF35409C4, 0xF35009BF
                dw 0xF34C09BA, 0xF34809B5, 0xF34409B0, 0xF34009AB, 0xF33D09A6
                dw 0xF33909A1, 0xF335099C, 0xF3310997, 0xF32E0992, 0xF32A098D
                dw 0xF3260988, 0xF3220983, 0xF31F097E, 0xF31B0979, 0xF3170974
                dw 0xF313096F, 0xF310096A, 0xF30C0965, 0xF308095F, 0xF305095A
                dw 0xF3010955, 0xF2FD0950, 0xF2FA094B, 0xF2F60946, 0xF2F20941
                dw 0xF2EF093C, 0xF2EB0937, 0xF2E80931, 0xF2E4092C, 0xF2E00927
                dw 0xF2DD0922, 0xF2D9091D, 0xF2D60918, 0xF2D20912, 0xF2CE090D
                dw 0xF2CB0908, 0xF2C70903, 0xF2C408FE, 0xF2C008F8, 0xF2BD08F3
                dw 0xF2B908EE, 0xF2B608E9, 0xF2B208E4, 0xF2AF08DE, 0xF2AB08D9
                dw 0xF2A808D4, 0xF2A408CF, 0xF2A108C9, 0xF29E08C4, 0xF29A08BF
                dw 0xF29708BA, 0xF29308B4, 0xF29008AF, 0xF28C08AA, 0xF28908A5
                dw 0xF286089F, 0xF282089A, 0xF27F0895, 0xF27B088F, 0xF278088A
                dw 0xF2750885, 0xF271087F, 0xF26E087A, 0xF26B0875, 0xF267086F
                dw 0xF264086A, 0xF2610865, 0xF25E085F, 0xF25A085A, 0xF2570855
                dw 0xF254084F, 0xF250084A, 0xF24D0845, 0xF24A083F, 0xF247083A
                dw 0xF2440834, 0xF240082F, 0xF23D082A, 0xF23A0824, 0xF237081F
                dw 0xF2340819, 0xF2300814, 0xF22D080E, 0xF22A0809, 0xF2270804
                dw 0xF22407FE, 0xF22107F9, 0xF21D07F3, 0xF21A07EE, 0xF21707E8
                dw 0xF21407E3, 0xF21107DD, 0xF20E07D8, 0xF20B07D2, 0xF20807CD
                dw 0xF20507C8, 0xF20207C2, 0xF1FF07BD, 0xF1FC07B7, 0xF1F907B2
                dw 0xF1F607AC, 0xF1F307A6, 0xF1F007A1, 0xF1ED079B, 0xF1EA0796
                dw 0xF1E70790, 0xF1E4078B, 0xF1E10785, 0xF1DE0780, 0xF1DB077A
                dw 0xF1D80775, 0xF1D5076F, 0xF1D2076A, 0xF1CF0764, 0xF1CC075E
                dw 0xF1C90759, 0xF1C60753, 0xF1C4074E, 0xF1C10748, 0xF1BE0742
                dw 0xF1BB073D, 0xF1B80737, 0xF1B50732, 0xF1B3072C, 0xF1B00726
                dw 0xF1AD0721, 0xF1AA071B, 0xF1A70715, 0xF1A50710, 0xF1A2070A
                dw 0xF19F0705, 0xF19C06FF, 0xF19A06F9, 0xF19706F4, 0xF19406EE
                dw 0xF19106E8, 0xF18F06E3, 0xF18C06DD, 0xF18906D7, 0xF18706D2
                dw 0xF18406CC, 0xF18106C6, 0xF17F06C1, 0xF17C06BB, 0xF17906B5
                dw 0xF17706AF, 0xF17406AA, 0xF17106A4, 0xF16F069E, 0xF16C0699
                dw 0xF16A0693, 0xF167068D, 0xF1650687, 0xF1620682, 0xF15F067C
                dw 0xF15D0676, 0xF15A0670, 0xF158066B, 0xF1550665, 0xF153065F
                dw 0xF1500659, 0xF14E0654, 0xF14B064E, 0xF1490648, 0xF1460642
                dw 0xF144063C, 0xF1410637, 0xF13F0631, 0xF13D062B, 0xF13A0625
                dw 0xF138061F, 0xF135061A, 0xF1330614, 0xF131060E, 0xF12E0608
                dw 0xF12C0602, 0xF12A05FD, 0xF12705F7, 0xF12505F1, 0xF12305EB
                dw 0xF12005E5, 0xF11E05DF, 0xF11C05DA, 0xF11905D4, 0xF11705CE
                dw 0xF11505C8, 0xF11205C2, 0xF11005BC, 0xF10E05B6, 0xF10C05B1
                dw 0xF10905AB, 0xF10705A5, 0xF105059F, 0xF1030599, 0xF1010593
                dw 0xF0FE058D, 0xF0FC0587, 0xF0FA0581, 0xF0F8057C, 0xF0F60576
                dw 0xF0F40570, 0xF0F2056A, 0xF0EF0564, 0xF0ED055E, 0xF0EB0558
                dw 0xF0E90552, 0xF0E7054C, 0xF0E50546, 0xF0E30540, 0xF0E1053A
                dw 0xF0DF0534, 0xF0DD052F, 0xF0DB0529, 0xF0D90523, 0xF0D7051D
                dw 0xF0D50517, 0xF0D30511, 0xF0D1050B, 0xF0CF0505, 0xF0CD04FF
                dw 0xF0CB04F9, 0xF0C904F3, 0xF0C704ED, 0xF0C504E7, 0xF0C304E1
                dw 0xF0C104DB, 0xF0BF04D5, 0xF0BD04CF, 0xF0BB04C9, 0xF0BA04C3
                dw 0xF0B804BD, 0xF0B604B7, 0xF0B404B1, 0xF0B204AB, 0xF0B004A5
                dw 0xF0AF049F, 0xF0AD0499, 0xF0AB0493, 0xF0A9048D, 0xF0A70487
                dw 0xF0A60481, 0xF0A4047B, 0xF0A20475, 0xF0A0046F, 0xF09F0469
                dw 0xF09D0463, 0xF09B045D, 0xF0990457, 0xF0980451, 0xF096044B
                dw 0xF0940444, 0xF093043E, 0xF0910438, 0xF08F0432, 0xF08E042C
                dw 0xF08C0426, 0xF08A0420, 0xF089041A, 0xF0870414, 0xF086040E
                dw 0xF0840408, 0xF0830402, 0xF08103FC, 0xF07F03F6, 0xF07E03EF
                dw 0xF07C03E9, 0xF07B03E3, 0xF07903DD, 0xF07803D7, 0xF07603D1
                dw 0xF07503CB, 0xF07303C5, 0xF07203BF, 0xF07003B9, 0xF06F03B2
                dw 0xF06D03AC, 0xF06C03A6, 0xF06B03A0, 0xF069039A, 0xF0680394
                dw 0xF066038E, 0xF0650388, 0xF0640381, 0xF062037B, 0xF0610375
                dw 0xF05F036F, 0xF05E0369, 0xF05D0363, 0xF05B035D, 0xF05A0356
                dw 0xF0590350, 0xF058034A, 0xF0560344, 0xF055033E, 0xF0540338
                dw 0xF0520332, 0xF051032B, 0xF0500325, 0xF04F031F, 0xF04D0319
                dw 0xF04C0313, 0xF04B030D, 0xF04A0306, 0xF0490300, 0xF04802FA
                dw 0xF04602F4, 0xF04502EE, 0xF04402E8, 0xF04302E1, 0xF04202DB
                dw 0xF04102D5, 0xF04002CF, 0xF03E02C9, 0xF03D02C2, 0xF03C02BC
                dw 0xF03B02B6, 0xF03A02B0, 0xF03902AA, 0xF03802A3, 0xF037029D
                dw 0xF0360297, 0xF0350291, 0xF034028B, 0xF0330284, 0xF032027E
                dw 0xF0310278, 0xF0300272, 0xF02F026C, 0xF02E0265, 0xF02D025F
                dw 0xF02C0259, 0xF02B0253, 0xF02B024D, 0xF02A0246, 0xF0290240
                dw 0xF028023A, 0xF0270234, 0xF026022D, 0xF0250227, 0xF0240221
                dw 0xF024021B, 0xF0230215, 0xF022020E, 0xF0210208, 0xF0200202
                dw 0xF02001FC, 0xF01F01F5, 0xF01E01EF, 0xF01D01E9, 0xF01D01E3
                dw 0xF01C01DC, 0xF01B01D6, 0xF01A01D0, 0xF01A01CA, 0xF01901C3
                dw 0xF01801BD, 0xF01801B7, 0xF01701B1, 0xF01601AA, 0xF01601A4
                dw 0xF015019E, 0xF0140198, 0xF0140191, 0xF013018B, 0xF0130185
                dw 0xF012017F, 0xF0110178, 0xF0110172, 0xF010016C, 0xF0100166
                dw 0xF00F015F, 0xF00F0159, 0xF00E0153, 0xF00E014D, 0xF00D0146
                dw 0xF00D0140, 0xF00C013A, 0xF00C0134, 0xF00B012D, 0xF00B0127
                dw 0xF00A0121, 0xF00A011B, 0xF0090114, 0xF009010E, 0xF0080108
                dw 0xF0080101, 0xF00800FB, 0xF00700F5, 0xF00700EF, 0xF00700E8
                dw 0xF00600E2, 0xF00600DC, 0xF00600D6, 0xF00500CF, 0xF00500C9
                dw 0xF00500C3, 0xF00400BC, 0xF00400B6, 0xF00400B0, 0xF00400AA
                dw 0xF00300A3, 0xF003009D, 0xF0030097, 0xF0030090, 0xF002008A
                dw 0xF0020084, 0xF002007E, 0xF0020077, 0xF0020071, 0xF001006B
                dw 0xF0010065, 0xF001005E, 0xF0010058, 0xF0010052, 0xF001004B
                dw 0xF0010045, 0xF000003F, 0xF0000039, 0xF0000032, 0xF000002C
                dw 0xF0000026, 0xF000001F, 0xF0000019, 0xF0000013, 0xF000000D
                dw 0xF0000006, 0xF0000000
                dw 0xF000FFFA, 0xF000FFF3, 0xF000FFED, 0xF000FFE7, 0xF000FFE1
                dw 0xF000FFDA, 0xF000FFD4, 0xF000FFCE, 0xF000FFC7, 0xF000FFC1
                dw 0xF001FFBB, 0xF001FFB5, 0xF001FFAE, 0xF001FFA8, 0xF001FFA2
                dw 0xF001FF9B, 0xF001FF95, 0xF002FF8F, 0xF002FF89, 0xF002FF82
                dw 0xF002FF7C, 0xF002FF76, 0xF003FF70, 0xF003FF69, 0xF003FF63
                dw 0xF003FF5D, 0xF004FF56, 0xF004FF50, 0xF004FF4A, 0xF004FF44
                dw 0xF005FF3D, 0xF005FF37, 0xF005FF31, 0xF006FF2A, 0xF006FF24
                dw 0xF006FF1E, 0xF007FF18, 0xF007FF11, 0xF007FF0B, 0xF008FF05
                dw 0xF008FEFF, 0xF008FEF8, 0xF009FEF2, 0xF009FEEC, 0xF00AFEE5
                dw 0xF00AFEDF, 0xF00BFED9, 0xF00BFED3, 0xF00CFECC, 0xF00CFEC6
                dw 0xF00DFEC0, 0xF00DFEBA, 0xF00EFEB3, 0xF00EFEAD, 0xF00FFEA7
                dw 0xF00FFEA1, 0xF010FE9A, 0xF010FE94, 0xF011FE8E, 0xF011FE88
                dw 0xF012FE81, 0xF013FE7B, 0xF013FE75, 0xF014FE6F, 0xF014FE68
                dw 0xF015FE62, 0xF016FE5C, 0xF016FE56, 0xF017FE4F, 0xF018FE49
                dw 0xF018FE43, 0xF019FE3D, 0xF01AFE36, 0xF01AFE30, 0xF01BFE2A
                dw 0xF01CFE24, 0xF01DFE1D, 0xF01DFE17, 0xF01EFE11, 0xF01FFE0B
                dw 0xF020FE04, 0xF020FDFE, 0xF021FDF8, 0xF022FDF2, 0xF023FDEB
                dw 0xF024FDE5, 0xF024FDDF, 0xF025FDD9, 0xF026FDD3, 0xF027FDCC
                dw 0xF028FDC6, 0xF029FDC0, 0xF02AFDBA, 0xF02BFDB3, 0xF02BFDAD
                dw 0xF02CFDA7, 0xF02DFDA1, 0xF02EFD9B, 0xF02FFD94, 0xF030FD8E
                dw 0xF031FD88, 0xF032FD82, 0xF033FD7C, 0xF034FD75, 0xF035FD6F
                dw 0xF036FD69, 0xF037FD63, 0xF038FD5D, 0xF039FD56, 0xF03AFD50
                dw 0xF03BFD4A, 0xF03CFD44, 0xF03DFD3E, 0xF03EFD37, 0xF040FD31
                dw 0xF041FD2B, 0xF042FD25, 0xF043FD1F, 0xF044FD18, 0xF045FD12
                dw 0xF046FD0C, 0xF048FD06, 0xF049FD00, 0xF04AFCFA, 0xF04BFCF3
                dw 0xF04CFCED, 0xF04DFCE7, 0xF04FFCE1, 0xF050FCDB, 0xF051FCD5
                dw 0xF052FCCE, 0xF054FCC8, 0xF055FCC2, 0xF056FCBC, 0xF058FCB6
                dw 0xF059FCB0, 0xF05AFCAA, 0xF05BFCA3, 0xF05DFC9D, 0xF05EFC97
                dw 0xF05FFC91, 0xF061FC8B, 0xF062FC85, 0xF064FC7F, 0xF065FC78
                dw 0xF066FC72, 0xF068FC6C, 0xF069FC66, 0xF06BFC60, 0xF06CFC5A
                dw 0xF06DFC54, 0xF06FFC4E, 0xF070FC47, 0xF072FC41, 0xF073FC3B
                dw 0xF075FC35, 0xF076FC2F, 0xF078FC29, 0xF079FC23, 0xF07BFC1D
                dw 0xF07CFC17, 0xF07EFC11, 0xF07FFC0A, 0xF081FC04, 0xF083FBFE
                dw 0xF084FBF8, 0xF086FBF2, 0xF087FBEC, 0xF089FBE6, 0xF08AFBE0
                dw 0xF08CFBDA, 0xF08EFBD4, 0xF08FFBCE, 0xF091FBC8, 0xF093FBC2
                dw 0xF094FBBC, 0xF096FBB5, 0xF098FBAF, 0xF099FBA9, 0xF09BFBA3
                dw 0xF09DFB9D, 0xF09FFB97, 0xF0A0FB91, 0xF0A2FB8B, 0xF0A4FB85
                dw 0xF0A6FB7F, 0xF0A7FB79, 0xF0A9FB73, 0xF0ABFB6D, 0xF0ADFB67
                dw 0xF0AFFB61, 0xF0B0FB5B, 0xF0B2FB55, 0xF0B4FB4F, 0xF0B6FB49
                dw 0xF0B8FB43, 0xF0BAFB3D, 0xF0BBFB37, 0xF0BDFB31, 0xF0BFFB2B
                dw 0xF0C1FB25, 0xF0C3FB1F, 0xF0C5FB19, 0xF0C7FB13, 0xF0C9FB0D
                dw 0xF0CBFB07, 0xF0CDFB01, 0xF0CFFAFB, 0xF0D1FAF5, 0xF0D3FAEF
                dw 0xF0D5FAE9, 0xF0D7FAE3, 0xF0D9FADD, 0xF0DBFAD7, 0xF0DDFAD1
                dw 0xF0DFFACC, 0xF0E1FAC6, 0xF0E3FAC0, 0xF0E5FABA, 0xF0E7FAB4
                dw 0xF0E9FAAE, 0xF0EBFAA8, 0xF0EDFAA2, 0xF0EFFA9C, 0xF0F2FA96
                dw 0xF0F4FA90, 0xF0F6FA8A, 0xF0F8FA84, 0xF0FAFA7F, 0xF0FCFA79
                dw 0xF0FEFA73, 0xF101FA6D, 0xF103FA67, 0xF105FA61, 0xF107FA5B
                dw 0xF109FA55, 0xF10CFA4F, 0xF10EFA4A, 0xF110FA44, 0xF112FA3E
                dw 0xF115FA38, 0xF117FA32, 0xF119FA2C, 0xF11CFA26, 0xF11EFA21
                dw 0xF120FA1B, 0xF123FA15, 0xF125FA0F, 0xF127FA09, 0xF12AFA03
                dw 0xF12CF9FE, 0xF12EF9F8, 0xF131F9F2, 0xF133F9EC, 0xF135F9E6
                dw 0xF138F9E1, 0xF13AF9DB, 0xF13DF9D5, 0xF13FF9CF, 0xF141F9C9
                dw 0xF144F9C4, 0xF146F9BE, 0xF149F9B8, 0xF14BF9B2, 0xF14EF9AC
                dw 0xF150F9A7, 0xF153F9A1, 0xF155F99B, 0xF158F995, 0xF15AF990
                dw 0xF15DF98A, 0xF15FF984, 0xF162F97E, 0xF165F979, 0xF167F973
                dw 0xF16AF96D, 0xF16CF967, 0xF16FF962, 0xF171F95C, 0xF174F956
                dw 0xF177F951, 0xF179F94B, 0xF17CF945, 0xF17FF93F, 0xF181F93A
                dw 0xF184F934, 0xF187F92E, 0xF189F929, 0xF18CF923, 0xF18FF91D
                dw 0xF191F918, 0xF194F912, 0xF197F90C, 0xF19AF907, 0xF19CF901
                dw 0xF19FF8FB, 0xF1A2F8F6, 0xF1A5F8F0, 0xF1A7F8EB, 0xF1AAF8E5
                dw 0xF1ADF8DF, 0xF1B0F8DA, 0xF1B3F8D4, 0xF1B5F8CE, 0xF1B8F8C9
                dw 0xF1BBF8C3, 0xF1BEF8BE, 0xF1C1F8B8, 0xF1C4F8B2, 0xF1C6F8AD
                dw 0xF1C9F8A7, 0xF1CCF8A2, 0xF1CFF89C, 0xF1D2F896, 0xF1D5F891
                dw 0xF1D8F88B, 0xF1DBF886, 0xF1DEF880, 0xF1E1F87B, 0xF1E4F875
                dw 0xF1E7F870, 0xF1EAF86A, 0xF1EDF865, 0xF1F0F85F, 0xF1F3F85A
                dw 0xF1F6F854, 0xF1F9F84E, 0xF1FCF849, 0xF1FFF843, 0xF202F83E
                dw 0xF205F838, 0xF208F833, 0xF20BF82E, 0xF20EF828, 0xF211F823
                dw 0xF214F81D, 0xF217F818, 0xF21AF812, 0xF21DF80D, 0xF221F807
                dw 0xF224F802, 0xF227F7FC, 0xF22AF7F7, 0xF22DF7F2, 0xF230F7EC
                dw 0xF234F7E7, 0xF237F7E1, 0xF23AF7DC, 0xF23DF7D6, 0xF240F7D1
                dw 0xF244F7CC, 0xF247F7C6, 0xF24AF7C1, 0xF24DF7BB, 0xF250F7B6
                dw 0xF254F7B1, 0xF257F7AB, 0xF25AF7A6, 0xF25EF7A1, 0xF261F79B
                dw 0xF264F796, 0xF267F791, 0xF26BF78B, 0xF26EF786, 0xF271F781
                dw 0xF275F77B, 0xF278F776, 0xF27BF771, 0xF27FF76B, 0xF282F766
                dw 0xF286F761, 0xF289F75B, 0xF28CF756, 0xF290F751, 0xF293F74C
                dw 0xF297F746, 0xF29AF741, 0xF29EF73C, 0xF2A1F737, 0xF2A4F731
                dw 0xF2A8F72C, 0xF2ABF727, 0xF2AFF722, 0xF2B2F71C, 0xF2B6F717
                dw 0xF2B9F712, 0xF2BDF70D, 0xF2C0F708, 0xF2C4F702, 0xF2C7F6FD
                dw 0xF2CBF6F8, 0xF2CEF6F3, 0xF2D2F6EE, 0xF2D6F6E8, 0xF2D9F6E3
                dw 0xF2DDF6DE, 0xF2E0F6D9, 0xF2E4F6D4, 0xF2E8F6CF, 0xF2EBF6C9
                dw 0xF2EFF6C4, 0xF2F2F6BF, 0xF2F6F6BA, 0xF2FAF6B5, 0xF2FDF6B0
                dw 0xF301F6AB, 0xF305F6A6, 0xF308F6A1, 0xF30CF69B, 0xF310F696
                dw 0xF313F691, 0xF317F68C, 0xF31BF687, 0xF31FF682, 0xF322F67D
                dw 0xF326F678, 0xF32AF673, 0xF32EF66E, 0xF331F669, 0xF335F664
                dw 0xF339F65F, 0xF33DF65A, 0xF340F655, 0xF344F650, 0xF348F64B
                dw 0xF34CF646, 0xF350F641, 0xF354F63C, 0xF357F637, 0xF35BF632
                dw 0xF35FF62D, 0xF363F628, 0xF367F623, 0xF36BF61E, 0xF36FF619
                dw 0xF372F614, 0xF376F60F, 0xF37AF60A, 0xF37EF605, 0xF382F601
                dw 0xF386F5FC, 0xF38AF5F7, 0xF38EF5F2, 0xF392F5ED, 0xF396F5E8
                dw 0xF39AF5E3, 0xF39EF5DE, 0xF3A2F5DA, 0xF3A6F5D5, 0xF3AAF5D0
                dw 0xF3AEF5CB, 0xF3B2F5C6, 0xF3B6F5C1, 0xF3BAF5BC, 0xF3BEF5B8
                dw 0xF3C2F5B3, 0xF3C6F5AE, 0xF3CAF5A9, 0xF3CEF5A4, 0xF3D2F5A0
                dw 0xF3D6F59B, 0xF3DAF596, 0xF3DEF591, 0xF3E2F58D, 0xF3E7F588
                dw 0xF3EBF583, 0xF3EFF57E, 0xF3F3F57A, 0xF3F7F575, 0xF3FBF570
                dw 0xF3FFF56B, 0xF404F567, 0xF408F562, 0xF40CF55D, 0xF410F559
                dw 0xF414F554, 0xF418F54F, 0xF41DF54B, 0xF421F546, 0xF425F541
                dw 0xF429F53D, 0xF42EF538, 0xF432F533, 0xF436F52F, 0xF43AF52A
                dw 0xF43FF525, 0xF443F521, 0xF447F51C, 0xF44BF518, 0xF450F513
                dw 0xF454F50E, 0xF458F50A, 0xF45DF505, 0xF461F501, 0xF465F4FC
                dw 0xF469F4F8, 0xF46EF4F3, 0xF472F4EF, 0xF477F4EA, 0xF47BF4E5
                dw 0xF47FF4E1, 0xF484F4DC, 0xF488F4D8, 0xF48CF4D3, 0xF491F4CF
                dw 0xF495F4CA, 0xF49AF4C6, 0xF49EF4C2, 0xF4A2F4BD, 0xF4A7F4B9
                dw 0xF4ABF4B4, 0xF4B0F4B0
                dw 0xF4B4F4AB, 0xF4B9F4A7, 0xF4BDF4A2, 0xF4C2F49E, 0xF4C6F49A
                dw 0xF4CAF495, 0xF4CFF491, 0xF4D3F48C, 0xF4D8F488, 0xF4DCF484
                dw 0xF4E1F47F, 0xF4E5F47B, 0xF4EAF477, 0xF4EFF472, 0xF4F3F46E
                dw 0xF4F8F469, 0xF4FCF465, 0xF501F461, 0xF505F45D, 0xF50AF458
                dw 0xF50EF454, 0xF513F450, 0xF518F44B, 0xF51CF447, 0xF521F443
                dw 0xF525F43F, 0xF52AF43A, 0xF52FF436, 0xF533F432, 0xF538F42E
                dw 0xF53DF429, 0xF541F425, 0xF546F421, 0xF54BF41D, 0xF54FF418
                dw 0xF554F414, 0xF559F410, 0xF55DF40C, 0xF562F408, 0xF567F404
                dw 0xF56BF3FF, 0xF570F3FB, 0xF575F3F7, 0xF57AF3F3, 0xF57EF3EF
                dw 0xF583F3EB, 0xF588F3E7, 0xF58DF3E2, 0xF591F3DE, 0xF596F3DA
                dw 0xF59BF3D6, 0xF5A0F3D2, 0xF5A4F3CE, 0xF5A9F3CA, 0xF5AEF3C6
                dw 0xF5B3F3C2, 0xF5B8F3BE, 0xF5BCF3BA, 0xF5C1F3B6, 0xF5C6F3B2
                dw 0xF5CBF3AE, 0xF5D0F3AA, 0xF5D5F3A6, 0xF5DAF3A2, 0xF5DEF39E
                dw 0xF5E3F39A, 0xF5E8F396, 0xF5EDF392, 0xF5F2F38E, 0xF5F7F38A
                dw 0xF5FCF386, 0xF601F382, 0xF605F37E, 0xF60AF37A, 0xF60FF376
                dw 0xF614F372, 0xF619F36F, 0xF61EF36B, 0xF623F367, 0xF628F363
                dw 0xF62DF35F, 0xF632F35B, 0xF637F357, 0xF63CF354, 0xF641F350
                dw 0xF646F34C, 0xF64BF348, 0xF650F344, 0xF655F340, 0xF65AF33D
                dw 0xF65FF339, 0xF664F335, 0xF669F331, 0xF66EF32E, 0xF673F32A
                dw 0xF678F326, 0xF67DF322, 0xF682F31F, 0xF687F31B, 0xF68CF317
                dw 0xF691F313, 0xF696F310, 0xF69BF30C, 0xF6A1F308, 0xF6A6F305
                dw 0xF6ABF301, 0xF6B0F2FD, 0xF6B5F2FA, 0xF6BAF2F6, 0xF6BFF2F2
                dw 0xF6C4F2EF, 0xF6C9F2EB, 0xF6CFF2E8, 0xF6D4F2E4, 0xF6D9F2E0
                dw 0xF6DEF2DD, 0xF6E3F2D9, 0xF6E8F2D6, 0xF6EEF2D2, 0xF6F3F2CE
                dw 0xF6F8F2CB, 0xF6FDF2C7, 0xF702F2C4, 0xF708F2C0, 0xF70DF2BD
                dw 0xF712F2B9, 0xF717F2B6, 0xF71CF2B2, 0xF722F2AF, 0xF727F2AB
                dw 0xF72CF2A8, 0xF731F2A4, 0xF737F2A1, 0xF73CF29E, 0xF741F29A
                dw 0xF746F297, 0xF74CF293, 0xF751F290, 0xF756F28C, 0xF75BF289
                dw 0xF761F286, 0xF766F282, 0xF76BF27F, 0xF771F27B, 0xF776F278
                dw 0xF77BF275, 0xF781F271, 0xF786F26E, 0xF78BF26B, 0xF791F267
                dw 0xF796F264, 0xF79BF261, 0xF7A1F25E, 0xF7A6F25A, 0xF7ABF257
                dw 0xF7B1F254, 0xF7B6F250, 0xF7BBF24D, 0xF7C1F24A, 0xF7C6F247
                dw 0xF7CCF244, 0xF7D1F240, 0xF7D6F23D, 0xF7DCF23A, 0xF7E1F237
                dw 0xF7E7F234, 0xF7ECF230, 0xF7F2F22D, 0xF7F7F22A, 0xF7FCF227
                dw 0xF802F224, 0xF807F221, 0xF80DF21D, 0xF812F21A, 0xF818F217
                dw 0xF81DF214, 0xF823F211, 0xF828F20E, 0xF82EF20B, 0xF833F208
                dw 0xF838F205, 0xF83EF202, 0xF843F1FF, 0xF849F1FC, 0xF84EF1F9
                dw 0xF854F1F6, 0xF85AF1F3, 0xF85FF1F0, 0xF865F1ED, 0xF86AF1EA
                dw 0xF870F1E7, 0xF875F1E4, 0xF87BF1E1, 0xF880F1DE, 0xF886F1DB
                dw 0xF88BF1D8, 0xF891F1D5, 0xF896F1D2, 0xF89CF1CF, 0xF8A2F1CC
                dw 0xF8A7F1C9, 0xF8ADF1C6, 0xF8B2F1C4, 0xF8B8F1C1, 0xF8BEF1BE
                dw 0xF8C3F1BB, 0xF8C9F1B8, 0xF8CEF1B5, 0xF8D4F1B3, 0xF8DAF1B0
                dw 0xF8DFF1AD, 0xF8E5F1AA, 0xF8EBF1A7, 0xF8F0F1A5, 0xF8F6F1A2
                dw 0xF8FBF19F, 0xF901F19C, 0xF907F19A, 0xF90CF197, 0xF912F194
                dw 0xF918F191, 0xF91DF18F, 0xF923F18C, 0xF929F189, 0xF92EF187
                dw 0xF934F184, 0xF93AF181, 0xF93FF17F, 0xF945F17C, 0xF94BF179
                dw 0xF951F177, 0xF956F174, 0xF95CF171, 0xF962F16F, 0xF967F16C
                dw 0xF96DF16A, 0xF973F167, 0xF979F165, 0xF97EF162, 0xF984F15F
                dw 0xF98AF15D, 0xF990F15A, 0xF995F158, 0xF99BF155, 0xF9A1F153
                dw 0xF9A7F150, 0xF9ACF14E, 0xF9B2F14B, 0xF9B8F149, 0xF9BEF146
                dw 0xF9C4F144, 0xF9C9F141, 0xF9CFF13F, 0xF9D5F13D, 0xF9DBF13A
                dw 0xF9E1F138, 0xF9E6F135, 0xF9ECF133, 0xF9F2F131, 0xF9F8F12E
                dw 0xF9FEF12C, 0xFA03F12A, 0xFA09F127, 0xFA0FF125, 0xFA15F123
                dw 0xFA1BF120, 0xFA21F11E, 0xFA26F11C, 0xFA2CF119, 0xFA32F117
                dw 0xFA38F115, 0xFA3EF112, 0xFA44F110, 0xFA4AF10E, 0xFA4FF10C
                dw 0xFA55F109, 0xFA5BF107, 0xFA61F105, 0xFA67F103, 0xFA6DF101
                dw 0xFA73F0FE, 0xFA79F0FC, 0xFA7FF0FA, 0xFA84F0F8, 0xFA8AF0F6
                dw 0xFA90F0F4, 0xFA96F0F2, 0xFA9CF0EF, 0xFAA2F0ED, 0xFAA8F0EB
                dw 0xFAAEF0E9, 0xFAB4F0E7, 0xFABAF0E5, 0xFAC0F0E3, 0xFAC6F0E1
                dw 0xFACCF0DF, 0xFAD1F0DD, 0xFAD7F0DB, 0xFADDF0D9, 0xFAE3F0D7
                dw 0xFAE9F0D5, 0xFAEFF0D3, 0xFAF5F0D1, 0xFAFBF0CF, 0xFB01F0CD
                dw 0xFB07F0CB, 0xFB0DF0C9, 0xFB13F0C7, 0xFB19F0C5, 0xFB1FF0C3
                dw 0xFB25F0C1, 0xFB2BF0BF, 0xFB31F0BD, 0xFB37F0BB, 0xFB3DF0BA
                dw 0xFB43F0B8, 0xFB49F0B6, 0xFB4FF0B4, 0xFB55F0B2, 0xFB5BF0B0
                dw 0xFB61F0AF, 0xFB67F0AD, 0xFB6DF0AB, 0xFB73F0A9, 0xFB79F0A7
                dw 0xFB7FF0A6, 0xFB85F0A4, 0xFB8BF0A2, 0xFB91F0A0, 0xFB97F09F
                dw 0xFB9DF09D, 0xFBA3F09B, 0xFBA9F099, 0xFBAFF098, 0xFBB5F096
                dw 0xFBBCF094, 0xFBC2F093, 0xFBC8F091, 0xFBCEF08F, 0xFBD4F08E
                dw 0xFBDAF08C, 0xFBE0F08A, 0xFBE6F089, 0xFBECF087, 0xFBF2F086
                dw 0xFBF8F084, 0xFBFEF083, 0xFC04F081, 0xFC0AF07F, 0xFC11F07E
                dw 0xFC17F07C, 0xFC1DF07B, 0xFC23F079, 0xFC29F078, 0xFC2FF076
                dw 0xFC35F075, 0xFC3BF073, 0xFC41F072, 0xFC47F070, 0xFC4EF06F
                dw 0xFC54F06D, 0xFC5AF06C, 0xFC60F06B, 0xFC66F069, 0xFC6CF068
                dw 0xFC72F066, 0xFC78F065, 0xFC7FF064, 0xFC85F062, 0xFC8BF061
                dw 0xFC91F05F, 0xFC97F05E, 0xFC9DF05D, 0xFCA3F05B, 0xFCAAF05A
                dw 0xFCB0F059, 0xFCB6F058, 0xFCBCF056, 0xFCC2F055, 0xFCC8F054
                dw 0xFCCEF052, 0xFCD5F051, 0xFCDBF050, 0xFCE1F04F, 0xFCE7F04D
                dw 0xFCEDF04C, 0xFCF3F04B, 0xFCFAF04A, 0xFD00F049, 0xFD06F048
                dw 0xFD0CF046, 0xFD12F045, 0xFD18F044, 0xFD1FF043, 0xFD25F042
                dw 0xFD2BF041, 0xFD31F040, 0xFD37F03E, 0xFD3EF03D, 0xFD44F03C
                dw 0xFD4AF03B, 0xFD50F03A, 0xFD56F039, 0xFD5DF038, 0xFD63F037
                dw 0xFD69F036, 0xFD6FF035, 0xFD75F034, 0xFD7CF033, 0xFD82F032
                dw 0xFD88F031, 0xFD8EF030, 0xFD94F02F, 0xFD9BF02E, 0xFDA1F02D
                dw 0xFDA7F02C, 0xFDADF02B, 0xFDB3F02B, 0xFDBAF02A, 0xFDC0F029
                dw 0xFDC6F028, 0xFDCCF027, 0xFDD3F026, 0xFDD9F025, 0xFDDFF024
                dw 0xFDE5F024, 0xFDEBF023, 0xFDF2F022, 0xFDF8F021, 0xFDFEF020
                dw 0xFE04F020, 0xFE0BF01F, 0xFE11F01E, 0xFE17F01D, 0xFE1DF01D
                dw 0xFE24F01C, 0xFE2AF01B, 0xFE30F01A, 0xFE36F01A, 0xFE3DF019
                dw 0xFE43F018, 0xFE49F018, 0xFE4FF017, 0xFE56F016, 0xFE5CF016
                dw 0xFE62F015, 0xFE68F014, 0xFE6FF014, 0xFE75F013, 0xFE7BF013
                dw 0xFE81F012, 0xFE88F011, 0xFE8EF011, 0xFE94F010, 0xFE9AF010
                dw 0xFEA1F00F, 0xFEA7F00F, 0xFEADF00E, 0xFEB3F00E, 0xFEBAF00D
                dw 0xFEC0F00D, 0xFEC6F00C, 0xFECCF00C, 0xFED3F00B, 0xFED9F00B
                dw 0xFEDFF00A, 0xFEE5F00A, 0xFEECF009, 0xFEF2F009, 0xFEF8F008
                dw 0xFEFFF008, 0xFF05F008, 0xFF0BF007, 0xFF11F007, 0xFF18F007
                dw 0xFF1EF006, 0xFF24F006, 0xFF2AF006, 0xFF31F005, 0xFF37F005
                dw 0xFF3DF005, 0xFF44F004, 0xFF4AF004, 0xFF50F004, 0xFF56F004
                dw 0xFF5DF003, 0xFF63F003, 0xFF69F003, 0xFF70F003, 0xFF76F002
                dw 0xFF7CF002, 0xFF82F002, 0xFF89F002, 0xFF8FF002, 0xFF95F001
                dw 0xFF9BF001, 0xFFA2F001, 0xFFA8F001, 0xFFAEF001, 0xFFB5F001
                dw 0xFFBBF001, 0xFFC1F000, 0xFFC7F000, 0xFFCEF000, 0xFFD4F000
                dw 0xFFDAF000, 0xFFE1F000, 0xFFE7F000, 0xFFEDF000, 0xFFF3F000
                dw 0xFFFAF000, 0xF000
                dw 0x6F000, 0xDF000, 0x13F000, 0x19F000, 0x1FF000, 0x26F000
                dw 0x2CF000, 0x32F000, 0x39F000, 0x3FF000, 0x45F001
                dw 0x4BF001, 0x52F001, 0x58F001, 0x5EF001, 0x65F001
                dw 0x6BF001, 0x71F002, 0x77F002, 0x7EF002, 0x84F002
                dw 0x8AF002, 0x90F003, 0x97F003, 0x9DF003, 0xA3F003
                dw 0xAAF004, 0xB0F004, 0xB6F004, 0xBCF004, 0xC3F005
                dw 0xC9F005, 0xCFF005, 0xD6F006, 0xDCF006, 0xE2F006
                dw 0xE8F007, 0xEFF007, 0xF5F007, 0xFBF008, 0x101F008
                dw 0x108F008, 0x10EF009, 0x114F009, 0x11BF00A, 0x121F00A
                dw 0x127F00B, 0x12DF00B, 0x134F00C, 0x13AF00C, 0x140F00D
                dw 0x146F00D, 0x14DF00E, 0x153F00E, 0x159F00F, 0x15FF00F
                dw 0x166F010, 0x16CF010, 0x172F011, 0x178F011, 0x17FF012
                dw 0x185F013, 0x18BF013, 0x191F014, 0x198F014, 0x19EF015
                dw 0x1A4F016, 0x1AAF016, 0x1B1F017, 0x1B7F018, 0x1BDF018
                dw 0x1C3F019, 0x1CAF01A, 0x1D0F01A, 0x1D6F01B, 0x1DCF01C
                dw 0x1E3F01D, 0x1E9F01D, 0x1EFF01E, 0x1F5F01F, 0x1FCF020
                dw 0x202F020, 0x208F021, 0x20EF022, 0x215F023, 0x21BF024
                dw 0x221F024, 0x227F025, 0x22DF026, 0x234F027, 0x23AF028
                dw 0x240F029, 0x246F02A, 0x24DF02B, 0x253F02B, 0x259F02C
                dw 0x25FF02D, 0x265F02E, 0x26CF02F, 0x272F030, 0x278F031
                dw 0x27EF032, 0x284F033, 0x28BF034, 0x291F035, 0x297F036
                dw 0x29DF037, 0x2A3F038, 0x2AAF039, 0x2B0F03A, 0x2B6F03B
                dw 0x2BCF03C, 0x2C2F03D, 0x2C9F03E, 0x2CFF040, 0x2D5F041
                dw 0x2DBF042, 0x2E1F043, 0x2E8F044, 0x2EEF045, 0x2F4F046
                dw 0x2FAF048, 0x300F049, 0x306F04A, 0x30DF04B, 0x313F04C
                dw 0x319F04D, 0x31FF04F, 0x325F050, 0x32BF051, 0x332F052
                dw 0x338F054, 0x33EF055, 0x344F056, 0x34AF058, 0x350F059
                dw 0x356F05A, 0x35DF05B, 0x363F05D, 0x369F05E, 0x36FF05F
                dw 0x375F061, 0x37BF062, 0x381F064, 0x388F065, 0x38EF066
                dw 0x394F068, 0x39AF069, 0x3A0F06B, 0x3A6F06C, 0x3ACF06D
                dw 0x3B2F06F, 0x3B9F070, 0x3BFF072, 0x3C5F073, 0x3CBF075
                dw 0x3D1F076, 0x3D7F078, 0x3DDF079, 0x3E3F07B, 0x3E9F07C
                dw 0x3EFF07E, 0x3F6F07F, 0x3FCF081, 0x402F083, 0x408F084
                dw 0x40EF086, 0x414F087, 0x41AF089, 0x420F08A, 0x426F08C
                dw 0x42CF08E, 0x432F08F, 0x438F091, 0x43EF093, 0x444F094
                dw 0x44BF096, 0x451F098, 0x457F099, 0x45DF09B, 0x463F09D
                dw 0x469F09F, 0x46FF0A0, 0x475F0A2, 0x47BF0A4, 0x481F0A6
                dw 0x487F0A7, 0x48DF0A9, 0x493F0AB, 0x499F0AD, 0x49FF0AF
                dw 0x4A5F0B0, 0x4ABF0B2, 0x4B1F0B4, 0x4B7F0B6, 0x4BDF0B8
                dw 0x4C3F0BA, 0x4C9F0BB, 0x4CFF0BD, 0x4D5F0BF, 0x4DBF0C1
                dw 0x4E1F0C3, 0x4E7F0C5, 0x4EDF0C7, 0x4F3F0C9, 0x4F9F0CB
                dw 0x4FFF0CD, 0x505F0CF, 0x50BF0D1, 0x511F0D3, 0x517F0D5
                dw 0x51DF0D7, 0x523F0D9, 0x529F0DB, 0x52FF0DD, 0x534F0DF
                dw 0x53AF0E1, 0x540F0E3, 0x546F0E5, 0x54CF0E7, 0x552F0E9
                dw 0x558F0EB, 0x55EF0ED, 0x564F0EF, 0x56AF0F2, 0x570F0F4
                dw 0x576F0F6, 0x57CF0F8, 0x581F0FA, 0x587F0FC, 0x58DF0FE
                dw 0x593F101, 0x599F103, 0x59FF105, 0x5A5F107, 0x5ABF109
                dw 0x5B1F10C, 0x5B6F10E, 0x5BCF110, 0x5C2F112, 0x5C8F115
                dw 0x5CEF117, 0x5D4F119, 0x5DAF11C, 0x5DFF11E, 0x5E5F120
                dw 0x5EBF123, 0x5F1F125, 0x5F7F127, 0x5FDF12A, 0x602F12C
                dw 0x608F12E, 0x60EF131, 0x614F133, 0x61AF135, 0x61FF138
                dw 0x625F13A, 0x62BF13D, 0x631F13F, 0x637F141, 0x63CF144
                dw 0x642F146, 0x648F149, 0x64EF14B, 0x654F14E, 0x659F150
                dw 0x65FF153, 0x665F155, 0x66BF158, 0x670F15A, 0x676F15D
                dw 0x67CF15F, 0x682F162, 0x687F165, 0x68DF167, 0x693F16A
                dw 0x699F16C, 0x69EF16F, 0x6A4F171, 0x6AAF174, 0x6AFF177
                dw 0x6B5F179, 0x6BBF17C, 0x6C1F17F, 0x6C6F181, 0x6CCF184
                dw 0x6D2F187, 0x6D7F189, 0x6DDF18C, 0x6E3F18F, 0x6E8F191
                dw 0x6EEF194, 0x6F4F197, 0x6F9F19A, 0x6FFF19C, 0x705F19F
                dw 0x70AF1A2, 0x710F1A5, 0x715F1A7, 0x71BF1AA, 0x721F1AD
                dw 0x726F1B0, 0x72CF1B3, 0x732F1B5, 0x737F1B8, 0x73DF1BB
                dw 0x742F1BE, 0x748F1C1, 0x74EF1C4, 0x753F1C6, 0x759F1C9
                dw 0x75EF1CC, 0x764F1CF, 0x76AF1D2, 0x76FF1D5, 0x775F1D8
                dw 0x77AF1DB, 0x780F1DE, 0x785F1E1, 0x78BF1E4, 0x790F1E7
                dw 0x796F1EA, 0x79BF1ED, 0x7A1F1F0, 0x7A6F1F3, 0x7ACF1F6
                dw 0x7B2F1F9, 0x7B7F1FC, 0x7BDF1FF, 0x7C2F202, 0x7C8F205
                dw 0x7CDF208, 0x7D2F20B, 0x7D8F20E, 0x7DDF211, 0x7E3F214
                dw 0x7E8F217, 0x7EEF21A, 0x7F3F21D, 0x7F9F221, 0x7FEF224
                dw 0x804F227, 0x809F22A, 0x80EF22D, 0x814F230, 0x819F234
                dw 0x81FF237, 0x824F23A, 0x82AF23D, 0x82FF240, 0x834F244
                dw 0x83AF247, 0x83FF24A, 0x845F24D, 0x84AF250, 0x84FF254
                dw 0x855F257, 0x85AF25A, 0x85FF25E, 0x865F261, 0x86AF264
                dw 0x86FF267, 0x875F26B, 0x87AF26E, 0x87FF271, 0x885F275
                dw 0x88AF278, 0x88FF27B, 0x895F27F, 0x89AF282, 0x89FF286
                dw 0x8A5F289, 0x8AAF28C, 0x8AFF290, 0x8B4F293, 0x8BAF297
                dw 0x8BFF29A, 0x8C4F29E, 0x8C9F2A1, 0x8CFF2A4, 0x8D4F2A8
                dw 0x8D9F2AB, 0x8DEF2AF, 0x8E4F2B2, 0x8E9F2B6, 0x8EEF2B9
                dw 0x8F3F2BD, 0x8F8F2C0, 0x8FEF2C4, 0x903F2C7, 0x908F2CB
                dw 0x90DF2CE, 0x912F2D2, 0x918F2D6, 0x91DF2D9, 0x922F2DD
                dw 0x927F2E0, 0x92CF2E4, 0x931F2E8, 0x937F2EB, 0x93CF2EF
                dw 0x941F2F2, 0x946F2F6, 0x94BF2FA, 0x950F2FD, 0x955F301
                dw 0x95AF305, 0x95FF308, 0x965F30C, 0x96AF310, 0x96FF313
                dw 0x974F317, 0x979F31B, 0x97EF31F, 0x983F322, 0x988F326
                dw 0x98DF32A, 0x992F32E, 0x997F331, 0x99CF335, 0x9A1F339
                dw 0x9A6F33D, 0x9ABF340, 0x9B0F344, 0x9B5F348, 0x9BAF34C
                dw 0x9BFF350, 0x9C4F354, 0x9C9F357, 0x9CEF35B, 0x9D3F35F
                dw 0x9D8F363, 0x9DDF367, 0x9E2F36B, 0x9E7F36F, 0x9ECF372
                dw 0x9F1F376, 0x9F6F37A, 0x9FBF37E, 0x9FFF382, 0xA04F386
                dw 0xA09F38A, 0xA0EF38E, 0xA13F392, 0xA18F396, 0xA1DF39A
                dw 0xA22F39E, 0xA26F3A2, 0xA2BF3A6, 0xA30F3AA, 0xA35F3AE
                dw 0xA3AF3B2, 0xA3FF3B6, 0xA44F3BA, 0xA48F3BE, 0xA4DF3C2
                dw 0xA52F3C6, 0xA57F3CA, 0xA5CF3CE, 0xA60F3D2, 0xA65F3D6
                dw 0xA6AF3DA, 0xA6FF3DE, 0xA73F3E2, 0xA78F3E7, 0xA7DF3EB
                dw 0xA82F3EF, 0xA86F3F3, 0xA8BF3F7, 0xA90F3FB, 0xA95F3FF
                dw 0xA99F404, 0xA9EF408, 0xAA3F40C, 0xAA7F410, 0xAACF414
                dw 0xAB1F418, 0xAB5F41D, 0xABAF421, 0xABFF425, 0xAC3F429
                dw 0xAC8F42E, 0xACDF432, 0xAD1F436, 0xAD6F43A, 0xADBF43F
                dw 0xADFF443, 0xAE4F447, 0xAE8F44B, 0xAEDF450, 0xAF2F454
                dw 0xAF6F458, 0xAFBF45D, 0xAFFF461, 0xB04F465, 0xB08F469
                dw 0xB0DF46E, 0xB11F472, 0xB16F477, 0xB1BF47B, 0xB1FF47F
                dw 0xB24F484, 0xB28F488, 0xB2DF48C, 0xB31F491, 0xB36F495
                dw 0xB3AF49A, 0xB3EF49E, 0xB43F4A2, 0xB47F4A7, 0xB4CF4AB
                dw 0xB50F4B0
                dw 0xB55F4B4, 0xB59F4B9, 0xB5EF4BD, 0xB62F4C2, 0xB66F4C6
                dw 0xB6BF4CA, 0xB6FF4CF, 0xB74F4D3, 0xB78F4D8, 0xB7CF4DC
                dw 0xB81F4E1, 0xB85F4E5, 0xB89F4EA, 0xB8EF4EF, 0xB92F4F3
                dw 0xB97F4F8, 0xB9BF4FC, 0xB9FF501, 0xBA3F505, 0xBA8F50A
                dw 0xBACF50E, 0xBB0F513, 0xBB5F518, 0xBB9F51C, 0xBBDF521
                dw 0xBC1F525, 0xBC6F52A, 0xBCAF52F, 0xBCEF533, 0xBD2F538
                dw 0xBD7F53D, 0xBDBF541, 0xBDFF546, 0xBE3F54B, 0xBE8F54F
                dw 0xBECF554, 0xBF0F559, 0xBF4F55D, 0xBF8F562, 0xBFCF567
                dw 0xC01F56B, 0xC05F570, 0xC09F575, 0xC0DF57A, 0xC11F57E
                dw 0xC15F583, 0xC19F588, 0xC1EF58D, 0xC22F591, 0xC26F596
                dw 0xC2AF59B, 0xC2EF5A0, 0xC32F5A4, 0xC36F5A9, 0xC3AF5AE
                dw 0xC3EF5B3, 0xC42F5B8, 0xC46F5BC, 0xC4AF5C1, 0xC4EF5C6
                dw 0xC52F5CB, 0xC56F5D0, 0xC5AF5D5, 0xC5EF5DA, 0xC62F5DE
                dw 0xC66F5E3, 0xC6AF5E8, 0xC6EF5ED, 0xC72F5F2, 0xC76F5F7
                dw 0xC7AF5FC, 0xC7EF601, 0xC82F605, 0xC86F60A, 0xC8AF60F
                dw 0xC8EF614, 0xC91F619, 0xC95F61E, 0xC99F623, 0xC9DF628
                dw 0xCA1F62D, 0xCA5F632, 0xCA9F637, 0xCACF63C, 0xCB0F641
                dw 0xCB4F646, 0xCB8F64B, 0xCBCF650, 0xCC0F655, 0xCC3F65A
                dw 0xCC7F65F, 0xCCBF664, 0xCCFF669, 0xCD2F66E, 0xCD6F673
                dw 0xCDAF678, 0xCDEF67D, 0xCE1F682, 0xCE5F687, 0xCE9F68C
                dw 0xCEDF691, 0xCF0F696, 0xCF4F69B, 0xCF8F6A1, 0xCFBF6A6
                dw 0xCFFF6AB, 0xD03F6B0, 0xD06F6B5, 0xD0AF6BA, 0xD0EF6BF
                dw 0xD11F6C4, 0xD15F6C9, 0xD18F6CF, 0xD1CF6D4, 0xD20F6D9
                dw 0xD23F6DE, 0xD27F6E3, 0xD2AF6E8, 0xD2EF6EE, 0xD32F6F3
                dw 0xD35F6F8, 0xD39F6FD, 0xD3CF702, 0xD40F708, 0xD43F70D
                dw 0xD47F712, 0xD4AF717, 0xD4EF71C, 0xD51F722, 0xD55F727
                dw 0xD58F72C, 0xD5CF731, 0xD5FF737, 0xD62F73C, 0xD66F741
                dw 0xD69F746, 0xD6DF74C, 0xD70F751, 0xD74F756, 0xD77F75B
                dw 0xD7AF761, 0xD7EF766, 0xD81F76B, 0xD85F771, 0xD88F776
                dw 0xD8BF77B, 0xD8FF781, 0xD92F786, 0xD95F78B, 0xD99F791
                dw 0xD9CF796, 0xD9FF79B, 0xDA2F7A1, 0xDA6F7A6, 0xDA9F7AB
                dw 0xDACF7B1, 0xDB0F7B6, 0xDB3F7BB, 0xDB6F7C1, 0xDB9F7C6
                dw 0xDBCF7CC, 0xDC0F7D1, 0xDC3F7D6, 0xDC6F7DC, 0xDC9F7E1
                dw 0xDCCF7E7, 0xDD0F7EC, 0xDD3F7F2, 0xDD6F7F7, 0xDD9F7FC
                dw 0xDDCF802, 0xDDFF807, 0xDE3F80D, 0xDE6F812, 0xDE9F818
                dw 0xDECF81D, 0xDEFF823, 0xDF2F828, 0xDF5F82E, 0xDF8F833
                dw 0xDFBF838, 0xDFEF83E, 0xE01F843, 0xE04F849, 0xE07F84E
                dw 0xE0AF854, 0xE0DF85A, 0xE10F85F, 0xE13F865, 0xE16F86A
                dw 0xE19F870, 0xE1CF875, 0xE1FF87B, 0xE22F880, 0xE25F886
                dw 0xE28F88B, 0xE2BF891, 0xE2EF896, 0xE31F89C, 0xE34F8A2
                dw 0xE37F8A7, 0xE3AF8AD, 0xE3CF8B2, 0xE3FF8B8, 0xE42F8BE
                dw 0xE45F8C3, 0xE48F8C9, 0xE4BF8CE, 0xE4DF8D4, 0xE50F8DA
                dw 0xE53F8DF, 0xE56F8E5, 0xE59F8EB, 0xE5BF8F0, 0xE5EF8F6
                dw 0xE61F8FB, 0xE64F901, 0xE66F907, 0xE69F90C, 0xE6CF912
                dw 0xE6FF918, 0xE71F91D, 0xE74F923, 0xE77F929, 0xE79F92E
                dw 0xE7CF934, 0xE7FF93A, 0xE81F93F, 0xE84F945, 0xE87F94B
                dw 0xE89F951, 0xE8CF956, 0xE8FF95C, 0xE91F962, 0xE94F967
                dw 0xE96F96D, 0xE99F973, 0xE9BF979, 0xE9EF97E, 0xEA1F984
                dw 0xEA3F98A, 0xEA6F990, 0xEA8F995, 0xEABF99B, 0xEADF9A1
                dw 0xEB0F9A7, 0xEB2F9AC, 0xEB5F9B2, 0xEB7F9B8, 0xEBAF9BE
                dw 0xEBCF9C4, 0xEBFF9C9, 0xEC1F9CF, 0xEC3F9D5, 0xEC6F9DB
                dw 0xEC8F9E1, 0xECBF9E6, 0xECDF9EC, 0xECFF9F2, 0xED2F9F8
                dw 0xED4F9FE, 0xED6FA03, 0xED9FA09, 0xEDBFA0F, 0xEDDFA15
                dw 0xEE0FA1B, 0xEE2FA21, 0xEE4FA26, 0xEE7FA2C, 0xEE9FA32
                dw 0xEEBFA38, 0xEEEFA3E, 0xEF0FA44, 0xEF2FA4A, 0xEF4FA4F
                dw 0xEF7FA55, 0xEF9FA5B, 0xEFBFA61, 0xEFDFA67, 0xEFFFA6D
                dw 0xF02FA73, 0xF04FA79, 0xF06FA7F, 0xF08FA84, 0xF0AFA8A
                dw 0xF0CFA90, 0xF0EFA96, 0xF11FA9C, 0xF13FAA2, 0xF15FAA8
                dw 0xF17FAAE, 0xF19FAB4, 0xF1BFABA, 0xF1DFAC0, 0xF1FFAC6
                dw 0xF21FACC, 0xF23FAD1, 0xF25FAD7, 0xF27FADD, 0xF29FAE3
                dw 0xF2BFAE9, 0xF2DFAEF, 0xF2FFAF5, 0xF31FAFB, 0xF33FB01
                dw 0xF35FB07, 0xF37FB0D, 0xF39FB13, 0xF3BFB19, 0xF3DFB1F
                dw 0xF3FFB25, 0xF41FB2B, 0xF43FB31, 0xF45FB37, 0xF46FB3D
                dw 0xF48FB43, 0xF4AFB49, 0xF4CFB4F, 0xF4EFB55, 0xF50FB5B
                dw 0xF51FB61, 0xF53FB67, 0xF55FB6D, 0xF57FB73, 0xF59FB79
                dw 0xF5AFB7F, 0xF5CFB85, 0xF5EFB8B, 0xF60FB91, 0xF61FB97
                dw 0xF63FB9D, 0xF65FBA3, 0xF67FBA9, 0xF68FBAF, 0xF6AFBB5
                dw 0xF6CFBBC, 0xF6DFBC2, 0xF6FFBC8, 0xF71FBCE, 0xF72FBD4
                dw 0xF74FBDA, 0xF76FBE0, 0xF77FBE6, 0xF79FBEC, 0xF7AFBF2
                dw 0xF7CFBF8, 0xF7DFBFE, 0xF7FFC04, 0xF81FC0A, 0xF82FC11
                dw 0xF84FC17, 0xF85FC1D, 0xF87FC23, 0xF88FC29, 0xF8AFC2F
                dw 0xF8BFC35, 0xF8DFC3B, 0xF8EFC41, 0xF90FC47, 0xF91FC4E
                dw 0xF93FC54, 0xF94FC5A, 0xF95FC60, 0xF97FC66, 0xF98FC6C
                dw 0xF9AFC72, 0xF9BFC78, 0xF9CFC7F, 0xF9EFC85, 0xF9FFC8B
                dw 0xFA1FC91, 0xFA2FC97, 0xFA3FC9D, 0xFA5FCA3, 0xFA6FCAA
                dw 0xFA7FCB0, 0xFA8FCB6, 0xFAAFCBC, 0xFABFCC2, 0xFACFCC8
                dw 0xFAEFCCE, 0xFAFFCD5, 0xFB0FCDB, 0xFB1FCE1, 0xFB3FCE7
                dw 0xFB4FCED, 0xFB5FCF3, 0xFB6FCFA, 0xFB7FD00, 0xFB8FD06
                dw 0xFBAFD0C, 0xFBBFD12, 0xFBCFD18, 0xFBDFD1F, 0xFBEFD25
                dw 0xFBFFD2B, 0xFC0FD31, 0xFC2FD37, 0xFC3FD3E, 0xFC4FD44
                dw 0xFC5FD4A, 0xFC6FD50, 0xFC7FD56, 0xFC8FD5D, 0xFC9FD63
                dw 0xFCAFD69, 0xFCBFD6F, 0xFCCFD75, 0xFCDFD7C, 0xFCEFD82
                dw 0xFCFFD88, 0xFD0FD8E, 0xFD1FD94, 0xFD2FD9B, 0xFD3FDA1
                dw 0xFD4FDA7, 0xFD5FDAD, 0xFD5FDB3, 0xFD6FDBA, 0xFD7FDC0
                dw 0xFD8FDC6, 0xFD9FDCC, 0xFDAFDD3, 0xFDBFDD9, 0xFDCFDDF
                dw 0xFDCFDE5, 0xFDDFDEB, 0xFDEFDF2, 0xFDFFDF8, 0xFE0FDFE
                dw 0xFE0FE04, 0xFE1FE0B, 0xFE2FE11, 0xFE3FE17, 0xFE3FE1D
                dw 0xFE4FE24, 0xFE5FE2A, 0xFE6FE30, 0xFE6FE36, 0xFE7FE3D
                dw 0xFE8FE43, 0xFE8FE49, 0xFE9FE4F, 0xFEAFE56, 0xFEAFE5C
                dw 0xFEBFE62, 0xFECFE68, 0xFECFE6F, 0xFEDFE75, 0xFEDFE7B
                dw 0xFEEFE81, 0xFEFFE88, 0xFEFFE8E, 0xFF0FE94, 0xFF0FE9A
                dw 0xFF1FEA1, 0xFF1FEA7, 0xFF2FEAD, 0xFF2FEB3, 0xFF3FEBA
                dw 0xFF3FEC0, 0xFF4FEC6, 0xFF4FECC, 0xFF5FED3, 0xFF5FED9
                dw 0xFF6FEDF, 0xFF6FEE5, 0xFF7FEEC, 0xFF7FEF2, 0xFF8FEF8
                dw 0xFF8FEFF, 0xFF8FF05, 0xFF9FF0B, 0xFF9FF11, 0xFF9FF18
                dw 0xFFAFF1E, 0xFFAFF24, 0xFFAFF2A, 0xFFBFF31, 0xFFBFF37
                dw 0xFFBFF3D, 0xFFCFF44, 0xFFCFF4A, 0xFFCFF50, 0xFFCFF56
                dw 0xFFDFF5D, 0xFFDFF63, 0xFFDFF69, 0xFFDFF70, 0xFFEFF76
                dw 0xFFEFF7C, 0xFFEFF82, 0xFFEFF89, 0xFFEFF8F, 0xFFFFF95
                dw 0xFFFFF9B, 0xFFFFFA2, 0xFFFFFA8, 0xFFFFFAE, 0xFFFFFB5
                dw 0xFFFFFBB, 0x1000FFC1, 0x1000FFC7, 0x1000FFCE, 0x1000FFD4
                dw 0x1000FFDA, 0x1000FFE1, 0x1000FFE7, 0x1000FFED, 0x1000FFF3
                dw 0x1000FFFA
word_800A8F20:  dh 0                  ; DATA XREF: ratan2:loc_800943BC?r
                                         ; ratan2:loc_80094444?r
                dh 1
                dw 0x20002, 0x30003, 0x50004, 0x60005, 0x70007, 0x90008
                dw 0xA0009, 0xB000A, 0xC000C, 0xE000D, 0xF000E, 0x100010
                dw 0x110011, 0x130012, 0x140013, 0x150015, 0x170016
                dw 0x180017, 0x190018, 0x1A001A, 0x1C001B, 0x1D001C
                dw 0x1E001E, 0x1F001F, 0x210020, 0x220021, 0x230023
                dw 0x240024, 0x260025, 0x270026, 0x280028, 0x2A0029
                dw 0x2B002A, 0x2C002B, 0x2D002D, 0x2F002E, 0x30002F
                dw 0x310031, 0x320032, 0x340033, 0x350034, 0x360036
                dw 0x370037, 0x390038, 0x3A0039, 0x3B003B, 0x3D003C
                dw 0x3E003D, 0x3F003E, 0x400040, 0x420041, 0x430042
                dw 0x440043, 0x450045, 0x470046, 0x480047, 0x490049
                dw 0x4A004A, 0x4C004B, 0x4D004C, 0x4E004E, 0x4F004F
                dw 0x510050, 0x520051, 0x530053, 0x540054, 0x560055
                dw 0x570056, 0x580058, 0x590059, 0x5B005A, 0x5C005B
                dw 0x5D005D, 0x5E005E, 0x60005F, 0x610060, 0x620062
                dw 0x630063, 0x650064, 0x660065, 0x670067, 0x680068
                dw 0x6A0069, 0x6B006A, 0x6C006B, 0x6D006D, 0x6F006E
                dw 0x70006F, 0x710070, 0x720072, 0x740073, 0x750074
                dw 0x760075, 0x770077, 0x780078, 0x7A0079, 0x7B007A
                dw 0x7C007C, 0x7D007D, 0x7F007E, 0x80007F, 0x810080
                dw 0x820082, 0x830083, 0x850084, 0x860085, 0x870087
                dw 0x880088, 0x8A0089, 0x8B008A, 0x8C008B, 0x8D008D
                dw 0x8E008E, 0x90008F, 0x910090, 0x920091, 0x930093
                dw 0x940094, 0x960095, 0x970096, 0x980098, 0x990099
                dw 0x9B009A, 0x9C009B, 0x9D009C, 0x9E009E, 0x9F009F
                dw 0xA100A0, 0xA200A1, 0xA300A2, 0xA400A4, 0xA500A5
                dw 0xA600A6, 0xA800A7, 0xA900A8, 0xAA00A9, 0xAB00AB
                dw 0xAC00AC, 0xAE00AD, 0xAF00AE, 0xB000AF, 0xB100B1
                dw 0xB200B2, 0xB400B3, 0xB500B4, 0xB600B5, 0xB700B6
                dw 0xB800B8, 0xB900B9, 0xBB00BA, 0xBC00BB, 0xBD00BC
                dw 0xBE00BE, 0xBF00BF, 0xC000C0, 0xC200C1, 0xC300C2
                dw 0xC400C3, 0xC500C5, 0xC600C6, 0xC700C7, 0xC900C8
                dw 0xCA00C9, 0xCB00CA, 0xCC00CB, 0xCD00CD, 0xCE00CE
                dw 0xCF00CF, 0xD100D0, 0xD200D1, 0xD300D2, 0xD400D3
                dw 0xD500D5, 0xD600D6, 0xD700D7, 0xD900D8, 0xDA00D9
                dw 0xDB00DA, 0xDC00DB, 0xDD00DD, 0xDE00DE, 0xDF00DF
                dw 0xE100E0, 0xE200E1, 0xE300E2, 0xE400E3, 0xE500E4
                dw 0xE600E6, 0xE700E7, 0xE800E8, 0xEA00E9, 0xEB00EA
                dw 0xEC00EB, 0xED00EC, 0xEE00ED, 0xEF00EF, 0xF000F0
                dw 0xF100F1, 0xF200F2, 0xF400F3, 0xF500F4, 0xF600F5
                dw 0xF700F6, 0xF800F7, 0xF900F8, 0xFA00FA, 0xFB00FB
                dw 0xFC00FC, 0xFD00FD, 0xFE00FE, 0x10000FF, 0x1010100
                dw 0x1020101, 0x1030102, 0x1040103, 0x1050104, 0x1060106
                dw 0x1070107, 0x1080108, 0x1090109, 0x10A010A, 0x10B010B
                dw 0x10D010C, 0x10E010D, 0x10F010E, 0x110010F, 0x1110110
                dw 0x1120111, 0x1130112, 0x1140113, 0x1150114, 0x1160116
                dw 0x1170117, 0x1180118, 0x1190119, 0x11A011A, 0x11B011B
                dw 0x11C011C, 0x11D011D, 0x11E011E, 0x120011F, 0x1210120
                dw 0x1220121, 0x1230122, 0x1240123, 0x1250124, 0x1260125
                dw 0x1270126, 0x1280127, 0x1290128, 0x12A0129, 0x12B012A
                dw 0x12C012B, 0x12D012C, 0x12E012D, 0x12F012E, 0x130012F
                dw 0x1310130, 0x1320131, 0x1330133, 0x1340134, 0x1350135
                dw 0x1360136, 0x1370137, 0x1380138, 0x1390139, 0x13A013A
                dw 0x13B013B, 0x13C013C, 0x13D013D, 0x13E013E, 0x13F013F
                dw 0x1400140, 0x1410141, 0x1420142, 0x1430142, 0x1440143
                dw 0x1450144, 0x1460145, 0x1470146, 0x1480147, 0x1490148
                dw 0x14A0149, 0x14B014A, 0x14C014B, 0x14D014C, 0x14E014D
                dw 0x14F014E, 0x150014F, 0x1510150, 0x1520151, 0x1530152
                dw 0x1540153, 0x1540154, 0x1550155, 0x1560156, 0x1570157
                dw 0x1580158, 0x1590159, 0x15A015A, 0x15B015B, 0x15C015C
                dw 0x15D015D, 0x15E015D, 0x15F015E, 0x160015F, 0x1610160
                dw 0x1620161, 0x1630162, 0x1640163, 0x1640164, 0x1650165
                dw 0x1660166, 0x1670167, 0x1680168, 0x1690169, 0x16A016A
                dw 0x16B016A, 0x16C016B, 0x16D016C, 0x16E016D, 0x16F016E
                dw 0x170016F, 0x1700170, 0x1710171, 0x1720172, 0x1730173
                dw 0x1740174, 0x1750174, 0x1760175, 0x1770176, 0x1780177
                dw 0x1790178, 0x1790179, 0x17A017A, 0x17B017B, 0x17C017C
                dw 0x17D017D, 0x17E017D, 0x17F017E, 0x180017F, 0x1810180
                dw 0x1810181, 0x1820182, 0x1830183, 0x1840184, 0x1850184
                dw 0x1860185, 0x1870186, 0x1870187, 0x1880188, 0x1890189
                dw 0x18A018A, 0x18B018B, 0x18C018B, 0x18D018C, 0x18E018D
                dw 0x18E018E, 0x18F018F, 0x1900190, 0x1910191, 0x1920191
                dw 0x1930192, 0x1930193, 0x1940194, 0x1950195, 0x1960196
                dw 0x1970196, 0x1980197, 0x1990198, 0x1990199, 0x19A019A
                dw 0x19B019B, 0x19C019B, 0x19D019C, 0x19D019D, 0x19E019E
                dw 0x19F019F, 0x1A001A0, 0x1A101A0, 0x1A201A1, 0x1A201A2
                dw 0x1A301A3, 0x1A401A4, 0x1A501A4, 0x1A601A5, 0x1A601A6
                dw 0x1A701A7, 0x1A801A8, 0x1A901A9, 0x1AA01A9, 0x1AB01AA
                dw 0x1AB01AB, 0x1AC01AC, 0x1AD01AD, 0x1AE01AD, 0x1AF01AE
                dw 0x1AF01AF, 0x1B001B0, 0x1B101B0, 0x1B201B1, 0x1B201B2
                dw 0x1B301B3, 0x1B401B4, 0x1B501B4, 0x1B601B5, 0x1B601B6
                dw 0x1B701B7, 0x1B801B8, 0x1B901B8, 0x1B901B9, 0x1BA01BA
                dw 0x1BB01BB, 0x1BC01BB, 0x1BD01BC, 0x1BD01BD, 0x1BE01BE
                dw 0x1BF01BE, 0x1C001BF, 0x1C001C0, 0x1C101C1, 0x1C201C2
                dw 0x1C301C2, 0x1C301C3, 0x1C401C4, 0x1C501C5, 0x1C601C5
                dw 0x1C601C6, 0x1C701C7, 0x1C801C8, 0x1C901C8, 0x1C901C9
                dw 0x1CA01CA, 0x1CB01CB, 0x1CC01CB, 0x1CC01CC, 0x1CD01CD
                dw 0x1CE01CD, 0x1CF01CE, 0x1CF01CF, 0x1D001D0, 0x1D101D0
                dw 0x1D101D1, 0x1D201D2, 0x1D301D3, 0x1D401D3, 0x1D401D4
                dw 0x1D501D5, 0x1D601D5, 0x1D701D6, 0x1D701D7, 0x1D801D8
                dw 0x1D901D8, 0x1D901D9, 0x1DA01DA, 0x1DB01DA, 0x1DC01DB
                dw 0x1DC01DC, 0x1DD01DD, 0x1DE01DD, 0x1DE01DE, 0x1DF01DF
                dw 0x1E001DF, 0x1E001E0, 0x1E101E1, 0x1E201E1, 0x1E301E2
                dw 0x1E301E3, 0x1E401E4, 0x1E501E4, 0x1E501E5, 0x1E601E6
                dw 0x1E701E6, 0x1E701E7, 0x1E801E8, 0x1E901E8, 0x1E901E9
                dw 0x1EA01EA, 0x1EB01EA, 0x1EB01EB, 0x1EC01EC, 0x1ED01EC
                dw 0x1ED01ED, 0x1EE01EE, 0x1EF01EE, 0x1EF01EF, 0x1F001F0
                dw 0x1F101F0, 0x1F101F1, 0x1F201F2, 0x1F301F2, 0x1F301F3
                dw 0x1F401F4, 0x1F501F4, 0x1F501F5, 0x1F601F6, 0x1F701F6
                dw 0x1F701F7, 0x1F801F8, 0x1F901F8, 0x1F901F9, 0x1FA01FA
                dw 0x1FB01FA, 0x1FB01FB, 0x1FC01FC, 0x1FD01FC, 0x1FD01FD
                dw 0x1FE01FE, 0x1FF01FE, 0x1FF01FF, 0x20001FF, 0x200
                dw 0, 0, 0
                dw 0x117350, 0x440000
dword_800A9738: dw 0                  ; DATA XREF: SpuStart+54?w
                                         ; SpuQuit+3C?r ...
dword_800A973C: dw 0                  ; DATA XREF: _SpuInit+B8?w
                                         ; SpuSetKey:loc_80096CDC?r ...
dword_800A9740: dw 0                  ; DATA XREF: _SpuInit+A8?w
                                         ; SpuSetTransferMode:loc_80096F44?w ...
dword_800A9744: dw 0                  ; DATA XREF: _SpuInit+5C?w
                                         ; SpuSetReverb+38?w ...
dword_800A9748: dw 0                  ; DATA XREF: _SpuInit+64?w
                                         ; SpuMalloc?r ...
dword_800A974C: dw 0                  ; DATA XREF: _SpuInit+80?w
                                         ; SpuMalloc+3C?r ...
                dw 0
dword_800A9754: dw 0                  ; DATA XREF: _SpuInit+4C?o
                                         ; _SpuInit+6C?w ...
word_800A9758:  dh 0                  ; DATA XREF: _SpuInit+70?w
                                         ; SpuSetReverbModeParam+3C4?w ...
word_800A975A:  dh 0                  ; DATA XREF: _SpuInit+74?w
                                         ; SpuSetReverbModeParam+3FC?w ...
dword_800A975C: dw 0                  ; DATA XREF: _SpuInit+78?w
                                         ; SpuSetReverbModeParam+148?w ...
dword_800A9760: dw 0                  ; DATA XREF: _SpuInit+7C?w
                                         ; SpuSetReverbModeParam+140?w ...
dword_800A9764: dw 0                  ; DATA XREF: _SpuInit+C8?w
                                         ; SpuSetKey+60?r ...
dword_800A9768: dw 0                  ; DATA XREF: _SpuInit+C0?w
                                         ; _SpuSetAnyVoice+D8?r ...
word_800A976C:  dh 0xC000             ; DATA XREF: SpuSetVoiceAttr+2C?o
                                         ; SpuGetVoiceAttr+2A0?r ...
                dh 0xC000
                dw 0xC000C000, 0xC000C000, 0xC000C000, 0xC000C000, 0xC000C000
                dw 0xC000C000, 0xC000C000, 0xC000C000, 0xC000C000, 0xC000C000
                db 0, 0xC0
word_800A979A:  dh 0xC000             ; DATA XREF: _SpuInit+28?o
dword_800A979C: dw 0                  ; DATA XREF: _SpuInit+D0?w
                                         ; _SpuSetAnyVoice+4?r ...
dword_800A97A0: dw 0                  ; DATA XREF: SpuStart?r
                                         ; SpuStart+20?w ...
                dw 0
                dw 0
                dw 0
dword_800A97B0: dw 0x1F801C00         ; DATA XREF: _spu_init+2C?r
                                         ; _spu_init+5C?r ...
dword_800A97B4: dw 0x1F8010C0         ; DATA XREF: TEXT:80094C40?r
                                         ; _spu_t+1F8?r
dword_800A97B8: dw 0x1F8010C4         ; DATA XREF: TEXT:80094C50?r
                                         ; _spu_t+22C?r
dword_800A97BC: dw 0x1F8010C8         ; DATA XREF: TEXT:80094C60?r
                                         ; _spu_t:loc_80094EE8?r
dword_800A97C0: dw 0x1F8010F0         ; DATA XREF: _spu_init+C?r
                                         ; TEXT:_spu_FsetPCR?r ...
dword_800A97C4: dw 0x1F801014         ; DATA XREF: sub_80095170?r
                                         ; sub_80095198?r
word_800A97C8:  dh 0                  ; DATA XREF: _spu_init+44?w
                                         ; _spu_init+168?w ...
                dh 0
dword_800A97CC: dw 0                  ; DATA XREF: _SpuInit+B0?w
                                         ; _spu_init+34?w ...
dword_800A97D0: dw 0                  ; DATA XREF: _spu_init+3C?w
dword_800A97D4: dw 2                  ; DATA XREF: _spu_init+E0?w
                                         ; _spu_FsetRXXa?r
dword_800A97D8: dw 3                  ; DATA XREF: _spu_init+EC?w
                                         ; _spu_t+64?r ...
dword_800A97DC: dw 8                  ; DATA XREF: _spu_init+F8?w
                                         ; _spu_FsetRXXa+14?r
dword_800A97E0: dw 7                  ; DATA XREF: _spu_init+104?w
                                         ; _spu_FsetRXXa+3C?r ...
dword_800A97E4: dw 1                  ; DATA XREF: _spu_init+24C?w
                                         ; SpuWrite+44?w ...
dword_800A97E8: dw 0                  ; DATA XREF: _spu_init+25C?w
                                         ; _spu_FiDMA:loc_80094B98?r ...
dword_800A97EC: dw 0                  ; DATA XREF: _spu_init+264?w
                                         ; SpuQuit+38?w ...
dword_800A97F0: dw 0x7070707, 0x7070707, 0x7070707, 0x7070707
                                         ; DATA XREF: _spu_init+154?o
dword_800A9800: dw 0                  ; DATA XREF: _spu_FiDMA?r
                                         ; TEXT:80094C6C?w ...
dword_800A9804: dw 0                  ; DATA XREF: _spu_t+1EC?w
                                         ; _spu_t+20C?r
dword_800A9808: dw 0                  ; DATA XREF: _spu_t+218?w
                                         ; _spu_t+224?r
                dw 0
dword_800A9810: dw 0                  ; DATA XREF: _SpuInit+90?w
                                         ; SpuInitMalloc+38?w ...
dword_800A9814: dw 0                  ; DATA XREF: _SpuInit+98?w
                                         ; SpuInitMalloc+30?w ...
dword_800A9818: dw 0                  ; DATA XREF: _SpuInit+A0?w
                                         ; SpuInitMalloc+28?w ...
                dw 0
dword_800A9820: dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                                         ; DATA XREF: SpuClearReverbWorkArea+114?o
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0
word_800A9C20:  dh 0x8000             ; DATA XREF: _spu_note2pitch+74?r
                                         ; _spu_pitch2note+94?r
                dh 0x879C
                dw 0x98378FAC, 0xAADCA145, 0xBFC8B504, 0xD744CB2F
                db 0x11, 0xE4
word_800A9C36:  dh 0xF1A1             ; DATA XREF: _spu_pitch2note+58?o
word_800A9C38:  dh 0x8000             ; DATA XREF: _spu_note2pitch+80?r
                dh 0x800E
                dw 0x802C801D, 0x804A803B, 0x80678058, 0x80858076, 0x80A38094
                dw 0x80C080B1, 0x80DE80CF, 0x80FC80ED, 0x811A810B, 0x81388129
                dw 0x81558146, 0x81738164, 0x81918182, 0x81AF81A0, 0x81CD81BE
                dw 0x81EB81DC, 0x820981FA, 0x82278218, 0x82458236, 0x82638254
                dw 0x82828272, 0x82A08291, 0x82BE82AF, 0x82DC82CD, 0x82FA82EB
                dw 0x8319830A, 0x83378328, 0x83558346, 0x83748364, 0x83928383
                dw 0x83B083A1, 0x83CF83C0, 0x83ED83DE, 0x840C83FD, 0x842A841B
                dw 0x8449843A, 0x84688458, 0x84868477, 0x84A58495, 0x84C384B4
                dw 0x84E284D3, 0x850184F1, 0x85208510, 0x853E852F, 0x855D854E
                dw 0x857C856D, 0x859B858B, 0x85BA85AA, 0x85D985C9, 0x85F885E8
                dw 0x86178607, 0x86368626, 0x86558645, 0x86748664, 0x86938683
                dw 0x86B286A2, 0x86D186C1, 0x86F086E0, 0x870F8700, 0x872E871F
                dw 0x874E873E, 0x876D875D
                db 0x7D, 0x87
word_800A9D36:  dh 0x878C             ; DATA XREF: _spu_pitch2note+BC?o
                dw 0
                dw 0
dword_800A9D40: dw 0xFFFE             ; DATA XREF: _SpuInit+54?r
                                         ; SpuSetReverbModeParam+8C?r ...
                dw 0xFB28, 0xFC18, 0xF6F8, 0xF204, 0xEA44, 0xE128, 0xCFF8
                dw 0xCFF8, 0xF880, 0, 0
dword_800A9D70: dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                                         ; DATA XREF: SpuSetReverbModeParam+E4?o
                                         ; SpuSetReverbModeParam+1C0?o ...
                dw 0
                dw 0x5B007D, 0x54B86D80, 0xBED0, 0xBA800000, 0x53005800
                dw 0x33304D6, 0x22703F0, 0x1EF0374, 0x1B50334, 0, 0
                dw 0, 0
                dw 0x13601B4, 0x5C00B8, 0x80008000, 0
                dw 0x250033, 0x4FA870F0, 0x4410BCE0, 0x9C00C0F0, 0x4EC05280
                dw 0x31B03E4, 0x2AF03A4, 0x2660372, 0x25D031C, 0x18E025C
                dw 0x135022F, 0xB701D2, 0xB5018F, 0x8000B4, 0x26004C
                dw 0x80008000, 0
                dw 0x7F00B1, 0x4FA870F0, 0x4510BCE0, 0xB4C0BEF0, 0x4EC05280
                dw 0x76B0904, 0x65F0824, 0x61607A2, 0x5ED076C, 0x42E05EC
                dw 0x305050F, 0x2B70462, 0x265042F, 0x1B20264, 0x800100
                dw 0x80008000, 0
                dw 0xA900E3, 0x4FA86F60, 0x4510BCE0, 0xA680BEF0, 0x52C05680
                dw 0xB580DFB, 0xA3C0D09, 0x9730BD9, 0x8DA0B59, 0x5E908D9
                dw 0x4B007EC, 0x3D206EF, 0x31D05EA, 0x238031C, 0xAA0154
                dw 0x80008000, 0
                dw 0x13901A5, 0x50006000, 0xB8004C00, 0xC000BC00, 0x5C006000
                dw 0x11BB15BA, 0x10BD14C2, 0xDC111BC, 0xDC311C0, 0x9C10DC0
                dw 0x7C10BC4, 0x6CD0A00, 0x5C109C2, 0x41A05C0, 0x13A0274
                dw 0x80008000, 0
                dw 0x231033D, 0x50007E00, 0xB000B400, 0xB0004C00, 0x54006000
                dw 0x1A311ED6, 0x183B1D14, 0x16B21BC2, 0x15EF1A32, 0x105515EE
                dw 0xF2D1334, 0xC5D11F6, 0xAE11056, 0x7A20AE0, 0x2320464
                dw 0x80008000, 0
                dw 0x10001, 0x7FFF7FFF, 0
                dw 0x81000000, 0
                dw 0xFFF1FFF, 0x51005, 0
                dw 0x51005, 0, 0, 0, 0
                dw 0x10021004, 0x20004, 0x80008000, 0
                dw 0x10001, 0x7FFF7FFF, 0, 0, 0
                dw 0xFFF1FFF, 0x51005, 0
                dw 0x51005, 0, 0, 0, 0
                dw 0x10021004, 0x20004, 0x80008000, 0
                dw 0x130017, 0x4FA870F0, 0x4510BCE0, 0x8500BEF0, 0x54C05F80
                dw 0x2AF0371, 0x1DF02E5, 0x1D702B0, 0x26A0358, 0x11E01D6
                dw 0xB1012D, 0x59011F, 0xE301A0, 0x400058, 0x140028
                dw 0x80008000, 0, 0
                dw 0x67350, 0x440000
dword_800AA028: dw 0x1F801814         ; DATA XREF: VSync?r
                                         ; VSync+B8?r ...
dword_800AA02C: dw 0x1F801110         ; DATA XREF: VSync+8?r
                                         ; VSync+12C?r
dword_800AA030: dw 0                  ; DATA XREF: VSync+48?r
                                         ; VSync+140?w ...
dword_800AA034: dw 0                  ; DATA XREF: VSync+84?r
                                         ; VSync:loc_800981A4?r ...
                dw 0
                dw 0
aLibraryProgram:db "Library Programs (c) 1993-1997 Sony Computer Entertainment In"
                db "c., All Rights Reserved.", 0x0
                dh 0
word_800AA098:  dh 0                  ; DATA XREF: sub_800984AC+8?o
                                         ; sub_800984AC+14?r ...
word_800AA09A:  dh 0                  ; DATA XREF: CheckCallback?r
                                         ; sub_80098584+68?w ...
dword_800AA09C: dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                                         ; DATA XREF: sub_80098584+90?o
                                         ; sub_80098754+14?o
word_800AA0C8:  dh 0                  ; DATA XREF: sub_80098584+60?r
                                         ; sub_80098584+F8?r ...
word_800AA0CA:  dh 0                  ; DATA XREF: sub_8009889C+44?w
                                         ; sub_8009893C+34?r
dword_800AA0CC: dw 0                  ; DATA XREF: sub_8009889C+54?w
                                         ; sub_8009893C+4C?r
dword_800AA0D0: dw 0                  ; DATA XREF: sub_800984AC+64?o
                                         ; sub_800984AC+80?o ...
dword_800AA0D4: dw 0                  ; DATA XREF: sub_800984AC:loc_80098524?o
                                         ; sub_800984AC+8C?w
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0
dword_800AB0B0: dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                                         ; DATA XREF: sub_800984AC+84?o
                dw 0, 0, 0
off_800AB100:   dw aIdIntrCV175199    ; DATA XREF: TEXT:off_800AB120?o
                                         ; "$Id: intr.c,v 1.75 1997/02/07 09:00:36 "...
                dw 0
                dw 0x80098754
                dw 0x800984AC
                dw 0x8009889C
                dw 0
                dw 0x8009893C
                dw word_800AA098
off_800AB120:   dw off_800AB100       ; DATA XREF: ResetCallback?r
                                         ; InterruptCallback?r ...
dword_800AB124: dw 0x1F801070         ; DATA XREF: sub_800984AC+24?r
                                         ; sub_80098584+34?r ...
dword_800AB128: dw 0x1F801074         ; DATA XREF: TEXT:GetIntrMask?r
                                         ; SetIntrMask?r ...
dword_800AB12C: dw 0x1F8010F0         ; DATA XREF: sub_800984AC+48?r
                                         ; sub_8009889C+34?r ...
dword_800AB130: dw 0                  ; DATA XREF: sub_80098584+148?o
                                         ; sub_80098584+150?r ...
                dw 0
                dw 0
                dw 0
dword_800AB140: dw 0, 0, 0, 0, 0, 0, 0, 0
                                         ; DATA XREF: startIntrVSync+4?o
                                         ; sub_80098AB0+18?o ...
dword_800AB160: dw 0                  ; DATA XREF: VSync+60?r
                                         ; VSync+C8?r ...
dword_800AB164: dw 0x1F801114         ; DATA XREF: startIntrVSync+C?r
                dw 0
                dw 0
dword_800AB170: dw 0x1F8010F4         ; DATA XREF: startIntrDMA+1C?r
                                         ; sub_80098BC4?r ...
dword_800AB174: dw 0, 0, 0, 0, 0, 0, 0, 0
                                         ; DATA XREF: startIntrDMA+4?o
                                         ; sub_80098BC4+4C?o ...
dword_800AB194: dw 0x1F801080         ; DATA XREF: sub_80098BC4+134?r
                dw 0
                dw 0
dword_800AB1A0: dw 0                  ; DATA XREF: TEXT:SetVideoMode?r
                                         ; TEXT:80098E28?w ...
                dw 0
                dw 0
                dw 0
dword_800AB1B0: dw 0                  ; DATA XREF: start:__main?r
                                         ; start+C8?w ...
dword_800AB1B4: dw 0                  ; DATA XREF: start+6C?w
dword_800AB1B8: dw 0                  ; DATA XREF: start+60?w
                dw 0x800148B8
                dw 0x88A24, 0x8009D2DC, 0xE008, 0x800ABBF0, 0x17618
                dw 0x37350, 0x440000, 0, 0
dword_800AB1E4: dw 0x1F801070         ; DATA XREF: TEXT:80099728?r
                                         ; TEXT:80099758?r
dword_800AB1E8: dw 0x1F801100         ; DATA XREF: TEXT:loc_80099664?r
                                         ; TEXT:loc_800996CC?r ...
dword_800AB1EC: dw 0x10               ; DATA XREF: TEXT:80099730?r
                                         ; TEXT:80099760?r
                db 0x20, 0, 0, 0
                dw 0x40, 1, 0, 0
dword_800AB204: dw 0x100              ; DATA XREF: SetConf+70?r
                                         ; SetConf:loc_80099880?r ...
                dw 0, 0, 0
dword_800AB214: dw 0                  ; DATA XREF: TEXT:80099DA4?w
                                         ; ReadInitPadFlag?r ...
dword_800AB218: dw 0x1F801040         ; DATA XREF: sub_80099FF0?r
dword_800AB21C: dw 0x1F801070         ; DATA XREF: sub_8009A058?r
                dw 0
                dw 0xC7350, 0x440000
dword_800AB22C: dw 0                  ; DATA XREF: TEXT:8009A974?r
                                         ; sub_8009AE60+94?r ...
dword_800AB230: dw 0                  ; DATA XREF: TEXT:8009A740?r
                                         ; TEXT:8009A798?r ...
dword_800AB234: dw 0                  ; DATA XREF: sub_8009C268+70?r
                                         ; sub_8009C32C+9C?r ...
dword_800AB238: dw 0                  ; DATA XREF: sub_8009C268+54?r
                                         ; sub_8009C32C+30?r ...
dword_800AB23C: dw 0                  ; DATA XREF: PadInitDirect+80?w
dword_800AB240: dw 0                  ; DATA XREF: PadGetState?r
                                         ; TEXT:8009A384?r ...
dword_800AB244: dw 0                  ; DATA XREF: unknown_libname_1+8?r
                                         ; sub_8009C0E4+78?r ...
dword_800AB248: dw 0                  ; DATA XREF: sub_8009B7E4+2C?r
                                         ; sub_8009BD58+10?r ...
dword_800AB24C: dw 0                  ; DATA XREF: sub_8009AB2C+D0?r
                                         ; sub_8009AB2C+134?r ...
dword_800AB250: dw 0                  ; DATA XREF: sub_8009AB2C+148?r
                                         ; sub_8009C32C+200?r ...
dword_800AB254: dw 0                  ; DATA XREF: sub_8009A810+38?r
dword_800AB258: dw 0                  ; DATA XREF: sub_8009C0E4+4C?r
dword_800AB25C: dw 0                  ; DATA XREF: sub_8009C0E4+38?r
dword_800AB260: dw 0                  ; DATA XREF: TEXT:8009A290?r
                                         ; TEXT:8009A738?r ...
dword_800AB264: dw 0                  ; DATA XREF: TEXT:8009A708?w
                                         ; TEXT:8009A7C0?w ...
dword_800AB268: dw 0                  ; DATA XREF: sub_8009C0E4+24?r
dword_800AB26C: dw 0                  ; DATA XREF: TEXT:8009A95C?w
                                         ; TEXT:loc_8009A988?r ...
dword_800AB270: dw 0                  ; DATA XREF: TEXT:8009A954?w
                                         ; sub_8009AE60+C?o ...
dword_800AB274: dw 0                  ; DATA XREF: TEXT:8009A998?w
                                         ; sub_8009CA54+EC?r ...
dword_800AB278: dw 0                  ; DATA XREF: TEXT:PadChkMtap?r
                                         ; sub_8009C1BC+5C?r ...
dword_800AB27C: dw 0                  ; DATA XREF: TEXT:8009A6D4?r
                                         ; TEXT:8009A724?w ...
dword_800AB280: dw 1                  ; DATA XREF: TEXT:8009A6CC?r
                                         ; TEXT:8009A77C?w ...
dword_800AB284: dw 0xFFFFFFFF         ; DATA XREF: sub_8009AB2C+78?r
                                         ; sub_8009AB2C+8C?o ...
                dw 0xFFFFFFFF
dword_800AB28C: dw 0x1F801070         ; DATA XREF: sub_8009A810?r
                                         ; sub_8009AA1C+3C?r ...
dword_800AB290: dw 0x1F801040         ; DATA XREF: TEXT:loc_8009A878?r
                                         ; TEXT:loc_8009A9E8?r ...
dword_800AB294: dw 0                  ; DATA XREF: TEXT:8009A8B8?w
                                         ; sub_8009AA08?r ...
                dw 0, 0, 0
dword_800AB2A4: dw 0                  ; DATA XREF: sub_8009C1BC+7C?w
                                         ; sub_8009C1BC+90?w ...
dword_800AB2A8: dw 0x1F801040         ; DATA XREF: sub_8009C32C+2D8?r
                                         ; sub_8009C32C+340?r
dword_800AB2AC: dw 0                  ; DATA XREF: unknown_libname_1+28?w
                                         ; sub_8009C0E4:loc_8009C144?r ...
dword_800AB2B0: dw 0                  ; DATA XREF: sub_8009C268+50?w
                                         ; sub_8009C268:loc_8009C2D0?r ...
dword_800AB2B4: dw 0x8009C09C         ; DATA XREF: sub_8009AE60+24?r
                dw 0x8009C0E4
                dw 0x8009C1BC
                dw 0x8009C268
                dw 0x8009C32C
                dw 0, 0, 0
dword_800AB2D4: dw 0x1F801040         ; DATA XREF: sub_8009C894:loc_8009C908?r
                dw 0, 0, 0
dword_800AB2E4: dw 0x200000           ; DATA XREF: start+24?r
                                         ; start+7C?o
dword_800AB2E8: dw 0x8000             ; DATA XREF: start+4C?r
off_800AB2EC:   dw aBislpm86247       ; DATA XREF: sub_8004983C+22C?r
                                         ; sub_8004BA80+38?r
                                         ; "BISLPM-86247"
aMem:           db "mem:", 0x0         ; DATA XREF: sub_800148B8+88?o
                db 0, 0, 0
aPad:           db "pad:", 0x0         ; DATA XREF: sub_800148B8+9C?o
                db 0, 0, 0
aGv:            db "gv:", 0x0          ; DATA XREF: sub_800148B8+B0?o
aFs:            db "fs:", 0x0          ; DATA XREF: sub_800148B8+C4?o
aDg:            db "dg:", 0x0          ; DATA XREF: sub_800148B8+D8?o
aGcl:           db "gcl:", 0x0         ; DATA XREF: sub_800148B8+EC?o
                db 0, 0, 0
aHzd:           db "hzd:", 0x0         ; DATA XREF: sub_800148B8+100?o
                db 0, 0, 0
aSound:         db "sound:", 0x0       ; DATA XREF: sub_800148B8+114?o
                db 0
aGm:            db "gm:", 0x0          ; DATA XREF: sub_800148B8+160?o
aStart:         db "start", 0xA, 0x0      ; DATA XREF: sub_800148B8+174?o
                db 0
dword_800AB330: dw 0                  ; DATA XREF: sub_8001682C+38C?r
                                         ; sub_8001A0E4?r ...
                dw 0
aGvdC:          db "gvd.c", 0x0        ; DATA XREF: sub_80014D18+58?o
                dh 0
asc_800AB340:   db "#", 0x0            ; DATA XREF: sub_800151D8+54?o
                dh 0
aNone:          db "none", 0x0         ; DATA XREF: TEXT:off_800AB34C?o
                db 0, 0, 0
off_800AB34C:   dw aNone              ; DATA XREF: sub_80014B34+8?r
                                         ; "none"
aVoided:        db "voided ", 0x0      ; DATA XREF: TEXT:80015C68?o
                                         ; TEXT:80015DCC?o
aFailed:        db "failed ", 0x0      ; DATA XREF: TEXT:80015C88?o
                                         ; TEXT:80015DEC?o
asc_800AB360:   db ")", 0xA, 0x0          ; DATA XREF: TEXT:80015C94?o
                                         ; TEXT:80015DF8?o
                db 0
aStatic:        db "static ", 0x0      ; DATA XREF: TEXT:80015D9C?o
asc_800AB36C:   db "", 0xA, 0x0           ; DATA XREF: TEXT:80015E9C?o
                dh 0
                dw 0x80117000
dword_800AB374: dw 0                  ; DATA XREF: TEXT:8002C9A8?w
                                         ; sub_80042730+60?w
                dw 0
                dw 0
dword_800AB380: dw 0                  ; DATA XREF: sub_8001682C+30?r
                                         ; sub_8001844C+8?w ...
                dw 0xFFFFFFFF, 0
word_800AB38C:  dh 0                  ; DATA XREF: sub_8001D324+238?r
word_800AB38E:  dh 0                  ; DATA XREF: sub_8001D324+240?r
word_800AB390:  dh 0                  ; DATA XREF: sub_8001D324+248?r
                dh 0
dword_800AB394: dw 0x3C808080         ; DATA XREF: sub_8001D19C+30?o
                                         ; sub_80031BD4+5C?o
dword_800AB398: dw 0x3E808080         ; DATA XREF: sub_8001D19C+44?o
                                         ; sub_80031BD4+70?o
byte_800AB39C:  db 0                  ; DATA XREF: sub_80025A7C+1FC?o
                                         ; sub_8002DA14+40?o ...
                db 0, 0
byte_800AB39F:  db 0                  ; DATA XREF: sub_8002DA14+48?r
                                         ; sub_80033784+30C?r ...
byte_800AB3A0:  db 0                  ; DATA XREF: sub_8002DA14+54?r
                                         ; sub_80033784+318?r ...
                db 0, 0
byte_800AB3A3:  db 0                  ; DATA XREF: sub_8002DA14+50?r
                                         ; sub_80033784+314?r ...
                dw 0xFFFFFFFF
dword_800AB3A8: dw 0xE20300, 0x1E0100
                                         ; DATA XREF: sub_8001FC28+C?o
dword_800AB3B0: dw 0xC40300, 0x1E0100, 0
                                         ; DATA XREF: sub_8001FC58+C?o
dword_800AB3BC: dw 0, 0               ; DATA XREF: sub_80020228:loc_80020254?o
dword_800AB3C4: dw 0, 0               ; DATA XREF: sub_8002A7D8+C?o
                                         ; sub_8002A880?o
dword_800AB3CC: dw 0                  ; DATA XREF: sub_8001682C+44?r
                                         ; sub_8001682C+F8?r ...
dword_800AB3D0: dw 0                  ; DATA XREF: sub_8001FF2C+4?r
                                         ; TEXT:8002C450?w ...
dword_800AB3D4: dw 0                  ; DATA XREF: sub_800331A4+20?r
                                         ; sub_80037514+3C?w ...
                dw 0
dword_800AB3DC: dw 0                  ; DATA XREF: sub_8005AD10+3A0?r
                                         ; sub_8005AD10:loc_8005B198?r
dword_800AB3E0: dw 0                  ; DATA XREF: sub_8005AD10:loc_8005B1E0?r
                                         ; sub_8005AD10:loc_8005B214?r
word_800AB3E4:  dh 0                  ; DATA XREF: TEXT:80069AD0?w
                                         ; TEXT:80069B84?w ...
                dh 0xFFFF
dword_800AB3E8: dw 0                  ; DATA XREF: sub_8006641C+254?r
                                         ; TEXT:loc_800699A4?r
dword_800AB3EC: dw 0                  ; DATA XREF: TEXT:80069C34?r
                                         ; TEXT:80069D74?r
dword_800AB3F0: dw 0                  ; DATA XREF: sub_8006DDEC+13C?r
dword_800AB3F4: dw 0                  ; DATA XREF: sub_8004983C+38?w
                                         ; sub_8004983C+49C?w ...
aInit:          db "init", 0x0         ; DATA XREF: sub_8002AAB0+10?o
                db 0, 0, 0
dword_800AB400: dw 0                  ; DATA XREF: sub_8002AB40+C?o
aGamedC:        db "gamed.c", 0x0      ; DATA XREF: sub_8002B77C+7C?o
aGcawi:         db "gcawi", 0x0        ; DATA XREF: TEXT:8002C7D8?o
                dh 0
dword_800AB414: dw 0xFFFFFFFF         ; DATA XREF: sub_80079960+20?r
aPrint:         db "print: ", 0x0      ; DATA XREF: TEXT:8002D0F0?o
aS_2:           db "%s ", 0x0
aD_3:           db "%d ", 0x0          ; DATA XREF: TEXT:8002D14C?o
asc_800AB428:   db "", 0xA, 0x0           ; DATA XREF: TEXT:8002D168?o
                dh 0
dword_800AB42C: dw 0x2710             ; DATA XREF: sub_8006B800+68?r
                                         ; sub_8006B888+70?w
byte_800AB430:  db 0x80               ; DATA XREF: sub_8002FCF0+28?o
                                         ; sub_8002FCF0+34?r ...
                db 2, 0
byte_800AB433:  db 8                  ; DATA XREF: sub_8002FCF0+30?r
                                         ; sub_80030938+20?w
byte_800AB434:  db 0                  ; DATA XREF: sub_8002FCF0+3C?r
                                         ; sub_80030938+2C?w
                db 0, 0
byte_800AB437:  db 0                  ; DATA XREF: sub_8002FCF0+38?r
                                         ; sub_80030938+28?w
                dw 0x2710, 0, 0, 0, 0
aNoHzd:         db "no hzd", 0xA, 0x0     ; DATA XREF: sub_800310D0+68?o
aDelayC:        db "delay.c", 0x0      ; DATA XREF: sub_80033230+AC?o
dword_800AB45C: dw 0xFFFFFFFF         ; DATA XREF: sub_8002E688+1D0?w
aInit_0:        db "init", 0x0         ; DATA XREF: sub_80037514+A4?o
                db 0, 0, 0
aTitle:         db "title", 0x0        ; DATA XREF: sub_80037514:loc_800375C8?o
                dh 0
aOverC:         db "over.c", 0x0       ; DATA XREF: sub_800376F8+44?o
                db 0
aItem:          db "item", 0x0         ; DATA XREF: sub_8003884C+AC?o
                db 0, 0, 0
                dw 0xD, 0x5555, 0x3FFF, 0
dword_800AB490: dw 0x17E03E0, 0x20020
                                         ; DATA XREF: sub_8003A664+134?o
                                         ; sub_8003AA2C+38?o
dword_800AB498: dw 0x5FBF5FBE, 0x5FFF5FFE
                                         ; DATA XREF: sub_8003A664+268?o
dword_800AB4A0: dw 0x8D118C91, 0x9A238C91
                                         ; DATA XREF: sub_8003A664+90?o
dword_800AB4A8: dw 0x80238023, 0x8023, 0, 0
                                         ; DATA XREF: sub_8003A664+9C?o
aSuppr:         db "SUPPR.", 0x0
                db 0
aScarf:         db "SCARF", 0x0
                dh 0
aRope:          db "ROPE", 0x0
                db 0, 0, 0
aDisc:          db "DISC", 0x0
                db 0, 0, 0
aMineD:         db "MINE.D", 0x0
                db 0
aTimerB:        db "TIMER.B", 0x0
aCard:          db "CARD", 0x0
                db 0, 0, 0
aPalKey:        db "PAL KEY", 0x0
aRation:        db "RATION", 0x0
                db 0
aCamera:        db "CAMERA", 0x0
                db 0
aBandana:       db "BANDANA", 0x0
aStealth:       db "STEALTH", 0x0
aKetchup:       db "KETCHUP", 0x0
aBArmor:        db "B.ARMOR", 0x0
aGasmask:       db "GASMASK", 0x0
aThermG:        db "THERM.G", 0x0
aNVG:           db "N.V.G", 0x0
                dh 0
aCBoxC:         db "C.BOX C", 0x0
aCBoxB:         db "C.BOX B", 0x0
aCBoxA:         db "C.BOX A", 0x0
aScope:         db "SCOPE", 0x0
                dh 0
aCigs:          db "CIGS", 0x0         ; DATA XREF: TEXT:off_8009E484?o
                db 0, 0, 0
aLv:            db "LV.", 0x0          ; DATA XREF: sub_8003B8F0+14C?o
aNoItem:        db "NO ITEM", 0x0      ; DATA XREF: sub_8003B8F0+288?o
                dw 0, 0
aEquip:         db "EQUIP", 0x0        ; DATA XREF: sub_8003BF1C+2C0?o
                dh 0
                dw 0
aPsg1:          db "PSG1", 0x0
                db 0, 0, 0
aChaffG:        db "CHAFF.G", 0x0
aStunG:         db "STUN.G", 0x0
                db 0
                dw 0x3443, 0x4E495453, 0x524547, 0x494B494E, 0x4154
                dw 0x4E455247, 0x454441, 0x4D2D4146, 0x5341
aSocom:         db "SOCOM", 0x0        ; DATA XREF: TEXT:off_8009E57C?o
                dh 0
                dw 0x80011B04
aMp5Sd:         db "MP 5 SD", 0x0      ; DATA XREF: sub_8003E0E8+228?o
aNoItem_0:      db "NO ITEM", 0x0      ; DATA XREF: sub_8003E0E8+254?o
                dw 0, 0
aWeapon:        db "WEAPON", 0x0       ; DATA XREF: sub_8003E674+2A8?o
                db 0
aLife:          db "LIFE", 0x0         ; DATA XREF: TEXT:off_8009E5F4?o
                db 0, 0, 0
aO2:            db "O2", 0x0           ; DATA XREF: TEXT:off_8009E600?o
                db 0
                dw 0
dword_800AB600: dw 0x10003C0, 0x500032
                                         ; DATA XREF: sub_8003F84C+8?o
                                         ; sub_8003F84C+9C?o
dword_800AB608: dw 0x480056           ; DATA XREF: sub_8003F84C+60?o
                dw 0x48002C
dword_800AB610: dw 0x1030402, 0x10304
                                         ; DATA XREF: sub_8003FD50+9C?o
aCall:          db "call", 0x0         ; DATA XREF: sub_800403E4+4?o
                db 0, 0, 0
aP3t3t:         db "P#3T#3T", 0x0      ; DATA XREF: sub_800407A4+4C?o
aMemory:        db "MEMORY", 0x0       ; DATA XREF: sub_800407A4+88?o
                db 0
dword_800AB630: dw 0x10403C0, 0x4C003F, 0x36B0, 0, 0
                                         ; DATA XREF: sub_80040F74+34?o
                                         ; sub_80040F74+50?o
                dw 0xFFFFFFFF, 0
byte_800AB64C:  db 0xC0               ; DATA XREF: sub_80042848+18?o
                                         ; sub_80042848+20?r
                db 3, 0xE8
byte_800AB64F:  db 1                  ; DATA XREF: sub_80042848+1C?r
byte_800AB650:  db 0x40               ; DATA XREF: sub_80042848+28?r
                db 0, 0xA
byte_800AB653:  db 0                  ; DATA XREF: sub_80042848+24?r
dword_800AB654: dw 0x6D756E           ; DATA XREF: sub_80042848+4?o
dword_800AB658: dw 0x1F203C0          ; DATA XREF: sub_80043138+4C?o
dword_800AB65C: dw 0, 0, 0, 0, 0, 0   ; DATA XREF: sub_80043138:loc_80043164?o
aNoD:           db "No %d", 0xA, 0x0      ; DATA XREF: sub_800445F8+118?o
                db 0
aIdD:           db "ID %d", 0xA, 0x0      ; DATA XREF: sub_800445F8+164?o
                db 0
aColD:          db "COL %d", 0xA, 0x0     ; DATA XREF: sub_800445F8+174?o
dword_800AB68C: dw 0                  ; DATA XREF: sub_80038A88+88?w
                dw 0x786574
                dw 0x6A626F
                dw 0x796C70
                dw 0x776F70
                dw 0x6D656D
                dw 0, 0, 0
                dw 1, 0, 0, 0, 0, 0
byte_800AB6C8:  db 0                  ; DATA XREF: sub_800469F0+74?o
                                         ; sub_80046A98+1C?o ...
                db 3, 0
byte_800AB6CB:  db 1                  ; DATA XREF: sub_80046B74+18?r
                                         ; sub_80046BD8+24?r
byte_800AB6CC:  db 0                  ; DATA XREF: sub_800469F0:loc_80046A58?o
                                         ; sub_80046B74+24?r ...
                db 1, 4
byte_800AB6CF:  db 0                  ; DATA XREF: sub_80046B74+20?r
                                         ; sub_80046BD8+2C?r
dword_800AB6D0: dw 0x1500380          ; DATA XREF: sub_800469F0+88?o
                                         ; sub_80046A98+40?o
dword_800AB6D4: dw 0x600040           ; DATA XREF: sub_800469F0+80?o
byte_800AB6D8:  db 0xF0               ; DATA XREF: sub_80048124+1C?o
                                         ; sub_80048124+30?o ...
                db 3, 0xB0
byte_800AB6DB:  db 1                  ; DATA XREF: sub_80048124+38?r
byte_800AB6DC:  db 5                  ; DATA XREF: sub_80048124+44?r
                db 0, 0x14
byte_800AB6DF:  db 0                  ; DATA XREF: sub_80048124+40?r
                dw 0
aPause:         db "PAUSE", 0x0        ; DATA XREF: sub_80048FD4+230?o
                dh 0
                dw 0
                dw 0xFFFFFFFF, 0
                dw 0
                dw 0xFFFFFFFF, 0
aError:         db "ERROR", 0x0        ; DATA XREF: TEXT:8009EBCC?o
                dh 0
aDiscD:         db "DISC %d", 0x0      ; DATA XREF: sub_8004B0A0+370?o
aTime:          db "TIME", 0x0         ; DATA XREF: sub_8004B0A0+398?o
                db 0, 0, 0
aEx:            db "EX", 0x0           ; DATA XREF: TEXT:8009EBFC?o
                db 0
dword_800AB720: dw 0x4448             ; DATA XREF: TEXT:8009EBF8?o
dword_800AB724: dw 0x4D4E             ; DATA XREF: TEXT:8009EBF4?o
dword_800AB728: dw 0x5A45             ; DATA XREF: TEXT:off_8009EBF0?o
dword_800AB72C: dw 0x4556             ; DATA XREF: sub_8004B0A0+410?o
aClear_0:       db "CLEAR", 0x0        ; DATA XREF: sub_8004B0A0+494?o
                                         ; sub_8004B0A0+498?r ...
                dh 0
aS_1:           db "S", 0x0            ; DATA XREF: sub_8004B0A0+504?o
                                         ; sub_8004B0A0+784?o
                dh 0
byte_800AB73C:  db 0                  ; DATA XREF: sub_8004B0A0+50C?o
                                         ; sub_8004B0A0+78C?o ...
                db 0, 0, 0
aNoCard:        db "NO CARD", 0x0      ; DATA XREF: sub_8004BE98+D8?o
                                         ; sub_8004BE98+DC?r ...
aNoFile_0:      db "NO FILE", 0x0      ; DATA XREF: sub_8004C418+94?o
aNo:            db "NO", 0x0           ; DATA XREF: TEXT:8009EC0C?o
                db 0
dword_800AB754: dw 0x534559           ; DATA XREF: TEXT:off_8009EC08?o
aResD:          db "Res %d", 0xA, 0x0     ; DATA XREF: sub_8004C418+7F0?o
                                         ; sub_8004C418+83C?o ...
dword_800AB760: dw 0x4081             ; DATA XREF: sub_8004CF20+34?o
                                         ; sub_8004D008+E0?o
dword_800AB764: dw 0x2563250C, 0x73, 0x2A, 0
                                         ; DATA XREF: sub_8004D14C+5C?o
a03d:           db "%03d", 0x0         ; DATA XREF: sub_8004D628+19C?o
                db 0, 0, 0
a02d_0:         db "%02d", 0x0         ; DATA XREF: sub_8004D628+1F0?o
                db 0, 0, 0
aClear:         db "clear", 0x0        ; DATA XREF: sub_8004E110+44?o
                dh 0
                dw 0x16100602, 0x5958811A
                dw 0x160F0000, 0x29281F19
                dw 0x160F0501, 0x29281F19
                dw 0x16100303, 0x5958811A
                dw 0x16105A5A, 0x5958352B
                dw 0x554E4C4C, 0x29285719
                dw 0x64635F5F, 0x5958661A
                dw 0x541514, 0x3D4
dword_800AB7CC: dw 0x96, 0x32         ; DATA XREF: sub_8004E5E8+58?o
dword_800AB7D4: dw 0                  ; DATA XREF: sub_8004F090+1C?o
                dw 0x64
dword_800AB7DC: dw 0xFC00, 0          ; DATA XREF: sub_8004F090+2C?o
dword_800AB7E4: dw 0x1F40005, 0x50    ; DATA XREF: sub_80056DDC+248?o
dword_800AB7EC: dw 0                  ; DATA XREF: sub_800571B8+9C?o
                db 0x20, 3, 0, 0
dword_800AB7F4: dw 0x640000, 0xFED4   ; DATA XREF: sub_800571B8+13C?o
dword_800AB7FC: dw 0                  ; DATA XREF: sub_80058C80+94?o
                dw 0xFED4, 0x20646170, 0xA7825, 0x657A616B, 0xA20
aKage:          db "kage", 0x0         ; DATA XREF: sub_800601B0+1C?o
                db 0, 0, 0
aShadow_0:      db "shadow", 0x0       ; DATA XREF: sub_800601B0+9C?o
                db 0
                dw 0xFF29
dword_800AB828: dw 0                  ; DATA XREF: sub_80065B04+178?o
                dw 0x20002
aSocom_0:       db "socom", 0x0        ; DATA XREF: sub_80065B04+48?o
                dh 0
aSocom2:        db "socom2", 0x0       ; DATA XREF: sub_80065B04+70?o
                db 0
aLsight:        db "lsight", 0x0       ; DATA XREF: sub_80065B04+114?o
                db 0
aSocomC:        db "socom.c", 0x0      ; DATA XREF: sub_80065D74+5C?o
dword_800AB850: dw 0xFE0C0005, 0x50   ; DATA XREF: sub_80065E90+17C?o
aFamas:         db "famas", 0x0        ; DATA XREF: sub_800661A8+2C?o
                dh 0
aMpfive:        db "mpfive", 0x0       ; DATA XREF: sub_800661A8:loc_800661D8?o
                db 0
aFamasC:        db "famas.c", 0x0      ; DATA XREF: sub_8006623C+64?o
dword_800AB870: dw 0xFCE0FF9C, 0x50   ; DATA XREF: sub_80066BC0+1B8?o
dword_800AB878: dw 0x640064, 0xC800C8
                                         ; DATA XREF: sub_80066EB0+68?o
dword_800AB880: dw 0xFED4FFCE, 0x64   ; DATA XREF: sub_80066EB0+7C?o
aNikita:        db "nikita", 0x0       ; DATA XREF: sub_80066EB0+1C?o
                db 0
aRcmL_0:        db "rcm_l", 0x0        ; DATA XREF: sub_80066EB0+C0?o
                dh 0
aRcmC:          db "rcm.c", 0x0        ; DATA XREF: sub_80066FF0+5C?o
                dh 0
                dw 0
dword_800AB8A4: dw 0xC8FED4, 0        ; DATA XREF: sub_800670CC+1E0?o
aStinger_0:     db "stinger", 0x0      ; DATA XREF: sub_800673F0+1C?o
aAamC:          db "aam.c", 0x0        ; DATA XREF: sub_80067480+5C?o
                dh 0
aMineC:         db "mine.c", 0x0       ; DATA XREF: sub_800677BC+5C?o
                db 0
aC4Bomb:        db "c4_bomb", 0x0      ; DATA XREF: sub_80067A94+1C?o
aBombC:         db "bomb.c", 0x0       ; DATA XREF: sub_80067B20+5C?o
                db 0
dword_800AB8D4: dw 0x12C0005, 0x50    ; DATA XREF: sub_80067D60+2BC?o
aRifle_0:       db "rifle", 0x0        ; DATA XREF: sub_80068184+1C?o
                dh 0
aRifleC:        db "rifle.c", 0x0      ; DATA XREF: sub_80068214+5C?o
dword_800AB8EC: dw 0                  ; DATA XREF: sub_80068D0C+70?o
                                         ; sub_80068D0C+A8?o
a0D:            db "-0%d", 0x0         ; DATA XREF: sub_80068420+254?o
                db 0, 0, 0
a0D_0:          db "0%d", 0x0          ; DATA XREF: sub_80068420+268?o
aD_2:           db "%d", 0x0           ; DATA XREF: sub_80068420:loc_8006868C?o
                db 0
aDD:            db "%d %d", 0xA, 0x0      ; DATA XREF: sub_80068A24+174?o
                db 0
aStinger:       db "stinger", 0x0      ; DATA XREF: sub_80068D0C+50?o
aRifle:         db "rifle", 0x0        ; DATA XREF: sub_800696CC:loc_80069704?o
                                         ; sub_800696CC+84?o
                dh 0
dword_800AB918: dw 0                  ; DATA XREF: start?o
dword_800AB91C: dw 0                  ; DATA XREF: sub_8001F078+110?w
                                         ; sub_8001F078+12C?w
dword_800AB920: dw 0                  ; DATA XREF: sub_80017194+10?r
                                         ; sub_800172A8?r ...
dword_800AB924: dw 0                  ; DATA XREF: sub_8002ADBC+178?r
                                         ; sub_8005D424+1C?r
dword_800AB928: dw 0                  ; DATA XREF: TEXT:loc_80014BAC?r
                                         ; sub_80016620?r ...
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
dword_800AB940: dw 0                  ; DATA XREF: sub_80014C70+38?r
                                         ; sub_8002B710+1C?r
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
dword_800AB960: dw 0, 0               ; DATA XREF: sub_80017194+84?o
dword_800AB968: dw 0                  ; DATA XREF: sub_800189A4+38?r
                                         ; sub_8001B66C+54?r ...
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
word_800AB980:  dh 0                  ; DATA XREF: sub_80043A24+28?r
                                         ; sub_80043A24+178?r ...
word_800AB982:  dh 0                  ; DATA XREF: sub_80043A24+3B0?r
                                         ; sub_80043A24+4AC?r
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
dword_800AB9A0: dw 0                  ; DATA XREF: TEXT:8005D560?r
                dw 0
dword_800AB9A8: dw 0                  ; DATA XREF: sub_80028454+3C?r
                                         ; sub_80030C6C+17C?w ...
                dw 0
dword_800AB9B0: dw 0                  ; DATA XREF: sub_80014F88:loc_80014FDC?w
                                         ; TEXT:8002C8E8?w ...
dword_800AB9B4: dw 0                  ; DATA XREF: sub_800391D0:loc_800393DC?r
                dw 0, 0, 0, 0
dword_800AB9C8: dw 0                  ; DATA XREF: sub_800163D8+10?r
                                         ; sub_80022E50:loc_80022F28?r ...
                dw 0, 0
dword_800AB9D4: dw 0                  ; DATA XREF: sub_800596FC+14C0?w
                                         ; sub_8005AD10+58?w
word_800AB9D8:  dh 0                  ; DATA XREF: sub_8003E3B0+64?w
                                         ; sub_8003E3B0+C0?w ...
                dh 0
dword_800AB9DC: dw 0                  ; DATA XREF: sub_8006DFDC+70?w
                                         ; sub_8006E0F0+80?w ...
                dw 0
dword_800AB9E4: dw 0                  ; DATA XREF: TEXT:8002CD5C?w
                                         ; sub_8003DF30:loc_8003E018?r
dword_800AB9E8: dw 0                  ; DATA XREF: sub_80020C0C+40?r
                                         ; sub_80020EAC+7C?w ...
word_800AB9EC:  dh 0                  ; DATA XREF: sub_8003E0E8+1E4?r
                                         ; sub_80057A90+A4?w ...
                dh 0
dword_800AB9F0: dw 0                  ; DATA XREF: sub_800559D8+60?r
                                         ; sub_800559D8+228?r ...
dword_800AB9F4: dw 0                  ; DATA XREF: TEXT:8002CE44?r
                                         ; sub_80033784:loc_80033D58?r ...
byte_800AB9F8:  db 0                  ; DATA XREF: sub_80054EFC+24C?o
                                         ; sub_80054EFC+268?w ...
                db 0, 0
byte_800AB9FB:  db 0                  ; DATA XREF: sub_80054EFC+264?w
                                         ; sub_800591F4+114?w ...
byte_800AB9FC:  db 0                  ; DATA XREF: sub_80054EFC+270?w
                                         ; sub_800591F4+120?w ...
                db 0, 0
byte_800AB9FF:  db 0                  ; DATA XREF: sub_80054EFC+26C?w
                                         ; sub_800591F4+11C?w ...
dword_800ABA00: dw 0                  ; DATA XREF: sub_8002E640+10?r
                                         ; sub_8002E91C+2C?r ...
dword_800ABA04: dw 0                  ; DATA XREF: TEXT:loc_8002CEF0?w
                                         ; sub_800649F4+1C?r ...
                dw 0
dword_800ABA0C: dw 0                  ; DATA XREF: sub_8002D208+C4?r
                                         ; sub_8002D300+BC?r ...
word_800ABA10:  dh 0                  ; DATA XREF: sub_800321F8+1C?o
                                         ; sub_800321F8+90?o ...
byte_800ABA12:  db 0                  ; DATA XREF: sub_8003C4EC+328?r
                                         ; sub_80066BC0+1D0?r
byte_800ABA13:  db 0                  ; DATA XREF: sub_800335D0+24?r
                                         ; sub_8005AD10+6F8?w ...
word_800ABA14:  dh 0                  ; DATA XREF: sub_800335D0+30?r
                                         ; sub_8003C4EC+330?r ...
                db 0
byte_800ABA17:  db 0                  ; DATA XREF: sub_800335D0+2C?r
                                         ; sub_8005AD10+700?w ...
dword_800ABA18: dw 0                  ; DATA XREF: sub_8002E91C+110?r
                                         ; sub_8003AEC0+14?r
dword_800ABA1C: dw 0                  ; DATA XREF: sub_80050440+A4?w
                                         ; sub_80050440+E4?w ...
dword_800ABA20: dw 0                  ; DATA XREF: sub_8005B52C:loc_8005B618?r
                                         ; sub_8005B52C+100?w ...
dword_800ABA24: dw 0                  ; DATA XREF: sub_8002F78C:loc_8002F99C?r
                                         ; sub_80054EFC+204?r ...
dword_800ABA28: dw 0                  ; DATA XREF: TEXT:8002CD7C?w
                                         ; sub_8003B6D0:loc_8003B77C?r
word_800ABA2C:  dh 0                  ; DATA XREF: sub_8003E0E8+1B0?r
                                         ; sub_80057A90+7C?r ...
                dh 0
dword_800ABA30: dw 0                  ; DATA XREF: sub_8002F78C+240?r
                                         ; sub_8002F78C+278?r ...
word_800ABA34:  dh 0                  ; DATA XREF: sub_8003F30C+CC?r
                                         ; sub_8003F530+24?r ...
                dh 0
dword_800ABA38: dw 0                  ; DATA XREF: sub_8002E41C+34?w
                                         ; sub_8002E460+98?w ...
dword_800ABA3C: dw 0                  ; DATA XREF: sub_8005D424+A4?r
                                         ; sub_8005D424+B4?w ...
dword_800ABA40: dw 0                  ; DATA XREF: sub_800596FC+14B0?w
                dw 0
dword_800ABA48: dw 0, 0               ; DATA XREF: TEXT:8002CEC8?o
                                         ; sub_800649F4+50?o
dword_800ABA50: dw 0                  ; DATA XREF: sub_8001F078+FC?r
                                         ; sub_8001FF2C+20?r ...
dword_800ABA54: dw 0                  ; DATA XREF: sub_8002E390+40?w
                                         ; sub_8005D424+C0?r ...
dword_800ABA58: dw 0, 0, 0, 0, 0, 0, 0, 0
                                         ; DATA XREF: TEXT:8002C360?o
                                         ; TEXT:8002C3A0?o
dword_800ABA78: dw 0, 0, 0, 0         ; DATA XREF: sub_8002E640+18?o
byte_800ABA88:  db 0                  ; DATA XREF: sub_8002F78C+D0?o
                                         ; sub_8002F78C+F0?o ...
                db 0, 0
byte_800ABA8B:  db 0                  ; DATA XREF: sub_8002F78C+10C?w
                                         ; TEXT:80030658?w ...
byte_800ABA8C:  db 0                  ; DATA XREF: sub_8002F78C+118?w
                                         ; TEXT:80030664?w ...
                db 0, 0
byte_800ABA8F:  db 0                  ; DATA XREF: sub_8002F78C+114?w
                                         ; TEXT:80030660?w ...
                dw 0, 0, 0
dword_800ABA9C: dw 0                  ; DATA XREF: sub_8006B800+6C?r
                                         ; sub_8006B888+80?w
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                dw 0, 0, 0, 0, 0, 0, 0, 0, 0
dword_800ABB08: dw 0                  ; DATA XREF: sub_80042198+464?r
                                         ; sub_80042198+4A0?r ...
dword_800ABB0C: dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                                         ; DATA XREF: sub_80042198+458?o
                dw 0, 0, 0, 0
dword_800ABB60: dw 0, 0               ; DATA XREF: sub_80049EDC+4C?o
                                         ; sub_80049EDC+13C?o ...
dword_800ABB68: dw 0, 0               ; DATA XREF: sub_80049EDC+3A4?o
                                         ; sub_80049EDC+478?o ...
dword_800ABB70: dw 0                  ; DATA XREF: sub_8004C418:loc_8004C75C?o
dword_800ABB74: dw 0                  ; DATA XREF: sub_8004C418+3F0?o
                                         ; sub_8004C418:loc_8004C970?o
dword_800ABB78: dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                                         ; DATA XREF: sub_8004C418+62C?o
dword_800ABBB8: dw 0, 0, 0, 0, 0, 0, 0
                                         ; DATA XREF: TEXT:8004FB90?o
                                         ; sub_8005AD10+3E8?o
word_800ABBD4:  dh 0                  ; DATA XREF: sub_800626D0+38?r
                                         ; sub_800626D0:loc_800627C0?r ...
                dh 0
dword_800ABBD8: dw 0                  ; DATA XREF: sub_80067558+10C?r
                                         ; sub_8006788C+110?r
word_800ABBDC:  dh 0                  ; DATA XREF: sub_800626D0+24?r
                                         ; sub_800626D0+D8?r ...
                dh 0
dword_800ABBE0: dw 0, 0               ; DATA XREF: sub_800696CC+A4?o
                                         ; sub_800696CC+CC?o ...
dword_800ABBE8: dw 0                  ; DATA XREF: start+74?w
                                         ; start+90?r
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
                dw 0
