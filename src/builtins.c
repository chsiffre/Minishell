/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/04/04 15:11:29 by lucas            ###   ########.fr       */
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

void	ft_cd(t_data *data)
{
	t_env	*tmp;
	int		args;

	args = 0;
	tmp = data->env;
	while (data->cmd[args])
		args++;
	if (args == 1)
	{
		while (tmp)
		{
			if (ft_compare_str(tmp->name, "HOME="))
				if (chdir(tmp->value) == -1)
					perror("Minishell: ");
			tmp = tmp->next;
		}
		return ;
	}
	else if (args == 2)
	{
		if (chdir(data->cmd[1]) == -1)
			perror("Minishell: ");
	}
	else
		ft_printf("Minishell : cd : too many arguments\n");
}

char	*ft_builtins(t_data *data)
{
	if (ft_compare_str(data->cmd[0], "echo"))
		return (ft_echo(data), NULL);
	if (ft_compare_str(data->cmd[0], "cd"))
		return (ft_cd(data), NULL);
	if (ft_compare_str(data->cmd[0], "pwd"))
		return (ft_get_pwd(), NULL);
	if (ft_compare_str(data->cmd[0], "export"))
		return (ft_export(data, data->cmd[1]), NULL);
	if (ft_compare_str(data->cmd[0], "unset"))
		return (ft_unset(data, data->cmd[1]), NULL);
	if (ft_compare_str(data->cmd[0], "env"))
		return (ft_print_env(data), NULL);
	if (ft_compare_str(data->cmd[0], "exit"))
		exit(1);
	return (data->cmd[0]);
}
