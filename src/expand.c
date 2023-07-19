/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:23:56 by chsiffre          #+#    #+#             */
/*   Updated: 2023/07/19 10:17:00 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*replace_var(char *str, char *ret, int *i, t_data *data)
{
	while (str[*i])
	{
		if (str[*i] == '$')
			ret = copy_var(str, ret, i, data);
		(*i)++;
	}
	ret[data->ind] = '\0';
	return (ret);
}

char	*copy_var(char *str, char *ret, int *i, t_data *data)
{
	int		y;
	t_env	*tmp;

	y = 0;
	tmp = data->env;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	(*i)++;
	while (tmp)
	{
		if (ft_compare_var(str, tmp->name, *i))
		{
			while (tmp->value[y])
				ret[data->ind++] = tmp->value[y++];
			while (str[*i] && ft_isalnum(str[*i]))
				(*i)++;
			(*i)--;
			return (ret);
		}
		tmp = tmp->next;
	}
	return (ret);
}

int	var_exist(char *str, int *i, t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	if (str[*i] == '$')
		(*i)++;
	while (tmp)
	{
		if (ft_compare_var(str, tmp->name, *i))
		{
			while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
				(*i)++;
			(*i)++;
			return ((int) ft_strlen(tmp->value));
		}
		tmp = tmp->next;
	}
	return (0);
}

int	is_var(char *str, int i, t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	if (str[i] == '$')
		(i)++;
	while (tmp)
	{
		if (ft_compare_var(str, tmp->name, i))
		{
			while (str[i] && str[i] != '\'' && str[i] != '\"')
				(i)++;
			return ((int) ft_strlen(tmp->value));
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_compare_var(char *s1, char *s2, int i)
{
	int	y;

	y = 0;
	while (s1[i] && s2[y])
	{
		if (s1[i] == '?' && !s1[i + 1])
			return (1);
		if (s1[i] == '\"' || s1[i] == '\'')
			break ;
		if (s1[i] == '$' && s2[y] == '=' && !s2[y + 1])
			return (1);
		if ((s1[i] != s2[y]))
			return (0);
		i++;
		y++;
	}
	if (s2[y] && s2[y] != '=')
		return (0);
	else
		return (1);
}
