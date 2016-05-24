#include "ft_nm.h"

void			ft_clean_sym(t_env *e)
{
	t_list		*tmp;
	t_list		*prev;

	tmp = e->sym;
	while (tmp)
	{
		if (((t_sym*)(tmp->data))->addr)
			free(((t_sym*)(tmp->data))->addr);
		// if (((t_sym*)(tmp->data))->name)
		// 	free(((t_sym*)(tmp->data))->name);
		free(((t_sym*)(tmp->data)));
		tmp->data = NULL;
		prev = tmp;
		tmp = tmp->next;
		if (prev)
			free(prev);
		prev = NULL;
	}
	if (e->sym)
		e->sym = NULL;
}

void			ft_clean_sects(t_env *e)
{
	t_list		*tmp;
	t_list		*prev;
	
	tmp = e->sects;
	while (tmp)
	{
		// if (((t_sect*)(tmp->data))->name)
			// free(((t_sect*)(tmp->data))->name);
		free(((t_sect*)(tmp->data)));
		tmp->data = NULL;
		prev = tmp;
		tmp = tmp->next;
		if (prev)
			free(prev);
		prev = NULL;
	}
	if (e->sects)
		e->sects = NULL;
}

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
	// ft_clean_sym(e);
	// ft_clean_sects(e);
}