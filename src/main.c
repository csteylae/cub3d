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


/* 
 * Needed to pass as argument void *param for my pointer to function
 */
typedef struct s_mlx_data
{
	void	*mlx_connection;
	void	*mlx_window;
}	t_mlx_data;

void	draw_square(void *mlx_connection, void *mlx_window)
{
	int	x = 0;
	int	y = 0;

	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			mlx_pixel_put(mlx_connection, mlx_window, WIDTH + x, HEIGHT + y, rand() % 0x100000);
			x++;
		}
		x = 0;
		y++;
	}
}

int	handle_escape(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
	{
		printf("The %d key (ESC) has been pressed\n\n", keysym);
		mlx_destroy_window(data->mlx_connection, data->mlx_window);
		mlx_destroy_display(data->mlx_connection);
		free(data->mlx_connection);
		exit(EXIT_SUCCESS);
	}
	printf("The key %d has been pressed\n\n", keysym);
	return (0);

}

int main(void)
{
	t_mlx_data	data;

	data.mlx_connection = mlx_init();

	data.mlx_window = mlx_new_window(data.mlx_connection, 1500,1500, "test");

	draw_square(data.mlx_connection, data.mlx_window);
	mlx_key_hook(data.mlx_window, handle_escape, &data);
	mlx_loop(data.mlx_connection);
}
	
