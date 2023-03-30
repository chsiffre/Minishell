/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:15:29 by luhumber          #+#    #+#             */
/*   Updated: 2023/03/30 11:49:40 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_envlast(t_env *lst)
{
	while (lst && lst->next)
		lst = lst->next;
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
	temp = -1;
	new = malloc(sizeof(t_env));
	while (str[k] != '=')
		k++;
	new->name = malloc(sizeof(char *) * (k + 1));
	if (!new->name)
		return (NULL);
	while (++temp <= k)
		new->name[temp] = str[temp];
	new->name[temp] = '\0';
	while (str[k])
		k++;
	new->value = malloc(sizeof(char *) * ((k - temp) + 1));
	k = temp;
	temp = 0;
	while (str[k])
		new->value[temp++] = str[k++];
	new->value[temp] = '\0';
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
