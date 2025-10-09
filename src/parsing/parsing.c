/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:27:45 by haloztur          #+#    #+#             */
/*   Updated: 2025/10/09 17:14:02 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*simple_get_line(int fd)
{
	static char	buffer[1000];
	static int	pos = 0;
	static int	size = 0;
	char		*line;
	int			i;

	i = 0;
	line = malloc(1000);
	if (!line)
		return (NULL);
	while (1)
	{
		if (pos >= size)
		{
			size = read(fd, buffer, 999);
			pos = 0;
			if (size <= 0)
			{
				if (i == 0)
				{
					free(line);
					return (NULL);
				}
				break ;
			}
		}
		if (buffer[pos] == '\n')
		{
			pos++;
			break ;
		}
		line[i++] = buffer[pos++];
	}
	line[i] = '\0';
	return (line);
}

char	**read_file(t_game *game, char *filename)
{
	int		fd;
	char	**lines;
	char	*line;
	int		count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = gc_malloc(&game->gc, sizeof(char *) * 1000);
	if (!lines)
		return (NULL);
	count = 0;
	while ((line = simple_get_line(fd)) != NULL)
	{
		if (ft_strlen(line) > 0)
			lines[count++] = gc_track(&game->gc, line);
		else
			free(line);
	}
	lines[count] = NULL;
	close(fd);
	return (lines);
}

int	parse_file(t_game *game, char *filename)
{
	char	**lines;

	lines = read_file(game, filename);
	if (!lines)
		return (0);
	if (!parse_textures(game, lines))
		return (0);
	if (!parse_colors(game, lines))
		return (0);
	if (!parse_map(game, lines, 6))
		return (0);
	return (1);
}