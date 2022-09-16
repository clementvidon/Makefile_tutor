# @author   clemedon (Clément Vidon)
####################################### BEG_5 ####

NAME        := icecream

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# LIBS_PATH libraries to be built
# LIBS_NAME libraries to be used
#
# INC_DIR   include directory
# INCS      include directories
#
# SRC_DIR   source directory
# SRCS      source files
#
# BUILD_DIR build directory
# OBJS      object files
# DEPS      dependency files
#
# CC        compiler
# CFLAGS    compiler flags
# CPPFLAGS  preprocessor flags
# LDFLAGS   linker flags
# LDLIBS    libraries name

LIBS_PATH   := \
	lib/libarom/libarom.a \
	lib/libbase/libbase.a
LIBS_NAME   := arom base m

INC_DIR     := include
INCS        := $(INC_DIR) $(dir $(LIBS_PATH))
INCS        := $(INCS) $(addsuffix $(INC_DIR)/,$(dir $(LIBS_PATH)))

SRC_DIR     := src
SRCS        := main.c
SRCS        := $(addprefix $(SRC_DIR)/,$(SRCS))

BUILD_DIR   := .build
OBJS        := $(subst .c,.o,$(SRCS))
OBJS        := $(subst $(SRC_DIR),$(BUILD_DIR),$(OBJS))

DEPS        := $(subst .o,.d,$(OBJS))
-include $(DEPS)

CC          := clang
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS     := $(addprefix -L,$(dir $(LIBS_PATH)))
LDLIBS      := $(addprefix -l,$(LIBS_NAME))

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        cleaning command

RM          := rm -f
MAKE        := $(MAKE) --silent --jobs --no-print-directory
DIR_DUP     = mkdir -p $(@D)

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# %.o       compilation .c -> .o
# $(NAME)   link .o -> archive
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal
# run       run the program
# info      print the default goal recipe

all: $(NAME)

$(LIBS_PATH):
	$(MAKE) -C $(@D)

$(NAME): $(OBJS) $(LIBS_PATH)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	$(info CREATED $(NAME))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

clean:
	for f in $(dir $(LIBS_PATH)); do $(MAKE) -C $$f clean; done
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	for f in $(dir $(LIBS_PATH)); do $(MAKE) -C $$f fclean; done
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: clean fclean re
.SILENT:

####################################### END_5 ####
