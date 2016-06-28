/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 22:12:01 by ppellegr          #+#    #+#             */
/*   Updated: 2014/04/27 22:12:51 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "libft.h"
# include <sys/stat.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <stdlib.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <ar.h>
# include <mach-o/ranlib.h>

typedef struct mach_header_64		header_64;
typedef struct load_command			loadcmd;
typedef struct segment_command_64	segcmd_64;
typedef struct symtab_command		symtab;
typedef struct nlist_64				nlist_64;
typedef struct section_64			section_64;
typedef struct fat_header			fat_header;
typedef struct fat_arch				fat_arch;
typedef struct ar_hdr				arch_hdr;
typedef struct ranlib				ranlib;

typedef struct						s_env
{
	int								archive;
	char							*name;
	void							*mem;
}									t_env;

void			ft_otool(t_env *);

#endif /* FT_OTOOL_H */
