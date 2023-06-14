/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:50:45 by chsiffre          #+#    #+#             */
/*   Updated: 2023/06/07 15:42:16 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *resize_var(char *str, t_data *data)
{
    int i;
    int new_size;
 
    i = -1;
    new_size = 0;
    while (str[++i] && str[i] != '$')
        new_size++;
    while (str[i])
    {
        if (str[i] == '$')
            new_size += check_size_var(str, &i, &new_size, data);
        i++;
    }
    return (malloc(sizeof(char ) * new_size + 1));
}

int check_size_var(char *str, int *i, int *new_size, t_data *data)
{
    t_env   *tmp;
    int     z;
    
    z = -1;
    tmp = data->env;
    (*i)++;
    while (tmp)
    {
        if (ft_compare_var(str, tmp->name, *i))
        {
            z = -1;
            while (tmp->value[++z])
                (*new_size)++;
            while (ft_isalnum(str[*i]))
                (*i)++;
            return (*new_size);
        }
        tmp = tmp->next;
    }
    return (*new_size);
}