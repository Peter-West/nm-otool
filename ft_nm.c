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
	t_sym			*sym;

	i = 0;
	strtab = e->mem + e->stc->stroff;
	n64 = e->mem + e->stc->symoff;
	while (i < e->stc->nsyms)
	{
		char *nam;
		nam = strtab + n64[i].n_un.n_strx;

		if (nam[0] != 0 && n64[i].n_type < 100)
		{
			sym = (t_sym*)malloc(sizeof(t_sym));
			hex = ft_ltoahex(n64[i].n_value);
			// printf("hex : %s\n", hex);
			sym->symtype = ft_symtype(n64[i].n_type, n64[i], e);
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
				sym->addr = ft_strjoin("0000000", hex);
			if (sym->symtype != '-')
				add_to_list(&e->sym, sym);
			else
			{
				free(sym);
				sym = NULL;
			}
		}
		i++;
	}
	ft_sort(&e->sym);
}

int			get_sects(t_env *e,int nb)
{
	unsigned int			i;
	section_64				*s64;
	t_sect					*sec;
	
	i = 0;
	s64 = (void*)e->sg64 + sizeof(*e->sg64);
	while (i < e->sg64->nsects)
	{
		sec = (t_sect*)malloc(sizeof(t_sect));
		sec->name = s64->sectname;
		sec->nb = nb++;
		add_to_list(&e->sects, sec);
		s64 = (void*)s64 + sizeof(*s64);
		i++;
	}
	return (nb);
}

void			ft_handle_64(t_env *e)
{
	int				i;
	int						nb = 1;

	i = 0;
	e->h = (header*)e->mem;
	e->lc = e->mem + sizeof(*e->h);
	while(i < (int)e->h->ncmds)
	{
		
		if (e->lc->cmd == LC_SEGMENT_64)
		{
			e->sg64 = (segcmd_64*)e->lc;
			nb = get_sects(e, nb);
		}
		if (e->lc->cmd == LC_SYMTAB)
		{
			e->stc = (symtab*)e->lc;
			add_sym(e);
		}
		
		e->lc = (void*)e->lc + e->lc->cmdsize;
		i++;
	}
}

void			ft_handle_32(t_env *e)
{
	printf("header 32");
	(void)e;
}

void			ft_handle_FAT(t_env *e)
{
	printf("Fat HEADER\n");
	(void)e;
}

void			ft_cigam(t_env *e)
{
	(void)e;
	printf("CIGAM\n");
}

void			ft_cigam_64(t_env *e)
{
	(void)e;
	printf("CIGAM 64\n");

}

void			ft_FAT_cigam(t_env *e)
{
	(void)e;
	printf("CIGAM\n");

}

void			ft_nm(t_env *e)
{
	unsigned int		magic_nb;

	magic_nb = *(unsigned int*)e->mem;
	// printf("magic_nb : %u\n", magic_nb);
	// printf("MH_MAGIC_64 %u\n", MH_MAGIC_64);
	// printf("MH_MAGIC %u\n", MH_MAGIC);
	// printf("FAT_MAGIC %u\n", FAT_MAGIC);
	// printf("FAT_CIGAM %u\n", FAT_CIGAM);
	 
	if (magic_nb == FAT_MAGIC)
		ft_handle_FAT(e);
	else if (magic_nb == FAT_CIGAM)
		ft_FAT_cigam(e);
	else if (!ft_strncmp(e->mem, ARMAG, SARMAG))
		ft_handle_arch(e);
	else if (magic_nb == MH_CIGAM)
		ft_cigam(e);
	else if (magic_nb == MH_CIGAM_64)
		ft_cigam_64(e);
	else if (magic_nb == MH_MAGIC_64)
		ft_handle_64(e);
	else if (magic_nb == MH_MAGIC)
		ft_handle_32(e);
	else
		printf("not handled yet\n");
	ft_print(e);
}

int				main(int argc, char **argv)
{
	int				fd;
	size_t			size;
	t_env			e;

	e.sym = NULL;
	e.sects = NULL;
	e.arch = NULL;
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
		e.filename = argv[1];
		ft_nm(&e);
		// ft_print(&e);
		if (munmap(e.mem, size) < 0)
		{
			ft_putstr_fd("Munmap error\n", 2);
			perror("munmap");
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
