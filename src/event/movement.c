/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:16:28 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/27 11:41:42 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static bool	is_wall_collision(t_mlx_data *data, t_vector pos)
{
	double	buffer;

	buffer = 0.2;
	if (data->map[(int)(pos.y + buffer)][(int)(pos.x + buffer)] == '1' ||
		data->map[(int)(pos.y - buffer)][(int)(pos.x + buffer)] == '1' ||
		data->map[(int)(pos.y + buffer)][(int)(pos.x - buffer)] == '1' ||
		data->map[(int)(pos.y - buffer)][(int)(pos.x - buffer)] == '1')
		return (true);
	return (false);
}

t_vector	move_forward(t_mlx_data *data, t_player *player)
{
	t_vector	new_pos;

	new_pos.x = player->pos.x + (player->dir.x * player->move_speed);
	new_pos.y = player->pos.y + (player->dir.y * player->move_speed);
	if (!is_wall_collision(data, new_pos))
		return (new_pos);
	return (player->pos);
}

t_vector	strafe_right(t_mlx_data *data, t_player *player)
{
	t_vector	new_pos;

	new_pos.x = player->pos.x - (player->dir.y * player->move_speed);
	new_pos.y = player->pos.y + (player->dir.x * player->move_speed);
	if (!is_wall_collision(data, new_pos))
		return (new_pos);
	return (player->pos);
}

t_vector	move_backward(t_mlx_data *data, t_player *player)
{
	t_vector	new_pos;

	new_pos.x = player->pos.x - (player->dir.x * player->move_speed);
	new_pos.y = player->pos.y - (player->dir.y * player->move_speed);
	if (!is_wall_collision(data, new_pos))
		return (new_pos);
	return (player->pos);
}

t_vector	strafe_left(t_mlx_data *data, t_player *player)
{
	t_vector	new_pos;

	new_pos.x = player->pos.x + (player->dir.y * player->move_speed);
	new_pos.y = player->pos.y - (player->dir.x * player->move_speed);
	if (!is_wall_collision(data, new_pos))
		return (new_pos);
	return (player->pos);
}
