/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:08:51 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/30 16:32:56 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ft_parse(t_data *data)
{
    t_lst   *lst;
    ssize_t i;
    ssize_t y;

    y = 0;
    i = -1;
    data->result = ft_split_charset(data->line, " \t\n\r\v\f");
    if (!data->result)
        return ;
    while (data->result[++i])
    {
        ft_check_redir(data->result, lst);
        i = check_cmd(data->result, lst,1);
        if (data->result[i][y] == '|')
            ft_add_lst(lst, data->result[i], 2);
    }
}

void    ft_check_redir(char **strs, t_lst *lst)
{
    ssize_t i;
    ssize_t y;

    y = 0;
    i = -1;
    while (strs[++i][y] != '|')
    {
        if (strs[i][y] == '<' || strs[i][y] == '>')
        {
            ft_add_lst(lst, strs[i], 0);
            i++;
            ft_add_lst(lst, strs[i], 0);
        }
    }
}

ssize_t ft_check_cmd(char **strs, t_lst *lst, int type)
{
    ssize_t i;
    ssize_t y;

    y = 0;
    i = -1;
    while (strs[++i][y] != '|')
    {
        if (strs[i][y] == '<' && strs[i][y] == '>')
            i = i + 2;
        if (ft_bultins())
            ft_add_lst(lst, strs[i], 2);
    }
    return (i);
}

void    ft_add_lst(t_lst **lst, char *str, int type)
{
    t_list  *new;
    
    new = ft_lstnew_t(str, type);
    if (!new)
        return (-1);
    ft_lstadd_back(lst, new);
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
