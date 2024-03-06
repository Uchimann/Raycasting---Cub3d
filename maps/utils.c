/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icelebi <icelebi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:56:24 by icelebi           #+#    #+#             */
/*   Updated: 2024/03/05 17:13:36 by icelebi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../minilibx/mlx.h"

int	ft_err(char *str, t_game *game)
{
	ft_err_mapcontrol(str, game->map);
	if (game->no != NULL)
	{
		mlx_destroy_image(game->mlx, game->no->image);
		free(game->no);
	}
	if (game->so != NULL)
	{
		mlx_destroy_image(game->mlx, game->so->image);
		free(game->so);
	}
	if (game->we != NULL)
	{
		mlx_destroy_image(game->mlx, game->we->image);
		free(game->we);
	}
	if (game->ea != NULL)
	{
		mlx_destroy_image(game->mlx, game->ea->image);
		free(game->ea);
	}
	if (game->image != NULL)
		free(game->image);
	return (0);
}

int	ft_err_mapcontrol(char *str, t_map *map)
{
	if (map->map_line != NULL)
		free(map->map_line);
	if (map->tmp_map != NULL)
		free_array2d(map->tmp_map);
	if (map->realmap != NULL)
		free_array2d(map->realmap);
	if (map->map != NULL)
		free_array2d(map->map);
	if (map->map_buff != NULL)
		free_array2d(map->map_buff);
	if (map->eatexturepath != NULL)
		free(map->eatexturepath);
	if (map->notexturepath != NULL)
		free(map->notexturepath);
	if (map->sotexturepath != NULL)
		free(map->sotexturepath);
	if (map->wetexturepath != NULL)
		free(map->wetexturepath);
	printf("%s\n", str);
	system("leaks cub3D");
	exit(0);
}
