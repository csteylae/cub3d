/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:12:46 by csteylae          #+#    #+#             */
/*   Updated: 2025/07/09 17:11:25 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static t_key	init_key(void)
{
	t_key	key;

	key.w = 0;
	key.a = 0;
	key.s = 0;
	key.d = 0;
	key.left = 0;
	key.right = 0;
	return (key);
}

static t_mlx_data	init_ptr(void)
{
	t_mlx_data	data;

	data.mlx = NULL;
	data.win = NULL;
	data.map = NULL;
	data.texture[NORTH].img = init_img();
	data.texture[SOUTH].img = init_img();
	data.texture[EAST].img = init_img();
	data.texture[WEST].img = init_img();
	data.framebuffer = init_img();
	return (data);
}

static void	get_cub_config(t_mlx_data *data, t_data *game)
{
	data->map = game->map;
	data->texture[NORTH].path = game->texture[NORTH];
	data->texture[SOUTH].path = game->texture[SOUTH];
	data->texture[WEST].path = game->texture[WEST];
	data->texture[EAST].path = game->texture[EAST];
	data->floor = game->floor_color;
	data->ceiling = game->ceiling_color;
	data->game = game;
}

t_vector	vec(double x, double y)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_mlx_data	init_data(t_data *game)
{
	t_mlx_data	data;

	data = init_ptr();
	get_cub_config(&data, game);
	data.player = init_player(&data);
	data.key = init_key();
	data.mlx = mlx_init();
	if (!data.mlx)
		put_error("mlx_init", &data);
	data.win = mlx_new_window(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!data.win)
		put_error("mlx_new_window", &data);
	init_framebuffer(&data);
	init_texture(&data);
	return (data);
}
