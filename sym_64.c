/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sym_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 20:58:26 by ppellegr          #+#    #+#             */
/*   Updated: 2014/04/23 20:58:27 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_sym			*addr_64(t_env *e, t_nlist_64 *n64, int i, char *strtab)
{
	char			*hex;
	t_sym			*sym;

	sym = (t_sym*)malloc(sizeof(t_sym));
	hex = ft_ltoahex(n64[i].n_value);
	sym->symtype = ft_symtype_64(n64[i].n_type, n64[i], e);
	sym->name = strtab + n64[i].n_un.n_strx;
	if (n64[i].n_value == 0)
	{
		if (sym->symtype == 'U')
		{
			hex[0] = ' ';
			sym->addr = ft_strjoin("               ", hex);
		}
		else
		{
			hex[0] = '0';
			sym->addr = ft_strjoin("000000000000000", hex);
		}
	}
	else
		sym->addr = ft_strjoin(zero_str_64(hex), hex);
	return (sym);
}

void			mngsym_64(t_env *e, t_sym **sym)
{
	if ((*sym)->symtype != '-')
		add_to_list(&e->sym, *sym);
	else
	{
		free(*sym);
		*sym = NULL;
	}
}

void			add_sym_64(t_env *e)
{
	unsigned int	i;
	t_nlist_64		*n64;
	t_sym			*sym;
	char			*strtab;
	char			*nam;

	i = 0;
	strtab = e->mem + e->stc->stroff;
	n64 = e->mem + e->stc->symoff;
	while (i < e->stc->nsyms)
	{
		nam = strtab + n64[i].n_un.n_strx;
		if (nam[0] != 0 && n64[i].n_type < 100)
		{
			sym = addr_64(e, n64, i, strtab);
			mngsym_64(e, &sym);
		}
		i++;
	}
	ft_sort(&e->sym);
}
