#include "map.h"

void	check_name(char *name)
{
	int	i;

	i = strlen(name);
	if (name[i - 1] != 'b' || name[i - 2] != 'u' || name[i - 3] != 'c' || name[i
		- 4] != '.')
	{
		printf("Error\n map file must be .cub\n");
		exit(0);
	}
}

void	mapread(t_map *map)
{
	char	*line;
	char	*str;

	map->fd = open(map->path, O_RDONLY);
	map->map_line = NULL;
	str = ft_strdup("");
	while (1)
	{
		line = get_next_line(map->fd);
		if (!line)
			break ;
		map->map_line = ft_strjoin(str, line);
		free(str);
		free(line);
		str = map->map_line;
	}
	if (!map->map_line)
	{
		printf("Errrrrrrrrror map\n");
		free(str);
		free(map->map_line);
		exit(1);
	}
	close(map->fd);
}

void	map_size(t_map *map)
{
	int	i;

	map->mapheight = 0;
	map->map = ft_split(map->map_line, '\n');
	if (!map->map)
	{
		printf("Error map\n");
		free_map(map);
		exit(1);
	}
	i = 0;
	while (map->map_line[i])
	{
		if (map->map_line[i] == '\n')
			map->mapheight++;
		i++;
	}
	printf("map_height = %d\n", map->mapheight);
}

int	map_sixthcontrol(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->mapheight > i && map->map[i])
	{
		map_so_control(map, i);
		map_no_control(map, i);
		map_ea_control(map, i);
		map_we_control(map, i);
		map_f_control(map, i);
		map_c_control(map, i);
		if (map->flagcount == 6 && map->if_flag == 0)
		{
			map->if_flag = 1;
			j = i;
		}
		i++;
	}
	if (map->flagcount != 6)
		ft_err_mapcontrol("map have not 6 direction\n", map);
	if (newline_control(map, j) == 0)
		ft_err_mapcontrol("\n direction partition error", map);
	return (j);
}

void	skip_spaces(t_map *map, int end)
{
	int	i;

	end++;
	i = 0;
	if (map->map[end] != NULL)
	{
		while (map->map[end])
		{
			while (map->map[end][i] == ' ' || map->map[end][i] == '\n')
				i++;
			if (map->map[end][i] == '\0')
				end++;
			else
			{
				map->map_start = end;
				break ;
			}
		}
		if (!map->map[end])
			map->map_start = end;
	}
	else
		ft_err_mapcontrol("map not have anything at lastline", map);
}
