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

# include <sys/stat.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <stdlib.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include "libft.h"

typedef struct mach_header_64		header;
typedef struct load_command			loadcmd;
typedef struct segment_command_64	segcmd_64;
typedef struct symtab_command		symtab;
typedef struct nlist_64				nlist_64;
typedef struct section_64			section_64;

typedef struct						s_list
{
	void							*data;
	struct s_list					*next;	
}									t_list;

typedef struct						output
{
	char							*addr;
	char							*symtype;
	char							*symtab;
}									out;

char			ft_symtype(nlist_64 *n64, section_64 *s64);
void			ft_fill_list(t_list **list, void *data);

#endif /* !FT_NM_H */
