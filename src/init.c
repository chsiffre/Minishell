/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:39:59 by chsiffre          #+#    #+#             */
/*   Updated: 2023/04/24 11:30:03 by luhumber         ###   ########.fr       */
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
    data.pipex = malloc(sizeof(t_data));
    return (data);
}
