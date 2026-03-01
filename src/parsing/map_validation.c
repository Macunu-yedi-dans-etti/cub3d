/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 22:15:00 by haloztur          #+#    #+#             */
/*   Updated: 2026/03/01 15:26:50 by musoysal         ###   ########.fr       */
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

static int	check_char(t_game *game, int i, int j)
{
	char	c;

	c = game->map.grid[i][j];
	if (c == '\t')
	{
		printf(ERR_MAP_TAB);
		return (0);
	}
	if (c != '0' && c != '1' && c != ' ' && c != 'N'
		&& c != 'S' && c != 'E' && c != 'W')
	{
		printf(ERR_MAP_INVALID);
		return (0);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	int		i;
	int		j;

	if (game->map.player_start_x == -1 || game->map.player_start_y == -1)
		return (printf(ERR_PLAYER_MISSING), 0);
	i = -1;
	while (++i < game->map.height)
	{
		j = -1;
		while (game->map.grid[i][++j])
		{
			if (!check_char(game, i, j))
				return (0);
			if (game->map.grid[i][j] == '0'
				|| ft_strchr("NSEW", game->map.grid[i][j]))
			{
				if (!check_cell_surrounded(game, i, j))
				{
					printf(ERR_MAP_NOT_CLOSED);
					return (0);
				}
			}
		}
	}
	return (1);
}
