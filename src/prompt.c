/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/06/21 12:05:43 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*free_data(t_data *data)
{
	int	i;

	i = 0;
	i = 0;
	while (data->res_parse && data->res_parse[i])
	{
		if (data->res_parse[i])
			free(data->res_parse[i++]);
		else
			i++;
	}
	if (data->res_parse)
		free(data->res_parse);
	i = 0;
	while (data->res_split && data->res_split[i])
	{
		if (data->res_split[i])
			free(data->res_split[i++]);
		else
			i++;
	}
	if (data->res_split)
		free(data->res_split);
	return (NULL);
}

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
		{
			if (data->lst->content)
				free(data->lst->content[i++]);
		}
		free(data->lst->content);
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
		return (ft_error(data, "Unexepted command\n", 1, 1), 2);
}

void	ft_parse_exec(t_data *data)
{
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
		data->line = readline("prompt> ");
		if (!data->line)
			ft_exit_pack(data, g_error_last);
		else if (data->line[0] != '\0')
			add_history(data->line);
		while (data->line[i++])
			if (!ft_isascii(data->line[i]))
				ft_error(data, "non printable\n", 2, 0);
		if (data->line[0] != '\0')
			ft_parse_exec(data);
		free(data->line);
		ft_to_free(data);
	}
}
