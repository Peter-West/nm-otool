/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtype.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/26 18:36:28 by ppellegr          #+#    #+#             */
/*   Updated: 2014/04/26 18:36:29 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <stdio.h>

void			ft_fill_list(t_list **list, void *data)
{
	t_list		*new;
	t_list		*tmp;
	new = (t_list*)malloc(sizeof(t_list));
	new->data = data;
	new->next = NULL;
	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/*
char			ft_symtype(nlist_64 n64, section_64 *s64)
{
	char				type;

	type = 'T';
	// if (n64.n_type == N_STAB)

	if (s64 == NO_SECT)
		return (type);
	if (ft_strequ(s64->segname, "__TEXT"))
	{
		if (ft_strequ(s64->sectname, "__text"))
			type = 'T';
		else if (ft_strequ(s64->sectname, "__cstring"))
			type = 'S';
		else if (ft_strequ(s64->sectname, "__eh_frame"))
			type = 'S';
		else if (ft_strequ(s64->sectname, "__const"))
			type = 'S';
	}
	else if (ft_strequ(s64->segname, "__DATA"))
		type = 'D';
	else if (ft_strequ(s64->segname, "__IMPORT"))
		type = 'I';
	if (!(n64.n_type & N_EXT))
		type += 32;
	return (type);
}

char		secto(t_lsection *sec, unsigned int n_sect)
{
	t_section	*tmp;

	tmp = sec->first;
	while (tmp)
	{
		if (tmp->nb == n_sect)
		{
			if (!ft_strcmp(tmp->name, SECT_DATA))
				return ('D');
			else if (!ft_strcmp(tmp->name, SECT_BSS))
				return ('B');
			else if (!ft_strcmp(tmp->name, SECT_TEXT))
				return ('T');
			else
				return ('S');
		}
		tmp = tmp->next;
	}
	return ('S');
}

char	typing(unsigned int type, unsigned int n_sect, t_ls *sec, int addr)
{
	char	ret;

	ret = '?';
	if ((type & N_TYPE) == N_UNDF)
	{
		if (addr)
			ret = 'C';
		else
			ret = 'U';
	}
	else if ((type & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((type & N_TYPE) == N_PBUD)
		ret = 'U';
	else if ((type & N_TYPE) == N_SECT)
		ret = secto(sec, n_sect);
	else if ((type & N_TYPE) == N_INDR)
		ret = 'I';
	if ((type & N_STAB) != 0)
		ret = 'Z';
	if ((type & N_EXT) == 0 && ret != '?')
		ret += 32;
	return (ret);
}*/
