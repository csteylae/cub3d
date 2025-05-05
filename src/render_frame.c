/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:27:57 by csteylae          #+#    #+#             */
/*   Updated: 2025/05/05 19:06:37 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

bool	is_inside_image(t_mlx_data *data, int x, int y)
{
	if (x < 0 || y < 0)
		return (false);
	if (x + data->square.size > WIDTH || y + data->square.size >= HEIGHT)
		return (false);
	return (true);
}

void	draw_square(t_mlx_data *data, t_square square)
{
	int	x = 0;
	int	y = 0;

	while (y < square.size)
	{
		while (x < square.size)
		{
			if (is_inside_image(data, data->square.pos.x + x, data->square.pos.y + y))
				my_pixel_put(&data->img, square.pos.x + x, square.pos.y + y, RED);
			x++;
		}
		x = 0;
		y++;
	}
}

void	ft_clear_image(t_mlx_data *data)
{
	ft_memset(data->img.pixel_addr, 0, HEIGHT * data->img.line_len);
}

void	update_position(t_mlx_data *data)
{
	int	new_x;
	int	new_y;

	new_x = data->square.pos.x;
	new_y = data->square.pos.y;
	if (data->key.w)
		new_y -= 10;
	if (data->key.a)
		new_x -= 10;
	if (data->key.s)
		new_y += 10;
	if (data->key.d)
		new_x += 10;
	if (is_inside_image(data, new_x, new_y))
	{
		data->square.pos.x = new_x;
		data->square.pos.y = new_y;
	}
}

int	render_frame(t_mlx_data *data)
{
	ft_clear_image(data);
	update_position(data);
	draw_square(data, data->square);
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
	return (0);
}
