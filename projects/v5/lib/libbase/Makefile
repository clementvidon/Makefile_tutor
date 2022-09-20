# @author   clemedon (Clément Vidon)
####################################### BEG_4 ####

NAME        := libbase.a

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# SRC_DIR   source directory
# BUILD_DIR object directory
# SRCS      source files
#
# OBJS      object files
# DEPS      dependency files
#
# CC        compiler
# CFLAGS    compiler flags
# CPPFLAGS  preprocessor flags

SRC_DIR     := src
BUILD_DIR   := .build
SRCS        := \
	milk.c \
	water.c

SRCS        := $(SRCS:%=$(SRC_DIR)/%)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

CC          := clang
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -MMD -MP -I include
AR          := ar
ARFLAGS     := -r -c -s

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove
# MAKE      quietly make
# DIR_DUP   duplicate directory tree

RM          := rm -f
MAKE        := $(MAKE) --no-print-directory
DIR_DUP     = mkdir -p $(@D)

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# $(NAME)   link .o -> library
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^
	$(info CREATED $@)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	$(info CREATED $@)

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: clean fclean re
.SILENT:

####################################### END_4 ####
