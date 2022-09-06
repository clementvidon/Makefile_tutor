NAME        := icecream.a

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# CC        compilers
# CFLAGS    compiler flags
# CPPFLAGS  preprocessor flags
#
# SRC_DIR   source directory
# BUILD_DIR	object directory
# SRCS      source files
# OBJS      object files
# DEPS      dependency files
# NODEPS    no-dependency files

CC          := clang
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -MMD -MP -I include

SRC_DIR     := src
BUILD_DIR	:= .build
SRCS        := \
	arom/coco.c		\
	base/milk.c		\
	base/water.c
SRCS        := $(SRCS:%=$(SRC_DIR)/%)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)
NODEPS		:= fclean clean
ifneq ($(MAKECMDGOALS), NODEPS)
	-include $(DEPS)
endif

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

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	-[ ! -d $(@D) ] && mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	echo "CREATED $@"

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	echo "CREATED $(NAME)"

clean:
	-[ -d $(BUILD_DIR) ] && $(RM) --recursive $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

all: $(NAME)

re: fclean all

#------------------------------------------------#
#   SPECIAL                                      #
#------------------------------------------------#

.SILENT:
.PHONY: clean fclean all re
