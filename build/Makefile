# Make parameters:
# 	PSYQ_SDK=YourPath // Access for psyq folders from "YourPath"
#	COLORS=false // Disable colors codes and emojis
#	C_DEPS=false // Don't generate c files dependencies (.d files)
#	compare // Compare hash from last compiled .exe with the target one hardcoded
#	build // launch the old powershell compilation script "build.ps1"
#	clean // Remove objects folder
#	fclean // Remove objects folder and executable
#	re // Remake the whole project
#-------------------------------------------------------------------------------

NAME = _mgsi

CFLAGS = -O2 -G 8 -g -Wall
CFLAGS_STATICLIBS = -O2 -G 0 -g -Wall
AFLAGS = /l /q
LFLAGS = /e mts_printf_8008BBA0=0x8008BBA0 /c /n 4000 /q /gp .sdata /m

SRCS_PATH =	 ../src
ASM_PATH =   ../asm
OBJS_PATH =  ../obj
BUILD_PATH = ../build

# Add entries here if more depth is needed for finding source files
SRCS_PSYQ_3 =	mts/*.c	SD/*.c
SRCS_PSYQ_4 =	*.c	*/*.c */*/*.c
SRCS_ASM =		*.s	*/*.s */*/*.s

EXE_FILE = $(OBJS_PATH)/$(NAME).exe
CPE_FILE = $(OBJS_PATH)/$(NAME).cpe
SYM_FILE = $(OBJS_PATH)/$(NAME).sym
MAP_FILE = $(OBJS_PATH)/$(NAME).map

LINK_FILE = $(BUILD_PATH)/linker_command_file.txt

#-------------------------------------------------------------------------------

TARGET_HASH = 4B8252B65953A02021486406CFCDCA1C7670D1D1A8F3CF6E750EF6E360DC3A2F
ifeq ($(findstring compare,$(MAKECMDGOALS)),compare)
CURRENT_HASH = $(shell powershell.exe -c "(Get-FileHash -Path $(EXE_FILE) -Algorithm SHA256).Hash")
endif

ifeq ($(PSYQ_SDK),)
#default path
PSYQ_SDK := ../../psyq
PSYQ_SDK_REALPATH := $(PSYQ_SDK)
else
PSYQ_SDK_REALPATH := $(realpath $(PSYQ_SDK))
endif
PSYQ_3_PATH = $(PSYQ_SDK)\psyq_4.3
PSYQ_4_PATH = $(PSYQ_SDK)\psyq_4.4
PSYQ_3_BIN_PATH = $(PSYQ_SDK_REALPATH)/psyq_4.3/bin
PSYQ_4_BIN_PATH = $(PSYQ_SDK_REALPATH)/psyq_4.4/bin

SRCS_PSYQ_3 := $(wildcard $(addprefix $(SRCS_PATH)/,$(SRCS_PSYQ_3)))
SRCS_PSYQ_4 := $(wildcard $(addprefix $(SRCS_PATH)/,$(SRCS_PSYQ_4)))
SRCS_ASM	:= $(wildcard $(addprefix $(ASM_PATH)/,$(SRCS_ASM)))

OBJS_PSYQ_3 :=	$(patsubst %.c,%.obj,$(SRCS_PSYQ_3:$(SRCS_PATH)%=$(OBJS_PATH)%))
OBJS_PSYQ_4 :=	$(patsubst %.c,%.obj,$(SRCS_PSYQ_4:$(SRCS_PATH)%=$(OBJS_PATH)%))
OBJS_ASM :=		$(patsubst %.s,%.obj,$(SRCS_ASM:$(ASM_PATH)%=$(OBJS_PATH)%))

SRC_DIRS =	$(SRCS_PATH) $(sort $(dir $(wildcard $(SRCS_PATH)/*/))) \
			$(sort $(dir $(wildcard $(SRCS_PATH)/*/*/)))	\
			$(sort $(dir $(wildcard $(SRCS_PATH)/*/*/*/)))
ASM_DIRS =  $(ASM_PATH) $(sort $(dir $(wildcard $(ASM_PATH)/*/))) \
			$(sort $(dir $(wildcard $(ASM_PATH)/*/*/)))		\
			$(sort $(dir $(wildcard $(ASM_PATH)/*/*/*/)))
INCLUDES = $(addprefix -I ,$(SRC_DIRS))

