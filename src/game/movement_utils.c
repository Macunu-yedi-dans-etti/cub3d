/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:00:00 by musoysal          #+#    #+#             */
/*   Updated: 2026/03/10 14:00:00 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_valid_position(t_game *game, double x, double y, double margin)
{
	if (x - margin < 0 || x + margin >= game->map.width)
		return (0);
	if (y - margin < 0 || y + margin >= game->map.height)
		return (0);
	return (1);
}

int	is_wall_at(t_game *game, double x, double y)
{
	if (game->map.grid[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

int	check_collision(t_game *game, double x, double y, double margin)
{
	if (is_wall_at(game, x - margin, y - margin))
		return (1);
	if (is_wall_at(game, x + margin, y - margin))
		return (1);
	if (is_wall_at(game, x - margin, y + margin))
		return (1);
	if (is_wall_at(game, x + margin, y + margin))
		return (1);
	return (0);
}
