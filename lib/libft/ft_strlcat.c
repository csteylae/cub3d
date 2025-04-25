/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:13:45 by csteylae          #+#    #+#             */
/*   Updated: 2023/04/24 17:09:45 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	n;
	size_t	len;

	i = 0;
	n = ft_strlen(dst);
	len = ft_strlen(src);
	if (n <= dstsize - 1 && dstsize > 0)
	{
		while (src[i] != '\0' && n + i < dstsize - 1)
		{
			dst[n + i] = src[i];
			i++;
		}
		dst[n + i] = '\0';
	}
	if (n >= dstsize)
		n = dstsize;
	return (len + n);
}
