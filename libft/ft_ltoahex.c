/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoahex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/26 17:16:22 by ppellegr          #+#    #+#             */
/*   Updated: 2014/04/26 17:16:26 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_hex(int n)
{
	if (n > 9)
		return (n + 39);
	else
		return (n);
}

char		*ft_reverse(char *s, int j)
{
	char	*tmp;
	int		i;
	int		k;

	k = 0;
	i = ft_strlen(s);
	if (j % 2 != 0)
	{
		tmp = (char *)malloc(sizeof(char) * (i + 2));
		tmp[k++] = '-';
	}
	else
		tmp = (char *)malloc(sizeof(char) * (i + 1));
	while (i--)
		tmp[k++] = s[i];
	tmp[k] = '\0';
	return (tmp);
}

size_t		ft_intlen(long n)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n = n * -1;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char		*ft_ltoahex(long n)
{
	char	*s;
	int		i;
	int		tmp;
	int		j;

	i = 0;
	j = 0;
	if ((s = (char *)malloc(sizeof(char) * ft_intlen(n))) == NULL)
		return (NULL);
	if (n < 0)
	{
		j++;
		n = n * -1;
	}
	if (n == 0)
		s[i++] = '0';
	while (n != 0)
	{
		tmp = n % 16;
		tmp = ft_hex(tmp);
		s[i++] = tmp + '0';
		n = n / 16;
	}
	s[i] = '\0';
	return (ft_reverse(s, j));
}
