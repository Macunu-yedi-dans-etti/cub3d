/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:27:45 by haloztur          #+#    #+#             */
/*   Updated: 2026/02/25 14:21:25 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Tek seferde dosyadan büyük bir blok okur ve buffer/pointer bilgilerini günceller.
// 8191 byte okunmasının sebebi, 8192 boyutlu buffer'da son karakteri '\0' için boş bırakmaktır.
// Buradan dönen değer size değeri dosyadan okunan byte sayısını verir.
static int	fill_buffer(int fd, char *buffer, int *pos, int *size)
{
	*size = read(fd, buffer, 8191);
	*pos = 0;
	return (*size);
}

// Geçici satır buffer'ının sonuna '\0' koyar ve bu satırı garbage collector üzerinden kopyalar.
static char	*get_processed_line(t_game *game, char *line_tmp, int i)
{
	line_tmp[i] = '\0';
	return (gc_strdup(&game->gc, line_tmp));
}

// Dosyadan satır okuyan basit bir "get_next_line" benzeri fonksiyon.
// - static buffer (buf) ve indexler (p, s) kullanarak bir kere okunan veriyi birden fazla çağrıda tüketir.
// - 8192: hem buffer hem de satır için "makul maksimum satır uzunluğu" sınırı (1 byte da '\0' için ayrılıyor).
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
	if (!parse_map(game, lines, 6))
		return (0);
	return (1);
}
