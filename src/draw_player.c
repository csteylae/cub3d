/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:59:18 by csteylae          #+#    #+#             */
/*   Updated: 2025/05/13 16:24:30 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int	get_slope(int a, int b)
{
	if (a < b)
		return (1);
	else if (a > b)
		return (-1);
	return (0);
}

static void	draw_line(t_mlx_data *data, int x0, int y0, int x1, int y1)
{
	//bresenham algo to draw a line
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1- x0);
	dy = -abs(y1 - y0);
	sx = get_slope(x0, x1);
	sy = get_slope(y0, y1);
	err = dx + dy;
	while (1)
	{
		if (is_inside_image(data, x0, y0))
			my_pixel_put(&data->framebuffer, x0, y0, RED);
		if (x0 == x1 && y0 == y1)
			return ;
		e2 = err * 2;
		if (e2 >=  dy)
		{
			if (x0 == x1)
				return;
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			if (y0 == y1)
				return ;
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_square(t_mlx_data *data, int posx, int posy)
{
	int	x = 0;
	int	y = 0;
	int size = 20;

	while (y != size)
	{
		x = 0;
		while (x != size)
		{
			if (is_inside_image(data, posx + x, posy + y))
				my_pixel_put(&data->framebuffer, posx + x, posy + y, RED);
			x++;
		}
		y++;
	}
}

void	draw_player(t_mlx_data *data)
{
	//draw square
	int	player_x = data->player.pos.x * TILE_SIZE;
	int	player_y = data->player.pos.y * TILE_SIZE;

	draw_square(data, player_x, player_y);

	//draw direction line
	int	dirx = player_x + (data->player.dir.x * 50);
	int	diry = player_y + (data->player.dir.y * 50);

	draw_line(data, player_x, player_y, dirx, diry);
}
