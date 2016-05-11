#include "ft_nm.h"
#include <stdio.h>

void	ft_swap_data(t_sym **sym0, t_sym **sym1)
{
	t_sym	*tmp;

	tmp = *sym0;
	*sym0 = *sym1;
	*sym1 = tmp;
}

void	ft_sort(t_list **sym)
{
	t_list	*tmp;
	t_sym	*sym_curr;
	t_sym	*sym_next;
	int		i;

	tmp = *sym;
	while (tmp)
	{
		sym_curr = ((t_sym*)(tmp->data));
		if (tmp->next)
		{
			sym_next = ((t_sym*)(tmp->next->data));
			i = 0;
			while (sym_curr->name[i] != '\0' && sym_next->name[i] != '\0')
			{	
				if (sym_curr->name[i] < sym_next->name[i])
					break ;
				if (sym_curr->name[i] > sym_next->name[i])
				{
					ft_swap_data(((t_sym**)&(tmp->data)), ((t_sym**)&(tmp->next->data)));
					tmp = *sym;
					break ;
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
}