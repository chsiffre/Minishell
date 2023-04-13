/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:18:45 by chsiffre          #+#    #+#             */
/*   Updated: 2023/04/13 17:02:36 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *ft_pre_split(char *str)
{
    int i;
    int new_size;
    char *copy;
    
    copy = ft_strdup(str);
    if (!copy)
        return (NULL);
    new_size = ft_strlen(str);
    i = -1;
    while (str[++i])
    {
        if (str[i] == '<' || str[i] == '>')
        {
            if (str[i + 1] && str[i + 1] != '<' && str[i + 1] != '>' && str[i + 1] != ' ')
                new_size++;
        }
    }
    str = malloc((new_size + 1) * sizeof(char));
    return (ft_str_replace(str, copy, new_size));
}


char *ft_str_replace(char *str, char *copy, int new_size)
{
    int i;
    int y;
    
    y = 0;
    i = 0;
    while (i < new_size)
    {
        if (copy[i] == '<' || copy[i] == '>')
        {
            str[y++] = copy[i];
            if (copy[i + 1] && copy[i + 1] != '<' && copy[i + 1] != '>' && copy[i + 1] != ' ')
            {
                str[y] = ' ';
                y++;
                if (copy[i + 1])
                    str[y++] = copy[i++ + 1];
            }
        }
        else
            str[y++] = copy[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}