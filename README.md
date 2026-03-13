*This project has been created as part of the 42 curriculum by haloztur, musoysal.*

## Description

cub3d is a raycasting engine. The goal is to render a 3D perspective view from a 2D map using the DDA (Digital Differential Analyzer) raycasting algorithm.

The project consists of:

- **Parser**: Reads `.cub` configuration files containing texture paths (NO, SO, EA, WE), floor and ceiling colors (F, C), and a 2D map grid
- **Raycasting**: DDA algorithm to cast rays and compute wall distances
- **Rendering**: [MinilibX-based](https://harm-smits.github.io/42docs/libs/minilibx) graphics with texture mapping and floor/ceiling colors
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

### Map Format

The `.cub` file must include textures, colors, and the map layout. Here is an example of a valid configuration:

```bash
NO textures/wolfenstein/grey_stone.xpm
SO textures/wolfenstein/purple_stone.xpm
WE textures/wolfenstein/red_brick.xpm
EA textures/wolfenstein/wood.xpm

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101  101111010001
11111111 1111111 111111111111
```

The map can contain spaces, but it must be surrounded by walls (`1`). The player starting position is indicated by `N`, `S`, `E`, or `W`.

## Resources

### References

- [Lodev Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [MinilibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)

### AI Usage

AI was used primarily for research purposes, helping to understand the DDA algorithm, exploring raycasting concepts, and finding solutions to specific technical challenges during development.
