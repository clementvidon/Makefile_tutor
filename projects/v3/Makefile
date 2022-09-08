# @author   clemedon (Clément Vidon)
####################################### BEG_3 ####

NAME        := icecream

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# SRC_DIR   source directory
# OBJ_DIR   object directory
# SRCS      source files
# OBJS      object files
# CC        compiler
# CFLAGS    compiler flags
# CPPFLAGS  preprocessor flags

SRC_DIR     := src
OBJ_DIR     := obj
SRCS        := \
	main.c          \
	arom/coco.c     \
	base/milk.c     \
	base/water.c
SRCS        := $(SRCS:%=$(SRC_DIR)/%)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC          := clang
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -I include

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        cleaning command
# MAKE      make command

RM          := rm --force
MAKE        := make --no-print-directory

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# %.o       compilation .c -> .o
# $(NAME)   linking .o -> binary
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@
	echo "CREATED $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	-[ ! -d $(@D) ] && mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	echo "CREATED $@"

.PHONY: clean
clean:
	$(RM) --recursive $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)


.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#
# .SILENT   silences the rules

.SILENT:

####################################### END_3 ####
