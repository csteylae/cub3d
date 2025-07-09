/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:25:29 by csteylae          #+#    #+#             */
/*   Updated: 2025/07/09 11:38:58 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h" 

int	key_release(int keysym, t_mlx_data *data)
{
	if (keysym == XK_w)
		data->key.w = 0;
	if (keysym == XK_a)
		data->key.a = 0;
	if (keysym == XK_s)
		data->key.s = 0;
	if (keysym == XK_d)
		data->key.d = 0;
	if (keysym == XK_Left)
		data->key.left = 0;
	if (keysym == XK_Right)
		data->key.right = 0;
	return (0);
}

int	key_press(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
		close_cub(data);
	if (keysym == XK_w)
		data->key.w = 1;
	if (keysym == XK_a)
		data->key.a = 1;
	if (keysym == XK_s)
		data->key.s = 1;
	if (keysym == XK_d)
		data->key.d = 1;
	if (keysym == XK_Left)
		data->key.left = 1;
	if (keysym == XK_Right)
		data->key.right = 1;
	return (0);
}
