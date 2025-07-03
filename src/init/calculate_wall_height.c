/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_wall_height.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:37:42 by csteylae          #+#    #+#             */
/*   Updated: 2025/07/03 11:38:04 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

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
