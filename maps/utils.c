#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "map.h"

int ft_err_mapcontrol(char *str, t_map *map)
{   
    if(map->map_line != NULL)
        free(map->map_line);
    if(map->tmp_map != NULL)
        free_array2d(map->tmp_map);
    if(map->realmap != NULL)
        free_array2d(map->realmap);
    if(map->map != NULL)
        free_array2d(map->map);
    //if(map->direction != NULL)
      //  free(map->direction);
    if(map->eatexturepath != NULL)
        free(map->eatexturepath);
    if(map->notexturepath != NULL)
        free(map->notexturepath);
    if(map->sotexturepath != NULL)
        free(map->sotexturepath);
    if(map->wetexturepath != NULL)
        free(map->wetexturepath);
    printf("%s\n",str);
    exit(0);
}