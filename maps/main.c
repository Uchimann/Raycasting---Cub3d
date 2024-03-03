#include "map.h"
#include <stdio.h>

int	exit_mlx(t_game *game)
{
	return (ft_err("cikis yapildi", game));
}

void	render_column(t_game *game, int x, int y)
{
	while (++y < HEIGHT)
	{
		game->texY = (int)game->texPos;
		if (y < game->drawStart)
			game->image->addr[y * WIDTH + x] = game->map->ccolor;
		else if (y > game->drawEnd)
			game->image->addr[y * WIDTH + x] = game->map->fcolor;
		else
		{
			if (game->side == 1 && game->rayDirY < 0)
				game->image->addr[y * WIDTH + x] = game->NO->addr[TEXHEIGHT * game->texY + game->texX];
			else if (game->side == 1 && game->rayDirY >= 0)
				game->image->addr[y * WIDTH + x] = game->SO->addr[TEXHEIGHT * game->texY + game->texX];
			if (game->side == 0 && game->rayDirX < 0)
				game->image->addr[y * WIDTH + x] = game->WE->addr[TEXHEIGHT * game->texY + game->texX];
			else if (game->side == 0 && game->rayDirX >= 0)
				game->image->addr[y * WIDTH + x] = game->EA->addr[TEXHEIGHT * game->texY + game->texX];
			game->texPos += game->step;
		}
	}
}
// plane = ekran düzlemi/kamera düzlemi
int	main(int ac, char **av)  
{
	if (ac != 2)
	{
		printf("Arguments Error\n");
		exit(0);
	}
	t_map map;
	t_game game;
	game.map = &map;
	map_control(&map, av[1]);

	ray_init(&game);
	game.mlx = mlx_init();
	if(game.mlx == NULL)
	{
		printf("mlx init error\n");
		exit(0);
	}
	game.mlxWin = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3D");

	ft_mlx(&game, 0, 0);
	mlx_hook(game.mlxWin, 2, 1L << 0, move_press, &game);
	mlx_hook(game.mlxWin, 3, 1L << 1, move_release, &game);
	mlx_hook(game.mlxWin, 17, 1L << 17, exit_mlx, &game);
	mlx_loop_hook(game.mlx, &gamefunc, &game);
	write(1, "\n--------------------------\n", 28);
	mlx_loop(game.mlx);
	// system("leaks");*/
	free_map(&map);
	return (0);
}
