#include <immintrin.h>
#include "amx-check.h"

void test_amx_tile ();

void test_amx_tile ()
{
  __tilecfg_u cfg_src, cfg_dst;
  __tile reg_src1, reg_src2, reg_ref;

  /* check tile config load & store. */
  init_tile_config (&cfg_src);
  _tile_storeconfig (cfg_dst.a);

  if (!check_tile_config (&cfg_src, &cfg_dst)){
	print_notOK();
    abort ();
	}

  /* check tile register load & store. */
  init_tile_reg_and_src (1, reg_src1);
  _tile_stored (1, reg_ref.buf, _STRIDE);
  if (!check_tile_register (&reg_ref, &reg_src1)){
	print_notOK();
    abort ();
	}

  /* check tile stream load instruction */
  init_tile_src (2, &reg_src2, NULL);
  _tile_stream_loadd (2, reg_src2.buf, _STRIDE);
  _tile_stored (2, reg_ref.buf, _STRIDE);
  if (!check_tile_register (&reg_ref, &reg_src2)){
	print_notOK();
    abort ();
	}

  /* check tile register zeroing */
  zero_tile_src (&reg_src2);
  _tile_zero (2);
  _tile_stored (2, reg_ref.buf, _STRIDE);
  if (!check_tile_register (&reg_ref, &reg_src2)){
	print_notOK();
    abort ();
   }

  /* check tile cfg zeroing */
  memset (cfg_dst.a, 0, sizeof(__tilecfg));
  _tile_release ();
  _tile_storeconfig (cfg_src.a);
  if (!check_tile_config (&cfg_src, &cfg_dst)){
	print_notOK();
    abort ();
	}
}

int main(){

	test_amx_tile();
	printOK();
	return 0;
}
