#ifndef AMX_CHECK_H_INCLUDED
#define AMX_CHECK_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "cpuid.h"

#define MAX 1000

/* TODO: The tmm emulation is temporary for current
   AMX implementation with no tmm regclass, should
   be changed in the future. */
typedef struct __tile_config
{
  uint8_t palette_id;
  uint8_t start_row;
  uint8_t reserved_0[14];
  uint16_t colsb[8]; /* Colum size of each tmm register in bytes */
  uint16_t reserved_1[8];
  uint8_t rows[8]; /* Row size of each tmm reg in bytes */
  uint8_t reserved_2[8];
} __tilecfg;

typedef union __union_tile_config
{
  __tilecfg s;
  uint8_t a[64];
} __tilecfg_u;

typedef struct __tile
{
  /* Max size of tile register */
  uint8_t buf[1024];
  int rows;
  int colsb;
} __tile;

/* Maxium col/row size in bytes */
#define MAX_ROWS 16
#define MAX_COLS 64

/* Stride (colum width in byte) used for tileload/store */
#define _STRIDE 64

/* Initialize tile config by setting all tmm size to 16x64 */
void init_tile_config (__tilecfg_u *dst)
{
  int i;

  dst->s.palette_id = 1;
  dst->s.start_row = 0;

  for (i = 0; i < 14; i++)
    dst->s.reserved_0[i] = 0;

  for (i = 0; i < 8; i++)
  {
    dst->s.colsb[i] = _STRIDE;
    dst->s.rows[i] = 16;
    dst->s.reserved_1[i] = 0;
    dst->s.reserved_2[i] = 0;
  }

  _tile_loadconfig (dst->a);
}

/* Init __tile variable that going to be store to register
   w/o extra buffer. If buffer exists, it should be the same
   size matrix as corresponding tmm register.
   Should execute init_tile_config first */
void init_tile_src (const int tmm_num, __tile *src, uint8_t *buffer)
{
  int rows, colsb, i, j;
  __tilecfg_u tmp;

  _tile_storeconfig (tmp.a);

  src->rows = rows = tmp.s.rows[tmm_num];
  src->colsb = colsb = tmp.s.colsb[tmm_num];

  for (i = 0; i < rows; i++)
    for (j = 0; j < colsb; j++)
    {
      if(buffer)
	src->buf[i * colsb + j] = buffer[i * colsb + j];
      else
	src->buf[i * colsb + j] = (i + 11 * j) % 256;
    }

}

/* Init __tile src and corresponding tmm register */
#define init_tile_reg_and_src(tmm_num, src)   \
{					      \
  init_tile_src (tmm_num, &src, NULL);	      \
  _tile_loadd (tmm_num, src.buf, _STRIDE);   \
}

#define init_tile_reg_and_src_with_buffer(tmm_num, src, buffer) \
{								\
  init_tile_src (tmm_num, &src, buffer);				\
  _tile_loadd (tmm_num, src.buf, _STRIDE);			\
}

/* Zero __tile src. It should be init first. */
void zero_tile_src (__tile *src)
{
  int i, j;

  for (i = 0; i < src->rows; i++)
    for (j = 0; j < src->colsb; j++)
      src->buf[i * src->colsb + j] = 0;
}

/* Compare tile config value with __tilecfg_u dst */
int check_tile_config (__tilecfg_u *src, __tilecfg_u *dst)
{
  size_t size = sizeof(__tilecfg);
  uint8_t *pa_src = (uint8_t *) src->a;
  uint8_t *pa_dst = (uint8_t *) dst->a;

  for (int i = 0; i < size; i++)
    if (pa_src[i] != pa_dst[i])
      return 0;

  return 1;
}

/* Compare tile register value with __tile variable */
int check_tile_register (__tile* ref, __tile* target)
{
  /* Tile register should be stored from tmm to
     memory and compare with emulation results. */
  int rows = target->rows;
  int colsb = target->colsb;
  int i, j;

  for (i = 0; i < rows; i++)
    for (j = 0; j < colsb; j++)
	if (ref->buf[i * colsb + j] != target->buf[i * colsb + j])
	    return 0;

  return 1;
}

void printOK(){
	printf("TMUL test PASS\n");
}

void print_notOK(){
	printf("TMUL test FAIL\n");
}

/* To verify whethe host has AMX support*/
int
valid_test ()
{
  unsigned int eax, ebx, ecx, edx;

/* Check XCR0 stat for AMX */
#define XSTATE_TILECFG          0x20000
#define XSTATE_TILEDATA         0x40000

  __cpuid (1, eax, ebx, ecx, edx);

  if (ecx & bit_OSXSAVE)
    {
      unsigned int xcrlow;

      __asm__ ("xgetbv"
	      : "=a" (xcrlow)
	      : "c" (0));

      if (xcrlow & (XSTATE_TILECFG | XSTATE_TILEDATA))
	{
	  __get_cpuid_count (7, 0, &eax, &ebx, &ecx, &edx);

	  if (edx & bit_AMX_TILE
#ifdef AMX_INT8
	    && (edx & bit_AMX_INT8)
#endif
#ifdef AMX_BF16
	    && (edx & bit_AMX_BF16)
#endif
	    )
	    return 1;
	}
    }

  return 0;
}

/*
int
main ()
{
  if (valid_test ())
    {
      DO_TEST ();
#ifdef DEBUG
      printf ("PASSED\n");
#endif
    }
#ifdef DEBUG
  else
    printf ("SKIPPED\n");
#endif

  return 0;
}
*/

#endif

