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

static t_vector	calc_ray_dir(t_player *player, int screen_x)
{
	double		camera_x;
	t_vector	ray_dir;

	camera_x = 2.0 * screen_x / (double)SCREEN_WIDTH - 1.0;
	ray_dir.x = player->dir.x + player->plane.x * camera_x;
	ray_dir.y = player->dir.y + player->plane.y * camera_x;
	return (ray_dir);
}

static void	calculate_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
}

void	cast_ray(t_mlx_data *data)
{
	int		screen_x;
	t_ray	ray;
	t_wall	wall;

	screen_x = 0;
	while (screen_x < SCREEN_WIDTH)
	{
		ray.dir = calc_ray_dir(&data->player, screen_x);
		initialize_dda(&data->player, &ray);
		perform_dda(data, &ray);
		calculate_wall_dist(&ray);
		wall = init_wall(data, ray);
		draw_textured_wall(data, screen_x, wall);
		screen_x++;
	}
}
