/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:08:51 by chsiffre          #+#    #+#             */
/*   Updated: 2023/04/06 17:33:45 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_parse(t_data *data)
{
	data->result = ft_split_charset(data->line, " \t\n\r\v\f");
	if (!data->result)
		return ;
	while (data->result[data->i])
	{
		ft_check_redir(data, data->result, data->i);
		ft_check_cmd(data, data->i);
		data->i = ft_check_builtins(data, data->i);
		if (data->result[data->i] && data->result[data->i][0] == '|')
			ft_add_lst(data, data->result, 2, data->i);
		if (data->result[data->i])
			data->i++;
	}
}

void	ft_add_lst(t_data *data, char **strs, int type, ssize_t i)
{
	t_lst	*new;

	new = ft_lstnew_t(strs, type, i);
	if (!new)
		return ;
	ft_add_back(&data->lst, new);
}

ssize_t	ft_strs_len(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

t_lst	*ft_lstnew_t(char **strs, int type, ssize_t i)
{
	t_lst	*ptr;
	size_t	y;

	y = 0;
	ptr = malloc(sizeof(t_lst));
	if (!ptr)
		return (NULL);
	ptr->content = malloc(sizeof(char *) * ft_strs_len(strs));
	if (!ptr->content)
		return (NULL);
	ptr->type = type;
	if (strs[i][0] == '<' || strs[i][0] == '>')
	{
		ptr->content[y++] = ft_strdup(strs[i++]);
		if (!ptr->content)
			return (NULL);
	}
	ptr->content[y++] = strs[i++];
	while (strs[i] && strs[i][0] == '-')
	{
		ptr->content[y++] = ft_strdup(strs[i++]);
		if (!ptr->content)
			return (NULL);
	}
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
