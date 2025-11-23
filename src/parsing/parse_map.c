/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:27:33 by haloztur          #+#    #+#             */
/*   Updated: 2025/11/23 13:32:51 by haloztur         ###   ########.fr       */
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
		return (0);
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

int	validate_map(t_game *game)
{
	int	i;
	int	j;

	if (game->map.height < 3 || game->map.width < 3)
		return (0);
	if (game->map.player_start_x == -1 || game->map.player_start_y == -1)
		return (0);
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < (int)ft_strlen(game->map.grid[i]))
		{
			if ((i == 0 || i == game->map.height - 1
					|| j == 0 || j == (int)ft_strlen(game->map.grid[i]) - 1)
				&& game->map.grid[i][j] != '1')
			{
				if (game->map.grid[i][j] != ' ')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}