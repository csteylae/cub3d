/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:57:20 by raneuman          #+#    #+#             */
/*   Updated: 2025/07/13 15:18:13 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/cub3D.h"

int	flood_fill(t_data *game, int y, int x)
{
	if (y < 0 || x < 0 || !game->map_copy[y]
		|| x >= (int)ft_strlen(game->map_copy[y]))
		return (1);
	if (game->map_copy[y][x] == ' ' || game->map_copy[y][x] == '\t')
		return (1);
	if (game->map_copy[y][x] == '1' || game->map_copy[y][x] == 'X')
		return (0);
	game->map_copy[y][x] = 'X';
	if (flood_fill(game, y - 1, x))
		return (1);
	if (flood_fill(game, y + 1, x))
		return (1);
	if (flood_fill(game, y, x - 1))
		return (1);
	if (flood_fill(game, y, x + 1))
		return (1);
	return (0);
}

char	**copy_map(char **src_map, t_data *game)
{
	int		i;
	char	**copy;

	i = 0;
	while (src_map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (src_map[++i])
	{
		copy[i] = ft_strdup(src_map[i]);
		if (!copy[i])
			free_all_error("Error\nInvalid file!\n", game);
	}
	copy[i] = NULL;
	return (copy);
}
