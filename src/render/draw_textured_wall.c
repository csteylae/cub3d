/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:01:56 by csteylae          #+#    #+#             */
/*   Updated: 2025/07/08 11:31:22 by csteylae         ###   ########.fr       */
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

void	draw_textured_wall(t_mlx_data *data, int pxl_x, t_wall wall, t_ray ray)
{
	int		pxl_y;
	double	txl_ratio;
	double	tex_pos;
	int		color;

	wall.tex_col = get_texture_column(data, wall, ray);
	txl_ratio = get_texel_ratio(data->texture[wall.side].height, wall.height);
	tex_pos = get_starting_row_texture(txl_ratio, wall);
	pxl_y = wall.top;
	draw_ceiling(data, pxl_x, 0, wall.top);
	while (pxl_y < wall.bottom)
	{
		color = get_pixel_color(data->texture[wall.side].img, wall.tex_col,
				(int)tex_pos);
		my_pixel_put(&data->framebuffer, pxl_x, pxl_y, color);
		tex_pos += txl_ratio;
		pxl_y++;
	}
	draw_ground(data, pxl_x, wall.bottom, SCREEN_HEIGHT);
}
