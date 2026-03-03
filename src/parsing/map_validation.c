/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 22:15:00 by haloztur          #+#    #+#             */
/*   Updated: 2026/03/03 20:01:45 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_valid_pos(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map.height)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(game->map.grid[y]))
		return (0);
	return (1);
}

static void	flood_fill(t_game *game, int **reachable, int x, int y)
{
	if (!is_valid_pos(game, x, y) || reachable[y][x]
		|| game->map.grid[y][x] == '1' || game->map.grid[y][x] == ' ')
		return ;
	reachable[y][x] = 1;
	flood_fill(game, reachable, x + 1, y);
	flood_fill(game, reachable, x - 1, y);
	flood_fill(game, reachable, x, y + 1);
	flood_fill(game, reachable, x, y - 1);
}

static int	check_cell_surrounded(t_game *game, int y, int x)
{
	if (!is_valid_pos(game, x + 1, y) || !is_valid_pos(game, x - 1, y)
		|| !is_valid_pos(game, x, y + 1) || !is_valid_pos(game, x, y - 1))
		return (0);
	if (game->map.grid[y][x + 1] == ' ' || game->map.grid[y][x + 1] == '\t'
		|| game->map.grid[y][x - 1] == ' ' || game->map.grid[y][x - 1] == '\t'
		|| game->map.grid[y + 1][x] == ' ' || game->map.grid[y + 1][x] == '\t'
		|| game->map.grid[y - 1][x] == ' ' || game->map.grid[y - 1][x] == '\t')
		return (0);
	return (1);
}

static int	**allocate_reachable_matrix(t_game *game)
{
	int	**matrix;
	int	i;

	matrix = gc_malloc(&game->gc, sizeof(int *) * game->map.height);
	if (!matrix)
		return (NULL);
	i = -1;
	while (++i < game->map.height)
	{
		matrix[i] = gc_malloc(&game->gc, sizeof(int) * game->map.width);
		if (!matrix[i])
			return (NULL);
		ft_bzero(matrix[i], sizeof(int) * game->map.width);
	}
	return (matrix);
}

static int	validate_cell(t_game *game, int i, int j, int **reachable)
{
	char	c;

	c = game->map.grid[i][j];
	if (c == '\t')
		return (printf(ERR_MAP_TAB), 0);
	if (c != '0' && c != '1' && c != ' ' && !ft_strchr("NSEW", c))
		return (printf(ERR_MAP_INVALID), 0);
	if (c == '0' || ft_strchr("NSEW", c))
	{
		if (reachable[i][j])
		{
			if (!check_cell_surrounded(game, i, j))
				return (printf(ERR_MAP_NOT_CLOSED), 0);
		}
		else if (!is_valid_pos(game, j + 1, i) || !is_valid_pos(game, j - 1, i)
			|| !is_valid_pos(game, j, i + 1) || !is_valid_pos(game, j, i - 1))
			return (printf(ERR_MAP_NOT_CLOSED), 0);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	int	**reachable;
	int	i;
	int	j;

	if (game->map.player_start_x == -1 || game->map.player_start_y == -1)
		return (printf(ERR_PLAYER_MISSING), 0);
	reachable = allocate_reachable_matrix(game);
	if (!reachable)
		return (0);
	flood_fill(game, reachable, game->map.player_start_x,
		game->map.player_start_y);
	i = -1;
	while (++i < game->map.height)
	{
		j = -1;
		while (game->map.grid[i][++j])
		{
			if (!validate_cell(game, i, j, reachable))
				return (0);
		}
	}
	return (1);
}
