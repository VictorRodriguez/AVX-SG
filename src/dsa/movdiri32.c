/* { dg-do run { target movdir } } */
/* { dg-options "-mmovdiri -O2" } */

#include <x86intrin.h>
#include <tap.h>

unsigned int dest = -1;

int movdiri_test(){

	if (!__builtin_cpu_supports ("movdiri"))
		return 1;

	_directstoreu_u32 (&dest, 0xbadbeef);

	if (dest != 0xbadbeef)
		abort ();

	return 0;
}

int main () {
	plan(1);
	ok(!movdiri_test(),"Check movdir_test");
	return 0;
}
