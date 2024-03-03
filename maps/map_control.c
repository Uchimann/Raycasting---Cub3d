#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	free_map(t_map *map)
{
	ft_err_mapcontrol("basariyla tamamlandi", map);
}

void	init_struct2(t_map *map)
{
	map->pos_x = 0;
	map->pos_y = 0;
	map->playercount = 0;
	map->ccolor = 0;
	map->fcolor = 0;
	map->realmap_height = 0;
	map->eatexturepath = NULL;
	map->wetexturepath = NULL;
	map->notexturepath = NULL;
	map->sotexturepath = NULL;
	map->realmap = NULL;
	map->tmp_map = NULL;
	map->map_buff = NULL;
}

void	init_struct(t_map *map)
{
	map->cflag = 0;
	map->cflag_buff = 0;
	map->fflag = 0;
	map->fflag_buff = 0;
	map->eaflag = 0;
	map->eaflag_buff = 0;
	map->flagcount = 0;
	map->flagcount_buff = 0;
	map->weflag = 0;
	map->weflag_buff = 0;
	map->noflag = 0;
	map->noflag_buff = 0;
	map->soflag = 0;
	map->soflag_buff = 0;
	map->if_flag = 0;
	map->if_flag_buff = 0;
	map->map_start = 0;
	map->map_start_buff = 0;
	init_struct2(map);
}

void	path_finder(t_map *map, int y, int x)
{
	if (x < 0 || y < 0 || y >= map->realmap_height || map->tmp_map[y][x] == ' '
		|| map->tmp_map[y][x] == '\0')
	{
		ft_err_mapcontrol("Hatali map\n", map);
	}
	else if (map->tmp_map[y][x] == '1')
		return ;
	map->tmp_map[y][x] = '1';
	path_finder(map, y, x - 1);
	path_finder(map, y - 1, x);
	path_finder(map, y, x + 1);
	path_finder(map, y + 1, x);
}

void	map_control(t_map *map, char *name)
{
	int	directions_end;

	directions_end = 0;
	check_name(name);
	map->path = name;
	mapread(map);
	map_size(map);
	init_struct(map);
	directions_end = map_sixthcontrol(map);
	skip_spaces(map, directions_end);
	deneme(map);
	deneme2(map);
	// find_buff_map_height(map);
	// check_last_line(map);
	skip_spaces2(map, map->buff_endofflag);
	newline_control2(map);
	read_real_map(map);
	check_real_map(map);
	check_real_map_counts(map);
	// pos_x ve pos_y belirlendi artık realmapin son kontrolu kaldi
	find_hight_real_map(map);
	create_tmp_map(map);
	printf("pos_y --> %d, pos_x --> %d \n", map->pos_y, map->pos_x);
	// burda real mapin yüksekliğini bul
	path_finder(map, map->pos_y, map->pos_x);
}
