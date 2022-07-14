//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

char buff[1024];
#define PRINT(f_, ...) sprintf(buff, (f_), ##__VA_ARGS__)

size_t lastFuncOffset = 0;
size_t totalFuncsSize = 0;
size_t totalFuncs = 0;

static unsigned char class_types[] =
{
  0x6B, 0x6A, 0x69, 0x68, 0x67, 0x66, 0x65, 0x13, 0x12, 0x11,
  0x10, 0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x0A, 0x09, 0x08, 0x07,
  0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00
};

static void parse_class(unsigned int class_type1)
{
    int index;
    unsigned char* tp;
    int found;

    PRINT("class ");

	if (class_type1 + 1 > 0x6B) {
		PRINT("?%d? ", class_type1);
		return;
	}

	index = 28;
	tp = class_types;
	do
	{
		if (!index)
			break;

		found = *tp == (unsigned char)(class_type1 + 1);
		tp++;
		index--;
	} while (!found);

	switch (index)
	{
	case 0:
		PRINT("?%d? ", class_type1);
		break;
	case 1:
		PRINT("EFCN ");
		break;
	case 2:
		PRINT("NULL ");
		break;
	case 3:
		PRINT("AUTO ");
		break;
	case 4:
		PRINT("EXT ");
		break;
	case 5:
		PRINT("STAT ");
		break;
	case 6:
		PRINT("REG ");
		break;
	case 7:
		PRINT("EXTDEF ");
		break;
	case 8:
		PRINT("LABEL ");
		break;
	case 9:
		PRINT("ULABEL ");
		break;
	case 10:
		PRINT("MOS ");
		break;
	case 11:
		PRINT("ARG ");
		break;
	case 12:
		PRINT("STRTAG ");
		break;
	case 13:
		PRINT("MOU ");
		break;
	case 14:
		PRINT("UNTAG ");
		break;
	case 15:
		PRINT("TPDEF ");
		break;
	case 16:
		PRINT("USTATIC ");
		break;
	case 17:
		PRINT("ENTAG ");
		break;
	case 18:
		PRINT("MOE ");
		break;
	case 19:
		PRINT("REGPARM ");
		break;
	case 20:
		PRINT("FIELD ");
		break;
	case 21:
		PRINT("BLOCK ");
		break;
	case 22:
		PRINT("FCN ");
		break;
	case 23:
		PRINT("EOS ");
		break;
	case 24:
		PRINT("FILE ");
		break;
	case 25:
		PRINT("LINE ");
		break;
	case 26:
		PRINT("ALIAS ");
		break;
	case 27:
		PRINT("HIDDEN ");
		break;
	}
}

static void parse_type(int class_type2)
{
	unsigned int type1; // eax

	PRINT("type ");

	while (class_type2 & 0xFFF0) {
		type1 = (class_type2 >> 4) & 3;

		switch (type1) {
		case 1: PRINT("PTR "); break;
		case 2: PRINT("FCN "); break;
		default: {
			if (type1 > 2) {
				PRINT("ARY ");
			}
		} break;
		}

		class_type2 = ((class_type2 >> 2) & 0xFFF0) + (class_type2 & 0xF);
	}

	switch (class_type2)
	{
	case 0:
		PRINT("NULL ");
		break;
	case 1:
		PRINT("VOID ");
		break;
	case 2:
		PRINT("CHAR ");
		break;
	case 3:
		PRINT("SHORT ");
		break;
	case 4:
		PRINT("INT ");
		break;
	case 5:
		PRINT("LONG ");
		break;
	case 6:
		PRINT("FLOAT ");
		break;
	case 7:
		PRINT("DOUBLE ");
		break;
	case 8:
		PRINT("STRUCT ");
		break;
	case 9:
		PRINT("UNION ");
		break;
	case 10:
		PRINT("ENUM ");
		break;
	case 11:
		PRINT("MOE ");
		break;
	case 12:
		PRINT("UCHAR ");
		break;
	case 13:
		PRINT("USHORT ");
		break;
	case 14:
		PRINT("UINT ");
		break;
	case 15:
		PRINT("ULONG ");
		break;
	}
}

static void read_string(FILE* input) {
    unsigned char count = fgetc(input);

    for (int i = 0; i < count; ++i) {
        PRINT("%c", fgetc(input));
    }
}

static unsigned int read_word(FILE* input)
{
    int v2 = fgetc(input);
    return v2 + (fgetc(input) << 8);
}

static unsigned int read_dword(FILE* input)
{
    int v2 = fgetc(input);
    int v3 = (fgetc(input) << 8) + v2;
    int v4 = (fgetc(input) << 16) + v3;
    return v4 + (fgetc(input) << 24);
}

