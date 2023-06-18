/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:07:27 by luhumber          #+#    #+#             */
/*   Updated: 2023/06/15 13:14:55 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(t_data *data)
{
	char	buff[REP_MAX];
	char	*str;

	if (ft_check_exist(data, data->env, "PWD=") == 0)
		return (1);
	if (getcwd(buff, REP_MAX) == NULL)
		ft_error(data, "PWD error\n", 1, 1);
	str = ft_strjoin("PWD=", buff);
	ft_add_var(data, str, 1);
	free(str);
	return (0);
}

int	ft_old_pwd(t_data *data)
{
	char	buff[REP_MAX];
	char	*str;

	if (ft_check_exist(data, data->env, "OLDPWD=") == 0)
		return (1);
	if (getcwd(buff, REP_MAX) == NULL)
		ft_error(data, "PWD error\n", 1, 1);
	str = ft_strjoin("OLDPWD=", buff);
	ft_add_var(data, str, 1);
	free(str);
	return (0);
}

int	ft_algo_cd(t_data *data, char *rep)
{
	ft_old_pwd(data);
	if (chdir(rep) == -1)
		ft_print_error(rep);
	ft_pwd(data);
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
				ft_algo_cd(data, tmp->value);
				return ;
			}
			tmp = tmp->next;
		}
		write(2, "bash: cd: HOME not set\n", 24);
	}
	else if (args == 2)
		ft_algo_cd(data, data->lst->content[1]);
	else
		ft_printf("bash: cd: too many arguments\n");
}
