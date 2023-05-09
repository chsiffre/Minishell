/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:08:51 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/09 12:59:53 by chsiffre         ###   ########.fr       */
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
	data->res_parse = malloc((ft_strs_len(data->res_split) + 1) * sizeof(char *));
	if (!data->res_parse)
		return (NULL);
	while (data->res_split[i])
	{
		data->res_parse = ft_check_redir(data->res_parse, data, data->res_split, i);
		data->res_parse = ft_check_cmd(data->res_parse, data, data->res_split, i);
		while (data->res_split[i] && data->res_split[i][0] != '|')
			i++;
		if (data->res_split[i])
			data->res_parse[data->i++] = data->res_split[i++];
	}
	data->res_parse[i] = '\0';
	lst = ft_convert_in_lst(lst, data);
	/*
	i = 0;
	while (lst)
	{
		i = -1;
		while (lst->content[++i])
			printf("[%s] ", lst->content[i]);
		printf("\n");
		lst = lst->next;
	}*/
	return (lst);
}

t_lst	*ft_convert_in_lst(t_lst *lst, t_data *data)
{
	while (data->res_parse[data->y])
	{
		if (ft_is_redir(data->res_parse[data->y]))
		{
			lst = ft_add_lst(lst, data, REDIR, 2);
			data->y = data->y + 2;
		}
		else if (data->res_parse[data->y] && !ft_is_redir(data->res_parse[data->y]))
		{
			lst = ft_add_lst(lst, data, CMD, ft_len_parse(data->res_parse, data->y));
			while (data->res_parse[data->y] && data->res_parse[data->y][0] != '|')
				data->y++;
			if (data->res_parse[data->y])
			{
				lst = ft_add_lst(lst, data, PIPE, 1);
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

t_lst	*ft_add_lst(t_lst *lst,t_data *data, int type, int size)
{
	t_lst	*new;

	new = ft_lstnew_t(data->res_parse, type, data->y, size);
	if (!new)
		return (NULL);
	ft_add_back(&lst, new);
	return (lst);
}

ssize_t	ft_strs_len(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

t_lst	*ft_lstnew_t(char **strs, int type, ssize_t i, int size)
{
	t_lst	*ptr;
	size_t	y;

	y = 0;
	ptr = malloc(sizeof(t_lst));
	if (!ptr)
		return (NULL);
	ptr->content = malloc(sizeof(char *) * (ft_strs_len(strs) + 1));
	ptr->content = malloc(sizeof(char *) * (size + 1));
	if (!ptr->content)
		return (NULL);
	ptr->type = type;
	if (strs[i] && ft_is_redir(strs[i]))
	{
		ptr->content[y++] = strs[i++];
		ptr->content[y++] = strs[i++];
	}
	else if (strs[i] && !ft_is_redir(strs[i]) && strs[i][0] != '|')
	{
		while (strs[i] && strs[i][0] != '|')
			ptr->content[y++] = strs[i++];
	}
	else
		ptr->content[y++] = strs[i++];
	ptr->content[y] = 0;
	ptr->next = NULL;
	return (ptr);
}

t_lst	*ft_last(t_lst *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_add_back(t_lst **lst, t_lst *new)
{
	t_lst	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_last(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}
