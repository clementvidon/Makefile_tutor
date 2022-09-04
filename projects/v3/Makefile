####################################### BEG_3 ####

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

RM          := rm -f

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# %.o       compilation
# $(NAME)   default goal
# clean     remove objects
# fclean    clean + remove binary
# all       all targets
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
	echo "REMOVED $(OBJ_DIR)"

fclean: clean
	$(RM) $(NAME)
	echo "REMOVED $(NAME)"

all: $(NAME)

re: fclean all

#------------------------------------------------#
#   EXTRA RECIPES                                #
#------------------------------------------------#
# run           run the program

info:
	make --dry-run --always-make --no-print-directory | grep -v "echo \| mkdir"

run: re
	-./$(NAME)

#------------------------------------------------#
#   SPECIAL                                      #
#------------------------------------------------#

.SILENT:
.PHONY: clean fclean all re run info

####################################### END_3 ####
