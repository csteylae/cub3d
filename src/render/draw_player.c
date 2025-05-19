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

#include "../../inc/cub3D.h"

static int get_slope(int a, int b)
{
    if (a < b)
        return (1);
    else if (a > b)
        return (-1);
    return (0);
}

void draw_line(t_mlx_data *data, t_line line, int color)
{
    // Bresenham algorithm to draw a line
    t_int_vec dir;
    t_int_vec step;
    t_int_vec current;
    int err;
    int e2;
    
    // Calculate absolute deltas
    dir.x = abs(line.end.x - line.start.x);
    dir.y = -abs(line.end.y - line.start.y);  // Negative for algorithm
    
    // Calculate step directions
    step.x = get_slope(line.start.x, line.end.x);
    step.y = get_slope(line.start.y, line.end.y);
    
    // Initialize error
    err = dir.x + dir.y;
    
    // Start at the beginning point
    current = line.start;
    
    while (1)
    {
        // Draw the current pixel if it's inside the image
        if (is_inside_image(data, current.x, current.y))
            my_pixel_put(&data->framebuffer, current.x, current.y, color);
        
        // Check if we've reached the end
        if (current.x == line.end.x && current.y == line.end.y)
            return;
        
        e2 = err * 2;
        
        // Update x position
        if (e2 >= dir.y)
        {
            if (current.x == line.end.x)
                return;
            err += dir.y;
            current.x += step.x;
        }
        
        // Update y position
        if (e2 <= dir.x)
        {
            if (current.y == line.end.y)
                return;
            err += dir.x;
            current.y += step.y;
        }
    }
}

/*
void	draw_line(t_mlx_data *data, int x0, int y0, int x1, int y1, int color)
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
			my_pixel_put(&data->framebuffer, x0, y0, color);
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

*/
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
//	int	dirx = player_x + (data->player.dir.x * 50);
//	int	diry = player_y + (data->player.dir.y * 50);

//	draw_line(data, player_x, player_y, dirx, diry);
}
