/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_padded_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:28:31 by csteylae          #+#    #+#             */
/*   Updated: 2025/07/14 13:29:31 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/cub3D.h"

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	get_max_width(char **map)
{
	int	i;
	int	max_len;

	i = 0;
	max_len = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > (size_t)max_len)
			max_len = ft_strlen(map[i]);
		i++;
	}
	return (max_len);
}

static void	fill_with_padded_char(char **map, int height, int width)
{
	int	i;

	i = 0;
	while (i < height)
	{
		map[i] = ft_calloc((width + 2 + 1), sizeof(char));
		if (map[i] == NULL)
		{
			free_padded_map(map, i);
			return ;
		}
		ft_memset(map[i], 'P', width + 2);
		i++;
	}
	map[i] = NULL;
}

static void	copy_padded_map(char **padded_map, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (padded_map[j] && map[i])
	{
		ft_memcpy(padded_map[j] + 1, map[i], ft_strlen(map[i]));
		i++;
		j++;
	}
}

char	**create_padded_map(t_data *game)
{
	char	**copy;
	int		height;
	int		width;

	height = get_map_height(game->map) + 2;
	width = get_max_width(game->map);
	copy = malloc(sizeof(char *) * (height + 2));
	if (!copy)
		free_all_error("Error\nCannot malloc map copy!\n", game);
	fill_with_padded_char(copy, height, width);
	if (!copy)
		free_all_error("Error\nCannot malloc map copy!\n", game);
	copy_padded_map(copy, game->map);
	return (copy);
}
