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
	int		new_x;
	int		new_y;

	new_x = data->square.x;
	new_y = data->square.y;
	if (data->key.w)
		new_y -= 5;
	if (data->key.a)
		new_x -= 5;
	if (data->key.s)
		new_y += 5;
	if (data->key.d)
		new_x += 5;
    if (data->key.left == 1)
	{
        data->square.rot_angle = fmod(data->square.rot_angle - ROT_SPEED, 2 * PI);
	}
	if (data->key.right == 1)
	{
		data->square.rot_angle = fmod(data->square.rot_angle + ROT_SPEED, 2 * PI);
	}
	if (data->square.rot_angle < 0)
	{
		data->square.rot_angle += 2 * PI;
	}
	data->square.x = new_x;
	data->square.y = new_y;
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
