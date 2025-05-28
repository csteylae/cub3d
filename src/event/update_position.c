/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:15:19 by csteylae          #+#    #+#             */
/*   Updated: 2025/05/13 16:23:41 by csteylae         ###   ########.fr       */
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
	if (data->map[(int)pos.y][(int)pos.x] == '1')
		return (true);
	return (false);
}


static t_vector	get_new_pos(t_mlx_data *data, t_player *player, char c)
{
	// when we move the player, we're changing their position based on their current direction. 
	// The basic formula is new_pos = current_pos + (move_speed * dir)
	//this setup will works for the  2D top-down view and the 3D 1st person view
	t_vector	new_pos;
	double		move_speed;

	move_speed = player->move_speed;
	new_pos = player->pos;
	if (c == 'W') //move forward
	{
		new_pos.x = player->pos.x + (player->dir.x * move_speed);
		new_pos.y = player->pos.y + (player->dir.y * move_speed);
	}
	else if (c == 'A')
	{
		// we use the left and right relative to the direction the player looks 
		// math trick : perpendicular vector to the direction vector
		new_pos.x = player->pos.x - (player->dir.y * player->move_speed);
		new_pos.y = player->pos.y + (player->dir.x * player->move_speed);
	}
	else if (c == 'S') //move backward. We need to go to the opposite direction
	{
		new_pos.x = player->pos.x - (player->dir.x * player->move_speed);
		new_pos.y = player->pos.y - (player->dir.y * player->move_speed); 
	}
	else if (c == 'D')
	{
		new_pos.x = player->pos.x + (player->dir.y * move_speed);
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
