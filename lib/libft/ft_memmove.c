/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:19:35 by csteylae          #+#    #+#             */
/*   Updated: 2023/04/24 16:22:47 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	size_t	tmp;

	i = 0;
	tmp = len - 1;
	if (dst == src)
		return (dst);
	if (src > dst)
	{
		while (i < len)
		{
			*((unsigned char *)dst + i) = *((unsigned char *)src + i);
			i++;
		}
	}
	else
	{
		while (i != len)
		{
			*((unsigned char *)dst + tmp) = *((unsigned char *)src + tmp);
			tmp--;
			i++;
		}
	}
	return (dst);
}
