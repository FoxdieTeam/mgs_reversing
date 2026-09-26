#!/usr/bin/env python3

import sys
import os
import hashlib
import shutil
import locale
from colorama import init as colorama_init
from termcolor import colored
from uninitializer import extract

TARGET_HASH = '4b8252b65953a02021486406cfcdca1c7670d1d1a8f3cf6e750ef6e360dc3a2f'
TARGET_VR_HASH = 'c370f8e41ec8fb78238bfe2ddbfc25a6d37ec8f0972c86ebfde075ecd4ee8dca'
TARGET_OVERLAYS_HASH = {
    'abst': 'aed6a6145201850156d251618561487456e1b02d7ce26a40cf1e492b6fa30ec0',
    'brf': '95f948d72f4b2dd523c3f60b3e036db2971c5f00b3f69d7dc9b4744c48996286',
    'camera': '7e1738af3c3987b5461773cf865da803bac48820000e0e916307f29fa836f388',
    'change': 'd2f0afa4861278774ecc818c19e31420e3b05e96da4313ea048451bfabf780e5',
    'd00a': '3dd07b291d5bc6b58a028d012b744d9d2c8023f143474467b0259e5a5603ad0a',
    'd01a': '3a8d292f250a80b708a06f3fd41ee0e6b74733390084ef5b163108ba5c8af4a1',
    'd03a': '3f3b4350dc263a088c70fa7518844ba8e5ec95a3f705ffbc5a37e6b5ff18f8b1',
    'd11c': '86edb16ecdb7319d0ad133687228a808170a50ce36f393c96678f8379c48c746',
    'd16e': 'bf5ab697b6d0415ba63b9aa3aaba28f387f324cd2f1b32eb46f5d3cb253e48ef',
    'd18a': 'c388e19be2811a05075a0da664b5b4264040ecd7e2f6eb6cd761d8e579c35103',
    'd18ar': 'df7d5353a7b3be3d6d0f2550179181de27538c41b65b900c7f4a90068ee9d18a',
    'demosel': 'bbf6a776efcc2631b982f920f2c9247c8b215dd7a1358b3b9f9d76484f7d43d9',
    'ending': '321c325577bb05cf68bec689083cbc9f7fc4d0b634776c1e6cad1f464ffb1da3',
    'endingr': 'c8eabac0fa0bde6d7bbbdba97a4b8948c3e6a0c839d2b438705345c392b43c35',
    'opening': '87a5e822f5b428376ad36fcd28ebc56f661cf340f0ea059f11489b5f24e85545',
    'option': '19e897b855f2e197e62160a8a409d2ff57a6b8588b831722fab9c3aaca324ea0',
    'preope': '3176b630b8a3f9d8cb01ed833d78fbe654054a576c1f2da0ed91007dd71bd136',
    'rank': '6a5ed242f966a4c60bba7daf9a2ba1c37482825d0786e1d77476e135030753f5',
    'roll': 'dfe3ca728b6e409613ef7a3dc11b48ecaa236d8ba6cd0951ce4321329842beae',
    's00a': '533cb8e9b6ffdcc442c25ba51eb3d83e90cb1ad2831d3870395333398c8402bc',
    's01a': '534f8365ad37dbb5c4753bd1720517fa4d1a92e9008597064e6b30a23dc00a75',
    's02a': 'ece10d39e1d5bafee5acb4dd970bf83801128b04e4fb24ad31756e5bb4ca754d',
    's02b': '57a66e93a2028e3fb805c97c585fb6cfb5fe76c93fc4b8495ccdb2c03a1de308',
    's02c': '7c0b12187840f60405970364a1f7c73ec96be32c1130b3f9a87ec58f6ea46915',
    's02d': '5fe851426faf64733c1077998f9463b5455c766d3e27c9cdceed38ac338e8542',
    's02e': 'cd79cd79a00e18bd5d323b0b8e153b4e8fe5548b6e0ea68f36d13f190eca0477',
    's03a': 'c42bba970bdc968ee48b572efb03c41f15869cfc00d6aa0d7c8106487534f580',
    's03ar': 'f34b46313625005b6aef5006b184556c4dd8f13e97a3b0c346f0f4fc7b9fbf04',
    's03b': 'cd728e144c960e7419d389c81802d3de73c00a2f31e9bfd7eea33ed3ed2be083',
    's03c': 'cc3b95638684f6f0a6cbcf9b0436fbc7b545ca0eeb0e6e60d6c4d0646dbc7fb4',
    's03d': 'f9fa0f39352d3305b5cb2bd6c292297d4f351387b0038a27ccec29f42150d903',
    's03dr': 'fa785a857655809ccf984d8c8ada626addbadfd11db31b34ef496ddce225ade1',
    's03e': 'af0e15b223431977c2ad233596c37a51c0367da6470c1b760d3f211eb82e894c',
    's03er': 'b1e60c25c0ee92e8c347b7f6a51b2e3fdb10d9ea33a2a77e1acbd8bfc7367114',
    's04a': '59b541a13b987478d6717643c3c146018b070fe374ffae0eaaf3f9a8bdc2ffb6',
    's04b': 'bca0c362260565051a8d41ffc49d3b9ae84d1bc9dc758164ea019cae82de7fa7',
    's04br': '3ceb35994af2c7da7955ab356cbbb7471c749ff6788ecdfbffab1c5679bb4f9b',
    's04c': '5e6bc0c9b13f009c69c2ebdfb401fe9d55a6cd6ee8610cbdd95ee9f3dd71f32a',
    's05a': 'fd08923d1e1ad01b8638f7e8f4a101e270a5f399f3d1afed47abca7532a8c081',
    's06a': '766d25f927a1116d565f97479786a42b93a275398310f775304668ec191a47e7',
    's07a': '20cb960a5d97e0b60c030ed0c17eea78bf6d7e0f5dc50945828e8c2106612546',
    's07b': 'bbe527b3883ad7c41e4999a8b1d49e64265100b7d8ff6a7724e3fce5d6fb7328',
    's07br': '04007a426525216049196b550e22fc0e922c75f78c6fcfc4b469f9d5defbbc47',
    's07c': '03904064a3d2d2bcd83f719cf7de0d780886ebeae5645dcc7e345acd7fe8cba1',
    's07cr': 'e3c3503599693be3d3729e0bfc09d364de85b46520eff3909b822a14a7dadfbd',
    's08a': '56a0d3aa551dd6eefda902497c3f0a90c458b4ab0a54b9a63b7fe3298606d4c9',
    's08b': '21c5534dd17e5579404b2b0b2f3c47fb324b27a363a108669e3818a3dee15ded',
    's08br': '064e8dbb2af7589a7122f02a51e202d43fd3e9bf05aa18258c5cd88621a2d69c',
    's08c': '5badd1f304a57a3e55af6d5fe15694c51398c602779a31ee2b7276ad9f9aafbb',
    's08cr': '1521588d917c0558839f915191ed5b643fba37a7d1fa4dc228951b433e1070c9',
    's09a': '4c698b375890c793c3622d410bffab7db48c01cfff393f458cd5712e316a7177',
    's09ar': '362fbe4c139197907498e38a1f56e403fe39b4a0217d34bfcf49cf86e86cb76b',
    's10a': '95f9cb0d5def5f30bb2133c0452b3aa49438f56c95535178d61eb11a03bb2e6e',
    's10ar': '465959ab31568740a4bf30bf0958865e485e48538e449a6b3c696c5fd7d52f69',
    's11a': '70be6cf00267ed663e29ce6b9598396e8fb7c60024b76ff86508244c56d39bf6',
    's11b': '280920ec9559d0c836bab8995de902f227759bb7430025a650f7c20633889f51',
    's11c': 'e49fbd3c76f8137fe4414699c7816143ea6c83c3dd1f8c44db9f1bd007e5ceec',
    's11d': 'b7e8487718b1c3dd835b3b71b785acc367469f5c84e7834d2b91518dc17da21e',
    's11e': '8400e639567b380f28320ccfc5d624b6aa16f8dafa80fdc212976ab386014a9a',
    's11g': '60c1e1882b4d9df99478a117a9bfb0d20eb58f4f37305aa46bb1658cf2761eb7',
    's11h': 'de8b36f6bdeb9871b28bf53c2fd13f3f53d836cadcf26fe735358e42151a478b',
    's11i': '706e9fa4b2b2288b6967cc0e519a109f0d2fd6da01dc190996f331b28e3f57e9',
    's12a': 'e99681d93e10f8cb1fd9fa0ae694bb1f5a517b18a42f8791d0df58feccdd2e1d',
    's12b': '7f7e125ea50101399608c859611515df3fb6f04c87ccfdcb10521d86a5aff71a',
    's12c': '3e22cf0791fffbef348149ba97e65b9d147488cb45992a1dd84e343414948cf1',
    's13a': '3af85549577319540e53c789f8a20fd10d8b080f74b309a3c6e966b453b75544',
    's14e': '0ad69a93f9aadf2e7b0b254cf6d39ad16c118d0af9686609b9df8ebcbed8986a',
    's15a': 'ab3bf00937e226119c4649e9aa5db7f24e4aab844cb550c752bc3ce1a06f735e',
    's15b': '5ab64d6c10801c11b0f672cbb4e68ab62ef1bf058944f5c3d32dbd073e3c8501',
    's15c': '7a6d398f600f359a04b8d9fcb7c006fdc888f4fcbdffd761e09ef4a932195483',
    's16a': '1bec05b1d61f2f5b6abffa1903abcea0ab9e5f4ddebb88ac64506c81548e6ccb',
    's16b': '811a2aa5d5cd7ba8673f3ca9cc3a89f07c8ac9e1f3f5843fed311557ebc0b9f6',
    's16c': '8217a2be487140af5bbded5f0dc37ab8cabedaf9af99d16256650ce27a8a5b50',
    's16d': 'c37c642eb06d7ec39364e4a1fac17e606804eee229e047102d4a2e93346e773f',
    's17a': 'a6b691ff0be4af526fb856847be0549dbe015b31b7fb137a1fbbe6027125d4d1',
    's17ar': 'a6b691ff0be4af526fb856847be0549dbe015b31b7fb137a1fbbe6027125d4d1',
    's18a': '4f605b802aef5c69ce4cc875165d41139acde9af1e9fdf419d0e4cee2bc7087e',
    's18ar': '17d33d059f09a7470b2e6f44efc2469f52f7ff74093542ffb4cdf52a5aa6c79d',
    's19a': '48390084a9a716bef980627c57df1867763a6502ad5109d2a6b3712e652840d7',
    's19ar': 'ef64d5fdb5e8285116ee2f8c693bc20f9af802dc6c16996f815d8823127352e6',
    's19b': 'd757942aca5d36ab95741801de1f68526c3a8e128018814f25655b7d72a7c249',
    's19br': '3d2d7c04d13dd3f55a97348f74eaf891615cfa203812d15494b53f9e570fe2bd',
    's20a': 'd14fdf0f3b5c98f72fd9f24fd119cdf88660528930ec784dc3d021b92e796925',
    's20ar': '4d6fee8a574d6b900eadff3925f2a38516c2d28784d6e38444ce6c9ece46e104',
    'select': '10350d22ceb73b58224a2da9cc71a87380415e304b4c161a787b491162636bc9',
    'select1': '6b101068fb3d41d9d634256f21cb094e13f331ed9fbbdb271be2a01ec631c145',
    'select2': '6b101068fb3d41d9d634256f21cb094e13f331ed9fbbdb271be2a01ec631c145',
    'select3': '6b101068fb3d41d9d634256f21cb094e13f331ed9fbbdb271be2a01ec631c145',
    'select4': '6b101068fb3d41d9d634256f21cb094e13f331ed9fbbdb271be2a01ec631c145',
    'selectd': '6b101068fb3d41d9d634256f21cb094e13f331ed9fbbdb271be2a01ec631c145',
    'sound': '4173d0fcbc7bfcd477d2e0fa6810b509bf6392efb01fd58a7fa114f003849816',
    'title': 'fb97721e30fd55cf6251e446d6e7d38e951049ec4703301da7fef7fe9c1afa6b',
}
TARGET_VR_OVERLAYS_HASH = {
    'camera': '33d5e225f34814ddc827e918a88e70535345c79cd77ec4ea5e9336c68cb00684',
    'movie': 'ddd1d8c812047388808d3210c871046b312f555333d175d93ad1440990735c70',
    'opening': 'a2a0751df48357df4bac6a73aa28da1450d8eff63ea83dfb6bbcdd81fa2ab344',
    'option': '40e504e60c0e6857726f771c9df358481bd89f63d5c0892b0937a13d6d36fe9a',
    'photo_m1': '4d09f9a89f5e6167de88f9e362619d83909d6ac1ed8b2985ea36b1af1a198a7f',
    'photo_m2': 'd7c3279543cc5fe309c214f4ea3c93046900ab162ead4a41bea3db5ee08632f5',
    'photo_n1': '634b2486063085bb750584c7c5e54d7998ba2bc26bbdf1579eb6ae68b6a76a92',
    'photo_n2': '2e4f3bbfe6df592b509d06758d23adf074cb381df8f8eee867bf391bdee56bef',
    'photo_n3': '5c9242a42230ebcee099c57f64b3235d0474bbe7b9138e1834c073fe639c178e',
    'select': 'fa8eec2a95979ba4bf68755a454ec91d3e723ff1ac2e75fd2ceca00b22a50296',
    'selectvr': '87ab9c17a99c65be6dfb59aad35006e58940c2b9f2dea70a0a1e50088b6685c0',
    'sound': 'bc0abafb4604a8fc1346a63e10a0587bc7df602a9fd4b90f9e6c5c0b847ac188',
    'vab_cfr': 'bba8bb118b6bdb277102093b722a065096dd2d209c294f1a3625a9448fbd3be5',
    'vab_clm': 'c18ea33776c7e7dbaa9e32bdc4cf511d21a538928c139099aaa530c5e53653db',
    'vab_fms': 'd08a363fd0dd5485d5464d4313cc80e3ca57604488a77fb1178f93a05b275a64',
    'vab_grn': '5f73014818a27f171768ed15c4864898c0824d771c7377b2f2b6d8095b56e4cf',
    'vab_nkt': '446ad3f771830407687b90c27d62a29697a9fc4b51e1af892fce1c331770ab10',
    'vab_psg': '6db9f9ad67d483c9ed657334ce59d64fed44c05e5c52b0ace0f905bebf72689e',
    'vab_scm': '2627939f2b8d7d47f9db14de3858d1241ba1afa3cc61ab73dbc7dc632d67906b',
    'vab_stg': '554e33f490619c209100dae7569475981a102792ea276382219900af2106238d',
    'vab_sud': 'a620f6487a2d70006821dec85a98b1db47a6d1e4369bdd0046464284a6d785f8',
    'vcd_n01': 'be4b2de7ef90ce39c274b2ae76218c89b305e3aea89aea623dd91afad0089553',
    'vcd_n02': '68bb72a036bd161e244b41b94f16b191651dc880dc76679ccc5a1c93af777077',
    'vcd_n03': '7e008ade3a8581fd26932a9c2fe242f640ba690d1f98f322f720354ec0085ba4',
    'vcd_n04': 'c4bee50f02d34a8e33b96ff3adb16bdfadff452994e1e66c4eec8129543bf9e0',
    'vcd_n05': '179de4726e44e0ad48d53110ff9e6ec90240cd7f8463ba8db0ed80ed29586c07',
    'vcd_n06': '858009f054adde758cab468ba2f5e8300f769cdada6bd1edc96e3793d1ff9e8b',
    'vefgh_01': 'c7047e1f5ebfde0eac28f162513908089ceecfb75dcdded16a700a97c21f1585',
    'vefgh_02': '9f5d966a1222959bab1dd407c5aff3c6da3add4fa5c322b12c0c40ba8ba3b4ce',
    'vefgh_03': '0b37518d03ce54c1949704fe2da2c9b91b20c2c527e17721bc3974068786841b',
    'vefgh_04': '4351fd981685d1091c3cc3b1823546a3712ea82ffc483094b657a16caeb3a2b8',
    'vefgh_05': 'c5830e751c1212f22642ca6bef1924820e6227c211e809650c662ef6cf0a3a2d',
    'vefgh_06': '1d55f7f595ccd75ccfe6b90ebc609c19cb6d96433d49f989986a2d6429a2b69d',
    'vefgh_07': 'c98097a8c4eb3d2d80a71fbb1ad7d733df80325f05dd7ffa052f5c30ddf71037',
    'vefgh_08': '82e5b69300536168746f5e2e0cb4ef19ee26da91b4ad5ddd404c82f06bf3e09f',
    'vefgh_09': 'b8f2e33ec4d276ecb1c8bf7d719fe84565c079b71c09a2f029f3cdfd32dc4869',
    'vefgh_10': 'eadc2f458b77b3f4e9781370cc98bdd328d83fd165ff858c1ce4cecb55c65bdd',
    'vijkl_01': 'dd17d6ba16892cd1449e71ad5a59ab70c9376c101bc8e997b9a8fead46c2aec0',
    'vijkl_02': '7b19973b2065cc98e0cc2b869c1820edfc99487ea9e43898a4152dfcadd5a944',
    'vijkl_03': '076c639788354d4f878b5eae5b3363658da2caa7b9397f07fc6c8a81bad9ba99',
    'vijkl_04': '4cf844a8b046386e1644256b6fecc8b67d8561823d3783e506d97cdb2acdd4e5',
    'vijkl_05': 'f6be0ff2fb5a3388f6d3b397d5291f5ef1f7651f2ea0e05894f1cc86bdf3de70',
    'vijkl_06': 'a6ac21344d324ab30f7d16edbebeb48f1d060d7666b7fae8db65510b147781b3',
    'vijkl_07': '758d1cf801ea0a31b1d82a57ae553d951e326eed6d49e7871dec0f4a5a20fd82',
    'vijkl_08': 'f48fcad8a8ffeb5ec00f98b43700d46fcfe073f0a1b459b48c392ede5b9930e2',
    'vijkl_09': '64522c4d342bdb7ee149c14d5d30393bd78bb0ba93a3d40a9b718d4c0eda338f',
    'vijkl_10': 'd09418e47278fc5d2a96c791be97a0d231391b24d20972ce83a5775bc1d5eee7',
    'vr_cfr01': 'e3540697d18e36e02328d53779eb3c3c8adcd842615fcf9a9d69993b80e402a2',
    'vr_cfr02': '9757d956ea9aad5a4cd7625ef23a36bab0d914526e0d9178eed13bd1ba2fe9e6',
    'vr_cfr03': 'c4c5f7dea2cf0409f3ae603e805a9c50628094091da7fc607e1188003ae5f181',
    'vr_cfr04': '20f73d6c77a8ecf7585dcb1d13abab74887feaca20a7b720efb3e5cf1c2de9b1',
    'vr_cfr05': '8d9a2c0bec8bd8e892ce8aa08e373ecd38a2e5c1351eb6fc517e2d72a82f92e8',
    'vr_clm01': '0d06593a1ee1ae3f5b72de9c18b6f58fe3ecb0b00e8ac7c4f422d4eb91d6f308',
    'vr_clm02': '8967cbc3c9c808a69a4b5654022209e008bfbf6e0bcfe8f6c41aecf58660ad8d',
    'vr_clm03': 'b1b340104058235bd3c25d2f3871bcd2eb026115c681c17d5cac357e6d3f7c22',
    'vr_clm04': '78008b3820689056c81efb75eba63b4c6cdc0a710ec0f56af6a30f6995d4acde',
    'vr_clm05': '4e87cb870e5111d855498c8ba84e97fb75bc850bb34facb454c2df758c60f37b',
    'vr_fms01': '17cc7a8894cf642e1ca2c222bfbd1ae0f7617e7032876ccea6a680bf3a38c679',
    'vr_fms02': '3e0a8f1164fe3b6a0ce62a07d190538bf7e790359694e16851c45371072b91fb',
    'vr_fms03': '0a8d39c760b2799002b707eeed74db9a88ff20c199a8d37f5d9fa9a0e7191ec5',
    'vr_fms04': '90094b757cfc00154a8b59d1f3b7fa06df7b21c734b06b662e962776a165bac1',
    'vr_fms05': '07ffa2646c98dc261e399a2f9ebd05203d769bebf4a494688dba9caa6bbe94cc',
    'vr_grn01': '2bf060f4a39e08fa5c28eed3b2b7419ea37d2f51890400c78fdb8635fa4de885',
    'vr_grn02': '0f26c0f2e3b509b5fdc14f35df0d1eecb8cd364f315af4e832397b116572ee59',
    'vr_grn03': '93cf09c7cb238eb7c9d44cb233acf234b3242b3e72fdd4aec254407091adab1e',
    'vr_grn04': 'b3189ddb34efa31166c8d33261bb7a1faf0ad402542026486b8c7dd1cc93664c',
    'vr_grn05': 'dbbb5eba5b191a009862568d5d17ec28e00152c383c15ce01aa07fd52da5e5a7',
    'vr_nkt01': '07161fb79db67a6f4f08cd0d3db87825c1a1a55afad7c87001aed968bc92677e',
    'vr_nkt02': '168a45e7ac9c3a9c4454a9048797a4b1efacfe17076038a5c27df191b7661112',
    'vr_nkt03': '786ad1a792e27dfbe1b2ab71c28416a8287d85c046524a8986e99ac39b0b283b',
    'vr_nkt04': 'e39592adcd7cb51b321105330a013b43886101d19f6308f4c423724f5f523174',
    'vr_nkt05': '0c58e1c20a614cc8dfb3411b05fb1879994e42374d0288699912d44ad3b1b5c2',
    'vr_psg01': '8ff3058151426649df67d8cf7cb13e2e63eea5ccadbc1bfed1be6fbad5ae2d8d',
    'vr_psg02': 'f84421c4a52296e31af9625a35ac9e12007306c112906ddfec97286fc52fde63',
    'vr_psg03': '2c80a4431576af6de08d0a64ef0763d8f4bfca4d4f3b7cc7d27ae9496f8af061',
    'vr_psg04': 'c7703abdfb59ca4d04a84a03fc2d42c26b14ff14fac001c3fbdf0a17228d8731',
    'vr_psg05': 'abcdac864c5c490bfb4e4c3da9756878222571a6b1a9bd63d481e5db47083d0c',
    'vr_scm01': '869b72323703f398289c9e59937afc135d8dede4ced8dda635a4edf55338d1c5',
    'vr_scm02': '922b222f5ad0058054ade591e0f43823230c744ccdf2bb088b7633cd698ff675',
    'vr_scm03': '853c533374616189dcc4da5556f83c1a5b5ef86b445dd2694c9a2ad3a3ee646e',
    'vr_scm04': 'a1400556a5067d0fbd9c1e5609fa2120cfb276b31aca430250a30b25e88c3bef',
    'vr_scm05': 'ee5936380bb945cc0eae69ae907f57bffb22d90ecef1d5cfd237b5382ed47a1e',
    'vr_stg01': 'd3ca029f51ec4d6cdaa395c2a349d0e22583d031b89029c8ad1e9f8c2bf428cb',
    'vr_stg02': 'e8a03cb422e7e4e9950b5c1a5c18bb65b472f89169b7009c71ed13a9d6d3d02f',
    'vr_stg03': '7ed01303c6a1878d28f3aaabb2cdc47ec86bc6fe1811fe5d27fc8cead3d75233',
    'vr_stg04': '6fe653b113082081917ec3f52b6ebaf11083e092ad919e6c5a6e2496b3b93a6a',
    'vr_stg05': '9b5964c6290b59ebd111b184cc4565b3781165edfd8ec93a8dc7b73368ab8bcb',
    'vr_sud01': '41f4f0bd54b6ccd45877dd8b35d40106d4f5be97fadfe45ce10c7cd6e7788c99',
    'vr_sud02': '8830cfab59f86056690b0f74cbeb51424b5776091b1bd52fd6dc84c7db0c5408',
    'vr_sud03': '456126883baace557e8f4fcb32660dd071a9587b3299fe0602c99359da4c574b',
    'vr_sud04': '286dae7ca61adb49ee84566c4188571c36ee7783874424dc2cdb52446e9cc630',
    'vr_sud05': '461cc1ef0cfa858be270da83da736ad04557fa7e388839d8f786870c396957d1',
    'vr_sud06': '2e84f6679c11a0cda69bb9d249a4d37378ce7e08685c7fa2d578b9d8f495c71c',
    'vr_sud07': 'b3b3c512b37b82d059a79ab4df47282fddef1a1c33bc1180f4dcbf292f69d8e7',
    'vr_sud08': '84e4c6c25797d164cf56f91fec79734b6efff3750b97156aa054cdc89f130fa7',
    'vr_sud09': 'e77f4e558ec9e5fecbf3fc939958875b38b40b40a4a9403e5ca6757e60b16639',
    'vr_sud10': '3b34df06259b8cb03d29ea9569dd9684090c713e44e1bfa4b84cc1f5c7311914',
    'vr_sud11': '870ef98c534f7c8880b83bdeb52f175ae09a3c306a21a095bc009c709956163f',
    'vr_sud12': 'd980455e00d779c60abe21407dc312586d1a73a355ea57e6a469aff527460f36',
    'vr_sud13': '2d3f45e3399d48b3cb328790176596d2c690e015c5054424aa131de33e936ab3',
    'vr_sud14': '3b986c02aa7e6b69ac1a7f0aec4e66d7111f4a65afbced1e424ea39f6bdaa4b7',
    'vr_sud15': '232040540e92f233c14c8e7da7d904b414c0381e07a0db9f496ab1d099f4cd49',
    'vrsave': 'ee1eeb23395a900bc9e36348db0a393e5a86e0ed4996180e16626e7d9156c674',
    'vrtitle': 'ade8ca6f7d0ca99d371abcfbca53987415b43e66f326f9ee77518f1b7a4aff39',
}
CACHED_GOOD_EXE = '_mgsi.matching.exe'
OBJ_EXE = '../obj/_mgsi.exe'
OBJ_VR_EXE = '../obj_vr/_mgsi.exe'
OVERLAY_EXE_PATH = '../obj/'
OVERLAY_VR_EXE_PATH = '../obj_vr/'
FUNCTIONS_FILE = 'functions.txt'
EXE_SIZE = 641024
TEXT_SEG_OFFSET = 0x50B8
TEXT_SEG_BASE = 0x800148B8
COLORS = os.environ.get('COLORS') != 'false'
SUPPORTS_EMOJIS = locale.getpreferredencoding().lower().startswith('utf')
SIDE_BY_SIDE_PADDING = 40

