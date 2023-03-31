/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:22:51 by luhumber          #+#    #+#             */
/*   Updated: 2023/03/31 13:34:15 by luhumber         ###   ########.fr       */
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
	name[i + 1] = '\0';
	while (i-- >= 0)
		name[i] = str[i];
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name)))
			return (free(name), 1);
		tmp = tmp->next;
	}
	return (free(name), 0);
}

t_env	*ft_add_value(t_data *data, char *str)
{
	t_env	*tmp;
	int		i;
	int		k;
	int		j;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = malloc(sizeof(char *) * i + 1);
	i++;
	name[i + 1] = '\0';
	k = i;
	j = k;
	while (i-- >= 0)
		name[i] = str[i];
	tmp = data->env;
	while (tmp && ft_strncmp(tmp->name, name, ft_strlen(name)))
		tmp = tmp->next;
	if (tmp->value != NULL)
		free(tmp->value);
	while (str[k])
		k++;
	tmp->value = malloc(sizeof(char *) * (k - j) + 1);
	k++;
	tmp->value[k + 1] = '\0';
	while (k-- >= j)
		tmp->value[k - j] = str[k];
	return (tmp);
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
		new = ft_add_value(data, str);
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
	else if (data->cmd[1] && !ft_check_exist(data->env, str))
		ft_add_var(data, str, 0);
	else if (data->cmd[1] && ft_check_exist(data->env, str))
		ft_add_var(data, str, 1);
}
