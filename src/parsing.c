/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/05/29 10:12:12 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../include/minishell.h"

t_lst	*ft_parse(t_data *data)
{
	t_lst	*lst;
	int		i;

	i = 0;
	lst = NULL;
	data->res_split = ft_split_charset(data->line, " \t\n\r\v\f");
	if (!data->res_split)
		return (NULL);
	// while (data->res_split[i])
	// 	printf("%s\n", data->res_split[i++]);
	// exit(1);
	data->res_parse = malloc((ft_strs_len(data->res_split) + 1) * sizeof(char *));
	if (!data->res_parse)
		return (NULL);
	while (data->res_split[i])
	{
		data->res_parse = ft_check_redir(data->res_parse, data, data->res_split, i);
		if (!data->res_parse)
			return (NULL);
		data->res_parse = ft_check_cmd(data->res_parse, data, data->res_split, i);
		while (data->res_split[i] && data->res_split[i][0] != '|')
			i++;
		if (data->res_split[i])
			data->res_parse[data->i++] = data->res_split[i++];
	}
	data->res_parse[i] = NULL;
	lst = ft_convert_in_lst(lst, data);
	if (!lst)
		return (NULL);
	// i = 0;
	// while (lst)
	// {
	// 	i = -1;
	// 	while (lst->content[++i])
	// 		printf("[%s] ", lst->content[i]);
	// 	printf("\n");
	// 	lst = lst->next;
	// }
	// exit(1);
	return (lst);
}

t_lst	*ft_convert_in_lst(t_lst *lst, t_data *data)
{
	while (data->res_parse[data->y])
	{
		if (ft_is_redir(data->res_parse[data->y]))
		{
			lst = ft_add_lst(lst, data, REDIR, 2);
			if (!lst)
				return (NULL);
			data->y = data->y + 2;
		}
		else if (data->res_parse[data->y] && !ft_is_redir(data->res_parse[data->y]) && data->res_parse[data->y][0] != '|')
		{
			lst = ft_add_lst(lst, data, CMD, ft_len_parse(data->res_parse, data->y));
			while (data->res_parse[data->y] && data->res_parse[data->y][0] != '|')
				data->y++;
			if (data->res_parse[data->y])
			{
				lst = ft_add_lst(lst, data, PIPE, 1);
				if (!lst)
					return (NULL);
				data->y++;
			}
		}
		else
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
