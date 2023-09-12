#============================================================================
# Mini Spin-X Library
#
# Copyright (c) 2022, Jarkko Lempiainen
# All rights reserved.
#----------------------------------------------------------------------------
#
# make options:
#   build=<build>       - options: debug (default), release, retail
#   platform=<platform> - options: linux32, linux64 (default), win32, win64
# make targets:
#   libs                - compile all engine libraries (default)
#   clean               - delete libraries and object files for the target
#   <library name>      - compile given engine library, e.g. core
#
# examples:
# to compile linux64 release build of all libraries:
#   make build=release libs
#
# to compile win64 release build of core and core_engine libraries:
#   make build=release platform=win64 core core_engine
#
# to clean all linux64 release build files:
#   make build=release clean
#
# to clean and rebuild linux64 debug engine libraries
#   make clean exes


# build settings
ifndef build
build=debug
endif
$(if $(filter $(build),debug release retail),,$(error unknown target build "$(build)"))
ifeq "$(build)" "debug"
CFLAGS=-ggdb
CDEFS=-D PFC_DEBUG
else ifeq "$(build)" "release"
CFLAGS=-O2 -fno-strict-aliasing
CDEFS=-D PFC_RELEASE
else ifeq "$(build)" "retail"
CFLAGS=-O3 -fno-strict-aliasing
CDEFS=-D PFC_RETAIL
endif

# platform settings
ifndef platform
platform=linux64
endif
$(if $(filter $(platform),linux32 linux64 win32 win64),,$(error unknown target platform "$(platform)"))
ifeq "$(platform)" "linux32"
CFLAGS+=-m32
CDEFS+=-D PFC_PLATFORM_LINUX32
else ifeq "$(platform)" "linux64"
CFLAGS+=-m64 -mcx16
CDEFS+=-D PFC_PLATFORM_LINUX64
else ifeq "$(platform)" "win32"
CFLAGS+=-m32
CDEFS+=-D PFC_PLATFORM_WIN32
else ifeq "$(platform)" "win64"
CFLAGS+=-m64
CDEFS+=-D PFC_PLATFORM_WIN64
endif

# generic settings
.DEFAULT_GOAL:=libs
MD=mkdir -p $(1)
RD=rm -r -f $(1)
RM=rm -f $(1)
EXEDIR=../../bin
INTDIR_ROOT=../../_intermediate
INTDIR=$(INTDIR_ROOT)/$(platform)_gcc/$(build)
LIBDIR=../../lib/$(platform)_gcc
EXTLIBDIR=../../sxp_extlibs/libs/$(platform)_gcc
SRCDIR=../../sxp_src
EXTLIBS=
# EXTLIBS=nvtexturetools libtiff libwebp openjpeg jpeglib libpng zlib
CLIBS=
# CLIBS=-lgdi32 -lcomdlg32 -lcomctl32 -lole32 -loleaut32 -luuid

# compiler settings
CC=g++
CINCS=-I../.. -I../../sxp_extlibs/zlib/src
CWARNS=-Wall -Wno-non-template-friend -Wno-comments -Wno-unknown-pragmas -Wno-int-in-bool-context
CDEFS+=-D PFC_COMPILER_GCC
CFLAGS+=-c -msse2 $(CWARNS) $(CDEFS) $(CINCS)

# linker settings
LD=g++
LDFLAGS=-pthread

# archiver settings
AR=ar
ARFLAGS=rcs

# libraries
LIBRARIES=MINI_SXP
# mini_sxp library
MINI_SXP_LIB:=$(LIBDIR)/mini_sxp_$(build).a
MINI_SXP_LIB_DIRS:=core core/fsys core/math core/math/prim2 core/math/prim3 core/mp core_engine core_engine/loaders
MINI_SXP_LIB_DIRS+=platform/posix
MINI_SXP_LIB_DIRS+=platform/linux/core platform/linux/core/fsys platform/linux/core/math platform/linux/core/mp
MINI_SXP_LIB_DIRS+=platform/opencl

# helper functions
SRC_FILES=$(filter-out $(2),$(foreach DIR,$(1),$(wildcard $(SRCDIR)/$(DIR)/*.cpp)))
OBJ_FILES=$(subst $(SRCDIR),$(INTDIR),$(1:.cpp=.o))

# library target template
define LIB_TEMPLATE
ALL_LIBS+=$($(1)_LIB)
ALL_LIB_DIRS+=$(firstword $(subst /, ,$($(1)_LIB_DIRS)))
$(1)_LIB_SRC:=$(call SRC_FILES,$($(1)_LIB_DIRS),$($(1)_LIB_EXCL))
$(1)_LIB_OBJ:=$$(call OBJ_FILES,$$($(1)_LIB_SRC))
.PHONY $(notdir $($(1)_LIB:_$(build).a=)):
$(notdir $($(1)_LIB:_$(build).a=)) $($(1)_LIB): $($(1)_LIB_DEPS) $$($(1)_LIB_OBJ)
	@echo Creating library $($(1)_LIB)
	@$(call MD,$(dir $($(1)_LIB)))
	@$(AR) $(ARFLAGS) $($(1)_LIB) $$($(1)_LIB_OBJ)
endef

# setup targets for all libraries
$(foreach LIB,$(LIBRARIES),$(eval $(call LIB_TEMPLATE,$(LIB))))

.PHONY: libs
libs: $(ALL_LIBS)

$(INTDIR)/%.o: $(SRCDIR)/%.cpp
	@echo $(subst $(SRCDIR)/,,$<)
	@$(call MD,$(dir $@))
	@$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	@echo Deleting libraries
	@$(foreach LIB,$(ALL_LIBS),$(call RM,$(LIB)))
	@echo Deleting intermediate directories
	@$(call RD,$(INTDIR_ROOT))

.PHONY: clean_int
clean_int:
	@echo Deleting intermediate directories
	@$(call RD,$(INTDIR_ROOT))
