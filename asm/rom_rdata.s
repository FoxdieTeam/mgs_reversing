	opt	c+, at+, e+, n-

	section	.RDATA

    xdef aComplete
    xdef aMemoryCard1
    xdef aMemoryCard2
    xdef dword_800122D8
    xdef dword_800122CC
    xdef dword_800122C0
    xdef dword_800122B4
    xdef dword_800122A8
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




                                         ; DATA XREF: sub_80022B5C+E4?o
aXXD:           db "%X %X %d", 0xA, 0x0   ; DATA XREF: sub_80022D00:loc_80022D74?o
                dh 0
aDCCD:          db "%d %c %c %d", 0xA, 0x0
                db 0, 0, 0
aHere:          db "HERE !!", 0xA, 0x0
                db 0, 0, 0
aWrongMode02xC: db "WRONG mode %02X (%c)", 0xA, 0x0
                                         ; DATA XREF: sub_80022E50+320?o
                dh 0
aWrongD:        db "!!! WRONG %d !!!", 0xA, 0x0
                                         ; DATA XREF: sub_800231A8+54?o
                dh 0
aNtagXSizeD:    db "ntag %X size %d", 0xA, 0x0
                                         ; DATA XREF: sub_80023460+9C?o
                db 0, 0, 0
aLimitX:        db "limit = %X", 0xA, 0x0
                                         ; DATA XREF: sub_80023460+AC?o
aDataXCNowX:    db "data %X %c, now %X", 0xA, 0x0
                                         ; DATA XREF: sub_80023460+D0?o
aInitXCNowX:    db "init %X %c, now %X", 0xA, 0x0
                                         ; DATA XREF: sub_80023460+E8?o
aLoadS:         db "load %s", 0xA, 0x0    ; DATA XREF: sub_800236E0+C?o
                db 0, 0, 0
aNotFoundS:     db "NOT FOUND %s", 0xA, 0x0
                                         ; DATA XREF: sub_800236E0+5C?o
                dh 0
aNo         db "no_mem", 0xA, 0x0     ; DATA XREF: sub_800236E0+80?o
aLoadCompleteTi:db "load complete time %d", 0xA, 0x0
                                         ; DATA XREF: sub_80023804+24?o
                db 0
aMovieFileIsWro:db "movie file is wrong", 0xA, 0x0
                                         ; DATA XREF: sub_80023860+34?o
                db 0, 0, 0
aMovieNumD:     db "MOVIE NUM %d", 0xA, 0x0
                                         ; DATA XREF: sub_80023860+80?o
                dh 0
aTablenumDSizeD:db "tablenum %d size %d", 0xA, 0x0
                                         ; DATA XREF: sub_80023860+BC?o
                db 0, 0, 0
aIdDFrameDPosD: db "id %d frame %d pos %d", 0xA, 0x0
                                         ; DATA XREF: sub_80023860+EC?o
                db 0
aStreamInitXX:  db "stream init %X %X", 0xA, 0x0
                                         ; DATA XREF: sub_80023FD4+24?o
                db 0
aClearX:        db "clear %X", 0xA, 0x0
                dh 0
aNowDataTopXLoa:db "now_data_top %X loaded_header %X", 0xA, 0x0
                                         ; DATA XREF: TEXT:800242C4?o
                dh 0
aTickD:         db "Tick %d", 0xA, 0x0    ; DATA XREF: TEXT:800242E4?o
                db 0, 0, 0
a08xTypeXSizeDT:db "%08X TYPE %X size %d time %d", 0xA, 0x0
                                         ; DATA XREF: TEXT:80024338?o
                dh 0
a08xTypeXSizeD: db "%08X TYPE %X size %d", 0xA, 0x0
                                         ; DATA XREF: TEXT:loc_80024360?o
                dh 0
dword_800107C4: dw 0x5D525B           ; DATA XREF: sub_800246C0+34?o
                                         ; sub_80024A54+68?o ...
aAccessWait:    db "ACCESS WAIT..", 0xA, 0x0
                                         ; DATA XREF: sub_800246C0+48?o
                                         ; sub_80024A54+7C?o ...
                db 0
aHwCardError:   db "*** hw card error", 0xA, 0x0
                                         ; DATA XREF: sub_80024524+10?o
                db 0
aCHTO:          db "[C.H.T.O]", 0x0    ; DATA XREF: sub_8002455C+10?o
                dh 0
aHwCardNew:     db "*** hw card new", 0xA, 0x0
                                         ; DATA XREF: sub_80024594+10?o
                db 0, 0, 0
aSwCardError:   db "*** sw card error", 0xA, 0x0
                                         ; DATA XREF: sub_800245F4+10?o
                db 0
aCSTO:          db "[C.S.T.O]", 0x0    ; DATA XREF: sub_8002462C+10?o
                dh 0
aSwCardNew:     db "*** sw card new", 0xA, 0x0
                                         ; DATA XREF: sub_80024664+10?o
                db 0, 0, 0
aEasyFormatTest:db "easy_format_test", 0xA, 0x0
                                         ; DATA XREF: sub_800246C0+18?o
                dh 0
aCardError:     db "card_error", 0xA, 0x0
                                         ; DATA XREF: sub_800246C0+CC?o
aCardNormal:    db "card_normal", 0xA, 0x0
                                         ; DATA XREF: sub_800246C0+100?o
                db 0, 0, 0
aCardUnformat:  db "card_unformat", 0xA, 0x0
                                         ; DATA XREF: sub_800246C0+110?o
                db 0
aBu02x:         db "bu%02X:*", 0x0     ; DATA XREF: sub_800247E8+28?o
                db 0, 0, 0
aLoadDirSStart: db "load_dir %s start", 0xA, 0x0
                                         ; DATA XREF: sub_800247E8+4C?o
                db 0
aTotalDFilesUse:db "TOTAL %d FILES used %d block", 0xA, 0x0
                                         ; DATA XREF: sub_800247E8+118?o
                dh 0
aNoFile:        db "NO FILE", 0xA, 0x0    ; DATA XREF: sub_800247E8+140?o
                db 0, 0, 0
aMemcardRetryOv:db "MEMCARD:RETRY OVER!!", 0xA, 0x0
                                         ; DATA XREF: sub_80024A54+E8?o
                dh 0
