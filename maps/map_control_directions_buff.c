#include "map.h"

int	map_so_control_buff(t_map *map, int i)
{
	if ((strncmp(map->map_buff[i], "SO ", 3) == 0) && (map->soflag_buff != 1))
	{
		map->soflag_buff = 1;
		map->flagcount_buff++;
		return (1);
	}
	else
		return (0);
}

int	map_no_control_buff(t_map *map, int i)
{
	if ((strncmp(map->map_buff[i], "NO ", 3) == 0) && (map->noflag_buff != 1))
	{
		map->noflag_buff = 1;
		map->flagcount_buff++;
		return (1);
	}
	else
		return (0);
}

int	map_ea_control_buff(t_map *map, int i)
{
	if ((strncmp(map->map_buff[i], "EA ", 3) == 0) && (map->eaflag_buff != 1))
	{
		map->eaflag_buff = 1;
		map->flagcount_buff++;
		return (1);
	}
	else
		return (0);
}

int	map_we_control_buff(t_map *map, int i)
{
	if ((strncmp(map->map_buff[i], "WE ", 3) == 0) && (map->weflag_buff != 1))
	{
		map->weflag_buff = 1;
		map->flagcount_buff++;
		return (1);
	}
	else
		return (0);
}

int	map_f_control_buff(t_map *map, int i)
{
	if ((strncmp(map->map_buff[i], "F ", 2) == 0) && (map->fflag_buff != 1))
	{
		map->fflag_buff = 1;
		map->flagcount_buff++;
		return (1);
	}
	else
		return (0);
}

int	map_c_control_buff(t_map *map, int i)
{
	if ((strncmp(map->map_buff[i], "C ", 2) == 0) && (map->cflag_buff != 1))
	{
		map->cflag_buff = 1;
		map->flagcount_buff++;
		return (1);
	}
	else
		return (0);
}