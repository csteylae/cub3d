/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:12:46 by csteylae          #+#    #+#             */
/*   Updated: 2025/05/05 19:21:58 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

#define KEYSIZE 6

static t_square	init_square(void)
{
	t_square	square;

	square.color = RED;
	square.size = 10;
	return (square);
}

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

static void	init_texture(t_mlx_data *data)
{

/*
	 int	width;
	 int	height;
	data->wall.ptr = mlx_xpm_file_to_image(data->mlx, "../textures/wall.xpm",
		   			&width, &height);
	if (!data->wall.ptr)
		put_error("mlx_xpm_file_image", data);
*/

	data->wall.ptr = mlx_new_image(data->mlx, TILE_SIZE, TILE_SIZE);
	if (!data->wall.ptr)
		put_error("mlx_new_image wall", data);
	data->wall.pixel_addr = mlx_get_data_addr(data->wall.ptr, &data->wall.bpp,
		   					&data->wall.line_len, &data->wall.endian);
	if (!data->wall.pixel_addr)
		put_error("mlx_get_data_addr", data);
	/*
	data->floor.ptr = mlx_xpm_file_to_image(data->mlx, "../textures/floor.xpm",
					 &width, &height);	
	 */
	data->floor.ptr = mlx_new_image(data->mlx, TILE_SIZE, TILE_SIZE);
	if (!data->floor.ptr)
		put_error("mlx_new_image floor", data);
	data->floor.pixel_addr = mlx_get_data_addr(data->floor.ptr, &data->floor.bpp,
							&data->floor.line_len, &data->floor.endian);
	if (!data->floor.pixel_addr)
		put_error("mlx_get_data_addr", data);
}

static void	init_player(t_mlx_data *data)
{
	data->player.square = init_square();
	data->player.pos.x = 64;
	data->player.pos.y = 64;
	data->player.pos.delta_x = 0;
	data->player.pos.delta_y = 0;
	data->player.pos.angle = 0;
	data->player.img.ptr = mlx_new_image(data->mlx, TILE_SIZE, TILE_SIZE);
	if (!data->player.img.ptr)
		put_error("error", data);
	data->player.img.pixel_addr = mlx_get_data_addr(data->player.img.ptr,
		   									&data->player.img.bpp,
											&data->player.img.line_len,
											&data->player.img.endian);
	if (!data->player.img.pixel_addr)
		put_error("error", data);
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

int	get_width_map(char **map)
{
	int	width;

	width = ft_strlen(map[0]);
	return (width);
}

int	get_height_map(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

char	**get_map(void)
{
	static char *map[] = {
		"111111111",
		"100000001",
		"1011P0001",
		"100010001",
		"111111111",
		NULL
	};
	return (map);
}

t_mlx_data	init_data(void)
{
	t_mlx_data	data;

	data.map = get_map();
	data.map_width = get_width_map(data.map);
	data.map_height = get_height_map(data.map);
	data.key = init_key();
	data.mlx = mlx_init();
	if (!data.mlx)
		put_error("mlx_init", &data);
	data.win = mlx_new_window(data.mlx, data.map_width * TILE_SIZE,
							data.map_height * TILE_SIZE, "test");
	if (!data.win)
		put_error("mlx_new_window", &data);
	init_texture(&data);
	init_player(&data);
	init_framebuffer(&data);
	return (data);	
}
