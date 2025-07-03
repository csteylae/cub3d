/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:12:46 by csteylae          #+#    #+#             */
/*   Updated: 2025/07/03 18:13:57 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static t_key	init_key(void)
{
	t_key	key;

	key.w = 0;
	key.a = 0;
	key.s = 0;
	key.d = 0;
	key.left = 0;
	key.right = 0;
	return (key);
}

static t_mlx_data	init_ptr(void)
{
	t_mlx_data	data;

	data.mlx = NULL;
	data.win = NULL;
	data.map = NULL;
	data.texture[NORTH].img = init_img();
	data.texture[SOUTH].img = init_img();
	data.texture[EAST].img = init_img();
	data.texture[WEST].img = init_img();
	data.framebuffer = init_img();
	return (data);
}
/*
#define EAST_PATH "/home/csteylae/42common_core/cub3d/textures/factorylargerocksplain.xpm"
#define WEST_PATH "/home/csteylae/42common_core/cub3d/textures/bookshelf_1_.xpm"
#define NORTH_PATH "/home/csteylae/42common_core/cub3d/textures/gemov2.xpm"
#define SOUTH_PATH "/home/csteylae/42common_core/cub3d/textures/bark.xpm"

char **get_map()
{
	int	i = 0;
	char **my_map = NULL;
	char *map[] = {
    "111111111111111111111111111111",
    "100000000000000001000000000001",
    "101111111011111101011111110101",
    "100000001010000001010000010001",
    "111110101011111101011111110111",
    "100010101000000101000000000001",
    "101110111011111111011111111101",
    "100000100010000000010000000001",
    "101111111110111111111111111101",
    "100000000000100000000000000001",
    "101111111111101111111111110101",
    "101000000000001000000000010101",
    "101011111111111011111110010101",
    "101000000000001000000010010001",
    "101011111111101111111010111101",
    "100010000000001000000010000001",
    "111110111111101111111110111101",
    "1000001000000000000000000000S1",
    "111111111111111111111111111111",
    NULL // <- permet d’avoir une fin détectable si besoin
	};
	int	cout = 0;
	while (map[cout])
		cout++;
	my_map = malloc(sizeof(char *) *(cout +1));
	while (i != cout)
	{
		my_map[i] =  ft_strdup(map[i]);
		i++;
	}
	my_map[i] = NULL;
	return (my_map);
}

static void	get_cub_config(t_mlx_data *data, t_data game)
{
	(void)game;
	data->map = get_map();
	data->texture[NORTH].path = ft_strdup(NORTH_PATH);
	data->texture[SOUTH].path = ft_strdup(SOUTH_PATH);
	data->texture[WEST].path = ft_strdup(WEST_PATH);
	data->texture[EAST].path = ft_strdup(EAST_PATH);
	data->floor = FOREST_GREEN;//game.floor_color;
	data->ceiling = SKY_BLUE;

}
	*/

static void	get_cub_config(t_mlx_data *data, t_data game)
{
	data->map = game.map;
	if (data->map)
		printf("no map sniffff\n");
	data->texture[NORTH].path = game.texture[NORTH];
	data->texture[SOUTH].path = game.texture[SOUTH];
	data->texture[WEST].path = game.texture[WEST];
	data->texture[EAST].path = game.texture[EAST];
	data->floor = game.floor_color;
	data->ceiling = game.ceiling_color;
}

t_vector	vec(double x, double y)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_mlx_data	init_data(t_data game)
{
	t_mlx_data	data;

//	(void)game;
	data = init_ptr();
	get_cub_config(&data, game);
	data.player = init_player(&data);
	data.key = init_key();
	data.mlx = mlx_init();
	if (!data.mlx)
		put_error("mlx_init", &data);
	data.win = mlx_new_window(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!data.win)
		put_error("mlx_new_window", &data);
	init_framebuffer(&data);
	init_texture(&data);
	return (data);
}
