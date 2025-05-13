/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:12:46 by csteylae          #+#    #+#             */
/*   Updated: 2025/05/13 12:57:31 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

#define KEYSIZE 6

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
	int	width;
	int	height;

	width = data->map_width;
	height = data->map_height;
	data->framebuffer.ptr = mlx_new_image(data->mlx, TILE_SIZE * width, TILE_SIZE * height);
	if (!data->framebuffer.ptr)
		put_error("mlx_new_image", data);
	data->framebuffer.pixel_addr = mlx_get_data_addr(data->framebuffer.ptr,
		   							&data->framebuffer.bpp, 
									&data->framebuffer.line_len,
									&data->framebuffer.endian);
	if (!data->framebuffer.pixel_addr)
		put_error("mlx_get_data_addr", data);
}

t_mlx_data	init_data(void)
{
	t_mlx_data	data;

	init_minimap(&data);
	data.player = init_player(&data);
	data.key = init_key();
	data.mlx = mlx_init();
	if (!data.mlx)
		put_error("mlx_init", &data);
	data.win = mlx_new_window(data.mlx, data.map_width * TILE_SIZE,
							data.map_height * TILE_SIZE, "test");
	if (!data.win)
		put_error("mlx_new_window", &data);
	init_framebuffer(&data);
	return (data);	
}