aRetryNew:      db "RETRY(new)", 0xA, 0x0
                                         ; DATA XREF: sub_80024A54+3B8?o
aRetry:         db "RETRY", 0xA, 0x0      ; DATA XREF: sub_80024A54+3C8?o
                db 0
aBu02xS:        db "bu%02X:%s", 0x0    ; DATA XREF: sub_800253C4+4C?o
                                         ; sub_8002554C+40?o
                dh 0
aDeletedFileS:  db "Deleted File %s", 0x0
                                         ; DATA XREF: sub_800253C4+70?o
aErrorCanTDelet:db "ERROR : can't delete %s", 0xA, 0x0
                                         ; DATA XREF: sub_800253C4:loc_80025448?o
                db 0, 0, 0
aMemcardReadWri:db "MEMCARD READ/WRITE end", 0xA, 0x0
                                         ; DATA XREF: sub_800254D4+18?o
aErrorMemcardRe:db "ERROR : MEMCARD READ/WRITE", 0xA, 0x0
                                         ; DATA XREF: sub_800254D4:loc_800254F0?o
aWarningMemcard:db "Warning : MEMCARD create error ... overwrite", 0xA, 0x0
                                         ; DATA XREF: sub_8002554C+78?o
                dh 0
aMemcardWriteEr:db "MEMCARD WRITE ERROR FD %d", 0xA, 0x0
                                         ; DATA XREF: sub_8002554C+9C?o
                db 0
aMemcardWriteSF:db "MEMCARD WRITE %s FD %d SIZE %d", 0xA, 0x0
                                         ; DATA XREF: sub_8002554C:loc_8002560C?o
aWritingFileS:  db "WRITING FILE %s...", 0xA, 0x0
                                         ; DATA XREF: sub_8002554C+120?o
aBu02xS_0:      db "bu%02x:%s", 0x0    ; DATA XREF: sub_8002569C+24?o
                dh 0
aMemcardReadErr:db "MEMCARD READ ERROR FD %d", 0xA, 0x0
                                         ; DATA XREF: sub_8002569C+5C?o
                dh 0
aMemcardReadSFd:db "MEMCARD READ %s FD %d SIZE %d", 0xA, 0x0
                                         ; DATA XREF: sub_8002569C+94?o
                db 0
aReadingFileS:  db "READING FILE %s...", 0xA, 0x0
                                         ; DATA XREF: sub_8002569C+E4?o
aBu02x_0:       db "bu%02x:", 0x0      ; DATA XREF: sub_800257C0+18?o
aFormatedD:     db "FORMATED %d", 0xA, 0x0
                                         ; DATA XREF: sub_800257C0+74?o
                db 0, 0, 0
aErrorMemcardFo:db "ERROR : MEMCARD FORMAT", 0xA, 0x0
                                         ; DATA XREF: sub_800257C0+C8?o
aErrorMemcardFo_0:db "ERROR : MEMCARD FORMATED CARD", 0xA, 0x0
                                         ; DATA XREF: sub_800257C0:loc_8002588C?o
                db 0
aInitcontrolNoM:db "InitControl : no map %X", 0xA, 0x0
                                         ; DATA XREF: sub_8002599C+48?o
                db 0, 0, 0
aExecScenario:  db "exec scenario", 0xA, 0x0
                                         ; DATA XREF: sub_8002ADBC+2A0?o
                db 0
aEndScenario:   db "end scenario", 0xA, 0x0
                                         ; DATA XREF: sub_8002ADBC+2D8?o
                dh 0
aCdromMgsS1:    db "cdrom:\\MGS\\%s;1", 0x0
                                         ; DATA XREF: sub_8002ADBC+508?o
aLoadS_0:       db "load %s", 0xA, 0x0    ; DATA XREF: sub_8002ADBC+5BC?o
                db 0, 0, 0
aStrStatusDIrqX:db "str_status %d irq %x %X %X", 0xA, 0x0
                                         ; DATA XREF: sub_8002ADBC+68C?o
aKey08x:        db "key %08X", 0xA, 0x0   ; DATA XREF: sub_8002ADBC+698?o
                dh 0
aTooLargeStageB:db "TOO LARGE STAGE BINARY!!", 0xA, 0x0
                                         ; DATA XREF: sub_8002B710+3C?o
                dh 0
aSetCameraD:    db "set camera %d", 0xA, 0x0
                                         ; DATA XREF: TEXT:8002BA2C?o
                db 0
aBindsOver:     db "binds over", 0xA, 0x0
                                         ; DATA XREF: TEXT:8002BD5C?o
                                         ; TEXT:8002BE48?o
aNtrapCanTSetEv:db "ntrap:can't set every", 0xA, 0x0
                                         ; DATA XREF: TEXT:8002BFB0?o
                db 0
aNtrapCanTSetPr:db "ntrap:can't set proc and block", 0xA, 0x0
                                         ; DATA XREF: TEXT:8002BFF8?o
aBind08x:       db "BIND %08X", 0xA, 0x0  ; DATA XREF: TEXT:loc_8002C020?o
                db 0
aMenuInitEnd:   db "MENU INIT END", 0xA, 0x0
                                         ; DATA XREF: TEXT:8002C26C?o
                db 0
aWrongCodeForRa:db "Wrong Code for radio over", 0xA, 0x0
                                         ; DATA XREF: TEXT:8002C540?o
                db 0
aVarsaveNotVar: db "VARSAVE: NOT VAR !!", 0xA, 0x0
                db 0, 0, 0
aSystemCChangeP:db "SYSTEM:%c:change proc name", 0xA, 0x0
aDemoNoCode:    db "DEMO:NO CODE", 0xA, 0x0
                                         ; DATA XREF: TEXT:8002C8B4?o
                dh 0
aDemoNoDataOnCd:db "DEMO ( no data on CD )", 0x0
                                         ; DATA XREF: TEXT:loc_8002C960?o
                db 0
aErrorDemoThrea:db "Error demo thread", 0xA, 0x0
                                         ; DATA XREF: TEXT:8002D0C0?o
                db 0
aLoadend:       db "LoadEnd", 0xA, 0x0    ; DATA XREF: sub_8002E41C+18?o
                db 0, 0, 0
aLoadreq:       db "LoadReq", 0xA, 0x0    ; DATA XREF: sub_8002E460+20?o
                db 0, 0, 0
