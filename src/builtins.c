/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:22:48 by luhumber          #+#    #+#             */
/*   Updated: 2023/03/29 18:12:47 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_envlast(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_envadd_back(t_env **env, t_env *new)
{
	t_env	*last;

	if (env)
	{
		if (*env)
		{
			last = ft_lstlast(*env);
			last->next = new;
		}
		else
			*env = new;
	}
}

t_env	*ft_new_env(t_data *data, char *str)
{
	t_env	*new;
	int		temp;
	int		k;

	k = 0;
	temp = 0;
	while (data->env_path[k] != '=')
	{
		new->name = malloc(sizeof(char *) * (k + 1));
		if (!new->name)
			return (NULL);
		while (temp <= k)
			new->name[temp] = data->env_path[temp++];
		while (data->env_path[k])
			k++;
		new->value = malloc(sizeof(char *) * ((k - temp) + 1));
		k = temp;
		temp = 0;
		while (data->env_path[k])
			new->value[temp++] = data->env_path[k++];
		new->next = NULL;
	}
}

t_env	*ft_struct_env(t_data *data, t_env *env)
{
	int		i;
	int		temp;
	t_env	*new;

	i = 0;
	while (data->env_path[i])
	{
		new = ft_new_env(data, data->env_path[i]);
		ft_envadd_back(env, new);
		i++;
	}
}

char	*ft_builtins(t_data *data)
{
	int	i;

	i = 0;
	if (!ft_strncmp(data->cmd[0], "exit", ft_strlen(data->cmd[0])))
		exit(1);
	if (!ft_strncmp(data->cmd[0], "env", ft_strlen(data->cmd[0])))
	{
		data->env = ft_struct_env(data, data->env);
	}
	return (data->cmd[0]);
}
