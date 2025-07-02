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

double	apply_linear_interpolation(t_range x, t_range y, double x_val)
{
	double	y_val;

	y_val = y.min + (x_val - x.min) * (y.max - y.min) / (x.max - x.min);
	return (y_val);
}

t_range	new_range(double min, double max)
{
	t_range	range;

	range.min = min;
	range.max = max;
	return (range);
}

static void	calculate_ray_dir(t_player *player, int screen_x, t_ray *ray)
{
	double	screen_ratio;
	t_range	input;
	t_range	output;

	input = new_range(0.0, SCREEN_WIDTH - 1);
	output = new_range(-1.0, 1.0);
	screen_ratio = apply_linear_interpolation(input, output, screen_x);
	ray->dir.x = player->dir.x + player->plane.x * screen_ratio;
	ray->dir.y = player->dir.y + player->plane.y * screen_ratio;
}

static void	calculate_perp_wall_dist(t_ray *ray)
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
	calculate_perp_wall_dist(&ray);
	return (ray);
}
