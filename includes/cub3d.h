/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 22:15:00 by haloztur          #+#    #+#             */
/*   Updated: 2026/03/01 15:39:52 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include "../minilibx-linux/mlx.h"
# include "libft/libft.h"

# define WIN_WIDTH 900
# define WIN_HEIGHT 900
# define WIN_TITLE "Cub3D"

# define MOVE_SPEED 0.08
# define ROT_SPEED 0.07

// # define KEY_ESC 53
// # define KEY_W 13
// # define KEY_A 0
// # define KEY_S 1
// # define KEY_D 2
// # define KEY_LEFT 124
// # define KEY_RIGHT 123

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65363
# define KEY_RIGHT 65361

# define WALL '1'
# define EMPTY '0'
# define PLAYER_N 'N'
# define PLAYER_S 'S'
# define PLAYER_E 'E'
# define PLAYER_W 'W'

# define ERR_USAGE "Error\nUsage: ./cub3D <map.cub>\n"
# define ERR_ARGS "Error\nInvalid number of arguments\n"
# define ERR_FILE "Error\nCannot open file\n"
# define ERR_FILE_NOT_FOUND "Error\nFile not found\n"
# define ERR_FILE_PERMISSION "Error\nPermission denied\n"
# define ERR_FILE_EXTENSION "Error\nFile must have .cub extension\n"
# define ERR_MAP_INVALID "Error\nInvalid map\n"
# define ERR_MAP_NOT_CLOSED "Error\nMap not surrounded by walls\n"
# define ERR_MAP_TAB "Error\nMap must not contain tab characters\n"
# define ERR_MAP_EMPTY "Error\nEmpty map\n"
# define ERR_PLAYER_MISSING "Error\nNo player found\n"
# define ERR_PLAYER_MULTIPLE "Error\nMultiple players found\n"
# define ERR_TEXTURE_MISSING "Error\nMissing texture\n"
# define ERR_TEXTURE_INVALID "Error\nInvalid texture file\n"
# define ERR_COLOR_INVALID "Error\nInvalid color format\n"
# define ERR_COLOR_MISSING "Error\nFloor and ceiling color missing or invalid\n"
# define ERR_COLOR_RANGE "Error\nColor values must be 0-255\n"
# define ERR_FLOOR_DUP "Error\nDuplicate floor color\n"
# define ERR_CEILING_DUP "Error\nDuplicate ceiling color\n"
# define ERR_MLX_INIT "Error\nMLX initialization failed\n"
# define ERR_MLX_WIN "Error\nWindow creation failed\n"
# define ERR_MLX_IMG "Error\nImage creation failed\n"
# define ERR_MALLOC "Error\nMemory allocation failed\n"
# define ERR_TEXTURE_LOAD "Error\nTexture loading failed\n"

typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}	t_gc_node;

typedef struct s_gc
{
	t_gc_node	*head;
}	t_gc;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	rgb;
}	t_color;

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	void	*north_img;
	void	*south_img;
	void	*east_img;
	void	*west_img;
	void	*north_img_ptr;
	void	*south_img_ptr;
	void	*east_img_ptr;
	void	*west_img_ptr;
	int		width;
	int		height;
}	t_texture;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_start_x;
	int		player_start_y;
	char	player_start_dir;
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_keys
{
	int	w_pressed;
	int	s_pressed;
	int	a_pressed;
	int	d_pressed;
	int	left_pressed;
	int	right_pressed;
	int	esc_pressed;
}	t_keys;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_game
{
	t_mlx		mlx;
	t_map		map;
	t_player	player;
	t_texture	texture;
	t_color		floor;
	t_color		ceiling;
	t_keys		keys;
	t_gc		gc;
}	t_game;

void	gc_init(t_gc *gc);
void	*gc_track(t_gc *gc, void *ptr);
void	*gc_malloc(t_gc *gc, size_t size);
char	*gc_strdup(t_gc *gc, const char *s);
void	gc_free_all(t_gc *gc);

int		main(int argc, char **argv);
void	init_game(t_game *game);
void	start_game(t_game *game);
int		game_loop(t_game *game);
void	cleanup_game(t_game *game);

int		parse_file(t_game *game, char *filename);
int		parse_textures(t_game *game, char **lines);
int		parse_colors(t_game *game, char **lines);
int		parse_map(t_game *game, char **lines, int start);
int		validate_map(t_game *game);
int		find_player_position(t_game *game);
int		is_map_line(char *line);
void	rgb_free(char **rgb);
int		is_valid_rgb_token(char *s);
int		is_invalid_color_string(char *line);
int		free_ret_err(char **arr, char *err);
int		parse_color_line(char *line, t_color *color);

void	raycast(t_game *game);
void	init_ray(t_game *game, t_ray *ray, int x);
void	perform_dda(t_game *game, t_ray *ray);
void	calculate_wall_height(t_game *game, t_ray *ray);

void	render_frame(t_game *game);
void	draw_background(t_game *game);
void	draw_wall(t_game *game, t_ray *ray, int x);
void	put_pixel(t_game *game, int x, int y, int color);

int		handle_key_press(int keycode, t_game *game);
int		handle_key_release(int keycode, t_game *game);
void	handle_movement(t_game *game);
void	move_player(t_game *game, double move_x, double move_y);
void	rotate_player(t_game *game, double angle);
int		close_window(t_game *game);

void	error_exit(t_game *game, char *message);
int		is_valid_extension(char *filename);
int		create_rgb(int r, int g, int b);
char	**read_file_lines(char *filename, t_gc *gc);

int		load_all_textures(t_game *game);

#endif