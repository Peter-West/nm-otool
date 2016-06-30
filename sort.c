/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 20:58:26 by ppellegr          #+#    #+#             */
/*   Updated: 2014/04/23 20:58:27 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	ft_swap_data(t_sym **sym0, t_sym **sym1)
{
	t_sym	*tmp;

	tmp = *sym0;
	*sym0 = *sym1;
	*sym1 = tmp;
}

int		loop_sort(t_list **sym, t_list **tmp)
{
	int		i;
	t_sym	*sym_next;
	t_sym	*sym_curr;

	i = 0;
	sym_curr = ((t_sym*)((*tmp)->data));
	sym_next = ((t_sym*)((*tmp)->next->data));
	while (sym_curr->name[i] != '\0' || sym_next->name[i] != '\0')
	{
		if (sym_curr->name[i] < sym_next->name[i])
			return (0);
		if (sym_curr->name[i] > sym_next->name[i])
		{
			ft_swap_data(((t_sym**)&((*tmp)->data)),
				((t_sym**)&((*tmp)->next->data)));
			*tmp = *sym;
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_sort(t_list **sym)
{
	t_list	*tmp;
	int		restart;

	tmp = *sym;
	while (tmp)
	{
		restart = 0;
		if (tmp->next)
			restart = loop_sort(sym, &tmp);
		if (!restart)
			tmp = tmp->next;
	}
}
