/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:39:59 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/09 15:17:50 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_data(t_data *data, char **envp)
{
	data->env_path = envp;
	data->env = NULL;
	data->lst = NULL;
	ft_struct_env(data);
}

t_data	ft_init_struct(t_data data)
{
	data.line = NULL;
	data.lst = NULL;
	data.path = NULL;
	data.split_path = NULL;
	data.cmd = NULL;
	data.res_split = NULL;
	data.i = 0;
	data.y = 0;
	data.pipex = malloc(sizeof(t_pipe));
	return (data);
}
