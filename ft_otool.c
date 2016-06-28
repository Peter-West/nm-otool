/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 22:06:58 by ppellegr          #+#    #+#             */
/*   Updated: 2014/04/27 22:06:58 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"
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

void		print_addr(uint64_t addr, int base)
{
	int		i;
	char	hex[]="0123456789abcdef";
	char	offset[base + 1];

	i = base - 1;
	offset[base] = '\0';
	while (i >= 0)
	{
		offset[i] = hex[addr % base];
		addr /= base;
		i--;
	}
	ft_putstr(offset);
	ft_putstr(" ");
}

void		print_data(unsigned char addr, int base)
{
	int		i;
	char	hex[]="0123456789abcdef";
	char	offset[base + 1];

	i = base - 1;
	offset[base] = '\0';
	while (i >= 0)
	{
		offset[i] = hex[addr % 16];
		addr /= 16;
		i--;
	}
	write(1, offset, base);
	ft_putstr(" ");
}

void		print_64(section_64 *s64, char *mem)
{
	uint64_t		i;
	uint64_t		add;
	uint32_t		off;
	int				j;

	i = 0;
	add = s64->addr;
	off = s64->offset;
	while (i < s64->size)
	{
		print_addr(add, 16);
		j = 0;
		while (j < 16 && i + j < s64->size)
		{
			print_data(*(mem + off), 2);
			off++;
			j++;
		}
		ft_putendl("");
		add += j;
		i += j;
	}
}

section_64	*get_section_text(segcmd_64 *sg64, t_env *e)
{
	uint8_t				i;
	struct section_64	*s64;

	i = 0;
	s64 = (struct section_64*)(sg64 + 1);
	
	while (i < sg64->nsects)
	{
		if (ft_strequ(s64->segname, "__TEXT") && ft_strequ(s64->sectname, "__text"))
		{
			if (e->archive != 1)
			{
				ft_putstr(e->name);
				ft_putendl(":");
			}
			ft_putendl("(__TEXT,__text) section");
			print_64(s64, e->mem);
			return (s64);
		}
		s64 += 1;
		++i;
	}
	return (NULL);
}

int				get_size_arch(char *name)
{
	char		*size;

	size = ft_strchr(name, '/') + 1;
	return (ft_atoi(size));
}

char			*get_name_arch(char *name)
{
	return (ft_strstr(name, ARFMAG) + ft_strlen(ARFMAG));
}

void			ft_handle_arch(t_env *e)
{
	arch_hdr	*hdr;
	arch_hdr	*hdr_name;
	ranlib		*ran;
	void		*start;
	int			i;
	int			size;
	unsigned int check_ran_off;

	i = 0;
	e->archive = 1;
	check_ran_off = -1;
	start = (void*)e->mem;
	hdr = (void*)e->mem + SARMAG;
	size = *((int *)((void*)hdr + sizeof(arch_hdr) + get_size_arch(hdr->ar_name)));
	size = size / sizeof(ranlib);
	ran = (void*)hdr + sizeof(arch_hdr) + get_size_arch(hdr->ar_name) + 4;
	ft_putstr("Archive : ");
	ft_putendl(e->name);
	while (i < size)
	{
		if (ran[i].ran_off != check_ran_off)
		{
			hdr_name = (void*)start + ran[i].ran_off;
			e->mem = (void*)hdr_name + sizeof(arch_hdr) + get_size_arch(hdr->ar_name);
			// ft_putstr("\n");
			ft_putstr(e->name);
			ft_putstr("(");
			ft_putstr(get_name_arch(hdr_name->ar_name));
			ft_putendl("):");
			ft_otool(e);
		}
		check_ran_off = ran[i].ran_off;
		i++;
	}
	e->mem = start;
}

void			ft_handle_64(t_env *e)
{
	header_64		*h;
	loadcmd			*lc;
	segcmd_64		*sg64;
	int				i;

	i = 0;
	h = (header_64*)e->mem;
	lc = e->mem + sizeof(*h);
	sg64 = (segcmd_64*)lc;
	while(i < (int)h->ncmds)
	{
		if (sg64[i].cmd == LC_SEGMENT_64)
		{
			get_section_text(&sg64[i], e);
		}
		i++;
	}
}

void			ft_otool(t_env *e)
{
	unsigned int		magic_nb;

	magic_nb = *(int*)e->mem;
	if (magic_nb == MH_MAGIC_64)
		ft_handle_64(e);
	else if (!ft_strncmp(e->mem, ARMAG, SARMAG))
		ft_handle_arch(e);
	else if (magic_nb == MH_CIGAM_64)
		printf("cigam_64\n");
		// ft_cigam_64(mem, name);
	else if (magic_nb == MH_MAGIC)
		printf("mh_magic\n");
		// ft_handle_32(e);
	else if (magic_nb == MH_CIGAM)
		printf("mh_cigam\n");
		// ft_cigam(e);
	else if (magic_nb == FAT_MAGIC)
		printf("fat_magic\n");
		// ft_handle_FAT(e, 0);
	else if (magic_nb == FAT_CIGAM)
		printf("fat_cigam\n");
		// ft_handle_FAT(e, 1);
	else
		ft_putstr("The file was not recognized as a valid object file.\n");
}

int				main(int argc, char **argv)
{
	int				fd;
	size_t			size;
	t_env			e;

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
		e.archive = 0;
		e.name = argv[1];
		ft_otool(&e);
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
