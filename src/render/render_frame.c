/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:27:57 by csteylae          #+#    #+#             */
/*   Updated: 2025/07/03 12:00:48 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	draw_3d_wall(t_mlx_data *data)
{
	int		x;
	t_ray	ray;
	t_wall	wall;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray = cast_ray(data, x);
		wall = init_wall(data, ray);
		draw_textured_wall(data, x, wall, ray);
		x++;
	}
}

int	render_frame(t_mlx_data *data)
{
	ft_clear_image(data);
	update_player_position(data, &data->player);
	draw_3d_wall(data);
	mlx_put_image_to_window(data->mlx, data->win, data->framebuffer.ptr, 0, 0);
	return (0);
}
