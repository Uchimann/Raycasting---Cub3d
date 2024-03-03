#include "map.h"

int	space_control(t_map *map, int i)
{
	int	j;

	// char current_char;
	j = 0;
	while ((map->map[i][j]) != '\0')
	{
		if (!(map->map[i][j] == ' ' || map->map[i][j] == '\n'))
		{
			printf("eror message");
			return (0);
		}
		j++;
	}
	return (1);
}

// satir icinde istenmeyen disinda bisey varsa 0 return (eder);
int	check_line_dir(char *map)
{
	int		i;
	char	c;

	i = 0;
	while (map[i])
	{
		c = map[i];
		if ((strncmp(map, "SO ", 3) == 0))
			return (1);
		else if ((strncmp(map, "NO ", 3) == 0))
			return (1);
		else if ((strncmp(map, "EA ", 3) == 0))
			return (1);
		else if ((strncmp(map, "WE ", 3) == 0))
			return (1);
		else if ((strncmp(map, "F ", 2) == 0))
			return (1);
		else if ((strncmp(map, "C ", 2) == 0))
			return (1);
		else if (c == '\n') // boşluk yasak ise burayu düzelt.
			// veya bosluk ise
			i++;
		else if (c == '\0')
			return (1);
		else
			return (0);
	}
	return (1);
}

int	newline_control(t_map *map, int i)
		// satir icinde istenmeyenler varsa return (0 doner);
{
	int j;
	// char *str;

	j = 0;
	while (j < i)
		// 13. satıra kadar while devam eder (flagcount un 6 oldugu satır sayisina kadar)
	{
		if (check_line_dir(map->map[j]) == 0)
			return (0);
		j++;
	}
	return (1);
}

int	map_f_control(t_map *map, int i)
{
	char	*str;

	str = NULL;
	if ((strncmp(map->map[i], "F ", 2) == 0) && (map->fflag != 1))
	{
		// burda devamini texture olarak alıp direction->1 2 3 4 diye yön verebiliriz ismail abi kızmaz ise
		// map->notexture =
			//map[i]. sinde 4. harften itibarini okuyan ve return (eden bir fonksiyon);
		// printf("f deki mapin isi -> %s\n",map->map[i]);
		str = color_path_handler(map->map[i]);
		printf("fcolor = %s\n", str);
		map->fcolor = take_rgb_color(str, map);
		map->fflag = 1;
		map->flagcount++;
		free(str);
		return 1;
	}
	else if ((strncmp(map->map[i], "F", 1) == 0) && (map->fflag == 1))
	{
		free(str);
		ft_err_mapcontrol(" \n Error! F den iki tane var burda programı bitir error mesaji ver",
			map);
	}
	return 0;
}

int	map_c_control(t_map *map, int i)
{
	char *str;

	str = NULL;
	if ((strncmp(map->map[i], "C ", 2) == 0) && (map->cflag != 1))
	{
		// burda devamini texture olarak alıp direction->1 2 3 4 diye yön verebiliriz ismail abi kızmaz ise
		// map->notexture =
			//map[i]. sinde 4. harften itibarini okuyan ve return eden bir fonksiyon;
		printf("mapin isi -> %s", map->map[i]);
		str = color_path_handler(map->map[i]);
		printf("buradaki str -> %s\n", str);
		map->ccolor = take_rgb_color(str, map);
		map->cflag = 1;
		map->flagcount++;
		free(str);
		return 1;
	}
	else if ((strncmp(map->map[i], "C", 1) == 0) && (map->cflag == 1))
	{
		free(str);
		ft_err_mapcontrol(" \n Error! C den iki tane var burda programı bitir error mesaji ver",
			map);
	}
	// free(str);
	return 0;
}