/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:27:51 by haloztur          #+#    #+#             */
/*   Updated: 2025/10/15 10:59:35 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

static void	calculate_step_and_side_dist(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y)
			* ray->delta_dist_y;
	}
}

void	perform_dda(t_game *game, t_ray *ray)
{
	calculate_step_and_side_dist(game, ray);
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= game->map.height
			|| ray->map_x < 0 || ray->map_x >= game->map.width
			|| game->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	calculate_wall_height(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}
static int get_texture_color(t_game *game, t_ray *ray, int tex_x, int tex_y)
{
	if (ray->side == 0)
		return (game->texture.north_img[tex_y * game->texture.width + tex_x]);
	else if (ray->side == 1)
		return (game->texture.south_img[tex_y * game->texture.width + tex_x]);
	else if (ray->side == 2)
		return (game->texture.west_img[tex_y * game->texture.width + tex_x]);
	else
		return (game->texture.east_img[tex_y * game->texture.width + tex_x]);
	return (game->texture.north_img[tex_y * game->texture.width + tex_x]);
}

void draw_walls(t_game *game, t_ray *ray, int x)
{
	double wall_x;
	int tex_x;
	double step;
	double tex_pos;
	int y;
	int tex_y;
	int color;

	// Duvarın çarpma noktasını bul
	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);

	// Texture X koordinatı
	tex_x = (int)(wall_x * (double)game->texture.width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = game->texture.width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = game->texture.width - tex_x - 1;

	// Texture dikey ölçekleme
	step = 1.0 * game->texture.height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;

	// Tavan
	y = 0;
	while (y < ray->draw_start)
		put_pixel(game, x, y++, game->ceiling.rgb);

	// Duvar
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (game->texture.height - 1);
		tex_pos += step;
		color = get_texture_color(game, ray, tex_x, tex_y);
		if (ray->side == 1)
			color = (color >> 1) & 8355711; // Gölgelendirme efekti
		put_pixel(game, x, y++, color);
	}

	// Zemin
	while (y < WIN_HEIGHT)
		put_pixel(game, x, y++, game->floor.rgb);
}

void raycast(t_game *game)
{
	t_ray ray;
	int x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(game, &ray, x);
		perform_dda(game, &ray);
		calculate_wall_height(game, &ray);
		draw_walls(game, &ray, x);
		x++;
	}
}