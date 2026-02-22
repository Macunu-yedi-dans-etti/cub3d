/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:27:39 by haloztur          #+#    #+#             */
/*   Updated: 2026/02/08 18:11:03 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	set_tex(t_game *game, char *line, char **tex, char *err)
{
	if (*tex)
	{
		printf("Error\nDuplicate %s texture\n", err);
		return (0);
	}
	*tex = gc_strdup(&game->gc, line + 3);
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

static int	parse_color_line(char *line, t_color *color)
{
	char	**rgb;

	if (is_invalid_color_string(line))
		return (printf(ERR_COLOR_INVALID), 0);
	rgb = ft_split(line + 2, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		if (rgb)
			rgb_free(rgb);
		return (printf(ERR_COLOR_INVALID), 0);
	}
	if (!is_valid_rgb_token(rgb[0]) || !is_valid_rgb_token(rgb[1])
		|| !is_valid_rgb_token(rgb[2]))
		return (rgb_free(rgb), printf(ERR_COLOR_INVALID), 0);
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (rgb_free(rgb), printf(ERR_COLOR_RANGE), 0);
	color->rgb = create_rgb(color->r, color->g, color->b);
	rgb_free(rgb);
	return (1);
}

int	parse_colors(t_game *game, char **lines)
{
	int	i;
	int	f_set;
	int	c_set;

	i = -1;
	f_set = 0;
	c_set = 0;
	while (lines[++i])
	{
		if (lines[i][0] == 'F' && lines[i][1] == ' ')
		{
			if (f_set++ && printf("Error\nDuplicate floor color\n"))
				return (0);
			if (!parse_color_line(lines[i], &game->floor))
				return (0);
		}
		else if (lines[i][0] == 'C' && lines[i][1] == ' ')
		{
			if (c_set++ && printf("Error\nDuplicate ceiling color\n"))
				return (0);
			if (!parse_color_line(lines[i], &game->ceiling))
				return (0);
		}
	}
	return (f_set && c_set);
}
