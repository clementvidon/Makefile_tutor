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
**a documented template** that evolves gradually, **version by version**.  With
the aim of making them more digestible and even tasty  🍔

**TL;DR** Confer to the bold text.

[**→ GitHub Page ←**](https://clemedon.github.io/Makefile_tutor/)<br>
[**→ GitHub Repo ←**](https://github.com/clemedon/Makefile_tutor/)

<hr>

***[ DONE ]***

- [GitHub Page](https://clemedon.github.io/Makefile_tutor/)
- A [ready to make](#usage) project of each template version
- [bold text](#usage) that acts as a summary
- [v1](#version-1) Simplest C project
- [v2](#version-2) Project that include headers
- [v3](#version-3) Project with any kind of directory structure
- [v4](#version-4) Static library
- [v5](#version-5) Project that uses libraries

***[ TODO ]***

- v6 Make C and C++
- Makefile generator
- BSD portability (POSIX)
- DOS portability

# Usage

This tutorial is designed to be read line by line **linearly at first**.

Then it can be quickly navigated thanks to the:

- **Brief** of each version which is visible from the [**Index**](#index).
- **Text in bold** that compile the essence of this tutorial.
- [**Return to Index ↑**](#index) buttons at the end of each version.

Each version of the template has an assigned directory in the
[**projects**](https://github.com/clemedon/Makefile_tutor/tree/main/projects)
directory of the repository, to play with a makefile open a terminal and run:

```bash
git clone git@github.com:clemedon/Makefile_tutor.git
cd Makefile_tutor/projects
```

```bash
cd <template_version>
make <target>
```

*PS1 **`C++` users** have to replace `CC = clang` with `CXX = g++` and `CFLAGS`
with `CXXFLAGS`.*

*PS2 do not hesitate to **fork me** so as to remove everything that does not
interest you and customize me according to your needs.*

# Glossary

Each **version** the template has **3 sections**:

- **Structure** is the project structure sketch.
- **Brief** is a summary made from the bold parts of the template comments.
- **Template** is a commented makefile template with comments (that are always
  placed at the end of the template part that concerns them).

Our **template** will be articulated around the following **parts**:

- `### BEG`         Mark the template **beginning**.
- `INGREDIENTS`     Build **variables**.
- `UTENSILS`        Shell **commands**.
- `RECIPES`         Build and extra **rules**.
- `SPEC`            **Special targets**.
- `#### END`        Mark the template **end**.

According to make a **`rule`** is made of:

- `targets` are the names of the **goals** we want to make. It can be a file or
  an action, the latter leading to a *pseudo target*.
- `prerequisites` are the goals that must be achieved so that the `rule` can
  execute.  Thus prerequisites are the **targets dependencies**.
- `recipe` is the set of lines that **begins with a `TAB`** character and appear
  in a rule context.

```make
target: prerequisite
    recipe line 1
    recipe line 2
    …
```

# Syntax

Like every makefile the template uses a combination of makefile syntax and shell
script syntax.  The **shell script syntax** is reserved and limited to recipe
lines, by default those lines have to **start with a `TAB`** character to be
differentiated by make (and passed to the shell).  The **makefile syntax** is
used for **all the other lines**.

About the **equal signs**:

- `:=` **simply expand** the defined variable (like C equal sign).
- `=` **recursively expand** the defined variable (the expression is expanded
  afterward, when (and each time) the variable is used).

```make
A := Did $(C)
B = Did $(C)

C  = you understand ?

all:
    $(info $(A)) # output "Did"
    $(info $(B)) # output "Did you understand ?"
```

**Automatic Variables** expansion:

- `$<` **leftmost prerequisite**
- `$@` **current target**
- `$^` **all prerequisites**
- `$(@D)` **directory part** of the file name of the target
- `$(@F)` **file part** of the file name of the target

*Cf. Version 1 / Automatic variables in practice.*

# Template

## Index

[**Version 1 / Simplest C project**](#version-1)

> - 42 C coding style conventions
> - `MAKE` predefined variable
> - The C compilation implicit rule
> - pattern rule contains `%` character
> - Automatic variables in practice
> - Illustration of a `make all`
> - C build recap
> - parallelization enabled by `make --jobs`
> - the `.PHONY:` special target

[**Version 2 / Project that include headers**](#version-2)

> - preprocessor's flags
> - print a custom message
> - C compilation implicit rule is overwritten
> - *default goal* `all` appears first
> - `.SILENT:` silences the rules output

[**Version 3 / Project with any kind of directory structure**](#version-3)

> - split the line with a `backslash`
> - substitution reference so `main.c` becomes `src/main.c`
> - generate the `OBJ_DIR` based on `SRC_DIR`
> - compilation rule uses multiple source and object directories

[**Version 4 / Static library**](#version-4)

> - when a header file is modified the executable will rebuild
> - automatically generate a list of dependencies
> - build directory
> - dependency files must be included
> - hyphen symbol to prevent make from complaining
> - creates a static library

[**Version 5 / Project that uses libraries**](#version-5)

> - system library linked by default
> - `addprefix` make function
> - flags and libraries used by the linker
> - `dir` function
> - Compiling with a library recap
> - builds each of the required libraries
> - call rules recursively

[**Bonus**](#bonus)

> - `make` and `run` the *default goal*
> - print `<target>` recipe without executing it
> - print the value of an arbitrary variable
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
- `MAKE` predefined variable
- The C compilation implicit rule
- pattern rule contains `%` character
- Automatic variables in practice
- Illustration of a `make all`
- C build recap
- parallelization enabled by `make --jobs`
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
    $(CC) $(OBJS) -o $(NAME)

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
  `all` and `re` as the basic rules as well as not using a wildcard to auto
  generate the sources list is guided by the **42 C coding style conventions**,
  do not hesitate to disagree and change it (like renaming `clean` and `fclean`
  to the more GNU conventional `mostlyclean` and `clean` respectively).

<sub><sub><hr></sub></sub>

- **`MAKE`** is a **predefined variable** whose value corresponds to the make
  executable being run, for this reason we choose to increment its options.
  When a makefile is executed from another makefile, the called's `MAKE`
  variable inherit from the caller's `MAKE` value.  We pass it the
  `--no-print-directory` flag for a cleaner output, try to remove it and run
  `make` to see the difference.

<sub><sub><hr></sub></sub>

- **The C compilation implicit rule** looks like this:

```make
%.o: %.c
    $(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
```

Where `%.o` expands to each objects, `%.c` to each sources, `$@` to the first
target (which is `%.o`) and `$<` to the leftmost prerequisite (which is `%.c`).

*As their name implies implicit rules are implicit and do not need to be
written.  All the implicit rules can be found in the data-base, accessible
with a `make -p -f/dev/null | less` shell command.*

<sub><sub><hr></sub></sub>

- A **pattern rule** is a rule whose target **contains** a **`%` character**
  (here `%.o: %.c`).  This character means "exactly one of them".  It is used
  here to say that each `.o` requires a `.c` with the same name and the `$(CC)…`
  recipe line will execute as many times as there are `.o: .c` pairs, thus
  creating for each source its corresponding object, one at a time.

<sub><sub><hr></sub></sub>

- **Automatic variables in practice**:

```make
# Linking step

$(NAME): $(OBJS)
    $(CC) $^ -o $@
```

`$@` expands to the *current target*, here we could have used `$(NAME)` instead.

`$^` expands to *all prerequisites*, here we could have used `$(OBJS)` instead
but not `$<` that expands to the *leftmost prerequisite* and so only the first
item found in `$(OBJS)`.

```make
# Compiling step

%.o: %.c
    $(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
```

`$<` expands to the *leftmost prerequisite*, here it could not have been
replaced with `$(SRCS)` because `$(SRCS)` expands to all the sources at once
which is not the case of the pattern rule `%.c`.  On the other hand here `$<` is
equivalent to `$^`, both will always expand to one source: the current one
expanded by `%.c`.  For the same reasons `$@` expands to `%.o` not to `$(OBJS)`.

<sub><sub><hr></sub></sub>

- **Illustration of a `make all`**:

```make
all: $(NAME)                            3 ← 2

$(NAME): $(OBJS)                        2 ← 1
    $(CC) $^ -o $@

%.o: %.c                                1 ← 0
    $(CC) $(CFLAGS) -c -o $@ $<
```

The `all` target requires `icecream` that requires the `objects` that require the
`sources` that requires…  a programmer.  In other words `all` creates `icecream`
with the objects created with the sources that you have created.

Make will first trace its path to the lower level where it finds a raw material
`3 → 2 → 1 → 0` (the `sources`) and then do it backward while building each
resource that is required by the direct upper level encountered `0 → 1 → 2 → 3`
(the `icecream`, our *final goal*).

<sub><sub><hr></sub></sub>

- **C build recap** `%.o` target requires the sources to be compiled into
  objects, the `-c` option tells the compiler to only compile without linking.
  The `-o` option is used to specify the objects name.  Afterward the `$(NAME)`
  target requires the linking the objects into a binary file whose name is
  specified with the `-o` flag.

<sub><sub><hr></sub></sub>

- For the `re` rule we have no choice but make an external call to our makefile
  because we should not rely on the order in which prerequisites are specified.
  For example `re: fclean all` wouldn't not be reliable if **parallelization**
  was **enabled by `make --jobs`**.

<sub><sub><hr></sub></sub>

- The prerequisites given to **the `.PHONY:` special target** become targets
  that make will run regardless of whether a file with that name exists.  In
  short these prerequisites are our targets that don't bear the name of a file.

Try to remove the `.PHONY: re`, create a file named `re` at the makefile level
in the project directory and run `make re`.  It won't work.

Now if you do the same with `all` it won't cause any problem, as we know
prerequisites are completed before their targets and `all` has the sole action
of invoking `$(NAME)`, as long as a rule doesn't have a recipe, `.PHONY` is not
necessary.

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
- print a custom message
- C compilation implicit rule is overwritten
- *default goal* `all` appears first
- `.SILENT:` silences the rules output

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
  its file name in the sources: `#include "icecream.h"` instead of `#include
  "../../path/to/include/icecream.h"`.

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
# $(NAME)   linking .o -> binary
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal

all: $(NAME)

$(NAME): $(OBJS)
    $(CC) $(OBJS) -o $(NAME)
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

- The `info` function is used here to **print a custom message** about what has
  just been built.

*We prefer `info` to shell `echo` because it is a make function.  Also unlike
`echo` that can only be used inside a recipe, `info` can be used anywhere in a
makefile which makes it powerful for debugging.*

<sub><sub><hr></sub></sub>

- The **C compilation implicit rule is overwritten** with an explicit equivalent
  which let us add an `info` statement to it.

<sub><sub><hr></sub></sub>

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
  special target **`.SILENT:` silences the rules output** specified as
  prerequisites, when it is used without prerequisites it silents all the rules
  (implicit included).

*To silence at the recipe-line level we can prefix the wanted recipe lines with an `@`
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

<sub><sub><hr></sub></sub>

- A string **substitution reference** substitutes the value of each item of a
  variable with the specified alterations.  `$(SRCS:%=$(SRC_DIR)/%)` means that
  each item of `SRCS` represented by `%` becomes itself (`%`) plus the
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
  `mkdir -p` which creates the directory and the parents directories if missing,
  and `$(@D)` that we have seen in [syntax](#syntax) section.

*This will work with every possible kind of src directory structure.*

```make
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
    $(CC) $(OBJS) -o $(NAME)
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

- The **compilation rule** `.o: %.c` becomes `$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c`
  since our structure **uses dedicated source and object directories**.

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

Builds a **library** so there are no `main.c`.  We generate **dependencies**
that are stored with the objects therefor we rename the `obj` directory into a
more general `.build` directory.

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
                           └── libicecream.a
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

NAME        := libicecream.a

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

- Unlike with sources, **when a header file is modified** make has no way of
  knowing this and will not consider **the executable** to be out of date, and
  therefor **will** not **rebuild** it.  In order to change this behavior we
  should add the appropriate header files as additional prerequisites:

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
  *substitution reference* to turn `.o` part of their name into `.d`.

<sub><sub><hr></sub></sub>

- We change our old `OBJ_DIR = obj` for a `BUILD_DIR = .build`, a hidden **build
  directory** that will contain our dependency files in addition to our objects.

<sub><sub><hr></sub></sub>

- A static library is not a binary but a collection of objects so we use `ar` to
  **creates a static library** during the linking step of the build.  `-r` to
  replace the older objects with the new ones with `-c` to create the library if
  it does not exist and `-s` to write an index into the archive or update an
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
# $(NAME)   link .o -> library
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal

all: $(NAME)

$(NAME): $(OBJS)
    $(AR) $(ARFLAGS) $(NAME) $(OBJS)
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
  `#include`, it tells make to suspend its current makefile reading and read the
  included files before continuing. Make sure to include the dependencies after
  they are created → after the compilation rule that invoke `-MMD` via
  `$(CPPFLAGS)`.

<sub><sub><hr></sub></sub>

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

Builds an `icecream` **program that uses** `libbase` and `libarom`
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

- system library linked by default
- `addprefix` make function
- flags and libraries used by the linker
- `dir` function
- Compiling with a library recap
- builds each of the required libraries
- call rules recursively

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

- We can notice that the `m` library from `LIBS` is not mentionned in
  `LIBS_TARGET` for the reason that `m` is a **system library** (`libm` for
  mathematical functions found in `math.h`).  Unlike the `libc` which is linked
  by default (we don't need to provide `-lc` flag to our linker) the `libm` is
  not **linked by default**.

<sub><sub><hr></sub></sub>

- In `CPPFLAGS` we use **`addprefix`** that, as its name suggests is a **make
  function** that allows you to add a prefix, here a `-I` to each of the item
  found in `$(INCS)` (that contains the paths to our project and libraries
  headers).

<sub><sub><hr></sub></sub>

- `LDFLAGS` and `LDLIBS` contains the **flags and libraries** that will be
  **used by the linker** `ld` to link the library to our project sources.

<sub><sub><hr></sub></sub>

- The **`dir` function** means that we want to keep only directory part of the
  given item, there exists a `notdir` function that does the opposite to keep
  only the file name of the given item.

<sub><sub><hr></sub></sub>

- **Compiling with a library recap**:

Compiling with a library requires, in addition to a C project and a library, a
`-I` flag that indicates to the compiler where to find the library header files,
`-L` indicate to the linker where to find the library and `-l` the name of this
library (conventionally: lib<name>).

For example: `-I lib/libarom/include -L lib/libarom -l arom`

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
# $(NAME)   link .o -> archive
# $(LIBS)   build libraries
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal
# run       run the program
# info      print the default goal recipe

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
    $(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
    $(info CREATED $(NAME))

$(LIBS_TARGET):
    $(MAKE) -C $(@D)

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

- `$(LIBS_TARGET)` rule **builds each of the required libraries** found in the
  `INGREDIENTS` part.  It is a `$(NAME)` prerequisite for the same reason as
  `$(OBJS)` because our *final goal* needs the libraries as well as the objects
  to be built.

<sub><sub><hr></sub></sub>

- As both rules `clean` and `fclean` appear in the makefile of all our
  `$(LIBS_TARGET)` we can **call** these **rules** for each of them
  **recursively** using a shell `for` loop.  Here again we use the `dir`
  function to only keep the directory part of the library.

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
info-%:
    $(MAKE) --dry-run --always-make $* | grep -v "info"
```

- `info-<target>` rule will execute a `make <target>` command with `--dry-run` to
  **print** the **`<target>` recipe without executing it**, `--always-make` to
  `make` even if the targets already exist and `grep -v` to filter the output.
  `$*` expands to the value given in place of the `%` at the rule call. For
  example with `make info-re` `$*` will expand to `re`.

```make
print-%:
    $(info '$*'='$($*)')
```

- The `print-<variable>` that works like `print-<rule>` will **print the value
  of an arbitrary variable**, for example a `make print-CC` will output
  `CC=clang`.

```make
.PHONY: update
update:
    git stash
    git pull
    git submodule update --init
    git stash pop
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
