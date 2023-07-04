/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/07/04 09:54:59 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_pipe(t_data *data)
{
	t_lst	*tmp;

	tmp = data->lst;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (ft_pipe(data) == 1)
				return (1);
			return (0);
		}
		tmp = tmp->next;
	}
	return (2);
}

int	ft_check_type(t_data *data)
{
	if (ft_check_pipe(data) == 0)
		return (0);
	if (data->lst->type == REDIR)
	{
		if (ft_which_redir(data) == 1)
			return (1);
		return (0);
	}
	else if (data->lst->type == CMD && !data->lst->next)
	{
		ft_make_dup(data);
		if (ft_execute_cmd(data, data->lst->content[0]) == 1)
			return (1);
		return (0);
	}
	else
		return (ft_error(data, "Unexepted command\n", 1, 1), 2);
}

int	ft_parse_exec(t_data *data)
{
	if (empty(data->line) || not_parse(data->line))
		return (0);
	data->line = ft_pre_split(data->line);
	if (!data->line)
		ft_syntax_error("`||'");
	data->lst = ft_parse(data);
	if (data->line && !data->lst)
		ft_syntax_error("`newline'");
	while (data->lst && data->lst->content)
	{
		if (ft_check_type(data) == 1)
			break ;
		if (data->lst == NULL || data->lst->next == NULL)
			break ;
		data->lst = data->lst->next;
	}
	return (1);
}

void	ft_prompt(t_data *data)
{
	int	i;
	int	to_free;

	to_free = 0;
	while (1)
	{
		i = 0;
		signal(SIGINT, ft_ctrl);
		signal(SIGTERM, ft_ctrl);
		signal(SIGQUIT, SIG_IGN);
		data->line = readline("prompt> ");
		if (!data->line)
			ft_exit_pack(data, g_error_last);
		else if (data->line[0] != '\0')
			add_history(data->line);
		while (data->line[i++])
			if (!ft_isascii(data->line[i]))
				ft_error(data, "non printable\n", 2, 0);
		if (ft_parse_exec(data) == 0)
			to_free = 1;
		free(data->line);
		if (to_free == 0)
			free_data(data);
		ft_to_free(data);
	}
}
