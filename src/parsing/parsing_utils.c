/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 22:15:00 by haloztur          #+#    #+#             */
/*   Updated: 2026/02/25 14:19:59 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rgb_free(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
}

int	is_valid_rgb_token(char *s)
{
	int	i;
	int	digit_count;

	if (!s)
		return (0);
	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (!s[i])
		return (0);
	while (s[i] == '0' && ft_isdigit(s[i + 1]))
		i++;
	digit_count = 0;
	while (ft_isdigit(s[i]))
	{
		digit_count++;
		i++;
	}
	if (digit_count == 0 || digit_count > 3)
		return (0);
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (s[i] == '\0');
}

int	is_invalid_color_string(char *line)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (line[i] && (line[i] == ' ' || line[i] == 'F' || line[i] == 'C'))
		i++;
	if (line[i] == ',')
		return (1);
	while (line[i])
	{
		if (line[i] == ',')
		{
			commas++;
			if (line[i + 1] == ',')
				return (1);
		}
		i++;
	}
	while (i > 0 && line[i - 1] == ' ')
		i--;
	if (commas != 2 || (i > 0 && line[i - 1] == ','))
		return (1);
	return (0);
}

int	free_ret_err(char **arr, char *err)
{
	if (arr)
		rgb_free(arr);
	if (err)
		printf("%s", err);
	return (0);
}

int	parse_color_line(char *line, t_color *color)
{
	char	**rgb;

	if (is_invalid_color_string(line))
		return (free_ret_err(NULL, ERR_COLOR_INVALID));
	rgb = ft_split(line + 2, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_ret_err(rgb, ERR_COLOR_INVALID));
	if (!is_valid_rgb_token(rgb[0]) || !is_valid_rgb_token(rgb[1])
		|| !is_valid_rgb_token(rgb[2]))
		return (free_ret_err(rgb, ERR_COLOR_INVALID));
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (free_ret_err(rgb, ERR_COLOR_RANGE));
	color->rgb = create_rgb(color->r, color->g, color->b);
	rgb_free(rgb);
	return (1);
}
