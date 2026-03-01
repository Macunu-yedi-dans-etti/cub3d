/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:44:24 by musoysal          #+#    #+#             */
/*   Updated: 2026/03/01 15:38:17 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int load_texture(t_game *game, char *path, void **texture, void **img_ptr)
{
	void *img;			 // resim pointer
	int width;			 // genişlik
	int height;			 // yükseklik
	int bpp;			 // bits per pixel
	int line_length;	 // satır uzunluğu
	int endian;			 // bit endian
	char full_path[256]; // tam yol

	snprintf(full_path, sizeof(full_path), "%s", path);
	img = mlx_xpm_file_to_image(game->mlx.mlx, full_path, &width, &height);
	if (!img)
	{
		printf("Error: Cannot load texture %s\n", full_path);
		return (1);
	}
	*img_ptr = img;
	*texture = mlx_get_data_addr(img, &bpp, &line_length, &endian);
	return (0);
}

int load_all_textures(t_game *game)
{
	if (load_texture(game, game->texture.north, &game->texture.north_img, &game->texture.north_img_ptr))
		return (1);
	if (load_texture(game, game->texture.south, &game->texture.south_img, &game->texture.south_img_ptr))
		return (1);
	if (load_texture(game, game->texture.west, &game->texture.west_img, &game->texture.west_img_ptr))
		return (1);
	if (load_texture(game, game->texture.east, &game->texture.east_img, &game->texture.east_img_ptr))
		return (1);
	game->texture.width = 64;
	game->texture.height = 64;
	return (0);
}