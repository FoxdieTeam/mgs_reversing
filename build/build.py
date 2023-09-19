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
# local copy as the pip version doesn't have dyndeps in build() func
import ninja_syntax

os.environ['WINEDEBUG'] = '-all'
os.environ['TMPDIR'] = tempfile.gettempdir()

has_wine = bool(which('wine'))
has_wibo = bool(which('wibo'))
has_cpp = bool(which('cpp'))

# Native preprocesor doesn't work under WSL
if "microsoft-standard" in platform.uname().release:
    has_cpp = False

# TODO: make r3000.h and asm.h case sensitive symlinks on linux

def parse_arguments():
    parser = argparse.ArgumentParser(description='MGS Ninja build script generator')

    # Optional
    parser.add_argument('--psyq_path', type=str, default=os.environ.get("PSYQ_SDK") or "../../psyq_sdk",
                        help='Path to the root of the cloned PSYQ repo')

    args = parser.parse_args()

    args.psyq_path = os.path.relpath(args.psyq_path).replace("\\","/")
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
        r'sd_drv\.c:\d+: warning: `temp\' might be used uninitialized in this function',
        r'stream\.c:\d+: warning: `dir_idx\' might be used uninitialized in this function',
        r'sd_main\.c:\d+: warning: unused variable `buffer\'',
        r'sd_drv\.c:\d+: warning: unused variable `temp\'',
        r'radioface\.c:\d+: warning: unused variable `pad\'',
        r'radiomem\.c:\d+: warning: unused variable `pad\'',
        r'item\.c:\d+: warning: `state\' might be used uninitialized in this function',
        r'memcard\.c:\d+: warning: `op\' might be used uninitialized in this function',
        r'memcard\.c:\d+: warning: `count\' might be used uninitialized in this function',
        r'door\.c:\d+: warning: unused variable `pad\'',
        r'motion\.c:\d+: warning: `time\' might be used uninitialized in this function',
        r'motion\.c:\d+: warning: unused variable `unused\'',
        r'motion\.c:\d+: warning: `pArchive2\' might be used uninitialized in this function',
        r'motion\.c:\d+: warning: `shift2\' might be used uninitialized in this function',
        r'motion\.c:\d+: warning: `archive\' might be used uninitialized in this function',
        r'memcard\.c:\d+: warning: `return\' with no value, in function returning non-void',
        r'main\.c:\d+: warning: control reaches end of non-void function',
        r'control\.c:\d+: warning: `vy\' might be used uninitialized in this function',
        r'font\.c:\d+: warning: `m2\' might be used uninitialized in this function',
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

if has_cpp:
    ninja.variable("psyq_c_preprocessor_44_exe", "cpp -nostdinc")
else:
    ninja.variable("psyq_c_preprocessor_44_exe", prefix("wine", "$psyq_path/psyq_4.4/bin/CPPPSX.exe"))
ninja.newline()

ninja.variable("psyq_cc_44_exe", prefix("wine", "$psyq_path/psyq_4.4/bin/CC1PSX.EXE"))
ninja.newline()

ninja.variable("psyq_aspsx_44_exe", prefix("wibo", "$psyq_path/psyq_4.4/bin/aspsx.exe"))
ninja.newline()

if has_cpp:
    ninja.variable("psyq_c_preprocessor_43_exe", "cpp -nostdinc")
else:
    ninja.variable("psyq_c_preprocessor_43_exe", prefix("wine", "$psyq_path/psyq_4.3/bin/CPPPSX.exe"))
ninja.newline()

ninja.variable("psyq_cc_43_exe", prefix("wine", "$psyq_path/psyq_4.3/bin/CC1PSX.EXE"))
ninja.newline()

ninja.variable("psyq_aspsx_2_56_exe", prefix("wibo", "$psyq_path/ASPSX/2.56/ASPSX.EXE"))

ninja.variable("psyq_psylink_exe", prefix("wibo", "$psyq_path/psyq_4.4/bin/psylink.exe"))
ninja.newline()

ninja.variable("src_dir", "../src")
ninja.newline()

# /l = produce linkable output file
# /q = run quietly
ninja.rule("psyq_asmpsx_assemble", "$psyq_asmpsx_44_exe /l /q $in,$out", "Assemble $in -> $out")
ninja.newline()

includes = "-I " + args.psyq_path + "/psyq_4.4/INCLUDE" + " -I $src_dir"

