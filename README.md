*This project has been created as part of the 42 curriculum by haloztur, musoysal.*

## Description

cub3d is a raycasting engine inspired by Wolfenstein 3D. The goal is to render a 3D perspective view from a 2D map using the DDA (Digital Differential Analyzer) raycasting algorithm.

The project consists of:

- **Parser**: Reads `.cub` configuration files containing texture paths (NO, SO, EA, WE), floor and ceiling colors (F, C), and a 2D map grid
- **Raycasting**: DDA algorithm to cast rays and compute wall distances
- **Rendering**: MinilibX-based graphics with texture mapping and floor/ceiling colors
- **Gameplay**: Player movement (W/A/S/D) and rotation (arrow keys), ESC to quit

## Instructions

### Compilation

```bash
make
```

or

```bash
make all
```

Dependencies (libft and MinilibX) are built automatically. The Makefile detects the platform (Linux or macOS) and links the appropriate MLX libraries.

### Execution

```bash
./cub3d maps/good/<map>.cub
```

Example:

```bash
./cub3d maps/good/cheese_maze.cub
```

The program expects a single argument: a valid `.cub` file path.

### Controls

| Key | Action |
|-----|--------|
| W | Move forward |
| S | Move backward |
| A | Strafe left |
| D | Strafe right |
| Left Arrow | Rotate left |
| Right Arrow | Rotate right |
| ESC | Quit |

### Make Targets

| Target | Description |
|--------|-------------|
| `make` / `make all` | Build the executable |
| `make clean` | Remove object files |
| `make fclean` | Remove objects and executable |
| `make re` | Clean and rebuild |
| `make valgrind` | Run with Valgrind (example map) |

### Map Format

The `.cub` file must include:

- **Textures**: `NO`, `SO`, `EA`, `WE` (north, south, east, west wall paths)
- **Colors**: `F` (floor) and `C` (ceiling) in RGB format: `F R,G,B` and `C R,G,B` (0-255 per channel)
- **Map**: Grid of `0` (empty), `1` (wall), and `N`/`S`/`E`/`W` (player spawn and direction)

## Resources

### References

- [Lodev Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [MinilibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- Wolfenstein 3D (id Software)

### AI Usage

AI usage: [Specify which tasks and parts of the project involved AI assistance.]
