/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:12:14 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/03 15:38:34 by csteylae         ###   ########.fr       */
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

int main(void)
{
	t_mlx_data	data;

	data = init_data();
	mlx_hook(data.win, 17, 0, close_cub3D, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_press, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, key_release, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_loop(data.mlx);
}
