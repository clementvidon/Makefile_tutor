# @author   clemedon (Clément Vidon)
####################################### BEG_4 ####

NAME        := icecream.a

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# CC        compiler
# CFLAGS    compiler flags
# CPPFLAGS  preprocessor flags
#
# SRC_DIR   source directory
# BUILD_DIR	object directory
# SRCS      source files
# OBJS      object files
# DEPS      dependency files

CC          := clang
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -MMD -MP -I include
AR          := ar
ARFLAGS     := -r -c -s

SRC_DIR     := src
BUILD_DIR	:= .build
SRCS        := \
	arom/coco.c \
	base/milk.c \
	base/water.c
SRCS        := $(SRCS:%=$(SRC_DIR)/%)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)
-include $(DEPS)

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        cleaning command

RM          := rm --force

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# %.o       compilation .c -> .o
# $(NAME)   link .o -> library
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	echo "CREATED $(NAME)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	-[ ! -d $(@D) ] && mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	echo "CREATED $@"

.PHONY: clean
clean:
	$(RM) --recursive $(BUILD_DIR)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re:
	make --no-print-directory fclean
	make --no-print-directory all

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#
# .SILENT   silences the rules

.SILENT:

####################################### END_4 ####
