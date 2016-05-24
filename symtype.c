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

char			ft_symtype(char type, nlist_64 n64, t_env *e)
{
	unsigned char	c;

	c = '?';
	// printf("\nn_sect : %d\n", n64.n_sect);
	// printf("name ? %s\n", s64[n64.n_sect].segname);
	// printf("name ? %s\n", s64[n64.n_sect].sectname);
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
/*	if (s64 == NO_SECT)
		return (type);
	// printf("s64[n_sect].sectname : %s\n", s64[n_sect].sectname);
	// printf("s64[n_sect].segname : %s\n", s64[n_sect].segname);
	if (ft_strcmp(s64[n_sect].sectname, SECT_TEXT) == 0)
		printf("***Yo\n");
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
		type += 32;*/
	return (c);
}
/*
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
}*/
/*
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
