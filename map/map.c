#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
// MAP CHECK

void mapsize(t_map *map)
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
}
void mapread(t_map *map)
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
        map->map[i] = (char *)malloc(sizeof(char) * map->mapwidth);
        if(area == NULL || area[0] == '\0')
        {
            free(area);
            break;
        }
        while(j < map->mapwidth)
        {
            map->map[i][j] = area[j];
            j++;
        }
        map->map[i][j] = '\0';
        i++;
        printf("%s",area);
        free(area);
    }
}

void mapcontrol(t_map *map)
{
    int x;
    int y;
    x = 0;
    y = 0;
    
    //mapın başladığı yeri bul
    while(x < map->mapwidth)
    {
        if(map->map[0][x++] != '1')
        {
            
            printf("\nMap is not closed\n");
            exit(1);
        }
    }
    while(y < map->mapheight)
    {
        if(map->map[y++][0] != '1')
        {
            printf("\nMap is not closed\n");
            exit(1);
        }
    }
    x = 0;
    while(x < map->mapwidth)
    {
        if(map->map[map->mapheight - 1][x++] != '1')
        {
            printf("\nMap is not closed\n");
            exit(1);
        }
    }

}


void checkformat(char *tmp)
{
    int arg_len;

    arg_len = strlen(tmp);
    if(tmp[arg_len - 1] != 'b' || tmp[arg_len - 2] != 'u' || tmp[arg_len - 3] != 'c' || tmp[arg_len - 4] != '.')
    {
        printf("Wrong file format\n");
        exit(1);
    }
    printf("File format is correct\n");
    printf("%s\n",tmp);
}
int main(int argc,char **argv)
{
    t_map map;
    if(argc != 2)
    {
        printf("Wrong number of arguments\n");
        return 1;
    }
    checkformat(argv[1]);
    map.path = argv[1];
    mapsize(&map);
    printf("mapheight = %d\n",map.mapheight);
    printf("mapwidth = %d\n",map.mapwidth);
    mapread(&map);
    mapcontrol(&map);
    //printmap(&map);

}