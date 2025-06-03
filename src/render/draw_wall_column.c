#include "../../inc/cub3D.h"

void	draw_wall_column(t_mlx_data *data, t_line wall, int color)
{
	int	y;
//	int	color;

	y = 0;
//	color = 0x808080;
	if (wall.start.x < 0 || wall.start.x >= SCREEN_WIDTH 
		|| wall.end.x < 0 || wall.end.x >= SCREEN_WIDTH)
		return ;
	while (y < wall.start.y)
	{
		//draw the ceiling
		my_pixel_put(&data->framebuffer, wall.start.x, y, 0x87ceeb);
		y++;
	}
	y = wall.start.y;
	while (y < wall.end.y)
	{
		my_pixel_put(&data->framebuffer, wall.start.x, y, color);
		y++;
	}
	y = wall.end.y + 1;
	while (y < SCREEN_HEIGHT)
	{
		//draw ground
		my_pixel_put(&data->framebuffer, wall.start.x, y, 0x228b22);
		y++;
	}
}
