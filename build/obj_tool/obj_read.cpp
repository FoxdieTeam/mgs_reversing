#define _CRT_SECURE_NO_WARNINGS

// This is a massively hacked copy of https://github.com/ogamespec/psxdev/blob/master/tools/dumpobj/dumpobj.c
// its purpose is to count the amount of bytes that make up C functions over a set of obj files.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <filesystem>
#include <map>

#define OBJ_VERSION 2

#define OBJ_SIGNATURE "LNK"

#define OBJ_SIGNATURE_SIZE 3

namespace fs = std::experimental::filesystem;

class Functions
{
public:
    void Add(const char* fullObjName, const char* funcName, size_t funcSize)
    {
        mFuncs[fullObjName][funcName] = funcSize;
        //printf("%s %s %d bytes %d instructions\n", fullObjName, funcName, funcSize, funcSize / 4);
    }

    size_t TotalSize(const std::string& filter = "") const
    {
        size_t total = 0;
        for (auto& objFuncs : mFuncs)
        {
            if (filter.empty() || (std::string(objFuncs.first).find(filter) != std::string::npos))
            {
                for (auto& objFunc : objFuncs.second)
                {
                    total += objFunc.second;
                }
            }
        }
        return total;
    }

private:
    std::map<std::string, std::map<std::string, size_t>> mFuncs;
};
static Functions gFunctions;

// Wanted to get rid of the printf's but the actualt stream reading is done in the varargs
// so compile it to an empty func since the stream reads won't be thrown away as they have side effects.
static inline void console_log(const char* formatStr, ...)
{

}

typedef struct _OBJ_HEADER
{
    char Signature[3];
    char Version;
} OBJ_HEADER, *POBJ_HEADER;

#define OBJ_TOK_CODE 2


static unsigned long ReadDword(FILE *f)
{
    unsigned long Result = 0;

    Result |= fgetc(f);
    Result |= fgetc(f) << 8;
    Result |= fgetc(f) << 16;
    Result |= fgetc(f) << 24;

    return Result;
}

static unsigned short ReadWord(FILE *f)
{
    unsigned short Result = 0;

    Result |= fgetc(f);
    Result |= fgetc(f) << 8;

    return Result;
}

static void ReadCode(FILE *f, int Size)
{
    int Num = 0;

    while (Num < Size)
    {
        if ((Num & 0xF) == 0)
        {
            console_log("\n%04x:", Num);
        }
        console_log("%02x ", fgetc(f));
        Num++;
    }

    console_log("\n\n");
}

static std::vector<char> ReadByteString(FILE *f)
{
    int Count = fgetc(f);

    std::vector<char> str;
    while (Count--)
    {
        str.push_back(fgetc(f));
    }
    str.push_back(0);
    console_log(str.data());
    return str;
}

static void DumpPatch(FILE *f)
{
    int Byte1;

    Byte1 = fgetc(f);

    if (Byte1 <= 24)
    {
        switch (Byte1)
        {
        case 0:
            console_log("$%lx", ReadDword(f));
            return;
        case 2:
            console_log("[%lx]", ReadWord(f));
            return;
        case 4:
            console_log("sectbase(%lx)", ReadWord(f));
            return;
        case 6:
            console_log("bank(%lx)", ReadWord(f));
            return;
        case 8:
            console_log("sectof(%lx)", ReadWord(f));
            return;
        case 10:
            console_log("offs(%lx)", ReadWord(f));
            return;
        case 12:
            console_log("sectstart(%lx)", ReadWord(f));
            return;
        case 14:
            console_log("groupstart(%lx)", ReadWord(f));
            return;
        case 16:
            console_log("groupof(%lx)", ReadWord(f));
            return;
        case 18:
            console_log("seg(%lx)", ReadWord(f));
            return;
        case 20:
            console_log("grouporg(%lx)", ReadWord(f));
            return;
        case 22:
            console_log("sectend(%lx)", ReadWord(f));
            return;
        case 24:
            console_log("groupend(%lx)", ReadWord(f));
            return;
        }
    }

    console_log("(");
    DumpPatch(f);

    switch (Byte1)
    {
    case 32: console_log("="); break;
    case 34: console_log("<>"); break;
    case 36: console_log("<="); break;
    case 38: console_log("<"); break;
    case 40: console_log(">="); break;
    case 42: console_log(">"); break;
    case 44: console_log("+"); break;
    case 46: console_log("-"); break;
    case 48: console_log("*"); break;
    case 50: console_log("/"); break;
    case 52: console_log("&"); break;
    case 54: console_log("!"); break;
    case 56: console_log("^"); break;
    case 58: console_log("<<"); break;
    case 60: console_log(">>"); break;
    case 62: console_log("%%"); break;
    case 64: console_log("---"); break;
    case 66: console_log("-revword-"); break;
    case 68: console_log("-check0-"); break;
    case 70: console_log("-check1-"); break;
    case 72: console_log("-bitrange-"); break;
    case 74: console_log("-arshift_chk-"); break;

    default:
        console_log("?%d?", Byte1);
        break;
    }

    DumpPatch(f);
    console_log(")");
}

