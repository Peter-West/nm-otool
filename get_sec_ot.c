/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sec_ot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 22:06:58 by ppellegr          #+#    #+#             */
/*   Updated: 2014/04/27 22:06:58 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

t_section_64	*get_section_text_64(t_segcmd_64 *sg64, t_env *e)
{
	uint8_t				i;
	struct section_64	*s64;

	i = 0;
	s64 = (struct section_64*)(sg64 + 1);
	while (i < sg64->nsects)
	{
		if (ft_strequ(s64->segname, "__TEXT")
			&& ft_strequ(s64->sectname, "__text"))
		{
			if (e->archive != 1)
			{
				ft_putstr(e->name);
				ft_putendl(":");
			}
			ft_putendl("(__TEXT,__text) section");
			print_64(s64, e->mem);
			return (s64);
		}
		s64 += 1;
		++i;
	}
	return (NULL);
}

t_section		*get_section_text_32(t_segcmd *sg, t_env *e)
{
	uint8_t				i;
	struct section		*s;

	i = 0;
	s = (struct section*)(sg + 1);
	while (i < sg->nsects)
	{
		if (ft_strequ(s->segname, "__TEXT")
			&& ft_strequ(s->sectname, "__text"))
		{
			if (e->archive != 1)
			{
				ft_putstr(e->name);
				ft_putendl(":");
			}
			ft_putendl("(__TEXT,__text) section");
			print_32(s, e->mem);
			return (s);
		}
		s += 1;
		++i;
	}
	return (NULL);
}
