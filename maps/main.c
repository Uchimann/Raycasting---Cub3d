/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icelebi <icelebi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:56:48 by icelebi           #+#    #+#             */
/*   Updated: 2024/03/03 17:06:04 by icelebi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdio.h>

int	exit_mlx(t_game *game)
{
	return (ft_err("exit successful", game));
}

void	render_column(t_game *game, int x, int y)
{
	while (++y < HEIGHT)
	{
		game->texy = (int)game->texpos;
		if (y < game->drawstart)
			game->image->addr[y * WIDTH + x] = game->map->ccolor;
		else if (y > game->drawend)
			game->image->addr[y * WIDTH + x] = game->map->fcolor;
		else
		{
			if (game->side == 1 && game->raydiry < 0)
				game->image->addr[y * WIDTH + x] = game->no->addr[TEXHEIGHT
					* game->texy + game->texx];
			else if (game->side == 1 && game->raydiry >= 0)
				game->image->addr[y * WIDTH + x] = game->so->addr[TEXHEIGHT
					* game->texy + game->texx];
			if (game->side == 0 && game->raydirx < 0)
				game->image->addr[y * WIDTH + x] = game->we->addr[TEXHEIGHT
					* game->texy + game->texx];
			else if (game->side == 0 && game->raydirx >= 0)
				game->image->addr[y * WIDTH + x] = game->ea->addr[TEXHEIGHT
					* game->texy + game->texx];
			game->texpos += game->step;
		}
	}
}

int	main(int ac, char **av)
{
	t_map	map;
	t_game	game;

	if (ac != 2)
	{
		printf("Arguments Error\n");
		exit(0);
	}
	game.map = &map;
	map_control(&map, av[1]);
	ray_init(&game);
	game.mlx = mlx_init();
	if (game.mlx == NULL)
	{
		printf("mlx init error\n");
		exit(0);
	}
	game.mlxwin = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3D");
	ft_mlx(&game, 0, 0);
	mlx_hook(game.mlxwin, 2, 1L << 0, move_press, &game);
	mlx_hook(game.mlxwin, 3, 1L << 1, move_release, &game);
	mlx_hook(game.mlxwin, 17, 1L << 17, exit_mlx, &game);
	mlx_loop_hook(game.mlx, &gamefunc, &game);
	mlx_loop(game.mlx);
	free_map(&map);
}
