/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:20:10 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/27 17:05:47 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

/*
 * DDA (Digital Differential Analyzer) is used to trace the ray from 
 * the player's position through the grid-based map, 
 * stepping from one cell to the next, until a wall is hit.
 *
 * First, we compute `delta_dist`,
 * which represents how far the ray has to travel along the x or y direction
 * to move from one side of a grid cell to the next.
 * It's based on the ray dir and uses the formula: delta = fabs(1 / ray_dir).
 * We need to check if the ray vector is perfectly horizontal or vertical 
 * and if so we need to give it a value that rpz safely the "infinity"
 *
 * Then we compute `side_dist`, which is the distance 
 * from the player's exact position to the first x or y grid boundary,
 * depending on the ray direction.
 * This distance depends on whether the ray is stepping left/right or up/down,
 * and is used to decide which side the ray hits first.
 *
 * The DDA loop compares `side_dist.x` and `side_dist.y`,
 * and steps through the grid in the direction of the smaller one. 
 * We increment `side_dist` by `delta_dist` at each step to simulate
 * the ray traversal.
 *
 * The loop ends when a wall cell is encountered, 
 * or if the ray goes out of bounds.
 */

static t_vector	get_delta_dist(t_vector raydir)
{
	t_vector	delta_dist;

	if (fabs(raydir.x) < EPSILON)
		delta_dist.x = SAFE_LARGE_VALUE;
	else
	{
		delta_dist.x = fabs(1.0 / raydir.x);
		if (delta_dist.x > SAFE_LARGE_VALUE)
			delta_dist.x = SAFE_LARGE_VALUE;
	}
	if (fabs(raydir.y) < EPSILON)
		delta_dist.y = SAFE_LARGE_VALUE;
	else
	{
		delta_dist.y = fabs(1.0 / raydir.y);
		if (delta_dist.y > SAFE_LARGE_VALUE)
			delta_dist.y = SAFE_LARGE_VALUE;
	}
	return (delta_dist);
}

static t_vector	get_side_dist(t_ray *ray, t_vector player_pos)
{
	t_vector	side_dist;

	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		side_dist.x = (player_pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		side_dist.x = ((ray->map.x + 1.0) - player_pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		side_dist.y = (player_pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		side_dist.y = ((ray->map.y + 1.0) - player_pos.y) * ray->delta_dist.y;
	}
	return (side_dist);
}

void	initialize_dda(t_player *player, t_ray *ray)
{
	ray->map.x = (int)player->pos.x;
	ray->map.y = (int)player->pos.y;
	ray->delta_dist = get_delta_dist(ray->dir);
	ray->side_dist = get_side_dist(ray, player->pos);
	ray->hit = false;
}

static bool	is_valid_map_position(t_mlx_data *data, int x, int y)
{
	if (!data->map[y] || !data->map[y][x])
		return (false);
	return (true);
}

void	perform_dda(t_mlx_data *data, t_ray *ray)
{
	initialize_dda(&data->player, ray);
	while (ray->hit == false)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (!is_valid_map_position(data, ray->map.x, ray->map.y))
		{
			ray->hit = true;
			break ;
		}
		if (data->map[ray->map.y][ray->map.x] == '1')
			ray->hit = true;
	}
}
