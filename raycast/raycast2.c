#include "../maps/map.h"

static bool	south_north(t_game *game)
{
	if (game->map->pov == 'S')
	{
		game->dirX = 0;
		game->dirY = 1;
		game->planeX = -0.66;
		game->planeY = 0;
		return (true);
	}
	else if (game->map->pov == 'N')
	{
		game->dirX = 0;
		game->dirY = -1.00;
		game->planeX = 0.66;
		game->planeY = 0;
		return (true);
	}
	return (false);
}

static bool	east_west(t_game *game)
{
	if (game->map->pov == 'W')
	{
		game->dirX = -1.0;
		game->dirY = 0.0;
		game->planeX = 0.0;
		game->planeY = -0.66;
		return (true);
	}
	else if (game->map->pov == 'E')
	{
		game->dirX = 1.0;
		game->dirY = 0.0;
		game->planeX = 0.0;
		game->planeY = 0.66;
		return (true);
	}
	return (false);
}

bool	check_player(t_game *game)
{
	if (east_west(game))
		return (true);
	if (south_north(game))
		return (true);
	return (false);
}

void	ray_init(t_game *game)
{
	if (!check_player(game))
		return (void)(ft_err("Error in check player \n", game));
	game->posX = game->map->pos_x + 0.5;
	game->posY = game->map->pos_y + 0.5;
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
		ft_err("EXIT complete", game);
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