OBJS_DIRS =		$(subst $(SRCS_PATH),$(OBJS_PATH),$(SRC_DIRS))	\
				$(subst $(ASM_PATH),$(OBJS_PATH),$(ASM_DIRS))
OBJS_DIRS := 	$(sort $(OBJS_DIRS))

export PSYQ_PATH := 			$(PSYQ_4_PATH)\bin
export C_PLUS_INCLUDE_PATH := 	$(PSYQ_4_PATH)\include
export C_INCLUDE_PATH := 		$(PSYQ_4_PATH)\include
export LIBRARY_PATH := 			$(PSYQ_4_PATH)\lib
export PSX_PATH := 				$(PSYQ_4_PATH)\bin)

# Add WSL compatibility
export WSLENV := PSYQ_SDK/p:PSYQ_PATH/p:C_PLUS_INCLUDE_PATH/p:C_INCLUDE_PATH/p:LIBRARY_PATH/p:PSX_PATH/p

ECHO = echo
ifneq ($(COLORS),false)
ECHO := echo -e

CGREY :=	\e[90m
CRED :=		\e[91m
CGREEN :=	\e[92m
CBLUE :=	\e[94m
CMAGENTA := \e[95m
CCYAN :=	\e[96m
CORANGE :=	\e[38;5;172m
CBROWN :=	\e[38;5;94m
ENDCOLOR :=	\e[0m
EMO_SUCCESS := 👌
EMO_FAIL :=	💩
endif

#-------------------------------------------------------------------------------
# Makefile special targets (https://www.gnu.org/software/make/manual/html_node/Special-Targets.html)

.ONESHELL:

.PHONY: all clean fclean re compare build

#-------------------------------------------------------------------------------
# Main rule/target

all: $(PSYQ_3_BIN_PATH)/psyq.ini $(PSYQ_4_BIN_PATH)/psyq.ini $(OBJS_DIRS) $(EXE_FILE)

#-------------------------------------------------------------------------------
# Create psyq.ini files

$(PSYQ_3_BIN_PATH)/PSYQ.ini.template $(PSYQ_4_BIN_PATH)/PSYQ.ini.template:
	@echo Error: Could not access $@ or psyq.ini is older than template
	@echo Make sure PSYQ_SDK is set with the correct path
	@echo PSYQ_SDK: '$(PSYQ_SDK)'
	@exit 1

$(PSYQ_3_BIN_PATH)/psyq.ini: $(PSYQ_3_BIN_PATH)/PSYQ.ini.template
	@echo "Creating $(PSYQ_3_PATH)\bin\psyq.ini"
	@echo "$(subst $$PSYQ_PATH,$(PSYQ_3_PATH),$(shell more $(PSYQ_3_PATH)\bin\PSYQ.ini.template))" > $@

$(PSYQ_4_BIN_PATH)/psyq.ini: $(PSYQ_4_BIN_PATH)/psyq.ini.template
	@echo "Creating $(PSYQ_4_PATH)\bin\psyq.ini"
	@echo "$(subst $$PSYQ_PATH,$(PSYQ_4_PATH),$(shell more $(PSYQ_4_PATH)\bin\PSYQ.ini.template))" > $@

#-------------------------------------------------------------------------------
# Create objects dirs

$(OBJS_DIRS):
	mkdir $(patsubst %,"%",$@) | exit 0

#-------------------------------------------------------------------------------
# Compile .c files and generate .d files

#--------------------------------------
ifneq ($(C_DEPS),false)
DEPFILES := $(OBJS_PSYQ_4:.obj=.obj.d)
-include $(wildcard $(DEPFILES))

.PRECIOUS: $(OBJS_PATH)/%.obj.d

$(OBJS_PATH)/%.obj.d: $(patsubst $(OBJS_PATH)%.obj.d,$(SRCS_PATH)%.c,$(OBJS_PATH)/%.obj.d)
	@$(ECHO) "$(CGREY)-> Updating dependencies $@$(ENDCOLOR)"
	@$(PSYQ_4_BIN_PATH)/ccpsx.exe -c $(patsubst $(OBJS_PATH)%.obj.d,$(SRCS_PATH)%.c,$@) -o $@ $(INCLUDES) -M

else
HEADERS_FILES := $(wildcard $(patsubst %.c,%.h,$(addprefix $(SRCS_PATH)/,$(SRCS_PSYQ_4))))
endif
#--------------------------------------

ifneq ($(C_DEPS),false)
$(OBJS_PATH)/mts/%.obj: $(SRCS_PATH)/mts/%.c $(OBJS_PATH)/mts/%.obj.d
	@echo "$(subst \ ,,$(patsubst $(SRCS_PATH)%.obj:,$(OBJS_PATH)%.obj:,$(shell more "$@.d")))" > $@.d
else
$(OBJS_PATH)/mts/%.obj: $(SRCS_PATH)/mts/%.c $(HEADERS_FILES)
endif
	@$(eval PSYQ_PATH = $(PSYQ_3_PATH)\bin)
	@$(eval C_PLUS_INCLUDE_PATH = $(PSYQ_3_PATH)\include)
	@$(eval C_INCLUDE_PATH = $(PSYQ_3_PATH)\include)
	@$(eval LIBRARY_PATH = $(PSYQ_3_PATH)\lib)
	@$(eval PSX_PATH = $(PSYQ_3_PATH)\bin)
	@$(ECHO) "-> Compiling with psyq_4.3 $(CBLUE)$<$(ENDCOLOR)"
	@$(PSYQ_3_BIN_PATH)/ccpsx.exe $(CFLAGS) -c $< -o $@ $(INCLUDES)

ifneq ($(C_DEPS),false)
$(OBJS_PATH)/SD/%.obj: $(SRCS_PATH)/SD/%.c $(OBJS_PATH)/SD/%.obj.d
	@echo "$(subst \ ,,$(patsubst $(SRCS_PATH)%.obj:,$(OBJS_PATH)%.obj:,$(shell more "$@.d")))" > $@.d
else
$(OBJS_PATH)/SD/%.obj: $(SRCS_PATH)/SD/%.c $(HEADERS_FILES)
endif
	@$(eval PSYQ_PATH = $(PSYQ_3_PATH)\bin)
	@$(eval C_PLUS_INCLUDE_PATH = $(PSYQ_3_PATH)\include)
	@$(eval C_INCLUDE_PATH = $(PSYQ_3_PATH)\include)
	@$(eval LIBRARY_PATH = $(PSYQ_3_PATH)\lib)
	@$(eval PSX_PATH = $(PSYQ_3_PATH)\bin)
	@$(ECHO) "-> Compiling with psyq_4.3 $(CBLUE)$<$(ENDCOLOR)"
	@$(PSYQ_3_BIN_PATH)/ccpsx.exe $(CFLAGS) -c $< -o $@ $(INCLUDES)

ifneq ($(C_DEPS),false)
$(OBJS_PATH)/%.obj: $(SRCS_PATH)/%.c $(OBJS_PATH)/%.obj.d
	@echo "$(subst \ ,,$(patsubst $(SRCS_PATH)%.obj:,$(OBJS_PATH)%.obj:,$(shell more "$@.d")))" > $@.d
else
$(OBJS_PATH)/%.obj: $(SRCS_PATH)/%.c $(HEADERS_FILES)
endif
	@$(eval PSYQ_PATH = $(PSYQ_4_PATH)\bin)
	@$(eval C_PLUS_INCLUDE_PATH = $(PSYQ_4_PATH)\include)
	@$(eval C_INCLUDE_PATH = $(PSYQ_4_PATH)\include)
	@$(eval LIBRARY_PATH = $(PSYQ_4_PATH)\lib)
	@$(eval PSX_PATH = $(PSYQ_4_PATH)\bin)
	@$(ECHO) "-> Compiling $(CCYAN)$<$(ENDCOLOR)"
	@$(PSYQ_4_BIN_PATH)/ccpsx.exe $(CFLAGS) -c $< -o $@ $(INCLUDES)

# Static libs

ifneq ($(C_DEPS),false)
$(OBJS_PATH)/Equip/%.obj: $(SRCS_PATH)/Equip/%.c $(OBJS_PATH)/Equip/%.obj.d
	@echo "$(subst \ ,,$(patsubst $(SRCS_PATH)%.obj:,$(OBJS_PATH)%.obj:,$(shell more "$@.d")))" > $@.d
else
$(OBJS_PATH)/Equip/%.obj: $(SRCS_PATH)/Equip/%.c $(HEADERS_FILES)
endif
	@$(eval PSYQ_PATH = $(PSYQ_4_PATH)\bin)
	@$(eval C_PLUS_INCLUDE_PATH = $(PSYQ_4_PATH)\include)
	@$(eval C_INCLUDE_PATH = $(PSYQ_4_PATH)\include)
	@$(eval LIBRARY_PATH = $(PSYQ_4_PATH)\lib)
	@$(eval PSX_PATH = $(PSYQ_4_PATH)\bin)
	@$(ECHO) "-> Compiling $(CCYAN)$<$(ENDCOLOR) with -G 0"
	@$(PSYQ_4_BIN_PATH)/ccpsx.exe $(CFLAGS_STATICLIBS) -c $< -o $@ $(INCLUDES)

#-------------------------------------------------------------------------------
# Compile .s files

$(OBJS_PATH)/%.obj: $(ASM_PATH)/%.s
	@$(eval PSYQ_PATH = $(PSYQ_4_PATH)\bin)
	@$(eval C_PLUS_INCLUDE_PATH = $(PSYQ_4_PATH)\include)
	@$(eval C_INCLUDE_PATH = $(PSYQ_4_PATH)\include)
	@$(eval LIBRARY_PATH = $(PSYQ_4_PATH)\lib)
	@$(eval PSX_PATH = $(PSYQ_4_PATH)\bin)
	@$(ECHO) "-> Compiling $(CBROWN)$<$(ENDCOLOR)"
	@$(PSYQ_4_BIN_PATH)/asmpsx.exe /j $(ASM_PATH) $(AFLAGS) $<,$@

#-------------------------------------------------------------------------------
# Link objects and generate .exe

$(CPE_FILE): $(OBJS_PSYQ_3) $(OBJS_PSYQ_4) $(OBJS_ASM)
	@$(eval PSYQ_PATH = $(PSYQ_4_PATH)\bin)
	@$(eval C_PLUS_INCLUDE_PATH = $(PSYQ_4_PATH)\include)
	@$(eval C_INCLUDE_PATH = $(PSYQ_4_PATH)\include)
	@$(eval LIBRARY_PATH = $(PSYQ_4_PATH)\lib)
	@$(eval PSX_PATH = $(PSYQ_4_PATH)\bin)
	@$(ECHO) "Linking to $(CMAGENTA)$(CPE_FILE)$(ENDCOLOR)"
	@$(PSYQ_4_BIN_PATH)/psylink.exe $(LFLAGS) @$(LINK_FILE),$(CPE_FILE),$(SYM_FILE),$(MAP_FILE)

$(EXE_FILE): $(CPE_FILE)
	@$(eval PSYQ_PATH = $(PSYQ_4_PATH)\bin)
	@$(eval C_PLUS_INCLUDE_PATH = $(PSYQ_4_PATH)\include)
	@$(eval C_INCLUDE_PATH = $(PSYQ_4_PATH)\include)
	@$(eval LIBRARY_PATH = $(PSYQ_4_PATH)\lib)
	@$(eval PSX_PATH = $(PSYQ_4_PATH)\bin)
	@$(ECHO) "Converting $(CMAGENTA)$(CPE_FILE)$(ENDCOLOR) to $(CGREEN)$(EXE_FILE)$(ENDCOLOR) using $(PSYQ_4_BIN_PATH)/cpe2exe.exe"
	@"$(PSYQ_4_BIN_PATH)/cpe2exe.exe" /CJ $(CPE_FILE) > $(OBJS_PATH)/log.txt
	@$(MAKE) --no-print-directory compare

#-------------------------------------------------------------------------------
# Utils

compare:
ifeq ($(TARGET_HASH),$(CURRENT_HASH)) # (Each access of CURRENT_HASH takes time)
	@$(ECHO) "$(CGREEN)OK: $(EXE_FILE) matches target hash$(ENDCOLOR) $(EMO_SUCCESS)"
else
	@$(ECHO) "$(CRED)FAIL: $(EXE_FILE) does not match target hash$(ENDCOLOR) $(EMO_FAIL)"
	@exit 1
endif

build:
	@echo "Executing build.ps1"
	@powershell.exe -File build.ps1 -psyq_path4dot4 $(PSYQ_4_PATH)\bin -psyq_path4dot3 $(PSYQ_3_PATH)\bin

#for appveyor only
progress:
	@echo "Executing progress.ps1"
	@powershell.exe -File progress.ps1

#-------------------------------------------------------------------------------
# Clean objects and remake

clean:
	@$(ECHO) "Removing $(OBJS_PATH)"
	@rm -rf "$(OBJS_PATH)"

fclean: clean
	@$(ECHO) "Removing $(EXE_FILE)"
	@rm -rf "$(EXE_FILE)"

re: fclean
	@$(MAKE) --no-print-directory
