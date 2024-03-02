#include "map.h"

void	read_real_map(t_map *map)
{
	int	i;
	int	j;

	i = map->map_start;
	j = 0;
	map->realmap = malloc((map->mapheight - i) * sizeof(char *) + 1);
	while (map->map[i])
	{
		map->realmap[j] = ft_strdup(map->map[i]);
		i++;
		j++;
	}
	map->realmap[j] = NULL;
}

void	check_real_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->realmap[i])
	{
		j = 0;
		while (map->realmap[i][j])
		{
			if (map->realmap[i][j] != 'W' && map->realmap[i][j] != 'E'
				&& map->realmap[i][j] != 'N' && map->realmap[i][j] != 'S'
				&& map->realmap[i][j] != '0' && map->realmap[i][j] != '1'
				&& map->realmap[i][j] != ' ')
				ft_err_mapcontrol("hata mesaji ver programi kapat \n haritada istenmeyen seyler var \n",
					map);
			j++;
		}
		i++;
	}
}

void	check_real_map_counts(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->realmap[i])
	{
		j = 0;
		while (map->realmap[i][j])
		{
			if (map->realmap[i][j] == 'N' || map->realmap[i][j] == 'S'
				|| map->realmap[i][j] == 'E' || map->realmap[i][j] == 'W')
			{
				map->playercount++;
				map->pos_x = j;
				map->pos_y = i;
				map->pov = map->realmap[i][j];
			}
			j++;
		}
		i++;
	}
	if (map->playercount != 1)
	{
		ft_err_mapcontrol("player count fazla veya eksik!\n", map);
	}
}

void	find_hight_real_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->realmap[i])
		i++;
	map->realmap_height = i;
}

void	create_tmp_map(t_map *map)
{
	int	j;

	j = 0;
	map->tmp_map = malloc((map->realmap_height + 1) * sizeof(char *));
	while (map->realmap[j])
	{
		map->tmp_map[j] = ft_strdup(map->realmap[j]);
		j++;
	}
	map->tmp_map[j] = NULL;
}