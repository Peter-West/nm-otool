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

typedef struct						s_env
{
	int								archive;
	char							*name;
	void							*mem;
	int								fd;
	size_t							size;
}									t_env;

void								ft_otool(t_env *e);
off_t								ft_get_size(int fd);
void								*ft_get_file(size_t size, int fd);
int									convert_endian(int num);
void								print_addr(uint64_t addr, int base);
void								print_data(unsigned char addr, int base);
void								print_64(t_section_64 *s64, char *mem);
void								print_32(t_section *s, char *mem);
t_section_64						*get_section_text_64(t_segcmd_64 *sg64,
	t_env *e);
t_section							*get_section_text_32(t_segcmd *sg,
	t_env *e);
int									get_size_arch(char *name);
char								*get_name_arch(char *name);
void								ft_handle_arch(t_env *e);
void								ft_handle_64(t_env *e);
void								ft_handle_32(t_env *e);
void								ft_handle_fat(t_env *e, int lit_end);
void								ft_otool(t_env *e);

#endif
