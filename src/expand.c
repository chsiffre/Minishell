/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:23:56 by chsiffre          #+#    #+#             */
/*   Updated: 2023/06/05 16:29:54 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char *ft_expand(char *str, t_data *data)
// {
//     int i;
//     int new_size;
//     char *ret;
    
//     new_size = ft_strlen(str);
//     i = 0;
//     ret = malloc(sizeof (char) * ft_strlen(str) + 1);
//     if (!ret)
//         return (NULL);
//     while (i < new_size)
//     {
//         if (str[i] == '$')
//         {
//             i++;
//             if (var_exist(str, &i, data))
//                 ret = resize_str(str, ret, data, &new_size);
//         }
//         else
//             ret[i] = str[i];
//         i++;
//     }
//     ret[i] = '\0';
//     return (ret);
// }

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

char *replace_var(char *str, char *ret, int *i, t_data *data)
{
    t_env   *tmp;

    int y;
    y = 0;
    tmp = data->env;
    (*i)++;
    while (tmp)
    {
        if (ft_compare_var(str, tmp->name, *i))
        {
            //printf("%s\n", tmp->value);
            while (tmp->value[y])
                ret[data->ind++] = tmp->value[y++];
            while (str[*i] && ft_isalnum(str[*i]))
                (*i)++;
            return (ret);
        }
        tmp = tmp->next;
    }
    return (ret);
}

// int resize_str(char *str, int *i, t_data *data)
// {
//     t_env *tmp;
//     int new_size;

//     new_size = 0;
//     tmp = data->env;
//     (*i)++;
//     while (tmp)
//     {
//         if (var_exist(str, &i, data))
//         {
//             new_size = var_exist(str, &i, data);
//             return (new_size);
//         }
//         tmp = tmp->next;
//     }
//     return (0);
// }