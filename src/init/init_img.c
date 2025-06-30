#include "../../inc/cub3D.h"

t_img	init_img(void)
{
	t_img	img;

	img.ptr = NULL;
	img.pixel_addr = NULL;
	img.bpp = -1;
	img.line_len = -1;
	img.endian = -1;
	return (img);
}

void	init_framebuffer(t_mlx_data *data)
{
	data->framebuffer.ptr = mlx_new_image(data->mlx,
			SCREEN_WIDTH,
			SCREEN_HEIGHT);
	if (!data->framebuffer.ptr)
		put_error("mlx_new_image", data);
	data->framebuffer.pixel_addr = mlx_get_data_addr(data->framebuffer.ptr,
			&data->framebuffer.bpp,
			&data->framebuffer.line_len,
			&data->framebuffer.endian);
	if (!data->framebuffer.pixel_addr)
		put_error("mlx_get_data_addr", data);
}
