/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:27:33 by haloztur          #+#    #+#             */
/*   Updated: 2026/02/25 14:18:05 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// bu fonksiyon map satırını kontrol eder, sadece 0,1,N,S,E,W karakterleri kabul edilir
int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			return (1);
		i++;
	}
	return (0);
}

static void	set_player(t_game *game, int x, int y, int *count)
{
	if (++(*count) == 1)
	{
		game->map.player_start_x = x;
		game->map.player_start_y = y;
		game->map.player_start_dir = game->map.grid[y][x];
	}
	game->map.grid[y][x] = '0';
}

int	find_player_position(t_game *game)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	game->map.player_start_x = -1;
	game->map.player_start_y = -1;
	i = -1;
	while (++i < game->map.height)
	{
		j = -1;
		while (++j < (int)ft_strlen(game->map.grid[i]))
			if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S'
				|| game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
				set_player(game, j, i, &count);
	}
	return (count);
}

static int	load_map_grid(t_game *game, char **lines, int start)
{
	int	i;
	int	m_ln;

	i = start;
	m_ln = 0;
	game->map.width = 0;
	while (lines[i])
	{
		game->map.grid[m_ln] = gc_strdup(&game->gc, lines[i]);
		if (!game->map.grid[m_ln] || !game->map.grid[m_ln][0])
			return (printf(ERR_MAP_INVALID), 0);
		if ((int)ft_strlen(game->map.grid[m_ln]) > game->map.width)
			game->map.width = ft_strlen(game->map.grid[m_ln]);
		m_ln++;
		i++;
	}
	game->map.grid[m_ln] = NULL;
	return (1);
}

int	parse_map(t_game *game, char **lines, int start)
{
	int	i;
	int	m_ln;

	i = start;
	while (lines[i] && !is_map_line(lines[i]))
		i++;
	if (!lines[i])
		return (printf(ERR_MAP_EMPTY), 0);
	m_ln = 0;
	while (lines[i + m_ln])
		m_ln++;
	game->map.height = m_ln;
	game->map.grid = gc_malloc(&game->gc, sizeof(char *) * (m_ln + 1));
	if (!game->map.grid || !load_map_grid(game, lines, i))
		return (0);
	m_ln = find_player_position(game);
	if (m_ln == 1)
		return (1);
	if (m_ln == 0)
		printf(ERR_PLAYER_MISSING);
	else
		printf(ERR_PLAYER_MULTIPLE);
	return (0);
}
