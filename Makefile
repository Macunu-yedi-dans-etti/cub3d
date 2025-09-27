
NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -lm -lmlx -lXext -lX11

LIBFT_PATH = includes/libft/
MLX_PATH = minilibx-linux/
LIBFT = $(LIBFT_PATH)libft.a
MLX = $(MLX_PATH)libmlx.a

SRC = cub3d.c source/map/parse_map.c source/map/check_the_map.c source/ft_error.c source/map/free_split.c source/file/file_control.c \
	includes/get_next_line/get_next_line.c includes/get_next_line/get_next_line_utils.c



OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_PATH) -lft -L$(MLX_PATH) $(MLX_FLAGS) -o $(NAME)

$(MLX):
	@make -C $(MLX_PATH)

$(LIBFT):
	@make -C $(LIBFT_PATH)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBFT_PATH)
	rm -rf $(OBJ)
	@make clean -C $(MLX_PATH)

fclean: clean
	rm -rf $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re
