/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arch_ot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 22:06:58 by ppellegr          #+#    #+#             */
/*   Updated: 2014/04/27 22:06:58 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

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

void			arch_loop(t_env *e, t_ranlib *ran, t_arch_hdr *hdr, int s)
{
	int				i;
	unsigned int	check_ran_off;
	t_arch_hdr		*hdr_name;
	void			*start;

	i = 0;
	check_ran_off = -1;
	start = (void*)e->mem;
	while (i < s)
	{
		if (ran[i].ran_off != check_ran_off)
		{
			hdr_name = (void*)start + ran[i].ran_off;
			e->mem = (void*)hdr_name + sizeof(t_arch_hdr) +
				get_size_arch(hdr->ar_name);
			ft_putstr(e->name);
			ft_putstr("(");
			ft_putstr(get_name_arch(hdr_name->ar_name));
			ft_putendl("):");
			ft_otool(e);
		}
		check_ran_off = ran[i].ran_off;
		i++;
	}
}

void			ft_handle_arch(t_env *e)
{
	t_arch_hdr		*hdr;
	t_ranlib		*ran;
	void			*start;
	int				size;
	unsigned int	check_ran_off;

	e->archive = 1;
	check_ran_off = -1;
	start = (void*)e->mem;
	hdr = (void*)e->mem + SARMAG;
	size = *((int *)((void*)hdr + sizeof(t_arch_hdr) +
		get_size_arch(hdr->ar_name)));
	size = size / sizeof(t_ranlib);
	ran = (void*)hdr + sizeof(t_arch_hdr) + get_size_arch(hdr->ar_name) + 4;
	ft_putstr("Archive : ");
	ft_putendl(e->name);
	arch_loop(e, ran, hdr, size);
	e->mem = start;
}
