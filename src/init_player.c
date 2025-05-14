/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:52:46 by csteylae          #+#    #+#             */
/*   Updated: 2025/05/13 14:58:08 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static bool	is_player_found(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

static t_vector	get_player_pos(t_mlx_data *data)
{
	int			x;
	int			y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (is_player_found(data->map[y][x]))
				return (vec(x, y));
			x++;
		}
		y++;
	}
	printf("error. no player found\n\n");
	exit(EXIT_FAILURE);
}

static t_vector	get_dir(t_mlx_data *data, t_vector pos)
{
	int	x;
	int	y;

	x = pos.x;
	y = pos.y;
	if (data->map[y][x] == 'S')
		return (vec(0, 1));
	else if (data->map[y][x] == 'N')
		return (vec(0, -1));
	else if (data->map[y][x] == 'E')
		return (vec(1, 0));
	else if (data->map[y][x] == 'W')
		return (vec(-1, 0));
	printf("Error. No correct direction\n\n");
	exit(EXIT_FAILURE);
}

t_vector	get_perpendicular_plane(t_vector dir, double plane_len)
{
	t_vector	plane;

	plane.x = -dir.y * plane_len;
	plane.y = dir.x * plane_len;
	return (plane);
}

t_player	init_player(t_mlx_data *data)
{
	t_player	player;

	player.pos = get_player_pos(data);
	player.dir = get_dir(data, player.pos);
	player.fov = (66 * M_PI) / 180; 
	player.plane_len = tan(player.fov / 2);
	player.plane = get_perpendicular_plane(player.dir, player.plane_len);;
	player.move_speed = 0.02;
	player.rot_speed = 0.02;
	return (player);
}
