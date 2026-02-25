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
