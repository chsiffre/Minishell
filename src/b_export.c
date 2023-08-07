/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:22:51 by luhumber          #+#    #+#             */
/*   Updated: 2023/08/07 13:17:52 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    update_env(t_data *data)
{
	int     i;
	t_env   *tmp;
	
	tmp = data->env;
	i = 0;
	if (data->split_path)
		while (data->split_path[i])
			free(data->split_path[i++]);
	free(data->split_path);
	i = 0;
	while (tmp)
	{
		if (tmp->value)
			data->env_path[i] = ft_strjoin(tmp->name, tmp->value);
		else if (tmp->name)
			data->env_path[i] = ft_strdup(tmp->name);
		tmp = tmp->next;
		i++;
	}
	ft_get_env(data);
}

void	ft_print_export(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		printf("declare -x %s", tmp->name);
		if (tmp->value)
			printf("\"%s\"", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
	g_error_last = 0;
}

int	ft_while_export(t_data *data, int i)
{
	int	ret;

	ret = ft_check_exist(data, data->env, data->iterator->content[i]);
	if (data->iterator->content[i])
	{
		if (ret == -1)
			return (ft_export_error(data->iterator->content[i]), -1);
		else if (ret == 0)
			return (ft_add_var(data, data->iterator->content[i], 0), 0);
		else if (ret == 1)
			return (ft_add_var(data, data->iterator->content[i], 1), 0);
		else if (ret == 2)
			return (ft_add_var(data, data->iterator->content[i], 2), 2);
		else
			return (-1);
	}
	return (-1);
}

int	ft_export(t_data *data)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	if (!data->iterator->content[i])
		return (ft_print_export(data), 0);
	while (data->iterator->content[i])
	{
		if (ft_while_export(data, i) == -1)
			error = 1;
		i++;
	}
	if (error == 1)
		g_error_last = 1;
	return (1);
}
