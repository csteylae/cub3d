/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:38:14 by csteylae          #+#    #+#             */
/*   Updated: 2023/04/25 18:26:47 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy_cat(char *dst, char *src, char *src2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (src2[j] != '\0')
	{
		dst[i] = src2[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	n;
	char	*strjoin;

	if (!s1 || !s2)
		return (NULL);
	n = ft_strlen(s1) + ft_strlen(s2);
	if (n == 0)
		return (ft_calloc(1, 1));
	strjoin = (char *) malloc(sizeof(char) * (n + 1));
	if (!strjoin)
		return (NULL);
	strjoin = ft_strcpy_cat(strjoin, (char *)s1, (char *)s2);
	return (strjoin);
}
