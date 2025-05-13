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

void	rotate(t_minimap_square *player, double angle)
{
	double	old_dir_x = player->dir.x;
	double	old_plane_x = player->plane.x;

	player->dir.x = (player->dir.x * cos(angle)) - (player->dir.y * sin(angle));
	player->dir.y = (old_dir_x * sin(angle)) + (player->dir.y * cos(angle));

	player->plane.x = (player->plane.x * cos(angle)) - (player->plane.y * sin(angle));
	player->plane.y = (old_plane_x * sin(angle)) + (player->plane.y * cos(angle));
}

void	update_position(t_mlx_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->square.pos.x;
	new_y = data->square.pos.y;
	if (data->key.w)
		new_y -= 5;
	if (data->key.a)
		new_x -= 5;
	if (data->key.s)
		new_y += 5;
	if (data->key.d)
		new_x += 5;
    if (data->key.left)
		rotate(&data->square, -ROT_SPEED);
	if (data->key.right)
		rotate(&data->square, ROT_SPEED);
	data->square.pos.x = new_x;
	data->square.pos.y = new_y;
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
