#!/usr/bin/env python3
import glob
import argparse
import sys
import os
import time
import subprocess
import re
import tempfile
import platform
from shutil import which
from ninja import BIN_DIR
from pathlib import Path
# local copy as the pip version doesn't have dyndeps in build() func
import ninja_syntax

os.environ['WINEDEBUG'] = '-all'
os.environ['TMPDIR'] = tempfile.gettempdir()

has_wine = bool(which('wine'))
has_wibo = bool(which('wibo'))
has_cpp = bool(which('cpp'))

# Native preprocesor doesn't work under WSL or MacOs
if "microsoft-standard" in platform.uname().release or platform.system() == 'Darwin':
    has_cpp = False

def parse_arguments():
    parser = argparse.ArgumentParser(description='MGS Ninja build script generator')

    # Optional
    parser.add_argument('--psyq_path', type=str, default=os.environ.get("PSYQ_SDK") or "../../psyq_sdk",
                        help='Path to the root of the cloned PSYQ repo')
    parser.add_argument('--variant', type=str, default='main_exe', choices=['main_exe', 'vr_exe', 'dev_exe'],
                        help='Variant to build: main_exe for MGS Integral Disc 1/2 (SLPM_862.47/SLPM_862.48), vr_exe for MGS Integral VR Disc (SLPM_862.49), dev_exe for non-matching build with debug mods that can be freely modified and loaded into an emulator')

    args = parser.parse_args()

    args.psyq_path = os.path.relpath(args.psyq_path).replace("\\","/")

    args.obj_directory = 'obj'
    if args.variant == 'vr_exe':
        args.obj_directory = 'obj_vr'
    elif args.variant == 'dev_exe':
        args.obj_directory = 'obj_dev'

    args.defines = ['INTEGRAL']
    if args.variant == 'vr_exe':
        args.defines += ['VR_EXE']
    elif args.variant == 'dev_exe':
        args.defines += ['DEV_EXE']

    print("psyq_path = " + args.psyq_path)
    return args

def prefix(pfx, cmd):
    if pfx == "wibo" and has_wibo:
        return f"wibo {cmd}"
    if has_wine:
        return f"wine {cmd}"
    return cmd

