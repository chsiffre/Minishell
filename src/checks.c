/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:55:39 by chsiffre          #+#    #+#             */
/*   Updated: 2023/04/27 12:05:13 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_check_redir(t_data *data, char **strs, ssize_t i)
{

	while (strs[i] && strs[i][0] != '|')
	{
		if (strs[i][0] == '<' || strs[i][0] == '>')
		{
			ft_add_lst(data, strs, 0, i);
			if (strs[i][0] == '<')
			{
				if (strs[i + 1])
					data->i = i + 2;
			}
			if (strs[i + 1])
				i = i + 2;
		}
		else
			i++;
	}
}

ssize_t	ft_check_builtins(t_data *data, ssize_t i)
{
	while (data->result[i] && data->result[i][0] != '|')
	{
		if (data->result[i][0] == '<' || data->result[i][0] == '>')
			if (data->result[i + 1])
				i = i + 2;
		if (data->result[i] && data->result[i][0] != '|')
		{
			if (ft_is_builtins(data->result[i]))
				ft_add_lst(data, data->result, 1, i);
			if (data->result[i])
				i++;
		}
	}
	return (i);
}

void	ft_check_cmd(t_data *data, ssize_t i)
{
	while (data->result[i] && data->result[i][0] != '|')
	{
		if ((data->result[i][0] == '<' || data->result[i][0] == '>'))
		{
			if (data->result[i + 1])
				i = i + 2;
		}
		if (data->result[i] && data->result[i][0] != '|'
			&& data->result[i][0] != '-' && !ft_is_builtins(data->result[i]))
		{
			ft_add_lst(data, data->result, 1, i++);
			while (data->result[i] && data->result[i][0] == '-')
				i++;
		}
		else
			i++;
	}
}

int	ft_is_builtins(char *str)
{
	if (!ft_strncmp(str, "exit", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "env", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "unset", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "export", ft_strlen(str)))
		return (1);
	return (0);
}
