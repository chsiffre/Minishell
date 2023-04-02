/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:22:51 by luhumber          #+#    #+#             */
/*   Updated: 2023/04/02 13:10:09 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_exist(t_env *env, char *str)
{
	t_env	*tmp;
	int		i;
	char	*name;

	tmp = env;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = malloc(sizeof(char *) * i + 1);
	i++;
	name[i] = '\0';
	while (i-- >= 0)
		name[i] = str[i];
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
			return (free(name), 1);
		tmp = tmp->next;
	}
	return (free(name), 0);
}

char	*ft_find_name(char *name, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*ft_switch_value(char *val, char *str)
{
	int	i;
	int	k;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	val = malloc(sizeof(char *) * (ft_strlen(str) - i));
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

char	*ft_add_value(char *str)
{
	char	*val;
	char	*name;

	val = NULL;
	name = NULL;
	name = ft_find_name(name, str);
	val = ft_switch_value(val, str);
	return (val);
}

void	ft_add_var(t_data *data, char *str, int exist)
{
	t_env	*new;
	char	*name;

	new = data->env;
	if (exist == 0)
	{
		new = ft_new_env(str);
		ft_envadd_back(&data->env, new);
	}
	else if (exist == 1)
	{
		name = NULL;
		name = ft_find_name(name, str);
		while (ft_strncmp(new->name, name, ft_strlen(name)))
			new = new->next;
		new->value = ft_add_value(str);
	}
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
