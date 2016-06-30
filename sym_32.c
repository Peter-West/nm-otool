/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sym_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 20:58:26 by ppellegr          #+#    #+#             */
/*   Updated: 2014/04/23 20:58:27 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_sym			*addr_32(t_env *e, t_nlist_32 *n, int i, char *strtab)
{
	char			*hex;
	t_sym			*sym;

	sym = (t_sym*)malloc(sizeof(t_sym));
	hex = ft_ltoahex(n[i].n_value);
	sym->symtype = ft_symtype(n[i].n_type, n[i], e);
	sym->name = strtab + n[i].n_un.n_strx;
	if (n[i].n_value == 0)
	{
		if (sym->symtype == 'U')
		{
			hex[0] = ' ';
			sym->addr = ft_strjoin("       ", hex);
		}
		else
		{
			hex[0] = '0';
			sym->addr = ft_strjoin("0000000", hex);
		}
	}
	else
		sym->addr = ft_strjoin(zero_str(hex), hex);
	return (sym);
}

void			mngsym_32(t_env *e, t_sym **sym)
{
	if ((*sym)->symtype != '-')
		add_to_list(&e->sym, *sym);
	else
	{
		free(*sym);
		*sym = NULL;
	}
}

void			add_sym(t_env *e)
{
	unsigned int	i;
	t_nlist_32		*n;
	t_sym			*sym;
	char			*strtab;
	char			*nam;

	i = 0;
	strtab = e->mem + e->stc->stroff;
	n = e->mem + e->stc->symoff;
	while (i < e->stc->nsyms)
	{
		nam = strtab + n[i].n_un.n_strx;
		if (nam[0] != 0 && n[i].n_type < 100)
		{
			sym = addr_32(e, n, i, strtab);
			mngsym_32(e, &sym);
		}
		i++;
	}
	ft_sort(&e->sym);
}
