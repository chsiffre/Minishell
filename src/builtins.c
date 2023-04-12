/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:02:44 by lucas             #+#    #+#             */
/*   Updated: 2023/04/12 16:42:42 by luhumber         ###   ########.fr       */
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
		ft_printf("Minishell: cd : too many arguments\n");
}

int	ft_builtins(t_data *data)
{
	if (ft_compare_str(data->lst->content[0], "echo"))
		return (ft_echo(data), 1);
	else if (ft_compare_str(data->lst->content[0], "cd"))
		return (ft_cd(data), 1);
	else if (ft_compare_str(data->lst->content[0], "pwd"))
		return (ft_get_pwd(), 1);
	else if (ft_compare_str(data->lst->content[0], "export"))
		return (ft_export(data), 1);
	else if (ft_compare_str(data->lst->content[0], "unset"))
		return (ft_unset(data, data->lst->content[1]), 1);
	else if (ft_compare_str(data->lst->content[0], "env"))
		return (ft_print_env(data), 1);
	else if (ft_compare_str(data->lst->content[0], "exit"))
	{
		printf("exit\n");
		exit(1);
	}
	return (0);
}
