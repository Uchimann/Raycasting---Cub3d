#include <stdio.h>
#include "map.h"

static void	ft_mlx2(t_game *g, int c)
{
	g->NO->addr = (int *)mlx_get_data_addr(g->NO->image, &c, &c, &c);
	g->SO->addr = (int *)mlx_get_data_addr(g->SO->image, &c, &c, &c);
	g->WE->addr = (int *)mlx_get_data_addr(g->WE->image, &c, &c, &c);
	g->EA->addr = (int *)mlx_get_data_addr(g->EA->image, &c, &c, &c);
	if (!g->NO->addr || !g->SO->addr || !g->WE->addr || !g->EA->addr)
		return (ft_err("dosya okunamadi",g));
}

void	ft_mlx(t_game *g, int a, int b)
{
	g->image = malloc(sizeof(t_image));
	g->NO = malloc(sizeof(t_image));
	g->SO = malloc(sizeof(t_image));
	g->WE = malloc(sizeof(t_image));
	g->EA = malloc(sizeof(t_image));
	if (!g->image || !g->NO || !g->SO || !g->WE || !g->EA)
		return (ft_err("Yön malloc acilmadi",g));
	g->image->image = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!g->image->image)
		return (ft_err("image malloc acilmadi",g));
	g->image->addr = (int *)mlx_get_data_addr(g->image->image, &a, &a, &a);
	if (!g->image->addr)
		return (ft_err("image addr malloc acilmadi",g));
	//printf("YYYYYYYYYYYYYYYYYYYYYYYYYYY\nNO: %s\n",g->map->notexturepath);
	//printf("SO: %s\n",g->map->sotexturepath);
	//printf("WE: %s\n",g->map->wetexturepath);
	//printf("EA: %s\n",g->map->eatexturepath);
	//printf("%d\n",b);
	g->NO->image = mlx_xpm_file_to_image(g->mlx, g->map->notexturepath, &b, &b);
	g->SO->image = mlx_xpm_file_to_image(g->mlx, g->map->sotexturepath, &b, &b);
	g->WE->image = mlx_xpm_file_to_image(g->mlx, g->map->wetexturepath, &b, &b);
	g->EA->image = mlx_xpm_file_to_image(g->mlx, g->map->eatexturepath, &b, &b);
	if (!g->NO->image || !g->SO->image || !g->WE->image || !g->EA->image)
		return (ft_err("dosya acilmadi",g));
	ft_mlx2(g, b);
}

void	ray_init(t_game *game)
{
	game->posX = game->map->pos_y + 0.5;
	game->posY = game->map->pos_x + 0.5;
	game->dirX = 0;
	game->dirY = -1;
	game->planeX = 0.66;
	game->planeY = 0;
	game->speed = 0.08;
	game->rspeed = 0.04;
	game->w = false;
	game->a = false;
	game->s = false;
	game->d = false;
	game->left = false;
	game->right = false;
}
int	move_press(int keyCode, t_game *game)
{
	if (keyCode == 53)
		ft_err("cikis yapildi",game);
	if (keyCode == 13)
		game->w = true;
	if (keyCode == 1)
		game->s = true;
	if (keyCode == 0)
		game->a = true;
	if (keyCode == 2)
		game->d = true;
	if (keyCode == 124)
		game->right = true;
	if (keyCode == 123)
		game->left = true;
	return (0);
}

int	move_release(int keyCode, t_game *game)
{
	if (keyCode == 13)
		game->w = false;
	if (keyCode == 1)
		game->s = false;
	if (keyCode == 0)
		game->a = false;
	if (keyCode == 2)
		game->d = false;
	if (keyCode == 124)
		game->right = false;
	if (keyCode == 123)
		game->left = false;
	return (0);
}

int	exit_mlx(t_game *game)
{
	return (ft_err("cikis yapildi",game));
}

