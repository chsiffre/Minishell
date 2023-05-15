/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:22:56 by luhumber          #+#    #+#             */
/*   Updated: 2023/05/15 12:52:06 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_here_doc(t_data *data)
{
	char	*line;

	data->limiter = data->lst->content[1];
	while (1)
	{
		line = readline("heredoc>");
		if (ft_compare_str(line, data->limiter))
			break ;
		free(line);
	}
	free(line);
	return (0);
}

int	ft_which_redir(t_data *data)
{
	if (ft_compare_str(data->lst->content[0], ">"))
	{
		data->out_redir = 1;
		data->fd = open
			(data->lst->content[1], O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (dup2(data->fd, STDOUT_FILENO) == -1)
			return (ft_print_error(data->lst->content[1]), 1);
	}
	else if (ft_compare_str(data->lst->content[0], "<"))
	{
		data->in_redir = 1;
		data->fd = open(data->lst->content[1], O_RDONLY, 0644);
		if (dup2(data->fd, STDIN_FILENO) == -1)
			return (ft_print_error(data->lst->content[1]), 1);
	}
	else if (ft_compare_str(data->lst->content[0], "<<"))
		ft_here_doc(data);
	else if (ft_compare_str(data->lst->content[0], ">>"))
	{
		data->fd = open
			(data->lst->content[1], O_RDWR | O_APPEND | O_CREAT, 0644);
		if (dup2(data->fd, STDOUT_FILENO) == -1)
			return (ft_print_error(data->lst->content[1]), 1);
	}
	return (0);
}

int	ft_redirection(t_data *data)
{
	ft_which_redir(data);
	return (0);
}