static void show_help()
{
    PRINT("dumpsym 2.02 (c) 1997 SN Systems Software Ltd\n");
    PRINT("Usage: dumpsym sym_file\n");
}

int main(int argc, const char** argv)
{
	int ver;
	int unit;
	int bin_pos;
	unsigned int offset;
	unsigned int tag;
	unsigned char byte_add;
	unsigned int word_add;
	unsigned int func_fp;
	unsigned int func_fsize;
	unsigned int func_retreg;
	unsigned int func_mask;
	unsigned int func_maskoffs;
	unsigned int func_line;
	unsigned int func_end_line;
	unsigned int block_start_line;
	unsigned int block_end_line;
	int class_def_type1;
	int class_def_type2;
	unsigned int class_def_obj_size;
	int class_def2_type1;
	int class_def2_type2;
	unsigned int class_def2_obj_size;
	unsigned int class_def2_dims_count;
	unsigned int class_def2_dim;
	unsigned int overlay_length;
	unsigned int overlay_id;
	unsigned int func2_fp;
	unsigned int func2_fsize;
	unsigned int func2_retreg;
	unsigned int func2_mask;
	unsigned int func2_maskoffs;
	unsigned int func2_fmask;
	unsigned int func2_fmaskoffs;
	unsigned int func2_line;
	unsigned char mx_info;

	if (argc != 2) {
		show_help();
		return 1;
	}

	FILE* f = fopen(argv[1], "rb");

	if (f == NULL) {
		PRINT("Error: Can't open file '%s' for input\n", argv[1]);
		return 1;
	}
	
	unsigned int line_num = 0;

	char sig[4];
	sig[0] = fgetc(f);
	sig[1] = fgetc(f);
	sig[2] = fgetc(f);
	sig[3] = 0;

	if (strncmp(sig, "MND", 3u)) {
		PRINT("Error: File '%s' is not in SN-SYM format\n", argv[1]);
		fclose(f);
		return 1;
	}

	PRINT("\nHeader : %s", sig);
	ver = fgetc(f);
	PRINT(" version %d\n", ver);
	unit = fgetc(f);
	PRINT("Target unit %d\n", unit);
	fgetc(f);
	fgetc(f);
	fgetc(f);

	while (1)
	{
		while (1)
		{
			bin_pos = ftell(f);
			PRINT("%06lx: ", bin_pos);
			offset = read_dword(f);
			tag = fgetc(f);
			if (tag != 8)
				break;
			mx_info = fgetc(f);
			PRINT("$%08lx %x MX-info %x\n", offset, 8, mx_info);
		}

		if (tag == -1)
			break;

		if (tag <= 0x7F) {
			PRINT("$%08lx %x ", offset, tag);
			read_string(f);
			PRINT("\n");
			continue;
		}

		switch (tag)
		{
		case 0x80u:
			PRINT("$%08lx %x Inc SLD linenum (to %ld)\n", offset, 0x80, ++line_num);
			break;
		case 0x82u:
			byte_add = fgetc(f);
			line_num += byte_add;
			PRINT("$%08lx %x Inc SLD linenum by byte %u (to %ld)\n", offset, tag, byte_add, line_num);
			break;
		case 0x84u:
			word_add = read_word(f);
			line_num += word_add;
			PRINT("$%08lx %x Inc SLD linenum by word %u (to %ld)\n", offset, tag, word_add, line_num);
			break;
		case 0x86u:
			line_num = read_dword(f);
			PRINT("$%08lx %x Set SLD linenum to %lu\n", offset, tag, line_num);
			break;
		case 0x88u:
			line_num = read_dword(f);
			PRINT("$%08lx %x Set SLD to line %lu of file ", offset, tag, line_num);
			read_string(f);
			PRINT("\n");
			break;
		case 0x8Au:
			PRINT("$%08lx %x End SLD info\n", offset, tag);
			break;
		case 0x8Cu:
			lastFuncOffset = offset;
			
			PRINT("$%08lx %x Function start\n", offset, 0x8C);
			func_fp = read_word(f);
			PRINT("    fp = %d\n", func_fp);
			func_fsize = read_dword(f);
			PRINT("    fsize = %ld\n", func_fsize);
			func_retreg = read_word(f);
			PRINT("    retreg = %d\n", func_retreg);
			func_mask = read_dword(f);
			PRINT("    mask = $%08lx\n", func_mask);
			func_maskoffs = read_dword(f);
			PRINT("    maskoffs = %ld\n", func_maskoffs);
			func_line = read_dword(f);
			PRINT("    line = %ld\n", func_line);
			PRINT("    file = ");
			read_string(f);
			PRINT("\n    name = ");
			read_string(f);
			PRINT("\n");
			break;
		case 0x8Eu:
			func_end_line = read_dword(f);
			PRINT("$%08lx %x Function end   line %ld\n", offset, tag, func_end_line);
		//	printf("adding size: %d\n", (offset - lastFuncOffset));
			totalFuncsSize += (offset - lastFuncOffset);
			totalFuncs++;
			break;
		case 0x90u:
			block_start_line = read_dword(f);
			PRINT("$%08lx %x Block start  line = %ld\n", offset, tag, block_start_line);
			break;
		case 0x92u:
			block_end_line = read_dword(f);
			PRINT("$%08lx %x Block end  line = %ld\n", offset, tag, block_end_line);
			break;
		case 0x94u:
			PRINT("$%08lx %x Def ", offset, 0x94);
			class_def_type1 = read_word(f);
			parse_class(class_def_type1);
			class_def_type2 = read_word(f);
			parse_type(class_def_type2);
			class_def_obj_size = read_dword(f);
			PRINT("size %ld ", class_def_obj_size);
			PRINT("name ");
			read_string(f);
			PRINT("\n");
			break;
		case 0x96u:
			PRINT("$%08lx %x Def2 ", offset, tag);
			class_def2_type1 = read_word(f);
			parse_class(class_def2_type1);
			class_def2_type2 = read_word(f);
			parse_type(class_def2_type2);
			class_def2_obj_size = read_dword(f);
			PRINT("size %ld ", class_def2_obj_size);
			class_def2_dims_count = read_word(f);
			PRINT("dims %ld ", class_def2_dims_count);
			for (; class_def2_dims_count; --class_def2_dims_count)
			{
				class_def2_dim = read_dword(f);
				PRINT("%ld ", class_def2_dim);
			}
			PRINT("tag ");
			read_string(f);
			PRINT(" name ");
			read_string(f);
			PRINT("\n");
			break;
		case 0x98u:
			overlay_length = read_dword(f);
			overlay_id = read_dword(f);
			PRINT("$%08lx overlay length $%08lx id $%lx\n", offset, overlay_length, overlay_id);
			break;
		case 0x9Au:
			PRINT("$%08lx set overlay\n", offset);
			break;
		case 0x9Cu:
			PRINT("$%08lx %x Function2 start\n", offset, tag);
			func2_fp = read_word(f);
			PRINT("    fp = %d\n", func2_fp);
			func2_fsize = read_dword(f);
			PRINT("    fsize = %ld\n", func2_fsize);
			func2_retreg = read_word(f);
			PRINT("    retreg = %d\n", func2_retreg);
			func2_mask = read_dword(f);
			PRINT("    mask = $%08lx\n", func2_mask);
			func2_maskoffs = read_dword(f);
			PRINT("    maskoffs = %ld\n", func2_maskoffs);
			func2_fmask = read_dword(f);
			PRINT("    fmask = $%08lx\n", func2_fmask);
			func2_fmaskoffs = read_dword(f);
			PRINT("    fmaskoffs = %ld\n", func2_fmaskoffs);
			func2_line = read_dword(f);
			PRINT("    line = %ld\n", func2_line);
			PRINT("    file = ");
			read_string(f);
			PRINT("\n    name = ");
			read_string(f);
			PRINT("\n");
			break;
		case 0x9Eu:
			PRINT("$%08lx %x Mangled name \"", offset, 0x9E);
			read_string(f);
			PRINT("\" is \"");
			read_string(f);
			PRINT("\n");
			break;
		default:
			PRINT("??? %d ???\n\n", tag);
			break;
		}
	}

	fclose(f);
	
	size_t totalFuncsToReverse = 1990;
	size_t textSectionLength = 0x00077D50;
	float progress = ((float)totalFuncsSize / (float)textSectionLength) * 100.0f;
	float funcsProgress = ((float)totalFuncs / (float)totalFuncsToReverse) * 100.0f;
	
	printf("Reversed funcs: %6d / ~%-5d (%.2f%%)\n", totalFuncs, totalFuncsToReverse, funcsProgress);
//	printf("Bytes of code in .text total:     %6d\n", textSectionLength);
//    printf("Bytes of code in .text from src:  %6d\n", totalFuncsSize);
	printf("Reversed bytes: %6d / %-6d (%.2f%%)\n", totalFuncsSize, textSectionLength, progress);
//	printf("Progress:       %.3f%%\n", progress);
	return 0;
}
