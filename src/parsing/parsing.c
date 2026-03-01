/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:27:45 by haloztur          #+#    #+#             */
/*   Updated: 2026/03/01 15:45:01 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Tek seferde dosyadan kucuk bir blok okur.
// 8191 byte okunur cunku buffer 8192 boyutludur (son char '\0')
// Buradan donen deger okunan byte sayisini verir.
static int	fill_buffer(int fd, char *buffer, int *pos, int *size)
{
	*size = read(fd, buffer, 8191);
	*pos = 0;
	return (*size);
}

// Gecici satir bufferinin sonuna '\0' koyar ve gc ile kopyalar.
static char	*get_processed_line(t_game *game, char *line_tmp, int i)
{
	line_tmp[i] = '\0';
	return (gc_strdup(&game->gc, line_tmp));
}

// Dosyadan satir okuyan get_next_line benzeri fonksiyon.
// - Static buffer ve indexler kullanarak veriyi cok kez tuketir.
// - 8192 makul max satir uzunlugu (1 byte gecerli null icindir).
static char	*simple_get_line(int fd, t_game *game)
{
	static char	buf[8192];
	static int	p = 0;
	static int	s = 0;
	char		ln[8192];
	int			i;

	i = 0;
	while (!(p >= s && fill_buffer(fd, buf, &p, &s) <= 0)
		&& i < 8191 && buf[p] != '\n')
	{
		if (buf[p] != '\r')
			ln[i++] = buf[p++];
		else
			p++;
	}
	if (i < 8191 && p < s && buf[p] == '\n')
		p++;
	if (i == 0 && s <= 0)
		return (NULL);
	return (get_processed_line(game, ln, i));
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
	line = simple_get_line(fd, game);
	while (line != NULL)
	{
		if (ft_strlen(line) > 0)
			lines[count++] = line;
		line = simple_get_line(fd, game);
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
	if (!parse_map(game, lines, 0))
		return (0);
	return (1);
}
