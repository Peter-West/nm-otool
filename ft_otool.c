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

	i = base;
	while (i >= 0)
	{
		offset[i] = hex[addr % base];
		addr /= base;
		i--;
	}
	ft_putstr(offset);
	// ft_putstr(" ");
}

void		print_data(uint32_t addr, int base)
{
	int		i;
	char	hex[]="0123456789abcdef";
	char	offset[base + 1];

	i = base;
	while (i >= 0)
	{
		offset[i] = hex[addr % base];
		addr /= base;
		i--;
	}
	ft_putstr(offset);
	// ft_putstr(" ");
}

void		print_64(section_64 *s64)
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
		while (j < 16)
		{
			print_data(off, 2);
			// printf(" %llu", add+off);
			off++;
			j++;
		}
		ft_putendl("");
		add += 16;
		i += 16;
	}
}

section_64	*get_section_text(segcmd_64 *sg64)
{
	uint8_t				i;
	struct section_64            *s64;

	i = 0;
	s64 = (struct section_64*)(sg64 + 1);
	printf("sg64->nsects : %d\n", sg64->nsects);
	while (i < sg64->nsects)
	{
		// printf("i:%d\n",i);
		if (ft_strequ(s64->segname, "__TEXT") && ft_strequ(s64->sectname, "__text"))
		{
			print_64(s64);
			return (s64);
		}
		s64 += 1;
		++i;
	}
	return (NULL);
}

void			ft_handle_64(void *mem)
{
	header_64		*h;
	loadcmd			*lc;
	segcmd_64		*sg64;
	int				i;
	// symtab			*stc;

	i = 0;
	h = (header_64*)mem;
	lc = mem + sizeof(*h);
	sg64 = (segcmd_64*)lc;
	printf("(int)h->ncmds : %d\n", (int)h->ncmds);
	while(i < (int)h->ncmds)
	{
		if (sg64[i].cmd == LC_SEGMENT_64)
		{
			printf("heyyyy\n");
			// stc = (symtab*)lc;
			// ft_print(stc->nsyms, stc->stroff, stc->symoff, mem);
			get_section_text(&sg64[i]);
		}
		// lc = (void*)lc + lc->cmdsize;
		i++;
	}
}

void			ft_otool(void *mem)
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
		ft_otool(mem);
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
