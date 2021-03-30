#include <immintrin.h>
#include "amx-check.h"

void TEST() {

    __tilecfg_u cfg;
    __tile dst, dst_ref, src1, src2;
    uint8_t tmp_dst_buf[1024];

    init_tile_config (&cfg);
	_tile_dpbssd(1,2,3);
	_tile_release();
}

int main (){
	TEST();
	return 0;
}
