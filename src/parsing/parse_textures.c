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

static void rgb_free(char **rgb)
{
	int i;

	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
}
static int	is_valid_rgb_token(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (!s[i])
		return (0);
	while (ft_isdigit(s[i]))
		i++;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (s[i] == '\0');
}

static int	has_consecutive_commas(char *line)
{
	int	i;

	i = 2;
	while (line[i])
	{
		if (line[i] == ',' && line[i + 1] == ',')
			return (1);
		i++;
	}
	return (0);
}

static int parse_color_line(char *line, t_color *color)
{ 
	char **rgb;

	if (has_consecutive_commas(line))
	{
		printf(ERR_COLOR_INVALID);
		return (0);
	}
	rgb = ft_split(line + 2, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		if (rgb)
			rgb_free(rgb);
		printf(ERR_COLOR_INVALID);
		return (0);
	}
	if (!is_valid_rgb_token(rgb[0]) || !is_valid_rgb_token(rgb[1]) || !is_valid_rgb_token(rgb[2]))
	{
		rgb_free(rgb);
		printf(ERR_COLOR_INVALID);
		return (0);
	}
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255 || color->b < 0 || color->b > 255)
	{
		rgb_free(rgb);
		printf(ERR_COLOR_RANGE);
		return (0);
	}
	color->rgb = create_rgb(color->r, color->g, color->b);
	rgb_free(rgb);
	return (1);
}

int parse_textures(t_game *game, char **lines)
{
	int i;

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
	if (!game->texture.north)
		printf("Error\nMissing north texture (NO)\n");
	if (!game->texture.south)
		printf("Error\nMissing south texture (SO)\n");
	if (!game->texture.west)
		printf("Error\nMissing west texture (WE)\n");
	if (!game->texture.east)
		printf("Error\nMissing east texture (EA)\n");
	return (game->texture.north && game->texture.south && game->texture.west && game->texture.east);
}

int parse_colors(t_game *game, char **lines)
{
	int i;
	int floor_set;
	int ceiling_set;

	i = 0;
	floor_set = 0;
	ceiling_set = 0;
	while (lines[i])
	{
		if (lines[i][0] == 'F' && lines[i][1] == ' ')
		{
			if (floor_set == 1)
			{
				printf("Error\nDuplicate floor color definition\n");
				return (0);
			}
			if (!parse_color_line(lines[i], &game->floor))
				return (0);
			floor_set = 1;
		}
		else if (lines[i][0] == 'C' && lines[i][1] == ' ')
		{
			if (ceiling_set == 1)
			{
				printf("Error\nDuplicate ceiling color definition\n");
				return (0);
			}
			if (!parse_color_line(lines[i], &game->ceiling))
				return (0);
			ceiling_set = 1;
		}
		i++;
	}
	if (!floor_set)
	{
		printf("Error\nMissing floor color definition\n");
		return (0);
	}
	if (!ceiling_set)
	{
		printf("Error\nMissing ceiling color definition\n");
		return (0);
	}
	return (1);
}