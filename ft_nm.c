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

void			ft_print(int nsyms, int stroff, int symoff, void *mem)
{
	int				i;
	nlist_64		*n64;
	char			*strtab;
	char			*hex;
	t_list			*list;
	// char			type;
	// section_64		*s64;

	list = NULL;
	i = 0;
	// s64 = mem + sizeof(segcmd_64*);
	strtab = mem + stroff;
	n64 = mem + symoff;
	while (i < nsyms)
	{
		hex = ft_ltoahex(n64[i].n_value);
		ft_data(hex, strtab + n64[i].n_un.n_strx, list);
		/*if (n64[i].n_type & N_EXT)
		{
			hex = ft_ltoahex(n64[i].n_value);
			if (n64[i].n_value == 0)
			{
				hex[0] = ' ';
				ft_putstr("                ");
			}
			else
				ft_putstr("00000000");
			type = ft_symtype(n64[i], s64);
			ft_putstr(hex);
			ft_putstr(" ");
			ft_putchar(type);
			ft_putstr(" ");
			ft_putendl(strtab + n64[i].n_un.n_strx);
		}*/
		// s64 = (void*)s64 + sizeof(section_64);
		i++;
	}
}

void			ft_handle_64(void *mem)
{
	header			*h;
	loadcmd			*lc;
	int				i;
	symtab			*stc;

	i = 0;
	h = (header*)mem;
	lc = mem + sizeof(*h);
	while(i < (int)h->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			stc = (symtab*)lc;
			ft_print(stc->nsyms, stc->stroff, stc->symoff, mem);
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	} 
}

void			ft_nm(void *mem)
{
	unsigned int		magic_nb;

	magic_nb = *(int*)mem;
	if (magic_nb == MH_MAGIC_64)
		ft_handle_64(mem);
}



int				main(int argc, char **argv)
{
	int				fd;
	size_t			size;
	void			*mem;

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
		if (!(mem = ft_get_file(size, fd)))
		{	
			ft_putstr_fd("Error while reading memory\n", 2);
			return (-1);
		}
		ft_nm(mem);
		if (munmap(mem, size) < 0)
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
