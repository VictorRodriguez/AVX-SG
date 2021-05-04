static_flags = -static

SRC_BASIC = src/basic/
SRC_AVX2 = src/avx2/
SRC_SSSE3 = src/ssse3/
SRC_AVX512 = src/avx512/
SRC_VNNI = src/vnni/
SRC_UD2 = src/ud2/
SRC_BFLOAT16 = src/bfloat16/
SRC_CRYPTO = src/crypto/
SRC_AMX = src/amx/

BUILD_DIR = build/
exp_dir = src/experiments/
imgs_dir = docker_images/templates


MKDIR  := mkdir -p
CC_HSW := gcc -O3 -march=haswell -I$(PWD)/src/
CC_SKX := gcc -O3 -march=skylake-avx512 -I$(PWD)/src/
CC_ICX := gcc -O3 -march=icelake-server -I$(PWD)/src/
CC_KN := gcc -O3 -march=skylake-avx512 -mavx5124vnniw -I$(PWD)/src/
CC_static := $(CC) $(static_flags)
CC_HSW_static := $(CC_HSW) $(static_flags)
CC_AMX := /install-dir/bin/gcc
ICC_AMX := icc

all:basic avx2

basic:
	$(MKDIR) $(BUILD_DIR)
	$(CC) $(SRC_BASIC)basic_add_asm.c -o $(BUILD_DIR)basic_add_asm
	$(CC) $(SRC_BASIC)basic_sub_asm.c -o $(BUILD_DIR)basic_sub_asm
	$(CC) $(SRC_BASIC)basic_mul_asm.c -o $(BUILD_DIR)basic_mul_asm
	$(CC) $(SRC_BASIC)basic_div_asm.c -o $(BUILD_DIR)basic_div_asm

avx2:
	$(MKDIR) $(BUILD_DIR)
	$(CC_HSW) $(SRC_AVX2)basic_add_avx2.c -o $(BUILD_DIR)basic_add_avx2
	$(CC_HSW) $(SRC_AVX2)stress_add_avx2.c -o $(BUILD_DIR)stress_add_avx2

ssse3:
	$(CC_HSW) $(SRC_SSSE3)basic_maddubs_epi.c -o $(BUILD_DIR)basic_maddubs_epi

