/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:45:58 by csteylae          #+#    #+#             */
/*   Updated: 2023/04/26 15:13:03 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nb_len(int nb)
{
	int	count;

	count = 1;
	if (nb < 0)
	{
		nb = -nb;
		count++;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

static	char	*manage_int_min(void)
{
	int		i;
	char	*str;
	char	*dst;

	i = 0;
	str = "-2147483648";
	dst = (char *)malloc(sizeof(char) * 12);
	if (!dst)
		return (NULL);
	while (str[i])
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*put_to_str(int n, char *dst, int len)
{
	int	i;
	int	tmp;
	int	minus;

	i = len;
	tmp = n;
	minus = 0;
	if (n < 0)
	{
		dst[0] = '-';
		tmp = -tmp;
		minus = 1;
	}
	while (len > minus)
	{
		n = tmp;
		while (n > 9)
			n = n % 10;
		dst[len - 1] = n + 48;
		len--;
		tmp = tmp / 10;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*dst;

	if (n == -2147483648)
		return (manage_int_min());
	len = ft_nb_len(n);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	dst = put_to_str(n, dst, len);
	return (dst);
}
