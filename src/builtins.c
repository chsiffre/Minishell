/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/03/30 16:29:45 by lucas            ###   ########.fr       */
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
		{
			printf("%s", tmp->name);
			printf("%s\n", tmp->value);
		}
		tmp = tmp->next;
	}
}

char	*ft_builtins(t_data *data)
{
	if (!ft_strncmp(data->cmd[0], "exit", ft_strlen(data->cmd[0])))
		exit(1);
	if (!ft_strncmp(data->cmd[0], "env", ft_strlen(data->cmd[0])))
		return (ft_print_env(data), NULL);
	if (!ft_strncmp(data->cmd[0], "unset", ft_strlen(data->cmd[0])))
		return (ft_unset(data, data->cmd[1]), NULL);
	if (!ft_strncmp(data->cmd[0], "export", ft_strlen(data->cmd[0])))
		return (ft_export(data, data->cmd[1]), NULL);
	return (data->cmd[0]);
}


//TODO enlever les var sans = de env