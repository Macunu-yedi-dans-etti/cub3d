/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:27:39 by haloztur          #+#    #+#             */
/*   Updated: 2026/03/02 19:06:41 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	set_tex(t_game *game, char *line, char **tex, int i)
{
	int		len;
	char	*base;

	if (*tex && printf(ERR_TEX_DUP, line))
		return (0);
	while (line[i] == ' ')
		i++;
	*tex = gc_strdup(&game->gc, line + i);
	len = ft_strlen(*tex);
	if (len < 4 || ft_strcmp(*tex + len - 4, ".xpm") != 0)
	{
		printf(ERR_TEX_INVALID_EXT, line);
		return (0);
	}
	base = ft_strrchr(*tex, '/');
	if (!base)
		base = *tex;
	else
		base++;
	if (ft_strcmp(base, ".xpm") == 0)
	{
		printf(ERR_TEX_INVALID_EXT, line);
		return (0);
	}
	return (1);
}

static int	assign_fc(t_game *game, char *tmp, int *count)
{
	int	res;

	res = 0;
	if (!ft_strncmp(tmp, "F ", 2))
	{
		if (game->floor.rgb != -1 && printf(ERR_FLOOR_DUP))
			return (0);
		res = parse_color_line(tmp, &game->floor);
	}
	else if (!ft_strncmp(tmp, "C ", 2))
	{
		if (game->ceiling.rgb != -1 && printf(ERR_CEILING_DUP))
			return (0);
		res = parse_color_line(tmp, &game->ceiling);
	}
	if (res)
		(*count)++;
	return (res);
}

static int	assign_textures(t_game *game, char *tmp, int *count)
{
	int	res;

	res = 0;
	if (!ft_strncmp(tmp, "NO ", 3))
		res = set_tex(game, tmp, &game->texture.north, 2);
	else if (!ft_strncmp(tmp, "SO ", 3))
		res = set_tex(game, tmp, &game->texture.south, 2);
	else if (!ft_strncmp(tmp, "WE ", 3))
		res = set_tex(game, tmp, &game->texture.west, 2);
	else if (!ft_strncmp(tmp, "EA ", 3))
		res = set_tex(game, tmp, &game->texture.east, 2);
	else
		return (0);
	if (res)
		(*count)++;
	return (res);
}

static int	assign_metadata(t_game *game, char *line, int *count)
{
	char	*tmp;

	tmp = line;
	while (*tmp == ' ')
		tmp++;
	if (!*tmp)
		return (1);
	if (!ft_strncmp(tmp, "NO ", 3) || !ft_strncmp(tmp, "SO ", 3)
		|| !ft_strncmp(tmp, "WE ", 3) || !ft_strncmp(tmp, "EA ", 3))
		return (assign_textures(game, tmp, count));
	if (!ft_strncmp(tmp, "F ", 2) || !ft_strncmp(tmp, "C ", 2))
		return (assign_fc(game, tmp, count));
	printf(ERR_METADATA_INV, line);
	return (0);
}

int	parse_metadata(t_game *game, char **lines)
{
	int		i;
	int		count;
	char	*tmp;

	i = 0;
	count = 0;
	game->floor.rgb = -1;
	game->ceiling.rgb = -1;
	while (lines[i] && count < 6)
	{
		if (!assign_metadata(game, lines[i++], &count))
			return (-1);
	}
	if (count < 6 && printf(ERR_METADATA_MISSING))
		return (-1);
	while (lines[i])
	{
		tmp = lines[i];
		while (*tmp == ' ')
			tmp++;
		if (*tmp)
			break ;
		i++;
	}
	return (i);
}