aNotFoundStageS:db "NOT FOUND STAGE %s", 0xA, 0x0
                                         ; DATA XREF: sub_8002E460+40?o
aLoaderC:       db "loader.c", 0x0     ; DATA XREF: sub_8002E460+6C?o
                db 0, 0, 0
dword_80010C60: dw 0                  ; DATA XREF: sub_8002FD9C+330?o
                dw 0x1E0001, 0x1E0002, 0x1E0003, 0x140003, 0xA0003
                dw 0x50003, 0x30003, 0x5D64255B, 0x206D6163, 0x2074756F
                dw 0xA6425, 0x5D64255B, 0x206D6163, 0x25206E69, 0xA64
aDChangeCameraD:db "[%d]change camera %d", 0xA, 0x0
                                         ; DATA XREF: sub_80030250+118?o
                dh 0
aCameraC:       db "camera.c", 0x0     ; DATA XREF: sub_800306A0+3C?o
                db 0, 0, 0
aSetMapD:       db "set map %d", 0xA, 0x0
                                         ; DATA XREF: sub_80031244+14?o
aAddMapD:       db "add map %d", 0xA, 0x0
aAddmapNotFound:db "addmap : not found map %d", 0xA, 0x0
                                         ; DATA XREF: sub_80031324:loc_80031394?o
                db 0
aDelMapD:       db "del map %d", 0xA, 0x0
aDelmapNotFound:db "delmap: not found map %d", 0xA, 0x0
                                         ; DATA XREF: sub_800313C0:loc_80031428?o
                dh 0
aReshadeNullMap:db "Reshade NULL map", 0xA, 0x0
                                         ; DATA XREF: sub_80031660+30?o
                dh 0
aHomingTargetOv:db "Homing target over !!!", 0xA, 0x0
                                         ; DATA XREF: TEXT:80032CE4?o
aFull:          db "FULL", 0x0         ; DATA XREF: sub_80033784+554?o
                db 0, 0, 0
aGetWeaponFirst:db "GET WEAPON FIRST", 0x0
                                         ; DATA XREF: sub_80033784+570?o
                db 0, 0, 0
dword_80010D68: dw 0x7325             ; DATA XREF: sub_80033784+798?o
dword_80010D6C: dw 0x80034090         ; DATA XREF: sub_80034020+20?o
                dw 0x800340B8         ; jump table for switch statement
                dw 0x80034060
                dw 0x80034060
                dw 0x800340A4
                dw 0x800340B8
aNoIdItem:      db "NO ID ITEM", 0xA, 0x0
                                         ; DATA XREF: sub_800340D0+E0?o
aShadow:        db "shadow", 0x0       ; DATA XREF: sub_800340D0+378?o
                db    0
aItemC:         db "item.c", 0x0       ; DATA XREF: TEXT:80034544?o
                                         ; TEXT:800347AC?o
                db    0
aItemMapD:      db "Item map = %d", 0xA, 0x0
                                         ; DATA XREF: TEXT:loc_80034580?o
                db    0
aDoublePcm:     db "Double Pcm !!", 0xA, 0x0
                                         ; DATA XREF: sub_80037820+198?o
                db 0
aWrongTypeHeade:db "??? WRONG TYPE HEADER!!", 0xA, 0x0
                                         ; DATA XREF: sub_80037820+1FC?o
                db 0, 0, 0
aStreamplayEnd: db "StreamPlay end", 0xA, 0x0
                                         ; DATA XREF: sub_80037820+288?o
aNewstreamD:    db "NewStream %d", 0xA, 0x0
                                         ; DATA XREF: sub_80037B64+1C?o
                dh 0
aPend:          db "pend!!", 0xA, 0x0     ; DATA XREF: sub_80037B64+50?o
aStrctrlC:      db "strctrl.c", 0x0    ; DATA XREF: sub_80037B64+EC?o
                dh 0
aStreamIsNotRea:db "stream is not ready", 0xA, 0x0
                                         ; DATA XREF: sub_80037D1C+34?o
                db 0, 0, 0
aGmStreamplayst:db "GM_StreamPlayStop", 0xA, 0x0
                                         ; DATA XREF: sub_80037D64+10?o
                db 0
aVoxstreamD:    db "VoxStream %d", 0xA, 0x0
                                         ; DATA XREF: sub_80037E40:loc_80037E80?o
                dh 0
aKutipakuEnd:   db "KUTIPAKU END", 0xA, 0x0
                                         ; DATA XREF: sub_80038070+378?o
                dh 0
jpt_800383D8:   dw 0x800383E0         ; DATA XREF: sub_80038070+2F8?o
                dw 0x80038400         ; jump table for switch statement
                dw 0x80038428
                dw 0x800384D8
                dw 0x80038458
                dw 0x80038464
                dw 0x8003849C
aJimctrlC:      db "jimctrl.c", 0x0    ; DATA XREF: sub_80038568+C0?o
                dh 0
aMenumanC:      db "menuman.c", 0x0    ; DATA XREF: sub_80038954+30?o
                                         ; sub_80038A20+38?o
                dh 0
