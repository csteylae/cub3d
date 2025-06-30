/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:19:28 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/27 17:39:51 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	calculate_ray_dir(t_player *player, int screen_x, t_ray *ray)
{
	double		camera_x;

	camera_x = 2.0 * screen_x / (double)SCREEN_WIDTH - 1.0;
	ray->dir.x = player->dir.x + player->plane.x * camera_x;
	ray->dir.y = player->dir.y + player->plane.y * camera_x;
}

static void	calculate_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
}

t_ray	cast_ray(t_mlx_data *data, int x)
{
	t_ray	ray;

	calculate_ray_dir(&data->player, x, &ray);
	perform_dda(data, &ray);
	calculate_wall_dist(&ray);
	return (ray);
}
