/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:44:24 by musoysal          #+#    #+#             */
/*   Updated: 2025/10/24 16:07:26 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int load_texture(t_game *game, char *path, int **texture)
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
	*texture = (int *)mlx_get_data_addr(img, &bpp, &line_length, &endian);
	printf("loaded texture: %s\n", path);
	return (0);
}

int load_all_textures(t_game *game)
{
	printf("Loading all textures...\n");
	printf("North texture: %s\n", game->texture.north);
	printf("South texture: %s\n", game->texture.south);
	printf("West texture: %s\n", game->texture.west);
	printf("East texture: %s\n", game->texture.east);

	if (load_texture(game, game->texture.north, &game->texture.north_img))
		return (1);
	if (load_texture(game, game->texture.south, &game->texture.south_img))
		return (1);
	if (load_texture(game, game->texture.west, &game->texture.west_img))
		return (1);
	if (load_texture(game, game->texture.east, &game->texture.east_img))
		return (1);
	game->texture.width = 64;
	game->texture.height = 64;
	printf("Textures loaded successfully\n");
	return (0);
}