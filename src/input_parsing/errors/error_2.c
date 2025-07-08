/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:49:58 by raneuman          #+#    #+#             */
/*   Updated: 2025/07/08 22:41:11 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D.h"

static void	free_game_data_2(t_data *game)
{
	if (game->cleaned)
		free_str(game->cleaned);
	if (game->rgb)
		free_str(game->rgb);
	if (game->map)
		free_str(game->map);
	if (game->map_copy)
		free_str(game->map_copy);
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
	if (game->trimmed)
		free(game->trimmed);
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
