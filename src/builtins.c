/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/04/03 16:35:48 by luhumber         ###   ########.fr       */
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

void	ft_get_pwd(void)
{
	char	buff[PATH_MAX];

	if (getcwd(buff, PATH_MAX) == NULL)
	{
		printf("ERREUR PWD\n");
		exit(1);
	}
	printf("%s\n", buff);
}

void	ft_echo(t_data *data)
{
	if (!ft_strncmp(data->cmd[1], "-n", 2))
		printf("%s", data->cmd[2]);
	else
		printf("%s\n", data->cmd[1]);
}

void	ft_cd(t_data *data)
{
	chdir(data->cmd[1]);
}

char	*ft_builtins(t_data *data)
{
	if (!ft_strncmp(data->cmd[0], "echo", ft_strlen(data->cmd[0])))
		return (ft_echo(data), NULL);
	if (!ft_strncmp(data->cmd[0], "cd", ft_strlen(data->cmd[0])))
		return (ft_cd(data), NULL);
	if (!ft_strncmp(data->cmd[0], "pwd", ft_strlen(data->cmd[0])))
		return (ft_get_pwd(), NULL);
	if (!ft_strncmp(data->cmd[0], "export", ft_strlen(data->cmd[0])))
		return (ft_export(data, data->cmd[1]), NULL);
	if (!ft_strncmp(data->cmd[0], "unset", ft_strlen(data->cmd[0])))
		return (ft_unset(data, data->cmd[1]), NULL);
	if (!ft_strncmp(data->cmd[0], "env", ft_strlen(data->cmd[0])))
		return (ft_print_env(data), NULL);
	if (!ft_strncmp(data->cmd[0], "exit", ft_strlen(data->cmd[0])))
		exit(1);
	return (data->cmd[0]);
}
