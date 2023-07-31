/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:02:44 by lucas             #+#    #+#             */
/*   Updated: 2023/07/31 17:22:43 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_error(t_data *data)
{
	ft_printf_fd("env: '%s': No such file or directory\n",
		2, data->iterator->content[1]);
	g_error_last = 127;
}

void	ft_print_env(t_data *data)
{
	t_env	*tmp;

	if (data->iterator->content[1] != NULL)
	{
		env_error(data);
		return ;
	}
	tmp = data->env;
	while (tmp)
	{
		if (tmp->equal == 1)
			printf("%s%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	g_error_last = 0;
}

void	ft_get_pwd(t_data *data)
{
	char	buff[REP_MAX];

	if (getcwd(buff, REP_MAX) == NULL)
		ft_error(data, "PWD error\n", 1, 1);
	printf("%s\n", buff);
	g_error_last = 0;
}

int	ft_builtins(t_data *data)
{
	if (ft_compare_str(data->iterator->content[0], "echo"))
		return (ft_echo(data), 1);
	else if (ft_compare_str(data->iterator->content[0], "cd"))
		return (ft_cd(data), 1);
	else if (ft_compare_str(data->iterator->content[0], "pwd"))
		return (ft_get_pwd(data), 1);
	else if (ft_compare_str(data->iterator->content[0], "export"))
	{
		if (ft_export(data) == 0)
			return (1);
		return (-1);
	}
	else if (ft_compare_str(data->iterator->content[0], "unset"))
		return (ft_unset(data), 1);
	else if (ft_compare_str(data->iterator->content[0], "env"))
		return (ft_print_env(data), 1);
	else if (ft_compare_str(data->iterator->content[0], "exit"))
		return (ft_exit(data), 1);
	return (0);
}
