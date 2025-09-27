#include "../../includes/cub3d.h"

static int	is_position_in_bounds(t_map *map, int relative_x, int relative_y)
{
	int	map_x;
	int	map_y;

	map_x = map->player_start_x + relative_x;
	map_y = map->player_start_y + relative_y;
	if (map_y < 0 || map_y >= map->height)
		return (0);
	if (map_x < 0 || map_x >= (int)ft_strlen(map->grid[map_y]))
		return (0);
	return (map->grid[map_y][map_x] != ' ');
}

static int	is_player_position_valid(t_map *map)
{
	if (!is_position_in_bounds(map, -1, 0) ||
		!is_position_in_bounds(map, 1, 0) ||
		!is_position_in_bounds(map, 0, -1) ||
		!is_position_in_bounds(map, 0, 1))
		return (0);
	return (1);
}

static int	check_player_count_and_position(t_map *map)
{
	int	row;
	int	col;
	int	player_count;
	char	cell;

	player_count = 0;
	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < (int)ft_strlen(map->grid[row]))
		{
			cell = map->grid[row][col];
			if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
			{
				player_count++;
				map->player_start_x = col;
				map->player_start_y = row;
				if (!is_player_position_valid(map))
					return (0);
			}
			col++;
		}
		row++;
	}
	return (player_count == 1);
}

static int	check_map_borders(t_map *map)
{
	int	col;
	int	row;
	int	last_row;
	int	line_len;
	char	top_char;
	char	bottom_char;
	char	left_char;
	char	right_char;

	col = 0;
	while (col < (int)ft_strlen(map->grid[0]))
	{
		top_char = map->grid[0][col];
		if (top_char != '1' && top_char != ' ')
			return (0);
		col++;
	}
	last_row = map->height - 1;
	col = 0;
	while (col < (int)ft_strlen(map->grid[last_row]))
	{
		bottom_char = map->grid[last_row][col];
		if (bottom_char != '1' && bottom_char != ' ')
			return (0);
		col++;
	}
	row = 0;
	while (row < map->height)
	{
		left_char = map->grid[row][0];
		if (left_char != '1' && left_char != ' ')
			return (0);
		line_len = ft_strlen(map->grid[row]);
		if (line_len > 0)
		{
			right_char = map->grid[row][line_len - 1];
			if (right_char != '1' && right_char != ' ')
				return (0);
		}
		row++;
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!game->map.north_texture || !game->map.south_texture ||
		!game->map.west_texture || !game->map.east_texture)
		return (0);
	
	if (!check_map_borders(&game->map))
		return (0);
	
	if (!check_player_count_and_position(&game->map))
		return (0);
	
	return (1);
}

static void	set_player_direction(t_game *game, char orientation)
{
	if (orientation == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
	}
	else if (orientation == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
	}
	else if (orientation == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
	else if (orientation == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}
	
	game->player.plane_x = -game->player.dir_y * 0.66;
	game->player.plane_y = game->player.dir_x * 0.66;
}

void	find_player_position(t_game *game)
{
	int	row;
	int	col;
	char	cell;

	game->player.x = 0.0;
	game->player.y = 0.0;
	row = 0;
	while (row < game->map.height)
	{
		col = 0;
		while (col < (int)ft_strlen(game->map.grid[row]))
		{
			cell = game->map.grid[row][col];
			if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
			{
				set_player_direction(game, cell);
				return ;
			}
			col++;
		}
		row++;
	}
}