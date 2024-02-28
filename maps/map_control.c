#include "map.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void free_map(t_map *map)
{

    ft_err_mapcontrol("basariyla tamamlandi",map);

}

void mapread(t_map *map)
{
    char *line;
    char *str;
    map->fd = open(map->path, O_RDONLY);
    map->map_line = NULL;
    str = ft_strdup("");
    while(1)
    {
        line = get_next_line(map->fd);
        if(!line)
            break;
        map->map_line = ft_strjoin(str, line);
        free(str);
        free(line);
        str = map->map_line;
    }
    if(!map->map_line)
    {
        printf("Errrrrrrrrror map\n");
        free(str);
        free(map->map_line);
        exit(1);
    }
    close(map->fd);
}

//bu fonksyon leakli en son headerda texturepathleri tutanlar freelenecek


int map_sixthcontrol(t_map *map)
{
	int	i;
    int j;

	i = 0;
	while(map->mapheight > i && map->map[i])
	{
        map_so_control(map,i);
        map_no_control(map,i);
        map_ea_control(map,i);
        map_we_control(map,i);
        map_f_control(map,i);
        map_c_control(map,i);

        if(map->flagcount == 6 && map->if_flag == 0)
        {
            map->if_flag = 1;
            j = i;
        }
        i++;
	}
    
    if(map->flagcount != 6)
        ft_err_mapcontrol("map have not 6 direction programı kapat ", map);

    if(newline_control(map, j) == 0)
        ft_err_mapcontrol("\n direction aralarında newline veya space disinda birsey var burda hata mesaji ver ve programı kapat", map);
    return j;
}

void init_struct(t_map *map)
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

void skip_spaces2(t_map *map, int end)
{
    end++;
    int i;

    i = 0;
    if(map->map_buff[end] != NULL)
    {
        while(map->map_buff[end])
        {
            i = 0;
            while(map->map_buff[end][i] == ' ')
                i++;
            if(map->map_buff[end][i] == '\n')
                end++;
            else 
            {
                map->map_start_buff = end;
                break;
            }
        }
        if(!map->map_buff[end]) // mapin end'i nulla geldiği için while bittiyse
            map->map_start_buff = end;
    }
    else
        ft_err_mapcontrol("mapin son satirinda birsey yok",map);
}

void skip_spaces(t_map *map, int end)
{
    end++;
    int i;

    i = 0;
    if(map->map[end] != NULL)
    {
        while(map->map[end])
        {
            while(map->map[end][i] == ' ' || map->map[end][i] == '\n')
                i++;
            if(map->map[end][i] == '\0')
                end++;
            else 
            {
                map->map_start = end;
                break;
            }
        }
        if(!map->map[end])
            map->map_start = end;
    }
    else
        ft_err_mapcontrol("mapin son satirinda birsey yok",map);
}

void read_real_map(t_map *map)
{
    int i;
    int j;

    i = map->map_start;

    j = 0;
    map->realmap = malloc((map->mapheight - i ) * sizeof(char *) + 1);
    while(map->map[i])
    {
        map->realmap[j] = ft_strdup(map->map[i]);
        i++;
        j++;
    }
    map->realmap[j] = NULL;
}

void create_tmp_map(t_map *map)
{
    int j;

    j = 0;
    map->tmp_map = malloc((map->realmap_height + 1) * sizeof(char *));
    while(map->realmap[j])
    {
        map->tmp_map[j] = ft_strdup(map->realmap[j]);
        j++;
    }
    map->tmp_map[j] = NULL;
}

void check_real_map(t_map *map)
{
    int i;
    int j;

    i = 0;
    while(map->realmap[i])
    {
        j = 0;
        while(map->realmap[i][j])
        {
            if(map->realmap[i][j] != 'W' && map->realmap[i][j] != 'E' && map->realmap[i][j] != 'N'
                && map->realmap[i][j] != 'S' && map->realmap[i][j] != '0' && map->realmap[i][j] != '1'
                && map->realmap[i][j] != ' ')
                    ft_err_mapcontrol("hata mesaji ver programi kapat \n haritada istenmeyen seyler var \n",map);
            j++;
        }
        i++;
    }
}

