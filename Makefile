NAME= cub3d
CC= cc
CFLAGS= -Wall -Wextra -Werror

LIBFT= ./lib/libft/libft.a
LIBMLX= ./minilibx-linux/libmlx.a
LIBMLX_FLAGS= -L./minilibx_linux -lmlx_Linux -L/usr/lib -I./minilibx_linux -lXext -lX11 -lm -lz

#SRCS=

#OBJS=$(SRCS:.c=.o)

$(NAME): $(OBJS) minilibx
	make -C ./minilibx-linux
	make -C ./lib/libft
	$(CC) $(CFLAGS) $M$(OBJS) $(LIBFT) $(LIBMLX)

minilibx : 
	tar -xf minilibx-linux.tgz

all : $(NAME)

clean :
	rm -rf minilibx-linux
	make clean -C ./lib/libft
	rm -rf $(OBJS)

fclean : clean
	make fclean -C ./lib/libft
	rm -rf $(NAME)

re: fclean all
