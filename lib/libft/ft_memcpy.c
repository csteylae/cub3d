/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:28:07 by csteylae          #+#    #+#             */
/*   Updated: 2023/04/24 11:57:10 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (dst);
	if (dst == 0 && src == 0)
		return (NULL);
	while (i < n)
	{
		*((unsigned char *) dst + i) = *((unsigned char *)src + i);
		i++;
	}
	return (dst);
}
