/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:54:57 by raneuman          #+#    #+#             */
/*   Updated: 2025/07/09 18:19:22 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/cub3D.h"

static void	extract_rgb_values(t_data *game, char *str, int i)
{
	game->comma_cnt = 0;
	while (str[++i])
	{
		if (str[i] == ',')
		{
			game->comma_cnt++;
			if (str[i + 1] == ',' || i == 0 || str[i + 1] == '\0')
				free_str_all(str, game);
		}
	}
	if (game->comma_cnt != 2)
		free_str_all(str, game);
	game->rgb = ft_split(str, ',');
	if (!game->rgb)
		free_str_all(str, game);
}

static int	parse_color(char *str, t_data *game, int i, int j)
{
	extract_rgb_values(game, str, -1);
	while (game->rgb[i])
		i++;
	if (i != 3)
		free_str_all(str, game);
	validate_rgb_components(str, game, -1, j);
	game->r = ft_atoi(game->cleaned[0]);
	game->g = ft_atoi(game->cleaned[1]);
	game->b = ft_atoi(game->cleaned[2]);
	if (game->r < 0 || game->r > 255 || game->g < 0 || game->g > 255
		|| game->b < 0 || game->b > 255)
		free_str_all(str, game);
	i = 0;
	while (i < 3)
	{
		free(game->cleaned[i]);
		game->cleaned[i] = NULL;
		i++;
	}
	free_str(game->rgb);
	game->rgb = NULL;
	return (create_trgb(0, game));
}

static void	c_color(t_data *game, char *line)
{
	char	*value;

	if (game->check_ceiling_color != 0)
		free_all_error("Error\nInvalid file!\n", game);
	value = ft_strtrim(line + 2, " \n");
	if (!value || value[0] == '\0')
		free_all_error("Error\nInvalid file!\n", game);
	game->check_ceiling_color = 1;
	game->ceiling_color = parse_color(value, game, 0, -1);
	free(value);
}

static void	f_color(t_data *game, char *line)
{
	char	*value;

	if (game->check_floor_color != 0)
		free_all_error("Error\nInvalid file!\n", game);
	value = ft_strtrim(line + 2, " \n");
	if (!value || value[0] == '\0')
		free_all_error("Error\nInvalid file!\n", game);
	game->check_floor_color = 1;
	game->floor_color = parse_color(value, game, 0, -1);
	free(value);
}

void	check_color(t_data *game, char *line)
{
	if (ft_strncmp(line, "F", 1) == 0)
	{
		if (game->cnt & F)
			free_all_error("Error\nDuplicate element!\n", game);
		game->cnt = game->cnt | F;
		f_color(game, line);
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		if (game->cnt & C)
			free_all_error("Error\nDuplicate element\n", game);
		game->cnt = game->cnt | C;
		c_color(game, line);
	}
}
