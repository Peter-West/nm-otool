/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 20:58:26 by ppellegr          #+#    #+#             */
/*   Updated: 2014/04/23 20:58:27 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void			ft_nm(t_env *e)
{
	unsigned int		magic_nb;

	magic_nb = *(unsigned int*)e->mem;
	if (magic_nb == FAT_MAGIC)
		ft_handle_fat(e, 0);
	else if (magic_nb == FAT_CIGAM)
		ft_handle_fat(e, 1);
	else if (!ft_strncmp(e->mem, ARMAG, SARMAG))
		ft_handle_arch(e);
	else if (magic_nb == MH_MAGIC_64)
		ft_handle_64(e);
	else if (magic_nb == MH_MAGIC)
		ft_handle_32(e);
	else
		ft_putstr("The file was not recognized as a valid object file.\n");
	ft_print(e);
}

int				open_file(t_env *e, char *name)
{
	if ((e->fd = open(name, O_RDONLY)) == -1)
	{
		ft_putstr_fd("File opening failed\n", 2);
		return (-1);
	}
	if ((e->size = ft_get_size(e->fd)) == EXIT_FAILURE)
	{
		ft_putstr_fd("Error getting size\n", 2);
		return (-1);
	}
	if (!(e->mem = ft_get_file(e->size, e->fd)))
	{
		ft_putstr_fd("Error while reading memory\n", 2);
		return (-1);
	}
	return (0);
}

int				close_file(t_env *e)
{
	if (munmap(e->mem, e->size) < 0)
	{
		ft_putstr_fd("Munmap error\n", 2);
		return (-1);
	}
	if (close(e->fd) == -1)
	{
		ft_putstr_fd("Close file error\n", 2);
		return (-1);
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_env			e;
	int				i;

	e.sym = NULL;
	e.sects = NULL;
	e.arch = NULL;
	e.is_arch = 0;
	if (argc > 2)
		e.multi_files = 1;
	else
		e.multi_files = 0;
	i = 1;
	while (i < argc)
	{
		if (open_file(&e, argv[i]) == -1)
			return (-1);
		e.filename = argv[i];
		ft_nm(&e);
		if (close_file(&e) == -1)
			return (-1);
		i++;
	}
	if (argc < 1)
		ft_putstr_fd("Usage: ./ft_nm [filename]\n", 2);
	return (0);
}
