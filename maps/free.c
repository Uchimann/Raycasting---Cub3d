/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icelebi <icelebi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:56:44 by icelebi           #+#    #+#             */
/*   Updated: 2024/03/04 15:08:12 by icelebi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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