ninja.rule("psyq_c_preprocess_44", "$psyq_c_preprocessor_44_exe -undef -D__GNUC__=2 -D__OPTIMIZE__ " + includes + " -lang-c -Dmips -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D__CHAR_UNSIGNED__ -D_LANGUAGE_C -DLANGUAGE_C $in $out", "Preprocess $in -> $out")
ninja.newline()

# generate header deps, adds edges to the build graph for the next build -M option will write header deps
ninja.rule("psyq_c_preprocess_44_headers", "$psyq_c_preprocessor_44_exe -M -undef -D__GNUC__=2 -D__OPTIMIZE__ " + includes + " -lang-c -Dmips -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D__CHAR_UNSIGNED__ -D_LANGUAGE_C -DLANGUAGE_C $in $out", "Preprocess for includes $in -> $out")
ninja.newline()

ninja.rule("header_deps", f"{sys.executable} $src_dir/../build/hash_include_msvc_formatter.py $in $out", "Include deps fix $in -> $out", deps="msvc")
ninja.newline()

ninja.rule("asm_include_preprocess_44", f"{sys.executable} $src_dir/../build/include_asm_preprocess.py $in $out", "Include asm preprocess $in -> $out")
ninja.newline()

ninja.rule("asm_include_postprocess", f"{sys.executable} $src_dir/../build/include_asm_fixup.py $in $out", "Include asm postprocess $in -> $out")
ninja.newline()

ninja.variable("gSize", "8")
ninja.newline()

ninja.rule("psyq_cc_44", "$psyq_cc_44_exe -quiet -O2 -G $gSize -g -Wall $in -o $out""", "Compile $in -> $out")
ninja.newline()

ninja.rule("psyq_aspsx_assemble_44", "$psyq_aspsx_44_exe -q $in -o $out", "Assemble $in -> $out")
ninja.newline()

ninja.rule("psyq_c_preprocess_43", "$psyq_c_preprocessor_43_exe -undef -D__GNUC__=2 -D__OPTIMIZE__ " + includes + " -lang-c -Dmips -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D__CHAR_UNSIGNED__ -D_LANGUAGE_C -DLANGUAGE_C $in $out", "Preprocess $in -> $out")
ninja.newline()

# For some reason 4.3 cc needs TMPDIR set to something that exists else it will just die with "CC1PSX.exe: /cta04280: No such file or directory"
ninja.rule("psyq_cc_43", "$psyq_cc_43_exe -quiet -O2 -G $gSize -g -Wall $in -o $out", "Compile $in -> $out")
ninja.newline()

ninja.rule("psyq_aspsx_assemble_2_56", "$psyq_aspsx_2_56_exe -q $in -o $out", "Assemble $in -> $out")
ninja.newline()

ninja.rule("psylink", f"$psyq_psylink_exe /l {args.psyq_path}/psyq_4.4/LIB /e printf=0x8008BBA0 /e mts_null_printf_8008BBA8=0x8008BBA8 /e mts_nullsub_8_8008BB98=0x8008BB98 /c /n 4000 /q /gp .sdata /m \"@$src_dir/../build/linker_command_file.txt\",$src_dir/../obj/_mgsi.cpe,$src_dir/../obj/asm.sym,$src_dir/../obj/asm.map", "Link $out")
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

