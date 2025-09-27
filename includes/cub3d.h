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
# include "color.h"
# include "get_next_line/get_next_line.h"

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define FOV 60
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_player
{
	double	x; // Oyuncunun haritadaki koordinatı
	double	y;
	double	dir_x;// Oyuncunun baktığı yön vektörü
	double	dir_y;
	double	plane_x;// Kamera düzlemi vektörü (görüş alanı için)
	double	plane_y;
}	t_player;

typedef struct s_ray // steplerden sonrası gpt ekledi anlamadım
{
	double	dir_x;// Işın yön vektörü
	double	dir_y;
	double	delta_dist_x;// Işınların bir sonraki x veya y kenarına olan mesafesi
	double	delta_dist_y;
	double	side_dist_x;// Işının bir sonraki x veya y kenarına olan mesafesi
	double	side_dist_y;
	double	perp_wall_dist;// Duvardan dik mesafe
	int		map_x;// Işının harita kare koordinatları
	int		map_y;
	int		step_x;// Işının x ve y yönündeki adımları
	int		step_y;
	int		hit; // Duvara çarpma durumu
	int		side;// Duvardan çarpılan taraf (0: x, 1: y)
	int		line_height;// Çizilecek duvar çizgisinin yüksekliği
	int		draw_start;// Çizim başlangıç ve bitiş noktaları
	int		draw_end;// Çizim başlangıç ve bitiş noktaları
    int		texture_id;// Kullanılacak doku ID'si
}	t_ray;

typedef struct s_texture //duvar packleri için bu structı ekledim şimdilik değştiricem forumdan gördüm
{
	void	*img;// mlx için
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_map //map kontrolü için gerekli bunu da makaleden gördüm
{
	char	**grid;
	int		width;
	int		height;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color;
	int		ceiling_color;
	int		player_start_x;  // Oyuncunun haritadaki başlangıç X koordinatı
	int		player_start_y;
}	t_map;

typedef struct s_game // Oyun durumu ve verileri için gerekli yapı top versiyon hepsini globale çıkardık tıpkı philodaki gibi
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_player	player;
	t_map		map;
	t_texture	textures[4];
}	t_game;


int		parse_map(char *filename, t_game *game);
int		validate_map(t_game *game);
void	find_player_position(t_game *game);



int file_control(char *file_path, int fd);
void    free_split(char **arr);
void	ft_error(const char *message);

#endif