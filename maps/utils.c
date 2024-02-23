#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "map.h"


int ft_err(char *str, t_game *game)
{
    ft_err_mapcontrol(str,game->map);
    if(game->image != NULL)
        free(game->image);
    if(game->NO != NULL)    
        free(game->NO);
    if(game->SO != NULL)
        free(game->SO);
    if(game->WE != NULL)
        free(game->WE);
    if(game->EA != NULL)
        free(game->EA);
}
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
    if(map->map_buff != NULL)
        free_array2d(map->map_buff);
    //if(map->direction != NULL)
      //  free(map->direction);
    if(map->eatexturepath != NULL)
        free(map->eatexturepath);
    if(map->notexturepath!= NULL)
        free(map->notexturepath);
    if(map->sotexturepath != NULL)
        free(map->sotexturepath);
    if(map->wetexturepath != NULL)
        free(map->wetexturepath);
    printf("%s\n",str);
    exit(0);
}