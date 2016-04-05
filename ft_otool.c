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

void			ft_output()
{
	
}

void			ft_print(int nsyms, int stroff, int symoff, void *mem)
{
	int				i;
	nlist_64		*n64;
	char			*strtab;
	char			*hex;
	section_64		*s64;

	i = 0;
	strtab = mem + stroff;
	n64 = mem + symoff;
	s64 = mem + sizeof(segcmd_64*);
	while (i < nsyms)
	{
		if (ft_strequ(s64->segname, "__TEXT"))
		{
			if (ft_strequ(s64->sectname, "__text"))
			{
				ft_output()
			}
		}
		s64 = (void*)s64 + sizeof(section_64);
		i++;
	}
}

struct section_64            *get_section_text(struct segment_command_64 *segment)
{
    uint8_t                        i;
    struct section_64            *section;

    i = 0;
    section = (struct section_64*)(segment + 1);
    while (i < segment->nsects)
    {
        if (ft_strequ(section->segname, "__TEXT")
            && ft_strequ(section->sectname, "__text"))
            return (section);
        section += 1;
        ++i;
    }
    return (NULL);
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
