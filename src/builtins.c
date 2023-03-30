/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:22:48 by luhumber          #+#    #+#             */
/*   Updated: 2023/03/29 20:47:48 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_env(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		printf("%s", tmp->name);
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
}

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
			last = ft_envlast(*env);
			last->next = new;
		}
		else
			*env = new;
	}
}

t_env	*ft_new_env(char *str)
{
	t_env	*new;
	int		temp;
	int		k;

	k = 0;
	temp = 0;
	new = malloc(sizeof(t_env));
	while (str[k] != '=')
		k++;
	new->name = malloc(sizeof(char *) * (k + 1));
	if (!new->name)
		return (NULL);
	while (temp <= k)
	{
		new->name[temp] = str[temp];
		temp++;
	}
	while (str[k])
		k++;
	new->value = malloc(sizeof(char *) * ((k - temp) + 1));
	k = temp;
	temp = 0;
	while (str[k])
		new->value[temp++] = str[k++];
	new->next = NULL;
	return (new);
}

void	ft_struct_env(t_data *data)
{
	int		i;
	t_env	*new;

	i = 0;
	while (data->env_path[i])
	{
		new = ft_new_env(data->env_path[i]);
		ft_envadd_back(&data->env, new);
		i++;
	}
}

char	*ft_builtins(t_data *data)
{
	if (!ft_strncmp(data->cmd[0], "exit", ft_strlen(data->cmd[0])))
		exit(1);
	if (!ft_strncmp(data->cmd[0], "env", ft_strlen(data->cmd[0])))
	{
		ft_struct_env(data);
		ft_print_env(data);
		return (NULL);
	}
	return (data->cmd[0]);
}
