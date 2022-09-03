<h1 align="center">
	MAKEFILE TUTOR
</h1>

<h3 align="center">
	<a href="#Summary">Summary</a>
	<span> · </span>
	<a href="#Glossary">Glossary</a>
	<span> · </span>
	<a href="#Glossary">Syntax</a>
	<span> · </span>
	<a href="#Template">Template</a>
	<span> · </span>
	<a href="#Sources">Sources</a>
	<span> · </span>
	<a href="#Todo">Todo</a>
</h3>

## Summary

Addressed to beginners and not to newcomers, the idea behind this tutorial is to
focus on the essentials. The basics such as syntax specifications or anything
not directly related to the template we are going to explore will not be covered
here.

Initially intended to help 42 students to step up their Makefile skills through
a documented template that evolves gradually, step by step. With the aim of
making them more digestible and even tasty 🍔

<hr>

***[LAST UPDATE]***
- Add **[GitHub Page](https://clemedon.github.io/Makefile_tutor/)** version
- Add *[projects](projects)* directory
- Add *[Syntax](#syntax)* section
- Add *BEG* and *END* to highlight the template beginning and the end
- Update *[Todo](#todo)* section

***[NEXT UPDATE]***

- Auto-Dependency Generation
- C++

## Glossary

Our template will be composed of the following parts:
```
####### BEG     mark the beginning of the template
INGREDIENTS     variables containing the build ingredients
UTENSILS        variables containing shell command tools
RECIPES         minimum essential set of rules
EXTRA RECIPES   custom rules
SPECIAL         make "special targets"
####### END     mark the end of the template
```
What we call a `rule` is made of:

- `targets` is the file name we want to make
- `prerequisites` are files required (dependencies) for the `rule` to execute
- `recipe` are any lines that begins with a `TAB` and appear in a "rule context"

```
target: prerequisite
    recipe line 1
    recipe line 2
    ...
```

## Syntax

Like every makefile our template use a combination of *makefile syntax* and
*shell script syntax*.  The *shell script syntax* is reserved and limited to
*recipe lines*, by default those lines have to start with a `TAB` character to
be differentiated by make (and passed to the shell).  The *makefile syntax* is
used for all the other lines.

Equal signs:

- `:=` simply expand the defined variable (like C equal sign)
- `=` recursively expand the defined variable (the expression is expanded afterward, when
  the variable is used)

## Template

- **[1 Makefile for basic C project](#1-Makefile-for-basic-C-project)**
- **[2 Makefile for basic C project](#2-Makefile-for-basic-C-project)**
- **[3 Makefile for basic C project](#3-Makefile-for-basic-C-project)**

###     1 Makefile for basic C project.

The simplest Makefile, made for projects with the following structure:

```
before build:        after build:

\---Project:         \---Project:
      Makefile             Makefile
      main.c               main.c
                           main.o
                           icecream
```

Build a program called `icecream`:

```make
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
# all       build all targets
# $(NAME)   build $(NAME) target
# clean     remove objects
# fclean    remove objects and binary
# re        remove objects and binary and rebuild all

all: $(NAME)

$(NAME): $(OBJS)
    $(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
    $(RM) $(OBJS)

fclean: clean
    $(RM) $(NAME)

re: fclean all

#------------------------------------------------#
#   SPECIAL                                      #
#------------------------------------------------#

.PHONY: all clean fclean re run

####################################### END_1 ####
```

- The prerequisites of the `.PHONY:` special target become targets that make
  will run regardless of whether a file with that name exists.

- The C compilation is operated by the following *implicit rule*:

```make
%.o: %.c
    $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
```

Where `%.o` evaluates to each object, `%.c` to each source, `$<` to the first
prerequisite (which is `%.c`) and `$@` to the name of the target being generated
(which is `%.o`).

*As their name implies implicit rules are implicit and do not need to be
written.*

- Illustration of a `make all`:

```make
all: $(NAME)                            3 ← 2

$(NAME): $(OBJS)                        2 ← 1
  $(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c                                1 ← 0
  $(CC) $(CFLAGS) -c $< -o $@
  echo "CREATED $@"
```

The `all` rule requires `icecream` that requires `objects` that require
`sources` that require... a `programmer`.  In other words `all` creates `icecream`
with the `.o` created with the `.c` that you are supposed to create.

Make will first trace his path to the lower level where there is the raw
material `3 → 2 → 1 → 0` (`source files`) and then do it in the opposite
direction while building each resource that is required by the direct upper level
`0 → 1 → 2 → 3`.

###     2 Makefile for basic C project.

As above but for a project including *header files* with the addition of
`CPPFLAGS` dedicated to preprocessor's flags like `-I <include_dir>`.

Thus the project tree changes quite a bit:

```
before build:        after build:

\---Project:         \---Project:
      Makefile             Makefile
      main.c               main.c
      icecream.h           main.o
                           icecream.h
                           icecream
```

We add the following features:

- Basic rules informative message printing.
- The use of `.SILENT:` to prevent rules from printing their recipe before its
  execution.
- First custom rule that make and run our program with a simple `make run`.

```make
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
# all       build all targets
# $(NAME)   build $(NAME) target
# clean     remove objects
# fclean    remove objects and binary
# re        remove objects and binary and rebuild all

all: $(NAME)

$(NAME): $(OBJS)
    $(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)
    echo "CREATED $(NAME)"

%.o: %.c
    $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
    echo "CREATED $@"
```

- The implicit C compilation rule is overwritten with an explicit version that
  comes with an `echo` statement.

```make
clean:
    $(RM) $(OBJS)
    echo "REMOVED $(OBJS)"

fclean: clean
    $(RM) $(NAME)
    echo "REMOVED $(NAME)"

re: fclean all

#------------------------------------------------#
#   EXTRA RECIPES                                #
#------------------------------------------------#
# run           run the program

run: re
    -./$(NAME)
```

- The dash at the start of `-./$(NAME)` suppresses the errors of non-zero status
  code.  In effect, make is interrupted by any line that return a non-zero
  value.

```make
#------------------------------------------------#
#   SPECIAL                                      #
#------------------------------------------------#

.SILENT:
.PHONY: all clean fclean re run

####################################### END_2 ####
```

- Normally make prints each line of a rule's recipe before it is executed.  The
  special target `.SILENT:` silence the rules passed to it as prerequisites,
  when it is used without prerequisites it silents all the rules (implicit ones
  like C compilation included).

*To silence at the line level we can prefix the wanted recipes line with an `@`
symbol.*

###     3 Makefile for basic C project.

As above but a more complex project structure that uses dedicated directories
for their source `.c` and header `.h` files:

```
before build:        after build:

\---Project:         \---Project:
    | Makefile           | Makefile
    |                    | icecream
    |                    |
    +---include:         +---include:
    |     icecream.h     |     icecream.h
    |                    |
    \---src:             +---obj:
        | main.c         |   | main.o
        |                |   |
        +---arom:        |   +---arom:
        |     coco.c     |   |     coco.o
        |                |   |
        \---base:        |   \---base:
              milk.c     |         milk.o
              water.c    |         water.o
                         \---src:
                             | main.c
                             |
                             +---arom:
                             |     coco.c
                             |
                             \---base:
                                   milk.c
                                   water.c
```

- For this result we add basic automations that facilitate the scaling up to a
  larger project with the use of *substitution reference* to automatically
  generate the `obj` directory based on the `src` directory structure.

*This will work the same with every possible kind of src directory structure.*

- We add the useful custom rule `info` that prints each lines of the build
  recipe (without executing them).

```make
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
```

- By ending it with a `backslash` we can split the line to increase the
  visibility of `SRCS` content and facilitate its modification.

- A *substitution reference* substitutes the value of a variable with the
  specified alterations.  `$(SRCS:%=$(SRC_DIR)/%)` means that each item of
  `SRCS` represented by `%` becomes itself `%` plus the `$(SRC_DIR)/`
  alteration, so the item `main.c` would be turned into `src/main.c`.

```make
#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        cleaning command

RM          := rm -f

#------------------------------------------------#
#   RECIPES                                      #
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
    -[ ! -d $(@D) ] && mkdir -p $(@D)
    $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
    echo "CREATED $@"

clean:
    -[ -d $(OBJ_DIR) ] && $(RM) --recursive $(OBJ_DIR)
    echo "REMOVED $(OBJ_DIR)"

fclean: clean
    $(RM) $(NAME)
    echo "REMOVED $(NAME)"

re: fclean all
```

-  In the compilation rule `.o: %.c` becomes  `$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c`
   since our structure uses directories.

- The compilation rule uses `@D`, an *automatic variable* that expands to the
  directory part of the target file name, to create the `OBJ_DIR` structure:

```
-[ ! -d $(@D) ] && mkdir -p $(@D)
|| |  |    |    |  |      |    |
+|-|--|----|----|--|------|----|- suppress make non-zero status errors
 +-|--|----|----|--|------|----|- if
   +--|----|----|--|------|----|- doesn't exist
      +----|----|--|------|----|- as a directory
           +----|--|------|----|- the dir part of the target filename
                +--|------|----|- then
                   +------|----|- create the directory
                          +----|- and the parents directories if missing
                               +- of the dir part of the target filename
```

- In the `clean` rule we add `--recursive` to `RM` to remove `OBJ_DIR` and its content recursively.

```make
#------------------------------------------------#
#   EXTRA RECIPES                                #
#------------------------------------------------#
# run           run the program

info:
    make --dry-run --always-make --no-print-directory | grep -v "echo \| mkdir"

run: re
    -./$(NAME)
```

- The `info` rule will execute a simple `make` command with `--dry-run` to print
  the recipe without executing it, `--always-make` to `make` even if the targets
  already exist.  The `--no-print-directory` flag and `grep` command are used to
  clear up the output from unwanted lines.

```make
#------------------------------------------------#
#   SPECIAL                                      #
#------------------------------------------------#

.SILENT:
.PHONY: all clean fclean re run info

####################################### END_3 ####
```

## Sources

- **[docs.w3cub.com/make](https://docs.w3cub.com/gnu_make/)**
- **[gnu.org/make/manual](https://www.gnu.org/software/make/manual/html_node)**
- **[makefiletutorial.com](https://makefiletutorial.com/)**

## Todo

- C++
- Auto-Dependency Generation
- Portability (GNU/BSD, POSIX compliant)
- project that uses a librairy
- project that is a librairy
- Change GitHub page theme.
- Add [GH Page Buttons](https://buttons.github.io/)
