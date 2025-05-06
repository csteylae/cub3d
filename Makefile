NAME= cub3D
CC= cc
CFLAGS= -Wall -Wextra -Werror #-fsanitize=address

LIBFT= ./lib/libft/libft.a
LIBMLX= ./minilibx-linux/libmlx.a

SRCS= ./src/main.c \
	  ./src/my_mlx_pixel_put.c \
	  ./src/init_data.c \
	  ./src/hook.c \
	  ./src/draw_map.c \
	  ./src/render_frame.c \

OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -Lminilibx-linux -lmlx_Linux -lX11 -lXext

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
