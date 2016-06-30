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

char			match_sect(char c, t_env *e, uint8_t s)
{
	t_list		*tmp;
	t_sect		*sect;

	tmp = e->sects;
	while (tmp)
	{
		sect = ((t_sect*)(tmp->data));
		if (s == sect->nb)
		{
			if (ft_strcmp(sect->name, SECT_TEXT) == 0)
				c = 't';
			else if (ft_strcmp(sect->name, SECT_DATA) == 0)
				c = 'd';
			else if (ft_strcmp(sect->name, SECT_BSS) == 0)
				c = 'b';
			else
				c = 's';
		}
		tmp = tmp->next;
	}
	return (c);
}

char			ft_symtype_64(char type, t_nlist_64 n64, t_env *e)
{
	unsigned char	c;

	c = '?';
	if (type & N_STAB)
		c = '-';
	else if ((type & N_TYPE) == N_UNDF)
	{
		c = 'u';
		if (n64.n_value != 0)
			c = 'c';
	}
	else if ((type & N_TYPE) == N_PBUD)
		c = 'u';
	else if ((type & N_TYPE) == N_ABS)
		c = 'a';
	else if ((type & N_TYPE) == N_SECT)
	{
		c = match_sect(c, e, n64.n_sect);
	}
	else if ((type & N_TYPE) == N_INDR)
		c = 'i';
	if ((n64.n_type & N_EXT) && c != '?')
		c = ft_toupper(c);
	return (c);
}

char			ft_symtype(char type, t_nlist_32 n, t_env *e)
{
	unsigned char	c;

	c = '?';
	if (type & N_STAB)
		c = '-';
	else if ((type & N_TYPE) == N_UNDF)
	{
		c = 'u';
		if (n.n_value != 0)
			c = 'c';
	}
	else if ((type & N_TYPE) == N_PBUD)
		c = 'u';
	else if ((type & N_TYPE) == N_ABS)
		c = 'a';
	else if ((type & N_TYPE) == N_SECT)
	{
		c = match_sect(c, e, n.n_sect);
	}
	else if ((type & N_TYPE) == N_INDR)
		c = 'i';
	if ((n.n_type & N_EXT) && c != '?')
		c = ft_toupper(c);
	return (c);
}
