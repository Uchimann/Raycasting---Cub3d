#include "../maps/map.h"

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
		if (a == 0)
		{
			game->sideDistX += game->deltaDistX;
			game->mapX += game->stepX;
			game->side = a;
		}
		else if (a == 1)
		{
			game->sideDistY += game->deltaDistY;
			game->mapY += game->stepY;
			game->side = a;
		}
		if (game->map->realmap[(int)game->mapY][(int)game->mapX] == '1')
		{
			break ;
		}
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
		game->texX = TEXWIDTH - game->texX - 1;
	if (game->side == 1 && game->rayDirY > 0)
		game->texX = TEXWIDTH - game->texX - 1;
	game->step = 1.0 * TEXHEIGHT / game->lineH;
	game->texPos = (game->drawStart - HEIGHT / 2 + game->lineH / 2)
		* game->step;
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
		game->texX = TEXWIDTH - game->texX - 1;
	if (game->side == 1 && game->rayDirY > 0)
		game->texX = TEXWIDTH - game->texX - 1;
	game->step = 1.0 * TEXHEIGHT / game->lineH;
	game->texPos = (game->drawStart - HEIGHT / 2 + game->lineH / 2)
		* game->step;
}
