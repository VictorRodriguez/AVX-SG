/* { dg-do run { target { movdir && { ! ia32 } } } } */
/* { dg-options "-mmovdiri -O2" } */

#include <x86intrin.h>
#include <tap.h>

unsigned long long int dest = -1LL;

int movdir64_test() {
  if (!__builtin_cpu_supports ("movdiri"))
    return 1;

  _directstoreu_u64 (&dest, 0x12345678badbeef);

  if (dest != 0x12345678badbeef)
    abort ();

  return 0;
}

int main () {
	plan(1);
	ok(!movdir64_test(),"Check movdir64_test");
	return 0;
}