void	movement(t_game *game)
{
	if (game->w)
	{
		if (game->map->realmap[(int)(game->posY)][(int)(game->posX
				+ game->dirX * game->speed)] != '1')
			game->posX += game->dirX * game->speed;
		if (game->map->realmap[(int)(game->posY + game->dirY
				* game->speed)][(int)(game->posX)] != '1')
			game->posY += game->dirY * game->speed;
	}
	if (game->s)
	{
		if (game->map->realmap[(int)(game->posY)][(int)(game->posX
				- game->dirX * game->speed)] != '1')
			game->posX -= game->dirX * game->speed;
		if (game->map->realmap[(int)(game->posY - game->dirY
				* game->speed)][(int)(game->posX)] != '1')
			game->posY -= game->dirY * game->speed;
	}
	movement_2(game);
}
void	movement_2(t_game *game)
{
	if (game->a)
	{
		if (game->map->realmap[(int)(game->posY)][(int)(game->posX
				- game->planeX * game->speed)] != '1')
			game->posX -= game->planeX * game->speed;
		if (game->map->realmap[(int)(game->posY - game->planeY
				* game->speed)][(int)(game->posX)] != '1')
			game->posY -= game->planeY * game->speed;
	}
	if (game->d)
	{
		if (game->map->realmap[(int)(game->posY)][(int)(game->posX
				+ game->planeX * game->speed)] != '1')
			game->posX += game->planeX * game->speed;
		if (game->map->realmap[(int)(game->posY + game->planeY
				* game->speed)][(int)(game->posX)] != '1')
			game->posY += game->planeY * game->speed;
	}
}
void	rotate(t_game *g, double dir, double plane)
{
	if (g->right)
	{
		dir = g->dirX;
		g->dirX = g->dirX * cos(g->rspeed) - g->dirY * sin(g->rspeed);
		g->dirY = dir * sin(g->rspeed) + g->dirY * cos(g->rspeed);
		plane = g->planeX;
		g->planeX = g->planeX * cos(g->rspeed) - g->planeY
			* sin(g->rspeed);
		g->planeY = plane * sin(g->rspeed) + g->planeY * cos(g->rspeed);
	}
	if (g->left)
	{
		dir = g->dirX;
		g->dirX = g->dirX * cos(g->rspeed) + g->dirY * sin(g->rspeed);
		g->dirY = -dir * sin(g->rspeed) + g->dirY * cos(g->rspeed);
		plane = g->planeX;
		g->planeX = g->planeX * cos(g->rspeed) + g->planeY
			* sin(g->rspeed);
		g->planeY = -plane * sin(g->rspeed) + g->planeY * cos(g->rspeed);
	}
}

void	calculate_ray(t_game *game, int x)
{
	game->cameraX = 2 * x / (double)WIDTH - 1;
	game->rayDirX = game->dirX + game->planeX * game->cameraX;
	game->rayDirY = game->dirY + game->planeY * game->cameraX;
	game->mapX = (int)game->posX;
	game->mapY = (int)game->posY;
	if (game->rayDirX == 0)
		game->deltaDistX = 1e30;
	else
		game->deltaDistX = fabs(1 / game->rayDirX);
	if (game->rayDirY == 0)
	{
		game->dirY = 0.001f;
		game->deltaDistY = 1e30;
	}
	else
		game->deltaDistY = fabs(1 / game->rayDirY);
}

void	calculate_step(t_game *g)
{
	if (g->rayDirX < 0)
	{
		g->stepX = -1;
		g->sideDistX = (g->posX - g->mapX) * g->deltaDistX;
	}
	else
	{
		g->stepX = 1;
		g->sideDistX = (g->mapX + 1.0 - g->posX) * g->deltaDistX;
	}
	if (g->rayDirY < 0)
	{
		g->stepY = -1;
		g->sideDistY = (g->posY - g->mapY) * g->deltaDistY;
	}
	else
	{
		g->stepY = 1;
		g->sideDistY = (g->mapY + 1.0 - g->posY) * g->deltaDistY;
	}
}

