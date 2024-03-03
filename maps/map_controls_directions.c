#include "map.h"

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
	if ((strncmp(map->map[i], "SO ", 3) == 0) && (map->soflag != 1))
	{
		map->sotexturepath = texture_path_handler(map->map[i]);
		if (!map->sotexturepath)
			ft_err_mapcontrol("sotexturepath bos olmamali hatalidir! \n", map);
		map->soflag = 1;
		map->flagcount++;
		return (1);
	}
	else if ((strncmp(map->map[i], "SO", 2) == 0) && (map->soflag == 1))
		ft_err_mapcontrol(" \n Error! SO dan iki tane var burda programı bitir error mesaji ver",
			map);
	return (0);
}

int	map_no_control(t_map *map, int i)
{
	if ((strncmp(map->map[i], "NO ", 3) == 0) && (map->noflag != 1))
	{
		map->notexturepath = texture_path_handler(map->map[i]);
		if (!map->notexturepath)
			ft_err_mapcontrol("notexturepath bos olmamali hatalidir! \n", map);
		map->noflag = 1;
		map->flagcount++;
		return (1);
	}
	else if ((strncmp(map->map[i], "NO", 2) == 0) && (map->noflag == 1))
		ft_err_mapcontrol(" \n Error! NO dan iki tane var burda programı bitir error mesaji ver",
			map);
	return (0);
}

int	map_ea_control(t_map *map, int i)
{
	if ((strncmp(map->map[i], "EA ", 3) == 0) && (map->eaflag != 1))
	{
		map->eatexturepath = texture_path_handler(map->map[i]);
		if (!map->eatexturepath)
			ft_err_mapcontrol("eatexturepath bos olmamali hatalidir! \n", map);
		map->eaflag = 1;
		map->flagcount++;
		return (1);
	}
	else if ((strncmp(map->map[i], "EA", 2) == 0) && (map->eaflag == 1))
		ft_err_mapcontrol(" \n Error! EA dan iki tane var burda programı bitir error mesaji ver",
			map);
	return (0);
}

int	map_we_control(t_map *map, int i)
{
	if ((strncmp(map->map[i], "WE ", 3) == 0) && (map->weflag != 1))
	{
		map->wetexturepath = texture_path_handler(map->map[i]);
		if (!map->wetexturepath)
			ft_err_mapcontrol("wetexturepath bos olmamali hatalidir! \n", map);
		map->weflag = 1;
		map->flagcount++;
		return (1);
	}
	else if ((strncmp(map->map[i], "WE", 2) == 0) && (map->weflag == 1))
		ft_err_mapcontrol(" \n Error! WE dan iki tane var burda programı bitir error mesaji ver",
			map);
	return (0);
}
