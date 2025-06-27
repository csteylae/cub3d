/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:12:14 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/27 15:52:52 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	close_cub3D(t_mlx_data *data)
{
	if (data->framebuffer.ptr)
		mlx_destroy_image(data->mlx, data->framebuffer.ptr);
	if (data->texture[EAST].img.ptr)
		mlx_destroy_image(data->mlx, data->texture[EAST].img.ptr);
	if (data->texture[WEST].img.ptr)
		mlx_destroy_image(data->mlx, data->texture[WEST].img.ptr);
	if (data->texture[SOUTH].img.ptr)
		mlx_destroy_image(data->mlx, data->texture[SOUTH].img.ptr);
	if (data->texture[NORTH].img.ptr)
		mlx_destroy_image(data->mlx, data->texture[NORTH].img.ptr);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_SUCCESS);
}

void	put_error(char *error_msg, t_mlx_data *data)
{
	if (error_msg)
		printf("%s\n\n", error_msg);
	close_cub3D(data);
}

int main(int argc, char **argv)
{
	int		len;
	t_data	game;
	t_mlx_data	data;

	if (argc != 2)
		ft_error("Error\nNot the right amount of arguments!\n");
	len = ft_strlen(argv[1]);
	if ((ft_strncmp(argv[1] + len - 4, ".cub", 4)) != 0)
		ft_error("Error\nMap format is invalid!\n");//Vérifie format map.
	init_game_struct(&game);//Initialise tous les éléments de ma structure principale.
	parse(&game, argv[1]);//Parsing du fichier .cub.
	map_is_valid(&game);//Validité de ma map.

	data = init_data(game);
	mlx_hook(data.win, 17, 0, close_cub3D, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_press, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, key_release, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_loop(data.mlx);
}
