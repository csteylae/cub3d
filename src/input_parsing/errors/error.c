/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:49:05 by raneuman          #+#    #+#             */
/*   Updated: 2025/07/08 22:29:09 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	free_str(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}

void	free_entire_fd(t_data *game)
{
	int	i;

	i = 0;
	if (!game->entire_fd)
		return ;
	while (game->entire_fd[i])
		free(game->entire_fd[i++]);
	free(game->entire_fd);
	game->entire_fd = NULL;
}

void	free_all(t_data *game)
{
	free_game_data(game);
	free(game);
}

void	free_all_error(char *str, t_data *game)
{
	free_game_data(game);
	free(game);
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}
