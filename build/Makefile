# Tested with "make v4.2.1", use "make -j" for faster compilation

# Define PSYQ_SDK in your environment variables before calling this makefile
ifeq ($(PSYQ_SDK),)
	PSYQ_SDK := ../../psyq_sdk
	PSYQ_SDK_REALPATH := $(PSYQ_SDK)
else
	PSYQ_SDK_REALPATH := $(realpath $(PSYQ_SDK))
endif
PSYQ_4_4_PATH = $(PSYQ_SDK)/psyq_4.4
PSYQ_4_3_PATH = $(PSYQ_SDK)/psyq_4.3
PSYQ_BIN_PATH = $(PSYQ_SDK_REALPATH)/psyq_4.4/bin

ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

NAME = _mgsi

CFLAGS = -O2 -G 8 -g -c -Wall
AFLAGS = /l /q
LFLAGS = /e mts_printf_8008BBA0=0x8008BBA0 /c /n 4000 /q /gp .sdata /m

SRCS_PATH =	 ../src
ASM_PATH =   ../asm
OBJS_PATH =  ../obj
BUILD_PATH = ../build

LINK_FILE = $(BUILD_PATH)/linker_command_file.txt

SRCS_PSYQ_4_3 = mts/*.c	SD/*.c
SRCS_PSYQ_4_4 = *.c	*/*.c */*/*.c
SRCS_ASM = 		*.s	*/*.s */*/*.s

HEADERS_FILES := $(wildcard $(patsubst %.c,%.h,$(addprefix $(SRCS_PATH)/,$(SRCS_PSYQ_4_4))))

SRCS_PSYQ_4_3 := $(wildcard $(addprefix $(SRCS_PATH)/,$(SRCS_PSYQ_4_3)))
SRCS_PSYQ_4_4 := $(wildcard $(addprefix $(SRCS_PATH)/,$(SRCS_PSYQ_4_4)))
SRCS_ASM	  := $(wildcard $(addprefix $(ASM_PATH)/,$(SRCS_ASM)))

OBJS_PSYQ_4_3 := $(patsubst %.c,%.obj,$(SRCS_PSYQ_4_3:$(SRCS_PATH)%=$(OBJS_PATH)%))
OBJS_PSYQ_4_4 := $(patsubst %.c,%.obj,$(SRCS_PSYQ_4_4:$(SRCS_PATH)%=$(OBJS_PATH)%))
OBJS_ASM :=		 $(patsubst %.s,%.obj,$(SRCS_ASM:$(ASM_PATH)%=$(OBJS_PATH)%))

SRC_DIRS =	$(sort $(dir $(wildcard $(SRCS_PATH)/*/)))		\
			$(sort $(dir $(wildcard $(SRCS_PATH)/*/*/)))	\
			$(sort $(dir $(wildcard $(SRCS_PATH)/*/*/*/)))
ASM_DIRS =  $(sort $(dir $(wildcard $(ASM_PATH)/*/)))		\
			$(sort $(dir $(wildcard $(ASM_PATH)/*/*/)))		\
			$(sort $(dir $(wildcard $(ASM_PATH)/*/*/*/)))

INCLUDES = $(addprefix -I ,$(SRC_DIRS))

OBJS_DIRS =		$(subst $(SRCS_PATH),$(OBJS_PATH),$(SRC_DIRS))	\
				$(subst $(ASM_PATH),$(OBJS_PATH),$(ASM_DIRS))
OBJS_DIRS := 	$(sort $(OBJS_DIRS))

TARGET_SHA256 = 4b8252b65953a02021486406cfcdca1c7670d1d1a8f3cf6e750ef6e360dc3a2f

export PSYQ_PATH := 			$(PSYQ_4_4_PATH)/bin
export C_PLUS_INCLUDE_PATH := 	$(PSYQ_4_4_PATH)/include
export C_INCLUDE_PATH := 		$(PSYQ_4_4_PATH)/include
export LIBRARY_PATH := 			$(PSYQ_4_4_PATH)/lib
export PSX_PATH := 				$(PSYQ_4_4_PATH)/bin)

# Add WSL compatibility
export WSLENV := PSYQ_SDK/p:PSYQ_PATH/p:C_PLUS_INCLUDE_PATH/p:C_INCLUDE_PATH/p:LIBRARY_PATH/p:PSX_PATH/p

