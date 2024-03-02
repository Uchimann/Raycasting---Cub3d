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

