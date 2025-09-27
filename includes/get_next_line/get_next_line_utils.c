/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:22:45 by haloztur          #+#    #+#             */
/*   Updated: 2024/12/22 12:49:34 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t  ft_strlen(const char *s)
{
    size_t i = 0;

    while (s[i] != '\0')
        i++;
    return (i);
}

char   *ft_strjoin(const char *s1, const char *s2)
{
    char    *str;
    size_t  i = 0;
    size_t  j = 0;

    if (!s1 || !s2)
        return (NULL);
    str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (!str)
        return (NULL);
    while (s1[i] != '\0')
        str[i] = s1[i];
    while (s2[j])
        str[i++] = s2[j++];
    str[i] = '\0';
    return (str);
}

char   *ft_strchr(const char *s, int c)
{
    int i;

    if (!s)
        return (0);
    i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == (char)c)
            return ((char *)(s + i));
        i++;
    }
    return (NULL);
}
