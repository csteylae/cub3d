/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:15:19 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/27 11:40:49 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	rotate(t_player *player, double angle)
{
	t_vector	prev_dir;
	t_vector	prev_plane;

	prev_dir = player->dir;
	prev_plane = player->plane;
	player->dir.x = (prev_dir.x * cos(angle)) - (prev_dir.y * sin(angle));
	player->dir.y = (prev_dir.x * sin(angle)) + (prev_dir.y * cos(angle));
	player->plane.x = (prev_plane.x * cos(angle)) - (prev_plane.y * sin(angle));
	player->plane.y = (prev_plane.x * sin(angle)) + (prev_plane.y * cos(angle));
}

void	update_position(t_mlx_data *data, t_player *player)
{
	if (data->key.w)
		player->pos = move_forward(data, player);
	if (data->key.a)
		player->pos = strafe_left(data, player);
	if (data->key.s)
		player->pos = move_backward(data, player);
	if (data->key.d)
		player->pos = strafe_right(data, player);
	if (data->key.left)
		rotate(&data->player, -player->rot_speed);
	if (data->key.right)
		rotate(&data->player, player->rot_speed);
}
