/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:03:51 by csteylae          #+#    #+#             */
/*   Updated: 2025/07/08 11:26:04 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static double	get_exact_wall_hit(t_mlx_data *data, t_ray ray)
{
	double	hit;

	if (ray.side == 0)
		hit = data->player.pos.y + ray.perp_wall_dist * ray.dir.y;
	else
		hit = data->player.pos.x + ray.perp_wall_dist * ray.dir.x;
	hit -= floor(hit);
	return (hit);
}

static int	get_wall_side(t_ray ray)
{
	if (ray.side == 0)
	{
		if (ray.step.x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (ray.step.y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

t_wall	init_wall(t_mlx_data *data, t_ray ray)
{
	t_wall	wall;

	wall.height = get_wall_height(ray.perp_wall_dist);
	wall.top = get_wall_top(wall.height);
	wall.bottom = get_wall_bottom(wall.height);
	wall.hit = get_exact_wall_hit(data, ray);
	wall.side = get_wall_side(ray);
	return (wall);
}