void	calculate_hit_distance(t_game *game)
{
	int	a;

	while (1)
	{
		a = !(game->sideDistX < game->sideDistY);
		if(a == 0)
		{
			game->sideDistX += game->deltaDistX;
			game->mapX += game->stepX;
			game->side = a;
		}
		else
		{
			game->sideDistY += game->deltaDistY;
			game->mapY += game->stepY;
			game->side = a;
		}
		if (game->map->realmap[game->mapY][game->mapX] == '1')
			break ;
	}
}
void	calculate_wall_height_x(t_game *game)
{
	game->perpWallDist = game->sideDistX - game->deltaDistX;
	game->lineH = (int)(HEIGHT / game->perpWallDist);
	game->drawStart = -game->lineH / 2 + HEIGHT / 2;
	game->drawStart = (game->drawStart >= 0) * game->drawStart;
	game->drawEnd = game->lineH / 2 + HEIGHT / 2;
	if (game->drawEnd >= HEIGHT)
		game->drawEnd = HEIGHT - 1;
	game->wallX = game->posY + game->perpWallDist * game->rayDirY;
	game->wallX = game->wallX - (int)game->wallX;
	game->texX = (int)(game->wallX * (double)TEXWIDTH);
	if (game->side == 0 && game->rayDirX < 0)
		game->texX = TEXWIDTH - game->texX- 1;
	if (game->side == 1 && game->rayDirY > 0)
		game->texX = TEXWIDTH - game->texX - 1;
	game->step = 1.0 * TEXHEIGHT / game->lineH;
	game->texPos = (game->drawStart - HEIGHT / 2 + game->lineH / 2) * game->step;
}
void	calculate_wall_height_y(t_game *game)
{
	game->perpWallDist = game->sideDistY - game->deltaDistY;
	game->lineH = (int)(HEIGHT / game->perpWallDist);
	game->drawStart = -game->lineH / 2 + HEIGHT / 2;
	game->drawStart = (game->drawStart >= 0) * game->drawStart;
	game->drawEnd = game->lineH / 2 + HEIGHT / 2;
	if (game->drawEnd >= HEIGHT)
		game->drawEnd = HEIGHT - 1;
	game->wallX = game->posX + game->perpWallDist * game->rayDirX;
	game->wallX = game->wallX - (int)game->wallX;
	game->texX = (int)(game->wallX * (double)TEXWIDTH);
	if (game->side == 0 && game->rayDirX < 0)
		game->texX = TEXWIDTH - game->texX- 1;
	if (game->side == 1 && game->rayDirY > 0)
		game->texX = TEXWIDTH - game->texX - 1;
	game->step = 1.0 * TEXHEIGHT / game->lineH;
	game->texPos = (game->drawStart - HEIGHT / 2 + game->lineH / 2) * game->step;
}
void	calculate_wall_height(t_game *game)
{
	if (game->side == 0)
		calculate_wall_height_x(game);
	else
		calculate_wall_height_y(game);
}

void	render_column(t_game *game, int x, int y)
{
	while (++y < HEIGHT)
	{
		game->texX = (int)game->texPos;
		if (y < game->drawStart)
			game->image->addr[y * WIDTH + x] = game->map->ccolor;
		else if (y > game->drawEnd)
			game->image->addr[y * WIDTH + x] = game->map->fcolor;
		else
		{
			if (game->side == 1 && game->rayDirY < 0)
				game->image->addr[y * WIDTH + x] = game->NO->addr[TEXHEIGHT
					* game->texY + game->texX];
			else if (game->side == 1 && game->rayDirY >= 0)
				game->image->addr[y * WIDTH + x] = game->SO->addr[TEXHEIGHT
					* game->texY + game->texX];
			if (game->side == 0 && game->rayDirX < 0)
				game->image->addr[y * WIDTH + x] = game->WE->addr[TEXHEIGHT
					* game->texY + game->texX];
			else if (game->side == 0 && game->rayDirX >= 0)
				game->image->addr[y * WIDTH + x] = game->EA->addr[TEXHEIGHT
					* game->texY + game->texX];
			game->texPos += game->step;
		}
	}
}

static void	raycast(t_game *g)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		calculate_ray(g, x);
		calculate_step(g);
		calculate_hit_distance(g);
		calculate_wall_height(g);
		render_column(g, x, -1);
	}
	mlx_put_image_to_window(g->mlx, g->mlxWin, g->image->image, 0, 0);
}

int	gamefunc(t_game *game)
{
	movement(game);
	rotate(game, 0, 0);
	raycast(game);
	return (0);
}

int main(int ac, char **av)
{
    if(ac != 2)
    {
        printf("Arguments Error\n");
        exit(0);
    }
    t_map map;
    t_game game;
    game.map = &map;
    map_control(&map,av[1]);
    //////////////////////////////////////////////////////////////
	//printf("Kontrol 1 --> %s\n",game.map->notexturepath);
    ray_init(&game);
    game.mlx = mlx_init();
	game.mlxWin = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3D");

    ft_mlx(&game, 0, 0);
    mlx_hook(game.mlxWin, 2, 1L << 0, move_press, &game);
	mlx_hook(game.mlxWin, 3, 1L << 1, move_release, &game);
	mlx_hook(game.mlxWin, 17, 1L << 17, exit_mlx, &game);
	mlx_loop_hook(game.mlx, &gamefunc, &game);
	mlx_loop(game.mlx);
    free_map(&map);

}