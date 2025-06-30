/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:03:31 by csteylae          #+#    #+#             */
/*   Updated: 2025/06/27 18:55:55 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include "structures.h"
# include "../lib/libft/libft.h"
# include "../lib/gnl/get_next_line.h"
# include "../minilibx-linux/mlx.h"

# define EPSILON 1e-10 //def "close enough to 0" for floating point comparison
# define SAFE_LARGE_VALUE 1e30

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define TILE_SIZE 64

# define EAST 3
# define WEST 2
# define SOUTH 1
# define NORTH 0

# define RED 0xff0000
# define GREEN 0x00ff00
# define BLUE 0x0000ff
# define YELLOW 0xffff00
# define SKY_BLUE 0x87CEEB
# define FOREST_GREEN 0x228B22

/*_______INIT______________*/
t_mlx_data	init_data(t_data game);
t_player	init_player(t_mlx_data *data);
void		init_texture(t_mlx_data *data);
t_img		init_img(void);
void		init_framebuffer(t_mlx_data *data);

/*_______EVENT_____________*/
int			close_cub3D(t_mlx_data *data);
int			key_press(int keysym, t_mlx_data *data);
int			key_release(int keysym, t_mlx_data *data);

/*_______IMAGE RENDERING __*/
void		my_pixel_put(t_img *img, int x, int y, int color);
void		ft_clear_image(t_mlx_data *data);
int			render_frame(t_mlx_data *data);
void		draw_textured_wall(t_mlx_data *data, int screen_x, t_wall wall);
t_wall		init_wall(t_mlx_data *data, t_ray ray);

/*_______MINIMAP___________*/
void		init_minimap(t_mlx_data *data);
void		draw_map(t_mlx_data *data);
bool		is_inside_image(t_mlx_data *data, int x, int y);
void		draw_player(t_mlx_data *data);

/*______MOVEMENT__________*/
void		update_position(t_mlx_data *data, t_player *player);
t_vector	get_perpendicular_plane(t_vector dir, double plane_len);
t_vector	move_forward(t_mlx_data *data, t_player *player);
t_vector	move_backward(t_mlx_data *data, t_player *player);
t_vector	strafe_right(t_mlx_data *data, t_player *player);
t_vector	strafe_left(t_mlx_data *data, t_player *player);

/*______RAYCASTING_______*/
t_vector	calculate_ray_dir(t_mlx_data *data, t_player *p, int x, int width);
void		initialize_dda(t_player *player, t_ray *ray);
void		cast_ray(t_mlx_data *data);
void		perform_dda(t_mlx_data *data, t_ray *ray);

/*_______ERROR_____________*/
void		put_error(char *error_msg, t_mlx_data *data);

/*_______UTILS_____________*/
t_vector	vec(double x, double y);
t_vector	get_plane(t_vector dir, double plane_len);
void		draw_line(t_mlx_data *data, t_line line, int color);

/*______________RACHEL______________*/
/*________UTILS________*/
void	ft_error(char *str);
void	ft_free_error(char *str, t_data *game);
int 	check_north(t_data *game, char *line);
int 	check_south(t_data *game, char *line);
int 	check_west(t_data *game, char *line);
int		check_east(t_data *game, char *line);
char	**copy_map(char **src_map);

/*________INIT________*/
void    init_game_struct(t_data *game);

/*________PARSE________*/
void    parse(t_data *game, char *file);
int		check_texture(t_data *game, char *line);
int		check_textures_path(char *path);
void	check_texture_exist(t_data *game);
void	textures_own_path(t_data *game);
int		check_color(t_data *game, char *line);
int		parse_map(t_data *game, char **lines);
int		maps_content(char *line);

/*________CHECK_MAP________*/
void    map_is_valid(t_data *game);

#endif