def ninja_run():
    ninja = os.path.join(BIN_DIR, 'ninja')
    ninja_args = [] # TODO: pass through args to ninja?

    # warrnings that were probably in the original code
    # TODO: hide these when building locally
    warning_whitelist = [
        r'select\.c:\d+: warning: control reaches end of non-void function',
        r'select\.c:\d+: warning: unsigned int format, pointer arg \(arg 2\)',
        r'sd_drv\.c:\d+: warning: `temp\' might be used uninitialized in this function',
        r'stream\.c:\d+: warning: `dir_idx\' might be used uninitialized in this function',
        r'sd_main\.c:\d+: warning: unused variable `buffer\'',
        r'sd_drv\.c:\d+: warning: unused variable `temp\'',
        r'sd_cli\.c:\d+: warning: control reaches end of non-void function',
        r'radiomes\.c:\d+: warning: unused variable `pad\'',
        r'radiomem\.c:\d+: warning: unused variable `pad\'',
        r'item\.c:\d+: warning: `state\' might be used uninitialized in this function',
        r'memcard\.c:\d+: warning: `op\' might be used uninitialized in this function',
        r'memcard\.c:\d+: warning: `count\' might be used uninitialized in this function',
        r'door\.c:\d+: warning: unused variable `pad\'',
        r'motion\.c:\d+: warning: `time\' might be used uninitialized in this function',
        r'motion\.c:\d+: warning: unused variable `unused\'',
        r'motion\.c:\d+: warning: `archive2\' might be used uninitialized in this function',
        r'motion\.c:\d+: warning: `shift2\' might be used uninitialized in this function',
        r'motion\.c:\d+: warning: `archive\' might be used uninitialized in this function',
        r'memcard\.c:\d+: warning: `return\' with no value, in function returning non-void',
        r'main\.c:\d+: warning: control reaches end of non-void function',
        r'control\.c:\d+: warning: `vy\' might be used uninitialized in this function',
        r'font\.c:\d+: warning: `m2\' might be used uninitialized in this function',
        r'radar\.c:\d+: warning: `pWalls\' might be used uninitialized in this function',
        r'radar\.c:\d+: warning: `ppWalls\' might be used uninitialized in this function',
        r'sndtst\.c:\d+: warning: `name\' might be used uninitialized in this function',
        r'sndtst\.c:\d+: warning: `code\' might be used uninitialized in this function',
        r'select\.c:\d+: warning: `proc_id\' might be used uninitialized in this function',
        r'select\.c:\d+: warning: `entry_name\' might be used uninitialized in this function',
        r'mts_new\.c:\d+: warning: control reaches end of non-void function',
        r'mosaic\.c:\d+: warning: unused variable `unused\'',
        r'vib_edit.c:\d+: warning: too many arguments for format',
        r'action.c:\d+: warning: assignment of read-only location',
        r'sphere.c:\d+: warning: `xoff\' might be used uninitialized in this function',
        r'sphere.c:\d+: warning: `yoff\' might be used uninitialized in this function',
        r'sphere.c:\d+: warning: `tpage\' might be used uninitialized in this function',
        r'sphere.c:\d+: warning: `clut\' might be used uninitialized in this function',
        r'sphere.c:\d+: warning: `u0\' might be used uninitialized in this function',
        r'sphere.c:\d+: warning: `v0\' might be used uninitialized in this function',
        r'sphere.c:\d+: warning: `u1\' might be used uninitialized in this function',
        r'sphere.c:\d+: warning: `v1\' might be used uninitialized in this function',
        r'blur\.c:\d+: warning: unused variable `pad1\'',
        r'blur\.c:\d+: warning: unused variable `pad2\'',
        r'blur\.c:\d+: warning: unused variable `pad3\'',
        r'rcm2\.c:\d+: warning: unused variable `mat\'',
        r'ending2\.c:\d+: warning: unused variable `pad\'',
        r'torture\.c:\d+: warning: unused variable `pad\'',
        r'ending2\.c:\d+: warning: `var_s1\' might be used uninitialized in this function',
        r'ending2\.c:\d+: warning: `var_s6\' might be used uninitialized in this function',
        r'smoke\.c:\d+: warning: `s00a_dword_800C34C8\' defined but not used',
        r'smoke3\.c:\d+: warning: unused variable `unused\'',
        # rope.c warnings (PR #2135)
        r'rope\.c:\d+: warning: assignment makes integer from pointer without a cast',
        r'rope\.c:\d+: warning: passing arg \d+ of `.*\' makes pointer from integer without a cast',
        r'rope\.c:\d+: warning: passing arg \d+ of `.*\' makes integer from pointer without a cast',
        r'rope\.c:\d+: warning: assignment makes pointer from integer without a cast',
        r'rope\.c:\d+: warning: comparison between pointer and integer',
        r'rope\.c:\d+: warning: unused variable `.*\'',
        r'rope\.c:\d+: warning: `.*\' might be used uninitialized in this function',
    ]

    if os.environ.get('APPVEYOR'):
        with subprocess.Popen([ninja] + ninja_args, stdout=subprocess.PIPE, encoding='utf8') as proc:
            for line in proc.stdout:
                sys.stdout.write(line)
                if 'warning: ' in line:
                    found = False
                    for whitelisted in warning_whitelist:
                        if re.search(whitelisted, line):
                            found = True
                            break
                    if not found:
                        print('^ this warning must be fixed in order to merge', file=sys.stderr)
                        print('.. and all other warnings minus these:')
                        for whitelisted in warning_whitelist:
                            print('    ', whitelisted)
                        sys.exit(1)
            return proc.wait()
    else:
        return subprocess.call([ninja] + ninja_args)

args = parse_arguments()