aMenuPrimOver:  db "!!!! MENU PRIM OVER !!!!", 0xA, 0x0
                                         ; DATA XREF: sub_80038A88+38?o
                dh 0
                dw 0x158214B0, 0x4C823782, 0x158223C2, 0x15D006D0, 0x1D827C80
                dw 0x138206D0, 0x34824082, 0x28821982, 0xF2904B82, 0x2E814990
                dw 0x37821582, 0x23C24C82, 0x6D01582, 0x1D8203D0, 0x138206D0
                dw 0x34824082, 0x28821982, 0x2E814B82, 0x8C907E90, 0x5281F390
                dw 0x881F490, 0x3D04B81, 0
                dw 0x2F8214B0, 0xB825382, 0x15D02182, 0x19827C80, 0x4822A82
                dw 0x6D03182, 0x6827FC0, 0x35824B82, 0x2F822E81, 0xB825382
                dw 0x3D02182, 0x19810B81, 0x2B810B81, 0xF190F090, 0x78902E81
                dw 0xC810481, 0x4B811981, 0x3D0, 0x4D8214B0, 0x378206D0
                dw 0x7C8015D0, 0xF817390, 0x74902681, 0x2A817590, 0x6D04D82
                dw 0x3D03782, 0x4822A82, 0x53824D82, 0xD190D090, 0x3D0EF90
                dw 0
                dw 0x4A9014B0, 0x3C22782, 0xF821982, 0x7C8015D0, 0x1F824182
                dw 0xE824B82, 0x2E810282, 0x71907090, 0x6D02782, 0xC811F82
                dw 0x41817290, 0x4C814981, 0x4812681, 0x28814B81, 0x6810481
                dw 0x27824A90, 0x198203C2, 0x3D00F82, 0
                dw 0x6A9014B0, 0x6C906B90, 0x6E906D90, 0x7C8015D0, 0x94909390
                dw 0x4B811981, 0x2D02881, 0x9D90EB90, 0x4C811581, 0x6A901F81
                dw 0x2E816B90, 0x9E90EC90, 0x4C820C81, 0x208206D0, 0x2B8106D0
                dw 0xEE90ED90, 0x4C811581, 0x3D04B81, 0
                dw 0x3FC014B0, 0x7C8015D0, 0x67900190, 0x3D06890, 0x2B824182
                dw 0x6D045C2, 0x54905281, 0x26810481, 0x4B810481, 0xD812881
                dw 0x24902B81, 0x69902781, 0x4B812681, 0x28811381, 0x27810C81
                dw 0x4B810D81, 0x3D0, 0x444914B0, 0x6D00B82, 0x15D02982
                dw 0x93907C80, 0x19819490, 0x28814B81, 0xD821B82, 0x4A8245C2
                dw 0x3C22682, 0x4C827FC0, 0x4B823982, 0x81310C81, 0x8127813E
                dw 0x81EA902E, 0x81549052, 0x904B8111, 0x810C81C6, 0x810D8127
                dw 0x3D04B, 0x415014B0, 0xD00B824C, 0xD0298206, 0x907C8015
                dw 0x82A290E5, 0x8206D013, 0x90E69029, 0x90AC90E7, 0x90169051
                dw 0x90E990E8, 0x822E8149, 0x8206D00B, 0x827FC029, 0xD006D00D
                dw 3, 0x188214B0, 0x1C820282, 0x40823182, 0x7C8015D0
                dw 0x5A905990, 0x5C905B90, 0x3D05D90, 0x2E815E90, 0x4B813581
                dw 0x52810881, 0x5C90E390, 0xE490DC90, 0x41815890, 0x3D04B81
                dw 0x2B824182, 0x6D045C2, 0x54905281, 0x26810481, 0x4B810481
                dw 0x2B81DC90, 0x3C821B90, 0x53821F82, 0x7B905281, 0x26811781
                dw 0x4990E290, 0x3D0, 0x559014B0, 0x57905690, 0x7C8015D0
                dw 0xDE90DD90, 0xE090DF90, 0x3D05790, 0x56905590, 0xE1905281
                dw 0xC6901981, 0x27810C81, 0x4B810D81, 0x418203D0, 0x45C22B82
                dw 0x528106D0, 0x4815490, 0x4812681, 0xDC904B81, 0x1B902B81
                dw 0x1F823C82, 0x52815382, 0x17817B90, 0xE2902681, 0x3D04990
                dw 0
                dw 0x4C8214B0, 0x178206D0, 0x538247C2, 0x7C8015D0, 0x4990D790
                dw 0xD990D890, 0xDB90DA90, 0x4C8003D0, 0x46804980, 0x52814580
                dw 0x53905290, 0x4B811981, 0x418203D0, 0x45C22B82, 0x528106D0
                dw 0x4815490, 0x4812681, 0xDC904B81, 0x1B902B81, 0x1F823C82
                dw 0x52815382, 0x17817B90, 0x48902681, 0x3D04990, 0x94909390
                dw 0xC912781, 0x48909890, 0x3D04990, 0
                dw 0xB8214B0, 0x49824182, 0x7C8015D0, 0x4D810481, 0x4D810481
                dw 0x28812A81, 0x4D811381, 0x4F905281, 0x27815090, 0x4B810D81
                dw 0x249003D0, 0x1A822781, 0x408206D0, 0x53820482, 0x189002D0
                dw 0x1A822781, 0x408206D0, 0x6820282, 0x3D02882, 0x27811D90
                dw 0x50904F90, 0x3D0, 0x408214B0, 0x53821282, 0x53823082
                dw 0x2A822082, 0x7C8015D0, 0x4A824182, 0xC814B82, 0x24813490
                dw 0x1F811181, 0x53823082, 0x2A822082, 0x7C8003D0, 0x40820BB0
                dw 0x53821282, 0x28810CD0, 0x6810481, 0xC818E90, 0x4812C81
                dw 0x3E811381, 0x26814C81, 0x4B810481, 0x3D0, 0x198214B0
                dw 0x4B822682, 0x4C901982, 0x15D04D90, 0xA827C80, 0x13821F82
                dw 0xC815382, 0x7E905490, 0x1F811781, 0x4A9002D0, 0xD3905281
                dw 0x1581D490, 0x26811B81, 0x94909390, 0x1F811781, 0x5281D590
                dw 0x6890D690, 0x19816490, 0x4C904B81, 0x17824D90, 0x26821982
                dw 0x3D04082, 0
                dw 0x118214B0, 0x43C22182, 0x378223C2, 0x7C8015D0, 0x45904490
                dw 0x3D04690, 0x1F820482, 0x2824A82, 0x28824790, 0x28823E82
                dw 0x49904890, 0x238003D0, 0x3C822490, 0x53821F82, 0x48902781
                dw 0xB6904990, 0x3D00F91, 0
                dw 0x3C8214B0, 0x3C22782, 0x28206D0, 0x3E8206D0, 0x15D006D0
                dw 0xFE907C80, 0xD090FF90, 0x5281D190, 0x49904890, 0x1F811781
                dw 0x8590D290, 0x19823982, 0x3D02882, 0x41822082, 0x188206D0
                dw 0x42905281, 0x15814390, 0x4B811B81, 0xC81C690, 0xD812781
                dw 0x3D04B81, 0
                dw 0xC8214B0, 0x3E821982, 0xF821982, 0x7C8015D0, 0xCA909190
                dw 0x64903A90, 0xCB904B90, 0xCC90C190, 0xC824990, 0x3E821982
                dw 0xF821982, 0x3F9003D0, 0x19820C82, 0xCD902E81, 0x4F802781
                dw 0x12823280, 0x188206D0, 0x43900C81, 0x1981CE90, 0x19824B81
                dw 0x6D03482, 0xC812982, 0xF81CF90, 0x4B812A81, 0x3D0
                dw 0x158214B0, 0x3E8206D0, 0x7FC04B82, 0x6D01482, 0x4B821082
                dw 0x7C8015D0, 0xC890C790, 0x38902E81, 0x5281C990, 0xC090BF90
                dw 0x19816490, 0x31904B81, 0xC1903290, 0x3D0C290, 0x4813190
                dw 0xC490C390, 0x42812781, 0xA4903290, 0xC5905281, 0x19812B90
                dw 0xC6904B81, 0x27810C81, 0x4B810D81, 0x3D0, 0x319014B0
                dw 0x14823290, 0x108206D0, 0x15D04B82, 0x4A907C80, 0xA6905281
                dw 0xBC90A790, 0xBD902B81, 0x1781BE90, 0xBF902681, 0x6490C090
                dw 0x4B811981, 0x32903190, 0xC290C190, 0x319003D0, 0xC3900481
                dw 0x2781C490, 0x32904281, 0x5281A490, 0x2B90C590, 0x4B811981
                dw 0xC81C690, 0xD812781, 0x3D04B81, 0
                dw 0x208214B0, 0x3C825382, 0x4B8206D0, 0xD043B990, 0xB07C8015
                dw 0x902F900B, 0xD0269030, 0x9028810C, 0x81048127, 0x81028126
                dw 0x3D04B, 0x208214B0, 0x3C825382, 0x4B8206D0, 0xD042B990
                dw 0xB07C8015, 0x902A900B, 0x90BA9085, 0x902C902B, 0xD02690BB
                dw 0x9028810C, 0x81048127, 0x81028126, 0x3D04B, 0x208214B0
                dw 0x3C825382, 0x4B8206D0, 0xD041B990, 0xB07C8015, 0x8238820B
                dw 0xD03D824A, 0x90288206, 0x810CD026, 0x81279028, 0x814C810B
                dw 0x81048126, 0x3D04B, 0x219014B0, 0x23902290, 0x7C8015D0
                dw 0x6390B690, 0xB890B790, 0x22902190, 0x3D02390, 0x27812490
                dw 0x6D01A82, 0x4824082, 0x2D05382, 0x27811890, 0x6D01A82
                dw 0x2824082, 0x28820682, 0x3D0, 0xB09014B0, 0x15D0B190
                dw 0x1D827C80, 0x23C24A82, 0x7FC02982, 0x2D821982, 0xF8206D0
                dw 0x49901F90, 0xB0902E81, 0x3D0B190, 0x481B290, 0xE81B390
                dw 0x2F812B81, 0xB590B490, 0x3E811781, 0x47C11781, 0x3D00681
                dw 0
                dw 0x118214B0, 0x43C22182, 0x378223C2, 0x7C8015D0, 0x4A817990
                dw 0x4812481, 0x4812681, 0x2D02681, 0x49904890, 0xD812781
                dw 0x4812A81, 0x3D0, 0x4C8214B0, 0x178206D0, 0x538247C2
                dw 0x7C8015D0, 0x4A817990, 0x4812481, 0x4812681, 0x2D02681
                dw 0x49904890, 0xD812781, 0x4812A81, 0x3D0, 0x5A414944
                dw 0x4D415045, 0
