/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 21:03:22 by ppellegr          #+#    #+#             */
/*   Updated: 2014/04/23 21:03:23 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

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

typedef struct mach_header_64		header;
typedef struct load_command			loadcmd;
typedef struct segment_command_64	segcmd_64;
typedef struct symtab_command		symtab;
typedef struct nlist_64				nlist_64;
typedef struct section_64			section_64;

typedef struct ar_hdr				arch_hdr;
typedef struct ranlib				ranlib;

typedef struct 						s_list
{
	void							*data;
	struct s_list					*next;
}									t_list;

typedef struct						s_sym
{
	char							*addr;
	unsigned char					symtype;
	char							*name;
}									t_sym;

typedef struct						s_sect
{
	int								nb;
	char							*name;
}									t_sect;

typedef struct						s_arch
{
	char							*name;
	unsigned int					off;
	unsigned int					strx;
}									t_arch;

typedef struct						s_env
{
	t_list							*sym;
	t_list							*sects;
	void							*mem;
	char							*filename;
	symtab							*stc;
	header							*h;
	loadcmd							*lc;
	segcmd_64						*sg64;
	section_64						*s64;

	t_list							*arch;
}									t_env;

void			ft_nm(t_env *e);
char			ft_symtype(char type, nlist_64 n64, t_env *e);
void			add_to_list(t_list **list, void *data);
void			ft_print(t_env *e);
void			ft_sort(t_list **sym);
void			ft_handle_arch(t_env *e);


#endif /* !FT_NM_H */
