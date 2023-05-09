/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:39:59 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/09 13:59:24 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_struct(t_data *data, char **envp)
{
	data->line = NULL;
	data->lst = NULL;
	data->path = NULL;
	data->split_path = NULL;
	data->cmd = NULL;
	data->res_split = NULL;
	data->i = 0;
	data->y = 0;
	data->pipex = malloc(sizeof(t_pipe));
	if (!data->pipex)
		return ;
	data->env_path = envp;
	data->env = malloc(sizeof(t_env));
	data->lst = NULL;
	//ft_struct_env(data);
    //return (ft_struct_env(data), data);
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