static int DumpObjInfo(const char* objFileName, FILE *f, int ShowCode)
{
    int Token;
    int BreakStream = 0;
    int Result = 0;
    unsigned short Word1, Word2;
    unsigned char Byte;
    unsigned long Dword1;
    size_t functionOffsetStart = 0;
    std::vector<char> lastFunctionName;

    while (1)
    {
        Token = fgetc(f);
        if (Token < 0 || BreakStream)
            break;

        switch (Token)
        {
        case 0:
            console_log("0 : End of file\n");
            break;

        case 2:
            Word1 = ReadWord(f);
            console_log("2 : Code %ld bytes\n", Word1);

            if (ShowCode)
                ReadCode(f, Word1);
            else
                fseek(f, Word1, SEEK_CUR);
            break;

        case 4:

            Word1 = ReadWord(f);
            Dword1 = ReadDword(f);

            console_log("4 : Run at offset %lx in section %lx\n", Dword1, Word1);

            break;

        case 6:

            console_log("6 : Switch to section %lx\n", ReadWord(f));

            break;

        case 8:

            console_log("8 : Uninitialised data, %ld bytes\n", ReadDword(f));

            break;

        case 10:

            Byte = fgetc(f);
            Word1 = ReadWord(f);

            console_log("10 : Patch type %d at offset %lx with ", Byte, Word1);
            DumpPatch(f);
            console_log("\n");

            break;

        case 12:

            Word1 = ReadWord(f);
            Word2 = ReadWord(f);
            Dword1 = ReadDword(f);

            console_log("12 : XDEF symbol number %lx \'", Word1);
            ReadByteString(f);
            console_log("\' at offset %lx in section %lx\n", Dword1, Word2);

            break;

        case 14:

            console_log("14 : XREF symbol number %lx \'", ReadWord(f));
            ReadByteString(f);
            console_log("\'\n");

            break;

        case 16:

            Word1 = ReadWord(f);
            Word2 = ReadWord(f);
            Byte = fgetc(f);

            console_log("16 : Section symbol number %lx \'", Word1);
            ReadByteString(f);
            console_log("\' in group %lx alignment %d\n", Word2, Byte);

            break;

        case 18:

            Word1 = ReadWord(f);
            Dword1 = ReadDword(f);

            console_log("18 : Local symbol \'");
            ReadByteString(f);
            console_log("\' at offset %lx in section %lx\n", Dword1, Word1);

            break;

        case 20:

            Word1 = ReadWord(f);
            Byte = fgetc(f);

            console_log("20 : Group symbol number %lx \'", Word1);
            ReadByteString(f);
            console_log("\' type %d\n", Byte);

            break;

        case 22:

            console_log("22 : Set byte size register to ");
            DumpPatch(f);
            console_log("  reg offset %d\n", ReadWord(f));

            break;

        case 24:

            console_log("24 : Set word size register to ");
            DumpPatch(f);
            console_log("  reg offset %d\n", ReadWord(f));

            break;

        case 26:

            console_log("26 : Set long size register to ");
            DumpPatch(f);
            console_log("  reg offset %d\n", ReadWord(f));

            break;

        case 28:

            console_log("28 : Define file ");
            console_log("number %x as \"", ReadWord(f));
            ReadByteString(f);
            console_log("\"\n");

            break;

        case 30:

            console_log("30 : Set to ");

            Word1 = ReadWord(f);
            Dword1 = ReadDword(f);

            console_log("file %lx, line %ld\n", Word1, Dword1);

            break;

        case 32:

            console_log("32 : Set to ");
            console_log("line %ld\n", ReadDword(f));

            break;

        case 34:

            console_log("34 : Increment line number\n");

            break;

        case 36:

            console_log("36 : Increment line number by ");
            console_log("%d\n", fgetc(f) & 0xFF);

            break;

        case 38:

            console_log("38 : Increment line number by ");
            console_log("%d\n", ReadWord(f));

            break;

        case 40:

            Word1 = ReadWord(f);
            Dword1 = ReadDword(f);

            console_log("40 : Very local symbol \'");
            ReadByteString(f);
            console_log("\' at offset %lx in section %lx\n", Dword1, Word1);

            break;

        case 42:

            console_log("42 : Set 3-byte size register to ");
            DumpPatch(f);
            console_log("  reg offset %d\n", ReadWord(f));

            break;

        case 44:

            Byte = fgetc(f);
            Word1 = ReadWord(f);
            console_log("44 : Set MX info at offset %x to %x\n", Word1, Byte);

            break;

        case 46:
            console_log("46 : Processor type %d\n", fgetc(f) & 0xFF);
            break;

        case 48:

            Word1 = ReadWord(f);
            Word2 = ReadWord(f);
            Dword1 = ReadDword(f);

            console_log("48 : XBSS symbol number %lx \'", Word1);
            ReadByteString(f);
            console_log("\' size %lx in section %lx\n", Dword1, Word2);

            break;

        case 50:

            console_log("50 : Inc SLD linenum at offset %lx\n", ReadWord(f));

            break;

        case 52:

            Word1 = ReadWord(f);
            Byte = fgetc(f);
            console_log("52 : Inc SLD linenum by byte %u at offset %lx\n", Byte, Word1);

            break;

        case 54:

            Word1 = ReadWord(f);
            Word2 = ReadWord(f);
            console_log("54 : Inc SLD linenum by word %lu at offset %lx\n", Word2, Word1);

            break;

        case 56:

            Word1 = ReadWord(f);
            Dword1 = ReadDword(f);
            console_log("56 : Set SLD linenum to %lu at offset %lx\n", Dword1, Word1);

            break;

        case 58:

            Word1 = ReadWord(f);
            Dword1 = ReadDword(f);
            Word2 = ReadWord(f);
            console_log("58 : Set SLD linenum to %lu at offset %lx in file %lx\n", Dword1, Word1, Word2);

            break;

        case 60:

            console_log("60 : End SLD info at offset %lx\n", ReadWord(f));

            break;

        case 62:

            console_log("62 : Repeat byte ");
            DumpPatch(f);
            console_log(" %ld times\n", ReadDword(f));

            break;

        case 64:

            console_log("64 : Repeat word ");
            DumpPatch(f);
            console_log(" %ld times\n", ReadDword(f));

            break;

        case 66:

            console_log("66 : Repeat longword ");
            DumpPatch(f);
            console_log(" %ld times\n", ReadDword(f));

            break;

        case 68:

            console_log("68 : Proc call ");

            Byte = fgetc(f);
            if (Byte)
                console_log("FAR ");
            else
                console_log("NEAR ");

            console_log("to symbol %lx ", ReadWord(f));

            Byte = fgetc(f);
            Word1 = ReadWord(f);

            switch (Byte)
            {
            case 0:
                console_log("dp:? ");
                break;
            case 2:
                console_log("dp:$%lx ", Word1);
                break;
            case 4:
                console_log("dp:(section %lx) ", Word1);
                break;
            case 6:
                console_log("dp:(group %lx) ", Word1);
                break;
            default:
                console_log("dp:?%x/%lx? ", Byte, Word1);
                break;
            }

            Byte = fgetc(f);
            Word1 = ReadWord(f);

            switch (Byte)
            {
            case 0:
                console_log("db:? ");
                break;
            case 2:
                console_log("db:$%lx ", Word1);
                break;
            case 4:
                console_log("db:(section %lx) ", Word1);
                break;
            case 6:
                console_log("db:(group %lx) ", Word1);
                break;
            default:
                console_log("db:?%x/%lx? ", Byte, Word1);
                break;
            }

            Byte = fgetc(f);
            if (Byte)
                console_log("A:long ");
            else
                console_log("A:short ");

            Byte = fgetc(f);
            if (Byte)
                console_log("I:long\n");
            else
                console_log("I:short\n");

            break;

        case 70:

            console_log("68 : Proc definition ");
            console_log("symbol %lx ", ReadWord(f));

            Byte = fgetc(f);
            Word1 = ReadWord(f);

            switch (Byte)
            {
            case 0:
                console_log("dp:? ");
                break;
            case 2:
                console_log("dp:$%lx ", Word1);
                break;
            case 4:
                console_log("dp:(section %lx) ", Word1);
                break;
            case 6:
                console_log("dp:(group %lx) ", Word1);
                break;
            default:
                console_log("dp:?%x/%lx? ", Byte, Word1);
                break;
            }

            Byte = fgetc(f);
            Word1 = ReadWord(f);

            switch (Byte)
            {
            case 0:
                console_log("db:? ");
                break;
            case 2:
                console_log("db:$%lx ", Word1);
                break;
            case 4:
                console_log("db:(section %lx) ", Word1);
                break;
            case 6:
                console_log("db:(group %lx) ", Word1);
                break;
            default:
                console_log("db:?%x/%lx? ", Byte, Word1);
                break;
            }

            Byte = fgetc(f);

            if (Byte != EOF)
            {
                console_log("MX:%x ", Byte);
            }

            Byte = fgetc(f);

            if (Byte != EOF)
            {
                if (Byte)
                {
                    console_log("FAR");
                }
                else
                {
                    console_log("NEAR");
                }
            }

            console_log("\n");

            break;

        case 72:

            console_log("72 : Repeat 3-byte ");
            DumpPatch(f);
            console_log(" %ld times\n", ReadDword(f));

            break;

        case 74:

            console_log("74 : Function start :\n");
            console_log("  section %04x\n", ReadWord(f));
            console_log("  offset $%08lx\n", ReadDword(f));
            console_log("  file %04x\n", ReadWord(f));
            console_log("  start line %ld\n", ReadDword(f));
            console_log("  frame reg %d\n", ReadWord(f));
            console_log("  frame size %ld\n", ReadDword(f));
            console_log("  return pc reg %d\n", ReadWord(f));
            console_log("  mask $%08lx\n", ReadDword(f));
            functionOffsetStart = ReadDword(f);
            console_log("  mask offset %ld\n", functionOffsetStart);
            console_log("  name ");
            lastFunctionName = ReadByteString(f);
            console_log("\n");

            break;

        case 76:
        {
            console_log("76 : Function end :\n");
            console_log("  section %04x\n", ReadWord(f));
            const size_t functionOffsetEnd = ReadDword(f);
            const size_t functionSize = functionOffsetEnd - functionOffsetStart;
            gFunctions.Add(objFileName, lastFunctionName.data(), functionSize);
            console_log("  offset $%08lx\n", functionOffsetEnd);
            console_log("  end line %ld\n", ReadDword(f));
        }
            break;

        case 78:

            console_log("78 : Block start :\n");
            console_log("  section %04x\n", ReadWord(f));
            console_log("  offset $%08lx\n", ReadDword(f));
            console_log("  start line %ld\n", ReadDword(f));

            break;

        case 80:

            console_log("80 : Block end\n");
            console_log("  section %04x\n", ReadWord(f));
            console_log("  offset $%08lx\n", ReadDword(f));
            console_log("  end line %ld\n", ReadDword(f));

            break;

        case 82:

            console_log("82 : Def :\n");
            console_log("  section %04x\n", ReadWord(f));
            console_log("  value $%08lx\n", ReadDword(f));
            console_log("  class %d\n", ReadWord(f));
            console_log("  type %d\n", ReadWord(f));
            console_log("  size %ld\n", ReadDword(f));
            console_log("  name : ");
            ReadByteString(f);
            console_log("\n");

            break;

        case 84:

            console_log("84 : Def2 :\n");
            console_log("  section %04x\n", ReadWord(f));
            console_log("  value $%08lx\n", ReadDword(f));
            console_log("  class %d\n", ReadWord(f));
            console_log("  type %d\n", ReadWord(f));
            console_log("  size %ld\n", ReadDword(f));

            Word1 = ReadWord(f);
            console_log("  dims %ld ", Word1);

            while (Word1--)
            {
                console_log("%ld ", ReadDword(f));
            }

            console_log("\n  tag ");
            ReadByteString(f);
            console_log("\n");
            ReadByteString(f);
            console_log("\n");

            break;

        default:
            console_log("%d : Unknown tag - exiting\n", Token);
            BreakStream = 1;
            break;
        }
    }

    return Result;
}

