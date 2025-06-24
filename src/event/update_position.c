/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:15:19 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/24 15:55:20 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	rotate(t_player *player, double angle)
{
	double	old_dir_x = player->dir.x;
	double	old_plane_x = player->plane.x;

	player->dir.x = (player->dir.x * cos(angle)) - (player->dir.y * sin(angle));
	player->dir.y = (old_dir_x * sin(angle)) + (player->dir.y * cos(angle));
	player->plane.x = (player->plane.x * cos(angle)) - (player->plane.y * sin(angle));
	player->plane.y = (old_plane_x * sin(angle)) + (player->plane.y * cos(angle));
}


static bool	is_wall_collision(t_mlx_data *data, t_vector pos)
{
	double collision_buffer;

	collision_buffer = 0.2;
	if (data->map[(int)(pos.y + collision_buffer)][(int)(pos.x + collision_buffer)] == '1' ||
		data->map[(int)(pos.y - collision_buffer)][(int)(pos.x + collision_buffer)] == '1' ||
		data->map[(int)(pos.y + collision_buffer)][(int)(pos.x - collision_buffer)] == '1' ||
		data->map[(int)(pos.y - collision_buffer)][(int)(pos.x - collision_buffer)] == '1')
		return (true);
	return (false);
}

static t_vector	get_new_pos(t_mlx_data *data, t_player *player, char c)
{
	t_vector	new_pos;

	new_pos = player->pos;
	if (c == 'W')
	{
		new_pos.x = player->pos.x + (player->dir.x * player->move_speed);
		new_pos.y = player->pos.y + (player->dir.y * player->move_speed);
	}
	else if (c == 'D')
	{
		new_pos.x = player->pos.x - (player->dir.y * player->move_speed);
		new_pos.y = player->pos.y + (player->dir.x * player->move_speed);
	}
	else if (c == 'S') //move backward. We need to go to the opposite direction
	{
		new_pos.x = player->pos.x - (player->dir.x * player->move_speed);
		new_pos.y = player->pos.y - (player->dir.y * player->move_speed); 
	}
	else if (c == 'A')
	{
		new_pos.x = player->pos.x + (player->dir.y * player->move_speed);
		new_pos.y = player->pos.y - (player->dir.x * player->move_speed);
	}
	if (!is_wall_collision(data, new_pos))
		return (new_pos);
	return (player->pos);
}

void	update_position(t_mlx_data *data, t_player *player)
{
	if (data->key.w)
		player->pos = get_new_pos(data, player, 'W');
	if (data->key.a)
		player->pos = get_new_pos(data, player, 'A');
	if (data->key.s)
		player->pos = get_new_pos(data, player, 'S');
	if (data->key.d)
		player->pos = get_new_pos(data, player, 'D');
    if (data->key.left)
		rotate(&data->player, -player->rot_speed);
	if (data->key.right)
		rotate(&data->player, player->rot_speed);
}
