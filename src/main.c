/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:27:57 by haloztur          #+#    #+#             */
/*   Updated: 2026/03/10 14:11:41 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	validate_args(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		printf(ERR_USAGE);
		return (0);
	}
	if (!is_valid_extension(argv[1]))
	{
		printf(ERR_FILE_EXTENSION);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf(ERR_FILE);
		return (0);
	}
	close(fd);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!validate_args(argc, argv))
		return (1);
	ft_memset(&game, 0, sizeof(t_game));
	gc_init(&game.gc);
	if (!parse_file(&game, argv[1]))
		error_exit(&game, "");
	if (!validate_map(&game))
		error_exit(&game, "");
	init_game(&game);
	start_game(&game);
	cleanup_game(&game);
	return (0);
}
