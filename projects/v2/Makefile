# @author   clemedon (Clément Vidon)
####################################### BEG_2 ####

NAME        := icecream

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# SRCS      source files
# OBJS      object files
#
# CC        compiler
# CFLAGS    compiler flags
# CPPFLAGS  preprocessor flags

SRCS        := main.c
OBJS        := main.o

CC          := clang
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -I .

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove
# MAKE      quietly make

RM          := rm -f
MAKE        := $(MAKE) --no-print-directory

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# $(NAME)   linking .o -> binary
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@
	$(info CREATED $@)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

clean:
	$(RM) $(OBJS)

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

####################################### END_2 ####
