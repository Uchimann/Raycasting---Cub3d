/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control_directions_buff2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icelebi <icelebi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:00:15 by icelebi           #+#    #+#             */
/*   Updated: 2024/03/04 15:25:11 by icelebi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "../libft/libft.h"

int	map_c_control_buff(t_map *map, int i)
{
	if ((ft_strncmp(map->map_buff[i], "C ", 2) == 0) && (map->cflag_buff != 1))
	{
		map->cflag_buff = 1;
		map->flagcount_buff++;
		return (1);
	}
	else
		return (0);
}
