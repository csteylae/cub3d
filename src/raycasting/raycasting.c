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
	if (ray->side == HORIZONTAL)
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
}

static t_line	get_wall_column(int x, t_ray ray)
{
	int	wall_height;
	t_line	wall_column;

	wall_height = (int)SCREEN_HEIGHT / ray.perp_wall_dist;
	wall_column.start.x = x;
	wall_column.start.y = -wall_height / 2 + SCREEN_HEIGHT / 2;
	if (wall_column.start.y < 0)
		wall_column.start.y = 0;
	wall_column.end.x = x;
	wall_column.end.y = wall_height / 2 + SCREEN_HEIGHT / 2;
	if (wall_column.end.y >= SCREEN_HEIGHT)
		wall_column.end.y = SCREEN_HEIGHT - 1;
	return (wall_column);
}

int	get_wall_side(t_ray ray)
{
	if (ray.side == HORIZONTAL)
	{
		if (ray.step.x > 0) // EAST_SIDE
			return (RED);
		return (BLUE); //WEST
	}
	if (ray.step.y > 0) // SOUTH
		return (YELLOW);
	return (GREEN); //NORTH
}

void	cast_ray(t_mlx_data *data)
{
	int		screen_x;
	t_ray	ray;
	t_line	wall_column;

	int	color;

	screen_x = 0;
	while (screen_x < SCREEN_WIDTH)
	{
		ray.dir = calculate_ray_dir(data, &data->player, screen_x, SCREEN_WIDTH);
		initialize_dda(&data->player, &ray);
		perform_dda(data, &ray);
		calculate_wall_dist(&ray);
		if (!isfinite(ray.perp_wall_dist) || ray.perp_wall_dist <= 0.001)
			ray.perp_wall_dist = 0.01;
		wall_column = get_wall_column(screen_x, ray);
		color = get_wall_side(ray);
		if (ray.side == VERTICAL)
			color /= 2;
		draw_wall_column(data, wall_column, color);
		screen_x++;
	}
}
