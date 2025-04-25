/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:53:56 by csteylae          #+#    #+#             */
/*   Updated: 2023/05/02 15:37:40 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dst;
	size_t	i;

	if (!s || !f)
		return (NULL);
	dst = ft_strdup(s);
	if (!dst)
		return (NULL);
	i = 0;
	while (dst[i] != '\0')
	{
		dst[i] = f(i, dst[i]);
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
