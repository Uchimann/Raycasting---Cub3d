#include "../maps/map.h"

void	rotate(t_game *g, double dir, double plane)
{
	if (g->right)
	{
		dir = g->dirX;
		g->dirX = g->dirX * cos(g->rspeed) - g->dirY * sin(g->rspeed);
		// 0.66 0 0 0.66
		g->dirY = dir * sin(g->rspeed) + g->dirY * cos(g->rspeed);
		plane = g->planeX;
		g->planeX = g->planeX * cos(g->rspeed) - g->planeY * sin(g->rspeed);
		g->planeY = plane * sin(g->rspeed) + g->planeY * cos(g->rspeed);
	}
	if (g->left)
	{
		dir = g->dirX;
		g->dirX = g->dirX * cos(g->rspeed) + g->dirY * sin(g->rspeed);
		g->dirY = -dir * sin(g->rspeed) + g->dirY * cos(g->rspeed);
		plane = g->planeX;
		g->planeX = g->planeX * cos(g->rspeed) + g->planeY * sin(g->rspeed);
		g->planeY = -plane * sin(g->rspeed) + g->planeY * cos(g->rspeed);
	}
}

void	movement(t_game *game)
{
	if (game->w)
	{
		if (game->map->realmap[(int)(game->posY)][(int)(game->posX + game->dirX
				* game->speed)] != '1')
			game->posX += game->dirX * game->speed;
		if (game->map->realmap[(int)(game->posY + game->dirY
				* game->speed)][(int)(game->posX)] != '1')
			game->posY += game->dirY * game->speed;
	}
	if (game->s)
	{
		if (game->map->realmap[(int)(game->posY)][(int)(game->posX - game->dirX
				* game->speed)] != '1')
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