aMedicine:      db "MEDICINE", 0x0
                db 0, 0, 0
jpt_8003C2B8:   dw 0x8003C2C0         ; DATA XREF: sub_8003C24C+58?o
                dw 0x8003C4DC         ; jump table for switch statement
                dw 0x8003C4DC
                dw 0x8003C4DC
                dw 0x8003C2C0
                dw 0x8003C390
                dw 0x8003C3D0
                dw 0x8003C4DC
                dw 0x8003C4DC
                dw 0x8003C414
jpt_8003C55C:   dw 0x8003C564         ; DATA XREF: sub_8003C4EC+5C?o
                dw 0x8003C660         ; jump table for switch statement
                dw 0x8003C760
                dw 0x8003C8D8
                dw 0x8003C934
aPanelMakeError:db "PANEL MAKE Error", 0xA, 0x0
                                         ; DATA XREF: sub_8003D2BC+64?o
                dh 0
aClaymore:      db "CLAYMORE", 0x0
                db 0, 0, 0
                dw 0x508014B0, 0x47805380, 0x15D03180, 0xAA907C80, 0x4990AB90
                dw 0x4824982, 0x4B823582, 0x939003D0, 0x19819490, 0x28814B81
                dw 0x96909590, 0x6D04282, 0x2B812982, 0x4B81AC90, 0x879003D0
                dw 0xD829B90, 0x278106D0, 0x96909590, 0x98909790, 0x238002D0
                dw 0x3C821D90, 0x53821F82, 0x7B905281, 0x28811981, 0x7F907E90
                dw 0x3D0, 0x218214B0, 0x358243C2, 0x10827FC0, 0x2D824C82
                dw 0x298206D0, 0x7C8015D0, 0xA790A690, 0xA990A890, 0x84905E90
                dw 0x3D08590, 0x1D902380, 0x1F823C82, 0x52815382, 0x19817B90
                dw 0x7C902881, 0x2D00881, 0x19817D90, 0x88902881, 0x4B811281
                dw 0x39103D0, 0x83900491, 0x5915281, 0x17810691, 0xA69002D0
                dw 0x9390A790, 0x52819E90, 0xA990A890, 0x4B811981, 0x3D0
                dw 0x198214B0, 0x53821F82, 0x10827FC0, 0x2D824C82, 0x298206D0
                dw 0x7C8015D0, 0xFF90FE90, 0x4A90A390, 0x84905E90, 0x3D08590
                dw 0x1D902380, 0x1F823C82, 0x52815382, 0x19817B90, 0x7C902881
                dw 0x2D00881, 0x19817D90, 0x88902881, 0x4B811281, 0xA29003D0
                dw 0x19817E90, 0x28814B81, 0xE39002D0, 0xDC905C90, 0x9F90E490
                dw 0x1915281, 0x15810291, 0x4B811B81, 0x3D0, 0x804314B0
                dw 0x90A29034, 0x8015D085, 0x8237827C, 0x82198249, 0x8223C221
                dw 0x90A2900F, 0x8003D085, 0x821D9023, 0x821F823C, 0x90278153
                dw 0xD09E909D, 0x90238002, 0x823C8224, 0x8153821F, 0x90A29027
                dw 0x3D082, 0xF8214B0, 0x4824C82, 0x2824282, 0x7C8015D0
                dw 0x99909190, 0x9B909A90, 0x6A909C90, 0x3D06B90, 0x1D902380
                dw 0x1F823C82, 0x27815382, 0x9E909D90, 0x9D9003D0, 0xDC909E90
                dw 0xED902B81, 0x1581EE90, 0x4B814C81, 0x7E90A290, 0xC890FD90
                dw 0xAC902B81, 0x28814B81, 0x7E90A290, 0x4B811981, 0x3D0
                dw 0x198214B0, 0x3C22682, 0xC825382, 0x7FC006D0, 0x15823F82
                dw 0x4B820482, 0x7C8015D0, 0x91906A90, 0x3F829290, 0x4821582
                dw 0x3D04B82, 0x94909390, 0x4B811981, 0x95902881, 0x42829690
                dw 0x298206D0, 0xAC902B81, 0x3D04B81, 0x9B908790, 0x6D00D82
                dw 0x95902781, 0x97909690, 0x2D09890, 0x1D902380, 0x1F823C82
                dw 0x52815382, 0x19817B90, 0x7E902881, 0x3D08C90, 0
                dw 0x4A8214B0, 0x13824282, 0x3F825382, 0x4821582, 0x15D04B82
                dw 0x89907C80, 0x8A903790, 0x3F828B90, 0x4821582, 0x3D04B82
                dw 0x1D902380, 0x1F823C82, 0x52815382, 0x19817B90, 0x7E902881
                dw 0x3D08C90, 0x8C907E90, 0x2D0FC90, 0x9B908790, 0x6D00D82
                dw 0x3F822781, 0x4821582, 0x52814B82, 0x90908F90, 0xD812781
                dw 0x3D04B81, 0
                dw 0x108214B0, 0x2D824C82, 0x298206D0, 0x7C8015D0, 0x83908290
                dw 0x84905E90, 0x3D08590, 0x1D902380, 0x1F823C82, 0x52815382
                dw 0x19817B90, 0x5B902881, 0x3482F890, 0x52815382, 0xD81F990
                dw 0x7D9002D0, 0x28811981, 0x12818890, 0x3D04B81, 0x53823482
                dw 0xF9905281, 0x26810481, 0x49810B81, 0x3580FA90, 0xFC90FB90
                dw 0xA2902B81, 0x3D07E90, 0
                dw 0x358214B0, 0x3E8201C2, 0x15D01982, 0x2827C80, 0x4B821582
                dw 0x49822882, 0x35820482, 0x3D04B82, 0x1D902380, 0x1F823C82
                dw 0x52815382, 0x19817B90, 0x7E902881, 0x3D07F90, 0x17817B90
                dw 0x25812481, 0x4B811181, 0x2D02881, 0x4B823582, 0x6D00A82
                dw 0x80902882, 0x3D08C90, 0
