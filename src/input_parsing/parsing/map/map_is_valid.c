/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:56:34 by raneuman          #+#    #+#             */
/*   Updated: 2025/07/14 15:21:57 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/cub3D.h"

static void	map_is_closed(t_data *game)
{
	int	y;
	int	x;

	y = 0;
	game->map_copy = copy_map(game->map, game);
	if (!game->map_copy)
		free_all_error("Error\nInvalid file!\n", game);
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				if (flood_fill(game, y, x))
					free_all_error("Error\nInvalid file!\n", game);
				return ;
			}
			x++;
		}
		y++;
	}
}

static int	is_line_truly_empty(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static void	check_map_empty_lines(t_data *game)
{
	int	i;
	int	in_map;
	int	empty_found;

	i = 0;
	in_map = 0;
	empty_found = 0;
	while (game->map[i])
	{
		if (is_line_truly_empty(game->map[i]))
		{
			if (in_map)
				empty_found = 1;
		}
		else
		{
			if (empty_found)
				free_all_error("Error\nInvalid file!\n", game);
			in_map = 1;
		}
		i++;
	}
}

static int	start_pos(t_data *game)
{
	int	y;
	int	count;
	int	x;

	y = 0;
	count = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'W')
				count++;
			x++;
		}
		y++;
	}
	if (count != 1)
		return (0);
	else if (!count)
		return (0);
	return (1);
}

void	map_is_valid(t_data *game)
{
	if (!start_pos(game))
		free_all_error("Error\nInvalid file!\n", game);
	check_map_empty_lines(game);
	map_is_closed(game);
	check_map_boundary(game);
	check_invalid_zero(game);
	if (game->map_copy)
	{
		free_str(game->map_copy);
		game->map_copy = NULL;
	}
}
