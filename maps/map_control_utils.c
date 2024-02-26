#include "map.h"

char *texture_path_handler(char *str)
{
    int i = 0;
    int j;
    char *ret_path;
   // int count = 0;

    while(str[i] && str[i] != ' ')
        i++;
    while(str[i] && str[i] == ' ')
        i++;
    
    
   // ret_path = malloc(100 * sizeof(char *));
    j = 0;
    //i = 3;

    ret_path = malloc((ft_strlen(&str[i]) * sizeof(char)) + 1);
    //ret_path = ft_substr(str,i,ft_strlen(str));
   // printf("ret_pathimiz --> %s ",ret_path);
    if(str[i] == '\0')
    {
        free(ret_path);
        return NULL;
    }
    while(str[i] != '\0')
    {
        ret_path[j] = str[i];
        i++;
        j++;
    }
    ret_path[j] = '\0';
    return ret_path;
}
char *color_path_handler(char *str)
{
    int i = 0;
    int j;
    char *ret_path;
  //  int count = 0;

    while(str[i] && str[i] != ' ')
        i++;
    while(str[i] && str[i] == ' ')
        i++;

    //ret_path = malloc(100 * sizeof(char));
    j = 0;
    ret_path = malloc((ft_strlen(&str[i]) * sizeof(char)) + 1);
    if(str[i] == '\0')
    {
        free(ret_path);
        return NULL;
    }
    while(str[i] != '\0')
    {
        ret_path[j] = str[i];
        i++;
        j++;
    }
    ret_path[j] = '\0';
    return ret_path;
}

void is_digit_color(char *tmp,char **str,t_map *map)
{
    int i;
    int j;

    i = 0;
    while(str[i])
    {
        j = 0;
        while(str[i][j])
        {
            if(!ft_isdigit(str[i][j]))
            {   
                free(tmp);
                free_array2d(str);
                ft_err_mapcontrol("renkler sadece sayi olmali ! \n",map);
                exit(1);
            }
            j++;
        }
        i++;
    }
}


void free_array2d(char **str)
{
    int i;

    i = 0;

    while(str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

/*
void free_array2d(char **str)
{
    char **temp = str; // Geçici bir pointer oluştur ve str'nin adresini atayarak başla

    // temp NULL değilse ve temp'in gösterdiği adres NULL değilse
    while (temp && *temp)
    {
        free(*temp); // Her bir string için belleği serbest bırak
        temp++;      // Sonraki stringe geçmek için temp'i artır
    }

    free(str); // Dizinin kendisini serbest bırak
}
*/
int take_rgb_color(char *str, t_map *map)
{
    char **tmp;
    int colorvalue;
    tmp = NULL;

    if(!str)
        ft_err_mapcontrol("renk alani bos birakilamaz\n",map);
    //printf("%s\n",str);
    tmp = ft_split(str,',');
    if(tmp[0] != NULL && tmp[1] != NULL && tmp[2] != NULL)
    {
        if(!(0 <= ft_atoi(tmp[0]) && ft_atoi(tmp[0]) <= 255)
            || !(0 <= ft_atoi(tmp[1]) && ft_atoi(tmp[1]) <= 255)
            || !(0 <= ft_atoi(tmp[2]) && ft_atoi(tmp[2]) <= 255))
        {
            free_array2d(tmp);
            free(str);
            //free(tmp);
            ft_err_mapcontrol("Girilen sayilar 0-255 arasinda değil !!!\n",map); // ft_err_msg;
        }
    }
    else
        return(free_array2d(tmp),free(str),ft_err_mapcontrol("renk kodlarinda eksik renk var! \n",map));
    if(count_comma(str) != 2)
        return(free_array2d(tmp),free(str),ft_err_mapcontrol("renk kodlarinda eksik veya fazla renk var! \n",map));
    is_digit_color(str,tmp,map);
    colorvalue = (ft_atoi(tmp[0]) << 16) + (ft_atoi(tmp[1]) << 8) + ft_atoi(tmp[2]);
    free_array2d(tmp);
    return colorvalue;
}
int count_comma(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while(str[i])
    {
        if(str[i] == ',')
            count++;
        i++;
    }
    return count;
}
void map_size(t_map *map)
{

    map->mapheight = 0;
    map->map = ft_split(map->map_line, '\n');

    ///////////////////////////////////7
    //printf("mapin mapinin 4.sü --> \n ******** \n %s *********\n",map->map[6]);
    //printf("line'ımız -> %s",map->map_line);
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
	//char current_char;
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
        else if(c == '\n') // boşluk yasak ise burayu düzelt. // veya bosluk ise
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
   // char *str;

    
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
    char *str;

    str = NULL;
    if((strncmp(map->map[i], "F ", 2) == 0) && (map->fflag != 1))
        {
            //burda devamini texture olarak alıp direction->1 2 3 4 diye yön verebiliriz ismail abi kızmaz ise
            //map->notexture = //map[i]. sinde 4. harften itibarini okuyan ve return eden bir fonksiyon;
            //printf("f deki mapin isi -> %s\n",map->map[i]);
            str = color_path_handler(map->map[i]);
            printf("fcolor = %s\n",str);
            map->fcolor = take_rgb_color(str,map);
            map->fflag = 1;
            map->flagcount++;
            free(str);
            return 1;
        }
    else if((strncmp(map->map[i], "F", 1) == 0) && (map->fflag == 1))
    {
        free(str);
        ft_err_mapcontrol(" \n Error! F den iki tane var burda programı bitir error mesaji ver",map);
    }
    return 0;
}

int map_c_control(t_map *map, int i)
{
    char *str;

    str = NULL;
    if((strncmp(map->map[i], "C ", 2) == 0) && (map->cflag != 1))
        {
            //burda devamini texture olarak alıp direction->1 2 3 4 diye yön verebiliriz ismail abi kızmaz ise
            //map->notexture = //map[i]. sinde 4. harften itibarini okuyan ve return eden bir fonksiyon;
            printf("mapin isi -> %s",map->map[i]);
            str = color_path_handler(map->map[i]);
            printf("buradaki str -> %s\n",str);
            map->ccolor = take_rgb_color(str,map);
            map->cflag = 1;
            map->flagcount++;
            free(str);
            return 1;
        }
    else if((strncmp(map->map[i], "C", 1) == 0) && (map->cflag == 1))
    {
        free(str);
        ft_err_mapcontrol(" \n Error! C den iki tane var burda programı bitir error mesaji ver",map);
    }
    //free(str);
    return 0;
}