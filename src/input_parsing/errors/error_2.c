/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:49:58 by raneuman          #+#    #+#             */
/*   Updated: 2025/07/09 15:55:48 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D.h"

static void	free_game_data_2(t_data *game)
{
	//if (game->cleaned)
	//	free_str(game->cleaned);
	if (game->cleaned)
    {
        int i = 0;
        while (i < 3)
        {
            if (game->cleaned[i])
                free(game->cleaned[i]);
            i++;
        }
        free(game->cleaned);
        game->cleaned = NULL;
    }
	//if (game->rgb)
	//	free_str(game->rgb);
	if (game->rgb)
    {
        free_str(game->rgb);
        game->rgb = NULL;
    }
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
	{
		free(game->trimmed);
		game->trimmed = NULL;	
	}
	//if (game->value)
	//{
	//	free(game->value);
	//	game->value = NULL;	
	//}
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
