NAME= cub3D
CC= cc
CFLAGS= -Wall -Wextra -Werror -fsanitize=address

LIBFT= ./lib/libft/libft.a
LIBMLX= ./minilibx-linux/libmlx.a

SRCS= ./src/main.c \
	  ./src/render/my_mlx_pixel_put.c \
	  ./src/init/init_data.c \
	  ./src/init/init_player.c \
	  ./src/init/init_texture.c \
	  ./src/event/hook.c \
	  ./src/event/update_position.c \
	  ./src/render/render_frame.c \
	  ./src/render/draw_textured_wall.c \
	  ./src/raycasting/dda.c \
	  ./src/raycasting/raycasting.c \
	  ./src/minimap/init_minimap.c \
	  ./src/minimap/draw_minimap.c \
	  ./src/minimap/draw_player.c \
	  ./src/minimap/render_2d.c \


OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lm -Lminilibx-linux -lmlx_Linux -lX11 -lXext

$(LIBMLX):
	tar -xf minilibx-linux.tgz
	make -C minilibx-linux

$(LIBFT):
	make -C ./lib/libft

clean :
	rm -rf ./minilibx-linux
	make clean -C ./lib/libft
	rm -rf $(OBJS)

fclean : clean
	make fclean -C ./lib/libft
	rm -rf $(NAME)

re: fclean all