static int ProcessObj(const char* filename)
{
    char Sig[OBJ_SIGNATURE_SIZE + 1];

    FILE *f = fopen(filename, "rb");
    if (!f)
    {
        printf("Error : unable to open file \'%s\' for input - exiting\n", filename);
        return -3;
    }

    memset(Sig, 0, sizeof(Sig));

    for (int i = 0; i < OBJ_SIGNATURE_SIZE; i++)
    {
        Sig[i] = fgetc(f);
    }

    if (strcmp(Sig, OBJ_SIGNATURE) != 0)
    {
        printf("Error : file \'%s\' is not an SNLink format object file - exiting\n", filename);

        fclose(f);
        return -4;
    }


    char Version = fgetc(f);

    if (Version != OBJ_VERSION)
    {
        printf("Error - file \'%s\' is in an %s SNLink object file format - exiting\n",
            filename, Version < OBJ_VERSION ? "obsolete" : "unknown");

        fclose(f);
        return -5;
    }

    console_log("\nHeader : version %d\n", Version);

    const int Result = DumpObjInfo(filename, f, 0);

    fclose(f);
    return Result;
}

int main(int argc, char **argv)
{
    int ret = 0;
    std::string path = argv[1];
    for (const auto & entry : fs::recursive_directory_iterator(path))
    {
        if (fs::is_regular_file(entry.path()))
        {
            if (entry.path().u8string().find(".obj") != std::string::npos)
            {
                //std::cout << "Processing " << entry.path() << std::endl;
                ret = ProcessObj(entry.path().u8string().c_str());
                if (ret != 0)
                {
                    break;
                }
            }
        }
    }

    // We could read the map file to see how big the .text section is to calculate the progress
    // but since its fixed value that can never change may as well just hard code it.
    const size_t mgs_exe_text_section_len = 0x00088A24;
    const size_t totalSizeOfCFuncs = gFunctions.TotalSize();

    const float progress = (static_cast<float>(totalSizeOfCFuncs) / static_cast<float>(mgs_exe_text_section_len)) * 100.0f;

    printf("Bytes of code in .text total %d\n", mgs_exe_text_section_len);
    printf("Bytes of code in .text from src %d\n", totalSizeOfCFuncs);
    printf("Progress: %.2f%%\n", progress);

    return ret;
}
