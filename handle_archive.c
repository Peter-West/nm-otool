#include "ft_nm.h"
#include <stdio.h>

int				get_size_arch(char *name)
{
	char		*size;

	size = ft_strchr(name, '/') + 1;
	return (ft_atoi(size));
}

char			*get_name_arch(char *name)
{
	return (ft_strstr(name, ARFMAG) + ft_strlen(ARFMAG));
}

void			ft_handle_arch(t_env *e)
{
	arch_hdr	*hdr;
	arch_hdr	*hdr_name;
	ranlib		*ran;
	int			size;
	int			i;

	i = 0;
	hdr = (void*)e->mem + SARMAG;
	size = *((int *)((void*)hdr + sizeof(arch_hdr) + get_size_arch(hdr->ar_name)));
	size = size / sizeof(ranlib);
	ran = (void*)hdr + sizeof(arch_hdr) + get_size_arch(hdr->ar_name) + 4;
	//printf("size : %ld\n", size);
	printf("sizeof(arch_hdr) : %lu, sizeof(*hdr), %lu\n", sizeof(arch_hdr), sizeof(*hdr));
	while (i < size)
	{
		hdr_name = (void*)e->mem + ran[i].ran_off;
		printf("%d.ran_off : %u, ran_strx : %s, %s\n", i, ran[i].ran_off, ft_ltoahex(ran[i].ran_un.ran_strx)
			, get_name_arch(hdr_name->ar_name));

		i++;
	}
}