dword_80011A8C: dw 0x1D8214B0, 0x138206D0, 0x34824082, 0x28821982, 0x15D04B82
                dw 0x42907C80, 0x98900C91, 0xE910D91, 0x4C8203D0, 0x168206D0
                dw 0x959006D0, 0xC1909690, 0x94909390, 0x238003D0, 0x3C821D90
                dw 0x53821F82, 0x7B905281, 0x28811981, 0x23C24D82, 0xA820F82
                dw 0x2D05382, 0x19817D90, 0x7E902881, 0x3D07F90, 0x37821582
                dw 0x23C24C82, 0x6D01582, 0x94909390, 0xF91B690, 0x3D0
                dw 0x504D14B0, 0x53203520, 0x8015D044, 0x8215827C, 0x823E8236
                dw 0x82538217, 0xD053820C, 0x90238003, 0x823C821D, 0x8153821F
                dw 0x817B9052, 0x90288119, 0xD07F907E, 0x817B9003, 0x81248117
                dw 0x81118125, 0xD028814B, 0x82358202, 0xD00A824B, 0x90288206
                dw 0xD08C9080, 0x82158203, 0xC24C8237, 0xD0158223, 0x90939006
                dw 0x3D094, 0x45524548, 0xA642520, 0
aPressSelectToE:db "PRESS SELECT TO EXIT", 0x0
                                         ; DATA XREF: sub_8004158C+324?o
                db 0, 0, 0
aSetCallFreqD:  db "set call freq %d", 0xA, 0x0
                                         ; DATA XREF: sub_8004158C+54C?o
                dh 0
aNoResponse:    db "NO RESPONSE", 0x0  ; DATA XREF: sub_8004158C+80C?o
dword_80011BB0: dw 0xAE90AD90, 0x4A810281, 0x1B813E81, 0x3D05381, 0
                                         ; DATA XREF: sub_8004158C+820?o
aGetpotionD:    db "GetPotion %d", 0xA, 0x0
                                         ; DATA XREF: sub_80042198+1B0?o
                dh 0
aPushSelect:    db "PUSH SELECT", 0x0  ; DATA XREF: sub_80042198+374?o
aCallbackTypeDP:db "callback type %d proc %X", 0xA, 0x0
                                         ; DATA XREF: sub_80042198+488?o
                dh 0
aExecproc:      db "ExecProc", 0xA, 0x0   ; DATA XREF: sub_80042198+4B0?o
                dh 0
aExitMusenki:   db "EXIT MUSENKI", 0xA, 0x0
                                         ; DATA XREF: sub_80042198+514?o
                dh 0
jpt_80041650:   dw 0x80041658         ; DATA XREF: sub_8004158C+B0?o
                dw 0x80041670         ; jump table for switch statement
                dw 0x80041948
                dw 0x800419C4
                dw 0x80041B28
                dw 0x80041B98
                dw 0x80041DE0
                dw 0x80041E08
                dw 0x80042064
                dw 0x80041D5C
                dw 0x800418C4
                dw 0x80041F4C
                dw 0x80041F70
                dw 0x80041FA0
                dw 0x80041FC8
                dw 0x80042038
                dw 0x80042044
                dw 0x80042064
                dw 0x80041E94
                dw 0x80041EE4
