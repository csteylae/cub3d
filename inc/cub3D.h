/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:47:21 by csteylae          #+#    #+#             */
/*   Updated: 2025/07/14 14:30:52 by raneuman         ###   ########.fr       */
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

# define EPSILON 1e-10
# define SAFE_LARGE_VALUE 1e30

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768

# define EA 1
# define WE 2
# define SO 4
# define NO 8
# define C 16
# define F 32

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
t_mlx_data	init_data(t_data *game);
t_player	init_player(t_mlx_data *data);
void		init_texture(t_mlx_data *data);
t_img		init_img(void);
void		init_framebuffer(t_mlx_data *data);
int			get_wall_height(double perp_wall_dist);
int			get_wall_top(int wall_height);
int			get_wall_bottom(int wall_height);

/*_______EVENT_____________*/
int			close_cub(t_mlx_data *data);
int			key_press(int keysym, t_mlx_data *data);
int			key_release(int keysym, t_mlx_data *data);

/*_______IMAGE RENDERING __*/
void		my_pixel_put(t_img *img, int x, int y, int color);
void		ft_clear_image(t_mlx_data *data);
int			render_frame(t_mlx_data *data);
void		draw_textured_wall(t_mlx_data *data, int x, t_wall wall, t_ray ray);
t_wall		init_wall(t_mlx_data *data, t_ray ray);
void		draw_3d_wall(t_mlx_data *data);
int			get_texture_column(t_mlx_data *data, t_wall wall, t_ray ray);
double		get_texel_ratio(int texture_size, int wall_height);
double		get_starting_row_texture(double txl_ratio, t_wall wall);

/*______MOVEMENT__________*/
void		update_player_position(t_mlx_data *data, t_player *player);
void		move_forward(t_mlx_data *data, t_vector dir);
void		move_backward(t_mlx_data *data, t_vector dir);
void		strafe_right(t_mlx_data *data, t_vector dir);
void		strafe_left(t_mlx_data *data, t_vector dir);
void		rotate(t_player *player, double rot_angle);
bool		is_wall_collision(t_mlx_data *data, t_vector pos);

/*______RAYCASTING_______*/
void		initialize_dda(t_player *player, t_ray *ray);
t_ray		cast_ray(t_mlx_data *data, int x);
void		perform_dda(t_mlx_data *data, t_ray *ray);

/*_______ERROR_____________*/
void		put_error(char *error_msg, t_mlx_data *data);

/*_______UTILS_____________*/
t_vector	vec(double x, double y);
t_vector	get_plane(t_vector dir, double plane_len);
void		draw_line(t_mlx_data *data, t_line line, int color);
int			get_pixel_color(t_img img, int pixel_x, int pixel_y);
t_range		new_range(double min, double max);

/*______________RACHEL______________*/
/*_____ERRORS_____*/
void		ft_error(char *str);
void		free_entire_fd(t_data *game);
void		free_str(char **str);
void		free_all(t_data *game);
void		free_all_error(char *str, t_data *game);
void		free_game_data(t_data *game);
void		free_str_all(char *str, t_data *game);
/*_____INIT_____*/
void		init_struct(t_data *game);

/*_____PARSING_____*/
void		parse(t_data *game, char *file);
void		open_file(t_data *game, char *file);

int			check_texture(t_data *game, char *line);
void		check_textures_path(char *path, t_data *game);

void		check_color(t_data *game, char *line);
void		validate_rgb_components(char *str, t_data *game, int i, int j);
int			create_trgb(int t, t_data *game);

void		parse_map(t_data *game, int map_start_index);
char		**copy_map(char **src_map, t_data *game);
int			flood_fill(t_data *game, int y, int x);
void		check_invalid_zero(t_data *game);

/*_____MAP_____*/
void		map_is_valid(t_data *game);
void		check_map_boundary(t_data *game);
void		free_padded_map(char **map, int len);
int			get_map_height(char **map);
int			get_max_width(char **map);
char		**create_padded_map(t_data *game);

#endif
