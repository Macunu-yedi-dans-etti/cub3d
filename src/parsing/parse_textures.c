/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:27:39 by haloztur          #+#    #+#             */
/*   Updated: 2025/10/15 11:00:23 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	parse_color_line(char *line, t_color *color)
{
	char	**rgb;
	int		i;

	rgb = ft_split(line + 2, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (0);
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (0);
	color->rgb = create_rgb(color->r, color->g, color->b);
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
	return (1);
}

int	parse_textures(t_game *game, char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (lines[i][0] == 'N' && lines[i][1] == 'O' && lines[i][2] == ' ')
			game->texture.north = gc_strdup(&game->gc, lines[i] + 3);
		else if (lines[i][0] == 'S' && lines[i][1] == 'O' && lines[i][2] == ' ')
			game->texture.south = gc_strdup(&game->gc, lines[i] + 3);
		else if (lines[i][0] == 'W' && lines[i][1] == 'E' && lines[i][2] == ' ')
			game->texture.west = gc_strdup(&game->gc, lines[i] + 3);
		else if (lines[i][0] == 'E' && lines[i][1] == 'A' && lines[i][2] == ' ')
			game->texture.east = gc_strdup(&game->gc, lines[i] + 3);
		i++;
	}
	if (!game->texture.north || !game->texture.south
		|| !game->texture.west || !game->texture.east)
		return (0);
	return (1);
}

int	parse_colors(t_game *game, char **lines)
{
	int	i;
	int	floor_set;
	int	ceiling_set;

	i = 0;
	floor_set = 0;
	ceiling_set = 0;
	while (lines[i])
	{
		if (lines[i][0] == 'F' && lines[i][1] == ' ')
		{
			if (!parse_color_line(lines[i], &game->floor))
				return (0);
			floor_set = 1;
		}
		else if (lines[i][0] == 'C' && lines[i][1] == ' ')
		{
			if (!parse_color_line(lines[i], &game->ceiling))
				return (0);
			ceiling_set = 1;
		}
		i++;
	}
	return (floor_set && ceiling_set);
}