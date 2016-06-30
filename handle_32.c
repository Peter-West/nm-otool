/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 20:58:26 by ppellegr          #+#    #+#             */
/*   Updated: 2014/04/23 20:58:27 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void			ft_handle_32(t_env *e)
{
	int				i;
	int				nb;

	i = 0;
	nb = 1;
	e->h = (t_header*)e->mem;
	e->lc = (void*)e->mem + sizeof(*e->h);
	while (i < (int)e->h->ncmds)
	{
		if (e->lc->cmd == LC_SEGMENT)
		{
			e->sg = (t_segcmd*)e->lc;
			nb = get_sects(e, nb);
		}
		if (e->lc->cmd == LC_SYMTAB)
		{
			e->stc = (t_symtab*)e->lc;
			add_sym(e);
		}
		e->lc = (void*)e->lc + e->lc->cmdsize;
		i++;
	}
}

int				get_sects(t_env *e, int nb)
{
	unsigned int			i;
	t_section				*s;
	t_sect					*sec;

	i = 0;
	s = (void*)e->sg + sizeof(*e->sg);
	while (i < e->sg->nsects)
	{
		sec = (t_sect*)malloc(sizeof(t_sect));
		sec->name = s->sectname;
		sec->nb = nb++;
		add_to_list(&e->sects, sec);
		s = (void*)s + sizeof(*s);
		i++;
	}
	return (nb);
}

char			*zero_str(char *str)
{
	int			to_add;
	char		*ret;
	int			i;

	i = 0;
	to_add = 8 - ft_strlen(str);
	ret = (char*)malloc(sizeof(char) * to_add + 1);
	while (i < to_add)
		ret[i++] = '0';
	ret[i] = 0;
	return (ret);
}
