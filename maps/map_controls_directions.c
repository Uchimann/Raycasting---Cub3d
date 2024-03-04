/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_controls_directions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icelebi <icelebi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:56:02 by icelebi           #+#    #+#             */
/*   Updated: 2024/03/04 15:21:06 by icelebi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "../libft/libft.h"
#include <fcntl.h>

int	try_path(char *str)
{
	int	fd;

	fd = open(str, 777);
	if (fd == -1)
		return (0);
	else
	{
		close(fd);
		return (1);
	}
}

int	map_so_control(t_map *map, int i)
{
	if ((ft_strncmp(map->map[i], "SO ", 3) == 0) && (map->soflag != 1))
	{
		map->sotexturepath = texture_path_handler(map->map[i]);
		if (!map->sotexturepath)
			ft_err_mapcontrol("sotexturepath musnt be empty! \n", map);
		map->soflag = 1;
		map->flagcount++;
		return (1);
	}
	else if ((ft_strncmp(map->map[i], "SO", 2) == 0) && (map->soflag == 1))
		ft_err_mapcontrol(" \n Error! SO more than one in map", map);
	return (0);
}

int	map_no_control(t_map *map, int i)
{
	if ((ft_strncmp(map->map[i], "NO ", 3) == 0) && (map->noflag != 1))
	{
		map->notexturepath = texture_path_handler(map->map[i]);
		if (!map->notexturepath)
			ft_err_mapcontrol("notexturepath not must empty! \n", map);
		map->noflag = 1;
		map->flagcount++;
		return (1);
	}
	else if ((ft_strncmp(map->map[i], "NO", 2) == 0) && (map->noflag == 1))
		ft_err_mapcontrol(" \n Error! NO is more than one in map", map);
	return (0);
}

int	map_ea_control(t_map *map, int i)
{
	if ((ft_strncmp(map->map[i], "EA ", 3) == 0) && (map->eaflag != 1))
	{
		map->eatexturepath = texture_path_handler(map->map[i]);
		if (!map->eatexturepath)
			ft_err_mapcontrol("eatexturepath not should be empty! \n", map);
		map->eaflag = 1;
		map->flagcount++;
		return (1);
	}
	else if ((ft_strncmp(map->map[i], "EA", 2) == 0) && (map->eaflag == 1))
		ft_err_mapcontrol(" \n Error! EA more than one in map", map);
	return (0);
}

int	map_we_control(t_map *map, int i)
{
	if ((ft_strncmp(map->map[i], "WE ", 3) == 0) && (map->weflag != 1))
	{
		map->wetexturepath = texture_path_handler(map->map[i]);
		if (!map->wetexturepath)
			ft_err_mapcontrol("wetexturepath not should be empty! \n", map);
		map->weflag = 1;
		map->flagcount++;
		return (1);
	}
	else if ((ft_strncmp(map->map[i], "WE", 2) == 0) && (map->weflag == 1))
		ft_err_mapcontrol(" \n Error! WE more than one in map", map);
	return (0);
}
