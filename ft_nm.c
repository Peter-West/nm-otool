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

char			*zero_str_64(char *str)
{
	int			to_add;
	char		*ret;
	int			i;

	i = 0;
	to_add = 16 - ft_strlen(str);
	// printf("ft_strlen hex : %zu\n", ft_strlen(hex));
	// printf("")
	ret = (char*)malloc(sizeof(char) * to_add + 1);
	while (i < to_add)
		ret[i++] = '0';
	ret[i] = 0;
	return (ret);
}

char			*zero_str(char *str)
{
	int			to_add;
	char		*ret;
	int			i;

	i = 0;
	to_add = 8 - ft_strlen(str);
	// printf("ft_strlen hex : %zu\n", ft_strlen(hex));
	// printf("")
	ret = (char*)malloc(sizeof(char) * to_add + 1);
	while (i < to_add)
		ret[i++] = '0';
	ret[i] = 0;
	return (ret);
}

void			add_sym_64(t_env *e)
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
			sym->symtype = ft_symtype_64(n64[i].n_type, n64[i], e);
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
				sym->addr = ft_strjoin(zero_str_64(hex), hex);
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

void			add_sym(t_env *e)
{
	unsigned int	i;
	nlist_32		*n;
	char			*strtab;
	char			*hex;
	t_sym			*sym;

	i = 0;
	strtab = e->mem + e->stc->stroff;
	n = e->mem + e->stc->symoff;
	while (i < e->stc->nsyms)
	{
		char *nam;
		nam = strtab + n[i].n_un.n_strx;

		if (nam[0] != 0 && n[i].n_type < 100)
		{
			sym = (t_sym*)malloc(sizeof(t_sym));
			hex = ft_ltoahex(n[i].n_value);
			sym->symtype = ft_symtype(n[i].n_type, n[i], e);
			sym->name = strtab + n[i].n_un.n_strx;
			if (n[i].n_value == 0)
			{
				if (sym->symtype == 'U')
				{
					hex[0] = ' ';
					sym->addr = ft_strjoin("       ", hex);
				}
				else
				{
					hex[0] = '0';
					sym->addr = ft_strjoin("0000000", hex);
				}
			}
			else
				sym->addr = ft_strjoin(zero_str(hex), hex);
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

int			get_sects64(t_env *e,int nb)
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

int			get_sects(t_env *e,int nb)
{
	unsigned int			i;
	section					*s;
	t_sect					*sec;
	
	i = 0;
	s = (void*)e->sg + sizeof(*e->sg);
	while (i < e->sg->nsects)
	{
		sec = (t_sect*)malloc(sizeof(t_sect));
		sec->name = s->sectname;
		sec->nb = nb++;
		add_to_list(&e->sects, sec);
		s = (void*)s + sizeof(*s);
		i++;
	}
	return (nb);
}

void			ft_handle_64(t_env *e)
{
	int				i;
	int				nb = 1;

	i = 0;
	e->h64 = (header_64*)e->mem;
	e->lc = e->mem + sizeof(*e->h64);
	while(i < (int)e->h64->ncmds)
	{
		if (e->lc->cmd == LC_SEGMENT_64)
		{
			e->sg64 = (segcmd_64*)e->lc;
			nb = get_sects64(e, nb);
		}
		if (e->lc->cmd == LC_SYMTAB)
		{
			e->stc = (symtab*)e->lc;
			add_sym_64(e);
		}	
		e->lc = (void*)e->lc + e->lc->cmdsize;
		i++;
	}
}

void			ft_handle_32(t_env *e)
{
	int				i;
	int				nb = 1;

	i = 0;
	e->h = (header*)e->mem;
	e->lc = (void*)e->mem + sizeof(*e->h);
	while(i < (int)e->h->ncmds)
	{
		if (e->lc->cmd == LC_SEGMENT)
		{
			e->sg = (segcmd*)e->lc;
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

void			ft_cigam(t_env *e)
{
	(void)e;
	printf("CIGAM\n");
	sleep(1);
}

void			ft_cigam_64(t_env *e)
{
	(void)e;
	printf("CIGAM 64\n");
	sleep(1);

}

int				convert_endian(int num)
{
	int		swapped;

	swapped = ((num>>24)&0xff) | // move byte 3 to byte 0
		((num<<8)&0xff0000) | // move byte 1 to byte 2
		((num>>8)&0xff00) | // move byte 2 to byte 1
		((num<<24)&0xff000000); // byte 0 to byte 3
	return (swapped);
}

void			ft_handle_FAT(t_env *e, int lit_end)
{
	fat_header	*hdr;
	fat_arch	*arch;
	int			cpu_type;
	int			nb_arch;
	int			i;

	i = 0;
	hdr = (fat_header*)e->mem;
	arch = (fat_arch*)((void*)e->mem + sizeof(fat_header));
	nb_arch = lit_end ? convert_endian(hdr->nfat_arch) : hdr->nfat_arch;
	while (i < nb_arch)
	{
		cpu_type = lit_end ? convert_endian(arch[i].cputype) : arch[i].cputype;
		if (cpu_type == CPU_TYPE_X86_64)
		{
			// e->mem = (void*)e->mem + convert_endian(arch->offset);
			e->mem += lit_end ? convert_endian(arch[i].offset) : arch[i].offset;
			ft_nm(e);
		}
		i++;
	}
}

void			ft_nm(t_env *e)
{
	unsigned int		magic_nb;

	magic_nb = *(unsigned int*)e->mem;
	 
	if (magic_nb == FAT_MAGIC)
		ft_handle_FAT(e, 0);
	else if (magic_nb == FAT_CIGAM)
		ft_handle_FAT(e, 1);
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
		ft_putstr("The file was not recognized as a valid object file.\n");
	ft_print(e);
}

int				main(int argc, char **argv)
{
	int				fd;
	size_t			size;
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
		if ((fd = open(argv[i], O_RDONLY)) == -1)
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
		e.filename = argv[i];
		ft_nm(&e);
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
		i++;
	}
	if (argc < 1)
		ft_putstr_fd("Usage: ./ft_nm [filename]\n", 2);
	return (0);
}
