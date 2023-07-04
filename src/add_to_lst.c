/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:11:52 by charles           #+#    #+#             */
/*   Updated: 2023/07/04 09:57:08 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lst	*ft_lstnew_t(char **strs, int type, ssize_t i)
{
	t_lst	*ptr;
	size_t	y;

	y = 0;
	ptr = malloc(sizeof(t_lst) + 1);
	if (!ptr)
		return (NULL);
	ptr->content = malloc(sizeof(char *) * (ft_strs_len(strs) + 1));
	if (!ptr->content)
		return (NULL);
	ptr->type = type;
	if (strs[i] && ft_is_redir(strs[i]))
	{
		ptr->content[y++] = ft_strdup(strs[i++]);
		if (!strs[i] || strs[i][0] == '|')
			return (NULL);
		ptr->content[y++] = ft_strdup(strs[i++]);
	}
	else if (strs[i] && !ft_is_redir(strs[i]) && strs[i][0] != '|')
	{
		while (strs[i] && strs[i][0] != '|')
			ptr->content[y++] = ft_strdup(strs[i++]);
	}
	else
		ptr->content[y++] = ft_strdup(strs[i++]);
	ptr->content[y] = 0;
	ptr->next = NULL;
	return (ptr);
}

t_lst	*ft_add_lst(t_lst *lst, t_data *data, int type)
{
	t_lst	*new;

	new = ft_lstnew_t(data->res_parse, type, data->y);
	if (!new)
		return (NULL);
	ft_add_back(&lst, new);
	return (lst);
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

ssize_t	ft_strs_len(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}
