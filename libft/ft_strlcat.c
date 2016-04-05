/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 17:30:41 by ppellegr          #+#    #+#             */
/*   Updated: 2013/11/19 17:30:46 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*tmp;

	tmp = dst;
	if (src == NULL || dst == NULL)
		return (0);
	if (size < ft_strlen(dst))
		return (ft_strlen(src) + size);
	while (*dst != '\0')
		dst++;
	while (size--)
		*dst++ = *src++;
	return (ft_strlen(tmp));
}
