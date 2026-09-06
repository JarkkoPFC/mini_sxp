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
ifneq (,$(filter linux32 linux64,$(platform)))
LIBRARIES+=DAWN SLANG
endif
# jpeglib library
JPEGLIB_LIB:=$(LIBDIR)/jpeglib_$(build).a
JPEGLIB_LIB_DIRS:=jpeglib/src
# libcurl library
LIBCURL_LIB:=$(LIBDIR)/libcurl_$(build).a
LIBCURL_LIB_DIRS:=libcurl/src libcurl/src/vauth libcurl/src/vquic libcurl/src/vssh libcurl/src/vtls
LIBCURL_LIB_DEPS:=../../libcurl/src/config-linux.h
LIBCURL_LIB_CFLAGS:=-D BUILDING_LIBCURL -D_FILE_OFFSET_BITS=64 -include ../../libcurl/src/config-linux.h -pthread
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
# dawn library (Linux Vulkan + null backends)
DAWN_LIB:=$(LIBDIR)/dawn_$(build).a
DAWN_LIB_DIRS:=dawn
DAWN_LIB_RECURSIVE=1
DAWN_LIB_CINCS:=-I../../dawn -I../../dawn/include -I../../dawn/src -I../../dawn/src/dawn/partition_alloc -I../../dawn/gen/include -I../../dawn/gen/src -I../../dawn/third_party -I../../dawn/third_party/abseil-cpp -I../../dawn/third_party/dxc -I../../dawn/third_party/spirv-headers/include -I../../vulkan/include
DAWN_LIB_CFLAGS:=-std=c++20 -D_LIB -DNOMINMAX -DDAWN_ENABLE_BACKEND_VULKAN=1 -DDAWN_ENABLE_BACKEND_NULL=1 -DDAWN_USE_BUILT_DXC=1 -DTINT_BUILD_NULL_WRITER=1 -DTINT_BUILD_SPV_READER=0 -DTINT_BUILD_SPV_WRITER=1 -DTINT_BUILD_WGSL_READER=1 -DTINT_BUILD_WGSL_WRITER=1 -DTINT_BUILD_MSL_WRITER=1 -DTINT_BUILD_HLSL_WRITER=1 -DTINT_BUILD_GLSL_WRITER=0 -DTINT_BUILD_GLSL_VALIDATOR=0 -DTINT_BUILD_IR_BINARY=0 -DTINT_BUILD_IS_WIN=0 -DTINT_BUILD_IS_MAC=0 -DTINT_BUILD_IS_LINUX=1
DAWN_LIB_EXCL:=$(SRCDIR)/dawn/src/dawn/common/IOSurfaceUtils.cpp $(SRCDIR)/dawn/src/dawn/common/WindowsUtils.cpp
DAWN_LIB_EXCL+=$(SRCDIR)/dawn/src/dawn/native/X11Functions.cpp
DAWN_LIB_EXCL+=$(SRCDIR)/dawn/src/dawn/native/d3d/%.cpp $(SRCDIR)/dawn/src/dawn/native/d3d12/%.cpp
DAWN_LIB_EXCL+=$(SRCDIR)/dawn/src/tint/utils/%_windows.cc $(SRCDIR)/dawn/src/tint/utils/%_mac.cc $(SRCDIR)/dawn/src/tint/utils/%_ios.cc $(SRCDIR)/dawn/src/tint/utils/%_android.cc $(SRCDIR)/dawn/src/tint/utils/%_fuchsia.cc
DAWN_LIB_EXCL+=$(SRCDIR)/dawn/src/tint/utils/system/terminal_other.cc $(SRCDIR)/dawn/src/tint/utils/file/tmpfile_other.cc $(SRCDIR)/dawn/src/tint/utils/text/styled_text_printer_other.cc
DAWN_LIB_EXCL+=$(SRCDIR)/dawn/third_party/abseil-cpp/absl/time/internal/cctz/src/time_zone_name_win.cc
# slang library (Linux compiler without LLVM/glslang/optional downstream backends)
SLANG_LIB:=$(LIBDIR)/slang_$(build).a
SLANG_LIB_DIRS:=slang
SLANG_LIB_RECURSIVE=1
SLANG_LIB_CINCS:=-I../../slang -I../../slang/include -I../../slang/source -I../../slang/source/slang -I../../slang/prelude -I../../slang/external/miniz -I../../slang/external/lz4/lib -I../../slang/external/unordered_dense/include -I../../slang/external/spirv-headers/include -I../../vulkan/include -I../../slang/generated/source/slang -I../../slang/generated/source/standard-modules -I../../slang/generated/external/miniz
SLANG_LIB_CFLAGS:=-std=c++20 -D_LIB -DSLANG_COMPILER -DSLANG_STATIC -DSLANG_EMBED_CORE_MODULE_SOURCE=1 -DNOMINMAX -Wno-unused-local-typedefs -Wno-reorder -Wno-switch
SLANG_LIB_EXCL:=$(SRCDIR)/slang/source/slang-llvm/%.cpp
SLANG_LIB_EXCL+=$(SRCDIR)/slang/source/core/windows/%.cpp $(SRCDIR)/slang/source/compiler-core/windows/%.cpp
SLANG_LIB_EXCL+=$(SRCDIR)/slang/source/compiler-core/slang-glslang-compiler.cpp $(SRCDIR)/slang/source/compiler-core/slang-metal-compiler.cpp $(SRCDIR)/slang/source/compiler-core/slang-nvrtc-compiler.cpp $(SRCDIR)/slang/source/compiler-core/slang-tint-compiler.cpp


