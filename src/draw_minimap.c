#include "../inc/cub3D.h"

/*
static void	draw_line(t_mlx_data *data, int from_x, int from_y, int x, int y, int col)
{
	double	delta_x;
	double	delta_y;
	int		total_pxl;
	double	x_inc;
	double	y_inc;
	int		i =0;
	double	curr_x;
	double	curr_y;

	delta_x = x - from_x;
	delta_y = y - from_y;
	delta_x = fabs(delta_x);
	delta_y = fabs(delta_y);

	if (delta_x > delta_y)
		total_pxl = delta_x;
	else
		total_pxl = delta_y;
	x_inc = delta_x / total_pxl;
	y_inc = delta_y / total_pxl;
	curr_x = from_x;
	curr_y = from_y;
	while (i < total_pxl)
	{
		my_pixel_put(&data->framebuffer, (int)curr_x, (int)curr_y, col);
		printf("Drawing pixel at: (%d, %d)\n", (int)curr_x, (int)curr_y);
		curr_x += x_inc;
		curr_y += y_inc;
		i++;
	}	
}
*/

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

void	draw_square(t_mlx_data *data)
{
	int	px;
	int	py;
	t_minimap_square *square;
	int	color;

	int	end_x;
	int	end_y;
	int	center_x;
	int	center_y;

	int	line_len = 30;

	px = 0;
	py = 0;
	square = &data->square;
	color = square->color;
	while (py < square->size)
	{
		while (px < square->size)
		{
			if (is_inside_image(data, square->x + px ,square->y + py)) 
				my_pixel_put(&data->framebuffer, square->x + px, square->y + py, color);
			px++;
		}
		px = 0;
		py++;
	}
	center_x = square->x + square->size / 2;
	center_y = square->y + square->size / 2;

	end_x = center_x + cos(square->rot_angle) * line_len;
	end_y = center_y - sin(square->rot_angle) * line_len;

	draw_line(data, center_x, center_y, 
			end_x, end_y);
}
