/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:27:45 by haloztur          #+#    #+#             */
/*   Updated: 2026/03/02 17:25:48 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_line_count(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static void	trim_line(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static char	**allocate_lines(t_game *game, int line_count)
{
	char	**lines;

	if (line_count <= 0)
	{
		printf(ERR_MAP_EMPTY);
		return (NULL);
	}
	lines = gc_malloc(&game->gc, sizeof(char *) * (line_count + 1));
	return (lines);
}

char	**read_file(t_game *game, char *filename)
{
	int		fd;
	char	**lines;
	char	*line;
	int		count;

	lines = allocate_lines(game, get_line_count(filename));
	if (!lines)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		trim_line(line);
		lines[count++] = gc_track(&game->gc, line);
		line = get_next_line(fd);
	}
	lines[count] = NULL;
	close(fd);
	return (lines);
}

int	parse_file(t_game *game, char *filename)
{
	char	**lines;
	int		map_start;

	lines = read_file(game, filename);
	if (!lines)
		return (0);
	map_start = parse_metadata(game, lines);
	if (map_start == -1)
		return (0);
	if (!parse_map(game, lines, map_start, 0))
		return (0);
	return (1);
}
