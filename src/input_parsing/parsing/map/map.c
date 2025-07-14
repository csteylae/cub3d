/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:00:13 by raneuman          #+#    #+#             */
/*   Updated: 2025/07/14 15:07:26 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/cub3D.h"

static void	allocation_map(t_data *game)
{
	if (game->cnt_map_lines == 0)
		free_all_error("Error\nInvalid file!\n", game);
	game->map = malloc(sizeof(char *) * (game->cnt_map_lines + 1));
	if (!game->map)
		free_all_error("Error\nInvalid file!\n", game);
}

static int	map_content(char *line)
{
	int	i;

	i = 0;
	if (ft_strlen(line) == 0)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0'
			&& line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	parse_map(t_data *game, int map_start_index)
{
	int	i;
	int	j;

	i = map_start_index - 1;
	while (game->entire_fd[++i])
	{
		if (!map_content(game->entire_fd[i]))
			free_all_error("Error\nInvalid file!\n", game);
		game->cnt_map_lines++;
	}
	allocation_map(game);
	i = map_start_index - 1;
	j = 0;
	while (game->entire_fd[++i])
	{
		game->map[j] = ft_strdup(game->entire_fd[i]);
		if (!game->map[j])
			free_all_error("Error\nInvalid file!\n", game);
		j++;
	}
	game->map[j] = NULL;
}
