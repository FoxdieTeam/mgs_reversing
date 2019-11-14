	opt	c+, at+, e+, n-

	section	.sdata_asm

	xref aBislpm86247
	
	xdef aError
	xdef dword_800AB728
	xdef dword_800AB724
	xdef dword_800AB720
	xdef aEx
	xdef dword_800AB754
	xdef aNo
	

dword_800AB600: dw 0x10003C0, 0x500032
dword_800AB608: dw 0x480056           ; DATA XREF: sub_8003F84C+60?o
                dw 0x48002C
dword_800AB610: dw 0x1030402, 0x10304
aCall:          db "call", 0x0         ; DATA XREF: sub_800403E4+4?o
                db 0, 0, 0
aP3t3t:         db "P#3T#3T", 0x0      ; DATA XREF: sub_800407A4+4C?o
aMemory:        db "MEMORY", 0x0       ; DATA XREF: sub_800407A4+88?o
                db 0
dword_800AB630: dw 0x10403C0, 0x4C003F, 0x36B0, 0, 0
                dw 0xFFFFFFFF, 0
byte_800AB64C:  db 0xC0               ; DATA XREF: sub_80042848+18?o
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
                db 3, 0
byte_800AB6CB:  db 1                  ; DATA XREF: sub_80046B74+18?r
byte_800AB6CC:  db 0                  ; DATA XREF: sub_800469F0:loc_80046A58?o
                db 1, 4
byte_800AB6CF:  db 0                  ; DATA XREF: sub_80046B74+20?r
dword_800AB6D0: dw 0x1500380          ; DATA XREF: sub_800469F0+88?o
dword_800AB6D4: dw 0x600040           ; DATA XREF: sub_800469F0+80?o
byte_800AB6D8:  db 0xF0               ; DATA XREF: sub_80048124+1C?o
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
                dh 0
aS_1:           db "S", 0x0            ; DATA XREF: sub_8004B0A0+504?o
                dh 0
byte_800AB73C:  db 0                  ; DATA XREF: sub_8004B0A0+50C?o
                db 0, 0, 0
aNoCard:        db "NO CARD", 0x0      ; DATA XREF: sub_8004BE98+D8?o
aNoFile_0:      db "NO FILE", 0x0      ; DATA XREF: sub_8004C418+94?o
aNo:            db "NO", 0x0           ; DATA XREF: TEXT:8009EC0C?o
                db 0
dword_800AB754: dw 0x534559           ; DATA XREF: TEXT:off_8009EC08?o
aResD:          db "Res %d", 0xA, 0x0     ; DATA XREF: sub_8004C418+7F0?o
dword_800AB760: dw 0x4081             ; DATA XREF: sub_8004CF20+34?o
dword_800AB764: dw 0x2563250C, 0x73, 0x2A, 0
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
a0D:            db "-0%d", 0x0         ; DATA XREF: sub_80068420+254?o
                db 0, 0, 0
a0D_0:          db "0%d", 0x0          ; DATA XREF: sub_80068420+268?o
aD_2:           db "%d", 0x0           ; DATA XREF: sub_80068420:loc_8006868C?o
                db 0
aDD:            db "%d %d", 0xA, 0x0      ; DATA XREF: sub_80068A24+174?o
                db 0
aStinger:       db "stinger", 0x0      ; DATA XREF: sub_80068D0C+50?o
aRifle:         db "rifle", 0x0        ; DATA XREF: sub_800696CC:loc_80069704?o
