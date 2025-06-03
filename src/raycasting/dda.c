/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:20:10 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/03 11:28:19 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../inc/cub3D.h"

/* 
 *  The dda algorithm will move from one grid cell to another until
 *  it hits a wall.
 *
 *  Once ray.dir is calculated and because it the ray will form an angle
 *  in our map, we need to know the distance the angle of the ray takes 
 *  to travel a whole grid cell (delta_dist),
 *  according,so,  to its direction vector (fabs(1 / ray_dir))
 *
 * 	Then, because our player can be anywhere within a grid cell 
 * 	(for ex player.pos.x = 2.344, player.pos.y = 1.89), we need to calculate the
 * 	distance it takes from our initial position to the boundary grid, according
 * 	to the direction (that is captured by step :
 * 	if step == 1 it will be right/down and if it -1 it will be left/up).
 * 	According to the direction, the calculation is slightly different dependant
 * 	of the direction.
 *
 *  Once the dda is initialized, we run the loop that
 *  just check which of side_dist.x or y 
 *  is the smaller (aka which one the ray will first encounter) and increment
 *  the ray->map x or y according to this. We continue to move until a wall
 *  is found.
 *
 *  */

static t_vector	get_delta_dist(t_vector raydir)
{
	t_vector	delta_dist;

	if (fabs(raydir.x) < EPSILON) // if the ray is perfectly vertical we need to handle div by 0 by setting a very high value
		delta_dist.x = SAFE_LARGE_VALUE; //we check with fabs because -0.000000000001 and 0.000000001 will causes the same shit
	else
	{
		delta_dist.x = fabs(1.0 / raydir.x);
		if (delta_dist.x > SAFE_LARGE_VALUE)
			delta_dist.x = SAFE_LARGE_VALUE;
	}
	if  (fabs(raydir.y) < EPSILON) //if the ray is floating point good enough to be considered as perfectly horizontal
		delta_dist.y = SAFE_LARGE_VALUE; //give it a value choosen to rpz safely infity for our calcul
	else
	{
		delta_dist.y = fabs(1.0 / raydir.y);
		if (delta_dist.y > SAFE_LARGE_VALUE)
			delta_dist.y = SAFE_LARGE_VALUE;
	}
	return (delta_dist);
}

static t_vector get_side_dist(t_ray *ray, t_vector player_pos)
{
	t_vector	side_dist;

	if (ray->dir.x < 0) //move to the previous left grid
	{
		ray->step.x = -1;	
		side_dist.x = (player_pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1; 
		side_dist.x = ((ray->map.x + 1.0) - player_pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0) //if raydir is going up
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
	if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height)
		return (false);
	if (!data->map[y] || !data->map[y][x])
		return (false);
	return (true);
}

void	perform_dda(t_mlx_data *data, t_ray *ray)
{
	while (ray->hit == false)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = HORIZONTAL;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = VERTICAL;
		}
		if (!is_valid_map_position(data, ray->map.x, ray->map.y))
		{
			ray->hit = true;
			break;
		}
		if (data->map[ray->map.y][ray->map.x] == '1')
			ray->hit = true;
	}
}
