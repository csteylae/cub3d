/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:27:57 by csteylae          #+#    #+#             */
/*   Updated: 2025/05/05 19:20:30 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	ft_clear_image(t_mlx_data *data)
{
	int	img_height;
	int	total_bytes;

	img_height = data->map_height * TILE_SIZE;
	total_bytes = img_height * data->framebuffer.line_len;
	ft_memset(data->framebuffer.pixel_addr, 0, total_bytes);
}

void	update_position(t_mlx_data *data)
{
	int	new_x;
	int	new_y;

	new_x = data->player.pos.x;
	new_y = data->player.pos.y;
	if (data->key.w)
		new_y -= 5;
	if (data->key.a)
		new_x -= 5;
	if (data->key.s)
		new_y += 5;
	if (data->key.d)
		new_x += 5;
//	if (is_inside_image(data, new_x + data->player.square.size, new_y + data->player.square.size))
//	{
		data->player.pos.x = new_x;
		data->player.pos.y = new_y;
//	}
}

void	draw_square(t_mlx_data *data)
{
	int	px;
	int	py;
	t_square *square;
	int	color;

	px = 0;
	py = 0;
	square = &data->player.square;
	color = square->color;
	while (py < square->size)
	{
		while (px < square->size)
		{
			if (is_inside_image(data, data->player.pos.x + px , data->player.pos.y + py)) 
				my_pixel_put(&data->framebuffer, data->player.pos.x + px, data->player.pos.y + py, color);
			px++;
		}
		px = 0;
		py++;
	}
}

int	render_frame(t_mlx_data *data)
{
	ft_clear_image(data);
	update_position(data);
	draw_map(data);
	draw_square(data);
	mlx_put_image_to_window(data->mlx, data->win, data->framebuffer.ptr, 0, 0);
	usleep(10000);
	return (0);
}
