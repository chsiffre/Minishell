/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:23:56 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/30 17:23:13 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *ft_expand(char *str, t_data *data)
{
    int i;
    int new_size;
    char *ret;
    
    new_size = ft_strlen(str);
    i = 0;
    ret = malloc(sizeof (char) * ft_strlen(str) + 1);
    if (!ret)
        return (NULL);
    while (i < new_size)
    {
        if (str[i] == '$')
        {
            i++;
            if (var_exist(str, &i, data))
                ret = resize_str(str, ret, data, &new_size);
            return (ret);
        }
        else
            ret[i] = str[i];
        i++;
    }
    ret[i] = '\0';
    return (ret);
}

// char *del_simple(char *str, int i)
// {
//     char *ret;
//     int y;

//     y = 0;
//     i = 0;
//     ret = malloc ((ft_strlen(str) * sizeof (char)) - 2);
//     while (str[i] != '\'')
//         ret[y++] = str[i++];
//     i++;
//     while (str[i] != '\'')
//         ret[y++] = str[i++];
//     ret[y] = '\0';
//     return (free(str), ret);
// }

char *replace_var(char *str, char *ret, t_data *data)
{
    t_env   *tmp;
    int     y;
    int     i;

    i = -1;
    y = 0;
    tmp = data->env;
    while (str[++i] != '$')
        ret[i] = str[i];
    while (tmp)
    {
        if (ft_compare_var(str, tmp->name, i + 1))
        {
            while (tmp->value[y])
            {
                ret[i++] = tmp->value[y++];
            }
            ret[i] = '\0';
            return (ret);
        }
        tmp = tmp->next;
    }
    return (ret);
}

char *resize_str(char *str, char *ret, t_data *data, int *new_size)
{
    t_env *tmp;
    int i;

    i = 1;
    tmp = data->env;
    ret = NULL;
    while (tmp)
    {
        if (var_exist(str, &i, data))
        {
            *new_size = var_exist(str, &i, data);
            ret = malloc((sizeof(char ) * ft_strlen(tmp->value)) + 1);
            if (!ret)
                return (NULL);
            return (replace_var(str, ret, data));
        }
        tmp = tmp->next;
    }
    return (ret);
}