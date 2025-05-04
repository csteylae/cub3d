#ifndef 	STRUCTURES_H

#define STRUCTURES_H

typedef struct s_pos
{
	int	x;
	int y;
}	t_pos;

typedef struct	s_square
{
	t_pos	pos;
	int		color;
	int		size;
}	t_square;

typedef struct	s_img
{
	void	*ptr;
	char	*pixel_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct	key
{
	int	right;
	int	left;
	int	up;
	int	down;
}

typedef struct s_mlx_data
{
	void		*mlx_connection;
	void		*mlx_window;
	t_square	square;
	t_img		img;
	t_key		key;

}	t_mlx_data;

#define PRESSED 1
#define RELEASED 0

#endif
