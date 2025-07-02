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

int	calculate_projection(double obj_size, double focal_len, double dist_to_obj)
{
	int	projected_height;

	projected_height = (obj_size * focal_len * SCREEN_HEIGHT) / dist_to_obj;
	return ((int)projected_height);
}

int	get_wall_height(double perp_wall_dist)
{
	return (calculate_projection(1.0, 1.0, perp_wall_dist));
}

int	get_wall_top(int wall_height)
{
	int	wall_top;

	wall_top = -wall_height / 2 + SCREEN_HEIGHT / 2;
	if (wall_top < 0)
		wall_top = 0;
	return (wall_top);
}

int	get_wall_bottom(int wall_height)
{
	int	wall_bottom;

	wall_bottom = wall_height / 2 + SCREEN_HEIGHT / 2;
	if (wall_bottom >= SCREEN_HEIGHT)
		wall_bottom = SCREEN_HEIGHT - 1;
	return (wall_bottom);
}

t_wall	init_wall(t_mlx_data *data, t_ray ray)
{
	t_wall	wall;

	wall.height = get_wall_height(ray.perp_wall_dist);
	wall.top = get_wall_top(wall.height);
	wall.bottom = get_wall_bottom(wall.height);
	wall.hit = get_exact_wall_hit(data, ray);
	wall.tex_col = get_texture_column(wall.hit, ray);
	wall.side = get_wall_side(ray);
	return (wall);
}
