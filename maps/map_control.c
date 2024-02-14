#include "map.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void free_map(t_map *map)
{
    int i;

    i = 0;
    while(map->map[i] != NULL)
    {
        free(map->map[i]);
        i++;
    }
    free(map->map);
    free(map->map_line);
    free(map->sotexturepath);
    free(map->notexturepath);
    free(map->eatexturepath);
    free(map->wetexturepath);


}



/*void mapsize(t_map *map)
{
    int x;
    int y;
    int fd;
    char *line;
    y = 0;
    fd = open(map->path,O_RDONLY);
    line = get_next_line(fd);
    x = strlen(line);
    while(1)
    {
        free(line);
        y++;
        line = get_next_line(fd);
        if(line[0] == '\0')
            break;
    }
    map->mapheight = y;
    map->mapwidth = x;
    //printf("mapheight = %d\n",map->mapheight);
    //printf("mapwidth = %d\n",map->mapwidth);
    close(fd);
}*/




/*void mapread(t_map *map)
{
    int fd;
    int i;
    int j;

    i = 0;
    j = 0;
    char *area;

    fd = open(map->path,O_RDONLY);
    map->map = (char **)malloc(sizeof(char *) * map->mapheight);
    while(i < map->mapheight)
    {
        j = 0;
        area = get_next_line(fd);
        map->map[i] = (char *)malloc(sizeof(char) * strlen(area));
        if(area == NULL || area[0] == '\0')
        {
            free(area);
            break;
        }
        while(j < strlen(area))
        {
            map->map[i][j] = area[j];
            j++;
        }
        map->map[i][j] = '\0';
        i++;
        printf("%s",area);
        free(area);
    }
}*/


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
        printf("Error map\n");
        free_map(map);
        exit(1);
    }
    //check_character(map);
    //free(str);
    close(map->fd);
}

//bu fonksyon leakli en son headerda texturepathleri tutanlar freelenecek


int map_sixthcontrol(t_map *map)
{
	int	i;
    int j;
	char *tmp;

	i = 0;
	while(map->mapheight > i && map->map[i])
	{
        //printf("\n\n mapin isini yazıyoruz %s \n\n",map->map[i]);
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
            printf("---------------- = %d \n",i);
        }
        i++;
	}
    
    printf(" \n %d mapin flag countudur\n", map->flagcount);
    if(map->flagcount != 6)
        ft_err_mapcontrol("map have not 6 direction programı kapat ",map);

	if(newline_control(map,j) == 0)
    {
        ft_err_mapcontrol("\n direction aralarında newline veya space disinda birsey var burda hata mesaji ver ve programı kapat",map);
        free_map(map);
    }
    printf("j nin degeri 14 olmali %d \n",j);
    return j;
}

void init_struct(t_map *map)
{
    map->cflag = 0;
    map->eaflag = 0;
    map->flagcount = 0;
    map->weflag = 0;
    map->noflag = 0;
    map->soflag = 0;
    map->if_flag = 0;
    map->map_start = 0;
    map->pos_x = 0;
    map->pos_y = 0;
    map->playercount = 0;
    map->eatexturepath = NULL;
    map->wetexturepath = NULL;
    map->notexturepath = NULL;
    map->sotexturepath = NULL;
    map->realmap = NULL;
}


void skip_spaces(t_map *map, int end)
{
    //printf("\n%s\n",map->map[end]);
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
        if(!map->map[end]) // mapin end'i nulla geldiği için while bittiyse
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
        //printf("\n realmapin i si-> %s \n",map->realmap[j]);
        i++;
        j++;
    }
    map->realmap[j] = NULL;
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
                {
                    printf("hata mesaji ver programi kapat \n haritada istenmeyen seyler var \n");
                    exit (0);
                }
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
            }
            j++;
        }
        i++;
    }
    if(map->playercount != 1)
    {
        printf("player count fazla hata ver programi kapat! \n");
        exit (0);
    }
}

void map_control(t_map *map,char *name)
{
    int directions_end;

    directions_end = 0;
    check_name(name);
    map->path = name;
    //check_sixth(map);
    mapread(map);
    map_size(map); 
    //map in icindeki mapte ilk 6 'SO' 'NO' 'EA' 'WE' 'F' veya 'C' olmalı bunun kontrolü yapılcak
    init_struct(map);
    directions_end = map_sixthcontrol(map);
    // simdi burda directions endden itibaren oku ve sadece harita veya bosluklu satırlar veya newline olmalı
    skip_spaces(map,directions_end);
    printf("mapin startı asagiki satırdir \n %s \n *******************\n",map->map[map->map_start]);
    printf("directions_end = %d \n",directions_end);
    printf("mapin startı = %d \n",map->map_start);
    read_real_map(map);
    check_real_map(map);
    check_real_map_counts(map); // pos_x ve pos_y belirlendi artık realmapin son kontrolu kaldi


}
