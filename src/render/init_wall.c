/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:03:51 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/24 15:05:59 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static double get_exact_wall_hit(t_mlx_data *data, t_ray ray)
{
    double hit;

    if (ray.side == 0)
        hit = data->player.pos.y + ray.perp_wall_dist * ray.dir.y; 
    else 
        hit = data->player.pos.x + ray.perp_wall_dist * ray.dir.x;
    
    hit -= floor(hit); 
//	if (hit < 0)
//		hit = 0;
//	if (hit >= 1.0)
//		hit = 0.999;
	return (hit);
}

static int get_texture_column(double wall_hit, t_ray ray)
{
    int tex_column;

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
	t_wall wall;

	wall.height = (int)SCREEN_HEIGHT / ray.perp_wall_dist;
	if (wall.height < 0)
	{
//		printf("wall_height = 0\n");
		wall.height = 0;
	}
	if (wall.height > SCREEN_HEIGHT - 1)
	{
//		printf("player pos : player X : %f, player y: %f\n\n", data->player.pos.x, data->player.pos.y); 
//		printf("wall_height = SCREEN HEIGHT -1\n");
		wall.height = SCREEN_HEIGHT - 1;
	}
//	printf("wall.height : %i\n", wall.height);
	wall.begin = -wall.height / 2 + SCREEN_HEIGHT / 2;
	if (wall.begin < 0)
		wall.begin = 0;
	wall.end = wall.height / 2 + SCREEN_HEIGHT / 2;
	if (wall.end >= SCREEN_HEIGHT)
		wall.end = SCREEN_HEIGHT - 1;
	wall.hit = get_exact_wall_hit(data, ray);
	wall.tex_col = get_texture_column(wall.hit, ray);
	wall.side = get_wall_side(ray);
//	printf("wall side : %i\n", wall.side);
	return (wall);
}
