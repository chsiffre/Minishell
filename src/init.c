/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:39:59 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/09 12:56:51 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data  ft_init_struct(t_data data, char **envp)
{
    data.line = NULL;
    data.lst = NULL;
    data.path = NULL;
    data.split_path = NULL;
    data.cmd = NULL;
    data.res_split = NULL;
    data.i = 0;
    data.y = 0;
    data.pipex = malloc(sizeof(t_data));
    if (!data.pipex)
        return (data);
    data.env_path = envp;
	data.env = NULL;
	data.lst = NULL;
    return (ft_struct_env(&data), data);
}

void    ft_free(t_data *data)
{
    int i;

    i = 0;
    while (data->lst)
    {
        i = 0;
        while (data->lst->content[i])
            free(data->lst->content[i++]);
        free(data->lst);
        data->lst = data->lst->next;
    }
}