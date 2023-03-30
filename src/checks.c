/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:55:39 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/30 16:52:50 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

ssize_t ft_check_cmd_builtins(char **strs, t_lst *lst)
{
    ssize_t i;
    ssize_t y;

    y = 0;
    i = -1;
    while (strs[++i][y] != '|')
    {
        if (strs[i][y] == '<' && strs[i][y] == '>')
            i = i + 2;
        if (!ft_is_builtins(strs[i]))
            ft_add_lst(lst, strs[i], 1);
    }
    i = -1;
    while (strs[++i][y] != '|')
    {
        if (strs[i][y] == '<' && strs[i][y] == '>')
            i = i + 2;
        if (ft_is_builtins(strs[i]))
            ft_add_lst(lst, strs[i], 3);
    }
    return (i);
}

int ft_is_builtins(char *str)
{
	if (!ft_strncmp(str, "exit", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "env", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "unset", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "export", ft_strlen(str)))
		return (1);
	return (0);
}
