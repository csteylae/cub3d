/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:12:14 by csteylae          #+#    #+#             */
/*   Updated: 2025/04/29 15:23:08 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#include <stdio.h>

#define WIDTH 500
#define HEIGHT 500

#define RED 0xff0000
#define BLACK 0x000000

#define IMG_WIDTH 40
#define IMG_HEIGHT 40

t_square	init_square(void)
{
	t_square	square;

	square.pos.x = 0;
	square.pos.y = 0;
	square.color = RED;
	return (square);
}

void	draw_square(t_mlx_data *data, t_square square)
{
	int	x = 0;
	int	y = 0;

	while (y < IMG_HEIGHT)
	{
		while (x < IMG_WIDTH)
		{
			my_mlx_pixel_put(&data->img, square.pos.x + x,
							square.pos.y + y, square.color);
			x++;
		}
		x = 0;
		y++;
	}
}

void	escape(t_mlx_data *data)
{
	mlx_destroy_image(data->mlx_connection, data->img.ptr);
	mlx_destroy_window(data->mlx_connection, data->mlx_window);
	mlx_destroy_display(data->mlx_connection);
	free(data->mlx_connection);
	exit(EXIT_SUCCESS);
}

int	handle_keypress(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
		escape(data);
	if (keysym == XK_Right)
		data->key.right = PRESSED;
	else if (keysym == XK_Left)
		data->key.left = PRESSED;
	else if (keysym == XK_Up)
		data->key.up = PRESSED;
	else if (keysym == XK_Down)
		data->key.down = PRESSED;
	return (0);
}

int	handle_keyrelease(int keysym, t_mlx_data *data)
{

}


int main(void)
{
	t_mlx_data	data;

	data.square = init_square();
	data.mlx_connection = mlx_init();
	data.mlx_window = mlx_new_window(data.mlx_connection, 1500,1500, "test");
	data.img.ptr = mlx_new_image(data.mlx_connection, IMG_WIDTH, IMG_HEIGHT);
	if (!data.img.ptr)
	{
		printf("Error\nCannot get new image\n\n");
		exit(EXIT_FAILURE);
	}
	//should init all images
	data.img.pixel_addr = mlx_get_data_addr(data.img.ptr,
		   									&data.img.bits_per_pixel,
											&data.img.line_length,
											&data.img.endian);
	if (!data.img.pixel_addr)
	{
		printf("Error\nCannot get_data_addr\n\n");
		exit(EXIT_FAILURE);
	}
	mlx_put_image_to_window(data->mlx_connection, data->mlx_window, 
							data->img.ptr, data->square.pos.x, 
							data->square.pos.y);
	mlx_key_hook(data.mlx_window, handle_keypress, &data);

	mlx_loop_hook(data.mlx_connection, animate_square, &data);
	mlx_loop(data.mlx_connection);
}
