/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:39:43 by csteylae          #+#    #+#             */
/*   Updated: 2023/04/26 15:39:40 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char*s, int c)
{
	int	i;
	int	last_occ;

	i = 0;
	last_occ = -1;
	while (s[i])
	{
		if (s[i] == (char)c)
			last_occ = i;
		i++;
	}
	if ((char)c == '\0')
		return ((char *) s + i);
	if (last_occ == -1)
		return (0);
	else
	{
		s = s + last_occ;
		return ((char *)s);
	}
}