static_check:
	cppcheck --enable=all --inconclusive --suppress=unusedFunction src/*

avx512:
	$(MKDIR) $(BUILD_DIR)
	$(CC_SKX) $(SRC_AVX512)basic_add_avx512.c -o $(BUILD_DIR)basic_add_avx512
	$(CC_SKX) $(SRC_AVX512)basic_add_d_avx512.c -o $(BUILD_DIR)basic_add_d_avx512
	$(CC_SKX) $(SRC_AVX512)basic_add_i_avx512.c -o $(BUILD_DIR)basic_add_i_avx512
	$(CC_SKX) $(SRC_AVX512)stress_add_avx512.c -o $(BUILD_DIR)stress_add_avx512
	$(CC_SKX) $(SRC_AVX512)stress_add_d_avx512.c \
		-o $(BUILD_DIR)stress_add_d_avx512
	$(CC_SKX) $(SRC_AVX512)stress_add_i_avx512.c \
		-o $(BUILD_DIR)stress_add_i_avx512

vnni:
	$(MKDIR) $(BUILD_DIR)
	$(CC_HSW) $(SRC_VNNI)basic_vpmaddwd.c -o $(BUILD_DIR)basic_vpmaddwd
	$(CC_ICX) $(SRC_VNNI)basic_dpbusd_vnni.c -o $(BUILD_DIR)simple_dpbusd_vnni
	$(CC_ICX) $(SRC_VNNI)stress_dpbusd_vnni.c -o $(BUILD_DIR)stress_dpbusd_vnni

vnni_container: vnni
	cp $(BUILD_DIR)simple_dpbusd_vnni $(imgs_dir)
	cd $(imgs_dir) && docker build -t vnni_test .

ud_test:
	$(MKDIR) $(BUILD_DIR)
	$(CC_SKX)   $(SRC_UD2)add_avx512_ud2.c -o $(BUILD_DIR)add_avx512_ud2

experiments:
	$(MKDIR) $(BUILD_DIR)
	$(CC_KN)  $(exp_dir)4dpwssd_epi32.c -o $(BUILD_DIR)4dpwssd_epi32
	$(CC_HSW) $(exp_dir)test_matrix_mul.c -o $(BUILD_DIR)test_matrix_mul
	$(CC_HSW) $(exp_dir)matrix_mul.c -o $(BUILD_DIR)matrix_mul

static:
	echo "sudo dnf config-manager --enable PowerTools"
	echo "sudo dnf install glibc-static"
	$(MKDIR) $(BUILD_DIR)
	$(CC_static) $(SRC_BASIC)basic_add_asm.c -o $(BUILD_DIR)basic_add_asm
	$(CC_static) $(SRC_BASIC)basic_sub_asm.c -o $(BUILD_DIR)basic_sub_asm
	$(CC_static) $(SRC_BASIC)basic_mul_asm.c -o $(BUILD_DIR)basic_mul_asm
	$(CC_static) $(SRC_BASIC)basic_div_asm.c -o $(BUILD_DIR)basic_div_asm

bfloat16:
	clang $(SRC_BFLOAT16)basic_bfloat.c \
		-I $(PWD)/src \
		-o $(BUILD_DIR)basic_bfloat -march=cooperlake
	clang $(SRC_BFLOAT16)basic_bfloat_mm512.c \
		-I $(PWD)/src \
		-o $(BUILD_DIR)basic_bfloat_mm512 -march=cooperlake

crypto: ifma gfni vaes clmul

crypto_container: clean crypto
	cp $(BUILD_DIR)/* $(imgs_dir)
	cd $(imgs_dir) && docker build -t crypto_test -f Dockerfile.crypto .

ifma:
	$(CC_ICX) $(SRC_CRYPTO)basic_vpmadd52huq_i_avx512.c \
		-o $(BUILD_DIR)basic_vpmadd52huq_i_avx512
	$(CC_ICX) $(SRC_CRYPTO)basic_vpmadd52luq_i_avx512.c \
		-o $(BUILD_DIR)basic_vpmadd52luq_i_avx512

gfni:
	$(CC_ICX) $(SRC_CRYPTO)basic_gf2p8affineinv_epi64_epi8.c \
		-o $(BUILD_DIR)basic_gf2p8affineinv_epi64_epi8
	$(CC_ICX) $(SRC_CRYPTO)basic_gf2p8affine_epi64_epi8.c \
		-o $(BUILD_DIR)basic_gf2p8affine_epi64_epi8
	$(CC_ICX) $(SRC_CRYPTO)basic_gf2p8mul_epi8.c \
		-o $(BUILD_DIR)basic_gf2p8mul_epi8

vaes:
	$(CC_ICX) $(SRC_CRYPTO)basic_mm256_aesdec_epi128.c \
		-o $(BUILD_DIR)basic_mm256_aesdec_epi128
	$(CC_ICX) $(SRC_CRYPTO)basic_mm256_aesdeclast_epi128.c \
		-o $(BUILD_DIR)basic_mm256_aesdeclast_epi128
	$(CC_ICX) $(SRC_CRYPTO)basic_mm256_aesenc_epi128.c \
		-o $(BUILD_DIR)basic__mm256_aesenc_epi128
	$(CC_ICX) $(SRC_CRYPTO)basic_mm256_aesenclast_epi128.c \
		-o $(BUILD_DIR)basic_mm256_aesenclast_epi128

clmul:
	$(CC_ICX) $(SRC_CRYPTO)basic_mm256_clmulepi64_epi128.c \
		-o $(BUILD_DIR)basic_mm256_clmulepi64_epi128
	$(CC_ICX) $(SRC_CRYPTO)basic_mm_clmulepi64_si128.c \
		-o $(BUILD_DIR)basic_mm_clmulepi64_si128

amx:
	@echo "Install latest version of master gcc or gcc 11"
	$(CC_AMX) $(SRC_AMX)mamx_basic.c -g -O2 -mamx-tile \
		-o $(BUILD_DIR)mamx_basic
	$(CC_AMX) $(SRC_AMX)amxtile-2.c -g -O2 -mamx-tile \
		-o $(BUILD_DIR)amxtile-2
	$(CC_AMX) $(SRC_AMX)amxbf16-dpbf16ps-2.c -g -O2 -mamx-tile -mamx-bf16 \
		-o $(BUILD_DIR)bf16_dpbf16p
	$(CC_AMX) $(SRC_AMX)amxint8-dpbsud-2.c -g -O2 -mamx-tile -mamx-int8 \
		-o $(BUILD_DIR)amxint8-dpbsud
	$(CC_AMX) $(SRC_AMX)amxint8-dpbssd-2.c -g -O2 -mamx-tile -mamx-int8 \
		-o $(BUILD_DIR)amxint8-dpbssd
	$(CC_AMX) $(SRC_AMX)amxint8-dpbusd-2.c -g -O2 -mamx-tile -mamx-int8 \
		-o $(BUILD_DIR)amxint8-dpbusd
	$(CC_AMX) $(SRC_AMX)amxint8-dpbusd-2.c -g -O2 -mamx-tile -mamx-int8 \
		-o $(BUILD_DIR)amxint8-dpbuud
	$(CC_AMX) $(SRC_AMX)amxint8-dpbssd-fixed-time-2.c -g -O2 -mamx-tile \
		-mamx-int8 -o $(BUILD_DIR)amxint8-dpbssd-fixed-time
	$(CC_AMX) $(SRC_AMX)amxint8-dpbssd-fixed-loops-2.c -g -O2 -mamx-tile \
		-mamx-int8 -o $(BUILD_DIR)amxint8-dpbssd-fixed-loops-2
	$(CC_AMX) $(SRC_AMX)amxint8-dpbssd-threads-2.c -lpthread -g -O2 -mamx-tile \
		-mamx-int8 -o $(BUILD_DIR)amxint8-dpbssd-threads-2

amx-icc:
	$(ICC_AMX) $(SRC_AMX)amxint8-dpbssd-icc-2.c -O2 -mamx-tile -mamx-int8 \
		-o $(BUILD_DIR)amxint8-dpbssd-icc

check:
	./$(BUILD_DIR)basic_add_asm
	./$(BUILD_DIR)basic_sub_asm
	./$(BUILD_DIR)basic_mul_asm
	./$(BUILD_DIR)basic_div_asm
	./$(BUILD_DIR)basic_add_avx2

release:
	mkdir -p avx-bench-basic
	cp run-all.sh avx-bench-basic
	cp -rf build/ avx-bench-basic/
	tar -czvf avx-bench-basic.tar.gz avx-bench-basic/

clean-release:
	rm -rf avx-bench-basic*

clean:
	@rm -rf build/*