def get_functions():
    ret = []
    with open(FUNCTIONS_FILE) as f:
        for line in f:
            split = line.rstrip().split(' ')
            assert len(split) == 3
            addr, size, name = split
            ret.append((int(addr, 16), int(size), name))
    return ret

def disasm(code, addr):
    from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32
    md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32)
    dis = []

    l = len(code)
    processing_addr = addr
    last_processed = addr

    while processing_addr < (addr + l):
        for inst in md.disasm(code, processing_addr):
            dis.append("0x%X: %s %s" % (inst.address, inst.mnemonic, inst.op_str))
            processing_addr += 4

        if processing_addr >= (addr + l):
            break

        code = code[processing_addr - last_processed:]

        # This instruction could not be disassembled by capstone,
        # so print the hex bytes of the instruction:
        dis.append('0x%X: %02X %02X %02X %02X' % (processing_addr, code[0], code[1], code[2], code[3]))

        processing_addr += 4
        last_processed = processing_addr
        code = code[4:]

    return dis

def chunk(xs, n):
    n = max(1, n)
    return (xs[i:i+n] for i in range(0, len(xs), n))

def hexdump(data):
    return ' '.join(['{:02X}'.format(x) for x in data])

def hexdump_lines(data, addr):
    dump = hexdump(data)
    splitted = dump.split(' ')
    chunks = chunk(splitted, 4)
    i = 0
    ret = []
    for c in chunks:
        ret.append('0x{:X}: {}'.format(addr + i, ' '.join(c)))
        i += 4
    return ret

