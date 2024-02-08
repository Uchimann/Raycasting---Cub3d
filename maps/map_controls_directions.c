#include "map.h"


int map_so_control(t_map *map, int i)
{
     if((strncmp(map->map[i],"SO ",3) == 0) && (map->soflag != 1))
        {
            //burda devamini texture olarak alıp direction->1 2 3 4 diye yön verebiliriz ismail abi kızmaz ise
           // map->sotexture = //map[i]. sinde 4. harften itibarini okuyan ve return eden bir fonksiyon;
            map->sotexturepath = texture_path_handler(map->map[i]);
            printf("texture pathimiz = -> %s \n",map->sotexturepath);
            map->soflag = 1;
            map->flagcount++;
            return 1;
        }
    else if((strncmp(map->map[i], "SO", 2) == 0) && (map->soflag == 1))
        ft_err_mapcontrol(" \n Error! SO dan iki tane var burda programı bitir error mesaji ver",map);
	/*else if(space_control(map,i) == 0)
	{
		printf("error message space veya newline olmali");
		exit(0);
	}*/
}

int map_no_control(t_map *map, int i)
{
    if((strncmp(map->map[i], "NO ", 3) == 0) && (map->noflag != 1))
        {
            //burda devamini texture olarak alıp direction->1 2 3 4 diye yön verebiliriz ismail abi kızmaz ise
           // map->notexture = //map[i]. sinde 4. harften itibarini okuyan ve return eden bir fonksiyon;
            map->notexturepath = texture_path_handler(map->map[i]);
            map->noflag = 1;
            map->flagcount++;
        }
    else if((strncmp(map->map[i], "NO", 2) == 0) && (map->noflag == 1))
        ft_err_mapcontrol(" \n Error! NO dan iki tane var burda programı bitir error mesaji ver",map);
	/*else if(space_control(map,i) == 0)
	{
		printf("error message space veya newline olmali");
		exit(0);
	}*/
}

int map_ea_control(t_map *map, int i)
{
    if((strncmp(map->map[i], "EA ", 3) == 0) && (map->eaflag != 1))
        {
            //burda devamini texture olarak alıp direction->1 2 3 4 diye yön verebiliriz ismail abi kızmaz ise
            //map->notexture = //map[i]. sinde 4. harften itibarini okuyan ve return eden bir fonksiyon;
            map->eatexturepath = texture_path_handler(map->map[i]);
            map->eaflag = 1;
            map->flagcount++;
        }
    else if((strncmp(map->map[i], "EA", 2) == 0) && (map->eaflag == 1))
        ft_err_mapcontrol(" \n Error! EA dan iki tane var burda programı bitir error mesaji ver",map);

}

int map_we_control(t_map *map, int i)
{
    if((strncmp(map->map[i], "WE ", 3) == 0) && (map->weflag != 1))
        {
            //burda devamini texture olarak alıp direction->1 2 3 4 diye yön verebiliriz ismail abi kızmaz ise
            //map->notexture = //map[i]. sinde 4. harften itibarini okuyan ve return eden bir fonksiyon;
            map->wetexturepath = texture_path_handler(map->map[i]);
            map->weflag = 1;
            map->flagcount++;
        }
    else if((strncmp(map->map[i], "WE", 2) == 0) && (map->weflag == 1))
        ft_err_mapcontrol(" \n Error! WE dan iki tane var burda programı bitir error mesaji ver",map);
}