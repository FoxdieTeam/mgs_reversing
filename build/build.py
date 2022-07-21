import ninja_syntax
import glob
import sys
import argparse
import os

def parse_arguments():
    parser = argparse.ArgumentParser(description='MGS Ninja build script generator')

    # Required
    parser.add_argument('--platform', type=str, required=True,
                        choices=['windows', 'wsl', 'linux'],
                        help='Platform to generate the build script for"')

    # Optional
    parser.add_argument('--psyq_path', type=str, default="./../../psyq_sdk",
                        help='Path to the root of the cloned PSYQ repo')

    args = parser.parse_args()

    print("generate for platform " + args.platform)

    args.psyq_path = os.path.abspath(args.psyq_path).replace("\\","/")
    print("psyq_path = " + args.psyq_path)
    return args

args = parse_arguments()

#ninja = ninja_syntax.Writer(sys.stdout)
f = open("build.ninja", "w")
ninja = ninja_syntax.Writer(f)

ninja.variable("psyq_path", args.psyq_path)
ninja.newline()

ninja.variable("psyq_asmpsx_44_exe", "$psyq_path/psyq_4.4/bin/asmpsx.exe")
ninja.newline()

ninja.variable("psyq_c_preprocessor_44_exe", "$psyq_path/psyq_4.4/bin/CPPPSX.exe")
ninja.newline()

ninja.variable("psyq_cc_44_exe", "$psyq_path/psyq_4.4/bin/CC1PSX.exe")
ninja.newline()

ninja.variable("psyq_aspsx_44_exe", "$psyq_path/psyq_4.4/bin/aspsx.exe")
ninja.newline()

ninja.variable("psyq_c_preprocessor_43_exe", "$psyq_path/psyq_4.3/bin/CPPPSX.exe")
ninja.newline()

ninja.variable("psyq_cc_43_exe", "$psyq_path/psyq_4.3/bin/CC1PSX.exe")
ninja.newline()

ninja.variable("psyq_aspsx_43_exe", "$psyq_path/psyq_4.3/bin/aspsx.exe")
ninja.newline()

ninja.variable("psyq_psylink_exe", "$psyq_path/psyq_4.4/bin/psylink.exe")
ninja.newline()

ninja.variable("src_dir", os.path.abspath("../src"))
ninja.newline()

# /l = produce linkable output file
# /q = run quietly
ninja.rule("psyq_asmpsx_assemble", "$psyq_asmpsx_44_exe /l /q $in,$out", "Assemble $in -> $out")
ninja.newline()

ninja.pool("single_threaded", 1)

includes = "-I " + args.psyq_path + "/psyq_4.4/include" + " -I $src_dir -I $src_dir\\font -I $src_dir\\memcard -I $src_dir\\chara\\snake -I $src_dir\\Thing -I $src_dir\\data\\data -I $src_dir\\data\\rdata -I $src_dir\\data\\sdata -I $src_dir\\libgv -I $src_dir\\libgcl -I $src_dir\\libdg -I $src_dir\\Game -I $src_dir\\Menu -I $src_dir\\mts -I $src_dir\\map -I $src_dir\\util"

ninja.rule("psyq_c_preprocess_44", "$psyq_c_preprocessor_44_exe -undef -D__GNUC__=2 -D__OPTIMIZE__ " + includes + " -lang-c -Dmips -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D__CHAR_UNSIGNED__ -D_LANGUAGE_C -DLANGUAGE_C $in $out", "Preprocess $in -> $out")
ninja.newline()

ninja.rule("psyq_cc_44", "$psyq_cc_44_exe -quiet -O2 -G 8 -g -Wall -O2 $in -o $out""", "Compile $in -> $out", pool="single_threaded")
ninja.newline()

ninja.rule("psyq_aspsx_assemble_44", "$psyq_aspsx_44_exe -q $in -o $out", "Assemble $in -> $out")
ninja.newline()

ninja.rule("psyq_c_preprocess_43", "$psyq_c_preprocessor_43_exe -undef -D__GNUC__=2 -D__OPTIMIZE__ " + includes + " -lang-c -Dmips -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D__CHAR_UNSIGNED__ -D_LANGUAGE_C -DLANGUAGE_C $in $out", "Preprocess $in -> $out" , pool="single_threaded")
ninja.newline()

# For some reason 4.3 cc needs TMPDIR set to something that exists else it will just die with "CC1PSX.exe: /cta04280: No such file or directory"
ninja.rule("psyq_cc_43", "cmd /c \"set TMPDIR=%TEMP%&& $psyq_cc_43_exe -quiet -O2 -g -Wall -O2 $in -o $out\"", "Compile $in -> $out", pool="single_threaded")
ninja.newline()

ninja.rule("psyq_aspsx_assemble_43", "$psyq_aspsx_43_exe -q $in -o $out", "Assemble $in -> $out")
ninja.newline()


ninja.rule("psylink", "$psyq_psylink_exe /e mts_printf_8008BBA0=0x8008BBA0 /c /n 4000 /q /gp .sdata /m \"@$src_dir/../build/linker_command_file.txt\",$src_dir/../obj/test2.cpe,$src_dir/../obj/asm.sym,$src_dir/../obj/asm.map", "Link $out")
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

    asmPath = os.path.abspath("../asm/")
    print("asm files path " + asmPath)
    asmFiles = get_files_recursive(asmPath, ".s")
    print("Got " + str(len(asmFiles)) + " asm files")

    sourcePath = os.path.abspath("../src/")
    print("source files files path " + sourcePath)
    cFiles = get_files_recursive(sourcePath, ".c")
    print("Got " + str(len(cFiles)) + " source files")

    linkerDeps = []

    # TODO: Use the correct toolchain and -G flag for each c file
    # TODO: Invoke the include_asm tools
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
        cPreProcFile = cOFile.replace(".c", ".c.preproc")
        cAsmFile = cOFile.replace(".c", ".asm")
        cOFile = cOFile.replace(".c", ".obj")
        #print("Build step " + asmFile + " -> " + asmOFile)
        if cFile.find("mts/") == -1 and cFile.find("SD/") == -1:
            ninja.build(cPreProcFile, "psyq_c_preprocess_44", cFile)
            ninja.build(cAsmFile, "psyq_cc_44", cPreProcFile)
            ninja.build(cOFile, "psyq_aspsx_assemble_44", cAsmFile)
        else:
            #print("44:" + cFile)
            ninja.build(cPreProcFile, "psyq_c_preprocess_43", cFile)
            ninja.build(cAsmFile, "psyq_cc_43", cPreProcFile)
            ninja.build(cOFile, "psyq_aspsx_assemble_43", cAsmFile)
        linkerDeps.append(cOFile)

        
    # run the linker to generate the cpe
    cpeFile = os.path.abspath(".") + "/obj/" + "_mgsi" + ".cpe"
    ninja.build(cpeFile, "psylink", implicit=linkerDeps)
    ninja.newline()

    # TODO: cpe to exe
    #cpeAsExe = "build/" + targetName + ".exe"
    #ninja.build(cpeAsExe, "cpe2exe", cpeFile)
    #ninja.newline()

    # exe hash check
    #ninja.build("build/" + targetName + ".ok", "hash_check", targetName + ".sha1", implicit=[elfAsBinFile])
    #ninja.newline()


init_psyq_ini_files(args.psyq_path)
gen_build_target("SLPM_862.47")

#gen_build_target("sound.bin")

# todo: all overlays
