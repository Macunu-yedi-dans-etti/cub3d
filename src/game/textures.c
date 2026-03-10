/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:44:24 by musoysal          #+#    #+#             */
/*   Updated: 2026/03/10 14:08:02 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	load_texture(t_game *game, char *path, void **texture,
	void **img_ptr)
{
	void	*img;
	int		width;
	int		height;
	int		addr_data[3];

	img = mlx_xpm_file_to_image(game->mlx.mlx, path, &width, &height);
	if (!img)
	{
		printf("Error: Cannot load texture %s\n", path);
		return (1);
	}
	*img_ptr = img;
	*texture = mlx_get_data_addr(img, &addr_data[0], &addr_data[1],
			&addr_data[2]);
	return (0);
}

int	load_all_textures(t_game *game)
{
	if (load_texture(game, game->texture.north, &game->texture.north_img,
			&game->texture.north_img_ptr))
		return (1);
	if (load_texture(game, game->texture.south, &game->texture.south_img,
			&game->texture.south_img_ptr))
		return (1);
	if (load_texture(game, game->texture.west, &game->texture.west_img,
			&game->texture.west_img_ptr))
		return (1);
	if (load_texture(game, game->texture.east, &game->texture.east_img,
			&game->texture.east_img_ptr))
		return (1);
	game->texture.width = 64;
	game->texture.height = 64;
	return (0);
}
