#include "../inc/cub3D.h"

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

	delta_x = abs(x - from_x);
	delta_y = abs(y - from_y);
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

void	draw_square(t_mlx_data *data)
{
	int	px;
	int	py;
	t_minimap_square *square;
	int	color;

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
	draw_line(data, square->x + square->size / 2, square->y, 
			square->x + square->size / 2, square->y - 30, RED);
}