CGREY :=	\e[90m
CRED :=		\e[91m
CGREEN :=	\e[92m
CBLUE :=	\e[94m
CMAGENTA := \e[95m
CCYAN :=	\e[96m
CORANGE :=	\e[38;5;208m
ENDCOLOR :=	\e[0m

.PHONY: all clean fclean re compare

all: $(OBJS_DIRS) $(OBJS_PATH)/$(NAME).exe

$(OBJS_DIRS):
	@mkdir -p $(OBJS_DIRS)

$(OBJS_PATH)/mts/%.obj: $(SRCS_PATH)/mts/%.c $(HEADERS_FILES)
	@$(eval PSYQ_PATH = $(PSYQ_4_3_PATH)/bin)
	@$(eval C_PLUS_INCLUDE_PATH = $(PSYQ_4_3_PATH)/include)
	@$(eval C_INCLUDE_PATH = $(PSYQ_4_3_PATH)/include)
	@$(eval LIBRARY_PATH = $(PSYQ_4_3_PATH)/lib)
	@$(eval PSX_PATH = $(PSYQ_4_3_PATH)/bin)
	@echo -e "-> Compiling with psyq_4.3 $(CBLUE)$<$(ENDCOLOR)"
	@$(PSYQ_BIN_PATH)/ccpsx.exe $(CFLAGS) $^ -o $@ $(INCLUDES)

$(OBJS_PATH)/SD/%.obj: $(SRCS_PATH)/SD/%.c $(HEADERS_FILES)
	@$(eval PSYQ_PATH = $(PSYQ_4_3_PATH)/bin)
	@$(eval C_PLUS_INCLUDE_PATH = $(PSYQ_4_3_PATH)/include)
	@$(eval C_INCLUDE_PATH = $(PSYQ_4_3_PATH)/include)
	@$(eval LIBRARY_PATH = $(PSYQ_4_3_PATH)/lib)
	@$(eval PSX_PATH = $(PSYQ_4_3_PATH)/bin)
	@echo -e "-> Compiling with psyq_4.3 $(CBLUE)$<$(ENDCOLOR)"
	@$(PSYQ_BIN_PATH)/ccpsx.exe $(CFLAGS) $^ -o $@ $(INCLUDES)

$(OBJS_PATH)/%.obj: $(SRCS_PATH)/%.c $(HEADERS_FILES)
	@$(eval PSYQ_PATH = $(PSYQ_4_4_PATH)/bin)
	@$(eval C_PLUS_INCLUDE_PATH = $(PSYQ_4_4_PATH)/include)
	@$(eval C_INCLUDE_PATH = $(PSYQ_4_4_PATH)/include)
	@$(eval LIBRARY_PATH = $(PSYQ_4_4_PATH)/lib)
	@$(eval PSX_PATH = $(PSYQ_4_4_PATH)/bin)
	@echo -e "-> Compiling $(CCYAN)$<$(ENDCOLOR)"
	@$(PSYQ_BIN_PATH)/ccpsx.exe $(CFLAGS) $^ -o $@ $(INCLUDES)

$(OBJS_PATH)/%.obj: $(ASM_PATH)/%.s
	@$(eval PSYQ_PATH = $(PSYQ_4_4_PATH)/bin)
	@$(eval C_PLUS_INCLUDE_PATH = $(PSYQ_4_4_PATH)/include)
	@$(eval C_INCLUDE_PATH = $(PSYQ_4_4_PATH)/include)
	@$(eval LIBRARY_PATH = $(PSYQ_4_4_PATH)/lib)
	@$(eval PSX_PATH = $(PSYQ_4_4_PATH)/bin)
	@echo -e "-> Compiling $(CGREY)$<$(ENDCOLOR)"
	@$(PSYQ_BIN_PATH)/asmpsx.exe /j $(ASM_PATH) $(AFLAGS) $^,$@

$(OBJS_PATH)/$(NAME).cpe: $(OBJS_PSYQ_4_3) $(OBJS_PSYQ_4_4) $(OBJS_ASM)
	@$(eval PSYQ_PATH = $(PSYQ_4_4_PATH)/bin)
	@$(eval C_PLUS_INCLUDE_PATH = $(PSYQ_4_4_PATH)/include)
	@$(eval C_INCLUDE_PATH = $(PSYQ_4_4_PATH)/include)
	@$(eval LIBRARY_PATH = $(PSYQ_4_4_PATH)/lib)
	@$(eval PSX_PATH = $(PSYQ_4_4_PATH)/bin)
	@echo -e "Linking to $(CMAGENTA)$(OBJS_PATH)/$(NAME).cpe$(ENDCOLOR)"
	@$(PSYQ_BIN_PATH)/psylink.exe $(LFLAGS) @$(LINK_FILE),\
	$(OBJS_PATH)/$(NAME).cpe,\
	$(OBJS_PATH)/$(NAME).sym,\
	$(OBJS_PATH)/$(NAME).map

$(OBJS_PATH)/$(NAME).exe: $(OBJS_PATH)/$(NAME).cpe
	@$(eval PSYQ_PATH = $(PSYQ_4_4_PATH)/bin)
	@$(eval C_PLUS_INCLUDE_PATH = $(PSYQ_4_4_PATH)/include)
	@$(eval C_INCLUDE_PATH = $(PSYQ_4_4_PATH)/include)
	@$(eval LIBRARY_PATH = $(PSYQ_4_4_PATH)/lib)
	@$(eval PSX_PATH = $(PSYQ_4_4_PATH)/bin)
	@echo -e "Converting $(CMAGENTA)$(OBJS_PATH)/$(NAME).cpe$(ENDCOLOR) to $(CGREEN)$(NAME).exe$(ENDCOLOR)"
	@$(PSYQ_BIN_PATH)/cpe2exe.exe /CJ $(OBJS_PATH)/$(NAME).cpe | /dev/null
	@$(MAKE) -s compare

compare:
	@if [ $(TARGET_SHA256) = `sha256sum $(OBJS_PATH)/$(NAME).exe | head -c 64` ]; then\
        echo -e "$(CGREEN)Generated $(NAME).exe does match$(ENDCOLOR) 👌";\
	else\
		echo -e "$(CRED)Generated $(NAME).exe does not match$(ENDCOLOR) 💩";\
    fi

clean:
	@rm -rf $(OBJS_PATH)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	@$(MAKE) -s

