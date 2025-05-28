#include "../../inc/cub3D.h"

void	draw_wall_column(t_mlx_data *data, int x, int draw_start, int draw_end)
{
	int	y;
	int	color;

	y = 0;
	color = 0x808080;
	if (x < 0 || x>= SCREEN_WIDTH)
		return ;
	while (y < draw_start)
	{
		//draw the ceiling
		my_pixel_put(&data->framebuffer, x, y, 0x87ceeb);
		y++;
	}
	y = draw_start;
	while (y < draw_end)
	{
		my_pixel_put(&data->framebuffer,x, y, color);
		y++;
	}
	y = draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		//draw ground
		my_pixel_put(&data->framebuffer,x, y, 0x228b22);
		y++;
	}
}
