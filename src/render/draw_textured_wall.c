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

int	get_pixel_color(t_img img, int x, int y)
{
	char	*pixel;

	pixel = img.pixel_addr + (y * img.line_len) + (x * (img.bpp / 8));
	return (*(int *)pixel);
}

void	draw_ceiling(t_mlx_data *data, int screen_x, int y_begin, int y_end)
{
	int	y;

	y = y_begin;
	while (y < y_end)
	{
		my_pixel_put(&data->framebuffer, screen_x, y, data->ceiling);
		y++;
	}
}

void	draw_ground(t_mlx_data *data, int screen_x, int y_begin, int y_end)
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
	int		tex_y;
	int		color;

	step = 1.0 * TILE_SIZE / wall.height;
	tex_pos = (wall.begin - SCREEN_HEIGHT / 2.0 + wall.height / 2.0) * step;
	screen_y = wall.begin;
	draw_ceiling(data, screen_x, 0, wall.begin);
	while (screen_y < wall.end)
	{
		tex_y = (int)tex_pos & (TILE_SIZE - 1);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= TILE_SIZE)
			tex_y = TILE_SIZE - 1;
		tex_pos += step;
		color = get_pixel_color(data->texture[wall.side].img, wall.tex_col,
				tex_y);
		my_pixel_put(&data->framebuffer, screen_x, screen_y, color);
		screen_y++;
	}
	draw_ground(data, screen_x, wall.end, SCREEN_HEIGHT);
}
