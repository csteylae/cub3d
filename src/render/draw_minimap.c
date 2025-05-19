#include "../../inc/cub3D.h"

bool	is_inside_image(t_mlx_data *data, int x, int y)
{
	if (x < 0 || y < 0)
		return (false);
	if (x > (data->map_width * TILE_SIZE) || y > (data->map_height * TILE_SIZE))
		return (false);
	return (true);
}

void	draw_tile(t_mlx_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < TILE_SIZE-1)
	{
		while (j < TILE_SIZE -1)
		{
			if (is_inside_image(data, x + j, y + i)) 
				my_pixel_put(&data->framebuffer, x + j, y + i, color);
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_map(t_mlx_data *data)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	color = 0;
	while (data->map[y])
	{
		while(data->map[y][x])
		{
			if (data->map[y][x] == '1')
				color = 0x000000;
			else
				color = 0xffffff;
			draw_tile(data, x * TILE_SIZE, y * TILE_SIZE, color);
			x++;
		}
		x = 0;
		y++;
	}
}
