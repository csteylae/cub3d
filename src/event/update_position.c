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

bool	is_wall_collision(t_mlx_data *data, t_vector pos)
{
	double	buffer;

	buffer = 0.1;
	if (data->map[(int)(pos.y + buffer)][(int)(pos.x + buffer)] == '1' ||
		data->map[(int)(pos.y - buffer)][(int)(pos.x + buffer)] == '1' ||
		data->map[(int)(pos.y + buffer)][(int)(pos.x - buffer)] == '1' ||
		data->map[(int)(pos.y - buffer)][(int)(pos.x - buffer)] == '1')
		return (true);
	return (false);
}

void	update_player_position(t_mlx_data *data, t_player *player)
{
	if (data->key.w)
		move_forward(data, player->dir);
	if (data->key.a)
		strafe_left(data, player->dir);
	if (data->key.s)
		move_backward(data, player->dir);
	if (data->key.d)
		strafe_right(data, player->dir);
	if (data->key.left)
		rotate(&data->player, -player->rot_speed);
	if (data->key.right)
		rotate(&data->player, player->rot_speed);
}
