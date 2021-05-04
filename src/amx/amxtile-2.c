#include <immintrin.h>
#include<tap.h>
#include "amx-check.h"

void test_amx_tile ();

void test_amx_tile ()
{
  __tilecfg_u cfg_src, cfg_dst;
  __tile reg_src1, reg_src2, reg_ref;

  /* check tile config load & store. */
  init_tile_config (&cfg_src);
  _tile_storeconfig (cfg_dst.a);

  ok(check_tile_config (&cfg_src, &cfg_dst), "Check tile config load & store");

  /* check tile register load & store. */
  init_tile_reg_and_src (1, reg_src1);
  _tile_stored (1, reg_ref.buf, _STRIDE);
  ok(check_tile_register (&reg_ref, &reg_src1), "Check tile register load & store");

  /* check tile stream load instruction */
  init_tile_src (2, &reg_src2, NULL);
  _tile_stream_loadd (2, reg_src2.buf, _STRIDE);
  _tile_stored (2, reg_ref.buf, _STRIDE);
  ok(check_tile_register (&reg_ref, &reg_src2), "check tile stream load instruction");

  /* check tile register zeroing */
  zero_tile_src (&reg_src2);
  _tile_zero (2);
  _tile_stored (2, reg_ref.buf, _STRIDE);
  ok(check_tile_register (&reg_ref, &reg_src2), "Check tile register zeroing");

  /* check tile cfg zeroing */
  memset (cfg_dst.a, 0, sizeof(__tilecfg));
  _tile_release ();
  _tile_storeconfig (cfg_src.a);
  ok(check_tile_config (&cfg_src, &cfg_dst), "check tile cfg zeroing");
}

int main(){
        plan(5);
	test_amx_tile();
        done_testing();
}
