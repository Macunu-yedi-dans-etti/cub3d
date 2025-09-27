#include "../../includes/cub3d.h"

static int	parse_rgb_color(char *line, int *color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(line + 2, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (0);
	r = atoi(rgb[0]);
	g = atoi(rgb[1]);
	b = atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_split(rgb);
		return (0);
	}
	*color = (r << 16) | (g << 8) | b;
	free_split(rgb);
	return (1);
}

static int	parse_texture_line(char *line, t_map *map)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		map->north_texture = ft_strdup(line + 3);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		map->south_texture = ft_strdup(line + 3);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		map->west_texture = ft_strdup(line + 3);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		map->east_texture = ft_strdup(line + 3);
	else if (line[0] == 'F' && line[1] == ' ')
		return (parse_rgb_color(line, &map->floor_color));
	else if (line[0] == 'C' && line[1] == ' ')
		return (parse_rgb_color(line, &map->ceiling_color));
	else
		return (0);
	return (1);
}

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && 
			line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && 
			line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}


static int	parse_map_grid(int fd, t_map *map)
{
	char	*line;
	char	**temp_grid;
	int		line_count;
	int		capacity;
	int		i;
	int		line_width;

	line_count = 0;
	capacity = 100;
	temp_grid = malloc(sizeof(char *) * capacity);
	if (!temp_grid)
		return (0);
	
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_map_line(line))
		{
			if (line_count >= capacity)
			{
				capacity *= 2;
				temp_grid = realloc(temp_grid, sizeof(char *) * capacity);
				if (!temp_grid)
				{
					free(line);
					return (0);
				}
			}
			temp_grid[line_count] = ft_strdup(line);
			if (!temp_grid[line_count])
				{
					free(line);
					return (0);
				}
			line_count++;
		}
		free(line);
		line = get_next_line(fd);
	}	map->height = line_count;
	map->grid = malloc(sizeof(char *) * (line_count + 1));
	if (!map->grid)
		return (0);
	
	map->width = 0;
	i = 0;
	while (i < line_count)
	{
		line_width = ft_strlen(temp_grid[i]);
		map->grid[i] = temp_grid[i];
		if (line_width > map->width)
			map->width = line_width;
		i++;
	}
	map->grid[i] = NULL;
	free(temp_grid);
	return (1);
}

int	parse_map(char *filename, t_game *game)
{
	int		fd;
	char	*line;
	int		parsing_textures;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	parsing_textures = 1;
	game->map.width = 0;
	game->map.height = 0;
	game->map.player_start_x = -1;
	game->map.player_start_y = -1;
	line = get_next_line(fd);
	while (parsing_textures && line != NULL)
	{
		if (!line[0] || line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		if (!is_map_line(line))
		{
			if (!parse_texture_line(line, &game->map))
			{
				free(line);
				close(fd);
				return (0);
			}
		}
		else if (is_map_line(line))
		{
			parsing_textures = 0;
			free(line);
			break;
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!parse_map_grid(fd, &game->map))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
