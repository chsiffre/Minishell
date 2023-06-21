/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/06/14 14:32:58 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lst	*ft_parse(t_data *data)
{
	t_lst	*lst;

	lst = NULL;
	data->res_split = ft_split_charset(data->line, " \t\n\r\v\f");
	if (!data->res_split)
		return (NULL);
	data->res_parse = malloc((ft_strs_len(data->res_split) + 1) * sizeof(char *));
	if (!data->res_parse)
		return (NULL);
	data->res_parse = check_res_split(data);
	data->res_parse = check_quotes(data->res_parse, data);
	lst = ft_convert_in_lst(lst, data);
	if (!lst)
		return (NULL);
	return (lst);
}

char **check_res_split(t_data *data)
{
	int	i;

	i = 0;
	while (data->res_split[i])
	{
		data->res_parse = ft_check_redir(data->res_parse, data, data->res_split, i);
		if (!data->res_parse)
			return (NULL);
		data->res_parse = ft_check_cmd(data->res_parse, data, data->res_split, i);
		while (data->res_split[i] && data->res_split[i][0] != '|')
			i++;
		if (data->res_split[i])
			data->res_parse[data->i++] = ft_strdup(data->res_split[i++]);
	}
	data->res_parse[i] = NULL;
	return (data->res_parse);
}

t_lst	*ft_convert_in_lst(t_lst *lst, t_data *data)
{
	while (data->res_parse[data->y])
	{
		if (ft_is_redir(data->res_parse[data->y]))
		{
			lst = ft_add_lst(lst, data, REDIR);
			if (!lst)
				return (NULL);
			data->y = data->y + 2;
		}
		else if (data->res_parse[data->y] 
			&& !ft_is_redir(data->res_parse[data->y]) && data->res_parse[data->y][0] != '|')
			lst = add_command(lst, data);
		else
			data->y++;
	}
	return (lst);
}

t_lst *add_command(t_lst *lst, t_data *data)
{
	lst = ft_add_lst(lst, data, CMD);
	while (data->res_parse[data->y] && data->res_parse[data->y][0] != '|')
		data->y++;
	if (data->res_parse[data->y])
	{
		lst = ft_add_lst(lst, data, PIPE);
		if (!lst)
			return (NULL);
		data->y++;
	}
	return (lst);
}

int	ft_len_parse(char **strs, int i)
{
	int	size;

	size = 0;
	while (strs[i] && strs[i][0] != '|')
	{
		size++;
		i++;
	}
	return (size);
}
