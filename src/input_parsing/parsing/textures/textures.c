/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:03:39 by raneuman          #+#    #+#             */
/*   Updated: 2025/07/14 13:50:42 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/cub3D.h"

static int	check_east(t_data *game, char *line)
{
	if (ft_strncmp(line, "EA", 2) == 0)
	{
		if (game->cnt & EA)
			free_all_error("Error\nDuplicate element!\n", game);
		game->cnt = game->cnt | EA;
		if (game->texture[3] != NULL)
			free_all_error("Error\nInvalid file!\n", game);
		if (game->texture[3] != NULL)
			free_all_error("Error\nInvalid file!\n", game);
		game->txt_path = ft_strtrim(line + 3, " \n");
		if (!game->txt_path || game->txt_path[0] == '\0')
			free_all_error("Error\nInvalid file!\n", game);
		check_textures_path(game->txt_path, game);
		game->texture[3] = ft_strdup(game->txt_path);
		if (!game->texture[3])
			free_all_error("Error\nInvalid file!\n", game);
		free(game->txt_path);
		game->txt_path = NULL;
		return (1);
	}
	return (0);
}

static int	check_west(t_data *game, char *line)
{
	if (ft_strncmp(line, "WE", 2) == 0)
	{
		if (game->cnt & WE)
			free_all_error("Error\nDuplicate element!\n", game);
		game->cnt = game->cnt | WE;
		if (game->texture[2] != NULL)
			free_all_error("Error\nInvalid file!\n", game);
		game->txt_path = ft_strtrim(line + 3, " \n");
		if (!game->txt_path || game->txt_path[0] == '\0')
			free_all_error("Error\nInvalid file!\n", game);
		check_textures_path(game->txt_path, game);
		game->texture[2] = ft_strdup(game->txt_path);
		if (!game->texture[2])
			free_all_error("Error\nInvalid file!\n", game);
		free(game->txt_path);
		game->txt_path = NULL;
		return (1);
	}
	return (0);
}

static int	check_south(t_data *game, char *line)
{
	if (ft_strncmp(line, "SO", 2) == 0)
	{
		if (game->cnt & SO)
			free_all_error("Error\nDuplicate element!\n", game);
		game->cnt = game->cnt | SO;
		if (game->texture[1] != NULL)
			free_all_error("Error\nInvalid file!\n", game);
		game->txt_path = ft_strtrim(line + 3, " \n");
		if (!game->txt_path || game->txt_path[0] == '\0')
			free_all_error("Error\nInvalid file!\n", game);
		check_textures_path(game->txt_path, game);
		game->texture[1] = ft_strdup(game->txt_path);
		if (!game->texture[1])
			free_all_error("Error\nInvalid file!\n", game);
		free(game->txt_path);
		game->txt_path = NULL;
		return (1);
	}
	return (0);
}

static int	check_north(t_data *game, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		if (game->cnt & NO)
			free_all_error("Error\nDuplicate element!\n", game);
		game->cnt = game->cnt | NO;
		if (game->texture[0] != NULL)
			free_all_error("Error\nInvalid file!\n", game);
		game->txt_path = ft_strtrim(line + 3, " \n");
		if (!game->txt_path || game->txt_path[0] == '\0')
			free_all_error("Error\nInvalid file!\n", game);
		check_textures_path(game->txt_path, game);
		game->texture[0] = ft_strdup(game->txt_path);
		if (!game->texture[0])
			free_all_error("Error\nInvalid file!\n", game);
		free(game->txt_path);
		game->txt_path = NULL;
		return (1);
	}
	return (0);
}

int	check_texture(t_data *game, char *line)
{
	if (ft_strlen(line) < 3)
		free_all_error("Error\nInvalid file!\n", game);
	if (check_north(game, line))
		return (1);
	if (check_south(game, line))
		return (1);
	if (check_west(game, line))
		return (1);
	if (check_east(game, line))
		return (1);
	if (ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
	{
		check_color(game, line);
		return (1);
	}
	return (0);
}
