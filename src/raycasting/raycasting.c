/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:19:28 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/03 14:16:37 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

t_vector	calculate_ray_dir(t_mlx_data *data, t_player *player, int screen_x, int screen_width)
{
	double		camera_x; 
	t_vector	ray_dir;
	
	if (screen_width <= 0)
	{
		printf("Error: invalid screen width\n");
		close_cub3D(data);
	}
	camera_x = 2.0 * screen_x / (double)screen_width - 1.0; 
	ray_dir.x = player->dir.x + player->plane.x * camera_x;
	ray_dir.y = player->dir.y + player->plane.y *camera_x;
	return (ray_dir);
}

static void	calculate_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
	if (!isfinite(ray->perp_wall_dist) || ray->perp_wall_dist <= 0.001)
		ray->perp_wall_dist = 0.01;
}

void	cast_ray(t_mlx_data *data)
{
	int		screen_x;
	t_ray	ray;

	screen_x = 0;
	while (screen_x < SCREEN_WIDTH)
	{
		ray.dir = calculate_ray_dir(data, &data->player, screen_x, SCREEN_WIDTH);
		initialize_dda(&data->player, &ray);
		perform_dda(data, &ray);
		calculate_wall_dist(&ray);
		draw_textured_wall(data, ray, screen_x);
		screen_x++;
	}
}
