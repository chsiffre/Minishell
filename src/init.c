/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:39:59 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/24 14:57:23 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_data(t_data *data, char **envp)
{

	data->env_path = envp;
	data->env = NULL;
	data->lst = NULL;
	data->in_redir = 0;
	data->out_redir = 0;
	data->savestdin = dup(0);
	data->savestdout = dup(1);
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
	if (!data.pipex)
		exit(1);
	return (data);
}
