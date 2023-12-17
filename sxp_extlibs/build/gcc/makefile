#============================================================================
# Mini Spin-X Library - External Libraries
#
# Copyright (c) 2022, Jarkko Lempiainen
# All rights reserved.
#----------------------------------------------------------------------------
#
# make options:
#   build=<build>       - options: debug (default), release, retail
#   platform=<platform> - options: linux32, linux64 (default), win32, win64
# make targets:
#   libs                - compile all libraries (default)
#   clean               - delete libraries and object files for the target
#   <library name>      - compile given library, e.g. jpeglib
#
# examples:
# to compile release build of all libraries (for linux64):
#   make build=release
#
# to compile release build for win64 of libpng and jpeglib:
#   make build=release platform=win64 libpng jpeglib
#
# to clean all release build files (for linux64):
#   make build=release clean
#
# to clean and rebuild linux64 debug libraries:
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
platform=linux64
endif
$(if $(filter $(platform),linux32 linux64 win32 win64),,$(error unknown target platform "$(platform)"))
ifeq "$(platform)" "linux32"
CFLAGS+=-m32
else ifeq "$(platform)" "linux64"
CFLAGS+=-m64
else ifeq "$(platform)" "win32"
CFLAGS+=-m32
else ifeq "$(platform)" "win64"
CFLAGS+=-m64
endif

# generic settings
.DEFAULT_GOAL:=libs
MD=mkdir -p $(1)
RD=rm -r -f $(1)
RM=rm -f $(1)
INTDIR_ROOT=../../_intermediate
INTDIR=$(INTDIR_ROOT)/$(platform)_gcc/$(build)
LIBDIR=../../lib/$(platform)_gcc
SRCDIR=../..
LIBDIR=../../lib/$(platform)_gcc

# compiler settings
CC=gcc
CINCS=-I../../jpeglib/src -I../../libcurl/src -I../../libcurl/include -I../../libpng/src -I../../libtiff/src -I../../zlib/src -I../../nvtexturetools/src -I../../nvtexturetools/src/extern/poshlib -I../../nvtexturetools/src/extern/poshlib
CWARNS=-Wall -Wno-comments -Wno-unknown-pragmas -Wno-write-strings -Wno-main
CDEFS=
CFLAGS+=-c -msse2 $(CWARNS) $(CDEFS) $(CINCS)

# archiver settings
AR=ar
ARFLAGS=rcs

# libraries
LIBRARIES=JPEGLIB LIBCURL LIBPNG LIBTIFF LIBWEBP NVTEXTURETOOLS OPENJPEG ZLIB
# jpeglib library
JPEGLIB_LIB:=$(LIBDIR)/jpeglib_$(build).a
JPEGLIB_LIB_DIRS:=jpeglib/src
# libcurl library
LIBCURL_LIB:=$(LIBDIR)/libcurl_$(build).a
LIBCURL_LIB_DIRS:=libcurl/src libcurl/src/vauth libcurl/src/vquic libcurl/src/vssh libcurl/src/vtls
LIBCURL_LIB_CFLAGS:=-D BUILDING_LIBCURL
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
NVTEXTURETOOLS_LIB_DIRS:=nvtexturetools/src/bc6h nvtexturetools/src/bc7 nvtexturetools/src/extern/posh nvtexturetools/src/nvcore nvtexturetools/src/nvimage nvtexturetools/src/nvmath nvtexturetools/src/nvthread nvtexturetools/src/nvtt nvtexturetools/src/nvtt/cuda nvtexturetools/src/nvtt/squish
NVTEXTURETOOLS_LIB_EXCL:=%/nvimage/ColorSpace.cpp %/nvimage/KtxFile.cpp %/nvimage/Quantize.cpp
NVTEXTURETOOLS_LIB_EXCL+=%/nvmath/Box.cpp %/nvmath/Color.cpp %/nvmath/Matrix.cpp %/nvmath/Vector.cpp
NVTEXTURETOOLS_LIB_EXCL+=%/nvtt/squish/alpha.cpp %/nvtt/squish/clusterfit.cpp %/nvtt/squish/rangefit.cpp %/nvtt/squish/singlechannelfit.cpp %/nvtt/squish/singlecolourfit.cpp %/nvtt/squish/squish.cpp
NVTEXTURETOOLS_LIB_EXCL+=%/nvtt/TaskDispatcher.cpp
NVTEXTURETOOLS_LIB_CFLAGS:=-D __SSE2__
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
	@$(call MD,$(dir $($(1)_LIB)))
	@$(AR) $(ARFLAGS) $($(1)_LIB) $$($(1)_LIB_OBJ)
$(INTDIR)/$$($(1)_LIB_DIR)/%.o: $(SRCDIR)/$$($(1)_LIB_DIR)/%.c
	@echo $(subst $(SRCDIR)/,,$$<)
	@$$(call MD,$$(dir $$@))
	@$(CC) $(CFLAGS) $($(1)_LIB_CFLAGS) $$< -o $$@
$(INTDIR)/$$($(1)_LIB_DIR)/%.o: $(SRCDIR)/$$($(1)_LIB_DIR)/%.cpp
	@echo $(subst $(SRCDIR)/,,$$<)
	@$$(call MD,$$(dir $$@))
	@$(CC) $(CFLAGS) $($(1)_LIB_CFLAGS) $$< -o $$@
endef

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
