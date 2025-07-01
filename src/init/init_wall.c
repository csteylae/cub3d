/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:03:51 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/27 18:32:33 by csteylae         ###   ########.fr       */
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

static int	get_texture_column(double wall_hit, t_ray ray)
{
	int	tex_column;

	tex_column = (int)(wall_hit * (double)TILE_SIZE);
	if (tex_column < 0)
		tex_column = 0;
	if (tex_column >= TILE_SIZE)
		tex_column = TILE_SIZE - 1;
	if (ray.side == 0 && ray.dir.x > 0)
		tex_column = TILE_SIZE - tex_column - 1;
	if (ray.side == 1 && ray.dir.y < 0)
		tex_column = TILE_SIZE - tex_column - 1;
	return (tex_column);
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

	wall.height = (int)(SCREEN_HEIGHT / ray.perp_wall_dist);
	if (wall.height < 0)
		wall.height = 0;
	wall.begin = -wall.height / 2 + SCREEN_HEIGHT / 2;
	if (wall.begin < 0)
		wall.begin = 0;
	wall.end = wall.height / 2 + SCREEN_HEIGHT / 2;
	if (wall.end >= SCREEN_HEIGHT)
		wall.end = SCREEN_HEIGHT - 1;
	wall.hit = get_exact_wall_hit(data, ray);
	wall.tex_col = get_texture_column(wall.hit, ray);
	wall.side = get_wall_side(ray);
	return (wall);
}