def sha256(path):
    with open(path,'rb') as f:
        return hashlib.sha256(f.read()).hexdigest()

def try_import_capstone():
    try:
        from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32
    except:
        print('warning: python-capstone not found for asm diffing. try `pip install capstone`')
        print('falling back to hex diff')
        return False
    return True

def extract_func_code(data):
    ret = []
    funcs = get_functions()
    for func in funcs:
        addr, size, name = func
        start = TEXT_SEG_OFFSET + (addr - TEXT_SEG_BASE)
        code = data[start:start+size]
        ret.append((addr, size, name, code))
    return ret

def compare_exes(a_path, b_path, have_capstone):
    with open(a_path, 'rb') as f:
        a_data = f.read()
    with open(b_path, 'rb') as f:
        b_data = f.read()

    size = len(a_data)
    assert size == len(b_data)

    a_funcs = extract_func_code(a_data)
    b_funcs = extract_func_code(b_data)

    assert len(a_funcs) == len(b_funcs)

    a_diff_found = False
    multiple_funcs_warning = True

    diff_funcs = []

    for i in range(len(a_funcs)):
        addr, size, name, a_code = a_funcs[i]
        _, _, _, b_code = b_funcs[i]

        if a_code != b_code:
            diff_funcs.append((addr, name, a_code, b_code))

    print('differing funcs:', len(diff_funcs))

    jump_to_func = None
    for addr, name, a_code, b_code in diff_funcs:
        if a_diff_found and multiple_funcs_warning and sys.stdout.isatty() and not jump_to_func:
            print('multiple funcs have differences, so the entire exe probably blew up.')
            print('options:')
            print('show next func: <Enter> - show remaining funcs a<Enter> - quit: q<Enter>')
            print('jump to func: <search query><Enter>')
            print('note: this tool currently assumes funcs are at the correct offsets in the built exe')
            selection = input('selection: ')
            print()
            if selection == 'a':
                multiple_funcs_warning = False
            elif selection == 'q':
                sys.exit(1)
            elif selection != '':
                jump_to_func = selection.lower()

        if jump_to_func and jump_to_func not in name.lower():
            continue
        elif jump_to_func:
            multiple_funcs_warning = True
            jump_to_func = None

        dis_func = disasm if have_capstone else hexdump_lines
        a_dis = dis_func(a_code, addr)
        b_dis = dis_func(b_code, addr)

        a_len = len(a_dis)
        b_len = len(b_dis)
        print('-', name, '-')
        print('Current', (SIDE_BY_SIDE_PADDING - len('Current')) * ' ', 'Target')
        for i in range(max(a_len, b_len)):
            a = '' if i >= a_len else a_dis[i]
            b = '' if i >= b_len else b_dis[i]

            padding_needed = 0
            if have_capstone:
                padding_needed = SIDE_BY_SIDE_PADDING - len(a)
                a_padded = a + (' ' * padding_needed)
            else:
                a_padded = a + '  '

            line = a_padded + '  ' + b
            if COLORS and a != b:
                print(colored(line, 'red'))
            else:
                print(line)
        print()
        a_diff_found = True

    if not a_diff_found:
        print('nothing to diff found. the changed bytes were probably outside the functions?')

