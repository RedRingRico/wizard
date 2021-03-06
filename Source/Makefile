###############################################################################
#                                                   Wizard Makefile [DOS x86] #
###############################################################################
ifndef TOPDIR
export TOPDIR		:= $(shell cd ../ && pwd)
export TOPSRC		= $(TOPDIR)/Source
export TARGETDIR	= $(TOPDIR)/Bin/$(PLATFORM)/$(ARCH)/$(BITSIZE)
export OBJSDIR		= $(TOPDIR)/Obj/$(PLATFORM)/$(ARCH)/$(BITSIZE)/GCC/$(GCCVER)/$(BUILD)
endif
SOURCEDIR	= Source ../Common/Source

PROJECT := Wizard
TARGET := $(PROJECT)
OUTFILE	=	$(TARGETDIR)/$(TARGET).exe

PLATFORM		:= DOS
BUILD_PLATFORM	:= DOS
BUILD_ARCH		:= X86
ARCH			:= x86
BITSIZE			:= 32

GCCVER	= $(shell $(CC) -dumpversion)

BUILD_TYPE := debug

CC = i586-pc-msdosdjgpp-gcc

CFLAGS	=	-c -m$(BITSIZE) -DWIZ_BUILD_$(BUILD_DEF) \
				-DWIZ_PLATFORM_$(BUILD_PLATFORM) \
				-DWIZ_PLATFORM_$(BUILD_PLATFORM)_$(BUILD_ARCH) \
				-DWIZ_PLATFORM_$(BUILD_PLATFORM)_$(BUILD_ARCH)_$(BITSIZE) \
				-DWIZ_BITSIZE_$(BITSIZE) -DWIZ_ARCH_$(BUILD_ARCH) \
				-I $(TOPSRC)/Headers
SYSIPATH	=
INCPATH		=
SYSLPATH	=	
LIBPATH		=
SYSLIBS		= -lm
LINKFLAGS	=

##### Debug #######
debug:		BUILD		= Debug
debug:		BUILD_TYPE	= debug
debug:		BUILD_DEF	= DEBUG
debug:		TARGET := $(TARGET)D
debug:		CFLAGS += -g -ggdb -Wall -D_DEBUG $(CFLAGS_EXT)
debug:		LIBS =
debug:		$(TARGET)

##### Release #####
release:	BUILD		= Release
release:	BUILD_TYPE	= release
release:	BUILD_DEF	= RELEASE
release:	TARGET := $(TARGET)
release:	CFLAGS += -O3 -s $(CFLAGS_EXT)
release:	LIBS =
release:	LINKFLAGS += -Wl,-S
release:	$(TARGET)

##### Profile #####
profile:	BUILD		= Profile
profile:	BUILD_TYPE	= profile
profile:	BUILD_DEF	= PROFILE
profile:	TARGET := $(TARGET)P
profile:	CFLAGS += -O3 -g -ggdb -Wall -D_DEBUG $(CFLAGS_EXT)
profile:	LIBS =
profile:	$(TARGET)

##### Build the object files while not in the Obj directory ###################
ifneq ($(OBJSDIR), $(CURDIR))

VERSIONINFO:
	@printf "%s" "------------------------- Generating Version Information ---"
	@printf "%s\n" "-------------------"
	@mkdir -p Headers
	@sh ./GitVersion.sh ./Headers/GitVersion.h $(PROJECT)
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n" "-------------------"

TARGETDIR:
	@mkdir -p $(TARGETDIR)

OBJSDIR:
	@mkdir -p $(OBJSDIR)

CFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.c)))
export VPATH	:= $(foreach dir,$(SOURCEDIR),$(CURDIR)/$(dir))
export OBJS		:= $(CFILES:.c=.o)

$(TARGET): OBJSDIR TARGETDIR VERSIONINFO
	@/usr/bin/time -f "%E" -o $(OBJSDIR)/compiletime $(MAKE) \
	--no-print-directory -C $(OBJSDIR) -f $(TOPSRC)/Makefile \
	$(BUILD_TYPE)
	@printf "\n%s" "----------------------------------------------------------"
	@printf "%s\n" "---------------------"
	@printf "Compile time: "
	@cat $(OBJSDIR)/compiletime
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n" "-------------------"

else

##### In the intermediate build directory #####################################

$(TARGET): $(OBJS)
	@printf "\n\n%s" "------------------------- MESSAGES FROM THE COMPILER ---"
	@printf "%s\n" "-----------------------"
	@cat *.cmsgs
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n\n" "-------------------"
	@printf "Creating: $(OUTFILE)... "
	@$(CC) -o $(OUTFILE) $(LINKFLAGS) -m$(BITSIZE) $(OBJS) $(SYSLPATH) \
	$(LIBPATH) $(LIBS) $(SYSLIBS) 2> lmsgs;\
	RETVAL=$$?;\
	if env | grep -q ^TERM=; then\
		COLOURSUPPORT=`tput colors`;\
		if [ $$COLOURSUPPORT -gt -1 ]; then\
			cat lmsgs | sed ''/error/s//`printf "\033[31merror\033[0m"`/'' > lmsgs;\
			cat lmsgs | sed ''/warning/s//`printf "\034[31mwarning\033[0m"`/'' > lmsgs;\
		fi;\
	fi;\
	if [[ $$RETVAL == 0 ]]; then\
		printf "[OK]\n";\
	else\
		printf "\n\n%s" "------------------------------------ ERROR --------";\
		printf "%s\n" "----------------------------";\
		cat lmsgs;\
		printf "%s" "-------------------------------------------------------";\
		printf "%s\n" "------------------------";\
		exit 1;\
	fi

%.o: %.c
	@printf "Compiling: $<... "
	@$(CC) -MMD -MP -MF $*.d $(CFLAGS) $(SYSIPATH) $(INCPATH) \
	$< -o $@ 2> $*.cmsgs;\
	RETVAL=$$?;\
	if env | grep -q ^TERM=; then\
		COLOURSUPPORT=`tput colors`;\
		if [ $$COLOURSUPPORT -gt -1 ]; then\
			cat $*.cmsgs | sed ''/error/s//`printf "\033[31merror\033[0m"`/'' > $*.cmsgs;\
			cat $*.cmsgs | sed ''/warning/s//`printf "\033[34mwarning\033[0m"`/'' > $*.cmsgs;\
		fi;\
	fi;\
	if [[ $$RETVAL == 0 ]]; then\
		printf "[OK]\n";\
	else\
		printf "\n\n%s" "--------------------------------- ERROR -----------";\
		printf "%s\n" "----------------------------";\
		cat $*.cmsgs;\
		printf "%s" "-------------------------------------------------------";\
		printf "%s\n\n" "------------------------";\
		exit 1;\
	fi

-include $(OBJSDIR)/*.d

endif

.PHONY: clean completeclean
clean:
	@printf "Removing files from: $(TARGETDIR)... "
	@rm -f $(TARGETDIR)/*
	@printf "[OK]\n"
	@printf "Removing files from: $(OBJSDIR)... "
	@rm -rf $(OBJSDIR)/*
	@printf "[OK]\n"

completeclean:
	@printf "Removing files from: $(TOPDIR)/Bin... "
	@rm -rf $(TOPDIR)/Bin
	@printf "[OK]\n"
	@printf "Removing files from: $(TOPDIR)/Obj... "
	@rm -rf $(TOPDIR)/Obj
	@printf "[OK]\n"

