/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:27:39 by haloztur          #+#    #+#             */
/*   Updated: 2026/03/02 19:06:41 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	set_tex(t_game *game, char *line, char **tex, char *err)
{
	int	i;
	int	len;

	if (*tex)
	{
		printf(ERR_TEX_DUP, err);
		return (0);
	}
	i = 2;
	while (line[i] == ' ')
		i++;
	*tex = gc_strdup(&game->gc, line + i);
	len = ft_strlen(*tex);
	if (len < 4 || ft_strcmp(*tex + len - 4, ".xpm") != 0)
	{
		printf(ERR_TEX_INVALID_EXT, err);
		return (0);
	}
	return (1);
}

static int	assign_metadata(t_game *game, char *line, int *count)
{
	char	*tmp;

	tmp = line;
	while (*tmp == ' ')
		tmp++;
	if (!*tmp)
		return (1);
	if (!ft_strncmp(tmp, "NO ", 3) && set_tex(game, tmp, &game->texture.north, "NO") && ++(*count))
		return (1);
	if (!ft_strncmp(tmp, "SO ", 3) && set_tex(game, tmp, &game->texture.south, "SO") && ++(*count))
		return (1);
	if (!ft_strncmp(tmp, "WE ", 3) && set_tex(game, tmp, &game->texture.west, "WE") && ++(*count))
		return (1);
	if (!ft_strncmp(tmp, "EA ", 3) && set_tex(game, tmp, &game->texture.east, "EA") && ++(*count))
		return (1);
	if (!ft_strncmp(tmp, "F ", 2))
	{
		if (game->floor.rgb != -1 && printf(ERR_FLOOR_DUP)) return (0);
		if (parse_color_line(tmp, &game->floor) && ++(*count))
			return (1);
		return (0);
	}
	if (!ft_strncmp(tmp, "C ", 2))
	{
		if (game->ceiling.rgb != -1 && printf(ERR_CEILING_DUP)) return (0);
		if (parse_color_line(tmp, &game->ceiling) && ++(*count))
			return (1);
		return (0);
	}
	printf("Error\nInvalid line in metadata: %s\n", line);
	return (0);
}

int	parse_metadata(t_game *game, char **lines)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	game->floor.rgb = -1;
	game->ceiling.rgb = -1;
	while (lines[i] && count < 6)
	{
		if (!assign_metadata(game, lines[i], &count))
			return (-1);
		i++;
	}
	if (count < 6)
	{
		printf("Error\nMissing texture(s) or color(s)\n");
		return (-1);
	}
	while (lines[i])
	{
		char *tmp = lines[i];
		while (*tmp == ' ') tmp++;
		if (*tmp) break;
		i++;
	}
	return (i);
}
