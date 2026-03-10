/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:00:00 by musoysal          #+#    #+#             */
/*   Updated: 2026/03/10 14:00:00 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_texture_color(t_game *game, t_ray *ray, int tex_x, int tex_y)
{
	int	*textures[4];

	textures[0] = (int *)game->texture.north_img;
	textures[1] = (int *)game->texture.south_img;
	textures[2] = (int *)game->texture.west_img;
	textures[3] = (int *)game->texture.east_img;
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (textures[3][tex_y * game->texture.width + tex_x]);
		else
			return (textures[2][tex_y * game->texture.width + tex_x]);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (textures[1][tex_y * game->texture.width + tex_x]);
		else
			return (textures[0][tex_y * game->texture.width + tex_x]);
	}
}

static int	calculate_texture_x(t_game *game, t_ray *ray)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)game->texture.width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = game->texture.width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = game->texture.width - tex_x - 1;
	return (tex_x);
}

static void	draw_ceiling_floor(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
		put_pixel(game, x, y++, game->ceiling.rgb);
	y = ray->draw_end + 1;
	while (y < WIN_HEIGHT)
		put_pixel(game, x, y++, game->floor.rgb);
}

static void	draw_wall_column(t_game *game, t_ray *ray, int x, int tex_x)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	step = 1.0 * game->texture.height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2)
		* step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (game->texture.height - 1);
		tex_pos += step;
		color = get_texture_color(game, ray, tex_x, tex_y);
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		put_pixel(game, x, y++, color);
	}
}

void	draw_walls(t_game *game, t_ray *ray, int x)
{
	int	tex_x;

	tex_x = calculate_texture_x(game, ray);
	draw_ceiling_floor(game, ray, x);
	draw_wall_column(game, ray, x, tex_x);
}