f = open("build.ninja", "w")
ninja = ninja_syntax.Writer(f)

ninja.variable("psyq_path", args.psyq_path)
ninja.newline()

ninja.variable("psyq_path_backslashed", args.psyq_path.replace('/', '\\'))
ninja.newline()

ninja.variable("psyq_asmpsx_44_exe", prefix("wibo", "$psyq_path/psyq_4.4/bin/asmpsx.exe"))
ninja.newline()

preprocessor_defines = ' '.join(f'-D{define}' for define in args.defines)

if has_cpp:
    ninja.variable("psyq_c_preprocessor_44_exe", f"cpp -nostdinc {preprocessor_defines}")
else:
    ninja.variable("psyq_c_preprocessor_44_exe", prefix("wine", f"$psyq_path/psyq_4.4/bin/cpppsx.exe {preprocessor_defines}"))
ninja.newline()

ninja.variable("psyq_cc_44_exe", prefix("wine", "$psyq_path/psyq_4.4/bin/cc1psx.exe"))
ninja.newline()

ninja.variable("psyq_aspsx_44_exe", prefix("wibo", "$psyq_path/psyq_4.4/bin/aspsx.exe"))
ninja.newline()

if has_cpp:
    ninja.variable("psyq_c_preprocessor_43_exe", f"cpp -nostdinc {preprocessor_defines}")
else:
    ninja.variable("psyq_c_preprocessor_43_exe", prefix("wine", f"$psyq_path/psyq_4.3/bin/cpppsx.exe {preprocessor_defines}"))
ninja.newline()

ninja.variable("psyq_cc_43_exe", prefix("wine", "$psyq_path/psyq_4.3/bin/cc1psx.exe"))
ninja.newline()

ninja.variable("psyq_aspsx_2_56_exe", prefix("wibo", "$psyq_path/aspsx/2.56/aspsx.exe"))

ninja.variable("psyq_aspsx_2_81_exe", prefix("wibo", "$psyq_path/aspsx/2.81/aspsx.exe"))

ninja.variable("psyq_psylink_exe", prefix("wibo", "$psyq_path/psyq_4.4/bin/psylink.exe"))
ninja.newline()

ninja.variable("psyq_psylink_overlay_fopen_mod_exe", prefix("wibo", "$psyq_path/psyq_4.4/bin/psylink_overlay_fopen_mod.exe"))
ninja.newline()

ninja.variable("src_dir", "../source")
ninja.newline()

if args.variant == 'vr_exe':
    ninja.variable("psx_incdir", "/psyq_4.5/include")
else:
    ninja.variable("psx_incdir", "/psyq_4.4/include")
ninja.newline()

# /l = produce linkable output file
# /q = run quietly
ninja.rule("psyq_asmpsx_assemble", "$psyq_asmpsx_44_exe /l /q $in,$out", "Assemble $in -> $out")
ninja.newline()

includes = "-I " + args.psyq_path + "$psx_incdir" + " -I $src_dir" + " -I $src_dir/include"

ninja.rule("psyq_c_preprocess_44", "$psyq_c_preprocessor_44_exe -undef -D__GNUC__=2 -D__OPTIMIZE__ " + includes + " -lang-c -Dmips -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D__CHAR_UNSIGNED__ -D_LANGUAGE_C -DLANGUAGE_C $in $out", "Preprocess $in -> $out")
ninja.newline()

ninja.rule("convert_c_encoding", f"{sys.executable} $src_dir/../build/convjp.py $in $out", "Convert $in from UTF-8 to EUC-JP")
ninja.newline()

# generate header deps, adds edges to the build graph for the next build -M option will write header deps
ninja.rule("psyq_c_preprocess_44_headers", "$psyq_c_preprocessor_44_exe -M -undef -D__GNUC__=2 -D__OPTIMIZE__ " + includes + " -lang-c -Dmips -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D__CHAR_UNSIGNED__ -D_LANGUAGE_C -DLANGUAGE_C $in $out", "Preprocess for includes $in -> $out")
ninja.newline()

