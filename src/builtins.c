/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/03/30 23:14:32 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

void	ft_print_env(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (tmp->equal == 1)
			printf("%s%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

void	ft_get_pwd(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "PWD=", 5))
			printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
}

void	ft_echo(t_data *data)
{
	if (!ft_strncmp(data->cmd[1], "-n", 2))
		printf("%s", data->cmd[2]);
	else
		printf("%s\n", data->cmd[1]);
}

char	*ft_builtins(t_data *data)
{
	if (!ft_strncmp(data->cmd[0], "echo", 4))
		return (ft_echo(data), NULL);
	if (!ft_strncmp(data->cmd[0], "pwd", 3))
		return (ft_get_pwd(data), NULL);
	if (!ft_strncmp(data->cmd[0], "export", 6))
		return (ft_export(data, data->cmd[1]), NULL);
	if (!ft_strncmp(data->cmd[0], "unset", 5))
		return (ft_unset(data, data->cmd[1]), NULL);
	if (!ft_strncmp(data->cmd[0], "env", 4))
		return (ft_print_env(data), NULL);
	if (!ft_strncmp(data->cmd[0], "exit", 4))
		exit(1);
	return (data->cmd[0]);
}

//TODO les options de export