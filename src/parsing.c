/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:08:51 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/30 21:45:51 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_parse(t_data *data)
{
	t_lst	*lst;
	ssize_t	i;
	ssize_t	y;

	lst = NULL;
	y = 0;
	i = -1;
	data->result = ft_split_charset(data->line, " \t\n\r\v\f");
	if (!data->result)
		return ;
    while (data->result[++i])
    {
        ft_check_redir(data->result, lst);
        i = ft_check_cmd_builtins(data->result, lst);
        if (data->result[i][y] == '|')
            ft_add_lst(lst, data->result[i], 2);
    }
}

void    ft_add_lst(t_lst *lst, char *str, int type)
{
    t_lst  *new;
    
    new = ft_lstnew_t(str, type);
    if (!new)
        return ;
    ft_add_back(&lst, new);
}

t_lst	*ft_lstnew_t(void *content, int type)
{
	t_lst	*ptr;

	ptr = malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	ptr->type = type;
	ptr->content = content;
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