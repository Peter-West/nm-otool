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
	// t_arch		*arch;
	void		*start;
	unsigned int check_ran_off;

	i = 0;
	check_ran_off = -1;
	start = (void*)e->mem;
	hdr = (void*)e->mem + SARMAG;
	size = *((int *)((void*)hdr + sizeof(arch_hdr) + get_size_arch(hdr->ar_name)));
	size = size / sizeof(ranlib);
	ran = (void*)hdr + sizeof(arch_hdr) + get_size_arch(hdr->ar_name) + 4;
	while (i < size)
	{
		if (ran[i].ran_off != check_ran_off)
		{
			hdr_name = (void*)start + ran[i].ran_off;
			// arch = (t_arch*)malloc(sizeof(t_arch));
			e->mem = (void*)hdr_name + sizeof(arch_hdr) + get_size_arch(hdr->ar_name);
			ft_putstr("\n");
			ft_putstr(e->filename);
			ft_putstr("(");
			ft_putstr(get_name_arch(hdr_name->ar_name));
			ft_putendl("):");
			ft_nm(e);
		}
		check_ran_off = ran[i].ran_off;
		i++;
	}
	e->mem = start;
}
