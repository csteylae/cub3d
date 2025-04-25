/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:08:53 by csteylae          #+#    #+#             */
/*   Updated: 2023/04/25 12:46:11 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0' && (i + needle_len <= len))
	{
		if (ft_strncmp(haystack + i, needle, needle_len) == 0)
			return (((char *)haystack + i));
		i++;
	}
	return (NULL);
}
