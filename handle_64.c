/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 20:58:26 by ppellegr          #+#    #+#             */
/*   Updated: 2014/04/23 20:58:27 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void			ft_handle_64(t_env *e)
{
	int				i;
	int				nb;

	i = 0;
	nb = 1;
	e->h64 = (t_header_64*)e->mem;
	e->lc = e->mem + sizeof(*e->h64);
	while (i < (int)e->h64->ncmds)
	{
		if (e->lc->cmd == LC_SEGMENT_64)
		{
			e->sg64 = (t_segcmd_64*)e->lc;
			nb = get_sects64(e, nb);
		}
		if (e->lc->cmd == LC_SYMTAB)
		{
			e->stc = (t_symtab*)e->lc;
			add_sym_64(e);
		}
		e->lc = (void*)e->lc + e->lc->cmdsize;
		i++;
	}
}

int				get_sects64(t_env *e, int nb)
{
	unsigned int			i;
	t_section_64			*s64;
	t_sect					*sec;

	i = 0;
	s64 = (void*)e->sg64 + sizeof(*e->sg64);
	while (i < e->sg64->nsects)
	{
		sec = (t_sect*)malloc(sizeof(t_sect));
		sec->name = s64->sectname;
		sec->nb = nb++;
		add_to_list(&e->sects, sec);
		s64 = (void*)s64 + sizeof(*s64);
		i++;
	}
	return (nb);
}

char			*zero_str_64(char *str)
{
	int			to_add;
	char		*ret;
	int			i;

	i = 0;
	to_add = 16 - ft_strlen(str);
	ret = (char*)malloc(sizeof(char) * to_add + 1);
	while (i < to_add)
		ret[i++] = '0';
	ret[i] = 0;
	return (ret);
}
