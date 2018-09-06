static_flags = -static
src_dir = src/
build_dir = build/

all:
	mkdir -p $(build_dir)
	gcc $(src_dir)basic_add_asm.c -o $(build_dir)basic_add_asm
	gcc $(src_dir)basic_sub_asm.c -o $(build_dir)basic_sub_asm
	gcc $(src_dir)basic_mul_asm.c -o $(build_dir)basic_mul_asm
	gcc $(src_dir)basic_div_asm.c -o $(build_dir)basic_div_asm
	gcc -O3 -march=haswell $(src_dir)basic_add_avx2.c -o $(build_dir)basic_add_avx2
	gcc -O3 -march=haswell $(src_dir)stress_add_avx2.c -o $(build_dir)stress_add_avx2
	gcc -O3 -march=skylake-avx512 $(src_dir)basic_add_avx512.c -o $(build_dir)basic_add_avx512
	gcc -O3 -march=skylake-avx512 $(src_dir)basic_add_d_avx512.c -o $(build_dir)basic_add_d_avx512
	gcc -O3 -march=skylake-avx512 $(src_dir)basic_add_i_avx512.c -o $(build_dir)basic_add_i_avx512
	gcc -O3 -march=skylake-avx512 $(src_dir)stress_add_avx512.c -o $(build_dir)stress_add_avx512
	gcc -O3 -march=skylake-avx512 $(src_dir)stress_add_d_avx512.c -o $(build_dir)stress_add_d_avx512
	gcc -O3 -march=skylake-avx512 $(src_dir)stress_add_i_avx512.c -o $(build_dir)stress_add_i_avx512
	gcc -O3 -march=skylake-avx512 -mavx5124vnniw $(src_dir)4dpwssd_epi32.c -o $(build_dir)4dpwssd_epi32
	gcc -O3 -march=icelake-server $(src_dir)stress_dpbusd_vnni.c -o $(build_dir)stress_dpbusd_vnni

static:
	mkdir -p $(build_dir)
	gcc $(src_dir)basic_add_asm.c -o $(build_dir)basic_add_asm $(static_flags)
	gcc $(src_dir)basic_sub_asm.c -o $(build_dir)basic_sub_asm $(static_flags)
	gcc $(src_dir)basic_mul_asm.c -o $(build_dir)basic_mul_asm $(static_flags)
	gcc $(src_dir)basic_div_asm.c -o $(build_dir)basic_div_asm $(static_flags)
	gcc -O3 -march=haswell $(src_dir)basic_add_avx2.c -o $(build_dir)basic_add_avx2 $(static_flags)
	gcc -O3 -march=haswell $(src_dir)stress_add_avx2.c -o $(build_dir)stress_add_avx2 $(static_flags)
	gcc -O3 -march=skylake-avx512 $(src_dir)basic_add_avx512.c -o $(build_dir)basic_add_avx512 $(static_flags)
	gcc -O3 -march=skylake-avx512 $(src_dir)basic_add_d_avx512.c -o $(build_dir)basic_add_d_avx512 $(static_flags)
	gcc -O3 -march=skylake-avx512 $(src_dir)basic_add_i_avx512.c -o $(build_dir)basic_add_i_avx512 $(static_flags)
	gcc -O3 -march=skylake-avx512 $(src_dir)stress_add_avx512.c -o $(build_dir)stress_add_avx512 $(static_flags)
	gcc -O3 -march=skylake-avx512 $(src_dir)stress_add_d_avx512.c -o $(build_dir)stress_add_d_avx512 $(static_flags)
	gcc -O3 -march=skylake-avx512 $(src_dir)stress_add_i_avx512.c -o $(build_dir)stress_add_i_avx512 $(static_flags)
	gcc -O3 -march=skylake-avx512 -mavx5124vnniw $(src_dir)4dpwssd_epi32.c -o $(build_dir)4dpwssd_epi32 $(static_flags)
	gcc -O3 -march=icelake-server $(src_dir)stress_dpbusd_vnni.c -o $(build_dir)stress_dpbusd_vnni $(static_flags)

check: all
	./$(build_dir)basic_add_asm
	./$(build_dir)basic_sub_asm
	./$(build_dir)basic_mul_asm
	./$(build_dir)basic_div_asm
	./$(build_dir)basic_add_avx2
	./$(build_dir)basic_add_avx512
	./$(build_dir)basic_add_d_avx512
	./$(build_dir)basic_add_i_avx512
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
