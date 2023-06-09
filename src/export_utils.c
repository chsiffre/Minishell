/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:00:23 by luhumber          #+#    #+#             */
/*   Updated: 2023/06/21 11:51:47 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	ft_loop_check(t_env *tmp, char *name, char *n_equal)
{
	while (tmp)
	{
		if (ft_compare_str(tmp->name, name))
			return (1);
		if (ft_compare_str(tmp->name, n_equal))
			return (1);
		tmp = tmp->next;
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
		ft_error(data, "malloc error\n", 1, 1);
	i++;
	name[i] = '\0';
	ft_strlcpy(name, str, i + 1);
	n_equal = ft_strjoin(name, "=");
	if (ft_loop_check(tmp, name, n_equal) == 1)
		return (free(name), free(n_equal), 1);
	return (free(name), free(n_equal), 0);
}
