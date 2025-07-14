NAME= cub3D
CC= cc
CFLAGS= -Wall -Wextra -Werror -g #-fsanitize=address

LIBFT= ./lib/libft/libft.a
LIBMLX= ./minilibx-linux/libmlx.a

SRCS= ./src/main.c \
	  ./src/init/init_data.c \
	  ./src/init/init_img.c \
	  ./src/init/init_player.c \
	  ./src/init/init_texture.c \
	  ./src/init/init_wall.c \
	  ./src/init/calculate_wall_height.c \
	  ./src/event/hook.c \
	  ./src/event/update_position.c \
	  ./src/event/movement.c \
	  ./src/event/rotation.c \
	  ./src/render/pixel_handlers.c \
	  ./src/render/render_frame.c \
	  ./src/render/draw_textured_wall.c \
	  ./src/render/texture_mapping.c \
	  ./src/raycasting/dda.c \
	  ./src/raycasting/raycasting.c \
	  ./lib/gnl/get_next_line.c \
	  ./lib/gnl/get_next_line_utils.c \
	  ./src/input_parsing/errors/error.c \
	  ./src/input_parsing/errors/free.c \
	  ./src/input_parsing/init_struct.c \
	  ./src/input_parsing/parsing/parse/parse.c \
	  ./src/input_parsing/parsing/textures/textures.c \
	  ./src/input_parsing/parsing/textures/txt_path.c \
	  ./src/input_parsing/parsing/colors/colors.c \
	  ./src/input_parsing/parsing/colors/validate_rgb.c \
	  ./src/input_parsing/parsing/map/map.c \
	  ./src/input_parsing/parsing/map/map_is_valid.c \
	  ./src/input_parsing/parsing/map/copy_map.c \
	  ./src/input_parsing/parsing/map/map_boundary.c \
	  ./src/input_parsing/parsing/map/construct_padded_map.c \

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
