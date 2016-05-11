#include "ft_nm.h"

void			ft_print(t_env *e)
{
	t_sym		*sym;
	t_list		*tmp;

	tmp = e->sym;
	while (tmp)
	{
		sym = ((t_sym*)(tmp->data));
		ft_putstr(sym->addr);
		ft_putstr(" ");
		ft_putchar(sym->symtype);
		ft_putstr(" ");
		ft_putendl(sym->name);
		tmp = tmp->next;
	}
}