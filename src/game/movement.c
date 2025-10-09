/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:30:00 by musoysal          #+#    #+#             */
/*   Updated: 2025/10/09 16:55:42 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		cleanup_game(game);
	else if (keycode == KEY_W)
		game->keys.w_pressed = 1;
	else if (keycode == KEY_S)
		game->keys.s_pressed = 1;
	else if (keycode == KEY_A)
		game->keys.a_pressed = 1;
	else if (keycode == KEY_D)
		game->keys.d_pressed = 1;
	else if (keycode == KEY_LEFT)
		game->keys.left_pressed = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.right_pressed = 1;
	return (0);
}

int	handle_key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w_pressed = 0;
	else if (keycode == KEY_S)
		game->keys.s_pressed = 0;
	else if (keycode == KEY_A)
		game->keys.a_pressed = 0;
	else if (keycode == KEY_D)
		game->keys.d_pressed = 0;
	else if (keycode == KEY_LEFT)
		game->keys.left_pressed = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.right_pressed = 0;
	return (0);
}

void	move_player(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + move_x;
	new_y = game->player.y + move_y;
	if (new_x >= 0 && new_x < game->map.width && new_y >= 0
		&& new_y < game->map.height)
	{
		if (game->map.grid[(int)new_y][(int)new_x] != '1')
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
}

void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
}

void	handle_movement(t_game *game)
{
	if (game->keys.w_pressed)
		move_player(game, game->player.dir_x * MOVE_SPEED,
			game->player.dir_y * MOVE_SPEED);
	if (game->keys.s_pressed)
		move_player(game, -game->player.dir_x * MOVE_SPEED,
			-game->player.dir_y * MOVE_SPEED);
	if (game->keys.a_pressed)
		move_player(game, -game->player.plane_x * MOVE_SPEED,
			-game->player.plane_y * MOVE_SPEED);
	if (game->keys.d_pressed)
		move_player(game, game->player.plane_x * MOVE_SPEED,
			game->player.plane_y * MOVE_SPEED);
	if (game->keys.left_pressed)
		rotate_player(game, ROT_SPEED);
	if (game->keys.right_pressed)
		rotate_player(game, -ROT_SPEED);
}