/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:30:00 by musoysal          #+#    #+#             */
/*   Updated: 2025/10/09 15:30:00 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_player(t_game *game)
{
	game->player.x = game->map.player_x + 0.5;
	game->player.y = game->map.player_y + 0.5;
	if (game->map.player_dir == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (game->map.player_dir == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else if (game->map.player_dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (game->map.player_dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

void	init_game(t_game *game)
{
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
		error_exit(game, ERR_MLX);
	game->mlx.win = mlx_new_window(game->mlx.mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, WINDOW_TITLE);
	if (!game->mlx.win)
		error_exit(game, ERR_MLX);
	game->mlx.img = mlx_new_image(game->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->mlx.img)
		error_exit(game, ERR_MLX);
	game->mlx.addr = mlx_get_data_addr(game->mlx.img,
			&game->mlx.bits_per_pixel, &game->mlx.line_length,
			&game->mlx.endian);
	init_player(game);
	ft_memset(&game->keys, 0, sizeof(t_keys));
}

int	game_loop(t_game *game)
{
	update_player_movement(game);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.img, 0, 0);
	return (0);
}

static int	close_window(t_game *game)
{
	cleanup_game(game);
	return (0);
}

void	start_game(t_game *game)
{
	mlx_hook(game->mlx.win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->mlx.win, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->mlx.win, 17, 1L << 17, close_window, game);
	mlx_loop_hook(game->mlx.mlx, game_loop, game);
	mlx_loop(game->mlx.mlx);
}

void	cleanup_game(t_game *game)
{
	if (game->mlx.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.img);
	if (game->mlx.win)
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	if (game->mlx.mlx)
	{
		mlx_destroy_display(game->mlx.mlx);
		free(game->mlx.mlx);
	}
	gc_free_all(&game->gc);
	exit(0);
}