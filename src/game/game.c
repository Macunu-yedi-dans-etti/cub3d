/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:27:14 by haloztur          #+#    #+#             */
/*   Updated: 2026/03/10 14:04:42 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	game_loop(t_game *game)
{
	handle_movement(game);
	raycast(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.img, 0, 0);
	return (0);
}

int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(0);
}

void	start_game(t_game *game)
{
	mlx_hook(game->mlx.win, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->mlx.win, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->mlx.win, 17, 1L << 17, close_window, game);
	mlx_loop_hook(game->mlx.mlx, game_loop, game);
	mlx_loop(game->mlx.mlx);
}

void	cleanup_game(t_game *game)
{
	if (game->texture.north_img_ptr)
		mlx_destroy_image(game->mlx.mlx, game->texture.north_img_ptr);
	if (game->texture.south_img_ptr)
		mlx_destroy_image(game->mlx.mlx, game->texture.south_img_ptr);
	if (game->texture.west_img_ptr)
		mlx_destroy_image(game->mlx.mlx, game->texture.west_img_ptr);
	if (game->texture.east_img_ptr)
		mlx_destroy_image(game->mlx.mlx, game->texture.east_img_ptr);
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
}
