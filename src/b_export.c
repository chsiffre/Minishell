/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:22:51 by luhumber          #+#    #+#             */
/*   Updated: 2023/04/04 14:14:50 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_exist(t_env *env, char *str)
{
	t_env	*tmp;
	int		i;
	char	*name;
	char	*n_equal;

	tmp = env;
	i = 0;
	while (str[i] && str[i + 1] != '=')
		i++;
	name = malloc(sizeof(char *) * i + 1);
	if (!name)
		return (1);
	i++;
	name[i] = '\0';
	ft_strlcpy(name, str, i + 1);
	n_equal = ft_strjoin(name, "=");
	while (tmp)
	{
		if (ft_compare_str(tmp->name, name))
			return (free(name), free(n_equal), 1);
		if (ft_compare_str(tmp->name, n_equal))
			return (free(name), free(n_equal), 1);
		tmp = tmp->next;
	}
	return (free(name), free(n_equal), 0);
}

void	ft_print_export(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		printf("declare -x %s", tmp->name);
		if (tmp->value)
			printf("%s", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
}

void	ft_export(t_data *data, char *str)
{
	if (!data->cmd[1])
		ft_print_export(data);
	else if (data->cmd[1] && ft_check_exist(data->env, str) == 0)
		ft_add_var(data, str, 0);
	else if (data->cmd[1] && ft_check_exist(data->env, str) == 1)
		ft_add_var(data, str, 1);
}
