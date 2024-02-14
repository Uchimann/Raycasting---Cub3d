#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"
#include "map.h"

typedef struct map
{
    char **map;
    int mapwidth;
    int mapheight;
    char *path;
    char *direction;
    int fd;

    int playercount;

    int map_start;
    char *map_line;

    char *sotexturepath;
    char *notexturepath;
    char *eatexturepath;
    char *wetexturepath;

    char **realmap;
    

    int pos_x;
    int pos_y;

    int noflag;
    int weflag;
    int eaflag;
    int soflag;
    int cflag;
    int fflag;
    int flagcount;
    int if_flag;
} t_map;

void map_control(t_map *map,char *name);
int map_so_control(t_map *map, int i);
int map_no_control(t_map *map, int i);
int map_ea_control(t_map *map, int i);
int map_we_control(t_map *map, int i);
int map_f_control(t_map *map, int i);
int map_c_control(t_map *map, int i);
//char **splitter(char *s,char c);
//void checkformat(char *tmp);
char	*get_next_line(int fd);
void	*myfree(void **str);
char *texture_path_handler(char *str);
void check_name(char *name);
int newline_control(t_map *map, int i);
int space_control(t_map *map, int i);
char *texture_path_handler(char *str);
int check_line_dir(char *map);
int map_sixthcontrol(t_map *map);
void    mapread(t_map *map);
int     ft_err_mapcontrol(char *str, t_map *map);
void free_map(t_map *map);
void map_size(t_map *map);

#endif