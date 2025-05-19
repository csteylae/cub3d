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
*/

void draw_filled_circle(t_mlx_data *data, int center_x, int center_y, int radius, int color)
{
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            // If the point is within the circle's radius
            if (x*x + y*y <= radius*radius)
            {
                int draw_x = center_x + x;
                int draw_y = center_y + y;
                
                if (is_inside_image(data, draw_x, draw_y))
                    my_pixel_put(&data->framebuffer, draw_x, draw_y, color);
            }
        }
    }
}

	
void	draw_player(t_mlx_data *data)
{
	int	player_x = data->player.pos.x * TILE_SIZE;
	int	player_y = data->player.pos.y * TILE_SIZE;
	int	radius = TILE_SIZE / 8;
	
	draw_filled_circle(data, player_x, player_y, radius, 0x00ff00);
	//draw_square(data, player_x, player_y);
	t_line	dir_line;
    int dir_line_length = TILE_SIZE / 2;
    dir_line.end.x = player_x + (int)(data->player.dir.x * dir_line_length);
    dir_line.end.y = player_y + (int)(data->player.dir.y * dir_line_length);
	dir_line.start.x = player_x;
	dir_line.start.y = player_y;
    draw_line(data, dir_line, 0x0000FF);	
}