jpt_80041A84:   dw 0x80042064         ; DATA XREF: sub_8004158C+4E4?o
                dw 0x80041A8C         ; jump table for switch statement
                dw 0x80041ACC
                dw 0x80041AF4
                dw 0x80041B1C
aTotalD:        db "TOTAL %d", 0xA, 0x0   ; DATA XREF: sub_800442E4+2C4?o
                dh 0
aClipD:         db "CLIP %d", 0xA, 0x0    ; DATA XREF: sub_800442E4+2D4?o
                db 0, 0, 0
aXDYD:          db "x %d y %d", 0xA, 0x0  ; DATA XREF: sub_800445F8+188?o
                db 0
aWDHD:          db "w %d h %d", 0xA, 0x0  ; DATA XREF: sub_800445F8+18C?o
                db 0
aWrongRubiCodeX:db "Wrong rubi code %x", 0xA, 0x0
                                         ; DATA XREF: sub_800458B8+90?o
                                         ; sub_80045AE4+1B8?o
aNoMemoryForSav:db "NO MEMORY FOR SAVE TEX", 0xA, 0x0
                                         ; DATA XREF: sub_800469F0+64?o
aNoFaceData:    db "NO_FACE_DATA", 0xA, 0x0
                                         ; DATA XREF: sub_80046DF4+124?o
                dh 0
aFrameNumD:     db "frame num %d", 0xA, 0x0
                                         ; DATA XREF: sub_80046F3C+B8?o
                dh 0
aSetCharaCodeD: db "set chara code %d", 0xA, 0x0
                                         ; DATA XREF: sub_800471AC+40?o
                db 0
aAnimeCharaDCod:db "ANIME CHARA %d CODE %d", 0xA, 0x0
                                         ; DATA XREF: sub_80047280+98?o
aVoxcodeX:      db "voxcode %X", 0xA, 0x0
                                         ; DATA XREF: sub_80047330+30?o
aIllegalCodeX:  db "illegal code %x", 0xA, 0x0
                                         ; DATA XREF: sub_80047514+90?o
                                         ; sub_800475B8+7C?o ...
                db 0, 0, 0
aSetDS:         db "set %d %s", 0xA, 0x0  ; DATA XREF: sub_80047768+14?o
                db 0
aBlockExecError:db "block exec error", 0xA, 0x0
                                         ; DATA XREF: sub_800478B4+18C?o
                dh 0
aNoMemoryForFac:db "NO MEMORY FOR FACE %d", 0xA, 0x0
                                         ; DATA XREF: sub_80047AA0+C0?o
                db 0
aFaceDataNumD:  db "face data num %d", 0xA, 0x0
                                         ; DATA XREF: sub_80047AA0+128?o
                dh 0
aNoMemoryForSta:db "NO MEMORY FOR STACK", 0xA, 0x0
                                         ; DATA XREF: sub_80047C3C+2C?o
                db 0, 0, 0
aNoMemory:      db "no memory", 0xA, 0x0  ; DATA XREF: sub_80047CE4+30?o
                                         ; sub_80047D70+74?o ...
                db 0
                dw 0
jpt_80047940:   dw 0x80047948, 0x8004795C, 0x80047970, 0x80047984, 0x80047998
                                         ; DATA XREF: sub_800478B4+48?o
                dw 0x800479AC, 0x800479C0, 0x800479D4, 0x80047A38, 0x80047A38  ; jump table for switch statement
                dw 0x80047A38, 0x80047A38, 0x80047A38, 0x80047A38, 0x80047A38
                dw 0x800479E8, 0x80047A38, 0x80047A38, 0x80047A38, 0x80047A38
                dw 0x80047A38, 0x80047A38, 0x80047A38, 0x80047A38, 0x80047A38
                dw 0x80047A38, 0x80047A38, 0x80047A38, 0x80047A38, 0x80047A38
                dw 0x80047A38, 0x800479FC, 0x80047A38, 0x80047A38, 0x80047A38
                dw 0x80047A38, 0x80047A38, 0x80047A38, 0x80047A38, 0x80047A38
                dw 0x80047A38, 0x80047A38, 0x80047A38, 0x80047A38, 0x80047A38
                dw 0x80047A38, 0x80047A38, 0x80047A10, 0x80047A38, 0x80047A38
                dw 0x80047A38, 0x80047A38, 0x80047A38, 0x80047A38, 0x80047A38
                dw 0x80047A38, 0x80047A38, 0x80047A38, 0x80047A38, 0x80047A38
                dw 0x80047A38, 0x80047A38, 0x80047A38, 0x80047A24
jpt_80048E64:   dw 0x80048F4C         ; DATA XREF: sub_80048DB0+68?o
                dw 0x80048E6C         ; jump table for switch statement
                dw 0x80048EB8
                dw 0x80048F30
                dw 0x80048F3C
aJimakuFontBuff:db "jimaku_font_buffer_size %d", 0xA, 0x0
                                         ; DATA XREF: sub_800493F8+70?o
aRadioCallOver: db "RADIO CALL OVER!!", 0xA, 0x0
                                         ; DATA XREF: sub_8004969C+5C?o
                db 0
aNoMemoryForFil:db "NO MEMORY FOR FILE BODY", 0xA, 0x0
                                         ; DATA XREF: sub_8004983C+68?o
                                         ; sub_80049CE8+54?o
                db 0, 0, 0
                dw 0x9C23582, 0x3E8206D0, 0x288223C2, 0x26811781, 0x3E810481
                dw 0x3D01981, 0
                dw 0x42824182, 0x6D04A82, 0x6D00B82, 0x52812982, 0x7C22182
                dw 0xF8223C2, 0x26811781, 0x3E810481, 0x3D01981, 0
