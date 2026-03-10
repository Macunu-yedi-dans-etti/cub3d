NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lm -lmlx -lXext -lX11

LIBFT_PATH = includes/libft/
MLX_PATH = minilibx-linux/
LIBFT = $(LIBFT_PATH)libft.a
MLX = $(MLX_PATH)libmlx.a

SRC = src/main.c src/utils/gc.c src/utils/utils.c src/utils/utils_two.c \
	src/parsing/parsing.c src/parsing/parse_textures.c \
	src/parsing/parsing_utils.c src/parsing/map_utils.c \
	src/parsing/parse_map.c src/parsing/map_validation.c \
	src/game/game.c src/game/game_init.c src/game/movement.c \
	src/game/movement_utils.c src/raycasting/raycasting.c \
	src/raycasting/raycasting_draw.c src/game/textures.c \
	src/utils/get_next_line.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_PATH) -lft -L$(MLX_PATH) $(MLX_FLAGS) -o $(NAME)

$(MLX):
	@make -C $(MLX_PATH)

$(LIBFT):
	@make -C $(LIBFT_PATH)

%.o: %.c
	$(CC) $(CFLAGS) -Iincludes -I$(MLX_PATH) -c $< -o $@

clean:
	@make clean -C $(LIBFT_PATH)
	rm -rf $(OBJ)
	@make clean -C $(MLX_PATH)

fclean: clean
	rm -rf $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re 