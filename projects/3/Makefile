NAME        := icecream

#------------------------------------------------#
#   VARIABLES                                    #
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
	main.c \
	arom/coco.c \
	base/milk.c \
	base/water.c
SRCS        := $(SRCS:%=$(SRC_DIR)/%)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#------------------------------------------------#
#   TOOLS                                        #
#------------------------------------------------#
# RM        cleaning command

RM          := rm -f

#------------------------------------------------#
#   BASIC RULES                                  #
#------------------------------------------------#
# all       build all targets
# $(NAME)   build $(NAME) target
# clean     remove objects
# fclean    remove objects and binary
# re        remove objects and binary and rebuild all

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)
	echo "CREATED $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	-[ ! -d $(@D) ] && mkdir -p  $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	echo "CREATED $@"

clean:
	-[ -d $(OBJ_DIR) ] && $(RM) --recursive $(OBJ_DIR)
	echo "REMOVED $(OBJ_DIR)"

fclean: clean
	$(RM) $(NAME)
	echo "REMOVED $(NAME)"

re: fclean all

#------------------------------------------------#
#   CUSTOM RULES                                 #
#------------------------------------------------#
# run           run the program

info:
	make --dry-run --always-make --no-print-directory | grep -v "echo \| mkdir"

run: re
	-./$(NAME)

#------------------------------------------------#
#   SPECIAL TARGETS                              #
#------------------------------------------------#

.SILENT:
.PHONY: all clean fclean re run
