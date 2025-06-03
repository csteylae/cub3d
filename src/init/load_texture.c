/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:40:40 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/03 18:26:12 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

// we need to work together to understand how to get the textures from .cub file.
// I will assume we have it now and hardcode their load here but we need a clean way to get them

#define NORTH_TEXT_PATH "../../texture/bebe.xpm"
#define SOUTH_TEXT_PATH "../../texture/moumoune_rose.xpm"
#define EAST_TEXT_PATH "../../texture/moumoune_linus.xpm"
#define WEST_TEXT_PATH "../../texture/loulou.xpm"
#define TEST "simple.xpm"


t_texture	load_texture(t_mlx_data *data, char *path)
{
	t_texture	tex;

	tex.img.ptr = mlx_xpm_file_to_image(data->mlx, path, &tex.width, &tex.height);
	if (!tex.img.ptr)
		put_error("error: cannot mlx_xpm_file_to_image", data);
	tex.img.pixel_addr = mlx_get_data_addr(tex.img.ptr,
											&tex.img.bpp,
											&tex.img.line_len,
											&tex.img.endian);
	if (!tex.img.pixel_addr)
		put_error("error: cannot mlx_get_pixel_addr", data);
	return (tex);
}

void	init_img(t_mlx_data *data)
{
	data->texture[EAST].img.ptr = NULL;
	data->texture[WEST].img.ptr = NULL;
	data->texture[SOUTH].img.ptr = NULL;
	data->texture[NORTH].img.ptr = NULL;
}

void	init_texture(t_mlx_data *data)
{
	init_img(data);
	data->texture[EAST] = load_texture(data, TEST);
	data->texture[WEST] = load_texture(data, TEST);
	data->texture[SOUTH] = load_texture(data, TEST);
	data->texture[NORTH] = load_texture(data, TEST);
}
