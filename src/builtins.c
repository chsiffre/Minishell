/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:22:48 by luhumber          #+#    #+#             */
/*   Updated: 2023/03/30 12:19:41 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_env(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		printf("%s", tmp->name);
		printf("%s\n", tmp->value);
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
	return (data->cmd[0]);
}
