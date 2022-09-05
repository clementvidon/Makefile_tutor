NAME        := icecream

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# CC        compilers
# CFLAGS    compiler flags
# CPPFLAGS  preprocessor flags
#
# SRC_DIR   source directory
# OBJ_DIR   object directory
# SRCS      source files
# OBJS      object files

CC          := clang
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -I include

SRC_DIR     := src
OBJ_DIR     := obj
SRCS        := \
	main.c          \
	arom/coco.c     \
	base/milk.c     \
	base/water.c
SRCS        := $(SRCS:%=$(SRC_DIR)/%)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        cleaning command

RM          := rm --force

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# %.o       compilation .c -> .o
# $(NAME)   linking .o -> binary
# clean     remove .o
# fclean    clean + remove binary
# all       build all
# re        fclean + all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	-[ ! -d $(@D) ] && mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	echo "CREATED $@"

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)
	echo "CREATED $(NAME)"

clean:
	-[ -d $(OBJ_DIR) ] && $(RM) --recursive $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

all: $(NAME)

re:
	make --no-print-directory clean
	make --no-print-directory all

#------------------------------------------------#
#   SPECIAL                                      #
#------------------------------------------------#

.SILENT:
.PHONY: clean fclean all re
