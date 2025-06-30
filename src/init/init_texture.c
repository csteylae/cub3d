/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:40:40 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/27 16:43:42 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	load_texture(t_mlx_data *data, t_texture *tex)
{
	tex->img.ptr = mlx_xpm_file_to_image(data->mlx, tex->path,
			&tex->width, &tex->height);
	if (!tex->img.ptr)
		put_error("error: cannot mlx_xpm_file_to_image", data);
	tex->img.pixel_addr = mlx_get_data_addr(tex->img.ptr, &tex->img.bpp,
			&tex->img.line_len, &tex->img.endian);
	if (!tex->img.pixel_addr)
		put_error("error: cannot mlx_get_pixel_addr", data);
}

void	init_texture(t_mlx_data *data)
{
	load_texture(data, &data->texture[NORTH]);
	load_texture(data, &data->texture[SOUTH]);
	load_texture(data, &data->texture[EAST]);
	load_texture(data, &data->texture[WEST]);
}
