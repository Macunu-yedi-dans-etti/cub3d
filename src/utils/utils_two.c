/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 22:05:00 by musoysal          #+#    #+#             */
/*   Updated: 2026/03/04 22:05:00 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rgb_free(char **rgb)
{
	int	i;

	i = 0;
	if (!rgb)
		return ;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
}

int	is_valid_extension(char *filename)
{
	int		len;
	char	*base;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(filename + len - 4, ".cub") != 0)
		return (0);
	base = ft_strrchr(filename, '/');
	if (base)
		base++;
	else
		base = filename;
	if (ft_strcmp(base, ".cub") == 0)
		return (0);
	return (1);
}
