#============================================================================
# Mini Spin-X Library - External Libraries
#
# Copyright (c) 2022, Jarkko Lempiainen
# All rights reserved.
#----------------------------------------------------------------------------
#
# make options:
#   build=<build>       - options: debug (default), release, retail
#   platform=<platform> - options: win32 (default), win64, linux32, linux64
# make targets:
#   libs                - compile all libraries (default)
#   clean               - delete libraries and object files for the target
#   <library name>      - compile given library, e.g. jpeglib
#
# examples:
# to compile release build of all libraries (for win32):
#   make build=release
#
# to compile release build for linux64 of libogg and jpeglib:
#   make build=release platform=linux64 libogg jpeglib
#
# to clean all release build files (for win32):
#   make build=release clean
#
# to clean and rebuild win32 debug libraries:
#   make clean libs


# build settings
ifndef build
build=debug
endif
$(if $(filter $(build),debug release retail),,$(error unknown target build "$(build)"))
ifeq "$(build)" "debug"
CFLAGS=-ggdb
else ifeq "$(build)" "release"
CFLAGS=-O2
else ifeq "$(build)" "retail"
CFLAGS=-O3
endif

# platform settings
ifndef platform
platform=linux32
endif
$(if $(filter $(platform),linux32 linux64 win32 win64),,$(error unknown target platform "$(platform)"))
ifeq "$(platform)" "win32"
CFLAGS+=-m32
else ifeq "$(platform)" "win64"
CFLAGS+=-m64
else ifeq "$(platform)" "linux32"
CFLAGS+=-m32
else ifeq "$(platform)" "linux64"
CFLAGS+=-m64
endif

# generic settings
.DEFAULT_GOAL:=libs
MD=mkdir -p $(1)
RD=rm -r $(1)
RM=rm $(1)
INTDIR_ROOT=../../_intermediate
INTDIR=$(INTDIR_ROOT)/$(platform)_gcc/$(build)
LIBDIR=../../lib/$(platform)_gcc
SRCDIR=../..
LIBDIR=../../lib/$(platform)_gcc

# compiler settings
CC=gcc
CINCS=-I../../libogg/src/include -I../../libpng/src -I../../libtiff/src -I../../zlib/src -I../../jpeglib/src -I../../nvtexturetools/src
CWARNS=-Wall -Wno-non-template-friend -Wno-comments -Wno-unknown-pragmas
CDEFS=
CFLAGS+=-c -msse2 $(CWARNS) $(CDEFS) $(CINCS)

# archiver settings
AR=ar
ARFLAGS=rcs

# libraries
LIBRARIES=JPEGLIB LIBPNG LIBTIFF LIBWEBP NVTEXTURETOOLS NVTRISTRIP OPENJPEG ZLIB
# jpeglib library
JPEGLIB_LIB:=$(LIBDIR)/jpeglib_$(build).a
JPEGLIB_LIB_DIRS:=jpeglib/src
# libpng library
LIBPNG_LIB:=$(LIBDIR)/libpng_$(build).a
LIBPNG_LIB_DIRS:=libpng/src
# libtiff library
LIBTIFF_LIB:=$(LIBDIR)/libtiff_$(build).a
LIBTIFF_LIB_DIRS:=libtiff/src
# libwebp library
LIBWEBP_LIB:=$(LIBDIR)/libwebp_$(build).a
LIBWEBP_LIB_DIRS:=libwebp/src/dec libwebp/src/demux libwebp/src/dsp libwebp/src/enc libwebp/src/mux libwebp/src/utils libwebp/src/webp
# nvtexturetools library
NVTEXTURETOOLS_LIB:=$(LIBDIR)/nvtexturetools_$(build).a
NVTEXTURETOOLS_LIB_DIRS:=nvtexturetools/src/nvcore nvtexturetools/src/nvcore/posh nvtexturetools/src/nvimage nvtexturetools/src/nvmath nvtexturetools/src/nvtt nvtexturetools/src/nvtt/cuda nvtexturetools/src/nvtt/squish
NVTEXTURETOOLS_LIB_CFLAGS:=-D __SSE2__
# nvtristrip library
NVTRISTRIP_LIB:=$(LIBDIR)/nvtristrip_$(build).a
NVTRISTRIP_LIB_DIRS:=nvtristrip/src
# openjpeg library
OPENJPEG_LIB:=$(LIBDIR)/openjpeg_$(build).a
OPENJPEG_LIB_DIRS:=openjpeg/src
OPENJPEG_LIB_CFLAGS:=-D OPJ_STATIC
# zlib library
ZLIB_LIB:=$(LIBDIR)/zlib_$(build).a
ZLIB_LIB_DIRS:=zlib/src


# helper functions
SRC_FILES=$(filter-out $(2),$(foreach DIR,$(1),$(wildcard $(SRCDIR)/$(DIR)/*.c $(SRCDIR)/$(DIR)/*.cpp)))
OBJ_FILES=$(subst $(SRCDIR),$(INTDIR),$(patsubst %.cpp,%.o,$(1:.c=.o)))

define LIB_TEMPLATE
ALL_LIBS+=$($(1)_LIB)
$(1)_LIB_DIR=$(firstword $(subst /, ,$($(1)_LIB_DIRS)))
ALL_LIB_DIRS+=$$($(1)_LIB_DIR)
#ALL_LIB_DIRS+=$(firstword $(subst /, ,$($(1)_LIB_DIRS)))
$(1)_LIB_SRC:=$(call SRC_FILES,$($(1)_LIB_DIRS),$($(1)_LIB_EXCL))
$(1)_LIB_OBJ:=$$(call OBJ_FILES,$$($(1)_LIB_SRC))
.PHONY $(notdir $($(1)_LIB:_$(build).a=)):
$(notdir $($(1)_LIB:_$(build).a=)) $($(1)_LIB): $$($(1)_LIB_OBJ)
	@echo Creating library $($(1)_LIB)
	$(call MD,$(dir $($(1)_LIB)))
	@$(AR) $(ARFLAGS) $($(1)_LIB) $$($(1)_LIB_OBJ)
$(INTDIR)/$$($(1)_LIB_DIR)/%.o: $(SRCDIR)/$$($(1)_LIB_DIR)/%.c
	@echo $(subst $(SRCDIR)/,,$$<)
	$$(call MD,$$(dir $$@))
	@$(CC) $(CFLAGS) $($(1)_LIB_CFLAGS) $$< -o $$@
$(INTDIR)/$$($(1)_LIB_DIR)/%.o: $(SRCDIR)/$$($(1)_LIB_DIR)/%.cpp
	@echo $(subst $(SRCDIR)/,,$$<)
	$$(call MD,$$(dir $$@))
	@$(CC) $(CFLAGS) $($(1)_LIB_CFLAGS) $$< -o $$@
endef

$(foreach LIB,$(LIBRARIES),$(eval $(call LIB_TEMPLATE,$(LIB))))

.PHONY: libs
libs: $(ALL_LIBS)

.PHONY: clean
clean:
	@echo Deleting libraries
	@$(foreach LIB,$(ALL_LIBS),$(call RM,$(LIB)))
	@echo Deleting intermediate directories
	@$(foreach LDIR,$(ALL_LIB_DIRS),$(call RD,$(INTDIR)/$(LDIR)))
