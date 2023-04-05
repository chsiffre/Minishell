/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:23:07 by luhumber          #+#    #+#             */
/*   Updated: 2023/04/05 12:00:12 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_envdelone(t_env *env)
{
	if (env)
	{
		free(env->name);
		free(env->value);
		free(env);
	}
}

int	ft_special_unset(char *name)
{
	if (ft_compare_str(name, "PWD")
		|| ft_compare_str(name, "_")
		|| ft_compare_str(name, "SHLVL"))
		return (printf("minishell: %s: not a valid identifer\n", name), 1);
	return (0);
}

int	ft_find_var(t_data *data, t_env *tmp, char *n_equal, char *name)
{
	t_env	*prev;

	prev = NULL;
	while (tmp)
	{
		if (ft_compare_str(tmp->name, n_equal)
			|| ft_compare_str(tmp->name, name))
		{
			if (prev == NULL)
				data->env = tmp->next;
			else
				prev->next = tmp->next;
			ft_envdelone(tmp);
			return (free(n_equal), 0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

int	ft_unset(t_data *data, char *name)
{
	t_env	*tmp;
	char	*n_equal;
	int		i;

	i = ft_strlen(name);
	tmp = data->env;
	if (ft_special_unset(name))
		return (1);
	if (name[i - 1] == '=')
		return (printf("minishell: %s: not a valid identifer\n", name), 1);
	n_equal = ft_strjoin(name, "=");
	if (ft_find_var(data, tmp, n_equal, name) == 0)
		return (0);
	return (1);
}
