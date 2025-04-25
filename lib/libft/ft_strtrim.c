/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:38:53 by csteylae          #+#    #+#             */
/*   Updated: 2023/05/01 18:44:54 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check_char(char c, char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (0);
		i++;
	}
	return (1);
}

static char	*ft_strncpy(char *dst, char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	int		i;
	int		front;
	int		len;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	front = 0;
	len = ft_strlen(s1);
	if (len == 0)
		return (ft_calloc(1, 1));
	while (s1[front] != '\0' && check_char((char)s1[front], (char *)set) == 0)
		front++;
	while (check_char((char)s1[len - (1 + i)], (char *)set) == 0)
		i++;
	if (front > len - (1 + i))
		return (ft_calloc(1, 1));
	len = ft_strlen(s1) - i - front;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	return (ft_strncpy(dst, (char *)s1 + front, len));
}