ninja.rule("header_deps", f"{sys.executable} $src_dir/../build/hash_include_msvc_formatter.py $in $out", "Include deps fix $in -> $out", deps="msvc")
ninja.newline()

ninja.rule("asm_include_preprocess_44", f"{sys.executable} $src_dir/../build/include_asm_preprocess.py {args.obj_directory} $in $out", "Include asm preprocess $in -> $out")
ninja.newline()

ninja.rule("asm_include_postprocess", f"{sys.executable} $src_dir/../build/include_asm_fixup.py $in $out", "Include asm postprocess $in -> $out")
ninja.newline()

ninja.variable("gSize", "8")
ninja.newline()

ninja.rule("psyq_cc_44", "$psyq_cc_44_exe -quiet -O2 -G $gSize -g0 -Wall $in -o $out""", "Compile $in -> $out")
ninja.newline()

ninja.rule("psyq_aspsx_assemble_44_overlays", "$psyq_aspsx_44_exe -q -G0 -s-overlay $in -o $out""", "Compile $in -> $out")
ninja.newline()

ninja.rule("psyq_aspsx_assemble_44", "$psyq_aspsx_44_exe -q $in -o $out", "Assemble $in -> $out")
ninja.newline()

ninja.rule("psyq_aspsx_assemble_2_81_overlays", "$psyq_aspsx_2_81_exe -q -G0 -s-overlay $in -o $out""", "Compile $in -> $out")
ninja.newline()

ninja.rule("psyq_aspsx_assemble_2_81", "$psyq_aspsx_2_81_exe -q $in -o $out", "Assemble $in -> $out")
ninja.newline()

# For some reason 4.3 cc needs TMPDIR set to something that exists else it will just die with "cc1psx.exe: /cta04280: No such file or directory"
ninja.rule("psyq_cc_43", "$psyq_cc_43_exe -quiet -O2 -G $gSize -g0 -Wall $in -o $out", "Compile $in -> $out")
ninja.newline()

ninja.rule("psyq_aspsx_assemble_2_56", "$psyq_aspsx_2_56_exe -q $in -o $out", "Assemble $in -> $out")
ninja.newline()

ninja.rule("linker_command_file_preprocess", f"{sys.executable} $src_dir/../build/linker_command_file_preprocess.py $in $psyq_sdk $out {' '.join(args.defines)} $overlay $overlay_suffix", "Preprocess $in -> $out")
ninja.newline()

# VR-DISC links with Runtime Library Release 4.5
psyq_lib = f'{args.psyq_path}/psyq_4.5/lib' if args.variant == 'vr_exe' else f'{args.psyq_path}/psyq_4.4/lib'

ninja.rule("psylink", f"$psyq_psylink_exe /l {psyq_lib} /c /n 4000 /q /gp .sdata /m \"@$src_dir/../{args.obj_directory}/linker_command_file$suffix.txt\",$src_dir/../{args.obj_directory}/_mgsi$suffix.cpe,$src_dir/../{args.obj_directory}/asm$suffix.sym,$src_dir/../{args.obj_directory}/asm$suffix.map", "Link $out")
ninja.newline()

ninja.rule("create_dummy_file_overlays", f"{sys.executable} $src_dir/../build/create_dummy_file.py $src_dir/../{args.obj_directory}/$overlay_bin $src_dir/../{args.obj_directory}/$overlay_bss_bin", "Create dummy files $overlay_bin, $overlay_bss_bin")
ninja.newline()

ninja.rule("psylink_overlay_fopen_mod", f"$psyq_psylink_overlay_fopen_mod_exe /l {psyq_lib} /c /n 4000 /q /gp .sdata /m \"@$src_dir/../{args.obj_directory}/linker_command_file$suffix.txt\",$src_dir/../{args.obj_directory}/_mgsi$suffix.cpe,$src_dir/../{args.obj_directory}/asm$suffix.sym,$src_dir/../{args.obj_directory}/asm$suffix.map", "Link (uninitialized) $out")
ninja.newline()

