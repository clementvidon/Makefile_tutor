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

RM          := rm --force

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# $(NAME)   linking .o -> binary
# clean     remove .o
# fclean    clean + remove binary
# all       build all
# re        fclean + all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

all: $(NAME)

re:
	make --no-print-directory clean
	make --no-print-directory all

#------------------------------------------------#
#   SPECIAL                                      #
#------------------------------------------------#

.PHONY: clean fclean all re