def diff_exe():
    have_capstone = try_import_capstone()

    if not os.path.exists(CACHED_GOOD_EXE):
        print('no cached matching exe exists for diffing, do a successful build first')
        return

    if os.stat(CACHED_GOOD_EXE).st_size != EXE_SIZE:
        print('cached matching exe is wrong size?')
        return

    if os.stat(OBJ_EXE).st_size != EXE_SIZE:
        print(OBJ_EXE, "is the wrong size, diffing only supported if it's correct")
        return

    compare_exes(OBJ_EXE, CACHED_GOOD_EXE, have_capstone)

def cache_good_exe():
    if not os.path.exists(CACHED_GOOD_EXE):
        shutil.copy(OBJ_EXE, CACHED_GOOD_EXE)

def cached_good_overlay_path(overlay):
    return f"{overlay}.matching.bin"

def cache_good_overlay(overlay, overlay_path):
    cached_overlay = cached_good_overlay_path(overlay)
    if not os.path.exists(cached_overlay):
        shutil.copy(overlay_path, cached_overlay)

def green(msg):
    extra = ' 👌' if SUPPORTS_EMOJIS else ''
    print(colored(msg, 'green') + extra)

def red(msg):
    extra = ' 💩' if SUPPORTS_EMOJIS else ''
    print(colored(msg, 'red') + extra)

