/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:23:07 by luhumber          #+#    #+#             */
/*   Updated: 2023/03/30 12:09:32 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_del((void *))
{
	
}

void	ft_envdelone(t_env *env, void (*del)(void *))
{
	if (!del)
		return ;
	if (env)
	{
		del((env->name));
		del((env->value));
		free (env);
	}
}

void	ft_unset(t_data *data, char *name)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = data->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name))
			ft_envdelone(tmp, ft_del());
	}
}
