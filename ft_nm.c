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
#include <stdio.h>

off_t			ft_get_size(int fd)
{
	struct stat		buf;
	
	if (fstat(fd, &buf) < 0)
		return (EXIT_FAILURE);
	return (buf.st_size);
}

void			*ft_get_file(size_t size, int fd)
{
	void			*read;

	if ((read = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (NULL);
	return (read);
}



void			add_sym(t_env *e)
{
	unsigned int	i;
	nlist_64		*n64;
	char			*strtab;
	char			*hex;
	// char			type;
	section_64		*s64;
	t_sym			*sym;

	i = 0;
	s64 = e->mem + sizeof(segcmd_64*);
	strtab = e->mem + e->stc->stroff;
	n64 = e->mem + e->stc->symoff;
	printf("nsyms : %d\n", e->stc->nsyms);
	while (i < e->stc->nsyms)
	{
		if (n64[i].n_type & N_EXT)
		{
			sym = (t_sym*)malloc(sizeof(t_sym));
			hex = ft_ltoahex(n64[i].n_value);
			if (n64[i].n_value == 0)
			{
				hex[0] = ' ';
				sym->addr = ft_strjoin("                ", hex);
			}
			else
				sym->addr = ft_strjoin("00000000", hex);
			sym->symtype = ft_symtype(n64[i].n_type, n64[i], s64);
			sym->name = strtab + n64[i].n_un.n_strx;
			add_to_list(&e->sym, sym);
		}
		s64 = (void*)s64 + sizeof(section_64);
		i++;
	}
	ft_sort(&e->sym);
}
void			ft_handle_64(t_env *e)
{
	int				i;
	// segcmd_64		*sg64;

	i = 0;
	e->h = (header*)e->mem;
	e->lc = e->mem + sizeof(*e->h);
	while(i < (int)e->h->ncmds)
	{
		if (e->lc->cmd == LC_SYMTAB)
		{
			e->stc = (symtab*)e->lc;
			add_sym(e);
		}
	/*	else if (lc->cmd == LC_SEGMENT64)
		{
			sg64 = (segcmd_64*)lc;
			printf("nsec: %d\n", sg64->nsects);

		}*/
		e->lc = (void*)e->lc + e->lc->cmdsize;
		i++;
	} 
}

void			ft_nm(t_env *e)
{
	unsigned int		magic_nb;

	magic_nb = *(int*)e->mem;
	if (magic_nb == MH_MAGIC_64)
		ft_handle_64(e);
	else
		printf("not managed yet\n");
}

// int			ft_error_file_opening()
// {
// 	return ()
// }



int				main(int argc, char **argv)
{
	int				fd;
	size_t			size;
	// void			*mem;
	t_env			e;

	e.sym = NULL;
	if (argc > 1)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
		{
			ft_putstr_fd("File opening failed\n", 2);
			return (-1);
		}
		if ((size = ft_get_size(fd)) == EXIT_FAILURE)
		{
			ft_putstr_fd("Error getting size\n", 2);
			return (-1);
		}
		if (!(e.mem = ft_get_file(size, fd)))
		{	
			ft_putstr_fd("Error while reading memory\n", 2);
			return (-1);
		}
		ft_nm(&e);
		ft_print(&e);
		if (munmap(e.mem, size) < 0)
		{
			ft_putstr_fd("Munmap error\n", 2);
			return (-1);
		}
		if (close(fd) == -1)
		{
			ft_putstr_fd("Close file error\n", 2);
			return (-1);
		}
	}
	else
		ft_putstr_fd("Usage: ./ft_nm [filename]\n", 2);
	return (0);
}
