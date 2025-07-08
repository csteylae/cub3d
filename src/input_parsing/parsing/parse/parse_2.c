/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:23:36 by raneuman          #+#    #+#             */
/*   Updated: 2025/07/08 14:20:00 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/cub3D.h"

static int	is_valid_element_2(char *line, t_data *game)
{
	if (ft_strncmp(line, "WE", 2) == 0)
	{
		game->cnt += 3;
		return (1);
	}
	if (ft_strncmp(line, "EA", 2) == 0)
	{
		game->cnt += 4;
		return (1);
	}
	if (ft_strncmp(line, "F", 1) == 0)
	{
		game->cnt += 5;
		return (1);
	}
	if (ft_strncmp(line, "C", 1) == 0)
	{
		game->cnt += 6;
		return (1);
	}
	return (0);
}

int	is_valid_element(char *line, t_data *game)
{
	if (!line)
		return (0);
	if (ft_strlen(line) == 0)
		return (1);
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		game->cnt += 1;
		return (1);
	}
	if (ft_strncmp(line, "SO", 2) == 0)
	{
		game->cnt += 2;
		return (1);
	}
	if (is_valid_element_2(line, game))
		return (1);
	return (0);
}

void	open_file(t_data *game, char *file)
{
	game->fd = open(file, O_RDONLY);
	if (game->fd == -1)
		ft_error("Error\nFile opening failure!\n");
}
