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

static double	apply_linear_interpolation(int x)
{
	int		x_min;
	int		x_max;
	double	y_min;
	double	y_max;
	double	y;

	x_min = 0;
	x_max = SCREEN_WIDTH -1;
	y_min = -1.0;
	y_max = 1.0;
	y = y_min + (double)(x - x_min) * (y_max - y_min) / (double)(x_max - x_min);
	return (y);
}

static void	calculate_ray_dir(t_player *player, int screen_x, t_ray *ray)
{
	double	screen_ratio;

	screen_ratio = apply_linear_interpolation(screen_x);
	ray->dir.x = player->dir.x + player->plane.x * screen_ratio;
	ray->dir.y = player->dir.y + player->plane.y * screen_ratio;
}

static void	get_wall_dist(t_ray *ray)
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
	get_wall_dist(&ray);
	return (ray);
}
