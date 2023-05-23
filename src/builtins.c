/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:02:44 by lucas             #+#    #+#             */
/*   Updated: 2023/05/23 10:39:54 by lucas            ###   ########.fr       */
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
	char	buff[PATH_MAX];

	if (getcwd(buff, PATH_MAX) == NULL)
		ft_error(data, "PWD error\n", 1);
	printf("%s\n", buff);
}

int	ft_old_pwd(t_data *data)
{
	t_env	*tmp;
	char	*pwd;

	tmp = data->env;
	while (tmp && ft_compare_str("PWD=", tmp->name))
		tmp = tmp->next;
	pwd = tmp->value;
	while (tmp && ft_compare_str("OLDPWD=", tmp->name))
		tmp = tmp->next;
	tmp->value = ft_switch_value(tmp->value, pwd);
	return (0);
}

void	ft_cd(t_data *data)
{
	t_env	*tmp;
	int		args;
	
	args = 0;
	tmp = data->env;
	while (data->lst->content[args])
		args++;
	if (args == 1)
	{
		while (tmp)
		{
			if (ft_compare_str(tmp->name, "HOME="))
			{
				if (chdir(tmp->value) == -1)
					perror("bash: ");
			//ft_old_pwd(data);
			}
			tmp = tmp->next;
		}
		return ;
	}
	else if (args == 2)
	{
		if (chdir(data->lst->content[1]) == -1)
			perror("bash: ");
		//ft_old_pwd(data);
	}
	else
		ft_printf("bash: cd: too many arguments\n");
}

int	ft_builtins(t_data *data)
{
	if (ft_compare_str(data->lst->content[0], "echo"))
		return (ft_echo(data), 1);
	else if (ft_compare_str(data->lst->content[0], "cd"))
		return (ft_cd(data), 1);
	else if (ft_compare_str(data->lst->content[0], "pwd"))
		return (ft_get_pwd(data), 1);
	else if (ft_compare_str(data->lst->content[0], "export"))
	{
		if (ft_export(data) == 0)
			return (1);
		return (-1);
	}
	else if (ft_compare_str(data->lst->content[0], "unset"))
		return (ft_unset(data), 1);
	else if (ft_compare_str(data->lst->content[0], "env"))
		return (ft_print_env(data), 1);
	else if (ft_compare_str(data->lst->content[0], "exit"))
	{
		printf("exit\n");
		exit(g_error_last);
	}
	return (0);
}