def ok(name):
    func = green if COLORS else print
    func('OK: {} matches target hash'.format(name))

def fail(name):
    func = red if COLORS else print
    func('FAIL: {} does not match target hash '.format(name))

def main():
    if os.name == 'nt':
        colorama_init(strip=False)

    if not os.path.exists(OBJ_EXE):
        print(OBJ_EXE, "doesn't exist")
        return

    # TODO - once all overlays are correctly building,
    # print an error if some overlay doesn't exist

    exe_hash = sha256(OBJ_EXE)

    failed = False
    if exe_hash != TARGET_HASH:
        fail(OBJ_EXE)
        if not os.environ.get('APPVEYOR'):
            diff_exe()
        failed = True
    else:
        ok(OBJ_EXE)
        cache_good_exe()

    if os.path.exists(OBJ_VR_EXE):
        exe_vr_hash = sha256(OBJ_VR_EXE)
        if exe_vr_hash != TARGET_VR_HASH:
            fail(OBJ_VR_EXE)
            failed = True
        else:
            ok(OBJ_VR_EXE)

    TARGET_CPE_HASH = sha256(OBJ_EXE.replace("_mgsi.exe", "_mgsi.cpe"))

    for overlay, overlay_target_hash in TARGET_OVERLAYS_HASH.items():
        overlay_path = os.path.join(OVERLAY_EXE_PATH, f"{overlay}.bin")

        if not os.path.exists(overlay_path):
            continue

        # First check the main executable built for this overlay.
        # We are running the linker separately for each overlay,
        # so actually the main executable is rebuilt for each overlay.
        # It's not a problem, because it's the same exact executable,
        # but sometimes, if you are not careful, that won't be the case,
        # for example if some additional PsyQ functions land in main exe.

        # FIXME: for now this check is disabled :( - it reported
        # false positive mismatch on main exe built for s11d - cpe files are different,
        # but after running them through cpe2exe they are identical.
        # But remember: we are STILL checking the generated overlay files - this is
        # what matters, this check was only to make our work easier.
        # I don't know what's the reason (maybe "rcossin_tbl" in
        # RotMatrixZYX in s11d and RotMatrixZYX_gte in main exe causes the problem)
        # I don't want to run cpe2exe for each overlay (increasing the build time)
        # and compare those exes (but it would fix the problem).

        #for run in ["lhs", "rhs"]:
        #    overlay_main_exe_path = OBJ_EXE.replace("_mgsi.exe", f"_mgsi_{overlay}_{run}.cpe")
        #    exe_hash = sha256(overlay_main_exe_path)
        #    if exe_hash != TARGET_CPE_HASH:
        #        fail(f"{overlay_main_exe_path} (something changed in main executable used to build the corresponding overlay)")
        #        failed = True

        overlay_hash = sha256(overlay_path)
        if overlay_hash != overlay_target_hash:
            fail(overlay_path)
            failed = True

            # TODO: select depending on comparison target.
            stagedir = 'stage'
            #stagedir = 'stagevr'

            # Is it only uninitialized memory?
            good_overlay = cached_good_overlay_path(overlay)
            if os.path.exists(good_overlay):
                try:
                    extract(os.path.join(OVERLAY_EXE_PATH, f"{overlay}_lhs.bin"),
                        os.path.join(OVERLAY_EXE_PATH, f"{overlay}_rhs.bin"),
                        good_overlay, None)
                    print(colored("... but the only difference is uninitialized memory!", 'yellow'))
                    print(colored("... You can fix it by rerunning extraction with this command:", 'yellow'))
                    print(colored(f"{sys.executable} uninitializer.py extract ../obj/{overlay}_lhs.bin ../obj/{overlay}_rhs.bin {good_overlay} ../um/{stagedir}/{overlay}.bin", 'yellow'))
                except:
                    # Extraction failed
                    pass
        else:
            ok(overlay_path)
            cache_good_overlay(overlay, overlay_path)

    if failed:
        func = red if COLORS else print
        func("FAIL: some files do not match target hash")
        sys.exit(1)

if __name__ == '__main__':
    main()
