/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:00:00 by musoysal          #+#    #+#             */
/*   Updated: 2026/03/10 14:00:00 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_player_north_south(t_game *game)
{
	if (game->map.player_start_dir == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (game->map.player_start_dir == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
}

static void	init_player_east_west(t_game *game)
{
	if (game->map.player_start_dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (game->map.player_start_dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

static void	init_player(t_game *game)
{
	game->player.x = game->map.player_start_x + 0.5;
	game->player.y = game->map.player_start_y + 0.5;
	init_player_north_south(game);
	init_player_east_west(game);
}

void	init_game(t_game *game)
{
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
		error_exit(game, ERR_MLX_INIT);
	game->mlx.win = mlx_new_window(game->mlx.mlx, WIN_WIDTH,
			WIN_HEIGHT, WIN_TITLE);
	if (!game->mlx.win)
		error_exit(game, ERR_MLX_WIN);
	game->mlx.img = mlx_new_image(game->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->mlx.img)
		error_exit(game, ERR_MLX_IMG);
	game->mlx.addr = mlx_get_data_addr(game->mlx.img,
			&game->mlx.bits_per_pixel, &game->mlx.line_length,
			&game->mlx.endian);
	init_player(game);
	ft_memset(&game->keys, 0, sizeof(t_keys));
	if (load_all_textures(game))
		error_exit(game, ERR_TEXTURE_LOAD);
}
