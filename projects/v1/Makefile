####################################### BEG_1 ####

NAME        := icecream

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# CC        compilers
# CFLAGS    compiler flags
#
# SRCS      source files
# OBJS      object files

CC          := clang
CFLAGS      := -Wall -Wextra -Werror

SRCS        := main.c
OBJS        := main.o

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        cleaning command

RM          := rm -f

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# $(NAME)   final target
# clean     remove objects
# fclean    clean + remove binary
# all       all targets
# re        fclean + all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

all: $(NAME)

re: | fclean all

#------------------------------------------------#
#   SPECIAL                                      #
#------------------------------------------------#

.PHONY: clean fclean all re run

####################################### END_1 ####
