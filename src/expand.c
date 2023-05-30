/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:23:56 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/30 13:51:21 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *ft_expand(char *str, t_data *data)
{
    int i;
    int new_size;
    char *ret;
    
    new_size = 0;
    i = 0;
    ret = resize_str(str, data, &new_size);
    while (i < new_size)
    {
        if (*str == '$')
        {
            if (var_exist(str, data))
                ret = replace_var(str, ret, &i, data);
        }
        else
            ret[i++] = *str;
        str++;
    }
    ret[i] = '\0';
    return (free(str), ret);
}

char *del_simple(char *str, int i)
{
    char *ret;
    int y;

    y = 0;
    i = 0;
    ret = malloc ((ft_strlen(str) * sizeof (char)) - 2);
    while (str[i] != '\'')
        ret[y++] = str[i++];
    i++;
    while (str[i] != '\'')
        ret[y++] = str[i++];
    ret[y] = '\0';
    return (free(str), ret);
}

char *replace_var(char *str, char *ret, int *i, t_data *data)
{
    t_env   *tmp;
    int     y;

    y = 0;
    tmp = data->env;
    while (tmp)
    {
        if (ft_compare_var(str, tmp->name))
        {
            while (tmp->value[y])
                ret[(*i)++] = tmp->value[y++];
        }
    }
    return (ret);
}