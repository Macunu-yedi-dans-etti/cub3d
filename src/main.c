/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:27:57 by haloztur          #+#    #+#             */
/*   Updated: 2025/10/09 16:27:58 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	validate_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		printf(ERR_ARGS);
		return (0);
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strcmp(argv[1] + len - 4, ".cub") != 0)
	{
		printf(ERR_FILE);
		return (0);
	}
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
		error_exit(&game, ERR_MAP);
	if (!validate_map(&game))
		error_exit(&game, ERR_MAP);
	init_game(&game);
	start_game(&game);
	cleanup_game(&game);
	return (0);
}