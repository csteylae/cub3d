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

#define NORTH_TEXT "/home/chloe/Documents/42_github_perso/cub3D/src/init/fibi_64x64.xpm"
#define SOUTH_TEXT "/home/chloe/Documents/42_github_perso/cub3D/src/init/linus_64.xpm"
#define EAST_TEXT "/home/chloe/Documents/42_github_perso/cub3D/src/init/bb_64.xpm"
#define WEST_TEXT "/home/chloe/Documents/42_github_perso/cub3D/src/init/fi_linus_64.xpm"
//#define NORTH_TEXT "/home/chloe/Documents/42_github_perso/cub3D/src/init/bark.xpm"
//#define SOUTH_TEXT "/home/chloe/Documents/42_github_perso/cub3D/src/init/bookshelf_1_.xpm"
//#define EAST_TEXT "/home/chloe/Documents/42_github_perso/cub3D/src/init/gemov2.xpm"
//#define WEST_TEXT "/home/chloe/Documents/42_github_perso/cub3D/src/init/walkstone_1_.xpm"


t_texture	load_texture(t_mlx_data *data, char *path)
{
	t_texture	tex;

	tex.img.ptr = mlx_xpm_file_to_image(data->mlx, path, &tex.width, &tex.height);
	if (!tex.img.ptr)
	{	
		printf("%s\n", path);
		put_error("error: cannot mlx_xpm_file_to_image", data);
	}
	printf("img name : %s, width : %d, height : %d\n", path, tex.width, tex.height);
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
	data->texture[EAST] = load_texture(data, EAST_TEXT);
	data->texture[WEST] = load_texture(data, WEST_TEXT);
	data->texture[SOUTH] = load_texture(data, SOUTH_TEXT);
	data->texture[NORTH] = load_texture(data, NORTH_TEXT);
}
