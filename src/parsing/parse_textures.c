/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:27:39 by haloztur          #+#    #+#             */
/*   Updated: 2026/02/25 14:19:08 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	set_tex(t_game *game, char *line, char **tex, char *err)
{
	int	i;

	if (*tex)
	{
		printf("Error\nDuplicate %s texture\n", err);
		return (0);
	}
	i = 2;
	while (line[i] == ' ')
		i++;
	*tex = gc_strdup(&game->gc, line + i);
	return (1);
}

static int	assign_texture(t_game *game, char *line)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (set_tex(game, line, &game->texture.north, "north (NO)"));
	if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (set_tex(game, line, &game->texture.south, "south (SO)"));
	if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (set_tex(game, line, &game->texture.west, "west (WE)"));
	if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (set_tex(game, line, &game->texture.east, "east (EA)"));
	return (1);
}

int	parse_textures(t_game *game, char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (!assign_texture(game, lines[i]))
			return (0);
		i++;
	}
	if (!game->texture.north || !game->texture.south
		|| !game->texture.west || !game->texture.east)
	{
		printf("Error\nMissing texture(s)\n");
		return (0);
	}
	return (1);
}

static int	check_fc(t_game *g, char *ln, int *f, int *c)
{
	if (ln[0] == 'F' && ln[1] == ' ')
	{
		if ((*f)++ && printf(ERR_FLOOR_DUP))
			return (0);
		if (!parse_color_line(ln, &g->floor))
			return (0);
	}
	else if (ln[0] == 'C' && ln[1] == ' ')
	{
		if ((*c)++ && printf(ERR_CEILING_DUP))
			return (0);
		if (!parse_color_line(ln, &g->ceiling))
			return (0);
	}
	return (1);
}

int	parse_colors(t_game *game, char **lines)
{
	int	i;
	int	f;
	int	c;

	i = -1;
	f = 0;
	c = 0;
	while (lines[++i])
	{
		if (!check_fc(game, lines[i], &f, &c))
			return (0);
	}
	if (!f || !c)
	{
		printf(ERR_COLOR_MISSING);
		return (0);
	}
	return (1);
}
