# @author   clemedon (Clément Vidon)
####################################### BEG_5 ####

NAME        := icecream

#------------------------------------------------#
#   VARS                                         #
#------------------------------------------------#
# LIBS      libraries
# SRCS      source files
#
# LIB_DIR   library directory
# INC_DIR   include directory
# SRC_DIR   source directory
# BUILD_DIR build directory
#
# INCS		include directories
# OBJS      object files
# DEPS      dependency files
#
# CC        compiler
# CFLAGS    compiler flags
# CPPFLAGS  preprocessor flags
# LDFLAGS   TODO
# LDLIBS    TODO

LIBS        := lib_one/icecream lib_two/icecream
SRCS        := 		\
	main.c          \
	arom/coco.c     \
	base/milk.c     \
	base/water.c	\

LIB_DIR     := lib/
INC_DIR     := include/
SRC_DIR     := src/
BUILD_DIR   := .build/
LIBS        := $(addprefix $(LIB_DIR),$(dir $(LIBS)))
INCS        := $(INC_DIR) $(LIBS)
SRCS        := $(addprefix $(SRC_DIR),$(SRCS))
OBJS        := $(subst .c,.o,$(SRCS))
OBJS        := $(subst $(SRC_DIR),$(BUILD_DIR),$(OBJS))
DEPS        := $(OBJS:.o=.d)
-include $(DEPS)

CC          := clang
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -MMD -MP
CPPFLAGS    += $(addprefix -I,$(INCS))
LDFLAGS     := $(addprefix -L,$(LIBS))
LDLIBS      := $(addprefix -l,$(notdir $(LIBS)))
LDLIBS      += -lm

#------------------------------------------------#
#   TOOLS                                        #
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
	for f in $(LIBS); do $(MAKE) -C $$f; done
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	echo "CREATED $(NAME)"

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
	-[ ! -d $(@D) ] && mkdir -p  $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	echo "CREATED $@"

.PHONY: clean
clean:
	for f in $(LIBS); do $(MAKE) -C $$f clean; done
	$(RM) --recursive $(BUILD_DIR)

.PHONY: fclean
fclean: clean
	for f in $(LIBS); do $(MAKE) -C $$f fclean; done
	$(RM) $(NAME)

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all

#------------------------------------------------#
#   OPTIONS                                      #
#------------------------------------------------#
# .SILENT       silences all the rules

.SILENT:

####################################### END_5 ####
