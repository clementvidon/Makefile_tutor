####################################### BEG_2 ####

NAME        := icecream

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# CC        compilers
# CFLAGS    compiler flags
# CPPFLAGS  preprocessor flags
#
# SRCS      source files
# OBJS      object files

CC          := clang
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -I .

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
# %.o       compilation
# $(NAME)   default goal
# clean     remove objects
# fclean    clean + remove binary
# all       all targets
# re        fclean + all

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	echo "CREATED $@"

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)
	echo "CREATED $(NAME)"

clean:
	$(RM) $(OBJS)
	echo "REMOVED $(OBJS)"

fclean: clean
	$(RM) $(NAME)
	echo "REMOVED $(NAME)"

all: $(NAME)

re: fclean all

#------------------------------------------------#
#   EXTRA RECIPES                                #
#------------------------------------------------#
# run           run the program

run: re
	-./$(NAME)

#------------------------------------------------#
#   SPECIAL                                      #
#------------------------------------------------#

.SILENT:
.PHONY: clean fclean all re run

####################################### END_2 ####
