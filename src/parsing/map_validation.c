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

static int	flood_fill_check(t_game *game, int x, int y, char **visited)
{
	if (!is_valid_pos(game, x, y))
		return (0);
	if (visited[y][x] == '1' || game->map.grid[y][x] == '1')
		return (1);
	if (game->map.grid[y][x] == ' ' || game->map.grid[y][x] == '\t')
		return (0);
	visited[y][x] = '1';
	if (!flood_fill_check(game, x + 1, y, visited))
		return (0);
	if (!flood_fill_check(game, x - 1, y, visited))
		return (0);
	if (!flood_fill_check(game, x, y + 1, visited))
		return (0);
	if (!flood_fill_check(game, x, y - 1, visited))
		return (0);
	return (1);
}

static char	**create_visited_map(t_game *game)
{
	char	**visited;
	int		i;
	int		j;

	visited = gc_malloc(&game->gc, sizeof(char *) * (game->map.height + 1));
	if (!visited)
		return (NULL);
	i = -1;
	while (++i < game->map.height)
	{
		visited[i] = gc_malloc(&game->gc, ft_strlen(game->map.grid[i]) + 1);
		if (!visited[i])
			return (NULL);
		j = -1;
		while (++j < (int)ft_strlen(game->map.grid[i]))
			visited[i][j] = '0';
		visited[i][j] = '\0';
	}
	visited[i] = NULL;
	return (visited);
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

int	validate_map(t_game *game, int i, int j)
{
	char	**visited;

	if (game->map.player_start_x == -1 || game->map.player_start_y == -1)
	{
		printf(ERR_PLAYER_MISSING);
		return (0);
	}
	i = -1;
	while (++i < game->map.height)
	{
		j = -1;
		while (++j < (int)ft_strlen(game->map.grid[i]))
			if (!check_char(game, i, j))
				return (0);
	}
	visited = create_visited_map(game);
	if (!visited)
		return (0);
	if (!flood_fill_check(game, game->map.player_start_x,
			game->map.player_start_y, visited))
	{
		printf(ERR_MAP_NOT_CLOSED);
		return (0);
	}
	return (1);
}
