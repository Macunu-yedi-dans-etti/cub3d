/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:27:33 by haloztur          #+#    #+#             */
/*   Updated: 2026/02/08 15:39:12 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	find_player_position(t_game *game)
{
	int i;
	int j;
	int count = 0;

	game->map.player_start_x = -1;
	game->map.player_start_y = -1;
	game->map.player_start_dir = 'N';
	for (i = 0; i < game->map.height; i++)
	{
		for (j = 0; j < (int)ft_strlen(game->map.grid[i]); j++)
		{
			if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S' || game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
			{
				count++;
				if (count == 1)
				{
					game->map.player_start_x = j;
					game->map.player_start_y = i;
					game->map.player_start_dir = game->map.grid[i][j];
				}
				game->map.grid[i][j] = '0';
			}
		}
	}
	return count;
}

int parse_map(t_game *game, char **lines, int start)
{
	int i;
	int map_lines;
	int player_count;

	i = start;
	while (lines[i] && !is_map_line(lines[i]))
		i++;
	if (!lines[i])
	{
		printf(ERR_MAP_EMPTY);
		return (0);
	}
	map_lines = 0;
	while (lines[i + map_lines] && is_map_line(lines[i + map_lines]))
		map_lines++;
	game->map.height = map_lines;
	game->map.grid = gc_malloc(&game->gc, sizeof(char *) * (map_lines + 1));
	if (!game->map.grid)
		return (0);
	game->map.width = 0;
	map_lines = 0;
	while (lines[i] && is_map_line(lines[i]))
	{
		game->map.grid[map_lines] = gc_strdup(&game->gc, lines[i]);
		if ((int)ft_strlen(lines[i]) > game->map.width)
			game->map.width = ft_strlen(lines[i]);
		map_lines++;
		i++;
	}
	game->map.grid[map_lines] = NULL;
	player_count = find_player_position(game);
	if (player_count != 1)
	{
		if (player_count == 0)
			printf(ERR_PLAYER_MISSING);
		else
			printf(ERR_PLAYER_MULTIPLE);
		return 0;
	}
	return (1);
}

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
	if (visited[y][x] == '1')
		return (1);
	if (game->map.grid[y][x] == ' ')
		return (0);
	if (game->map.grid[y][x] == '1')
		return (1);
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
	i = 0;
	while (i < game->map.height)
	{
		visited[i] = gc_malloc(&game->gc, ft_strlen(game->map.grid[i]) + 1);
		if (!visited[i])
			return (NULL);
		j = 0;
		while (j < (int)ft_strlen(game->map.grid[i]))
		{
			visited[i][j] = '0';
			j++;
		}
		visited[i][j] = '\0';
		i++;
	}
	visited[i] = NULL;
	return (visited);
}

int	validate_map(t_game *game)
{
	char	**visited;
	int		i;
	int		j;

	if (game->map.height < 3 || game->map.width < 3)
	{
		printf(ERR_MAP_EMPTY);
		return (0);
	}
	if (game->map.player_start_x == -1 || game->map.player_start_y == -1)
	{
		printf(ERR_PLAYER_MISSING);
		return (0);
	}
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < (int)ft_strlen(game->map.grid[i]))
		{
			if (game->map.grid[i][j] != '0' && game->map.grid[i][j] != '1'
				&& game->map.grid[i][j] != ' ')
			{
				printf(ERR_MAP_INVALID);
				return (0);
			}
			j++;
		}
		i++;
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
