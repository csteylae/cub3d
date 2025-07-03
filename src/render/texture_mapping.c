/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:53:18 by csteylae          #+#    #+#             */
/*   Updated: 2025/07/03 15:36:02 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	get_texture_column(t_mlx_data *data, t_wall wall, t_ray ray)
{
	int	text_width;
	int	tex_column;

	text_width = data->texture[wall.side].width;
	tex_column = (int)(wall.hit * (double)text_width);
	if (tex_column < 0)
		tex_column = 0;
	if (tex_column >= text_width)
		tex_column = text_width - 1;
	if (ray.side == 0 && ray.dir.x > 0)
		tex_column = text_width - tex_column - 1;
	if (ray.side == 1 && ray.dir.y < 0)
		tex_column = text_width - tex_column - 1;
	return (tex_column);
}

double	get_texel_ratio(int texture_size, int wall_height)
{
	return ((double)texture_size / (double)wall_height);
}

double	get_starting_row_texture(double txl_ratio, t_wall wall)
{
	double	row;

	row = (wall.top - SCREEN_HEIGHT / 2.0 + wall.height / 2.0) * txl_ratio;
	return (row);
}
