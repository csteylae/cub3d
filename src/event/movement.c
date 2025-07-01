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

static void	move_player(t_mlx_data	*data, double dir_x, double dir_y)
{
	t_vector	pos;
	double		speed;
	t_vector	new_pos;

	pos = data->player.pos;
	speed = data->player.move_speed;
	new_pos.x = pos.x + dir_x * speed;
	new_pos.y = pos.y + dir_y * speed;
	if (!is_wall_collision(data, new_pos))
		data->player.pos = new_pos;
}

void	move_forward(t_mlx_data *data, t_vector dir)
{
	move_player(data, dir.x, dir.y);
}

void	move_backward(t_mlx_data *data, t_vector dir)
{
	move_player(data, -dir.x, -dir.y);
}

void	strafe_right(t_mlx_data *data, t_vector dir)
{
	move_player(data, -dir.y, dir.x);
}

void	strafe_left(t_mlx_data *data, t_vector dir)
{
	move_player(data, dir.y, -dir.x);
}
