/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:27:33 by haloztur          #+#    #+#             */
/*   Updated: 2026/03/04 22:00:00 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_chars_after_map(char **lines, int start)
{
	int		i;
	char	*tmp;

	i = start;
	while (lines[i])
	{
		tmp = lines[i];
		while (*tmp == ' ')
			tmp++;
		if (*tmp)
		{
			if (is_map_line(lines[i]))
				printf(ERR_MAP_LAST);
			else
				printf(ERR_MAP_FORBIDDEN, lines[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	set_player(t_game *game, int x, int y, int *count)
{
	(*count)++;
	if (*count == 1)
	{
		game->map.player_start_x = x;
		game->map.player_start_y = y;
		game->map.player_start_dir = game->map.grid[y][x];
	}
	game->map.grid[y][x] = '0';
}

static int	find_player_position(t_game *game)
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
		while (game->map.grid[i][++j])
			if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S'
				|| game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
				set_player(game, j, i, &count);
	}
	return (count);
}

static int	validate_and_check_player(t_game *game)
{
	int	m_ln;

	m_ln = find_player_position(game);
	if (m_ln == 1)
		return (validate_map(game));
	if (m_ln == 0 && printf(ERR_PLAYER_MISSING))
		return (0);
	printf(ERR_PLAYER_MULTIPLE);
	return (0);
}

int	parse_map(t_game *game, char **lines, int start, int i)
{
	int	m_ln;

	i = start;
	if (!lines[i] || !is_map_line(lines[i]))
	{
		if (!lines[i])
			printf(ERR_MAP_EMPTY);
		else
			printf(ERR_MAP_BEFORE);
		return (0);
	}
	m_ln = 0;
	while (lines[i + m_ln] && is_map_line(lines[i + m_ln]))
		m_ln++;
	game->map.height = m_ln;
	if (!check_chars_after_map(lines, i + m_ln))
		return (0);
	game->map.grid = gc_malloc(&game->gc, sizeof(char *) * (m_ln + 1));
	if (!game->map.grid || !load_map_grid(game, lines, i))
		return (0);
	return (validate_and_check_player(game));
}
