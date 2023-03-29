/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:08:51 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/29 17:52:03 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ft_parse(t_data *data)
{
    t_lst   *lst;
    ssize_t  i;

    i = -1;
    data->result = ft_split_charset(data->line, " \t\n\r\v\f");
    if (!data->result)
        return ;
    ft_check_redir(data->result, lst);
}

void    ft_check_redir(char **strs, t_lst *lst)
{
    ssize_t i;
    ssize_t y;

    y = 0;
    i = -1;
    while (strs[++i][y] != "|")
    {
        if (strs[i][y] == "<" || strs[i][y] == ">")
        {
            ft_add_lst(lst, strs[i], 0);
            i++;
            ft_add_lst(lst, strs[i], 0);
        }
    }
}

void    ft_add_lst(t_lst **lst, char *str, int type)
{
    t_list  *new;
    
    new = ft_lstnew_t(str, type);
    if (!new)
        return (-1);
    ft_lstadd_back(lst, new);
}

t_list	*ft_lstnew_t(void *content, int type)
{
	t_list	*ptr;
	
	ptr = malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	lst->type = type;
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}
