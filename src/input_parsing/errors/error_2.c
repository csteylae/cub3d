/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:49:58 by raneuman          #+#    #+#             */
/*   Updated: 2025/07/09 18:09:53 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D.h"

static void	free_game_data_3(t_data *game)
{
	if (game->trimmed)
	{
		free(game->trimmed);
		game->trimmed = NULL;
	}
	if (game->txt_path)
	{
		free(game->txt_path);
		game->txt_path = NULL;
	}
}

static void	free_game_data_2(t_data *game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (game->cleaned[i])
		{
			free(game->cleaned[i]);
			game->cleaned[i] = NULL;
		}
		i++;
	}
	if (game->rgb)
		free_str(game->rgb);
	if (game->map_copy)
		free_str(game->map_copy);
	free_game_data_3(game);
}

void	free_game_data(t_data *game)
{
	int	i;

	if (!game)
		return ;
	if (game->fd >= 0)
	{
		close(game->fd);
		game->fd = -1;
	}
	if (game->entire_fd)
		free_str(game->entire_fd);
	if (game->map)
		free_str(game->map);
	i = 0;
	while (i < 4)
	{
		if (game->texture[i])
		{
			free(game->texture[i]);
			game->texture[i] = NULL;
		}
		i++;
	}
	free_game_data_2(game);
}
