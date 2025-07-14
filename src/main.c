/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:12:14 by csteylae          #+#    #+#             */
/*   Updated: 2025/07/14 15:22:51 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	free_texture(t_mlx_data *data, t_texture *texture)
{
	if (!texture)
		return ;
	if (texture->path)
	{
		free(texture->path);
		texture->path = NULL;
	}
	if (texture->img.ptr)
	{
		mlx_destroy_image(data->mlx, texture->img.ptr);
		texture->img.ptr = NULL;
	}
}

int	close_cub(t_mlx_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = NULL;
	free_texture(data, &data->texture[EAST]);
	free_texture(data, &data->texture[WEST]);
	free_texture(data, &data->texture[NORTH]);
	free_texture(data, &data->texture[SOUTH]);
	if (data->framebuffer.ptr)
		mlx_destroy_image(data->mlx, data->framebuffer.ptr);
	if (data->mlx && data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data->game);
	exit(EXIT_SUCCESS);
}

void	put_error(char *error_msg, t_mlx_data *data)
{
	if (error_msg)
		printf("%s\n\n", error_msg);
	close_cub(data);
}

int	main(int argc, char **argv)
{
	int			len;
	t_data		*game;
	t_mlx_data	data;

	if (argc != 2)
		ft_error("Error\nNot the right amount of arguments!\n");
	len = ft_strlen(argv[1]);
	if ((ft_strncmp(argv[1] + len - 4, ".cub", 4)) != 0)
		ft_error("Error\nInvalid map format!\n");
	game = malloc(sizeof(t_data));
	if (!game)
		ft_error("Error\nFailed allocation memory!\n");
	init_struct(game);
	parse(game, argv[1]);
	map_is_valid(game);
	data = init_data(game);
	mlx_hook(data.win, 17, 0, close_cub, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_press, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, key_release, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
