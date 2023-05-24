/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:18:45 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/24 13:13:27 by charles          ###   ########.fr       */
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
            if (str[i - 1] && str[i - 1] != ' ')
                new_size++; 
        }
        if (str[i] && str[i] == '|' && str[i - 1] != ' ')
            new_size++;
        if (str[i] && str[i] == '|' && str[i + 1] && str[i + 1] != ' ')
            new_size++;
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
    
    if (check_pipe(copy) == 0)
        return (NULL);
    while (i < new_size)
    {
        if (copy[i] == '<' || copy[i] == '>')
        {
            if (copy[i - 1] && copy[i - 1] != ' ' && copy[i - 1] != '<' && copy[i - 1] != '>')
            {
                str[y++] = ' ';
                if (copy[i])
                    str[y++] = copy[i];
            }
            else 
                str[y++] = copy[i];
            if (copy[i + 1] && copy[i + 1] != '<' && copy[i + 1] != '>' && copy[i + 1] != ' ')
            {
                str[y] = ' ';
                y++;
                if (copy[i + 1])
                    str[y++] = copy[i++ + 1];
            }
        }
        else if ((copy[i] != ' ' && copy[i + 1] == '|') || (copy[i] == '|' && copy[i + 1] != ' '))
        {
            if (copy[i])
                str[y++] = copy[i];
            str[y++] = ' ';
        }
        else
            str[y++] = copy[i];
        i++;
    }
    str[i] = '\0';
    return (free(copy), str);
}

int check_pipe(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] && str[i + 1] && (str[i] == '|' && str[i + 1] == '|'))
            return (0);
        i++;
    }
    return (1);
}