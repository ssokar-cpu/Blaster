#ifndef FT_VIRUS_H
# define FT_VIRUS_H

#include <stdint.h>
#include <stdio.h>

typedef struct	s_header
{
		uint32_t	size;
		void		*address;
		unsigned char	key[16];
			
}		__attribute__((packed))t_header;

void	Blaster_start( void );
void	Main_Blaster( void );


/* -- Loader -- */
/* -- For Encrypt -- */
void 	loader( void );
t_header	*_GET_HEADER_VIRUSE( void );

void	Blaster_end( void );
#endif