dword_80011F5C: dw 0x6D01B82, 0xCD903682, 0x19812781, 0x3D0, 0x42824182
                dw 0x6D04A82, 0x6D00B82, 0xC812982, 0x15811581, 0x26814C81
                dw 0x3E810481, 0x53811B81, 0x3D0, 0x9C23582, 0x3E8206D0
                dw 0x288223C2, 0x9912B81, 0x17810A91, 0x17813E81, 0x3D01F81
                dw 0
                dw 0x6D01B82, 0x17813682, 0x17813E81, 0x3D01F81, 0
                dw 0x42824182, 0x6D04A82, 0x6D00B82, 0xC812982, 0x11911091
                dw 0x15816490, 0x26814C81, 0x3E810481, 0x53811B81, 0x3D0
                dw 0xD819290, 0x4D823682, 0xF8223C2, 0x1F810C81, 0x3E814A81
                dw 0x53811B81, 0x3D0, 0x49820882, 0xC8106D0, 0xCA907E90
                dw 0x3E811781, 0x1F811781, 0x3D0, 0x6D01B82, 0x27813682
                dw 0x3E810D81, 0x53811B81, 0x17812781, 0x3D01F81, 0
dword_8001203C: dw 0x6D01B82, 0xC813682, 0x8910791, 0x3E811781, 0x1F811781
                dw 0x3D0, 0x6D04D82, 0xCD902982, 0x19812781, 0x3D0
                dw 0x6D04D82, 0x17812982, 0x17813E81, 0x3D01F81, 0
                dw 0x6D01B82, 0x35823682, 0x48201C2, 0xC814B82, 0x4A810281
                dw 0x1B813E81, 0x3D05381, 0
                dw 0x6D04D82, 0x27812982, 0x3E810D81, 0x53811B81, 0x17812781
                dw 0x3D01F81, 0
dword_800120B4: dw 0x6D04D82, 0xC812982, 0x8910791, 0x3E811781, 0x1F811781
                dw 0x3D0, 0x9C23582, 0x3E8206D0, 0x288223C2, 0x3E811781
                dw 0xB811981, 0x3FC0, 0x27900B91, 0x17810D81, 0x48812681
                dw 0x17814D81, 0x27810481, 0xB811981, 0x3FC0, 0x4D524F46
                dw 0x4F205441, 0x3F4B, 0x5245564F, 0x54495257, 0x4B4F2045
                dw 0x3F, 0x55514552, 0x20545345, 0xA5825, 0x55534552
                dw 0x2520544C, 0xA58
aNoMemoryForSta_0:db "NO MEMORY FOR STACK", 0xA, 0x0
                                         ; DATA XREF: sub_8004A424+2C?o
                db 0, 0, 0
aComplete:      db "COMPLETE", 0x0     ; DATA XREF: TEXT:8009EBC4?o
                db 0, 0, 0
aNoMemoryForObj:db "NO MEMORY FOR OBJ", 0xA, 0x0
                                         ; DATA XREF: sub_8004A800+28?o
                db 0
aNewFileNeedDBl:db "NEW FILE [ NEED %d BLOCK%s ]", 0x0
                                         ; DATA XREF: sub_8004B0A0+4F8?o
                db 0, 0, 0
aFreeDBlockS:   db "FREE: %d BLOCK%s", 0x0
                                         ; DATA XREF: sub_8004B0A0+76C?o
                db 0, 0, 0
aCloseInfo:     db "close info", 0xA, 0x0
                                         ; DATA XREF: sub_8004B91C+18?o
aNoMemoryForInf:db "NO MEMORY FOR INFO", 0xA, 0x0
                                         ; DATA XREF: sub_8004B958+48?o
aAllocInfoX:    db "alloc info %X", 0xA, 0x0
                                         ; DATA XREF: sub_8004B958+58?o
                db 0
aFileS:         db "FILE %s", 0xA, 0x0
                db 0, 0, 0
aMemoryCard2:   db "MEMORY CARD 2", 0x0
                                         ; DATA XREF: TEXT:8009EC04?o
                dh 0
aMemoryCard1:   db "MEMORY CARD 1", 0x0
                                         ; DATA XREF: TEXT:off_8009EC00?o
                dh 0
aSaving:        db "SAVING...", 0x0    ; DATA XREF: sub_8004C418+50?o
                dh 0
aNoSpace:       db "NO SPACE", 0x0     ; DATA XREF: sub_8004C418+58?o
                db 0, 0, 0
aLoadData:      db "LOAD DATA", 0x0    ; DATA XREF: sub_8004C418+78?o
                dh 0
aLoading:       db "LOADING...", 0x0   ; DATA XREF: sub_8004C418+88?o
                db 0
aSelectMemoryCa:db "SELECT MEMORY CARD", 0x0
                                         ; DATA XREF: sub_8004C418+410?o
                                         ; sub_8004C418+580?o ...
                db 0
aPressToExit:   db "PRESS * TO EXIT", 0x0
                                         ; DATA XREF: sub_8004C418+7CC?o
aPressToSelectM:db "PRESS * TO SELECT MEMORY CARD", 0x0
                                         ; DATA XREF: sub_8004C418+904?o
                dh 0
aEndSaveMode:   db "END SAVE MODE", 0xA, 0x0
                                         ; DATA XREF: sub_8004C418+9B0?o
                db 0
aEndStateD:     db "END STATE %d", 0xA, 0x0
                                         ; DATA XREF: sub_8004C418+9EC?o
                dh 0
aNoPlace:       db "NO PLACE", 0x0     ; DATA XREF: sub_8004CF20+28?o
                db 0, 0, 0
aCodeD:         db "code %d", 0xA, 0x0    ; DATA XREF: sub_8004CF20+4C?o
                db 0, 0, 0
dword_800122A8: dw 0x64826D81, 0x6E817782, 0
                                         ; DATA XREF: TEXT:8009EC2C?o
dword_800122B4: dw 0x67826D81, 0x6E816382, 0
                                         ; DATA XREF: TEXT:8009EC28?o
dword_800122C0: dw 0x6D826D81, 0x6E816C82, 0
                                         ; DATA XREF: TEXT:8009EC24?o
dword_800122CC: dw 0x64826D81, 0x6E817982, 0
                                         ; DATA XREF: TEXT:8009EC20?o
dword_800122D8: dw 0x75826D81, 0x6E816482, 0
                                         ; DATA XREF: TEXT:off_8009EC1C?o
aSSSSSS:        db "%s%s%s%s%s%s", 0x0
                                         ; DATA XREF: sub_8004D008+EC?o
                db 0, 0, 0
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
