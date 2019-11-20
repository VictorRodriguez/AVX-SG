static_flags = -static
src_dir = src/
build_dir = build/
exp_dir = src/experiments/

MKDIR  := mkdir -p
CC_HSW := gcc -O3 -march=haswell
CC_SKX := gcc -O3 -march=skylake-avx512
CC_ICX := gcc -O3 -march=icelake-server
CC_KN := gcc -O3 -march=skylake-avx512 -mavx5124vnniw
CC_static := $(CC) $(static_flags)
CC_HSW_static := $(CC_HSW) $(static_flags)



all:
	$(MKDIR) $(build_dir)
	$(CC) $(src_dir)basic_add_asm.c -o $(build_dir)basic_add_asm
	$(CC) $(src_dir)basic_sub_asm.c -o $(build_dir)basic_sub_asm
	$(CC) $(src_dir)basic_mul_asm.c -o $(build_dir)basic_mul_asm
	$(CC) $(src_dir)basic_div_asm.c -o $(build_dir)basic_div_asm
	$(CC_HSW) $(src_dir)basic_add_avx2.c -o $(build_dir)basic_add_avx2
	$(CC_HSW) $(src_dir)stress_add_avx2.c -o $(build_dir)stress_add_avx2

avx512:
	$(MKDIR) $(build_dir)
	$(CC_SKX) $(src_dir)basic_add_avx512.c -o $(build_dir)basic_add_avx512
	$(CC_SKX) $(src_dir)basic_add_d_avx512.c -o $(build_dir)basic_add_d_avx512
	$(CC_SKX) $(src_dir)basic_add_i_avx512.c -o $(build_dir)basic_add_i_avx512
	$(CC_SKX) $(src_dir)stress_add_avx512.c -o $(build_dir)stress_add_avx512
	$(CC_SKX) $(src_dir)stress_add_d_avx512.c -o $(build_dir)stress_add_d_avx512
	$(CC_SKX) $(src_dir)stress_add_i_avx512.c -o $(build_dir)stress_add_i_avx512

vnni:
	$(MKDIR) $(build_dir)
	$(CC_ICX) $(src_dir)stress_dpbusd_vnni.c -o $(build_dir)stress_dpbusd_vnni
	$(CC_ICX) $(src_dir)basic_dpbusd_vnni.c -o $(build_dir)simple_dpbusd_vnni

ud_test:
	$(MKDIR) $(build_dir)
	$(CC_SKX)   $(ud2_dir)add_avx512_ud2.c -o $(build_dir)add_avx512_ud2
	$(CC_SKX_T) $(ud2_dir)add_avx512_t_ud2.c -o $(build_dir)add_avx512_t_ud2
	$(CC_SKX_T) $(ud2_dir)add_avx_mthread.c -o $(build_dir)add_avx_mthread

experiments:
	$(MKDIR) $(build_dir)
	$(CC_KN)  $(exp_dir)4dpwssd_epi32.c -o $(build_dir)4dpwssd_epi32
	$(CC_HSW) $(exp_dir)test_matrix_mul.c -o $(build_dir)test_matrix_mul
	$(CC_HSW) $(exp_dir)matrix_mul.c -o $(build_dir)matrix_mul

static:
	$(MKDIR) $(build_dir)
	$(CC_static) $(src_dir)basic_add_asm.c -o $(build_dir)basic_add_asm
	$(CC_static) $(src_dir)basic_sub_asm.c -o $(build_dir)basic_sub_asm
	$(CC_static) $(src_dir)basic_mul_asm.c -o $(build_dir)basic_mul_asm
	$(CC_static) $(src_dir)basic_div_asm.c -o $(build_dir)basic_div_asm
	$(CC_HSW_static) $(src_dir)basic_add_avx2.c -o $(build_dir)basic_add_avx2
	$(CC_HSW_static) $(src_dir)stress_add_avx2.c -o $(build_dir)stress_add_avx2

check:
	./$(build_dir)basic_add_asm
	./$(build_dir)basic_sub_asm
	./$(build_dir)basic_mul_asm
	./$(build_dir)basic_div_asm
	./$(build_dir)basic_add_avx2

release:
	mkdir -p avx-bench-basic
	cp run-all.sh avx-bench-basic
	cp -rf build/ avx-bench-basic/
	tar -czvf avx-bench-basic.tar.gz avx-bench-basic/

clean-release:
	rm -rf avx-bench-basic*

clean:
	@find . -type f -executable -exec sh -c "file -i '{}' | grep -q 'x-executable; charset=binary'" \; -print | xargs rm -f
	@rm -rf build
