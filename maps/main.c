#include <stdio.h>
#include "map.h"

int main(int ac, char **av)
{
    if(ac != 2)
    {
        printf("Arguments Error\n");
        exit(0);
    }
    t_map map;
    map_control(&map,av[1]);
}