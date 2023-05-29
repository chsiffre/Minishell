/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:23:56 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/29 10:48:02 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *ft_expand(char *str, t_data *data)
{
    int i;
    char f_quote;
    char *ret;
    
    i = 0;
    f_quote = 0;
    ret = NULL;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
            f_quote = str[i];
        if (str[i] == '$')
        {
            if (f_quote == '\'')
                return  (del_simple(str, i));
            else if (f_quote == '\"')
                return (expand_var(str, data));
            else
                return (expand_var(str, data));
        }
        i++;
    }
    return (free(str), register);
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

char *expand_w_double(char *str, t_data *data)
{
    int i;

    i = 0;
    while (data->env)
    {
        if ()
    }   
    return (str);
}
