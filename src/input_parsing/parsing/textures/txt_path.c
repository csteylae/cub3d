/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:01:39 by raneuman          #+#    #+#             */
/*   Updated: 2025/07/13 15:34:44 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/cub3D.h"

void	check_textures_path(char *path, t_data *game)
{
	int	len;
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		free_all_error("Error\nInvalid file!\n", game);
	len = ft_strlen(path);
	if (len < 4 || (ft_strncmp(path + len - 4, ".xpm", 4)) != 0)
		free_all_error("Error\nInvalid file!\n", game);
}