void check_real_map_counts(t_map *map)
{
    int i;
    int j;

    i = 0;
    while(map->realmap[i])
    {
        j = 0;
        while(map->realmap[i][j])
        {
            if(map->realmap[i][j] == 'N' || map->realmap[i][j] == 'S'
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
    if(map->playercount != 1)
    {
        ft_err_mapcontrol("player count fazla veya eksik, hata ver programi kapat! \n",map);
    }
}

void    path_finder(t_map *map, int y, int x)
{
    if (x < 0 || y < 0 || y >=map->realmap_height || \
        map->tmp_map[y][x] == ' ' || map->tmp_map[y][x] == '\0')
    {
        ft_err_mapcontrol("Hatali map\n",map);
    }

    else if (map->tmp_map[y][x] == '1')
        return ;
    map->tmp_map[y][x] = '1';
    path_finder(map, y, x - 1);
    path_finder(map, y - 1, x);
    path_finder(map, y, x + 1);
    path_finder(map, y + 1, x);
}
void find_hight_real_map(t_map *map)
{
    int i;

    i = 0;
    while(map->realmap[i])
        i++;
    map->realmap_height = i;
}
void deneme(t_map *map)
{
    char *line;
    int i;
    i = 0;
    map->fd_buff = open(map->path, O_RDONLY);
    if (map->fd_buff == -1)
    {
        printf("Error open file\n");
        exit(1);
    }
    map->map_buff = (char **)malloc(sizeof(char *) * (map->mapheight + 2));
    while (1)
    {
        line = get_next_line(map->fd_buff);
        if (!line)
            break;
        map->map_buff[i] = ft_strdup(line);
        i++;
        free(line);
    }
    map->map_buff[i] = NULL;
    close(map->fd_buff);
}

void deneme2(t_map *map)
{
    int i;

    i = 0;

  	while(map->map_buff[i])
	{
        map_so_control_buff(map,i);
        map_no_control_buff(map,i);
        map_ea_control_buff(map,i);
        map_we_control_buff(map,i);
        map_f_control_buff(map,i);
        map_c_control_buff(map,i);

        if(map->flagcount_buff == 6 && map->if_flag_buff == 0)
        {   
            map->if_flag_buff = 1;
            map->buff_endofflag = i;
            break;
        }
        i++;
	}
}


void check_last_line(t_map *map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(map->map_buff[i] && map->map_buff[i][j])
        i++;
    if(map->map_buff[i - 1])
        while(map->map_buff[i - 1][j] != '\n')
            j++;
    if(map->map_buff[i - 1][j] != '\n')
        return ;
    if(map->map_buff[i - 1][j] != '\n')
        ft_err_mapcontrol("Error: Map son satirda bir newline bekler",map);
}

void newline_control2(t_map *map)
{
    int i;
    
    i = map->map_start_buff;
    while(map->map_buff[i])
    {
        if(map->map_buff[i][0] == '\n')
            ft_err_mapcontrol("Error: Map icerisinde newline var",map);
        i++;
    }
}


void map_control(t_map *map,char *name)
{
    int directions_end;

    directions_end = 0;
    check_name(name);
    map->path = name;
    mapread(map);
    map_size(map);
    init_struct(map);
    directions_end = map_sixthcontrol(map);

    skip_spaces(map,directions_end);
    deneme(map);
    deneme2(map);
    //find_buff_map_height(map);
    //check_last_line(map);
    skip_spaces2(map,map->buff_endofflag);
    newline_control2(map);

    read_real_map(map);
    check_real_map(map);
    check_real_map_counts(map); // pos_x ve pos_y belirlendi artık realmapin son kontrolu kaldi
    find_hight_real_map(map);
    create_tmp_map(map);
    printf("pos_y --> %d, pos_x --> %d \n",map->pos_y,map->pos_x);
    //burda real mapin yüksekliğini bul
    path_finder(map,map->pos_y,map->pos_x); // bu fonks sadece oyuncunun hareket edebileceiği yeri kontrol ediyor.
}
