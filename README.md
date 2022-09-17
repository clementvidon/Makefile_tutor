<h1 align="center">
    MAKEFILE TUTOR (GNU UNIX)
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
**focus on the essential**.  Anything that is not directly related to the
template we are going to explore will not be covered here.  On the other hand
everything that is covered in this tutorial will be carefully detailed.

Initially intended to help 42 students to step up their makefile skills through
a **documented template** that evolves gradually, **step by step**.  With the aim
of making them more digestible and even tasty  🍔

**TL;DR** Confer to the bold text.

[**→ GitHub Page ←**](https://clemedon.github.io/Makefile_tutor/)<br>
[**→ GitHub Repo ←**](https://github.com/clemedon/Makefile_tutor/)

<hr>

***[ DONE ]***

- [GitHub Page](https://clemedon.github.io/Makefile_tutor/).
- projects directory to [try](#usage) each template version.
- Bold text that compile the whole tutorial into a quick summary.
- v1 Minimal makefile.
- v2 Include directory.
- v3 Multiple source directories.
- v3 Corresponding target directories for objects.
- v3 Creation of target directories when they don't exist.
- v4 Make a library.
- v4 Auto-dependency generation.
- v4 Dependency management (build only the necessary).
- v4 Build directory for objects and deps.

***[ SOON ]***

- v5 Make with library.
- v5 Fully automated and auto scalability.
- v5 String functions.

***[ TODO ]***

- v6 Make C and C++.
- Makefile generator.
- BSD compatibility (and POSIX compliance).
- DOS compatibility.

# Usage

This tutorial is designed to be read line by line **linearly at first**.

Then it can be quickly navigated thanks to the:

- **Brief** of each version which is visible from the [**Index**](#index).
- **Text in bold** that compile **the essence** of this tutorial.
- [**Return to Index ↑**](#index) buttons at the end of each version.

Each version of the templates has an assigned directory in the
[**projects**](https://github.com/clemedon/Makefile_tutor/tree/main/projects) directory of the repository, to play with a makefile
open a terminal and run:

```bash
git clone git@github.com:clemedon/Makefile_tutor.git
cd Makefile_tutor && cd project
```

```bash
cd <template_version>
make <any_rule>
```

PS **`C++` users** can replace `CC = clang` with `CXX = g++` and `CFLAGS` with
`CXXFLAGS`.

# Glossary

Each **version** of our template has **3 sections**:

- **Structure** The **project structure** type.
- **Brief** Compilation of the **bold text** from the template comments.
- **Template** Our makefile **with comments** (that are always placed at the end
  of the template part that concerns them).

Our **template** will be articulated around the following parts:

- `### BEG`         Mark the **template beginning**.
- `INGREDIENTS`     **Build variables**.
- `UTENSILS`        **Shell commands**.
- `RECIPES`         **Build and extra rules**.
- `SPEC`            **Special targets and specifications**.
- `#### END`        Mark the template **end**.

What we call a **`rule`** is made of:

- `targets`         Name of a **goal** (action or a file) we want to make.
- `prerequisites`   Files required (**targets dependencies**) for the `rule` to execute.
- `recipe`          Lines that **begins with a `TAB`** character, appear in a rule context.

```
target: prerequisite
    recipe line 1
    recipe line 2
    ...
```

# Syntax

Like every makefile our template uses a combination of makefile syntax and shell
script syntax.  The **shell script syntax** is reserved and limited to recipe
lines, by default those lines have to **start with a `TAB`** character to be
differentiated by make (and passed to the shell).  The **makefile syntax** is
used for **all the other lines**.

**Equal** signs:

- `:=` **simply expand** the defined variable (like C equal sign).
- `=` **recursively expand** the defined variable (the expression is expanded afterward, when
  the variable is used).

```make
A := Yes $(C)
B = Yes $(C)

C  = you got it

all:
    $(info $(A)) # output "Yes"
    $(info $(B)) # output "Yes you got it"
```

**Automatic Variables** expansion:

- `$<` **leftmost prerequisite**
- `$@` **current target**
- `$^` **all prerequisites**
- `$(@D)` **directory part** of the file name of the target
- `$(@F)` **file part** of the file name of the target

# Template

## Index

***The first part focuses on building a functional makefile in 3 steps.***

[**Version 1 / base**](#version-1)

> - 42 C coding style conventions
> - `MAKE` predifined variable
> - The C compilation implicit rule
> - Illustration of a `make all`
> - C build recap
> - multi-threaded `make` with `--jobs`
> - the `.PHONY:` special target

[**Version 2 / simple**](#version-2)

> - preprocessor's flags
> - output of a descriptive message
> - C compilation implicit rule is overwritten
> - rules are written in their order of execution
> - `.SILENT:` silences the rules

[**Version 3 / structured**](#version-3)

> - split the line with a `backslash`
> - substitution reference so `main.c` becomes `src/main.c`
> - generate the `OBJ_DIR` based on `SRC_DIR`
> - compilation rule uses multiple source and object directories
> - `clean` rule `--recursive`

***The second part presents various useful makefiles and more advanced features.***

[**Version 4 / for library**](#version-4)

> - when a header file is modified the executable will rebuild
> - automatically generate a list of dependencies
> - build directory
> - dependency files must be included
> - hyphen symbol to prevent make from complaining
> - creates a static library

[**Version 5 / with libraries**](#version-5)

  ***SOON***

[**Bonus**](#bonus)

> - `make` and `run` the *default goal*
> - print `$(NAME)` recipe without executing it
> - prints the value of an arbitrary variable
> - update the git repository

##  Version 1

###     v1 Structure

The simplest, build a program called `icecream` with the following structure:

```
    before build:    after build:
    .                .
    ├── Makefile     ├── Makefile
    └── main.c       ├── main.o
                     ├── main.c
                     └── icecream
```

###     v1 Brief

- 42 C coding style conventions
- `MAKE` predifined variable
- The C compilation implicit rule
- Illustration of a `make all`
- C build recap
- multi-threaded `make` with `--jobs`
- the `.PHONY:` special target

###     v1 Template

```make
####################################### BEG_1 ####

NAME        := icecream

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# SRCS      source files
# OBJS      object files
#
# CC        compiler
# CFLAGS    compiler flags

SRCS        := main.c
OBJS        := main.o

CC          := clang
CFLAGS      := -Wall -Wextra -Werror

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove

RM          := rm -f
MAKE        := $(MAKE) --no-print-directory

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# $(NAME)   linking .o -> binary
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal

all: $(NAME)

$(NAME): $(OBJS)
    $(CC) $^ -o $@

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

####################################### END_1 ####
```

- The choice of the `CC` and `CFLAGS` values, `$(NAME)`, `clean`, `fclean`,
  `all` and `re` as the basic rules as well as not using a wildcard to
  auto-detect source files are specific to the **42 C coding style
  conventions**, do not hesitate to disagree and change it (like renaming
  `clean` and `fclean` to the more GNU conventional `mostlyclean` and `clean`
  respectively).

- **`MAKE`** is a **predefined variable** whose value corresponds to the make
  executable being run, for this reason we pass our options to it by
  incrementation.  When a makefile is executed from another makefile, the
  called's `MAKE` variable inherit from the caller's `MAKE` value.  We pass it
  the `--no-print-directory` flag for a cleaner output, remove it to see the
  difference.

- **The C compilation implicit rule** looks like this:

```make
%.o: %.c
    $(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
```

Where `%.o` evaluates to each object, `%.c` to each source, `$@` to the first
target (which is `%.o`) and `$<` to the leftmost prerequisite (which is `%.c`).
Note that `$@` can be replaced by `$(OBJS)` and `$<` by `$(SRCS)`.

*As their name implies implicit rules are implicit and do not need to be
written.  All the implicit rules can be found in the data-base, accessible
with a `make -p -f/dev/null | less` shell command.*

- **Illustration of a `make all`**:

```make
all: $(NAME)                            3 ← 2

$(NAME): $(OBJS)                        2 ← 1
    $(CC) $^ -o $@

%.o: %.c                                1 ← 0
    $(CC) $(CFLAGS) -c -o $@ $<
```

The `all` rule requires `icecream` that requires `objects` that require
`sources` that require...  a programmer.  In other words `all` creates `icecream`
with the `.o` created with the `.c` that you are supposed to create.

Make will first trace its path to the lower level where it finds a raw material
`3 → 2 → 1 → 0` (`source files`) and then do it in the opposite direction while
building each resource that is required by the direct upper level `0 → 1 → 2 →
3` (`target`).

- **C build recap** `%.o` target compile the `.c` into `.o`, the `-c`
  tells to compile the `.c` without linking the `.o` and the `-o` indicate how
  to name the `.o` resulting from the `.c`.  Afterward the `$(NAME)` is in
  charge of linking the `.o` into a binary `$(NAME)` file whose name is
  specified with the `-o` flag.

- For the `re` command we have no choice but make an external call to our
  makefile because we should not rely on the order in which prerequisites are
  specified.  For example `re: fclean all` wouldn't work with a **multi-threaded
  `make` with `--jobs`** option.

- The prerequisites given to **the `.PHONY:` special target** become targets
  that make will run regardless of whether a file with that name exists.  In
  short these prerequisites are our targets that don't bear the name of a file.

  Try to remove the `.PHONY: re`, create a file named `re` in your project
  directory and run `make re`.  It won't work.

  Now if you do the same with `all` it won't cause any problem, as we know
  prerequisites are completed before their target and `all` has the sole action
  of invoking `$(NAME)`, as long as a rule doesn't have a recipe, `.PHONY` is
  not necessary.

[**Return to Index ↑**](#index)

##  Version 2

###     v2 Structure

As above but for a project that **includes header files**:

```
    before build:     after build:
    .                 .
    ├── Makefile      ├── Makefile
    ├── main.c        ├── main.o
    └── icecream.h    ├── main.c
                      ├── icecream.h
                      └── icecream
```

###     v2 Brief

- preprocessor's flags
- output of a descriptive message
- C compilation implicit rule is overwritten
- *default goal* `all` appears first
- `.SILENT:` silences the rules

###     v2 Template

```make
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
```

- `CPPFLAGS` is dedicated to **preprocessor's flags** like `-I <include_dir>`,
  it allows you to no longer have to write the full path of a header but only
  its file name in the source files: `#include "icecream.h"`.

```make
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
# %.o       compilation .c -> .o
# $(NAME)   linking .o -> binary
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal

all: $(NAME)

$(NAME): $(OBJS)
    $(CC) $^ -o $@
    $(info CREATED $(NAME))

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
```

- The use of the `info` function to **output of a descriptive message** in the
  basic rules.

- The **C compilation implicit rule is overwritten** with an explicit version in
  which we can add an `info` statement.

- The order in which the rules are written does not matter as long as our
  **default goal `all` appears first** (the rule that will be triggered by a
  simple `make` command).

```make
#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: clean fclean re
.SILENT:
```

- Normally make prints each line of a rule's recipe before it is executed.  The
  special target **`.SILENT:` silences the rules** specified as prerequisites,
  when it is used without prerequisites it silents all the rules (implicit ones
  like C compilation included).

*To silence at the line level we can prefix the wanted recipe lines with an `@`
symbol.*

```make
####################################### END_2 ####
```

[**Return to Index ↑**](#index)

##  Version 3

###     v3 Structure

As above but a more complex project structure with **multiple source
directories** and their **corresponding object directories**:

```
    before build:          after build:
    .                      .
    ├── src                ├── src
    │   ├── base           │   ├── base
    │   │   ├── water.c    │   │   ├── water.c
    │   │   └── milk.c     │   │   └── milk.c
    │   ├── arom           │   ├── arom
    │   │   └── coco.c     │   │   └── coco.c
    │   └── main.c         │   └── main.c
    ├── include            ├── obj
    │   └── icecream.h     │   ├── base
    └── Makefile           │   │   ├── water.o
                           │   │   └── milk.o
                           │   ├── arom
                           │   │   └── coco.o
                           │   └── main.o
                           ├── include
                           │   └── icecream.h
                           ├── Makefile
                           └── icecream
```

###     v3 Brief

- split the line with a `backslash`
- substitution reference so `main.c` becomes `src/main.c`
- generate the `OBJ_DIR` based on `SRC_DIR`
- compilation rule uses multiple source and object directories
- `clean` rule `--recursive`

###     v3 Template

```make
####################################### BEG_3 ####

NAME        := icecream

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# SRC_DIR   source directory
# OBJ_DIR   object directory
# SRCS      source files
# OBJS      object files
#
# CC        compiler
# CFLAGS    compiler flags
# CPPFLAGS  preprocessor flags

SRC_DIR     := src
OBJ_DIR     := obj
SRCS        := \
    main.c          \
    arom/coco.c     \
    base/milk.c     \
    base/water.c
SRCS        := $(SRCS:%=$(SRC_DIR)/%)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC          := clang
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -I include
```

- We can **split the line** by ending it **with a `backslash`** to increase the
  readability of `SRCS` content and facilitate its modification.

- A string **substitution reference** substitutes the value of each item of a
  variable with the specified alterations.  `$(SRCS:%=$(SRC_DIR)/%)` means that
  each item of `SRCS` represented by `%` becomes itself `%` plus the
  `$(SRC_DIR)/` alteration, so `main.c` becomes `src/main.c`. `OBJS` will then
  use the same process to convert `src/main.c` into `src/main.o`, dedicated to
  the `OBJ_DIR`.

```make
#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove
# MAKE      quietly make
# DIR_DUP   duplicate directory tree

RM          := rm -f
MAKE        := $(MAKE) --no-print-directory
DIR_DUP     = mkdir -p $(@D)
```

- `DIR_DUP` will **generate the `OBJ_DIR` based on `SRC_DIR`** structure with
  `mkdir -p` that create the directory and the parents directories if missing,
  and `$(@D)` automatic variable that we have already seen.

*This will work with every possible kind of src directory structure.*

```make
#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# %.o       compilation .c -> .o
# $(NAME)   linking .o -> binary
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal

all: $(NAME)

$(NAME): $(OBJS)
    $(CC) $^ -o $@
    $(info CREATED $(NAME))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
    $(DIR_DUP)
    $(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
    $(info CREATED $@)

clean:
    $(RM) $(OBJS)

fclean: clean
    $(RM) $(NAME)

re:
    $(MAKE) fclean
    $(MAKE) all
```

-  The **compilation rule** `.o: %.c` becomes `$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c`
   since our structure **uses multiple source and object directories**.

- In the **`clean` rule** we add **`--recursive`** to `RM` to remove `OBJ_DIR` and its content recursively.

```make
#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: clean fclean re
.SILENT:

####################################### END_3 ####
```

[**Return to Index ↑**](#index)

##  Version 4

###     v4 Structure

Builds a **library** so we remove `main.c`.  We generate **dependencies** that
are stored with the object files thus we rename `obj` directory into `.build`.

```
    before build:          after build:
    .                      .
    ├── src                ├── src
    │   ├── base           │   ├── base
    │   │   ├── water.c    │   │   ├── water.c
    │   │   └── milk.c     │   │   └── milk.c
    │   └── arom           │   └── arom
    │       └── coco.c     │       └── coco.c
    ├── include            ├── include
    │   └── icecream.h     │   └── icecream.h
    └── Makefile           ├── .build
                           │   ├── base
                           │   │   ├── water.o
                           │   │   ├── water.d
                           │   │   ├── milk.o
                           │   │   └── milk.d
                           │   └── arom
                           │       ├── coco.o
                           │       └── coco.d
                           ├── Makefile
                           └── icecream.a
```

###     v4 Brief

- when a header file is modified the executable will rebuild
- automatically generate a list of dependencies
- build directory
- dependency files must be included
- hyphen symbol to prevent make from complaining
- creates a static library

###     v4 Template

```make
####################################### BEG_4 ####

NAME        := icecream.a

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# SRC_DIR   source directory
# SRCS      source files
#
# BUILD_DIR object directory
# OBJS      object files
# DEPS      dependency files
#
# CC        compiler
# CFLAGS    compiler flags
# CPPFLAGS  preprocessor flags

SRC_DIR     := src
SRCS        :=  \
    arom/coco.c \
    base/milk.c \
    base/water.c
SRCS        := $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR   := .build
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

CC          := clang
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -MMD -MP -I include
AR          := ar
ARFLAGS     := -r -c -s
```

- Unlike source files, **when a header file is modified** make has no way of
  knowing this and will not consider **the executable** to be out of date, and
  therefor **will** not **rebuild** it.  In order to change this behavior we
  should add the appropriate header files as an additional prerequisites:

```make
#before                     #after
main.o: main.c              main.o: main.c icecream.h
    clang -c $< -o $@           clang -c $< -o $@
```

- Doing this manually for multiple sources and headers is both tedious and error
  prone.  By adding `-MMD` to `CPPFLAGS` our compiler will **automatically
  generate a list of dependencies** for each object file encountered during the
  compilation.  The `-MP` option prevents errors that are triggered if a header
  file has been deleted or renamed.

  Dependency files must be included into our makefile right after the objects
  creation so to obtain their names we copy `OBJS` into `DEPS` and use
  *substitution reference* to turn `.o` part into `.d`.

- We change our old `OBJ_DIR = obj` for a `BUILD_DIR = .build`, a hidden **build
  directory** that will contain our object files as well as our dependency
  files.

- A library is not a binary but a collection of object files so we use `ar`
  to **creates a static library** during the linking step of the build. `-r` to
  replace the older object files with the new ones; `-c` to create the library
  if it does not exist and `-s` to write an index into the archive or update an
  existing one.

```make
#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove
# MAKE      quietly make
# DIR_DUP   duplicate directory tree

RM          := rm -f
MAKE        := $(MAKE) --no-print-directory
DIR_DUP     = mkdir -p $(@D)

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# %.o       compilation .c -> .o
# $(NAME)   link .o -> library
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal

all: $(NAME)

$(NAME): $(OBJS)
    $(AR) $(ARFLAGS) $@ $<
    $(info CREATED $(NAME))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
    $(DIR_DUP)
    $(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
    $(info CREATED $@)

-include $(DEPS)

clean:
    $(RM) $(OBJS) $(DEPS)

fclean: clean
    $(RM) $(NAME)

re:
    $(MAKE) fclean
    $(MAKE) all
```

- **Dependency files** are written in the make language and **must be included**
  into our makefile to be read.  The `include` directive work the same as C
  include, it tells make to suspend the current makefile reading and read the
  included files before continuing. Make sure to include the dependencies after
  they are created = after the compilation rule.

- The purpose of the `-include $(DEPS)` initial **hyphen symbol** is **to
  prevent make from complaining** when a non-zero status code is encountered,
  which can be caused here by a missing files from our generated dependency
  files list.

```make
#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: clean fclean re
.SILENT:

####################################### END_4 ####
```

[**Return to Index ↑**](#index)

##  Version 5

###     v5 Structure

Builds a an `icecream` **program that uses** a `libbase` and `libarom`
**libraries**.  Both libraries are v4 based.

```
    before build:              after build:
    .                          .
    ├── src                    ├── src
    │   └── main.c             │   └── main.c
    ├── lib                    ├── lib
    │   ├── libbase            │   ├── libbase
    │   │   ├── src            │   │   ├── src
    │   │   │   ├── water.c    │   │   │   ├── water.c
    │   │   │   └── milk.c     │   │   │   └── milk.c
    │   │   ├── include        │   │   ├── include
    │   │   │   └── base.h     │   │   │   └── base.h
    │   │   └── Makefile       │   │   ├── .build
    │   └── libarom            │   │   │   ├── water.o
    │       ├── src            │   │   │   ├── water.d
    │       │   ├── coco.c     │   │   │   ├── milk.o
    │       │   └── cherry.c   │   │   │   └── milk.d
    │       ├── include        │   │   ├── Makefile
    │       │   └── arom.h     │   │   └── libbase.a
    │       └── Makefile       │   └── libarom
    ├── include                │       ├── src
    │   └── icecream.h         │       │   ├── coco.c
    └── Makefile               │       │   └── cherry.c
                               │       ├── include
                               │       │   └── arom.h
                               │       ├── .build
                               │       │   ├── coco.o
                               │       │   ├── coco.d
                               │       │   ├── cherry.o
                               │       │   └── cherry.d
                               │       ├── Makefile
                               │       └── libarom.a
                               ├── include
                               │   └── icecream.h
                               ├── .build
                               │   ├── main.o
                               │   └── main.d
                               ├── Makefile
                               └── icecream
```

###     v5 Brief

  ***SOON***

###     v5 Template

```make
# @author   clemedon (Clément Vidon)
####################################### BEG_5 ####

NAME        := icecream

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# LIBS        libraries to be used
# LIBS_TARGET libraries to be built
#
# INCS        header file locations
#
# SRC_DIR     source directory
# SRCS        source files
#
# BUILD_DIR   build directory
# OBJS        object files
# DEPS        dependency files
#
# CC          compiler
# CFLAGS      compiler flags
# CPPFLAGS    preprocessor flags
# LDFLAGS     linker flags
# LDLIBS      libraries name

LIBS        := arom base m
LIBS_TARGET :=            \
    lib/libarom/libarom.a \
    lib/libbase/libbase.a

INCS        := include    \
    lib/libarom/include   \
    lib/libbase/include

SRC_DIR     := src
SRCS        := main.c
SRCS        := $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR   := .build
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

CC          := clang
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS     := $(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS      := $(addprefix -l,$(LIBS))
```

  ***SOON***

```make
#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove
# MAKE      quietly make
# DIR_DUP   duplicate directory tree

RM          := rm -f
MAKE        := $(MAKE) --silent --no-print-directory
DIR_DUP     = mkdir -p $(@D)

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# %.o       compilation .c -> .o
# $(NAME)   link .o -> archive
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal
# run       run the program
# info      print the default goal recipe

all: $(NAME)

$(LIBS_TARGET):
    $(MAKE) -C $(@D)

$(NAME): $(OBJS) $(LIBS_TARGET)
    $(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
    $(info CREATED $(NAME))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
    $(DIR_DUP)
    $(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
    $(info CREATED $@)

-include $(DEPS)

clean:
    for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
    $(RM) $(OBJS) $(DEPS)

fclean: clean
    for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done
    $(RM) $(NAME)

re:
    $(MAKE) fclean
    $(MAKE) all
```

  ***SOON***

```make
#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: clean fclean re
.SILENT:

####################################### end_5 ####
```

[**Return to Index ↑**](#index)

##  Bonus

###     Extra rules

```make
.PHONY: run
run: re
    -./$(NAME)
```

- `run` is a simple rule that **`make` and `run` the default goal**.  We start
  the shell command with the `hyphen` symbol to prevent make from interrupting
  its execution if our program execution returns a non-zero value.

```make
.PHONY: info
info:
    $(MAKE) --dry-run --always-make | grep -v "info"
```

- The `info` rule will execute a simple `make` command with `--dry-run` to
  **print** the **`$(NAME)` recipe without executing it**, `--always-make` to `make`
  even if the targets already exist and filter the output with `grep`.

```make
.PHONY: FORCE
print-%: FORCE
    $(info '$*'='$($*)')
```

- The `print-<variable>` rule **prints the value of an arbitrary variable**, for
  example a `make print-CC` will output `CC=clang`.

```make
update:
    git stash
    git pull
    git submodule update --init
    git stash pop
.PHONY: update
```

- The `update` rule will **update the git repository** to its last version, as
  well as its *git submodules*. `stash` commands saves eventual uncommitted
  changes and put them back in place once the update is done.

# Sources

- [**doc / w3cub**](https://docs.w3cub.com/gnu_make/)
- [**manual / gnu**](https://www.gnu.org/software/make/manual/html_node)
- [**a richer tutorial / makefiletutorial**](https://makefiletutorial.com/)
- [**order-only exquisite / stackoverflow**](https://stackoverflow.com/a/68584653)
- [**c libraries / docencia**](https://docencia.ac.upc.edu/FIB/USO/Bibliografia/unix-c-libraries.html#creating_static_archive)
- [**auto-deps gen / mad-scientist**](http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/)
- [**auto-deps gen / scottmcpeak**](https://scottmcpeak.com/autodepend/autodepend.html)
- [**auto-deps gen / microhowto**](http://www.microhowto.info/howto/automatically_generate_makefile_dependencies.html)
- [**include statement / gnu**](https://www.gnu.org/software/make/manual/html_node/Include.html)
- [**redis makefiel / github**](https://github.com/redis/redis/blob/unstable/src/Makefile)

# Contact

```
cvidon   42
clemedon icloud
```

<sub><i>Copyright 2022 Clément Vidon.  All Rights Reserved.</i></sub>
