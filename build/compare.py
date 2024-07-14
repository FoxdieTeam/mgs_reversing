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
CACHED_GOOD_EXE = '_mgsi.matching.exe'
OBJ_EXE = '../obj/_mgsi.exe'
OBJ_VR_EXE = '../obj_vr/_mgsi.exe'
OVERLAY_EXE_PATH = '../obj/'
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

            # Is it only uninitialized memory?
            good_overlay = cached_good_overlay_path(overlay)
            if os.path.exists(good_overlay):
                try:
                    extract(os.path.join(OVERLAY_EXE_PATH, f"{overlay}_lhs.bin"),
                        os.path.join(OVERLAY_EXE_PATH, f"{overlay}_rhs.bin"),
                        good_overlay, None)
                    print(colored("... but the only difference is uninitialized memory!", 'yellow'))
                    print(colored("... You can fix it by rerunning extraction with this command:", 'yellow'))
                    print(colored(f"{sys.executable} uninitializer.py extract ../obj/{overlay}_lhs.bin ../obj/{overlay}_rhs.bin {good_overlay} ../um/{overlay}.bin", 'yellow'))
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
