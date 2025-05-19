/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:27:57 by csteylae          #+#    #+#             */
/*   Updated: 2025/05/13 16:15:50 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	ft_clear_image(t_mlx_data *data)
{
	int	img_height;
	int	total_bytes;

	img_height = data->map_height * TILE_SIZE;
	total_bytes = img_height * data->framebuffer.line_len;
	ft_memset(data->framebuffer.pixel_addr, 0, total_bytes);
}

int	render_frame(t_mlx_data *data)
{
	ft_clear_image(data);
	update_position(data, &data->player);
	draw_map(data);
	cast_ray(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->framebuffer.ptr, 0, 0);
//	printf("player pos : %f %f\n\n", data->player.pos.x, data->player.pos.y);
	return (0);
}