ninja.rule("uninitializer", f"{sys.executable} $src_dir/../build/uninitializer.py inject $in $out", "Uninitializer $in -> $out")
ninja.newline()

# TODO: update the tool so we can set the output name optionally
# cmd /c doesn't like forward slashed relative paths
ninja.rule("cpe2exe", prefix("wine", "cmd /c \"$psyq_path_backslashed\\psyq_4.3\\bin\\cpe2exe.exe -CJ $in > NUL\""), "cpe2exe $in -> $out")
ninja.newline()

ninja.rule("hash_check", f"{sys.executable} $src_dir/../build/compare.py $in", "Hash check $in")
ninja.newline()

def create_psyq_ini(sdkDir, psyqDir):
    data = ""
    with open(sdkDir + "/" + psyqDir + "/bin/psyq.ini.template", 'r') as file:
        data = file.read()
    data = data.replace("$PSYQ_PATH", sdkDir + "/" + psyqDir)
    data = data.replace("/", "\\")
    ini_file = open(sdkDir + "/" + psyqDir + "/bin/psyq.ini", "w")
    ini_file.write(data)

def init_psyq_ini_files(sdkDir):
    create_psyq_ini(sdkDir, "psyq_4.3")
    create_psyq_ini(sdkDir, "psyq_4.4")

def get_files_recursive(path, ext):
    collectedFiles = []
    # r=root, d=directories, f = files
    for r, d, f in os.walk(path):
        for file in f:
            if file.endswith(ext):
                collectedFiles.append(os.path.join(r, file))
    return collectedFiles

def get_file_global_size(file):
    if "overlays/" in file or "mts/" in file or "sd/" in file:
        return "0"

    g0_list = [
        "/equip/",
        "/bullet/",
        "/thing/",
        "/okajima/",
        "game/item.c", # todo figure out if correct, why not all .c files in this dir ??
        "anime.c", # ditto
        "vibrate.c",
        "/takabe/",
        "/libfs/",
        "kojo/demo.c",
        "kojo/demothrd.c",
        "strctrl.c",
        "jimctrl.c",
        "memcard.c",
        "dgd.c",
        "sna_hzd.c",
    ]

    if any(i in file for i in g0_list):
        return "0"

    return "8"

