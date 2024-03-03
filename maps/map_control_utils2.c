#include "map.h"

char	*texture_path_handler(char *str)
{
	int		i;
	int		j;
	char	*ret_path;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	j = 0;
	ret_path = malloc((ft_strlen(&str[i]) * sizeof(char)) + 1);
	if (!ret_path)
		return (NULL);
	if (str[i] == '\0')
	{
		free(ret_path);
		return (NULL);
	}
	while (str[i] != '\0')
	{
		ret_path[j] = str[i++];
		j++;
	}
	ret_path[j] = '\0';
	return (ret_path);
}
char	*color_path_handler(char *str)
{
	int		i;
	int		j;
	char	*ret_path;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	j = 0;
	ret_path = malloc((ft_strlen(&str[i]) * sizeof(char)) + 1);
	if (!ret_path)
		return (NULL);
	if (str[i] == '\0')
	{
		free(ret_path);
		return (NULL);
	}
	while (str[i] != '\0')
	{
		ret_path[j] = str[i++];
		j++;
	}
	ret_path[j] = '\0';
	return (ret_path);
}

void	is_digit_color(char *tmp, char **str, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
			{
				free(tmp);
				free_array2d(str);
				ft_err_mapcontrol("colors must be digit ! \n", map);
				exit(1);
			}
			j++;
		}
		i++;
	}
}

int	take_rgb_color(char *str, t_map *map)
{
	char	**tmp;
	int		colorvalue;

	tmp = NULL;
	if (!str)
		ft_err_mapcontrol("color musn't empty\n", map);
	tmp = ft_split(str, ',');
	if (tmp[0] != NULL && tmp[1] != NULL && tmp[2] != NULL)
	{
		if (!(0 <= ft_atoi(tmp[0]) && ft_atoi(tmp[0]) <= 255)
			|| !(0 <= ft_atoi(tmp[1]) && ft_atoi(tmp[1]) <= 255)
			|| !(0 <= ft_atoi(tmp[2]) && ft_atoi(tmp[2]) <= 255))
		{
			free_array2d(tmp);
			free(str);
			ft_err_mapcontrol("Number should beetween the 0-255 !!!\n", map);
		}
	}
	else
		return (free_array2d(tmp), free(str),
			ft_err_mapcontrol("colors not enough! \n", map));
	if (count_comma(str) != 2)
		return (free_array2d(tmp), free(str),
			ft_err_mapcontrol("colors miss or much! \n", map));
	is_digit_color(str, tmp, map);
	colorvalue = (ft_atoi(tmp[0]) << 16) + (ft_atoi(tmp[1]) << 8)
		+ ft_atoi(tmp[2]);
	free_array2d(tmp);
	return (colorvalue);
}
int	count_comma(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}
