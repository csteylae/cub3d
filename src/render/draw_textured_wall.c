/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:01:56 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/24 14:42:58 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int get_pixel_color(t_img img, int x, int y)
{
	char *pixel;

	pixel = img.pixel_addr + (y * img.line_len) + (x * (img.bpp / 8));
	return *(int *)pixel;
}

void	draw_vertical_line(t_mlx_data *data, int x, int y_begin, int y_end, int color)
{
	int	y;

	y = y_begin;
	while (y < y_end)
	{
		my_pixel_put(&data->framebuffer, x, y, color);
		y++;
	}
}

void draw_textured_wall(t_mlx_data *data, int screen_x, t_wall wall)
{
    int screen_y;
    double step;
    double tex_pos;
    int tex_y;
    int color;

    step = 1.0 * TILE_SIZE / wall.height;
	if (step < 0.05)
		step = 0.05;
    tex_pos = (wall.begin - SCREEN_HEIGHT / 2.0 + wall.height / 2.0) * step;
	screen_y = wall.begin;
    draw_vertical_line(data, screen_x, 0, wall.begin, SKY_BLUE);
	while (screen_y < wall.end)
	{
       tex_y = (int)tex_pos;
       if (tex_y < 0)
           tex_y = 0;
       if (tex_y >= TILE_SIZE)
           tex_y = TILE_SIZE - 1;
       tex_pos += step;
       color = get_pixel_color(data->texture[wall.side].img, wall.tex_col, tex_y);
       my_pixel_put(&data->framebuffer, screen_x, screen_y, color);
	   screen_y++;
	}
	draw_vertical_line(data, screen_x, wall.end, SCREEN_HEIGHT, FOREST_GREEN);
}
