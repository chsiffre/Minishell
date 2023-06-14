/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/06/14 11:49:24 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_to_free(t_data *data)
{
	int		i;
	t_lst	*next;

	next = NULL;
	while (data->lst != NULL)
	{
		next = data->lst->next;
		i = 0;
		while (data->lst->content[i])
			free(data->lst->content[i++]);
		free(data->lst);
		data->lst = next;
	}
	ft_close_end(data);
	data->in_redir = 0;
	data->out_redir = 0;
	data->i = 0;
	data->y = 0;
	data->ind = 0;
}

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
		return (ft_error(data, "Unexepted command\n", 1), 2);
}

void	ft_parse_exec(t_data *data)
{
	data->line = ft_pre_split(data->line);
	if (!data->line)
		ft_write_error("bash: syntax error near unexpected token `||'");
	data->lst = ft_parse(data);
	if (data->line && !data->lst)
		ft_write_error
			("syntax error near unexpected token `newline'");
	while (data->lst && data->lst->content)
	{
		if (ft_check_type(data) == 1)
			break ;
		if (data->lst == NULL || data->lst->next == NULL)
			break ;
		data->lst = data->lst->next;
	}
}

void	ft_prompt(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		signal(SIGINT, ft_ctrl);
		signal(SIGTERM, ft_ctrl);
		signal(SIGQUIT, SIG_IGN);
		//data->line = readline("prompt> ");
		data->line = "echo   \"$USER\"";
		if (!data->line)
			ft_rl_error(data);
		else if (data->line[0] != '\0')
			add_history(data->line);
		while (data->line[i++])
			if (!ft_isascii(data->line[i]))
				ft_error(data, "non printable\n", 1);
		if (data->line[0] != '\0')
			ft_parse_exec(data);
		free(data->line);
		ft_to_free(data);
		exit(1);
	}
}
