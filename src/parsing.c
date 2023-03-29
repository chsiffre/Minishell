/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:08:51 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/29 15:47:32 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ft_parse(t_data *data)
{
    t_lst   *lst;
    ssize_t i;
    ssize_t y;
    
    i = -1;
    y = 0;
    data->result = ft_split_charset(data->line, " \t\n\r\v\f");
    if (!data->result)
        return ;
    while (data->result[++i])
    {
        if (line[i] == "<" || line[i] == ">")
        {
            lst = ft_lstnew(line);
            if (!lst)
                return ;
            ft_lstadd_back(lst, line);
            
            
        }
    }
}