/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:01:56 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/27 16:12:16 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	draw_ceiling(t_mlx_data *data, int screen_x, int y_begin, int y_end)
{
	int	y;

	y = y_begin;
	while (y < y_end)
	{
		my_pixel_put(&data->framebuffer, screen_x, y, data->ceiling);
		y++;
	}
}

static void	draw_ground(t_mlx_data *data, int screen_x, int y_begin, int y_end)
{
	int	y;

	y = y_begin;
	while (y < y_end)
	{
		my_pixel_put(&data->framebuffer, screen_x, y, data->floor);
		y++;
	}
}

double	get_texel_ratio(int texture_size, int wall_height)
{
	return ((double)texture_size / (double)wall_height);
}

double	get_starting_row_texture(double txl_ratio, t_wall wall)
{
	double	row;

	row = (wall.top - SCREEN_HEIGHT / 2.0 + wall.height / 2.0) * txl_ratio;
	return (row);
}

void	draw_textured_wall(t_mlx_data *data, int screen_x, t_wall wall)
{
	int		screen_y;
	double	txl_ratio;
	double	tex_pos;
	int		color;

	txl_ratio = get_texel_ratio(TILE_SIZE, wall.height);
	tex_pos = get_starting_row_texture(txl_ratio, wall);//(wall.top - SCREEN_HEIGHT / 2.0 + wall.height / 2.0) * step;
	screen_y = wall.top;
	draw_ceiling(data, screen_x, 0, wall.top);
	while (screen_y < wall.bottom)
	{
		color = get_pixel_color(data->texture[wall.side].img, wall.tex_col,
				(int)tex_pos);
		my_pixel_put(&data->framebuffer, screen_x, screen_y, color);
		tex_pos += txl_ratio;
		screen_y++;
	}
	draw_ground(data, screen_x, wall.bottom, SCREEN_HEIGHT);
}


/*
static void	draw_ceiling(t_mlx_data *data, int screen_x, int y_begin, int y_end)
{
	int	y;

	y = y_begin;
	while (y < y_end)
	{
		my_pixel_put(&data->framebuffer, screen_x, y, data->ceiling);
		y++;
	}
}

static void	draw_ground(t_mlx_data *data, int screen_x, int y_begin, int y_end)
{
	int	y;

	y = y_begin;
	while (y < y_end)
	{
		my_pixel_put(&data->framebuffer, screen_x, y, data->floor);
		y++;
	}
}


void	draw_textured_wall(t_mlx_data *data, int screen_x, t_wall wall)
{
	int		screen_y;
	double	step;
	double	tex_pos;
	int		tex_row;
	int		color;

	step = 1.0 * TILE_SIZE / wall.height;
	tex_pos = (wall.top - SCREEN_HEIGHT / 2.0 + wall.height / 2.0) * step;
	screen_y = wall.top;
	draw_ceiling(data, screen_x, 0, wall.top);
	while (screen_y < wall.bottom)
	{
		tex_row = (int)tex_pos & (TILE_SIZE - 1);
		if (tex_row < 0)
			tex_row = 0;
		if (tex_row >= TILE_SIZE)
			tex_row = TILE_SIZE - 1;
		tex_pos += step;
		color = get_pixel_color(data->texture[wall.side].img, wall.tex_col,
				tex_row);
		my_pixel_put(&data->framebuffer, screen_x, screen_y, color);
		screen_y++;
	}
	draw_ground(data, screen_x, wall.bottom, SCREEN_HEIGHT);
}
*/
