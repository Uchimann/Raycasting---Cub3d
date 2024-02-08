#include "map.h"

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

void map_size(t_map *map)
{
    map->mapheight = 0;
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
};
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