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

typedef struct mach_header_64		t_header_64;
typedef struct mach_header			t_header;
typedef struct load_command			t_loadcmd;
typedef struct segment_command_64	t_segcmd_64;
typedef struct segment_command		t_segcmd;
typedef struct symtab_command		t_symtab;
typedef struct nlist_64				t_nlist_64;
typedef struct nlist				t_nlist_32;
typedef struct section_64			t_section_64;
typedef struct section				t_section;
typedef struct fat_header			t_fat_header;
typedef struct fat_arch				t_fat_arch;
typedef struct ar_hdr				t_arch_hdr;
typedef struct ranlib				t_ranlib;

typedef struct						s_list
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
	int								multi_files;
	int								is_arch;
	int								fd;
	size_t							size;
	t_symtab						*stc;
	t_header_64						*h64;
	t_header						*h;
	t_loadcmd						*lc;
	t_segcmd_64						*sg64;
	t_segcmd						*sg;
	t_section_64					*s64;
	t_list							*arch;
}									t_env;

void								ft_nm(t_env *e);
char								ft_symtype_64(char type, t_nlist_64 n64,
	t_env *e);
char								ft_symtype(char type, t_nlist_32 n,
	t_env *e);
void								add_to_list(t_list **list, void *data);
void								ft_print(t_env *e);
void								ft_sort(t_list **sym);
void								ft_handle_arch(t_env *e);
int									convert_endian(int num);
void								add_sym(t_env *e);
void								add_sym_64(t_env *e);
char								*zero_str_64(char *str);
char								*zero_str(char *str);
void								ft_handle_32(t_env *e);
void								ft_handle_64(t_env *e);
void								ft_handle_fat(t_env *e, int lit_end);
off_t								ft_get_size(int fd);
void								*ft_get_file(size_t size, int fd);
int									get_sects64(t_env *e, int nb);
int									get_sects(t_env *e, int nb);

#endif
