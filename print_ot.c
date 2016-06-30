/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 22:06:58 by ppellegr          #+#    #+#             */
/*   Updated: 2014/04/27 22:06:58 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void		print_addr(uint64_t addr, int base)
{
	int				i;
	char			*hex;
	char			offset[base + 1];

	hex = "0123456789abcdef";
	i = base - 1;
	offset[base] = '\0';
	while (i >= 0)
	{
		offset[i] = hex[addr % 16];
		addr /= 16;
		i--;
	}
	ft_putstr(offset);
	ft_putstr(" ");
}

void		print_data(unsigned char addr, int base)
{
	int				i;
	char			*hex;
	char			offset[base + 1];

	hex = "0123456789abcdef";
	i = base - 1;
	offset[base] = '\0';
	while (i >= 0)
	{
		offset[i] = hex[addr % 16];
		addr /= 16;
		i--;
	}
	write(1, offset, base);
	ft_putstr(" ");
}

void		print_64(t_section_64 *s64, char *mem)
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
		while (j < 16 && i + j < s64->size)
		{
			print_data(*(mem + off), 2);
			off++;
			j++;
		}
		ft_putendl("");
		add += j;
		i += j;
	}
}

void		print_32(t_section *s, char *mem)
{
	uint64_t		i;
	uint64_t		add;
	uint32_t		off;
	int				j;

	i = 0;
	add = s->addr;
	off = s->offset;
	while (i < s->size)
	{
		print_addr(add, 8);
		j = 0;
		while (j < 16 && i + j < s->size)
		{
			print_data(*(mem + off), 2);
			off++;
			j++;
		}
		ft_putendl("");
		add += j;
		i += j;
	}
}
