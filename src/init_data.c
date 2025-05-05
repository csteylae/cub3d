/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:12:46 by csteylae          #+#    #+#             */
/*   Updated: 2025/05/05 19:21:58 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

#define KEYSIZE 6

t_square	init_square(void)
{
	t_square	square;

	square.pos.x = 0;
	square.pos.y = 0;
	square.color = RED;
	square.size = 40;
	return (square);
}

t_key	init_key(void)
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

t_mlx_data	init_data(void)
{
	t_mlx_data	data;

	data.key = init_key();
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		printf("error: mlx_init\n\n");
		exit(EXIT_FAILURE);
	}
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "test");
	if (!data.win)
	{
		printf("error:mlx_new_window\n\n");
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		exit(EXIT_SUCCESS);
	}
	data.square = init_square();
	data.img.ptr = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (!data.img.ptr)
	{
		printf("Error\nCannot get new image\n\n");
		exit(EXIT_FAILURE);
	}
	data.img.pixel_addr = mlx_get_data_addr(data.img.ptr,
		   									&data.img.bits_per_pixel,
											&data.img.line_len,
											&data.img.endian);
	if (!data.img.pixel_addr)
	{
		printf("Error\nCannot get_data_addr\n\n");
		exit(EXIT_FAILURE);
	}
	return (data);	
}
