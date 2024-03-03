#include "../maps/map.h"

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
		ft_err("cikis yapildi", game);
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
