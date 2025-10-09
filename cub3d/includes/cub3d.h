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

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define WINDOW_TITLE "cub3d"

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define WALL '1'
# define EMPTY '0'
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'

# define ERR_ARGS "Error\nInvalid number of arguments\n"
# define ERR_FILE "Error\nCannot open file\n"
# define ERR_MAP "Error\nInvalid map\n"
# define ERR_TEXTURE "Error\nInvalid texture\n"
# define ERR_COLOR "Error\nInvalid color\n"
# define ERR_MLX "Error\nMLX initialization failed\n"
# define ERR_MALLOC "Error\nMemory allocation failed\n"

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
	int		width;
	int		height;
}	t_texture;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
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
void	*gc_calloc(t_gc *gc, size_t count, size_t size);
char	*gc_strdup(t_gc *gc, const char *s);
void	**gc_track_array(t_gc *gc, void **array);
void	gc_free_all(t_gc *gc);

int		main(int argc, char **argv);
void	init_game(t_game *game);
void	start_game(t_game *game);
int		game_loop(t_game *game);
void	cleanup_game(t_game *game);

int		parse_file(t_game *game, char *filename);
int		parse_map(t_game *game, char **lines, int start);
int		parse_textures(t_game *game, char **lines);
int		parse_colors(t_game *game, char **lines);
int		validate_map(t_game *game);

void	raycast(t_game *game);
void	cast_rays(t_game *game);
void	calculate_ray(t_game *game, t_ray *ray, int x);
void	perform_dda(t_game *game, t_ray *ray);
void	draw_wall(t_game *game, t_ray *ray, int x);
void	calculate_wall_height(t_ray *ray);
void	draw_walls(t_game *game, t_ray *ray, int x);
void	init_ray(t_game *game, t_ray *ray, int x);

void	render_frame(t_game *game);
void	draw_background(t_game *game);
void	put_pixel(t_game *game, int x, int y, int color);
int		get_texture_color(t_game *game, t_ray *ray, int tex_x, int tex_y);

int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
void	handle_movement(t_game *game);
void	update_player_movement(t_game *game);
void	move_player(t_game *game, double move_x, double move_y);
void	rotate_player(t_game *game, double angle);

void	error_exit(t_game *game, char *message);
int		is_valid_extension(char *filename, char *extension);
int		create_rgb(int r, int g, int b);
char	**read_file_lines(char *filename, t_gc *gc);

#endif