def gen_build_target(targetName):
    ninja.comment("Build target " + targetName)

    asmFiles = get_files_recursive("../asm", ".s")
    print("Got " + str(len(asmFiles)) + " asm files")

    cFiles = get_files_recursive("../src", ".c")
    print("Got " + str(len(cFiles)) + " source files")

    linkerDeps = []

    # TODO: Use the correct toolchain and -G flag for each c file
    # TODO: .h file deps of .c files

    # build .s files
    for asmFile in asmFiles:
        asmFile = asmFile.replace("\\", "/")
        asmOFile = asmFile.replace("/asm/", "/obj/")
        asmOFile = asmOFile.replace(".s", ".obj")
        #print("Build step " + asmFile + " -> " + asmOFile)
        ninja.build(asmOFile, "psyq_asmpsx_assemble", asmFile)
        linkerDeps.append(asmOFile)

    # build .c files
    for cFile in cFiles:
        cFile = cFile.replace("\\", "/")
        cOFile = cFile.replace("/src/", "/obj/")
        cPreProcHeadersFile = cOFile.replace(".c", ".c.preproc.headers")
        cPreProcHeadersFixedFile = cOFile.replace(".c", ".c.preproc.headers_fixed")
        cPreProcFile = cOFile.replace(".c", ".c.preproc")
        cDynDepFile = cOFile.replace(".c", ".c.dyndep")
        cAsmPreProcFile = cOFile.replace(".c", ".c.asm.preproc")
        cAsmPreProcFileDeps = cOFile.replace(".c", ".c.asm.preproc.deps")
        cAsmFile = cOFile.replace(".c", ".asm")
        cTempOFile = cOFile.replace(".c", "_fixme.obj")
        cOFile = cOFile.replace(".c", ".obj")
        #print("Build step " + asmFile + " -> " + asmOFile)
        if cFile.find("mts/") == -1 and cFile.find("SD/") == -1:
            ninja.build(cPreProcHeadersFile, "psyq_c_preprocess_44_headers", cFile)
            ninja.build(cPreProcHeadersFixedFile, "header_deps", cPreProcHeadersFile)
            ninja.build(cPreProcFile, "psyq_c_preprocess_44", cFile, implicit=[cPreProcHeadersFixedFile])
            ninja.build([cAsmPreProcFile, cAsmPreProcFileDeps, cDynDepFile], "asm_include_preprocess_44", cPreProcFile)

            g0 = False
            buildWithG0 = [
                "/Equip/",
                 "/Bullet/",
                 "/Thing/",
                 "/Okajima/",
                 "item.c", # todo figure out if correct, why not all .c files in this dir ??
                 "vibrate.c",
                 "anime.c", # ditto
                 "/Takabe/",
                 "/libfs/",
                 "DG_ResetExtPaletteMakeFunc_800791E4.c", # Despite the name, this might be related to Takabe due to proximity?
                 "DG_ResetPaletteEffect_80078FF8.c", # Same as above
                 "DG_StorePaletteEffect_80078F30.c", # Same as above
                 "demothrd.c",
                 "sub_80037DB8.c",
                 "Kojo/demothrd.c",
                 "strctrl.c",
                 "jimctrl.c",
                 "memcard.c",
                 "dgd.c",
                 "sub_80060644.c",
                 "sub_80060548.c"
                 ]
            for item in buildWithG0:
                if cFile.find(item) != -1:
                    g0 = True
                    break
            if g0:
                # print("-G 0: " + cFile)
                ninja.build(cAsmFile, "psyq_cc_44", cAsmPreProcFile, variables= { "gSize": "0"})
            else:
                ninja.build(cAsmFile, "psyq_cc_44", cAsmPreProcFile, variables= { "gSize": "8"})
            ninja.build(cTempOFile, "psyq_aspsx_assemble_44", cAsmFile)
            ninja.build(cOFile, "asm_include_postprocess", cTempOFile, implicit=[cAsmPreProcFileDeps, cDynDepFile], dyndep=cDynDepFile)

        else:
            #print("43:" + cFile)
            ninja.build(cPreProcHeadersFile, "psyq_c_preprocess_44_headers", cFile)
            ninja.build(cPreProcHeadersFixedFile, "header_deps", cPreProcHeadersFile)
            ninja.build(cPreProcFile, "psyq_c_preprocess_43", cFile, implicit=[cPreProcHeadersFixedFile])
            ninja.build([cAsmPreProcFile, cAsmPreProcFileDeps, cDynDepFile], "asm_include_preprocess_44", cPreProcFile)

            #print("-G 0: " + cFile)
            ninja.build(cAsmFile, "psyq_cc_43", cAsmPreProcFile, variables= { "gSize": "0"})

            ninja.build(cTempOFile, "psyq_aspsx_assemble_2_56", cAsmFile)
            ninja.build(cOFile, "asm_include_postprocess", cTempOFile, implicit=[cAsmPreProcFileDeps, cDynDepFile], dyndep=cDynDepFile)

        linkerDeps.append(cOFile)
        linkerDeps.append("linker_command_file.txt")

    # run the linker to generate the cpe
    cpeFile = "../obj/_mgsi.cpe"
    ninja.build(cpeFile, "psylink", implicit=linkerDeps)
    ninja.newline()

    # cpe to exe
    exeFile = "../obj/_mgsi.exe"
    ninja.build(exeFile, "cpe2exe", cpeFile)
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

if exit_code == 0:
    ret = subprocess.run([sys.executable, 'compare.py'])
    exit_code = ret.returncode

if exit_code == 0:
    ret = subprocess.run([sys.executable, 'post_build_checkup.py'])
    exit_code = ret.returncode

sys.exit(exit_code)