def gen_build_target(targetName):
    ninja.comment("Build target " + targetName)

    asmFiles = get_files_recursive("../asm", ".s")
    print("Got " + str(len(asmFiles)) + " asm files")

    cFiles = get_files_recursive("../source", ".c")
    print("Got " + str(len(cFiles)) + " source files")

    linkerDeps = []

    # TODO: Use the correct toolchain and -G flag for each c file
    # TODO: .h file deps of .c files

    # build .s files
    for asmFile in asmFiles:
        asmFile = asmFile.replace("\\", "/")
        asmOFile = asmFile.replace("/asm/", f"/{args.obj_directory}/")
        asmOFile = asmOFile.replace(".s", ".obj")
        #print("Build step " + asmFile + " -> " + asmOFile)
        ninja.build(asmOFile, "psyq_asmpsx_assemble", asmFile)
        linkerDeps.append(asmOFile)

    # build .c files
    for cFile in cFiles:
        cFile = cFile.replace("\\", "/")
        cOFile = cFile.replace("/source/", f"/{args.obj_directory}/")
        cPreProcHeadersFile = cOFile.replace(".c", ".c.preproc.headers")
        cPreProcHeadersFixedFile = cOFile.replace(".c", ".c.preproc.headers_fixed")
        cConvertedFile = cOFile.replace(".c", ".c.eucjp")
        cPreProcFile = cOFile.replace(".c", ".c.preproc")
        cDynDepFile = cOFile.replace(".c", ".c.dyndep")
        cAsmPreProcFile = cOFile.replace(".c", ".c.asm.preproc")
        cAsmPreProcFileDeps = cOFile.replace(".c", ".c.asm.preproc.deps")
        cAsmFile = cOFile.replace(".c", ".asm")
        cTempOFile = cOFile.replace(".c", "_fixme.obj")
        cOFile = cOFile.replace(".c", ".obj")
        #print("Build step " + asmFile + " -> " + asmOFile)

        ninja.build(cPreProcHeadersFile, "psyq_c_preprocess_44_headers", cFile)
        ninja.build(cPreProcHeadersFixedFile, "header_deps", cPreProcHeadersFile)

        compiler = "psyq_cc_44"
        if "mts/" in cFile or "sd/" in cFile:
            compiler = "psyq_cc_43"

        aspsx = "psyq_aspsx_assemble_44"
        if "overlays" in cFile:
            if args.variant == 'vr_exe':
                aspsx = "psyq_aspsx_assemble_2_81_overlays"
            else:
                aspsx = "psyq_aspsx_assemble_44_overlays"
        elif "mts/" in cFile or "sd/" in cFile:
            aspsx = "psyq_aspsx_assemble_2_56"
        elif args.variant == 'vr_exe':
            aspsx = "psyq_aspsx_assemble_2_81"

        ninja.build(cPreProcFile, "psyq_c_preprocess_44", cFile, implicit=[cPreProcHeadersFixedFile])
        ninja.build([cAsmPreProcFile, cAsmPreProcFileDeps, cDynDepFile], "asm_include_preprocess_44", cPreProcFile)
        ninja.build(cConvertedFile, "convert_c_encoding", cAsmPreProcFile)
        ninja.build(cAsmFile, compiler, cConvertedFile, variables= { "gSize": get_file_global_size(cFile) })
        ninja.build(cTempOFile, aspsx, cAsmFile)
        ninja.build(cOFile, "asm_include_postprocess", cTempOFile, implicit=[cAsmPreProcFileDeps, cDynDepFile], dyndep=cDynDepFile)

        linkerDeps.append(cOFile)

    # Build main exe

    # preprocess linker_command_file.txt
    linkerCommandFile = f"../{args.obj_directory}/linker_command_file.txt"
    ninja.build(linkerCommandFile, "linker_command_file_preprocess", f"linker_command_file.txt", variables={'psyq_sdk': args.psyq_path})
    ninja.newline()

    # run the linker to generate the cpe
    cpeFile = f"../{args.obj_directory}/_mgsi.cpe"
    ninja.build(cpeFile, "psylink", implicit=linkerDeps + [linkerCommandFile])
    ninja.newline()

    # cpe to exe
    exeFile = f"../{args.obj_directory}/_mgsi.exe"
    ninja.build(exeFile, "cpe2exe", cpeFile)
    ninja.newline()

    # Run linker separately for each overlay to make it possible
    # to share objects (same symbols) across overlays.

    OVERLAYS = [
        "sound",
        "select1", "select2", "select3", "select4", "selectd",
        "change",
        "s16b",
        "camera",
        "select",
        "d11c",
        "s00a",
        "d03a",
        "s03e", "s03er",
        "title",
        "s01a",
        "d01a",
        "s02c", "s02e",
        "s16c",
        "s06a",
        "s02a",
        "s02d",
        "s12c",
        "s07a",
        "s04a",
        "s02b",
        "s16a",
        "d16e",
        "s16d",
        "s20a", "s20ar",
        "s03a", "s03ar",
        "d00a",
        "s15b",
        "s11e",
        "s07c", "s07cr",
        "s08c", "s08cr",
        "s11i",
        "s15c",
        "ending", "endingr",
        "preope",
        "opening",
        "roll",
        "s03b",
        "s11g",
        "s11c",
        "s12a",
        "option",
        "s03c",
        "s11d",
        "s04c",
        "demosel",
        "s13a",
        "s08a",
        "d18a", "d18ar",
        "s19b", "s19br",
        "s08b", "s08br",
    ]

    if args.variant == 'vr_exe' or args.variant == 'dev_exe':
        OVERLAYS = []

    for overlay in OVERLAYS:
        # It turns out that MGS overlays contain uninitialized memory
        # in:
        # - Padding between values in data/rdata (e.g. padding between strings)
        # - BSS
        # Our psylink doesn't have the same problem and it fills those
        # spaces correctly with 0s.
        #
        # To inject back the uninitialized memory we run the linker twice.
        # The first run uses unmodified psylink, so the generated overlay
        # has 0s in those described places. The second run uses a modified
        # version of psylink that writes on top of an existing file
        # (fopen(, "r+b") instead of fopen(, "wb")). Before the second run
        # we create a dummy file filled with a repeating non-zero byte -
        # this represents the uninitialized memory that we will detect.
        # After that we can use those two generated files, diff them
        # and combined with the uninitialized memory extracted from original
        # files to generate an overlay with uninitialized memory.

        # First run (LHS)
        linkerCommandFile = f"../{args.obj_directory}/linker_command_file_{overlay}_lhs.txt"
        linkerCommandPreprocessVars = {
            "overlay": f"OVERLAY={overlay}",
            "overlay_suffix": "OVERLAY_SUFFIX=lhs",
            "psyq_sdk": args.psyq_path
        }
        ninja.build(linkerCommandFile, "linker_command_file_preprocess", f"linker_command_file.txt", variables=linkerCommandPreprocessVars)
        ninja.newline()

        lhsOverlayFile = f"../{args.obj_directory}/{overlay}_lhs.bin"
        ninja.build(lhsOverlayFile, "psylink", implicit=linkerDeps + [linkerCommandFile], variables={"suffix": f"_{overlay}_lhs"})
        ninja.newline()

        # Second run (RHS)
        linkerCommandFile = f"../{args.obj_directory}/linker_command_file_{overlay}_rhs.txt"
        linkerCommandPreprocessVars = {
            "overlay": f"OVERLAY={overlay}",
            "overlay_suffix": "OVERLAY_SUFFIX=rhs",
            "psyq_sdk": args.psyq_path
        }
        ninja.build(linkerCommandFile, "linker_command_file_preprocess", f"linker_command_file.txt", variables=linkerCommandPreprocessVars)
        ninja.newline()

        dummyFile = f"../{args.obj_directory}/{overlay}_rhs_bss.bin"
        ninja.build(dummyFile, "create_dummy_file_overlays", implicit=linkerDeps + [linkerCommandFile], variables={"overlay_bin": f"{overlay}_rhs.bin", "overlay_bss_bin": f"{overlay}_rhs_bss.bin"})
        ninja.newline()

        rhsOverlayFile = f"../{args.obj_directory}/{overlay}_rhs.bin"
        ninja.build(rhsOverlayFile, "psylink_overlay_fopen_mod", implicit=linkerDeps + [linkerCommandFile, dummyFile], variables={"suffix": f"_{overlay}_rhs"})
        ninja.newline()

        overlayFile = f"../{args.obj_directory}/{overlay}.bin"
        ninja.build(overlayFile, "uninitializer", inputs=[lhsOverlayFile, rhsOverlayFile, f"../um/{overlay}.bin"], variables={"overlay": f"{overlay}"})
        ninja.newline()

#init_psyq_ini_files(args.psyq_path)
gen_build_target("SLPM_862.47")

#gen_build_target("sound.bin")

# TODO: all overlays

f.close()

time_before = time.time()
exit_code = ninja_run()
took = time.time() - time_before
print(f'build took {took:.2f} seconds')

if exit_code == 0 and args.variant != 'dev_exe':
    ret = subprocess.run([sys.executable, 'compare.py'])
    exit_code = ret.returncode

if exit_code == 0 and args.variant != 'dev_exe':
    ret = subprocess.run([sys.executable, 'post_build_checkup.py'])
    exit_code = ret.returncode

if exit_code == 0:
    # You can monitor build_success.txt to detect when a successful build happened
    Path(f"../{args.obj_directory}/build_success.txt").touch()

sys.exit(exit_code)
