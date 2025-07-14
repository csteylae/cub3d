/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:05:15 by raneuman          #+#    #+#             */
/*   Updated: 2025/07/14 15:09:55 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/cub3D.h"

static void	search_textures(t_data *game)
{
	if (!game->trimmed)
		free_all_error("Error\nInvalid file!\n", game);
	if (ft_strlen(game->trimmed) > 0)
	{
		if (!check_texture(game, game->trimmed))
			free_all_error("Invalid file!\n", game);
	}
	if (game->trimmed)
	{
		free(game->trimmed);
		game->trimmed = NULL;
	}
}

void	open_file(t_data *game, char *file)
{
	game->fd = open(file, O_RDONLY);
	if (game->fd == -1)
		free_all_error("Error\nFile opening failure!\n", game);
}

static char	**read_lines_2(t_data *game)
{
	char	*line;
	int		i;

	if (!game->entire_fd)
		free_all_error("Error\nMalloc failed\n", game);
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
		free_all_error("Error\nInvalid file!\n", game);
	open_file(game, file);
	game->entire_fd = malloc(sizeof(char *) * (count + 1));
	return (read_lines_2(game));
}

void	parse(t_data *game, char *file)
{
	int	i;
	int	map_start_index;
	int	expected;

	expected = NO | SO | EA | WE | F | C;
	game->entire_fd = read_lines(game, file);
	i = -1;
	map_start_index = -1;
	while (game->entire_fd[++i])
	{
		if (game->cnt == expected)
			break ;
		game->trimmed = ft_strtrim(game->entire_fd[i], " \t");
		search_textures(game);
	}
	map_start_index = i;
	parse_map(game, map_start_index);
	free_entire_fd(game);
}
