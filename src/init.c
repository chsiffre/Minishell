/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:39:59 by chsiffre          #+#    #+#             */
/*   Updated: 2023/04/06 13:04:27 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data  ft_init_struct(t_data data)
{
    data.line = NULL;
    data.lst = NULL;
    data.path = NULL;
    data.split_path = NULL;
    data.cmd = NULL;
    data.result = NULL;
    data.i = 0;
    return (data);
}

// t_lst   ft_init_lst(t_lst lst, char *str)
// {
    
//     return (lst);
// }