#include "map.h"

void	free_array2d(char **str)
{
	char	**temp;

	temp = str;
	while (temp && *temp)
	{
		free(*temp);
		temp++;
	}
	free(str);
}
