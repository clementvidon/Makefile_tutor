# @author   clemedon (Clément Vidon)
####################################### BEG_5 ####

NAME        := icecream

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# LIBS_NAME	local lib name
# LIBS_PATH	local lib path
# INC_DIR   include directory
# INCS		include directories
# SRC_DIR   source directory
# SRCS      source files
# BUILD_DIR build directory
# OBJS      object files
# DEPS      dependency files
# CC        compiler
# CFLAGS    compiler flags
# CPPFLAGS  preprocessor flags
# LDFLAGS   linker flags
# LDLIBS    library names

LIBS_NAME	:= base arom m
LIBS_PATH	:= $(addsuffix /,$(wildcard lib/*))

INC_DIR     := include/
INCS        := $(INC_DIR) $(LIBS_PATH)
INCS        := $(INCS) $(addsuffix $(INC_DIR),$(LIBS_PATH))

SRC_DIR     := src/
SRCS        := main.c
SRCS        := $(addprefix $(SRC_DIR),$(SRCS))

BUILD_DIR   := .build/
OBJS        := $(subst .c,.o,$(SRCS))
OBJS        := $(subst $(SRC_DIR),$(BUILD_DIR),$(OBJS))

DEPS        := $(subst .o,.d,$(OBJS))
-include $(DEPS)

CC          := clang
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS     := $(addprefix -L,$(LIBS_PATH))
LDLIBS      := $(addprefix -l,$(LIBS_NAME))

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        cleaning command

RM          := rm --force
MAKE        := make --silent --jobs --no-print-directory

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# %.o       compilation .c -> .o
# $(NAME)   link .o -> archive
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal
# run		run the program
# info		print the default goal recipe

all: $(NAME)

$(NAME): $(OBJS)
	for f in $(LIBS_PATH); do $(MAKE) -C $$f; done
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
	-[ ! -d $(@D) ] && mkdir -p  $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	for f in $(LIBS_PATH); do $(MAKE) -C $$f clean; done
	$(RM) --recursive $(BUILD_DIR)

.PHONY: fclean
fclean: clean
	for f in $(LIBS_PATH); do $(MAKE) -C $$f fclean; done
	$(RM) $(NAME)

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#
# .SILENT       silences all the rules

.SILENT:
