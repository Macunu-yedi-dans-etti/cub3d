/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:30:00 by musoysal          #+#    #+#             */
/*   Updated: 2025/10/09 15:30:00 by musoysal         ###   ########.fr       */
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

static void	find_player_position(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < (int)ft_strlen(game->map.grid[i]))
		{
			if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S'
				|| game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
			{
				game->map.player_x = j;
				game->map.player_y = i;
				game->map.player_dir = game->map.grid[i][j];
				game->map.grid[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

int	parse_map(t_game *game, char **lines, int start)
{
	int	i;
	int	map_lines;

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
	find_player_position(game);
	return (1);
}

int	validate_map(t_game *game)
{
	int	i;
	int	j;

	if (game->map.height < 3 || game->map.width < 3)
		return (0);
	if (game->map.player_x == -1 || game->map.player_y == -1)
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