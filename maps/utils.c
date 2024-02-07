#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "map.h"

int ft_err_mapcontrol(char *str, t_map *map)
{
    free(map->eatexturepath);
    free(map->notexturepath);
    free(map->sotexturepath);
    free(map->wetexturepath);
    printf("%s\n",str);
    exit(0);
}