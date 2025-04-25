/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:50:17 by csteylae          #+#    #+#             */
/*   Updated: 2023/05/02 15:27:14 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

static int	ft_nb_of_split(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			count++;
		}
	}
	return (count);
}

static char	*ft_newstr(char *s, char sep)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != sep)
		i++;
	s = s + i;
	return (s);
}

static char	*ft_trimcpy(char *s, char sep)
{
	size_t		i;
	char		*dst;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0' && s[i] != sep)
		i++;
	dst = (char *)malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != sep)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	**make_free(char **split, int index)
{
	while (index >= 0)
	{
		free(split[index]);
		index--;
	}
	free(split);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**dst;
	int		array_size;
	int		k;
	int		i;

	k = -1;
	if (!s)
		return (NULL);
	array_size = ft_nb_of_split((char *)s, c);
	dst = (char **)malloc(sizeof(char *) * (array_size + 1));
	if (!dst)
		return (NULL);
	while (++k < array_size)
	{
		i = 0;
		while (s[i] != '\0' && s[i] == c)
			i++;
		s = s + i;
		dst[k] = ft_trimcpy((char *)s, c);
		if (dst[k] == NULL)
			return (make_free(dst, k));
		s = ft_newstr((char *)s, c);
	}
	dst[k] = 0;
	return (dst);
}
