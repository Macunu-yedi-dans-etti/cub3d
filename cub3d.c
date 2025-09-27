#include "includes/cub3d.h"


int arg_parse(char **argv)
{
	if (file_control(argv[1], 0) == 0)
		return (0);
	return (1);
}


int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		ft_error("Usage: ./cub3d <map.cub>\n");
	
	arg_parse(argv);
	if (!parse_map(argv[1], &game))
		ft_error("Failed to parse map\n");

	if (!validate_map(&game))
		ft_error("Invalid map\n");

	//init_game(&game); yapılacak
	find_player_position(&game);
	
	// mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	// mlx_hook(game.win, 17, 1L<<17, (int (*)())cleanup_game, &game); genel yapı böyle yapılacak
	// mlx_loop_hook(game.mlx, game_loop, &game);
	// mlx_loop(game.mlx);
	
	return (0);
}