/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:12:46 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/27 18:22:53 by csteylae         ###   ########.fr       */
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

void	init_framebuffer(t_mlx_data *data)
{
	data->framebuffer.ptr = mlx_new_image(data->mlx,
			SCREEN_WIDTH,
			SCREEN_HEIGHT);
	if (!data->framebuffer.ptr)
		put_error("mlx_new_image", data);
	data->framebuffer.pixel_addr = mlx_get_data_addr(data->framebuffer.ptr,
			&data->framebuffer.bpp,
			&data->framebuffer.line_len,
			&data->framebuffer.endian);
	if (!data->framebuffer.pixel_addr)
		put_error("mlx_get_data_addr", data);
}

void	get_info(t_mlx_data *data, t_data game)
{
	data->map = game.map;
	data->texture[NORTH].path = game.texture[NORTH];
	data->texture[SOUTH].path = game.texture[SOUTH];
	data->texture[WEST].path = game.texture[WEST];
	data->texture[EAST].path = game.texture[EAST];
	data->floor = game.floor_color; 
	data->ceiling = game.ceiling_color;
}

t_mlx_data	init_data(t_data game)
{
	t_mlx_data	data;

//	init_minimap(&data);
	get_info(&data, game);
//	data.ceiling = SKY_BLUE;
//	data.floor = FOREST_GREEN;
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
