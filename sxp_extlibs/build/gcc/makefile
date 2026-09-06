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
ifeq "$(platform)" "linux32"
CDEFS+=-D PFC_PLATFORM_LINUX32
else ifeq "$(platform)" "linux64"
CDEFS+=-D PFC_PLATFORM_LINUX64
else ifeq "$(platform)" "win32"
CDEFS+=-D PFC_PLATFORM_WIN32
else ifeq "$(platform)" "win64"
CDEFS+=-D PFC_PLATFORM_WIN64
endif
CFLAGS+=-c -msse2 $(CWARNS) $(CDEFS) $(CINCS)

# archiver settings
AR=ar
ARFLAGS=rcs

# libraries
ifneq (,$(filter linux32 linux64,$(platform)))
LIBRARIES=JPEGLIB LIBCRYPTO LIBSSL LIBCURL LIBPNG LIBTIFF LIBWEBP NVTEXTURETOOLS OPENJPEG ZLIB
LIBRARIES+=DAWN SLANG
else
LIBRARIES=JPEGLIB LIBCURL LIBPNG LIBTIFF LIBWEBP NVTEXTURETOOLS OPENJPEG ZLIB
endif
# jpeglib library
JPEGLIB_LIB:=$(LIBDIR)/jpeglib_$(build).a
JPEGLIB_LIB_DIRS:=jpeglib/src
# libcurl library
LIBCURL_LIB:=$(LIBDIR)/libcurl_$(build).a
LIBCURL_LIB_DIRS:=libcurl/src libcurl/src/vauth libcurl/src/vquic libcurl/src/vssh libcurl/src/vtls
LIBCURL_LIB_DEPS:=../../libcurl/src/config-linux.h ../../openssl/include/openssl/configuration.h ../../openssl/include/openssl/opensslv.h
LIBCURL_LIB_CFLAGS:=-D BUILDING_LIBCURL -D_FILE_OFFSET_BITS=64 -include ../../libcurl/src/config-linux.h -pthread
LIBCURL_LIB_CINCS:=-I../../openssl/include
# libcrypto library
LIBCRYPTO_LIB:=$(LIBDIR)/libcrypto_$(build).a
LIBCRYPTO_LIB_DIRS:=openssl/crypto openssl/providers
LIBCRYPTO_LIB_RECURSIVE=1
LIBCRYPTO_LIB_DEPS:=../../openssl/include/openssl/configuration.h ../../openssl/include/crypto/bn_conf.h ../../openssl/include/crypto/dso_conf.h ../../openssl/include/internal/param_names.h ../../openssl/crypto/buildinf.h ../../openssl/crypto/params_idx.c
LIBCRYPTO_LIB_CINCS:=-I../../openssl/include -I../../openssl -I../../openssl/providers/common/include -I../../openssl/providers/implementations/include -I../../openssl/providers/fips/include
LIBCRYPTO_LIB_CFLAGS:=-D OPENSSL_BUILDING_OPENSSL -D OPENSSL_PIC
LIBCRYPTO_LIB_EXCL:=$(SRCDIR)/openssl/crypto/armcap.c $(SRCDIR)/openssl/crypto/dllmain.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/loongarchcap.c $(SRCDIR)/openssl/crypto/ppccap.c $(SRCDIR)/openssl/crypto/riscvcap.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/s390xcap.c $(SRCDIR)/openssl/crypto/sparcv9cap.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/LPdir_nyi.c $(SRCDIR)/openssl/crypto/LPdir_unix.c $(SRCDIR)/openssl/crypto/LPdir_vms.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/LPdir_win.c $(SRCDIR)/openssl/crypto/LPdir_win32.c $(SRCDIR)/openssl/crypto/LPdir_wince.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/bn/asm/x86_64-gcc.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/bn/bn_ppc.c $(SRCDIR)/openssl/crypto/bn/bn_s390x.c $(SRCDIR)/openssl/crypto/bn/bn_sparc.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/bn/rsaz_exp.c $(SRCDIR)/openssl/crypto/bn/rsaz_exp_x2.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/chacha/chacha_ppc.c $(SRCDIR)/openssl/crypto/chacha/chacha_riscv.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/des/ncbc_enc.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/ec/ecp_nistp224.c $(SRCDIR)/openssl/crypto/ec/ecp_nistp256.c $(SRCDIR)/openssl/crypto/ec/ecp_nistp384.c $(SRCDIR)/openssl/crypto/ec/ecp_nistp521.c $(SRCDIR)/openssl/crypto/ec/ecp_nistputil.c $(SRCDIR)/openssl/crypto/ec/ecp_nistz256.c $(SRCDIR)/openssl/crypto/ec/ecp_nistz256_table.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/ec/ecp_ppc.c $(SRCDIR)/openssl/crypto/ec/ecp_s390x_nistp.c $(SRCDIR)/openssl/crypto/ec/ecx_s390x.c $(SRCDIR)/openssl/crypto/ec/ecp_sm2p256.c $(SRCDIR)/openssl/crypto/ec/ecp_sm2p256_table.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/hmac/hmac_s390x.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/evp/legacy_md2.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/md2/md2_dgst.c $(SRCDIR)/openssl/crypto/md2/md2_one.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/poly1305/poly1305_base2_44.c $(SRCDIR)/openssl/crypto/poly1305/poly1305_ieee754.c $(SRCDIR)/openssl/crypto/poly1305/poly1305_ppc.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/rand/rand_egd.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/rc5/rc5cfb64.c $(SRCDIR)/openssl/crypto/rc5/rc5ofb64.c $(SRCDIR)/openssl/crypto/rc5/rc5_ecb.c $(SRCDIR)/openssl/crypto/rc5/rc5_enc.c $(SRCDIR)/openssl/crypto/rc5/rc5_skey.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/sha/sha_ppc.c $(SRCDIR)/openssl/crypto/sha/sha_riscv.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/crypto/sm3/sm3_riscv.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/providers/legacyprov.c $(SRCDIR)/openssl/providers/common/securitycheck_fips.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/providers/implementations/ciphers/cipher_blowfish.c $(SRCDIR)/openssl/providers/implementations/ciphers/cipher_blowfish_hw.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/providers/implementations/ciphers/cipher_cast5.c $(SRCDIR)/openssl/providers/implementations/ciphers/cipher_cast5_hw.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/providers/implementations/ciphers/cipher_des.c $(SRCDIR)/openssl/providers/implementations/ciphers/cipher_desx.c $(SRCDIR)/openssl/providers/implementations/ciphers/cipher_desx_hw.c $(SRCDIR)/openssl/providers/implementations/ciphers/cipher_des_hw.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/providers/implementations/ciphers/cipher_idea.c $(SRCDIR)/openssl/providers/implementations/ciphers/cipher_idea_hw.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/providers/implementations/ciphers/cipher_rc2.c $(SRCDIR)/openssl/providers/implementations/ciphers/cipher_rc2_hw.c $(SRCDIR)/openssl/providers/implementations/ciphers/cipher_rc4.c $(SRCDIR)/openssl/providers/implementations/ciphers/cipher_rc4_hmac_md5.c $(SRCDIR)/openssl/providers/implementations/ciphers/cipher_rc4_hmac_md5_hw.c $(SRCDIR)/openssl/providers/implementations/ciphers/cipher_rc4_hw.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/providers/implementations/ciphers/cipher_rc5.c $(SRCDIR)/openssl/providers/implementations/ciphers/cipher_rc5_hw.c $(SRCDIR)/openssl/providers/implementations/ciphers/cipher_seed.c $(SRCDIR)/openssl/providers/implementations/ciphers/cipher_seed_hw.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/providers/implementations/digests/md2_prov.c $(SRCDIR)/openssl/providers/implementations/digests/md4_prov.c $(SRCDIR)/openssl/providers/implementations/digests/mdc2_prov.c $(SRCDIR)/openssl/providers/implementations/digests/wp_prov.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/providers/implementations/kdfs/pbkdf1.c $(SRCDIR)/openssl/providers/implementations/kdfs/pvkkdf.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/providers/implementations/kem/template_kem.c $(SRCDIR)/openssl/providers/implementations/keymgmt/template_kmgmt.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/providers/implementations/macs/blake2_mac_impl.c $(SRCDIR)/openssl/providers/implementations/rands/fips_crng_test.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/providers/implementations/rands/seeding/rand_cpu_arm64.c $(SRCDIR)/openssl/providers/implementations/rands/seeding/rand_vms.c $(SRCDIR)/openssl/providers/implementations/rands/seeding/rand_vxworks.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/providers/implementations/rands/seeding/rand_win.c
LIBCRYPTO_LIB_EXCL+=$(SRCDIR)/openssl/providers/implementations/storemgmt/winstore_store.c
# libssl library
LIBSSL_LIB:=$(LIBDIR)/libssl_$(build).a
LIBSSL_LIB_DIRS:=openssl/ssl
LIBSSL_LIB_RECURSIVE=1
LIBSSL_LIB_DEPS:=../../openssl/include/openssl/configuration.h ../../openssl/include/openssl/opensslv.h ../../openssl/include/internal/param_names.h
LIBSSL_LIB_CINCS:=-I../../openssl/include -I../../openssl -I../../openssl/providers/common/include -I../../openssl/providers/implementations/include -I../../openssl/providers/fips/include
LIBSSL_LIB_CFLAGS:=-D OPENSSL_BUILDING_OPENSSL -D OPENSSL_PIC
LIBSSL_LIB_EXCL:=$(SRCDIR)/openssl/ssl/priority_queue.c $(SRCDIR)/openssl/ssl/record/methods/ktls_meth.c
LIBSSL_LIB_EXCL+=$(SRCDIR)/openssl/ssl/rio/poll_builder.c $(SRCDIR)/openssl/ssl/rio/rio_notifier.c
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
