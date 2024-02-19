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
    int fd_buff;

    int realmap_height;

    int playercount;

    int map_start;
    int map_start_buff;
    char *map_line;

    char *sotexturepath;
    char *notexturepath;
    char *eatexturepath;
    char *wetexturepath;

    char **realmap;
    char **tmp_map;
    char **map_buff;
    int pos_x;
    int pos_y;

    int fcolor;
    int ccolor;
    int noflag;
    int noflag_buff;
    int weflag;
    int weflag_buff;
    int eaflag;
    int eaflag_buff;
    int soflag;
    int soflag_buff;
    int cflag;
    int cflag_buff;
    int fflag;
    int fflag_buff;
    int flagcount;
    int flagcount_buff;
    int if_flag_buff;
    int if_flag;
    int buff_endofflag;
} t_map;

void map_control(t_map *map,char *name);
int map_so_control(t_map *map, int i);
int map_so_control_buff(t_map *map, int i);
int map_no_control(t_map *map, int i);
int map_no_control_buff(t_map *map, int i);
int map_ea_control(t_map *map, int i);
int map_ea_control_buff(t_map *map, int i);
int map_we_control(t_map *map, int i);
int map_we_control_buff(t_map *map, int i);
int map_f_control(t_map *map, int i);
int map_f_control_buff(t_map *map, int i);
int map_c_control(t_map *map, int i);
int map_c_control_buff(t_map *map, int i);
//char **splitter(char *s,char c);
//void checkformat(char *tmp);
char	*get_next_line(int fd);
void	*myfree(void **str);
char *texture_path_handler(char *str);
void check_name(char *name);
int newline_control(t_map *map, int i);
int space_control(t_map *map, int i);
char *color_path_handler(char *str);
int check_line_dir(char *map);
int map_sixthcontrol(t_map *map);
void    mapread(t_map *map);
int     ft_err_mapcontrol(char *str, t_map *map);
void free_map(t_map *map);
void map_size(t_map *map);
int take_rgb_color(char *str, t_map *map);
void is_digit_color(char **str,t_map *map);
void free_array2d(char **str);
void create_tmp_map(t_map *map);
void deneme(t_map *map);
void deneme2(t_map *map);

#endif