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

void check_name(char *name)
{
    int i;

    i = strlen(name);

    if(name[i - 1] != 'b' || name[i - 2] != 'u' || name[i - 3] != 'c' || name[i - 4] != '.')
    {
        printf("Error\n map file must be .cub\n");
        exit(0);
    }
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


void map_size(t_map *map)
{
    map->map = ft_split(map->map_line, '\n');
    if(!map->map)
    {
        printf("Error map\n");
        free_map(map);
        exit(1);
    }
    int i = 0;
    while(map->map_line[i])
    {
        if(map->map_line[i] == '\n')
            map->mapheight++;
        i++;
    }
    printf("map_height = %d\n", map->mapheight);
}




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
char *texture_path_handler(char *str)
{
    int i;
    int j;
    char *ret_path;

    ret_path = malloc(100 * sizeof(char *));
    j = 0;
    i = 3;

    while(str[i])
    {
        ret_path[j] = str[i];
        i++;
        j++;
    }
    return ret_path;
}

int space_control(t_map *map, int i)
{
	char current_char;
    int j;

	j = 0;
    while ((map->map[i][j]) != '\0')
	{
        if (!(map->map[i][j] == ' ' || map->map[i][j] == '\n'))
		{
            printf("eror message");
			return 0;
        }
        j++;
    }

    return 1;
}


 // satir icinde istenmeyen disinda bisey varsa 0 return eder;
int check_line_dir(char *map)
{
    int i;
    char c;

    i = 0;

    while(map[i])
    {
        c = map[i];
        if((strncmp(map,"SO ",3) == 0))
            return 1;
        else if((strncmp(map,"NO ",3) == 0))
            return 1;
        else if((strncmp(map,"EA ",3) == 0))
            return 1;
        else if((strncmp(map,"WE ",3) == 0))
            return 1;
        else if((strncmp(map,"F ",2) == 0))
            return 1;
        else if((strncmp(map,"C ",2) == 0))
            return 1;
        else if(c == ' ' || c == '\n')
            i++;
        else if (c == '\0')
            return 1;
        else 
            return 0;
    }
    return 1;
}

int newline_control(t_map *map, int i) // satir icinde istenmeyenler varsa return 0 doner;
{
	int j;
    char *str;

    
	j = 0;
	while(j < i) // 13. satıra kadar while devam eder (flagcount un 6 oldugu satır sayisina kadar)
	{
        if(check_line_dir(map->map[j]) == 0)
            return 0;
        j++;
	}
    return 1;
}

int map_so_control(t_map *map, int i)
{
     if((strncmp(map->map[i],"SO ",3) == 0) && (map->soflag != 1))
        {
            //burda devamini texture olarak alıp direction->1 2 3 4 diye yön verebiliriz ismail abi kızmaz ise
           // map->sotexture = //map[i]. sinde 4. harften itibarini okuyan ve return eden bir fonksiyon;
            map->sotexturepath = texture_path_handler(map->map[i]);
            printf("texture pathimiz = -> %s \n",map->sotexturepath);
            map->soflag = 1;
            map->flagcount++;
            return 1;
        }
    else if((strncmp(map->map[i], "SO", 2) == 0) && (map->soflag == 1))
        ft_err_mapcontrol(" \n Error! SO dan iki tane var burda programı bitir error mesaji ver",map);
	/*else if(space_control(map,i) == 0)
	{
		printf("error message space veya newline olmali");
		exit(0);
	}*/
}

int map_no_control(t_map *map, int i)
{
    if((strncmp(map->map[i], "NO ", 3) == 0) && (map->noflag != 1))
        {
            //burda devamini texture olarak alıp direction->1 2 3 4 diye yön verebiliriz ismail abi kızmaz ise
           // map->notexture = //map[i]. sinde 4. harften itibarini okuyan ve return eden bir fonksiyon;
            map->notexturepath = texture_path_handler(map->map[i]);
            map->noflag = 1;
            map->flagcount++;
        }
    else if((strncmp(map->map[i], "NO", 2) == 0) && (map->noflag == 1))
        ft_err_mapcontrol(" \n Error! NO dan iki tane var burda programı bitir error mesaji ver",map);
	/*else if(space_control(map,i) == 0)
	{
		printf("error message space veya newline olmali");
		exit(0);
	}*/
}

int map_ea_control(t_map *map, int i)
{
    if((strncmp(map->map[i], "EA ", 3) == 0) && (map->eaflag != 1))
        {
            //burda devamini texture olarak alıp direction->1 2 3 4 diye yön verebiliriz ismail abi kızmaz ise
            //map->notexture = //map[i]. sinde 4. harften itibarini okuyan ve return eden bir fonksiyon;
            map->eatexturepath = texture_path_handler(map->map[i]);
            map->eaflag = 1;
            map->flagcount++;
        }
    else if((strncmp(map->map[i], "EA", 2) == 0) && (map->eaflag == 1))
        ft_err_mapcontrol(" \n Error! EA dan iki tane var burda programı bitir error mesaji ver",map);

}

int map_we_control(t_map *map, int i)
{
    if((strncmp(map->map[i], "WE ", 3) == 0) && (map->weflag != 1))
        {
            //burda devamini texture olarak alıp direction->1 2 3 4 diye yön verebiliriz ismail abi kızmaz ise
            //map->notexture = //map[i]. sinde 4. harften itibarini okuyan ve return eden bir fonksiyon;
            map->wetexturepath = texture_path_handler(map->map[i]);
            map->weflag = 1;
            map->flagcount++;
        }
    else if((strncmp(map->map[i], "WE", 2) == 0) && (map->weflag == 1))
        ft_err_mapcontrol(" \n Error! WE dan iki tane var burda programı bitir error mesaji ver",map);
}

int map_f_control(t_map *map, int i)
{
    if((strncmp(map->map[i], "F ", 2) == 0) && (map->fflag != 1))
        {
            //burda devamini texture olarak alıp direction->1 2 3 4 diye yön verebiliriz ismail abi kızmaz ise
            //map->notexture = //map[i]. sinde 4. harften itibarini okuyan ve return eden bir fonksiyon;
            map->fflag = 1;
            map->flagcount++;
        }
    else if((strncmp(map->map[i], "F", 1) == 0) && (map->fflag == 1))
        ft_err_mapcontrol(" \n Error! F den iki tane var burda programı bitir error mesaji ver",map);
}

int map_c_control(t_map *map, int i)
{
    if((strncmp(map->map[i], "C ", 2) == 0) && (map->cflag != 1))
        {
            //burda devamini texture olarak alıp direction->1 2 3 4 diye yön verebiliriz ismail abi kızmaz ise
            //map->notexture = //map[i]. sinde 4. harften itibarini okuyan ve return eden bir fonksiyon;
            map->cflag = 1;
            map->flagcount++;
        }
    else if((strncmp(map->map[i], "C", 1) == 0) && (map->cflag == 1))
        ft_err_mapcontrol(" \n Error! C den iki tane var burda programı bitir error mesaji ver",map);
}

int map_sixthcontrol(t_map *map)
{
	int	i;
    int j;
	char *tmp;

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
    
    printf(" \n %d mapin flag countudur\n", map->flagcount);
    if(map->flagcount != 6)
        ft_err_mapcontrol("map have not 6 direction programı kapat ",map);

	if(newline_control(map,j) == 0)
    {
        ft_err_mapcontrol("\n direction aralarında newline veya space disinda birsey var burda hata mesaji ver ve programı kapat",map);
        free_map(map);
    }

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
    map->eatexturepath = NULL;
    map->wetexturepath = NULL;
    map->notexturepath = NULL;
    map->sotexturepath = NULL;
}

void map_control(t_map *map,char *name)
{
    int directions_end;
    check_name(name);
    map->path = name;
    //check_sixth(map);
    mapread(map);
    map_size(map);
    //map in icindeki mapte ilk 6 'SO' 'NO' 'EA' 'WE' 'F' veya 'C' olmalı bunun kontrolü yapılcak
    init_struct(map);
    directions_end = map_sixthcontrol(map);
    // simdi burda directions endden itibaren oku ve sadece harita veya bosluklu satırlar veya newline olmalı


}
