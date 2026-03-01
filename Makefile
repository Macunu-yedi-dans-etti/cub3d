NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# Platform-specific MLX link flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
MLX_FLAGS = -lm -lmlx -framework OpenGL -framework AppKit
else
MLX_FLAGS = -lm -lmlx -lXext -lX11
endif

LIBFT_PATH = includes/libft/
MLX_PATH = minilibx-linux/
LIBFT = $(LIBFT_PATH)libft.a
MLX = $(MLX_PATH)libmlx.a

SRC = src/main.c src/utils/gc.c src/utils/utils.c src/parsing/parsing.c \
	src/parsing/parse_textures.c src/parsing/parsing_utils.c \
	src/parsing/parse_map.c src/parsing/map_validation.c \
	src/game/game.c src/game/movement.c src/raycasting/raycasting.c \
	src/game/textures.c

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

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) maps/good/creepy.cub

.PHONY: all clean fclean re valgrind