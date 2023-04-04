/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:08:51 by chsiffre          #+#    #+#             */
/*   Updated: 2023/04/04 17:40:55 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_parse(t_data *data)
{
	ssize_t	i;

	i = 0;
	data->result = ft_split_charset(data->line, " \t\n\r\v\f");
	if (!data->result)
		return ;
    while (data->result[i])
    {
        i = ft_check_redir(data, data->result, i);
        ft_check_cmd(data, i);
		break;
		i = ft_check_builtins(data, i);
        if (data->result[i] && data->result[i][0] == '|')
			ft_add_lst(data, data->result, 2, i);
		if (data->result[i])
			i++;
    }
	i = 0;
	while (data->lst)
	{
		i = 0;
		while (data->lst->content[i])
			printf("%s ", data->lst->content[i++]);
		printf("\n");
		data->lst = data->lst->next;
	}
	exit(1);
}

void	ft_add_lst(t_data *data, char **strs, int type, size_t i)
{
    t_lst  *new;
	
    new = ft_lstnew_t(strs, type, i);
    if (!new)
    	return ;
    ft_add_back(&data->lst, new);
}

t_lst	*ft_lstnew_t(char **strs, int type, size_t i)
{
	t_lst	*ptr;
	size_t	y;
	
	y = 0;
	ptr = malloc(sizeof(t_lst));
	if (!ptr)
		return (NULL);
	ptr->type = type;
	ptr->content = malloc(sizeof(char) * ft_strlen(strs[i]));
	ptr->content = strs;
	printf("%s\n", ptr->content[y]);
	while (strs[i][0] == '-')
		ptr->content[++y] = strs[++i];
	if (strs[i][0] == '<' || strs[i][0] == '>')
		ptr->content[++y] = strs[++i];
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