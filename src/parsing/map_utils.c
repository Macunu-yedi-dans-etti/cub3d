/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 22:00:00 by musoysal          #+#    #+#             */
/*   Updated: 2026/03/07 16:50:00 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_valid_pos(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map.height)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(game->map.grid[y]))
		return (0);
	return (1);
}

int	is_map_line(char *line)
{
	int	i;
	int	has_cnt;

	i = 0;
	has_cnt = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			return (1);
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ')
			return (0);
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			has_cnt = 1;
		i++;
	}
	return (has_cnt);
}

int	load_map_grid(t_game *game, char **lines, int start)
{
	int	i;
	int	m_ln;

	i = start;
	m_ln = 0;
	game->map.width = 0;
	while (m_ln < game->map.height)
	{
		game->map.grid[m_ln] = gc_strdup(&game->gc, lines[i]);
		if (!game->map.grid[m_ln])
			return (0);
		if ((int)ft_strlen(game->map.grid[m_ln]) > game->map.width)
			game->map.width = ft_strlen(game->map.grid[m_ln]);
		m_ln++;
		i++;
	}
	game->map.grid[m_ln] = NULL;
	return (1);
}

int	check_all_cells(t_game *game, int **reachable)
{
	int	i;
	int	j;

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
