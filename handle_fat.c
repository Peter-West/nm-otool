/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 20:58:26 by ppellegr          #+#    #+#             */
/*   Updated: 2014/04/23 20:58:27 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

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
			ft_nm(e);
		}
		i++;
	}
}
