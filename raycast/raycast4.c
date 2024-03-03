#include "../maps/map.h"

static void	ft_mlx2(t_game *g, int c)
{
	g->NO->addr = (int *)mlx_get_data_addr(g->NO->image, &c, &c, &c);
	g->SO->addr = (int *)mlx_get_data_addr(g->SO->image, &c, &c, &c);
	g->WE->addr = (int *)mlx_get_data_addr(g->WE->image, &c, &c, &c);
	g->EA->addr = (int *)mlx_get_data_addr(g->EA->image, &c, &c, &c);
	if (!g->NO->addr || !g->SO->addr || !g->WE->addr || !g->EA->addr)
		return (void)(ft_err("dosya okunamadi", g));
}

void	ft_mlx(t_game *g, int a, int b)
{
	g->image = malloc(sizeof(t_image));
	g->NO = malloc(sizeof(t_image));
	g->SO = malloc(sizeof(t_image));
	g->WE = malloc(sizeof(t_image));
	g->EA = malloc(sizeof(t_image));
	if (!g->image || !g->NO || !g->SO || !g->WE || !g->EA)
		return (void)(ft_err("Yön malloc acilmadi", g));
	g->image->image = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!g->image->image)
		return (void)(ft_err("image malloc acilmadi", g));
	g->image->addr = (int *)mlx_get_data_addr(g->image->image, &a, &a, &a);
	if (!g->image->addr)
		return (void)(ft_err("image addr malloc acilmadi", g));
	g->NO->image = mlx_xpm_file_to_image(g->mlx, g->map->notexturepath, &b, &b);
	g->SO->image = mlx_xpm_file_to_image(g->mlx, g->map->sotexturepath, &b, &b);
	g->WE->image = mlx_xpm_file_to_image(g->mlx, g->map->wetexturepath, &b, &b);
	g->EA->image = mlx_xpm_file_to_image(g->mlx, g->map->eatexturepath, &b, &b);
	if (!g->NO->image || !g->SO->image || !g->WE->image || !g->EA->image)
		return (void)(ft_err("dosya acilmadi", g));
	ft_mlx2(g, b);
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

void	calculate_wall_height(t_game *game)
{
	if (game->side == 0)
		calculate_wall_height_x(game);
	else if (game->side == 1)
		calculate_wall_height_y(game);
}