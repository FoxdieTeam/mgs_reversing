	opt	c+, at+, e+, n-
	section overlay.text

	xdef s12c_fadeio_800D5010
s12c_fadeio_800D5010:
	dw 0x27BDFFD0 ; 800D5010
	dw 0xAFB50024 ; 800D5014
	dw 0x0080A821 ; 800D5018
	dw 0xAFB3001C ; 800D501C
	dw 0x00A09821 ; 800D5020
	dw 0xAFB40020 ; 800D5024
	dw 0x00C0A021 ; 800D5028
	dw 0xAFB60028 ; 800D502C
	dw 0x00E0B021 ; 800D5030
	dw 0xAFBF002C ; 800D5034
	dw 0xAFB20018 ; 800D5038
	dw 0xAFB10014 ; 800D503C
	dw 0xAFB00010 ; 800D5040
	dw 0x86B2002E ; 800D5044
	dw 0x00000000 ; 800D5048
	dw 0x1A400122 ; 800D504C
	dw 0x26B10048 ; 800D5050
	dw 0x26B00094 ; 800D5054
	dw 0x12C000F4 ; 800D5058
	dw 0x00001821 ; 800D505C
	dw 0x32820010 ; 800D5060
	dw 0x104000F1 ; 800D5064
	dw 0x24030002 ; 800D5068
	dw 0x26220020 ; 800D506C
	dw 0x8C4C0000 ; 800D5070
	dw 0x8C4D0004 ; 800D5074
	dw 0x48CC0000 ; 800D5078
	dw 0x48CD0800 ; 800D507C
	dw 0x8C4C0008 ; 800D5080
	dw 0x8C4D000C ; 800D5084
	dw 0x8C4E0010 ; 800D5088
	dw 0x48CC1000 ; 800D508C
	dw 0x48CD1800 ; 800D5090
	dw 0x48CE2000 ; 800D5094
	dw 0x8C4C0014 ; 800D5098
	dw 0x8C4D0018 ; 800D509C
	dw 0x48CC2800 ; 800D50A0
	dw 0x8C4E001C ; 800D50A4
	dw 0x48CD3000 ; 800D50A8
	dw 0x48CE3800 ; 800D50AC
	dw 0x3C051F80 ; 800D50B0
	dw 0x8E02FFF4 ; 800D50B4
	dw 0x34A50018 ; 800D50B8
	dw 0x8C430008 ; 800D50BC
	dw 0x24420008 ; 800D50C0
	dw 0x3C011F80 ; 800D50C4
	dw 0xAC230000 ; 800D50C8
	dw 0x8C430004 ; 800D50CC
	dw 0x3C081F80 ; 800D50D0
	dw 0x3C011F80 ; 800D50D4
	dw 0xAC230004 ; 800D50D8
	dw 0x8C430008 ; 800D50DC
	dw 0x35080030 ; 800D50E0
	dw 0x3C011F80 ; 800D50E4
	dw 0xAC230008 ; 800D50E8
	dw 0x8C43000C ; 800D50EC
	dw 0x3C071F80 ; 800D50F0
	dw 0x3C011F80 ; 800D50F4
	dw 0xAC23000C ; 800D50F8
	dw 0x8C430010 ; 800D50FC
	dw 0x34E70060 ; 800D5100
	dw 0x3C011F80 ; 800D5104
	dw 0xAC230010 ; 800D5108
	dw 0x8C420014 ; 800D510C
	dw 0x24040009 ; 800D5110
	dw 0x3C011F80 ; 800D5114
	dw 0xAC220014 ; 800D5118
	dw 0x24060003 ; 800D511C
	dw 0x24A30004 ; 800D5120
	dw 0x30820001 ; 800D5124
	dw 0x10400005 ; 800D5128
	dw 0x00000000 ; 800D512C
	dw 0x3C021F80 ; 800D5130
	dw 0x9442000C ; 800D5134
	dw 0x08035454 ; 800D5138
	dw 0xA4A20000 ; 800D513C
	dw 0x3C021F80 ; 800D5140
	dw 0x94420000 ; 800D5144
	dw 0x00000000 ; 800D5148
	dw 0xA4A20000 ; 800D514C
	dw 0x30820002 ; 800D5150
	dw 0x10400005 ; 800D5154
	dw 0x00000000 ; 800D5158
	dw 0x3C021F80 ; 800D515C
	dw 0x94420010 ; 800D5160
	dw 0x0803545F ; 800D5164
	dw 0xA462FFFE ; 800D5168
	dw 0x3C021F80 ; 800D516C
	dw 0x94420004 ; 800D5170
	dw 0x00000000 ; 800D5174
	dw 0xA462FFFE ; 800D5178
	dw 0x30820004 ; 800D517C
	dw 0x10400005 ; 800D5180
	dw 0x00000000 ; 800D5184
	dw 0x3C021F80 ; 800D5188
	dw 0x94420014 ; 800D518C
	dw 0x0803546A ; 800D5190
	dw 0xA4620000 ; 800D5194
	dw 0x3C021F80 ; 800D5198
	dw 0x94420008 ; 800D519C
	dw 0x00000000 ; 800D51A0
	dw 0xA4620000 ; 800D51A4
	dw 0x24630008 ; 800D51A8
	dw 0x24A50008 ; 800D51AC
	dw 0x24C6FFFF ; 800D51B0
	dw 0x1CC0FFDB ; 800D51B4
	dw 0x2484FFFF ; 800D51B8
	dw 0x3C051F80 ; 800D51BC
	dw 0x34A50018 ; 800D51C0
	dw 0xE90C0000 ; 800D51C4
	dw 0xE90D0004 ; 800D51C8
	dw 0xE90E0008 ; 800D51CC
	dw 0xE8F10000 ; 800D51D0
	dw 0xE8F20004 ; 800D51D4
	dw 0xE8F30008 ; 800D51D8
	dw 0x3C0B1F80 ; 800D51DC
	dw 0x356B0018 ; 800D51E0
	dw 0xC9600000 ; 800D51E4
	dw 0xC9610004 ; 800D51E8
	dw 0xC9620008 ; 800D51EC
	dw 0xC963000C ; 800D51F0
	dw 0xC9640010 ; 800D51F4
	dw 0xC9650014 ; 800D51F8
	dw 0x2508000C ; 800D51FC
	dw 0x24E7000C ; 800D5200
	dw 0x4A280030 ; 800D5204
	dw 0x1C80FFC5 ; 800D5208
	dw 0x24060003 ; 800D520C
	dw 0xE90C0000 ; 800D5210
	dw 0xE90D0004 ; 800D5214
	dw 0xE90E0008 ; 800D5218
	dw 0xE8F10000 ; 800D521C
	dw 0xE8F20004 ; 800D5220
	dw 0xE8F30008 ; 800D5224
	dw 0x3C041F80 ; 800D5228
	dw 0x3484003C ; 800D522C
	dw 0x24050007 ; 800D5230
	dw 0x3C061F80 ; 800D5234
	dw 0x84C6003C ; 800D5238
	dw 0x3C081F80 ; 800D523C
	dw 0x8508003E ; 800D5240
	dw 0x00C03821 ; 800D5244
	dw 0x01004821 ; 800D5248
	dw 0x24840004 ; 800D524C
	dw 0x84830000 ; 800D5250
	dw 0x00000000 ; 800D5254
	dw 0x0066102A ; 800D5258
	dw 0x10400003 ; 800D525C
	dw 0x00E3102A ; 800D5260
	dw 0x0803549E ; 800D5264
	dw 0x00603021 ; 800D5268
	dw 0x10400002 ; 800D526C
	dw 0x00000000 ; 800D5270
	dw 0x00603821 ; 800D5274
	dw 0x84830002 ; 800D5278
	dw 0x00000000 ; 800D527C
	dw 0x0068102A ; 800D5280
	dw 0x10400003 ; 800D5284
	dw 0x0123102A ; 800D5288
	dw 0x080354A8 ; 800D528C
	dw 0x00604021 ; 800D5290
	dw 0x10400002 ; 800D5294
	dw 0x00000000 ; 800D5298
	dw 0x00604821 ; 800D529C
	dw 0x24A5FFFF ; 800D52A0
	dw 0x1CA0FFEA ; 800D52A4
	dw 0x24840004 ; 800D52A8
	dw 0x2484FFFC ; 800D52AC
	dw 0x3C0A1F80 ; 800D52B0
	dw 0x854A0090 ; 800D52B4
	dw 0x00000000 ; 800D52B8
	dw 0x0146102A ; 800D52BC
	dw 0x14400059 ; 800D52C0
	dw 0x00002821 ; 800D52C4
	dw 0x3C051F80 ; 800D52C8
	dw 0x84A50094 ; 800D52CC
	dw 0x00000000 ; 800D52D0
	dw 0x00E5102A ; 800D52D4
	dw 0x14400052 ; 800D52D8
	dw 0x00000000 ; 800D52DC
	dw 0x3C041F80 ; 800D52E0
	dw 0x84840092 ; 800D52E4
	dw 0x00000000 ; 800D52E8
	dw 0x0088102A ; 800D52EC
	dw 0x1440004C ; 800D52F0
	dw 0x00000000 ; 800D52F4
	dw 0x3C031F80 ; 800D52F8
	dw 0x84630096 ; 800D52FC
	dw 0x00000000 ; 800D5300
	dw 0x0123102A ; 800D5304
	dw 0x14400046 ; 800D5308
	dw 0x0147102A ; 800D530C
	dw 0x14400008 ; 800D5310
	dw 0x00C5102A ; 800D5314
	dw 0x14400006 ; 800D5318
	dw 0x0089102A ; 800D531C
	dw 0x14400005 ; 800D5320
	dw 0x24090001 ; 800D5324
	dw 0x0103102A ; 800D5328
	dw 0x10400002 ; 800D532C
	dw 0x24090002 ; 800D5330
	dw 0x24090001 ; 800D5334
	dw 0x3C021F80 ; 800D5338
	dw 0x8C420098 ; 800D533C
	dw 0x00000000 ; 800D5340
	dw 0x30420002 ; 800D5344
	dw 0x1040002D ; 800D5348
	dw 0x00004021 ; 800D534C
	dw 0x3C051F80 ; 800D5350
	dw 0x34A5006C ; 800D5354
	dw 0x01003821 ; 800D5358
	dw 0x3406FFFF ; 800D535C
	dw 0x24040008 ; 800D5360
	dw 0x8CA30000 ; 800D5364
	dw 0x00000000 ; 800D5368
	dw 0x0066102A ; 800D536C
	dw 0x10400002 ; 800D5370
	dw 0x00E3102A ; 800D5374
	dw 0x00603021 ; 800D5378
	dw 0x10400002 ; 800D537C
	dw 0x00000000 ; 800D5380
	dw 0x00603821 ; 800D5384
	dw 0x10600002 ; 800D5388
	dw 0x00000000 ; 800D538C
	dw 0x01204021 ; 800D5390
	dw 0x2484FFFF ; 800D5394
	dw 0x1C80FFF2 ; 800D5398
	dw 0x24A50004 ; 800D539C
	dw 0x11000020 ; 800D53A0
	dw 0x00000000 ; 800D53A4
	dw 0x00C02021 ; 800D53A8
	dw 0x04810002 ; 800D53AC
	dw 0x3C02800E ; 800D53B0
	dw 0x248400FF ; 800D53B4
	dw 0x8C43A430 ; 800D53B8
	dw 0x00041203 ; 800D53BC
	dw 0x0043102A ; 800D53C0
	dw 0x10400017 ; 800D53C4
	dw 0x00000000 ; 800D53C8
	dw 0x00E02021 ; 800D53CC
	dw 0x04810002 ; 800D53D0
	dw 0x3C02800E ; 800D53D4
	dw 0x248400FF ; 800D53D8
	dw 0x8C43A428 ; 800D53DC
	dw 0x00041203 ; 800D53E0
	dw 0x0043102A ; 800D53E4
	dw 0x1440000F ; 800D53E8
	dw 0x01002821 ; 800D53EC
	dw 0x0803550A ; 800D53F0
	dw 0x34A50004 ; 800D53F4
	dw 0x0803550A ; 800D53F8
	dw 0x01202821 ; 800D53FC
	dw 0x3C041F80 ; 800D5400
	dw 0x3484006C ; 800D5404
	dw 0x24030008 ; 800D5408
	dw 0x8C820000 ; 800D540C
	dw 0x00000000 ; 800D5410
	dw 0x1440FFF8 ; 800D5414
	dw 0x2463FFFF ; 800D5418
	dw 0x1C60FFFB ; 800D541C
	dw 0x24840004 ; 800D5420
	dw 0x00002821 ; 800D5424
	dw 0x00A01821 ; 800D5428
	dw 0x96020000 ; 800D542C
	dw 0x00000000 ; 800D5430
	dw 0x30420018 ; 800D5434
	dw 0x00431025 ; 800D5438
	dw 0x10600012 ; 800D543C
	dw 0xA6020000 ; 800D5440
	dw 0x24020008 ; 800D5444
	dw 0xA6020002 ; 800D5448
	dw 0x00131080 ; 800D544C
	dw 0x02221021 ; 800D5450
	dw 0x8C420054 ; 800D5454
	dw 0x00000000 ; 800D5458
	dw 0x1440001A ; 800D545C
	dw 0x02202021 ; 800D5460
	dw 0x02602821 ; 800D5464
	dw 0x0C006A94 ; 800D5468
	dw 0x02803021 ; 800D546C
	dw 0x04410015 ; 800D5470
	dw 0x32820020 ; 800D5474
	dw 0x10400013 ; 800D5478
	dw 0xA6000000 ; 800D547C
	dw 0x08035536 ; 800D5480
	dw 0xA6A00032 ; 800D5484
	dw 0x00131080 ; 800D5488
	dw 0x02221021 ; 800D548C
	dw 0x8C420054 ; 800D5490
	dw 0x00000000 ; 800D5494
	dw 0x1040000A ; 800D5498
	dw 0x00000000 ; 800D549C
	dw 0x96020002 ; 800D54A0
	dw 0x00000000 ; 800D54A4
	dw 0x2442FFFF ; 800D54A8
	dw 0xA6020002 ; 800D54AC
	dw 0x00021400 ; 800D54B0
	dw 0x1C400003 ; 800D54B4
	dw 0x02202021 ; 800D54B8
	dw 0x0C006AB4 ; 800D54BC
	dw 0x02602821 ; 800D54C0
	dw 0xA6000000 ; 800D54C4
	dw 0x2610005C ; 800D54C8
	dw 0x2652FFFF ; 800D54CC
	dw 0x1E40FEE1 ; 800D54D0
	dw 0x2631005C ; 800D54D4
	dw 0x8FBF002C ; 800D54D8
	dw 0x8FB60028 ; 800D54DC
	dw 0x8FB50024 ; 800D54E0
	dw 0x8FB40020 ; 800D54E4
	dw 0x8FB3001C ; 800D54E8
	dw 0x8FB20018 ; 800D54EC
	dw 0x8FB10014 ; 800D54F0
	dw 0x8FB00010 ; 800D54F4
	dw 0x03E00008 ; 800D54F8
	dw 0x27BD0030 ; 800D54FC