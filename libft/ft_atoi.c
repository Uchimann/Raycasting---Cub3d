/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icelebi <icelebi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:57:09 by icelebi           #+#    #+#             */
/*   Updated: 2024/03/03 17:00:20 by icelebi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	result;

	sign = 1;
	result = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while ((ft_isdigit(str[i]) == 1) && (str[i] != '\0'))
		result = result * 10 + (str[i++] - 48);
	if (result > 18446744073709551)
	{
		if (sign == -1)
			return (0);
		return (-1);
	}
	return (result * sign);
}
