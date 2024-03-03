#include "map.h"

void	deneme(t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	map->fd_buff = open(map->path, O_RDONLY);
	if (map->fd_buff == -1)
	{
		printf("Error open file\n");
		exit(1);
	}
	map->map_buff = (char **)malloc(sizeof(char *) * (map->mapheight + 2));
	if (!map->map_buff)
		ft_err_mapcontrol("Error: Map buff malloc", map);
	while (1)
	{
		line = get_next_line(map->fd_buff);
		if (!line)
			break ;
		map->map_buff[i] = ft_strdup(line);
		i++;
		free(line);
	}
	map->map_buff[i] = NULL;
	close(map->fd_buff);
}

void	deneme2(t_map *map)
{
	int	i;

	i = 0;
	while (map->map_buff[i])
	{
		map_so_control_buff(map, i);
		map_no_control_buff(map, i);
		map_ea_control_buff(map, i);
		map_we_control_buff(map, i);
		map_f_control_buff(map, i);
		map_c_control_buff(map, i);
		if (map->flagcount_buff == 6 && map->if_flag_buff == 0)
		{
			map->if_flag_buff = 1;
			map->buff_endofflag = i;
			break ;
		}
		i++;
	}
}

void	check_last_line(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map_buff[i] && map->map_buff[i][j])
		i++;
	if (map->map_buff[i - 1])
		while (map->map_buff[i - 1][j] != '\n')
			j++;
	if (map->map_buff[i - 1][j] != '\n')
		return ;
	if (map->map_buff[i - 1][j] != '\n')
		ft_err_mapcontrol("Error: Map wait the newline at lastline", map);
}

void	newline_control2(t_map *map)
{
	int	i;

	i = map->map_start_buff;
	while (map->map_buff[i])
	{
		if (map->map_buff[i][0] == '\n')
			ft_err_mapcontrol("Error: It is newline at map", map);
		i++;
	}
}

void	skip_spaces2(t_map *map, int end)
{
	int	i;

	end++;
	i = 0;
	if (map->map_buff[end] != NULL)
	{
		while (map->map_buff[end])
		{
			i = 0;
			while (map->map_buff[end][i] == ' ')
				i++;
			if (map->map_buff[end][i] == '\n')
				end++;
			else
			{
				map->map_start_buff = end;
				break ;
			}
		}
		if (!map->map_buff[end])
			// mapin end'i nulla geldiği için while bittiyse
			map->map_start_buff = end;
	}
	else
		ft_err_mapcontrol("map doesnt have anything at lastline", map);
}
