/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:50:45 by chsiffre          #+#    #+#             */
/*   Updated: 2023/06/06 15:27:19 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *resize_var(char *str, t_data *data)
{
    t_env   *tmp;
    int i;
    int new_size;
 
    i = 0;
    new_size = 0;
    tmp = data->env;
    
    while (str[i++] && str[i] != '$')
        new_size++;
    while (tmp)
    {
        if (ft_compare_var(str, tmp->name, i))
        {
            i = -1;
            while (tmp->value[++i])
                new_size++;
            break;
        }
        tmp = tmp->next;
    }
    return (malloc(sizeof(char ) * new_size + 1));
}