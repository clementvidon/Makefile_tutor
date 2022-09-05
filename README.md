<h1 align="center">
	MAKEFILE TUTOR (GNU UNIX C)
</h1>

<h3 align="center">
	<a href="#summary">Summary</a>
	<span> · </span>
	<a href="#usage">Usage</a>
	<span> · </span>
	<a href="#glossary">Glossary</a>
	<span> · </span>
	<a href="#syntax">Syntax</a>
	<span> · </span>
	<a href="#index">Index</a>
	<span> · </span>
	<a href="#sources">Sources</a>
	<span> · </span>
	<a href="#contact">Contact</a>
</h3>

# Summary

Addressed to beginners and not to newcomers, the idea behind this tutorial is to
**focus on the essential**. The basics such as exhaustive syntax specifications
or anything not directly related to the template we are going to explore will
not be covered here.

Initially intended to help 42 students to step up their Makefile skills through
a **documented template** that evolves gradually, **step by step**. With the aim
of making them more digestible and even tasty 🍷

**TL;DR** Confer to the bold text.

[**→ GitHub Page ←**](https://clemedon.github.io/Makefile_tutor/)<br>
[**→ GitHub Repo ←**](https://github.com/clemedon/Makefile_tutor/)

<hr>

***[ DONE ]***

- [GitHub Page](https://clemedon.github.io/Makefile_tutor/).
- projects directory to [try](#usage) each template version.
- Bold text that compile the whole tutorial into a quick summary.
- v1 Minimal Makefile.
- v2 Include directory.
- v3 Multiple source directories.
- v3 Corresponding target directories for objects.
- v3 Creation of target directories when they don't exist.

***[ SOON ]***

- v4 Make a library.
- v4 Auto-dependency generation.
- v4 Dependency management (build only the necessary).
- v4 Build directory for objects and deps.
- v5 Make with a library.
- v5 Parallelization.
- v6 Make C and C++.
- v7 Bloated automations and scalability.
- BSD compatibility (and POSIX compliance).
- DOS compatibility.

***[ TODO ]***

- v5 Make with a library/framework.
- v7 Make C++.
- v8 Fully automated

# Usage

This tutorial is designed to be read line by line **linearly at first**.

Then it can be quickly navigated thanks to the:

- **Brief** of each version which is visible from the [**Index**](#index).
- **Text in bold** that compile **the essence** of this tutorial.
- [**Return to Index ↑**](#index) buttons at the end of each version.

Each version of the templates has an assigned directory in the
[**projects**](projects) directory of the repository, to play with a Makefile
open a terminal and run:

```bash
git clone git@github.com:clemedon/Makefile_tutor.git
cd Makefile_tutor && cd project
```

```bash
cd <template_version>
make <any_rule>
```

*The template versions are not meant to be copied and pasted but to understand their features so you can apply them to your own.*

# Glossary

Each **version** of our template has **3 sections**:

- **Structure** the project structure type.
- **Brief** compilation of the bold text from the template comments.
- **Template** our Makefile with comments (that are always placed at the end of
  the template part that concerns them).

Our **template** will be composed of the following parts:

- `### BEG`         Mark the template **beginning**.
- `INGREDIENTS`     Variables containing the **build ingredients**.
- `UTENSILS`        Variables containing **shell command tools**
- `RECIPES`         Basic set of **rules**.
- `EXTRA RECIPES`   **Custom rules**.
- `SPECIAL`         Make **special targets**.
- `#### END`        Mark the template **end**.

What we call a **`rule`** is made of:

- `targets`         Name of an **action or a file** we want to make.
- `prerequisites`   Files required (**targets dependencies**) for the `rule` to execute.
- `recipe`          Lines that **begins with a `TAB`** character, appear in a rule context.

```
target: prerequisite
    recipe line 1
    recipe line 2
    ...
```

# Syntax

Like every makefile our template use a combination of makefile syntax and shell
script syntax.  The **shell script syntax** is reserved and limited to recipe
lines, by default those lines have to **start with a `TAB`** character to be
differentiated by make (and passed to the shell).  The **makefile syntax** is
used for **all the other lines**.

**Equal** signs:

- `:=` **simply expand** the defined variable (like C equal sign).
- `=` **recursively expand** the defined variable (the expression is expanded afterward, when
  the variable is used).

```make
A  = You ${C}
B := You ${C}

C  = underestood.

all:
    echo ${A} # echoes "You"
    echo ${B} # echoes "You understood"
```

# Template

## Index

***The first part focuses on building a functional Makefile in 3 steps.***

[**Version 1**](#version-1)

> - the `.PHONY:` special target
> - The implicit C compilation
> - Illustration of a `make all`
> - 42 C coding style conventions

[**Version 2**](#version-2)

> - preprocessor's flags
> - output of a descriptive message
> - implicit C compilation rule is overwritten
> - the `hyphen` prevent make from complaining
> - `.SILENT:` silences the rules

[**Version 3**](#version-3)

> - split the line with a `backslash`
> - substitution reference so `main.c` becomes `src/main.c`
> - compilers rule uses multiple source and object directories
> - `@D` expands to the directory part of the target file name
> - `clean` rule `--recursive`
> - `info` rule print the `$(NAME)` recipe without executing it
> - automation substitution reference `@D` automatic variable

***The second part presents various useful Makefiles and more advanced features.***

[**Version 4**](#version-4)

TODO

##  Version 1

###     Structure

The simplest, build a program called `icecream` with the following structure:

```
before build:        after build:

\---Project:         \---Project:
      Makefile             Makefile
      main.c               main.c
                           main.o
                           icecream
```

###     Brief

- the `.PHONY:` special target
- The implicit C compilation
- Illustration of a `make all`
- 42 C coding style conventions

###     Template

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

RM          := rm --force

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# $(NAME)   default goal
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

re: fclean all

#------------------------------------------------#
#   SPECIAL                                      #
#------------------------------------------------#

.PHONY: clean fclean all re run
```

- The prerequisites given to **the `.PHONY:` special target** become targets
  that make will run regardless of whether a file with that name exists.  In
  short these prerequisites are our targets that don't bear the name of a file.

```make
####################################### END_1 ####
```

- **The implicit C compilation** is operated by the following *implicit rule*:

```make
%.o: %.c
    $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
```

Where `%.o` evaluates to each object, `%.c` to each source, `$<` to the first
prerequisite (which is `%.c`) and `$@` to the name of the target being generated
(which is `%.o`).

*As their name implies implicit rules are implicit and do not need to be
written.*

- **Illustration of a `make all`**:

```make
%.o: %.c                                1 ← 0
    $(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)                        2 ← 1
    $(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)                            3 ← 2
```

The `all` rule requires `icecream` that requires `objects` that require
`sources` that require... a programmer.  In other words `all` creates `icecream`
with the `.o` created with the `.c` that you are supposed to create.

Make will first trace its path to the lower level where it finds a raw material
`3 → 2 → 1 → 0` (`source files`) and then do it in the opposite direction while
building each resource that is required by the direct upper level `0 → 1 → 2 →
3` (`target`).

- The choice of the `CC` and `CFLAGS` values, as well as the `$(NAME)`, `clean`,
  `fclean`, `all` and `re` rules are based on **42 C coding style conventions**,
  don't hesitate to put those of your choice.

[**Return to Index ↑**](#index)

##  Version 2

###     Structure

As above but for a project that **includes header files**:

```
before build:        after build:

\---Project:         \---Project:
      Makefile             Makefile
      main.c               main.c
      icecream.h           main.o
                           icecream.h
                           icecream
```

###     Brief

- preprocessor's flags
- output of a descriptive message
- implicit C compilation rule is overwritten
- the `hyphen` prevent make from complaining
- `.SILENT:` silences the rules

###     Template

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
```

- `CPPFLAGS` is dedicated to **preprocessor's flags** like `-I <include_dir>`.

```make
#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        cleaning command

RM          := rm --force

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
```

- The **output of a descriptive message** is operated by the `echo` statements
  in the basic rules.

- The **implicit C compilation rule is overwritten** with an explicit version that
  comes with an `echo` statement.

```make
#------------------------------------------------#
#   EXTRA RECIPES                                #
#------------------------------------------------#
# run           run the program

run: re
    -./$(NAME)
```

- **The hyphen symbol** at the start of `-./$(NAME)` **prevent make from
  complaining** when a non-zero status code is encountered.  We use it here
  because we don't want make to stop its execution if our binary returns a
  non-zero value.

```make
#------------------------------------------------#
#   SPECIAL                                      #
#------------------------------------------------#

.SILENT:
.PHONY: clean fclean all re run
```

- Normally make prints each line of a rule's recipe before it is executed.  The
  special target **`.SILENT:` silences the rules** passed to it as prerequisites,
  when it is used without prerequisites it silents all the rules (implicit ones
  like C compilation included).

*To silence at the line level we can prefix the wanted recipes line with an `@`
symbol.*

```make
####################################### END_2 ####
```

[**Return to Index ↑**](#index)

##  Version 3

###     Structure

As above but a more complex project structure with **multiple source
directories** and their **corresponding object directories**:

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

###     Brief

- split the line with a `backslash`
- substitution reference so `main.c` becomes `src/main.c`
- compilers rule uses multiple source and object directories
- `@D` expands to the directory part of the target file name
- `clean` rule `--recursive`
- `info` rule print the `$(NAME)` recipe without executing it
- automation substitution reference `@D` automatic variable

###     Template

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

- We can **split the line** by ending it **with a `backslash`** to increase the
  readability of `SRCS` content and facilitate its modification.

- A **substitution reference** substitutes the value of a variable with the
  specified alterations.  `$(SRCS:%=$(SRC_DIR)/%)` means that each item of
  `SRCS` represented by `%` becomes itself `%` plus the `$(SRC_DIR)/`
  alteration, so `main.c` becomes `src/main.c`. `OBJS` will then use the same
  process to convert `src/main.c` into `src/main.o`, dedicated to the `OBJ_DIR`.

```make
#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        cleaning command

RM          := rm --force

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
```

-  The **compilation rule** `.o: %.c` becomes `$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c`
   since our structure **uses multiple source and object directories**.

- **`@D`** is an *automatic variable* that **expands to the directory part of the
  target file name**, to create the `OBJ_DIR` structure:

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

- In the **`clean` rule** we add **`--recursive`** to `RM` to remove `OBJ_DIR` and its content recursively.

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

- The **`info` rule** will execute a simple `make` command with `--dry-run` to
  **print the `$(NAME)` recipe without executing it**, `--always-make` to `make`
  even if the targets already exist and `--no-print-directory` flag and `grep`
  command to clean the output from unwanted lines.

```make
#------------------------------------------------#
#   SPECIAL                                      #
#------------------------------------------------#

.SILENT:
.PHONY: clean fclean all re run info

####################################### END_3 ####
```

- The basic **automation** provided by the **substitution reference** and the
  **`@D` automatic variable** enable the scaling up to a larger project and the
  generation of the `obj` directory based on the `src` directory structure.

*This will work the same with every possible kind of src directory structure.*

[**Return to Index ↑**](#index)

##  Version 4

###     Structure

As above but without `main.c` and a the **`.build`** directory which replaces
the `obj` folder and which will contain, in addition to objects, the
**dependencies**.

```
before build:        after build:

\---Project:         \---Project:
    | Makefile           | Makefile
    |                    | icecream.a
    |                    |
    +---include:         +---include:
    |     icecream.h     |     icecream.h
    |                    |
    \---src:             +---obj:
        |                |   |
        +---arom:        |   +---arom:
        |     coco.c     |   |     coco.o
        |                |   |     coco.d
        \---base:        |   |
              milk.c     |   \---base:
              water.c    |         milk.o
                         |         milk.d
                         |         water.o
                         |         water.d
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

###     Brief

TODO

###     Template

TODO

```make
    ####################################### BEG_4 ####

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
    # NODEPS    files without dependency

    CC          := clang
    CFLAGS      := -Wall -Wextra -Werror -c
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
```

TODO About libs
TODO About deps

```make
    #------------------------------------------------#
    #   UTENSILS                                     #
    #------------------------------------------------#
    # RM        cleaning command

    RM          := rm --force

    #------------------------------------------------#
    #   RECIPES                                      #
    #------------------------------------------------#
    # %.o       compilation
    # $(NAME)   default goal
    # clean     remove objects
    # fclean    clean + remove binary
    # all       all targets
    # re        fclean + all

    $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
    	-[ ! -d $(@D) ] && mkdir -p $(@D)
    	@$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@
    	echo "CREATED $@"

    $(NAME): $(OBJS)
    	@ar rcs $(NAME) $(OBJS)
    	echo "CREATED $(NAME)"

    clean:
    	-[ -d $(BUILD_DIR) ] && $(RM) --recursive $(BUILD_DIR)

    fclean: clean
    	$(RM) $(NAME)

    all: $(NAME)

    re: fclean all
```

TODO About libs

```make
#------------------------------------------------#
#   SPECIAL                                      #
#------------------------------------------------#

.SILENT:
.PHONY: clean fclean all re

    ####################################### END_4 ####
```

TODO About deps

# Sources

- [**gnu.org/make/manual**](https://www.gnu.org/software/make/manual/html_node)
- [**docs.w3cub.com/make**](https://docs.w3cub.com/gnu_make/)
- [**makefiletutorial.com**](https://makefiletutorial.com/)
- [**well worth a look**](https://stackoverflow.com/a/68584653)

# Contact

```
clemedon icloud
```

<sub><i>Copyright 2022 Clément Vidon. All Rights Reserved.</i></sub>
