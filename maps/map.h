#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"
#include "map.h"
#include <stdbool.h>
#include "../minilibx-linux/mlx.h"
#include <math.h>

//# define SW 640
//# define SH 480
//# define  texWidth 64
//# define  texHeight 64
# define WIDTH 800
# define HEIGHT 600
# define TEXWIDTH 64
# define TEXHEIGHT 64

typedef struct s_image
{
	void *image;
	int  *addr;
	int  number;
} t_image;

typedef struct s_map
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

typedef struct s_game
{
	void   *mlx;
	void   *mlxWin;
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
    double cameraX;
    double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	double wallX;
    double rayDirX;
    double rayDirY;
    double step;
    double texPos;
    int    color;
	int    mapX;
	int	   mapY;
	int	   stepX;
	int	   stepY;
	int	   hit;
	int	   side; // side sıfır ise x demektir. side 1 ise y demektir.
	int    lineH;
	//int    floor;
    //int    ceiling;
    int    drawStart;
    int    drawEnd;
    int    texX;
    int    texY;
    int    texH;
    int    texW;
    bool   w;
    bool   s;
    bool   a;
    bool   d;
    bool   left;
    bool   right;
    float  speed;
    float  rspeed;
    t_image *NO;
	t_image *SO;
	t_image *WE;
	t_image *EA;
    t_image *image;
    t_map *map;
   // char **map;
} t_game;

int ft_err(char *str, t_game *game);
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
void is_digit_color(char *tmp,char **str,t_map *map);
void free_array2d(char **str);
void create_tmp_map(t_map *map);
void deneme(t_map *map);
void deneme2(t_map *map);
int count_comma(char *str);

#endif