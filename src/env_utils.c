/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:23:01 by luhumber          #+#    #+#             */
/*   Updated: 2023/06/15 13:15:34 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_has_equal(char *str)
{
	int	k;

	k = 0;
	while (str[k])
	{
		if (str[k] == '=')
			return (1);
		k++;
	}
	return (0);
}

char	*ft_switch_value(char *val, char *str, int i)
{
	int	k;

	val = malloc(sizeof(char) * (ft_strlen(str) - i));
	if (!val)
		return (NULL);
	i++;
	k = 0;
	while (str[i])
	{
		val[k] = str[i];
		k++;
		i++;
	}
	val[k] = '\0';
	return (val);
}

char	*ft_add_value(char *str, int i)
{
	char	*val;

	val = NULL;
	val = ft_switch_value(val, str, i);
	if (!val)
		return (NULL);
	return (val);
}

void	ft_exist_var(t_data *data, char *str, t_env *new)
{
	char	*name;
	int		i;

	i = 0;
	name = NULL;
	name = ft_find_name(name, str);
	if (name == NULL)
		ft_error(data, "malloc error\n", 1, 1);
	while (ft_strncmp(new->name, name, ft_strlen(name) - 1))
		new = new->next;
	free(new->name);
	new->name = name;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		free(new->value);
		new->value = ft_add_value(str, i);
		if (!new->value)
			ft_error(data, "malloc error\n", 1, 1);
		if (ft_has_equal(new->name))
			new->equal = 1;
	}
}

void	ft_add_var(t_data *data, char *str, int exist)
{
	t_env	*new;

	new = data->env;
	if (exist == 0)
	{
		new = ft_new_env(str);
		ft_envadd_back(&data->env, new);
	}
	else if (exist == 1)
	{
		ft_exist_var(data, str, new);
	}
}
