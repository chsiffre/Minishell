/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:23:07 by luhumber          #+#    #+#             */
/*   Updated: 2023/04/03 18:55:01 by lucas            ###   ########.fr       */
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
	if (ft_compare_str(name, "PWD=")
		|| ft_compare_str(name, "_=")
		|| ft_compare_str(name, "SHLVL="))
		return (printf("minishell: %s: not a valid identifer\n", name), 1);
	return (0);
}

void	ft_unset(t_data *data, char *name)
{
	t_env	*tmp;
	t_env	*prev;

	prev = NULL;
	tmp = data->env;
	if (ft_special_unset(name))
		return ;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name) - 1))
		{
			if (prev == NULL)
				data->env = tmp->next;
			else
				prev->next = tmp->next;
			ft_envdelone(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
