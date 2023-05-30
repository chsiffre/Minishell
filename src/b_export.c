/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:22:51 by luhumber          #+#    #+#             */
/*   Updated: 2023/05/30 13:41:48 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_export_error(char *str)
{
	char	*join;

	join = ft_strjoin("bash: export: '", str);
	join = ft_strjoin(join, "' not a valid indentifier\n");
	write(2, join, ft_strlen(join));
	free(join);
	return (1);
}

int	ft_check_isok(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) == 0 && str[i] != '_')
		return (1);
	while (str[i] && str[i + 1] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_exist(t_data *data, t_env *env, char *str)
{
	t_env	*tmp;
	int		i;
	char	*name;
	char	*n_equal;

	tmp = env;
	i = 0;
	if (ft_check_isok(str) == 1)
		return (-1);
	while (str[i] && str[i + 1] != '=')
		i++;
	name = malloc(sizeof(char *) * i + 1);
	if (!name)
		ft_error(data, "malloc error\n", 1);
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
			printf("\"%s\"", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
}

int	ft_export(t_data *data)
{
	int	i;

	i = 1;
	if (!data->lst->content[i])
		return (ft_print_export(data), 0);
	while (data->lst->content[i])
	{
		if (data->lst->content[i]
			&& ft_check_exist(data, data->env, data->lst->content[i]) == -1)
			ft_export_error(data->lst->content[i]);
		else if (data->lst->content[i]
			&& ft_check_exist(data, data->env, data->lst->content[i]) == 0)
			ft_add_var(data, data->lst->content[i], 0);
		else if (data->lst->content[i]
			&& ft_check_exist(data, data->env, data->lst->content[i]) == 1)
			ft_add_var(data, data->lst->content[i], 1);
		else
			return (1);
		i++;
	}
	return (1);
}
