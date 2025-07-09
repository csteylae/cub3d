/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:05:15 by raneuman          #+#    #+#             */
/*   Updated: 2025/07/09 11:53:51 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/cub3D.h"

static int	parse_3(t_data *game)
{
	if (!game->trimmed)
		free_all_error("Error\n failure!\n", game);
	if (ft_strlen(game->trimmed) > 0)
	{
		if (!check_texture(game, game->trimmed))
		{
			free(game->trimmed);
			game->trimmed = NULL;
			return (1);
		}
	}
	if (game->trimmed)
	{
		free(game->trimmed);
		game->trimmed = NULL;
	}
	return (0);
}

static void	parse_2(t_data *game)
{
	if (!game->trimmed)
		free_all_error("Error\nInvalid file!\n", game);
	if (!is_valid_element(game->trimmed, game))
		free_all_error("Error\nInvalid file!\n", game);
	if (game->trimmed)
	{
		free(game->trimmed);
		game->trimmed = NULL;
	}
}

static char	**read_lines_2(t_data *game)
{
	char	*line;
	int		i;

	if (!game->entire_fd)
		ft_error("Error\nMalloc failed\n");
	i = 0;
	line = get_next_line(game->fd);
	while (line != NULL)
	{
		game->entire_fd[i++] = line;
		line = get_next_line(game->fd);
	}
	game->entire_fd[i] = NULL;
	close(game->fd);
	return (game->entire_fd);
}

static char	**read_lines(t_data *game, char *file)
{
	char	*line;
	int		count;

	count = 0;
	open_file(game, file);
	line = get_next_line(game->fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(game->fd);
	}
	close(game->fd);
	if (count == 0)
	{
		free_all(game);
		ft_error("Error\nFile must contain something!\n");
	}
	open_file(game, file);
	game->entire_fd = malloc(sizeof(char *) * (count + 1));
	return (read_lines_2(game));
}

void	parse(t_data *game, char *file)
{
	int	i;
	int	j;
	int	map_start_index;

	game->entire_fd = read_lines(game, file);
	i = -1;
	map_start_index = -1;
	while (game->entire_fd[++i])
	{
		if (game->cnt == 21)
			break ;
		game->trimmed = ft_strtrim(game->entire_fd[i], " \t");
		parse_2(game);
	}
	map_start_index = i;
	j = -1;
	while (game->entire_fd[++j])
	{
		game->trimmed = ft_strtrim(game->entire_fd[j], " \t");
		if (parse_3(game))
			break ;
	}
	parse_map(game, map_start_index);
	free_entire_fd(game);
}