# helper functions
SRC_FILES=$(filter-out $(2),$(foreach DIR,$(1),$(wildcard $(SRCDIR)/$(DIR)/*.c $(SRCDIR)/$(DIR)/*.cc $(SRCDIR)/$(DIR)/*.cpp)))
SRC_FILES_RECURSIVE=$(filter-out $(2),$(foreach DIR,$(1),$(shell find $(SRCDIR)/$(DIR) -type f \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' \))))
OBJ_FILES=$(subst $(SRCDIR),$(INTDIR),$(patsubst %.cpp,%.o,$(patsubst %.cc,%.o,$(1:.c=.o))))

define LIB_TEMPLATE
ALL_LIBS+=$($(1)_LIB)
$(1)_LIB_DIR=$(firstword $(subst /, ,$($(1)_LIB_DIRS)))
ALL_LIB_DIRS+=$$($(1)_LIB_DIR)
#ALL_LIB_DIRS+=$(firstword $(subst /, ,$($(1)_LIB_DIRS)))
$(1)_LIB_SRC:=$(if $($(1)_LIB_RECURSIVE),$(call SRC_FILES_RECURSIVE,$($(1)_LIB_DIRS),$($(1)_LIB_EXCL)),$(call SRC_FILES,$($(1)_LIB_DIRS),$($(1)_LIB_EXCL)))
$(1)_LIB_OBJ:=$$(call OBJ_FILES,$$($(1)_LIB_SRC))
.PHONY $(notdir $($(1)_LIB:_$(build).a=)):
$(notdir $($(1)_LIB:_$(build).a=)) $($(1)_LIB): $$($(1)_LIB_OBJ)
	@echo Creating library $($(1)_LIB)
	@$(call MD,$(dir $($(1)_LIB)))
	@$(AR) $(ARFLAGS) $($(1)_LIB) $$($(1)_LIB_OBJ)
$(INTDIR)/$$($(1)_LIB_DIR)/%.o: $(SRCDIR)/$$($(1)_LIB_DIR)/%.c $($(1)_LIB_DEPS)
	@echo $(subst $(SRCDIR)/,,$$<)
	@$$(call MD,$$(dir $$@))
	@$(CC) $(CFLAGS) $($(1)_LIB_CFLAGS) $($(1)_LIB_CINCS) $$< -o $$@
$(INTDIR)/$$($(1)_LIB_DIR)/%.o: $(SRCDIR)/$$($(1)_LIB_DIR)/%.cpp $($(1)_LIB_DEPS)
	@echo $(subst $(SRCDIR)/,,$$<)
	@$$(call MD,$$(dir $$@))
	@$(CC) $(CFLAGS) $($(1)_LIB_CFLAGS) $($(1)_LIB_CINCS) $$< -o $$@
$(INTDIR)/$$($(1)_LIB_DIR)/%.o: $(SRCDIR)/$$($(1)_LIB_DIR)/%.cc $($(1)_LIB_DEPS)
	@echo $(subst $(SRCDIR)/,,$$<)
	@$$(call MD,$$(dir $$@))
	@$(CC) $(CFLAGS) $($(1)_LIB_CFLAGS) $($(1)_LIB_CINCS) $$< -o $$@
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
