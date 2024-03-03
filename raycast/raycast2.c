/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icelebi <icelebi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:56:31 by icelebi           #+#    #+#             */
/*   Updated: 2024/03/03 16:55:37 by icelebi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../maps/map.h"

static bool	south_north(t_game *game)
{
	if (game->map->pov == 'S')
	{
		game->dirx = 0;
		game->diry = 1;
		game->planex = -0.66;
		game->planey = 0;
		return (true);
	}
	else if (game->map->pov == 'N')
	{
		game->dirx = 0;
		game->diry = -1.00;
		game->planex = 0.66;
		game->planey = 0;
		return (true);
	}
	return (false);
}

static bool	east_west(t_game *game)
{
	if (game->map->pov == 'W')
	{
		game->dirx = -1.0;
		game->diry = 0.0;
		game->planex = 0.0;
		game->planey = -0.66;
		return (true);
	}
	else if (game->map->pov == 'E')
	{
		game->dirx = 1.0;
		game->diry = 0.0;
		game->planex = 0.0;
		game->planey = 0.66;
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
		return ((void)(ft_err("Error in check player \n", game)));
	game->posx = game->map->pos_x + 0.5;
	game->posy = game->map->pos_y + 0.5;
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
