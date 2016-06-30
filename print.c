/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 20:58:26 by ppellegr          #+#    #+#             */
/*   Updated: 2014/04/23 20:58:27 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (e->multi_files && tmp && !e->is_arch)
	{
		ft_putendl("");
		ft_putstr(e->filename);
		ft_putendl(":");
	}
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
	ft_clean_sym(e);
	ft_clean_sects(e);
}
