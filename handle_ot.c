/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 22:06:58 by ppellegr          #+#    #+#             */
/*   Updated: 2014/04/27 22:06:58 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void			ft_handle_64(t_env *e)
{
	t_header_64		*h;
	t_loadcmd		*lc;
	t_segcmd_64		*sg64;
	int				i;

	i = 0;
	h = (t_header_64*)e->mem;
	lc = e->mem + sizeof(*h);
	sg64 = (t_segcmd_64*)lc;
	while (i < (int)h->ncmds)
	{
		if (sg64[i].cmd == LC_SEGMENT_64)
		{
			get_section_text_64(&sg64[i], e);
		}
		i++;
	}
}

void			ft_handle_32(t_env *e)
{
	t_header		*h;
	t_loadcmd		*lc;
	t_segcmd		*sg;
	int				i;

	i = 0;
	h = (t_header*)e->mem;
	lc = e->mem + sizeof(*h);
	sg = (t_segcmd*)lc;
	while (i < (int)h->ncmds)
	{
		if (sg[i].cmd == LC_SEGMENT)
		{
			get_section_text_32(&sg[i], e);
		}
		i++;
	}
}

void			ft_handle_fat(t_env *e, int lit_end)
{
	t_fat_header	*hdr;
	t_fat_arch		*arch;
	int				cpu_type;
	int				nb_arch;
	int				i;

	i = 0;
	hdr = (t_fat_header*)e->mem;
	arch = (t_fat_arch*)((void*)e->mem + sizeof(t_fat_header));
	nb_arch = lit_end ? convert_endian(hdr->nfat_arch) : hdr->nfat_arch;
	while (i < nb_arch)
	{
		cpu_type = lit_end ? convert_endian(arch[i].cputype) : arch[i].cputype;
		if (cpu_type == CPU_TYPE_X86_64)
		{
			e->mem += lit_end ?
				convert_endian(arch[i].offset) : arch[i].offset;
			ft_otool(e);
		}
		i++;
	}
}
