/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz <ercdeniz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:34:36 by ercdeniz          #+#    #+#             */
/*   Updated: 2023/09/19 15:34:37 by ercdeniz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
    char    *str;
    size_t    i;

    if (!s)
        return (NULL);
    i = ft_strlen(s) - start;
    if (len < i)
        i = len;
    if (start > ft_strlen(s) - 1)
        return (ft_strdup(""));
    str = (char *)malloc(sizeof(char) * (i + 1));
    if (!str)
        return (0);
    ft_strlcpy(str, s + start, i + 1);
    return (str);
}
